// heartbeat.ino

void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);
}

void loop() {
  delay (900);
  int time = (double)millis()/1000;
  digitalWrite(13,HIGH);
  delay(100);
  digitalWrite(13,LOW);
  Serial.print(time);
  Serial.println(" seconds have elapsed");
}

// random change
// random changes for other team

