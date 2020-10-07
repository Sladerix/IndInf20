#include <iostream>

using namespace std;

//STATE MACHINE OF MOORE
//Input Symbols:             'a' 'b'  'c'  'x'
const int table[][4] = {
                            { 2,  1,   3,  -1}, //  State 0
                            {-1,  1,   3,  -1}, //  State 1
                            { 0, -1,  -1,  -1}, //  State 2
                            {-1, -1,  -1,  -1}  //  State 3
                        };

const string outmfn[] = {"You are in state: 0", "You are in state: 1", "You are in state: 2", "You are in state: 3"};


int sfn(int currentState, int in)
{

	return table[currentState][in];

}

void mfn(int currentState)
{

    cout << outmfn[currentState] << endl;

}

int main(int argc, char **argv)
{

		int state = 0;

		while(true)
		{

			char letter = ' ';
			cout << "Insert a symbol: ";
			cin >> letter;
			int numLetter = (int) letter - 'a';
			state = sfn(state, numLetter);

			if (state < 0)
			{
				goto error;
				break;
            }
			else if (state == 3)
			{
                mfn(state);
				cout << "Input is legal :)" << endl;
				return 0;
            } else {
                mfn(state);
            }
		}

		error:
			cout << "Error!!" << endl;
			cout << "Input not legal!" << endl;
			return -1;

        return 0;
}
