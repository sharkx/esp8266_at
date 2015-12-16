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
#include "gpio.h"

#include "frame.h"
#include "version.h"

uint8_t request_GPIO_handler(uint8_t* frame)
{
	// don't use buffers that are too large
	uint8_t respFrame[FRAME_LENGTH_SHORT];

	respFrame[FRAME_POS_MAGIC] 				= FRAME_MAGIC;
	respFrame[FRAME_POS_TYPE] 				= MAKE_RESP_TYPE(FRAME_CMD_GPIO);
	respFrame[FRAME_POS_SIZE_LSB] 			= LOBYTE(FRAME_SIZE_GPIO);
	respFrame[FRAME_POS_SIZE_MSB] 			= HIBYTE(FRAME_SIZE_GPIO);
	respFrame[FRAME_POS_SEQ] 				= frame[FRAME_POS_SEQ];

	respFrame[FRAME_POS_RESCODE] 			= SUCCESS;
	respFrame[FRAME_POS_GPIO_OUT_BIT] 		= frame[FRAME_POS_GPIO_IN_BIT];

	if (frame[FRAME_POS_GPIO_IN_BIT] == 0xff)
	{
		// use gpio_input_get() to get all values
		*((uint32_t*)(respFrame+FRAME_POS_GPIO_OUT_VALUE)) = gpio_input_get();
	}
	else
	{
		*((uint32_t*)(respFrame+FRAME_POS_GPIO_OUT_VALUE)) = (uint32_t)GPIO_INPUT_GET(frame[FRAME_POS_GPIO_IN_BIT]);
	}

	return sendFrame(checksum(respFrame));
}

uint8_t command_GPIO_handler(uint8_t* frame)
{
	// don't use buffers that are too large
	uint8_t respFrame[FRAME_LENGTH_SHORT];

	uint8_t gpioBit= frame[FRAME_POS_GPIO_IN_BIT];

	if (gpioBit == 0xff)
	{
		uint32_t setValue = *((uint32_t*)(respFrame+FRAME_POS_GPIO_IN_SET));
		uint32_t clearValue = *((uint32_t*)(respFrame+FRAME_POS_GPIO_IN_CLEAR));
		uint32_t enableValue = *((uint32_t*)(respFrame+FRAME_POS_GPIO_IN_ENABLE));
		uint32_t disableValue = *((uint32_t*)(respFrame+FRAME_POS_GPIO_IN_DISABLE));

		gpio_output_set(setValue, clearValue, enableValue, disableValue);
	}
	else
	{
		uint8_t cmdCode = frame[FRAME_POS_GPIO_IN_CMD];

		// entire IO register
		switch (cmdCode)
		{
			case CMD_GPIO_SET :
				gpio_output_set(1<<gpioBit, 0, 1<<gpioBit, 0);
				break;
			case CMD_GPIO_CLEAR :
				gpio_output_set(0, 1<<gpioBit, 1<<gpioBit, 0);
				break;
			case CMD_GPIO_ENABLE :
				gpio_output_set(0, 0, 1<<gpioBit, 0);
				break;
			case CMD_GPIO_DISABLE :
				gpio_output_set(0, 0, 0, 1<<gpioBit);
				break;
		}
	}

	return request_GPIO_handler(frame);
}
