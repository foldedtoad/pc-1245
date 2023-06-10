;-----------------------------------------------
; cap.asm = Capacitance Meter for SHARP PC-1245
; AS61860 assembler, port Xout,Xin
; Assemble: as61860 -glaxff cap.asm
;-----------------------------------------------

        .AREA t61860 (ABS)

        .ORG    0xC000
        LP      REG_XL
        ANIM    0x00
        LP      REG_XH
        ANIM    0x00
        LIP     REG_Cout
        ORIM    0x50        ; Xout
        OUTC
loop1:
        IX                  ; X + 1 --> X, X --> DP
        TEST    0x80        ; Xin --> z
        JRZM    loop1
        LIDP    0x6036      ; DP = 0x6036
        SLW                 ; [SHIFT4LEFT(P); P-1 --> P] * I
        LP      REG_XL
        MVDM                ; (P) --> (DP)
        LIDP    0x6037      ; DP = 0x6037
        LP      REG_XH
        MVDM                ; (P) --> (DP)
        RTN
