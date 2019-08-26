#include"MorseCodes.h"

const int led = 13;
const int button_pin = A0;
const int morse_unit = 1000;
unsigned long press_time = 0;
unsigned long blink_time = 0;
const int blink_delta = .5*morse_unit;
int button_state = 1;
int last_button_state = 1;
unsigned long debounce_time = 0;
const int debounce_delta = 50;
String morse_char = "";
String decoded = "";
unsigned long initial_press = 0;
unsigned long initial_release = 0;
unsigned long release_time = 0;


void setup() {
  Serial.begin(9600);
  pinMode(button_pin,INPUT_PULLUP);
  pinMode(led,OUTPUT);
}

void convertIncomingMorseCodeToChars() {
  int reading = analogRead(button_pin) > 500;
  // If the reading is not consistent with the last state,
  // reset the debounce counter
  if (reading != last_button_state) {
    debounce_time = millis();
  }
  // If enough time has elapsed, check button state
  if (millis() > debounce_time + debounce_delta) {
    // update button reading if there's a change
    if (reading != button_state) {
      button_state = reading;
      if (button_state == LOW) {  //Set initial time of button press
        initial_press = millis();
      }
      else initial_release = millis();  // Initial time of button release
    }
  }
    // While the button is pressed, count the time it's pressed
    if (button_state == LOW) {
      press_time = millis();
      if (initial_release > 0 || initial_press > 0) {
        
        if (sqrt(pow(initial_release - initial_press,2)) < .666*morse_unit) {
          Serial.println("#Too short of a gap between dot/dash#");
          initial_release = 0;
          initial_press = 0;
        }
      }
    }
    if (button_state == HIGH) { // After button is released, 
      press_time = press_time - initial_press;  //Press_time counts the time difference between the press and the current time
      release_time = millis() - initial_release;  //Same for release_time
      if (0 < press_time && press_time < .666*morse_unit) {
        Serial.println("#Too short for a dot, try again#");
        press_time = 0; //Reset press_time counter and initial_press time to 0s
        initial_press = 0;
      }
      if (.667*morse_unit < press_time && press_time < 1.333*morse_unit) {
        morse_char += ".";
        Serial.println(morse_char);
        press_time = 0;
        initial_press = 0;
      }
      if (1.334*morse_unit < press_time && press_time < 2*morse_unit) {
        Serial.println("#Too long for a dot, too short for a dash, try again#");
        press_time = 0;
        initial_press = 0;
      }
      if (2.001*morse_unit < press_time && press_time < 4*morse_unit) {
        morse_char += "-";
        Serial.println(morse_char);
        press_time = 0;
        initial_press = 0;
      }
      if (press_time > 4.001*morse_unit) {
        Serial.println("#Too long for a dash, try again#");
        press_time = 0;
        initial_press = 0;
      }
      if (morse_char.length() > 6) {  // Checks morse_char length and resets if too large
        Serial.println("#Too long for valid morse code#");
        morse_char = "";
        press_time = 0;
        initial_press = 0;
      }
      
      if (release_time > 3*morse_unit && release_time < 7*morse_unit) {  
        char char_to_add = morseDecode(morse_char); //Decode and then reset morse_char string
        if (char_to_add > 0) {  // If there's a character associated with morse_decode(morse_char), add it to the decoded string
            decoded += char_to_add;
            Serial.println("#Letter: #" + (String)char_to_add);
            morse_char = "";
            initial_release += release_time;  // Reset release counter
          }
        
        else {    //Having trouble, not sure how to differentiate a "space" from a null character
          morse_char += " ";
          if (morseDecode(morse_char) == 0) {
            Serial.println("#Not valid morse code#");
            initial_release += release_time;
            morse_char = "";
            initial_release += release_time;
          }
          
        }
        morse_char = "";
      }
    
      if (release_time > 7.001*morse_unit) {  // Word is over, print out the final word and reset release counter
        Serial.println("Word: " + decoded);
        decoded = "";
        initial_release += release_time;
      }
    }
    
      
   last_button_state = reading;
}

void updateLED() {
  if (millis() > blink_time) {
    digitalWrite(led,HIGH);
    if (millis() > blink_time + blink_delta) {
      digitalWrite(led,LOW);
      blink_time += 2*blink_delta;
    }
  }
}

void loop() {
  // No Need to Modify this.  Put most of your code in "convertIncomingMorseCodeToChars()" and "updateLED()"
  updateLED();
  convertIncomingMorseCodeToChars();
  
  

  // Extra credit: Merge in your convertIncomingCharsToMorseCode() to have a 
  // complete encoder/decoder
}
