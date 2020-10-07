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
const int timeoutMs = 2000;
int pins[] = {ledBlue, ledRed, ledYellow, ledGreen};
int numberPins = sizeof(pins)/sizeof(pins[0]);

void setLed(int ledNumber)
{

    digitalWrite(ledNumber, true);

}

// Turns off all leds
void resetLeds() {

    int indexPins;
    for(indexPins = 0; indexPins < numberPins; indexPins++)
    {

        digitalWrite(pins[indexPins], false);

    }

}

void init()
{
    wiringPiSetup();
    pinMode(ledBlue, OUTPUT);
    pinMode(ledRed, OUTPUT);
    pinMode(ledYellow, OUTPUT);
    pinMode(ledGreen, OUTPUT);
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
        digitalWrite(ledRed, true);
        cout << "Input not legal!" << endl;
    } else if(currentState == 0) {
        digitalWrite(ledBlue, true);
    } else if(currentState == 1 || currentState == 2) {
        digitalWrite(ledYellow, true);
        cout << outmfn[currentState] << endl;
    } else if(currentState == 3) {
        digitalWrite(ledGreen, true);
        cout << "Input is legal :)" << endl;
    }

}

int main(int argc, char **argv)
{

        init();

		int state = 0;
		digitalWrite(ledBlue, true);

		while(true)
		{

			char letter = ' ';
			cout << "Insert a symbol: ";
			cin >> letter;
			int numLetter = (int) letter - 'a';
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
