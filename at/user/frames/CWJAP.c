/*

 * CWJAP.c
 * CWJAP : Join access point
 *
 *  Created on: Jan 14, 2015
 *      Author: Stefan
 */

#include "ets_sys.h"
#include "at_wifiCmd.h"
#include "driver/uart.h"
#include "osapi.h"
#include "at.h"
#include "user_interface.h"

#include "frame.h"

os_timer_t 	timer_CWJAPCheck;
uint8_t		timer_CWJAPTimeout		= 0x00;
uint8_t		flags_CWJAP				= 0x00;
uint8_t		seq_CWJAP 				= 0x00;

uint8_t request_CWJAP_handler(uint8_t* frame)
{
	// don't use buffers that are too large
	uint8_t respFrame[FRAME_LENGTH_LONG];

	struct station_config stationConf;
	struct ip_info ipInfo;

	wifi_station_get_config(&stationConf);
	wifi_get_ip_info(0x00, &ipInfo);

	if ((ipInfo.ip.addr == 0) || (stationConf.ssid == 0))
	{
		// respond with current status; it is either INFO_CWJAP_AP_NONE or INFO_CWJAP_AP_PENDING
		return sendResultFrame(frame, CWJAPstatus);
	}

	// otherwise, we're connected

	// 12 bytes for IP data (IP, MASK, GW, each 4 bytes)
	// length of SSID string, including terminating null
	uint8_t frameLength = 12 + strlen(stationConf.ssid) + 2;

	respFrame[FRAME_POS_MAGIC] 				= FRAME_MAGIC;
	respFrame[FRAME_POS_TYPE] 				= MAKE_RESP_TYPE((frame != NULL)?FRAME_CMD_CWJAP:((flags_CWJAP & FLAG_CWJAP_SYNCHRONOUS)?FRAME_CMD_CWJAP:FRAME_STAT_CWJAP));
	respFrame[FRAME_POS_SIZE_LSB] 			= LOBYTE(frameLength);
	respFrame[FRAME_POS_SIZE_MSB] 			= HIBYTE(frameLength);
	respFrame[FRAME_POS_SEQ] 				= (frame != NULL)?frame[FRAME_POS_SEQ]:((flags_CWJAP & FLAG_CWJAP_SYNCHRONOUS)?seq_CWJAP:0x00);

	respFrame[FRAME_POS_RESCODE] 			= SUCCESS;

	*(uint32_t*)(respFrame + FRAME_POS_CWJAP_OUT_IP) 	= ipInfo.ip.addr;
	*(uint32_t*)(respFrame + FRAME_POS_CWJAP_OUT_MASK) 	= ipInfo.netmask.addr;
	*(uint32_t*)(respFrame + FRAME_POS_CWJAP_OUT_GW) 	= ipInfo.gw.addr;

	memcpy(respFrame + FRAME_POS_CWJAP_OUT_SSID, stationConf.ssid, strlen(stationConf.ssid) + 1);

	return sendFrame(checksum(respFrame));
}

void ICACHE_FLASH_ATTR
timer_fun_CWJAPCheck(void *arg)
{
	uint8_t japState;
	char temp[32];

	os_timer_disarm(&timer_CWJAPCheck);

	timer_CWJAPTimeout--;
	japState = wifi_station_get_connect_status();
	if (japState == STATION_GOT_IP)
	{
		if (at_state == at_statProcess)
		{
			// accept new commands
			at_state = statIdle;
		}

		// we're connected
		if (flags_CWJAP & FLAG_CWJAP_NO_NOTIFICATION)
		{
			// no notification
		}
		else
		{
			// just send back connection info
			request_CWJAP_handler(NULL);
		}
	}
	else if (timer_CWJAPTimeout > 0)
	{
		// wait another round
		os_timer_arm(&timer_CWJAPCheck, 1000, 0);
	}
	else
	{
		if (at_state == at_statProcess)
		{
			// accept new commands
			at_state = statIdle;
		}

		// we're past requested timeout
		wifi_station_disconnect();
		if (flags_CWJAP & FLAG_CWJAP_NO_NOTIFICATION)
		{
			// no notification
		}
		else
		{
			sendResultFrame(NULL, ERROR_AP_CONNECTION_TIMEOUT);
		}
	}
}

uint8_t command_CWJAP_handler(uint8_t* frame)
{
	// don't use buffers that are too large
	struct station_config stationConf;
	uint8_t respFrame[FRAME_LENGTH_SHORT];

	if (CWJAPstatus == INFO_CWJAP_AP_CONN)
	{
		// already connected; disconnect first
		return sendResultFrame(frame, ERROR_AP_ALREADY_CONNECTED);
	}

	if (CWJAPstatus == INFO_CWJAP_AP_PENDING)
	{
		// there is already a pending connection
		return sendResultFrame(frame, ERROR_AP_CONNECTION_PENDING);
	}

	if ((at_wifiMode & CWMODE_STANDALONE) == 0)
	{
		return sendResultFrame(frame, ERROR_AP_ONLY_APMODE);
	}

	os_bzero(&stationConf, sizeof(struct station_config));
	strncpy(stationConf.ssid, frame + 7, 32);
	strncpy(stationConf.password, frame + 7 + strlen(stationConf.ssid) + 1, 64);

	// will be used by both synchronous and asynchronous modes
	timer_CWJAPTimeout = frame[FRAME_POS_CWJAP_IN_TIMEOUT];
	flags_CWJAP = frame[FRAME_POS_CWJAP_IN_FLAGS];
	seq_CWJAP = frame[FRAME_POS_SEQ];

    ETS_UART_INTR_DISABLE();
    wifi_station_set_config(&stationConf);
    ETS_UART_INTR_ENABLE();
    wifi_station_connect();

    // change status
    CWJAPstatus = INFO_CWJAP_AP_PENDING;

    if (frame[FRAME_POS_CWJAP_IN_FLAGS] & FLAG_CWJAP_SYNCHRONOUS)
    {
    	// don't accept new commands
    	at_state = at_statProcess;
    }

    // setup a timer, then inform via STAT frame
	os_timer_disarm(&timer_CWJAPCheck);
	os_timer_setfn(&timer_CWJAPCheck, (os_timer_func_t *)timer_fun_CWJAPCheck, NULL);
	os_timer_arm(&timer_CWJAPCheck, 1000, 0);

    if (!(frame[FRAME_POS_CWJAP_IN_FLAGS] & FLAG_CWJAP_SYNCHRONOUS))
    {
		respFrame[FRAME_POS_MAGIC] 			= FRAME_MAGIC;
		respFrame[FRAME_POS_TYPE] 			= MAKE_RESP_TYPE(FRAME_CMD_CWJAP);
		respFrame[FRAME_POS_SIZE_LSB] 		= LOBYTE(FRAME_SIZE_CWJAP_NOSTAT);
		respFrame[FRAME_POS_SIZE_MSB] 		= HIBYTE(FRAME_SIZE_CWJAP_NOSTAT);
		respFrame[FRAME_POS_SEQ] 			= frame[FRAME_POS_SEQ];

		respFrame[FRAME_POS_RESCODE] 		= CWJAPstatus;

		return sendFrame(checksum(respFrame));
    }

    return 0;
}
