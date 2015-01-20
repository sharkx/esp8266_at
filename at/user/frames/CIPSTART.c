/*

 * CIPSTART.c
 * CIPSTART : Module version & identification
 *
 *  Created on: Jan 14, 2015
 *      Author: Stefan
 */

#include "ets_sys.h"
#include "at_wifiCmd.h"
#include "driver/uart.h"
#include "osapi.h"
#include "at.h"

#include "frame.h"
#include "version.h"

uint8_t request_CIPSTART_handler(uint8_t* frame)
{
	// don't use buffers that are too large
	uint8_t respFrame[FRAME_LENGTH_SHORT];

	respFrame[FRAME_POS_MAGIC] 			= FRAME_MAGIC;
	respFrame[FRAME_POS_TYPE] 			= MAKE_RESP_TYPE(FRAME_CMD_CIPSTART);
	respFrame[FRAME_POS_SIZE_LSB] 		= LOBYTE(FRAME_SIZE_CIPSTART);
	respFrame[FRAME_POS_SIZE_MSB] 		= HIBYTE(FRAME_SIZE_CIPSTART);
	respFrame[FRAME_POS_SEQ] 			= frame[FRAME_POS_SEQ];

	respFrame[FRAME_POS_RESCODE] 		= SUCCESS;

	return sendFrame(checksum(respFrame));
}

uint8_t command_CIPSTART_handler(uint8_t* frame)
{
	// don't use buffers that are too large
	uint8_t respFrame[FRAME_LENGTH_SHORT];

	respFrame[FRAME_POS_MAGIC] 			= FRAME_MAGIC;
	respFrame[FRAME_POS_TYPE] 			= MAKE_RESP_TYPE(FRAME_CMD_CIPSTART);
	respFrame[FRAME_POS_SIZE_LSB] 		= LOBYTE(FRAME_SIZE_CIPSTART);
	respFrame[FRAME_POS_SIZE_MSB] 		= HIBYTE(FRAME_SIZE_CIPSTART);
	respFrame[FRAME_POS_SEQ] 			= frame[FRAME_POS_SEQ];

	respFrame[FRAME_POS_RESCODE] 		= SUCCESS;

	return sendFrame(checksum(respFrame));
}
