/* display
 *  
 *  CSE 132 - Assignment 7
 *  
 *  Fill this out so we know whose assignment this is.
 *  
 *  Name: David Shaw  
 *  WUSTL Key: david.shaw
 *  
 *  Name: Conner Bennett
 *  WUSTL Key: connerbennett
 *  
 */

#include "font.h"
const int row_1 = 10;
const int row_2 = 9;
const int row_3 = 11;
const int row_4 = 5;
const int row_5 = 4;
const int row_6 = 3;
const int row_7 = 2;
const int col_1 = 12;
const int col_2 = 13;
const int col_3 = 8;
const int col_4 = 6;
const int col_5 = 7;
const int up_button = A0;
const int down_button = A1; 
const int rows[] = {row_1,row_2,row_3,row_4,row_5,row_6,row_7};
const int cols[] = {col_1,col_2,col_3,col_4,col_5};
const int frame_rate = 15;
int font_index = 33;
unsigned long debounce_time = 0;
const int debounce_delta = 50;
int up_button_state = 1;
int up_last_button_state = 1;
int down_button_state = 1;
int down_last_button_state = 1;


void setup() {
  Serial.begin(9600);
  for (int i = 0; i < sizeof(rows); ++i) {  //Initialize rows as Low, Cols as High
    pinMode(rows[i],OUTPUT);
    digitalWrite(rows[i],LOW);
  }
  for (int i = 0; i < sizeof(cols); ++i) {
    pinMode(cols[i],OUTPUT);
    digitalWrite(cols[i],HIGH);
  }
  pinMode(up_button,INPUT_PULLUP);
  pinMode(down_button,INPUT_PULLUP);
}

void loop ()
{
  change_letter();
  unsigned char hex[5];                    
  String bin[5];                          // Convert the array of hex values into strings
  for (int i = 0; i < 5; ++i) {
    hex[i] = font_5x7[font_index][i];     // For now = 33, more generally read the font index
    if (1&hex[i]>>7) {
      // If leading digit is 1, fine as is; otherwise, invert it
      // In both cases right shift it 8 bits to ignore truncated 0's
      bin[i] = String(hex[i]<<8,BIN);          // convert hexadecimal value into binary string  
    }
    else {
       bin[i] = String((~hex[i])<<8,BIN);
    }
    
    for (int j = 0; j < 5; ++j) {
        if (i == j) {
          digitalWrite(cols[j],LOW);     // Write High to every column except column i
        }
        else {
          digitalWrite(cols[j],HIGH);
        }
    }
    
    
    
    char rows_to_light[16];  // On a specific column i, new character array with the contents of bin(i) 
                                            // ex. bin(i) = 0111 1110, rows_to_light = {0,1,1,1,1,1,1,0}
         
    bin[i].toCharArray(rows_to_light,16);
    for (int k = 0; k < 7; ++k) {
      //Iterate over rows and write LOW to rows_to_light[k] = 0, HIGH otherwise
      
      if (1&hex[i]>>7) {
        digitalWrite(rows[k],(1 & rows_to_light[k]));
        
      }
      else {
        digitalWrite(rows[k],!(1 & rows_to_light[k]));
      }
    }
    
    delay(frame_rate/5);                      // Wait 1/5 the framerate, in this case 6 ms
  }
}

void change_letter() {
  int up_reading = analogRead(up_button) > 500;
  int down_reading = analogRead(down_button) > 500;
  // If the reading is not consistent with the last state,
  // reset the debounce counter
  if (up_reading != up_last_button_state) {
    debounce_time = millis();
  }
  if (down_reading != down_last_button_state) {
    debounce_time = millis();
  }
  // If enough time has elapsed, check button state
  if (millis() > debounce_time + debounce_delta) {
    // update button reading if there's a change
    if (up_reading != up_button_state) {
      up_button_state = up_reading;
      if (up_button_state == LOW) { 
        if (font_index == 95) {
          font_index = 0;
        }
        else font_index += 1;
      }
    }
    if (down_reading != down_button_state) {
      down_button_state = down_reading;
      if (down_button_state == LOW) {  
        if (font_index == 0) {
          font_index = 95;
        }
        else font_index -= 1;
      }
    }
  }
  up_last_button_state = up_reading;
  down_last_button_state = down_reading;
}




