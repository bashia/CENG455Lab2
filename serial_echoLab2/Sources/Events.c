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
#include "server.h"


#ifdef __cplusplus
extern "C" {
#endif

//typedef struct server_message
//{
//   MESSAGE_HEADER_STRUCT   HEADER;
//   unsigned char                   DATA[5];
//} SERVER_MESSAGE, * SERVER_MESSAGE_PTR;
//
//SERVER_MESSAGE_PTR msg_ptr;
//  _mqx_uint          i;
//  _queue_id          server_qid;
//  bool            result;
//  _task_id           task_id;

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


	bool            result;
  /* Write your code here ... */
	//UART_DRV_SendData(myUART_IDX, myRxBuff, sizeof(myRxBuff));

		   //client_qid  = _msgq_open((_queue_number)(CLIENT_QUEUE_BASE), 0);

//		   if (client_qid == 0) {
//		      printf("\nCould not open a client message queue\n");
//		     // _task_block();
//		   }

		   msg_ptr = (SERVER_MESSAGE_PTR)_msg_alloc(message_pool);

		   	      if (msg_ptr == NULL) {
		   	         //printf("\nCould not allocate a message\n");
		   	         //_task_block();
		   	      }

		      msg_ptr->HEADER.SOURCE_QID = message_qid;
		        msg_ptr->HEADER.TARGET_QID = _msgq_get_id(0, SERVER_QUEUE);
		        msg_ptr->HEADER.SIZE = sizeof(MESSAGE_HEADER_STRUCT) +
		           strlen((char *)msg_ptr->DATA) + 1;
		        msg_ptr->DATA[0] = (myRxBuff);

		        result = _msgq_send(msg_ptr);

		        if (result != TRUE) {
		           //printf("\nCould not send a message\n");
		           //_task_block();
		        }

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
