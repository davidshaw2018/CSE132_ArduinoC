#include"MorseCodes.h"

const int led = 13;
const int unit = 400;
int dot_delta = unit;
unsigned long next_time = 0;
const int dash_delta = 3*unit;
const int off_delta = unit;
const int letter_delta = 3*unit;
const int space_delta = 4*unit;
String str = "";

// Argument: Any character
// Return Value: Either:
//                  1) If the character is a letter, the upper case equivalent.  
//                  2) If the character is not a letter, the original value.
char toUpper(char c) {
  // TODO
  if (c > 96 && c < 123) {
    return c ^ 32;
  }
  else return c;
}

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}


void convertIncomingCharsToMorseCode() {
  // TODO
  if (Serial.available() > 0) {
    while(Serial.available() > 0) {
      char input = Serial.read();
      String ans = morseEncode(input);  
      str = str + '/' + ans;
    }
    Serial.println(str);
    int i = 0;
    while (i < str.length()) {    // iterate over string length
       
       if (str[i] == '-') {                     /// 4 if statements for 4 possible characters
        if (millis() > next_time) {
          digitalWrite(led,HIGH);
          if (millis() > next_time + dash_delta) {
            digitalWrite(led,LOW);
            next_time += dash_delta+off_delta;
            i += 1;
          }
        }
       }
       
       if (str[i] == '.') {                     /// 4 if statements for 4 possible characters
        if (millis() > next_time) {
          digitalWrite(led,HIGH);
          if (millis() > next_time + dot_delta) {
            digitalWrite(led,LOW);
            next_time += dot_delta + off_delta;
            i += 1;
          }
        }
       }
       
       if (str[i] == '/') {     
        digitalWrite(led,LOW);
          if (millis() > next_time + letter_delta) {
            next_time += letter_delta;
            i += 1;
          }
        }
       }
       
       if (str[i] == ' ') { 
          digitalWrite(led,LOW);
          if (millis() > next_time + space_delta) {
            next_time += space_delta;
            i += 1;
          }
        }
       }
       
    }
            
  

  





void loop() {
  // No Need to Modify this.  Put most of your code in "convertIncomingCharsToMorseCode()"
  convertIncomingCharsToMorseCode();

  
}
