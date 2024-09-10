#include "mbed.h"
#include "iostream"
string st;

DigitalOut rele(D6);

DigitalIn mybutton(D4);
Timer timer, start;
long long releTimer = 0;
bool flag = false;
long long btnTimer = 0;
int main()
{    
    mybutton.mode(PullUp);
    timer.start();
    while(1)     {
        
        if(!rele){
            cout << "Введите пароль: ";
            cin >> st;
            while(1)     {
                if (mybutton && !flag && timer.read_ms() - btnTimer > 100) {
                    flag = true;
                    btnTimer = timer.read_ms();

                    if (st == "1234"){
                        cout << "Добро пожаловать!" << endl;
                        cout << "Дверь открыта!" << endl;
                        rele = 1;
                        releTimer = timer.read_ms();
                    }  else{
                        cout << "Пароль неверный!" << endl;
                    }
                }
                if (!mybutton && flag && timer.read_ms() - btnTimer > 100) {
                    flag = false;
                    btnTimer = timer.read_ms();
                    break;
                }
            }
        }
        st = "";
        if(timer.read_ms() - releTimer > 10000 && rele){
            rele=0;
            cout << "Дверь закрыта!" << endl;
        }
        
    }
}