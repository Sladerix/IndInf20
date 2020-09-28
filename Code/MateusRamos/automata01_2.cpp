#include <iostream>

//define the number of states and Inputs
#define STATES 4
#define INPUTS 3

using namespace std;

//Array of allowed inputs;
char inputs[INPUTS] = { 'a','b','c'};
char inputOutput[INPUTS] = {4, 1, 9};
//State x Output table
char stateOutput[STATES][STATES]= {
        {'\0','a','b','c'},
        {'a','\0','\0','\0'},
        {'\0','\0','b','c'},
        {'\0','\0','\0','\0'}
};

//State x input table
int stateInput[STATES][INPUTS]{
        {1, 2, 3},
        {1, -1, -1},
        {-1, 2, 3},
        {-1, -1, -1}
};


//function implemented with State x input Table;
int nextStateI(int *currentState, int stateInput[][INPUTS], char input){
    if(stateInput[*currentState][input-'a'] != -1){
        *currentState = stateInput[*currentState][input-'a'];
        return inputOutput[input-'a'];
    }else{
        return -1;
    }
}
//funcion implemente with State x Output Table;
int nextStateS(int *currentState, char mState[][STATES] , char input){
    int i;
    int r = 0;
    for(i = 0; i < STATES; i++){
        if(mState[*currentState][i] == input){
            *currentState = i;
            r == 1;
            return i;
        }
    }
    if(r==0){
        cout << "Input non valido" << endl;
        return -1;
    }
}

int main() {
    int state;
    int check = 0;
    char input;

    while(check > -1){
        cout << "Inserisci carattere: " << endl;
        cin >> input;
        check = nextStateI(&state,stateInput, input);
        cout << "Stato attuale: " << state << endl;
    }

}
