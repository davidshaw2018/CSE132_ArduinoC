//Fill in the values below with the pins that you chose to use

const int POT_PIN = A0;
const int BUTTON_PIN = 3;

const int HOT_PIN = 10;
const int COLD_PIN = 8;
const int DRY_PIN = 12;
const int LOCK_PIN = 13;

enum State {
  off,
  idle,
  economy,
  deluxe,
  superDeluxe,
  
};

State washerState = off;

bool hotWater;
bool coldWater;
bool drying;
bool locked;
bool button;


State nextState(State state) {
  switch (state) {

    case idle: {
      button = digitalRead(3);
      locked = 1;
      output(state);
      State newState = economy;
      if (analogRead(A0) >= 333 && analogRead(A0) < 666) {
        newState = deluxe;
      }
      if (analogRead(A0) >= 666) {
        newState = superDeluxe;
      }
      if (button) {
        state = idle;
        break;
      }
      else {
        state = newState;
        break;
      }
      
    }
    case off: {
      hotWater = 0;
      coldWater = 0;
      drying = 0;
      locked = 0;
      output(state);
      if (digitalRead(BUTTON_PIN)) {
        state = off;
      }
      else state = idle;
      break;
    }

    case economy: {
      locked = 1;
      coldWater = 1;
      output(state);
      delay(5000);
      if (analogRead(A0) >= 333) {
        coldWater = 0; 
        drying = 1;
        output(state);
        delay(7000);
        state = off;
        break;
      }
      else {
        coldWater = 0;
        drying = 1;
        output(state);
        delay(2000);
        state = off;
        break;
      }
    }

    case deluxe: {
      locked = 1;
      hotWater = 1;
      output(state);
      delay(7000);
      if (analogRead(A0) < 333) {
        hotWater = 0;
        drying = 1;
        output(state);
        delay(2000);
        state = off;
        break;
      }
      else {
        hotWater = 0;
        drying = 1;
        output(state);
        delay(7000);
        state = off;
        break;
      }
    }

    case superDeluxe: {
      locked = 1;
      hotWater = 1;
      output(state);
      delay(7000);
      coldWater = 1;
      output(state);
      delay(7000);
      if (analogRead(A0) < 333) {
        hotWater = 0;
        coldWater = 0;
        drying = 1;
        output(state);
        delay(2000);
        state = off;
        break;
      }
      else {
        hotWater = 0; 
        coldWater = 0;
        drying = 1;
        output(state);
        delay(7000);
        state = off;
        break;
        }
      }
    }
    return state;
  }
  


void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(BUTTON_PIN,INPUT_PULLUP);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //output(washerState);
  //nextState(washerState);
  washerState = nextState(washerState);
  Serial.println(washerState);
  delay(1000);
}

void output(State s) {
  pinMode(10, OUTPUT);
  digitalWrite(10, hotWater);
  pinMode(8,OUTPUT);
  digitalWrite(8, coldWater);
  pinMode(12,OUTPUT);
  digitalWrite(12, drying);
  pinMode(13,OUTPUT);
  digitalWrite(13, locked);
 
}
