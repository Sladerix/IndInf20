///
/// NOTE On Desktop systems, compile with -D NO_PI flag
//

#include <iostream>

#ifndef NO_PI
#include <wiringPi.h>
#endif

using namespace std;

///
/// Configuration
///
const int led_Blue = 0;
const int timeoutMs = 1000;

///
/// Utils
///
void init()
{
#ifndef NO_PI
    wiringPiSetup();
    pinMode(led_Blue, OUTPUT);
#endif
}

void setLed(int ledNumber, bool value)
{
#ifndef NO_PI
    digitalWrite(ledNumber, value);
#else
    cout << "Setting led " << ledNumber << " to " << (value ? "ON" : "OFF") << endl;
#endif
}

int main()
{
    init();

    // Ok, inited. Now do your work...

    bool onoff = true;

    while(1)
    {
       	// We can now add our custom logics here
	/////

        // If this led blinks, then the loop is working
        setLed(led_Blue, onoff);
        onoff = !onoff;

#ifndef NO_PI
        delay(timeoutMs);
#else
        // TODO Add desktop delay (sleep?)
#endif
    }

    return 0;
}
