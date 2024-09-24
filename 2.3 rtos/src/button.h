#ifndef BUTTON_H
#define BUTTON_H
#endif

#include "mbed.h"
class Button {  
    private: 
        Timer timer, start;
        bool flag = false;
        bool ArduinoMode;
        long long btnTimer = 0;
        DigitalIn myButton;
    public:
        Button(PinName PinBut, bool ArduinoMode = 0);
        bool press();
        bool hold();
        bool relize();
        int status();
};