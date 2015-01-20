/*
 * CWMODE.h
 * CWMODE : Wireless mode
 *
 *  Created on: Jan 14, 2015
 *      Author: Stefan
 */

#ifndef INCLUDE_FRAMES_CWMODE_H_
#define INCLUDE_FRAMES_CWMODE_H_

// 1 byte rescode + 1 byte payload
#define FRAME_SIZE_CWMODE				2

#define CWMODE_STANDALONE				0x01
#define CWMODE_ACCESSPOINT				0x02
#define CWMODE_BOTH						(CWMODE_STANDALONE | CWMODE_ACCESSPOINT)

#define FRAME_POS_CWMODE_IN_MODE		(FRAME_POS_PAYLOAD_IN + 0x00)
#define FRAME_POS_CWMODE_OUT_MODE		(FRAME_POS_PAYLOAD_OUT + 0x00)

uint8_t		request_CWMODE_handler(uint8_t* frame);
uint8_t		command_CWMODE_handler(uint8_t* frame);

#endif /* INCLUDE_FRAMES_CWMODE_H_ */
