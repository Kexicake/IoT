#include <mbed.h> 

UnbufferedSerial pc(USBTX, USBRX); 
UnbufferedSerial dev(D8, D2); 
DigitalOut led1(LED1); 

void dev_recv() 
{ 
    char c; 
    led1 = !led1; 
    while(dev.readable()) { 
        dev.read(&c, sizeof(char)); 
        pc.write(&c, sizeof(char)); 
    } 
} 

void pc_recv() 
{ 
    char c; 
    while(pc.readable()) { 
        pc.read(&c, sizeof(char)); 
        dev.write(&c, sizeof(char)); 
    } 
} 

int main() 
{ 
    pc.baud(115200); 
    dev.baud(115200); 

    pc.attach(&pc_recv, SerialBase::RxIrq); 
    dev.attach(&dev_recv, SerialBase::RxIrq); 

    while(1) { 
        sleep(); 
    } 
}
  //AT+S.SCFG=wifi_wpa_psk_text,qjopa228  AT+CFUN=1
