/*
 * GMR.h
 * GMR : Module version & identification
 *
 *  Created on: Jan 14, 2015
 *      Author: Stefan
 */

#ifndef INCLUDE_FRAME_CIPSTART_H_
#define INCLUDE_FRAME_CIPSTART_H_

// + 1 byte payload
#define FRAME_SIZE_CIPSTART				5

#define FRAME_POS_CIPSTART_			(FRAME_POS_PAYLOAD_OUT + 0x00)

uint8_t		request_CIPSTART_handler(uint8_t* frame);
uint8_t		command_CIPSTART_handler(uint8_t* frame);

#endif /* INCLUDE_FRAME_CIPSTART_H_ */
