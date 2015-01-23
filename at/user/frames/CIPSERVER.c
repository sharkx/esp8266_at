/*

 * GMR.c
 * GMR : Module version & identification
 *
 *  Created on: Jan 14, 2015
 *      Author: Stefan
 */

#include <stdlib.h>

#include "c_types.h"
#include "user_interface.h"
#include "version.h"
#include "espconn.h"
#include "mem.h"
#include "at.h"
#include "at_ipCmd.h"
#include "at_wifiCmd.h"
#include "osapi.h"
#include "driver/uart.h"
#include "upgrade.h"
#include "ets_sys.h"

#include "frame.h"
#include "version.h"

uint8_t request_CIPSERVER_handler(uint8_t* frame)
{
	// don't use buffers that are too large
	uint8_t respFrame[FRAME_LENGTH_SHORT];

	if (pTcpServer == NULL)
	{
		return sendResultFrame(frame, INFO_CIPSERVER_NO_SERVER);
	}

	respFrame[FRAME_POS_MAGIC] = FRAME_MAGIC;
	respFrame[FRAME_POS_TYPE] = MAKE_RESP_TYPE(FRAME_CMD_CIPSERVER);
	respFrame[FRAME_POS_SIZE_LSB] = LOBYTE(FRAME_SIZE_CIPSERVER);
	respFrame[FRAME_POS_SIZE_MSB] = HIBYTE(FRAME_SIZE_CIPSERVER);
	respFrame[FRAME_POS_SEQ] = frame[FRAME_POS_SEQ];

	respFrame[FRAME_POS_RESCODE] = SUCCESS;

	memcpy(respFrame + FRAME_POS_CIPSERVER_OUT_TCP_IP, pTcpServer->proto.tcp->local_ip, 4);
	memcpy(respFrame + FRAME_POS_CIPSERVER_OUT_TCP_PORT, &pTcpServer->proto.tcp->local_port, 2);
	memcpy(respFrame + FRAME_POS_CIPSERVER_OUT_UDP_IP, pUdpServer->proto.udp->local_ip, 4);
	memcpy(respFrame + FRAME_POS_CIPSERVER_OUT_UDP_PORT, &pUdpServer->proto.udp->local_ip, 4);

	return sendFrame(checksum(respFrame));
}

uint8_t command_CIPSERVER_handler(uint8_t* frame)
{
	// don't use buffers that are too large
	uint8_t respFrame[FRAME_LENGTH_SHORT];

	// enable or disable
	if ((frame[FRAME_POS_CIPSERVER_IN_FLAGS] & FLAG_CIPSERVER_ACTION_MASK) == FLAG_CIPSERVER_STOP)
	{
		// we need stop; TCP or UDP ?
		if ((frame[FRAME_POS_CIPSERVER_IN_FLAGS] & FLAG_CIPSERVER_PROTO_MASK) == FLAG_CIPSERVER_TCP)
		{
			// stop the TCP server
			if (pTcpServer != NULL)
			{
				// how ?
			}
			else
			{
				return sendResultFrame(frame, ERROR_SERVER_NOTSTARTED);
			}
		}
		else
		{
			// stop the UDP server
			if (pUdpServer != NULL)
			{
				// how ?
			}
			else
			{
				return sendResultFrame(frame, ERROR_SERVER_NOTSTARTED);
			}
		}
	}
	else
	{
		// we need start; TCP or UDP ?
		if ((frame[FRAME_POS_CIPSERVER_IN_FLAGS] & FLAG_CIPSERVER_PROTO_MASK) == FLAG_CIPSERVER_TCP)
		{
			// start the TCP server
			pTcpServer = (struct espconn *) os_zalloc(sizeof(struct espconn));
			if (pTcpServer == NULL)
			{
				return sendResultFrame(frame, ERROR_ESPCONN_ALLOC);
			}

			pTcpServer->type = ESPCONN_TCP;
			pTcpServer->state = ESPCONN_NONE;
			pTcpServer->proto.tcp = (esp_tcp *) os_zalloc(sizeof(esp_tcp));
			pTcpServer->proto.tcp->local_port = *(int*) (frame + FRAME_POS_CIPSERVER_IN_PORT);
			espconn_regist_connectcb(pTcpServer, at_tcpserver_listen);
			espconn_accept(pTcpServer);
			espconn_regist_time(pTcpServer, server_timeover, 0);
		}
		else
		{
			// start the UDP server
			pUdpServer = (struct espconn *) os_zalloc(sizeof(struct espconn));
			if (pUdpServer == NULL)
			{
				return sendResultFrame(frame, ERROR_ESPCONN_ALLOC);
			}

			pUdpServer->type = ESPCONN_UDP;
			pUdpServer->state = ESPCONN_NONE;
			pUdpServer->proto.udp = (esp_udp *) os_zalloc(sizeof(esp_udp));
			pUdpServer->proto.udp->local_port = *(int*) (frame + FRAME_POS_CIPSERVER_IN_PORT);
			pUdpServer->reverse = NULL;
			espconn_regist_recvcb(pUdpServer, at_udpserver_recv);

			sint8_t result = espconn_create(pUdpServer);
			if (result == 0)
			{
				return sendResultFrame(frame, SUCCESS);
			}
			else
			{
				// error code
			}
		}
	}

	return sendFrame(checksum(respFrame));
}
