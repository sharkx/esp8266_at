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

uint8_t ha_setup()
{
	// is module in setup mode or production mode ?
	// setup mode is needed when parameters are not set or when resetting with at least one button pressed
	if (false)
	{
		// setup mode
		// when in setup mode
	}
	else
	{
		// production mode
		// when in production mode, no AP functions
		ETS_UART_INTR_DISABLE();
		wifi_set_opmode(STATION_MODE);
		ETS_UART_INTR_ENABLE();

		// configure GPIO pins
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U, FUNC_GPIO0);
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2);
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO4_U, FUNC_GPIO4);
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO5_U, FUNC_GPIO5);

	}

	return 0;
}
