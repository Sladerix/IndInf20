/* Implement an automata that checks if the input sequence is legal
 * State 0 (Initial state):
 *  a -> 2
 *  b -> 1
 *  c -> 3
 * State 1:
 *  a -> Error
 *  b -> 1
 *  c -> 3
 * State 2:
 *  a -> 0
 *  b -> Error
 *  c -> Error
 * State 3 (Final state)
 */

#include <iostream>
#include <utility>
#include <map>

using namespace std;

char next (string word) {
    static int i = 0;
    return word[i++];
}

int main() {

    // Create the map
    map<pair<int, char>, pair<int, int>> legalInput;

    // Fill the map
    legalInput.insert(make_pair(make_pair(0, 'a'), make_pair(2, 4)));
    legalInput.insert(make_pair(make_pair(0, 'b'), make_pair(1, 2)));
    legalInput.insert(make_pair(make_pair(0, 'c'), make_pair(3, 9)));
    legalInput.insert(make_pair(make_pair(1, 'b'), make_pair(1, 1)));
    legalInput.insert(make_pair(make_pair(1, 'c'), make_pair(3, 6)));
    legalInput.insert(make_pair(make_pair(2, 'a'), make_pair(0, 5)));

    string input;
    cout << "Insert the path: ";
    // Saving the input as a variable named 'input'
    getline(cin, input);

    // Setting initial state
    int currState = 0;

    int i = 0;
    char nextIn;
    bool found;
    while (i < (input.length())) {
        nextIn = next(input);
        found = false;
        for (auto & it : legalInput) {
            if ((currState == it.first.first) && nextIn == it.first.second) {
                cout << "Function output is: " << it.second.second << endl;
                currState = it.second.first;
                found = true;
                cout << "State updated to: " << currState << endl;
                cout << endl;
                break;
            }
        }
        if (!found) {
            goto error;
        }
        if (nextIn == 'c') {
            cout << "Automa has reached final state" << endl;
            break;
        }
        i++;
    }

    return 0;

    error:
    cout << nextIn << " is an illegal input" << endl;

    return 1;

}

