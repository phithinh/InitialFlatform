/*
 * gpio_common.h
 *
 *  Created on: Mar 8, 2014
 *      Author: TV
 */

#ifndef GPIO_USER_H_
#define GPIO_USER_H_

ULONG gpio_common_getRCC(GPIO_TypeDef * t_gpio_type_def);
UBYTE gpio_common_getPortSrc(GPIO_TypeDef * t_gpio_type_def);
ULONG gpio_common_getLine(UWORD GPIO_pins_uw);
UBYTE gpio_common_getLineIRQn(UWORD GPIO_pins_uw);
UBYTE gpio_common_getPinSrc(UWORD GPIO_pins_uw);

#endif /* GPIO_USER_H_ */
