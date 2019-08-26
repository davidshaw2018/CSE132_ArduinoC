#include <avr/io.h>
#include "asmMacros.s"  // Include macros to print log messages or a single register
.text


.global slowDivisionUint8
slowDivisionUint8:
  // TODO: uint8_t slowDivisionUint8(uint8_t a, uint8_t b)
  // r24 = a, r22 = b
  // Copy r24 to r22/r18, and replace r24 with 0; represents sum
  mov r20,r24
  mov r18,r24
  ldi r24,0
  // r20 is now the dividend, r22 the divisor; leave unchanged
  // decrease r18 
  jmp sub_loop
sub_loop:
  cp r18,r22
  brlo loop_end
  sub r18,r22
  inc r24
  jmp sub_loop
loop_end:
  // Register contents now: r18 = remainder, r20 = dividend, 
  // r22 = divisor, r24 = quotient
  ret


.global greaterThanOrEqualUInt16
greaterThanOrEqualUInt16:
  // TODO: bool greaterThanOrEqualUInt16(uint16_t a, uint16_t b)
  // r25,r24 represent a; r23,r22 represent b, but both unsigned
  // Check r25, r23; if r25 < r23, a must be less than b, return false
  cp r25,r23
  brlo method_false
  // Check equality next; r25 >= r23 at this stage; if not equal a > b, return true
  cp r25,r23
  brne method_true
  // r25 must be equal to r23 if this stage reached; check r24,r22
  cp r24,r22
  // branch to win method if r24 >= r22
  brsh method_true
  // At this point, r25 < r23, r24 < r22; must be false 
  jmp method_false
method_true:
  // Any time this is reached, return true
  ldi r24,1
  ret
method_false:
  // Any time this is reached, return false
  ldi r25,0
  ldi r24,0
  ret


.global slowDivisionUint16
slowDivisionUint16:
  // TODO: uint16_t slowDivisionUint16(uint16_t a, uint16_t b)
  // Initially: r25/r24 contains dividend, r23/r22 contains divisor
  // Move r25/r24 to r19/r18, use r24 to store answer
  // r19/r18 to keep track of current dividend value
  movw r18,r24
  // movw r20,r24
  ldi r24,0
  ldi r25,0
  // load r20 with 255, to check for overflow with subtraction
  ldi r20, 255
  jmp sub_16_loop
sub_16_loop:
  // Push r24,r25 to stack
  push r24
  push r25
  // compare r19/r18 to r23/r22
  movw r24,r18
  call greaterThanOrEqualUInt16;
  // If false, end loop
  cpi r24,0
  breq end_16_loop
  // Do while loop stuff
  pop r25
  pop r24
  // Decrease r19/r18 accordingly
  sbc r18,r22
  sbc r19,r23
  // Increment r25
  inc r25
  // Check for r24 overflow, skip decrementing r25 if true
  cpse r24,r20
  dec r25
  inc r24
  jmp sub_16_loop
end_16_loop:
  pop r25
  pop r24
  // At this point, r24 should represent quotient
  ret
  
.global slowModulusUint8
slowModulusUint8:
  // TODO: uint16_t slowModulusUint8(uint8_t a, uint8_t b)
  call slowDivisionUint8;
  // r24 now the quotient, r20 the dividend, r22 the divisor
  push r0
  push r1
  // Multiply quotient * divisor, store in r0
  mul r24,r22
  // subtract result from dividend, and move to r24
  sub r20,r0
  mov r24,r20
  // restore r1,r0
  pop r1
  pop r0
  // clear r25
  ldi r25,0
  ret

.global sumOddsUint8
sumOddsUint8:
  // TODO uint16_t sumOddsUint8(uint8_t a, uint8_t b)
  // register status: r24 min, r22 max
  // 1st step: check moduluses == 0
  // put min in r18, max in r16
  mov r18,r24
  push r16
  mov r16,r22
  // r18 used in division method; push
  push r18
  // load r22 with 2 to use modulus method
  ldi r22,2
  // call printRegs;
  call slowModulusUint8;
  // r24 now either 1 or 0; 1 if min is odd, 0 if even
  ldi r20,1
  // if true, min is odd skip incrementation
  pop r18
  cpse r24,r20
  inc r18
  mov r24,r16
  // call printRegs;
  push r16
  push r18
  call slowModulusUint8;
  // max now in r16
  // Check if max is odd
  ldi r20,1
  pop r18
  pop r16
  cpse r24,r20 
  dec r16
  // Now a and b are odd numbers in r18/r16 respectively
  //jump to while loop
  // call printRegs;
  ldi r20,0
  jmp add_loop
add_loop:
  // Check min <= max still, otherwise go to loop end
  cp r16,r18
  brlo add_loop_end
  // Use r20 for sum
  add r20,r18
  // min += 2
  add r18,r22
  jmp add_loop
add_loop_end:
  mov r24,r20
  pop r16
  ret

