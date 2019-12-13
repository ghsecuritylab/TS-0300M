#ifndef __I2C_SIMULATE_H__
#define __I2C_SIMULATE_H__ 


#define IIC_IO_IN  0
#define IIC_IO_OUT 1

typedef void	(*T_SimSerial_PO)			(u8 Level);		// 0:LowLevel	1:HighLevel
typedef u8 		(*T_SimSerial_PI)			(void);			// 0:LowLevel	else:HighLevel
typedef void	(*T_SimSerial_PIN_Mode)	(u8 Mode);		// 0:Input		1:Output, for Singlet duplex, can be set as NULL


typedef struct
{
	u8						Slave_Address;
	T_SimSerial_PO			SCK;
	T_SimSerial_PO			SDO;
	T_SimSerial_PI			SDI;
	T_SimSerial_PIN_Mode	SDA_Mode;
}T_I2C_Master_PIN_OPT;

//IIC所有操作函数
void IIC_BUS_Write_One_Byte(T_I2C_Master_PIN_OPT * PIN_OPT,u8 Sub_Addr,u8 txd);//IIC协议发送1字节数据
void IIC_BUS_Write_More_Byte(T_I2C_Master_PIN_OPT * PIN_OPT,u8 Sub_Addr,uc8 *txd,u8 dat_Length);      //IIC协议发送n字节数据
u8   IIC_BUS_Read_One_Byte(T_I2C_Master_PIN_OPT * PIN_OPT,u8 Sub_Addr);                                  //IIC协议读取1字节数据
void IIC_BUS_Read_More_Byte(T_I2C_Master_PIN_OPT * PIN_OPT,u8 Sub_Addr,u8 *rxd,u8 dat_Length);        //IIC协议读取n字节数据
void IIC_BUS_Write_4_Byte(T_I2C_Master_PIN_OPT * PIN_OPT,u8 Sub_Addr,uc32 data);
void IIC_BUS_Write_More_Byte_2_Byte_Rigister_Address(T_I2C_Master_PIN_OPT * PIN_OPT,u16 Sub_Addr,u16 dat_Length,const u8 *txd);
void IICDataDownload(uc8 *Register,T_I2C_Master_PIN_OPT * IICCompment,u16 ArrayLength);
void IIC_BUS_Read_More_Byte_2_Byte_Rigister_Address(T_I2C_Master_PIN_OPT * PIN_OPT,u16 Sub_Addr,u8 *rxd,u16 dat_Length);
void IIC_BUS_Write_7Bitadd_9Bitdata(T_I2C_Master_PIN_OPT * PIN_OPT,u8 Sub_Addr,u16 txd);
u8 IIC_BUS_Read_8Bitdata(T_I2C_Master_PIN_OPT * PIN_OPT,u8 Sub_Addr);

#endif

/********************************END_FILE****************************/















