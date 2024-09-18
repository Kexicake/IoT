#include "mbed.h"
#include "button.h"

Button::Button(PinName PinBut) : myButton(PinBut){
    myButton.mode(PullUp);
    timer.start();
}
bool Button::press(){
    if (myButton && !flag && timer.read_ms() - btnTimer > 100) {
        flag = true;
        btnTimer = timer.read_ms();
        printf("Button state is: press\n");
        return 1;
    }
    return 0;
}
bool Button::hold(){
    if (myButton && flag && timer.read_ms() - btnTimer > 500) {
        flag = true;
        btnTimer = timer.read_ms();
        printf("Button state is: hoooold\n");
        return 1;
    }
    return 0;
}
bool Button::relize(){
    if (myButton && flag && timer.read_ms() - btnTimer > 100) {
        flag = false;
        btnTimer = timer.read_ms();
        printf("Button state is: relise\n");
        return 1;
    } 
    return 0;
}

int Button::status(){
    if (hold()){
        return 1;
    }else if(press()){
        return 2;
    }else if(relize()){
        return 0;
    }
    return 0;
}