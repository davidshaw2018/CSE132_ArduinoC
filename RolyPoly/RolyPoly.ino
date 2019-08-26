#include <Wire.h>
#include <SparkFun_MMA8452Q.h>
MMA8452Q accel;


// Predator and prey win conditions to be checked
// Prey position not displayed correctly 
// 
// Debugging

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


const int rows[] = {row_1,row_2,row_3,row_4,row_5,row_6,row_7};
const int cols[] = {col_1,col_2,col_3,col_4,col_5};

int pred_score = 0;
int prey_score = 0;

int n = 0;

const float accel_tolerance = .1;

unsigned char pred_pos[] = {0x00,0x00,0x00,0x00,0x00};
unsigned char prey_pos[] = {0x00,0x00,0x00,0x00,0x00};
unsigned char score[] = {0x00,0x00,0x00,0x00,0x00};

const int frame_rate = 15;
unsigned long last_round_time = 0;
unsigned long last_break_time = 0;
const int reset_time = 4000;
const long round_time = 15000;
unsigned long prey_time = 0;
const int prey_delta = 300;
unsigned long last_blink_time = 0;

void setup() {
  Serial.begin(9600);
  
  // Give prey random initial position
  randomSeed(analogRead(0));
  reset_position();
  //Initialize accelerometer
  accel.init();
  // Set pins to output, initially rows low, cols high
  for (int i = 0; i < sizeof(rows); ++i) {  
    pinMode(rows[i],OUTPUT);
    digitalWrite(rows[i],LOW);
  }
  for (int i = 0; i < sizeof(cols); ++i) {
    pinMode(cols[i],OUTPUT);
    digitalWrite(cols[i],HIGH);
  }
  Serial.println("Game starting!");
}

void loop() {
  unsigned long timer = millis();
  // Run simulation if t<15s
  bool pred_has_won = collision();
  if (pred_has_won) {
    // Round time counter resets to current time
    // Break time counter begins
    // Update scoreboard, and light the board with score array
    if (n==0) {
      pred_win();
      last_break_time = timer;
      Serial.println("Predator: " + (String)pred_score);
      Serial.println("Prey: " + (String)prey_score);
    }
    light_leds(score);
    // Stop if time exceeds 4 seconds - reset board, round time begins
    if (timer > last_break_time + reset_time) {
        // Reset round timer to 0
        last_round_time = timer;
        last_break_time = timer;
        pred_has_won = false;
        n = 0;
        reset_position();
    }
  }
  else if (timer < last_round_time + round_time) {

    // Checks if data is incoming from java, updates predator position
    pred_movement();
    // Check prey movement every 300 ms
    if (timer > prey_time) {
      prey_movement(); 
      prey_time += prey_delta;
    }
    // Display both prey and predator
    unsigned char hex[5];
    for (int i=0;i<5;++i) {
        hex[i] = prey_pos[i];
    }
    // Make predator blink
    if (timer > last_blink_time) {
      for (int i=0;i<5;++i) {
        hex[i] += pred_pos[i];
      }
      if (timer > last_blink_time + 125) {
        last_blink_time += 250;
      }
    }
    light_leds(hex);
//    else {
//      for (int i=0;i<5;++i) {
//        hex[i] = prey_pos[i];
//      }
//    }
  
    
    
  }
  
  else {
  // Round time has now exceeded 15s; prey has won
    // Update scoreboard and light display
    if (n==0) {
      last_break_time = timer;
      prey_win();
      Serial.println("Predator: " + (String)pred_score);
      Serial.println("Prey: " + (String)prey_score);
    }
    light_leds(score);
    if (timer > last_break_time + reset_time) {
      for (int i=0;i<5;++i) {
        pred_pos[i] = 0x00;
        prey_pos[i] = 0x00;
        score[i] = 0x00;
      }
      reset_position();
      last_round_time = timer;
      last_break_time = timer;
      n = 0;
    }
  }
}


// update scoreboard depending on who won
void pred_win() {
  for (int i=0;i<5;++i) {
    score[i] = 0x00;
  }
  Serial.println("Predator has won");
  n += 1;
  pred_score += 1;
  if (pred_score - prey_score < -2) {
//    prey is winning by more than 2
//    score = {0x02,0x02,0x1a,0x18,0x00};
      score[0] = 0x02;
      score[1] = 0x02;
      score[2] = 0x1a;
      score[3] = 0x18;
      score[4] = 0x00;
  }
  else if (pred_score - prey_score < 0) {
//    score = {0x00,0x02,0x1a,0x18,0x00};
      score[0] = 0x00;
      score[1] = 0x02;
      score[2] = 0x1a;
      score[3] = 0x18;
      score[4] = 0x00;
  }
  else if (pred_score - prey_score == 0) {
//    score = {0x00,0x00,0x1a,0x18,0x00};
      score[0] = 0x00;
      score[1] = 0x00;
      score[2] = 0x1a;
      score[3] = 0x18;
      score[4] = 0x00;
  }
  else if (pred_score - prey_score <= 2) {
//    score = {0x00,0x00,0x1a,0x1a,0x00};
      score[0] = 0x00;
      score[1] = 0x00;
      score[2] = 0x1a;
      score[3] = 0x1a;
      score[4] = 0x00;
  }
  else {
//    score = {0x00,0x00,0x1a,0x1a,0x02};
      score[0] = 0x00;
      score[1] = 0x00;
      score[2] = 0x1a;
      score[3] = 0x1a;
      score[4] = 0x02;
  }
}

void prey_win() {
  for (int i=0;i<5;++i) {
    score[i] = 0x00;
  }
  Serial.println("Prey has won");
  n += 1;
  prey_score += 1;
  if (prey_score - pred_score < -2) {
//    score = {0x00,0x00,0x12,0x02,0x02};
      score[0] = 0x02;
      score[1] = 0x02;
      score[2] = 0x12;
      score[3] = 0x00;
      score[4] = 0x00;
  }
  else if (prey_score - pred_score < 0) {
//    score = {0x00,0x00,0x12,0x02,0x00};
      score[0] = 0x00;
      score[1] = 0x02;
      score[2] = 0x12;
      score[3] = 0x00;
      score[4] = 0x00;
  }
  else if (prey_score - pred_score == 0) {
//    score = {0x00,0x00,0x12,0x00,0x00};
      score[0] = 0x00;
      score[1] = 0x00;
      score[2] = 0x12;
      score[3] = 0x00;
      score[4] = 0x00;
  }
  else if (prey_score - pred_score <= 2) {
//    score = {0x00,0x02,0x12,0x00,0x00};
      score[0] = 0x00;
      score[1] = 0x00;
      score[2] = 0x12;
      score[3] = 0x02;
      score[4] = 0x00;
  }
  else {
//    score = {0x02,0x02,0x12,0x00,0x00};
      score[0] = 0x00;
      score[1] = 0x00;
      score[2] = 0x12;
      score[3] = 0x02;
      score[4] = 0x02;
  }
}

//Check pred movement
void pred_movement() {
   if (Serial.available() > 0) {
     byte incomingByte = Serial.read();
     // If left 
     if (incomingByte == (byte)1) {
        if (pred_pos[0] == 0x00) {
            for (int i=0;i<4;++i) {
              pred_pos[i] = pred_pos[i+1];
            }
            pred_pos[4] = 0x00;
          }
     }
     // If up
     if (incomingByte == (byte)2) {
        boolean uppermost = false;
        for (int i = 0;i<5;++i) {
          if (pred_pos[i] == 0xc0) {
              uppermost = true;
          }
        }
        // if it is not at the uppermost, then shift position right
        if (!uppermost) {
          for (int i=0;i<5;++i) {
            pred_pos[i] = (pred_pos[i]<<1) ;
          }
        }
     }

     // If right
     if (incomingByte == (byte)3) {
       if (pred_pos[4] == 0x00) {
           for (int i=4;i>0;--i) {
              pred_pos[i] = pred_pos[i-1];
           }
           pred_pos[0] = 0x00;
       }
     }

     //If down

     if (incomingByte == (byte)4) {
        boolean lowermost = false;
          for (int i = 0;i<5;++i) {
            if (pred_pos[i] == 0x06) {
              lowermost = true;
            }
          }
          // if it is not, then shift position lower
          if (!lowermost) {
            for (int i=0;i<5;++i) {
              pred_pos[i] = pred_pos[i]>>1;
            }
          }
     }
  }
}
//Check prey movement

void prey_movement() {
  if (accel.available()) {
    accel.read(); 
    bool left = accel.cx < -accel_tolerance;
    bool right = accel.cx > accel_tolerance;
    bool up = accel.cy > accel_tolerance;
    bool down = accel.cy < -accel_tolerance;
//    Serial.println("X vel: " + (String)accel.cx + ", Y vel: " + (String)accel.cy);
//    Move prey left
    if (left) {
//      Serial.println("Left");
      if (prey_pos[0] == 0x00) {
         for (int i=0;i<4;++i) {
           prey_pos[i] = prey_pos[i+1];
         }
         prey_pos[4] = 0x00;
      }
    }
    // Move prey right
    if (right) {
//      Serial.println("Right");
      if (prey_pos[4] == 0x00) {
           for (int i=4;i>0;--i) {
              prey_pos[i] = prey_pos[i-1];
           }
           prey_pos[0] = 0x00;
       }
    }
    // Move prey up
    if (up) {
//      Serial.println("Up");
      bool uppermost = false;
      // Check if it is in upmost row
      for (int i = 0;i<5;++i) {
        if (prey_pos[i] == 0x80) {
           uppermost = true;
        }
      }
      // if it is not at the uppermost, then shift position right
      if (!uppermost) {
        for (int i=0;i<5;++i) {
          prey_pos[i] = (prey_pos[i]<<1) ;
        }
      }
    }
    //
    // Move prey down
    if (down) {
//      Serial.println("Down");
      bool lowermost = false;
      for (int i = 0;i<5;++i) {
        if (prey_pos[i] == 0x02) {
           lowermost = true;
        }
      }
      // if it is not, then shift position lower
      if (!lowermost) {
        for (int i=0;i<5;++i) {
           prey_pos[i] = prey_pos[i]>>1;
        }
      }
    }
    
  }
}

// Reset position to random positions

void reset_position() {
  // Clear positions
  for (int i=0;i<5;++i) {
    prey_pos[i] = 0x00;
    pred_pos[i] = 0x00;
  }
  int rand_prey_row = (int)random(0,7);
  int rand_prey_col = (int)random(0,5);
  prey_pos[rand_prey_col] = (0x80 >> rand_prey_row);
  // Give predator random initial position
  int rand_pred_row = (int)random(0,6);
  int rand_pred_col = (int)random(0,4);
  // Checks if it is the same position as prey;
  // If not, regenerate predator position until they are separated
  if(abs(rand_pred_col-rand_prey_col) <= 1) {
    while (abs(rand_pred_row-rand_prey_row) <= 2) {
      if (rand_pred_row == 5) {
        rand_pred_row = 0;
      }
      else rand_pred_row ++;
    }
  }
  pred_pos[rand_pred_col] = (0xc0 >> rand_pred_row);
  pred_pos[rand_pred_col + 1] = pred_pos[rand_pred_col];
}

// Check collision
bool collision() {
  bool all_zero = true;
  for (int i=0;i<5;++i) {
    // If the prey is located in this column
    if (prey_pos[i] > 0) {
      // If the prey and predator are touching, pred|prey = pred
      unsigned char prey_upper = prey_pos[i] << 1;
      unsigned char prey_lower = prey_pos[i] >> 1;
      if (prey_pos[i] + prey_upper == pred_pos[i] 
            || prey_pos[i] + prey_lower == pred_pos[i]) {
        return true;
      }
      all_zero = false;
    }
  }
  return all_zero;
}

void light_leds(unsigned char hex[5]) {
  String bin[5];
  for (int i =0;i<5;++i) {
    if (1&hex[i]>>7) {
      // If leading digit is 1, fine as is; otherwise, invert it
      // In both cases right shift it 8 bits to ignore truncated 0's
      bin[i] = String(hex[i]<<8,BIN);          // convert hexadecimal value into binary string  
    }
    else {
      bin[i] = String((~hex[i])<<8,BIN);
    }
  }
  
  //Writing LEDs
  for (int i=0;i<5;++i) {
    for (int j = 0; j < 5; ++j) {
        if (i == j) {
          digitalWrite(cols[j],LOW);     // Write High to every column except column i
        }
        else {
          digitalWrite(cols[j],HIGH);
        }
    }
    char rows_to_light[16];  // On a specific column i, new character array with the contents of bin(i) 
                                            // ex. bin(i) = 0111 1110, rows_to_light = {0,1,1,1,1,1,1,0} bin[i].toCharArray(rows_to_light,16);
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
    delay(frame_rate/5);
  }
}
