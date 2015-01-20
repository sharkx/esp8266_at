/*
 * CWJAP.h
 * CWJAP : Join access point
 *
 *  Created on: Jan 14, 2015
 *      Author: Stefan
 */

#ifndef INCLUDE_FRAMES_CWJAP_H_
#define INCLUDE_FRAMES_CWJAP_H_

#define FLAG_CWJAP_SYNCHRONOUS		0x01
#define FLAG_CWJAP_NO_NOTIFICATION	0x02

// 1 byte rescode
#define FRAME_SIZE_CWJAP_NOSTAT		1

#define FRAME_POS_CWJAP_IN_FLAGS	(FRAME_POS_PAYLOAD_IN  + 0x00)
#define FRAME_POS_CWJAP_IN_TIMEOUT	(FRAME_POS_PAYLOAD_IN  + 0x01)
#define FRAME_POS_CWJAP_OUT_IP		(FRAME_POS_PAYLOAD_OUT + 0x00)
#define FRAME_POS_CWJAP_OUT_MASK	(FRAME_POS_PAYLOAD_OUT + 0x04)
#define FRAME_POS_CWJAP_OUT_GW		(FRAME_POS_PAYLOAD_OUT + 0x08)
#define FRAME_POS_CWJAP_OUT_SSID	(FRAME_POS_PAYLOAD_OUT + 0x0C)


extern uint8_t		CWJAPstatus;

uint8_t		request_CWJAP_handler(uint8_t* frame);
uint8_t		command_CWJAP_handler(uint8_t* frame);

#endif /* INCLUDE_FRAMES_COM_H_ */
