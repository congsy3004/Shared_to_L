/******************************************************************************
 * @file           : App_Com.c
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

/* -------------------------------------------------------------------------
 *                           << Private Constants >>                                   
 * -------------------------------------------------------------------------*/
#define U1_TX_BUFFER_SIZE ((U1) 9) // Size of the transmission buffer
#define U1_RX_BUFFER_SIZE ((U1) 9) // Size of the reception buffer
/* -------------------------------------------------------------------------
 *                           << Private Macros >>                                   
 * -------------------------------------------------------------------------*/
/* -------------------------------------------------------------------------
 *                           << Private Types >>                                   
 * -------------------------------------------------------------------------*/
typedef struct {
	U1 u1_tx_buffer[U1_TX_BUFFER_SIZE]; // Buffer for transmission
	U1 u1_rx_buffer[U1_RX_BUFFER_SIZE]; // Buffer for reception
}ST_COM_HANDLER;
static ST_COM_HANDLER st_com_handler; // Communication handler instance
/* -------------------------------------------------------------------------
 *                           << Private Variables >>                                   
 * -------------------------------------------------------------------------*/
static U1 u1_data[]="Hello, SPI!"; // Sample data to be transmitted
/* -------------------------------------------------------------------------
 *                           << Private Functions Declarations >>                                   
 * -------------------------------------------------------------------------*/

/* -------------------------------------------------------------------------
 *                           << Private Functions Definitions >>                                   
 * -------------------------------------------------------------------------*/
static void SPI_TxCpltCallback( void )
{
	// Handle the completion of SPI transmission
	// This function can be used to process the data after transmission is complete
	// For example, you can log the transmitted data or trigger another action
	U1 u1_debug;
	u1_debug = 1;
}

static void SPI_RxCpltCallback( void )
{
	// Handle the completion of SPI reception
	// This function can be used to process the data after reception is complete
	// For example, you can log the received data or trigger another action
	SPI_ReceiveData(st_com_handler.u1_rx_buffer, 12);
}

/* -------------------------------------------------------------------------
 *                           << Public Functions Definitions >>                                   
 * -------------------------------------------------------------------------*/
void Init_Com( void )
{
}

void Com_SendData( void )
{
	SPI_SendData(u1_data, 11);
}


/******************************** END OF FILE ********************************/
