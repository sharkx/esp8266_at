/*
 * File	: at_wifiCmd.c
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
#include "user_interface.h"
#include "at.h"
#include "at_miscCmd.h"
#include "osapi.h"
#include "c_types.h"
#include "mem.h"

uint8_t g_comProtocolMode;

extern at_funcationType at_fun[];

/** @defgroup AT_MISCCMD_Functions
  * @{
  */


/**
  * @brief  Test commad of set COM protocol mode.
  * @param  id: protocol identifier
  * @retval None
  */
void ICACHE_FLASH_ATTR
at_testCmdCOMMode(uint8_t id)
{
  char temp[32];
  os_sprintf(temp, "%s:(1-7)\r\n", at_fun[id].at_cmdName);
  uart0_sendStr(temp);
  at_backOk;
}

/**
  * @brief  Query commad of set wifi mode.
  * @param  id: commad id number
  * @retval None
  */
void ICACHE_FLASH_ATTR
at_queryCmdCOMMode(uint8_t id)
{
  char temp[32];

  os_sprintf(temp, "%s:%d\r\n", at_fun[id].at_cmdName, g_comProtocolMode);
  uart0_sendStr(temp);
  at_backOk;
}

/**
  * @brief  Setup commad of set wifi mode.
  * @param  id: commad id number
  * @param  pPara: AT input param
  * @retval None
  */
void ICACHE_FLASH_ATTR
at_setupCmdCOMMode(uint8_t id, char *pPara)
{
  uint8_t mode;
  char temp[32];

  pPara++;
  mode = atoi(pPara);
  if(mode == g_comProtocolMode)
  {
    at_backOk;
    return;
  }

  if((mode & COM_INBOUND_MASK) != 0)
  {
	  g_comProtocolMode = mode & COM_MASK;
	  at_backOk;
  }
  else
  {
    at_backError;
  }
}

/**
  * @}
  */
