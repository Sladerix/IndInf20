#include <iostream>

using namespace std;


//const char inputs[] = {'b', 'c'};
const char inputs[] = {'a', 'a', 'b', 'c'};
int inputs_size = sizeof(inputs) / sizeof(inputs[0]);



char next()
{
	static int i = 0;
	if(i >= inputs_size)
		return 'x';
	return inputs[i++];
}

/*
S0 = 0
S1 = 1
S2 = 2
S3 = 3
*/

int main()
{

	char c;
	int stato = 0;
	
	std::cout << "Stato iniziale:" << stato << endl;
	while(1)
	{
		c = next();
		if (c == 'a' && stato == 0){
			stato = 2;
		} else if (c == 'a' && stato == 2){
			stato = 0;
		} else if (c == 'b' && stato == 0){
			stato = 1;
		} else if (c == 'b' && stato == 1){
			stato = 1;
		} else if (c == 'c' && stato == 0){
			stato = 3;
			cout << "Stato finale: " << stato << endl;
			return 0;
		} else if (c == 'c' && stato == 1){
			stato = 3;
			cout << "Stato finale: " << stato << endl;
			return 0;
		} else {
			cout << "Error " << endl;
			return 1;
		}
		cout << "Stato attuale: " << stato << endl;
	
	}
	cout << "Stato finale: " << stato << endl;
	return 0;
}