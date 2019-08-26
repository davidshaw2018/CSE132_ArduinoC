#include "assembly.h"

// Include printRegs.h to call printRegs() from C (if needed)
 #include "printRegs.h"

void setup() {
  Serial.begin(9600);
  Serial.println("Starting program...");

  // Run the assembly functions
  byte a = giveMeMax();
//  byte b = giveMeZero();
//  byte c = addFour(255);
  turnOnLight;
  

  // Print the results from the assembly functions
//  Serial.print("a = ");
//  Serial.println(a);
//  Serial.print("b = ");
//  Serial.println(b);
//  Serial.print("c = ");
//  Serial.println(c);

  /* add further code here */

  // Makes sure you returned from all your functions:
  Serial.println("Ended setup!");
}

void loop() { /* unused */ }
