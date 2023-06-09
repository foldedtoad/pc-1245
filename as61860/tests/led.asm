;led.asm = LED Light Effect for PC-1245
; AS61860 assembler
; Assemble: as61860 -glaxff led.asm
; ---------------------------------------------------
;IB8 = data  74HC595 
;IB7 = clock 74HC595 
;FO2 = lach  74HC595 
; ---------------------------------------------------

    .AREA t61860 (ABS)

    .ORG    0xC000
    LIA     0x00    ;A=0
    LP      REG_K
    ANIM    0x00
    ORIM    0x08    ;K=8
Loop:
    LIP     REG_IB
    ANIM    0x3F    ;IB=00111111
    OUTB
    SR              ;A>>1,C
    JRNCP   Jump
    ORIM    0x80    ;IB=10111111
Jump:
    OUTB
    ORIM    0x40    ;IB=X1111111
    OUTB
    DECK
    JRNZM   Loop
    LIP     REG_FO
    ORIM    0x02    ;FO=00000010
    OUTF
    ANIM    0xFD    ;FO=11111101
    OUTF
    RTN
