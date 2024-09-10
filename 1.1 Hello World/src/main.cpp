#include "mbed.h"
PwmOut led(LED1);
float brightness=0.0;
int j = 0;
int main()
{    
    int i = 0;
    printf("Hello World !\n");
    while(1)     {
        
        
        while(j < 1000){
            brightness += 0.001;
            led = brightness;
            j++;
            
            wait_ns(500000); // 1 second
        }
        while(j > 0){
            brightness -= 0.001;
            led = brightness;
            j--;
            
            wait_ns(500000); // 1 second
        }
        // led = !led; // Toggle LED
        printf("This program runs since %d seconds.\n", i++);    
    }
}