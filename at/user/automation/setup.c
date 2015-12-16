/**
 * setup.c
 * Main setup functions for home automation
 */

#include "ets_sys.h"
#include "at_wifiCmd.h"
#include "driver/uart.h"
#include "osapi.h"
#include "at.h"
#include "user_interface.h"

#include "automation/automation.h"
#include "automation/setup.h"

uint8_t g_haNodeType = HA_NODETYPE_UNDEFINED;

uint8_t ha_setup()
{
	// read module mode

	// is module in setup mode or production mode ?
	// setup mode is needed when parameters are not set or when resetting with at least one button pressed
	if (g_haNodeType == HA_NODETYPE_UNDEFINED)
	{
		// setup mode
		// when in setup mode, activate soft AP, so that we can remotely connect
		// to the node and set it up
		ETS_UART_INTR_DISABLE();

		struct softap_config apConfig;
		os_bzero(&apConfig, sizeof(struct softap_config));

		uint8 softAPMAC[6];
		wifi_get_macaddr(SOFTAP_IF, softAPMAC);

		apConfig.authmode = AUTH_WPA2_PSK;
		os_sprintf(apConfig.ssid, "NODE_%02X%02X%02X%02X", MAC2STR_SHORT(softAPMAC));
		apConfig.ssid_len = strlen(apConfig.ssid);
		os_sprintf(apConfig.password, "P4ssW0rd_%02X%02X%02X%02X", MAC2STR_SHORT(softAPMAC));
		apConfig.channel = 6;
		apConfig.max_connection = 1;
		apConfig.ssid_hidden = 0;

		wifi_softap_set_config(&apConfig);
		wifi_set_opmode(SOFTAP_MODE);

		wifi_softap_dhcps_start();

		ETS_UART_INTR_ENABLE();
	}
	else
	{
		// production mode
		// when in production mode, no AP functions
		ETS_UART_INTR_DISABLE();
		wifi_set_opmode(STATION_MODE);
		ETS_UART_INTR_ENABLE();

		switch (NODE_TYPE(g_haNodeType))
		{
			case HA_NODETYPE_LOAD :
				// pins 4 & 5 command two separate loads
				PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO4_U, FUNC_GPIO4);
				PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO5_U, FUNC_GPIO5);
				break;
			case HA_NODETYPE_COMMAND :
				// pins 4 & 5 are used to read button commands
				PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO4_U, FUNC_GPIO4);
				PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO5_U, FUNC_GPIO5);
				break;
		}
	}

	return 0;
}
