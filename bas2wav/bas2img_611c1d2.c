/* Textcoding Unicode (UTF-8, no BOM), End of Line Windows (CRLF)
              contains UTF-8 graphic characters in the code
bas2img.c

For the copying conditions, please note the comments in front of and the output (--version) of the "PrintVersion" function.

Development history
-------------------
  until ver 5.0     Joachim BOHS (changes for ASM after version 4.0 were reintegrated in 2019)
2004-08-15	0.9-4.0 Joachim BOHS
	von ver 0.9 hochgezählt in v1.0 wegen UPRSTR(inputline) soll nicht die
	ganze zeile umfassen, "comments" and  "strings" sollen bleiben.
	noch zu ändern uprstr nur auf nicht "" anwenden.
	von ver 1.0 hochgezählt in v2.0 wegen USING fehlte
	von ver 2.0 hochgezählt in v3.0 wegen REM nutzte nicht line_buffer2
	von ver 3.0 hochgezählt in v4.0 wegen spaces am end of line is error in PC1500

2010-03-12	V 5.0	Norbert ROLL
	Umgestellt auf ANSI-C, u.a. strupr() ersetzt; DOS-Fkt. entfernt; zusätzliche Fehlermeldungen,
	Ausgabe auf stdout statt auf stderr; im BASIC-Text CRLF, CR oder LF möglich (Win/Mac/Unix)
	Ausgabe der eingelesenen Zeilen als Fortschrittsanzeige (z.B. bei Benutzung von DOSBox (0.73))
	gcc 4.0.1 (Mac OSX 10.4.11 auf Intel Core Duo für OSX ab 10.1 auf Intel 32 Bit und PowerPC 32 Bit)
		gcc -Wall -arch i386 -arch ppc -mmacosx-version-min=10.1 bas2img.c -o bas2img
	gcc 3.4.5-20060117-3 (MinGW, Win XP Home Edition 2002 auf Intel Celeron M für 32-Bit DOS-Box/Win)
		gcc -Wall bas2img.c -o bas2img.exe
	gcc 4.4.2 (DJGPP, Win XP Home Edition 2002 auf Intel Celeron M für 16-Bit DOS-Box mit DPMI / Win)
		gcc -Wall bas2img.c -o bas2img.exe
	dmc 8.42n (Digital Mars, Win XP Home Edition 2002 auf Intel Celeron M für 16-Bit DOS ab 8088)
		dmc -ms -d -w- -0 bas2img.c -o bas2img.exe

2011-12-05	V 5.1	Manfred NOSSWITZ
	Changed to ANSI-C e.g. strupr()
	Expanded to PC-1245, 1251 (OLD-BASIC); 1261, 1350, 1360, 1401, 1402, 1403, 1450, 1475 (NEW-BASIC).
	Ignore spaces in the beginning of lines and after REM-Commands for NEW-BASIC.
	Last character in OLD-BASIC- and NEW-BASIC-IMG-File is 0x0D.
	Last characters in 1500-IMG-File are 0x0D, 0xFF.
	Translation of π (PI), √ (SQR) and ¥ (Yen). (utf-8 <-> Sharp-ASCII)
	Command line parser changed to getopt().
	Undefined behavior of strcpy( x, x + 1 ) when source and destination strings overlap, solved.
	Functions strupr, shift_left, del_spaces and replace_str tested in 64bit-systems.
	32bit compilation with gcc (tdm64-1) 4.6.1 (WindowsXP-prof [32bit]): gcc -pedantic -m32 -o xxx xxx.c
	32bit compilation with gcc-4_5-branch revision 167585 (OpenSUSE 11.4 [32bit]): gcc -pedantic -m32 -o xxx xxx.c
	64bit compilation with gcc (tdm64-1) 4.6.1 (Windows7-prof [64bit]): gcc -pedantic -m64 -o xxx xxx.c
	64bit compilation with gcc-4_5-branch revision 167585 (OpenSUSE 11.4 [64bit]): gcc -pedantic -m64 -o xxx xxx.c
	For testing PC-1402 was available only.

2013-10-05	v 5.2	Olivier De Smet
	Added 1475 tokens

2013-11-25	v 5.2.1b	Torsten Muecker
	Added more 1360 tokens, special chars, moved 1360 to NEW_BAS2
	Delete colons following the line numbers (for compatibility with other listings)
2014-01-12	v 5.2.1b	Torsten Muecker
	Tokens corrected for NEW_BAS2, LET i.e. ,now EXT_BAS as Wav2bin
	Special chars in Strings and one-char-functions PI, SQR corrected for PC-14xx
	Comment lines beginning with ' are allowed now and will not be transfered
	Sources from TransFile PC (.SHA) with special DOS chars allowed now -
	put "." as first char in the first line to convert, rest of first line is ignored
	Leading artifact in ASC-Files from some serial transfers are ignored now
2014-09-01	v 5.3.0 beta 12b	Torsten Mücker
	Support for OLD-BAS (i.e. 1251) completed, line, conv_asc2old
	Convert lower chars in string constants to upper for PCs, that don´t support lower chars
	Separate tokens for PC-1421 added,
	2-Byte tokens for PC-1403, 1460, 1445, 1440, 1425 added (tokenL=1 and tokenL=2 mixed)
	PC-1280 and more PCs added,
	Help screen changed
	Tokens for PC-E500 added
	Handling for old Exp sign €/[E] and equal placeholders [SQR][PI][Y] for all PC groups added
	For OLD_BAS Handling of >=, <=, <> corrected
	more and precise handling of special chars, card symbols added, [INS][FUL] added
	if DOS-US Chars for √, π, € found, always will converted
    Image line maximal length check implemented
	Existing Limitation for EXT_BAS:
        NO compile of fixed numeric line number to 0x1F + binary format HL will done,
        recommended for pocketcom: Switch to "TEXT" and recompile with "BASIC" will do it
    Tokens for PC-E500S added
	Existing Limitation for E/G-BAS:
        NO compile of fixed numeric line number and mark distances, no compile of fixed numbers, no relative branch distances,
        MUST done on pocketcom: Switch to "TEXT" and recompile with "BASIC" will do it
    additional EOF mark for PC-1500 removed
    some changes in categorisation of pocket computers
    Tokens for E/G-series up to G850S and 2. REM ID "'"
    Debug levels added, no line output without l option, better to see errors and warnings,
    added old arguments conversion to new arguments for backward compatibility with 3rd-party software
    added minor tokens for old BASIC
    minor token replacements for PC-G800 series
    token for PC-1600 series added, support for merged files with linenb 99999,
    adapted check of line length
2014-09-21	v 5.3.1 beta 2b	Torsten Mücker
    --type option added, output of BASIC Text modus lines and ASCII files
    reconstruct all special chars from wav2bin
    compile fixed line numbers for PC-1600, GRP_EXT and newer series
    changes spaces after ASCII line number
    check compatibility with type ASC and TXT
2014-11-26	v 5.9.8 beta 09 Torsten Mücker
    more support of merged program files
    post-processing of G series for RemIdChar
    shortcuts for tokens
    more checks for length of tokens and lines
    E-series labels not tokenized, G850 label without :
    PC-121x tokens separated from old BASIC
2015-05-31	v 5.9.9 gamma 4c1 Torsten Mücker
    PC-1421 i, n
    Debug option for preprocessor and upper cases
    Illegal line number sequence for New BASIC without auto merge mark with l=0x800
2015-07-22	v 6.0.9 beta 3.01 Torsten Mücker
    --keywords loadable keyword files
    debug option for append EOF markto image (not recommended normally)
    preparations for other Home computer with simple intermediate codes (non SHARP PC)
    Token for PC-BASIC, RWE and other
2015-11-16	v 6.0.9 beta 4.02 Torsten Mücker
    1600M1, Ursoft
2016-02-28	V 6.0.9 RC1 for V 6.1 Torsten Mücker
2019-03-16	V 6.0.9c2b Torsten Mücker
    improved debug option 0x200000 to append additional end marks for asc files
    check for EOF_ASC [SUB]
    added parameter --endmark
2019-05-08	V 6.0.9c2b1a
    conflict old VAL function with ~
2019-06-13	V 6.0.9c2b3c
    CE-158 commands with lower cases
2019-06-22	V 6.0.9 c2b3c(1) PC-1460 token COLOR, CSIZE
2019-07-05	V 6.0.9 c2b3d/e(d) Series 1260-1475, E200/G801-G850 models with japan mode,
    support for Japanese chars, remove UTF-8 BOM
2019-07-21	V 6.0.9 c2b4(0) PC-1500 Katakana, other with -l 0x100,
    --codepoints file parameter for self-definition of special chars
    integrated CP437 for UTF8 characters (PC-1600 and E500)
    --utf8 parameter as wav2bin
    Indents, spaces at the beginning of the line in the PC-E/G series are no longer removed
2019-07-26	V 6.0.9 c2b4(4) PC-1500 Katakana, other with -l 0x100,
    changed special char processing, istoken1
    improvements for codepoints files
2019-07-27	V 6.0.9 c2b5(1)
    UTF8_ESC replace escaped chars
    Refactored tokenizer: Save lower cases after REM inside of lines,
    Outsourced processing of REM lines, better del_Spaces,
    Probably not necessary attempts of token recognition commented out
2019-08-03	V 6.0.9 c2b5(3c)
    E437 tables, Token E/G could be inside a variable name
    Refactoring Tokenizer: IsChar4Cmd
    Added dedicated tokens for G850 series
2019-08-18	V 6.0.9 c2b6
    Refactored Preprocessor, default values for special chars
    prc_token1C, Istoken(1C) preprocessor, shortcuts, IsChar4Cmd,
    warn-counter, tokenizer, E-Label, E-Label convert to string
2019-08-29	V 6.0.9 c2b6(2) GRP_E Token :ELSE
2019-08-30                  Path length
2019-09-12	V 6.0.9 c2b6(3) Block ELSE, structured B. shortcuts
                            Separation of tokens PC-E/G/ext. series, isShrtC()
2019-09-13	V 6.0.9 c2b6(4) -l BAS_AUTO AUTO_INC line number, e.g. for .asm (original from J. Bohs 2005)
2019-09-16	V 6.0.9 c2b7    --auto auto_incr, 2x --level, text line cnt
2019-09-20	V 6.0.9 c2b7(1) -SJIS for ANSI
2019-09-26	V 6.0.9 c2b7(1a) auto_new (delete existing line numbers), E500 LNb + colon only
2019-09-28	V 6.0.9 c2b7(1a1) type asm/c of G series
2019-11-01	V 6.0.9 c2b7(2) type asm/c of G series no fixed tags, asm needs leading spaces
                            restore leading spaces without line number, [EOF]
2019-11-25(22) V 6.0.9 c2b7(2b) E437 [FE], [FF]
2020-04-01  V 6.0.9 c2c(1)  Less warnings for text line length
2020-10-18  V 6.0.9 c2c(3a) PC-1100 group, G850VS token PIOPUT, thanks to Robert
2020-11-08  V 6.0.9 c2c(4b3)PC-144x, CASL, CAP-X, SPC_LINES_OK flag
2020-11-11  V 6.0.9 c2c(4b4a)Restoration of the compiler-independent EOF recognition of bin2wav 5.0, thanks Robert
2020-12-30  V 6.0.9 c2d = c2c(4b4a1) Compiler warnings
2020-12-31  V 6.0.9 c2d(1) recover leading spaces from non numbered asm lines

2021-01-27  V 6.1.1 b1a Robert van Engelen
	Optimizations of the BASIC compiler of the PC-E500(S)
	Compile all numbers, add jump distance to branches
2021-01-31  V 6.1.1 b2b(2) comments and messages
2021-02-12  V 6.1.1 b2c do not tokenize E500 DATA values

2021-04-05  V 6.1.1 b2c(3)  1416G INP, OUT, PC-1600 KBRD
2021-04-18  V 6.1.1 c1  Torsten Muecker
2021-07-15  V 6.1.1 c1 (3)b PC-1100, CNV_SJIS for some jap. models, ParamCnt, models with "Jap"
2021-07-16  V 6.1.1 c1c
2021-08-11  V 6.1.1 c1d beta (2b) Kanji support for PC-1360K, 1600K, minimal for 1500D, with codepoint file only
2021-08-29  V 6.1.1 c1d beta (3c1) PC-1246DB Katakana, beta (4) E500J, E500K(2)
2021-09-01  V 6.1.1 c1d beta (6a) Kanji chars outside of strings/REM and tokenize PI, pi
2021-10-01  V 6.1.1 c1d length of codestrings for replacing of full width Katakana with 2 codes for new (S1) series
2021-10-31  V 6.1.1 c1d (1) Robert van Engelen
    PC-E500 double precision tokenized value with total number of digits including zeros exceeds 10
2022-10-18  V 6.1.1 c1d (1a) Names of PC-1401V2 and derived
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>		/* Command line parser getopt(). */
#include <ctype.h>		/* Test Characters */
/* #include <locale.h>     Problem with strupr and special chars xFA-xFE */

#define PDATE           "October 2022"
#define PVERSION        "6.1.1 c1d (2)"
#define DEBUG_ARG       "0"

#define TYPE_NOK        0
#define TYPE_IMG        2
#define TYPE_ASC        6   /* For PC-E/G/1600 ASCII Data */
#define TYPE_TXT        8   /* For GRP_NEW, GRP_EXT and GRP_E text modus Image Data */

/* For the E-500 series, the full format is supported with version 6.1.1 for transmission via CLOAD
   There are no known errors, but if runtime errors occur on the pocket computer, then you have to
   carry out the code optimization with Basic -> TEXT -> BASIC on it.
   In this case you can also use the switch bas2img -l1 here. */
#define GRP_E           0x05    /* E500-series: PC-E500 */
#define GRP_G           0x08    /* G800 series: PC-G8xx, E200, E220 */
#define GRP_16          0x10    /* PC-1600 */
#define GRP_MZ          0x180   /* MZ series very limited support */

#define IDENT_UNKNOWN   0x00
#define IDENT_OLD_BAS   0x20	/* PC-1100 - 1255, End of line character 0x00 */
#define IDENT_NEW_BAS   0x70	/* PC-1260 - 1460, End of line character 0x0D */
#define IDENT_EXT_BAS   0x72	/* PC-1280, 1360, 147x */
#define IDENT_E_BAS     0x02    /* PC-E/G-series */

#define IDENT_PC15_BAS  0xA1	/* End of line characters 0x0D, EOF 0xFF removed */
#define IDENT_PC16_BAS  0x11    /* Mode 1 ID is as IDENT_E_BAS, real Mode 2 ID is 01 (PC-1500) */

#define BAS_MAX_CHR     0xDF    /* Higher should the 1. byte of a token of PC-16/1500 */
#define BAS_MAX_C15J    0xE6    /* Higher should the 1. byte of a token of PC-1500Jap */
#define BAS_NEW_CODE    0xEF    /* New 2-Byte tokens also */
#define BAS_EXT_CODE    0xFE    /* Extended 2-Byte only */
#define BAS_EXT_LINE_NB 0x1F    /* E- or extended fixed line numbers are binary coded */
#define BAS_E_JMP       0x1E    /* E500 and newer relative jumps after (IF, ELSE,) REM assist the interpreter */
#define BAS_E_NB        0x1D    /* E500 constant decimal numbers binary coded */
#define BAS_E_LBL       0x1C    /* E500 labeled jumps with * */

#define KANJI_CODE_MIN  0x81    /* Lowest table code */
#define KANJI_CODE_MAX  0x98    /* Highest table code PC-1360K, 1600K */
#define KANJI_CODE_MAXE 0x9F    /* Highest table code PC-E500K and other software drivers */
#define KANJI_CODE_MIN2 0xE0    /* Lowest first table code 2nd table space, software drivers */
#define KANJI_CODE_MAX2 0xEF    /* Highest first table code 2nd table space, software drivers */

#define UTF8_SET        239     /* Identify Katakana UTF8-Chars, first of three bytes (Uchar) */
                                /* utf8= 0 and 1 reserved for no, yes */
#define UTF8_DOS        3       /* for DOS-based Software with DOS-US graphics charset */
#define UTF8_ESCX       5       /* for conversion scripts, that use escape sequences to mask Sharp special and upper chars */

#define MERGE_MARK      99999   /* Number with empty line for mark of merged programs */

#define EOF_ASC         '\x1A'  /* End of ASCII transfered files */
#define BAS_NEW_EOL     '\x0D'  /* End of line, most BASIC intermediate codes */
#define BAS_OLD_EOL     '\x00'  /* End of line, of old BASIC intermediate codes */
#define BAS_NEW_EOF     '\xFF'  /* one of two bytes */
#define BAS_OLD_EOF     '\xF0'  /* one byte only */

#define B_ENDIAN_BIG     1      /* byte order of the target computer, all Sharp Pocket Computer */
#define B_ENDIAN_LITTLE  2      /* byte order of the target computer, Z80 based computers */
#define B_LINE_L_REL     1      /* line length stored relative in the image line */
#define B_LINE_L_ABS     2      /* instead a line length an absolute address pointer to next line is used */

#define LINE_LC_SHA      3      /* Negative offset between absolute length and the length entry of BASIC lines */
#define LINE_LC_OLD      2      /* Negative offset between absolute length and the PC buffer length of lines */

#define BGN_LINE         0x1000 /* Line Label may follow */
#define TOKEN_GEN        0      /* for GRP_EXT and newer line number processing and E-Labels */
#define TOKEN_LBL        0x100  /* Line number may follow this token */
#define TOKEN_LST        0x200  /* ON, ... more line numbers possible */
#define TOKEN_REM        0x400
#define TOKEN_COL        0x800  /* Colon before token need */
                                /* The lower byte of TokenType is needed for E500-Series control characters in the future */
#define true 1
#define false 0
#define last4CMD         2      /* For tokenizer, char allowed but only as the last character of a command */

#define cLL  1024		/* Constant value for max. Length of Lines */ // old: 256, 512 increased because transcription for PC-E series
#define cLPF 260		/* Constant value for max. Length of PathFilenames and other arguments */
#define cLC  255		/* Constant value for max. Length of Commands */ //old: 80

#define cLTK            16		/* Constant value for max. length of a token + 1 */
#define cMAXNBTK        2048    /* Maximum number of external defined token keywords*/
#define cLCH            10		/* Constant value for max. length of a character utf8 + 1 */
#define cLCS            17		/* Constant value for max. length of "[FE][hh][FE][hh]" + 1 */
#define cMAXNBCH        7000    /* Maximum number of external defined code points (code space entries) */  //before 1024
                                /* Option flags */
#define BAS_EOF_INCL  0x200000  /* Append an End Mark (0xFF or 0x1A) */
#define ERR_LIGN        0x800   /* Depress some line errors */
#define CNV_SJIS        0x100   /* Force conversion of 0xA1-DF to Japanese HW-Katakana, for ANSI SJIS and UTF-8 (unsupported PCs)*/
#define BAS_EXT_FRMT    0x1000  /* Switch convert *LABEL format of E/G-Series to BAS_EXT/1600 "LABEL" strings */
#define INS_APST        0x2000  /* Insert an apostrophe at the beginning of each line (for PC-Macro ) */
#define SPC_LINES_OK    0x400   /* Don't delete (empty) lines if with spaces */
#define BAS_AUTO        0x200   /* Replace missing/all line numbers according to an AUTO statement (no Renum, for .asm)*/
#define AUTO_INC        10      /* Increment value for AUTO line number */

#define SOURCE_BAS  0	/* BAS default source file written by wav2bin */
#define SOURCE_SHA  1	/* SHA Source file from "TransFile PC" with one header line */

#define ERR_NOK    -1   /* also normal EOF */
#define ERR_OK      0
#define ERR_ORD     2   /* Error when compiling a (decimal) number  */
#define ERR_SYNT    1
#define ERR_ARG     3   /* pocket not implemented, argument problem */
#define ERR_LINE    4   /* error with line numbers, old definition: 255 */
#define ERR_FILE    5   /* File I-O */
#define ERR_MEM     6   /* Line to long, Memory */
#define ERR_FMT     7   /* False token number format in keyword file */

#define COLON       0x3A

/*                      used types  def. bits    Win32 Lin32 Win64 Lin64 */
typedef int		bool;
/*			char;	    8             8     8     8     8    */
typedef unsigned char	uchar;
/*	        short;	    at least 16  16    16    16    16    */
typedef unsigned short	ushort;
/*			int;	    at least 16  32    32    32    32    */
typedef unsigned int	uint;
/*	long			    at least 32  32    32    32    64    */
typedef unsigned long	ulong;

 char  argP[cLPF] = "" ;
uchar  ident = IDENT_UNKNOWN ;
uint   pcId =  0 ;      /* moved from main to support more token tables for one Id, PC-1421 */
                        /* pcMode upper bits include the flags CNV_SJIS and Kanji as in wav2bin now */
uchar  pcMode = 0 ;     /* for PCs with more (E500) or modified (1600 Mode 1) character code tables
                           add 4 for Japanese models (Katakana), 8 for JIS-1 Kanji enabled, 16 for JIS-1-2.area */
ushort pcgrpId = IDENT_UNKNOWN ;

char  SQRidStr[6] = "\x00\x00\x00\x00\x00";
char  PI_idStr[6] = "\x00\x00\x00\x00\x00", piLidStr[6] = "\x00\x00\x00\x00\x00";
char  YENidStr[6] = "\x00\x00\x00\x00\x00", EURidStr[6] = "\x00\x00\x00\x00\x00";
char  INSidStr[6] = "\x00\x00\x00\x00\x00", FULidStr[6] = "\x00\x00\x00\x00\x00"; // fuLidStr[3]
const char* VarTAGidStr = "\xFF\xFF" ;

uint REMid  =  0 ;      /* moved from main to support TokenType (0) */
uint tokenL =  0 ;      /* moved from main to support tokens with mixed length (0) */
uint ll_Img = 80 ;      /* Constant value for max. length of BASIC IMAGE lines,
                           minus length of line Nb text to stay editable,
                           PC-E500 series lower 255 */
uint del_spc_cnt = 80 ; /* Value is reduced for the E/G series because spaces are allowed in the line */
const char* utf8_BOMstr = "\xEF\xBB\xBF" ;

bool err_line_ign = false ; /* depress some line errors */
bool shortcuts = true ;     /* replace also shortcuts (P. = PRINT ...) with tokens */
bool KeysFromFileOnly = false ; /* Use only token from keyword file*/

uint key_cnt = 0 ;      /* number of tokens from keyword definition file */
char keyword[cMAXNBTK][cLTK] ;
ushort keyval [cMAXNBTK] ;

uint code_cnt = 0 ;      /* number of changed entries in code space - code points file */
char  chrstring[cMAXNBCH][cLCH] ;
char codestring[cMAXNBCH][cLCS] ;
ushort codepoint [cMAXNBCH] ;
uint Kanji_Code_Max = KANJI_CODE_MAX ;

ulong  err_cnt = 0 ;    /* counts minor errors */
ulong  wrn_cnt = 0 ;    /* counts warnings */

/* PC-1600 mode 0, PC-E500 1. table from 80 to FF
   UTF-8 codes for code page 437, extended ASCII */

static uint  CodeE437_offset = 0x80;
static char* CodeE437[] = {
    "Ç","ü","é" ,"â","ä" ,"à","å","ç",    "ê","ë","è" ,"ï","î" ,"ì","Ä","Å",
    "É","æ","Æ" ,"ô","ö" ,"ò","û","ù",    "ÿ","Ö","Ü" ,"¢","£" ,"¥","₧","ƒ",
    "á","í","ó" ,"ú","ñ" ,"Ñ","ª","º",    "¿","⌐","¬" ,"½","¼" ,"¡","«","»",
    "░","▒","▓" ,"│","┤" ,"╡","╢","╖",    "╕","╣","║" ,"╗","╝" ,"╜","╛","┐",
    "└","┴","┬" ,"├","─" ,"┼","╞","╟",    "╚","╔","╩" ,"╦","╠" ,"═","╬","╧",
    "╨","╤","╥" ,"╙","╘" ,"╒","╓","╫",    "╪","┘","┌" ,"█","▄" ,"▌","▐","▀",
    "α","ß","Γ" ,"π","Σ" ,"σ","µ","τ",    "Φ","Θ","Ω" ,"δ","∞" ,"φ","ε","∩",
    "≡","±","≥" ,"≤","⌠" ,"⌡","÷","≈",    "°","∙","·" ,"√","ⁿ" ,"²","■","□",
};

static char* CodeE437_2atrans[] = {
    "[80]","[81]","[82]","[83]", "[84]","[85]","[86]","[87]",
    "[88]","[89]","[8A]","[8B]", "[8C]","[8D]","[8E]","[8F]",
    "[90]","[91]","[92]","[93]", "[94]","[95]","[96]","[97]",
    "[98]","[99]","[9A]","[9B]", "[9C]","[Y]", "[9E]","[9F]",
    "[A0]","[A1]","[A2]","[A3]", "[A4]","[A5]","[A6]","[A7]",
    "[A8]","[A9]","[AA]","[AB]", "[AC]","[AD]","[AE]","[AF]",
    "[B0]","[B1]","[B2]","[B3]", "[B4]","[B5]","[B6]","[B7]",
    "[B8]","[B9]","[BA]","[BB]", "[BC]","[BD]","[BE]","[BF]",
    "[C0]","[C1]","[C2]","[C3]", "[C4]","[C5]","[C6]","[C7]",
    "[C8]","[C9]","[CA]","[CB]", "[CC]","[CD]","[CE]","[CF]",
    "[D0]","[D1]","[D2]","[D3]", "[D4]","[D5]","[D6]","[D7]",
    "[D8]","[D9]","[DA]","[FUL]","[DC]","[DD]","[DE]","[DF]", //FUL: E500:DB,1600:7F
    "[E0]","[E1]","[E2]", "[pi]","[E4]","[E5]","[E6]","[E7]",
    "[E8]","[E9]","[EA]","[EB]", "[EC]","[ED]","[EE]","[EF]",
    "[F0]","[F1]","[F2]","[F3]", "[F4]","[F5]","[F6]","[F7]",
    "[F8]","[F9]","[FA]","[SQR]","[FC]","[FD]","[FUL]","[INS]",
};
/*template*/
//static char* Code2asc[] = {
//    "[00]","[01]","[02]","[03]","[04]","[05]","[06]","[07]",
//    "[08]","[09]","[0A]","[0B]","[0C]","[0D]","[0E]","[0F]",
//    "[10]","[11]","[12]","[13]","[14]","[15]","[16]","[17]",
//    "[18]","[19]","[1A]","[1B]","[1C]","[1D]","[1E]","[1F]",
//    " ","!","\"","#","$" ,"%","&","'",    "(",")","*" ,"+","," ,"-",".","/",
//    "0","1","2" ,"3","4" ,"5","6","7",    "8","9",":" ,";","<" ,"=",">","?",
//    "@","A","B" ,"C","D" ,"E","F","G",    "H","I","J" ,"K","L" ,"M","N","O",
//    "P","Q","R" ,"S","T" ,"U","V","W",    "X","Y","Z" ,"[","\\","]","^","_",
//    "`","a","b" ,"c","d" ,"e","f","g",    "h","i","j" ,"k","l" ,"m","n","o",
//    "p","q","r" ,"s","t" ,"u","v","w",    "x","y","z" ,"{","|" ,"}","~","[7F]",
//    "[80]","[81]","[82]","[83]","[84]","[85]","[86]","[87]",
//    "[88]","[89]","[8A]","[8B]","[8C]","[8D]","[8E]","[8F]",
//    "[90]","[91]","[92]","[93]","[94]","[95]","[96]","[97]",
//    "[98]","[99]","[9A]","[9B]","[9C]","[9D]","[9E]","[9F]",
//    "[A0]","[A1]","[A2]","[A3]","[A4]","[A5]","[A6]","[A7]",
//    "[A8]","[A9]","[AA]","[AB]","[AC]","[AD]","[AE]","[AF]",
//    "[B0]","[B1]","[B2]","[B3]","[B4]","[B5]","[B6]","[B7]",
//    "[B8]","[B9]","[BA]","[BB]","[BC]","[BD]","[BE]","[BF]",
//    "[C0]","[C1]","[C2]","[C3]","[C4]","[C5]","[C6]","[C7]",
//    "[C8]","[C9]","[CA]","[CB]","[CC]","[CD]","[CE]","[CF]",
//    "[D0]","[D1]","[D2]","[D3]","[D4]","[D5]","[D6]","[D7]",
//    "[D8]","[D9]","[DA]","[DB]","[DC]","[DD]","[DE]","[DF]",
//    "[E0]","[E1]","[E2]","[E3]","[E4]","[E5]","[E6]","[E7]",
//    "[E8]","[E9]","[EA]","[EB]","[EC]","[ED]","[EE]","[EF]",
//    "[F0]","[F1]","[F2]","[F3]","[F4]","[F5]","[F6]","[F7]",
//    "[F8]","[F9]","[FA]","[FB]","[FC]","[FD]","[FE]","[FF]",
//};

/* befehl is valid shortcut for fullcmd ?*/
bool isShrtC( char *befehl, const char *shortcmd /* shortest possible command */,
              char *pDotB,
              char *tokenstr, const char *fullcmd )
{
    char *pDotS = NULL ;
    int posS = 0 ;
    int posB = pDotB - befehl ;

    if ( posB > 0 && (uint) posB < strlen(fullcmd) && !strncmp( befehl, fullcmd, posB)) {
        pDotS = strrchr (shortcmd, '.') ;
        if (pDotS != NULL) posS = pDotS - shortcmd ;
        if ( posS > 0 && !strncmp( befehl, shortcmd, posS)) {
            strcpy (tokenstr, fullcmd) ;
            return (true) ;
        }
        else return(false) ;
    }
    else return(false) ;
}

/* is a token of BASIC intermediate code,
   used chars A to Z and $#. and see IsChar4Cmd */
uint istoken( char *befehl )
{
   char  tokenstr[cLC] = "";
   char* pDot = NULL;
   uint  ii;

   if (strlen(befehl)== 0) return (0);
   pDot = strrchr (befehl, '.') ;

   /* Remaining strings of the preprocessor, upper cases */
   if (      !strcmp( befehl, "[PI]" ) )  strcpy (tokenstr, "PI") ;
   else if ( !strcmp( befehl, "[SQR]" ) ) strcpy (tokenstr, "SQR") ;

   else if (shortcuts && pDot != NULL) {
    if (      !strcmp( befehl, "AB." ) )  strcpy (tokenstr, "ABS") ;
    else if ( !strcmp( befehl, "AC." ) )  strcpy (tokenstr, "ACS") ;
    else if ( !strcmp( befehl, "AE." ) )  strcpy (tokenstr, "AER") ;
    else if ( !strcmp( befehl, "AN." ) )  strcpy (tokenstr, "AND") ;
    else if ( !strcmp( befehl, "AS." ) )  strcpy (tokenstr, "ASC") ;
    else if ( !strcmp( befehl, "A." ) ) {
            if  (ident==IDENT_EXT_BAS ||
                     pcgrpId == GRP_E  )  strcpy (tokenstr, "ASC") ;
            else if (pcgrpId == GRP_G)    strcpy (tokenstr, "ABS") ;
            else                          strcpy (tokenstr, "AREAD") ;
    }
    else if ( isShrtC( befehl, "AR."     , pDot , tokenstr, "AREAD" ) ) ;
    else if ( !strcmp( befehl, "ARU." ) ) strcpy (tokenstr, "ARUN") ;
    else if ( !strcmp( befehl, "AT." ) )  strcpy (tokenstr, "ATN") ;
    else if ( isShrtC( befehl, "AU."     , pDot , tokenstr, "AUTOGOTO" ) ) ;
    else if ( isShrtC( befehl, "B."      , pDot , tokenstr, "BEEP" ) ) ;
    else if ( isShrtC( befehl, "BA."     , pDot , tokenstr, "BASIC" ) ) ;
    else if ( isShrtC( befehl, "BLO."    , pDot , tokenstr, "BLOAD" ) ) ;
    else if ( isShrtC( befehl, "BS."     , pDot , tokenstr, "BSAVE" ) ) ;
    else if ( isShrtC( befehl, "C."      , pDot , tokenstr, "CONT" ) ) ;
    else if ( !strcmp( befehl, "CA." ) )  strcpy (tokenstr, "CALL") ;
    else if ( !strcmp( befehl, "CAS." ) ) strcpy (tokenstr, "CASE") ;
    else if ( !strcmp( befehl, "CH." ) )  strcpy (tokenstr, "CHR$") ; // 1262 CHAIN
    else if ( !strcmp( befehl, "CHR." ) ) strcpy (tokenstr, "CHR$") ;
    else if ( !strcmp( befehl, "CHA." ) ) strcpy (tokenstr, "CHAIN") ;
    else if ( !strcmp( befehl, "CHAI." ) )strcpy (tokenstr, "CHAIN") ;
    else if ( isShrtC( befehl, "CI."     , pDot , tokenstr, "CIRCLE" ) ) ;
    else if ( isShrtC( befehl, "CL."     , pDot , tokenstr, "CLEAR" ) ) ;
    else if ( !strcmp( befehl, "CLO." ) ) strcpy (tokenstr, "CLOAD") ;
    else if ( !strcmp( befehl, "CLOA." ) )strcpy (tokenstr, "CLOAD") ;
    else if ( !strcmp( befehl, "CLOS." ) )strcpy (tokenstr, "CLOSE") ;
    else if ( !strcmp( befehl, "COL." ) ) strcpy (tokenstr, "COLOR") ;
    else if ( !strcmp( befehl, "COLO." ) )strcpy (tokenstr, "COLOR") ;
    else if ( isShrtC( befehl, "CONS."   , pDot , tokenstr, "CONSOLE" ) ) ;
    else if ( !strcmp( befehl, "COP." ) ) strcpy (tokenstr, "COPY") ;
    else if ( isShrtC( befehl, "CR."     , pDot , tokenstr, "CROTATE" ) ) ;
    else if ( isShrtC( befehl, "CS."     , pDot , tokenstr, "CSAVE" ) ) ;
    else if ( !strcmp( befehl, "CSI." ) ) strcpy (tokenstr, "CSIZE") ;
    else if ( isShrtC( befehl, "CU."     , pDot , tokenstr, "CURSOR" ) ) ;
    else if ( !strcmp( befehl, "D." ) )   strcpy (tokenstr, "DIM") ;
    else if ( !strcmp( befehl, "DI." ) )  strcpy (tokenstr, "DIM") ;
    else if ( !strcmp( befehl, "DA." ) )  strcpy (tokenstr, "DATA") ;
    else if ( !strcmp( befehl, "DAT." ) ) strcpy (tokenstr, "DATA") ;
    else if ( isShrtC( befehl, "DE."     , pDot , tokenstr, "DEGREE" ) ) ;
    else if ( isShrtC( befehl, "DEF."    , pDot , tokenstr, "DEFDBL" ) ) ;
    else if ( isShrtC( befehl, "DEFA."   , pDot , tokenstr, "DEFAULT" ) ) ;
    else if ( isShrtC( befehl, "DEFS."   , pDot , tokenstr, "DEFSNG" ) ) ;
    else if ( isShrtC( befehl, "DEL."    , pDot , tokenstr, "DELETE" ) ) ;
    else if ( !strcmp( befehl, "DM." ) ) {
                         if (pcId >= 850 && pcId <= 853)
                                          strcpy (tokenstr, "DMS$") ;
                         else             strcpy (tokenstr, "DMS") ;
    }
    else if ( !strcmp( befehl, "DS." ) )  strcpy (tokenstr, "DSKF") ;
    else if ( !strcmp( befehl, "DSK." ) ) strcpy (tokenstr, "DSKF") ;
    else if ( !strcmp( befehl, "E." ) )   strcpy (tokenstr, "END") ;
    else if ( !strcmp( befehl, "EN." ) )  strcpy (tokenstr, "END") ;
    else if ( !strcmp( befehl, "EL." ) )  strcpy (tokenstr, "ELSE") ;
    else if ( !strcmp( befehl, "ENDI." ) )strcpy (tokenstr, "ENDIF") ;
    else if ( isShrtC( befehl, "ENDS."   , pDot , tokenstr, "ENDSWITCH" ) ) ;
    else if ( !strcmp( befehl, "EO." ) )  strcpy (tokenstr, "EOF") ;
    else if ( isShrtC( befehl, "ER."     , pDot , tokenstr, "ERASE" ) ) ;
    else if ( !strcmp( befehl, "ERR." ) ) strcpy (tokenstr, "ERROR") ;
    else if ( !strcmp( befehl, "EX." ) )  strcpy (tokenstr, "EXP") ;
    else if ( !strcmp( befehl, "F." ) )   strcpy (tokenstr, "FOR") ;
    else if ( !strcmp( befehl, "FO." ) )  strcpy (tokenstr, "FOR") ;
    else if ( isShrtC( befehl, "FI."     , pDot , tokenstr, "FILES" ) ) ;
    else if ( !strcmp( befehl, "FR." ) )  strcpy (tokenstr, "FRE") ;
    else if ( isShrtC( befehl, "G."      , pDot , tokenstr, "GOTO" ) ) ;
    else if ( isShrtC( befehl, "GC."     , pDot , tokenstr, "GCURSOR" ) ) ;
    else if ( isShrtC( befehl, "GL."     , pDot , tokenstr, "GLCURSOR" ) ) ;
    else if ( !strcmp( befehl, "GOS." ) ) strcpy (tokenstr, "GOSUB") ;
    else if ( !strcmp( befehl, "GOSU." ) )strcpy (tokenstr, "GOSUB") ;
    else if ( isShrtC( befehl, "GP."     , pDot , tokenstr, "GPRINT" ) ) ;
    else if ( !strcmp( befehl, "GR." ) )  strcpy (tokenstr, "GRAD") ;
    else if ( !strcmp( befehl, "GRA." ) ) strcpy (tokenstr, "GRAD") ;
    else if ( !strcmp( befehl, "GRAP." ) )strcpy (tokenstr, "GRAPH") ;
    else if ( !strcmp( befehl, "H.") || !strcmp( befehl, "HE.") ) {
                         if (pcId >= 850 && pcId <= 853)
                                          strcpy (tokenstr, "HEX$") ;
                         else             strcpy (tokenstr, "HEX") ;
    }
    else if ( isShrtC( befehl, "H.$"     , pDot , tokenstr, "HEX$" ) ) ;
    else if ( isShrtC( befehl, "I."      , pDot , tokenstr, "INPUT" ) ) ;
    else if ( !strcmp( befehl, "INI." ) ) strcpy (tokenstr, "INIT") ;
    else if ( isShrtC( befehl, "K."      , pDot , tokenstr, "KILL" ) ) ;
    else if ( !strcmp( befehl, "KE." ) )  strcpy (tokenstr, "KEY") ;
    else if ( isShrtC( befehl, "INK."    , pDot , tokenstr, "INKEY$" ) ) ;
    else if ( isShrtC( befehl, "L."      , pDot , tokenstr, "LIST" ) ) ;
    else if ( !strcmp( befehl, "LE." ) )  strcpy (tokenstr, "LET") ;
    else if ( !strcmp( befehl, "LEF." ) ) strcpy (tokenstr, "LEFT$") ;
    else if ( isShrtC( befehl, "LF."     , pDot , tokenstr, "LFILES" ) ) ;
    else if ( isShrtC( befehl, "LL."     , pDot , tokenstr, "LLIST" ) ) ;
    else if ( !strcmp( befehl, "LLIN." ) )strcpy (tokenstr, "LLINE") ;
    else if ( !strcmp( befehl, "LIN." ) ) strcpy (tokenstr, "LINE") ;
    else if ( isShrtC( befehl, "LO."     , pDot , tokenstr, "LOCATE" ) ) ;
    else if ( !strcmp( befehl, "LOA." ) ) strcpy (tokenstr, "LOAD") ;
    else if ( isShrtC( befehl, "LP."     , pDot , tokenstr, "LPRINT" ) ) ;
    else if ( !strcmp( befehl, "LS." ) )  strcpy (tokenstr, "LSET") ;
    else if ( isShrtC( befehl, "LT."     , pDot , tokenstr, "LTEXT" ) ) ;
    else if ( !strcmp( befehl, "M." ) )   strcpy (tokenstr, "MEM") ;
    else if ( !strcmp( befehl, "M.$" ) )  strcpy (tokenstr, "MEM$") ;//Ext 'MEM $', not token
    else if ( !strcmp( befehl, "ME." ) ) {
                    if (pcgrpId == GRP_E) strcpy (tokenstr, "MEM$") ;//E500
                    else                  strcpy (tokenstr, "MEM") ;
    }
    else if ( !strcmp( befehl, "MD." ) )  strcpy (tokenstr, "MDF") ;
    else if ( !strcmp( befehl, "MER." ) ) strcpy (tokenstr, "MERGE") ;
    else if ( !strcmp( befehl, "MERG." ) )strcpy (tokenstr, "MERGE") ;
    else if ( isShrtC( befehl, "MI."     , pDot , tokenstr, "MID$" ) ) ;
    else if ( !strcmp( befehl, "MO." ) )  strcpy (tokenstr, "MON") ;
    else if ( isShrtC( befehl, "N."      , pDot , tokenstr, "NEXT" ) ) ;
    else if ( !strcmp( befehl, "NA." ) )  strcpy (tokenstr, "NAME") ;
    else if ( !strcmp( befehl, "NO." ) )  strcpy (tokenstr, "NOT") ;
    else if ( !strcmp( befehl, "O." ) )   strcpy (tokenstr, "ON") ;
    else if ( !strcmp( befehl, "OP." ) )  strcpy (tokenstr, "OPEN") ;
    else if ( !strcmp( befehl, "OP.$" ) ) strcpy (tokenstr, "OPEN$") ;
    else if ( !strcmp( befehl, "OU." ) )  strcpy (tokenstr, "OUT") ;
    else if ( isShrtC( befehl, "P."      , pDot , tokenstr, "PRINT" ) ) ;
    else if ( !strcmp( befehl, "PA." ) )  strcpy (tokenstr, "PASS") ;
    else if ( !strcmp( befehl, "PAS." ) ) strcpy (tokenstr, "PASS") ;
    else if ( !strcmp( befehl, "PAU." ) ) strcpy (tokenstr, "PAUSE") ;
    else if ( !strcmp( befehl, "PAUS." ) )strcpy (tokenstr, "PAUSE") ;
    else if ( !strcmp( befehl, "PAI." ) ) strcpy (tokenstr, "PAINT") ;
    else if ( !strcmp( befehl, "PE." ) )  strcpy (tokenstr, "PEEK") ;
    else if ( isShrtC( befehl, "PI."     , pDot , tokenstr, "PIOSET" ) ) ;
    else if ( !strcmp( befehl, "PIOG." ) )strcpy (tokenstr, "PIOGET") ;
    else if ( !strcmp( befehl, "PIOP." ) )strcpy (tokenstr, "PIOPUT") ;
    else if ( !strcmp( befehl, "POI." ) ) strcpy (tokenstr, "POINT") ;
//  else if ( !strcmp( befehl, "PO." ) )  strcpy (tokenstr, "POKE") ; // PC-1251/140x POL
    else if ( !strcmp( befehl, "POK." ) ) strcpy (tokenstr, "POKE") ;
    else if ( isShrtC( befehl, "PRE."    , pDot , tokenstr, "PRESET" ) ) ;
    else if ( !strcmp( befehl, "PS." ) )  strcpy (tokenstr, "PSET") ;
    else if ( !strcmp( befehl, "R." ) )   strcpy (tokenstr, "RUN") ;
    else if ( !strcmp( befehl, "RU." ) )  strcpy (tokenstr, "RUN") ;
    else if ( isShrtC( befehl, "RA."     , pDot , tokenstr, "RANDOM" ) ) ;
    else if ( isShrtC( befehl, "RAD."    , pDot , tokenstr, "RADIAN" ) ) ;
    else if ( isShrtC( befehl, "RE."     , pDot , tokenstr, "RETURN" ) ) ;
    else if ( !strcmp( befehl, "REA." ) ) strcpy (tokenstr, "READ") ;
    else if ( !strcmp( befehl, "REN." ) ) strcpy (tokenstr, "RENUM") ;
    else if ( isShrtC( befehl, "REP."    , pDot , tokenstr, "REPEAT" ) ) ;
    else if ( isShrtC( befehl, "RES."    , pDot , tokenstr, "RESTORE" ) ) ;
    else if ( !strcmp( befehl, "RESU." ) )strcpy (tokenstr, "RESUME") ;
    else if ( isShrtC( befehl, "RI."     , pDot , tokenstr, "RIGHT$" ) ) ;
    else if ( isShrtC( befehl, "RL."     , pDot , tokenstr, "RLINE" ) ) ;
    else if ( !strcmp( befehl, "RN." ) )  strcpy (tokenstr, "RND") ;
    else if ( !strcmp( befehl, "RS." ) )  strcpy (tokenstr, "RSET") ;
    else if ( isShrtC( befehl, "S."      , pDot , tokenstr, "STOP" ) ) ;
    else if ( !strcmp( befehl, "SA." ) )  strcpy (tokenstr, "SAVE") ;
    else if ( !strcmp( befehl, "SE." ) )  strcpy (tokenstr, "SET") ;
    else if ( !strcmp( befehl, "SG." ) )  strcpy (tokenstr, "SGN") ;
    else if ( !strcmp( befehl, "SI." ) )  strcpy (tokenstr, "SIN") ;
    else if ( isShrtC( befehl, "SO."     , pDot , tokenstr, "SORGN" ) ) ;
    else if ( !strcmp( befehl, "SQ." ) )  strcpy (tokenstr, "SQR") ;
    else if ( !strcmp( befehl, "STE." ) ) strcpy (tokenstr, "STEP") ;
    else if ( !strcmp( befehl, "STR." ) ) strcpy (tokenstr, "STR$") ;
    else if ( isShrtC( befehl, "SW."     , pDot , tokenstr, "SWITCH" ) ) ;
    else if ( isShrtC( befehl, "T."      , pDot , tokenstr, "THEN" ) ) ;
    else if ( !strcmp( befehl, "TA." ) )  strcpy (tokenstr, "TAN") ;
    else if ( !strcmp( befehl, "TE." ) )  strcpy (tokenstr, "TEXT") ;
    else if ( !strcmp( befehl, "TR." ) )  strcpy (tokenstr, "TRON") ;
    else if ( !strcmp( befehl, "TROF." ) )strcpy (tokenstr, "TROFF") ;
    else if ( isShrtC( befehl, "U."      , pDot , tokenstr, "USING" ) ) ;
    else if ( isShrtC( befehl, "UN."     , pDot , tokenstr, "UNTIL" ) ) ;
    else if ( !strcmp( befehl, "V." ) )   strcpy (tokenstr, "VAL") ;
    else if ( !strcmp( befehl, "VD." ) )  strcpy (tokenstr, "VDEG") ;
    else if ( isShrtC( befehl, "W."      , pDot , tokenstr, "WAIT" ) ) ;
    else if ( isShrtC( befehl, "WH."     , pDot , tokenstr, "WHILE" ) ) ;
    else if ( !strcmp( befehl, "WE." ) )  strcpy (tokenstr, "WEND") ;
    else if ( !strcmp( befehl, "X." ) )   strcpy (tokenstr, "XOR") ;
    else strncpy (tokenstr, befehl, cLC-1) ;
  }
  else strncpy (tokenstr, befehl, cLC-1) ;

   /* Check external token keywords */
   for ( ii = 0 ; ii < key_cnt ; ++ii ) {
	if ( !strcmp( tokenstr, keyword[ii] ) )    	return keyval[ii];
   }
   if (KeysFromFileOnly) return 0 ;

/* NOTE (All#3#): Tokeniser: whenever you add a token, you should also do this in Wav2bin
   in order to restore the symmetry of Wav2bin to Bas2img with regard to BASIC tokens */

  if ( ident == IDENT_OLD_BAS )
  {
	if ( !strcmp( tokenstr, ">=" ) )    		return 0x82;
	if ( !strcmp( tokenstr, "<=" ) )    		return 0x83;
	if ( !strcmp( tokenstr, "<>" ) )    		return 0x84;//above can be done by the preprocessor
	if ( !strcmp( tokenstr, "AREAD" ) )    		return 0xDC;
	if ( !strcmp( tokenstr, "ABS" ) )    		return 0xAA;
	if ( !strcmp( tokenstr, "ACS" ) )    		return 0xA4;
	if ( !strcmp( tokenstr, "ASN" ) )    		return 0xA3;
	if ( !strcmp( tokenstr, "ATN" ) )    		return 0xA5;
	if ( !strcmp( tokenstr, "BEEP" ) )    		return 0xDB;
	if ( !strcmp( tokenstr, "CHAIN" ) )    		return 0xD9;
	if ( !strcmp( tokenstr, "CLEAR" ) )    		return 0xC5;
	if ( !strcmp( tokenstr, "CLOAD" ) )    		return 0xB7;
	if ( !strcmp( tokenstr, "CLOSE" ) )    		return 0x9D;
	if ( !strcmp( tokenstr, "CONT" ) )    		return 0xB4;
	if ( !strcmp( tokenstr, "COS" ) )    		return 0xA1;
	if ( !strcmp( tokenstr, "CSAVE" ) )    		return 0xB6;
	if ( !strcmp( tokenstr, "DEBUG" ) )    		return 0xB5;
	if ( !strcmp( tokenstr, "DEGREE" ) )    	return 0xC4;
	if ( !strcmp( tokenstr, "DEG" ) )    		return 0xAC;
	if ( !strcmp( tokenstr, "DMS" ) )    		return 0xAD;
	if ( !strcmp( tokenstr, "END" ) )    		return 0xD4;
	if ( !strcmp( tokenstr, "EXP" ) )    		return 0xA6;
	if ( !strcmp( tokenstr, "FOR" ) )    		return 0xD1;
	if ( !strcmp( tokenstr, "GOSUB" ) )    		return 0xD8;
	if ( !strcmp( tokenstr, "GOTO" ) )   		return 0xD7;
	if ( !strcmp( tokenstr, "GRAD" ) )    		return 0xC0;
	if ( !strcmp( tokenstr, "IF" ) )    		return 0xD0;
	if ( !strcmp( tokenstr, "INPUT" ) )    		return 0xC2;
	if ( !strcmp( tokenstr, "INT" ) )    		return 0xA9;
	if ( !strcmp( tokenstr, "LN" ) )    		return 0xA7;
	if ( !strcmp( tokenstr, "LET" ) )    		return 0xD2;
	if ( !strcmp( tokenstr, "LIST" ) )    		return 0xB3;
	if ( !strcmp( tokenstr, "LOG" ) )    		return 0xA8;
	if ( !strcmp( tokenstr, "MEM" ) )    		return 0xB2;
	if ( !strcmp( tokenstr, "NEXT" ) )    		return 0xD5;
	if ( !strcmp( tokenstr, "NEW" ) )    		return 0xB1;
	if ( !strcmp( tokenstr, "OPEN" ) )    		return 0x9C;
	if ( !strcmp( tokenstr, "PAUSE" ) )    		return 0xDA;
	if ( !strcmp( tokenstr, "PRINT" ) )    		return 0xC1;
	if ( !strcmp( tokenstr, "RADIAN" ) )    	return 0xC3;
	if ( !strcmp( tokenstr, "REM" ) )    		return 0xD3;
	if ( !strcmp( tokenstr, "RETURN" ) )    	return 0xDE;
	if ( !strcmp( tokenstr, "RUN" ) )    		return 0xB0;
	if ( !strcmp( tokenstr, "SETCOM" ) )    	return 0x9B;
	if ( !strcmp( tokenstr, "SGN" ) )    		return 0xAB;
	if ( !strcmp( tokenstr, "SIN" ) )    		return 0xA0;
	if ( !strcmp( tokenstr, "STEP" ) )    		return 0x91;
	if ( !strcmp( tokenstr, "STOP" ) )    		return 0xD6;
	if ( !strcmp( tokenstr, "TAN" ) )    		return 0xA2;
	if ( !strcmp( tokenstr, "THEN" ) )    		return 0x92;
	if ( !strcmp( tokenstr, "TO" ) )    		return 0x90;
	if ( !strcmp( tokenstr, "USING" ) )    		return 0xDD;

    if ( pcId < 1210 || 1212 < pcId ) {
        if ( !strcmp( tokenstr, "AND" ) )    		return 0x81;
        if ( !strcmp( tokenstr, "ASC" ) )    		return 0x7D;
        if ( !strcmp( tokenstr, "CALL" ) )    		return 0xC9;
        if ( !strcmp( tokenstr, "CHR$" ) )    		return 0x88;
        if ( !strcmp( tokenstr, "CLOSE" ) )      	return 0x9D;
        if ( !strcmp( tokenstr, "COM$" ) )    		return 0x89;
        if ( !strcmp( tokenstr, "DATA" ) )    		return 0xCB;
        if ( !strcmp( tokenstr, "DIM" ) )    		return 0xCA;
        if ( !strcmp( tokenstr, "ERROR" ) )    		return 0x96;
        if ( !strcmp( tokenstr, "INKEY$" ) )    	return 0x8A;
        if ( !strcmp( tokenstr, "INSTAT" ) )    	return 0xBF;
        if ( !strcmp( tokenstr, "KEY" ) )    		return 0x99;
        if ( !strcmp( tokenstr, "LEFT$" ) )    		return 0x8C;
        if ( !strcmp( tokenstr, "LEN" ) )    		return 0x7F;
        if ( !strcmp( tokenstr, "LLIST" ) )    		return 0xBC;
        if ( !strcmp( tokenstr, "LPRINT" ) )    	return 0x9F;
        if ( !strcmp( tokenstr, "MERGE" ) )    		return 0xB8;
        if ( !strcmp( tokenstr, "MID$" ) )    		return 0x8E;
        if ( !strcmp( tokenstr, "NOT" ) )    		return 0x86;
        if ( !strcmp( tokenstr, "OFF" ) )    		return 0xCD;
        if ( !strcmp( tokenstr, "ON" ) )    		return 0xCC;
        if ( !strcmp( tokenstr, "OPEN" ) )      	return 0x9C;
        if ( !strcmp( tokenstr, "OR" ) )    		return 0x85;
        if ( !strcmp( tokenstr, "OUTSTAT" ) )    	return 0xBE;
        if ( !strcmp( tokenstr, "PASS" ) )    		return 0xBB;
        if ( !strcmp( tokenstr, "PEEK" ) )    		return 0xAF;
        if ( !strcmp( tokenstr, "PI" ) )    		return 0xBD;
        if ( !strcmp( tokenstr, "POKE" ) )    		return 0xCE;
        if ( !strcmp( tokenstr, "RANDOM" ) )    	return 0x93;
        if ( !strcmp( tokenstr, "READ" ) )    		return 0xCF;
        if ( !strcmp( tokenstr, "RESTORE" ) )    	return 0xDF;
        if ( !strcmp( tokenstr, "RIGHT$" ) )    	return 0x8D;
        if ( !strcmp( tokenstr, "RND" ) )    		return 0xAE;
        if ( !strcmp( tokenstr, "ROM" ) )    		return 0x9E;
        if ( !strcmp( tokenstr, "SETCOM" ) )    	return 0x9B;
        if ( !strcmp( tokenstr, "SQR" ) )    		return 0x87;
        if ( !strcmp( tokenstr, "STR$" ) )    		return 0x8B;
        if ( !strcmp( tokenstr, "TROFF" ) )    		return 0xBA;
        if ( !strcmp( tokenstr, "TRON" ) )    		return 0xB9;
        if ( !strcmp( tokenstr, "VAL" ) )           return 0xFE; /* placeholder before conv_asc2old */
        if ( !strcmp( tokenstr, "WAIT" ) )  		return 0x95;
	} // End if PC-121x
	return 0;
  } // End if OLD_BAS
  else if ( ident == IDENT_NEW_BAS ) {
    if (pcId == 1421) {
        if ( !strcmp( tokenstr, "ACC" ) )  		return 0xB8;
        if ( !strcmp( tokenstr, "ARMT" ) ) 		return 0xB9;
        if ( !strcmp( tokenstr, "COMP" ) )  	return 0xBA;
        if ( !strcmp( tokenstr, "MDF" ) )  		return 0xBB;
        if ( !strcmp( tokenstr, "EFF" ) )  		return 0xBC;
        if ( !strcmp( tokenstr, "APR" ) )  		return 0xBD;
        if ( !strcmp( tokenstr, "DAYSII" ) )  	return 0xBF;
        if ( !strcmp( tokenstr, "DAYSI" ) )  	return 0xBE;
        if ( !strcmp( tokenstr, "BGNON" ) )  	return 0xCE;
        if ( !strcmp( tokenstr, "BGNOFF" ) )  	return 0xCF;
        if ( !strcmp( tokenstr, "ERASE" ) )  	return 0xE5;
        if ( !strcmp( tokenstr, "FIN" ) )   	return 0xE6;
        if ( !strcmp( tokenstr, "CST" ) )  	    return 0xEA;
        if ( !strcmp( tokenstr, "SEL" ) )  	    return 0xEB;
        if ( !strcmp( tokenstr, "MAR" ) )  	    return 0xEC;
        if ( !strcmp( tokenstr, "MU" ) )  	    return 0xED;
        if ( !strcmp( tokenstr, "PV" ) )  	    return 0xEE;
        if ( !strcmp( tokenstr, "FV" ) )  	    return 0xEF;
        if ( !strcmp( tokenstr, "PMT" ) )  	    return 0xF0;
        if ( !strcmp( tokenstr, "NPV" ) )  	    return 0xF1;
        if ( !strcmp( tokenstr, "IRR" ) )  	    return 0xF2;
        if ( !strcmp( tokenstr, "PRN" ) )  	    return 0xF3;
        if ( !strcmp( tokenstr, "INTE" ) )  	return 0xF4;
        if ( !strcmp( tokenstr, "BAL" ) )  	    return 0xF5;
        if ( !strcmp( tokenstr, "SPRN" ) ) 	    return 0xF6;
        if ( !strcmp( tokenstr, "SINTE" ) )     return 0xF7;
        if ( !strcmp( tokenstr, "NI" ) )  	    return 0xF8;
        if ( !strcmp( tokenstr, "CFI" ) )  	    return 0xF9;
    }
    if (pcId == 1401) {
        if ( !strcmp( tokenstr, "DEC" ) )     	return 0x84; // PC-1401, 1.version
        if ( !strcmp( tokenstr, "FAC" ) )     	return 0x90; // PC-1401, 1.version
    }
	if ( !strcmp( tokenstr, "ABS" ) )  		return 0x99;
	if ( !strcmp( tokenstr, "ACS" ) )  		return 0x9E;
	if ( !strcmp( tokenstr, "AHC" ) )  		return 0x8E;
	if ( !strcmp( tokenstr, "AHS" ) )  		return 0x8D;
	if ( !strcmp( tokenstr, "AHT" ) )  		return 0x8F;
	if ( !strcmp( tokenstr, "AND" ) )  		return 0xA1;
	if ( !strcmp( tokenstr, "AREAD" ) )  	return 0xE1;
	if ( !strcmp( tokenstr, "ASC" ) )  		return 0xA4;
	if ( !strcmp( tokenstr, "ASN" ) )  		return 0x9D;
	if ( !strcmp( tokenstr, "ATN" ) )  		return 0x9F;
	if ( !strcmp( tokenstr, "BASIC" ) )  	return 0xEC;
	if ( !strcmp( tokenstr, "BEEP" ) )  	return 0xC4;
	if ( !strcmp( tokenstr, "CALL" ) )  	return 0xCC;
	if ( !strcmp( tokenstr, "CHAIN" ) )  	return 0xE5;
	if ( !strcmp( tokenstr, "CHR$" ) )  	return 0xA8;
	if ( !strcmp( tokenstr, "CLEAR" ) )  	return 0xC9;
	if ( !strcmp( tokenstr, "CLOAD" ) )  	return 0xB7;
	if ( !strcmp( tokenstr, "CLOSE" ) )  	return 0xBC;
	if ( !strcmp( tokenstr, "CLS" ) )  		return 0xCE;
	if ( !strcmp( tokenstr, "CONSOLE" ) )  	return 0xBF;
	if ( !strcmp( tokenstr, "CONT" ) )  	return 0xB2;
	if ( !strcmp( tokenstr, "COS" ) )  		return 0x96;
	if ( !strcmp( tokenstr, "CSAVE" ) )  	return 0xB6;
	if ( !strcmp( tokenstr, "CUR" ) )  		return 0x89;
	if ( !strcmp( tokenstr, "CURSOR" ) )  	return 0xCF;
	if ( !strcmp( tokenstr, "DATA" ) )  	return 0xDC;
	if ( !strcmp( tokenstr, "DECI" ) )  	return 0x84;
	if ( !strcmp( tokenstr, "DEG" ) )  		return 0x9B;
	if ( !strcmp( tokenstr, "DEGREE" ) )  	return 0xC1;
	if ( !strcmp( tokenstr, "DIM" ) )  		return 0xCB;
	if ( !strcmp( tokenstr, "DMS" ) )  		return 0x9C;
	if ( !strcmp( tokenstr, "END" ) )  		return 0xD8;
	if ( !strcmp( tokenstr, "EQU#" ) )  	return 0xB9;
	if ( !strcmp( tokenstr, "EXP" ) )  		return 0x93;
	if ( !strcmp( tokenstr, "FACT" ) )  	return 0x90;
	if ( !strcmp( tokenstr, "FOR" ) )  		return 0xD5;
	if ( !strcmp( tokenstr, "GCURSOR" ) )  	return 0xE6;
	if ( !strcmp( tokenstr, "GOSUB" ) )  	return 0xE0;
	if ( !strcmp( tokenstr, "GOTO" ) )  	return 0xC6;
	if ( !strcmp( tokenstr, "GPRINT" ) )  	return 0xE7;
	if ( !strcmp( tokenstr, "GRAD" ) )  	return 0xC3;
	if ( !strcmp( tokenstr, "HCS" ) )  		return 0x8B;
	if ( !strcmp( tokenstr, "HEX" ) )  		return 0x85;
	if ( !strcmp( tokenstr, "HSN" ) )  		return 0x8A;
	if ( !strcmp( tokenstr, "HTN" ) )  		return 0x8C;
	if ( !strcmp( tokenstr, "IF" ) )  		return 0xD4;
	if ( !strcmp( tokenstr, "INKEY$" ) )  	return 0xAD;
	if ( !strcmp( tokenstr, "INPUT" ) )  	return 0xDF;
	if ( !strcmp( tokenstr, "INT" ) )  		return 0x98;
	if ( !strcmp( tokenstr, "LEFT$" ) )  	return 0xAB;
	if ( !strcmp( tokenstr, "LEN" ) )  		return 0xA6;
	if ( !strcmp( tokenstr, "LET" ) )  		return 0xD6;
	if ( !strcmp( tokenstr, "LINE" ) )  	return 0xE8;
	if ( !strcmp( tokenstr, "LIST" ) )  	return 0xB4;
	if ( !strcmp( tokenstr, "LLIST" ) )  	return 0xB5;
	if ( !strcmp( tokenstr, "LN" ) )  		return 0x91;
	if ( !strcmp( tokenstr, "LOAD" ) )  	return 0xBE;
	if ( !strcmp( tokenstr, "LOG" ) )  		return 0x92;
	if ( !strcmp( tokenstr, "LPRINT" ) )  	return 0xE2;
	if ( !strcmp( tokenstr, "MDF" ) )  		return 0x80;
	if ( !strcmp( tokenstr, "MEM" ) )  		return 0xAF;
	if ( !strcmp( tokenstr, "MEM#" ) )  	return 0xBA;
	if ( !strcmp( tokenstr, "MERGE" ) )  	return 0xB8;
	if ( !strcmp( tokenstr, "MID$" ) )  	return 0xAA;
	if ( !strcmp( tokenstr, "NEW" ) )  		return 0xB1;
	if ( !strcmp( tokenstr, "NEXT" ) )  	return 0xD9;
	if ( !strcmp( tokenstr, "NOT" ) )  		return 0xA3;
	if ( !strcmp( tokenstr, "ON" ) )  		return 0xD3;
	if ( !strcmp( tokenstr, "OPEN" ) )  	return 0xBB;
	if ( !strcmp( tokenstr, "OPEN$" ) )  	return 0xEE;
	if ( !strcmp( tokenstr, "OR" ) )  		return 0xA2;
	if ( !strcmp( tokenstr, "PASS" ) )  	return 0xB3;
	if ( !strcmp( tokenstr, "PAUSE" ) )  	return 0xDD;
	if ( !strcmp( tokenstr, "PEEK" ) )  	return 0xA7;
	if ( !strcmp( tokenstr, "PI" ) )  		return 0xAE;
	if ( !strcmp( tokenstr, "POINT" ) )  	return 0xE9;
	if ( !strcmp( tokenstr, "POKE" ) )  	return 0xCD;
	if ( !strcmp( tokenstr, "POL" ) )  		return 0x82;
	if ( !strcmp( tokenstr, "PRESET" ) )  	return 0xEB;
	if ( !strcmp( tokenstr, "PRINT" ) )  	return 0xDE;
	if ( !strcmp( tokenstr, "PSET" ) )  	return 0xEA;
	if ( !strcmp( tokenstr, "RADIAN" ) )  	return 0xC2;
	if ( !strcmp( tokenstr, "RANDOM" ) )  	return 0xC0;
	if ( !strcmp( tokenstr, "RCP" ) )  		return 0x87;
	if ( !strcmp( tokenstr, "READ" ) )  	return 0xDB;
	if ( !strcmp( tokenstr, "REC" ) )  		return 0x81;
	if ( !strcmp( tokenstr, "REM" ) )  		return 0xD7;
	if ( !strcmp( tokenstr, "RESTORE" ) )  	return 0xE4;
	if ( !strcmp( tokenstr, "RETURN" ) )  	return 0xE3;
	if ( !strcmp( tokenstr, "RIGHT$" ) )  	return 0xAC;
	if ( !strcmp( tokenstr, "RND" ) )  		return 0xA0;
	if ( !strcmp( tokenstr, "ROT" ) )  		return 0x83;
	if ( !strcmp( tokenstr, "RUN" ) )  		return 0xB0;
	if ( !strcmp( tokenstr, "SAVE" ) )  	return 0xBD;
	if ( !strcmp( tokenstr, "SGN" ) )  		return 0x9A;
	if ( !strcmp( tokenstr, "SIN" ) )  		return 0x95;
	if ( !strcmp( tokenstr, "SQR" ) )  		return 0x94;
	if ( !strcmp( tokenstr, "SQU" ) )  		return 0x88;
	if ( !strcmp( tokenstr, "STEP" ) )  	return 0xD1;
	if ( !strcmp( tokenstr, "STOP" ) )  	return 0xDA;
	if ( !strcmp( tokenstr, "STR$" ) )  	return 0xA9;
	if ( !strcmp( tokenstr, "TAN" ) )  		return 0x97;
	if ( !strcmp( tokenstr, "TEN" ) )  		return 0x86;
	if ( !strcmp( tokenstr, "TEXT" ) )  	return 0xED;
	if ( !strcmp( tokenstr, "THEN" ) )  	return 0xD2;
	if ( !strcmp( tokenstr, "TO" ) )  		return 0xD0;
	if ( !strcmp( tokenstr, "TROFF" ) )  	return 0xC8;
	if ( !strcmp( tokenstr, "TRON" ) ) 		return 0xC7;
	if ( !strcmp( tokenstr, "USING" ) ) 	return 0xCA;
	if ( !strcmp( tokenstr, "VAL" ) ) 		return 0xA5;
	if ( !strcmp( tokenstr, "WAIT" ) )		return 0xC5;

    /* pcId 1403, 1425 ... 1445, 1460 */
    if (tokenL == 0) {
        if ( !strcmp( tokenstr, "APPEND" ) )  	return 0xEFE1;
        if ( !strcmp( tokenstr, "AS" ) )  	    return 0xEFE2;
        if ( !strcmp( tokenstr, "BDS" ) )  	    return 0xEF8C;
        if ( !strcmp( tokenstr, "BIN" ) )  	    return 0xEF84;
        if ( !strcmp( tokenstr, "COPY" ) )  	return 0xEFB6;
        if ( !strcmp( tokenstr, "CONVERT" ) )  	return 0xEFB7;
        if ( !strcmp( tokenstr, "CSI" ) )  	    return 0xEF5A;
        if ( !strcmp( tokenstr, "COLOR" ) )  	return 0xEFC9;
        if ( !strcmp( tokenstr, "CIRCLE" ) )  	return 0xEFCC;
        if ( !strcmp( tokenstr, "CROTATE" ) )  	return 0xEFCB;
        if ( !strcmp( tokenstr, "CSIZE" ) )  	return 0xEFC8;
        if ( !strcmp( tokenstr, "DSKF" ) )  	return 0xEF81;
        if ( !strcmp( tokenstr, "DELETE" ) )  	return 0xEFA9;
        if ( !strcmp( tokenstr, "EOF" ) )  	    return 0xEF80;
        if ( !strcmp( tokenstr, "ERASE" ) )  	return 0xEFC0;
        if ( !strcmp( tokenstr, "FILES" ) )  	return 0xEFB0;
        if ( !strcmp( tokenstr, "FDS" ) )  	    return 0xEF9B;
        if ( !strcmp( tokenstr, "GRAPH" ) )  	return 0xEFC6;
        if ( !strcmp( tokenstr, "GLCURSOR" ) )  return 0xEFC4;
        if ( !strcmp( tokenstr, "INIT" ) )  	return 0xEFB2;
        if ( !strcmp( tokenstr, "INP" ) )   	return 0xEF90;
        if ( !strcmp( tokenstr, "KILL" ) )  	return 0xEFB3;
        if ( !strcmp( tokenstr, "LOF" ) )  	    return 0xEF82;
        if ( !strcmp( tokenstr, "LOC" ) )  	    return 0xEF83;
        if ( !strcmp( tokenstr, "LFILES" ) )  	return 0xEFB1;
        if ( !strcmp( tokenstr, "LTEXT" ) )  	return 0xEFC5;
        if ( !strcmp( tokenstr, "LF" ) )  	    return 0xEFC7;
        if ( !strcmp( tokenstr, "LLINE" ) )  	return 0xEFC2;
        if ( !strcmp( tokenstr, "NAME" ) )  	return 0xEFB4;
        if ( !strcmp( tokenstr, "NCR" ) )  	    return 0xEF86;
        if ( !strcmp( tokenstr, "NPR" ) )  	    return 0xEF87;
        if ( !strcmp( tokenstr, "NDS" ) )  	    return 0xEF98;
        if ( !strcmp( tokenstr, "OUT" ) )   	return 0xEFC1;
        if ( !strcmp( tokenstr, "OUTPUT" ) )    return 0xEFE0;
        if ( !strcmp( tokenstr, "OCT" ) )  	    return 0xEF85;
        if ( !strcmp( tokenstr, "PAINT" ) )  	return 0xEFCD;
        if ( !strcmp( tokenstr, "PND" ) )  	    return 0xEF88;
        if ( !strcmp( tokenstr, "PTD" ) )  	    return 0xEF89;
        if ( !strcmp( tokenstr, "PXD" ) )  	    return 0xEF8A;
        if ( !strcmp( tokenstr, "PFD" ) )  	    return 0xEF8B;
        if ( !strcmp( tokenstr, "PDS" ) )  	    return 0xEF8D;
        if ( !strcmp( tokenstr, "RENUM" ) )  	return 0xEFA8;
        if ( !strcmp( tokenstr, "RLINE" ) )  	return 0xEFC3;
        if ( !strcmp( tokenstr, "SET" ) )     	return 0xEFB5;
        if ( !strcmp( tokenstr, "SORGN" ) )  	return 0xEFCA;
        if ( !strcmp( tokenstr, "TDS" ) )  	    return 0xEF99;
        if ( !strcmp( tokenstr, "XDS" ) )  	    return 0xEF9A;
        if ( !strcmp( tokenstr, "XOR" ) )  	    return 0xEFA1;
    }
    return 0;
  } // End if NEW_BAS
  else if ( ident == IDENT_EXT_BAS || ident == IDENT_E_BAS )
  {
    if (pcgrpId == GRP_G) {
        if ( !strcmp( tokenstr, "BLOAD" ) )  	return 0xFE16; // G850V replaces CLOAD
        if ( !strcmp( tokenstr, "BSAVE" ) )  	return 0xFE20; // G850V replaces CSAVE
        if ( !strcmp( tokenstr, "FIX" ) )  		return 0xFEC7;
        if ( !strcmp( tokenstr, "LNINPUT" ) )  	return 0xFE63;
        if ( !strcmp( tokenstr, "VDEG" ) )  	return 0xFED3;
        if ( !strcmp( tokenstr, "DMS$" ) )  	return 0xFEF3;
        if ( !strcmp( tokenstr, "HDCOPY" ) )  	return 0xFE4C;
        if ( !strcmp( tokenstr, "HEX" ) )  		return 0xFEF2; // Alias, replaced by HEX$
        if ( !strcmp( tokenstr, "INP" ) )  	    return 0xFEA6;
        if ( err_line_ign &&                                   /* LCOPY bug */
             !strcmp( tokenstr, "LCOPY" ) )  	return 0xFE1F;
        if ( !strcmp( tokenstr, "MERGE" ) )  	return 0;      // PC-E500 other
        if ( !strcmp( tokenstr, "MEM" ) )     	return 0xFEAF; // Alias, replaced by FRE
        if ( !strcmp( tokenstr, "MOD" ) )  		return 0xFEC6;
        if ( !strcmp( tokenstr, "MON" ) )  		return 0xFE0F; // E220/G
        if ( !strcmp( tokenstr, "OUT" ) )  		return 0xFE45;
        if ( !strcmp( tokenstr, "PAUSE" ) )  	return 0xFE60; // Alias, replaced by PRINT
        if ( !strcmp( tokenstr, "PIOGET" ) )  	return 0xFEA8;
        if ( !strcmp( tokenstr, "PIOSET" ) )  	return 0xFE48;
        if ( !strcmp( tokenstr, "PIOPUT" ) )  	return 0xFE49;
        if ( !strcmp( tokenstr, "RENUM" ) )  	return 0xFE17; // other token than E500
        if ( !strcmp( tokenstr, "SPOUT" ) )  	return 0xFE4A;
        if ( !strcmp( tokenstr, "SPINP" ) )  	return 0xFE4B;
        if ( !strcmp( tokenstr, "VDEG" ) )  	return 0xFED3;
    }
    if (pcgrpId == GRP_E ) {
        if ( !strcmp( tokenstr, "AER" ) )  		return 0xFEBE; // E500 ? check 1470U
        if ( !strcmp( tokenstr, "BDATA$" ) )  	return 0xFE0C; // E500
        if ( !strcmp( tokenstr, "BTEXT$" ) )  	return 0xFE0B; // E500
        if ( !strcmp( tokenstr, "EVAL" ) )  	return 0xFEA7; // E500
        if ( !strcmp( tokenstr, "KEY" ) )     	return 0xFE79; // E500
        if ( !strcmp( tokenstr, "MEM$" ) )  	return 0xFE0D; // E500, 1475 no token: 'MEM $'
//      if ( !strcmp( tokenstr, "RESERVED" ) )  return 0xFE00; // E500?, [00] unsupported
        if ( !strcmp( tokenstr, "RESUME" ) )  	return 0xFE77; // E500
    }
    if (ident == IDENT_EXT_BAS ) {
        if ( !strcmp( tokenstr, "AREAD" ) )  	return 0xFE63;
        if ( !strcmp( tokenstr, "MEM" ) )  		return 0xFEAF;
        if ( pcId == 1470 &&
             !strcmp( tokenstr, "AER" ) )  		return 0xFEBE; //? 1470U
       	if ( pcId == 1360 ) {                                  // not 1475
            if ( !strcmp( tokenstr, "GCURSOR" ) )  	return 0xFE68;
            if ( !strcmp( tokenstr, "LINE" ) )  	return 0xFE69;
            if ( !strcmp( tokenstr, "POINT" ) )  	return 0xFEAD;
            if ( !strcmp( tokenstr, "PRESET" ) )  	return 0xFE35;
            if ( !strcmp( tokenstr, "PSET" ) )  	return 0xFE34;
        }
    }
    if (pcgrpId == GRP_E || pcgrpId == GRP_G) {
        if ( !strcmp( tokenstr, "CASE" ) )  	return 0xFE7D; // E500S, G850VS
        if ( !strcmp( tokenstr, "DEFAULT" ) )  	return 0xFE7E; // E500S, G850VS
        if ( !strcmp( tokenstr, "ELSE" ) )  	return 0xFE76; // E500,  G850VS
        if ( !strcmp( tokenstr, "ENDIF" ) )  	return 0xFE4D; // E500S, G850VS
        if ( !strcmp( tokenstr, "ENDSWITCH" ) ) return 0xFE7F; // E500S, G850VS
        if ( !strcmp( tokenstr, "FRE" ) )     	return 0xFEAF; // E500 other Syntax, G = Ext. MEM
        if ( !strcmp( tokenstr, "GCURSOR" ) )  	return 0xFE68; // not 1475
        if ( !strcmp( tokenstr, "LINE" ) )  	return 0xFE69; // not 1475
        if ( !strcmp( tokenstr, "POINT" ) )  	return 0xFEAD; // not 1475
        if ( !strcmp( tokenstr, "PRESET" ) )  	return 0xFE35; // not 1475
        if ( !strcmp( tokenstr, "PSET" ) )  	return 0xFE34; // not 1475
        if ( !strcmp( tokenstr, "REPEAT" ) )  	return 0xFE4E; // E500S, G850VS
        if ( !strcmp( tokenstr, "SWITCH" ) )  	return 0xFE7C; // E500S, G850VS
        if ( !strcmp( tokenstr, "UNTIL" ) )  	return 0xFE4F; // E500S, G850VS
        if ( !strcmp( tokenstr, "WEND" ) )  	return 0xFE7B; // E500S, G850VS
        if ( !strcmp( tokenstr, "WHILE" ) )  	return 0xFE7A; // E500S, G850VS
    }
    if (pcgrpId == GRP_E || ident == IDENT_EXT_BAS ) {
        if ( !strcmp( tokenstr, "AUTO" ) )  	return 0xFE1A;
        if ( !strcmp( tokenstr, "AUTOGOTO" ) )  return 0xFE75;
        if ( !strcmp( tokenstr, "ARUN" ) )  	return 0xFE74;
        if ( !strcmp( tokenstr, "BASIC" ) )  	return 0xFE36;
        if ( !strcmp( tokenstr, "CHAIN" ) )  	return 0xFE67;
        if ( !strcmp( tokenstr, "COLOR" ) )  	return 0xFE44;
        if ( !strcmp( tokenstr, "CONSOLE" ) )  	return 0xFE24;
        if ( !strcmp( tokenstr, "COPY" ) )  	return 0xFE3D;
        if ( !strcmp( tokenstr, "CROTATE" ) )  	return 0xFE6E;
        if ( !strcmp( tokenstr, "CSIZE" ) )  	return 0xFE43;
        if ( !strcmp( tokenstr, "DEFDBL" ) )  	return 0xFE46;
        if ( !strcmp( tokenstr, "DEFSNG" ) )  	return 0xFE47;
        if ( !strcmp( tokenstr, "DSKF" ) )  	return 0xFEB1;
        if ( !strcmp( tokenstr, "ERL" ) )  		return 0xFEC1;
        if ( !strcmp( tokenstr, "ERN" ) )  		return 0xFEC0;
        if ( !strcmp( tokenstr, "ERROR" ) )  	return 0xFE78;
        if ( !strcmp( tokenstr, "GLCURSOR" ) )  return 0xFE6C;
        if ( !strcmp( tokenstr, "GRAPH" ) )  	return 0xFE41;
        if ( !strcmp( tokenstr, "INIT" ) )  	return 0xFE1D;
        if ( !strcmp( tokenstr, "LF" ) )  		return 0xFE42;
        if ( !strcmp( tokenstr, "LLINE" ) )  	return 0xFE6A;
        if ( !strcmp( tokenstr, "LTEXT" ) )  	return 0xFE40;
        if ( !strcmp( tokenstr, "LOC" ) )  		return 0xFEB3;
        if ( !strcmp( tokenstr, "NAME" ) )  	return 0xFE3E;
        if ( !strcmp( tokenstr, "OPEN$" ) )  	return 0xFEE8; // E500: OPEN $
        if ( !strcmp( tokenstr, "PAUSE" ) )  	return 0xFE5F;
        if ( !strcmp( tokenstr, "RENUM" ) )  	return 0xFE19; // other token than G850
        if ( !strcmp( tokenstr, "RLINE" ) )  	return 0xFE6B;
        if ( !strcmp( tokenstr, "SET" ) )  		return 0xFE3F;
        if ( !strcmp( tokenstr, "SORGN" ) )  	return 0xFE6D;
        if ( !strcmp( tokenstr, "TEXT" ) )  	return 0xFE37;
        /* functions */
        if ( !strcmp( tokenstr, "ROT" ) )  		return 0xFE83;
        if ( !strcmp( tokenstr, "DECI" ) )  	return 0xFE84;
        if ( !strcmp( tokenstr, "HEX" ) )  		return 0xFE85;
    }
	if ( !strcmp( tokenstr, "ABS" ) )  		return 0xFE99;
	if ( !strcmp( tokenstr, "ACS" ) )  		return 0xFE9E;
	if ( !strcmp( tokenstr, "AHC" ) )  		return 0xFE8E;
	if ( !strcmp( tokenstr, "AHS" ) )  		return 0xFE8D;
	if ( !strcmp( tokenstr, "AHT" ) )  		return 0xFE8F;
	if ( !strcmp( tokenstr, "AND" ) )  		return 0xFEA1;
	if ( !strcmp( tokenstr, "ASN" ) )  		return 0xFE9D;
	if ( !strcmp( tokenstr, "ATN" ) )  		return 0xFE9F;
	if ( !strcmp( tokenstr, "COS" ) )  		return 0xFE96;
	if ( !strcmp( tokenstr, "CUB" ) )  		return 0xFEBF;
	if ( !strcmp( tokenstr, "CUR" ) )  		return 0xFE89;
	if ( !strcmp( tokenstr, "DEG" ) )  		return 0xFE9B;
	if ( !strcmp( tokenstr, "DMS" ) )  		return 0xFE9C;
	if ( !strcmp( tokenstr, "EXP" ) )  		return 0xFE93;
	if ( !strcmp( tokenstr, "FACT" ) )  	return 0xFE90;
	if ( !strcmp( tokenstr, "HCS" ) )  		return 0xFE8B;
	if ( !strcmp( tokenstr, "HSN" ) )  		return 0xFE8A;
	if ( !strcmp( tokenstr, "HTN" ) )  		return 0xFE8C;
	if ( !strcmp( tokenstr, "INT" ) )  		return 0xFE98;
	if ( !strcmp( tokenstr, "LN" ) )  		return 0xFE91;
	if ( !strcmp( tokenstr, "LOG" ) )  		return 0xFE92;
	if ( !strcmp( tokenstr, "LOF" ) )  		return 0xFEB2;
	if ( !strcmp( tokenstr, "NCR" ) )  		return 0xFEB6;
	if ( !strcmp( tokenstr, "NPR" ) )  		return 0xFEB7;
	if ( !strcmp( tokenstr, "OR" ) )  		return 0xFEA2;
	if ( !strcmp( tokenstr, "PI" ) )  		return 0xFEAE;
	if ( !strcmp( tokenstr, "POL" ) )  		return 0xFE82;
	if ( !strcmp( tokenstr, "RCP" ) )  		return 0xFE87;
	if ( !strcmp( tokenstr, "REC" ) )  		return 0xFE81;
	if ( !strcmp( tokenstr, "RND" ) )  		return 0xFEA0;
	if ( !strcmp( tokenstr, "SGN" ) )  		return 0xFE9A;
	if ( !strcmp( tokenstr, "SIN" ) )  		return 0xFE95;
	if ( !strcmp( tokenstr, "SQR" ) )  		return 0xFE94;
	if ( !strcmp( tokenstr, "SQU" ) )  		return 0xFE88;
	if ( !strcmp( tokenstr, "TAN" ) )  		return 0xFE97;
	if ( !strcmp( tokenstr, "TEN" ) )  		return 0xFE86;
	if ( !strcmp( tokenstr, "XOR" ) )  		return 0xFEA5;
    /* commands */
	if ( !strcmp( tokenstr, "AKCNV$" ) )  	return 0xFEE0;
	if ( !strcmp( tokenstr, "APPEND" ) )  	return 0xFE72;
	if ( !strcmp( tokenstr, "AS" ) )	  	return 0xFE73;
	if ( !strcmp( tokenstr, "ASC" ) )  		return 0xFED0;
	if ( !strcmp( tokenstr, "BEEP" ) )  	return 0xFE29;
	if ( !strcmp( tokenstr, "CALL" ) )  	return 0xFE31;
	if ( !strcmp( tokenstr, "CHR$" ) )  	return 0xFEF0;
	if ( !strcmp( tokenstr, "CIRCLE" ) )  	return 0xFE6F;
	if ( !strcmp( tokenstr, "CLEAR" ) )  	return 0xFE2E;
	if ( !strcmp( tokenstr, "CLOAD" ) )  	return 0xFE16;
	if ( !strcmp( tokenstr, "CLOSE" ) )  	return 0xFE22;
	if ( !strcmp( tokenstr, "CLS" ) )  		return 0xFE50;
	if ( !strcmp( tokenstr, "CONT" ) )  	return 0xFE12;
	if ( !strcmp( tokenstr, "CONVERT" ) )  	return 0xFE1E;
	if ( !strcmp( tokenstr, "CSAVE" ) )  	return 0xFE20;
	if ( !strcmp( tokenstr, "CURSOR" ) )  	return 0xFE51; // EXT, Alias for G/E LOCATE
	if ( !strcmp( tokenstr, "DATA" ) )  	return 0xFE5E;
	if ( !strcmp( tokenstr, "DEGREE" ) )  	return 0xFE26;
	if ( !strcmp( tokenstr, "DELETE" ) )  	return 0xFE1B;
	if ( !strcmp( tokenstr, "DIM" ) )  		return 0xFE30;
	if ( !strcmp( tokenstr, "END" ) )  		return 0xFE5A;
	if ( !strcmp( tokenstr, "EOF" ) )  		return 0xFEB0;
	if ( !strcmp( tokenstr, "ERASE" ) )  	return 0xFE3A;
	if ( !strcmp( tokenstr, "FIELD" ) )  	return 0xFE48;
	if ( !strcmp( tokenstr, "FILES" ) )  	return 0xFE1C;
	if ( !strcmp( tokenstr, "FOR" ) )  		return 0xFE57;
	if ( !strcmp( tokenstr, "GET" ) )  		return 0xFE4A;
	if ( !strcmp( tokenstr, "GOSUB" ) )  	return 0xFE62;
	if ( !strcmp( tokenstr, "GOTO" ) )  	return 0xFE2B;
	if ( !strcmp( tokenstr, "GPRINT" ) )  	return 0xFE33;
	if ( !strcmp( tokenstr, "GRAD" ) )  	return 0xFE28;
	if ( !strcmp( tokenstr, "HEX$" ) )  	return 0xFEF2;
	if ( !strcmp( tokenstr, "IF" ) )  		return 0xFE56;
	if ( !strcmp( tokenstr, "INKEY$" ) )  	return 0xFEE9;
	if ( !strcmp( tokenstr, "INPUT" ) )  	return 0xFE61;
	if ( !strcmp( tokenstr, "JIS$" ) )  	return 0xFEE2;
	if ( !strcmp( tokenstr, "KILL" ) )  	return 0xFE3C;
	if ( !strcmp( tokenstr, "KLEN" ) )  	return 0xFED3;
	if ( !strcmp( tokenstr, "KMID$" ) )  	return 0xFEED;
	if ( !strcmp( tokenstr, "KLEFT$" ) )  	return 0xFEEE;
	if ( !strcmp( tokenstr, "KRIGHT$" ) )  	return 0xFEEF;
	if ( !strcmp( tokenstr, "KACNV$" ) )  	return 0xFEE1;
	if ( !strcmp( tokenstr, "LEFT$" ) )  	return 0xFEEB;
	if ( !strcmp( tokenstr, "LEN" ) )  		return 0xFED2;
	if ( !strcmp( tokenstr, "LET" ) )  		return 0xFE58;
	if ( !strcmp( tokenstr, "LFILES" ) )  	return 0xFE3B;
	if ( !strcmp( tokenstr, "LIST" ) )  	return 0xFE14;
	if ( !strcmp( tokenstr, "LLIST" ) )  	return 0xFE15;
    if ( !strcmp( tokenstr, "LOCATE" ) )    return 0xFE51; // G/E, Alias for Ext CURSOR
	if ( !strcmp( tokenstr, "LOAD" ) )  	return 0xFE18;
	if ( !strcmp( tokenstr, "LPRINT" ) )  	return 0xFE64;
	if ( !strcmp( tokenstr, "LSET" ) )  	return 0xFE4B;
	if ( !strcmp( tokenstr, "MDF" ) )  		return 0xFE80;
	if ( !strcmp( tokenstr, "MERGE" ) )  	return 0xFE17;
	if ( !strcmp( tokenstr, "MID$" ) )  	return 0xFEEA;
	if ( !strcmp( tokenstr, "NEW" ) )  		return 0xFE11;
	if ( !strcmp( tokenstr, "NEXT" ) )  	return 0xFE5B;
	if ( !strcmp( tokenstr, "NOT" ) )  		return 0xFEA3;
	if ( !strcmp( tokenstr, "ON" ) )  		return 0xFE55;
	if ( !strcmp( tokenstr, "OPEN" ) )  	return 0xFE21;
	if ( !strcmp( tokenstr, "OUTPUT" ) )  	return 0xFE71;
	if ( !strcmp( tokenstr, "PAINT" ) )  	return 0xFE70;
	if ( !strcmp( tokenstr, "PASS" ) )  	return 0xFE13;
	if ( !strcmp( tokenstr, "PEEK" ) )  	return 0xFEA4;
	if ( !strcmp( tokenstr, "POKE" ) )  	return 0xFE32;
	if ( !strcmp( tokenstr, "PRINT" ) )  	return 0xFE60;
	if ( !strcmp( tokenstr, "PUT" ) )  		return 0xFE49;
	if ( !strcmp( tokenstr, "RADIAN" ) )  	return 0xFE27;
	if ( !strcmp( tokenstr, "RANDOM" ) )  	return 0xFE25; // Ext, Alias for G/E RANDOMIZE
    if ( !strcmp( tokenstr, "RANDOMIZE" ) ) return 0xFE25; // G/E, Alias for Ext RANDOM
	if ( !strcmp( tokenstr, "READ" ) )  	return 0xFE5D;
	if ( !strcmp( tokenstr, "REM" ) )  		return 0xFE59;
	if ( !strcmp( tokenstr, "RESTORE" ) )  	return 0xFE66;
	if ( !strcmp( tokenstr, "RETURN" ) )  	return 0xFE65;
	if ( !strcmp( tokenstr, "RIGHT$" ) ) 	return 0xFEEC;
	if ( !strcmp( tokenstr, "RSET" ) )  	return 0xFE4C;
	if ( !strcmp( tokenstr, "RUN" ) )  		return 0xFE10;
	if ( !strcmp( tokenstr, "SAVE" ) )  	return 0xFE23;
	if ( !strcmp( tokenstr, "STEP" ) )  	return 0xFE53;
	if ( !strcmp( tokenstr, "STOP" ) )  	return 0xFE5C;
	if ( !strcmp( tokenstr, "STR$" ) )  	return 0xFEF1;
	if ( !strcmp( tokenstr, "THEN" ) )  	return 0xFE54;
	if ( !strcmp( tokenstr, "TO" ) )  		return 0xFE52;
	if ( !strcmp( tokenstr, "TROFF" ) )  	return 0xFE2D;
	if ( !strcmp( tokenstr, "TRON" ) ) 		return 0xFE2C;
	if ( !strcmp( tokenstr, "USING" ) ) 	return 0xFE2F;
	if ( !strcmp( tokenstr, "VAL" ) ) 		return 0xFED1;
	if ( !strcmp( tokenstr, "WAIT" ) )		return 0xFE2A;
	if ( !strcmp( tokenstr, "WIDTH" ) )		return 0xFE38;
	else
        return 0;
  }  // End if EXT_BAS, E_BAS
  else if ( ident == IDENT_PC15_BAS || ident == IDENT_PC16_BAS )
  {
    if (ident == IDENT_PC16_BAS) {
        if ( !strcmp( tokenstr, "ACNV$" ) )  	return 0xF2F6;
        if ( !strcmp( tokenstr, "ADIN" ) )  	return 0xF280;
        if ( !strcmp( tokenstr, "AIN" ) )  	    return 0xF25A;
        if ( !strcmp( tokenstr, "ALARM$" ) )  	return 0xF25C;
        if ( !strcmp( tokenstr, "AOFF" ) )  	return 0xF2BC;
        if ( !strcmp( tokenstr, "APPEND" ) )  	return 0xF2BF;
        if ( !strcmp( tokenstr, "AS" ) )  	    return 0xF2BD;
        if ( !strcmp( tokenstr, "AUTO" ) )  	return 0xF2B6;
        if ( !strcmp( tokenstr, "BLOAD" ) )  	return 0xF290;
        if ( !strcmp( tokenstr, "BSAVE" ) )  	return 0xF291;
        if ( !strcmp( tokenstr, "CALL" ) )  	return 0xF282; // PC_15 Mode XCALL
        if ( !strcmp( tokenstr, "CLOSE" ) )  	return 0xF292;
        if ( !strcmp( tokenstr, "COM" ) )  	    return 0xF2A3;
        if ( !strcmp( tokenstr, "COPY" ) )  	return 0xF293;
        if ( !strcmp( tokenstr, "DATE$" ) )  	return 0xF257;
        if ( !strcmp( tokenstr, "DELETE" ) )  	return 0xF2B9;
        if ( !strcmp( tokenstr, "DSKF" ) )  	return 0xF274;
        if ( !strcmp( tokenstr, "ELSE" ) )  	return 0xF283;
        if ( !strcmp( tokenstr, "EOF" ) )  	    return 0xF271;
        if ( !strcmp( tokenstr, "ERASE" ) )  	return 0xF2B7;
        if ( !strcmp( tokenstr, "FILES" ) )  	return 0xF098;
        if ( !strcmp( tokenstr, "HEX$" ) )  	return 0xF265;
        if ( !strcmp( tokenstr, "INIT" ) )  	return 0xF294;
        if ( !strcmp( tokenstr, "INP" ) )  	    return 0xF266;
        if ( !strcmp( tokenstr, "INSTR" ) )  	return 0xF267;
        if ( !strcmp( tokenstr, "JS$" ) )  	    return 0xF268;
        if ( !strcmp( tokenstr, "KBUFF$" ) )  	return 0xF284;
        if ( !strcmp( tokenstr, "KCNV$" ) )  	return 0xF263;
        if ( !strcmp( tokenstr, "KEFT$" ) )  	return 0xF269;
        if ( !strcmp( tokenstr, "KEN" ) )  	    return 0xF26A;
        if ( !strcmp( tokenstr, "KEYSTAT" ) )  	return 0xF286;
        if ( !strcmp( tokenstr, "KEY" ) )  	    return 0xF285;
        if ( !strcmp( tokenstr, "KID$" ) )  	return 0xF26B;
        if ( !strcmp( tokenstr, "KIGHT$" ) )  	return 0xF26C;
        if ( !strcmp( tokenstr, "KILL" ) )  	return 0xF287;
        if ( !strcmp( tokenstr, "KN$" ) )  	    return 0xF264;
        if ( !strcmp( tokenstr, "LCURSOR" ) )  	return 0xF0A5; // changed PC_15
        if ( !strcmp( tokenstr, "LFILES" ) )  	return 0xF0A0; // changed PC_15: BYE
        if ( !strcmp( tokenstr, "LINE" ) )  	return 0xF099; // changed PC_15
        if ( !strcmp( tokenstr, "LLINE" ) )  	return 0xF0B7; // from PC-15 LINE
        if ( !strcmp( tokenstr, "LOAD" ) )  	return 0xF295;
        if ( !strcmp( tokenstr, "LOC" ) )  	    return 0xF272;
        if ( !strcmp( tokenstr, "LOF" ) )  	    return 0xF273;
        if ( !strcmp( tokenstr, "MAXFILES" ) )  return 0xF288;
        if ( !strcmp( tokenstr, "MODE" ) )  	return 0xF2B3;
        if ( !strcmp( tokenstr, "MOD" ) )  	    return 0xF250;
        if ( !strcmp( tokenstr, "NAME" ) )  	return 0xF297;
        if ( !strcmp( tokenstr, "OPEN" ) )  	return 0xF296;
        if ( !strcmp( tokenstr, "OUTPUT" ) )  	return 0xF2BE;
        if ( !strcmp( tokenstr, "OUT" ) )  	    return 0xF28A;
        if ( !strcmp( tokenstr, "PAPER" ) )  	return 0xE381;
        if ( !strcmp( tokenstr, "PASS" ) )  	return 0xF2B8;
        if ( !strcmp( tokenstr, "PCONSOLE" ) )  return 0xF2B1;
        if ( !strcmp( tokenstr, "PEEK#" ) )  	return 0xF26E; // changed PC-15
        if ( !strcmp( tokenstr, "PEEK" ) )  	return 0xF26D; // changed PC-15
        if ( !strcmp( tokenstr, "PHONE" ) )     return 0xF2A0;
        if ( !strcmp( tokenstr, "PITCH" ) )     return 0xF0A4;
        if ( !strcmp( tokenstr, "POKE" ) )  	return 0xF28C; // changed PC-15, POKE# ?
        if ( !strcmp( tokenstr, "POWER" ) )  	return 0xF28B;
        if ( !strcmp( tokenstr, "PRESET" ) )  	return 0xF09A;
        if ( !strcmp( tokenstr, "PSET" ) )  	return 0xF09B;
        if ( !strcmp( tokenstr, "PZONE" ) )  	return 0xF2B4;
        if ( !strcmp( tokenstr, "RCVSTAT" ) )  	return 0xF2A4;
        if ( !strcmp( tokenstr, "RENUM" ) )  	return 0xF2B5;
        if ( !strcmp( tokenstr, "RESUME" ) )  	return 0xF28D;
        if ( !strcmp( tokenstr, "RETI" ) )  	return 0xF28E;
        if ( !strcmp( tokenstr, "RXD$" ) )  	return 0xF256;
        if ( !strcmp( tokenstr, "SAVE" ) )  	return 0xF299;
        if ( !strcmp( tokenstr, "SET" ) )  	    return 0xF298;
        if ( !strcmp( tokenstr, "SNDBRK" ) )  	return 0xF2A1;
        if ( !strcmp( tokenstr, "SNDSTAT" ) )  	return 0xF2A2;
        if ( !strcmp( tokenstr, "TAB" ) )  	    return 0xE683; // from PC-15 LCURCOR
        if ( !strcmp( tokenstr, "TIME$" ) )  	return 0xF258;
        if ( !strcmp( tokenstr, "TITLE" ) )  	return 0xF2BA;
        if ( !strcmp( tokenstr, "WAKE$" ) )  	return 0xF261;
        if ( !strcmp( tokenstr, "WIDTH" ) )  	return 0xF087;
        if ( !strcmp( tokenstr, "XCALL" ) )  	return 0xF18A; // from PC-15
        if ( !strcmp( tokenstr, "XOR" ) )  	    return 0xF251;
        if ( !strcmp( tokenstr, "XPEEK#" ) )  	return 0xF16E; // from PC-15
        if ( !strcmp( tokenstr, "XPEEK" ) )  	return 0xF16F; // from PC-15
        if ( !strcmp( tokenstr, "XPOKE#" ) )  	return 0xF1A0; // from PC-15
        if ( !strcmp( tokenstr, "XPOKE" ) )  	return 0xF1A1; // from PC-15

        if ( !strcmp( tokenstr, "KBRD" ) )  	return 0xF2C0; // spellbound
    }
    /* PC-1500 */
	if ( !strcmp( tokenstr, "ABS" ) )		return 0xF170;
	if ( !strcmp( tokenstr, "ACS" ) )		return 0xF174;
	if ( !strcmp( tokenstr, "AND" ) )		return 0xF150;
	if ( !strcmp( tokenstr, "AREAD" ) )		return 0xF180;
	if ( !strcmp( tokenstr, "ARUN" ) )		return 0xF181;
	if ( !strcmp( tokenstr, "ASC" ) )		return 0xF160;
	if ( !strcmp( tokenstr, "ASN" ) )		return 0xF173;
	if ( !strcmp( tokenstr, "ATN" ) )		return 0xF175;
	if ( !strcmp( tokenstr, "BEEP" ) )		return 0xF182;
	if ( !strcmp( tokenstr, "BREAK" ) )		return 0xF0B3;
	if ( !strcmp( tokenstr, "CALL" ) )		return 0xF18A;
	if ( !strcmp( tokenstr, "CHAIN" ) )		return 0xF0B2;
	if ( !strcmp( tokenstr, "CHR$" ) )		return 0xF163;
	if ( !strcmp( tokenstr, "CLEAR" ) )		return 0xF187;
	if ( !strcmp( tokenstr, "CLOAD" ) )		return 0xF089;
	if ( !strcmp( tokenstr, "COM$" ) )		return 0xE858;
	if ( !strcmp( tokenstr, "CONT" ) )		return 0xF183;
	if ( !strcmp( tokenstr, "COS" ) )		return 0xF17E;
	if ( !strcmp( tokenstr, "CSAVE" ) )		return 0xF095;
	if ( !strcmp( tokenstr, "CSIZE" ) )		return 0xE680;
	if ( !strcmp( tokenstr, "DATA" ) )		return 0xF18D;
	if ( !strcmp( tokenstr, "DEG" ) )		return 0xF165;
	if ( !strcmp( tokenstr, "DEGREE" ) )	return 0xF18C;
	if ( !strcmp( tokenstr, "DEV$" ) )		return 0xE857;
	if ( !strcmp( tokenstr, "DIM" ) )		return 0xF18B;
	if ( !strcmp( tokenstr, "DMS" ) )		return 0xF166;
	if ( !strcmp( tokenstr, "DTE" ) )		return 0xE884;
	if ( !strcmp( tokenstr, "END" ) )		return 0xF18E;
	if ( !strcmp( tokenstr, "ERROR" ) )		return 0xF1B4;
	if ( !strcmp( tokenstr, "EXP" ) )		return 0xF178;
	if ( !strcmp( tokenstr, "FEED" ) )		return 0xF0B0;
	if ( !strcmp( tokenstr, "FOR" ) )		return 0xF1A5;
	if ( !strcmp( tokenstr, "GCURSOR" ) )	return 0xF093;
	if ( !strcmp( tokenstr, "GLCURSOR" ) )	return 0xE682;
	if ( !strcmp( tokenstr, "GOSUB" ) )		return 0xF194;
	if ( !strcmp( tokenstr, "GOTO" ) )		return 0xF192;
	if ( !strcmp( tokenstr, "GPRINT" ) )	return 0xF09F;
	if ( !strcmp( tokenstr, "GRAD" ) )		return 0xF186;
	if ( !strcmp( tokenstr, "GRAPH" ) )		return 0xE681;
	if ( !strcmp( tokenstr, "IF" ) )		return 0xF196;
	if ( !strcmp( tokenstr, "INKEY$" ) )	return 0xF15C;
	if ( !strcmp( tokenstr, "INPUT" ) )		return 0xF091;
	if ( !strcmp( tokenstr, "INSTAT" ) )	return 0xE859;
	if ( !strcmp( tokenstr, "INT" ) )		return 0xF171;
	if ( !strcmp( tokenstr, "LCURSOR" ) )	return 0xE683;
	if ( !strcmp( tokenstr, "LEFT$" ) )		return 0xF17A;
	if ( !strcmp( tokenstr, "LEN" ) )		return 0xF164;
	if ( !strcmp( tokenstr, "LET" ) )		return 0xF198;
	if ( !strcmp( tokenstr, "LF" ) )		return 0xF0B6;
	if ( !strcmp( tokenstr, "LINE" ) )		return 0xF0B7;
	if ( !strcmp( tokenstr, "LIST" ) )		return 0xF090;
	if ( !strcmp( tokenstr, "LLIST" ) )		return 0xF0B8;
	if ( !strcmp( tokenstr, "LN" ) )		return 0xF176;
	if ( !strcmp( tokenstr, "LOCK" ) )		return 0xF1B5;
	if ( !strcmp( tokenstr, "LOG" ) )		return 0xF177;
	if ( !strcmp( tokenstr, "LPRINT" ) )	return 0xF0B9;
	if ( !strcmp( tokenstr, "MEM" ) )		return 0xF158;
	if ( !strcmp( tokenstr, "MERGE" ) )		return 0xF08F;
	if ( !strcmp( tokenstr, "MID$" ) )		return 0xF17B;
	if ( !strcmp( tokenstr, "NEW" ) )		return 0xF19B;
	if ( !strcmp( tokenstr, "NEXT" ) )		return 0xF19A;
	if ( !strcmp( tokenstr, "NOT" ) )		return 0xF16D;
	if ( !strcmp( tokenstr, "OFF" ) )		return 0xF19E;
	if ( !strcmp( tokenstr, "ON" ) )		return 0xF19C;
	if ( !strcmp( tokenstr, "OPN" ) )		return 0xF19D;
	if ( !strcmp( tokenstr, "OR" ) )		return 0xF151;
	if ( !strcmp( tokenstr, "OUTSTAT" ) )	return 0xE880;
//	if ( !strcmp( tokenstr, "P    " ) )		return 0xF1A3;
	if ( !strcmp( tokenstr, "PAUSE" ) )		return 0xF1A2;
	if ( !strcmp( tokenstr, "PEEK" ) )		return 0xF16F;
	if ( !strcmp( tokenstr, "PEEK#" ) )		return 0xF16E;
	if ( !strcmp( tokenstr, "PI" ) )		return 0xF15D;
	if ( !strcmp( tokenstr, "POINT" ) )		return 0xF168;
	if ( !strcmp( tokenstr, "POKE" ) )		return 0xF1A1;
	if ( !strcmp( tokenstr, "POKE#" ) )		return 0xF1A0;
	if ( !strcmp( tokenstr, "PRINT" ) )		return 0xF097;
	if ( !strcmp( tokenstr, "RADIAN" ) )	return 0xF1AA;
	if ( !strcmp( tokenstr, "RANDOM" ) )	return 0xF1A8;	/* F0A8 */
	if ( !strcmp( tokenstr, "READ" ) )		return 0xF1A6;
	if ( !strcmp( tokenstr, "REM" ) )		return 0xF1AB;
	if ( !strcmp( tokenstr, "RESTORE" ) )	return 0xF1A7;
	if ( !strcmp( tokenstr, "RETURN" ) )	return 0xF199;
	if ( !strcmp( tokenstr, "RIGHT$" ) )	return 0xF172;
	if ( !strcmp( tokenstr, "RINKEY$" ) )	return 0xE85A;
	if ( !strcmp( tokenstr, "RLINE" ) )		return 0xF0BA;
	if ( !strcmp( tokenstr, "RMT" ) )		return 0xE7A9;
	if ( !strcmp( tokenstr, "RND" ) )		return 0xF17C;
	if ( !strcmp( tokenstr, "ROTATE" ) )	return 0xE685;
	if ( !strcmp( tokenstr, "RUN" ) )		return 0xF1A4;
	if ( !strcmp( tokenstr, "SETCOM" ) )	return 0xE882;
	if ( !strcmp( tokenstr, "SETDEV" ) )	return 0xE886;
	if ( !strcmp( tokenstr, "SGN" ) )		return 0xF179;
	if ( !strcmp( tokenstr, "SIN" ) )		return 0xF17D;
	if ( !strcmp( tokenstr, "SORGN" ) )		return 0xE684;
	if ( !strcmp( tokenstr, "SPACE$" ) )	return 0xF061;
	if ( !strcmp( tokenstr, "SQR" ) )		return 0xF16B;
	if ( !strcmp( tokenstr, "STATUS" ) )	return 0xF167;
	if ( !strcmp( tokenstr, "STEP" ) )		return 0xF1AD;
	if ( !strcmp( tokenstr, "STOP" ) )		return 0xF1AC;
	if ( !strcmp( tokenstr, "STR$" ) )		return 0xF161;
	if ( !strcmp( tokenstr, "TAB" ) )		return 0xF0BB;
	if ( !strcmp( tokenstr, "TAN" ) )		return 0xF17F;
	if ( !strcmp( tokenstr, "TERMINAL" ) )	return 0xE883;
	if ( !strcmp( tokenstr, "TEST" ) )		return 0xF0BC;
	if ( !strcmp( tokenstr, "TEXT" ) )		return 0xE686;
	if ( !strcmp( tokenstr, "THEN" ) )		return 0xF1AE;
	if ( !strcmp( tokenstr, "TIME" ) )		return 0xF15B;
	if ( !strcmp( tokenstr, "TO" ) )		return 0xF1B1;
	if ( !strcmp( tokenstr, "TRANSMIT" ) )	return 0xE885;
	if ( !strcmp( tokenstr, "TROFF" ) )		return 0xF1B0;
	if ( !strcmp( tokenstr, "TRON" ) )		return 0xF1AF;
    if ( !strcmp( tokenstr, "UNLOCK" ) )  	return 0xF1B6;
	if ( !strcmp( tokenstr, "USING" ) )		return 0xF085;
	if ( !strcmp( tokenstr, "VAL" ) )		return 0xF162;
	if ( !strcmp( tokenstr, "WAIT" ) )		return 0xF1B3;
	if ( !strcmp( tokenstr, "ZONE" ) )		return 0xF0B4;

    {   /* Tramsoft Tools */
        /* Tool1 V2.0    */
        if ( !strcmp( tokenstr, "APPEND" ) )    return 0xF0C0;
        if ( !strcmp( tokenstr, "CHANGE" ) )    return 0xF0C1;
        if ( !strcmp( tokenstr, "DELETE" ) )    return 0xF0C2;
        if ( !strcmp( tokenstr, "ERASE" ) )     return 0xF0C3;
        if ( !strcmp( tokenstr, "FIND" ) )      return 0xF0C4;
        if ( !strcmp( tokenstr, "KEEP" ) )      return 0xF0C5;
        if ( !strcmp( tokenstr, "LINK" ) )      return 0xF0CA;
        if ( !strcmp( tokenstr, "PLIST" ) )     return 0xF0C6;
        if ( !strcmp( tokenstr, "PLAST" ) )     return 0xF0C9;
        if ( !strcmp( tokenstr, "PROGRAM" ) )   return 0xF0C7;
        if ( !strcmp( tokenstr, "RENUMBER" ) )  return 0xF0C8;
        if ( !strcmp( tokenstr, "SPLIT" ) )     return 0xF0CB;
        /* Tool2 V1.0    */
        if ( !strcmp( tokenstr, "FLOAD" ) )     return 0xE180;
        if ( !strcmp( tokenstr, "FSAVE" ) )     return 0xE181;
        if ( !strcmp( tokenstr, "FCHAIN" ) )    return 0xE182;
        if ( !strcmp( tokenstr, "VERIFY" ) )    return 0xE183;
        /* Tool3 V1.5    */
        if ( !strcmp( tokenstr, "CLR" ) )       return 0xE2C0;
        if ( !strcmp( tokenstr, "DEC" ) )       return 0xF070;
        if ( !strcmp( tokenstr, "ERL" ) )       return 0xF053;
        if ( !strcmp( tokenstr, "ERN" ) )       return 0xF052;
        if ( !strcmp( tokenstr, "FRC" ) )       return 0xE271;
        if ( !strcmp( tokenstr, "FRE" ) )       return 0xE250;
        if ( !strcmp( tokenstr, "HEX$" ) )      return 0xF071;
        if ( !strcmp( tokenstr, "INSTR" ) )     return 0xE273;
        if ( !strcmp( tokenstr, "PGM" ) )       return 0xE251;
        if ( !strcmp( tokenstr, "PSIZE" ) )     return 0xE252;
        if ( !strcmp( tokenstr, "PURGE" ) )     return 0xE2C1;
        if ( !strcmp( tokenstr, "REDIM" ) )     return 0xE2C2;
        if ( !strcmp( tokenstr, "RESUME" ) )    return 0xE2C3;
        if ( !strcmp( tokenstr, "STRING$" ) )   return 0xE272;
        if ( !strcmp( tokenstr, "SWAP" ) )      return 0xE2C4;
        if ( !strcmp( tokenstr, "VKEEP" ) )     return 0xE253;
        if ( !strcmp( tokenstr, "VLIST" ) )     return 0xE2C5;
        /* Tool4 V1.0    */
        if ( !strcmp( tokenstr, "AVGX" ) )      return 0xE350;
        if ( !strcmp( tokenstr, "AVGY" ) )      return 0xE351;
        if ( !strcmp( tokenstr, "CLEN" ) )      return 0xE360;
        if ( !strcmp( tokenstr, "CONVL$" ) )    return 0xE363;
        if ( !strcmp( tokenstr, "CONVS$" ) )    return 0xE364;
        if ( !strcmp( tokenstr, "CONV" ) )      return 0xE362;
        if ( !strcmp( tokenstr, "CORR" ) )      return 0xE352;
        if ( !strcmp( tokenstr, "ENTER" ) )     return 0xE3D0;
        if ( !strcmp( tokenstr, "ELAST" ) )     return 0xE35F;
        if ( !strcmp( tokenstr, "ELINE" ) )     return 0xE361;
        if ( !strcmp( tokenstr, "ELIST$" ) )    return 0xE365;
        if ( !strcmp( tokenstr, "GRA" ) )       return 0xE353;
        if ( !strcmp( tokenstr, "STATON" ) )    return 0xE3C0;
        if ( !strcmp( tokenstr, "STATOFF" ) )   return 0xE3C1;
        if ( !strcmp( tokenstr, "STATCLR" ) )   return 0xE3C2;
        if ( !strcmp( tokenstr, "STATIN" ) )    return 0xE3C3;
        if ( !strcmp( tokenstr, "STATOUT" ) )   return 0xE3C4;
        if ( !strcmp( tokenstr, "STAT" ) )      return 0xE370;
        if ( !strcmp( tokenstr, "SDNX" ) )      return 0xE354;
        if ( !strcmp( tokenstr, "SDNY" ) )      return 0xE355;
        if ( !strcmp( tokenstr, "SDVX" ) )      return 0xE357;
        if ( !strcmp( tokenstr, "SDVY" ) )      return 0xE358;
        if ( !strcmp( tokenstr, "STX" ) )       return 0xE371;
        if ( !strcmp( tokenstr, "STY" ) )       return 0xE372;
        if ( !strcmp( tokenstr, "SEG" ) )       return 0xE356;
    }
    {   /* RVS PC-BASIC 84 */
        if ( !strcmp( tokenstr, "CASE" ) )      return 0xF0D3;
        if ( !strcmp( tokenstr, "DEFFN" ) )     return 0xF0D2;
        if ( !strcmp( tokenstr, "DO" ) )        return 0xF0D4;
        if ( !strcmp( tokenstr, "EXIT" ) )      return 0xF0CE;
        if ( !strcmp( tokenstr, "ELSE" ) )      return 0xF0CF;
        if ( !strcmp( tokenstr, "FN" ) )        return 0xF06F;
        if ( !strcmp( tokenstr, "GSB" ) )       return 0xF0AF;
        if ( !strcmp( tokenstr, "LOOP" ) )      return 0xF0D5;
        if ( !strcmp( tokenstr, "ROUND" ) )     return 0xF07C;
        if ( !strcmp( tokenstr, "SELECT" ) )    return 0xF0D0;
        if ( !strcmp( tokenstr, "SUBEND" ) )    return 0xF0D9;
        if ( !strcmp( tokenstr, "SUBCLR" ) )    return 0xF0DA;
        if ( !strcmp( tokenstr, "SUB" ) )       return 0xF0D8;
        if ( !strcmp( tokenstr, "WHILE" ) )     return 0xF0D6;
        if ( !strcmp( tokenstr, "IF#" ) )       return 0xF0CC;
        if ( !strcmp( tokenstr, "INTEGRAL" ) )  return 0xF07D;
        if ( !strcmp( tokenstr, "ENDIF" ) )     return 0xF0CD;
        if ( !strcmp( tokenstr, "ENDSELECT" ) ) return 0xF0D1;
    }
    {   /* IWS Video interface*/
        if ( !strcmp( tokenstr, "CLS" ) )       return 0xF088;
        if ( !strcmp( tokenstr, "COLOR" ) )		return 0xF0B5;
        if ( !strcmp( tokenstr, "CONSOLE" ) )	return 0xF0B1;
        if ( !strcmp( tokenstr, "CURSOR" ) )	return 0xF084; //(VCURSOR)
        if ( !strcmp( tokenstr, "DIR" ) )       return 0xF0E0;
        if ( !strcmp( tokenstr, "DEZ" ) )       return 0xF070;
        // RWE if ( !strcmp( tokenstr, "ERL" ) )       return 0xF053;
        // RWE if ( !strcmp( tokenstr, "ERN" ) )       return 0xF052;
        if ( !strcmp( tokenstr, "GCLS" ) )      return 0xF0E1;
        if ( !strcmp( tokenstr, "GVCURSOR" ) )	return 0xF093;
        if ( !strcmp( tokenstr, "GVPRINT" ) )	return 0xF09F;
        if ( !strcmp( tokenstr, "HCURSOR" ) )	return 0xF054;
        if ( !strcmp( tokenstr, "HPCURSOR" ) )	return 0xF055;
        // RWE if ( !strcmp( tokenstr, "HEX$" ) )      return 0xF071;
        if ( !strcmp( tokenstr, "KEY" ) )       return 0xF0E2;
        if ( !strcmp( tokenstr, "REPKEY" ) )    return 0xF0C3;
        if ( !strcmp( tokenstr, "SLEEP" ) )     return 0xF0E7;
        if ( !strcmp( tokenstr, "VCURSOR" ) )	return 0xF056;
        if ( !strcmp( tokenstr, "VPCURSOR" ) )	return 0xF050;
        if ( !strcmp( tokenstr, "QVERIFY" ) )	return 0xF083;
    }
    {   /* RWEtools 4 */
        if ( !strcmp( tokenstr, "CREATE" ) )    return 0xF0C0;
        if ( !strcmp( tokenstr, "DELETE" ) )    return 0xF0C2;
        if ( !strcmp( tokenstr, "EDIT" ) )      return 0xF0DE;
        if ( !strcmp( tokenstr, "FETCH" ) )     return 0xF0C6;
        if ( !strcmp( tokenstr, "HEX$" ) )      return 0xF071;
        if ( !strcmp( tokenstr, "MODUL" ) )     return 0xF0C7;
        if ( !strcmp( tokenstr, "OLD" ) )       return 0xF0C5;
        if ( !strcmp( tokenstr, "PURGE" ) )     return 0xF0AE;
        if ( !strcmp( tokenstr, "QLOAD" ) )     return 0xF080;
        if ( !strcmp( tokenstr, "QSAVE" ) )     return 0xF081;
        if ( !strcmp( tokenstr, "RENUM" ) )     return 0xF0C8;
    }
    {   /* RWErelics */
        if ( !strcmp( tokenstr, "BYE" ) )       return 0xF0A0;
        if ( !strcmp( tokenstr, "CATALOG" ) )   return 0xF0A1;
        if ( !strcmp( tokenstr, "CHECK" ) )     return 0xF0A2;
        if ( !strcmp( tokenstr, "COPY" ) )      return 0xF0A3;
        if ( !strcmp( tokenstr, "DEEK" ) )      return 0xF07B;
        if ( !strcmp( tokenstr, "DOKE" ) )      return 0xF0AB;
        if ( !strcmp( tokenstr, "EXCHANGE" ) )  return 0xF0A4;
        if ( !strcmp( tokenstr, "FAC" ) )       return 0xF075;
        if ( !strcmp( tokenstr, "HELP" ) )      return 0xF0A5;
        if ( !strcmp( tokenstr, "INPT" ) )      return 0xF0A6;
        if ( !strcmp( tokenstr, "MOVE" ) )      return 0xF0A7;
        if ( !strcmp( tokenstr, "NAME$" ) )     return 0xF07A;
        if ( !strcmp( tokenstr, "RPU" ) )       return 0xF0AC;
        if ( !strcmp( tokenstr, "SPU" ) )       return 0xF0AD;
        if ( !strcmp( tokenstr, "SEARCH" ) )    return 0xF0A8;
        if ( !strcmp( tokenstr, "SEEK" ) )      return 0xF0A9;
        if ( !strcmp( tokenstr, "SORT" ) )      return 0xF0AA;
    }
    {   /* Ursoft */
        if ( !strcmp( tokenstr, "SECONDS" ) )   return 0xE302;
        if ( !strcmp( tokenstr, "PRON" ) )      return 0xE304;
        if ( !strcmp( tokenstr, "ZEIT$" ) )     return 0xE35E;
        // if ( !strcmp( tokenstr, "DATE$" ) )  return 0xE35F;
        if ( !strcmp( tokenstr, "FRAC" ) )      return 0xE360;
        // if ( !strcmp( tokenstr, "HEX$" ) )   return 0xE361;
        if ( !strcmp( tokenstr, "BINDEC" ) )    return 0xE362;
        if ( !strcmp( tokenstr, "BINSTR$" ) )   return 0xE363;
        if ( !strcmp( tokenstr, "GET" ) )       return 0xE380;
        if ( !strcmp( tokenstr, "INVERT" ) )    return 0xE381;
        if ( !strcmp( tokenstr, "PWROFF" ) )    return 0xE382;
        if ( !strcmp( tokenstr, "REPEAT" ) )    return 0xE383;
        if ( !strcmp( tokenstr, "UNTIL" ) )     return 0xE384;
        // if ( !strcmp( tokenstr, "WHILE" ) )  return 0xE385;
        if ( !strcmp( tokenstr, "WEND" ) )      return 0xE386;
        // if ( !strcmp( tokenstr, "SWAP" ) )   return 0xE388;
        if ( !strcmp( tokenstr, "JAHR" ) )      return 0xE389;
        if ( !strcmp( tokenstr, "LOOPEND" ) )   return 0xE38A;
        // if ( !strcmp( tokenstr, "LOOP" ) )   return 0xE38B;
        if ( !strcmp( tokenstr, "MAL" ) )       return 0xE38C;
        if ( !strcmp( tokenstr, "INC" ) )       return 0xE38D;
        if ( !strcmp( tokenstr, "DEC" ) )       return 0xE38E;
        // if ( !strcmp( tokenstr, "SORT" ) )   return 0xE38F;
        if ( !strcmp( tokenstr, "CLOCK" ) )     return 0xE392;
        if ( !strcmp( tokenstr, "POP" ) )       return 0xE393;
        if ( !strcmp( tokenstr, "INITLOOP" ) )  return 0xE394;
    }
    {   /* JK tools */
        if ( !strcmp( tokenstr, "TTIME$" ) )    return 0xF05E;
        // if ( !strcmp( tokenstr, "DATE$" ) )  return 0xF05F;
        // if ( !strcmp( tokenstr, "HEX$" ) )   return 0xF062;
        if ( !strcmp( tokenstr, "INV" ) )       return 0xF080;
        // if ( !strcmp( tokenstr, "PWROFF" ) )    return 0xF0A8;
        // if ( !strcmp( tokenstr, "FRAC" ) )      return 0xF060;
        if ( !strcmp( tokenstr, "FACT" ) )      return 0xF061;
        // if ( !strcmp( tokenstr, "OLD" ) )    return 0xF0A7;
        if ( !strcmp( tokenstr, "MBS" ) )       return 0xF083;
        if ( !strcmp( tokenstr, "MCL" ) )       return 0xF0A6;
        // if ( !strcmp( tokenstr, "RENUMBER")) return 0xF0A5; //not inside lines
        if ( !strcmp( tokenstr, "FCSAVE" ) )    return 0xF0A2; // SuperTape
        if ( !strcmp( tokenstr, "FCLOAD" ) )    return 0xF0A1;
        // if ( !strcmp( tokenstr, "FCHAIN" ) ) return 0xF0A0;
        if ( !strcmp( tokenstr, "FMERGE" ) )    return 0xF0A3;
        if ( !strcmp( tokenstr, "FVERIFY" ) )   return 0xF0A4;
    }
    {   /* Dr. Schetter BMC MC-12(A) */
        if ( !strcmp( tokenstr, "AUTORANGE" ) ) return 0xE384;
        if ( !strcmp( tokenstr, "BUFFER" ) )    return 0xE363;
        if ( !strcmp( tokenstr, "BUFLEN" ) )    return 0xE350;
        if ( !strcmp( tokenstr, "BUFINIT" ) )   return 0xE3A1;
        if ( !strcmp( tokenstr, "BUFNUM" ) )    return 0xE351;
        if ( !strcmp( tokenstr, "BUFREAD" ) )   return 0xE3A3;
        if ( !strcmp( tokenstr, "BUFOPEN" ) )   return 0xE3A4;
        if ( !strcmp( tokenstr, "BUFWRITE" ) )  return 0xE3A5;
        if ( !strcmp( tokenstr, "BUFRANGE" ) )  return 0xE364;
        if ( !strcmp( tokenstr, "CHA" ) )       return 0xE361;
        if ( !strcmp( tokenstr, "COM" ) )       return 0xE3AE;
        if ( !strcmp( tokenstr, "DBUFINIT" ) )  return 0xE3AB;
        if ( !strcmp( tokenstr, "INCHA" ) )     return 0xE386;
        if ( !strcmp( tokenstr, "INIT" ) )      return 0xE390;
        if ( !strcmp( tokenstr, "INSCAN" ) )    return 0xE3AA;
        if ( !strcmp( tokenstr, "INFUNCTION" ) )return 0xE399;
        if ( !strcmp( tokenstr, "LOADBUFFER" ) )return 0xE3A6;
        if ( !strcmp( tokenstr, "MCON" ) )      return 0xE38A;
        if ( !strcmp( tokenstr, "MCOFF" ) )     return 0xE38B;
        if ( !strcmp( tokenstr, "MULTIMETER" ) )return 0xE39B;
        if ( !strcmp( tokenstr, "OUTCHA" ) )    return 0xE382;
        if ( !strcmp( tokenstr, "OUTSCREEN" ) ) return 0xE393;
        if ( !strcmp( tokenstr, "PREHIST" ) )   return 0xE355;
        if ( !strcmp( tokenstr, "POSITION" ) )  return 0xE356;
        if ( !strcmp( tokenstr, "PLOT" ) )      return 0xE39A;
        if ( !strcmp( tokenstr, "RANGE" ) )     return 0xE362;
        if ( !strcmp( tokenstr, "RELAY" ) )     return 0xE39D;
        if ( !strcmp( tokenstr, "ROM#" ) )      return 0xE357;
        if ( !strcmp( tokenstr, "SWITCH" ) )    return 0xE380;
        if ( !strcmp( tokenstr, "SCANTIME" ) )  return 0xE353;
        if ( !strcmp( tokenstr, "SCREEN" ) )    return 0xE381; // TRM PC-1600: PAPER
        // if ( !strcmp( tokenstr, "SELECT" ) )    return 0xE3A9;
        if ( !strcmp( tokenstr, "SETCOM" ) )    return 0xE3AF;
        if ( !strcmp( tokenstr, "SETRANGE" ) )  return 0xE389;
        if ( !strcmp( tokenstr, "SETTRIGGER" ) )return 0xE395;
        if ( !strcmp( tokenstr, "SETSCANTIME") )return 0xE396;
        if ( !strcmp( tokenstr, "SETPREHIST" ) )return 0xE397;
        if ( !strcmp( tokenstr, "SETFUNCTION") )return 0xE398;
        // if ( !strcmp( tokenstr, "SLEEP" ) )     return 0xE39E;
        if ( !strcmp( tokenstr, "TRIGGER" ) )   return 0xE354;
        if ( !strcmp( tokenstr, "TRANSREC" ) )  return 0xE39C;
        if ( !strcmp( tokenstr, "POSTLOAD" ) )  return 0xF0FC;
        if ( !strcmp( tokenstr, "RVSLOAD" ) )   return 0xF0FB;
    }
  } // End if PC-1500, PC-1600
  return 0;
}
/* Tokenize one-character commands (outside of strings and comments) depending on context */
uint istoken1C( uchar SpecChar )
{
   char befehl[cLC] = "";
    uint  i_token = 0 ;

    /* Convert a special char to function text for models where the chars are not full supported */
    if (ident == IDENT_E_BAS || (pcgrpId == GRP_16 && (pcMode &3) == 0) ) { // PC-E/G/16 series
        if (      *SQRidStr && (uchar) *SQRidStr == SpecChar) strcpy( befehl, "SQR"); // '[' PC-1600
        else if ( *PI_idStr && (uchar) *PI_idStr == SpecChar) strcpy( befehl, "PI") ; // ']' PC-1600
        else if ( *piLidStr && (uchar) *piLidStr == SpecChar) strcpy( befehl, "PI") ; /* long after short, if ='[..]' */
    }
    else if (pcgrpId != GRP_16) { /* REMidC ' allowed only for new groups, replace for older */
        if (SpecChar == '\'') strcpy( befehl, "REM") ;
    }
    if (strlen(befehl)== 0) return (0);
    i_token = istoken( befehl );
    return i_token;
}
/* Tokenise two-character commands (Kanji), outside of strings and comments, depending on context */
uint istoken2C( uchar SpecChar, uchar SpecChar1 )
{
   char befehl[cLC] = "";
    uint  i_token ;

    /* Convert a special char to function text for models where the chars are not full supported */
    if (ident == IDENT_E_BAS || (pcgrpId == GRP_16 && (pcMode &3) == 0) ) { // PC-E/G/16 series
        if (      *SQRidStr && (uchar) SQRidStr[0] == SpecChar && (uchar) SQRidStr[1] == SpecChar1) strcpy( befehl, "SQR"); // '[' PC-1600
        else if ( *PI_idStr && (uchar) PI_idStr[0] == SpecChar && (uchar) PI_idStr[1] == SpecChar1) strcpy( befehl, "PI") ; // ']' PC-1600
        else if ( *piLidStr && (uchar) piLidStr[0] == SpecChar && (uchar) piLidStr[1] == SpecChar1) strcpy( befehl, "PI") ;
    }
    else if (pcgrpId == GRP_16 && (pcMode &3)== 1) { /* PC-1600K in PC-1500J compatible mode 1 */
        if (      *SQRidStr && (uchar) SQRidStr[0] == SpecChar && (uchar) SQRidStr[1] == SpecChar1) strcpy( befehl, "[") ;
        else if ( *PI_idStr && (uchar) PI_idStr[0] == SpecChar && (uchar) PI_idStr[1] == SpecChar1) strcpy( befehl, "]") ;
        else if ( *piLidStr && (uchar) piLidStr[0] == SpecChar && (uchar) piLidStr[1] == SpecChar1) strcpy( befehl, "]") ;
    }
    else if (ident == IDENT_EXT_BAS) { /* PC-1360K, Convert Kanji characters into standard characters recognized by the BASIC interpreter */
        if (      *SQRidStr && (uchar) SQRidStr[0] == SpecChar && (uchar) SQRidStr[1] == SpecChar1) strcpy( befehl, "\xFC") ;
        else if ( *PI_idStr && (uchar) PI_idStr[0] == SpecChar && (uchar) PI_idStr[1] == SpecChar1) strcpy( befehl, "\xFB") ;
        else if ( *piLidStr && (uchar) piLidStr[0] == SpecChar && (uchar) piLidStr[1] == SpecChar1) strcpy( befehl, "\xFB") ;
    }
    if (strlen(befehl) > 1 )    i_token = istoken( befehl );
    else if (strlen(befehl) == 1) i_token = (uchar) *befehl;
    else i_token = 0 ;

    return i_token;
}

/* Some tokens require additional post-processing, such as
   inserting a colon or converting a line number to binary format. */
uint TokenType (uint token)
{
    if (token == REMid ) return TOKEN_REM ;

    else if ( ident == IDENT_EXT_BAS || ident == IDENT_E_BAS  ) {

        switch (token) {

        case 0xFE55 : /* ON */
            return TOKEN_LST ;

        case 0xFE1B : /* DELETE */
        case 0xFE15 : /* LLIST */
        case 0xFE19 : /* RENUM */
        case 0xFE67 : /* CHAIN */
            return (TOKEN_LBL | TOKEN_LST) ;

        case 0xFE74 : /* ARUN */
        case 0xFE1A : /* AUTO, E500 */
        case 0xFE75 : /* AUTOGOTO */
        case 0xFE62 : /* GOSUB */
        case 0xFE2B : /* GOTO */
        case 0xFE14 : /* LIST */
        case 0xFE66 : /* RESTORE */
        case 0xFE77 : /* RESUME */
        case 0xFE10 : /* RUN */
        case 0xFE54 : /* THEN */
            return TOKEN_LBL ;

        case 0xFE76 : /* ELSE, E500, PC-G with colon before */
//          if (ident == IDENT_EXT_BAS) return (TOKEN_LBL) ; /* Pseudo E475 */
            return (TOKEN_LBL | TOKEN_COL) ;

        case 0xFE59 : /* REM */
            return TOKEN_REM ;

        default:
            return TOKEN_GEN ;
        }
    }
    else if ( ident == IDENT_PC16_BAS || ident == IDENT_PC15_BAS ) {

        switch (token) {

        case 0xF19C : /* ON */
            return TOKEN_LST ;

        case 0xF2B9 : /* DELETE */
        case 0xF0C2 : /* DELETE Tramsoft */
        case 0xF0B8 : /* LLIST */
        case 0xF2B5 : /* RENUM */
        case 0xF0C8 : /* RENUMBER Tramsoft */
        case 0xF0B2 : /* CHAIN */
            return (TOKEN_LBL | TOKEN_LST) ;

        case 0xF181 : /* ARUN */
        case 0xF2B6 : /* AUTO */
        case 0xF283 : /* ELSE */
        case 0xF194 : /* GOSUB */
        case 0xF192 : /* GOTO */
        case 0xF090 : /* LIST */
        case 0xF1A7 : /* RESTORE */
        case 0xF28D : /* RESUME */
        case 0xF1A4 : /* RUN */
        case 0xF1AE : /* THEN */
            return TOKEN_LBL ;

        case 0xF1AB : /* REM */
            return TOKEN_REM ;

        default:
            return TOKEN_GEN ;
        }
    }
    else if ( ident == IDENT_NEW_BAS ) {

        switch (token) {

        case 0xD3 : /* ON */
            return TOKEN_LST ;

        case 0xEFA9 : /* DELETE */
        case 0xB5 :   /* LLIST */
        case 0xEFA8 : /* RENUM */
        case 0xE5 :   /* CHAIN */
            return (TOKEN_LBL | TOKEN_LST) ;

        case 0xE0 :   /* GOSUB */
        case 0xC6 :   /* GOTO */
        case 0xB4 :   /* LIST */
        case 0xE4 :   /* RESTORE */
        case 0xB0 :   /* RUN */
        case 0xD2 :   /* THEN */
            return TOKEN_LBL ;

        case 0xD7 :   /* REM */
            return TOKEN_REM ;

        default:
            return TOKEN_GEN ;
        }
    }
    else if ( ident == IDENT_OLD_BAS ) {

        switch (token) {

        case 0xCC : /* ON */
            return TOKEN_LST ;

        case 0xBC : /* LLIST */
        case 0xD9 : /* CHAIN */
            return (TOKEN_LBL | TOKEN_LST) ;

        case 0xD8 : /* GOSUB */
        case 0xD7 : /* GOTO */
        case 0xB3 : /* LIST */
        case 0xDF : /* RESTORE */
        case 0xB0 : /* RUN */
        case 0x92 : /* THEN */
            return TOKEN_LBL ;

        case 0xD3 : /* REM */
            return TOKEN_REM ;

        default:
            return TOKEN_GEN ;
        }
    }
    else
        return TOKEN_GEN ;
}

int IsChar4Cmd( char *line_buffer, char *befehl, uint chars_ext)
               /* globals:  uchar  ident, ushort pcgrpId, bool shortcuts */
{
    int is4cmd = false ;
    uint cmd_len = strlen (befehl) ;

    if (*line_buffer >= 'A' && *line_buffer <= 'Z') is4cmd = true ;

    else if (*line_buffer == '$' && cmd_len > 1 ) is4cmd = last4CMD ; /* OK as last char of a command */

    else if (*line_buffer == '#' && cmd_len > 1 &&
             (ident == IDENT_NEW_BAS || ident == IDENT_PC15_BAS || ident == IDENT_PC16_BAS)
            )   is4cmd = last4CMD ;

    else if ((ident == IDENT_OLD_BAS || pcgrpId == GRP_MZ) && //if not replaced by preprocessor
             (*line_buffer == '<' || *line_buffer == '=' || *line_buffer == '>') ) {
                if (cmd_len < 1) is4cmd = true ;
                else if  (cmd_len == 1  && (*befehl == '<' || *befehl == '=' || *befehl == '>'))
                     is4cmd = last4CMD ;
             /* else is4cmd = false ;  Process it with the next command */
    }    /* Comparison signs may not be divided into different commands */
    else if ( pcgrpId == GRP_MZ  && (*line_buffer == '+' || *line_buffer == '-' ||
              *line_buffer == '/' || *line_buffer == '*' || *line_buffer == '^'  ) ) {

            if (cmd_len < 1 ) is4cmd = last4CMD ; /* OK first and last */
         /* else is4cmd = false ;  Process it with the next command */
    }
    else if ( *line_buffer == '.' && cmd_len > 0 && shortcuts) {
            if (line_buffer[1] == '$') is4cmd = true ; /* e.g. OP.$ */
            else is4cmd = last4CMD ;
    }
    else if ( *line_buffer == ']' && cmd_len > 1 && chars_ext > 0) {
            if ( *befehl == '[') is4cmd = last4CMD;
    }
    else if ( *line_buffer == '[' && chars_ext > 0) {

            if (cmd_len < 1 ) is4cmd = true ; /* ok, is first char */
         /* else is4cmd = false ; Process it as the beginning of the next command */
    }
    return is4cmd ;
}


void conv_asc2old( char *str, int len ) /* For IDENT_OLD_BAS and 121x series */
{                                       /* The character set is different from ASCII.*/
    int ii ;
    uchar asc, old ;                    //  len = strlen (str) ;

    for ( ii = 2 ; ii < len ; ii++  ) {
        asc=str[ii] ;
        if (asc == 0) break ;
        old = asc ;

        if ((asc > 47 && asc < 58 ) || // Numbers
            (asc > 64 && asc < 91 ))   // upper chars
            old = asc + 16 ;
        else {
            if (asc == 0x60) old = 75 ; // Placeholder for Exp
            if (asc == 0x80) old = 76 ; // Placeholder for FullFrame
            if (asc == ' ' ) old = 17 ;
            if (asc == 34 )  old = 18 ;
            if (asc == '?' ) old = 19 ;
            if (asc == '!' ) old = 20 ;
            if (asc == 35 )  old = 21 ;
            if (asc == '%' ) old = 22 ;
            if (asc == '$' ) old = 24 ;
            if (asc == ',' ) old = 27 ;
            if (asc == ';' ) old = 28 ;
            if (asc == ':' ) old = 29 ;
            if (asc == '@' ) old = 30 ;
            if (asc == '&' ) old = 31 ;
            if (asc == '(' ) old = 48 ;
            if (asc == ')' ) old = 49 ;
            if (asc == '>' ) old = 50 ;
            if (asc == '<' ) old = 51 ;
            if (asc == '=' ) old = 52 ;
            if (asc == '+' ) old = 53 ;
            if (asc == '-' ) old = 54 ;
            if (asc == '*' ) old = 55 ;
            if (asc == '/' ) old = 56 ;
            if (asc == '^' ) old = 57 ;
            if (asc == '.' ) old = 74 ;
            if (asc == '_' ) old = 78 ;
            if (asc == '~' ) old = 77 ;   // 0x7E
            if (asc == 0xFE) old = 0x7E ; // Placeholder for VAL
            // if (asc == 'e' ) old = 75 ;
            else if (asc > 96 && asc < 123) old = asc - 16 ; // lower chars
        }
        str[ii] = (uchar)old ;
    }
}

/* String-change UPPER, special SHARP chars are converted by strupr to false code, undone elsewhere */
char *strupr( char *string )
{
  int  i = 0;
  while ( ( string[i] = toupper( string[i] ) ) != '\0') i++;
  return string;
}

/* String-change LOWER */
char *strlor( char  *string )
{
  int  i = 0;
  while ( ( string[i] = tolower( string[i] ) ) != '\0') ++i;
  return string;
}

/* String-shift left */
char *shift_left( char *string )
{
  int  i = 0;
  while ( ( string[i] = string[i+1] ) != '\0') i++;
  return string;
}

char *shift_left2( char *buffer, char *buffer2 )
{
  shift_left( buffer );
  shift_left( buffer2);
  return buffer;
}

/* String-delete one leading colon */
char *del_colon( char *string )
{
  if ( string[0]==COLON ) shift_left(string);
  return string;
}

/* String-delete leading spaces and count usable white-spaces */
int del_spaces( char *string )
{
  int  i = 0;
  while ( isspace( (uchar) *string ) ) {
        shift_left(string);
        i++;
  }
  return i; /* Restriction: All White Space characters are treated the same, even a tab is counted just like a space. */
}

/* The older series do not allow spaces between commands, but they are allowed in the PC-E/G series.
   Permitted indents from the beginning of the line are supported by this function.*/
int prc_spaces( char *line_buffer, char *line_buffer2, int* ptr_spc_cnt, char* out_line, uint* ptr_i_out_line, uint del_spc_max )
{
  int spc_cnt = 0, error = ERR_OK;

  spc_cnt = del_spaces( line_buffer ) - del_spc_max ;
  if (spc_cnt < 0) spc_cnt = 0 ;
  *ptr_spc_cnt = spc_cnt;

  del_spaces( line_buffer2 );

  if (*line_buffer != 0 ) { /* ignore spaces at end of line */
    if ( *ptr_i_out_line + spc_cnt > cLL -1 ) return ERR_MEM ;
        while (spc_cnt-- > 0) out_line[ (*ptr_i_out_line)++] = 0x20;
  }
  return (error);
}

  /* Sub process tokenizer REMid found */
int prc_REMid( char *line_buffer, char *line_buffer2, char* befehl, char* befehl2, char* merke, char* merke2,
               char* out_line, uint* ptr_i_out_line, uint* ptr_i_token, bool delREMspc)
{           // global uint tokenL
  uint i_out_line = *ptr_i_out_line ;
  int error = ERR_OK, spc_cnt = 0;

  strcpy( befehl, "" ); strcpy( befehl2, "" );
  if  ( tokenL == 2 || *ptr_i_token > 255 ) {  /* 2Byte-Token */
        out_line[i_out_line] = (uchar) ( *ptr_i_token / 256 );
        i_out_line++;
}
  out_line[i_out_line] = (uchar) *ptr_i_token;
  i_out_line++;

  if  ( delREMspc && !strlen(merke2) ) {  /* Delete spaces after REM-Command */
        error = prc_spaces( line_buffer, line_buffer2, &spc_cnt, out_line, &i_out_line, del_spc_cnt) ;
  }
  if ( strlen( merke2 ) ) {
        while ( strlen( merke2 ) ) {
            strcat( befehl2, ( merke2 + strlen( merke2 ) - 1 ) );
            *( merke2 + strlen( merke2 ) - 1 ) = '\0';
        }
        memcpy( &out_line[i_out_line], befehl2, strlen( befehl2 ) );
        i_out_line += strlen( befehl2 );
        strcpy( merke, "" );
        strcpy( befehl, "" ); strcpy( befehl2, "" );
  }
  if (pcgrpId == GRP_E) {
        out_line[i_out_line++] = BAS_E_JMP;
        out_line[i_out_line++] = (uchar) (strlen(line_buffer2) +2);
  }
  while ( !( *line_buffer == '\0' ) ) {
        out_line[i_out_line++] = *line_buffer2;
        shift_left2( line_buffer, line_buffer2 );
  }
  *ptr_i_out_line = i_out_line ;
  return (error);
}

  /* Sub process of tokenizer check leading char if is one-char-token before write out */
int prc_token1C( char *buffer, char *buffer2,
                 char* out_line, uint* ptr_i_out_line, uint* ptr_i_token)
{             // global uint tokenL
  int error = ERR_OK;
  uint i_out_line = *ptr_i_out_line ;
  uint i_token = istoken1C ( (uchar) *buffer );

  if ( i_token ) {   /* replace 1-byte-character with the token and write out */
        if  ( tokenL == 2 || i_token > 255 ) {  /* 2-Byte-Token */
            out_line[i_out_line++] = (uchar) ( i_token >>8 );
        }
        out_line[i_out_line++] = (uchar) i_token;
        shift_left2( buffer, buffer2 );
        *ptr_i_out_line = i_out_line ;
  } /* else not written here because the character will be processed further */
  * ptr_i_token = i_token ;
  return (error);
}

  /* Sub process of tokeniser check leading char if it is a Kanji char or token (PI...) before write out */
bool is_kanji2C ( char *buffer, char *buffer2,
                  char* out_line, uint* ptr_i_out_line, uint* ptr_i_token)
{
  uint i_out_line = *ptr_i_out_line ;
  uchar byte ;
  uint i_token = 0 ;

  if ( strlen(buffer2) < 2 ) return false ;
  byte = (uchar) *buffer2 ; /* Recognize Kanji characters */
  if ( ( ( KANJI_CODE_MIN  <= byte && byte <= Kanji_Code_Max ) && (pcMode &   8) >0 ) ||   /* S JIS-1 part 1 */
       ( ( KANJI_CODE_MIN2 <= byte && byte <= KANJI_CODE_MAX2) && (pcMode &0x10) >0 )  ) { /* S JIS-1 part 2 */

    shift_left2( buffer, buffer2 );
    i_token = istoken2C ( byte, (uchar) *buffer2) ;
    if ( i_token ) { /* replace the Kanji character with the token and write out */
        if  ( i_token > 0xFF ) {  /* 2-byte-token */
            out_line[i_out_line++] = (uchar) ( i_token >>8 );
        }
        out_line[i_out_line++] = (uchar) i_token;
    }
    else { /* write out the Kanji character unchanged */
        out_line[i_out_line++] = byte;
        out_line[i_out_line++] = (uchar) *buffer2 ; // byte2
    }
    shift_left2( buffer, buffer2 );
    *ptr_i_out_line = i_out_line ;
    *ptr_i_token = i_token ;
  }
  else return false ;
  return true ;
}

/* From: http://bytes.com/topic/c/answers/223500-how-replace-substring-string-using-c
   In string "str" replace all occurrences of "orig" with "repl" */
char *replace_str2( const char *str, const char *orig, const char *repl )
{
    char  *ret, *r;
   const  char *p, *q;
  size_t  len_str = strlen(str);
  size_t  len_orig = strlen(orig);
  size_t  len_repl = strlen(repl);
  size_t  count;

  for(count = 0, p = str; (p = strstr(p, orig)); p += len_orig)
  count++;

  ret = malloc(count * (len_repl - len_orig) + len_str + 1);
  if(!ret)
  return NULL;

  for(r = ret, p = str; (q = strstr(p, orig)); p = q + len_orig) {
  count = q - p;
  memcpy(r, p, count);
  r += count;
  strcpy(r, repl);
  r += len_repl;
  }

  strcpy(r, p);
  return ret;
}

/* String-replace (for utf-8 characters also) */
void replace_str( char *str, char *orig, char *repl )
{
  strcpy( str, replace_str2(str, orig, repl));
}

/* String convert of UTF-8 Katakana to Sharp Japanese */
int replace_japanChars ( char *line_buffer, ulong utf8, ulong debug, bool type_asm )
{/* uchar ident from global */
    int   error = ERR_OK;
    char  *ptrUJchar = NULL ;
// Space A0 before Katakana is not used for pocket computers
    char  orig[4] = "｡"; /* UTF8_KATAKANA1, EF BD A1 (- EF BD BF --> [A1]-[BF] ) */
    char  repl[9] = "[A1]";     /* Sharp ext series, and newer */
    int   rpos = 1;
    uchar cc,   /* index UTF-8 table */
          tt ;  /* index Sharp token table */

    if (type_asm) {
        strcpy (repl, "\xA1");
        rpos = 0 ;
    }
// All checked computers of the new series (S1) uses the coding [FE]..
    else if (ident == IDENT_NEW_BAS) {
        strcpy (repl, "[FE][A1]");  /* Sharp new series 1260... */
        rpos = 5 ;
    }
    if (utf8 == 1) {
        ptrUJchar = strchr (line_buffer, UTF8_SET) ; /* First Byte of Japanese UTF-8 char */
        if (ptrUJchar != NULL) {

            cc = (uchar) orig[2] ; //0xA1
            for ( tt = cc ; tt < 0xE0; ++tt ) {
                if (cc == 0xC0) {
                    strcpy(orig,  "ﾀ") ; /* UTF8_KATAKANA2, EF BE 80 (- EF BE 9F --> [C0]-[DF])*/
                    cc = (uchar) orig[2] ; //0x80
                }
                orig[2] = (char) cc;
                if (type_asm)
                    repl[rpos] = (char) tt;
                else {
                    if (ident == IDENT_OLD_BAS && tt < 0xA6)  /* start for 124xDB */
                        sprintf(&repl[rpos], "%02X]", (uchar) 0x4C);/* Filler FUL */
                    else
                        sprintf(&repl[rpos], "%02X]", (uchar) tt);
                }
                if (cLL - strlen(line_buffer) < strlen(repl)<<2) return (ERR_MEM);
                replace_str(line_buffer, orig, repl);
                ++cc ;
            }
        }
    }
    else if (utf8 ==0 && ((pcMode & 0x1C)>0 || (debug & CNV_SJIS)>0) && !type_asm) { /* ANSI with Japanese chars */
        orig[1] = 0;
        for ( tt = 0xA1 ; tt < 0xE0; ++tt ) {
            orig[0] = (char) tt;
            sprintf(&repl[rpos], "%02X]", (uchar) tt);
            if (cLL - strlen(line_buffer) < strlen(repl)<<2) return (ERR_MEM);
            replace_str(line_buffer, orig, repl);
        }
    }
    return (error) ;
}

/* Remove BOM if it was written by UTF-8 editor*/
int remove_BOM ( char *line_buffer )
{
    uint  ii = 0 ;

    if (strlen(line_buffer) > 2 &&
        line_buffer[0]==utf8_BOMstr[0] && line_buffer[1]==utf8_BOMstr[1] && line_buffer[2]==utf8_BOMstr[2]) {
                for ( ii = 0 ; ii < 3 ; ++ii ) shift_left( line_buffer );
                ii = 1 ;
    }
    return (ii) ;
}

/* returns one line from file without the system's native newline sequence (CRLF, CR, LF, ...) */
char *getlineF( char *retstring, ulong maxchars, FILE *datei, uint* ptrLine_cnt, uint* ptrLine_cntN )
{
	ulong  cin = 0;
	 int   igot = 0;
	 char  cgot = 0;
 	 bool  ineol = false;
	 bool  afteol = false;
     uint  line_cntR = *ptrLine_cnt = *ptrLine_cntN;

	while ( ( igot != EOF ) && ( afteol != true ) && ( cin < maxchars ) )
	{
		igot = getc( datei );
		if ( igot != EOF )
		{
			cgot = igot;
			if ( ( cgot != '\x0D' ) && ( cgot != '\x0A' ) )
			{
				if (ineol != true)
				{
					retstring[cin++] = cgot;
				}
				else
				{
					ungetc( igot, datei );
					afteol = true;
				}
			}
			else
			{
				if ( cgot == '\x0A') ++(*ptrLine_cntN); /* line counter with last empty lines */
				else if ( cgot == '\x0D') ++line_cntR ;
				// retstring[cin] = '\0'; Manfred Nosswitz 2011
				ineol = true;
			}
		}
	}
	retstring[cin] = '\0'; /* Finish string */
	// printf("Zeile %u\n",__LINE__); printf("|%s|\n",retstring);
    if ( line_cntR > *ptrLine_cntN) *ptrLine_cntN = line_cntR ;
	if ( ( cin == 0 ) && ( igot == EOF ) )
	  return NULL;
	else {
      ++(*ptrLine_cnt); /* line counter without last empty lines */
      return retstring;
    }
}

/* Post processing of a line, Insert needed colons before some token or Rem char of E/G-series
   These functions have been moved to the tokenizer and are currently being done twice.
   For reliability and later enhancements to newest series, the routine is maintained. */
int PostProcess_G  ( char  REMidC,
                     char* out_line,
                     uint* ptrI_line )
{
     char  line_buffer[cLL];

     uchar  byte ;
       int  error = ERR_OK;
      uint  ii, i_in_line=3, i_out_line=3 , /* start after the line number and length */
            token, token_type ;
     bool   string_auf = false,
            rem_line   = false,
            is_colon = false,
            pre_colon ;

    out_line[*ptrI_line] = '\x00';
    for (ii = 0; ii <= *ptrI_line; ++ii) line_buffer[ii] = out_line[ii] ;

    while ( i_in_line < *ptrI_line && error == ERR_OK ) {

        byte = (uchar) line_buffer[i_in_line++] ;
        out_line[i_out_line++] = byte ;
        if (i_out_line == cLL) {
                error = ERR_MEM ;
                break ;
        }
        pre_colon = is_colon ;
        if ( byte == ':' ) is_colon = true ;
        else is_colon = false ;

        if ( byte == '"' )string_auf = !string_auf;
        else if ( byte == REMidC && REMidC != 0) rem_line = true ;

        if ( !pre_colon && byte == REMidC ) {
                if (i_out_line+1 >= cLL) {
                        error = ERR_MEM ;
                        break ;
                }
                else { /* Insert a colon */
                        out_line[i_out_line-1] = ':' ;
                        out_line[i_out_line++] = byte ;
                }
        } // End if RemIdC

        if ( rem_line || string_auf ) {
            /* read and write string or a REM line */
            while ( i_in_line < *ptrI_line ) {

                byte = (uchar) line_buffer[i_in_line++] ;
                out_line[i_out_line++] = byte ;
                if (i_out_line == cLL) {
                        error = ERR_MEM ;
                        break ;
                }
                if ( !rem_line && byte == '"' ){
                    string_auf = !string_auf;
                    break;
                }
            }
            if (error != ERR_OK) break ;
	}
        /* Is a token ? */
        if ( i_in_line < *ptrI_line && byte == BAS_EXT_CODE ) {

            token = byte << 8;
            byte =  (uchar) line_buffer[i_in_line++] ;
            out_line[i_out_line++] = byte ;

            token |= byte ;
            token_type = TokenType (token) ;

//            if (i_in_line >= *ptrI_line ) break ; does not work with ELSE at Eol

            if ((token_type & TOKEN_REM) >0 ) rem_line = true ;
            else {
                if ( !pre_colon && (token_type & TOKEN_COL) != 0 ) {
                    if (i_out_line+1 >= cLL) {
                            error = ERR_MEM ;
                            break ;
                    }
                    else { /* Insert a colon */
                        out_line[i_out_line-2] = ':' ;
                        out_line[i_out_line-1] = (char) BAS_EXT_CODE ;
                        out_line[i_out_line++] = byte ;
                    }
                } // End if TOKEN_COL
            } // End if no TOKEN_REM
        } // End if no TOKEN
    } // End of line

    if ( error != ERR_OK) for (ii = 0; ii <= *ptrI_line; ++ii) out_line[ii] = line_buffer[ii] ; /* cancel changes */
    else *ptrI_line = i_out_line ;

    return (error) ;
}
/* Convert of E series fixed Ascii numbers to BCD format SHOULD be done here in a later version in one step
   with line numbers because not to do mistakes with token ID later, but NOT implemented until now */

/* Convert fixed line numbers (jump targets) from ASCII to the intermediate format */
int CompileFixedJumpNb( char  REMidC,
                        char* out_line,
                        uint* ptrI_line )
{
     char  line_buffer[cLL],
           line_nbr[cLL] ,
           *ptrErr;

     uchar  byte, byte2 ;
       int  error = ERR_OK;
      uint  ii, kk, i_in_line=3, i_out_line=3 , /* start after the line number and length */
            line_nbr_len, token, token_type ;
      uint  if_jmp[50],    /* IF jump backpatch location, max 50 nested IF allowed by E500 */
            else_jmp[50],  /* ELSE jump packpatch location, max 50 nested IF allowed by E500 */
            if_nbr = 0,    /* number of nested IF tokens */
            else_nbr = 0 ; /* number of ELSE tokens */
    ulong   zeilennummer ;
     uint   bracket_level = 0 ;
     bool   string_auf = false,
            rem_line   = false,
            token_lst  = false ;

    out_line[*ptrI_line] = '\x00';
    for (ii = 0; ii <= *ptrI_line; ++ii) line_buffer[ii] = out_line[ii] ;
    // strncpy (line_buffer, out_line, cLL -1) ; /* method to cancel changes on error, see below */

    while ( i_in_line < *ptrI_line && error == ERR_OK ) {

        byte = (uchar) line_buffer[i_in_line++] ;
        byte2 = (uchar) line_buffer[i_in_line] ;
        out_line[i_out_line++] = byte ;
        if (i_out_line >= cLL) {
                error = ERR_MEM ;
                break ;
        }
        if ( byte == ':' ) {
                token_lst  = false ;
                bracket_level = 0 ;
        }
        else if ( byte == '(' ) ++bracket_level;
        else if ( byte == ')' && bracket_level >0) --bracket_level;
        else if ( byte == '"' ) string_auf = !string_auf;
        else if ( byte == REMidC && REMidC != 0) rem_line = true ;

        if ( rem_line || string_auf ) {
            /* read and write string or a REM line */
            while ( i_in_line < *ptrI_line ) {

                byte = (uchar) line_buffer[i_in_line++] ;
                out_line[i_out_line++] = byte ;
                if ( i_out_line >= cLL ) {
                        error = ERR_MEM ;
                        break ;
                }
                if ( !rem_line && byte == '"' ){
                    string_auf = !string_auf;
                    break;
                }
            }
            if (error != ERR_OK) break ;
        }
        /* E500 series: skip non-tokenized DATA statement and values */
        else if ( pcgrpId == GRP_E && byte == BAS_EXT_CODE && byte2 == 0x5E ) {
            /* GRP_E: read and write DATA (xFE5E) and its values until : or end of the line */
            while ( i_in_line < *ptrI_line ) {
                byte = (uchar) line_buffer[i_in_line++] ;
                out_line[i_out_line++] = byte ;
                if ( i_out_line >= cLL ) {
                    error = ERR_MEM ;
                    break ;
                }
                if ( byte == ':' && !string_auf )
                    break ;
                if ( byte == '"' )
                    string_auf = !string_auf ;
            }
            if (error != ERR_OK) break ;
        }
        /* E500 series: extend IF and ELSE with a forward jump */
        else if ( pcgrpId == GRP_E && byte == BAS_EXT_CODE && (byte2 == 0x56 || byte2 == 0x76) ) {
            /* GRP_E: IF (xFE56) and ELSE (xFE76) tokens require a forward jump */

            if ( i_out_line + 3 >= cLL ) {
                error = ERR_MEM ;
                break ;
            }

            if ( byte2 == 0x76 ) { /* ELSE token */
                if ( else_nbr >= 50 ) { /* Check if max 50 nested ELSE is not exceeded */
                    error = ERR_MEM ;
                    break ;
                }
                if ( if_nbr > 0 ) { /* Backpatch previous IF jump to jump to this ELSE */
                    if_nbr--; /* One fewer IF to backpatch */
                    out_line[if_jmp[if_nbr]] = (uchar) (i_out_line - if_jmp[if_nbr]) ; /* Compute and insert IF jump distance */
                }
                else_jmp[else_nbr++] = i_out_line + 2; /* Remember this ELSE jump location to backpatch later */
            }
            else { /* IF token */
                if ( if_nbr >= 50 ) { /* Check if max 50 nested IF is not exceeded */
                    error = ERR_MEM ;
                    break ;
                }
                if_jmp[if_nbr++] = i_out_line + 2; /* Remember this IF jump location to backpatch later */
            }
            out_line[i_out_line++] = byte2 ; /* Store IF/ELSE token */
            out_line[i_out_line++] = BAS_E_JMP ;
            out_line[i_out_line++] = 0 ; /* Forward IF/ELSE jump distance will be backpatched later */
            i_in_line++;
        }
        else if ((i_in_line+1 <= *ptrI_line && ( /* Is a token ? */
            (   byte == BAS_EXT_CODE    && pcgrpId != GRP_16) ||
            (0xEF < byte && byte < 0xF3 && pcgrpId == GRP_16) ||
            (0xE5 < byte && byte < 0xE9 && pcgrpId == GRP_16) ||
            (   byte == 0xE3            && pcgrpId == GRP_16)  )) ||
            (   byte == ',' && token_lst && bracket_level == 0)     ) {

            /* Is not list of line numbers */
            if ( byte != ',' ) {

                token = byte << 8;
                byte =  (uchar) line_buffer[i_in_line++] ;
                out_line[i_out_line++] = byte ;

                token |= byte ;
                token_type = TokenType (token) ;
            }
            if (i_in_line >= *ptrI_line ) break ;

            if ((token_type & TOKEN_REM) != 0 ) rem_line = true ;
            else {
                if ((token_type & TOKEN_LST) != 0 ) token_lst = true ;
                if ((token_type & TOKEN_LBL) != 0 ) {

                    if (( pcgrpId == GRP_16 && i_out_line+4 >= cLL) ||
                        ( pcgrpId != GRP_16 && i_out_line+3 >= cLL)  ) {
                            error = ERR_MEM ;
                            break ;
                    }
                    byte =  (uchar) line_buffer[i_in_line] ;

                    if (pcgrpId == GRP_E && byte == '*') {
                        /* GRP_E: label * with alphanumeric ASCII chars */

                        if ( i_out_line+4 >= cLL ) {
                            error = ERR_MEM ;
                            break ;
                        }

                        out_line[i_out_line++] = '*' ;
                        out_line[i_out_line++] = BAS_E_LBL ;
                        out_line[i_out_line++] = 0 ; /* Jump compiles to zero, which is resolved at runtime */
                        out_line[i_out_line++] = 0 ;

                        /* Store the alphanumeric label name */
                        byte = (uchar) line_buffer[++i_in_line] ;
                        while ((byte >= '0' && byte <= '9') ||
                               (byte >= 'A' && byte <= 'Z') ||
                               (byte >= 'a' && byte <= 'z')) {
                            if ( i_out_line >= cLL ) {
                                error = ERR_MEM ;
                                break ;
                            }
                            out_line[i_out_line++] = byte ;
                            byte = (uchar) line_buffer[++i_in_line] ;
                        }
                    }
                    else {

                        strcpy(line_nbr, "") ;
                        line_nbr_len = 0;
                        while ('0' <= byte && byte <='9') { /* fixed line number ASCII chars */
                            line_nbr[line_nbr_len] = byte ;
                            byte = (uchar) line_buffer[++line_nbr_len + i_in_line] ;
                        }
                        line_nbr[line_nbr_len] = 0 ; /* str end */

                        if ( byte == 0 || byte == ':' || (byte == ',' && token_lst == true )) {
                            /* convert line number from ASCII to binary */
                            zeilennummer = strtoul( line_nbr, &ptrErr, 0) ;
                            if (*ptrErr != 0) {
                                printf ("%s: Line number %s is not valid\n", argP, line_nbr) ;
                                error = ERR_LINE ;
                            }
                            else if ( zeilennummer > 65279) {
                                printf ("%s: Line number %s is to large\n", argP, line_nbr) ;
                                error = ERR_LINE ;
                            }
                            else if (line_nbr_len >0) {
                                /* write the converted line number */
                                out_line[i_out_line++] = BAS_EXT_LINE_NB ;
                                out_line[i_out_line++] = (uchar) (zeilennummer >> 8) ;
                                out_line[i_out_line++] = (uchar) (zeilennummer & 0xFF) ;
                                if (pcgrpId == GRP_16) out_line[i_out_line++] = 0 ;

                                i_in_line += line_nbr_len ;
                            }
                        } // Is a fixed number, no expression
                    } /* Is a label or fixed number */
                } // End if TOKEN_LBL
            } // End if no TOKEN_REM
        } // End if no TOKEN
        else if ( pcgrpId == GRP_E && (byte == '&' || (byte >= 'A' && byte <= 'Z') || (byte >= 'a' && byte <= 'z')) ) {
            /* GRP_E: decimals should not be translated when occurring in identifiers and hexadecimal numbers */

            byte = byte2;
            while ( (byte >= '0' && byte <= '9') || (byte >= 'A' && byte <= 'Z') || (byte >= 'a' && byte <= 'z') ) {
                out_line[i_out_line++] = byte ;
                byte = (uchar) line_buffer[++i_in_line] ;
                if ( i_out_line >= cLL ) {
                    error = ERR_MEM ;
                    break ;
                }
            }
        }
        else if ( pcgrpId == GRP_E && (byte == '.' || (byte >= '0' && byte <= '9')) ) {
            /* GRP_E: translate decimal number to binary coded */

            bool dbl_prec = false ; /* Double precision flag */
            int decimal_exp = cLL ; /* Exponent -99 to 99 or cLL when undefined */
            uint decimal_nbr_len = 0 ; /* Number of significant digits, length of the mantissa */
            char decimal_nbr[cLL] ; /* Mantissa */
            char *decimal_ptr = decimal_nbr ;

            i_out_line-- ; /* Correction to ignore previous byte stored */

            while ( byte == '0' ) byte = (uchar) line_buffer[i_in_line++] ; /* Leading zeros are irrelevant, skip them */

            while ( byte == '.' || (byte >= '0' && byte <= '9') ) {
                if ( byte == '.' ) {
                    if ( decimal_exp < cLL ) {
                        printf ("%s: Decimal value is not valid\n", argP) ;
                        error = ERR_ORD ;
                    }
                    else {
                        decimal_exp = decimal_nbr_len ; /* Decimal period: set exponent to number of digits */
                    }
                }
                else {
                    decimal_nbr[decimal_nbr_len++] = byte ; /* Fill mantissa with next significant digit */
                }
                byte = (uchar) line_buffer[i_in_line++] ;
            }

            decimal_nbr[decimal_nbr_len] = '\0' ; /* str end */

            if ( decimal_exp == cLL ) decimal_exp = decimal_nbr_len ; /* Set exponent to number of significant digits if no decimal period */

            if ( byte == 'E' || byte == 'D' || byte == 'e' || byte == 'd' ) {
                /* Process the exponent part of the number */

                bool neg_exp = false ; /* Exponent is negative flag */

                dbl_prec = (byte == 'D' || byte == 'd') ; /* D means double precision exponent */

                byte = (uchar) line_buffer[i_in_line++] ;

                if ( byte == '+' ) {
                    byte = (uchar) line_buffer[i_in_line++] ;
                }
                else if ( byte == '-' ) {
                    byte = (uchar) line_buffer[i_in_line++] ;
                    neg_exp = true ; /* Negative exponent */
                }

                if ( byte >= '0' && byte <= '9' ) {
                    /* Parse one or two-digit exponent */

                    while ( byte == '0' ) byte = (uchar) line_buffer[i_in_line++] ; /* Leading zeros in exponent are irrelevant */

                    if ( byte >= '0' && byte <= '9' ) {
                        uint exp = byte - '0' ;
                        byte = (uchar) line_buffer[i_in_line++] ;
                        if ( byte >= '0' && byte <= '9' ) {
                            exp = 10*exp + byte - '0' ;
                            byte = (uchar) line_buffer[i_in_line++] ;
                        }
                        decimal_exp += neg_exp ? -exp : exp ; /* Update the exponent depending on the decimal period */
                        if ( byte >= '0' && byte <= '9' ) {
                            printf ("%s: Decimal value overflow\n", argP) ;
                            error = ERR_ORD ;
                        }
                    }
                }
                else {
                    printf ("%s: Decimal value is missing an exponent\n", argP) ;
                    error = ERR_ORD ;
                }
            }

            if ( decimal_nbr_len > 10 ) {
                /* Double prevision when over 10 significant digits */
                dbl_prec = true ;
            }

            while ( *decimal_ptr == '0' ) {
                /* Normalize mantissa by shifting out leading zeros and adjusting the exponent */
                decimal_ptr++ ;
                decimal_nbr_len--;
                decimal_exp-- ;
            }

            if ( decimal_nbr_len > 20 ) {
              /* Over 20 digits: round up when 21st digit is >=5 for example 99999999999999999999.5 => 1D20 */
              if ( decimal_ptr[20] >= '5' ) {
                for (kk = 20; kk > 0; kk--) {
                  if ( decimal_ptr[kk-1] < '9' ) {
                    decimal_ptr[kk-1]++;
                    break;
                  }
                  decimal_ptr[kk-1] = '0';
                }
                if (kk == 0) {
                  for (kk = 19; kk > 0; kk--)
                    decimal_ptr[kk] = decimal_ptr[kk-1];
                  decimal_ptr[0] = '1';
                  decimal_exp++;
                }
              }
            }

            if ( *decimal_ptr != '\0' )
                decimal_exp-- ; /* Adjust exponent for first significant (nonzero) digit, the digit before the decimal period */

            if ( decimal_exp < -99 ) {
                printf ("%s: Decimal value underflow\n", argP) ;
                error = ERR_ORD ;
            }
            else if ( decimal_exp > 99 ) {
                printf ("%s: Decimal value overflow\n", argP) ;
                error = ERR_ORD ;
            }
            else {
                if ( byte == '#' ) {
                    dbl_prec = true ; /* Double precision when decimal has a DBL # marker */
                    i_in_line++ ;
                }
                for ( kk = decimal_nbr_len /* - (decimal_ptr - decimal_nbr) */; kk < (dbl_prec ? 20 : 10); kk++ )
                    decimal_ptr[kk] = '0' ; /* Fill rest of the mantissa with zeros */
                decimal_ptr[kk] = '\0' ; /* str end */
                if ( i_out_line + (dbl_prec ? 13 : 8) >= cLL ) {
                    error = ERR_MEM ;
                    break ;
                }
                out_line[i_out_line++] = BAS_E_NB ;
                out_line[i_out_line++] = (dbl_prec ? 1 : 0) ;   /* 1 for DBL, 0 otherwise */
                out_line[i_out_line++] = decimal_exp ;          /* Store exponent in two's complement */
                for ( kk = 0; kk < (dbl_prec ? 20 : 10); kk += 2 ) /* Store 10 or 20 digits BCD mantissa */
                    out_line[i_out_line++] = ((decimal_ptr[kk] - '0') << 4) | (decimal_ptr[kk+1] - '0') ;
            }

            i_in_line-- ; /* Backup to last byte consumed */
        }
    } // End of line

    if ( pcgrpId == GRP_E ) {
        /* Resolve forward IF/ELSE jumps */
        for ( kk = 0; kk < if_nbr; kk++ ) /* backpatch previous IF jumps to jump to the end of the line */
          out_line[if_jmp[kk]] = i_out_line - if_jmp[kk] + 1 ;
        for ( kk = 0; kk < else_nbr; kk++ ) /* backpatch previous ELSE jumps to jump to the end of the line */
          out_line[else_jmp[kk]] = i_out_line - else_jmp[kk] + 1 ;
    }

    // if ( error != ERR_OK) strncpy (out_line, line_buffer,  cLL -1) ; /* cancel changes */
    if ( error != ERR_OK) for (ii = 0; ii <= *ptrI_line; ++ii) out_line[ii] = line_buffer[ii] ; /* cancel changes */

    else *ptrI_line = i_out_line ;

    return (error) ;
}


int ReadCodepointsFromFile (char*  ptrCodeSpaceFile) /* Characters code file string */
{ /* globals    uint code_cnt = 0  ;  number of tokens from character code definition file
    char chrstring[cMAXNBCH][cLCH] ;  char codestring[cMAXNBCH][cLCH];  ushort codepoint [cMAXNBCH] ; */

    char    line_buffer[cLL] = "" ,
            key_buffer[7] = "0x",
            *ptrErr, *ptrToken, *ptrToken2 ;
    uint    codeval = 0, code_table = 0 ;
    uint    line_cnt = 0, line_cntN = 0, ii ;
    int     error_tmp, error = ERR_OK ;
    FILE*   ptrFk = NULL ;      /* codepoint file pointer */

    /* Open the chrstring file */
    ptrFk = fopen (ptrCodeSpaceFile, "rb") ;
    if (ptrFk == NULL) {
        printf ("\n%s: Can't open the code points file: %s\n", argP, ptrCodeSpaceFile) ;
        error = ERR_FILE ;
        return (error) ;
    }

    while ( getlineF( line_buffer, cLL, ptrFk, &line_cnt, &line_cntN ) != NULL ) {
        if (line_cnt < 2) remove_BOM ( line_buffer ) ; // utf8_chars = true
        if ( strlen(line_buffer) < 3) continue ;
        if ((line_buffer[0] == '\'' || line_buffer[0] == ';') && line_buffer[1] != '=') continue ;
        if (code_cnt >= cMAXNBCH ) {
            printf ("\n%s: To much (%i ) code points reached in file: %s\n", argP, code_cnt, ptrCodeSpaceFile) ;
            error = ERR_MEM ;
            break ;
        }

        ptrToken = strchr (&line_buffer[1], ':') ;                      // with priority  Codepoint:=HHHH
        if (ptrToken != NULL) {
            ptrToken2 = ptrToken ;
            ptrToken2++ ;

            if (*ptrToken2 == '=' ) {
                *ptrToken = '\0' ;
                ptrToken++ ;
            }
            else ptrToken = NULL ;
        }
        if (ptrToken == NULL) ptrToken = strchr (&line_buffer[1], '=') ;// normal  Codepoint=HHHH
        if (ptrToken != NULL) {
            *ptrToken = '\0' ;
            ptrToken++ ;
            if ( strchr (ptrToken, '=')) *(strchr (ptrToken, '=')) = '\0'; /* in line comments with second '='*/

            if (*ptrToken == '[') {
                if (strlen(ptrToken)< cLCS && ptrToken[strlen(ptrToken)-1] == ']') {
                    strncpy (codestring[code_cnt], ptrToken, cLCS-1) ;
                    /* This blocks the assignment of subsequent code points when recognizing the Sharp special characters in the main program */
                    codepoint[code_cnt] = 0xFFFF ;
                    strncpy (chrstring[code_cnt++], line_buffer, cLCH-1);
                }
                else {
                    printf ("%s: Code point '%s' has not a placeholder format in line %i of\n file %s\n", argP, ptrToken, line_cnt, ptrCodeSpaceFile) ;
                    error = ERR_FMT ;
                    break ;
                }
            }
            else {
                /* convert token code from hex string to binary */
                strncpy (&key_buffer[2], ptrToken, 4) ;
                codeval = strtoul( key_buffer, &ptrErr, 0) ;
                if (*ptrErr != 0) {
                    printf ("%s: Code point '%s' is not a valid hex in line %i of\n file %s\n", argP, ptrToken, line_cnt, ptrCodeSpaceFile) ;
                    error = ERR_FMT ;
                    break ;
                }
                else if (codeval > 0xFFFF || (codeval & 0xFF) == 0) {
                    printf ("%s: Code point %s value is out of range in line %i of file %s.\n", argP, ptrToken, line_cnt, ptrCodeSpaceFile) ;
                    error = ERR_FMT ;
                    break ;
                }
                else {
                    ii = 1;
                    strcpy (codestring[code_cnt], "[") ;
                    code_table = codeval >> 8 & 0xFF ;
                    if (codeval > 0xFF ) {
                        if (pcgrpId == GRP_E) {
                            if ((pcMode & 8) >0) {
                                if (code_table > Kanji_Code_Max && code_table < KANJI_CODE_MAXE +1)
                                    Kanji_Code_Max = KANJI_CODE_MAXE ; /* extend area for E500K */
                                else if (code_table > KANJI_CODE_MIN2 -1 && code_table < KANJI_CODE_MAX2 +1)
                                    pcMode |= 0x10 ;  /* activate 2. area */
                            }
                        }
                        sprintf(&codestring[code_cnt][ii], "%02X", (uchar) (codeval >>8)) ;
                        strcat(codestring[code_cnt], "][") ; // "[HH][HH]"
                        ii = 5;
                    }
                    sprintf(&codestring[code_cnt][ii], "%02X", (uchar) (codeval & 0xFF)) ;
                    strcat(codestring[code_cnt], "]") ;

                    codepoint[code_cnt] = codeval ;
                    strncpy(chrstring[code_cnt++], line_buffer, cLCH-1);
                }
            } // no placeholder
        }
        else printf ("%s Missing '=' in file %s, line %i.\n", argP, ptrCodeSpaceFile, line_cnt) ;
    }
    error_tmp = error ;

    /* Close the code space file */
    if (ptrFk != NULL) {
        error = fclose (ptrFk) ;
        if (error != ERR_OK) {
            printf ("\n%s: Can't close the code points file\n", argP) ;
            error = ERR_FILE ;
        }
    }
    if (error == ERR_OK) error = error_tmp;
    return (error) ;
}


int ReadKeywordsFromFile (char*  ptrKeywordFile) /* Keyword file string */
{ /* globals
    uint key_cnt = 0 ;      number of tokens from keyword definition file
    char keyword[cMAXNBTK][cLTK] ;
    ushort keyval [cMAXNBTK] ; */

    char    line_buffer[cLL] = "" ,
            key_buffer[7] = "0x",
            *ptrErr, *ptrToken, *ptrToken2 ;
    uint    line_cnt = 0, line_cntN = 0 ;
    int     error_tmp, error = ERR_OK ;
    FILE*   ptrFk = NULL ;                  /* keyword file pointer */

    /* Open the keyword file */
    ptrFk = fopen (ptrKeywordFile, "rb") ;
    if (ptrFk == NULL) {
        printf ("\n%s: Can't open the keyword file: %s\n", argP, ptrKeywordFile) ;
        error = ERR_FILE ;
        return (error) ;
    }

    while ( getlineF( line_buffer, cLL, ptrFk, &line_cnt, &line_cntN ) != NULL ) {
        if (line_cnt < 2) remove_BOM ( line_buffer ) ; // utf8_chars = true
        if ( strlen(line_buffer) < 3) continue ;
        if ((line_buffer[0] == '\'' || line_buffer[0] == ';') && line_buffer[1] != '=') continue ;
        if (key_cnt >= cMAXNBTK ) {
            printf ("\n%s: To much (%i ) keywords reached in file: %s\n", argP, key_cnt, ptrKeywordFile) ;
            error = ERR_MEM ;
            break ;
        }

        ptrToken = strchr (&line_buffer[1], ':') ;                      // with priority  Token:=HHHH
        if (ptrToken != NULL) {
            ptrToken2 = ptrToken ;
            ptrToken2++ ;

            if (*ptrToken2 == '=' ) {
                *ptrToken = '\0' ;
                ptrToken++ ;
            }
            else ptrToken = NULL ;
        }
        if (ptrToken == NULL) ptrToken = strchr (&line_buffer[1], '=') ;// normal  Token=HHHH
        if (ptrToken != NULL) {
            *ptrToken = '\0' ;
            ptrToken++ ;
            if ( strchr (ptrToken, '=')) *(strchr (ptrToken, '=')) = '\0'; /* Inline comments with second '='*/

            /* convert token code from hex string to binary */
            strncpy (&key_buffer[2], ptrToken, 4) ;
            keyval[key_cnt] = strtoul( key_buffer, &ptrErr, 0) ;
            if (*ptrErr != 0) {
                printf ("%s: Token '%s' is not a valid hex in line %i of\n file %s\n", argP, ptrToken, line_cnt, ptrKeywordFile) ;
                error = ERR_FMT ;
                break ;
            }
            else if ((keyval[key_cnt] & 0xFF) == 0) {
                printf ("%s: Token %s value is out of range in line %i of file %s\n", argP, ptrToken, line_cnt, ptrKeywordFile) ;
                error = ERR_FMT ;
                break ;
            }
            else {  // printf ("debug: line %i. %s \t%02X\n", line_cnt, line_buffer, keyval[key_cnt]) ;
                    strncpy(keyword[key_cnt++], line_buffer, cLTK-1);
            }
        }
        else printf ("%s Missing '=' in file %s, line %i.\n", argP, ptrKeywordFile, line_cnt) ;
    }
    error_tmp = error ;

    /* Close the keyword file */
    if (ptrFk != NULL) {
        error = fclose (ptrFk) ;
        if (error != ERR_OK) {
            printf ("\n%s: Can't close the keyword file\n", argP) ;
            error = ERR_FILE ;
        }
    }
    if (error == ERR_OK) error = error_tmp;
    return (error) ;
}


void PrintHelp (void)  /* 1         2         3         4         5         6         7         8 */
{             /* 12345678901234567890123456789012345678901234567890123456789012345678901234567890 */
	printf ("Usage: %s [Options] SrcFile [DstFile]\n", argP) ;
	printf ("SrcFile         : BASIC-program text file\n") ;
	printf ("DstFile         : Binary image file (default: SrcFile.img or .asc)\n") ;
	printf ("Options:\n") ;
	printf ("-p, --pc=NUMBER : Sharp pocket computer, currently supported\n") ;
	printf ("                   1150, 1211, 1245, 1248, 1251, 1261, 1280, 1350, 1360, 1401\n") ;
	printf ("                   1402, 1403, 1421, 1425, 1430, 1445, 1450, 1460, 1475, 1500\n") ;
	printf ("                   1600, E220, G850 and more (default: 1500),\n") ;
	printf ("                    Only at E500 series must be used the commands 'TEXT'\n") ;
	printf ("                    and then 'BASIC' after the transfer of an img.\n") ;
	printf ("-k, --keywords=KeywordFile (for tokens of add-on hardware, max. use: 3 times)\n") ;
	printf ("-o, --codepoints=CodepointFile (code points def. file, maximum use: 2 times)\n") ;
	printf ("-t, --type=TYPE : destination file type (default: img),  asc,txt,asm,asm5,asm6\n") ;
	printf ("                  img  BASIC Program binary image with intermediate code\n") ;
	printf ("                  txt  TEXT mode image,  asc  ASCII file: Text Menu Cmt/serial\n") ;
	printf ("-e, --endmark   : Append an end mark to the file,     -u, --utf8= (yes),no,dos\n") ;
	printf ("-q, --quiet     : Quiet mode (minimal display output) -a, --auto= AUTO_inc(10)\n") ;
	printf ("    --version   : Display version information --help: Display this information\n") ;
    printf ("-l, --level=SUM : 1     Don't/Do compile fixed line no. (in line) =0x1000:ELbl\n") ;
    printf ("   (max use 2x) : 2     Append missing apostrophes at end of line =0x2000: Bgn\n") ;
    printf ("                : 4     Don't replace shortcuts(.) with commands, =0x100: SJIS\n") ;
    printf ("                : 8     Don't convert to upper case, 0x10 Disable preprocessor\n") ;
    printf ("                : 0x80 (0x20) Print lines in,        0x40 Print values out\n") ;
    printf ("                : 0x800 Depress some line errors, result may not editable") ; /* ERR_LIGN */
	/*                 debug : 0x10     Deactivate preprocessor with special chars conversion
                             : 0x100  = CNV_SJIS Force the conversion of Japanese characters (from UTF8) to (FE)&hA1-DF
                             : 0x200  = BAS_AUTO Replace missing/ all line numbers after first text line
                                        according to an AUTO statement (for .asm), No Renumber in the lines!
                             : 0x400  = SPC_LINES_OK flag, don't delete (empty) lines if with spaces
                             : 0x1000 = BAS_EXT_FRMT flag, switch convert/not E-Label E/older Series
                             : 0x2000 = INS_APST flag, insert an apostrophe at the beginning of each line (for PC-Macro asm)
                             : 0x100000 Deactivate build in token, only use loaded tokens only
                             : BAS_EOF_INCL = 0x200000, -e Append an EOF mark to the output file
	*/
    #ifdef __APPLE__
        /* Mac specific here, test __linux__ not for _WIN32 shell */
        printf ("\n") ;
    #endif
    #ifdef __linux__
        /* Test __linux__ */
        printf ("\n") ;
    #endif
    exit( EXIT_SUCCESS );
}


/* Copying conditions: GNU Lesser General Public License version (GPLv3), see COPYING.LESSER and this supplement:
   You may not use any code from the "Pocket Tools for SHARP Pocket Computers" project if you do not name
   the original authors in the code and documentation or if you remove this notice or the following function. */
void PrintVersion (uint Qcnt)
{   char  argPU[cLPF] = "" ;
	strcpy(argPU, argP) ;
	printf ("%s (%s) version: %s for Pocket Tools 2.1, %s \n", argP, strupr(argPU), PVERSION, PDATE ) ;
	if (!Qcnt) {
	printf ("Authors: Pocket -> www.pocketmuseum.com\n") ; /* Please do not remove */
	printf ("         2001-2005 Joachim Bohs\n") ; /* Ported from his software for an interface (80s)*/
	printf ("         2010-2013 Norbert Roll, Manfred Nosswitz, Olivier De Smet\n") ;
	printf ("         2013-2022 Torsten Muecker\n") ;      /* Please do not remove */
	printf ("         2021      Robert van Engelen\n") ;
	printf ("        for complete list see the manual and the source code\n") ;
	printf ("This is free software; see the source for copying conditions. There is NO\n") ;
    printf ("warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE,\n") ;
    printf ("to the extent permitted by law.\n") ;
	}
	exit( EXIT_SUCCESS ); /* no arguments were passed */
}


void MoreInfo (int error)
{	printf("%s: '%s --help' gives you more information\n", argP, argP) ;
	exit( error ); /* no arguments were passed */
}   // Before debugging, you should set a breakpoint here.


int main( int argc, char **argv )  /* (int argc, char* argv[]) */
{               /* 0=SrcFile 1=[DstFile] 2=[-t] 3=[-p] 4=[-l] 5=[-k] 6=[-k] 7=[-k] 8=[-o] 9=[-o] 10=[-u] 11=[-a] 12=[2.-l] */
        char  argD[13][cLPF] = { "", "", "img", "1500", DEBUG_ARG, "", "", "", "", "", "no", "", "" }, \
	          line_buffer[cLL] = "", line_buffer2[cLL] = "", line_nbr[cLL] = "", \
              out_line[cLL] = "", befehl[cLC] = "", befehl2[cLC] = "", merke[cLC] = "", merke2[cLC] = "", \
              bas_eol = BAS_NEW_EOL, bas_eof = BAS_NEW_EOF, \
		      *ptrErr;                                  /* befehl: command, merke: note */
        char  argS[cLPF] = "", *ptrToken ,
              spec_str[]= "[FF]", spec_chr[]= "\xFF";   /* working area for replace of placeholders */
        char  REMidC = 0, ins_apst = '"' ;              /* char for 2. REM ID 16/E/G, Insert apostrophe for text or assembler lines */
         int  asm_id = 0, ins_spc1 = 0 ;                /* Insert space at begin of line, for assembler source operation codes */

         int  is4cmd = false ;                          /* is an allowed character for a command */
        uint  command_len_min = 2 ;                     /* minimum length of a command with a token*/
	    uint  ii, i_token = 0, i_token1C = 0, i_out_line = 0, nbByte = 0, tmpl = 0, inline_len2 = 0, \
	          FILEcnt = 0, Tcnt = 0, PCcnt = 0, Qcnt = 0, Ecnt = 0, Lcnt = 0, Kcnt = 0, Ocnt = 0, Ucnt = 0, Acnt = 0, \
	          /* pcId = 0, tokenL = 0, REMid = 0, key_cnt = 0, moved to global */ \
	          line_cnt = 0, line_cntN = 0, src_type = SOURCE_BAS, \
	          line_nbr_len = 0, token_type = 0, token_type1 = 0, bracket_level = 0, /* tokenizer variables, bracket_level for ON i GOTO v(0,0) */ \
	          line_nbb_pos = 0, line_len_pos = 2,       /* default position-1 of line number bytes and length in every image line   */
	          line_len_bytes = 1,                       /* number of bytes for length or address offset to next in every image line */
	          line_lc = LINE_LC_SHA;                    /* line length calculation offset - negative */
       uchar  type, lnb_order = B_ENDIAN_BIG,           /* Byte order with Sharp PCs, MZ other */
                    lln_order = B_ENDIAN_LITTLE,        /* Byte order of other computer with 2-byte length */
                    llc_mode  = B_LINE_L_REL;

       ulong  debug = 0, utf8 = 16, codecnv_opt = 0 ;   /* utf-8 option and subtype */
	   ulong  pre_zeilennr = 0, zeilennummer = 0,       /* zeilennummer: line number, pre_zeilennr: last (old_zeilennr) */
              auto_inc = AUTO_INC,                      /* default increment value for AUTO line no. */
              base_addr = 0,                            /* Begin BASIC for computers (E500) with absolute pointers to the next BASIC line */
              total = 0 ;                               /* Byte counter for the image */
	    FILE  *dateiein, *dateiaus;                     /* dateiein: File In, dateiaus: File Out */

	     char** CodeC = CodeE437 ;                      /* utf8-table for code page 437 */
	     char** CodeC2= CodeE437_2atrans ;              /* ascii transcription for code page 437 */
	     uint CodeC_offset = CodeE437_offset ;          /* start offset of tables */

	    bool  string_auf = false, delREMspc = false, cnvstr_upr = false, cnv_Elabel = false, type_asm = false, auto_new = false ;
        bool  new_arg = false, old_arg = false, InsertMergeMark = false, pre_Elabel = false, pre_colon = false ; // utf8_chars = false

	     int  option_index, i, j, k, l, error = ERR_OK, c = 0, spc_cnt = 0, spc_cnt1 = 0 ;
  static int  longval;

   const int  Token_Nb = 3 ;
       char*  oldToken[] = { "PC:", "/Q", "/?" } ; /* TOKEN_NB */
       char*  newToken[] = { "-p" , "-q", "-h" } ; /* strlen 2 only */

	struct option long_options[] =
	{
		{"type",    required_argument, NULL,      't'},
		{"pc",	    required_argument, NULL,      'p'},
		{"quiet",   no_argument,       NULL,      'q'},
		{"endmark", no_argument,       NULL,      'e'},
        {"level",   required_argument, NULL,      'l'},
        {"keywords",required_argument, NULL,      'k'},  /* keyword definition file */
        {"codepoints",required_argument,NULL,     'o'},  /* code space definition file */
		{"utf8",    optional_argument, NULL,      'u'},
		{"auto",    optional_argument, NULL,      'a'},
		{"version", no_argument,       &longval,  'v'},  /* long option only */
		{"help",    no_argument,       NULL,      'h'},
	        {0, 0, 0, 0}
	};

	/* ProgramName */
	if      (strrchr (argv[0], '\\')) strcpy(argP, 1 + strrchr (argv[0], '\\'));  /* Windows path separator '\' */
	else if (strrchr (argv[0], '/')) strcpy(argP, 1 + strrchr (argv[0], '/'));    /* Linux   path separator '/' */
	else strcpy(argP, argv[0]);
	if ( strrchr (argP, '.')) *(strrchr (argP, '.')) = '\0';                      /* Extension separator '.' */


    /* check, if the old argument format is used */
    for (i = 1; i < argc; ++i) {// 1. argument is program
        if ( *argv[i] == '-' ) {
                new_arg = true ;
                break ;
        }
        strncpy (argS, argv[i], cLPF -1) ;
        strupr(argS) ;
        ptrToken = strstr (argS, "PC:") ; /* PC: */
        if (ptrToken == argS) {
                old_arg = true ;
                break ;
        }
        if ( strcmp(argS, "/Q") == 0 ) old_arg = true ;
        if ( strcmp(argS, "/?") == 0 ) old_arg = true ;
    }
    if ( !new_arg && old_arg) {
        printf("%s: Old format of arguments was detected", argP);
        for (i = 1; i < argc; ++i) { // 1. argument is program
            strncpy (argS, argv[i], cLPF -1) ;
            strupr(argS) ;
            for ( j = 0 ; j < Token_Nb ; ++j ) { // old TOKEN_NB /
                ptrToken = strstr (argS, oldToken[j]) ;
                if (ptrToken == argS) { // replace on old argument token /
                    for ( k = 0 ; k < 2 ; ++k ) { // new_token length 2 /
                        argv[i][k] = newToken[j][k] ;
                    }  // next char
                    k = 2 ;
                    l = strlen (oldToken[j]) ;
                    if (l > k) { // shift argument content to left /
                        do { argv[i][k++] = argv[i][l]; }
                        while (argv[i][l++]!= 0) ;
                    }
                    ++c;
                    break ;
                } // END if old token found
            } // next old token
        } // next argv
        printf(" and %i arguments converted!\n", c);
    } // END if old argv


	while (1) {

	/* getopt_long stores the option index here. */
        option_index = 0;

        c = getopt_long (argc, argv, "t:p:qel:k:o:u::a::vh", long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)  break;

	switch (c)
          {
		case 't': strncpy( argD[2], optarg, cLPF-1); ++Tcnt; break;
		case 'p': strncpy( argD[3], optarg, cLPF-1); ++PCcnt; break;
		case 'q': ++Qcnt; break;
		case 'e': ++Ecnt; break;
        case 'l': { if (Lcnt < 2) strncpy( argD[4+8*Lcnt], optarg, cLPF-1);
                    ++Lcnt; break; }
        case 'k': { if (Kcnt < 3) strncpy( argD[5+Kcnt], optarg, cLPF-1);
                    ++Kcnt; break; }
        case 'o': { if (Ocnt < 2) strncpy( argD[8+Ocnt], optarg, cLPF-1);
                    ++Ocnt; break; }
        case 'u': { if ( optarg != 0 ) strncpy( argD[10], optarg, cLPF-1);
                    ++Ucnt; break; }
        case 'a': { if ( optarg != 0 ) strncpy( argD[11], optarg, cLPF-1);
                    ++Acnt; break; }
		case 'h': PrintHelp (); break;
		case 0:
		  switch (longval) {
		    case 'v': PrintVersion (Qcnt); break;
		    // case 'h': PrintHelp (); break;
		  } break;
        case '?':
                  printf("%s: Unknown argument for '%s'\n", argP, argP);
		default : MoreInfo (ERR_SYNT); break;
          }
	}

	if (optind < argc) /* get non-option ARGV-elements */
    {
      while (optind < argc) {
	    strncpy(argD[FILEcnt!=0], argv[optind++], cLPF-1);
	    ++FILEcnt;
	  }
    }

	if ((FILEcnt > 2) || (Tcnt > 1) || (PCcnt> 1) || (Lcnt > 2) ||
           (Kcnt > 3) || (Ocnt > 2) || (Ucnt > 1) || (Acnt > 1) ) {
                       printf("%s: [E] Too many arguments of same type for '%s'\n", argP, argP); MoreInfo (ERR_SYNT);
    }
    else if ((Qcnt > 1) || (Ecnt > 1)) {
                       printf("%s: [W] Too many arguments of same type for '%s'\n", argP, argP);
    }
	if (FILEcnt < 1) { printf("%s: Missing file operand after '%s'\n", argP, argP); MoreInfo (ERR_SYNT); }

    /* Convert debug in a long */
    debug = (ulong) strtol (argD[4], &ptrErr, 0) ;
    if (*ptrErr != 0) {
        debug = 0 ;
        printf ("%s: Convert debug level number from '%s' is not valid\n", argP, argD[4]) ;
        MoreInfo (ERR_ARG);
    }
    debug = debug | (ulong) strtol (argD[12], &ptrErr, 0) ;
    if (*ptrErr != 0) {
        debug = 0 ;
        printf ("%s: Convert debug level number2 from '%s' is not valid\n", argP, argD[12]) ;
        MoreInfo (ERR_ARG);
    }
    if (Ecnt > 0) debug |= BAS_EOF_INCL ;
    if ((debug & ERR_LIGN) >0) err_line_ign = true ;
    if ((debug & 0x04) >0) shortcuts = false ;
    if (Acnt > 0 && (debug & BAS_AUTO)>0 ) auto_new = true; /* With both options set: delete existing line no. after first text line */
                                                            // if (debug & 0x400 ) ; // DEBUG code
    /* source text format */
    if ( Ucnt==0 || strcmp (argD[10], "yes") == 0) utf8 = 1 ;
    else if (strcmp (argD[10], "no" ) == 0) utf8 = 0 ;
    else if (strcmp (argD[10], "asc") == 0 || strcmp (argD[10], "2asc") == 0) utf8 = 0 ;
    else if (strcmp (argD[10], "dos") == 0 || strcmp (argD[10], "2dos") == 0) utf8 = UTF8_DOS ;
    else if (strcmp (argD[10], "esc") == 0) utf8 = 0 ;
    else if (strcmp (argD[10], "escx") == 0) {
            utf8 = 0; codecnv_opt = UTF8_ESCX ;
    }
    else if (strcmp (argD[10], "bom") == 0) utf8 = 1 ; /* UTF8_BOM will be recognized automatically */
    if (utf8 > 8) {
        printf ("%s: Wrong value for -u\n", argP) ;
        MoreInfo (ERR_ARG);
    }

    /* type part 1 */
    (void) strlor (argD[2]) ;
    type = TYPE_NOK ;

    if (strcmp (argD[2], "img") == 0) type = TYPE_IMG ;
    else if (strcmp (argD[2], "txt") == 0) type = TYPE_TXT ;
    else if (strcmp (argD[2], "asc") == 0) type = TYPE_ASC ;
    else if (strcmp (argD[2], "bas") == 0) type = TYPE_ASC ;
    /* more checks after PC Ident was read */

	/* Check PC Ident */
        i = 3 ;
        if (strlen (argD[i]) == 0) {
            pcId = 1500 ;      // default pcId
        }
        else {
            strupr (argD[i]) ;
            if (strlen(argD[i])>2 &&
                strcmp(&argD[i][strlen(argD[i])-3], "JAP")==0) argD[i][strlen(argD[i])-2] ='\0'; /* Naming in PockEmul */
            else if (strlen(argD[i])>1 && 
                strcmp(&argD[i][strlen(argD[i])-2], "K2")==0) {
                argD[i][strlen(argD[i])-1]='\0'; /* E500K2, 2nd character area */
                pcMode|=0x1C ;
            }
            if (strcmp(&argD[i][strlen(argD[i])-1], "J")== 0) pcMode|=4;        /* Japanese version, E500 series */
            else if (strcmp(&argD[i][strlen(argD[i])-1], "K")== 0) 
                pcMode|=0xC;                                                    /* E500 series with Kanji driver */

            if (strcmp (argD[i], "PA-500") == 0){strcpy (argD[i],  "1100") ; pcMode|=4;}
            else if (strcmp (argD[i], "EL-6300")== 0) strcpy (argD[i],  "1100") ;
            else if (strcmp (argD[i], "6300")   == 0) strcpy (argD[i],  "1100") ;
            else if (strcmp (argD[i], "1110")   == 0) strcpy (argD[i],  "1245") ;
            else if (strcmp (argD[i], "1140")   == 0) strcpy (argD[i],  "1150") ;
            else if (strcmp (argD[i], "1210")   == 0) strcpy (argD[i],  "1211") ;
            else if (strcmp (argD[i], "1210H")  == 0) strcpy (argD[i],  "1211") ;
            else if (strcmp (argD[i], "1212")   == 0) strcpy (argD[i],  "1211") ;
            else if (strcmp (argD[i], "1246S")  == 0) strcpy (argD[i],  "1246") ;
            else if (strcmp (argD[i], "1246DB") == 0){strcpy (argD[i],  "1146") ; pcMode|=4;}
            else if (strcmp (argD[i], "1248DB") == 0){strcpy (argD[i],  "1148") ; pcMode|=4;}
            else if (strcmp (argD[i], "D200")   == 0) strcpy (argD[i],  "1248") ;
            else if (strcmp (argD[i], "LAMBDA2")== 0) strcpy (argD[i],  "1248") ;
            else if (strcmp (argD[i], "RAMUDA10")== 0) strcpy (argD[i], "1248") ;
            else if (strcmp (argD[i], "1250A")  == 0) strcpy (argD[i],  "1250") ;
            else if (strcmp (argD[i], "1251H")  == 0) strcpy (argD[i],  "1251") ;
            else if (strcmp (argD[i], "1252H")  == 0) strcpy (argD[i],  "1251") ;
            else if (strcmp (argD[i], "1252")   == 0) strcpy (argD[i],  "1251") ;
            else if (strcmp (argD[i], "1253H")  == 0) strcpy (argD[i],  "1251") ;
            else if (strcmp (argD[i], "1253")   == 0) strcpy (argD[i],  "1251") ;
            else if (strcmp (argD[i], "1270")   == 0) strcpy (argD[i],  "1248") ;
            else if (strcmp (argD[i], "1260H")  == 0) strcpy (argD[i],  "1260") ;
            else if (strcmp (argD[i], "1260J")  == 0){strcpy (argD[i],  "1260") ; pcMode|=4;}
            else if (strcmp (argD[i], "1261J")  == 0){strcpy (argD[i],  "1261") ; pcMode|=4;}
            else if (strcmp (argD[i], "1262J")  == 0){strcpy (argD[i],  "1262") ; pcMode|=4;}
            else if (strcmp (argD[i], "1280J")  == 0){strcpy (argD[i],  "1280") ; pcMode|=4;}
            else if (strcmp (argD[i], "1285")   == 0) strcpy (argD[i],  "1280") ;
            else if (strcmp (argD[i], "1285J")  == 0){strcpy (argD[i],  "1280") ; pcMode|=4;}
            else if (strcmp (argD[i], "1350J")  == 0){strcpy (argD[i],  "1350") ; pcMode|=4;}
            else if (strcmp (argD[i], "1360J")  == 0){strcpy (argD[i],  "1360") ; pcMode|=4;}
            else if (strcmp (argD[i], "1360K")  == 0){strcpy (argD[i],  "1360") ; pcMode|=0xC;} /* also Kanji */
            else if (strcmp (argD[i], "1365")   == 0) strcpy (argD[i],  "1360") ;
            else if (strcmp (argD[i], "1365K")  == 0){strcpy (argD[i],  "1360") ; pcMode|=0xC;} /* also Kanji */
            else if (strcmp (argD[i], "1401V1") == 0) strcpy (argD[i],  "1401") ;
            else if (strcmp (argD[i], "1401V2") == 0) strcpy (argD[i],  "1402") ;
            else if (strcmp (argD[i], "1403H")  == 0) strcpy (argD[i],  "1403") ;
            else if (strcmp (argD[i], "1404")  == 0)  strcpy (argD[i],  "1403") ;
            else if (strcmp (argD[i], "1404G")  == 0) strcpy (argD[i],  "1402") ;
            else if (strcmp (argD[i], "1405G")  == 0) strcpy (argD[i],  "1430") ;
            else if (strcmp (argD[i], "1415G")  == 0) strcpy (argD[i],  "1430") ;
            else if (strcmp (argD[i], "1416")   == 0) strcpy (argD[i],  "1440") ;
            else if (strcmp (argD[i], "1416G")  == 0) strcpy (argD[i],  "1440") ;
            else if (strcmp (argD[i], "1417")   == 0) strcpy (argD[i],  "1445") ;
            else if (strcmp (argD[i], "1417G")  == 0) strcpy (argD[i],  "1445") ;
            else if (strcmp (argD[i], "1417GS") == 0) strcpy (argD[i],  "1445") ;
            else if (strcmp (argD[i], "1425J")  == 0){strcpy (argD[i],  "1425") ; pcMode|=4;}
            else if (strcmp (argD[i], "1450J")  == 0){strcpy (argD[i],  "1450") ; pcMode|=4;}
            else if (strcmp (argD[i], "1460J")  == 0){strcpy (argD[i],  "1460") ; pcMode|=4;}
            else if (strcmp (argD[i], "1470U")  == 0){strcpy (argD[i],  "1470") ; pcMode|=4;}
            else if (strcmp (argD[i], "1475J")  == 0){strcpy (argD[i],  "1475") ; pcMode|=4;}
            else if (strcmp (argD[i], "1500ST") == 0) strcpy (argD[i],  "1500") ; /* for Bin2wav with SuperTape */
            else if (strcmp (argD[i], "1500QT") == 0) strcpy (argD[i],  "1500") ; /* for Bin2wav with Quick-Tape */
            else if (strcmp (argD[i], "1500QT4") ==0) strcpy (argD[i],  "1500") ;
            else if (strcmp (argD[i], "1500QT1") ==0) strcpy (argD[i],  "1500") ; /* for Bin2wav with QT, standard header */
            else if (strcmp (argD[i], "1500A")  == 0) strcpy (argD[i],  "1500") ;
            else if (strcmp (argD[i], "1500D")  == 0){strcpy (argD[i],  "1500") ; pcMode|=4;} /* minimal Kanji */
            else if (strcmp (argD[i], "1500J")  == 0){strcpy (argD[i],  "1500") ; pcMode|=4;}
            else if (strcmp (argD[i], "1501")   == 0){strcpy (argD[i],  "1500") ; pcMode|=4;}
            else if (strcmp (argD[i], "150")    == 0) strcpy (argD[i],  "1500") ;    /* CE-150 */
            else if (strcmp (argD[i], "158")    == 0) strcpy (argD[i],  "1500") ;
            else if (strcmp (argD[i], "2500")   == 0) strcpy (argD[i],  "1350") ;
            else if (strcmp (argD[i], "EL-5400")== 0) strcpy (argD[i],  "1430") ;
            else if (strcmp (argD[i], "5400")   == 0) strcpy (argD[i],  "1430") ;
            else if (strcmp (argD[i], "EL-5500III")==0) strcpy (argD[i],"1403") ;
            else if (strcmp (argD[i], "5500III")== 0) strcpy (argD[i],  "1403") ;
            else if (strcmp (argD[i], "EL-5500II")== 0) strcpy (argD[i],"1402") ;
            else if (strcmp (argD[i], "5500II") == 0) strcpy (argD[i],  "1402") ;
            else if (strcmp (argD[i], "EL-5500-T")== 0) strcpy (argD[i],"1402") ;
            else if (strcmp (argD[i], "5500-T") == 0) strcpy (argD[i],  "1402") ;
            else if (strcmp (argD[i], "EL-5500")== 0) strcpy (argD[i],  "1402") ;
            else if (strcmp (argD[i], "5500")   == 0) strcpy (argD[i],  "1402") ;
            else if (strcmp (argD[i], "EL-5510")== 0) strcpy (argD[i],  "1421") ;
            else if (strcmp (argD[i], "5510")   == 0) strcpy (argD[i],  "1421") ;
            else if (strcmp (argD[i], "EL-5520")== 0) strcpy (argD[i],  "1450") ;
            else if (strcmp (argD[i], "5520")   == 0) strcpy (argD[i],  "1450") ;
            else if (strcmp (argD[i], "PTA-4000+16")== 0) strcpy (argD[i], "1500") ; // Hiradas Technika
            else if (strcmp (argD[i], "PTA-4000")== 0) strcpy (argD[i], "1500") ;
            else if (strcmp (argD[i], "MC-2200") == 0) strcpy (argD[i], "1245") ;    // Seiko
            else if (strcmp (argD[i], "2200")   == 0) strcpy (argD[i],  "1245") ;
            else if (strcmp (argD[i], "34")     == 0) strcpy (argD[i],  "1250") ;    // Tandy
            else if (strcmp (argD[i], "31")     == 0) strcpy (argD[i],  "1250") ;
            else if (strcmp (argD[i], "TRS-80PC-1")==0) strcpy (argD[i],"1210") ;
            else if (strcmp (argD[i], "1")      == 0) strcpy (argD[i],  "1210") ;
            else if (strcmp (argD[i], "TRS-80PC-2")==0) strcpy (argD[i],"1500") ;
            else if (strcmp (argD[i], "2")      == 0) strcpy (argD[i],  "1500") ;
            else if (strcmp (argD[i], "TRS-80PC-3A")==0)strcpy (argD[i],"1251") ;
            else if (strcmp (argD[i], "TRS-80PC-3")==0) strcpy (argD[i],"1251") ;
            else if (strcmp (argD[i], "TRS-80PC-8")==0) strcpy (argD[i],"1246") ;
            else if (strcmp (argD[i], "3A")     == 0) strcpy (argD[i],  "1251") ;
            else if (strcmp (argD[i], "3")      == 0) strcpy (argD[i],  "1251") ;
            else if (strcmp (argD[i], "8")      == 0) strcpy (argD[i],  "1246") ;
            else if (strcmp (argD[i], "1600K")  == 0
                 ||  strcmp (argD[i], "1605K")  == 0) {
                                                      pcgrpId = GRP_16 ;
                                                      REMidC = '\'' ;
                                                      strcpy (argD[i],  "1600") ; pcMode|=0xC; /* also Kanji */
            }
            else if (strcmp (argD[i], "1600P")  == 0                 /* (1609) CE-1600P, PC-1600 Mode 0 */
                 ||  strcmp (argD[i], "1600")   == 0) {
                                                      pcgrpId = GRP_16 ;
                                                      REMidC = '\'' ;
                                                      strcpy (argD[i],  "1600") ;
            }
            else if (strcmp (argD[i], "1600M1") == 0                 /* (1601) CE-150, PC-1600 Mode 1 */
                 ||  strcmp (argD[i], "1600K1") == 0                 /* (1600K)CE-150, PC-1600K Mode 1 */
                 ||  strcmp (argD[i], "1601")   == 0) {
                                                      debug ^= 0x01;
                    if (Qcnt == 0 && (debug & 0x01) >0 )  {
                                     printf ("\n%s: Fixed line numbers are not compiled to binary with mode 1.\n", argP) ;
                                     printf ("         For maximal speed you have to edit this lines on PC-1600.\n\n") ;
                    }
/*                   if (Qcnt == 0) printf ("\n%s: Only the BASIC of 'PC-1500' is supported with PC-%s.\n", argP, argD[i]) ;
                                                      strcpy (argD[i],  "1500") ; */
                    if (strcmp(&argD[i][strlen(argD[i])-2], "K1")== 0) pcMode|=4; /* min. Kanji as PC-1500D, with 1500J file */
                                                      pcMode |= 1 ;
                                                      pcgrpId = GRP_16 ;
                                                      REMidC = '\'' ;
                                                      strcpy (argD[i],  "1600") ;
            }
            else if (strcmp (argD[i], "E220")   == 0
                 ||  strcmp (argD[i], "220")    == 0) {
                                                      ll_Img = 255 ;
                                                      del_spc_cnt = 1 ;
                                                      REMidC = '\'' ;
                                                      pcgrpId = GRP_G ;
                                                      strcpy (argD[i],  "220") ;
            }
            else if (strcmp (argD[i], "E200")   == 0
                 ||  strcmp (argD[i], "200")    == 0
                 ||  strcmp (argD[i], "G801")   == 0
                 ||  strcmp (argD[i], "801")    == 0
                 ||  strcmp (argD[i], "G802")   == 0
                 ||  strcmp (argD[i], "802")    == 0
                 ||  strcmp (argD[i], "G803")   == 0
                 ||  strcmp (argD[i], "803")    == 0
                 ||  strcmp (argD[i], "G805")   == 0
                 ||  strcmp (argD[i], "805")    == 0
                 ||  strcmp (argD[i], "G811")   == 0
                 ||  strcmp (argD[i], "811")    == 0
                 ||  strcmp (argD[i], "G813")   == 0
                 ||  strcmp (argD[i], "813")    == 0
                 ||  strcmp (argD[i], "G815")   == 0
                 ||  strcmp (argD[i], "815")    == 0
                 ||  strcmp (argD[i], "G820")   == 0
                 ||  strcmp (argD[i], "820")    == 0
                 ||  strcmp (argD[i], "G830")   == 0
                 ||  strcmp (argD[i], "830")    == 0
                 ||  strcmp (argD[i], "G850S")  == 0
                 ||  strcmp (argD[i], "G850")   == 0
                 ||  strcmp (argD[i], "850")    == 0
                                                    ) {
                                                      ll_Img = 255 ;
                                                      del_spc_cnt = 1 ;
                                                      REMidC = '\'' ;
                                                      pcgrpId = GRP_G ;
                                                      strcpy (argD[i],  "850") ; pcMode|=4;
            }
            else if (strcmp (argD[i], "850V")   == 0
                 ||  strcmp (argD[i], "G850VS") == 0
                 ||  strcmp (argD[i], "G850V")  == 0
                                                    ) {
                                                      ll_Img = 255 ;
                                                      del_spc_cnt = 1 ;
                                                      REMidC = '\'' ;
                                                      pcgrpId = GRP_G ;
                                                      strcpy (argD[i],  "852") ; pcMode|=4;
            }
            else if (strcmp (argD[i], "E500S")  == 0
                 ||  strcmp (argD[i], "E500M2") == 0   /* 2nd character set active*/
                 ||  strcmp (argD[i], "E500J")  == 0
                 ||  strcmp (argD[i], "E500K")  == 0   /* and E500K2 (2nd character area) */
                 ||  strcmp (argD[i], "E500-BL")== 0
                 ||  strcmp (argD[i], "E500")   == 0
                 ||  strcmp (argD[i], "500")    == 0
                 ||  strcmp (argD[i], "E550")   == 0
                 ||  strcmp (argD[i], "550")    == 0
                 ||  strcmp (argD[i], "E650")   == 0
                 ||  strcmp (argD[i], "650")    == 0
                 ||  strcmp (argD[i], "U6000II")== 0
                 ||  strcmp (argD[i], "U6000")  == 0
                 ||  strcmp (argD[i], "6000")   == 0
                 ||  strcmp (argD[i], "1490UII")== 0
                 ||  strcmp (argD[i], "1490U")  == 0
                 ||  strcmp (argD[i], "1490")   == 0
                 ||  strcmp (argD[i], "1480U")  == 0
                 ||  strcmp (argD[i], "1480")   == 0
                                                    ) {
                 if (type == TYPE_IMG && (debug & 0x01)>0 &&
                     Qcnt == 0) { printf ("\n%s: A simplified format is used for PC-%s. If you use the native tape\n", argP, argD[i]) ;
                                  printf ("         format with Bin2wav (default) then you MUST switch the PC after\n") ;
                                  printf ("         the transfer of a IMG or TXT to 'TEXT' and back to 'BASIC' mode.\n") ;
                                  printf ("         Alternatively, the ASCII format may be used (slower, --device).\n") ;
                                  printf ("         You also can convert with Bin2wav into PC-1475 tape format (slow).\n") ;
                                  /* Decimal numbers was included as unsigned 0x1D + 7- or 12-byte BCD-format by Robert van Engelen
                                     also fixed line number 0x1F, jumps 0x1E, labels 0x1C in 2-byte binary format HL in version 6.1.1
                                     see also Dr. Joachim Stange: Systemhandbuch PC-E500, Ch. 6, publisher Fischel */
                 }
                 if (strstr(argD[i], "500")== NULL) pcMode|=4;
                 if (strcmp(&argD[i][strlen(argD[i])-2], "M2")== 0) pcMode |= 2 ; // with 2nd character table
                                                      ll_Img = 255 ;
                                                      del_spc_cnt = 1 ;
                                                      REMidC = '\'' ;
                                                      pcgrpId = GRP_E ;
                                                      strcpy (argD[i],  "500") ;
            }
            else if (strcmp (argD[i], "MZ700")  == 0  /* limited support */
                 ||  strcmp (argD[i], "MZ800")  == 0
                                                    ) {
                 if (Qcnt == 0) { printf ("\n%s: LIMITED SUPPORT FOR %s ONLY,\n", argP, argD[i]) ;
                                  printf ("         NO tokenisation of numbers and operators in the lines (remain ASCII)!\n") ;
                 }
                 if (Kcnt == 0) { printf ("\n%s: No build in tokens - the keyword file is necessary for %s, use -k\n", argP, argD[i]) ;
                                  MoreInfo( ERR_ARG ) ;
                 }
                                                      lnb_order = B_ENDIAN_LITTLE ; // lln_order = B_ENDIAN_LITTLE ;
                                                      line_len_pos = 0; line_len_bytes = 2; line_lc = 0;
                                                      line_nbb_pos = 2; // ll_Img = 255; llc_mode = B_LINE_L_REL; base_addr = 0x6BCE+1;
                                                      bas_eol = BAS_OLD_EOL ; REMid = 0x97 ;// REMidC = '!' ;
                                                      strcpy (argD[i],  "700") ;
            }
            else if (strcmp (argD[i], "MZ80")  == 0  /* experimental support */
                                                    ) {
                 if (Qcnt == 0)   printf ("\n%s: VERY EXPERIMENTALLY FOR %s ONLY!\n", argP, argD[i]) ;
                 if (Kcnt == 0) { printf ("\n%s: No build in tokens - a keyword file is necessary for %s.\n", argP, argD[i]) ;
                                  MoreInfo( ERR_ARG ) ;
                 }
                                                      lnb_order = B_ENDIAN_LITTLE ; // line_nbb_pos = 0; line_len_pos = 2 ;
                                                      line_len_bytes = 0 ; REMid = 0x80 ;
                                                      strcpy (argD[i],  "80") ;
            }
/*          ZX81 needs character conversion routine and numbers in text in dual format
            else if (strcmp (argD[i], "ZX81")  == 0 / experimental support for other computer only /
                                                    ) {
                 if (Qcnt == 0)   printf ("\n%s: SUPPORT EXPERIMENTALLY FOR %s ONLY!\n", argP, argD[i]) ;
                 if (Kcnt == 0) { printf ("\n%s: No build in tokens - a keyword file is necessary for %s.\n", argP, argD[i]) ;
                                  MoreInfo( ERR_ARG ) ;
                 }
                                                      // lnb_order = B_ENDIAN_BIG ; lln_order = B_ENDIAN_LITTLE ;
                                                      line_len_bytes = 2; line_lc = 4; // llc_mode = B_LINE_L_REL ;
                                                      bas_eol = 0x76 ; REMid = 234 ;   // ll_Img = 255 ;
                                                      strcpy (argD[i],  "81") ;
            } */
            else if (strcmp (argD[i], "KC87")  == 0 /* experimental support for other computer only */
                                                    ) {
                 if (Qcnt == 0)   printf ("\n%s: SUPPORT EXPERIMENTALLY FOR %s ONLY!\n", argP, argD[i]) ;
                 if (Kcnt == 0) { printf ("\n%s: No build in tokens - a keyword file is necessary for %s.\n", argP, argD[i]) ;
                                  MoreInfo( ERR_ARG ) ;
                 }
                                                      lnb_order = B_ENDIAN_LITTLE ; // lln_order = B_ENDIAN_LITTLE ;
                                                      line_len_bytes = 2; line_lc = 0; llc_mode = B_LINE_L_ABS ;
                                                      base_addr = 0x400+1; // ll_Img = 255 ;
                                                      bas_eol = BAS_OLD_EOL ; REMid = 0x8E ; REMidC = '!' ;
                                                      strcpy (argD[i],  "87") ;
            }

            pcId = (uint) strtol (argD[i], &ptrErr, 0) ;
            if (*ptrErr != 0) {
                printf ("%s: Pocket computer %s is not valid\n", argP, argD[i]);
                MoreInfo (ERR_ARG);  // exit (ERR_SYNT) ;
            }
        }
//        if ((pcMode & 0xC)>0 ) debug|=CNV_SJIS;

	switch (pcId) {
        case 1211 : // IDENT_PC1211 in the other tools
        case 1245 : // IDENT_OLD_BAS
        case 1246 :
        case 1247 :
        case 1248 :
        case 1250 :
        case 1251 :
        case 1255 :
            // cnvstr_upr done by conv_asc2old ;
        case 1140 :
        case 1146 : /* 1246DB */
        case 1148 : /* 1248DB */
        case 1150 :
            {    ident=IDENT_OLD_BAS;  tokenL=1;  REMid=0xD3;   delREMspc=true;
                 line_len_bytes = 0; line_lc = LINE_LC_OLD ;
                 bas_eol = BAS_OLD_EOL ; /* NO: bas_eof = BAS_OLD_EOF ; Old EOF in RAM also as New 0xFF */
            } break; // delREMspc=false;

        case 1401 : // IDENT_NEW_BAS
        case 1402 :
        case 1421 :
        case 1430 :
        case 1431 :
            cnvstr_upr=true ;
            // hereafter PCs supports lower cases, cnvstr_upr=false
        case 1100 :
        case 1260 :
        case 1261 :
        case 1262 :
        case 1350 :
        case 1450 :
            tokenL=1 ;
            {    ident=IDENT_NEW_BAS; REMid=0xD7; delREMspc=true;  } break;

            // hereafter PCs use a variable token length, tokenL=0
        case 1440 :
        case 1445 :
            cnvstr_upr=true ;
            // hereafter PCs supports lower cases, cnvstr_upr=false
        case 1403 :
        case 1425 :
        case 1460 :
            {    ident=IDENT_NEW_BAS; REMid=0xD7; delREMspc=true;  } break;

        case  500 : // GRP was set before
            if (type == TYPE_IMG && Qcnt == 0 && (debug & 0x01)>0 )
                printf ("%s: Switch to 'TEXT' and back to 'BASIC' to compile jumps and numbers!\n\n", argP) ;
        case  220 : // GRP_G
        case  850 :
        case  852 :

        case 1280 : // IDENT_EXT_BAS
        case 1360 :
        case 1470 :
        case 1475 :
            {    ident=IDENT_EXT_BAS;  tokenL=2;  REMid=0xFE59; delREMspc=true;  }

            if (pcgrpId == GRP_E || pcgrpId == GRP_G ) ident=IDENT_E_BAS;

            break;

        case 1500 : // IDENT_PC15_BAS
            {    ident=IDENT_PC15_BAS; tokenL=2;  REMid=0xF1AB; delREMspc=true; } break;
        case 1600 :
            {    ident=IDENT_PC16_BAS; tokenL=2;  REMid=0xF1AB; delREMspc=true; } break;

        case 700  : /* experimentally only*/
        case 80   :
                 pcgrpId = GRP_MZ ; command_len_min = 1;
        // case 81   :
        case 87   :
            {    ident=IDENT_NEW_BAS; delREMspc=false; } break;
	default:
		{
		printf("%s: Pocket computer PC-%u not implemented until now\n", argP, pcId );
		MoreInfo (ERR_ARG);
		}
	}

    /* type part 2 */
    if (type == TYPE_NOK) {
        if ( strcmp (argD[2], "asm4") == 0 || strcmp (argD[2], "capx") == 0 ||
            (strcmp (argD[2], "casl") == 0 && ident == IDENT_NEW_BAS) )  {
            type = TYPE_TXT ;
            type_asm = true ;
            asm_id = 4 ;        /* PC-144x CAP-X or CASL */
            debug |= BAS_AUTO ;
            ins_spc1 = 1 ;
        }
        else if (strcmp (argD[2], "asm5") == 0) {
            type = TYPE_TXT ;  /* PC-1500 RVS PC-Macro and other */
            type_asm = true ;
            asm_id = 5 ;
            debug |= BAS_AUTO | INS_APST ;
            //ins_apst = '"';
        }
        else if (strcmp (argD[2], "asm6") == 0) {
            type = TYPE_TXT ;
            type_asm = true ;
            asm_id = 6 ;       /* PC-1600, Klaus Ditze */
            debug |= BAS_AUTO | INS_APST ;
            ins_apst = '\'' ;
        }
        else if (strncmp (argD[2], "asm", 3) == 0 || strcmp (argD[2], "c") == 0 ||
                 (strcmp (argD[2], "casl") == 0 && pcgrpId == GRP_G)) {

            if (pcgrpId == GRP_G && pcId < 852) type = TYPE_ASC ; /* PC-E200-G850S, CMT-Menu */
            else type = TYPE_TXT ;                                /* PC-G850V(S), CLOAD */
            type_asm = true ;
            debug |= BAS_AUTO ;

            if (strncmp (argD[2], "asm", 3) == 0) {
                asm_id = (int) argD[2][3] ;
                if (asm_id >=0x30)asm_id -= 0x30 ;
                if (asm_id == 2)  asm_id = 8 ;
                if (asm_id !=0 && asm_id !=8 ) type = TYPE_NOK;
                if (pcgrpId == GRP_G) ins_spc1 = 1 ; /* E2-G8 asm OpCodes need leading spc */
            }
        }
    }
    if (type == TYPE_NOK) {
        printf ("%s: Source file type %s is not valid\n", argP, argD[2]) ;
        MoreInfo (ERR_SYNT);
    }
    if (type != TYPE_IMG) {
        if ( Qcnt==0) printf ("%s: Tokenization is depressed for file type %s\n", argP, argD[2]) ;
    }

	if (FILEcnt == 1) {
		if ( strrchr (argD[0], '.') != NULL) {
            strncat (argD[1], argD[0], strrchr(argD[0], '.') - argD[0] ); /* GetSrcFile */
            /* ToDo: Space to make adjustments based on the source file extension */
		}
		else strncpy (argD[1], argD[0], cLPF -1) ;
        if (type == TYPE_ASC) strcat (argD[1], ".asc" );
        else strcat (argD[1], ".img" );
	}

    if ( type == TYPE_TXT) {
        if ( pcgrpId == GRP_16 && !(debug & INS_APST) ) type = TYPE_ASC ; /* for comment lines saved with SAVE* CAS: */
        else if ( pcgrpId != GRP_E && ident != IDENT_EXT_BAS && ident != IDENT_NEW_BAS && !(debug & INS_APST || type_asm) ) {
            printf ("%s: Destination file type '%s' is for TEXT mode, not valid for PC-%u!\n", argP, argD[2], pcId) ;
            if (pcgrpId == GRP_G){
                printf ("%s: Text MENU Cmt loads BAS type! Type is switched from %s to BAS now.\n", argP, argD[2]) ;
                type = TYPE_ASC ;
            }
            else {
                if (Qcnt==0) printf ("%s: You have to tokenize (edit) every line at the PC-%u.\n", argP, pcId) ;
                ++err_cnt;
            }
        }
        else if ( pcgrpId == GRP_E ) { /* That CSAVEd from TEXT modus may not CLOADable*/
            printf ("%s: File type %s has to CLOAD as Bin2wav type IMG for group of PC-E%u\n", argP, argD[2], pcId);
        }
    }
    if ( (type == TYPE_ASC) && !(pcgrpId == GRP_16 || pcgrpId == GRP_E || pcgrpId == GRP_G)) {
        if (Qcnt == 0 || ident == IDENT_OLD_BAS) {
            printf ("%s: Src type %s (Text Menu or device CAS:)is not valid for group of PC-%u\n", argP, argD[2], pcId) ;
        }
        if (ident == IDENT_OLD_BAS) MoreInfo (ERR_ARG);
        if (Qcnt == 0) printf (" You can only use %s with type=%s for text formatting for this PC.\n", argP, argD[2]) ;
    }
    if (Qcnt == 0) {
            if (type== TYPE_IMG) printf ("Target file: BASIC image, format of PC-%u\n", pcId) ;
            else if (type== TYPE_TXT) printf ("Target file: BASIC TEXT modus image, format of PC-%u\n", pcId) ;
            else if (type== TYPE_ASC) printf ("Target file: BASIC ASCII (Text Menu Cmt/ LOAD CAS:), format of PC-%u\n", pcId) ;
    }
    if (Qcnt == 0 && (debug & SPC_LINES_OK)>0 && type== TYPE_IMG && pcgrpId != GRP_E) {
            printf ("%s: The SPC_LINES_OK flag used allows very short lines, which can \n", argP) ;
            printf ("         cause unexpected effects when listing or running this image.\n") ;
    }
    if (Acnt > 0) {
        debug |= BAS_AUTO ;
        if (strlen( argD[11] )>0) {
            auto_inc = (ulong) strtol (argD[11], &ptrErr, 0) ;
            if (*ptrErr != 0) {
                printf ("%s: AUTO increment '%s' is not valid\n", argP, argD[11]) ;
                MoreInfo (ERR_ARG);
            }
        }
        if ( auto_inc == 0 || auto_inc > 0xFFFF ) {
            printf ("%s: AUTO increment '%ld' is out of range\n", argP, auto_inc) ;
            MoreInfo (ERR_ARG);
        }
    }
    if (type== TYPE_IMG) {

        if (ident != IDENT_E_BAS) cnv_Elabel = true ;
        if ((debug & BAS_EXT_FRMT) >0 ) cnv_Elabel = !cnv_Elabel ;

        /* Read files with external token keywords */
        for ( ii = 0 ; ii < Kcnt ; ++ii ){
            error = ReadKeywordsFromFile ( argD[5 + ii] ) ;
            if (error != ERR_OK) MoreInfo (error) ;
        }
        if (key_cnt > 0 ) {
            if ( (debug & 0x100000) > 0 ) KeysFromFileOnly = true ;
            if (Qcnt == 0 && debug != 0 ) printf ("%s: %u tokens loaded from keyword file(s)\n", argP, key_cnt) ;
        }
    }
    i_token = istoken("REM") ;
    if (i_token) REMid = i_token ;
    if (ins_apst == '\'' && REMidC !=0) ins_apst = REMidC ;

    /* Read files with external code points, set code_cnt */
    for ( ii = 0 ; ii < Ocnt ; ++ii ){
        error = ReadCodepointsFromFile ( argD[8 + ii]) ;
        if (error != ERR_OK) MoreInfo (error) ;
    }
    if (error != ERR_OK) return (error) ;
    if (code_cnt > 0 && Qcnt == 0 ) printf ("%s: %u code points loaded from file(s)\n", argP, code_cnt) ;
    if ( (pcMode & 8)>0 && code_cnt<65 && utf8==1 && Qcnt==0 )
        printf ("Extra utf8 chars from a file --cOdepoints=Kanji.cfg required for full Kanji!\n") ;

/*    Search the variable special characters in the codepoints file to determine the Sharp value for the special character,
      mask the values in the codepoint file with Utf8:=[Placeholder], if Bas2img should use the default values
      instead of a 1:1 conversion for Wav2bin, e.g. Π=[PI] from the standard character table instead of the Kanji ROM */

    if (Ocnt> 0) {
      for ( ii = 0 ; ii < code_cnt ; ++ii) {
         if (codepoint[ii] == 0) continue ;
         if (codepoint[ii] < 0x0100) { /*  1 byte codepoints */
            if (      !strcmp( chrstring[ii], "√" ) && *SQRidStr ==0) *SQRidStr = (char) (uchar) codepoint[ii] ;
            else if ( !strcmp( chrstring[ii], "Π" ) && *PI_idStr ==0) *PI_idStr = (char) (uchar) codepoint[ii] ;
            else if ( !strcmp( chrstring[ii], "π" ) && *piLidStr ==0) *piLidStr = (char) (uchar) codepoint[ii] ;
            else if ( !strcmp( chrstring[ii], "¥" ) && *YENidStr ==0) *YENidStr = (char) (uchar) codepoint[ii] ;
            else if ( !strcmp( chrstring[ii], "€" ) && *EURidStr ==0) *EURidStr = (char) (uchar) codepoint[ii] ;
            else if ( !strcmp( chrstring[ii], "□" ) && *INSidStr ==0) *INSidStr = (char) (uchar) codepoint[ii] ;
            else if ( !strcmp( chrstring[ii], "■" ) && *FULidStr ==0) *FULidStr = (char) (uchar) codepoint[ii] ;
         }
         else { /* 2 byte, 0xFFFF is set for variable tags, blocks the assignment of subsequent code points in the file */
            if (      !strcmp( chrstring[ii], "√" ) && *SQRidStr ==0) {
                SQRidStr[0] = (char) (uchar) (codepoint[ii] >> 8) ;
                SQRidStr[1] = (char) (uchar) (codepoint[ii] & 0xFF) ;
            }
            else if ( !strcmp( chrstring[ii], "Π" ) && *PI_idStr ==0) {
                PI_idStr[0] = (char) (uchar) (codepoint[ii] >> 8) ;
                PI_idStr[1] = (char) (uchar) (codepoint[ii] & 0xFF) ;
            }
            else if ( !strcmp( chrstring[ii], "π" ) && *piLidStr ==0) {
                piLidStr[0] = (char) (uchar) (codepoint[ii] >> 8) ;
                piLidStr[1] = (char) (uchar) (codepoint[ii] & 0xFF) ;
            }
            else if ( !strcmp( chrstring[ii], "¥" ) && *YENidStr ==0) {
                YENidStr[0] = (char) (uchar) (codepoint[ii] >> 8) ;
                YENidStr[1] = (char) (uchar) (codepoint[ii] & 0xFF) ;
            }
            else if ( !strcmp( chrstring[ii], "€" ) && *EURidStr ==0) {
                EURidStr[0] = (char) (uchar) (codepoint[ii] >> 8) ;
                EURidStr[1] = (char) (uchar) (codepoint[ii] & 0xFF) ;
            }
            else if ( !strcmp( chrstring[ii], "□" ) && *INSidStr ==0) {
                INSidStr[0] = (char) (uchar) (codepoint[ii] >> 8) ;
                INSidStr[1] = (char) (uchar) (codepoint[ii] & 0xFF) ;
            }
            else if ( !strcmp( chrstring[ii], "■" ) && *FULidStr ==0) {
                FULidStr[0] = (char) (uchar) (codepoint[ii] >> 8) ;
                FULidStr[1] = (char) (uchar) (codepoint[ii] & 0xFF) ;
            }
         }
      }
      /* Release IDs blocked by variable tags for reassignment */
      if (strcmp (SQRidStr, VarTAGidStr) ==0) *SQRidStr=0 ;
      if (strcmp (PI_idStr, VarTAGidStr) ==0) *PI_idStr=0 ;
      if (strcmp (piLidStr, VarTAGidStr) ==0) *piLidStr=0 ;
      if (strcmp (YENidStr, VarTAGidStr) ==0) *YENidStr=0 ;
      if (strcmp (EURidStr, VarTAGidStr) ==0) *EURidStr=0 ;
      if (strcmp (INSidStr, VarTAGidStr) ==0) *INSidStr=0 ;
      if (strcmp (FULidStr, VarTAGidStr) ==0) *FULidStr=0 ;
    }

    /* Search the variable special characters in the code page 437 for 1600 M0 and E500 set 1 series */
    if ( (ident == IDENT_PC16_BAS && (pcMode & 0x1C)==0) || (pcgrpId == GRP_E && (pcMode & 0x1F) < 2) ) {
        if ( ident == IDENT_PC16_BAS && *FULidStr ==0 ) *FULidStr = '\x7F';//FUL: E437/E500:DB, 15/1600:7F

        for ( ii = CodeC_offset ; ii < 0x100 ; ++ii) {
            if (      !strcmp( CodeC[ii-CodeC_offset], "√" ) && *SQRidStr ==0 ) *SQRidStr = (char) ii ;
            else if ( !strcmp( CodeC[ii-CodeC_offset], "Π" ) && *PI_idStr ==0 ) *PI_idStr = (char) ii ;
            else if ( !strcmp( CodeC[ii-CodeC_offset], "π" ) && *piLidStr ==0 ) *piLidStr = (char) ii ;
            else if ( !strcmp( CodeC[ii-CodeC_offset], "¥" ) && *YENidStr ==0 ) *YENidStr = (char) ii ;
            else if ( !strcmp( CodeC[ii-CodeC_offset], "€" ) && *EURidStr ==0 ) *EURidStr = (char) ii ;
            else if ( !strcmp( CodeC[ii-CodeC_offset], "□" ) && *INSidStr ==0 ) *INSidStr = (char) ii ;
            else if ( !strcmp( CodeC[ii-CodeC_offset], "■" ) && *FULidStr ==0 ) *FULidStr = (char) ii ;
        }
    }   /* E500 2. character set, E220 and G-Series needs the external code points file therefore */

/*  Default values, if the variable to be translated special characters have not yet been found
    or refer to a value whose use is not recommended in a program text of the pocket computer */
    switch (ident) {

        case IDENT_PC15_BAS :
            /* Default values PC-1500 */
            if (*SQRidStr == 0 || (uchar) *SQRidStr > BAS_MAX_CHR) strcpy (SQRidStr, "\x5B");
            if (*PI_idStr == 0 || (uchar) *PI_idStr > BAS_MAX_CHR) strcpy (PI_idStr, "\x5D");
            if (*piLidStr == 0 || (uchar) *piLidStr > BAS_MAX_CHR) strcpy (piLidStr, "\x5D");
            if (*YENidStr == 0 || (uchar) *YENidStr > BAS_MAX_CHR) strcpy (YENidStr, "\x5C");
            if (*EURidStr == 0 || (uchar) *EURidStr > BAS_MAX_CHR) strcpy (EURidStr, "\x45");
            if (*INSidStr == 0 || (uchar) *INSidStr > BAS_MAX_CHR) strcpy (INSidStr, "\x27");
            if (*FULidStr == 0 || (uchar) *FULidStr > BAS_MAX_CHR) strcpy (FULidStr, "\x7F");

            break ;

        case IDENT_PC16_BAS :

            /* Default values PC-1600, >0xDF: code is not listable or strings "~" */
            if (*SQRidStr == 0 || (uchar) *SQRidStr > BAS_MAX_CHR) strcpy (SQRidStr, "[");
            if (*PI_idStr == 0 || (uchar) *PI_idStr > BAS_MAX_CHR) strcpy (PI_idStr, "]");
            if ((pcMode &3) == 1) {
                if (*piLidStr == 0 || (uchar) *piLidStr > BAS_MAX_CHR) strcpy (piLidStr, "]");
                if (*YENidStr == 0 || (uchar) *YENidStr > BAS_MAX_CHR) {
                    if ((pcMode & 0xC)>0 ) strcpy (YENidStr, "\x5C");
                    else strcpy (YENidStr, "\\");
                }
            }
            else { /* pcMode 0 */
                if (*piLidStr == 0 || (uchar) *piLidStr > BAS_MAX_CHR) strcpy (piLidStr, "]");//[pi]
                if (*YENidStr == 0 || (uchar) *YENidStr > BAS_MAX_CHR) {
                    if ((pcMode & 0xC)>0 ) strcpy (YENidStr, "\x5C");
                    else strcpy (YENidStr, "\x9D");
                }
            }
            if (*EURidStr == 0 || (uchar) *EURidStr > BAS_MAX_CHR) strcpy (EURidStr, "E");
            if (*INSidStr == 0 || (uchar) *INSidStr > BAS_MAX_CHR) {
                    if ((pcMode & 0xC)>0 ) strcpy (INSidStr, "\x1E");
                    else strcpy (INSidStr, "\xB0");
            }
            if (*FULidStr == 0 || (uchar) *FULidStr > BAS_MAX_CHR) strcpy (FULidStr, "\x7F");

            break ;

        case IDENT_E_BAS :

            if (pcgrpId == GRP_G || (pcgrpId == GRP_E && (pcMode & 0x1C) >0) ) {
                if (*EURidStr == 0) strcpy (EURidStr, "E");

                if (pcId == 220 ) {
                    if (*SQRidStr == 0) strcpy (SQRidStr, "\xEB");
                    if (*PI_idStr == 0) strcpy (PI_idStr, "\x90");
                    if (*piLidStr == 0) strcpy (piLidStr, "\xB0");
                    /* YEN, INS not available */
                    if (*FULidStr == 0) strcpy (FULidStr, "\xF7");
                }
                else { /* GRP_G without E220, E500 Japanese */
                    if (*YENidStr == 0) strcpy (YENidStr, "\x5C");
                        /* INS not available */
                    if ((pcMode & 0x18) ==0 &&
                        *FULidStr == 0) strcpy (FULidStr, "\x87");
                  }
            }
            else { /* GRP_E(500) international */

                if (ident == IDENT_E_BAS && (pcMode &3) < 2) {       /* 1. char table */
                    if (*SQRidStr == 0) strcpy (SQRidStr, "\xFB");
                    if (*PI_idStr == 0) strcpy (PI_idStr, "\xE3");
                    if (*piLidStr == 0) strcpy (piLidStr, "\xE3");

                    if (*YENidStr == 0) strcpy (YENidStr, "\x9D");
                    if (*INSidStr == 0) strcpy (INSidStr, "\xB0");
                    if (*FULidStr == 0) strcpy (FULidStr, "\xDB");
                }
                else if (ident == IDENT_E_BAS && (pcMode &3) == 2) { /* 2. char table */
                    if (*SQRidStr == 0) strcpy (SQRidStr, "\xEB");
                    if (*PI_idStr == 0) strcpy (PI_idStr, "\x90");
                    if (*piLidStr == 0) strcpy (piLidStr, "\xB0");
                    /* YEN, INS, FUL not available */
                }
                if (*EURidStr == 0) strcpy (EURidStr, "E");
            }
            break ;

        // case IDENT_EXT_BAS :
        // case IDENT_NEW_BAS :
        // NOTE (Mr#4#): Only fixed assignment of the standard values to variable [Tags] because no expandable operating systems:
        // break ;

       // default: {}
    } // end switch ident

//  Removed: Function CountBits uses <limits.h>
//	printf("CHAR_BIT  = %d\n", 8 * sizeof( char ) );	printf("SHORT_BIT = %d\n", 8 * sizeof( short ) );
//	printf("INT_BIT   = %d\n", 8 * sizeof( int ) ); 	printf("LONG_BIT  = %d\n", 8 * sizeof( long ) );
//	if ( ( dateiein = fopen( argD[0], "rt" ) ) != NULL )  /* end-of-line sequence is system-dependent! */

	if ( ( dateiein = fopen( argD[0], "rb" ) ) != NULL )
	{
		if (Qcnt == 0 && debug !=0 ) printf("File %s was opened\n", argD[0] );
		/* Get the length of the source file */
		fseek( dateiein, 0, SEEK_END ) ;   /* set file position indicator to end */
		nbByte = ftell( dateiein ) ;       /* get file position indicator */
		fseek( dateiein, 0, SEEK_SET ) ;   /* set file position indicator to start */
		if (Qcnt == 0) printf("File size of %s is %u bytes\n\n", argD[0], nbByte );
		dateiaus = fopen( argD[1], "wb" ); /* write in binary mode */

        /* Begin of line processing */  // old: while ( fgets( line_buffer, cLL, dateiein ) != NULL )
		while ( getlineF( line_buffer, cLL, dateiein, &line_cnt, &line_cntN ) != NULL )
		{  /* get one line - eine zeile rausholen */

        /* Begin of processing of a line */
			if (line_cnt < 2) {
                if (remove_BOM ( line_buffer )>0 && utf8 != 1) {
                    ++wrn_cnt;
                    if ( Qcnt==0) printf ("%s: This source begins with a UTF-8 mark. The utf8 parameter is false?\n", argP ) ;
                }
                /* starting first line in text with a '.' is usable to convert more chars from DOS-US */
                if((uchar) *line_buffer == '.') {
                    /*found src_type SHA"  */
                    src_type = SOURCE_SHA ;
                    continue ; /* ignore the header line of a SHA-file */
                }
                /* remove artifact: First byte in file is "\xF8" if serial transfer was done with some hardware */
                if ((uchar) *line_buffer >= 0xF8) shift_left( line_buffer ) ;
			}
			spc_cnt1 = del_spaces( line_buffer );  /* Delete leading spaces of the line number */
			if (strlen (line_buffer) == 0 && !(debug & SPC_LINES_OK)) continue ; /* ignore empty line */

            /* Progress (Fortschrittsanzeige) DOSBox 0.73,  Win XP 900 MHz */
			if (Qcnt == 0 && (debug & 0x80) >0 ) {
                    printf("%s\n", line_buffer );
			}
			/* Ignore comment lines in BASIC source, out of line comments are allowed now */
			if ((uchar) *line_buffer == '\'' ) {
                if (!(debug & BAS_AUTO)) continue ; /* Out-of-line comment without AUTO not transfered, next line */
                else if (type != TYPE_IMG &&        /* for images OK, because tokenizer changes to REM */
                         *line_buffer != REMidC) *line_buffer = '"' ;   /* type change to apostrophe */
			}
            if (strncmp(line_buffer, "[EOF]", 5)==0) {    /* EOF without additional end mark */
                    replace_str(line_buffer, "[EOF]", "");
                    if ( Qcnt==0) printf ("%s: The end marker [EOF] was reached in source text line %u.\n", argP, line_cnt) ;
			        break ;
            }
            replace_str(line_buffer, "[SUB]", "\x1A");   /* EOF_ASC */
			if ((uchar) *line_buffer == EOF_ASC) {       /* End mark of source text */
			        if ( Qcnt==0) printf ("%s: The end marker [SUB] was reached in source text line %u.\n", argP, line_cnt) ;
			        if (type == TYPE_ASC) debug |= BAS_EOF_INCL ;
			        break ;
			}
			if (Qcnt == 0 && (debug & 0x20) >0 ) {
			/* Show content of line_buffer as hex values */
                i = 0;
                printf ("i<");
                while ( line_buffer[i] != '\0') { printf ("%02X ", (uchar) line_buffer[i]); i++; }
                    printf ("%02X", (uchar) line_buffer[i]);
                printf (">\n") ;
			}

        /* Begin of the Preprocessor */
            if ((debug & 0x10) == 0) {

                /* replace (utf8-)characters with codepoints, loaded from external file */
                if (Ocnt> 0) for ( ii = 0 ; ii < code_cnt ; ++ii) {
                        replace_str(line_buffer, chrstring[ii], codestring[ii]);
                }
                /* replaces Japanese UTF-8 half-width Katakana chars */
                if (  ident == IDENT_NEW_BAS  || ident == IDENT_EXT_BAS || // only page with Katakana, no conflict
                      ident == IDENT_PC15_BAS || (pcgrpId == GRP_G && pcId != 220) ||     // different code pages:
                    ((ident == IDENT_PC16_BAS ||  pcgrpId == GRP_G || pcgrpId == GRP_E || ident == IDENT_OLD_BAS) &&
                     ( (debug & CNV_SJIS) >0  || (pcMode & 0x1C) >0 ) ) )   //supported only with pcMode or -l0x100
                    error = replace_japanChars (line_buffer, utf8, debug, type_asm) ;
                if (error != ERR_OK) break ;

                if (utf8 == 1 ) {
                    /* convert UTF-8 chars of code page 437 for 1600 and E500 (M1) series, other require a file */
                    if ( (ident == IDENT_PC16_BAS && (pcMode & 0xF) < 2) || /* Mode 0 | 1 , no jap. chars*/
                         (pcgrpId == GRP_E && (pcMode & 0x1F) < 2) ) {      /* Mode 1 only */

                        /* replace (utf8-)characters with Sharp-values from E437 table */
                        for ( ii = CodeC_offset ; ii < 0x100 ; ++ii) {
                            replace_str(line_buffer, CodeC[ii-CodeC_offset], CodeC2[ii-CodeC_offset]);
                        }
                    }   /* E500 2. character set, E220, G-Series and Kanji models need the external code points file therefore */

                    replace_str(line_buffer, "円", "[YEN]");
                    replace_str(line_buffer, "年", "[YEAR]");
                    replace_str(line_buffer, "月", "[MONTH]");
                    replace_str(line_buffer, "日", "[DAY]");
                    replace_str(line_buffer, "時", "[HOUR]");
                    replace_str(line_buffer, "分", "[MINUTE]");
                    replace_str(line_buffer, "秒", "[SECOND]");
                    replace_str(line_buffer, "♠",  "[SPADE]");
                    replace_str(line_buffer, "♥",  "[HEART]");
                    replace_str(line_buffer, "♦",  "[DIAMOND]");
                    replace_str(line_buffer, "♣",  "[CLUB]");

                    replace_str(line_buffer, "√", "[SQR]");      // U+221A
                    replace_str(line_buffer, "Π", "[PI]");
                    replace_str(line_buffer, "π", "[pi]");
                    /* replaces inside strings for line_buffer2 */
                    replace_str(line_buffer, "¥", "[Y]");
                    replace_str(line_buffer, "€", "[E]");
                    replace_str(line_buffer, "□", "[INS]") ;     // U+25A1
                    replace_str(line_buffer, "■", "[FUL]") ;     // U+25A0

                } // End utf8
                /* Replace special esc chars from emulator */
                replace_str(line_buffer, "\\YEN" ,  "[YEN]");
                replace_str(line_buffer, "\\YEAR",  "[YEAR]");
                replace_str(line_buffer, "\\MONTH", "[MONTH]");
                replace_str(line_buffer, "\\DAY" ,  "[DAY]");
                replace_str(line_buffer, "\\HOUR",  "[HOUR]");
                replace_str(line_buffer, "\\MINUTE","[MINUTE]");
                replace_str(line_buffer, "\\SECOND","[SECOND]");

                replace_str(line_buffer, "\\SPADE",  "[SPADE]");
                replace_str(line_buffer, "\\HEART",  "[HEART]");
                replace_str(line_buffer, "\\DIAMOND","[DIAMOND]");
                replace_str(line_buffer, "\\CLUB",   "[CLUB]");

                replace_str(line_buffer, "\\SQR" ,  "[SQR]");
                replace_str(line_buffer, "\\PI"  ,  "[PI]") ;
                replace_str(line_buffer, "\\INS" ,  "[INS]");
                replace_str(line_buffer, "\\BX"  ,  "[FUL]");
                // Coding of old BASIC exponent char for PokecomGO
                replace_str(line_buffer, "\\EX"  ,   "[E]"); /* ? */
                /* replaces DOS-US graphic chars, often in older Listings found, if this would */
                /* conflict with usable UTF-chars then separate option for bas2img --utf8 would needed */
                if (src_type == SOURCE_SHA || utf8 != 1 ) {
                    replace_str(line_buffer, "\xFB", "[SQR]") ; /* .SHA  √ <-- xFB */
                    replace_str(line_buffer, "\xE3", "[PI]") ;  /* .SHA  π <-- xE3 */
                    replace_str(line_buffer, "\x90", "[E]") ;   /* .SHA  € <-- x90 */
                }
                /* tested with "TransFile PC 5.55 D" and PC-1401/1251 */
                if (src_type == SOURCE_SHA || utf8 == UTF8_DOS) {
                    replace_str(line_buffer, "\x9D", "[Y]") ;   /* .SHA  ¥ <-- x90 */
                    replace_str(line_buffer, "\xF0", "[INS]") ; /* Space Frame */
                    replace_str(line_buffer, "\xDB", "[FUL]") ; /* FullFrame rectangle */
                    if (ident == IDENT_NEW_BAS || ident == IDENT_EXT_BAS ) {
                        replace_str(line_buffer, "\x06", "[SPADE]") ; /* Card symbols ♠ ♥ ♦ ♣ */
                        replace_str(line_buffer, "\x03", "[HEART]") ;
                        replace_str(line_buffer, "\x04", "[DIAMOND]") ;
                        replace_str(line_buffer, "\x05", "[CLUB]") ;
                    }
                } // end if SHA

                i = 0;

                switch (ident) {
                case IDENT_OLD_BAS :

                    replace_str(line_buffer, "[SQR]", "\x1A");
                    replace_str(line_buffer, "[PI]" , "\x19");
                    replace_str(line_buffer, "[pi]" , "\x19");
                    replace_str(line_buffer, "[Y]"  , "\x17");
                    replace_str(line_buffer, "[E]"  , "\x60"); // Placeholder for Exp before conv_asc2old
                    replace_str(line_buffer, "[INS]", "\x10");
                    replace_str(line_buffer, "[FUL]", "\x80"); // Placeholder for FullFrame before conv_asc2old
                    replace_str(line_buffer, "[4C]" , "\x80"); // Placeholder FUL
                    /* reconstruct special chars generated by wav2bin from placeholders - moved to end of section*/
/*                  replace_str(line_buffer, "[10]", "\x10");
                    replace_str(line_buffer, "[3A]", "\x3A"); // -3F Japanese chars
*/
                    while ( line_buffer[i] != '\0' ) {
                        if ( (uchar) line_buffer[i] > 0x80 ) {
                            ++wrn_cnt;
                            printf ("%s:WARNING for line of text %u, %i. character 0x%02X should be invalid.\n",
                                     argP, line_cnt, i+1, (uchar) line_buffer[i]);
                        }
                        i++;
                    }
                    replace_str(line_buffer, ">=", "\x82");  // istoken had not worked for this in older versions
                    replace_str(line_buffer, "<=", "\x83");
                    replace_str(line_buffer, "<>", "\x84");
                    replace_str(line_buffer, "[S]", "\x9B"); // S ETCOM
                    replace_str(line_buffer, "[O]", "\x9C"); // O PEN
                    replace_str(line_buffer, "[C]", "\x9D"); // C LOSE

                    break ;

                case IDENT_EXT_BAS :
                case IDENT_NEW_BAS :

                    if (ident == IDENT_NEW_BAS && cnvstr_upr == true ) {
                        replace_str(line_buffer, "[INS]", "\xFD") ;
                        replace_str(line_buffer, "[FUL]", "\xFE") ;
                        if (pcId == 1421) {
                            replace_str(line_buffer, " i ", "i") ;
                            replace_str(line_buffer, " n ", "n") ;
                        }
                    }
                    else {
                        replace_str(line_buffer, "[INS]", "\xFA") ;
                        replace_str(line_buffer, "[FUL]", "\xF9") ;
                    }
                    if ((pcMode & 0xC) >0) {
                        replace_str(line_buffer, "[YEAR]",   "\xF1") ;
                        replace_str(line_buffer, "[MONTH]",  "\xF2") ;
                        replace_str(line_buffer, "[DAY]" ,   "\xF3") ;
                        replace_str(line_buffer, "[YEN]" ,   "\xF4") ;
                    }
                    replace_str(line_buffer, "[SPADE]",  "\xF5");
                    replace_str(line_buffer, "[HEART]",  "\xF6");
                    replace_str(line_buffer, "[DIAMOND]","\xF7");
                    replace_str(line_buffer, "[CLUB]",   "\xF8");
                    replace_str(line_buffer, "[SQR]","\xFC");
                    replace_str(line_buffer, "[PI]", "\xFB");
                    replace_str(line_buffer, "[pi]", "\xFB");
                    replace_str(line_buffer, "[Y]",  "\x5C");
                    replace_str(line_buffer, "[E]",  "\x45");
/*                  replace_str(line_buffer, "[5C]", "\x5C");   // Yen
                    replace_str(line_buffer, "[F5]", "\xF5"); - FE  */

                    while ( line_buffer[i] != '\0') {
                        if ( ( line_buffer[i] < 0 ) && !(( line_buffer[i] >= '\xF1' ) && ( line_buffer[i] <= '\xFE' )) ) {
                            ++wrn_cnt;
                            printf ("%s:WARNING for line of text %u, %i. character 0x%02X should be invalid.\n",
                                     argP, line_cnt, i+1, (uchar) line_buffer[i]);
                        }
                        i++;
                    }
                    if (ident == IDENT_EXT_BAS && (pcMode & 8)>0 ) { /* 1360K */
                        replace_str(line_buffer, "[HOUR]",   "\x8E\x9E");
                        replace_str(line_buffer, "[MINUTE]", "\x95\xAA");
                        replace_str(line_buffer, "[SECOND]", "\x95\x62");
                    }
                    break ;

                case IDENT_PC15_BAS :

                    if (*SQRidStr) replace_str(line_buffer, "[SQR]", SQRidStr);
                    if (*PI_idStr) replace_str(line_buffer, "[PI]" , PI_idStr);
                    if (*piLidStr) replace_str(line_buffer, "[pi]" , piLidStr);
                    if (*YENidStr) replace_str(line_buffer, "[Y]"  , YENidStr);
                    if (*EURidStr) replace_str(line_buffer, "[E]"  , EURidStr);
                    if (*INSidStr) replace_str(line_buffer, "[INS]", INSidStr);
                    if (*FULidStr) replace_str(line_buffer, "[FUL]", FULidStr);
/*                  replace_str(line_buffer, "[27]", "\x27");
                    replace_str(line_buffer, "[7F]", "\x7F"); */

                    while ( line_buffer[i] != '\0') {
                        if ( line_buffer[i] < 0 ) {
                            ++wrn_cnt;
                            printf ("%s:WARNING for line of text %u, %i. character 0x%02X should be invalid.\n",
                                     argP, line_cnt, i+1, (uchar) line_buffer[i]);
                        }
                        i++;
                    }
                    break ;

                case IDENT_PC16_BAS :

                    if (*SQRidStr) replace_str(line_buffer, "[SQR]", SQRidStr);
                    if (*PI_idStr) replace_str(line_buffer, "[PI]",  PI_idStr);
                    if (*piLidStr) replace_str(line_buffer, "[pi]" , piLidStr);
                    if (*YENidStr) replace_str(line_buffer, "[Y]"  , YENidStr);
                    if (*EURidStr) replace_str(line_buffer, "[E]"  , EURidStr);
                    if (*INSidStr) replace_str(line_buffer, "[INS]", INSidStr);
                    if (*FULidStr) replace_str(line_buffer, "[FUL]", FULidStr);

                    if ( (pcMode & 8)>0 ) { /* 1600K */
                        replace_str(line_buffer, "[YEN]" ,   "\x89\x7E") ;
                        replace_str(line_buffer, "[YEAR]",   "\x94\x4E") ;
                        replace_str(line_buffer, "[MONTH]",  "\x8C\x8E") ;
                        replace_str(line_buffer, "[DAY]" ,   "\x93\xFA") ;
                        replace_str(line_buffer, "[HOUR]",   "\x8E\x9E");
                        replace_str(line_buffer, "[MINUTE]", "\x95\xAA");
                        replace_str(line_buffer, "[SECOND]", "\x95\x62");
                    }

                    break ;

                case IDENT_E_BAS :

                 /* Replacement of this UTF8 chars could work only, if not done fix from E437 table before */
                  if (pcgrpId == GRP_G || (pcgrpId == GRP_E && (pcMode & 0x1C) >0) ) {

                    if (pcId != 220 ) {               /* GRP_G without E220 */
                        /* no special chars for √ or Π exist for this group */
                        /* variable [Tags] preserved in strings, outside this resolved by tokeniser (see shortcuts) */
                        // if (*SQRidStr == 0) replace_str(line_buffer, "[SQR]","SQR ");
                        // if (*PI_idStr == 0) replace_str(line_buffer, "[PI]", "PI ");
                        // if (*piLidStr == 0) replace_str(line_buffer, "[pi]", "PI ");

                        replace_str(line_buffer, "[YEN]" ,   "\xF1") ;
                        replace_str(line_buffer, "[YEAR]",   "\xF2") ;
                        replace_str(line_buffer, "[MONTH]",  "\xF3") ;
                        replace_str(line_buffer, "[DAY]" ,   "\xF4") ;
                        replace_str(line_buffer, "[HOUR]",   "\xF5");
                        replace_str(line_buffer, "[MINUTE]", "\xF6");
                        replace_str(line_buffer, "[SECOND]", "\xF7");

                        if ((pcMode & 0x10) ==0) { /* hidden by driver for 2nd Kanji area */
                            replace_str(line_buffer, "[SPADE]",  "\xE8");
                            replace_str(line_buffer, "[HEART]",  "\xE9");
                            replace_str(line_buffer, "[DIAMOND]","\xEA");
                            replace_str(line_buffer, "[CLUB]",   "\xEB");
                        }
                    }
                    if (*SQRidStr) replace_str(line_buffer, "[SQR]", SQRidStr);
                    if (*PI_idStr) replace_str(line_buffer, "[PI]",  PI_idStr);
                    if (*piLidStr) replace_str(line_buffer, "[pi]" , piLidStr);
                    if (*YENidStr) replace_str(line_buffer, "[Y]"  , YENidStr);
                    if (*EURidStr) replace_str(line_buffer, "[E]"  , EURidStr);
                    if (*INSidStr) replace_str(line_buffer, "[INS]", INSidStr);
                    if (*FULidStr) replace_str(line_buffer, "[FUL]", FULidStr);
                  }
                  else { /* GRP_E (500) */

                    if (*SQRidStr) replace_str(line_buffer, "[SQR]", SQRidStr);
                    if (*PI_idStr) replace_str(line_buffer, "[PI]",  PI_idStr);
                    if (*piLidStr) replace_str(line_buffer, "[pi]" , piLidStr);
                    if (*YENidStr) replace_str(line_buffer, "[Y]"  , YENidStr);
                    if (*EURidStr) replace_str(line_buffer, "[E]"  , EURidStr);
                    if (*INSidStr) replace_str(line_buffer, "[INS]", INSidStr);
                    if (*FULidStr) replace_str(line_buffer, "[FUL]", FULidStr);
                  }
                  break ;
                   // default: {}
                } // end switch ident

                /* replace all placeholders [HH] for special chars of one byte */
                // not planned: replace placeholders for special chars of two bytes
                if (!type_asm) {
                  for ( ii = 1 ; ii < 0x100 ; ++ii) { // [00] is not allowed
                   if (strchr(line_buffer, '[') == NULL) break ;
                    // spec_str = "[FF]"
                    tmpl = ii>>4 ;
                    if (tmpl > 9) spec_str[1] = tmpl + 0x37 ; else spec_str[1] = tmpl | 0x30 ;
                    tmpl = ii & 0x0F ;                                             // A-F, 0-9
                    if (tmpl > 9) spec_str[2] = tmpl + 0x37 ; else spec_str[2] = tmpl | 0x30 ;
                    spec_chr[0] = ii ;
                    replace_str(line_buffer, spec_str, spec_chr);
                  }
                  /* replace ESC placeholders, \xHH for special chars after escape */
                  if (codecnv_opt == UTF8_ESCX)
                    for ( ii = 1 ; ii < 0x100 ; ++ii) { // \x00 is not allowed
                     if (strchr(line_buffer, '\\') == NULL) break ;
                        strcpy (spec_str, "\\xFF") ;
                        tmpl = ii>>4 ;
                        if (tmpl > 9) spec_str[2] = tmpl + 0x37 ; else spec_str[2] = tmpl | 0x30 ;
                        tmpl = ii & 0x0F ;
                        if (tmpl > 9) spec_str[3] = tmpl + 0x37 ; else spec_str[3] = tmpl | 0x30 ;
                        spec_chr[0] = ii ;
                        replace_str(line_buffer, spec_str, spec_chr);
                    }
                }
                i = 0 ;
                while ( line_buffer[i] != '\0') {
                    if ( line_buffer[i] < 0) {
                        ii = 0 ;
                /* Replace leads to 1600(1500) List problems, if the first byte of a 2-byte token results from a E437-char */
                        if ( ident == IDENT_PC15_BAS && (pcMode & 0xC)>0 &&  /* PC-1500J */
                             ( (uchar) line_buffer[i] > BAS_MAX_C15J) ) ii = 2 ; /* List problems in Pocket because expected token*/
                        else if ( ident == IDENT_PC15_BAS && (pcMode & 0xC)>0 &&  /* PC-1500J */
                             ( (uchar) line_buffer[i] > BAS_MAX_CHR) ) ii = 1 ; /* not editable, avoid it */
                        else if ( (ident == IDENT_PC16_BAS || ident == IDENT_PC15_BAS) &&
                             ( (uchar) line_buffer[i] > BAS_MAX_CHR) ) ii = 2 ;  /* 3rd-party PC-1500 token starts also with E0...E6 */
                        else if ( (ident == IDENT_EXT_BAS || pcgrpId == GRP_E || pcgrpId == GRP_G ) &&
                             ( (uchar) line_buffer[i] == BAS_EXT_CODE ) ) ii = 2 ; /* RESERVED, next byte expected token */
                        else if ( (ident == IDENT_NEW_BAS || tokenL == 0 ) &&
                             ( (uchar) line_buffer[i] == BAS_NEW_CODE ) ) ii = 2 ; /* expected 2-byte token */
                        if (ii>1) {
                            ++wrn_cnt;
                            printf ("%s:WARNING for line of text %u, %i. character 0x%02X could be invalid.\n",
                                argP, line_cnt, i+1, (uchar) line_buffer[i]) ;
                        }
                        else if (ii>0) {
                            printf ("%s:In line of text %u, %i. character 0x%02X is not editable.\n",
                                argP, line_cnt, i+1, (uchar) line_buffer[i]) ;
                        }
                    }
                    i++;
                }
                if (Qcnt == 0 && (debug & 0x20) >0 ) {
                /* Show content of line_buffer after preprocessor as hex values */
                    i = 0;
                    printf ("t<");
                    while ( line_buffer[i] != '\0') { printf ("%02X ", (uchar) line_buffer[i]); i++; }
                        printf ("%02X", (uchar) line_buffer[i]);
                    printf (">\n") ;
                }
            }

        /* End of preprocessor of a line, starting 1. part of main processing */
			inline_len2 = strlen (line_buffer);
			strcpy( line_nbr, "" );

			/* Get the line number */
			while ( isdigit( (uchar) *line_buffer ) )
			{
				strncat( line_nbr, line_buffer, 1 );
				shift_left( line_buffer );
			}
			strcat( line_nbr, "\0" );  /* Finish string */

			/* line_buffer2 protects text constants in BASIC Lines */
            strcpy( line_buffer2, line_buffer );

            if ((debug & 8) == 0) {
                strupr( line_buffer );  /* Some special chars was converted by strupr to false code, undo it */
                for ( ii = strlen( line_buffer ) ; ii > 0 ; ) { --ii;
                        if ( (uchar) line_buffer2[ii] > 0xDF ) line_buffer[ii] = line_buffer2[ii] ;
                }
                if (pcId == 1421) /* special financial variables */
                    for ( ii = strlen( line_buffer ) ; ii > 0 ; ) {
                        --ii;
                        if (line_buffer2[ii]=='i') line_buffer[ii] = 'i' ;
                        if (line_buffer2[ii]=='n') line_buffer[ii] = 'n' ;
                    }
                else if ( ident == IDENT_PC15_BAS || ident == IDENT_PC16_BAS )
                    for ( ii = 0 ; ii + 5 < strlen( line_buffer2 ) ; ii++ ) {
                        /* CE-158 CSAVE/CLOAD r/a, MERGE a */

                        if ( strncmp (line_buffer +ii, "MERGE", 5) == 0 ||
                             strncmp (line_buffer +ii, "CLOAD", 5) == 0 ||
                             strncmp (line_buffer +ii, "CSAVE", 5) == 0  ) {
                             if      (line_buffer2[ii + 5] == 'a'  ) line_buffer[ii + 5] = 'a' ;
                             else if (line_buffer2[ii + 5] == ' ' &&
                                      line_buffer2[ii + 6] == 'a'  ) line_buffer[ii + 6] = 'a' ;
                        }
                        if ( strncmp (line_buffer +ii, "CLOAD", 5) == 0 ||
                             strncmp (line_buffer +ii, "CSAVE", 5) == 0  ) {
                             if      (line_buffer2[ii + 5] == 'r'  ) line_buffer[ii + 5] = 'r' ;
                             else if (line_buffer2[ii + 5] == ' ' &&
                                      line_buffer2[ii + 6] == 'r'  ) line_buffer[ii + 6] = 'r' ;
                        }
                    }
                /* for models that do not support lowercase letters at all*/
                if (cnvstr_upr) strcpy( line_buffer2, line_buffer );
            }

            /* process the line number */
            ii = strlen (line_nbr) ;                             /* Temp. length of read line number */
            if (ii>0) spc_cnt1 = 0 ;                             /* Spaces before a line number are ignored */
            if (auto_new && line_cnt>1 ) strcpy( line_nbr, "" ); /* delete existing line numbers */

            if( strlen(line_nbr)==0 && (debug & BAS_AUTO)>0 ) {
                zeilennummer = pre_zeilennr + auto_inc;
                sprintf(line_nbr, "%ld", zeilennummer);
            }
            else {
                zeilennummer = strtoul ( line_nbr, &ptrErr, 0) ;
                if (*ptrErr != 0) {
                  printf ("%s: Line number %s is not valid\n", argP, line_nbr ) ;
                  error = ERR_LINE ;
                  break ;
                }
			}
			line_nbr_len = strlen (line_nbr);

			if ( zeilennummer==0 ) {
                if (strlen(line_buffer)>0) {
                    if (Qcnt==0) printf ("Text line no. %u without valid number was ignored.\n", line_cnt);
                    ++wrn_cnt;
                }
			}
			else if (!(debug & (INS_APST | SPC_LINES_OK))
                                         && (strlen(line_buffer)==0 ||    /* E500 executes source code where lines consist of only a colon */
                                             strlen(line_buffer)== strspn(line_buffer," " )  ||
                      ( pcgrpId != GRP_E &&  strlen(line_buffer)== strspn(line_buffer," :") ) ) ) { /* this does not run for other series. */
                    if (Qcnt==0 && ((debug & 0xE0)>0 || ii>0))
                        printf ("Line number %lu, empty text line no. %u was ignored.\n", zeilennummer, line_cnt);
                    if (ii>0) ++wrn_cnt;
			}
            else
			{
                strcpy( out_line, "" );
                i_out_line = 0;

                if (type == TYPE_ASC) {
                    strcpy( out_line, line_nbr );
                    i_out_line = line_nbr_len;
                }
				else if (! ( pre_zeilennr < zeilennummer ) ) {
					printf("%s: Merged line number %lu: not higher than previous line number %lu\n",
                            argP, zeilennummer, pre_zeilennr );
					// printf("%s: Previous line number: %lu\n", argP, pre_zeilennr );
					// printf("%s: Actual line number: %lu\n", argP, zeilennummer );
					if ( pcgrpId == GRP_E || pcgrpId == GRP_G) {
                        printf("%s: This line number sequence is illegal for group of %i\n", argP, pcId);
                        if ((debug & 0x800) == 0 ) {
                            error = ERR_LINE ;
                            break ;
                        }
                        else ++err_cnt;
                    }
                    else if (ident != IDENT_OLD_BAS && (debug & 0x800) == 0) {
                        InsertMergeMark = true;
                        ++wrn_cnt;
                    }
                    else ++wrn_cnt;
                }
				strcpy( line_nbr, "" );

				if ( ident == IDENT_OLD_BAS )
				{
					if ( zeilennummer > 999 )
					{
                      if ( zeilennummer == MERGE_MARK) continue ; /* not used in OLD_BAS read next line*/

					  printf("%s: Line number: %lu higher than 999 (MAX line number)\n", argP, zeilennummer );
					  if ((debug & 0x800) == 0) {
                            error = ERR_LINE ;
                            break ;
                      }
                      else ++err_cnt;
					}
                    if (type != TYPE_ASC) {
                        out_line[0] = (uchar) ( zeilennummer / 100 | 0xE0 );
                        i_out_line++;
                        tmpl = zeilennummer - (100 * out_line[0]);
                        out_line[1] = (uchar) ( ((tmpl / 10 ) << 4) | (tmpl % 10) );
                        i_out_line++;
					}
				}
				else
				{
					if ( zeilennummer == MERGE_MARK || InsertMergeMark ) { /* merged basic programs */

                        if ( zeilennummer == MERGE_MARK && (pcgrpId == GRP_E || pcgrpId == GRP_G))
                                                  continue ; /* not support in E_BAS, read next line*/
                        if (type != TYPE_ASC) {
                            out_line[0] = '\xFF'; /* Start mark of a merged basic program block */
                            i_out_line++;

                            if (Qcnt == 0 && (debug & 0x40) >0 ) printf ("o> %02X<\n", (uchar) out_line[0]);
                        }
                        else if (Qcnt == 0 && (debug & 0x40) >0) printf ("o> %s<\n", out_line);

                        fwrite( out_line, sizeof( char ), i_out_line, dateiaus );

                        if (InsertMergeMark) {
                            InsertMergeMark = false ;
                            if (Qcnt ==0) printf ("%s: Merging line %lu was missed but mark inserted.\n",
                                                  argP, (ulong) MERGE_MARK);
                            /* process the actual line*/
                            strcpy( out_line, "" );
                            i_out_line = 0;
                        }
                        else { // MERGE_MARK
                            pre_zeilennr = 0;
                            continue ; /* read next line*/
                        }
					}
					if ( zeilennummer > 65279 ) {
					  printf("%s: Line number: %lu higher than 65279 (MAX line number)\n", argP, zeilennummer );
                      error = ERR_LINE ;
                      break ;
					}
                    if (type != TYPE_ASC) {
                        if (lnb_order == B_ENDIAN_LITTLE) {
                            out_line[line_nbb_pos] = (uchar) (zeilennummer);
                            out_line[line_nbb_pos+1] = (uchar) (zeilennummer / 256 );
                        }
                        else { // B_ENDIAN_BIG
                            out_line[line_nbb_pos] = (uchar) (zeilennummer / 256 );
                            out_line[line_nbb_pos+1] = (uchar) (zeilennummer);
                        }
                        i_out_line++;
                        i_out_line++;

                        for ( ii = 0 ; ii < line_len_bytes ; ++ii) { /* only after line number supported */
                            out_line[line_len_pos + ii] = '\xFF'; /* Placeholder for length of Binary image command line (or addr of next) */
                            i_out_line++;                       /* Length is not in images of type OLD_BAS */
                        }
                    }
				}
                pre_zeilennr = zeilennummer;

                if (inline_len2 > ll_Img ) {  /* long source line, text modus may fail */
                      if (Qcnt==0 && (debug & 0xA0) >0 && (debug & 0x800) == 0)
                        printf ("%s: The length of line number %lu: is %u (for the text editor).\n",
                                                                    argP, zeilennummer, inline_len2) ;
                      // ++wrn_cnt;
                }
        /* End of line number processing, process chars between line number and body */

				/* Delete colon and spaces following the line number */
				if ( !type_asm || asm_id > 4) {
                    error = prc_spaces( line_buffer, line_buffer2, &spc_cnt, out_line, &i_out_line, del_spc_cnt) ;
                    if (error != ERR_OK) break ;
                    if (strlen(line_buffer) > strspn(line_buffer," :") || /* E-500 more chars than space and colon exist */
                        strrchr(line_buffer, COLON) - strchr(line_buffer, COLON)>0) { /* more colons exist */
                        del_colon( line_buffer );
                        del_colon( line_buffer2 );
                    }
				}
				else spc_cnt = 0;

                string_auf = false; /* string_open: not */
                if ((debug & INS_APST)>0 &&     /* Insert a string or comment at the beginning of the line, if not already exists */
                    *line_buffer != '"' && *line_buffer != ins_apst &&  /* an accepted sign */
                    (type != TYPE_IMG || *line_buffer != '\'') &&       /* an in images accepted as REM or replaced by REM */
                    (REMidC==0 || *line_buffer != REMidC))              /* other characters accepted for REM */
                {
                        out_line[i_out_line++] = ins_apst;
                        string_auf = !string_auf;
                }

                if ((ident == IDENT_E_BAS || (type_asm && ins_spc1 != 0)) && spc_cnt1>0) /* Recover leading spaces from non-numbered lines */
                    while (spc_cnt1-- > 0) out_line[ (i_out_line)++] = 0x20;

                else if ( type_asm && ins_spc1 != 0 && spc_cnt1 == 0) { /* ASM Files need leading space without labels */
                    string_auf = !string_auf;
                    if ( spc_cnt > 0 && (pcgrpId == GRP_G || asm_id == 4)) /* Recover leading spaces after lnb, for CASL and PIC assembler */
                        while (spc_cnt-- > 0) out_line[ (i_out_line)++] = 0x20;
                    else if ( asm_id == 8 )
                     for ( ii = 0 ; ii < 7 ; ++ii) { /* label length 6 + colon, for E200-G850VS internal assembler only */
                        if ((line_buffer[ii] >= '?' && line_buffer[ii] <= '[') || /* includes @, A-Z */
                            (line_buffer[ii] >= '0' && line_buffer[ii] <= '9') ||
                             line_buffer[ii] == '_' || line_buffer[ii] == ']'   ) continue ;
                        if ( line_buffer[ii] == COLON ) break ;
                        else {
                            out_line[i_out_line++] = ' ';
                            break;
                        }
                     }
                }
        /* End of 1. part of main processing, process the body of the line */

				if (type == TYPE_TXT || type == TYPE_ASC ) {
                    if (!string_auf) error = prc_spaces( line_buffer, line_buffer2, &spc_cnt, out_line, &i_out_line, del_spc_cnt) ;
                    if (error != ERR_OK) break ;
                    if (type == TYPE_ASC && pcgrpId != GRP_G) {
                        // if (spc_cnt == 0)
                        out_line[i_out_line++] = 0x20;
					}
                    while ( !( *line_buffer == '\0' ) )
                    {
                        out_line[i_out_line++] = *line_buffer2;
                        shift_left2( line_buffer, line_buffer2 );
                    }
				}
                else  { /*TYPE_IMG*/
                  bracket_level = 0 ;
                  token_type1 = 0 ;                         /* no TOKEN_LST before */
                  if ( ident == IDENT_E_BAS || cnv_Elabel)
                        token_type = BGN_LINE | TOKEN_LBL ;  /* force check for one E-label at begin of line */
                  else token_type = 0 ;

				  /* Loop to End of line, process the body of a line, begin of tokenizer */
				  while ( !( *line_buffer == '\0' ) )
				  {
                    if (ident == IDENT_E_BAS && !string_auf ) { /* Transfer leading spaces */
                        error = prc_spaces( line_buffer, line_buffer2, &spc_cnt, out_line, &i_out_line, pcgrpId==GRP_E ? 0 : del_spc_cnt) ;
                        if (error != ERR_OK) break ;
                        if ( *line_buffer == '*' && (token_type & TOKEN_LBL) >0 ) {
                            /* Label of E/G-Series, may have command-strings inside */
                            if (cnv_Elabel ) { //&& !string_auf
                                out_line[i_out_line++] = '"';
                                shift_left2( line_buffer, line_buffer2 );
                            }
                            do
                            {   out_line[i_out_line++] = *line_buffer;
                                shift_left2( line_buffer, line_buffer2 );

                              /* Definition, which characters may (not)/be included in a label */
                            } while ( !( *line_buffer == ' ' || *line_buffer == ':' || /* Label also without : */
                                         *line_buffer == ',' || *line_buffer == REMidC ||
                                         *line_buffer == '"' || *line_buffer == '\0' )  &&
                                    ((*line_buffer >= '@' && *line_buffer <= 'Z') ||
                                     (*line_buffer >= '0' && *line_buffer <= '9') ||
                                      *line_buffer == '[' || *line_buffer == ']'  ||
                                      *line_buffer == '?' || *line_buffer == '_'   )     );
                            if (cnv_Elabel ) { //&& !string_auf
                                out_line[i_out_line++] = '"';
                                if ( (token_type & BGN_LINE) >0 && *line_buffer == ':')
                                    shift_left2( line_buffer, line_buffer2 ); /* necessary for stand-alone label, not E-series */
                            }
                            error = prc_spaces( line_buffer, line_buffer2, &spc_cnt, out_line, &i_out_line, 0) ; /* keep spaces, separator */
                            pre_Elabel = true ;
                        }
                        else pre_Elabel = false ;
                    }
                    else if ( cnv_Elabel && !string_auf) {
                        error = prc_spaces( line_buffer, line_buffer2, &spc_cnt, out_line, &i_out_line, del_spc_cnt) ;
                        if (error != ERR_OK) break ;
                        if ( *line_buffer == '*' && (token_type & TOKEN_LBL) >0 ) {
                            /* Convert label of E/G-Series to a string */
                            out_line[i_out_line++] = '"';
                            shift_left2( line_buffer, line_buffer2 );
                            do
                            {   out_line[i_out_line++] = *line_buffer;
                                shift_left2( line_buffer, line_buffer2 );

                              /* Definition, which characters may (not)/be included in a label */
                            } while ( !( *line_buffer == REMidC || *line_buffer == '\0') &&
                                    ((*line_buffer >= '@' && *line_buffer <= 'Z') ||
                                     (*line_buffer >= '0' && *line_buffer <= '9') ||
                                      *line_buffer == '[' || *line_buffer == ']'  ||
                                      *line_buffer == '?' || *line_buffer == '_'   )      );

                            out_line[i_out_line++] = '"';
                            if ( (token_type & BGN_LINE) >0 && *line_buffer == ':') shift_left2( line_buffer, line_buffer2 );
                            error = prc_spaces( line_buffer, line_buffer2, &spc_cnt, out_line, &i_out_line, del_spc_cnt) ;
                        }
                    }
                    else if (!string_auf) /* Delete leading spaces */
                        error = prc_spaces( line_buffer, line_buffer2, &spc_cnt, out_line, &i_out_line, del_spc_cnt) ;
                    if (error != ERR_OK) break ;
					/* Comment OR $-out */
					if ( *line_buffer == '"' )  /* jump label or alternative REM line */
					{
						string_auf = !string_auf;
						if (!string_auf) {
								out_line[i_out_line++] = *line_buffer;
								shift_left2( line_buffer, line_buffer2 );
                        }
					}
						if ( string_auf )
						{   // use line_buffer2 (lower cases)
							do
							{
								out_line[i_out_line++] = *line_buffer2;
								shift_left2( line_buffer, line_buffer2 );
							} while ( !( *line_buffer == '"' || *line_buffer == '\0' ) );

                            if ( *line_buffer == '"' )
                            {
                                string_auf = !string_auf;
                                out_line[i_out_line++] = *line_buffer;
                                shift_left2( line_buffer, line_buffer2 );
                            }
						}
//						else
//						{   // use line_buffer
//							do
//							{
//
//							} while ( !( *line_buffer == '"' || *line_buffer == '\0' ) );
//						}
					if ( *line_buffer == ':' )
					{
						pre_colon = true ;
						token_type1 = token_type = 0 ; /* new command follows */
                        bracket_level = 0 ;
						out_line[i_out_line++] = *line_buffer;
						shift_left2( line_buffer, line_buffer2 );
					}
					else pre_colon = false ;
                                                /* Check for Kanji (2 byte chars) outside REM and strings   */
                    if ( (pcMode & 0x18) >0) {  /* and transfer it or tokenise special Kanji chars (PI, pi) */
                        if (is_kanji2C( line_buffer, line_buffer2, out_line, &i_out_line, &i_token) ) continue ;
                    }

                    /* Reading a string containing only characters that could be a command for the tokenizer */
					while ( (bool)(is4cmd = IsChar4Cmd( line_buffer, befehl, Ocnt>0 || Kcnt>0 ) ) ) /* false, true or last4CMD */
					{   /* Read the next text to check for a token */
						if (strlen(befehl) < cLC-1) {
                                strncat( befehl, line_buffer, 1 );
                                strncat( befehl2, line_buffer2, 1 );
						}
						else {
                            printf ("%s: A word with excessive length found in line with number %lu.\n",
                                        argP, zeilennummer) ;
                            error = ERR_MEM ;
                            break ;
						}
						shift_left2( line_buffer, line_buffer2);
                      if (is4cmd == last4CMD) break ; /* last char allowed only at the end of a command */
					}
                    if (error != ERR_OK) break ;

					if ( strlen( befehl ) ) /* Core of the tokenizer */
					{   // Code optimization of the tokenizer was done in 2019

						do /* Forward search: Start with the longest allowable (for a command) string found here */
						{  /* Outer loop: begin of while with next (shifted out) leading char */

							while ( (uint) strlen( befehl ) >= command_len_min ) // > -> >= // i_token == 0 &&
							{   /* Inner loop: shorten the length by one character from the end for each additional attempt */
								i_token = istoken( befehl );  // 2. part of tries */
                                if ( i_token > 0) {
                                    token_type = TokenType (i_token);
                                    if ( (token_type & TOKEN_LST) >0 ) token_type1 = token_type ;
                                }
                                else token_type = 0;

                                /* If necessary, further tokens can be processed here individually
                                   if this is not done in CompileFixedJumpNb or by Post-processor. */
								if ( (token_type & TOKEN_REM) >0 )  /* REM */
                                    prc_REMid( line_buffer, line_buffer2, befehl, befehl2, merke, merke2, /* merke empty */
                                               out_line, &i_out_line, &i_token, delREMspc); //, REM_out_buf1
								else if ( i_token )
								{   /* write it out */
								    if (pre_Elabel && pcgrpId == GRP_G && out_line[i_out_line-1] == ' ') --i_out_line;
                                    if ((token_type & TOKEN_COL) >0 && pre_colon == false )
                                                        out_line[i_out_line++] = ':'; /* also done by Post-processor */
								    /* More token specific work can be done here */

									if  ( tokenL == 2 || i_token > 255 )   /* 2Byte-Token */
                                        out_line[i_out_line++] = (uchar) ( i_token >>8 );
									out_line[i_out_line++] = (uchar) i_token;
									strcpy( befehl, "" ); strcpy( befehl2, "" );

                                    /* Skip the tokenization of the E500 DATA values */
                                    if ( pcgrpId == GRP_E && i_token == 0xFE5E ) {
                                        /* E500 series: do not tokenize DATA values */
                                        /* fine-tune for spaces, delete one space after a command string for E/G series */
                                        error = prc_spaces( line_buffer, line_buffer2, &spc_cnt, out_line, &i_out_line, del_spc_cnt ) ;
                                        if ( error == ERR_OK ) {
                                            /* keep DATA values as they are until : or end of line */
                                            while ( *line_buffer != '\0' ) {
                                                if ( *line_buffer == ':' && !string_auf )
                                                    break;
                                                out_line[i_out_line++] = *line_buffer ;
                                                if ( *line_buffer == '"')
                                                    string_auf = !string_auf;
                                                shift_left2( line_buffer, line_buffer2 );
                                            }
                                        }
                                    }
								}
								else
								{   /* Memorize the last characters of command string, stored in reverse order */
									strcat( merke, befehl + strlen( befehl ) - 1 );
									strcat( merke2, befehl2 + strlen( befehl2 ) - 1 );
									/* shorten the possible command string */
									*( befehl + strlen( befehl ) - 1 ) = '\0';
									*( befehl2 + strlen( befehl2 ) - 1 ) = '\0';
								}
							}  /*end while inner loop, shorten the end of the command string */

							while ( strlen ( merke ) ) /* Restore the rest of string */
							{
								strcat( befehl, ( merke + strlen( merke ) - 1 ) );
								*( merke + strlen( merke ) - 1 ) = '\0';
								strcat( befehl2, ( merke2 + strlen( merke2 ) - 1 ) );
								*( merke2 + strlen( merke2 ) - 1 ) = '\0';
							}

							if ( strlen( befehl) && !i_token )  // was not token
                            {   /* Check leading character if special one-byte-char=token and write a token out */
                                prc_token1C( befehl, befehl2, out_line, &i_out_line, &i_token1C) ; /* e.g. PC-1600: [ == SQR */
                                if ( !i_token1C ) { // not 1-char-token
                                    /* Write out and remove the leading character of the string */
                                    out_line[i_out_line++] = *befehl;
                                    shift_left2( befehl, befehl2);
                                }
							}  /* Continue with the string reduced by the leading character */

						} while ( (uint) strlen( befehl ) >= command_len_min && /* Outer loop, shift the begin of command */
                                   ident != IDENT_E_BAS );  /* Variable names with commands inside allowed for E/G series */

						if ( strlen( befehl ) ) /* transfer the rest of the or a to short command */
						{   token_type = 0 ;    /* don t check for an E-Label */
							memcpy( &out_line[i_out_line], befehl, strlen( befehl ) );
							i_out_line += strlen( befehl );
							strcpy( befehl, "" ); strcpy( befehl2, "" );
						}
						else if (i_token) /*  fine-tune for spaces, delete one space after a command string for E/G series */
                            error = prc_spaces( line_buffer, line_buffer2, &spc_cnt, out_line, &i_out_line, del_spc_cnt ) ;

					}   // end if tokenizer core (strlen befehl)

					else /* No command string could build possible for a token, other characters of the line */
					{
						if ( !( *line_buffer == '\0' || /* process in the first part of the loop*/
                                *line_buffer == ' '  || *line_buffer == '"' || *line_buffer == ':' ) )
                        {
						    /* check for special one-byte-char =token (PI etc.) to convert to token */
						    /* Only characters that may be in the command string are treated here   */
						    prc_token1C( line_buffer, line_buffer2, out_line, &i_out_line, &i_token) ;
                            if ( i_token ) { /* only token */

                                token_type = TokenType (i_token);
                                if ( (token_type & TOKEN_REM) >0 ) /* REMidC changed to REMid  by istoken1 */
                                  while ( !( *line_buffer == '\0' ) )    /* transfer the rest of the line */
                                  {
                                    out_line[i_out_line++] = *line_buffer2;
                                    shift_left2( line_buffer, line_buffer2);
                                  }
                            }    // end 1-byte-Char as token found
                            else if ( *line_buffer == REMidC ) {    /* 2. REM-id, One char */

                                if (ident == IDENT_E_BAS && pre_colon == false)
                                    out_line[i_out_line++] = ':'; /* also done by Post-processor */

                                out_line[i_out_line++] = *line_buffer;
                                shift_left2( line_buffer, line_buffer2);

                                if (pcgrpId == GRP_E) {
                                    out_line[i_out_line++] = BAS_E_JMP;
                                    out_line[i_out_line++] = (uchar) (strlen(line_buffer2) +2);
                                }
                                while ( !( *line_buffer == '\0' ) ) /* transfer the rest of the line */
                                {
                                    out_line[i_out_line++] = *line_buffer2;
                                    shift_left2( line_buffer, line_buffer2);
                                }
                            }  // end REMid Char found
                            else if ( *line_buffer == '(' ) {
                                ++bracket_level;
                                out_line[i_out_line++] = *line_buffer;
                                shift_left2( line_buffer, line_buffer2 );
                            }
                            else if ( *line_buffer == ')' && bracket_level >0) {
                                --bracket_level;
                                out_line[i_out_line++] = *line_buffer;
                                shift_left2( line_buffer, line_buffer2 );
                            }
                            else {
                                if (*line_buffer == ',' && bracket_level ==0 &&
                                    (token_type1 & TOKEN_LST) >0 ) token_type = TOKEN_LBL;
                                    /* check or not for E_BAS labels next */
                                else // if (*line_buffer != ' ' )
                                    token_type = 0;

                                /* Write out all the other characters */
                                out_line[i_out_line++] = *line_buffer;
                                shift_left2( line_buffer, line_buffer2);
                            }
						}   // character for next loop or end of line
					}  // end if no command string build

				  } /* end while (until End Of Line), End of tokenizer */
                  if (error != ERR_OK) break ;

				  if ( string_auf && debug & 0x02 ) /* Better readable source but longer lines with apostrophe at end  */
				  {
					out_line[i_out_line] = '"';
					i_out_line++;
					string_auf = !string_auf;
				  }

                  /* Post-processing for RemIdChar and ELSE of G series, no more at moment, and
                     the Compile of fixed numeric line number to binary format for 16/G/E/EXT_BAS,
                     see Wav2bin ReadLineFromBasWav, "case IDENT_E_BAS" */

                   if ( ident == IDENT_E_BAS ) {
                        error = PostProcess_G( REMidC, out_line, &i_out_line ) ;
                        if (error == ERR_MEM) {
                            ++err_cnt;
                            printf ("\n WARNING: Post-processed line would be to long, line: %lu\n\n", zeilennummer) ;
                        }
                   }
        /* Post-processing of E-500 Series  1. step (prc_REMid together with PostProcess_G, placeholder for jump marks),
                                            2. step (all numeric constants to BCD is done now in CompileFixedJumpNb),
                                            3. step (calculate jump marks): could be done at end of file processing, but is
                                            not necessary because the PC-E500 optimizes the jumps itself during runtime  */

                   if ( (debug & 0x01)==0 && ident != IDENT_OLD_BAS && ident != IDENT_NEW_BAS && ident != IDENT_PC15_BAS ) {

                        if (Qcnt == 0 && (debug & 0x40) >0 ) {
                            /* Display the contents of line_buffer as hex values after tokenization and before compilation  */
                            ii = 0;
                            printf ("t>");
                            for ( ii = 0 ; ii <= i_out_line ; ++ii)
                                printf (" %02X", (uchar) out_line[ii]);
                            printf ("<\n") ;
                        }
                        error = CompileFixedJumpNb( REMidC, out_line, &i_out_line ) ;
                        if (error == ERR_MEM) {
                            ++err_cnt;
                            printf ("\n WARNING: Compiled line would be to long, line: %lu\n", zeilennummer) ;
                        }
                        else if (error == ERR_LINE) {
                            ++err_cnt;
                            printf ("\n WARNING: Illegal line numbers found in line: %lu\n", zeilennummer) ;
                        }
                        else if (error == ERR_ORD) {
                            ++err_cnt;
                            printf ("\n WARNING: Invalid decimal value found in line: %lu\n", zeilennummer) ;
                        }
                        if ( error > 0) printf
                           ("After the transfer you have to switch to 'TEXT' and back to 'BASIC'!\n\n") ;
                   }


                } // if End TYPE_IMG
                if (type == TYPE_ASC) {
                    /* In ASCII file each End Of Line is indicated by 0x0D 0x0A*/
                    out_line[i_out_line] = '\x0D'; /* Usage of '\r' could be system dependent! */
                    i_out_line++;
                    out_line[i_out_line] = '\x0A';
                    i_out_line++;
                    tmpl = i_out_line ;
                    if (tmpl > ll_Img && (debug & 0x800) == 0) {
                            ++wrn_cnt;
                            printf ("\n WARNING: ASCII line length %i to long - not editable, line: %lu\n\n", tmpl, zeilennummer) ;
                    }
                    if (tmpl > 0xFF) {
                            ++err_cnt;
                            error = ERR_MEM ;
                            break ;
                    }
                    total += i_out_line ;
                }
				else if (ident == IDENT_OLD_BAS ) {
                    out_line[i_out_line] = bas_eol; //'\x00'
                    conv_asc2old(out_line, i_out_line) ; /* convert ASCII chars to OLD chars */
                    i_out_line++;
                    tmpl = i_out_line - line_lc ;
                    if (tmpl > ll_Img - line_nbr_len && (debug & 0x800) == 0) {
                        ++wrn_cnt;
                        printf ("\n WARNING: Image line length %i to long - not editable, line: %lu\n\n", tmpl, zeilennummer) ;
                    }
                    if (tmpl > 0xFF) {
                            ++err_cnt;
                            error = ERR_MEM ;
                            break ;
                    }
                    total += i_out_line ;
                }
                else {
                    /* In Binary image file each End Of Line is indicated by 0x0D */
                    if (asm_id != 4) /* PC-144x ASM without CR */
                        out_line[i_out_line++] = bas_eol; /* '\x0D', Usage of '\r' could be system dependent! */
                    tmpl = i_out_line - line_lc ;
                    if (tmpl > ll_Img - line_nbr_len && (debug & 0x800) == 0) {
                        if (type == TYPE_TXT) {
                            ++err_cnt;
                            printf ("\n ERROR %i: Image line length %i is to long, line: %lu\n", ERR_MEM, tmpl, zeilennummer) ;
                            error = ERR_MEM ;
                            break ;
                        }
                        else {
                            ++wrn_cnt;
                            printf ("\n WARNING: Image line length %i to long - not editable, line: %lu\n\n", tmpl, zeilennummer) ;
                        }
                    }
                    if (tmpl > 0xFF) {
                            ++err_cnt;
                            printf ("\n ERROR %i: Image line length %i is to long, line: %lu\n", ERR_MEM, tmpl, zeilennummer) ;
                            error = ERR_MEM ;
                            break ;
                    }
                    else if (tmpl < 2) {
                            ++wrn_cnt;
                            printf ("\n WARNING: Image line length %i to short - not usable, line: %lu\n\n", tmpl, zeilennummer) ;
                    }
                    total += i_out_line ;
                    if (line_len_bytes == 1) {
                        if (asm_id == 4) {
                            out_line[line_len_pos] = out_line[line_len_pos-2] ; /* CASL: reverse byte order */
                            out_line[line_len_pos-2] = (uchar) tmpl+3 ;       /* Length of line with header */
                        }
                        else
                            out_line[line_len_pos] = (uchar) tmpl ; /* Length of Binary image command line */
                    }
                    else if (line_len_bytes == 2) { /* not for Poke Com */
                        if (llc_mode == B_LINE_L_ABS) tmpl = total + base_addr ;
                        if (lln_order == B_ENDIAN_LITTLE) {
                            out_line[line_len_pos] = (uchar) (tmpl);
                            out_line[line_len_pos+1] = (uchar) (tmpl / 256 );
                        }
                        else { // B_ENDIAN_BIG
                            out_line[line_len_pos] = (uchar) (tmpl / 256 );
                            out_line[line_len_pos+1] = (uchar) (tmpl);
                        }
                    }
                } // end if No OLD_BAS
                if (Qcnt == 0 && (debug & 0x40) >0 ) {
                    /* Show content of line_buffer as hex values */
                    ii = 0;
                    printf ("o>");
                    for ( ii = 0 ; ii < i_out_line ; ++ii)
                        printf (" %02X", (uchar) out_line[ii]);
                    printf ("<\n") ;
                }
				fwrite( out_line, sizeof( char ), i_out_line, dateiaus );
			}  // end if ( zeilennummer ) : line number
         } // end while getlineF line_buffer

        /* EOF mark for PC-1500 from image removed for compatibility of this image with images from Wav2bin and
           for uniformity with the other images, Bin2wav also does append it (now: if it was not found before)
           use parameter --endmark if you need it */
		   // if (ident == IDENT_PC15_BAS )  {  /* In Binary image file of PC-1500 a 0xFF was additional used as End Of File indicator */
		if ((debug & BAS_EOF_INCL ) >0) {
                 if (type == TYPE_IMG || type == TYPE_TXT){
                    ++total ;
                    out_line[0] = bas_eof; //'\xFF' in old RAM not old wav mark
                    fwrite( out_line, sizeof( char ), 1, dateiaus );
                 }
                 else if (type == TYPE_ASC){
                    ++total ;
                    out_line[0] = EOF_ASC; //'\x1A'
                    fwrite( out_line, sizeof( char ), 1, dateiaus );
                 }
                 if (Qcnt == 0) printf ("The requested end mark was added to the file.\n" );
        }
		fclose( dateiaus );
		if (Qcnt == 0)  {
            printf("File %s was written\n with %lu bytes", argD[1], total );
            if (wrn_cnt > 0 && (debug > 0 || err_cnt == 0) ) printf (", %ld warning(s)", wrn_cnt );
            if (err_cnt > 0) printf (", %ld minor error(s)!\n", err_cnt );
            else printf ("\n");
		}
		fclose( dateiein );
	}  // end if dateiein fopen
	else /* open with error : öffnen fehlerhaft */
	{
		error = ERR_FILE ;
		printf ("%s: Can't open the source file: %s\n", argP, argD[0]);
	}
	if (line_cnt < 1) {
        error = ERR_FILE ;
		printf ("%s: Empty or locked source file: %s\n", argP, argD[0]);
	}

    if (error != ERR_OK && error != ERR_NOK) {
            if (debug != 0) printf ("Exit with fatal error %d\n", error) ;
            return (error) ;
    }
    else return (EXIT_SUCCESS) ;
}   // Before debugging, you should set two breakpoints here and in MoreInfo
