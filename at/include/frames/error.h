/* error.h
 *  Created on: Jan 14, 2015
 *      Author: Stefan
 */

#ifndef USER_ERROR_H_
#define USER_ERROR_H_

// error codes have bit 7 set
// 0x00 means success
// codes ranging from 0x01 to 0x7F mean success with info
// codes ranging from 0x80 to 0xFF are real error codes
#define ERROR_INVALID_FRAME						0x81
#define ERROR_INVALID_PARAM						0x82
#define ERROR_INBOUND_DATA_TOO_LONG				0x83
#define ERROR_AP_ALREADY_CONNECTED				0x84
#define ERROR_AP_CONNECTION_PENDING				0x85
#define ERROR_AP_CONNECTION_TIMEOUT				0x86
#define ERROR_AP_ONLY_APMODE					0x87
#define ERROR_NO_FRAME_HANDLER					0x88
#define ERROR_AP_NOT_CONNECTED					0x89

#define ERROR_GENERIC_FAIL						0xFF

#endif /* USER_ERROR_H_ */
