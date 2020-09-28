#include <iostream>
#include <string> 
#include <bits/stdc++.h> 
using namespace std; 

//ogni riga corrisponde ad uno stato, ogni elemento che la compone è l'input che lo stato deve ricevere per raggiungere lo stato Sx, dove x è 'indice dell'elemento.
//riga con indice 0 fa riferimento allo stato S0, riga con indice 1 fa riferimento allo stato S1, etc etc..

//ES: seconda riga:
// -l'elemento con indice 0 (ovvero '0') rappresenta l'input che deve ricevere lo stato 1 per passare allo stato 0. In questo caso vale '0' perché
// non esiste nessun input che mi permetta di passare dallo stato 1 allo stato 0
// -l'elemento con indice 1 della stessa riga (ovvvero 'b') rappresenta l'input che deve riceve lo stato 1 per passare allo stato 1 (cioé se stesso).
// -l'elemento con indice 2 (ovvero '0') rappresenta l'input che deve ricevere lo stato 1 per passare allo stato 2. In questo caso vale '0' perché
// non esiste nessun input che mi permetta di passare dallo stato 1 allo stato 2
// -l'elemento con indice 3 (ovvvero 'c') rappresenta l'input che deve riceve lo stato 1 per passare allo stato 3, quindi 'c'.


 						     // S0, S1, S2, S3}
const std::vector< std::vector<char> > statesMatrix={{ '0','b','a','c'},//<---stato 0
						     { '0','b','0','c'},//<---stato 1
						     { 'a','0','0','0'},//<---stato 2
						     { '0','0','0','0'}};//<---stato 3;



int getIndex(vector<char> v, char K) 
{ 
    auto it = find(v.begin(), v.end(), K);
    if (it != v.end()) { 
        int index = distance(v.begin(), it); 
        return index; 
    } 
    else {
        return -1; 
    } 
} 

int main()
{
	static int currentState=0;
	char input;
	cout << "Type 'x' to quit the program\n\n";
	static bool flag=true;
	while(flag){
		cout << "################################\n\nCurrent state: S" << currentState <<"\n";
		cout<< "Input= ";
		cin >> input;
		if(input=='x'){
			cout << "\n\nBye :)\n";
			flag=false;
		}else{
				int new_state=getIndex(statesMatrix[currentState], input);
				if(new_state==-1){
					cout<<"\nThe current state does not support entered input.\n\n";
				}else{
					cout<<"New state= S"<<new_state<<endl<<endl;
					currentState=new_state;
				}
		}
	}
	return 0;
}
