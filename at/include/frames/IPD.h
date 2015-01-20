/*
 * IPD.h
 *
 *  Created on: Jan 14, 2015
 *      Author: Stefan
 */

#ifndef INCLUDE_FRAMES_IPD_H_
#define INCLUDE_FRAMES_IPD_H_

#define FRAME_STAT_IPD				(FRAME_STAT_BASE + 0x00)

#define FRAME_POS_COM_IPD_CONN		(FRAME_POS_PAYLOAD_OUT + 0x00)

typedef struct espconn ESPCONN;

uint8_t		response_IPD_handler(ESPCONN* arg, char* pdata, unsigned short len);

#endif /* INCLUDE_FRAMES_COM_H_ */
