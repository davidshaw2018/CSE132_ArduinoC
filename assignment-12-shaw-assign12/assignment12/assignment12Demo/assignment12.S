#include <avr/io.h>
#include "asmMacros.s"  // Include macros to print log messages or a single register
.data
globalvar: .byte 0

.text


.global updateGlobal
updateGlobal:
  // TODO: void updateGlobal(byte a)
  ldi r30, lo8(globalvar);
  ldi r31, hi8(globalvar);
  ld r22, Z
  add r24,r22
  st Z,r24
  ret


.global getGlobal
getGlobal:
  // TODO: uint8_t getGlobal()
  ldi r30, lo8(globalvar);
  ldi r31, hi8(globalvar);
  ld r24,Z
  ret


.global cStringLength
cStringLength:
  // TODO: uint8_t cStringLength(const char aString[])
  // Step 1: move aString to mem space
  mov r30,r24
  mov r31,r25
  // r24 is answer
  ldi r24,0
  jmp length_while_loop
length_while_loop:
  // Load Z into r20, increment Z
  ld r20, Z+
  // Check if r20 == 0
  cpi r20,0
  breq end_length_while_loop
  inc r24
  jmp length_while_loop
end_length_while_loop:
  ret

.global sumArrays
sumArrays:
  // TODO: void sumArrays(uint8_t *a, uint8_t *b, uint8_t *c, byte length)
  // Move c into memory space Z
  mov r30, r20
  mov r31, r21
  // Push registers r26-29 to stack
  push r26
  push r27
  push r28
  push r29
  // Move b into memory space Y
  mov r28,r22
  mov r29,r23
  // Move a into memory space X
  mov r26,r24
  mov r27,r25
  // r20 is i, counter
  ldi r20,0
  jmp sum_while_loop
sum_while_loop:
  // Compare length in r18 to counter
  cp r20,r18
  brsh end_sum_while_loop
  // Let r24 = a[i],r22 = b[i]
  ld r24, X+
  ld r22, Y+
  // sum x and y in r24
  add r24,r22
  // Store r24 in Z memory space
  st Z+,r24
  // Increment i
  inc r20
  jmp sum_while_loop
end_sum_while_loop:
  // Restore X, Y registers
  pop r29
  pop r28
  pop r27
  pop r26
  ret

.global dot
dot:
  // TODO uint16_t dot(uint8_t *a, uint8_t *b, byte length)
  // Let r18 be the counter, r16 be the sum
  // Push r0,r1
  push r0
  push r1
  push r16
  ldi r16,0
  clr r17
  ldi r18,0
  // Push a, b to memory space Z and Y
  mov r30,r24
  mov r31,r25
  push r28
  push r29
  // Stack order: r0,r1,r16,r28,r29
  mov r28,r22
  mov r29,r23
  jmp dot_while_loop
dot_while_loop:
  // Branch if i >= length
  cp r18,r20
  brsh dot_end_loop
  // Store a[i], b[i] in r24,r22
  ld r24,Z+
  ld r22,Y+
  // Multiply r24,r22, and store result in r0,r1
  mul r24,r22
  // Add multiplication result to r16
  add r16,r0
  adc r17,r1
  inc r18
  jmp dot_while_loop
dot_end_loop:
  // Move r16, r17 to r24,r25
  movw r24,r16
  // Restore stack
  pop r29
  pop r28
  pop r16
  pop r1
  pop r0
  ret

