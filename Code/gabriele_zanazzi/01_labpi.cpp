#include <iostream>
#include <string>

using namespace std;

const int myData[][3] = {{2, 1, 3},{-1, 1, 3},{0, -1, -1}}; // FSM{state0{state2, state1, state3}, state1{stateError, state1, state3}, state2{state0, stateError, stateError}}
int currentState = 0, numberInput;

bool flag = true, illegalInput = false, firstTime = true;

int decodeInput(string input){
    int letterToNumber;
    char cInput;
    cInput = input[0];
    letterToNumber = cInput - 'a';
    if(letterToNumber == 0 || letterToNumber == 1 || letterToNumber == 2){
        return letterToNumber;
    }
    else{
        flag = false;
        return -1;
    }
}

void checkLenght(string input){
    int ninput;
    ninput = input.length();
    if(ninput > 1){
        cout << "Illegal input, only single letters are accepted!" << endl;
        illegalInput = true;
        flag = false;
        currentState = -1;
    }
}

int getState(bool flag){
    if(flag == true && firstTime == false){
        currentState = myData[currentState][numberInput];
        return currentState;
    }
    else{
        return currentState;
    }
    return -1;
}

void getLED(int state){
    switch(state){
        case 0:
                if(firstTime == true){
                    cout << "Led green is ON" << endl;
                    firstTime = false;    
                }
                else{
                    cout << "Led green is blinking" << endl; 
                }
                break;
        case 1:
                cout << "Led yellow 1 is ON" << endl;
                break;
        case 2:
                cout << "Led yellow 2 is ON" << endl;
                break;
        case 3:
                cout << "Led blue is ON" << endl;
                flag = false;
                break;
    }
}

void isCurrentstateLegal(int currentState){
    if (currentState == -1 && illegalInput == false)
    {
        cout << "Illegal input, u typed a single letter but it's not permitted, GAMEOVER, insert coin!" << endl;
        flag = false;
    }
    if(currentState == -1 && illegalInput == true){
        cout << "GAMEOVER, insert coin!" << endl; // managing the error that comes from string not accepted, string.lenght() > 1
        flag = false;
    }
    if(currentState != -1)
    {
        cout << "Now your state is: " << currentState << endl;
        getLED(currentState);
    }
}

int main(){
    cout << "Start your journey, good luck!" << endl;
    currentState = getState(flag);
    isCurrentstateLegal(currentState);
    while(flag){
        string letterInput;
        cout << "Insert a letter: " << endl;
        cin >> letterInput;
        checkLenght(letterInput);
        numberInput = decodeInput(letterInput);
        currentState = getState(flag);
        isCurrentstateLegal(currentState);
    }
    return 0;
}