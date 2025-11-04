/******************************************************************************
 * @file           : Platfrom_ST7789VI.c
 * @brief          : Brief description
 * 
 * Detailed description of the file's purpose and functionality.
 *
 * @author         : Your Name
 * @date           : 27-May-2025
 ******************************************************************************/

/* -------------------------------------------------------------------------
 *                           << Include Files >>                                   
 * -------------------------------------------------------------------------*/
#include "Platform_ST7789VI.h"
#include "Platform_SPI.h"
#include "Platform_common.h"
#include "main.h"
#include "spi.h"
#include "lv_st7789.h"

/* -------------------------------------------------------------------------
 *                           << Private Constants >>                                   
 * -------------------------------------------------------------------------*/
#define U2_HOR_RES 				((U2)240)  // Horizontal resolution of the display
#define U2_VER_RES 				((U2)320)  // Vertical resolution of the display
#define U2_BYTES_PER_PIXEL		(LV_COLOR_FORMAT_GET_SIZE(LV_COLOR_FORMAT_RGB565))	
#define U2_CMD_TRANS_TIMEOUT	((U2) 1000)  // SPI transmission timeout
#define U4_DRAW_BUF_PAR_SIZE	((U4)(U2_HOR_RES * U2_VER_RES / 10 * U2_BYTES_PER_PIXEL))
// #define U4_DRAW_BUF_FULL_SIZE	((U4)(U2_HOR_RES * U2_VER_RES * U2_BYTES_PER_PIXEL))

/* -------------------------------------------------------------------------
 *                           << Private Macros >>                                   
 * -------------------------------------------------------------------------*/
/****************************************************************************/
/* Define pins connected to ST7789VI driver in 4-line serial interface 1 	*/
/*--------------------------------------------------------------------------*/
/* CS		|	Chip selection signal 										*/
/* DCX		|	LOW = write command, HIGH = write data						*/
/* SCK		|	Clock signal												*/
/* SDI		|	(Slave Data Input) Serial I/O singal						*/
/* RESET	|	Reset signal												*/
/****************************************************************************/
#define LCD_CS_PIN 		LCD_CS_Pin
#define LCD_CS_PORT 	LCD_CS_GPIO_Port
#define LCD_SCK_PIN 	LCD_SCK_Pin
#define LCD_SCK_PORT 	LCD_SCK_GPIO_Port
#define LCD_SDI_PIN 	LCD_SDI_Pin
#define LCD_SDI_PORT 	LCD_SDI_GPIO_Port
#define LCD_DCX_PIN 	LCD_DCX_Pin
#define LCD_DCX_PORT 	LCD_DCX_GPIO_Port
#define LCD_RESET_PIN 	LCD_RESET_Pin
#define LCD_RESET_PORT 	LCD_RESET_GPIO_Port

/* Define command value in Write Command Mode */
#define CMD_SLPOUT	((U1) 0x11) // Sleep Out
#define CMD_COLMOD	((U1) 0x3A) // Set color mode
#define CMD_MADCTL	((U1) 0x36) // Memory data access control
#define CMD_DISPON	((U1) 0x29) // Display on
#define CMD_CASET   ((U1) 0x2A) // Set the range of displaying content on X-axis
#define CMD_RASET   ((U1) 0x2B) // Set the range of displaying content on Y-axis
#define CMD_SWRESET ((U1) 0x01) // Soft reset
#define COLOR_RGB565 ((U1) 0x55) // 65K color of RGB & 16bit/pixel

/* Define the selected state of the display */
#define U1_SELECTED  U1TRUE
#define U1_RELEASED  U1FALSE

#define U1_MODE_CMD	 U1FALSE
#define U1_MODE_DATA U1TRUE

/* Define the reset type */
#define LCD_RESET_HARD 	U1TRUE
#define LCD_RESET_SOFT	U1FALSE		
/* -------------------------------------------------------------------------
 *                           << Private Types >>                                   
 * -------------------------------------------------------------------------*/
typedef struct 
{
	volatile bool is_display_on :1;
}ST_DISPLAY_DSC;

/* -------------------------------------------------------------------------
 *                           << Private Variables >>                                   
 * -------------------------------------------------------------------------*/
static U1 u1_is_LCD_busy;
static lv_display_t * pst_lv_disp; // Pointer to the display object
static U1 buf1[U4_DRAW_BUF_PAR_SIZE];
static U1 buf2[U4_DRAW_BUF_PAR_SIZE];
// static U1 buf1_full[U4_DRAW_BUF_FULL_SIZE];
// static U1 buf2_full[U4_DRAW_BUF_FULL_SIZE];
/* -------------------------------------------------------------------------
 *                           << Private Functions Declarations >>                                   
 * -------------------------------------------------------------------------*/
// static void indicate_lcd_busy( void );
static void wakeup_disp( void );
static void lcd_color_transfer_ready_cb( SPI_HandleTypeDef *hspi );
static int32_t lcd_io_init(void);
static void lcd_send_cmd(lv_display_t *disp, const uint8_t *cmd, size_t cmd_size, const uint8_t *param, size_t param_size);
static void lcd_send_color(lv_display_t *disp, const uint8_t *cmd, size_t cmd_size, uint8_t *param, size_t param_size);

/* -------------------------------------------------------------------------
 *                           << Private Functions Definitions >>                                   
 * -------------------------------------------------------------------------*/
static void lcd_reset( U1 au1_resettype )
{
	U1 u1_cmd = CMD_SWRESET;
	if ( au1_resettype == LCD_RESET_HARD )
	{
		HAL_GPIO_WritePin(LCD_RESET_PORT, LCD_RESET_PIN, GPIO_PIN_RESET);
		HAL_Delay(2);
		HAL_GPIO_WritePin(LCD_RESET_PORT, LCD_RESET_PIN, GPIO_PIN_SET);
		HAL_Delay(120);
	}
	else if ( au1_resettype == LCD_RESET_SOFT )
	{
		lcd_send_cmd(pst_lv_disp, &u1_cmd, sizeof(u1_cmd), NULL, 0);
	}	
}
static void wakeup_disp( void )
{
	U1 u1_cmd = CMD_SLPOUT;
	/* Sleep out */
	lcd_send_cmd(pst_lv_disp, &u1_cmd, sizeof(u1_cmd), NULL, 0);
	/* Display on */
	u1_cmd =  CMD_DISPON;
	lcd_send_cmd(pst_lv_disp, &u1_cmd, sizeof(u1_cmd), NULL, 0);

}

static void lcd_color_transfer_ready_cb( SPI_HandleTypeDef *hspi )
{
        /* CS high */
        HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
        u1_is_LCD_busy = 0;
        lv_display_flush_ready(pst_lv_disp);
}


/* Initialize LCD I/O bus, reset LCD */
static int32_t lcd_io_init(void)
{
	/* reset LCD */
	lcd_reset(LCD_RESET_HARD);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_DCX_PORT, LCD_DCX_PIN, GPIO_PIN_SET);

	return HAL_OK;
}
/* Platform-specific implementation of the LCD send command function. In general this should use polling transfer. */
static void lcd_send_cmd(lv_display_t *disp, const uint8_t *cmd, size_t cmd_size, const uint8_t *param, size_t param_size)
{
        LV_UNUSED(disp);
        while (u1_is_LCD_busy);   /* wait until previous transfer is finished */
        /* Set the SPI in 8-bit mode */
        hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
        HAL_SPI_Init(&hspi1);
        /* DCX low (command) */
        HAL_GPIO_WritePin(LCD_DCX_PORT, LCD_DCX_PIN, GPIO_PIN_RESET);
        /* CS low */
        HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
        /* send command */
        if (HAL_SPI_Transmit(&hspi1, cmd, cmd_size, U2_CMD_TRANS_TIMEOUT) == HAL_OK) {
                /* DCX high (data) */
                HAL_GPIO_WritePin(LCD_DCX_PORT, LCD_DCX_PIN, GPIO_PIN_SET);
                /* for short data blocks we use polling transfer */
                HAL_SPI_Transmit(&hspi1, (uint8_t *)param, (uint16_t)param_size, U2_CMD_TRANS_TIMEOUT);
                /* CS high */
                HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
        }
}

/* Platform-specific implementation of the LCD send color function. For better performance this should use DMA transfer.
 * In case of a DMA transfer a callback must be installed to notify LVGL about the end of the transfer.
 */
static void lcd_send_color(lv_display_t *disp, const uint8_t *cmd, size_t cmd_size, uint8_t *param, size_t param_size)
{
        LV_UNUSED(disp);
        while (u1_is_LCD_busy);   /* wait until previous transfer is finished */
        /* Set the SPI in 8-bit mode */
        hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
        HAL_SPI_Init(&hspi1);
        /* DCX low (command) */
        HAL_GPIO_WritePin(LCD_DCX_PORT, LCD_DCX_PIN, GPIO_PIN_RESET);
        /* CS low */
        HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
        /* send command */
        if (HAL_SPI_Transmit(&hspi1, cmd, cmd_size, U2_CMD_TRANS_TIMEOUT) == HAL_OK) {
                /* DCX high (data) */
                HAL_GPIO_WritePin(LCD_DCX_PORT, LCD_DCX_PIN, GPIO_PIN_SET);
                /* for color data use DMA transfer */
                /* Set the SPI in 16-bit mode to match endianness */
                hspi1.Init.DataSize = SPI_DATASIZE_16BIT;
                HAL_SPI_Init(&hspi1);
                u1_is_LCD_busy = 1;
                HAL_SPI_Transmit_DMA(&hspi1, param, (uint16_t)param_size / 2);
                /* NOTE: CS will be reset in the transfer ready callback */
        }
}
/* -------------------------------------------------------------------------
 *                           << Public Functions Definitions >>                                   
 * -------------------------------------------------------------------------*/
void Platform_Init_LCD( void )
{
	/* Initialize LCD-related I/O ports */
	if (lcd_io_init() != 0)
	return;
	
	/* Create a display instance for st7789-based LCD panel */ 
	pst_lv_disp = lv_st7789_create( U2_HOR_RES, U2_VER_RES, LV_LCD_FLAG_NONE, lcd_send_cmd, lcd_send_color );
	
	if (pst_lv_disp == NULL) {
		// Handle error in display creation
		LV_LOG_ERROR("Failed to create display");
		return;
	}
	lv_display_set_rotation(pst_lv_disp, LV_DISP_ROTATION_270);

	lv_display_set_buffers(pst_lv_disp, buf1, buf2, U4_DRAW_BUF_PAR_SIZE, LV_DISPLAY_RENDER_MODE_PARTIAL);

	/* Register SPI Tx Complete Callback */
	HAL_SPI_RegisterCallback(&hspi1, 0, lcd_color_transfer_ready_cb);
}

void LCD_HardReset( void )
{
	lcd_reset(LCD_RESET_HARD);
	HAL_Delay(5);
	wakeup_disp();
}

void LCD_SoftReset( void )
{
	lcd_reset(LCD_RESET_SOFT);
	HAL_Delay(120);
	wakeup_disp();
}

/******************************** END OF FILE ********************************/
