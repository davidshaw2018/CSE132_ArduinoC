

void setup() {
  Serial.begin(9600);
}

void loop() {
  if(Serial.available() > 0) {
    String x = Serial.readString();
    Serial.print(x);
  }
//  int x = 5; 
//  Serial.write(x);
//  delay(500);
}



