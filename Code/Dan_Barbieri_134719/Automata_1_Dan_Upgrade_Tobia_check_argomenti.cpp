#include <iostream>

using namespace std;

//STATE MACHINE. THE PROGRAM WANTS AS AN INPUT IN THE ARGUMENT THE LETTERS LOWERCASE
//WITH SPACES BETWEEN THEM

const int schema[][4] = {{2, 1, 3, -1},
						{-1, 1, 3, -1},
						{0, -1, -1, -1},
						{-1, -1, -1, -1}};

int controllo_successivo(int statoattuale, int in){
	return schema[statoattuale][in];
	}

int main(int argc, char **argv){
	if (argc > 1){
		int stato = 0;
		int i = 0;
		int argcletto = argc -1;
		for ( int c = 0 ; c < argcletto ; c++ ){//replaced while with "loop for" depending on the number of arguments passed
			int argcurr = (int) argv[i+1][0]; 
			int numero_lettera = argcurr - 'a';
			i++;
			stato = controllo_successivo(stato, numero_lettera);
			if (stato < 0){
				goto error;
				}
			else if (stato == 3){
				cout << "Input is legal :)" << endl;
				return 0;
				}
		}
		cout << " gli argomenti dati sono compatibili ma non abbastanza per arrivare in stato 3" << endl;// new alert
		goto error;
	}
	else{
		cout << "non ci sono argomenti " << endl;
		return -1;
	}
	error:
		cout << "Errore!!" << endl;
		cout << "Input non compatibile" << endl;
		return -1;
}
