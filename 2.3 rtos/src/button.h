#ifndef BUTTON_H
#define BUTTON_H
#endif

#include "mbed.h"
class Button {  
    private: 
        Timer timer, start;
        bool flag = false;
        long long btnTimer = 0;
        DigitalIn myButton;
    public:
        Button(PinName PinBut);
        bool press();
        bool hold();
        bool relize();
        int status();
};