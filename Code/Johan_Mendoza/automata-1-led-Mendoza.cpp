#include <iostream>
#include <vector>
#include <cstring>

#ifndef NO_PI
#include <wiringPi.h>
#endif


///
/// Configuration
///
const int led_Blue = 3;
const int led_Red = 1;
const int led_Yellow = 0;
const int led_Green = 2;

const int timeoutMs = 1000;

///
/// Utils
///
void init()
{

    wiringPiSetup();
    pinMode(led_Blue, OUTPUT);
    pinMode(led_Red, OUTPUT);
    pinMode(led_Yellow, OUTPUT);
    pinMode(led_Green, OUTPUT);

}


void setLed(int ledNumber, bool value)
{

    digitalWrite(ledNumber, value);
    ///cout << "Setting led " << ledNumber << " to " << (value ? "ON" : "OFF") << endl;
}

using namespace std;


/*
S0 = 0
S1 = 1
S2 = 2
S3 = 3

State = -1 ---> input sequence not legal for state

Accept input in form a,a,b,c for array, or a single value.
*/


int nextState(int current_state, char inputs){

    if (inputs == 'a' && current_state == 0){
        setLed(led_Blue, false);
        setLed(led_Red,false);
        setLed(led_Yellow, true);
        return 2;
    } else if (inputs == 'a' && current_state == 2){
        setLed(led_Yellow, false);
        setLed(led_Red,false);
        setLed(led_Blue, true);
        return 0;
    } else if (inputs == 'b' && current_state == 0){
        setLed(led_Blue, false);
        setLed(led_Red,false);
        setLed(led_Yellow, true);
        return 1;
    } else if (inputs == 'b' && current_state == 1){
        setLed(led_Blue, false);
        setLed(led_Red,false);
        setLed(led_Yellow, true);
        return  1;
    } else if (inputs == 'c' && current_state == 0){
        setLed(led_Yellow, false);
        setLed(led_Blue, false);
        setLed(led_Red,false);
        setLed(led_Green, true);
        return 3;
    } else if (inputs == 'c' && current_state == 1){
        setLed(led_Yellow, false);
        setLed(led_Blue, false);
        setLed(led_Red,false);
        setLed(led_Green, true);
        return  3;
    } else {
        return -1;
    }


}



//* The function split, split an char array.
vector<char> split (char *arr, int arr_len, char splitby){
    vector<char> list;

    for(int i = 0; i < arr_len; i++){
        if (arr[i] != splitby) {
            auto it = list.insert(list.end(), arr[i]);
        }
    }
    return list;
}

int main()
{
    init();

    char array[10];
    char i;
    int state;
    int current_state = 0;

    setLed(led_Blue, true);
    delay(timeoutMs);

    vector<char> list;

    cout << "Type 'x' to quit the program" << endl;
    cout << "Accept input in format = a,a,b,c or a single value" << endl;

    //*std::cout << "Stato iniziale:" << current_state << endl;
    while(true)
    {
        cout << "Enter sequence = ";
        cin >> array;

        list = split(array,(unsigned)strlen(array),',');

        for (int c = 0; c < list.size(); c++){
            i = list[c];
            cout << "Current state: S" << current_state << endl;

            if (i == 'x'){
                cout << "Exited" << endl;
                setLed(led_Red,true);
                setLed(led_Blue,true);
                setLed(led_Yellow,true);
                setLed(led_Green,true);

                delay(500);

                setLed(led_Red,false);
                setLed(led_Blue,false);
                setLed(led_Yellow,false);
                setLed(led_Green,false);

                delay(500);

                setLed(led_Red,true);
                setLed(led_Blue,true);
                setLed(led_Yellow,true);
                setLed(led_Green,true);

                delay(500);

                setLed(led_Red,false);
                setLed(led_Blue,false);
                setLed(led_Yellow,false);
                setLed(led_Green,false);


                return 0;
            }

            state = nextState(current_state,i);

            if(state == -1){
                cout << "Input sequence (" << i << ") not legal for state S" << current_state << endl;
                setLed(led_Yellow, false);
                setLed(led_Blue, false);
                setLed(led_Red, true);
                delay(timeoutMs);

                setLed(led_Red, false);
                setLed(led_Green, false);
                return -1;
            } else if(state == 3) {
                cout << "we're in final state: S3" << endl;
                setLed(led_Yellow, false);
                setLed(led_Blue, false);
                setLed(led_Green, true);
                delay(timeoutMs);

                setLed(led_Green, false);
                setLed(led_Red, false);
                return 0;
            } else {
                cout << "Next state: S" << state << endl;
                current_state = state;
            }
            delay(timeoutMs);

        }

    }

}
