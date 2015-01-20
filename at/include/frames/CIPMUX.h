/*
 * CIPMUX.h
 * CIPMUX : Wireless mode
 *
 *  Created on: Jan 14, 2015
 *      Author: Stefan
 */

#ifndef INCLUDE_FRAMES_CIPMUX_H_
#define INCLUDE_FRAMES_CIPMUX_H_

// 1 byte rescode + 1 byte payload
#define FRAME_SIZE_CIPMUX				2

#define FRAME_POS_CIPMUX_IN_MODE		(FRAME_POS_PAYLOAD_IN + 0x00)
#define FRAME_POS_CIPMUX_OUT_MODE		(FRAME_POS_PAYLOAD_OUT + 0x00)

uint8_t		request_CIPMUX_handler(uint8_t* frame);
uint8_t		command_CIPMUX_handler(uint8_t* frame);

#endif /* INCLUDE_FRAMES_CIPMUX_H_ */
