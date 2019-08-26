#include "assembly.h"  // Declarations for ASM functions
#include "printRegs.h"     // Print registers for debugging
#include "pprintf.h"       // Include macro to do simple formatted printing (See: https://en.wikipedia.org/wiki/Printf_format_string)


uint16_t sumArrayPointers(uint8_t *a, uint8_t length) {
  // TODO: Write a C-code version of summing an array, using pointers
  uint16_t ans = 0;
  int i = 0;
  while (i  < length) {
    uint8_t x = *a;
    ans += x;
    a++;
    i++;
  }
  return ans;
} 

void testIncrementDecrement() {
  Serial.println("**** Testing increment() and decrement() (Prints \"<- ERROR\" on errors) ****");  

  // Individual test cases
                // 1    3    3    4    5    6    7    8    9    10
  byte ops[] = {1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0};
  byte a = 0;
    
  int numTests = sizeof(ops)/sizeof(byte);

  for(int i=0;i<numTests;i++) {

    if(ops[i] == 1) {
      a++;
      byte b = increment();
      if(a != b) {
          pprintf("Global variable is %u; Should be %u\n <- ERROR in increment", b, a);
          Serial.println();
          return;
      }
    } else {
      a--;
      byte b = decrement();
      if(a != b) {
          pprintf("Global variable is %u; Should be %u\n <- ERROR in decrement", b, a);
          Serial.println();
          return;
      }
    }
  }
}

void testSumArray() {
  Serial.println("**** Testing sumArray() (Prints \"<- ERROR\" on errors) ****");  

  // Individual test cases
                // 1    3    3    4    5    6    7    8    9    10
  uint8_t t1[] =  { 1,   2,   3};
  uint8_t t2[] =  {50, 200, 100};
  uint8_t t3[] =  {10,   2,   7,   4,  19,  80,  72,  54,  96, 100};
  uint8_t t4[] =  { 1};
  uint8_t t5[] =  {};
  uint8_t t6[] =  { 1,   5};

  // Array of all test cases
  uint8_t *a[] =      {  t1, t2, t3, t4, t5, t6};
  // Tests are in uint8_ts already (no need to divide by sizeof(uint8_t))
  uint8_t lengths[] = { sizeof(t1), sizeof(t2), sizeof(t3), sizeof(t4), sizeof(t5), sizeof(t6)};

  uint16_t answers[] = {6, 350, 444, 1, 0, 6};
  
  int numTests = sizeof(lengths)/sizeof(uint8_t);

  for(int i=0;i<numTests;i++) {
    uint8_t *array = a[i];
    uint8_t length = lengths[i];    
    uint16_t algorithm = sumArrayPointers(array, length);
    uint16_t assembly = sumArray(array,length);
    Serial.print("Summing: [");
    for(int j=0;j<length-1;j++) {
      Serial.print(array[j]);
      Serial.print(", ");
    }
    if(length)
      Serial.print(array[length-1]);
    Serial.println("]");
    // Compare the results of assembly language implementation and real answer

    if(algorithm != answers[i]) {
        pprintf("sumArrayPointers(...) is %u; Should be %u\n <- ERROR in C function", algorithm, answers[i]);
    }
    if(assembly != answers[i]) {
      pprintf("sumArray(...) is %u; Should be %u\n <- ERROR in C function  <- ERROR in assembly", assembly, answers[i]);
    }
    Serial.println();
  }
}




void setup() {
  Serial.begin(9600);
  Serial.println("Starting tests...");

  // testIncrementDecrement();
 
  /* Simple Test
  uint8_t array[] = { 1,2,3,4,5};
  uint8_t arrayLength = sizeof(array)/sizeof(uint8_t);
  uint16_t sum = sumArray(array,arrayLength);
  pprintf("sumArray(...) is %u; sumArrayPointers(...) is %u; Should be %u\n", sum, sumArrayPointers(array, arrayLength), 15);
  // */
  // Full Test:
  testSumArray();

  
  Serial.println("Done with tests!!!");
}

void loop() { /* unused */ }
