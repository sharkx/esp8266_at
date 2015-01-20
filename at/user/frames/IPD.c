/*

 * IPD.c
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

uint8_t response_IPD_handler(ESPCONN* arg, char* pdata, unsigned short len)
{
	// don't use buffers that are too large
	uint16_t i = 0;
	uint8_t respFrame[FRAME_LENGTH_MAX];

	if (len > (FRAME_LENGTH_MAX - FRAME_OVERHEAD + 2))
	{
		return sendErrorFrame(NULL, ERROR_INBOUND_DATA_TOO_LONG);
	}
	else
	{
		uint16_t frameLength = len + FRAME_OVERHEAD + 1;

		respFrame[FRAME_POS_MAGIC] 			= FRAME_MAGIC;
		respFrame[FRAME_POS_TYPE] 			= MAKE_RESP_TYPE(FRAME_STAT_IPD);
		respFrame[FRAME_POS_SIZE_LSB] 		= LOBYTE(frameLength);
		respFrame[FRAME_POS_SIZE_MSB] 		= HIBYTE(frameLength);
		respFrame[FRAME_POS_SEQ] 			= FRAME_SEQ_NONE;

		respFrame[FRAME_POS_RESCODE] 		= SUCCESS;

		// copy data to frame
		memcpy(respFrame + FRAME_POS_COM_IPD_CONN, pdata, len);

		return sendFrame(checksum(respFrame));
	}
}
