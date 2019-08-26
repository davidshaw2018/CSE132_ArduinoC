#include "assemblyFunctions.h"
#include "printRegs.h"

// Notes:
//   ADD MORE TEST CASES WHERE THERE'S A "TODO" INDICATOR!!!
//   Many of these test cases use "parallel arrays". 
//      Multiple arrays are used for both input and output.
//      The i-th element of each corresponds to a single test case.
//   The "sizeof()" operator is used to count the number of items in the array.
//   (Here it's used to find the size of the "results" array in bytes and then 
//    to divide by the size of an int.  For example, if an array is 12 bytes and 
//    an int takes 2 bytes, the array has 6 elements in it)


void testHasAOne() {
  Serial.println("**** Testing hasAOne() (only prints errors in tests) ****");  
  if(hasAOne((byte)0) == true) {
      Serial.println("hasAOne() error on: 0");
  }
  // Test for errors with all other values
  for(byte b=1; b!=0; b++) {
    if(hasAOne(b) == false) {
      Serial.print("hasAOne() error on: ");
      Serial.println(b);
    }
  }  
}

void testByteToAscii() {
  // TODO: Add "exhaustive" test cases.
  byte ascii[] = {48,49,50,51,52,53,54,55,56,57};
  byte nums[] = {0,1,2,3,4,5,6,7,8,9};
  // It should show that all inputs (0-9) produce the correct result ('0'-'9')
  Serial.println("**** Testing byteToAscii, only printing errors ****");
  for (int i=0; i<10; ++i) {
    byte input = nums[i];
    if (byteToAscii(nums[i]) != ascii[i]) {
      Serial.println("Error on byteToAscii(" + (String)input + ")");
    }
  }
}

void testInt8ToInt() {
  Serial.println("**** Testing int8ToInt() (only prints errors in tests) ****");  
  for(int expected=-128;expected<128;expected++) {
    int8_t input  = expected;
    int    result = int8ToInt(input);
    if(result != expected) {
      Serial.print("Error. ");
      Serial.print(input);
      Serial.print(" expected ");
      Serial.print(expected);
      Serial.print(" but was ");
      Serial.println(result);
    }
  }  
}

void testAddInt8ToInt() {
  // TODO: Add more test cases!
  
  Serial.println("**** Testing addInt8ToInt() (only prints errors in tests) ****");  
  int8_t int8Values[]  = {0, 1, -1,  1, -1,  -1,  64, -64,  127, -128, -127, -127, 100, -100, 100};
  int    int16Values[] = {0, 1,  1, -1, -1, 256,  64, -64, -127,  128,  128, -127, 300, 1000, -120};
  int    results[]     = {0, 2,  0,  0, -2, 255, 128,-128,    0,    0,    1, -254, 400,  900, -20};
  const int numTests = sizeof(results)/sizeof(int);
  
  for(int i=0;i<numTests;i++) {
    int8_t int8 = int8Values[i];     // Signed 8-bit int
    int    int16 = int16Values[i];   // Signed 16-bit int
    int    expected = results[i];
    int    result = addInt8ToInt(int8, int16);
    if(result != expected) {
      Serial.print("Error. ");
      Serial.print(int8);
      Serial.print(" + "); 
      Serial.print(int16);
      Serial.print(" expected ");
      Serial.print(expected);
      Serial.print(" but was ");
      Serial.println(result);
    }
  }  
}  


void testAdd4Int8() {
  // TODO: Add more test cases!
  Serial.println("**** Testing add4Int8() (only prints errors in tests) ****");  
  int8_t as[]   = {127, -1,  1, -128, 5, -16, 0, 1, 10};
  int8_t bs[]   = {127, -1, -1, -128, 5, -16, 0, 2, 11};
  int8_t cs[]   = {127, -1,  1, -128, 5, -16, 0, 3, 12};
  int8_t ds[]   = {127, -1, -1, -128, 5, -16, 0, 4, 20};
  int results[] = {508, -4,  0, -512, 20,-64, 0,10, 53};  
  const int numTests = sizeof(results)/sizeof(int);
  
  for(int i=0;i<numTests;i++) {
    int8_t a = as[i];
    int8_t b = bs[i];
    int8_t c = cs[i];
    int8_t d = ds[i];
    int    expected = results[i];   // Signed 16-bit int
    
    int result = add4Int8(a,b,c,d);
    if(result != expected) {
      Serial.print("Error. ");
      Serial.print(a);
      Serial.print(" + "); 
      Serial.print(b);
      Serial.print(" + "); 
      Serial.print(c);
      Serial.print(" + "); 
      Serial.print(d);
      Serial.print(" expected ");
      Serial.print(expected);
      Serial.print(" but was ");
      Serial.println(result);
    }
  }
}


void testAverage() {
  // TODO: Add more test cases!
  Serial.println("**** Testing average() (only prints errors in tests) ****");  
  byte  as[]      = {0, 255, 127,  1, 0,   5, 10, 132};
  byte  bs[]      = {0, 255, 128,  0, 1, 100, 18, 124};
  byte  results[] = {0, 255, 127,  0, 0,  52, 14, 128};
  const int numTests = sizeof(results)/sizeof(byte);

  for(int i=0;i<numTests;i++) {
    byte a = as[i];
    byte b = bs[i];
    byte expected = results[i];
    byte result = average(a,b);
    if(result != expected) {
      Serial.print("Error. (");
      Serial.print(a);
      Serial.print(" + "); 
      Serial.print(b);
      Serial.print(")/2 expected ");
      Serial.print(expected);
      Serial.print(" but was ");
      Serial.println(result);
    }
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Starting program...");
  testHasAOne();
  testByteToAscii();
  testInt8ToInt();
  testAddInt8ToInt();
  testAdd4Int8();
  testAverage();
  Serial.println("Testing Done!");
}

void loop() { /* unused */ }
