/*
 * GPIO.h
 * GPIO : Control GPIO ports
 *
 *  Created on: Jan 14, 2015
 *      Author: Stefan
 */

#ifndef INCLUDE_FRAMES_GPIO_H_
#define INCLUDE_FRAMES_GPIO_H_

// 1 byte rescode + 5 byte payload
#define FRAME_SIZE_GPIO				6

#define FRAME_POS_GPIO_IN_BIT			(FRAME_POS_PAYLOAD_IN + 0x00)

#define FRAME_POS_GPIO_OUT_BIT			(FRAME_POS_PAYLOAD_OUT + 0x00)
#define FRAME_POS_GPIO_OUT_VALUE		(FRAME_POS_PAYLOAD_OUT + 0x01)

uint8_t		request_GPIO_handler(uint8_t* frame);
uint8_t		command_GPIO_handler(uint8_t* frame);

#endif /* INCLUDE_FRAMES_GPIO_H_ */
