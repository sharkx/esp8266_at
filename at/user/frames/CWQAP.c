/*

 * CWQAP.c
 * CWQAP : Join access point
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

uint8_t command_CWQAP_handler(uint8_t* frame)
{
	// don't use buffers that are too large
	uint8_t respFrame[FRAME_LENGTH_SHORT];

	struct station_config stationConf;
	struct ip_info ipInfo;

	wifi_station_get_config(&stationConf);
	wifi_get_ip_info(0x00, &ipInfo);

	if (ipInfo.ip.addr != 0)
	{
		CWJAPstatus = INFO_CWJAP_AP_CONN;
	}

	if (CWJAPstatus == INFO_CWJAP_AP_NONE)
	{
		// already connected; disconnect first
		return sendErrorFrame(frame, ERROR_AP_NOT_CONNECTED);
	}

	if (CWJAPstatus == INFO_CWJAP_AP_PENDING)
	{
		// there is already a pending connection
		return sendErrorFrame(frame, ERROR_AP_CONNECTION_PENDING);
	}

	// disconnect !
	wifi_station_disconnect();
	CWJAPstatus = INFO_CWJAP_AP_NONE;

	respFrame[FRAME_POS_MAGIC] 			= FRAME_MAGIC;
	respFrame[FRAME_POS_TYPE] 			= MAKE_RESP_TYPE(FRAME_CMD_CWQAP);
	respFrame[FRAME_POS_SIZE_LSB] 		= LOBYTE(FRAME_SIZE_CWQAP);
	respFrame[FRAME_POS_SIZE_MSB] 		= HIBYTE(FRAME_SIZE_CWQAP);
	respFrame[FRAME_POS_SEQ] 			= frame[FRAME_POS_SEQ];

	respFrame[FRAME_POS_RESCODE] 		= SUCCESS;

	return sendFrame(checksum(respFrame));
}
