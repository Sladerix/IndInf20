#include <iostream>

using namespace std;



//this finite state machine takes in input an array of the letter a, b, c 
const char inputs[] = {'a', 'a', 'b', 'b', 'c'};



const int n_input = 3; //number of the different possible input
const int n_stati = 4; //number of the state
struct str_state
{
    int values[n_input];
    int output;
};

                                   //{ a  b  c} output
const str_state table[n_stati] = {  {{ 2, 1, 3},4}, //s0
                                    {{-1, 1, 3},7}, //s1                                    
                                    {{ 0,-1,-1},3}, //s2
                                    {{-1,-1,-1},5}};//s3

char next(){
    static int i =0;
    return inputs[i++];
}
int output(int n){
    return table[n].output;
}

int main () {   
    int state = 0;
    char curr_input;
    int n = sizeof(inputs) / sizeof(inputs[0]);  //this finds the size of the array 
    cout<< output(state)<<endl; //moore -->print the output of the starting state

    for(int k=0;k<n;k++){ 
        curr_input = next();
        int index = (int) curr_input - 'a';
        if(index >= 3){ //check if the input is not a, b or c -->default case
            cout<<"input non esistente"<<endl;
            goto error;
        }
        //cout<<"input ricevuto"<<endl;  mealy --> print if an input is received            
        int nextstate = table[state].values[index];
        if (nextstate < 0){ //check the combination of the current state and the input is correct
            cout<<"input non consentito nello stato s"<< state <<endl;
            goto error;            
        }
        else{
            cout<< output(nextstate)<<endl; //moore -->print the output of the state (exept the starting one)        
            state=nextstate;                       
        }        
    }        
    cout <<"sequenza legale"<<endl;
    return 0;

    error:
    cout <<"Errore"<<endl;
    return -1;  
}