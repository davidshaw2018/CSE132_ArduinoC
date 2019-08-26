#include "assignment12.h"  // Declarations for ASM functions
#include "printRegs.h"     // Print registers for debugging
#include "pprintf.h"       // Include macro to do simple formatted printing (See: https://en.wikipedia.org/wiki/Printf_format_string)


uint8_t cStringLengthAlgorithm(const char aString[]) {
   // TODO: Write a C-code version of the algorithm to find the string's length 
   uint8_t ans = 0;
   while (true) {
      const char x = *aString;
      if (x == 0) {
        break;
      }
      ans++;
      aString++;
   }
   return ans;
}

void cSumArrays(uint8_t *a, uint8_t *b, uint8_t *c, byte length) {
  // TODO: Write a C-code version of the algorithm to sum arrays a and b, storing the result in c using pointers (no [] allowed!)
  byte i = 0;
  while (i < length) {
    uint8_t x = *a;
    uint8_t y = *b;
    *c = x + y;
    a++;
    b++;
    c++;
    i++;
  }
}

uint16_t cDot(uint8_t *a, uint8_t *b, byte length) {
  // TODO: Write a C-code version that returns the dot product of a and b, using pointers (no [] allowed!)
  byte i = 0;
  uint16_t ans = 0;
  while (i < length) {
    uint8_t x = *a;
    uint8_t y = *b;
    ans += x*y;
    a++;
    b++;
    i++;
  }
  return ans;
}

void testGlobals() {
  Serial.println("**** Testing increment() and decrement() (Prints \"<- ERROR\" on errors) ****");  

  // Individual test cases
  uint8_t ops[] = {6, 2, 7, 9, 8, 4, 2, 2, 2};
  uint8_t a = 0;
    
  int numTests = sizeof(ops)/sizeof(uint8_t);

  for(int i=0;i<numTests;i++) {
    a += ops[i];
    updateGlobal(ops[i]);
    uint8_t b = getGlobal();
    if(a != b) {
      pprintf("Global variable is %u; Should be %u\n <- ERROR in update/get global", b, a);
      Serial.println();
      return;
    } 
  }
}

void testCStringLength() {
    Serial.println("**** Testing cStringLength() (Prints \"<- ERROR\" on errors) ****");  

  // An Array of c-style strings to test
  char *strings[] = { 
    (char*)"1234567890",
    (char*)"Hello, world!",
    (char*)"Test case",
    (char*)"",
    (char*)"1",
    (char*)"\t\n",       // Include "escaped characters"
    (char*)"Oh N\0es",   // Include a null terminator IN the string!
    (char*)"last"
    };
  const uint16_t numTests = sizeof(strings)/sizeof(char*);

  for(uint16_t i=0;i<numTests;i++) {
    char *string = strings[i];
    uint8_t assembly = cStringLength(string);
    uint8_t algorithm = cStringLengthAlgorithm(string);
    uint8_t expected = strlen(string);
    pprintf("cStringLength(\"%s\") is %u (algorithm) and %u (assembly) ; Should be %u", string, algorithm, assembly, expected);
    // Compare the results of cStringLength() to the C libraries strlen()
    if(algorithm != expected) {
      Serial.print(" <- ERROR in Algorithm!");
    }
    if(assembly != expected) {
      Serial.print(" <- ERROR in Assembly!");
    }
    Serial.println();
  }
}

void testSumArrays() {
  Serial.println("**** Testing sumArrays() ****");  

  // Individual test cases
  uint8_t t1[] =  { 1,   2,   3};
  uint8_t t2[] =  {50, 200, 100};
  uint8_t t3[] =  {10,   2};
  uint8_t t4[] =  { 100, 7};
  uint8_t t5[] =  { 3, 2, 1};
  uint8_t t6[] =  { 1,   5};

  // Array of all test cases
  uint8_t *a[] =      {  t1, t2, t3, t4, t5, t6};
  uint8_t *b[] =      {  t1, t5, t6, t4, t1, t4};

  uint8_t a1[] = { 2, 4, 6};
  uint8_t a2[] = {53, 202, 101};
  uint8_t a3[] = {11, 7};
  uint8_t a4[] = {200, 14};
  uint8_t a5[] = {4, 4, 4};
  uint8_t a6[] = {101, 12};

  uint8_t lengths[] = { 3, 3, 2, 2, 3, 2};

  uint8_t *answers[] = {a1, a2, a3, a4, a5, a6};
  
  int numTests = sizeof(lengths)/sizeof(uint8_t);

  for(int i=0;i<numTests;i++) {
    uint8_t *array1 = a[i];
    uint8_t *array2 = b[i];
    uint8_t length = lengths[i];  
    uint8_t algorithm[length];
    uint8_t assembly[length];  
    cSumArrays(array1, array2, algorithm, length);
    sumArrays(array1, array2, assembly, length);
    Serial.print("Summing: [");
    for(int j=0;j<length-1;j++) {
      Serial.print(array1[j]);
      Serial.print(", ");
    }
    if(length)
      Serial.print(array1[length-1]);
    Serial.println("]");
    Serial.print("and: [");
    for(int j=0;j<length-1;j++) {
      Serial.print(array2[j]);
      Serial.print(", ");
    }
    if(length)
      Serial.print(array2[length-1]);
    Serial.println("]");
    // Compare the results of assembly language implementation and real answer

    for(int j = 0; j < length-1; j++) {
      if(algorithm [j]!= answers[i][j]) {
          Serial.print("Error in cSumArrays: Recieved [");
          for(int k = 0; k < length-1; k++) {
            Serial.print(algorithm[k]);
            Serial.print(", ");
          }
          if(length)
            Serial.print(algorithm[length-1]);
          Serial.println("]");
          Serial.print("Should be: [");
          for(int k = 0; k < length-1; k++) {
            Serial.print(answers[i][k]);
            Serial.print(", ");
          }
          if(length)
            Serial.print(answers[i][length-1]);
          Serial.println("]");
          break;
      }
    }

    for(int j = 0; j < length; j++) {
      if(assembly[j] != answers[i][j]) {
          Serial.print("Error in sumArrays (assembly): Recieved [");
          for(int k = 0; k < length-1; k++) {
            Serial.print(assembly[k]);
            Serial.print(", ");
          }
          if(length)
            Serial.print(assembly[length-1]);
          Serial.println("]");
          Serial.print("Should be: [");
          for(int k = 0; k < length-1; k++) {
            Serial.print(answers[i][k]);
            Serial.print(", ");
          }
          if(length)
            Serial.print(answers[i][length-1]);
          Serial.println("]");
          break;
      }
    }
  }
}

void testDot() {
  Serial.println("**** Testing dot() ****");  

  // Individual test cases
  uint8_t t1[] =  { 1,   2,   3};
  uint8_t t2[] =  {50, 200, 100};
  uint8_t t3[] =  {10,   2};
  uint8_t t4[] =  { 100, 7};
  uint8_t t5[] =  { 3, 2, 1};
  uint8_t t6[] =  { 1,   5};

  // Array of all test cases
  uint8_t *a[] =      {  t1, t2, t3, t4, t5, t6};
  uint8_t *b[] =      {  t1, t5, t6, t4, t1, t4};

  uint8_t lengths[] = { 3, 3, 2, 2, 3, 2};

  uint16_t answers[] = {14, 650, 20, 10049, 10, 135};
  
  int numTests = sizeof(lengths)/sizeof(uint8_t);

  for(int i=0;i<numTests;i++) {
    uint8_t *array1 = a[i];
    uint8_t *array2 = b[i];
    uint8_t length = lengths[i];    
    uint16_t algorithm = cDot(array1, array2, length);
    uint16_t assembly = dot(array1, array2, length);
    Serial.print("Dot product of: [");
    for(int j=0;j<length-1;j++) {
      Serial.print(array1[j]);
      Serial.print(", ");
    }
    if(length)
      Serial.print(array1[length-1]);
    Serial.println("]");
    Serial.print("and: [");
    for(int j=0;j<length-1;j++) {
      Serial.print(array2[j]);
      Serial.print(", ");
    }
    if(length)
      Serial.print(array2[length-1]);
    Serial.println("]");

    if(algorithm != answers[i]) {
      pprintf("cDot(...) is %u; Should be %u <- ERROR in cDot()", algorithm, answers[i]);
      Serial.println();
    }

    if(assembly != answers[i]) {
      pprintf("dot(...) is %u; Should be %u <- ERROR in dot()", assembly, answers[i]);
      Serial.println();
    }
  }
}
void setup() {
  Serial.begin(9600);
  Serial.println("Starting tests...");

  testGlobals();

  testCStringLength();

  testSumArrays();

  testDot();

  Serial.println("Done with tests!!!");
}

void loop() { /* unused */ }
