/*
 * GPIO.h
 * GPIO : Control GPIO ports
 *
 *  Created on: Jan 14, 2015
 *      Author: Stefan
 */

#ifndef INCLUDE_FRAMES_RGPIO_H_
#define INCLUDE_FRAMES_RGPIO_H_

// 1 byte rescode + 5 byte payload (GPIO number and GPIO register)
#define FRAME_SIZE_RGPIO		6

#define CMD_RGPIO_SET 			0x01
#define CMD_RGPIO_CLEAR 		0x02
#define CMD_RGPIO_ENABLE 		0x03
#define CMD_RGPIO_DISABLE 		0x04

#define FRAME_POS_RGPIO_IN_REMOTE		(FRAME_POS_PAYLOAD_IN + 0x00)
#define FRAME_POS_RGPIO_IN_BIT			(FRAME_POS_PAYLOAD_IN + 0x04)
#define FRAME_POS_RGPIO_IN_CMD			(FRAME_POS_PAYLOAD_IN + 0x05)

#define FRAME_POS_RGPIO_IN_SET			(FRAME_POS_PAYLOAD_IN + 0x05)
#define FRAME_POS_RGPIO_IN_CLEAR		(FRAME_POS_PAYLOAD_IN + 0x09)
#define FRAME_POS_RGPIO_IN_ENABLE		(FRAME_POS_PAYLOAD_IN + 0x0D)
#define FRAME_POS_RGPIO_IN_DISABLE		(FRAME_POS_PAYLOAD_IN + 0x11)

#define FRAME_POS_RGPIO_OUT_BIT			(FRAME_POS_PAYLOAD_OUT + 0x00)
#define FRAME_POS_RGPIO_OUT_VALUE		(FRAME_POS_PAYLOAD_OUT + 0x01)

#define RGPIO_REMOTE_PORT				0x7765

uint8_t		request_RGPIO_handler(uint8_t* frame);
uint8_t		command_RGPIO_handler(uint8_t* frame);

#endif /* INCLUDE_FRAMES_RGPIO_H_ */
