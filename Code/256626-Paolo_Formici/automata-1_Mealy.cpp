#include <iostream>
#include <string>
#include <map>
using namespace std;

/* Gets input char, or 'x' if no char left */
char next(string word) {
    static int i = 0;
    if(i == word.length())
        return '-';
    return word[i++];
}



int main () {
    // Initializing states table as map<pair<state, input> , pair <nextstate, output>
    map<pair<int, char> , pair <int, int>> st;

    // Building up states table, keeping only legal transitions
    st.insert(make_pair(make_pair(0, 'a'), make_pair(2, 4)));
    st.insert(make_pair(make_pair(0, 'b'), make_pair(1, 2)));
    st.insert(make_pair(make_pair(0, 'c'), make_pair(3, 9)));
    st.insert(make_pair(make_pair(1, 'b'), make_pair(1, 1)));
    st.insert(make_pair(make_pair(1, 'c'), make_pair(3, 6)));
    st.insert(make_pair(make_pair(2, 'a'), make_pair(0, 5)));

    int state = 0;
    int eout = 0;
    int e = 0;
    char in;

    // Getting sequence word from stdin
    string word;
    cout << "Write down sequence word: ";
    cin >> word;

    while(true) {
        // Getting next char from input stream
        char in = next(word);
        cout << "Next input char is: " << in << "\t" << "Current state is: " << state << endl;
        
        // If input stream is finished
        if (in == '-') {
            e = -1;
            goto error;
        }

        auto it = st.find(make_pair(state,in));
        // If input sequence is not legal
        if (it == st.end()) {
            e = -2;
            goto error;
        }
        state = it->second.first;
        eout = it->second.second;
        cout << "State updated to: " << state << "\t" << "Edge crossing output is:" << eout << "\n" << endl;
        
        // If final state is reached exit cycle
        if (state == 3)
            break;
    }
    
    cout << "Input sequence is legal for our Language" << endl;
    return 0;
    
    error:
        switch(e) {
            case -1:
                cout << "ERROR!" << endl;
                cout << "Inputs stream finished - Final state not reached " << endl;
                cout << "State reached is" << state << endl;
                return state;
                break;
            case -2:
                cout << "ERROR!" << endl;
                cout << "Input " << in << " not legal for state " << state << endl;
                return state;
                break;
        }

}