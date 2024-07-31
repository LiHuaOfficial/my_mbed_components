#include "rtt_log.h"
#include "RTT/SEGGER_RTT.h"

void Log_Init(void){
    SEGGER_RTT_Init(); 
}

void Log_Base(log_level_t lv,const char* tag,const char* format, ...)
{
    switch (lv)
    {
    case LOG_LEVEL_DEBUG:
        SEGGER_RTT_printf(0,RTT_CTRL_TEXT_BRIGHT_WHITE"[DEBUG]");
        break;
    case LOG_LEVEL_WARNING:
        SEGGER_RTT_printf(0,RTT_CTRL_TEXT_BRIGHT_YELLOW"[WARNING]");
        break;
    case LOG_LEVEL_ERROR:
        SEGGER_RTT_printf(0,RTT_CTRL_TEXT_BRIGHT_RED"[ERROR]");
        break;
    case LOG_LEVEL_INFO:
        //share with default
    default:
        SEGGER_RTT_printf(0,RTT_CTRL_TEXT_BRIGHT_GREEN"[INFO]");
        break;
    }
    //tag
    SEGGER_RTT_printf(0,"%s:",tag);

    //content
    va_list args;
    va_start(args, format);
    SEGGER_RTT_vprintf(0,format,&args);
    va_end(args);

    //end of line
    SEGGER_RTT_PutChar(0,'\n');
}