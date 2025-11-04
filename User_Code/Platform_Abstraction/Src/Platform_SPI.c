/******************************************************************************
 * @file           : Platform_SPI.c
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
#include "Platform_SPI.h"
#include "spi.h"

/* -------------------------------------------------------------------------
 *                           << Private Types >>                                   
 * -------------------------------------------------------------------------*/
static fnp_SPI_Callback fnp_spi_txcplcallback;
static fnp_SPI_Callback fnp_spi_rxcplcallback;
static EM_PLATFORM_STATUS em_platform_status;


/* -------------------------------------------------------------------------
 *                           << Private Variables >>                                   
 * -------------------------------------------------------------------------*/

/* -------------------------------------------------------------------------
 *                           << Private Constants >>                                   
 * -------------------------------------------------------------------------*/

/* -------------------------------------------------------------------------
 *                           << Private Macros >>                                   
 * -------------------------------------------------------------------------*/

/* -------------------------------------------------------------------------
 *                           << Private Functions Declarations >>                                   
 * -------------------------------------------------------------------------*/

/* -------------------------------------------------------------------------
 *                           << Private Functions Definitions >>                                   
 * -------------------------------------------------------------------------*/
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
    if (fnp_spi_txcplcallback != NULL)
    {
        fnp_spi_txcplcallback();
    }
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
    if (fnp_spi_rxcplcallback != NULL)
    {
        fnp_spi_rxcplcallback();
    }
}
/* -------------------------------------------------------------------------
 *                           << Public Functions Definitions >>                                   
 * -------------------------------------------------------------------------*/
EM_PLATFORM_STATUS Platform_Init_SPI( void )
{
	fnp_spi_txcplcallback = NULL; // Initialize the callback to NULL
	fnp_spi_rxcplcallback = NULL; // Initialize the callback to NULL
	em_platform_status = EM_PLATFORM_OK; // Initialize the status to OK
	return em_platform_status;
}

void SPI_TxCallbackRegister( fnp_SPI_Callback ap_cb )
{
	if ( ap_cb != NULL ) {
		fnp_spi_txcplcallback = ap_cb; // Register the callback function
	}
}

void SPI_RxCallbackRegister( fnp_SPI_Callback ap_cb )
{
	if ( ap_cb != NULL ) {
		fnp_spi_rxcplcallback = ap_cb; // Register the callback function
	}
}

EM_PLATFORM_STATUS SPI_SendData( const U1* apu1_data, U2 au2_size )
{
    if (HAL_SPI_Transmit_IT(&hspi1, apu1_data, au2_size) != HAL_OK)
    {
        em_platform_status = EM_PLATFORM_ERROR;
    }
    else
    {
        em_platform_status = EM_PLATFORM_OK;
    }
    return em_platform_status;
}

EM_PLATFORM_STATUS SPI_ReceiveData( U1* apu1_data, U2 au2_size )
{
	if ( HAL_OK != HAL_SPI_Receive_IT(&hspi1, apu1_data, au2_size) ) {
		em_platform_status = EM_PLATFORM_ERROR; // Set the status to error if reception fails
	}
	else {
		em_platform_status = EM_PLATFORM_OK; // Set the status to OK if reception is successful
	}
	return em_platform_status; // Return the status
}


/******************************** END OF FILE ********************************/
