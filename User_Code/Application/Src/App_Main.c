/******************************************************************************
 * @file           : App_Main.c
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
#include "FuncDef.h"
#include "DataDef.h"


#include "lvgl.h"
/* -------------------------------------------------------------------------
 *                           << Private Types >>                                   
 * -------------------------------------------------------------------------*/

/* -------------------------------------------------------------------------
 *                           << Private Variables >>                                   
 * -------------------------------------------------------------------------*/
static U2 u2_cyclic_task_counter; // Counter for cyclic task execution
static U1 u1_cyclic_task_flag; // Flag to indicate if the cyclic task should be executed
static U2 u2_cyclic1_task_counter; // Counter for cyclic task execution
static U1 u1_cyclic1_task_flag; // Flag to indicate if the cyclic task should be executed
/* -------------------------------------------------------------------------
 *                           << Private Constants >>                                   
 * -------------------------------------------------------------------------*/

/* -------------------------------------------------------------------------
 *                           << Private Macros >>                                   
 * -------------------------------------------------------------------------*/
#define U2_CYCLIC_TASK_INTERVAL ((U2) 2) // Define the interval for the cyclic task in milliseconds
#define U2_CYCLIC1_TASK_INTERVAL ((U2) 3000) // Define the interval for the cyclic task in milliseconds
/* -------------------------------------------------------------------------
 *                           << Private Functions Declarations >>                                   
 * -------------------------------------------------------------------------*/

/* -------------------------------------------------------------------------
 *                           << Private Functions Definitions >>                                   
 * -------------------------------------------------------------------------*/

/* -------------------------------------------------------------------------
 *                           << Public Functions Definitions >>                                   
 * -------------------------------------------------------------------------*/
int main( void )
{
	Init_App(); // Initialize the application
	while ( 1 )
	{
		if ( u1_cyclic_task_flag == U1TRUE ) {
			u1_cyclic_task_flag = U1FALSE; // Reset the flag after executing the task
			/* The task running lv_timer_handler should have lower priority than that running `lv_tick_inc` */
			lv_timer_handler();
		}
		if ( u1_cyclic1_task_flag == U1TRUE ) {
			u1_cyclic1_task_flag = U1FALSE; // Reset the flag after executing the task
		}
		if ( Is_One_Press() )
		{
			UI_Change();
			
		}
	}
	
	return 0; // Return 0 to indicate successful execution
}

void App_Cyclic_Task( void)
{
	if ( u2_cyclic_task_counter ==  U2_CYCLIC_TASK_INTERVAL)	{
		u2_cyclic_task_counter = U1MIN;
		u1_cyclic_task_flag = U1TRUE;
	}
	else
	{
		u2_cyclic_task_counter++;
	}
	#ifdef U2_CYCLIC1_TASK_INTERVAL
	if ( u2_cyclic1_task_counter ==  U2_CYCLIC1_TASK_INTERVAL)	{
		u2_cyclic1_task_counter = U1MIN;
		u1_cyclic1_task_flag = U1TRUE;
	}
	else
	{
		u2_cyclic1_task_counter++;
	}
	#endif
}

void Init_Main( void )
{
	// Initialize the cyclic task counter and flag
	u2_cyclic_task_counter = U1MIN;
	u1_cyclic_task_flag = U1FALSE;
	u2_cyclic1_task_counter = U1MIN;
	u1_cyclic1_task_flag = U1FALSE;

	// Additional initialization code can be added here
}

/******************************** END OF FILE ********************************/
