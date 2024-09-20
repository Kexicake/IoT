#define DEBUG

#include "mbed.h"
#include "button.h"

PwmOut led(LED1); // Встроенный светодиод
Ticker toggle_led_ticker; // Тикер для мерцания светодиодом
Button butt(BUTTON1); // Встроенная кнопка
Thread led_thread; // Поток для светодиода

float brightness = 0.0;
bool flag = 1; // Статус яркости светодиода (увеличивается или уменьшается)
bool led_st = 0; // Статус светодиода (вкл/выкл)

void tick_led(){
    if(brightness <= 0 || brightness >= 1){
        flag = !flag;
    }
    brightness += flag?1:-1 * 0.001;
    #ifdef DEBUG
        printf("Ticker start\n");
    #endif
}

void led_ded(){
    toggle_led_ticker.attach(&tick_led, 100ms);
    #ifdef DEBUG
        printf("Thread start\n");
    #endif
}

int main(){
    while (1)
    {
        if(butt.status() == 1){
            if (led_st)
                led_thread.terminate();
            else
                led_thread.start(led_ded);
            thread_sleep_for(1000);
        }
    }
    
}