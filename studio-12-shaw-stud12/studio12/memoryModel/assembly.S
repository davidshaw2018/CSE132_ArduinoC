#include <avr/io.h>
#include "asmMacros.S"

.data
globalasm: .byte 0

// TODO: Complete functions!

.text

.global increment
increment:
  ldi r30, lo8(globalasm)
  ldi r31, hi8(globalasm)
  ld r24,Z
  inc r24
  st Z,r24
  ret

.global decrement
decrement:
  ldi r30, lo8(globalasm)
  ldi r31, hi8(globalasm)
  ld r24,Z
  dec r24
  st Z,r24
  ret

.global sumArray
sumArray:
  // r24, r25 we want to use for sum
  mov r30,r24
  mov r31,r25
  ldi r24,0
  ldi r25,0
  // r18 is counter i
  mov r18,r24
  jmp while_loop
while_loop:
  // check i < length
  cp r22,r18
  brlo end_loop
  // Load Z into r20, increment Z
  ld r20, Z+
  // Add r20 to r24
  add r24,r20
  adc r25,r1
  inc r18
  jmp while_loop
end_loop:
  ret
