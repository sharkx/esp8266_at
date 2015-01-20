/*

 * COM.c
 * COM : Serial communication mode
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

uint8_t request_COM_handler(uint8_t* frame)
{
	// don't use buffers that are too large
	uint8_t respFrame[FRAME_LENGTH_SHORT];

	respFrame[FRAME_POS_MAGIC] 				= FRAME_MAGIC;
	respFrame[FRAME_POS_TYPE] 				= MAKE_RESP_TYPE(FRAME_CMD_COM);
	respFrame[FRAME_POS_SIZE_LSB] 			= LOBYTE(FRAME_SIZE_COM);
	respFrame[FRAME_POS_SIZE_MSB] 			= HIBYTE(FRAME_SIZE_COM);
	respFrame[FRAME_POS_SEQ] 				= frame[FRAME_POS_SEQ];

	respFrame[FRAME_POS_RESCODE] 			= SUCCESS;
	respFrame[FRAME_POS_COM_OUT_MODE] 		= g_comProtocolMode;

	return sendFrame(checksum(respFrame));
}

uint8_t command_COM_handler(uint8_t* frame)
{
	// don't use buffers that are too large
	uint8_t respFrame[FRAME_LENGTH_SHORT];
	uint8_t newMode = frame[FRAME_POS_COM_IN_MODE];

	if ((newMode & COM_INBOUND_MASK) == 0)
	{
		return sendErrorFrame(frame, ERROR_INVALID_PARAM);
	}

	// process command first (trim out not used bits)
	g_comProtocolMode = newMode & COM_MASK;
	return request_COM_handler(frame);
}
