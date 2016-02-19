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
#include "os_tasks.h"
#include <mqx.h>
#include <message.h>

#ifdef __cplusplus
extern "C" {
#endif 




/* User includes (#include below this line is not maintained by Processor Expert) */
#include "server.h"
#include "accessfunctions.h"


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
  /* Write your local variable definition here */

	int numencoding;

	SERVER_MESSAGE_PTR msg_ptr;
	 _task_id           task_id;
	 _queue_id server_qid;

	 /* Open a message queue: */
	 server_qid = _msgq_open(SERVER_QUEUE, 0);
	 /* Create a message pool: */
	 message_pool = _msgpool_create(sizeof(SERVER_MESSAGE),
	 NUM_USERS, 0, 0);

	 if (message_pool == MSGPOOL_NULL_POOL_ID) {
	      printf("\nCount not create a message pool\n");
	      //_task_block();
	   }


	 for (int j = 0; j < NUM_USERS; j++)
	 {
	    task_id = _task_create(0, USER_TASK, j); //(uint32_t)

	    if (task_id == 0)
	    {
		   printf("\nCould not create a User task\n");
		       //_task_block();
		}
	}


	printf("serialTask Created!\n\r");

	char buf[13];
	sprintf(buf, "\n\rType here: ");
	UART_DRV_SendDataBlocking(myUART_IDX, buf, sizeof(buf), 1000);

	printf("\nChecking for messages\n");
#ifdef PEX_USE_RTOS
  while (1) {
#endif

	if (interrupt_occur == 1)
	{
		int openreader = 0;
		//Check if open for read
		for (int i = 0; i < PERMLEN; i++)
		{
			/*Check if tasks are open for reading */
			if (readpermission[i] > 0)
			{
				openreader = 1;
				break;
			}
		}

		/*If no tasks are open for reading Reloop*/
		if (openreader == 1)
		{
			/*Recieve message */
			msg_ptr = _msgq_receive(server_qid, 0);
			numencoding = (int)msg_ptr->DATA[0];

			interrupt_occur = 0;

			/*Check if valid ASCII character*/ // ^U=21 ^H=8 ^W=23
			if ((numencoding > 31) && (numencoding < 127))
			{
				printf("%c", msg_ptr->DATA[0]);
			}
			else
			{
				switch(numencoding)
				{
				case 8: // 8=^H Erase Character
					printf("\b \b");
					break;
				case 13: // 13= New Line (Enter)
					printf("\n");
					//get_line
					break;
				case 21: // 21=^U Erase Line
					printf("\33[2K\r");  //VT100 escape code
					break;

				case 23: //8=^W Erase Word


					break;
				}
			}
		}
			_msg_free(msg_ptr);
		//}


	}
	//
    /* Write your code here ... */
	// Check handler queue


	// 	 If a user task has opened the device for reading
	// 	 	 Determine what the character is

	// 	 	 If the character is printable put it in the notification queue

	// 	 	 Else if the character is a special character, handle it appropriately

	// 	 	 Else if the character is none of the above, ignore it

	// 	 Else discard the character

    
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
