

enum State {
  up0,        // 0
  up1,        // 1
  up2,        // 2
  up3,        // 3
  up4,        // 4
  up5,        // 5
  up6,        // 6
  up7,
};

State counterState = up0; //What state are we currently in?

bool bit1;
bool bit2;
bool bit3;



void setup() {

  Serial.begin(9600);
  
}

State nextState(State state) {
  switch (state) {
    case up0:               //When state up0 , the FSM must:

      bit1 = 0;        //set the bits to match the Count
      bit2 = 0;
      bit3 = 0;

      blinkLed(state);


      state = up1;          //Move to the next state
      //The next loop will go to case up1

      break;                       //Break to the end of the switch
    //So the next case won't run

    case up1:               //only if counterState == up1
      bit1 = 1;
      blinkLed(state);
      state = up2;
      break;

    case up2:
      bit1 = 0;
      bit2 = 1;
      blinkLed(state);
      state = up3;
      break;

    case up3:
      bit1 = 1;
      blinkLed(state);
      state = up4;
      break;

    case up4:
      bit1 = 0;
      bit2 = 0;
      bit3 = 1;
      blinkLed(state);
      state = up5;
      break;

    case up5:
      bit1 = 1;
      blinkLed(state);
      state = up6;
      break;

    case up6:
      bit1 = 0;
      bit2 = 1;
      blinkLed(state);
      state = up7;
      break;

    case up7:
      bit1 = 1;
      blinkLed(state);
      state = up0;
      break;

   
  }
  return state;
}

void loop() {
  
  counterState = nextState(counterState);
  Serial.println(counterState);
  delay(1000);
}


void blinkLed(State state) {
  pinMode(3,OUTPUT);
  digitalWrite(3,bit3);
  pinMode(4,OUTPUT);
  digitalWrite(4,bit2);
  pinMode(5,OUTPUT);
  digitalWrite(5,bit1);
 
}


