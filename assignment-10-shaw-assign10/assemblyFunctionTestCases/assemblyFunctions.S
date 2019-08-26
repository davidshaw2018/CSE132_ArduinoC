#include <avr/io.h>


.global hasAOne
hasAOne:
  ldi r22, 0
  cpse r24,r22
  ldi r24,1
  ret
  
.global byteToAscii
byteToAscii:
  ldi r22, 48
  add r24,r22
  ret

.global int8ToInt
int8ToInt:
  ldi r22,1
  push r0
  push r1
  muls r24,r22
  movw r24,r0
  pop r1
  pop r0
  ret

.global addInt8ToInt
addInt8ToInt:
  push r22
  call int8ToInt;
  pop r22
  add r24,r22
  adc r25,r23
  ret

.global add4Int8
add4Int8:
  // Save r22, since it is used in int8ToInt
  push r22  
  // num1 is now a 16-bit integer in r25,r24
  call int8ToInt;
  // Move num1 in r25/r24 to r23/r22
  movw r22,r24
  // Pop num2 in stack onto r24
  pop r24
  // Current status: num1 as int is in r23/r22, num2 as int8_t is in r24
  // Call add function
  call addInt8ToInt;
  // Now r24/r25 contain sum of num1 and num2
  // move sum of num1 and num2 to r22, as above
  movw r22,r24
  // move num3 in r20 to r24
  mov r24,r20
  // Call add function again, repeat
  call addInt8ToInt;
  movw r22,r24
  mov r24,r18
  call addInt8ToInt;
  ret

.global average
average:
  add r24,r22
  ror r24
  ret
