/**
 * automation.h
 * Main definitions for home automation functions
 */

#ifndef HA_AUTOMATION_H_
#define HA_AUTOMATION_H_

#define HA_MODE_SETUP			0x00
#define HA_MODE_RUN				0x01

#define HA_NODETYPE_LOAD		0x01
#define HA_NODETYPE_COMMAND		0x02

#define HA_LOAD_GENERIC			0x00
#define HA_LOAD_LIGHTING		0x01

#define MAKE_NODETYPE_TYPE(TYPE, SUBTYPE)	(((TYPE & 0x0F)<<4) | (SUBTYPE & 0x0F))


#endif /* HA_AUTOMATION_H_ */
