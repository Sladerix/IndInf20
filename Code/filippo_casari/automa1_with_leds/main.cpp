#include <iostream>
#include <string>
#include <sstream>
#include <wiringPi.h>
using namespace std;


const int led_red= 0;// stato 0
const int led_blue = 1;// stato 1

const int led_green = 2;// stato 2
const int led_white = 3;//stato3

void init() //inizializzazione
{
    wiringPiSetup();
    pinMode(led_blue, OUTPUT);
    pinMode(led_red, OUTPUT);
    pinMode(led_white, OUTPUT);
    pinMode(led_green, OUTPUT);

}


void creaMatrice(const char *matricestati, const char *matricelettere, char matricetot[][3],
                 int dimensione, int size2);

void printMatrix(char matricetot[][3], int dimensione);

int findfun(char matricetot[][3], int statocorrente, char lettera, int dimensione, bool *flag);

int main() {

    init();
    char matricestati[4] = {'0', '1', '2', '3'};
    char matricelettere[3] = {'a', 'b', 'c'};
    int size1 = sizeof(matricestati);
    int size2 = sizeof(matricelettere);
    int dimensione = (size1 * size2);
    int statocorrente = 0;
    char matricetot[dimensione][3]; //matrice totale: matrice contenenti tutte le permutazioni
    digitalWrite(statocorrente, true); //inizializzo tutto allo stato 0
    creaMatrice(matricestati, matricelettere, matricetot, dimensione, size2);//creo matrice
    char lettera; 
    printMatrix(matricetot, dimensione);
    do { //ciclo infinito
        bool flag = false; 
        cout << "inserisci lettera (q per uscire dal programma): ";
        cin >> lettera;
        if (lettera == 'q') {
            cout << "uscita dal programma!" << endl;
            break;
        }
        int statoprec= statocorrente; //statoprec è un temp
        statocorrente = findfun(matricetot, statocorrente, lettera, dimensione, &flag); //trovo la coppia (statoattuale, input) nella tabella totale
        digitalWrite(statocorrente, true); //aggiorno il led e lo stato
        if(statocorrente!=statoprec){
            digitalWrite(statoprec, false); //se ci sono state modiche spengo il led precedente
        }


        cout << "stato corrente=" << statocorrente << endl;
        if (flag) {
            cout << "trovato" << endl;
            if (lettera == 'c') { //esco dal ciclo se l'utente usa la q
                delay(2000); //delay per mostrare l'ultimo led che si accende prima che finisca il programma
                digitalWrite(statocorrente, false); //spengo il led
                break;
            }
        } else {
            cout << "Errore, nessuna corrispondenza (statocorrente, input), riprova o esci" << endl; //nessuna corrispondenza tra la coppia e la matrice di permutazione, vado avanti

        }

        } while (true);

}


void creaMatrice(const char *matricestati, const char *matricelettere, char matricetot[][3], int dimensione,
                 int size2) {


    int indicestato = -1;
    int indicelettera = -1;
    //creazione matrice di permutazione
    for (int i = 0; i < dimensione; i++) {


        if (i % size2 == 0) {
            indicestato++;
        }
        matricetot[i][0] = matricestati[indicestato];

        indicelettera++;
        if ((indicelettera) % (size2) == 0) {
            indicelettera = 0;
        }
        matricetot[i][1] = matricelettere[indicelettera];
        matricetot[i][2] = 'N'; //nessuna azione

    }
    //decido come è fatta la terza colonna in base alla macchina a stati finiti
    matricetot[0][2] = '2';
    matricetot[1][2] = '1';
    matricetot[2][2] = '3';
    matricetot[4][2] = '1';
    matricetot[5][2] = '3';
    matricetot[6][2] = '0';

}

int findfun(char matricetot[][3], int statocorrente, char lettera, int dimensione, bool *flag) {

    for (int i = 0; i < dimensione; i++) {
        stringstream str;
        str << matricetot[i][0];
        int x;
        str >> x;
        if (statocorrente == x and lettera == matricetot[i][1] and matricetot[i][2] != 'N') {
            statocorrente = (int(matricetot[i][2]));
            statocorrente = statocorrente - 48; // oppure -'a'
            *flag = true; //puntatore si aggiorna
            if (statocorrente == 3) {
                cout << "FINE PROGRAMMA" << endl;
            }
            break;

        }
    }
    return statocorrente; //ritorno lo stato corrente, se è stato modificato, viene modificato anche nel main


}
//stampo la matrice 
void printMatrix(char matricetot[][3], int dimensione) {
    for (int i = 0; i < dimensione; i++) {
        for (int j = 0; j < 3; j++) {
            cout << matricetot[i][j] << " ";
        }
        cout << endl;
    }
}

