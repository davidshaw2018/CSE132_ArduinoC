#include <avr/io.h>
#include "asmMacros.S"


// TODO: Complete functions!

.global lessThan
lessThan:
  cp r24,r22
  brlt less
  ldi r24,0
  ret
less:
  ldi r24,1
  ret

.global lessThanOrEqualUnsigned
lessThanOrEqualUnsigned:
  cp r24,r22
  brne notequal
  ldi r24,1
  ret
notequal:
  cp r24,r22
  brlo lower
  ldi r24,0
  ret
lower:
  ldi r24,1
  ret
  

.global slowMultiply
slowMultiply:
  ldi r20,0 // Sum
  ldi r18,0 // Counter
  push r16
  ldi r16,1 // ++i
  jmp whileloop
whileloop: 
  cp r18,r24
  breq finished
  add r20,r22
  add r18,r16
  jmp whileloop
finished:
  mov r24,r20
  pop r16
  ret

.global slowExponent
slowExponent:
  ldi r20,1 // Sum
  ldi r18,0 // Exponent Counter, i
  push r16
  push r26
  ldi r26,1 // ++
  push r28
  jmp outerloop
  // Stack order: r28,r26,r16
outerloop:
  cp r18,r22   // Check i < power
  breq endloop
  ldi r28,0   // innersum
  ldi r16,0   // Multiply counter, j
  jmp innerloop
innerloop:
  cp r16,r24
  breq outerloopend
  add r28,r20 // innersum += sum
  add r16,r26 // ++j
  jmp innerloop
outerloopend:
  mov r20,r28 //sum = innersum
  add r18,r26 //++i
  jmp outerloop
endloop:
  mov r24,r20
  pop r28
  pop r26
  pop r16
  ret






  
