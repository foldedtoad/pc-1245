;-----------------------------------------------
; motor.asm = Motor control for SHARP PC-1245
; AS61860 assembler, port IB7,IB8
; Assemble: as61860 -glaxff motor.asm
; -----------------------------------------------

        .AREA t61860 (ABS)

        .ORG    0xC000
; Motor Left
        LIP     REG_IB
        ANIM    0x7F    ;IB = IB & 0x7F
        ORIM    0x80    ;IB = IB | 0x80
        OUTB
        RTN

; Motor Right
        LIP     REG_IB
        ANIM    0xBF    ;IB = IB & 0xBF
        ORIM    0x40    ;IB = IB | 0x40
        OUTB
        RTN

; Motor Stop
        LIP     REG_IB
        ANIM    0x3F    ;IB = IB & 0x3F
        OUTB
        RTN
