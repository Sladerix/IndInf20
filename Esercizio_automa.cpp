#include <iostream>
using namespace std;

int main(){
	char ingresso;
	char stato='A', uscita='N';
	
	while(uscita != 'R'){
		cout << "Inserisci un lettera con valore X o Y: \n";
		cin >> ingresso;
		
		switch(stato){
			case 'A': if(ingresso == 'X') stato = 'B';
			break;
			
			case 'B': if(ingresso == 'Y') stato = 'C';
					  else stato = 'A';
					  break;
			
			case 'C': if(ingresso == 'Y') stato = 'A';
					  else stato = 'D':
					  break;
			
			case 'D': if(ingresso == 'Y') stato = 'C';
			          else { 
			          		stato = 'A';
			          		uscita = 'R';
					  } 
					  break;

		}			  
		
	}
}
