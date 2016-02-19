/*
 * accessfunctions.h
 *
 *  Created on: Feb 10, 2016
 *      Author: cccarr
 */

#ifndef SOURCES_ACCESSFUNCTIONS_H_
#define SOURCES_ACCESSFUNCTIONS_H_

#define PERMLEN 64
int readpermission[PERMLEN] = {0};
int readindex = 0;
int writepermission = 0;
_queue_id write_qid = 0;
//int writeindex = 0;

int OpenR(uint16_t stream_no);

int _getline(char* string);

_queue_id OpenW(void);

int _putline(_queue_id qid, char* string);

int Close(void);


#endif /* SOURCES_SERVER_H_ */
