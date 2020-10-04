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
	int s0 = 1;
	int s1 = 0;
	int s2 = 0;
	int s3 = 0;
	int currentStatus = 0;
	int nextState = 0;
	int enableType = 1;
	
	
	cout << "Current Status = S0" << endl;
	cout << "s0 = 1" << endl;
	cout << "TIP : type (a, b or c) character to continue" << endl;
	
	while(enableType==1){
		cout << "type a character" << endl;
		cin >> entryChar;
		numberEntryChar = (int) entryChar;
		number = numberEntryChar - 'a';
		
		nextState = checkNextState(currentStatus, number);
	
		switch (nextState){
			case 0:
				s0 = 1;
				s1 = 0;
				s2 = 0;
				s3 = 0;
				currentStatus = nextState;
				enableType = 1;
				cout << "Current Status = s0" << endl;
				cout << "s0 = " << s0 << endl;
				cout << "TIP : type (a, b or c) character to continue" << endl;
				break;
			case 1:
				s0 = 0;
				s1 = 1;
				s2 = 0;
				s3 = 0;
				currentStatus = nextState;
				enableType = 1;
				cout << "Current Status = S1" << endl;
				cout << "s1 = " << s1 << endl;
				cout << "TIP : type (b or c) character to continue" << endl;
				break;
			case 2:
				s0 = 0;
				s1 = 0;
				s2 = 1;
				s3 = 0;
				currentStatus = nextState;
				enableType = 1;
				cout << "Current Status = S2" << endl;
				cout << "s2 = " << s2 << endl;
				cout << "TIP : type (a) character to continue" << endl;
				break;	
			case 3:
				s0 = 0;
				s1 = 0;
				s2 = 0;
				s3 = 1;
				currentStatus = nextState;
				enableType = 0;
				cout << "Current Status = S3" << endl;
				cout << "s3 = " << s3 << endl;
				cout << "program completed successfully" << endl;
				s3 = 0;
				cout << "s0 = " << s0 << endl;
				cout << "s1 = " << s1 << endl;
				cout << "s2 = " << s2 << endl;
				cout << "s3 = " << s3 << endl;
				return 0;
				break;
			case -1:
				s0 = 0;
				s1 = 0;
				s2 = 0;
				s3 = 0;
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
	

				
				
				
