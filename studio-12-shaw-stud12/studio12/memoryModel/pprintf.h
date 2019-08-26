#ifndef pprintf

#define sprintfBufferSz 100

extern char sprintfBuffer[];
// pprint assumes the format is constant.
#define pprintf(fmt, ...) { String fmtStr = F(fmt); \
                            snprintf(sprintfBuffer, sprintfBufferSz, fmtStr.c_str(), __VA_ARGS__); \
                            Serial.print(sprintfBuffer); }

#endif
