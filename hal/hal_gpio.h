#ifndef __HAL_GPIO_H_
#define __HAL_GPIO_H_

#include "fsl_common.h"
#include "fsl_gpio.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

typedef uint8_t HAL_GpioIndex;

/* IO中断回调函数 */
typedef void(*GpioIrqCallback)(void *param);

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/
HAL_GpioIndex HAL_GpioInit(GPIO_Type *base, uint8_t pin, gpio_pin_direction_t dirc, uint8_t logic, gpio_interrupt_mode_t mode);
status_t HAL_SetGpioLevel(HAL_GpioIndex index,uint8_t level);
status_t HAL_SetIrqCallback(HAL_GpioIndex index,GpioIrqCallback callback,void *param);


#endif
