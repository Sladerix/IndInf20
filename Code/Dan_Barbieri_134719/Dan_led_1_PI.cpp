// #define NO_PI

#include <iostream>
#include <unistd.h>  // used for the sleep function

#ifndef NO_PI
	#include <wiringPi.h> // used for GPIO Raspberry
#else
	#include <conio.h> // used for kbhit function
#endif

using namespace std;

///
/// Configuration
///
const int led_Blue_Output = 0;
const int led_Red_Output = 1;
const int led_Yellow_Output = 2;
const int led_Green_Output = 3;
const int timeout_Blue_Ms = 1000;
const int timeout_Red_Ms = 1000;
const int timeout_Yellow_Ms = 1000;
const int timeout_Green_Ms = 1000;


///
/// Utils
///
void init()
{
#ifndef NO_PI
	wiringPiSetup();
    pinMode(led_Blue_Output, OUTPUT);
    pinMode(led_Red_Output, OUTPUT);
    pinMode(led_Yellow_Output, OUTPUT);
    pinMode(led_Green_Output, OUTPUT);
#endif
}

///
/// Function
///

void setLed(int ledNumber, bool value) // ledNumber 0=Blue 1=Red 2=Yellow 3=Green
{
#ifndef NO_PI
    digitalWrite(ledNumber, value);
#endif
    if (ledNumber==0){
    	cout << "Setting led Blu Pin " << ledNumber << " to " << (value ? "ON" : "OFF") << endl;
	}
	else if (ledNumber==1){
    	cout << "Setting led Red Pin " << ledNumber << " to " << (value ? "ON" : "OFF") << endl;
	}
	else if (ledNumber==2){
    	cout << "Setting led Yellow Pin " << ledNumber << " to " << (value ? "ON" : "OFF") << endl;
	}
	else if (ledNumber==3){
    	cout << "Setting led Green Pin " << ledNumber << " to " << (value ? "ON" : "OFF") << endl;
	}
	else{
		cout << "I don't know which led turn on/off" << endl;
	}
}

///
/// Finished state machine status
///


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
	bool led_Blu_Status = false;
	bool led_Red_Status = false;
	bool led_Yellow_Status = false;
	bool led_Green_Status = false;
	int currentStatus = 0;
	int nextState = 0;
	bool enableType = true;
	
#ifndef NO_PI
	init();
	setLed(led_Blue_Output, led_Blu_Status);
	setLed(led_Red_Output, led_Red_Status);
	setLed(led_Yellow_Output, led_Yellow_Status);
	setLed(led_Green_Output, led_Green_Status);
#endif
	
	///
	/// start cycle first state activated
	///
		
	cout << "Current Status = S0" << endl;
	cout << "s0 = 1" << endl;
	cout << "TIP : type (a, b or c) character to continue" << endl;
	led_Blu_Status = true;
#ifndef NO_PI
	int countFirst=0;
	while(countFirst<6){
	    setLed(led_Blue_Output, led_Blu_Status);
        led_Blu_Status = !led_Blu_Status;
        sleep(1);
        countFirst = countFirst+1;
        delay(timeout_Blue_Ms);
	}	
#else
	while(1){
			setLed(led_Blue_Output, led_Blu_Status);
	        led_Blu_Status = !led_Blu_Status;
	        sleep(1);
	        if(kbhit()){
				break;
			}
	}
#endif
	led_Blu_Status = true;
	setLed(led_Blue_Output, led_Blu_Status);
	
	
	///
	/// state change based on state and input
	///

	while(enableType){
		int count0=0;
		int count1=0;
		int count2=0;
		cout << "type a character" << endl;
		cin >> entryChar;
		numberEntryChar = (int) entryChar;
		number = numberEntryChar - 'a';
		
		if (number>3){
			goto error;
			break;
		}
		
		else if (number<0){
			goto error;
			break;
		}
				
		nextState = checkNextState(currentStatus, number);
	
		switch (nextState){
			case 0:
				s0 = 1;
				s1 = 0;
				s2 = 0;
				s3 = 0;
				led_Blu_Status = true;
				led_Red_Status = false;
				led_Yellow_Status = false;
				led_Green_Status = false;
				currentStatus = nextState;
				enableType = true;
				cout << "Current Status = s0" << endl;
				cout << "s0 = " << s0 << endl;
				setLed(led_Blue_Output, led_Blu_Status);
				setLed(led_Red_Output, led_Red_Status);
				setLed(led_Yellow_Output, led_Yellow_Status);
				setLed(led_Green_Output, led_Green_Status);
				cout << "TIP : type (a, b or c) character to continue" << endl;
			#ifndef NO_PI
				while(count0<6){
				    setLed(led_Blue_Output, led_Blu_Status);
			        led_Blu_Status = !led_Blu_Status;
			        sleep(1);
			        count0 = count0+1;
			        delay(timeout_Blue_Ms);
				}	
			#else
				while(1){
						setLed(led_Blue_Output, led_Blu_Status);
				        led_Blu_Status = !led_Blu_Status;
				        sleep(1);
				        if(kbhit()){
							break;
						}
				}
			#endif   
				led_Blu_Status = true;
				setLed(led_Blue_Output, led_Blu_Status);
				break;
			case 1:
				s0 = 0;
				s1 = 1;
				s2 = 0;
				s3 = 0;
				led_Blu_Status = false;
				led_Red_Status = false;
				led_Yellow_Status = true;
				led_Green_Status = false;
				currentStatus = nextState;
				enableType = true;
				cout << "Current Status = S1" << endl;
				cout << "s1 = " << s1 << endl;
				setLed(led_Blue_Output, led_Blu_Status);
				setLed(led_Red_Output, led_Red_Status);
				setLed(led_Yellow_Output, led_Yellow_Status);
				setLed(led_Green_Output, led_Green_Status);
				cout << "TIP : type (b or c) character to continue" << endl;
			#ifndef NO_PI
				while(count1<6){
				    setLed(led_Yellow_Output, led_Yellow_Status);
			        led_Yellow_Status = !led_Yellow_Status;
			        sleep(1);
			        count1 = count1+1;
			        delay(timeout_Yellow_Ms);
				}	
			#else
				while(1){
						setLed(led_Yellow_Output, led_Yellow_Status);
				        led_Yellow_Status = !led_Yellow_Status;
				        sleep(1);
				        if(kbhit()){
							break;
						}
				}
			#endif   
				led_Yellow_Status = true;
				setLed(led_Yellow_Output, led_Yellow_Status);
				break;
			case 2:
				s0 = 0;
				s1 = 0;
				s2 = 1;
				s3 = 0;
				led_Blu_Status = false;
				led_Red_Status = false;
				led_Yellow_Status = true;
				led_Green_Status = false;
				currentStatus = nextState;
				enableType = true;
				cout << "Current Status = S2" << endl;
				cout << "s2 = " << s2 << endl;
				setLed(led_Blue_Output, led_Blu_Status);
				setLed(led_Red_Output, led_Red_Status);
				setLed(led_Yellow_Output, led_Yellow_Status);
				setLed(led_Green_Output, led_Green_Status);
				cout << "TIP : type (a) character to continue" << endl;
			#ifndef NO_PI
				while(count2<6){
				    setLed(led_Yellow_Output, led_Yellow_Status);
			        led_Yellow_Status = !led_Yellow_Status;
			        sleep(1);
			        count2 = count2+1;
			        delay(timeout_Yellow_Ms);
				}	
			#else
				while(1){
						setLed(led_Yellow_Output, led_Yellow_Status);
				        led_Yellow_Status = !led_Yellow_Status;
				        sleep(1);
				        if(kbhit()){
							break;
						}
				}
			#endif
				led_Yellow_Status = true;
				setLed(led_Yellow_Output, led_Yellow_Status);
				break;	
			case 3:
				s0 = 0;
				s1 = 0;
				s2 = 0;
				s3 = 1;
				led_Blu_Status = false;
				led_Red_Status = false;
				led_Yellow_Status = false;
				led_Green_Status = true;
				currentStatus = nextState;
				enableType = false;
				cout << "Current Status = S3" << endl;
				cout << "s3 = " << s3 << endl;
				setLed(led_Blue_Output, led_Blu_Status);
				setLed(led_Red_Output, led_Red_Status);
				setLed(led_Yellow_Output, led_Yellow_Status);
				setLed(led_Green_Output, led_Green_Status);
				cout << "program completed successfully" << endl;
				return 0;
				break;
			case -1:
				enableType = false;
				goto error;
			default : goto error;	
		}	
	}	
	error:
	s0 = 0;
	s1 = 0;
	s2 = 0;
	s3 = 0;
	led_Blu_Status = false;
	led_Red_Status = true;
	led_Yellow_Status = false;
	led_Green_Status = false;
	setLed(led_Blue_Output, led_Blu_Status);
	setLed(led_Red_Output, led_Red_Status);
	setLed(led_Yellow_Output, led_Yellow_Status);
	setLed(led_Green_Output, led_Green_Status);
	cout << "Error!!" << endl;
	cout << "incompatible input" << endl;
	return -1;
}	
