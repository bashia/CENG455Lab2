/* ###################################################################
**     Filename    : os_tasks.c
**     Project     : serial_echoLab2
**     Processor   : MK64FN1M0VLL12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-02-01, 16:06, # CodeGen: 1
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         serial_task - void serial_task(os_task_param_t task_init_data);
**
** ###################################################################*/
/*!
** @file os_tasks.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup os_tasks_module os_tasks module documentation
**  @{
*/         
/* MODULE os_tasks */

#include "Cpu.h"
#include "Events.h"
#include "rtos_main_task.h"
#include "os_tasks.h"
#include <mqx.h>
#include <message.h>

#ifdef __cplusplus
extern "C" {
#endif 

#define NUM_CLIENTS           (7)
#define FP_SYSTEM_QUEUE_BASE   2

/* Task IDs */
#define SERVER_TASK       5
#define CLIENT_TASK       6

/* Queue IDs */
#define SERVER_QUEUE      8
#define CLIENT_QUEUE_BASE 9

/* This structure contains a data field and a message header structure */
typedef struct server_message
{
   MESSAGE_HEADER_STRUCT   HEADER;
   unsigned char                   DATA[5];
} SERVER_MESSAGE, * SERVER_MESSAGE_PTR;

/* Function prototypes */
void server_task (uint32_t initial_data);
void client_task (uint32_t initial_data);
_pool_id message_pool;


/* User includes (#include below this line is not maintained by Processor Expert) */

/*
** ===================================================================
**     Callback    : serial_task
**     Description : Task function entry.
**     Parameters  :
**       task_init_data - OS task parameter
**     Returns : Nothing
** ===================================================================
*/
//Handler
/*Do forever
 	 Check handler queue
 	 If a user task has opened the device for reading
 	 	 Determine what the character is
 	 	 If the character is printable put it in the notification queue
 	 	 Else if the character is a special character, handle it appropriately
 	 	 Else if the character is none of the above, ignore it
 	 Else discard the character
 */
void serial_task(os_task_param_t task_init_data)
{
	SERVER_MESSAGE_PTR msg_ptr;
	   _queue_id          client_qid;
	   bool            result;
  /* Write your local variable definition here */
	printf("serialTask Created!\n\r");

	char buf[13];
	sprintf(buf, "\n\rType here: ");
	UART_DRV_SendDataBlocking(myUART_IDX, buf, sizeof(buf), 1000);

	msg_ptr = (SERVER_MESSAGE_PTR)_msg_alloc(message_pool);

	      if (msg_ptr == NULL) {
	         printf("\nCould not allocate a message\n");
	         _task_block();
	      }

	      msg_ptr->HEADER.SOURCE_QID = client_qid;
	        msg_ptr->HEADER.TARGET_QID = _msgq_get_id(0, SERVER_QUEUE);
	        msg_ptr->HEADER.SIZE = sizeof(MESSAGE_HEADER_STRUCT) +
	           strlen((char *)msg_ptr->DATA) + 1;
	        msg_ptr->DATA[0] = ('A');

	        printf("Client Task\n");

	        result = _msgq_send(msg_ptr);

	        if (result != TRUE) {
	           printf("\nCould not send a message\n");
	           _task_block();
	        }

	        /* wait for a return message */
	        msg_ptr = _msgq_receive(client_qid, 0);

	        if (msg_ptr == NULL) {
	           printf("\nCould not receive a message\n");
	           _task_block();
	        }

	         /* free the message */
	        _msg_free(msg_ptr);
  
#ifdef PEX_USE_RTOS
  while (1) {
#endif
    /* Write your code here ... */

    
    OSA_TimeDelay(10);                 /* Example code (for task release) */
   
    
    
    
#ifdef PEX_USE_RTOS   
  }
#endif    
}

/* END os_tasks */

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
