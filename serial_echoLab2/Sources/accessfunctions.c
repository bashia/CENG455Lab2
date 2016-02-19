
#include "Cpu.h"
#include "Events.h"
#include "os_tasks.h"
#include <mqx.h>
#include <message.h>
#include "accessfunctions.h"

#ifdef __cplusplus
extern "C" {
#endif

int arraycontains(int array[], int value)
{
	for (int i = 0; i < sizeof(array); i++)
	{
		if (array[i] == value)
		{
			return 1;
		}

	}
	return 0;
}

int OpenR(uint16_t stream_no)
{
	/*get user id */
	_task_id tid = _task_get_id();

	if (arraycontains(readpermission, (int)tid) == 1)
	{
		return 0;
	}
	else
	{
		readpermission[readindex] = (int)tid;
		readindex += 1;
		return 1;
	}

}

int _getline(char* string)
{
	return 0;
}

_queue_id OpenW(void)
{
	if (writepermission == 0)
	{
		_task_id tid = _task_get_id();
		writepermission = (int)tid;
		return write_qid;
	}
	else
	{
		return 0;
	}

}

int _putline(_queue_id qid, char* string)
{
	return 0;
}

int Close(void)
{
	_task_id tid = _task_get_id();
		int privrevoked = 0;
		//Revoke Write Privilege
		if (writepermission == (int)tid)
		{
			writepermission = 0;
			privrevoked = 1;
		}
		/* IF READ PERMISSION CONTAINS tid
		 * readpermission[index] = 0
		 * privrevoked = 1;
		 */

		if (privrevoked == 1)
		{
			return 1;
		}
		else
		{
			return 0;
		}
}

#ifdef __cplusplus
}  /* extern "C" */
#endif
