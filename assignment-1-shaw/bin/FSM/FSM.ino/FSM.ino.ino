/*
   FSM intro
*/

#include <Arduino.h>
#include <Wire.h>

enum State {
  // random change
  up0,        // 0
  up1,        // 1
  up2,        // 2
  up3,        // 3
  up4,        // 4
  up5,        // 5
  up6,        // 6
  up7,
  down0,      // 0
  down1,      // 1
  down2,      // 2
  down3,      // 3
  down4,      // 4
  down5,      // 5
  down6,      // 6
  down7,      // 7
};

State counterState = up0; //What state are we currently in?

bool bit1;
bool bit2;
bool bit3;



void setup() {
  Serial.begin(9600);
}

void loop() {
  bool reverse = checkReverse();
  if (reverse == 1) {
    counterState = switchDirection(counterState);
  }
  else counterState = nextState(counterState);
  delay(1000);
}


State nextState(State state) {
  switch (state) {
    case up0:               //When state up0 , the FSM must:

      bit1 = 0;        //set the bits to match the Count
      bit2 = 0;
      bit3 = 0;

      pprint(state);


      state = up1;          //Move to the next state
      //The next loop will go to case up1

      break;                       //Break to the end of the switch
    //So the next case won't run

    case up1:               //only if counterState == up1
      bit1 = 1;
      pprint(state);
      state = up2;
      break;

    case up2:
      bit1 = 0;
      bit2 = 1;
      pprint(state);
      state = up3;
      break;

    case up3:
      bit1 = 1;
      pprint(state);
      state = up4;
      break;

    case up4:
      bit1 = 0;
      bit2 = 0;
      bit3 = 1;
      pprint(state);
      state = up5;
      break;

    case up5:
      bit1 = 1;
      pprint(state);
      state = up6;
      break;

    case up6:
      bit1 = 0;
      bit2 = 1;
      pprint(state);
      state = up7;
      break;

    case up7:
      bit1 = 1;
      pprint(state);
      state = up0;
      break;

    case down7:
      bit1 = 1;
      bit2 = 1;
      bit3 = 1;
      pprint(state);
      state = down6;
      break;

    case down6:
      bit1 = 0;
      pprint(state);
      state = down5;
      break;

    case down5:
      bit1 = 1;
      bit2 = 0;
      bit3 = 1;
      pprint(state);
      state = down4;
      break;

    case down4:
      bit1 = 0;
      pprint(state);
      state = down3;
      break;

    case down3:
      bit1 = 1;
      bit2 = 1;
      bit3 = 0;
      pprint(state);
      state = down2;
      break;

    case down2:
      bit1 = 0;
      pprint(state);
      state = down1;
      break;

    case down1:
      bit1 = 1;
      bit2 = 0;
      pprint(state);
      state = down0;
      break;

    case down0:
      bit1 = 0;
      pprint(state);
      state = down7;
      break;
      
  }
  return state;
}

State switchDirection(State state) {
  switch (state) {
    case up0:
      bit1 = 0;
      bit2 = 0;
      bit3 = 0;
      state = down0;
      break;

    case up1:
      bit3 = 1;
      state = down1;
      break;

    case up2:
      bit2 = 1;
      bit3 = 0;
      state = down2;
      break;

    case up3:
      bit3 = 0;
      state = down3;
      break;

    case up4:
      state = down4;
      break;

    case up5:
      state = down5;
      break;

    case up6:
      state = down6;
      break;

    case up7:
      state = down7;
      break;

    case down7:
      state = up7;
      break;
      
    case down6:
      state = up6;
      break;

    case down5:
      state = up5;
      break;

    case down4:
      state = up4;
      break;

    case down3:
      state = up3;
      break;

    case down2:
      state = up2;
      break;

    case down1:
      state = up1;
      break;

    case down0:
      state = up0;
      break;
  }
  Serial.println("--Reverse--");
  return state;
}

bool checkReverse() {
  if (Serial.read() > 0) {
    return 1;
  }
  else return 0;
}


void pprint(State state) {
  if (state < 8) {
    Serial.print(state);
  }
  else {
    Serial.print(state - 8);
  }
  Serial.print("  :  ");
  Serial.print(bit3);
  Serial.print(bit2);
  Serial.println(bit1);
}

