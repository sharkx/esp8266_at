/*
 * COM.h
 * COM : Serial communication mode
 *
 *  Created on: Jan 14, 2015
 *      Author: Stefan
 */

#ifndef INCLUDE_FRAMES_COM_H_
#define INCLUDE_FRAMES_COM_H_

// 1 byte rescode + 1 byte payload
#define FRAME_SIZE_COM				2

#define FRAME_POS_COM_IN_MODE		(FRAME_POS_PAYLOAD_IN + 0x00)
#define FRAME_POS_COM_OUT_MODE		(FRAME_POS_PAYLOAD_OUT + 0x00)

uint8_t		request_COM_handler(uint8_t* frame);
uint8_t		command_COM_handler(uint8_t* frame);

#endif /* INCLUDE_FRAMES_COM_H_ */
