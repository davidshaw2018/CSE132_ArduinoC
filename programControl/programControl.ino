#include "assembly.h"
#include "printRegs.h"



// Function to test "lessThan()"  Prints "ERROR" on any tests that failed!
void testLessThan() {
  int8_t x[]       = {4, 6, 4, -4,  4, -4, -3, -4,  127, -128};
  int8_t y[]       = {6, 4, 4,  6, -6, -4, -4, -3, -128,  127};
  bool expected[]  = {1, 0, 0,  1,  0,  0,  0,  1,    0,    1};
  const int numTests = sizeof(x) / sizeof(int8_t);

  Serial.println(" *** lessThan() *** ");
  for(int i=0; i<numTests;i++) {
    int8_t arg1 = x[i];
    int8_t arg2 = y[i];
    bool value = lessThan(arg1, arg2);
    Serial.print(arg1);  
    Serial.print(" < ");  
    Serial.print(arg2);  
    Serial.print(" is ");  
    Serial.print(value);  
    if(value!=expected[i]) {
      Serial.print(" <- ERROR");
    }
    Serial.println();
  }  
}

// TODO: Include test for lessThanOrEqualUnsigned()

void testLessThanOrEqualUnsigned() {
  byte x[]         = {4, 6, 4,   5, 255, 128, 127, 0, 250};
  byte y[]         = {6, 4, 4, 255,   5, 127, 128, 0, 250};
  bool expected[]  = {1, 0, 1,   1,   0,   0,   1, 1,   1};
  const int numTests = sizeof(x) / sizeof(byte);
  
  Serial.println(" *** lessThanOrEqualUnsigned() *** ");
  for(int i=0; i<numTests;i++) {
    byte arg1 = x[i];
    byte arg2 = y[i];
    bool value = lessThanOrEqualUnsigned(arg1, arg2);
    Serial.print(arg1);  
    Serial.print(" <= ");  
    Serial.print(arg2);  
    Serial.print(" is ");  
    Serial.print(value);  
    if(value!=expected[i]) {
      Serial.print(" <- ERROR");
    }
    Serial.println();
  }  
}


// TODO: Include test for slowMultiply()

void testSlowMultiply() {
  byte x[]         = { 4,  6,  4,   1,   6, 200,   1, 0, 0, 1};
  byte y[]         = { 6,  4,  4, 255,  40,   1, 200, 0, 1, 0};
  byte expected[]  = {24, 24, 16, 255, 240, 200, 200, 0, 0, 0};
  const int numTests = sizeof(x) / sizeof(byte);
  
  Serial.println(" *** slowMultiply() *** ");
  for(int i=0; i<numTests;i++) {
    byte arg1 = x[i];
    byte arg2 = y[i];
    byte value = slowMultiply(arg1, arg2);
    Serial.print(arg1);  
    Serial.print(" * ");  
    Serial.print(arg2);  
    Serial.print(" is ");  
    Serial.print(value);  
    if(value!=expected[i]) {
      Serial.print(" <- ERROR");
    }
    Serial.println();
  }  
}

// */


// TODO: Include test for slowExponent()

void testSlowExponent() {
  byte x[]         = { 4,  2,  3,  3,  6,   1,   1, 0,  8,   3,   2};
  byte y[]         = { 2,  4,  2,  3,  2, 210,   0, 1,  2,   5,   7};
  byte expected[]  = {16, 16,  9, 27, 36,   1,   1, 0, 64, 243, 128};
  const int numTests = sizeof(x) / sizeof(byte);
  
  Serial.println(" *** slowExponent() *** ");
  for(int i=0; i<numTests;i++) {
    byte arg1 = x[i];
    byte arg2 = y[i];
    byte value = slowExponent(arg1, arg2);
    Serial.print(arg1);  
    Serial.print(" ^ ");  
    Serial.print(arg2);  
    Serial.print(" is ");  
    Serial.print(value);  
    if(value!=expected[i]) {
      Serial.print(" <- ERROR");
    }
    Serial.println();
  }  
}

// */

void setup() {
  Serial.begin(9600);
  Serial.println("Starting program...");

  // Test the functions
  testLessThan();

  // TODO: Add in tests for remaining functions
  testLessThanOrEqualUnsigned();
  testSlowMultiply();
  testSlowExponent();
  
  // Makes sure you returned from all your functions:
  Serial.println("Ended setup!");
}

void loop() { /* unused */ }
