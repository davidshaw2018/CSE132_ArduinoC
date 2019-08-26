// Function prototypes for assembly file.

extern "C" {
  boolean hasAOne(byte num);
  char byteToAscii(byte num);
  int int8ToInt(int8_t num);
  int addInt8ToInt(int8_t num1, int num2);
  int add4Int8(int8_t num1, int8_t num2, int8_t num3, int8_t num4);
  int average(byte num1, byte num2);
}
