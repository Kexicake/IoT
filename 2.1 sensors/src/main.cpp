#include "mbed.h"
#include <ADXL345_I2C.h>
#include <RangeFinder.h>

Thread light_thread;
Thread range_thread;

AnalogIn light_sencor(PA_1);
ADXL345_I2C accelerometer(I2C_SDA,I2C_SCL);
//Указываем pio(PA_2), scale(10), pulsetime(5000), timeout(100000)
RangeFinder rf(PA_2, 10, 5000, 10000);

float range;
float light;
int readings[3] = {0, 0, 0};

void lightSensor(){
    light = light_sencor.read() * 100;
    printf("Light: %f\n", light);
    fflush(stdout);
    thread_sleep_for(1000);
}

void rangeFinder(){
    range = rf.read_m();
    if(range == -1.0){ // если есть ошибки подключения или дальше 4-5 метров
        printf("Timeout Error.\n");
        fflush(stdout);
    }else{
        printf("Distance = %f m.\n", range);
        fflush(stdout);
    }
    thread_sleep_for(500);
}

int main(){
    light_thread.start(&lightSensor);
    range_thread.start(&rangeFinder);
    printf("Starting ADXL345 text...\n");
	

	//Перейдите в режим ожидания, чтобы настроить устройство.
	accelerometer.setPowerControl(0x00);
	
	// Полное разрешение, +/- 16 г, 4 мг / младший бит.
	accelerometer.setDataFormatControl(0x0B);
	
	// Скорость передачи данных 3.2 кГц.
	accelerometer.setDataRate(ADXL345_3200HZ);
	
	// Режим измерения.
	accelerometer.setPowerControl(0x08);

    while(1){
		accelerometer.getOutput(readings);
		
		// 13-битные, знаковые расширенные значения.
		printf("%i, %i, %i\n", (int16_t)readings[0], (int16_t)readings[1], (int16_t)readings[2]);       
    }
}