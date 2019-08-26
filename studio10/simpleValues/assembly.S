#include <avr/io.h>


; AVR assembly comments start with a semicolon 
// (or a double slash, like C)
; Lines without labels should be indented once.

; You can "call printRegs" in your code to help you understand the register values and how they change.

.global giveMeMax
giveMeMax:
  call printRegs;
  ldi r24, 255 // Load the value 1 into register 24
  ret

.global giveMeZero
giveMeZero:
  ldi r24, 0
  ret

 // Define further "functions" below:
 // .global functionName
 // functionName:
 //   *code*
 //   ret

.global addFour 
addFour: 
  ldi r18, 4
  call printRegs;
  add r24,r18
  ret

.global turnOnLight
turnOnLight:
  
  sbi _SFR_IO_ADDR(DDRB), PIN5
//  sbi _SFR_IO_ADDR(DDRB), 1
  sbi _SFR_IO_ADDR(PORTB), PIN5
  ret




  
