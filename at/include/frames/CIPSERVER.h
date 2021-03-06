/*
 * CIPSERVER.h
 * CIPSERVER : Join access point
 *
 *  Created on: Jan 14, 2015
 *      Author: Stefan
 */

#ifndef INCLUDE_FRAMES_CIPSERVER_H_
#define INCLUDE_FRAMES_CIPSERVER_H_

#include "ip.h"

#define FLAG_CIPSERVER_ACTION_MASK	0x01
#define FLAG_CIPSERVER_STOP			0x00
#define FLAG_CIPSERVER_START		0x01

#define FLAG_CIPSERVER_PROTO_MASK	0x02
#define FLAG_CIPSERVER_TCP			0x00
#define FLAG_CIPSERVER_UDP			0x02

// 1 byte rescode
#define FRAME_SIZE_CIPSERVER		13

#define FRAME_POS_CIPSERVER_IN_FLAGS		(FRAME_POS_PAYLOAD_IN  + 0x00)
#define FRAME_POS_CIPSERVER_IN_IP			(FRAME_POS_PAYLOAD_IN  + 0x01)
#define FRAME_POS_CIPSERVER_IN_PORT			(FRAME_POS_PAYLOAD_IN  + 0x05)
#define FRAME_POS_CIPSERVER_OUT_TCP_IP		(FRAME_POS_PAYLOAD_OUT + 0x00)
#define FRAME_POS_CIPSERVER_OUT_TCP_PORT	(FRAME_POS_PAYLOAD_OUT + 0x04)
#define FRAME_POS_CIPSERVER_OUT_UDP_IP		(FRAME_POS_PAYLOAD_OUT + 0x06)
#define FRAME_POS_CIPSERVER_OUT_UDP_PORT	(FRAME_POS_PAYLOAD_OUT + 0x0A)


uint8_t		request_CIPSERVER_handler(uint8_t* frame);
uint8_t		command_CIPSERVER_handler(uint8_t* frame);

void 		at_tcpserver_listen(void *arg);
void 		at_udpserver_recv(void *arg, char *pusrdata, unsigned short len);

#endif /* INCLUDE_FRAMES_COM_H_ */
