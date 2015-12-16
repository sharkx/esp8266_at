/**
 * config.h
 * Definitions for module configuration
 */

#ifndef MODULE_CONFIG_H_
#define MODULE_CONFIG_H_

#define ESP_PARAM_START_SEC   0x3C

#define ESP_PARAM_SAVE_0    1
#define ESP_PARAM_SAVE_1    2
#define ESP_PARAM_FLAG      3
struct esp_platform_sec_flag_param
{
	uint8 flag;
	uint8 pad[3];
};

typedef struct
{
	uint32_t baud;
	uint32_t saved;
} at_uartType;

typedef struct
{
	at_uartType 	uartParam;
	uint8_t			nodeType;

	// adjust accordingly
	uint8_t 		_padding[3];
} moduleConfig;

extern moduleConfig g_moduleConfig;

uint8_t config_init();

void ICACHE_FLASH_ATTR user_esp_platform_load_param(void *param, uint16 len);
void ICACHE_FLASH_ATTR user_esp_platform_save_param(void *param, uint16 len);

#endif /* MODULE_CONFIG_H_ */
