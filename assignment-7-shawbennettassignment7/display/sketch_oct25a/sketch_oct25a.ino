int button_pin = A0;
int last_button_state = 1;
unsigned long debounce_time = 0;
int debounce_delta = 50;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0,INPUT_PULLUP);
}

void loop() {
  int reading = analogRead(button_pin);
  // If the reading is not consistent with the last state,
  // reset the debounce counter
//  if (reading != last_button_state) {
//    debounce_time = millis();
//  }
  // If enough time has elapsed, check button state
//  if (millis() > debounce_time + debounce_delta) {
//    // update button reading if there's a change
//    if (reading != button_state) {
//      button_state = reading;
//      if (button_state == LOW) {  //Set initial time of button press
//        initial_press = millis();
//      }
//      else initial_release = millis();  // Initial time of button release
//    }
//  }
  Serial.println(reading);
  delay(500);
}
