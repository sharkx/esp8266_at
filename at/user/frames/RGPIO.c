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
#include "ip.h"
#include "ip_addr.h"
#include "espconn.h"

#include "frame.h"
#include "version.h"

struct espconn RGPIO_conn;

static void ICACHE_FLASH_ATTR RGPIO_connect_cb(void *arg);
static void ICACHE_FLASH_ATTR RGPIO_reconnect_cb(void *arg, sint8 errType);
static void ICACHE_FLASH_ATTR RGPIO_disconnect_cb(void *arg);
void ICACHE_FLASH_ATTR RGPIO_recv_cb(void *arg, char *pdata, unsigned short len);
static void ICACHE_FLASH_ATTR RGPIO_sent_cb(void *arg);

uint8_t request_RGPIO_handler(uint8_t* frame)
{
	// don't use buffers that are too large
	uint8_t respFrame[FRAME_LENGTH_SHORT];

	respFrame[FRAME_POS_MAGIC] 				= FRAME_MAGIC;
	respFrame[FRAME_POS_TYPE] 				= MAKE_RESP_TYPE(FRAME_CMD_RGPIO);
	respFrame[FRAME_POS_SIZE_LSB] 			= LOBYTE(FRAME_SIZE_RGPIO);
	respFrame[FRAME_POS_SIZE_MSB] 			= HIBYTE(FRAME_SIZE_RGPIO);
	respFrame[FRAME_POS_SEQ] 				= frame[FRAME_POS_SEQ];

	respFrame[FRAME_POS_RESCODE] 			= SUCCESS;
	respFrame[FRAME_POS_RGPIO_OUT_BIT] 		= frame[FRAME_POS_RGPIO_IN_BIT];

	// send command remotely and replay return value
	uint32_t remote = *((uint32_t*)(respFrame+FRAME_POS_RGPIO_IN_REMOTE));

	if (RGPIO_conn.type != 0)
	{
		return sendResultFrame(frame, ERROR_RGPIO_PENDING);
	}
	else
	{
		RGPIO_conn.type = ESPCONN_TCP;
		RGPIO_conn.state = ESPCONN_NONE;

		RGPIO_conn.proto.tcp = (esp_tcp*)os_zalloc(sizeof(esp_tcp));
		RGPIO_conn.proto.tcp->local_port = espconn_port();
		RGPIO_conn.proto.tcp->remote_port = RGPIO_REMOTE_PORT;

		os_memcpy(RGPIO_conn.proto.tcp->remote_ip, &remote, 4);

		espconn_regist_connectcb(&RGPIO_conn, RGPIO_connect_cb);
		espconn_regist_reconcb(&RGPIO_conn, RGPIO_reconnect_cb);

		espconn_connect(&RGPIO_conn);

		return sendResultFrame(frame, SUCCESS);
	}
}

uint8_t command_RGPIO_handler(uint8_t* frame)
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

static void ICACHE_FLASH_ATTR RGPIO_connect_cb(void *arg)
{
	struct espconn *pConn = (struct espconn *) arg;

	espconn_regist_disconcb(pConn, RGPIO_disconnect_cb);
	espconn_regist_recvcb(pConn, RGPIO_recv_cb); ////////
	espconn_regist_sentcb(pConn, RGPIO_sent_cb); ///////
}

static void ICACHE_FLASH_ATTR RGPIO_reconnect_cb(void *arg, sint8 errType)
{
	struct espconn *pConn = (struct espconn *) arg;
	espconn_disconnect(&RGPIO_conn);
	RGPIO_conn.type = 0;
}

static void ICACHE_FLASH_ATTR RGPIO_disconnect_cb(void *arg)
{
	struct espconn *pConn = (struct espconn *) arg;
	if (pConn->proto.tcp != NULL)
	{
		os_free(pConn->proto.tcp);
	}
	RGPIO_conn.type = 0;

	ETS_UART_INTR_ENABLE();
}

void ICACHE_FLASH_ATTR RGPIO_recv_cb(void *arg, char *pdata, unsigned short len)
{
	struct espconn *pConn = (struct espconn *) arg;

	// we have a response from remote; relay as frame
}

static void ICACHE_FLASH_ATTR RGPIO_sent_cb(void *arg)
{
	// nothing to do here
}
