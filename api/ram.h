#ifndef _RAMMANAGE_H_
#define _RAMMANAGE_H_

#include "stdint.h"
#include "ff.h"
#include "app.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define WAIT_RAM_ALLOC								1
#define RAM_ALLOC_WAIT_TIME						(WAIT_RAM_ALLOC * MAX_NUM)
 
#define MALLOC(size)									Ram.malloc(size,RAM_ALLOC_WAIT_TIME,__FUNCTION__)
#define FREE(p)												Ram.free((void **)(&p))
 

//#define STATIC_MALLOC(size)	__attribute__((at(configOCRAM_START_ADDR)))
 

/* API struct */
typedef struct {
	void (*init)(void);
	void *(*malloc)(size_t ,uint32_t ,const char *);
	void (*free)(void **);
}Ram_S;
/*******************************************************************************
 * API
 ******************************************************************************/
extern Ram_S Ram;

#endif

