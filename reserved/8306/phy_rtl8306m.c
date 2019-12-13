#include "esp_attr.h"
#include "esp_log.h"
#include "esp_eth.h"

#include "eth_phy/phy_rtl8306m.h"
#include "eth_phy/phy_reg.h"

/* Value of MII_PHY_IDENTIFIER_REGs for Microchip RTL8306M
 * (Except for bottom 4 bits of ID2, used for model revision)
 */
#define RTL8306M_PHY_ID1 		0x001C
#define RTL8306M_PHY_ID2 		0xC850
#define RTL8306M_PHY_ID2_MASK 	0xFFF0


#define MII_BASIC_MODE_CONTROL_REG          (0x0)
#define MII_SOFTWARE_RESET                     BIT(15)

#define MII_BASIC_MODE_STATUS_REG           (0x1)
#define MII_AUTO_NEGOTIATION_COMPLETE          BIT(5)
#define MII_LINK_STATUS                        BIT(2)

#define MII_PHY_IDENTIFIER_1_REG              (0x2)
#define MII_PHY_IDENTIFIER_2_REG              (0x3)

#define MII_AUTO_NEG_ADVERTISEMENT_REG      (0x4)
#define MII_ASM_DIR                            BIT(11)
#define MII_PAUSE                              BIT(10)

#define MII_PHY_LINK_PARTNER_ABILITY_REG    (0x5)
#define MII_PARTNER_ASM_DIR                    BIT(11)
#define MII_PARTNER_PAUSE                      BIT(10)

/* RTL8306M-specific registers */
#define PORT5_PHY_CONTROL_REG0						(0x16)
#define PORT5_LINK_STATUS							BIT(15)
#define PORT5_LOCAL_LOOPBACK						BIT(13)
#define PORT5_NULL_VID_REPLACEMENT					BIT(12)
#define PORT5_NON_PVID_PACKERS_DISCARD				BIT(11)
#define PORT5_802_1P_PRIORITY_DISABLE				BIT(10)
#define PORT5_DIFFSERV_PRIORITY_DISABLE				BIT(9)
#define PORT5_PORTBASE_PRIORITY_DISABLE				BIT(8)
#define PORT5_AUTO_NEGOTITATION_ENABLE				BIT(6)
#define PORT5_SPEED_INDICATION_100T              	BIT(5)
#define PORT5_DUPLEX_INDICATION_FULL               	BIT(4)
#define PORT5_802_3X_FLOW_CONTROL_ABILITY			BIT(3)
#define PORT5_BACKPRESSURE_ENABLE					BIT(2)

#define PORT5_PHY_CONTROL_REG1						(0x18)
#define DISABLE_TRANSMIT_FLOW_CONTROL_OF_PORT5_MAC	BIT(14)
#define DISABLE_RECEIVE_FLOW_CONTROL_OF_PORT5_MAC	BIT(13)
#define FORCE_ASYM_FLOW_CONTROL_OF_PORT5_MAC		BIT(12)
#define PORT5_TRANSMISSION_ENABLE					BIT(11)
#define PORT5_RECEPTION_ENABLE						BIT(10)
#define PORT5_LEARNING_ENABLE						BIT(9)
#define PORT5_LOOP_STATUS							BIT(8)


static const char *TAG = "rtl8306m";

void phy_rtl8306m_check_phy_init(void)
{
    phy_rtl8306m_dump_registers();

    esp_eth_smi_wait_set(MII_BASIC_MODE_STATUS_REG, MII_AUTO_NEGOTIATION_COMPLETE, 0);
}

eth_speed_mode_t phy_rtl8306m_get_speed_mode(void)
{
    if(esp_eth_smi_read(PORT5_PHY_CONTROL_REG0) & PORT5_SPEED_INDICATION_100T) {
        ESP_LOGD(TAG, "phy_rtl8306m_get_speed_mode(100)");
        return ETH_SPEED_MODE_100M;
    } else {
        ESP_LOGD(TAG, "phy_rtl8306m_get_speed_mode(10)");
        return ETH_SPEED_MODE_10M;
    }
}

eth_duplex_mode_t phy_rtl8306m_get_duplex_mode(void)
{
    if(esp_eth_smi_read(PORT5_PHY_CONTROL_REG0) & PORT5_DUPLEX_INDICATION_FULL) {
        ESP_LOGD(TAG, "phy_rtl8306m_get_duplex_mode(FULL)");
        return ETH_MODE_FULLDUPLEX;
    } else {
        ESP_LOGD(TAG, "phy_rtl8306m_get_duplex_mode(HALF)");
        return ETH_MODE_HALFDUPLEX;
    }
}

void phy_rtl8306m_power_enable(bool enable)
{
	uint32_t data = esp_eth_smi_read(MII_AUTO_NEG_ADVERTISEMENT_REG);
    data |= MII_PAUSE;
    esp_eth_smi_write(MII_AUTO_NEG_ADVERTISEMENT_REG, data);
}

void phy_rtl8306m_init(void)
{
	ESP_LOGD(TAG, "phy_rtl8306m_init()");
    phy_rtl8306m_dump_registers();

    esp_eth_smi_write(MII_BASIC_MODE_CONTROL_REG, MII_SOFTWARE_RESET);

    esp_err_t res1, res2;
    do {
        // Call esp_eth_smi_wait_value() with a timeout so it prints an error periodically
        res1 = esp_eth_smi_wait_value(MII_PHY_IDENTIFIER_1_REG, RTL8306M_PHY_ID1, UINT16_MAX, 1000);
        res2 = esp_eth_smi_wait_value(MII_PHY_IDENTIFIER_2_REG, RTL8306M_PHY_ID2, RTL8306M_PHY_ID2_MASK, 1000);
    } while(res1 != ESP_OK || res2 != ESP_OK);

    ets_delay_us(300);

	uint32_t data;
	//Enable puase flow control
	data  = esp_eth_smi_read(MII_AUTO_NEG_ADVERTISEMENT_REG);
    data |= MII_PAUSE;
    esp_eth_smi_write(MII_AUTO_NEG_ADVERTISEMENT_REG, data);

	//Enable auto negotitation
	data  = esp_eth_smi_read(PORT5_PHY_CONTROL_REG0);
    data |= PORT5_AUTO_NEGOTITATION_ENABLE;
    esp_eth_smi_write(PORT5_PHY_CONTROL_REG0, data);

	//Set link up
	data  = esp_eth_smi_read(PORT5_PHY_CONTROL_REG0);
    data |= PORT5_LINK_STATUS;
    esp_eth_smi_write(PORT5_PHY_CONTROL_REG0, data);
}

bool rtl8306m_check_link_status(void)
{
	return 1;
}

const eth_config_t phy_rtl8306m_default_ethernet_config = {
    // By default, the PHY address is 6 based on PHYAD0
    // pin. Can also be overriden in software. See datasheet
    // for defaults.
    .phy_addr = 6,
    .mac_mode = ETH_MODE_RMII,
    .clock_mode = ETH_CLOCK_GPIO0_IN,
    //Only FULLDUPLEX mode support flow ctrl now!
    .flow_ctrl_enable = true,
    .phy_init = phy_rtl8306m_init,
    .phy_check_init = phy_rtl8306m_check_phy_init,
    .phy_power_enable = phy_rtl8306m_power_enable,
    //.phy_check_link = phy_mii_check_link_status,
    .phy_check_link = rtl8306m_check_link_status,
    .phy_get_speed_mode = phy_rtl8306m_get_speed_mode,
    .phy_get_duplex_mode = phy_rtl8306m_get_duplex_mode,
    .phy_get_partner_pause_enable = phy_mii_get_partner_pause_enable,
};

void phy_rtl8306m_dump_registers()
{
    ESP_LOGD(TAG, "RTL8306M PHY6 Registers:");
    ESP_LOGD(TAG, "CONTROL	0x%04x", esp_eth_smi_read(0x0));
    ESP_LOGD(TAG, "STATUS	0x%04x", esp_eth_smi_read(0x1));
    ESP_LOGD(TAG, "ID1		0x%04x", esp_eth_smi_read(0x2));
    ESP_LOGD(TAG, "ID2		0x%04x", esp_eth_smi_read(0x3));
    ESP_LOGD(TAG, "ANAR		0x%04x", esp_eth_smi_read(0x4));
	ESP_LOGD(TAG, "ANLPAR 	0x%04x", esp_eth_smi_read(0x5));
    ESP_LOGD(TAG, "CR0		0x%04x", esp_eth_smi_read(0x16));
    ESP_LOGD(TAG, "CR1		0x%04x", esp_eth_smi_read(0x18));
}

