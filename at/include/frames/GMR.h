/*
 * GMR.h
 * GMR : Module version & identification
 *
 *  Created on: Jan 14, 2015
 *      Author: Stefan
 */

#ifndef INCLUDE_FRAME_GMR_H_
#define INCLUDE_FRAME_GMR_H_

// 4 byte rescode + 1 byte payload
#define FRAME_SIZE_GMR				5

#define FRAME_POS_GMR_FRAMEVER		(FRAME_POS_PAYLOAD_OUT + 0x00)
#define FRAME_POS_GMR_SDKMAJ		(FRAME_POS_PAYLOAD_OUT + 0x01)
#define FRAME_POS_GMR_SDKMIN		(FRAME_POS_PAYLOAD_OUT + 0x02)
#define FRAME_POS_GMR_SDKREV		(FRAME_POS_PAYLOAD_OUT + 0x03)

uint8_t		request_GMR_handler(uint8_t* frame);

#endif /* INCLUDE_FRAME_GMR_H_ */
