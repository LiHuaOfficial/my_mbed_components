#include "button.hpp"

myBtn::Button::Button(PinName pin):btnIn(pin),btnEvtCb(nullptr)
{
    t.start();//mbed said their timer could last my whole life...
    btnIn.fall(callback(this,&Button::onFall));
    btnIn.rise(callback(this,&Button::onRise));
}

int myBtn::Button::enable()
{
    btnIn.enable_irq();
    return 0;
}

int myBtn::Button::disable()
{
    btnIn.disable_irq();
    return 0;
}



#ifdef BUTTON_USING_STD_FUNCTIONAL
void myBtn::Button::attach(std::function<void(btn_event_t)> cb)
{
    btnEvtCb=cb;
}

#else
void myBtn::Button::attach(Callback<void(btn_event_t)> cb)
{
    btnEvtCb=cb;
}


#endif

void myBtn::Button::onFall()
{
    btnIn.disable_irq();
    whenFallMs=std::chrono::duration_cast<ms>(t.elapsed_time());
    timeout.attach(callback(this,&Button::afterFilter),ms(BTN_CONFIG_FILTER_MS));
}

void myBtn::Button::onRise()
{   
    btnIn.disable_irq();
    auto currentMs=std::chrono::duration_cast<ms>(t.elapsed_time());
    if(btnEvtCb!=nullptr){
        if((currentMs-lastPressMs).count()<BTN_CONFIG_DOUBLE_MS){
            //following mouse logic,first tap will also behave
            btnEvtCb(BTN_EVENT_DOUBLE_PRESSED);
        }
        else if((currentMs-whenFallMs).count()>BTN_CONFIG_PRESS_MS){
            btnEvtCb(BTN_EVENT_LONG_PRESSED);
        }else{
            btnEvtCb(BTN_EVENT_PRESSED);
        }
    }
    lastPressMs=currentMs;
    timeout.attach(callback(this,&Button::afterFilter),ms(BTN_CONFIG_FILTER_MS));
}

void myBtn::Button::afterFilter()
{   
    btnIn.enable_irq();
}
