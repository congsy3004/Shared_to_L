/******************************************************************************
 * @file           : Platform_SPI.h
 * @brief          : Brief description
 * @author         : Huynh Cong Sy
 * @date           : 27-May-2025
 ******************************************************************************/

#ifndef PLATFORM_SPI_H
#define PLATFORM_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

/* -------------------------------------------------------------------------
 *                           << Include Files >>                                   
 * -------------------------------------------------------------------------*/
#include <ASTIdef.h>
#include <Platform_common.h>

/* -------------------------------------------------------------------------
 *                           << Exported Types >>                                   
 * -------------------------------------------------------------------------*/
typedef void (*fnp_SPI_Callback)( void );
/* -------------------------------------------------------------------------
 *                           << Exported Constants >>                                   
 * -------------------------------------------------------------------------*/

/* -------------------------------------------------------------------------
 *                           << Exported Macros >>                                   
 * -------------------------------------------------------------------------*/

/* -------------------------------------------------------------------------
 *                           << Exported Functions >>                                   
 * -------------------------------------------------------------------------*/
EM_PLATFORM_STATUS Platform_Init_SPI( void );
void SPI_TxCallbackRegister( fnp_SPI_Callback ap_cb );
void SPI_RxCallbackRegister( fnp_SPI_Callback ap_cb );
EM_PLATFORM_STATUS SPI_SendData( const U1* apu1_data, U2 au2_size );
EM_PLATFORM_STATUS SPI_ReceiveData( U1* apu1_data, U2 au2_size );

#ifdef __cplusplus
}
#endif

#endif /* PLATFORM_SPI_H */

/******************************** END OF FILE ********************************/
