/*

 * CWMODE.c
 * CWMODE : Wireless mode
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

uint8_t request_CWMODE_handler(uint8_t* frame)
{
	// don't use buffers that are too large
	uint8_t respFrame[FRAME_LENGTH_SHORT];

	respFrame[FRAME_POS_MAGIC] 				= FRAME_MAGIC;
	respFrame[FRAME_POS_TYPE] 				= MAKE_RESP_TYPE(FRAME_CMD_CWMODE);
	respFrame[FRAME_POS_SIZE_LSB] 			= LOBYTE(FRAME_SIZE_CWMODE);
	respFrame[FRAME_POS_SIZE_MSB] 			= HIBYTE(FRAME_SIZE_CWMODE);
	respFrame[FRAME_POS_SEQ] 				= frame[FRAME_POS_SEQ];

	respFrame[FRAME_POS_RESCODE] 			= SUCCESS;
	respFrame[FRAME_POS_CWMODE_OUT_MODE] 	= at_wifiMode;

	return sendFrame(checksum(respFrame));
}

uint8_t command_CWMODE_handler(uint8_t* frame)
{
	// don't use buffers that are too large
	uint8_t respFrame[FRAME_LENGTH_SHORT];

	// process command first
	if (frame[FRAME_POS_CWMODE_IN_MODE] == at_wifiMode)
	{
		return request_CWMODE_handler(frame);
	}
	if ((frame[FRAME_POS_CWMODE_IN_MODE] >= 1) && (frame[FRAME_POS_CWMODE_IN_MODE] <= 3))
	{
		ETS_UART_INTR_DISABLE();
		wifi_set_opmode(frame[FRAME_POS_CWMODE_IN_MODE]);
		ETS_UART_INTR_ENABLE();
		at_wifiMode = frame[FRAME_POS_CWMODE_IN_MODE];

		return request_CWMODE_handler(frame);
	}
	else
	{
		// KO back
		return sendResultFrame(frame, ERROR_INVALID_PARAM);
	}

	// unreachable code
	return 0xff;
}
