// Function prototypes for assembly file.
extern "C" {
    void updateGlobal(uint8_t a);
    uint8_t getGlobal();
    uint8_t cStringLength(const char aString[]);
    void sumArrays(uint8_t *a, uint8_t *b, uint8_t *c, byte length);
    uint16_t dot(uint8_t *a, uint8_t *b, byte length);
}

