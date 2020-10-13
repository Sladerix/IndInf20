#include <iostream>
#include <string>
#include <wiringPi.h>
using namespace std;



/*I don't have the rasberry pi connected, so I'm using the windows to print the leds.*/

/*The automa that I'm implementing have this matrix
	x	a	b	c
	s0	s2	s1	s3
	s1	Er	s1	s3
	s2	s0	Er	Er
	
	The state are
	1. point --> s0
	s1 / s2 and 2. final s3
*/
const int autom_matrix [3][3] = {2,1,3, -1, 1, 3, 0, -1,-1};

/*The input value are going to modify the leds.
	1. Each led have a state
	2. and when there is gonna transfer from one state to another, the powerd up led switch
	3. the error state is the red led.
	
	In this case:
	 Led Blue = s0
	 Led Yellow = s1, s2
	 Led Green = s3
	 Led Red = error
	 Error = led red will power up and "down" within few seconds --> it will beep
*/
	 
/*bool Led_Blu = true;
bool Led_Yellow = false;
bool Led_Green = false;
bool Led_Red = false;*/
 
/*Le input letter may change in time, in this case I use an array standard:*/
const char inputs[] = {'a', 'a'};


/*size of the array in input*/
int ninputs = sizeof(inputs) / sizeof(inputs[0]);

/*Acrivate Led*/
void init(int Blu, int Yellow, int Green, int Red){
		wiringPiSetup();
		pinMode(Blu, OUTPUT);
		pinMode(Yellow, OUTPUT);
		pinMode(Green, OUTPUT);
		pinMode(Red, OUTPUT);
		digitalWrite(Blu, HIGH);
}



/*I have to implement the function next() that scans the letters.*/

char next(){
	
	//int i = 0 only one time
	static int i = 0;
	/*if i is greater than the array lenght, the function
	retuns a specific char letter that
	speficies the and of the phrase */
	if(i >= ninputs){
		return 'x';
	}else{
		return inputs[i++];
	}

	//if not return the next letter
	
}

int lettertonumber(char lettera){
	return (int)(lettera-96);
}

int nextState(int currState, char input){
	if ((autom_matrix[currState][lettertonumber(input)-1] >= -1) || (autom_matrix[currState][lettertonumber(input)-1]  != 3)){
		return autom_matrix[currState][lettertonumber(input)-1];
	}if(autom_matrix[currState][lettertonumber(input)-1] ==3 ){
		return -2;
	}else{
		return -3;
	}
	
	
}

bool isFinalState(int s)
{
	return s == 3;
}

void active_Led(bool Blu, bool Yellow, bool Green, bool Red){
	cout << "Led Blu " << (Blu ? "ON": "OFF") <<endl;
	cout << "Led Yellow " << (Yellow ? "ON": "OFF") <<endl;
	cout << "Led Green " << (Green ? "ON": "OFF") <<endl;
	cout << "Led Red " << (Red ? "ON": "OFF") <<endl;
	
}


/*change Led in raspberry
 * 	This function does not work. It enters the case but does not lighting up the leds. */
/*
void setLed(int currState,int Blu, int Yellow, int Green, int Red){
	switch(currState){
		case 0:
			digitalWrite(Blu, true);
			digitalWrite(Yellow, false);
			digitalWrite(Green, false);
			cout <<" case 0" << endl;
			break;
		
		case 1:
			digitalWrite(Blu, false);
			digitalWrite(Yellow, true);
			digitalWrite(Green, false);
			cout <<" case 1" << endl;
			break;
		
		case 2:
			digitalWrite(Blu, false);
			digitalWrite(Yellow, true);
			digitalWrite(Green, false);
			cout <<" case 2" << endl;
			break;
		
		case 3:
			digitalWrite(Blu, false);
			digitalWrite(Yellow, false);
			digitalWrite(Green, true);
			cout <<" case 3" << endl;
			break;
		
		default:
			digitalWrite(Blu, false);
			digitalWrite(Yellow, false);
			digitalWrite(Green, false);
			digitalWrite(Red, true);
			cout <<" case defualt" << endl;
	}

}
*/
/*Program error*/

void errLed(int Red, int pre_state){
	
	digitalWrite(pre_state, false);
	digitalWrite(Red, true);
	}

/*Change led activated*/
void led_activat(int CurrState, int pre_state){
	if(CurrState == 1){
			CurrState = 2;
			}
		if(pre_state ==1){
			pre_state =2;}
	if(pre_state == -1){
		
		}else {
		digitalWrite(pre_state, false);	
		}
		
		digitalWrite(CurrState, true);
		cout << CurrState << endl;
		cout << pre_state << endl;
	}


void changeLed(int currState, bool Blu, bool Yellow, bool Green, bool Red){
	switch(currState){
		case 0:
			Blu = true;
			Yellow = false;
			Green = false;
			Red = false;
			active_Led(Blu, Yellow, Green, Red);
			break;
		
		case 1:
			Blu = false;
			Yellow = true;
			Green = false;
			Red = false;
			active_Led(Blu, Yellow, Green, Red);
			break;
		
		case 2:
			Blu = false;
			Yellow = true;
			Green = false;
			Red = false;
			active_Led(Blu, Yellow, Green, Red);
			break;
		
		case 3:
			Blu = false;
			Yellow = false;
			Green = true;
			Red = false;
			active_Led(Blu, Yellow, Green, Red);
			break;
		
		default:
			Blu = false;
			Yellow = false;
			Green = false;
			Red = true;
			active_Led(Blu, Yellow, Green, Red);
	}
	
	}


int main() {
	cout << "Inputs size is " << ninputs << endl;
	int currState = 0;
	int state = -1;
	char c;
	
	
	/*Led input*/
	bool Led_Blu = true;
	bool Led_Yellow = false;
	bool Led_Green = false;
	bool Led_Red = false;
	
	/*GPIO ports*/
	int B = 0;
	int Y = 2;
	int G = 3;
	int R = 1;
	
	//int control = 0;
	
	
	/*Fist Led ON*/
	init(B, Y, G, R);
	cout << "\n"<<"First Led activated:" <<"\n" << endl;
	changeLed(currState, Led_Blu, Led_Yellow, Led_Green, Led_Red);
	
	/*I had to include delays because i can not see the leds.*/
	delay(1000);
	
	while(1)
	{
		// Get next input
		c = next();
		
		
		// We ran out of inputs, and
		if(c == 'x')
		{
			if(!isFinalState(currState))
				goto error;
			// This should never happen, if our algo works well
			else
				break;
		}
		
		cout << "------------------------------" << endl;
		cout << "Next input word is " << c << ", current state is " << currState << endl;
	
		
		state = nextState(currState, c);
		
		led_activat(state, currState);
		
		cout << "\n"<<"Led active:" <<"\n" << endl;
		changeLed(currState, Led_Blu, Led_Yellow, Led_Green, Led_Red);
		//setLed(currState,B, Y, G,  R);
		
		
		delay(1000);
		
		// Check for errors
		if(state < 0)
			goto error;
			
		
		cout << "Next state will be " << state << endl;
		
		if(isFinalState(state))
			break;
		
		// Update curr state
		currState = state;
	}
	
	cout << "Input sequence is legal for our Language" << endl;
	return 0;

error:
	cout << "ERROR!" << endl;
	cout << "Input " << c << " not legal for state " << currState << endl;
	cout << "Error code is " << state << endl;
	
	errLed(1, currState);
	
	//changeLed(state, Led_Blu, Led_Yellow, Led_Green, Led_Red);
	return state;

	
	return 0;
}
