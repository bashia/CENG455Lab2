/* ###################################################################
**     Filename    : Events.c
**     Project     : serial_echoLab2
**     Processor   : MK64FN1M0VLL12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-02-01, 15:35, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"
#include "rtos_main_task.h"
#include "os_tasks.h"
#include <mqx.h>
#include <bsp.h>
#include <message.h>

#ifdef __cplusplus
extern "C" {
#endif 

typedef struct server_message
{
   MESSAGE_HEADER_STRUCT   HEADER;
   unsigned char                   DATA[5];
} SERVER_MESSAGE, * SERVER_MESSAGE_PTR;

typedef struct my_isr_struct
{
   void                 *OLD_ISR_DATA;
   INT_ISR_FPTR          OLD_ISR;
   _mqx_uint             COUNTER;
} MY_ISR_STRUCT, * MY_ISR_STRUCT_PTR;

/* User includes (#include below this line is not maintained by Processor Expert) */

/*
** ===================================================================
**     Callback    : myUART_RxCallback
**     Description : This callback occurs when data are received.
**     Parameters  :
**       instance - The UART instance number.
**       uartState - A pointer to the UART driver state structure
**       memory.
**     Returns : Nothing
** ===================================================================
*/
void myUART_RxCallback(uint32_t instance, void * uartState)
{
	 SERVER_MESSAGE_PTR msg_ptr;
	   _queue_id          client_qid;
	   bool            result;
  /* Write your code here ... */
	UART_DRV_SendData(myUART_IDX, myRxBuff, sizeof(myRxBuff));

	return;
}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
