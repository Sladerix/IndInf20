#include <iostream>
#include <wiringPi.h>

using namespace std;

///
/// Configuration
///
const int led_Blue = 0;
const int mainLoopTimeoutMs = 1000;

///
/// Work with leds
///
void setLed(int n, bool onoff)
{
	cout << "Setting led " << n << " " << (onoff ? "ON" : "OFF") << endl;
	digitalWrite(n, onoff);
}

///
/// Utils
///

void init()
{
	wiringPiSetup();
	pinMode(led_Blue, OUTPUT);	
}

int main()
{
	init();
	
	bool set = false;
	
	while(1)
	{
		setLed(led_Blue, set);
		set = !set;
		
		delay(mainLoopTimeoutMs);
	}
	return 0;
}
