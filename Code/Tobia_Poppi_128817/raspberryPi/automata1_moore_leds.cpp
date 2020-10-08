#include <wiringPi.h>
#include <iostream>

using namespace std;

const int blue_led = 0; //GPIO 0
const int red_led = 1; //GPIO 1
const int yellow_led = 2; //GPIO 2
const int green_led = 3; //GPIO 3

const int sfn[][4] = {{2, 1, 3, -1},{-1, 1, 3, -1},{0, -1, -1, -1},{-1, -1, -1, -1}};
const int mfn[4] = {0, 2, 2, 3};

void clearLed(){
  digitalWrite(0, false);
  digitalWrite(1, false);
  digitalWrite(2, false);
  digitalWrite(3, false);
}

void init(){
  wiringPiSetup();
  //INIZIALIZZARE pinMode
  pinMode(blue_led, OUTPUT);
  pinMode(red_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  clearLed();
}


void setLedOn(int ledNumber){
    cout << "Setting led " << ledNumber << " to ON " << endl;
    digitalWrite(ledNumber, true);
    for (int i = 0; i < (int) sizeof(mfn); i++){
      if (ledNumber != i){
        digitalWrite(i, false);
      }
    }
}

int main(){
  init();
  int state = 0;
  char letter;
  while (state < 3){
    setLedOn(mfn[state]);
    cout << "Insert the symbol: " << endl;
    cin >> letter;
    int in = letter - 'a';
    if ((in < 0) || (in > 2)){
    	goto error;
    }
    state = sfn[state][in];
    if (state < 0){
      goto error;
    }
    else if (state == 3){
      char k;
      setLedOn(3);
      cout << "Input is legal :)\nWrite X to exit" << endl;
      cin >> k;
      while (k != 'x'){
        cout << "that's not an option... :/" << endl;
        cin >> k;
      }
      clearLed();
      return 0;
    }
  }
  error:
    char k;
    setLedOn(1);
    cout << "Error!!" << endl;
    cout << "Input not legal!\nWrite X to exit" << endl;
    cin >> k;
    while (k != 'x'){
      cout << "that's not an option... :/" << endl;
      cin >> k;
    }
    clearLed();
    return -1;
}
