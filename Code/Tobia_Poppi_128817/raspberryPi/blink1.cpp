//INFINITE CYCLE OF BLINKING LED, WITH 1 SEC DELAY BETWEEN ON AND OFF
//
//
//#define NO_PI 5

#include <iostream>

#ifndef NO_PI
#   include <wiringPi.h>
#endif
using namespace std;

///
/// CONFIGURATION

const int led_Blue = 0;
int timeoutMs = 1000;

///
/// UTILS

void init(){
#ifndef NO_PI
    wiringPiSetup();
    pinMode(led_Blue, OUTPUT);
#endif
}

void setLed(int ledNumber, bool value){
    cout << "Setting led " << ledNumber << " to " << (value ? "ON" : "OFF") << endl;
#ifndef NO_PI
    digitalWrite(ledNumber, value);
#endif
}

int main(){

    init();
    bool onoff = true;
    while(1){
      setLed(led_Blue, onoff);

      delay(timeoutMs);
      onoff = !onoff;
    }
    return 0;
}
