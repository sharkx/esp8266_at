/*
 * File	: user_main.c
 * This file is part of Espressif's AT+ command set program.
 * Copyright (C) 2013 - 2016, Espressif Systems
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ets_sys.h"
#include "driver/uart.h"
#include "osapi.h"
#include "at.h"
#include "frame.h"

#include "automation/automation.h"
#include "automation/setup.h"

extern uint8_t at_wifiMode;
extern void user_esp_platform_load_param(void *param, uint16 len);

void user_init(void)
{
  uint8_t userbin;
  uint32_t upFlag;
  at_uartType tempUart;

  gpio_init();

  user_esp_platform_load_param((uint32 *)&tempUart, sizeof(at_uartType));
  if(tempUart.saved == 1)
  {
    uart_init(tempUart.baud, BIT_RATE_19200);
  }
  else
  {
    uart_init(BIT_RATE_19200, BIT_RATE_19200);
  }

  // accept all commands and reply as frames
  g_comProtocolMode = COM_INBOUND_BOTH | COM_OUTBOUND_FRAME;
  at_wifiMode = wifi_get_opmode();

  ha_setup();

  os_printf("ready!!!\r\n");
  uart0_sendStr("ready\r\n");

  at_init();
}
