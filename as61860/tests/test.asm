			.ORG 0x2100
			case1 $05,$ABOC
			case2
			dl $05,$D84C
			dl $06,$AEC0
			dl $07,$D15B
			dl $0B,$E801
			dl $0C,$E8A0
			dw $B250
			ds 5
			db 'A','B'
			db "Hello"," ","World",0
			db $10,$20,$30,$40,$50

start:
			jrp	main
			lp $10
			cal	$1D20
GetByteSIO:
			lia $FF
			push
			lip $5D
			anim $DF
			outb
			orim $20
_loop:
			inb
			tsia $20
			jrzp _20
			loop _loop
			outb
			wait $20
			sc
			rtn
_20:
			pop
			wait $0A
			rtn
main:
			call GetByteSIO
			rtn

			end
