#define NO_PI

#include <iostream>
#include <string>
#include <map>
#include <unistd.h>

#ifndef NO_PI
    #include <wiringPi.h>
#else  /// if not included with wiringPi headers, define them
    #define HIGH 1
    #define LOW 0
#endif

using namespace std;


///
/// Configuration
///
#define LED_RED 0
#define LED_GREEN 1
#define LED_BLUE 2
#define LED_YELLOW 3

///
/// Utils
///
void init() {
    #ifndef NO_PI
	    wiringPiSetup();
        pinMode(LED_RED, OUTPUT);
        pinMode(LED_GREEN, OUTPUT);
        pinMode(LED_BLUE, OUTPUT);
        pinMode(LED_YELLOW, OUTPUT);
    #endif
}   

void setLed(int ledNumber, bool value) {
#ifndef NO_PI
    digitalWrite(ledNumber, value);
#else
    cout <<"########## Setting led " << ledNumber << " to " << (value ? "ON" : "OFF") << " ##########" << endl;
#endif
}

/* Final state not reached error:
   - clear mid-state led indicator
   - set error led indicator
*/
void simpleError() {
    // No need to switch off initial state led because input string lenght supposed to be > 0, else if not legal input at state 0 switch to error -2
    setLed(LED_YELLOW, LOW);
    setLed(LED_RED, HIGH);
}

/* Input sequence not legal error:
   - clear initial-state led indicator
   - clear mid-state led indicator
   - set error led indicator to blinking
*/
void blinkError() {
    setLed(LED_GREEN, LOW);
    setLed(LED_YELLOW, LOW);
    // Setting red LED to blinking
    bool onoff = true;
    while(true) {
        setLed(LED_RED, onoff);
        onoff = !onoff;
        #ifndef NO_PI
            delay(1000);
        #else
            sleep(1);
        #endif
    }
}

/* Gets input char, or 'x' if no char left */
char next(string word) {
    static int i = 0;
    if(i == word.length())
        return 'x';
    return word[i++];
}


int main () {
    // Initializing states table
    map<pair<int, char> , int> st;

    // Building up states table, keeping only legal transitions
    st.insert(make_pair(make_pair(0, 'a'), 2));
    st.insert(make_pair(make_pair(0, 'b'), 1));
    st.insert(make_pair(make_pair(0, 'c'), 3));
    st.insert(make_pair(make_pair(1, 'b'), 1));
    st.insert(make_pair(make_pair(1, 'c'), 3));
    st.insert(make_pair(make_pair(2, 'a'), 0));
    st.insert(make_pair(make_pair(2, 'd'), 3));
    
    int state = 0;
    int e;
    char in;
    bool lap = false;

    init();
    setLed(LED_GREEN, HIGH);

    // Getting sequence word from stdin
    string word;
    cout << "Write down sequence word: ";
    cin >> word;

    while(true) {
        // Getting next char from input stream
        in = next(word);
        cout << "Next input char is: " << in << "\t" << "Current state is: " << state << endl;
        
        // If input stream is finished
        if (in == 'x') {
            e = -1;
            goto error;
        }

        auto it = st.find(make_pair(state,in));
        // If input sequence is not legal
        if (it == st.end()) {
            e = -2;
            goto error;
        }
        state = it->second;
        cout << "State updated to: " << state << endl;
        
        // If final state is reached exit cycle
        if (state == 3)
            break;
        
        // If state is updated (and is not error state or final state) set mid-state led indicator
        if(!lap)
            setLed(LED_YELLOW, HIGH);
            lap = true;
    }
    
    // Final state reached - clear mid-state led indicator, set final-state led indicator
    setLed(LED_YELLOW, LOW);
    setLed(LED_BLUE, HIGH);
    cout << "Input sequence is legal for our Language" << endl;
    return 0;
    
    error:
        switch(e) {
            case -1:
                simpleError();
                cout << "ERROR!" << endl;
                cout << "Inputs stream finished - Final state not reached " << endl;
                cout << "State reached is " << state << endl;
                break;
            case -2:
                blinkError();
                cout << "ERROR!" << endl;
                cout << "Input " << in << " not legal for state " << state << endl;
                break;
        }
}