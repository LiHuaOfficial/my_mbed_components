#ifndef __RTT_LOG__
#define __RTT_LOG__

#include<stdint.h>
#include<stdarg.h>

/*
inspired by esp-idf,i love their logger
*/

typedef enum{LOG_LEVEL_INFO,LOG_LEVEL_DEBUG,LOG_LEVEL_WARNING,LOG_LEVEL_ERROR} log_level_t;

#ifdef __cplusplus
extern "C" {
#endif

//its said that ##__VA_ARGS__ not support by all compilers
//at least in armclang gcc its functional 
#define LOG_INFO(tag,fmt,...) Log_Base(LOG_LEVEL_INFO,tag,fmt,##__VA_ARGS__)
#define LOG_DEBUG(tag,fmt,...) Log_Base(LOG_LEVEL_DEBUG,tag,fmt,##__VA_ARGS__)
#define LOG_WARNING(tag,fmt,...) Log_Base(LOG_LEVEL_WARNING,tag,fmt,##__VA_ARGS__)
#define LOG_ERROR(tag,fmt,...) Log_Base(LOG_LEVEL_ERROR,tag,fmt,##__VA_ARGS__)

void Log_Init(void);

void Log_Base(log_level_t lv,const char* tag,const char* format,...);


#ifdef __cplusplus
}
#endif

#endif
