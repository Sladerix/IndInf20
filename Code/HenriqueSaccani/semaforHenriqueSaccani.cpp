#include<iostream>

#ifndef NO_PI
#include <wiringPi.h>
 #endif
 
const int blue_led=0;
const int red_led = 5;
const int green_led = 2;
const int yellow_led = 3;

const int timeoutRedGreen = 4000;
const int timeoutGreenYellow=3000;
const int timeoutYellowRed=1000;

int act_led=red_led; 

void init (int led_n){
	#ifndef NO_PI
		wiringPiSetup();
		pinMode(led_n,OUTPUT);
	#endif
}

void setLed ( int led_n, bool value){
	cout << " led n "<< led_n << " setted to " << (value ? "ON" : "OFF") << endl;
	#ifndef NO_PI
		digitalWrite(led_n,value);
	#endif
}
 using namespace std;
 
 int previous_led(){
	int pl=act_led;
	switch (act_led){
		case yellow_led:
			act_led=red_led;
			break;
		case red_led:
			act_led=green_led;
			break;
		case green_led:
			act_led=yellow_led;
			break;
	}
	 return pl;
	}
 
 int main (){
	init(blue_led);
	init(red_led);
	init(green_led);
	init(yellow_led);
	int i=0;
	int prev_led=0;
	while(i<20){
		prev_led=previous_led();
		setLed(prev_led,true);
		switch (prev_led){
			case yellow_led:
				delay(timeoutYellowRed);
				
				break;
			case red_led:
				delay(timeoutRedGreen);
				break;
			case green_led:
				delay(timeoutGreenYellow);
				break;
		}
		setLed(prev_led,false);
		cout<<"pv led "<<prev_led<<"nxt led "<<act_led<<endl;
		i+=1;
	}
	setLed(red_led,false);
	setLed(green_led,false);
	setLed(yellow_led,false);
	return 0;
}
 
