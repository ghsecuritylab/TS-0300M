#ifndef _AUDIO_SAI_H_
#define _AUDIO_SAI_H_

#include "stdint.h"
#include "app_common.h"
#include "data_stream.h"


/*******************************************************************************
 * Definitions
 ******************************************************************************/
typedef enum {
	normal,
	stream,
}TransmitType_EN;



typedef struct {
    void (*init)(void);
		void (*deinit)(void);
		
		void (*recStart)(TransmitType_EN );
		void (*recStop)(void);
		void (*recEnd)(void);
		
		void (*sendStart)(void);
		void (*sendStop)(void);
		void (*sendEnd)(void);
		
		uint32_t (*dataOutput)(uint8_t *,uint32_t );
		void (*dataInput)(uint8_t* );
		
		void (*setInputStream)(DataStreamHandler_S *);
		void (*setOutputStream)(DataStreamHandler_S *);
} AudioSai_S;

/*******************************************************************************
 * API
 ******************************************************************************/
extern AudioSai_S AudioSai;

#endif

