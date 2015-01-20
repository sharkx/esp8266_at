/*

 * CIPMUX.c
 * CIPMUX : Wireless mode
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

uint8_t request_CIPMUX_handler(uint8_t* frame)
{
	// don't use buffers that are too large
	uint8_t respFrame[FRAME_LENGTH_SHORT];

	respFrame[FRAME_POS_MAGIC] 				= FRAME_MAGIC;
	respFrame[FRAME_POS_TYPE] 				= MAKE_RESP_TYPE(FRAME_CMD_CIPMUX);
	respFrame[FRAME_POS_SIZE_LSB] 			= LOBYTE(FRAME_SIZE_CIPMUX);
	respFrame[FRAME_POS_SIZE_MSB] 			= HIBYTE(FRAME_SIZE_CIPMUX);
	respFrame[FRAME_POS_SEQ] 				= frame[FRAME_POS_SEQ];

	respFrame[FRAME_POS_RESCODE] 			= SUCCESS;
	respFrame[FRAME_POS_CIPMUX_OUT_MODE] 	= at_ipMux;

	return sendFrame(checksum(respFrame));
}

uint8_t command_CIPMUX_handler(uint8_t* frame)
{
	// don't use buffers that are too large
	uint8_t respFrame[FRAME_LENGTH_SHORT];

	if (mdState == m_linked)
	{
		// can't change this parameter while connected
		return sendErrorFrame(frame, ERROR_ALREADY_CONNECTED);
	}

	// process command first
	at_ipMux = (frame[FRAME_POS_CIPMUX_IN_MODE] != 0);
	return request_CIPMUX_handler(frame);
}
