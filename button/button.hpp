#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "mbed.h"

//#define BUTTON_USING_STD_FUNCTIONAL

#ifdef BUTTON_USING_STD_FUNCTIONAL
#include <functional>
#endif

/*
默认enable
使用InterruptIn、Timer、Timeout
使用std::bind给函数传参
*/

namespace myBtn
{

typedef enum btn_event{BTN_EVENT_PRESSED,BTN_EVENT_LONG_PRESSED,BTN_EVENT_DOUBLE_PRESSED} btn_event_t;

class Button
{
public:
    Button()=delete;
    Button(PinName pin);
    int enable();
    int disable();
    #ifdef BUTTON_USING_STD_FUNCTIONAL
    void attach(std::function<void(btn_event_t)>);
    #else
    void attach(Callback<void(btn_event_t)>);
    #endif
    

private:
    static const int BTN_CONFIG_FILTER_MS=10;
    static const int BTN_CONFIG_PRESS_MS=900;
    static const int BTN_CONFIG_DOUBLE_MS=300;

    void onFall();
    void onRise();
    void afterFilter();
    
    InterruptIn btnIn;//default enable
    Timeout timeout;
    #ifdef BUTTON_USING_STD_FUNCTIONAL
    std::function<void(btn_event_t)> btnEvtCb;
    #else
    Callback<void(btn_event_t)> btnEvtCb;
    #endif
    Timer t;

    using ms=std::chrono::milliseconds;

    ms whenFallMs;
    ms lastPressMs;
    
};
}


#endif


