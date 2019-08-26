
enum State {
  trafficFlow,
  trafficStop,
  pedGo,
  pedStop,
};

void setup() {
  Serial.begin(9600);
 
}

unsigned long time = 0;
const unsigned long delta = 3041;
unsigned long nextStep = 0;
const unsigned long greenTime = 9000;
const unsigned long yellowTime = 3000;
const unsigned long redTime = 9000;
const unsigned long pedGoTime = 5000;
const unsigned long pedStopTime = 4000;
State trafficState = trafficFlow;
bool redLight;
bool yellowLight;
bool greenLight;
bool walk;
bool dontWalk;

State nextState (State s) {

  switch(s) {
    
    case trafficFlow: {
      redLight = 0;
      yellowLight = 0;
      greenLight = 1;
      walk = 0;
      dontWalk = 0;
      time = millis();
      if (time > nextStep) {
        dontWalk = !dontWalk;
        nextStep += delta;
      }
      if (time > greenTime) {
        s = trafficStop;
      }
      else s = trafficFlow;
      break;
    }

    case trafficStop: {
      redLight = 0;
      yellowLight = 1;
      greenLight = 0;
      walk = 0;
      dontWalk = 0;
      time = millis();
      if (time > nextStep) {
        dontWalk = !dontWalk;
        nextStep += delta;
      }
     
      if (time > yellowTime) {
        s = pedGo;
      }
      else s = trafficStop;
      break;
    }

    case pedGo: {
      redLight = 1;
      yellowLight = 0;
      greenLight = 0;
      walk = 1;
      dontWalk = 0;
      time = millis();
      if (time > pedGoTime) {
        s = pedStop;
      }
      else s = pedGo;
      break;
    }

    case pedStop: {
      redLight = 1;
      yellowLight = 0;
      greenLight = 0;
      walk = 0;
      dontWalk = 0;
      time = millis();
      if (time > nextStep) {
        dontWalk = !dontWalk;
        nextStep += delta;
      }
     
      if (time > pedStopTime) {
        s = trafficFlow;
      }
      else s = pedStopTime;
      break;
  }
  return s;
}
}



void loop() {
  nextState(trafficState);
  output(trafficState);
}

void output(State s) {
      pinMode(3,OUTPUT);
      digitalWrite(3,dontWalk);
      pinMode(5,OUTPUT);
      digitalWrite(5,walk);
      pinMode(7,OUTPUT);
      digitalWrite(7,redLight);
      pinMode(9,OUTPUT);
      digitalWrite(9,yellowLight);
      pinMode(11,OUTPUT);
      digitalWrite(11,greenLight);
}



