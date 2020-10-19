#include <iostream>
#include <wiringPi.h>

using namespace std;

///
/// Configuration
///
enum leds {
    LED_RED = 1,
    LED_YELLOW,
    LED_GREEN
};
enum state_led {
    ON = true,
    OFF = false
};
// Times in second
enum times {
    TIME_RED = 1,
    TIME_GREEN = 1,
    TIME_YELLOW_GREEN = 1,
    TIME_YELLOW_ERROR = 4,
    TIME_NO_LIGHT_ERROR = 4
};
const int timeoutMs = 1000; // one second
const bool errorState = false;

int pins[] = {LED_RED, LED_YELLOW, LED_GREEN};
int timers[] = {TIME_RED, TIME_YELLOW_GREEN, TIME_GREEN, 0, TIME_YELLOW_ERROR, TIME_NO_LIGHT_ERROR};

int numberPins = sizeof(pins)/sizeof(pins[0]);
int states[] = {2, // From state 0 I will go to 2
                0, // From state 1 I will go to 0
                1, // From state 2 I will go to 1
                -1, // Non-existent state
                5, // From state 3 I will go to 4
                4}; // From state 4 I will go to 3
const string coutMfn[] = {"Green red", "Green light", "Green/Yellow light"};

unsigned int count = 0;

int* check;

//INITIALIZING DYNAMIC ALLOCATION OF ARRAYS BASING ON CONSTANTS PRE-DEFINED

const int mfn[][sizeof(states)/sizeof(states[0])] = {
    {LED_RED}, //state0
    {LED_YELLOW, LED_GREEN}, //state1
    {LED_GREEN}, //state2
    {}, //state3
    {LED_YELLOW}, //state4
    {} //state5
};

int* allocate_array(){
    int n = sizeof(states)/sizeof(states[0]);
    int* check = new int[n];

    for(int i = 0; i < n; ++i){
        check[i] = timers[i];
    }
    return check;
}

void setLed(int ledNumber, bool action)
{
    digitalWrite(ledNumber, action);
}

// Turns off all leds
void resetLeds()
{
    int indexPins;
    for(indexPins = 0; indexPins < numberPins; indexPins++)
    {
        setLed(pins[indexPins], OFF);
    }
}

void init()
{
    wiringPiSetup();
    int indexPins;
    for(indexPins = 0; indexPins < numberPins; indexPins++)
    {
        pinMode(pins[indexPins], OUTPUT);
    }
    resetLeds();
    check = allocate_array();
}

void normalCycle()
{
    int initialState = 0;
    int currentState = initialState;
    setLed(LED_RED,ON);
    while(1){
        cout << "Current value is " << count << endl;
        if (count == check[currentState]){
            resetLeds();
            currentState = states[currentState];
            for (int i = 0; i < sizeof(mfn[currentState])/sizeof(mfn[currentState][0]); i++){
                setLed(mfn[currentState][i], ON);
            }
            count = 0;
        }
        else{
            count++;
            delay(timeoutMs);
        }
    }
}

void errorCycle()
{
    int initialState = 4;
    int currentState = initialState;
    setLed(LED_YELLOW,ON);
    while(1){
        cout << "Current value is " << count << endl;
        if (count == check[currentState]){
            resetLeds();
            currentState = states[currentState];
            for (int i = 0; i < sizeof(mfn[currentState])/sizeof(mfn[currentState][0]); i++){
                setLed(mfn[currentState][i], ON);
            }
            count = 0;
        }
        else{
            count++;
            delay(timeoutMs);
        }
    }
}


void startTimer()
{
    cout << "Error State" << errorState << endl;

    if(!errorState)
    {
        normalCycle();
    }
    else
    {
        errorCycle();
    }
}

int main(int argc, char **argv)
{
    init();
    startTimer();
}
