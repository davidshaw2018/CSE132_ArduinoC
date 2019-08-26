
# Use this macro to print words to aid debugging.
# This can help you trace through programs and get a better idea of 
# the sequence of execution.  You can use it to log the execution and see how many times
# loops repeat, whether an if or an else executes, etc.
#
#  Use:   print word        // will print "word". 
#  Use:   Multiple words by using [] for grouping
#    print [this and that]  // will print "[this and that]"
.macro print m
.data 
_p\@: .asciz "\m"
.text
  push r16 
  push r17 
  push r18
  push r19
  push r20
  push r21
  push r22
  push r23
  push r24
  push r25
  push r26
  push r27
  push r28
  push r29
  push r30
  push r31
  in r16,0x3f   // r16 = SREG

  ldi r24, lo8(_p\@)
  ldi r25, hi8(_p\@)
  call _asmprint

  pop r31
  pop r30
  pop r29
  pop r28
  pop r27
  pop r26
  pop r25
  pop r24
  pop r23
  pop r22
  pop r21
  pop r20
  pop r19
  pop r18
  pop r17
  out 0x3f,r16  // SREG = r16
  pop r16

.endm

# Use this macro to print a single register.
# Use:  printAReg n  // where n is the number of the register, like 22 for r22.  This will print "r22 = X"
.macro printAReg r
.data 
.text
  push r16 
  push r17 
  push r18
  push r19
  push r20
  push r21
  push r22
  push r23
  push r24
  push r25
  push r26
  push r27
  push r28
  push r29
  push r30
  push r31
  in r16,0x3f   // r16 = SREG

  mov  22,\r
  ldi  r24, \r
  call _asmprintRV

  pop r31
  pop r30
  pop r29
  pop r28
  pop r27
  pop r26
  pop r25
  pop r24
  pop r23
  pop r22
  pop r21
  pop r20
  pop r19
  pop r18
  pop r17
  out 0x3f,r16  // SREG = r16
  pop r16
.endm
