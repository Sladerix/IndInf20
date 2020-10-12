#include <iostream>
#include <vector>
#include <cstring>

#include <wiringPi.h>


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


//only one led is ON, and if led = O, all led will set OFF
// B --> Blue, R --> Red, Y --> Yellow, G --> Green
void OnlyOneOn(char led){
    if (led == 'B'){
        setLed(led_Red,false);
        setLed(led_Yellow,false);
        setLed(led_Green,false);
        setLed(led_Blue,true);
    } else if (led == 'R'){
        setLed(led_Blue,false);
        setLed(led_Yellow,false);
        setLed(led_Green,false);
        setLed(led_Red,true);
    } else if (led == 'Y'){
        setLed(led_Red,false);
        setLed(led_Blue,false);
        setLed(led_Green,false);
        setLed(led_Yellow,true);
    } else if (led == 'G'){
        setLed(led_Red,false);
        setLed(led_Yellow,false);
        setLed(led_Blue,false);
        setLed(led_Green,true);
    } else {
        setLed(led_Red,false);
        setLed(led_Blue,false);
        setLed(led_Yellow,false);
        setLed(led_Green,false);

    }
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
        OnlyOneOn('Y');
        return 2;
    } else if (inputs == 'a' && current_state == 2){
        OnlyOneOn('B');
        return 0;
    } else if (inputs == 'b' && current_state == 0){
        OnlyOneOn('Y');
        return 1;
    } else if (inputs == 'b' && current_state == 1){
        OnlyOneOn('Y');
        return  1;
    } else if (inputs == 'c' && current_state == 0){
        OnlyOneOn('G');
        return 3;
    } else if (inputs == 'c' && current_state == 1){
        OnlyOneOn('G');
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
            list.insert(list.end(), arr[i]);
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
                for (int p = 0; p<2; p++) {

                    setLed(led_Red, true);
                    setLed(led_Blue, true);
                    setLed(led_Yellow, true);
                    setLed(led_Green, true);

                    delay(500);
                    OnlyOneOn('O');

                }

                return 0;
            }

            state = nextState(current_state,i);

            if(state == -1){

                cout << "Input sequence (" << i << ") not legal for state S" << current_state << endl;
                OnlyOneOn('R');
                delay(timeoutMs);

                OnlyOneOn('O');
                return -1;
            } else if(state == 3) {

                cout << "we're in final state: S3" << endl;
                OnlyOneOn('G');
                delay(timeoutMs);

                OnlyOneOn('O');
                return 0;
            } else {
                cout << "Next state: S" << state << endl;
                current_state = state;
            }
            delay(timeoutMs);

        }

    }

}
