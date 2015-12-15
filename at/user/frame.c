/*

 * frame.c
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

uint8_t dataFrameIn[FRAME_LENGTH_MAX];
uint8_t frameCheckSum = 0;
uint16_t nFrameIndexPtr = 0;
uint16_t nBytesToGo = 0;

// not connected by default
uint8_t CWJAPstatus = INFO_CWJAP_AP_NONE;

frameHandlerStruct frameHandlers[] =
{
	{ request_GMR_handler, NULL },
	{ request_CWMODE_handler, command_CWMODE_handler },
	{ request_COM_handler, command_COM_handler },
	{ request_CWJAP_handler, command_CWJAP_handler },
	{ NULL, command_CWQAP_handler },
	{ request_CIPSTART_handler, command_CIPSTART_handler },
	{ request_CIPSERVER_handler, command_CIPSERVER_handler },
	{ request_CIPMUX_handler, command_CIPMUX_handler },
	{ request_GPIO_handler, command_GPIO_handler }
};

uint16_t getFrameSize(uint8_t* frame)
{
	return (frame[FRAME_POS_SIZE_MSB] << 8) | frame[FRAME_POS_SIZE_LSB];
}

uint8_t getFrameType(uint8_t* frame)
{
	return (frame[FRAME_POS_TYPE] & FRAME_TYPE_MASK);
}

uint8_t getFrameCommand(uint8_t* frame)
{
	return (frame[FRAME_POS_TYPE] & FRAME_COMMAND_MASK);
}

uint8_t isRequestFrame(uint8_t* frame)
{
	return (getFrameType(frame) == FRAME_TYPE_REQUEST);
}

uint8_t isCommandFrame(uint8_t* frame)
{
	return (getFrameType(frame) == FRAME_TYPE_COMMAND);
}

uint8_t processFrame(uint8_t* frame)
{
	uint8_t nFrameType = getFrameCommand(frame);

	fun_requestHandler handler = isRequestFrame(frame)
		? frameHandlers[nFrameType - FRAME_CMD_BASE].requestHandler
		: frameHandlers[nFrameType - FRAME_CMD_BASE].commandHandler;

	if (handler == NULL)
	{
		return sendResultFrame(frame, ERROR_NO_FRAME_HANDLER);
	}
	else
	{
		return handler(frame);
	}
}

uint8_t sendFrame(uint8_t* frameToSend)
{
	uint16_t i = 0;
	uint16_t len = getFrameSize(frameToSend) + FRAME_OVERHEAD;
	for (i = 0; i < len; i++)
	{
		uart_tx_one_char(frameToSend[i]);
	}

	return 0;
}

uint8_t* checksum(uint8_t* frame)
{
	uint8_t i = 0;
	uint16_t size = getFrameSize(frame) + FRAME_OVERHEAD - 1;
	uint16_t checkSumPos = getFrameSize(frame) + FRAME_OVERHEAD - 1;

	frame[checkSumPos] = 0;
	for (i = 0; i < size; i++)
	{
		frame[checkSumPos] ^= frame[i];
	}

	return frame;
}

uint8_t sendResultFrame(uint8_t* frameIn, uint8_t errorCode)
{
	uint8_t i = 0;
	uint8_t respFrame[FRAME_LENGTH_SHORT];

	respFrame[FRAME_POS_MAGIC] = FRAME_MAGIC;
	respFrame[FRAME_POS_TYPE] = (frameIn == NULL)
		? MAKE_RESP_TYPE(FRAME_COMMAND_NONE)
		: MAKE_RESP_TYPE(FRAME_TYPE(frameIn[FRAME_POS_TYPE]));
	respFrame[FRAME_POS_SIZE_LSB] = 1;
	respFrame[FRAME_POS_SIZE_MSB] = 0;
	respFrame[FRAME_POS_SEQ] = (frameIn == NULL)
		? 0x00
		: frameIn[FRAME_POS_SEQ];

	// actual payload
	respFrame[FRAME_POS_RESULT] = errorCode;

	// checksum
	return sendFrame(checksum(respFrame));
}



