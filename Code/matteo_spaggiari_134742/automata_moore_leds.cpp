#include <iostream>
#include <wiringPi.h>

using namespace std;

///
/// Configuration
///
const int ledBlue = 0;
const int ledRed = 1;
const int ledYellow = 2;
const int ledGreen = 3;
const int timeoutMs = 3000;
const bool ON = true;
const bool OFF = false;
int pins[] = {ledBlue, ledRed, ledYellow, ledGreen};
int numberPins = sizeof(pins)/sizeof(pins[0]);

void setLed(int ledNumber, bool action)
{

    digitalWrite(ledNumber, action);

}

// Turns off all leds
void resetLeds() {

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

//STATE MACHINE OF MOORE
//Input Symbols:             'a' 'b'  'c'  'x'
const int table[][4] = {
                            { 2,  1,   3,  -1}, //  State 0
                            {-1,  1,   3,  -1}, //  State 1
                            { 0, -1,  -1,  -1}, //  State 2
                            {-1, -1,  -1,  -1}  //  State 3
                        };

const string outmfn[] = {"You are in state: 0", "You are in state: 1", "You are in state: 2", "You are in state: 3"};


int sfn(int currentState, int in)
{

	return table[currentState][in];

}

void mfn(int currentState)
{

    resetLeds();

    if(currentState < 0) {
        setLed(ledRed, ON);
        cout << "Input not legal!" << endl;
        delay(timeoutMs);
        // Turn OFF Led
        setLed(ledRed, OFF);
    } else if(currentState == 0) {
        setLed(ledBlue, ON);
        cout << outmfn[currentState] << endl;
    } else if(currentState == 1 || currentState == 2) {
        setLed(ledYellow, ON);
        cout << outmfn[currentState] << endl;
    } else if(currentState == 3) {
        setLed(ledGreen, ON);
        cout << "Input is legal :)" << endl;
        delay(timeoutMs);
        // Turn OFF Led
        setLed(ledGreen, OFF);
    }

}

int main(int argc, char **argv)
{

        init();

	int state = 0;
	setLed(ledBlue, ON);

	while(true)
	{

		char letter = ' ';
		cout << "Insert a symbol: ";
		cin >> letter;
		int numLetter = (int) letter - 'a';
	
		// Check if it's a legal symbol
		if(numLetter < 0 || numLetter > 2) {
	
	                resetLeds();
	                setLed(ledRed, ON);
	                cout << "Symbol not legal" << endl;
	                delay(timeoutMs);
	                // Turn OFF Led
	                setLed(ledRed, OFF);
	                break;
			return -1;
	
		}
	
		state = sfn(state, numLetter);
		mfn(state);
	
		if (state < 0)
		{
                	break;
			return -1;
            	}
		else if (state == 3)
		{
                	break;
			return 0;
            	}
	}

        return 0;

}
