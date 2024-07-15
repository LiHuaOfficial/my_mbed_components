#include "mbed.h"
#include "button.hpp"

#include "SEGGER_RTT.h"
//using namespace rtos;

using namespace myBtn;

DigitalOut led1{p17};
DigitalOut led2{p18};
DigitalOut led3{p19};
DigitalOut led4{p20};



#ifdef BUTTON_USING_STD_FUNCTIONAL

void btnBlink1(btn_event_t btn_evt){
    switch (btn_evt)
    {
    case BTN_EVENT_PRESSED:
        led1=!led1;
        break;
    case BTN_EVENT_LONG_PRESSED:
        led2=!led2;
        break;
    default:
        break;
    }
}

void btnBlink2(btn_event_t btn_evt,DigitalOut *led){
    switch (btn_evt)
    {
    case BTN_EVENT_LONG_PRESSED:
        *led=!*led;
        break;
    
    default:
        break;
    }
}

void btnBlink3(btn_event_t btn_evt,DigitalOut *led){
    switch (btn_evt)
    {
    case BTN_EVENT_DOUBLE_PRESSED:
        *led=!*led;
        break;
    default:
        break;
    }
}
#else
void btnBlinkForCallback(btn_event_t evt){
    switch (evt)
    {
    case BTN_EVENT_PRESSED:
        led1=!led1;
        break;
    case BTN_EVENT_DOUBLE_PRESSED:
        led2=!led2;
        break;
    case BTN_EVENT_LONG_PRESSED:
        led3=!led3;
        break;
    
    default:
        break;
    }
}
#endif
int main(){

#ifdef BUTTON_USING_STD_FUNCTIONAL
    Button btn1(p13);
    Button btn2(p14);
    Button btn3(p15);
    btn1.attach(btnBlink1);
    btn2.attach(std::bind(btnBlink2,std::placeholders::_1,&led3));
    btn3.attach(std::bind(btnBlink3,std::placeholders::_1,&led4));
#else
    /*
    call back is hard to pass btn_event and custom args
    ,might need further wrapping
    ,isn't std::function good enough?
     */
    btn1.attach(callback(btnBlinkForCallback));
#endif

    while (1)
    {
        
        ThisThread::sleep_for(100ms);
    }
}