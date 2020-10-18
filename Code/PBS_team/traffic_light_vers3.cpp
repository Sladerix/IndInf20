#include <iostream>
#include <wiringPi.h>

using namespace std;

///
/// Configuration
///
enum leds {
    LED_RED = 0,
    LED_YELLOW,
    LED_GREEN
};
enum state_led {
    ON = true,
    OFF = false
};
// Times in second
enum times {
    TIME_RED = 4,
    TIME_GREEN = 5,
    TIME_YELLOW_GREEN = 2,
    TIME_YELLOW_ERROR = 4,
    TIME_NO_LIGHT_ERROR = 4
};
const int timeoutMs = 1000; // one second
const bool errorState = false;

int pins[] = {LED_RED, LED_YELLOW, LED_GREEN};

int numberPins = sizeof(pins)/sizeof(pins[0]);
int states[] = {2, // From state 0 I will go to 2
                0, // From state 1 I will go to 0
                1, // From state 2 I will go to 1
                -1, // Non-existent state
                5, // From state 3 I will go to 4
                4}; // From state 4 I will go to 3
const string coutMfn[] = {"Green red", "Green light", "Green/Yellow light"};

unsigned int count = 0;

const int mfn1[][6] = {
    {0, 0, 0, 0, 1 ,0},
    {0, 0, 1, 0, 0 ,0},
    {0, 0, 0, 0, 0 ,1}
};
const int mfn2[][3] = {
    {1, 0, 0},
    {0, 1, 1},
    {0, 0, 1}
};

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
}

void normalCycle()
{
    int initialState = 0;
    int currentState = initialState;
    setLed(LED_RED,ON);
    bool response;
    while(1){
        cout << "Current value is " << count << endl;
        response = mfn1[currentState][count];
        if (response == 1){
            resetLeds();
            currentState = states[currentState];
            for (int i = 0; i < sizeof(mfn2)/sizeof(mfn2[0]); i++){
                if (mfn2[currentState][i] == 1){
                    setLed(pins[i], ON);
                }
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

    while(1)
    {
        cout << "Current value is " << count << endl;

        switch(currentState)
        {
            case 4:
                if(count == TIME_YELLOW_ERROR)
                {
                    currentState = states[currentState];
                    resetLeds();
                    count = 0;
                }
                break;
            case 5:
                if(count == TIME_NO_LIGHT_ERROR)
                {
                    currentState = states[currentState];
                    resetLeds();
                    setLed(LED_YELLOW,ON);
                    count = 0;
                }
                break;
        }
        // Increment timer counter
        count++;
        delay(timeoutMs);
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
