/* cricket
 *  
 *  CSE 132 - Assignment 3
 *  
 *  Fill this out so we know whose assignment this is.
 *  
 *  Name: David Shaw
 *  WUSTL Key: david.shaw
 *  
 *  and if two are partnered together
 *  
 *  Name: Conner Bennett
 *  WUSTL Key: connerbennett
 */
const long tempDelta = 250;
long nextTempTime = 250;
long nextCricketTime = 0;
const long blinkTime = 200;
const int FILTER_COUNTS = 10;
const int LED_PIN = 3;
const int TMP_PIN = A0;
float temperatures[FILTER_COUNTS];
int count = 10;
float average = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  analogReference(INTERNAL);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  long time = millis();
  if (time >= nextTempTime) {
    float temp = readTemp();   
    for (int i = 0; i < FILTER_COUNTS; ++i) {
      average += temperatures[i];
    }
    average = average/FILTER_COUNTS;
    Serial.println("Raw temperature: " + String(temp) + ", Averaged temperature: " + String(average));
    Serial.println();
    nextTempTime += tempDelta;
  }
  float avForCricket = 60*(7*(average - 10) + 40);
  float cricketDelta = 1000/avForCricket;

  if (time >= nextCricketTime) {
    pinMode(LED_PIN,OUTPUT);
    digitalWrite(LED_PIN,HIGH);
    time = millis();
    if (time >= nextCricketTime + blinkTime) {
      pinMode(LED_PIN,OUTPUT);
      digitalWrite(LED_PIN,LOW);
      nextCricketTime += cricketDelta + blinkTime;
    }
  
  }
}

float readTemp() {
  int tRaw = analogRead(TMP_PIN);
  float voltage = 1.1*((float)(tRaw)/1023);
  float tFinal = 25 + (voltage - .75)*(100);
  temperatures[count % FILTER_COUNTS] = tFinal;
  count += 1;
  return tFinal;
}

