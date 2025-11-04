/******************************************************************************
 * @file           : Platform_Button.c
 * @brief          : Brief description
 * 
 * Detailed description of the file's purpose and functionality.
 *
 * @author         : Your Name
 * @date           : 18-Jun-2025
 ******************************************************************************/

/* -------------------------------------------------------------------------
 *                           << Include Files >>                                   
 * -------------------------------------------------------------------------*/
#include "Platform_Button.h"
#include "main.h"
#include <stdint.h>
/* -------------------------------------------------------------------------
 *                           << Private Types >>                                   
 * -------------------------------------------------------------------------*/

/* -------------------------------------------------------------------------
 *                           << Private Variables >>                                   
 * -------------------------------------------------------------------------*/
static U1 U1_button_B1_stt;
/* -------------------------------------------------------------------------
 *                           << Private Constants >>                                   
 * -------------------------------------------------------------------------*/

/* -------------------------------------------------------------------------
 *                           << Private Macros >>                                   
 * -------------------------------------------------------------------------*/
#define BUTTON_ACTIVE_HI
#define BUTTON_B1_PIN	BUTTON_B1_Pin
#define BUTTON_B1_PORT 	BUTTON_B1_GPIO_Port
#ifdef BUTTON_ACTIVE_HI
	#define BUTTON_RELEASED GPIO_PIN_RESET
	#define BUTTON_PRESSED 	GPIO_PIN_SET
#elif defined(BUTTON_ACTIVE_LO)
	#define BUTTON_RELEASED GPIO_PIN_SET
	#define BUTTON_PRESSED 	GPIO_PIN_RESET
#endif

#define BUTTON_SAMPLE_PERIOD	( (U1) 10 )

/* -------------------------------------------------------------------------
 *                           << Private Functions Declarations >>                                   
 * -------------------------------------------------------------------------*/

/* -------------------------------------------------------------------------
 *                           << Private Functions Definitions >>                                   
 * -------------------------------------------------------------------------*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	U1_button_B1_stt = BUTTON_PRESSED;	
}

/* -------------------------------------------------------------------------
 *                           << Public Functions Definitions >>                                   
 * -------------------------------------------------------------------------*/
void Platform_Init_Button( void )
{
	U1_button_B1_stt = BUTTON_RELEASED;
}

U1 Is_One_Press( void )
{
	if( U1_button_B1_stt == BUTTON_PRESSED )
	{
		U1_button_B1_stt = BUTTON_RELEASED;
		return U1TRUE;
	}
	else
	{
		return U1FALSE;
	}
}



/******************************** END OF FILE ********************************/