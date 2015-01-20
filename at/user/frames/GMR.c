/*

 * GMR.c
 * GMR : Module version & identification
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

uint8_t request_GMR_handler(uint8_t* frame)
{
	// don't use buffers that are too large
	uint8_t respFrame[FRAME_LENGTH_SHORT];

	respFrame[FRAME_POS_MAGIC] 			= FRAME_MAGIC;
	respFrame[FRAME_POS_TYPE] 			= MAKE_RESP_TYPE(FRAME_CMD_GMR);
	respFrame[FRAME_POS_SIZE_LSB] 		= LOBYTE(FRAME_SIZE_GMR);
	respFrame[FRAME_POS_SIZE_MSB] 		= HIBYTE(FRAME_SIZE_GMR);
	respFrame[FRAME_POS_SEQ] 			= frame[FRAME_POS_SEQ];

	respFrame[FRAME_POS_RESCODE] 		= SUCCESS;

	respFrame[FRAME_POS_GMR_FRAMEVER] 	= FRAME_VERSION;
	respFrame[FRAME_POS_GMR_SDKMAJ] 	= SDK_MAJOR;
	respFrame[FRAME_POS_GMR_SDKMIN] 	= SDK_MINOR;
	respFrame[FRAME_POS_GMR_SDKREV] 	= SDK_REVISION;

	return sendFrame(checksum(respFrame));
}
