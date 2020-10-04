#include <iostream>

using namespace std;

const int sfn[][4] = {
						{ 2,  1,  3, -1},//each element of the array indicates the
						{-1,  1,  3, -1},//that will be assumed according to
						{ 0, -1, -1, -1},//to the current state and the input
						{-1, -1, -1, -1}
						};					

int checkNextState(int currentStatus, int number){
	return sfn[currentStatus][number];
	}

//int main(int argc, char **argv){
int main(){
	char entryChar;
	int numberEntryChar = 0;
	int number = 0;
	int t0 = 0;
	int t1 = 0;
	int t2 = 0;
	int t3 = 0;
	int currentStatus = 0;
	int nextState = 0;
	int enableType = 1;
	int enableTransition = 0;
	cout << "TIP : type (a, b or c) character to continue" << endl;
	
	while(enableType==1){
		if ( enableTransition == 1){
			t0 = 0;
			t1 = 0;
			t2 = 0;
			t3 = 0;
			cout << "t0 = " << t0 << endl;
			cout << "t1 = " << t1 << endl;
			cout << "t2 = " << t2 << endl;
			cout << "t3 = " << t3 << endl;	
		}
		else {
			enableTransition = 1;
		}
			
		cout << "type a character" << endl;
		cin >> entryChar;
		numberEntryChar = (int) entryChar;
		number = numberEntryChar - 'a';
		
		nextState = checkNextState(currentStatus, number);		
				
		switch (nextState){
			case 0:
				t0 = 1;
				currentStatus = nextState;
				enableType = 1;
				cout << "Transition to Status = s0" << endl;
				cout << "t0 = " << t0 << endl;
				cout << "TIP : type (a, b or c) character to continue" << endl;
				break;
			case 1:
				t1 = 1;
				currentStatus = nextState;
				enableType = 1;
				cout << "Transition to Status = S1" << endl;
				cout << "t1 = " << t1 << endl;
				cout << "TIP : type (b or c) character to continue" << endl;
				break;
			case 2:
				t2 = 1;
				currentStatus = nextState;
				enableType = 1;
				cout << "Transition to Status = S2" << endl;
				cout << "t2 = " << t2 << endl;
				cout << "TIP : type (a) character to continue" << endl;
				break;	
			case 3:
				t3 = 1;
				currentStatus = nextState;
				enableType = 0;
				cout << "Transition to Status = S3" << endl;
				cout << "t3 = " << t3 << endl;
				cout << "program completed successfully" << endl;
				t3 = 0;
				cout << "t0 = " << t0 << endl;
				cout << "t1 = " << t1 << endl;
				cout << "t2 = " << t2 << endl;
				cout << "t3 = " << t3 << endl;
				return 0;
				break;
			case -1:
				t0 = 0;
				t1 = 0;
				t2 = 0;
				t3 = 0;
				enableType = 0;
				goto error;
			default : goto error;	
		}	
	}	
	error:
	cout << "Error!!" << endl;
	cout << "incompatible input" << endl;
	return -1;
}	
	

				
				
				
