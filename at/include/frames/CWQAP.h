/*
 * CWQAP.h
 * CWQAP : Join access point
 *
 *  Created on: Jan 14, 2015
 *      Author: Stefan
 */

#ifndef INCLUDE_FRAMES_CWQAP_H_
#define INCLUDE_FRAMES_CWQAP_H_

// 1 byte rescode + 1 byte payload
#define FRAME_SIZE_CWQAP			1

uint8_t		command_CWQAP_handler(uint8_t* frame);

#endif /* INCLUDE_FRAMES_COM_H_ */
