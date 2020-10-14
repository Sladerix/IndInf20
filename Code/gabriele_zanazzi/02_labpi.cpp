#include <iostream>
#include <unistd.h>

#define timerOne 5
#define timerTwo 10
#define timerThree 15
#define GreenLight 0
#define YellowLight 1
#define RedLight 2
#define HIGH true
#define LOW false

using namespace std;

const int myTimer[3] = {timerOne, timerTwo, timerThree};
const int timeoutMs = 200;
int count = 0, currentState = 0, errorCounter = 0;

void printLight(int lightNumber){
    switch (lightNumber)
    {
    case 0:
        cout << "GREEN LIGHT";
        break;
    case 1:
        cout << "YELLOW LIGHT";
        break;
    case 2:
        cout << "RED LIGHT";
        break;
    }
}

void prettyPrint(){
    cout << "================================================" << endl;
}

void setLight(int lightNumber, bool value)
{
    cout << "Setting ";
    printLight(lightNumber);
    cout << " to " << (value ? "ON" : "OFF") << endl;
}

void blinkingLight(){
    bool onoff = true;
    while(1){
        setLight(YellowLight, onoff);
        onoff = !onoff;
        sleep(1);
    }
}

void resetTimer(){
        count = 0;
        currentState++;
        errorCounter++;
}

void restartProcess(){
    sleep(1);
    cout << "U you can cross the pedestrian crossing!" << endl;
    sleep(1);
    prettyPrint();
    currentState = 0;
}

void getLight(int count){
    if(errorCounter != 10){
        if (count == myTimer[0] && currentState == 0)
        {
            setLight(GreenLight, HIGH);
            setLight(YellowLight, LOW);
            setLight(RedLight, LOW);
            prettyPrint();
            resetTimer();
        }
        if (count == myTimer[1] && currentState == 1)
        {
            setLight(GreenLight, HIGH);
            setLight(YellowLight, HIGH);
            setLight(RedLight, LOW);
            prettyPrint();
            resetTimer();
        }
        if (count == myTimer[2] && currentState == 2)
        {
            setLight(GreenLight, LOW);
            setLight(YellowLight, LOW);
            setLight(RedLight, HIGH);
            prettyPrint();
            resetTimer();
            restartProcess();
        }
    }
    else{
        blinkingLight();
    }
}

void startTimer(){
    while(1)
    {
        count++;
        usleep(timeoutMs * 1000);
        getLight(count);
    }
}

int main(){
    startTimer();
    return 0;
}