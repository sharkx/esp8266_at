/*
 * File	: at_ipCmd.h
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
#ifndef __AT_IP_H
#define __AT_IP_H

#define at_linkMax 5

typedef enum
{
	teClient, teServer
} teType;

typedef struct
{
	BOOL linkEn;
	BOOL teToff;
	uint8_t linkId;
	teType teType;
	uint8_t repeaTime;
	uint8_t changType;
	uint8 remoteIp[4];
	int32_t remotePort;
	struct espconn *pCon;
} at_linkConType;

#endif
