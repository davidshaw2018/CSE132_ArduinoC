#include "assignment11.h"  // Declarations for ASM functions
#include "printRegs.h"     // Print registers for debugging
#include "pprintf.h"       // Include macro to do simple formatted printing (See: https://en.wikipedia.org/wiki/Printf_format_string)


uint16_t slowDivisionAlgorithm8(uint8_t dividend, uint8_t divisor) {
  // TODO: Write a C-code version of division (don't use divide; use a loop with repeated subtraction!)  
  uint16_t ans = 0;
//  uint8_t total = dividend;
  while (dividend >= divisor) {
    dividend -= divisor;
    ans++;
  }
  return ans;
}


uint16_t slowDivisionAlgorithm16(uint16_t dividend, uint16_t divisor) {
  // TODO: Write a C-code version of division (don't use divide; use a loop with repeated subtraction!) 
  uint16_t ans = 0;
  uint16_t total = dividend;
  while (total >= divisor) {
    total -= divisor;
    ans++;
  }
  return ans; 
}

uint16_t slowModulusAlgorithm(uint8_t dividend, uint8_t divisor) {
  //TODO: Write a C-code version of modulus that uses your division function
   uint16_t quotient = slowDivisionAlgorithm8(dividend,divisor);
   uint16_t ans = dividend - quotient * divisor;
  return ans;
}

uint16_t sumOdds(uint8_t min, uint8_t max) {
  //TODO: Write a C-code function that will sum all of the odd values between min and max (inclusive)
  if (slowModulusAlgorithm(min,2) == 0) {
    min += 1;
  }
  if (slowModulusAlgorithm(max,2) == 0) {
    max -= 1;
  }
  uint16_t sum = 0;
  for (int i=min; i<= max; i += 2) {
    sum += i;
  }
  return sum;
}

// ******  Test cases:  Feel free to add to tests (but don't remove any) ******
void testSlowDivisionUint8() {
    Serial.println("**** Testing divisionUint8() (Prints \"<- ERROR\" on errors) ****");  

  uint8_t dividends[]  = {4, 2, 100,   5,  7, 200, 255, 9, 16, 255, 128, 128};
  uint8_t divisors[]   = {2, 4,   5, 100, 10,   2,   5, 2,  3,   9,   2,   3};
  const int numTests = sizeof(dividends)/sizeof(uint8_t);

  for(int i=0;i<numTests;i++) {
    uint8_t dividend = dividends[i];
    uint8_t divisor = divisors[i];
    uint8_t algorithm = slowDivisionAlgorithm8(dividend, divisor);
    uint8_t assembly = slowDivisionUint8(dividend, divisor);
    uint8_t expected = dividend/divisor;
    pprintf("slowDivisionAlgorithm8(%u,%u) is %u (algorithm) and %u (assembly); Should be %u", dividend, divisor, algorithm, assembly, expected);
    // Compare the results of the algorithm and real answer
    if(algorithm != expected) {
      Serial.print(" <- ERROR in Algorithm!");
    }
    // Compare the results of assembly language implementation and real answer
    if(assembly != expected) {
      Serial.print(" <- ERROR in Assembly!");
    }
    Serial.println();
  }  
}

void testGreaterThanOrEqualUInt16() {
  Serial.println("**** Testing greaterThanOrEqualUInt16() (Prints \"<- ERROR\" on errors) ****");  

  uint16_t as[] =   {4, 2, 4096, 4097, 4096, 4096, 4352, 100,   5,  7, 1000, 3, 9, 16, 0, 21001, 21000, 32000, 4, 2, 100,   5,  7, 1000, 3, 9, 16, 65525};
  uint16_t bs[]   = {2, 4, 4097, 4096, 4096, 4352, 4096,   5, 100, 10,    1, 2, 2,  3, 0, 21000, 21001, 32000, 2, 4,   5, 100, 10,    1, 2, 2,  3, 65535};
  const int numTests = sizeof(as)/sizeof(uint16_t);

  for(int i=0;i<numTests;i++) {
    uint16_t a = as[i];
    uint16_t b = bs[i];
    bool result = greaterThanOrEqualUInt16(a,b);
    bool expected = a>=b;
    pprintf("greaterThanOrEqualUInt16(%u,%u) is %u; Should be %u", a, b, result, expected);
    if(result != expected) {
      Serial.print(" <- ERROR");
    }
    Serial.println();
  }
}


void testSlowDivisonUint16() {
    Serial.println("**** Testing divisonUint16() (Prints \"<- ERROR\" on errors) ****");  

  uint16_t dividends[]  = {4, 2, 100,   5,  7, 1000, 3, 9, 16, 65535, 65535, 65525, 65535, 64000};
  uint16_t divisors[]   = {2, 4,   5, 100, 10,    1, 2, 2,  3,     1,   800, 65535, 65535, 16000};
  const int numTests = sizeof(dividends)/sizeof(uint16_t);

  for(int i=0;i<numTests;i++) {
    uint16_t dividend = dividends[i];
    uint16_t divisor = divisors[i];
    uint16_t algorithm = slowDivisionAlgorithm16(dividend, divisor);
    uint16_t assembly = slowDivisionUint16(dividend, divisor);
    uint16_t expected = dividend/divisor;
    pprintf("slowDivisionAlgorithm16(%u,%u) is %u (algorithm) and %u (assembly); Should be %u", dividend, divisor, algorithm, assembly, expected);
    // Compare the results of the algorithm and real answer
    if(algorithm != expected) {
      Serial.print(" <- ERROR in Algorithm!");
    }
    // Compare the results of assembly language implementation and real answer
    if(assembly != expected) {
      Serial.print(" <- ERROR in Assembly");
    }
    Serial.println();
  }
}

void testSlowModulusUint8() {
    Serial.println("**** Testing modulusUint8() (Prints \"<- ERROR\" on errors) ****");  

  uint8_t dividends[]  = {4, 2, 100,   5,  7, 200, 255, 9, 16, 255, 128, 128};
  uint8_t divisors[]   = {2, 4,   5, 100, 10,   2,   5, 2,  3,   9,   2,   3};
  const int numTests = sizeof(dividends)/sizeof(uint8_t);

  for(int i=0;i<numTests;i++) {
    uint8_t dividend = dividends[i];
    uint8_t divisor = divisors[i];
    uint8_t algorithm = slowModulusAlgorithm(dividend, divisor);
    uint8_t assembly = slowModulusUint8(dividend, divisor);
    uint8_t expected = dividend%divisor;
    pprintf("slowModulusAlgorithm(%u,%u) is %u (algorithm) and %u (assembly); Should be %u", dividend, divisor, algorithm, assembly, expected);
    // Compare the results of the algorithm and real answer
    if(algorithm != expected) {
      Serial.print(" <- ERROR in Algorithm!");
    }
    // Compare the results of assembly language implementation and real answer
    if(assembly != expected) {
      Serial.print(" <- ERROR in Assembly!");
    }
    Serial.println();
  }  
}

void testSumOddsUint8() {
    Serial.println("**** Testing modulusUint8() (Prints \"<- ERROR\" on errors) ****");  

  uint8_t arg1s[]  = {2, 2, 5,  7, 2, 3, 254, 100};
  uint8_t arg2s[]   = {7, 4, 100, 10, 9,  16, 255, 128};
  uint16_t results[]   = {15, 3, 2496, 16, 24, 63, 255, 1596};
  const int numTests = sizeof(arg1s)/sizeof(uint8_t);

  for(int i=0;i<numTests;i++) {
    uint8_t arg1 = arg1s[i];
    uint8_t arg2 = arg2s[i];
    uint8_t algorithm = sumOdds(arg1, arg2);
    uint8_t assembly = sumOddsUint8(arg1, arg2);
    uint8_t expected = results[i];
    pprintf("sumOdds(%u,%u) is %u (algorithm) and %u (assembly); Should be %u", arg1, arg2, algorithm, assembly, expected);
    // Compare the results of the algorithm and real answer
    if(algorithm != expected) {
      Serial.print(" <- ERROR in Algorithm!");
    }
    // Compare the results of assembly language implementation and real answer
    if(assembly != expected) {
      Serial.print(" <- ERROR in Assembly!");
    }
    Serial.println();
  }  
}

void setup() {
  Serial.begin(9600);
  Serial.println("Starting tests...");

  // Note: To uncomment a single "Simple Test", just change the "/*" to a "//*"

  /* Simple Test
  uint8_t dividend8 = 175;
  uint8_t divisor8 = 26;
  uint8_t quotient8ASM = slowDivisionUint8(dividend8,divisor8);
  uint8_t quotient8Alg = slowDivisionAlgorithm8(dividend8,divisor8);
  pprintf("slowDivisionAlgorithm8(%u,%u) is %u (algorithm) and %u (assembly); Should be %u\n", dividend8, divisor8, quotient8Alg, quotient8ASM, dividend8/divisor8);
  // */ 
  // Full Test:
   testSlowDivisionUint8();

  /* Simple Test
  uint16_t a = 1234;
  uint16_t b =  456;  
  pprintf("greaterThanOrEqualUInt16(%u,%u) is %u; Should be %u\n", a, b, greaterThanOrEqualUInt16(a,b), a>=b);
  // */
  // Full Test:
   testGreaterThanOrEqualUInt16();

  /* Simple Test
  uint16_t dividend16 = 12356;
  uint16_t divisor16 = 123;
  uint16_t quotient16Alg = slowDivisionAlgorithm16(dividend16,divisor16);
  uint16_t quotient16ASM = slowDivisionUint16(dividend16,divisor16);
  pprintf("slowDivisionUint16(%u,%u) is %u (algorithm) and %u (assembly); Should be %u\n", dividend16, divisor16, quotient16Alg, quotient16ASM, dividend16/divisor16);
  // */
  // Full Test:
   testSlowDivisonUint16();
  
  /* Simple Test
  uint8_t dividend8 = 5;
  uint8_t divisor8 = 100;
  uint8_t mod8Alg = slowModulusUint8(dividend8,divisor8);
  uint8_t mod8ASM = slowModulusAlgorithm(dividend8,divisor8);
  pprintf("slowModulusAlgorithm(%u,%u) is %u (algorithm) and %u (assembly); Should be %u\n", dividend8, divisor8, mod8Alg, mod8ASM, dividend8%divisor8);
  // */ 
  // Full Test:
   testSlowModulusUint8();

  /* Simple Test
  uint8_t arg1 = 2;
  uint8_t arg2 = 7;
  uint8_t oddsAlg = sumOdds(arg1,arg2);
  uint8_t oddsASM = sumOddsUint8(arg1,arg2);
  pprintf("slowModulusAlgorithm(%u,%u) is %u (algorithm) and %u (assembly); Should be %u\n", arg1, arg2, oddsAlg, oddsASM, 15);
  // */ 
  // Full Test:
  testSumOddsUint8();

  Serial.println("Done with tests!!!");
}

void loop() { /* unused */ }
