#ifndef _DATA_QUEUE_H_
#define _DATA_QUEUE_H_

#include "app_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
//#define DATA_QUEUE_ERGODIC_DEBUG	1

typedef void * DataQueueHandler_S;

typedef struct {
    DataQueueHandler_S *(*creat)(uint32_t ,uint32_t);
	bool (*enter)(DataQueueHandler_S *, void *);
	bool (*exit)(DataQueueHandler_S *, void *);
	uint32_t (*getSize)(DataQueueHandler_S *);
	uint32_t (*search)(DataQueueHandler_S *,void *);
	void (*toArray)(DataQueueHandler_S *,void *);
	bool (*deleted)(DataQueueHandler_S *,uint32_t );
	void (*empty)(DataQueueHandler_S * );
} DataQueue_S;

/*******************************************************************************
 * API
 ******************************************************************************/
extern DataQueue_S DataQueue;

#ifdef DATA_QUEUE_ERGODIC_DEBUG
extern void DataQueue_ErgodicDebug(DataQueueHandler_S *handler);
#endif

#endif

