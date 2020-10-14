///
/// NOTE On Desktop systems, compile with -D NO_PI flag and disable raw #define
///	     or  compile without -D NO_PI flag and enable raw #define NO_PI
//   

#define NO_PI

#include <iostream>
#include <Windows.h>
#include <unistd.h>

#ifndef NO_PI
#include <wiringPi.h>
#endif

using namespace std;


///
/// Configuration
///

//const int led_Blue_Output = 0;
//const int led_Red_Output = 1;
const int led_Yellow_Output = 2;
//const int led_Green_Output = 3;
//int timeOn_Blue_Sec = 0;
//int timeOn_Red_Sec = 0;
int timeOn_Yellow_Sec = 1; // Value in Second
//int timeOn_Green_SEc = 0;
int count = 0;
//int phase_Duration_Blue = 10;
//int phase_Duration_Red = 10;
int phase_Duration_Yellow = 10;
//int phase_Duration_Green = 10;



///
/// Finished state machine status
///

const int mfn[1][2] = {
						{ 4, 5}, //each element of the array indicates the
					                    	 //that will be assumed according to
										 	 //to the current state and the input
					  };					

const int sfn[1][2] = {
						{ 4, 5}, //each element of the array indicates the
					                    	 //transition between two state
					  };			


///
/// Not used
///
int checkNextState(int currentStatus, int number){
	return mfn[currentStatus][number];
	}

int checkTransition(int currentTransition, int number){
	return sfn[currentTransition][number];
	}



///
/// Utils
///
void init_Output()
{
#ifndef NO_PI
	wiringPiSetup();
//    pinMode(led_Blue, OUTPUT);
//    pinMode(led_Red, OUTPUT);
    pinMode(led_Yellow, OUTPUT);
//    pinMode(led_Green, OUTPUT);
#endif
}


///
/// Functions
///

void setLed(int ledNumber, bool value) // ledNumber 0=Blue 1=Red 2=Yellow 3=Green
{
#ifndef NO_PI
    digitalWrite(ledNumber, value);
#endif
//    if (ledNumber==0){
//    	cout << "Setting led Blu Pin " << ledNumber << " to " << (value ? "ON" : "OFF") << endl;
//	}
//	else if (ledNumber==1){
//   	cout << "Setting led Red Pin " << ledNumber << " to " << (value ? "ON" : "OFF") << endl;
//	}
	if (ledNumber==2){
    	cout << "Setting led Yellow Pin " << ledNumber << " to " << (value ? "ON" : "OFF") << endl;
	}
//	else if (ledNumber==3){
//    	cout << "Setting led Green Pin " << ledNumber << " to " << (value ? "ON" : "OFF") << endl;
//	}
	else{
		cout << "I don't know which led turn on/off" << endl;
	}
}

void reset_Output() // reset state output to off
{
//	bool led_Blu_Status = false;
//	bool led_Red_Status = false;
	bool led_Yellow_Status = false;
//	bool led_Green_Status = false;
//  setLed(led_Blue_Output, led_Blu_Status);
//  setLed(led_Red_Output, led_Red_Status);
    setLed(led_Yellow_Output, led_Yellow_Status);
//  setLed(led_Green_Output, led_Green_Status);
	cout << "reset output for initialization" << endl;
}



void blinkYellow(int timeOn_Yellow_Sec){
	int currentStatus = 4;
	int currentTransition = 4;
	bool led_Yellow_Status = true;
	count = 0;
	while(1){
		setLed(led_Yellow_Output, led_Yellow_Status);
		if(currentStatus == 4 && led_Yellow_Status == true){		
			cout << "transition to state 5" << endl;
			currentTransition = 5;
			cout << "state 5 activated" << endl;
			currentStatus = 5;
		}	
		if(currentStatus == 5 && led_Yellow_Status == false){
			cout << "transition to state 4" << endl;
			currentTransition = 4;
			cout << "state 4 activated" << endl;
			currentStatus = 4;
		}			
        led_Yellow_Status = !led_Yellow_Status;
        if (count==phase_Duration_Yellow){
        	break;
		}
		count++;
        
#ifndef NO_PI
        delay(timeOn_Yellow_Sec);
#else
        sleep(timeOn_Yellow_Sec);
#endif
	}
}




int main(){
    //int currentStatus = 4;
	//int nextState = 0;
	//int currentTransition =0;
	init_Output();
	reset_Output();
	timeOn_Yellow_Sec = 1;
	blinkYellow(timeOn_Yellow_Sec);
	return 0;
}
