/* error.h
 *  Created on: Jan 14, 2015
 *      Author: Stefan
 */

#ifndef USER_INFO_H_
#define USER_INFO_H_

// error codes have bit 7 set
// 0x00 means success
// codes ranging from 0x01 to 0x7F mean success with info
// codes ranging from 0x80 to 0xFF are real error codes

#define INFO_CWJAP_AP_NONE					0x01
#define INFO_CWJAP_AP_PENDING				0x02
#define INFO_CWJAP_AP_CONN					0x03

#define INFO_CWQAP_AP_NONE					0x04
#define INFO_CWQAP_AP_PENDING				0x05
#define INFO_CWQAP_AP_CONN					0x06

#define INFO_CIPSERVER_NO_SERVER			0x07


#endif /* USER_INFO_H_ */
