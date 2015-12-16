/**
 * automation.h
 * Main definitions for home automation functions
 */

#ifndef HA_AUTOMATION_H_
#define HA_AUTOMATION_H_

#define HA_NODETYPE_UNDEFINED	0x00
#define HA_NODETYPE_LOAD		0x01
#define HA_NODETYPE_COMMAND		0x02

#define HA_LOAD_GENERIC			0x00
#define HA_LOAD_LIGHTING		0x01

#define NODE_TYPE_MASK			0xF0
#define NODE_SUBTYPE_MASK		0x0F

#define MAKE_NODETYPE_TYPE(TYPE, SUBTYPE)	(((TYPE & 0x0F)<<4) | (SUBTYPE & 0x0F))

#define NODE_TYPE(T)			((T & NODE_TYPE_MASK)>>4)

extern uint8_t g_haNodeType;

#define MAC2STR_SHORT(a) (a)[2], (a)[3], (a)[4], (a)[5]
#define MACSTR_SHORT "%02x%02x%02x%02x"


#endif /* HA_AUTOMATION_H_ */
