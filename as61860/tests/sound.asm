; -----------------------------------------------
; sound.asm = Sound for SHARP PC-1245
; AS61860 assembler
; Assemble: as61860 -glaxff sound.asm
; -----------------------------------------------

      .AREA sound (ABS)

      .ORG  0xC000
      LIA   0x00        ; <== Length
      PUSH              ; A --> (R)
      LIP   REG_Cout
      LDM               ; (P) --> A
      ORIA  0x10        ; A = A | 0x10 
loop:
      EXAM              ; A <--> (P)
      OUTC
      WAIT  0x00        ; <== Frequency
      LOOP  loop
      RTN
