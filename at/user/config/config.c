/**
 *
 */

#include <stdlib.h>
#include "osapi.h"
#include "c_types.h"
#include "user_interface.h"
#include "driver/uart.h"
#include "driver/uart_register.h"

#include "config/config.h"

moduleConfig g_moduleConfig;

uint8_t config_init()
{
	// load settings from flash
	user_esp_platform_load_param((uint32 *) &g_moduleConfig, sizeof(moduleConfig));

	// config UART
	if (g_moduleConfig.uartParam.saved == 1)
	{
		uart_init(g_moduleConfig.uartParam.baud, BIT_RATE_19200);
	}
	else
	{
		uart_init(BIT_RATE_19200, BIT_RATE_19200);
	}

	return 0;
}

/******************************************************************************
 * FunctionName : user_esp_platform_load_param
 * Description  : load parameter from flash, toggle use two sector by flag value.
 * Parameters   : param--the parame point which write the flash
 * Returns      : none
 *******************************************************************************/
void ICACHE_FLASH_ATTR user_esp_platform_load_param(void *param, uint16 len)
{
	struct esp_platform_sec_flag_param flag;
	spi_flash_read((ESP_PARAM_START_SEC + ESP_PARAM_FLAG) * SPI_FLASH_SEC_SIZE, (uint32 *) &flag, sizeof(struct esp_platform_sec_flag_param));

	if (flag.flag == 0)
	{
		spi_flash_read((ESP_PARAM_START_SEC + ESP_PARAM_SAVE_0) * SPI_FLASH_SEC_SIZE, (uint32 *) param, len);
	}
	else
	{
		spi_flash_read((ESP_PARAM_START_SEC + ESP_PARAM_SAVE_1) * SPI_FLASH_SEC_SIZE, (uint32 *) param, len);
	}
}

/******************************************************************************
 * FunctionName : user_esp_platform_save_param
 * Description  : toggle save param to two sector by flag value,
 *              : protect write and erase data while power off.
 * Parameters   : param -- the parame point which write the flash
 * Returns      : none
 *******************************************************************************/
void ICACHE_FLASH_ATTR user_esp_platform_save_param(void *param, uint16 len)
{
	struct esp_platform_sec_flag_param flag;
	spi_flash_read((ESP_PARAM_START_SEC + ESP_PARAM_FLAG) * SPI_FLASH_SEC_SIZE, (uint32 *) &flag, sizeof(struct esp_platform_sec_flag_param));

	if (flag.flag == 0)
	{
		spi_flash_erase_sector(ESP_PARAM_START_SEC + ESP_PARAM_SAVE_1);
		spi_flash_write((ESP_PARAM_START_SEC + ESP_PARAM_SAVE_1) * SPI_FLASH_SEC_SIZE, (uint32 *) param, len);
		flag.flag = 1;
		spi_flash_erase_sector(ESP_PARAM_START_SEC + ESP_PARAM_FLAG);
		spi_flash_write((ESP_PARAM_START_SEC + ESP_PARAM_FLAG) * SPI_FLASH_SEC_SIZE, (uint32 *) &flag, sizeof(struct esp_platform_sec_flag_param));
	}
	else
	{
		spi_flash_erase_sector(ESP_PARAM_START_SEC + ESP_PARAM_SAVE_0);
		spi_flash_write((ESP_PARAM_START_SEC + ESP_PARAM_SAVE_0) * SPI_FLASH_SEC_SIZE, (uint32 *) param, len);
		flag.flag = 0;
		spi_flash_erase_sector(ESP_PARAM_START_SEC + ESP_PARAM_FLAG);
		spi_flash_write((ESP_PARAM_START_SEC + ESP_PARAM_FLAG) * SPI_FLASH_SEC_SIZE, (uint32 *) &flag, sizeof(struct esp_platform_sec_flag_param));
	}
}

