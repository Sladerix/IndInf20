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

/* Sets ledNumber to value [HIGH - LOW] */
void setLed(int ledNumber, bool value) {
#ifndef NO_PI
    digitalWrite(ledNumber, value);
#else
    cout <<"########## Setting led " << ledNumber << " to " << (value ? "ON" : "OFF") << " ##########" << endl;
#endif
}

/* Sets ledNumber to blink 5 times, then on */
void blinkLed(int ledNumber) {
    bool onoff = true;
    int times = 0;
    while(times != 5) {
        setLed(ledNumber, onoff);
        onoff = !onoff;
        #ifndef NO_PI
            delay(1000);
        #else
            sleep(1);
        #endif
        times++;
    }
}

/* Switch all ledNumbers to LOW */
void clearAllLed() {
    setLed(LED_RED, LOW);
    setLed(LED_GREEN, LOW);
    setLed(LED_BLUE, LOW);
    setLed(LED_YELLOW, LOW);
}


/* Gets input char, or '-' if no char left */
char next(string word) {
    static int i = 0;
    if(i == word.length())
        return '-';
    return word[i++];
}

/* Updates output depending on the state:
   - case 0: Initial state, LED_GREEN HIGH ;
   - case 3: Final state, LED_BLUE HIGH;
   - case -1: Final state not reached, LED_RED HIGH;
   - case -2: Input sequence not legal, LED_RED blinks 5 times then HIGH;
*/
void outUpdate(int state) {
    switch(state) {
        case 0:
            clearAllLed();
            setLed(LED_GREEN, HIGH);
            break;
        case 3:
            clearAllLed();
            setLed(LED_BLUE, HIGH);
            break;
        case -1:
            clearAllLed();
            setLed(LED_RED, HIGH);
            break;
        case -2:
            clearAllLed();
            blinkLed(LED_RED);
            break;
        default:
            clearAllLed();
            setLed(LED_YELLOW, HIGH);
    }
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

    init();
    
    int state = 0;
    char in;
    outUpdate(state);

    // Getting sequence word from stdin
    string word;
    cout << "Write down sequence word: ";
    cin >> word;

    while(true) {
        // Getting next char from input stream
        in = next(word);
        cout << "Next input char is: " << in << "\t" << "Current state is: " << state << endl;
        
        // If input stream is finished exit cycle
        if (in == '-') {
            cout << "ERROR!" << endl;
            cout << "Inputs stream finished - Final state not reached " << endl;
            cout << "State reached is " << state << endl;
            state = -1;
            break;
        }

        auto it = st.find(make_pair(state,in));
        // If input sequence is not legal exit cycle
        if (it == st.end()) {
            cout << "ERROR!" << endl;
            cout << "Input " << in << " not legal for state " << state << endl;
            state = -2;
            break;
        }
        
        state = it->second;
        cout << "State updated to: " << state << endl;

        // If final state is reached exit cycle
        if (state == 3) {
            cout << "Input sequence is legal for our Language" << endl;
            break;
        }

        // Get here if state updated with no errors and final state not reached
        outUpdate(state);
    }
    
    // Get here if an error occured or final state is reached
    outUpdate(state);
    cout << "Program ended, closing in 10sec" << endl;
    sleep(10);
    clearAllLed();
    return state;
}