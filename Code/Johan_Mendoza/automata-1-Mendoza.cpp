#include <iostream>
#include <vector>

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
        return 2;
    } else if (inputs == 'a' && current_state == 2){
        return 0;
    } else if (inputs == 'b' && current_state == 0){
        return 1;
    } else if (inputs == 'b' && current_state == 1){
        return  1;
    } else if (inputs == 'c' && current_state == 0){
        return 3;
    } else if (inputs == 'c' && current_state == 1){
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
	char array[10];
	char i;
	int state;
	int current_state = 0;

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
                return 0;
            }

            state = nextState(current_state,i);

            if(state == -1){
                cout << "Input sequence (" << i << ") not legal for state S" << current_state << endl;
                return -1;
            } else if(state == 3) {
                cout << "we're in final state: S3" << endl;
                return 0;
            } else {
                cout << "Next state: S" << state << endl;
                current_state = state;
            }

	    }

	}

}