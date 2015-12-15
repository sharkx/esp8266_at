/*

 *

frame.h
 *
 * Definitions for frame format while in non-AT comm protocol
 *
 * Frame format is as follows
 * [0] Magic number 0x88; actually can be anything BUT 'A' or 'a'
 * [1] Frame type
 * [2] LSB frame length
 * [3] MSB frame length frame length is the number of bytes until the checksum
 * [4] Frame sequence
 * [5...N] frame payload (depending on frame type)
 * [N+1] checksum; plain XOR of ALL frame bytes
 *
 * Frame type is built as a bitmap
 *  1RRTTTTT
 *    R = 00 not valid
 *        01 if frame is a request
 *        10 if frame is a command
 *        11 if frame is a response
 *    T = frame identified
 *
 *
 *  Created on: Jan 14, 2015
 *      Author: Stefan
 */

#ifndef USER_FRAME_H_
#define USER_FRAME_H_

#include "frames/error.h"
#include "frames/info.h"

#include "frames/COM.h"
#include "frames/CWMODE.h"
#include "frames/GMR.h"
#include "frames/IPD.h"
#include "frames/CWJAP.h"
#include "frames/CWQAP.h"
#include "frames/CIPSTART.h"
#include "frames/CIPSERVER.h"
#include "frames/CIPMUX.h"
#include "frames/GPIO.h"

#define FRAME_MAGIC				0x88

#define FRAME_LENGTH_SHORT		0x0F
#define FRAME_LENGTH_LONG		0xFF
#define FRAME_LENGTH_MAX		0x3FF

// the number of bytes, including the checksum
// that are in excess of the actual payload
#define FRAME_OVERHEAD			6

#define FRAME_POS_MAGIC			0
#define FRAME_POS_TYPE			1
#define FRAME_POS_SIZE			2
#define FRAME_POS_SIZE_LSB		2
#define FRAME_POS_SIZE_MSB		3
#define FRAME_POS_SEQ			4
#define FRAME_POS_RESCODE		5
#define FRAME_POS_PAYLOAD_IN	5
#define FRAME_POS_PAYLOAD_OUT	6

// STAT frames (status change and incoming data) start at 0
// COMMAND frames start at 0x08
#define FRAME_STAT_BASE			0x00
#define FRAME_CMD_BASE			0x08

// type-specific info

// if the frame is a RESPONSE, the result code is always the first byte of the payload
#define FRAME_POS_RESULT		5

#define FRAME_SEQ_NONE			0x00

#define FRAME_COMMAND_MASK		0x1F
#define FRAME_COMMAND_NONE		0x1F

#define FRAME_TYPE_MASK			0x60
#define FRAME_TYPE_REQUEST		0x20
#define FRAME_TYPE_COMMAND		0x40
#define FRAME_TYPE_RESPONSE		0x60

// status frames
#define FRAME_NO_CMD			0

#define MAKE_FRAME_TYPE(R, T)	(0x80 | ((r & 0x03)<<5) | (T & FRAME_COMMAND_MASK))

#define MAKE_REQ_TYPE(T)		(0x80 | FRAME_TYPE_REQUEST  | (T & FRAME_COMMAND_MASK))
#define MAKE_CMD_TYPE(T)		(0x80 | FRAME_TYPE_COMMAND  | (T & FRAME_COMMAND_MASK))
#define MAKE_RESP_TYPE(T)		(0x80 | FRAME_TYPE_RESPONSE | (T & FRAME_COMMAND_MASK))

#define FRAME_TYPE(T)			(T & FRAME_COMMAND_MASK)

#define FRAME_STAT_CWJAP				(FRAME_STAT_BASE + 0x01)

#define FRAME_CMD_GMR					(FRAME_CMD_BASE + 0x00)
#define FRAME_CMD_CWMODE				(FRAME_CMD_BASE + 0x01)
#define FRAME_CMD_COM					(FRAME_CMD_BASE + 0x02)
#define FRAME_CMD_CWJAP					(FRAME_CMD_BASE + 0x03)
#define FRAME_CMD_CWQAP					(FRAME_CMD_BASE + 0x04)
#define FRAME_CMD_CIPSTART				(FRAME_CMD_BASE + 0x05)
#define FRAME_CMD_CIPSERVER				(FRAME_CMD_BASE + 0x06)
#define FRAME_CMD_CIPMUX				(FRAME_CMD_BASE + 0x07)
#define FRAME_CMD_GPIO					(FRAME_CMD_BASE + 0x08)


#define SUCCESS					0x00

extern uint8_t 	dataFrameIn[FRAME_LENGTH_MAX];
extern uint8_t 	frameCheckSum;
extern uint16_t nFrameIndexPtr;
extern uint16_t nBytesToGo;

typedef uint8_t (*fun_requestHandler)(uint8_t* frame);

typedef struct
{
	fun_requestHandler requestHandler;
	fun_requestHandler commandHandler;
}
frameHandlerStruct;

extern frameHandlerStruct frameHandlers[];

#define LOBYTE(N16)		((N16)&0xFF)
#define HIBYTE(N16)		((N16)>>8)

uint16_t 	getFrameSize(uint8_t* frame);
uint8_t 	getFrameType(uint8_t* frame);
uint8_t 	getFrameCommand(uint8_t* frame);
uint8_t 	isRequestFrame(uint8_t* frame);
uint8_t 	isCommandFrame(uint8_t* frame);

uint8_t		processFrame(uint8_t* frameIn);
uint8_t		sendFrame(uint8_t* frameToSend);
uint8_t 	sendResultFrame(uint8_t* frameIn, uint8_t errorCode);

uint8_t*	checksum(uint8_t* frame);

#endif /* USER_FRAME_H_ */
