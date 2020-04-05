/*
 *  App_Cfg.h
 *  Description: this file contains an App pre_compile configurations
 *  Created on: Jan 12, 2020
 *  Author: Ahemd_Elbadwi
 */


#ifndef APP_CFG_H_
#define APP_CFG_H_

/*
 * This macro define the maximum used leds
 */
#define LED_MAX_NUM	(4)

/*
 * LED_x_GPIO and LED_x_BIT
 * where x is the led identifier
 */
#define LED_GPIO    (GPIOB)

#define LED_0_GPIO	(GPIOB)
#define LED_0_PIN	(PIN4)

#define LED_1_GPIO	(GPIOB)
#define LED_1_PIN	(PIN5)

#define LED_2_GPIO	(GPIOB)
#define LED_2_PIN	(PIN6)


#define TASK0_DELAY  (50U)
#define TASK1_DELAY  (100U)
#define TASK2_DELAY  (150U)
#endif /* APP_CFG_H_ */
