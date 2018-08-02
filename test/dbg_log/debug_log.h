/******************************************************************************
  file: debug_log.h
  description: n/a
  Nhi Pham @ 2018
*******************************************************************************/
#ifndef _DEBUG_LOG_H_
#define _DEBUG_LOG_H_
#include <stdint.h>

extern void debug_init(void);
extern void debug_log(unsigned char* msg, uint16_t value);

#endif /* _DEBUG_LOG_H_ */