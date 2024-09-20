#include "mbed.h"

AnalogIn light_sencor(PA_1);

int main(){
    float light;
    while(1){
        light = light_sencor.read()*100;
        printf("Light: %f\n",light);
    }
}