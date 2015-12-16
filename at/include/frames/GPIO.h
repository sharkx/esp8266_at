/*
 * GPIO.h
 * GPIO : Control GPIO ports
 *
 *  Created on: Jan 14, 2015
 *      Author: Stefan
 */

#ifndef INCLUDE_FRAMES_GPIO_H_
#define INCLUDE_FRAMES_GPIO_H_

// 1 byte rescode + 5 byte payload (GPIO number and GPIO register)
#define FRAME_SIZE_GPIO				6

#define CMD_GPIO_SET 			0x01
#define CMD_GPIO_CLEAR 			0x02
#define CMD_GPIO_ENABLE 		0x03
#define CMD_GPIO_DISABLE 		0x04

#define FRAME_POS_GPIO_IN_BIT			(FRAME_POS_PAYLOAD_IN + 0x00)
#define FRAME_POS_GPIO_IN_CMD			(FRAME_POS_PAYLOAD_IN + 0x01)

#define FRAME_POS_GPIO_IN_SET			(FRAME_POS_PAYLOAD_IN + 0x01)
#define FRAME_POS_GPIO_IN_CLEAR			(FRAME_POS_PAYLOAD_IN + 0x05)
#define FRAME_POS_GPIO_IN_ENABLE		(FRAME_POS_PAYLOAD_IN + 0x09)
#define FRAME_POS_GPIO_IN_DISABLE		(FRAME_POS_PAYLOAD_IN + 0x0D)

#define FRAME_POS_GPIO_OUT_BIT			(FRAME_POS_PAYLOAD_OUT + 0x00)
#define FRAME_POS_GPIO_OUT_VALUE		(FRAME_POS_PAYLOAD_OUT + 0x01)

uint8_t		request_GPIO_handler(uint8_t* frame);
uint8_t		command_GPIO_handler(uint8_t* frame);

#endif /* INCLUDE_FRAMES_GPIO_H_ */
