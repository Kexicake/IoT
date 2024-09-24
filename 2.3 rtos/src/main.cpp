#include "mbed.h"
#include "button.h"

PwmOut led(LED1); // Встроенный светодиод
Ticker toggle_led_ticker; // Тикер для мерцания светодиодом (выводить в серийный порт нельзя в тикере)
Button butt(BUTTON1); // Встроенная кнопка

float brightness = 0.0; // Яркость светодиода
bool flag = 1; // Статус яркости светодиода (увеличивается или уменьшается)
bool led_st = 0; // Статус светодиода (вкл/выкл)

void tick_led(){
    if(brightness <= 0 || brightness >= 1){
        brightness = brightness < 0? 0:1; 
        flag = !flag;
    }
    if(flag)
        brightness += 0.1;
    else
        brightness -= 0.1;
    led = brightness;
}

int main(){
    toggle_led_ticker.attach(&tick_led, 50ms);
    while (1)
    {
        if(butt.status() == 1){
            if (led_st)
                toggle_led_ticker.attach(&tick_led, 50ms);
            else
                toggle_led_ticker.detach();
            led_st = !led_st;
            thread_sleep_for(1000);
        }
    }
    
}