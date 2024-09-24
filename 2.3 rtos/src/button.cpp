#include "mbed.h"
#include "button.h"


/*
    Реализация обработки кнопки без использования ртос(потоков и тикеров)
    Реализация простоя и банальная, создан таймер который позволяет сгладить дребезг при нажатии на кнопку.
    Так же добавлена проддерка ардуино мода.
*/
Button::Button(PinName PinBut, bool ArduioMode = 0) : myButton(PinBut){
    myButton.mode(PullUp);
    timer.start();
}

bool Button::press(){
    if (ArduinoMode?myButton:!myButton && !flag && timer.read_ms() - btnTimer > 100) {
        flag = true;
        btnTimer = timer.read_ms();
        #ifdef DEBUG
            printf("Button state is: press\n");
        #endif
        return 1;
    }
    return 0;
}
bool Button::hold(){
    if (ArduinoMode?myButton:!myButton && flag && timer.read_ms() - btnTimer > 500) {
        flag = true;
        btnTimer = timer.read_ms();
        #ifdef DEBUG
            printf("Button state is: hoooold\n");
        #endif
        return 1;
    }
    return 0;
}
bool Button::relize(){
    if (ArduinoMode?!myButton:myButton && flag && timer.read_ms() - btnTimer > 100) {
        flag = false;
        btnTimer = timer.read_ms();
        #ifdef DEBUG
            printf("Button state is: relise\n");
        #endif
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