// Function prototypes for assembly file.

extern "C" {
  bool lessThan(int8_t a, int8_t b);
  bool lessThanOrEqualUnsigned(byte a, byte b);
  byte slowMultiply(byte a, byte b);
  byte slowExponent(byte base, byte power);
}
