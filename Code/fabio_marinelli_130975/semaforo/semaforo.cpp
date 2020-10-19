using namespace std;
#include <wiringPi.h>
#include <algorithm>
#include <iostream>

const int err_state =0;
const int red_led = 1; //GPIO 1
const int green_led = 2; //GPIO 2
const int yellow_led = 3; //GPIO 3


//ad ogni "giro" parte un cronometro che si resetta alla fine dello stesso giro
//la tabella contiene il "giro"/secondo a cui si passa dallo stato in riga a quello in colonna
// 0 = non posso passare a quello stato
//dopo 3 volte che diventa rosso va in "errore"
//per poi ricominciare il giro dopo 4 secondi

//										   e- r- g- y
const int semaforoStatesMatrix[][4] =	{{ 0, 4, 0, 0}, //<---stato 0 --> error
										 {-1, 0, 2, 0}, //<---stato 1 --> red
						     			 { 0, 0, 0, 4}, //<---stato 2 --> green
						     			 { 0, 6, 0, 0}};//<---stato 3 --> yellow
				
const int timeout=1000;
static bool errLedState=false;
void resetLed(){
  digitalWrite(red_led, false);
  digitalWrite(green_led, false);
  digitalWrite(yellow_led, false);
}

void init(){
  wiringPiSetup();
  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);
  resetLed();
}

int indexOf(int elem, int currentState){
	int n = sizeof(semaforoStatesMatrix[currentState])/sizeof(semaforoStatesMatrix[currentState][0]);
	auto itr = find(semaforoStatesMatrix[currentState], semaforoStatesMatrix[currentState] + n, elem);
	if (itr != end(semaforoStatesMatrix[currentState])) {
		return distance(semaforoStatesMatrix[currentState], itr);
	}
	else {
		return -1;
	}
}

void switchErrLed(){
	if(errLedState){
		digitalWrite(yellow_led, false);
		errLedState=false;
	}else{
		digitalWrite(yellow_led, true);
		errLedState=true;
	}
}

int main()
{
	init();
	static int currentState=0;
	static int cronometro=0;
	static int errorCounter=0;

	while(true){
		if(errorCounter==3){
			digitalWrite(currentState, false);
			currentState=err_state;
			digitalWrite(currentState, true);
		}
		if (cronometro==0){
			digitalWrite(red_led, true);
			currentState=red_led;
		}else{
			int found=indexOf(cronometro, currentState);
			if(found>0){
				digitalWrite(currentState, false);
				currentState=found;
				digitalWrite(currentState, true);
				if(currentState==red_led){
					cronometro=0;
					if(errorCounter<3){
						errorCounter++;
					}else{
						errorCounter=0;
						errLedState=false;
					}
					digitalWrite(yellow_led, false);
				}
			}
		}
		cronometro++;
		if(currentState==err_state){
			switchErrLed();
		}
		delay(timeout);

	}
	return 0;
}
