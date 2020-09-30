#include <iostream>

using namespace std;

//STATE MACHINE OF MEALY

const int schema[][4] = {{2, 1, 3, -1},{-1, 1, 3, -1},{0, -1, -1, -1},{-1, -1, -1, -1}};

const string schema_out[][4] = {{"ora serve una a", "ora puoi mettere b, c", "fine", "errore"},
																{"errore","ora puoi mettere b, c","fine","errore"},
																{"ora puoi mettere a, b, c","errore","errore","errore"},
																{"errore","errore","errore","errore"}};

int sfn(int statoattuale, int in){
	return schema[statoattuale][in];
	}

void mfn(int statoattuale, int in){
	cout << schema_out[statoattuale][in] << endl;
}

int main(int argc, char **argv)
{
		int stato = 0;
		int i = 0;
		while(true){
			char lettera_attuale = ' ';
			cout << "Inserire il prossimo simbolo in minuscolo:" << endl;
			cin >> lettera_attuale;
			int numero_lettera = (int) lettera_attuale - 'a';
			i++;
			mfn(stato, numero_lettera);
			stato = sfn(stato, numero_lettera);
			if (stato < 0){
				goto error;
				break;
				}
			else if (stato == 3){
				cout << "Input is legal :)" << endl;
				return 0;
				}
		}
		return 0;
		error:
			cout << "Error!!" << endl;
			cout << "Input not legal!" << endl;
			return -1;
}
