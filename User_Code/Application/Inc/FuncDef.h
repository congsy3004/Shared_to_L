//==================================================================================================
//
//	Project name	#xxxx
// 	File Name		FuncDef.h
//	
//	Author			H.Sy ( ASTI Corp )
//	Outline			This file contains the function prototype of all functions in the program
//	
//	History			Ver.0.01	2025.24.04	H.Sy	New
//
//==================================================================================================
//	Local Compile Option
//==================================================================================================
#ifndef FUNCDEF_H
#define FUNCDEF_H

//==================================================================================================
//	Header File
//==================================================================================================

#include "ASTIDef.h"	
#include "DataDef.h"      
#include "Platform_common.h"  
#include "Platform_Button.h"

//==================================================================================================
//  Function Prototype
//==================================================================================================
void Init_Core( void );

void Init_Main( void );
void App_Cyclic_Task( void );
void Init_App( void );

void Init_Com( void );
void Com_SendData( void );

void Init_Display( void );
void Init_UI( void );
void UI_Change( void );
void LCD_HardReset( void );
void LCD_SoftReset( void );



#endif // FUNCDEF_H
//************************************* End of File ************************************************
