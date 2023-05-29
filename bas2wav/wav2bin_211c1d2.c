/* Textcoding Unicode (UTF-8, no BOM), End of Line Windows (CRLF)

wav2bin.c

For the copying conditions, please note the comments in front of and the output (--version) of the "PrintVersion" function.

Development history
-------------------
      until V 1.3	www.pocketmuseum.com

2006-02-17	Marcus von Cube <marcus@mvcsys.de>
	Handling of data files handled (preliminary!)

2011-12-05	V 1.5	Manfred NOSSWITZ
	Changed to ANSI-C e.g. strupr()
	Translation of π (PI), √ (SQR) and ¥ (Yen). (utf-8 <-> Sharp-ASCII)
	Command line parser changed to getopt().
	Quiet mode and Minimum width of line number added.
	32bit compilation with gcc (tdm64-1) 4.6.1 (WindowsXP-prof [32bit]): gcc -pedantic -m32 -o xxx xxx.c
	32bit compilation with gcc-4_5-branch revision 167585 (OpenSUSE 11.4 [32bit]): gcc -pedantic -m32 -o xxx xxx.c
	64bit compilation with gcc (tdm64-1) 4.6.1 (Windows7-prof [64bit]): gcc -pedantic -m64 -o xxx xxx.c
	64bit compilation with gcc-4_5-branch revision 167585 (OpenSUSE 11.4 [64bit]): gcc -pedantic -m64 -o xxx xxx.c
	For testing PC-1402 was available only.

2014-03-05	V 1.6.0 beta 12	Torsten Muecker
	Additional sums in the headers of data files removed, variable length !=8 allowed,
	Added calculation of most checksums, but without most headers, not all footers at moment,
    False Checksum stops processing with "ERROR 8", use -l 0x800 to ignore and continue
    Exit codes other then ERR_NOK added and will be returned to OS,
    Arguments buffer length protected,
    Line buffer length protected,
    Wav time of checksum added to "ERROR 8"-Message,
    Debug-Modus 0x0400 will show the wav time of every byte now (for editing wav files),
    CodeNew/Ext additional leading spaces added for TO, STEP, THEN, AND, OR, XOR, ELSE
    added special chars to extended basic,
    Token for PC-1421 added, option -p was needed,
    2-byte-tokens for PC-1403, 1460, 1445, 1425 added,
    PC-1280 and more PCs added,
    check of maximal images line length added beginning with new BAS, check CR
    tidy up --help screen
    higher sample rate allowed, use the native frequency of audio hardware up to 96000,
    support of 16-bit wav files (8, 24, other rates experimentally),
    text data allowed now after the end of audio data
    24- and 32-bit wav files supported, audio up to 96 kHz (studio tapes)
    Sync PC-1500 with 2500 Hz only
    more pockets implemented, but NOT the E-series in native mode
    multichannel wav files (stereo, 4) are supported, first channel (left) is processed
    removed some compiler warnings because comparing signed with unsigned integers
    reduced the difference between low and high sound level, better with precise audio hardware
    use old definition with debug: - l 0x2000  (for older or noisy wav files)
    rounding error for &FF corrected with 16-bit samples and higher
2014-04-07	V 1.6.1 beta 7b  Torsten Mücker
    added differential component to PCM signal processing for middle and higher sample rates,
        to compensate signal errors where amplitudes "on the false side of the neutral line",
        does not work for PC-1500 low frequency signal form !
    Support for ReSerVe data and type=RSV added, not tested with PC-1500
    Processing of old Exp sign €/[E] and non-UTF equal placeholders [SQR][PI][Y] for all PC groups added
    Additional Spaces added to text e.g. IF Q1_IF Q2_GOSUB Label, Removed spaces after EXT_Line_NB
    utf8=2asc added, for later serial transfer of text
    IDENT_OLD_DAT and processing added, IDENT_PC121_DAT experimentally, not tested ID
    help screens --help=recording, --help=l implemented
    complex search with blocks for the first sync, tuning of base_freq to freq will be done during this,
    no sync at start of audio data, type of "position" corrected to signed long for negative fseeks
    error counter for minor errors implemented,
    BAS_OLD without checksum after EOF now,
    RSV length for 1500 up to 188 bytes,
    check start bit in nibbles and read all nibbles with first stop bit now,wav2bin_163alpha3
    some errors with combined stop-start-bits will synced now but normally get error 8
    multiply stars inserted between OLD_BAS variable names with --utf8=asc
    Additional Spaces for Basic text of PC-1500
    utf8=2dos added, for transfer to DOS based Software with Code Page 437
    Rounding error for tmpS in FindAmps corrected
    Option cspeed for clock modified Pocket Computers with a SpeedUp
    Tested with old cassettes and base frequency 7111 Hz, modified some parameters for amplitudes detection
2014-06-13	V 1.6.2 beta 5c  Torsten Mücker
    2. method for bit reading implemented with mean time difference between opposite amplitudes for the
       decision, what to do with Bit_MID transitions and what is Bit_1
    FindSyncAndFreq improved, only from higher level without recursion now
    Sync all start bits to Bit_0 and all stop bits to Bit_1
    check if end of byte with more stop bits
    exit line processing if CR found, line length check modified
    End of Data Block count with changed management of long sync
    between bytes shifted nibbles for series 12xx-14xx most time corrected
    implemented limited corrections for transmission errors with combined stop-start-bits
    support for files with more transmission errors implemented, but destination file must corrected by hand
    ERR-Level and -processing corrected
    tests with PC-1500 and some corrections done in previous code
    implement amp detect for PC-1500, changes in ReadBitField and Sync
    --type raw and type --rawdat for debug purposes
    DAT-Files for PC-1500
    RSV-Data for PC-1500
    checksum for filenames and all headers
    Tokens for PC-E500(S) only for compatibility with Bas2img
    Checksum for NEW BIN at end of file, when EOF marks are written before the expected checksum
    Checksum for NEW BASIC at end of line, when EOF marks are written before the expected checksum
    Checksum for PC-1500 BASIC avoid double read when EOF at block end
    Check double EOF marks from Bas2img
    skip one-bit gaps in wav file
    added adapting level difference between max- and min amplitudes
    PC-1211 block distance
    No Rate_amp for PC-1211 Hardware at low level
    pcgrpId based weight of detection methods trans / amps in Readbitfield because of hardware issues
    adjust Trans_High-Low adaptive after the first sync
    adjust Amp Parameter adaptive after the first sync
    Sync(Start)BitFromWav, Parameter for PC-1500
    Finer scale for rate_amp
    some changes in categorisation of pocket computers
    InsertStars improved
2014-10-02	V 1.6.3 beta 12d4 Torsten Mücker
    support for PC-E500 BAS, Password
    support for PC-E500 BIN and DAT
    added old arguments conversion to new arguments for backward compatibility with 3rd-party software
    added device parameter for different filter sets and started to implement different devices
    -d AIR for wav files of PC-1245...1475 made from buzzer with Mic without interface (tricky!)
    -d CAS for wav files from cassette recorder (directly) with minor changes in filter rules
    minor changes in standard parameters, and warnings
    support of input --tap and output -t tap of emulator tap file format (raw bytes, checksum included)
    added support for PC-1500  -t tap
    added minor tokens for old BASIC
    improved processing of end of file and other error conditions
    warnings, if dropout found in debug mode
    changes of PC-G800 series to PC-E500 series implemented
    Len of RSV 126x corrected
    implemented PC-1600 BAS
    changed π (PI) from older SHARP code to Π (uppercase) because of conflict with characters of E-Series
    Ext/E-series TEXT modus, E-Series ASCII (SAVE "CAS:File")
    limited support for "Transfile PC Plus 5.55" (PC-1245-1475) SHC files, SHA Basic files
    PC-1600 BASIC, Image, working: to implement PC-1600 Binary, RSV, Data,
    corrected tap-Format for PC-1500 and double end mark processing and depressed Groups by freq
    PC-1600 DAT, ASC-DAT more formats
    PC-1600 Mode 1 format
    sync improved in cases, where false base frequency was found first
    Pre-amplifying of wav files recorded with low sound level
    improved intermediate sync for PC-16/E/G with low signal
    PC-1211 optimizing data, SHC support, better sync of start bit after long skips
    device=EMU more speed tolerance, don´t forget to analyse frequency in wav files from emulator and
     set cspeed to the quotient between the found peak and the real base frequency
    decide depending from file id, how to process type ASC -> IMG or BAS
2014-11-26	V 1.9.8 beta 08b2 Torsten Mücker
    support of merged program files
    added Entry address PC-1500
    old bin files without EOF mark (YASM) accepted, check length of all binary files,
    DebugEnd EOF_15 changed,
    type used for default file extension, more checks for correct type parameter
    corrected processing of type image, no check for CR in line for newer series
    for PC-1600 not char conversion, PC-1600 no long lines
2015-05-04	V 1.9.9 beta c4a1 Torsten Mücker
    debug traces not longer than print for 256 byte a line, reduced printed warnings
    read tap file also when false --pc parameter given
    find wav data after other sub-chunks
    PC-1421 i,n
    WAVE_FORMAT_EXTENSIBLE supported
    speed up multichannel processing
    minor changes see change files of the release candidates
    Print last BASIC line also after sync errors with the EOF mark
    unknown token of PC-1500 (PC-1600) returnable
    token of some third-party extensions
2015-08-11	V 2.0.9 beta 12b1 Torsten Mücker
    debug switch for tokens of BMC MC-12 implemented
    testing: external keyword files
    More unknown keywords and Japanese chars (reversible)
    type DEF Def Keys, file A3 PC-1500
    type IMB for IMG not line by line
    BAS_15 end if full checksum block
    support for --img -> BAS, with support for SuperTape Binary .ST
    support for PC-1500 Quick-Tape, SuperTape formats
    resolve PC-E500 jump labels, that was modified from run, two steps (1.IMG, 2.BAS) needed
2015-12-13	V 2.0.9 beta 14c2 Torsten Mücker
    PC-1234
    --device=BIN
    -x (exit after header), write infos to --parameters file (-m)
    parameters file more infos: type, typew
    alternative exit code with --exit=type, =ident
    warn linenb for PC-1600 with CE-150, automatic switch to PC-1600
    more parameter to CFG file: errors, warnings
2016-01-24	V 2.0.9 beta 15a Torsten Mücker
    preparation for file caching
2016-02-28	V 2.0.9 RC1 for V 2.1 Torsten Mücker
2019-03-08	V 2.1.0 TS Torsten Mücker
    improved debug option 0x200000 to append additional end marks
2019-03-10	V 2.0.9 RC2 for V 2.1.0 Torsten Mücker
    Bug fixed in SyncStartBitFromEWav and improved routine for start bit synchronization of the series G/E/1600/1500QT
2019-03-27	V 2.0.9 c2b1 Torsten Mücker
    added parameter --endmark
    improved messages and hints
2019-04-07	V 2.0.9 c2b2 Torsten Mücker
    Img(st)2bas for PC-1500 error corrected
2019-04-10	V 2.0.9 c2b2a1 Torsten Mücker
    improved messages for end of data sync, img variants st, shc
2019-04-16	V 2.0.9 c2b3a Torsten Mücker
    Variants of BASIC line number separators (spaces, colons, colons + spaces)
2019-05-08	V 2.0.9 c2b3b remove compiler warnings
2019-06-21	V 2.0.9 c2b3c PC-1460 token COLOR, CSIZE
2019-07-04	V 2.0.9 c2b3e(d3) Series 1260-1475, E200/G801-G850 models with japan mode
    support for Katakana chars and limited Kanji with --utf8=yes
    --utf8=esc for conversion scripts with escape chars
2019-07-23	V 2.0.9 c2b4(2c), improved EOF handling for --img, with included endmark,
    PC-1600 --img 2bas,
    Katakana for PC-1500,
    --codepoints file, for own character definitions
    No additional spaces before special chars
    --utf8=BOM
2019-08-14	V 2.0.9 c2b5 (3c), E437 tables, ConvertByteToBAS, E500 chars in REMlines
    token table minor changes, G850 Fkt. FIX
    2- -w for level of spaces inside of line
    Extended BAS direct detokenization
    -spaces inside " : ", -w EOL r, n
2019-08-26	V 2.0.9 c2b5 (5)
    PC-1500 -dCAS# (Trans_Weak_Exp parameter), Amp_Diff_Mid, Rate_Amp_4_Cas, -dCS
    PC-1234 -dCAS#  Amp_Diff_Min_Cas, Amp_Diff_Mid
2019-08-31	V 2.0.9 c2b6 (1a) E500 :ELSE,
            last byte wavtime, path length, long debug traces for OLD
2019-09-03	V 2.0.9 c2b6 (2) EXT/E/G/15/16 bytes before Eol, debug CR_DEF_EOL
2019-10-06	V 2.0.9 c2b7 (0) text line cnt, -l0xC00000 CnvCmdLor, -w!
2019-11-25(02)	V 2.0.9 c2b7 (1a) -l0x3000000 DEL_REMC | DEL_APST, type c, asm6, asm, asm5, CE-158 DelSpcAfterRem
2019-12-04	V 2.0.9 c2c (1b1) type defined bin && found img -> imB, COPY/SAVE CAS E_IMG
2020-01-26	V 2.0.9 c2c (2a) type BIN corrected PC-1500, CFG addr=0, tested with J. Bohs
2020-04-01  V c2c (3)
2020-10-18  V 2.0.9 c2c (4a) PC-1100 New GRP, Memos data (telephone, scheduler, notes, RAM card), G850VS PIOPUT
2020-10-26  V 2.0.9 c2c (4b1) PC-1445 CASL, Img and Asm-Source
2020-11-03  V 2.0.9 c2c (4b2) PC-1150/40, 124x-DB, MEM-Format binary only
2020-11-08  V 2.0.9 c2c (4b3) CAP-X ident
2020-11-11          c2c (4b4) compatibility and warnings
2020-12-30          c2d = c2c(4b4a)  compiler warnings
2021-01-06  V 2.0.9 c2d (1)  E500 fixed numbers -E with Android compiler, warnings
2021-03-02  V 2.0.9 c2d (2)  1416G INP, OUT
2021-03-08  V 2.1.1 b1a start time parameter for processing of a wav file
2021-03-11(30)2.1.1 b2a(1) start time parameter automatic detection from wav file
2021-04-23  V 2.1.1 c1 (1) messages
2021-05-05  V 2.1.1 c1 (2) PC1500QT1 position of checksum blocks corrected, comment out entryadr=0
2021-05-11  V 2.1.1 c1(2b1) imb warn -> img, 2. parameter -s Debug Time for low level debugging,
                           Low Level and Bit Debug Traces
2021-05-17  V 2.1.1 c1b2 SyncBitFromWav: more precise calculation of the begin of each start bit of the PC-1100-1500
                         More levels for auto --start
2021-06-28  V 2.1.1 c1c(3)a --khx read from khx file instead of tap (or wav) file, Japanese characters of new series,
                            ParamsCnt
2021-07-16  V 2.1.1 c1c(3)a2 QLOAD, QSAVE, BYE symmetry to Bas2img, models "J", "Jap"
2021-07-20  V 2.1.1 c1c(4) Khx for unsupported (PC-1500 formated), newest groups without spaces
2021-08-11  V 2.1.1 c1d beta(2) Kanji support for PC-1360K, 1600K, minimal for 1500D, with codepoint file only
2021-08-30  V 2.1.1 c1d beta(3c) 1246DB Katakana, MEM 2 kB, beta(4) E500J, E500K - 2. character area
2021-09-27  V 2.1.1 c1d
2022-10-14 	V 2.1.1 c1d (1) PC-1401 V.1 less stop bits, PC-150x more
2022-10-19 	V 2.1.1 c1d (1a) PC-1401V2 and derivative models, write full pc name to params, error messages at the end and of Convert
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>		/* Command line parser getopt(). */
#include <ctype.h>

#define PDATE           "October 2022"
#define PVERSION        "2.1.1 c1d (2)"
                        /* delete "//" in next line to activate debug modus by default */
// #define DEBUG           1   /* should be commented for final releases */
#ifdef DEBUG
   #define DEBUG_ARG    "0xC0"  /* Set -l default for more output */
#else
   #define DEBUG_ARG    "0"
#endif // DEBUG
#define DEBUG_TIME_ARG  "10000.0" /* [s] default start of debugging for sample value processing */
#define DEBUG_TIME_LEN  0.012 /* Time frame [s] after start for low level sample debugging */
#define DEBUG_TIME_L15  0.020 /* Time frame [s] after start for low level sample debugging PC-1500 */
#define DEBUG_TIME_L1   0.200 /* Additional time frame [s] before/after for Trans/Amp debug */
#define DEBUG_TIME_L4   0.500 /* Additional time frame [s] before/after for Bits debug */

#define STAT_SYNC      -22  /* Switch between skipping and syncing fore some intermediate syncs */
#define STAT_EOT       -12  /* Expected possible end of Pocket Computer Transmission */
#define STAT_FMT        -7  /* Manual check of format conversion needed */
#define STAT_OK          0  /* Normal data transmission */

/* Regular Errors such as EOF and recoverable such as End of sync *MUST* have a lower value then ERR_OK */
#define ERR_GLIT       -21  /* Glitch detected in the wav */
#define ERR_DROP       -20  /* Dropout detected in the wav */

#define ERR_NSYNC      -9   /* new long sync or low freq detected */
#define ERR_EOT        -2   /* End of Pocket Computer Transmission */
#define ERR_EOF        -1   /* Normal EOF, End of audio data, */
#define ERR_NOK        -1   /* old definition minor error unspecified */

#define ERR_OK          0   /* no error, nothing to do */

/* Unexpected NOT recoverable error *MUST* have a higher value then ERR_OK */
#define ERR_SYNT        1   /* arguments missing, syntax error or nothing to do */
#define ERR_ORD         2   /* misplaced order, nibbles in bytes or other */
#define ERR_ARG         3   /* arguments problem, pocket not implemented */
#define ERR_LINE        4   /* error with line numbers */
#define ERR_FILE        5   /* File I-O */
#define ERR_MEM         6   /* Line to long, buffer overflow */
#define ERR_FMT         7   /* False wav format or SHARP file header */
#define ERR_SUM         8   /* Checksum read different from calculated */
#define ERR_SYNC        9   /* No Sync found*/
#define ERR_MULTI       10  /* multiple errors, exit code + last error */

#define ERR_CNT_MAX     768  /* exit, if this or more (minor) errors */

#define EXIT_NO         0   /* do not --exit after header */
#define EXIT_ERR        1   /* -x --exit returns error level (default) */
#define EXIT_TYPE       2   /* --exit returns type value - see TYPE definitions */
#define EXIT_IDENT      3   /* --exit returns pocket file or artificial identity value, see the manual */
#define EXIT_PCGRPID    4   /* --exit returns internal used pcgrpId */

#define DEBUG_TRACES  0xFFF     /* All debug traces */
#define CR_DEF_EOL    0x200     /* CR has a higher priority than the line length (in case of error) */
#define IGN_ERR_SUM   0x800     /* option flag to ignore false checksums */
#define BASE_FRQ_FIX  0x1000    /* option flag not to tune the base frequency, use fixed base frequencies*/
#define TRANS_OLD     0x2000    /* option flag to use old TRANS level definitions, no amplitude detect, no gain */
#define NO_RATE_AMP   0x4000    /* option flag for amplitudes detect and count only, no gain */
#define NO_PRE_AMP    0x8000    /* option flag for don't analyse wav file, no Pre-Amplification */
#define WRT_NUL_DATA  0x40000   /* option flag for writing zero data at end of file */
#define BMC_TOKEN     0x80000   /* option flag if commands of BMC MC-12 (A) are used */
#define BAS_EOF_INCL  0x200000  /* option flag for: append an End Mark (0xFF or 0x1A) see -e */
#define DEL_REMC      0x1000000 /* Delete a comment character at the beginning of each line*/
#define DEL_APST      0x2000000 /* Delete an apostrophe at the beginning of each line*/

#define UTF8_SET        239     /* Identify Katakana UTF8-Chars, first Byte (Uchar), see InsertSpaceNeeded */
#define UTF8_KATAKANA1  189     /* half width Katakana letter, 2. utf-8 byte */
#define UTF8_KATAKANA2  190     /* half width Katakana letter, 2. utf-8 byte */
                                /* utf8= 0 and 1 reserved for no, yes */
#define UTF8_ASC        2       /* for later serial transfer or from OLD_BAS to newer PC Groups */
#define UTF8_DOS        3       /* for transfer to DOS-based Software with DOS-US graphics charset */
#define UTF8_ESC        4       /* for conversion scripts, that use escape sequences to mask special chars */
#define UTF8_ESCX       5       /* for conversion scripts, that use escape sequences to mask special chars and 8-bit chars */
#define UTF8_BOM        8       /* yes and write a BOM at the begin of utf-8 text */

#define SPC_LSTD        5       /* Default Level for insert spaces before command, spc_level of 2. -w parameter */
#define SPC_LMAX        8       /* Max. Level for insert spaces before command */
#define LNFRM_SCOLS     4       /* lineformat ' : ' */

#define TYPE_NOK        0
#define TYPE_BIN        1       /* subtype of TYPE_IMG */
#define TYPE_IMG        2       /* Write a image of Binary code, Basic intermediate code, Text modus, ASCII or data */
#define TYPE_DAT        4       /* subtype of TYPE_IMG */
#define TYPE_RSV        5       /* Write a image of ReSerVable memory (for keys) */
#define TYPE_ASC        6       /* For PC-E/G/1600 ASCII Data */
#define TYPE_BAS        7       /* Translate Basic intermediate code to lines of Basic source code */
#define TYPE_TXT        8       /* subtype of TYPE_IMG */
#define TYPE_DEF        9       /* Write a binary image for definable keys, PC-1500 software */
#define TYPE_DIM       10       /* subtype of TYPE_IMG */
#define TYPE_MEM       11       /* Tables of PC-1140 - PC-1248DB, subtype of TYPE_IMG */
#define TYPE_CRD       0x6A     /* PC-1100 full RAM card, subtype of TYPE_IMG */
#define TYPE_TEL       0x61     /* Telephone database export */
#define TYPE_SCD       0x62     /* Scheduler database export  */
#define TYPE_NOT       0x64     /* Notes database export */
#define TYPE_CSL       0x7A     /* NEW_CASL or CAP-X, parameter for bin2wav, PC-144x (PC-1416/7G) */

#define TYPE_RAW       11       /* Raw data with checksums and name, also for emulator TAP format */

#define DEV_PC          0       /* digitalization directly from Pocket Computer interface*/
#define DEV_CAS         1       /* digitalization directly from cassette recorder */
#define DEV_AIR         2       /* digitalization with microphone from buzzer over air */
#define DEV_EMU         3       /* digitalization from emulator sound */
#define DEV_BIN         4       /* synthetic wav, e.g. from Bin2wav or a digital interface */

                                /* Group IDENT_PC1211 for PC-1210 ... 1212 */
#define GRP_OLD         0x20    /* most inside PC-1245 ... 1255 */
#define GRP_NEW         0x70    /* most of PC-1260 ... 1460 */
#define GRP_EXT         0x72    /* PC-1360, PC-1475, PC-1280 */
#define GRP_16          0x10    /* PC-1600 */
#define GRP_E           0x05    /* PC-E500 series */
#define GRP_G           0x08    /* PC-G850, E200 series */
                                /* Group IDENT_PC1500 for PC-1500 */
#define IDENT_UNKNOWN   0x100
#define IDENT_NAMEPAS   0x12F    /* for name reading only */

                                /* Real Tape header identity of SHARP file */
#define IDENT_OLD_BAS   0x20    /* PC-1245 ... PC-1255 */
#define IDENT_OLD_PAS   0x21
#define IDENT_OLD_DAT   0x24
#define IDENT_OLD_BIN   0x26
#define IDENT_QT_BAS    0x42    // B
#define IDENT_QT_BIN    0x4D    // M
#define IDENT_QT_RSV    0x52    // R
#define IDENT_QT_DIM    0x44    // D = V DIM
#define IDENT_QT_DAT    0x56    // V
#define IDENT_QTAPE     0x0AA0
#define IDENT_NEW_TEL   0x61    // MEMO  TEL
#define IDENT_NEW_SCD   0x62    // MEMO  SCDL
#define IDENT_NEW_NOT   0x64    // MEMO  NOTE
#define IDENT_NEW_CRD   0x6A    // BASIC RAM Card OUT
#define IDENT_OLD_MEM2  0x6D    // MEM 1246DB, old, all DB Tables
#define IDENT_OLD_MEM   0x6E    // MEM 1150, old, all DB Tables
#define IDENT_NEW_BAS   0x70
#define IDENT_NEW_PAS   0x71
#define IDENT_EXT_BAS   0x72    /* PC-1360, 1475, 1280 */
#define IDENT_EXT_PAS   0x73
#define IDENT_NEW_DAT   0x74
#define IDENT_NEW_BIN   0x76
#define IDENT_NEW_CSL   0x7A    // CASL or CAP-X CMT
#define IDENT_PC1211    0x80    /* also GRP Id */
#define IDENT_PC121_DAT 0x8F    /* one variable length block only */
#define IDENT_PC1500    0x0A    /* also GRP Id */
#define IDENT_PC15_BIN  0xA0
#define IDENT_PC15_BAS  0xA1
#define IDENT_PC15_RSV  0xA2
#define IDENT_PC15_DEF  0xA3
#define IDENT_PC15_DAT  0xA4
#define IDENT_PC15QTBAS 0xA5
#define IDENT_PC15QTBIN 0xA6
#define IDENT_PC15_IMG  0x1A1   /* Read PC-1500 IMG binary, not line by line */

#define IDENT_RAW       0x1FF
#define IDENT_PC16_BAS  0x101   /* Mode 1 ID is IDENT_E_BAS, real Mode 2 ID is 01 */
#define IDENT_PC16_RSV  0x102   /* Mode 1 ID is IDENT_E_BAS, real Mode 2 ID is 02 */
#define IDENT_PC16_IMG  0x110   /* Mode 1 ID is IDENT_PC16_CAS */
#define IDENT_E_IMG     0x104   /* Mode 1 ID is IDENT_E_ASC */

#define IDENT_PC16_CAS  0x00    /* PC-1600 ASCII Data or BASIC Image */
#define IDENT_PC16_DAT  0x08    /* Special binary data format PC-1600 */
#define IDENT_E_ASC     0x04    /* ASCII, CAS: Data or BASIC */
#define IDENT_E_BAS     0x02    /* E- and G series */
#define IDENT_E_BIN     0x01

#define BAS_NEW_CODE    0xEF    /* PC-1403...PC-1460, for tokens of length 2 */
#define BAS_EXT_CODE    0xFE    /* Extended BASIC and newer Series 2-Byte token only */
#define BAS_EXT_LINE_NB 0x1F    /* Extended fixed line numbers are binary coded, also PC-1600 and all newer series */
#define BAS_E_JMP       0x1E    /* E500 and newer relative jumps after IF, ELSE, REM assist the interpreter */
#define BAS_E_NB        0x1D    /* E500 fixed numbers binary coded */
#define BAS_E_LBL       0x1C    /* E500 labeled jumps with */

#define KANJI_CODE_MIN  0x81    /* Lowest table code */
#define KANJI_CODE_MAX  0x98    /* Highest table code PC-1360K, 1600K */
#define KANJI_CODE_MAXE 0x9F    /* Highest table code PC-E500K and other software drivers */
#define KANJI_CODE_MIN2 0xE0    /* Lowest first table code 2nd table space, software drivers */
#define KANJI_CODE_MAX2 0xEF    /* Highest first table code 2nd table space, software drivers */

#define MERGE_MARK      99999   /* Number with empty line for mark of merged programs */

#define EOF_ASC         0x1A    /* End of ASCII transfered files, also device CAS: of newer series */
#define EOF_15          0x55    /* End of complete file of PC-1500 */
#define BAS_1500_EOF    0xFF    /* one of two bytes */
#define BAS_NEW_EOFFF   0xFFFF  /* both two bytes */
#define BAS_NEW_EOF     0xFF    /* one of two bytes */
#define BAS_OLD_EOF     0xF0    /* one byte only */
#define DATA_EOF        0x0F    /* End of old/new data block with variable length */

#define DATA_STD_LEN    8       /* length of a standard data variable element*/
#define DATA_HEAD_LEN   5       /* length of the header of a data variable element*/
#define DATA_VARIABLE   0xFE00  /* No length of Data block, standard data variable with variable length follows: old/new/ext */

#define BLK_OLD_SUM     8       /* Transmission Block (plus checksums), old series bas without, data old/new with checksum reset */
#define BLK_OLD         80      /* Transmission Block (plus checksums) of PC-1500 and old series with checksum reset */
#define BLK_NEW         120     /* Transmission Block (plus checksum) of new series 1260-1475 */
#define BLK_E_DAT       256     /* Checksum of series E500 and newer Ascii Data or Sources */
#define BLK_E_HEAD      0x30    /* Length of header1 of newer series, next IMG/BIN only after the end of a Transmission Block   */
#define FILE_HEAD_E_LEN 52      /* Length of file header of E series in the pocket computer, usual starts with FB, ends with 0D */
#define BLK_QT1         0x100   /* Length of Block QT1 */

#define UNREAD          0x100   /* byte or nibble was not read from source completely */

#define SYNC_E_HEAD     40      /* additional sync for E-series header block */
#define SYNC_E_DATA     20      /* additional sync for E-series data block */

#define SUPT_HEAD_L     26      /* SuperTape BINARY (*.ST) length of header block with low byte of checksum included */
#define SHC_HEAD_L       9      /* Transfile PC (*.SHC) length of header variant without password, (no checksums) */

#define BIT_0           8       /* transitions per bitLen L */
#define BIT_1           16      /* transitions per bitLen H */

#define BIT_0_Q         2       /* transitions per bitLen L */
#define BIT_1_Q         4       /* transitions per bitLen H */

#define BITL_Q          2       /* number of waves per bitLen for PC-1500 QTape variants */
#define BITL_E1         5/2     /* Factor BitLen E-Series for BIT_1/BIT_0 */

#define FSYNC_NB_TRY    5       /* try restart of FindFreq&Sync and FindSync if sync or ReadSaveID broken */
#define SYNC_NB_TRY     1280    /* try reads a bit sequence and count trans >= Bit_1 */
#define SYNC_NB_CNT     16      /* sequence block of bits with trans>=Bit_1 +- 1 to test for first sync */
#define SYNC_FRAC_1     3/4     /* fraction of bits in block with trans>=Bit_1 for start of first sync, no brackets! */
#define BIT_LEN_RTOL    1/32    /* 3% relative tolerance of samples before calculating new frequency, no brackets! */
#define SYNC_TIME_MIN   260     /* [msec] how long Sync-Bit_1 read after FindSync before accepting sync */

#define SYNC_BIT_MAX    0x7FFF  /* how many Sync-Bit_1 read in mode FindSync before new sync */
#define STOP_BIT_MAX    250     /* how many Stop-Bit_1 read in mode ReadBitField before new sync, normal 11 enough,  */
                                /* but End of old variable data follows with 101 bit, PC-15_DAT ~80 0,25s distance */
#define STOP_BIT_M11    2000    /* PC-121x 1808-5 = 1803 distance */

#define SYNC_TR_TOL     3       /* how many trans less Bit_1 or above BIT_0 are accepted, multi-pass */
#define CNT_ERR_ORD     0       /* try to shift the nibbles between bytes after (CNT_ERR_ORD+2) missing stop bits*/

#define ORDER_STD       0       /* nibbles in a byte swapped */
#define ORDER_INV       1       /* nibbles in a byte no swapped or two-times swapped, PC-1500 or DATA */
#define ORDER_E         9       /* no nibbles, a byte with one start bit, newer method 16/G/E */
#define ORDER_Q         11      /* no nibbles, a byte with one start + 2 stop bits, Quick/Fast method */

#define BASE_FREQ1      4000    /* Sync, stop bits or high bit for PC-12xx, 13xx, 14xx, default, no speedup */
#define BASE_FREQ2      2500    /* PC-1500 */
#define BASE_FREQ3      3000    /* E-Series 3000/1200, G850 + PC-1600: 3056/1222 */
#define BASE_FREQ4      5000    /* Quick-Tape */
#define BASE_FREQ5      1250    /* SuperTape lead in, unsupported */

#define cLL_IMG         79		/* Constant value for max. length of BASIC IMAGE lines,
                                   PC-E500 series lower 255 */
#define cLL             1024	/* Constant value for max. length of BASIC TEXT lines, 256 to small */
#define cLPF            260		/* Constant value for max. length of PathFilenames and other arguments */
#define cLC             255		/* Constant value for max. length of minor texts or commands */
#define cLNB            30		/* Constant value for max. buffer length for a line number or E500 numeric values */

#define cLTK            16		/* Constant value for max. length of a token + 1 */
#define cMAXNBTK        2048    /* Maximum number of external defined token keywords*/
#define cLCH            10		/* Constant value for max. length of a encoded character utf8 or [hh][hh] + 1 */
#define cMAXNBCH        7000    /* Maximum number of external defined code points (code space entries) with Kanji */

#define FRQ_AMPS        3       /* Minimal frequency factor relative to base_freq for new processing of wav,
                                   lower absolute values only, >= absolute values + differential component */
#define AMP_WEIGHT_HIGH 66      /* Weight of amplitudes detection inside the Bit 0/1 detection, most of PC-1234 */
#define AMP_WEIGHT_LOW  33      /* Transitions are higher weighted than amplitudes for Bit 0/1 detection, PC-1500 */

#define RATE_AMP_OFF   -1       /* Old method, no amplitudes detection */
#define RATE_SCALE      16      /* Divisor of amplification factor for differential component */
#define RATE_AMP_4      26      /* /16 Amplification factor for differential component based on last amplitude
                                   Higher about 3*16 may make from double peeks two amplitudes! */
#define RATE_AMP_4_CAS  40      /* /16 recorded signal from cassette recorder, default -dCAS */
#define RATE_AMP_4_AIR  6       /* /16 recorded signal from air with refections and noise */
#define RATE_AMP_4_MIN  14      /* /16 Low level recorded signals tends to false amps */
#define RATE_AMP_4_BLW  0x60
#define RATE_AMP_12     0       /* /16 Amplification method does not work for PC-1211 hardware with low signal level */
#define RATE_AMP_12_MAX 12      /* /16 Amplification method for PC-1211 hardware with hight signal level */
#define RATE_AMP_12_ABV 0xB5
#define RATE_AMP_15     0       /* /16 High Amplification method does not work for PC-1500 low frequency signal form */
#define RATE_AMP_15_MAX 1       /* /16 Amplification method for PC-1500 hardware with high signal level */
#define RATE_AMP_15_ABV 0xB5
#define RATE_AMP_Q_CAS  10      /* /16 QTape 1500 series recorded signal from CAS-recorder, better trans, problems with len. */
#define RATE_AMP_E      0       /* /16 No amplification for 16/G/E series when direct recorded */
#define RATE_AMP_E_CAS  20      /* /16 E/G/16 series recorded signal from CAS-recorder, better trans, see len. */

#define AMP_DPOS_MAXB   7       /* expected maximal time distance for amplitudes relative to this of base frequency */
                                /* 4:= 1x amp Bit_0 = lost */
#define AMP_DIFF_REL    4       /* No amplitude if the difference to opposite amplitude is not higher relative to the last
                                   difference (MAX-MIN)/AMP_DIFF_REL, depress false amps, lower 3 not work after high peek errors*/
#define AMP_DIFF_MID    8       /* No amplitude if the difference to opposite amplitude is not higher relative to the
                                   main difference (MAX-MIN)/AMP_DIFF_MID of all data read, depress false amps */
#define AMP_DIFF_MID_CAS 12     /* PC-1234, MID, for device CAS because of lower 4 kHz in the level */
#define AMP_DIFF_MID_121 4      /* PC-1211 has more equal level but tends to greater signal errors */
#define AMP_DIFF_MID_15  4      /* PC-1500, also used for adaption of AMP_MIN/MAX and TRANS_H/L to main level */
#define AMP_DIFF_CAS_15  8      /* PC-1500, MID, for device CAS because of larger fluctuations in the level */

#define AMP_DIFF_MIN    10      /* No amplitude if the difference to opposite amplitude is absolute not higher, defend double amps */
#define AMP_MAX_ABOVE   0x19    /* Detect no maximum at this level and below, to filter between double minimums */
#define AMP_MIN_BELOW   0xE7    /* Detect no minimum from this level and above, to filter double peaks */
#define AMP_MAX_ABV_15  0x93    /* AMP_MAX_ABOVE start value for PC-1500 */
#define AMP_MIN_BLW_15  0x6C    /* AMP_MIN_BELOW start value for PC-1500 */

#define TRANS_MID       0x80    /* Signal processing is done with 8-bit sample values */
#define TRANS_DIFF_AIR  0x28    /* TRANS_HIGH - TRANS_MID for device AIR at start */

#define TRANS_HIGH_15   0x8F    /* TRANS_HIGH from start and at reference level for PC-1500 */
#define TRANS_LOW_15    0x70    /* TRANS_LOW  from start and at reference level for PC-1500 */
#define TRANS_WEAK_EXP  2       /* Default 2-exponent for signal level of main in relation to weakest area (dropout) from -dCAS tape */
#define TRANS_HIGH_121  0x8F    /* TRANS_HIGH for PC-121x at full level */
#define TRANS_LOW_121   0x70    /* TRANS_LOW  for PC-121x at full level */
#define TRANS_HIGH_E    0x82    /* TRANS_HIGH, for PC-E/G/16 silence needs +/-1 one */
#define TRANS_LOW_E     0x7E    /* TRANS_HIGH, for PC-E/G/16 prevent quantisation noise and on silence noise */
#define TRANS_HIGH      0x81    /* Default TRANS_HIGH, shifted to global variable Trans_High */
#define TRANS_LOW       0x7F    /* for PC-1245-75, audio level to prevent quantisation noise only */

#define SYNC_LEV_MIN    5       /* /16 Medium volume required for recognizing the synchronization tone */
#define SYNC_LEV_E      7       /* /16 Medium volume required for the synchronization tone of 16/E/G series */

#define true 1
#define false 0

/*                      used types  */
typedef     int		    bool;
/* NOTE (mr#4#): The data type char should be replaced by this data type wherever errors are caused if uchar is used by a compiler instead. */
/*	some systems use unsigned char for char by default */
typedef signed char     schar;
/*			char;	    */
typedef unsigned char	uchar;
/*			short;	    */
typedef unsigned short	ushort;
/*			int;	    */
typedef unsigned int	uint;
/*			long;	    */
typedef unsigned long	ulong;

 uint   Bit_0 = BIT_0 ;                 /* transitions per bitLen L */
 uint   Bit_1 = BIT_1 ;                 /* transitions per bitLen H */
 uint   Bit_MID   = ((BIT_0 + BIT_1) / 2) ;
 uint   Bit_LOW   = ((BIT_0 / 4) * 2 + 1) ;
 uint   Bit_LOW2  =  (BIT_0 * 3) / 4 ;
 uint   Wav_Nb_Bit1 = BIT_1 / 2 ;       /* full waves of BASE_FREQ per Bit 1 (BIT_1 / 2) */

                                        /* This constants are modified by the --cspeed parameter */
 ulong  Base_FREQ1 = BASE_FREQ1 ;       /* Sync, stop bits or high bit for PC-12xx, 13xx, 14xx */
 ulong  Base_FREQ2 = BASE_FREQ2 ;       /* PC-1500 (Start bit and low bit are half of the following frequency) */
 ulong  Base_FREQ3 = BASE_FREQ3 ;       /* Sync and bit 0 of native PC-1600, PC-E500, -E200, and G-series */
 ulong  Base_FREQ4 = BASE_FREQ4 ;       /* Quick-Tape lead in */
 ulong  Base_FREQ5 = BASE_FREQ5 ;       /* SuperTape lead in, unsupported */

   int  Stop_Bit_Max = STOP_BIT_MAX ;   /* Maximum of stop bits to expect after a bit for intermediate sync */
  uint  Sync_Lev_Min = SYNC_LEV_MIN;    /* Medium volume required for recognizing the synchronization tone */
                                        /* The following values are sample values (8 bit) or differences of them */
   int  Trans_High_def = TRANS_HIGH ;   /* Default level to accept transmission to high state (Schmitt Trigger)*/
   int  Trans_Low_def  = TRANS_LOW  ;   /* Default level to accept transmission to low state (Schmitt Trigger)*/
   int  Trans_High_15 = TRANS_HIGH_15 ; /* Transmission to high state for PC-1500 */
   int  Trans_Low_15  = TRANS_LOW_15  ; /* Transmission to low state for PC-1500 */
  uint  Trans_Weak_Exp= TRANS_WEAK_EXP; /* 2-exponent for -dCAS for signal level of main in relation to weakest area (dropout) from CAS tape */
   int  Trans_High = TRANS_MID +1 ;     /* Adapted level to accept transmission to high state */
   int  Trans_Low  = TRANS_MID -1 ;     /* Adapted level to accept transmission to low state */
   int  Amp_Diff_Rel = AMP_DIFF_REL ;   /* Filter out amplitudes, relative low to the last amplitude before that */
   int  Amp_Diff_Mid = AMP_DIFF_MID ;   /* Filter out amplitudes, relative low to the all counted amplitudes of file */
   int  Amp_Diff_Min = AMP_DIFF_MIN ;   /* Filter out amplitudes, with (too) low(er) absolute differences*/
   int  Amp_Diff_Min_Cas = AMP_DIFF_MIN;/* Filter out amplitudes, absolute to low */
   int  Amp_Max_Above = TRANS_MID;      /* A maximum amplitude has to be above this sample value */
   int  Amp_Min_Below = TRANS_MID;      /* A minimum amplitude has to be below this sample value */
   int  Rate_Amp_Def = RATE_AMP_4 ;     /* Default gain for of the last amplitude based amplification of sample values */
   int  Rate_Amp_Cas = RATE_AMP_4_CAS ; /* Default gain for of the last amplitude based amplification of sample values from Cassette */
   int  Amp_Dpos_Bas = 0 ;              /* Distances of base frequency amplitudes (samples), only for warning used momently */
   int  Amp_Dpos_Max = 0 ;
   int  Amp_Dpos_Min = 0 ;

double  Debug_Time = 10000.00000 ;      /* [s] start of debugging for sample value processing - standard value needed  */
//double  debug_time = 10.00000 ;       /* start time of your debug for sample processing - for low level testing only */
double  Debug_Time_End = 10000.00000 ;  /* [s] end of debugging for sample value processing - standard value needed */
long    Debug_Position = 2000000000 ;   /* Manual debugging based on the position in the wav file, de-comment and insert code */
// long    Debug_Position = 1000000 ;

  char  argP[cLPF] = "" ;
double  speed = 1 ;  /* factor of recording or CPU speed to default speed */
  uint  SHAc = 0 ;   /* Write not to bas, but to Transfile PC plus SHA-format (name included) */
  uint  SHCc = 0 ;   /* Write not to bin, but to Transfile PC plus SHC-format (header included) */
  uint  TAPw = 0 ;   /* Write not to raw, but to Emulator TAP-format (header included) */
  uint  TAPc = 0 ;              /* Input not wav, from emulator tap format (raw byte) or IMG */
  uint  KHXc = 0 ;              /* Input not wav, from DSAVE-30 khx format (raw ascii hex text)*/
  uint  IMBc = 0 ;              /* Write BAS Image not line by line, but as one block*/
  uint  IMGc = 0 ;              /* Input not wav, from image format (without checksums)*/
  uint  Scnt = 0 ;              /* Start processing at given wav time requested */
double  StartTime = 0 ;         /* Time (seconds) in the wav file at which signal processing is to be started */
  uint  Qcnt = 0 ;              /* Quiet, minimal output */
  uint  Xcnt = EXIT_NO ;        /* Exit (value) after header was read */
  uint  Mcnt = 0 ;              /* Write header parameter to a file */
 ulong  linewidth  = 0 ;        /* Line number or leading spaces, 0 = not intended */
  bool  linenbr_del = false;    /* ! delete line numbers, for ASM, C etc.*/
  uint  lineformat = 1 ;        /* Format after line number: 0= no space, 1= 1x space (default), 2= 1x colon, 3=": ", 4=" : "  */
  uint  spc_level  = 0 ;        /* Intensity level used to insert spaces before commands */
//bool  InsSpcBeforeCmd = true; /* Insert unnecessary spaces before commands for better readability */
  bool  DelSpcAfterCmd = false; /* Delete spaces after commands for shorter lines */
  bool  DelSpcAfterRem = false; /* Delete spaces after REM command, for CE-158 */
  bool  type_asm = false ;      /* Image contains assembler source code (subtype), also for CASL */
  uint  CnvCmdLor = 0;          /* convert commands or characters to lower cases */
ushort  devId = DEV_PC;         /* ID number of the device from witch was digitized the wav file */
  uint  pcId = 0 ;              /* ID number of the pocket computer */
 uchar  pcMode = 0 ;            /* for PCs with more (E500) or modified (1600 Mode 1) character code tables,
                                   add 4 for Japanese models (Katakana), 8 for JIS-1 Kanji enabled, 16 for JIS-1-2.area */
 ulong  pcAddr = 0 ;            /* PC-specific address, used for the end of variable data of PCs with DB-tables */
ushort  pcgrpId = IDENT_UNKNOWN;/* Group ID number, categorisation of the pocket computer */
  bool  KeysFromFileOnly=false; /* Use only token from keyword file */

  uint  ll_Img = cLL_IMG ;      /* Constant value for max. length of BASIC IMAGE lines */

const uchar  ELSEid_E2 = 0x76 ; /* PC-G token for ELSE */
const char* REMstr = "REM " ;   /* trailing space needed, is included in the token table */
const uchar  REMidC = '\'' ;    /* PC-1600/G/E only */
static uchar apostrophe = 0x22; /* old series other value */
const char* utf8_BOMstr = "\xEF\xBB\xBF" ;
static char* Eol_r = "\x0D" ;
static char* Eol_n = "\x0A" ;
static char* Eol = "\x0D\x0A" ;

uint key_cnt = 0 ;      /* number of tokens from keyword definition file */
char keyword[cMAXNBTK][cLTK] ;
ushort keyval [cMAXNBTK] ;

uint code_cnt = 0 ;      /* number of changed entries in code space - code points file */
char chrstring[cMAXNBCH][cLCH] ;
ushort codepoint [cMAXNBCH] ;
uint Kanji_Code_Max = KANJI_CODE_MAX ;

typedef struct {        /* variables, that used near global */
    FILE*  ptrFd ;      /* source file pointer */
    ulong  ident ;      /* SHARP file type */
    ulong  id_version ; /* Release or variant of this file type */
    ulong  length ;     /* Length of OUT file (MEMO, RAM card) for PC-11xx */

    ulong  freq ;       /* SHARP detected real audio frequency for syncing bits */
    ulong  base_freq ;  /* SHARP audio default base frequency for sync bits, corrected with --cspeed */

     bool  writing ;    /* status flag, that image processing is not inside header or footer,
                           all bytes that read will be written */
     bool  check_end ;  /* status flag, that checksum processing should consider the possibility,
                           that a End of Transmission mark could follow, EXT/NEW_BAS */
     bool  pause ;      /* status flag, that more stop bits (or a sync) were found and
                           End of Transmission mark could follow, OLD_DAT */
    ulong  total ;      /* Bytes written */
    ulong  count ;      /* Counter of bytes in a block for checksum */
    ulong  sum ;        /* Checksum calculated */
    ulong  sum_before ; /* Checksum calculated before last byte, sometime needed at end of file */
    ulong  block_len ;  /* Block length for checksum, variable used for E-Series */
    ulong  usedat_len ; /* Length of useful data of the next block, for Qtape */

    ulong  wav_freq ;   /* Sample rate of the wav file */
     uint  blockAlign ; /* Length of a sample block in bytes */
     uint  bytesPerP  ; /* Length of a sample point/value in bytes */
    ulong  bgnSamples ; /* First byte of audio data */
    ulong  startSampl ; /* Begin of Processing of audio data */
    ulong  endSamples ; /* Last byte of audio data */
      int  pre_amp ;    /* pre-amplification for wav files with low sound level */

     uint  start_amp ;  /* sign (phase) of the first amp of the start bit + TRANS_MID */
    ulong  bitLen ;     /* Wav sample blocks per SHARP bit all older series */
    ulong  wavLenMin ;  /* Length of a short wave (2 amps) in sample blocks, 1600 and newer series */
    ulong  wavLenMax ;  /* Length of a long wave (2 amps) for 1600 (SHARP bit1) and newer and Qtape bit0 */
    ulong  wavLenMid ;  /* 0ne short amp + one long amp, criterion of detection */
    ulong  byteLen ;    /* Wav sample blocks per SHARP byte */

      int  synching ;   /* Length for long bit sync for reading nibbles and end marks, also status flag */

      int  rate_amp ;   /* rate amplification, gain of the differential component, or no gain or off */
      int  amp_weight;  /* Weight of amplitudes inside the bit 1/0 detection process*/

    ulong  ampd_sum ;   /* Sum of all amplitudes Max-Min, newer series only during sync*/
    ulong  ampd_cnt ;   /* Counter for amplitudes, for mean level calculation */
    ulong  nbStopBMin ; /* Minimum of additional stop bits to expect after a byte */
    ulong  skip_bits ;  /* Number of bits skipped or if a gap then synced last time */
     bool  sync_bit ;   /* status flag, that SyncBit is running, no normal bit reading, no ampd_cnt */

    ulong  type ;       /* Type BAS or IMG (BIN, DAT), RSV, ... */
    ulong  subtype ;    /* Type BAS or IMG, BIN, DAT, RSV, ... parameters file type for Bin2wav */
    ulong  utf8 ;       /* convert special chars from UTF8 not, or transcription, ASC for serial, DOS */

    ulong  debug ;      /* debug level and special options */
      int  status ;     /* status of processing (End...) */
      int  err_exit ;   /* Set exit error */
      int  err_last ;   /* last minor error */
    ulong  err_cnt ;    /* counts minor errors */
    ulong  wrn_cnt ;    /* counts warnings */
     long  position ;   /* Tap/Img position after last byte read */
   double  wavtime ;    /* WavTime after last byte read */

/*   File cache for input from wav
     #define CACHESIZE       0xFF
     int   Cache[CACHESIZE];
     bool  CacheState;  // Cache filled, overwrite (after end of cache start at begin) or space available /
     long  CacheEnd ;   // Position of the highest valid sample value in the cache or -1 /
     long  CachePos ;   // Absolute position of the actual file pointer to the cache /
     Initialise CacheState, CacheEnd, CachePos in Convert */

} FileInfo ;

typedef struct {        /* header of a data variable record */
      uint  length ;
     uchar  dim1 ;
     uchar  dim2 ;
     uchar  itemLen ;
                        /* The type is a part of the variable name only, not transfered with PRINT # */
} TypeInfo ;

static const uchar ApostOld = 0x12 ;

/* NOTE (All#3#): Token tables: whenever you add a token, you should also do this in Bas2img
   in order to restore the symmetry of Bas2img to Wav2bin with regard to BASIC tokens */

/* PC-1251, 1245, 1211 ... */
static char* CodeOld[] = {
    "[00]"  ,"[01]"  ,"[02]"   ,"[03]"   ,"[04]"   ,"[05]"   ,"[06]"    ,"[07]"    ,
    "[08]"  ,"[09]"  ,"[0A]"   ,"[0B]"   ,"[0C]"   ,"[0D]"   ,"[0E]"    ,"[0F]"    ,
    "□"     ," "     ,"\""     ,"?"      ,"!"      ,"#"      ,"%"       ,"¥"       , // 10=InsFrame  □
    "$"     ,"Π"     ,"√"      ,","      ,";"      ,":"      ,"@"       ,"&"       ,
    "[20]"  ,"[21]"  ,"[22]"   ,"[23]"   ,"[24]"   ,"[25]"   ,"[26]"    ,"[27]"    ,
    "[28]"  ,"[29]"  ,"[2A]"   ,"[2B]"   ,"[2C]"   ,"[2D]"   ,"[2E]"    ,"[2F]"    ,
    "("     ,")"     ,">"      ,"<"      ,"="      ,"+"      ,"-"       ,"*"       ,
    "/"     ,"^"     ,"[3A]"   ,"[3B]"   ,"[3C]"   ,"[3D]"   ,"[3E]"    ,"[3F]"    , // grafic
    "0"     ,"1"     ,"2"      ,"3"      ,"4"      ,"5"      ,"6"       ,"7"       ,
    "8"     ,"9"     ,"."      ,"€"      ,"■"      ,"~"      ,"_"       ,"[4F]"    , // 4C=FullFrame ■
    "[50]"  ,"A"     ,"B"      ,"C"      ,"D"      ,"E"      ,"F"       ,"G"       ,
    "H"     ,"I"     ,"J"      ,"K"      ,"L"      ,"M"      ,"N"       ,"O"       ,
    "P"     ,"Q"     ,"R"      ,"S"      ,"T"      ,"U"      ,"V"       ,"W"       ,
    "X"     ,"Y"     ,"Z"      ,"[6B]"   ,"[6C]"   ,"[6D]"   ,"[6E]"    ,"[6F]"    ,
    "[70]"  ,"[71]"  ,"[72]"   ,"[73]"   ,"[74]"   ,"[75]"   ,"[76]"    ,"[77]"    ,
    "[78]"  ,"[79]"  ,"[7A]"   ,"[7B]"   ,"[7C]"   ,"ASC "   ,"VAL "    ,"LEN "    ,
    "[80]"  ," AND " ,">="     ,"<="     ,"<>"     ," OR "   ,"NOT "    ,"SQR "    ,
    "CHR$ " ,"COM$ " ,"INKEY$ ","STR$ "  ,"LEFT$ " ,"RIGHT$ ","MID$ "   ,"[8F]"    ,
    " TO "  ," STEP "," THEN " ,"RANDOM ","[94]"   ,"WAIT "  ,"ERROR "  ,"[97]"    ,
    "[98]"  ,"KEY "  ,"[9A]"   ,"SETCOM ","OPEN "  ,"CLOSE " ,"ROM "    ,"LPRINT " , // [S], [O], [C]
    "SIN "  ,"COS "  ,"TAN "   ,"ASN "   ,"ACS "   ,"ATN "   ,"EXP "    ,"LN "     ,
    "LOG "  ,"INT "  ,"ABS "   ,"SGN "   ,"DEG "   ,"DMS "   ,"RND "    ,"PEEK "   ,
    "RUN "  ,"NEW "  ,"MEM "   ,"LIST "  ,"CONT "  ,"DEBUG " ,"CSAVE "  ,"CLOAD "  ,
    "MERGE ","TRON " ,"TROFF " ,"PASS "  ,"LLIST " ,"PI "    ,"OUTSTAT ","INSTAT " ,
    "GRAD " ,"PRINT ","INPUT " ,"RADIAN ","DEGREE ","CLEAR " ,"[C6]"    ,"[C7]"    ,
    "[C8]"  ,"CALL " ,"DIM "   ,"DATA "  ,"ON "    ,"OFF "   ,"POKE "   ,"READ "   ,
    "IF "   ,"FOR "  ,"LET "   ,"REM "   ,"END "   ,"NEXT "  ,"STOP "   ,"GOTO "   ,
    "GOSUB ","CHAIN ","PAUSE " ,"BEEP "  ,"AREAD " ,"USING " ,"RETURN " ,"RESTORE ",
    "[E0]"  ,"[E1]"  ,"[E2]"   ,"[E3]"   ,"[E4]"   ,"[E5]"   ,"[E6]"    ,"[E7]"    ,
    "[E8]"  ,"[E9]"  ,"[EA]"   ,"[EB]"   ,"[EC]"   ,"[ED]"   ,"[EE]"    ,"[EF]"    ,
    "[F0]"  ,"[F1]"  ,"[F2]"   ,"[F3]"   ,"[F4]"   ,"[F5]"   ,"[F6]"    ,"[F7]"    ,
    "[F8]"  ,"[F9]"  ,"[FA]"   ,"[FB]"   ,"[FC]"   ,"[FD]"   ,"[FE]"    ,"[FF]"    ,
};

/* PC-1246DB, 1248DB */
static char* CodeOldSJ[] = {
    "[00]"  ,"[01]"  ,"[02]"   ,"[03]"   ,"[04]"   ,"[05]"   ,"[06]"    ,"[07]"    ,
    "[08]"  ,"[09]"  ,"[0A]"   ,"[0B]"   ,"[0C]"   ,"[0D]"   ,"[0E]"    ,"[0F]"    ,
    "□"     ," "     ,"\""     ,"?"      ,"!"      ,"#"      ,"%"       ,"¥"       , // 10=InsFrame  □
    "$"     ,"Π"     ,"√"      ,","      ,";"      ,":"      ,"@"       ,"&"       ,
    "[20]"  ,"[21]"  ,"[22]"   ,"[23]"   ,"[24]"   ,"[25]"   ,"[26]"    ,"[27]"    ,
    "[28]"  ,"[29]"  ,"[2A]"   ,"[2B]"   ,"[2C]"   ,"[2D]"   ,"[2E]"    ,"[2F]"    ,
    "("     ,")"     ,">"      ,"<"      ,"="      ,"+"      ,"-"       ,"*"       ,
    "/"     ,"^"     ,"[3A]"   ,"[3B]"   ,"[3C]"   ,"[3D]"   ,"[3E]"    ,"[3F]"    , // grafic
    "0"     ,"1"     ,"2"      ,"3"      ,"4"      ,"5"      ,"6"       ,"7"       ,
    "8"     ,"9"     ,"."      ,"€"      ,"■"      ,"~"      ,"_"       ,"[4F]"    , // 4C=FullFrame ■
    "[50]"  ,"A"     ,"B"      ,"C"      ,"D"      ,"E"      ,"F"       ,"G"       ,
    "H"     ,"I"     ,"J"      ,"K"      ,"L"      ,"M"      ,"N"       ,"O"       ,
    "P"     ,"Q"     ,"R"      ,"S"      ,"T"      ,"U"      ,"V"       ,"W"       ,
    "X"     ,"Y"     ,"Z"      ,"[6B]"   ,"[6C]"   ,"[6D]"   ,"[6E]"    ,"[6F]"    ,
    "[70]"  ,"[71]"  ,"[72]"   ,"[73]"   ,"[74]"   ,"[75]"   ,"[76]"    ,"[77]"    ,
    "[78]"  ,"[79]"  ,"[7A]"   ,"[7B]"   ,"[7C]"   ,"[7D]"   ,"[7E]"    ,"[7F]"    ,
    "[80]"  ,"[81]"  ,">="     ,"<="     ,"<>"     ,"[85]"   ,"[86]"    ,"[87]"    ,
    "[88]"  ,"[89]"  ,"[8A]"   ,"[8B]"   ,"[8C]"   ,"[8D]"   ,"[8E]"    ,"[8F]"    ,
    "[90]"  ,"[91]"  ,"[92]"   ,"[93]"   ,"[94]"   ,"[95]"   ,"[96]"    ,"[97]"    ,
    "[98]"  ,"[99]"  ,"[9A]"   ,"[9B]"   ,"[9C]"   ,"[9D]"   ,"[9E]"    ,"[9F]"    ,
    "[A0]"  ,"[A1]"  ,"[A2]"   ,"[A3]"   ,"[A4]"   ,"[A5]"   ,  "ｦ"     ,    "ｧ"   ,
    "ｨ"   ,    "ｩ"   ,  "ｪ"    ,   "ｫ"   ,  "ｬ"    ,  "ｭ"    ,   "ｮ"    ,    "ｯ"   ,
    "ｰ"   ,    "ｱ"   ,  "ｲ"   ,   "ｳ"   ,   "ｴ"   ,  "ｵ"   ,   "ｶ"     ,    "ｷ"   ,
    "ｸ"   ,    "ｹ"   ,  "ｺ"   ,   "ｻ"   ,   "ｼ"   ,  "ｽ"   ,   "ｾ"     ,    "ｿ"   ,
    "ﾀ"   ,    "ﾁ"   ,  "ﾂ"   ,   "ﾃ"   ,   "ﾄ"    , "ﾅ"   ,   "ﾆ"     ,    "ﾇ"   ,
    "ﾈ"   ,    "ﾉ"   ,  "ﾊ"   ,   "ﾋ"   ,   "ﾌ"    , "ﾍ"   ,   "ﾎ"     ,    "ﾏ"   ,
    "ﾐ"   ,    "ﾑ"   ,  "ﾒ"   ,   "ﾓ"   ,   "ﾔ"    , "ﾕ"   ,   "ﾖ"     ,    "ﾗ"   ,
    "ﾘ"   ,    "ﾙ"   ,  "ﾚ"   ,   "ﾛ"   ,   "ﾜ"    , "ﾝ"   ,   "ﾞ"      ,    "ﾟ"   ,
    "[E0]"  ,"[E1]"  ,"[E2]"   ,"[E3]"   ,"[E4]"   ,"[E5]"   ,"[E6]"    ,"[E7]"    ,
    "[E8]"  ,"[E9]"  ,"[EA]"   ,"[EB]"   ,"[EC]"   ,"[ED]"   ,"[EE]"    ,"[EF]"    ,
    "[F0]"  ,"[F1]"  ,"[F2]"   ,"[F3]"   ,"[F4]"   ,"[F5]"   ,"[F6]"    ,"[F7]"    ,
    "[F8]"  ,"[F9]"  ,"[FA]"   ,"[FB]"   ,"[FC]"   ,"[FD]"   ,"[FE]"    ,"[FF]"    ,
};
/*The following spaces for PI, MEM ... are not needed here, but other software needs them. */
/* PC-1421, optionally for PC-1401/02 */
static char* CodeNew1421[] = {
    "[00]","[01]","[02]","[03]","[04]","[05]","[06]","[07]",
    "[08]","[09]","[0A]","[0B]","[0C]","[0D]","[0E]","[0F]",
    "[10]","[11]","[12]","[13]","[14]","[15]","[16]","[17]",
    "[18]","[19]","[1A]","[1B]","[1C]","[1D]","[1E]","[1F]",
    " ","!"  ,"\"","#","$","%","&"  ,"'"   ,
    "(",")"  ,"*" ,"+",",","-","."  ,"/"   ,
    "0","1"  ,"2" ,"3","4","5","6"  ,"7"   ,
    "8","9"  ,":" ,";","<","=",">"  ,"?"   ,
    "@","A"  ,"B" ,"C","D","E","F"  ,"G"   ,
    "H","I"  ,"J" ,"K","L","M","N"  ,"O"   ,
    "P","Q"  ,"R" ,"S","T","U","V"  ,"W"   ,
    "X","Y"  ,"Z" ,"[","¥","]","^"  ,"_"   , //PC-1403, 1450 and newer have no "¥"
    "`","A"  ,"B" ,"C","D","E","F"  ,"G"   , /*lower only for compatibility with other series */
    "H"," i ","J" ,"K","L","M"," n ","O"   ,
    "P","Q"  ,"R" ,"S","T","U","V"  ,"W"   ,
    "X","Y"  ,"Z" ,"{","|","}","~"  ,"[7F]",
    "[80]"   ,"REC "   ,"POL "   ,"ROT "   ,"DECI "   ,"HEX "   ,"TEN "  ,"RCP "   , // 1401-1. Vers. DEC
    "SQU "   ,"CUR "   ,"HSN "   ,"HCS "   ,"HTN "    ,"AHS "   ,"AHC "  ,"AHT "   ,
    "FACT "  ,"LN "    ,"LOG "   ,"EXP "   ,"SQR "    ,"SIN "   ,"COS "  ,"TAN "   , // 1401-1. Vers. FAC
    "INT "   ,"ABS "   ,"SGN "   ,"DEG "   ,"DMS "    ,"ASN "   ,"ACS "  ,"ATN "   ,
    "RND "   ," AND "  ," OR "   ,"NOT "   ,"ASC "    ,"VAL "   ,"LEN "  ,"PEEK "  ,
    "CHR$ "  ,"STR$ "  ,"MID$ "  ,"LEFT$ " ,"RIGHT$ " ,"INKEY$ ","PI "   ,"MEM "   ,
    "RUN "   ,"NEW "   ,"CONT "  ,"PASS "  ,"LIST "   ,"LLIST " ,"CSAVE ","CLOAD " ,
    "ACC "   ,"ARMT "  ,"COMP "  ,"MDF "   ,"EFF "    ,"APR "   ,"DAYSI ","DAYSII ",
    "RANDOM ","DEGREE ","RADIAN ","GRAD "  ,"BEEP "   ,"WAIT "  ,"GOTO " ,"TRON "  ,
    "TROFF " ,"CLEAR " ,"USING " ,"DIM "   ,"CALL "   ,"POKE "  ,"BGNON ","BGNOFF ",
    " TO "   ," STEP " ," THEN " ,"ON "    ,"IF "     ,"FOR "   ,"LET "  ,"REM "   ,
    "END "   ,"NEXT "  ,"STOP "  ,"READ "  ,"DATA "   ,"PAUSE " ,"PRINT ","INPUT " ,
    "GOSUB " ,"AREAD " ,"LPRINT ","RETURN ","RESTORE ","ERASE " ,"FIN "  ,"[E7]"   ,
    "[E8]"   ,"[E9]"   ,"CST "   ,"SEL "   ,"MAR "    ,"MU "    ,"PV "   ,"FV "    ,
    "PMT "   ,"NPV "   ,"IRR "   ,"PRN "   ,"INTE "   ,"BAL "   ,"SPRN " ,"SINTE " ,
    "NI "    ,"CFI "   ,"[FA]"   ,"Π"      ,"√"       ,"□"      ,"■"     ,"[FF]"   , // FD=[INS] □ , FE=[FUL] ■
};

/* PC-1261, 1350, (1401) ... 1403 ... tokens L=1 */
static char* CodeNew[] = {
    "[00]","[01]","[02]","[03]","[04]","[05]","[06]","[07]",
    "[08]","[09]","[0A]","[0B]","[0C]","[0D]","[0E]","[0F]",
    "[10]","[11]","[12]","[13]","[14]","[15]","[16]","[17]",
    "[18]","[19]","[1A]","[1B]","[1C]","[1D]","[1E]","[1F]",
    " ","!","\"","#","$" ,"%","&","'"   ,
    "(",")","*" ,"+","," ,"-",".","/"   ,
    "0","1","2" ,"3","4" ,"5","6","7"   ,
    "8","9",":" ,";","<" ,"=",">","?"   ,
    "@","A","B" ,"C","D" ,"E","F","G"   ,
    "H","I","J" ,"K","L" ,"M","N","O"   ,
    "P","Q","R" ,"S","T" ,"U","V","W"   ,
    "X","Y","Z" ,"[","\\","]","^","_"   , // PC-1401, 1402, 1421: "\" <-> "¥"
    "`","a","b" ,"c","d" ,"e","f","g"   ,
    "h","i","j" ,"k","l" ,"m","n","o"   ,
    "p","q","r" ,"s","t" ,"u","v","w"   ,
    "x","y","z" ,"{","|" ,"}","~","[7F]",
    "MDF "   ,"REC "   ,"POL "   ,"ROT "   ,"DECI "   ,"HEX "   ,"TEN "    ,"RCP "    , // 1401-1. Vers. DEC
    "SQU "   ,"CUR "   ,"HSN "   ,"HCS "   ,"HTN "    ,"AHS "   ,"AHC "    ,"AHT "    ,
    "FACT "  ,"LN "    ,"LOG "   ,"EXP "   ,"SQR "    ,"SIN "   ,"COS "    ,"TAN "    , // 1401-1. Vers. FAC
    "INT "   ,"ABS "   ,"SGN "   ,"DEG "   ,"DMS "    ,"ASN "   ,"ACS "    ,"ATN "    ,
    "RND "   ," AND "  ," OR "   ,"NOT "   ,"ASC "    ,"VAL "   ,"LEN "    ,"PEEK "   ,
    "CHR$ "  ,"STR$ "  ,"MID$ "  ,"LEFT$ " ,"RIGHT$ " ,"INKEY$ ","PI "     ,"MEM "    ,
    "RUN "   ,"NEW "   ,"CONT "  ,"PASS "  ,"LIST "   ,"LLIST " ,"CSAVE "  ,"CLOAD "  ,
    "MERGE " ,"EQU# "  ,"MEM# "  ,"OPEN "  ,"CLOSE "  ,"SAVE "  ,"LOAD "   ,"CONSOLE ",
    "RANDOM ","DEGREE ","RADIAN ","GRAD "  ,"BEEP "   ,"WAIT "  ,"GOTO "   ,"TRON "   ,
    "TROFF " ,"CLEAR " ,"USING " ,"DIM "   ,"CALL "   ,"POKE "  ,"CLS "    ,"CURSOR " ,
    " TO "   ," STEP " ," THEN " ,"ON "    ,"IF "     ,"FOR "   ,"LET "    ,"REM "    ,
    "END "   ,"NEXT "  ,"STOP "  ,"READ "  ,"DATA "   ,"PAUSE " ,"PRINT "  ,"INPUT "  ,
    "GOSUB " ,"AREAD " ,"LPRINT ","RETURN ","RESTORE ","CHAIN " ,"GCURSOR ","GPRINT " ,
    "LINE "  ,"POINT " ,"PSET "  ,"PRESET ","BASIC "  ,"TEXT "  ,"OPEN$ "  ,"[EF]"    ,
    "[F0]"   ,"年"     ,"月"     ,"日"     ,"円"      ,"♠"      ,"♥"       ,"♦"       , /* F1-F4 Jap. date/yen, F5-F8 card symbols */
    "♣"      ,"■"      ,"□"      ,"Π"      ,"√"       ,"□"      ,"■"       ,"[FF]"    , /* FD, FE for compatibility with 1401 */
};

/* New BASIC for Strings, no token allowed */
static char* CodeNewS[] = {
    "[00]","[01]","[02]","[03]","[04]","[05]","[06]","[07]",
    "[08]","[09]","[0A]","[0B]","[0C]","[0D]","[0E]","[0F]",
    "[10]","[11]","[12]","[13]","[14]","[15]","[16]","[17]",
    "[18]","[19]","[1A]","[1B]","[1C]","[1D]","[1E]","[1F]",
    " ","!","\"","#","$" ,"%","&","'"   ,
    "(",")","*" ,"+","," ,"-",".","/"   ,
    "0","1","2" ,"3","4" ,"5","6","7"   ,
    "8","9",":" ,";","<" ,"=",">","?"   ,
    "@","A","B" ,"C","D" ,"E","F","G"   ,
    "H","I","J" ,"K","L" ,"M","N","O"   ,
    "P","Q","R" ,"S","T" ,"U","V","W"   ,
    "X","Y","Z" ,"[","\\","]","^","_"   , // PC-1401, 1402, 1421: "\" <-> "¥"
    "`","a","b" ,"c","d" ,"e","f","g"   ,
    "h","i","j" ,"k","l" ,"m","n","o"   ,
    "p","q","r" ,"s","t" ,"u","v","w"   ,
    "x","y","z" ,"{","|" ,"}","~","[7F]",
    "[80]","[81]","[82]","[83]","[84]","[85]","[86]","[87]",
    "[88]","[89]","[8A]","[8B]","[8C]","[8D]","[8E]","[8F]",
    "[90]","[91]","[92]","[93]","[94]","[95]","[96]","[97]",
    "[98]","[99]","[9A]","[9B]","[9C]","[9D]","[9E]","[9F]",
    "[A0]","[A1]","[A2]","[A3]","[A4]","[A5]","[A6]","[A7]",
    "[A8]","[A9]","[AA]","[AB]","[AC]","[AD]","[AE]","[AF]",
    "[B0]","[B1]","[B2]","[B3]","[B4]","[B5]","[B6]","[B7]",
    "[B8]","[B9]","[BA]","[BB]","[BC]","[BD]","[BE]","[BF]",
    "[C0]","[C1]","[C2]","[C3]","[C4]","[C5]","[C6]","[C7]",
    "[C8]","[C9]","[CA]","[CB]","[CC]","[CD]","[CE]","[CF]",
    "[D0]","[D1]","[D2]","[D3]","[D4]","[D5]","[D6]","[D7]",
    "[D8]","[D9]","[DA]","[DB]","[DC]","[DD]","[DE]","[DF]",
    "[E0]","[E1]","[E2]","[E3]","[E4]","[E5]","[E6]","[E7]",
    "[E8]","[E9]","[EA]","[EB]","[EC]","[ED]","[EE]","[EF]",
    "[F0]", "年", "月" , "日"  ,"円"  , "♠"  , " ♥"  , "♦" , /* F1-F4 Jap. date/yen, F5-F8 card symbols */
    "♣"   , "■" , "□"  , "Π"   ,"√"   , "□"  , "■" , "[FF]", /* FD, FE for compatibility with 1401 */
};

/* Japanese chars place holder New BASIC for Strings and REM lines, Japanese variants of PC-1350, 1450 and newer */
static char* CodeNewJ[] = {
    "[FE][00]","[FE][01]","[FE][02]","[FE][03]","[FE][04]","[FE][05]","[FE][06]","[FE][07]",
    "[FE][08]","[FE][09]","[FE][0A]","[FE][0B]","[FE][0C]","[FE][0D]","[FE][0E]","[FE][0F]",
    "[FE][10]","[FE][11]","[FE][12]","[FE][13]","[FE][14]","[FE][15]","[FE][16]","[FE][17]",
    "[FE][18]","[FE][19]","[FE][1A]","[FE][1B]","[FE][1C]","[FE][1D]","[FE][1E]","[FE][1F]",
    "[FE][20]","[FE][21]","[FE][22]","[FE][23]","[FE][24]","[FE][25]","[FE][26]","[FE][27]",
    "[FE][28]","[FE][29]","[FE][2A]","[FE][2B]","[FE][2C]","[FE][2D]","[FE][2E]","[FE][2F]",
    "[FE][30]","[FE][31]","[FE][32]","[FE][33]","[FE][34]","[FE][35]","[FE][36]","[FE][37]",
    "[FE][38]","[FE][39]","[FE][3A]","[FE][3B]","[FE][3C]","[FE][3D]","[FE][3E]","[FE][3F]",
    "[FE][40]","[FE][41]","[FE][42]","[FE][43]","[FE][44]","[FE][45]","[FE][46]","[FE][47]",
    "[FE][48]","[FE][49]","[FE][4A]","[FE][4B]","[FE][4C]","[FE][4D]","[FE][4E]","[FE][4F]",
    "[FE][50]","[FE][51]","[FE][52]","[FE][53]","[FE][54]","[FE][55]","[FE][56]","[FE][57]",
    "[FE][58]","[FE][59]","[FE][5A]","[FE][5B]","[FE][5C]","[FE][5D]","[FE][5E]","[FE][5F]",
    "[FE][60]","[FE][61]","[FE][62]","[FE][63]","[FE][64]","[FE][65]","[FE][66]","[FE][67]",
    "[FE][68]","[FE][69]","[FE][6A]","[FE][6B]","[FE][6C]","[FE][6D]","[FE][6E]","[FE][6F]",
    "[FE][70]","[FE][71]","[FE][72]","[FE][73]","[FE][74]","[FE][75]","[FE][76]","[FE][77]",
    "[FE][78]","[FE][79]","[FE][7A]","[FE][7B]","[FE][7C]","[FE][7D]","[FE][7E]","[FE][7F]",
    "[FE][80]","[FE][81]","[FE][82]","[FE][83]","[FE][84]","[FE][85]","[FE][86]","[FE][87]",
    "[FE][88]","[FE][89]","[FE][8A]","[FE][8B]","[FE][8C]","[FE][8D]","[FE][8E]","[FE][8F]",
    "[FE][90]","[FE][91]","[FE][92]","[FE][93]","[FE][94]","[FE][95]","[FE][96]","[FE][97]",
    "[FE][98]","[FE][99]","[FE][9A]","[FE][9B]","[FE][9C]","[FE][9D]","[FE][9E]","[FE][9F]",
    "[FE][A0]",    "｡"   ,    "｢"    ,   "｣"    ,    "､"   ,    "･"   ,    "ｦ"    ,    "ｧ"   ,
        "ｨ"   ,    "ｩ"   ,    "ｪ"    ,   "ｫ"    ,    "ｬ"   ,    "ｭ"   ,    "ｮ"    ,    "ｯ"   ,
        "ｰ"   ,    "ｱ"   ,    "ｲ"   ,    "ｳ"   ,    "ｴ"   ,    "ｵ"   ,    "ｶ"    ,    "ｷ"   ,
        "ｸ"   ,    "ｹ"   ,    "ｺ"   ,    "ｻ"   ,    "ｼ"   ,    "ｽ"   ,    "ｾ"    ,    "ｿ"   ,
        "ﾀ"   ,    "ﾁ"   ,    "ﾂ"   ,    "ﾃ"   ,    "ﾄ"    ,   "ﾅ"   ,    "ﾆ"    ,    "ﾇ"   ,
        "ﾈ"   ,    "ﾉ"   ,    "ﾊ"   ,    "ﾋ"   ,    "ﾌ"    ,   "ﾍ"   ,    "ﾎ"    ,    "ﾏ"   ,
        "ﾐ"   ,    "ﾑ"   ,    "ﾒ"   ,    "ﾓ"   ,    "ﾔ"    ,   "ﾕ"   ,    "ﾖ"    ,    "ﾗ"   ,
        "ﾘ"   ,    "ﾙ"   ,    "ﾚ"   ,    "ﾛ"   ,    "ﾜ"    ,   "ﾝ"   ,    "ﾞ"     ,    "ﾟ"   ,
    "[FE][E0]","[FE][E1]","[FE][E2]","[FE][E3]","[FE][E4]","[FE][E5]","[FE][E6]","[FE][E7]",
    "[FE][E8]","[FE][E9]","[FE][EA]","[FE][EB]","[FE][EC]","[FE][ED]","[FE][EE]","[FE][EF]",
    "[FE][F0]","[FE][F1]","[FE][F2]","[FE][F3]","[FE][F4]","[FE][F5]","[FE][F6]","[FE][F7]",
    "[FE][F8]","[FE][F9]","[FE][FA]","[FE][FB]","[FE][FC]","[FE][FD]","[FE][FE]","[FE][FF]",
};

/* PC-1403, 1416G, 1417G, 1425, 1440, 1445, 1460 tokens L=2 */
static char* CodeNew2[] = {
    "[EF][00]","[EF][01]","[EF][02]","[EF][03]","[EF][04]","[EF][05]","[EF][06]","[EF][07]",
    "[EF][08]","[EF][09]","[EF][0A]","[EF][0B]","[EF][0C]","[EF][0D]","[EF][0E]","[EF][0F]",
    "[EF][10]","[EF][11]","[EF][12]","[EF][13]","[EF][14]","[EF][15]","[EF][16]","[EF][17]",
    "[EF][18]","[EF][19]","[EF][1A]","[EF][1B]","[EF][1C]","[EF][1D]","[EF][1E]","[EF][1F]",
    "[EF][20]","[EF][21]","[EF][22]","[EF][23]","[EF][24]","[EF][25]","[EF][26]","[EF][27]",
    "[EF][28]","[EF][29]","[EF][2A]","[EF][2B]","[EF][2C]","[EF][2D]","[EF][2E]","[EF][2F]",
    "[EF][30]","[EF][31]","[EF][32]","[EF][33]","[EF][34]","[EF][35]","[EF][36]","[EF][37]",
    "[EF][38]","[EF][39]","[EF][3A]","[EF][3B]","[EF][3C]","[EF][3D]","[EF][3E]","[EF][3F]",
    "[EF][40]","[EF][41]","[EF][42]","[EF][43]","[EF][44]","[EF][45]","[EF][46]","[EF][47]",
    "[EF][48]","[EF][49]","[EF][4A]","[EF][4B]","[EF][4C]","[EF][4D]","[EF][4E]","[EF][4F]",
    "[EF][50]","[EF][51]","[EF][52]","[EF][53]","[EF][54]","[EF][55]","[EF][56]","[EF][57]",
    "[EF][58]","[EF][59]","CSI "    ,"[EF][5B]","[EF][5C]","[EF][5D]","[EF][5E]","[EF][5F]",
    "[EF][60]","[EF][61]","[EF][62]","[EF][63]","[EF][64]","[EF][65]","[EF][66]","[EF][67]",
    "[EF][68]","[EF][69]","[EF][6A]","[EF][6B]","[EF][6C]","[EF][6D]","[EF][6E]","[EF][6F]",
    "[EF][70]","[EF][71]","[EF][72]","[EF][73]","[EF][74]","[EF][75]","[EF][76]","[EF][77]",
    "[EF][78]","[EF][79]","[EF][7A]","[EF][7B]","[EF][7C]","[EF][7D]","[EF][7E]","[EF][7F]",
    "EOF "    ,"DSKF "   ,"LOF "    ,"LOC "    ,"BIN "    ,"OCT "    ,"NCR "    ,"NPR "    ,
    "PND "    ,"PTD "    ,"PXD "    ,"PFD "    ,"BDS "    ,"PDS "    ,"[EF][8E]","[EF][8F]",
    "INP "    ,"[EF][91]","[EF][92]","[EF][93]","[EF][94]","[EF][95]","[EF][96]","[EF][97]",
    "NDS "    ,"TDS "    ,"XDS "    ,"FDS "    ,"[EF][9C]","[EF][9D]","[EF][9E]","[EF][9F]",
    "[EF][A0]"," XOR "   ,"[EF][A2]","[EF][A3]","[EF][A4]","[EF][A5]","[EF][A6]","[EF][A7]",
    "RENUM "  ,"DELETE " ,"[EF][AA]","[EF][AB]","[EF][AC]","[EF][AD]","[EF][AE]","[EF][AF]",
    "FILES "  ,"LFILES " ,"INIT "   ,"KILL "   ,"NAME "   ,"SET "    ,"COPY "   ,"CONVERT ",
    "[EF][B8]","[EF][B9]","[EF][BA]","[EF][BB]","[EF][BC]","[EF][BD]","[EF][BE]","[EF][BF]",
    "ERASE "  ,"OUT "    ,"LLINE "  ,"RLINE "  ,"GLCURSOR ","LTEXT " ,"GRAPH "  ,"LF "     ,
    "CSIZE "  ,"COLOR "  ,"SORGN "  ,"CROTATE ","CIRCLE " ,"PAINT "  ,"[EF][CE]","[EF][CF]",
    "[EF][D0]","[EF][D1]","[EF][D2]","[EF][D3]","[EF][D4]","[EF][D5]","[EF][D6]","[EF][D7]",
    "[EF][D8]","[EF][D9]","[EF][DA]","[EF][DB]","[EF][DC]","[EF][DD]","[EF][DE]","[EF][DF]",
    "OUTPUT " ,"APPEND " ,"AS "     ,"[EF][E3]","[EF][E4]","[EF][E5]","[EF][E6]","[EF][E7]",
    "[EF][E8]","[EF][E9]","[EF][EA]","[EF][EB]","[EF][EC]","[EF][ED]","[EF][EE]","[EF][EF]",
    "[EF][F0]","[EF][F1]","[EF][F2]","[EF][F3]","[EF][F4]","[EF][F5]","[EF][F6]","[EF][F7]",
    "[EF][F8]","[EF][F9]","[EF][FA]","[EF][FB]","[EF][FC]","[EF][FD]","[EF][FE]","[EF][FF]",
};

/* PC-1360, 1280, 1475 chars */
static char* CodeExt[] = {
    "[00]","[01]","[02]","[03]","[04]","[05]","[06]","[07]",
    "[08]","[09]","[0A]","[0B]","[0C]","[0D]","[0E]","[0F]",
    "[10]","[11]","[12]","[13]","[14]","[15]","[16]","[17]",
    "[18]","[19]","[1A]","[1B]","[1C]","[1D]","[1E]","[1F]",
    " ","!","\"","#","$" ,"%","&","'"   ,
    "(",")","*" ,"+","," ,"-",".","/"   ,
    "0","1","2" ,"3","4" ,"5","6","7"   ,
    "8","9",":" ,";","<" ,"=",">","?"   ,
    "@","A","B" ,"C","D" ,"E","F","G"   ,
    "H","I","J" ,"K","L" ,"M","N","O"   ,
    "P","Q","R" ,"S","T" ,"U","V","W"   ,
    "X","Y","Z" ,"[","\\","]","^","_"   ,
    "`","a","b" ,"c","d" ,"e","f","g"   ,
    "h","i","j" ,"k","l" ,"m","n","o"   ,
    "p","q","r" ,"s","t" ,"u","v","w"   ,
    "x","y","z" ,"{","|" ,"}","~","[7F]",
    "[80]","[81]","[82]","[83]","[84]","[85]","[86]","[87]",
    "[88]","[89]","[8A]","[8B]","[8C]","[8D]","[8E]","[8F]",
    "[90]","[91]","[92]","[93]","[94]","[95]","[96]","[97]",
    "[98]","[99]","[9A]","[9B]","[9C]","[9D]","[9E]","[9F]",
    "[A0]","[A1]","[A2]","[A3]","[A4]","[A5]","[A6]","[A7]",
    "[A8]","[A9]","[AA]","[AB]","[AC]","[AD]","[AE]","[AF]",
    "[B0]","[B1]","[B2]","[B3]","[B4]","[B5]","[B6]","[B7]",
    "[B8]","[B9]","[BA]","[BB]","[BC]","[BD]","[BE]","[BF]",
    "[C0]","[C1]","[C2]","[C3]","[C4]","[C5]","[C6]","[C7]",
    "[C8]","[C9]","[CA]","[CB]","[CC]","[CD]","[CE]","[CF]",
    "[D0]","[D1]","[D2]","[D3]","[D4]","[D5]","[D6]","[D7]",
    "[D8]","[D9]","[DA]","[DB]","[DC]","[DD]","[DE]","[DF]",
    "[E0]","[E1]","[E2]","[E3]","[E4]","[E5]","[E6]","[E7]",
    "[E8]","[E9]","[EA]","[EB]","[EC]","[ED]","[EE]","[EF]",
    "[F0]","年"  ,"月"  ,"日"  ,"円"  ,"♠"   ,"♥"   ,"♦"   , /* Graphic characters here are necessary. The conversion takes place in */
    "♣"   ,"■"   ,"□"   ,"Π"   ,"√"  ,"[FD]","[FE]","[FF]", /* ConvertByteToBas, whereby several variants are supported. */
};
/* PC-1360, 1280, 1475 with Japanese chars */
static char* CodeExtU[] = {
    "[00]","[01]","[02]","[03]","[04]","[05]","[06]","[07]",
    "[08]","[09]","[0A]","[0B]","[0C]","[0D]","[0E]","[0F]",
    "[10]","[11]","[12]","[13]","[14]","[15]","[16]","[17]",
    "[18]","[19]","[1A]","[1B]","[1C]","[1D]","[1E]","[1F]",
    " ","!","\"","#","$" ,"%","&","'"   ,
    "(",")","*" ,"+","," ,"-",".","/"   ,
    "0","1","2" ,"3","4" ,"5","6","7"   ,
    "8","9",":" ,";","<" ,"=",">","?"   ,
    "@","A","B" ,"C","D" ,"E","F","G"   ,
    "H","I","J" ,"K","L" ,"M","N","O"   ,
    "P","Q","R" ,"S","T" ,"U","V","W"   ,
    "X","Y","Z" ,"[","\\","]","^","_"   ,
    "`","a","b" ,"c","d" ,"e","f","g"   ,
    "h","i","j" ,"k","l" ,"m","n","o"   ,
    "p","q","r" ,"s","t" ,"u","v","w"   ,
    "x","y","z" ,"{","|" ,"}","~","[7F]",
    "[80]","[81]","[82]","[83]","[84]","[85]","[86]","[87]",
    "[88]","[89]","[8A]","[8B]","[8C]","[8D]","[8E]","[8F]",
    "[90]","[91]","[92]","[93]","[94]","[95]","[96]","[97]",
    "[98]","[99]","[9A]","[9B]","[9C]","[9D]","[9E]","[9F]",
    "[A0]","｡","｢", "｣", "､" , "･", "ｦ", "ｧ",
    "ｨ",  "ｩ", "ｪ", "ｫ", "ｬ" , "ｭ", "ｮ", "ｯ",
    "ｰ",  "ｱ", "ｲ", "ｳ", "ｴ", "ｵ", "ｶ", "ｷ",
    "ｸ",  "ｹ", "ｺ", "ｻ", "ｼ", "ｽ", "ｾ", "ｿ",
    "ﾀ",  "ﾁ", "ﾂ", "ﾃ", "ﾄ", "ﾅ", "ﾆ", "ﾇ",
    "ﾈ",  "ﾉ", "ﾊ", "ﾋ", "ﾌ", "ﾍ", "ﾎ", "ﾏ",
    "ﾐ",  "ﾑ", "ﾒ", "ﾓ", "ﾔ", "ﾕ", "ﾖ", "ﾗ",
    "ﾘ",  "ﾙ", "ﾚ", "ﾛ", "ﾜ", "ﾝ", "ﾞ" , "ﾟ",
    "[E0]","[E1]","[E2]","[E3]","[E4]","[E5]","[E6]","[E7]",
    "[E8]","[E9]","[EA]","[EB]","[EC]","[ED]","[EE]","[EF]",
    "[F0]","年"  ,"月"  ,"日"  ,"円"   ,"♠"   ,"♥"   ,"♦"   ,
    "♣"   ,"■"   ,"□"   ,"Π"   ,"√"   ,"[FD]","[FE]","[FF]",
};

/* PC-1360, 1475, 1280, E500 tokens only for compatibility with Bas2img */
static char* CodeExt2[] = {
    "[FE][00]","[FE][01]","[FE][02]","[FE][03]","[FE][04]","[FE][05]","[FE][06]","[FE][07]", //[FE][00]RESERVED
    "[FE][08]","[FE][09]","[FE][0A]","BTEXT$ " ,"BDATA$ ","MEM$ "    ,"[FE][0E]","MON "    , //E220 MON
    "RUN "    ,"NEW "    ,"CONT "   ,"PASS "   ,"LIST "  ,"LLIST "   ,"CLOAD "  ,"MERGE "  , //G850V BLOAD->CLOAD, BSAVE->CSAVE
    "LOAD "   ,"RENUM "  ,"AUTO "   ,"DELETE " ,"FILES " ,"INIT "    ,"CONVERT ","LCOPY "  , //G850 MERGE-> RENUM?, LCOPY, OUT
    "CSAVE "  ,"OPEN "   ,"CLOSE "  ,"SAVE "   ,"CONSOLE ","RANDOM " ,"DEGREE " ,"RADIAN " , // E500 [25] RANDOMIZE
    "GRAD "   ,"BEEP "   ,"WAIT "   ,"GOTO "   ,"TRON "  ,"TROFF "   ,"CLEAR "  ,"USING "  ,
    "DIM "    ,"CALL "   ,"POKE "   ,"GPRINT " ,"PSET "  ,"PRESET "  ,"BASIC "  ,"TEXT "   ,
    "WIDTH "  ,"[FE][39]","ERASE "  ,"LFILES " ,"KILL "  ,"COPY "    ,"NAME "   ,"SET "    ,
    "LTEXT "  ,"GRAPH "  ,"LF "     ,"CSIZE "  ,"COLOR " ,"OUT "     ,"DEFDBL " ,"DEFSNG " ,
    "FIELD "  ,"PUT "    ,"GET "    ,"LSET "   ,"RSET "  ,"ENDIF "   ,"REPEAT " ,"UNTIL "  , // G850 [48-C]-> PIOSET, POIPUT, SPOUT, SPINP, HDCOPY
    "CLS "    ,"CURSOR " ," TO "    ," STEP "  ," THEN " ,"ON "      ,"IF "     ,"FOR "    , // E500 [51] LOCATE
    "LET "    ,"REM "    ,"END "    ,"NEXT "   ,"STOP "  ,"READ "    ,"DATA "   ,"PAUSE "  , /* see also variable REMstr */
    "PRINT "  ,"INPUT "  ,"GOSUB "  ,"AREAD "  ,"LPRINT ","RETURN "  ,"RESTORE ","CHAIN "  , //G850 AREAD-> LNINPUT
    "GCURSOR ","LINE "   ,"LLINE "  ,"RLINE "  ,"GLCURSOR ","SORGN " ,"CROTATE ","CIRCLE " ,
    "PAINT "  ,"OUTPUT " ,"APPEND " ,"AS "     ,"ARUN "  ,"AUTOGOTO "," ELSE "  ,"RESUME " ,
    "ERROR "  ,"KEY "    ,"WHILE "  ,"WEND "   ,"SWITCH ","CASE "    ,"DEFAULT ","ENDSWITCH ",
    "MDF "    ,"REC "    ,"POL "    ,"ROT "    ,"DECI "  ,"HEX "     ,"TEN "    ,"RCP "    ,
    "SQU "    ,"CUR "    ,"HSN "    ,"HCS "    ,"HTN "   ,"AHS "     ,"AHC "    ,"AHT "    ,
    "FACT "   ,"LN "     ,"LOG "    ,"EXP "    ,"SQR "   ,"SIN "     ,"COS "    ,"TAN "    ,
    "INT "    ,"ABS "    ,"SGN "    ,"DEG "    ,"DMS "   ,"ASN "     ,"ACS "    ,"ATN "    ,
    "RND "    ," AND "   ," OR "    ,"NOT "    ,"PEEK "  ," XOR "    ,"INP "    ,"EVAL "   , //G850 INP, PIOGET, MOD, UPDATE
    "PIOGET " ,"[FE][A9]","[FE][AA]","[FE][AB]","[FE][AC]","POINT "  ,"PI "     ,"MEM "    ,	// E500 [AF] FRE
    "EOF "    ,"DSKF "   ,"LOF "    ,"LOC "    ,"[FE][B4]","[FE][B5]","NCR "    ,"NPR"     ,
    "[FE][B8]","[FE][B9]","[FE][BA]","[FE][BB]","[FE][BC]","[FE][BD]","AER "    ,"CUB "    ,
    "ERN "    ,"ERL "    ,"[FE][C2]","[FE][C3]","[FE][C4]","[FE][C5]","MOD "    ,"UPDATE " ,
    "[FE][C8]","[FE][C9]","[FE][CA]","[FE][CB]","[FE][CC]","[FE][CD]","[FE][CE]","[FE][CF]",
    "ASC "    ,"VAL "    ,"LEN "    ,"KLEN "   ,"[FE][D4]","[FE][D5]","[FE][D6]","[FE][D7]", //G850 KLEN-> VDEG, DMS$
    "[FE][D8]","[FE][D9]","[FE][DA]","[FE][DB]","[FE][DC]","[FE][DD]","[FE][DE]","[FE][DF]",
    "AKCNV$ " ,"KACNV$ " ,"JIS$ "   ,"[FE][E3]","[FE][E4]","[FE][E5]","[FE][E6]","[FE][E7]",
    "OPEN$ "  ,"INKEY$ " ,"MID$ "   ,"LEFT$ "  ,"RIGHT$ " ,"KMID$ "  ,"KLEFT$ " ,"KRIGHT$ ",
    "CHR$ "   ,"STR$ "   ,"HEX$ "   ,"DMS$ "   ,"[FE][F4]","[FE][F5]","[FE][F6]","[FE][F7]",
    "[FE][F8]","[FE][F9]","[FE][FA]","[FE][FB]","[FE][FC]","[FE][FD]","[FE][FE]","[FE][FF]", //G850V &HF8
};

/* PC-1600 mode 0, PC-E500 series 1. table */
static char* CodeE437[] = {
    "[00]","[01]","[02]","[03]","[04]","[05]","[06]","[07]",
    "[08]","[09]","[0A]","[0B]","[0C]","[0D]","[0E]","[0F]",
    "[10]","[11]","[12]","[13]","[14]","[15]","[16]","[17]",
    "[18]","[19]","[1A]","[1B]","[1C]","[1D]","[1E]","[1F]", // PC-E500: 1C-1F →←↑↓
    " ","!","\"","#","$","%","&","'",
    "(",")","*","+",",","-",".","/",
    "0","1","2","3","4","5","6","7",
    "8","9",":",";","<","=",">","?",
    "@","A","B","C","D","E","F","G",
    "H","I","J","K","L","M","N","O",
    "P","Q","R","S","T","U","V","W",
    "X","Y","Z","[","\\","]","^","_",
    "`","a","b","c","d","e","f","g",
    "h","i","j","k","l","m","n","o",
    "p","q","r","s","t","u","v","w",
    "x","y","z","{","|","}","~","[7F]",  //E-500: x7F, PC-1600: [FUL] (longer string)
    "[80]","[81]","[82]","[83]","[84]","[85]","[86]","[87]",
    "[88]","[89]","[8A]","[8B]","[8C]","[8D]","[8E]","[8F]",
    "[90]","[91]","[92]","[93]","[94]","[95]","[96]","[97]",
    "[98]","[99]","[9A]","[9B]","[9C]","¥"  , "[9E]","[9F]",
    "[A0]","[A1]","[A2]","[A3]","[A4]","[A5]","[A6]","[A7]",
    "[A8]","[A9]","[AA]","[AB]","[AC]","[AD]","[AE]","[AF]",
    "[B0]","[B1]","[B2]","[B3]","[B4]","[B5]","[B6]","[B7]",
    "[B8]","[B9]","[BA]","[BB]","[BC]","[BD]","[BE]","[BF]",
    "[C0]","[C1]","[C2]","[C3]","[C4]","[C5]","[C6]","[C7]",
    "[C8]","[C9]","[CA]","[CB]","[CC]","[CD]","[CE]","[CF]",
    "[D0]","[D1]","[D2]","[D3]","[D4]","[D5]","[D6]","[D7]",
    "[D8]","[D9]","[DA]","[DB]","[DC]","[DD]","[DE]","[DF]",
    "[E0]","[E1]","[E2]","π"  , "[E4]","[E5]","[E6]","[E7]",
    "[E8]","[E9]","[EA]","[EB]","[EC]","[ED]","[EE]","[EF]",
    "[F0]","[F1]","[F2]","[F3]","[F4]","[F5]","[F6]","[F7]",
    "[F8]","[F9]","[FA]","√"  , "[FC]","[FD]","[FE]","[FF]",/* For Sharp special characters: see ConvertByteToBas */
};
/* PC-1600 mode 0, PC-E500 series 1. table */
static char* CodeE437U[] = {
    "[00]","[01]","[02]","[03]","[04]","[05]","[06]","[07]",
    "[08]","[09]","[0A]","[0B]","[0C]","[0D]","[0E]","[0F]",
    "[10]","[11]","[12]","[13]","[14]","[15]","[16]","[17]",
    "[18]","[19]","[1A]","[1B]","[1C]","[1D]", "□",  "[1F]", // PC-E500: 1C-1F →←↑↓
    " ","!","\"","#","$","%","&","'",
    "(",")","*","+",",","-",".","/",
    "0","1","2","3","4","5","6","7",
    "8","9",":",";","<","=",">","?",
    "@","A","B","C","D","E","F","G",
    "H","I","J","K","L","M","N","O",
    "P","Q","R","S","T","U","V","W",
    "X","Y","Z","[","\\","]","^","_",
    "`","a","b","c","d","e","f","g",
    "h","i","j","k","l","m","n","o",
    "p","q","r","s","t","u","v","w",
    "x","y","z","{","|","}","~","[7F]", //E-500: ⌂, PC-1600: "■\x00]"
    "Ç","ü","é","â","ä","à","å","ç",
    "ê","ë","è","ï","î","ì","Ä","Å",
    "É","æ","Æ","ô","ö","ò","û","ù",
    "ÿ","Ö","Ü","¢","£","¥","₧","ƒ",
    "á","í","ó","ú","ñ","Ñ","ª","º",
    "¿","⌐","¬","½","¼","¡","«","»",
    "░","▒","▓","│","┤","╡","╢","╖",
    "╕","╣","║","╗","╝","╜","╛","┐",
    "└","┴","┬","├","─","┼","╞","╟",
    "╚","╔","╩","╦","╠","═","╬","╧",
    "╨","╤","╥","╙","╘","╒","╓","╫",
    "╪","┘","┌","█","▄","▌","▐","▀",
    "α","ß","Γ","π","Σ","σ","µ","τ",
    "Φ","Θ","Ω","δ","∞","φ","ε","∩",
    "≡","±","≥","≤","⌠","⌡","÷","≈",
    "°","∙","·","√","ⁿ","²","■","[FF]",
};
/* PC-E220 models without Japanese Chars */
static char* CodeE220[] = {
    "[00]","[01]","[02]","[03]","[04]","[05]","[06]","[07]",
    "[08]","[09]","[0A]","[0B]","[0C]","[0D]","[0E]","[0F]",
    "[10]","[11]","[12]","[13]","[14]","[15]","[16]","[17]",
    "[18]","[19]","[1A]","[1B]","[1C]","[1D]","[1E]","[1F]",
    " ","!","\"","#","$" ,"%","&","'"   ,
    "(",")","*" ,"+","," ,"-",".","/"   ,
    "0","1","2" ,"3","4" ,"5","6","7"   ,
    "8","9",":" ,";","<" ,"=",">","?"   ,
    "@","A","B" ,"C","D" ,"E","F","G"   ,
    "H","I","J" ,"K","L" ,"M","N","O"   ,
    "P","Q","R" ,"S","T" ,"U","V","W"   ,
    "X","Y","Z" ,"[","\\","]","^","_"   ,
    "`","a","b" ,"c","d" ,"e","f","g"   ,
    "h","i","j" ,"k","l" ,"m","n","o"   ,
    "p","q","r" ,"s","t" ,"u","v","w"   ,
    "x","y","z" ,"{","|" ,"}","~","[7F]",
    "[80]","[81]","[82]","[83]","[84]","[85]","[86]","[87]", /* No special chars converted a moment */
    "[88]","[89]","[8A]","[8B]","[8C]","[8D]","[8E]","[8F]",
    "[90]","[91]","[92]","[93]","[94]","[95]","[96]","[97]",
    "[98]","[99]","[9A]","[9B]","[9C]","[9D]","[9E]","[9F]",
    "[A0]","[A1]","[A2]","[A3]","[A4]","[A5]","[A6]","[A7]",
    "[A8]","[A9]","[AA]","[AB]","[AC]","[AD]","[AE]","[AF]",
    "[B0]","[B1]","[B2]","[B3]","[B4]","[B5]","[B6]","[B7]",
    "[B8]","[B9]","[BA]","[BB]","[BC]","[BD]","[BE]","[BF]",
    "[C0]","[C1]","[C2]","[C3]","[C4]","[C5]","[C6]","[C7]",
    "[C8]","[C9]","[CA]","[CB]","[CC]","[CD]","[CE]","[CF]",
    "[D0]","[D1]","[D2]","[D3]","[D4]","[D5]","[D6]","[D7]",
    "[D8]","[D9]","[DA]","[DB]","[DC]","[DD]","[DE]","[DF]",
    "[E0]","[E1]","[E2]","[E3]","[E4]","[E5]","[E6]","[E7]",
    "[E8]","[E9]","[EA]","[EB]","[EC]","[ED]","[EE]","[EF]",
    "[F0]","[F1]","[F2]","[F3]","[F4]","[F5]","[F6]","[F7]",
    "[F8]","[F9]","[FA]","[FB]","[FC]","[FD]","[FE]","[FF]",
};

/* PC-G850 series for transfer to ASCII */
static char* CodeG850[] = {
    "[00]","[01]","[02]","[03]","[04]","[05]","[06]","[07]",
    "[08]","[09]","[0A]","[0B]","[0C]","[0D]","[0E]","[0F]",
    "[10]","[11]","[12]","[13]","[14]","[15]","[16]","[17]",
    "[18]","[19]","[1A]","[1B]","[1C]","[1D]","[1E]","[1F]",
    " ","!","\"","#","$" ,"%","&","'"   ,
    "(",")","*" ,"+","," ,"-",".","/"   ,
    "0","1","2" ,"3","4" ,"5","6","7"   ,
    "8","9",":" ,";","<" ,"=",">","?"   ,
    "@","A","B" ,"C","D" ,"E","F","G"   ,
    "H","I","J" ,"K","L" ,"M","N","O"   ,
    "P","Q","R" ,"S","T" ,"U","V","W"   ,
    "X","Y","Z" ,"[","¥","]","^","_"   ,
    "`","a","b" ,"c","d" ,"e","f","g"   ,
    "h","i","j" ,"k","l" ,"m","n","o"   ,
    "p","q","r" ,"s","t" ,"u","v","w"   ,
    "x","y","z" ,"{","|" ,"}","~","[7F]",
    "[80]","[81]","[82]","[83]","[84]","[85]","[86]","[87]",
    "[88]","[89]","[8A]","[8B]","[8C]","[8D]","[8E]","[8F]",
    "[90]","[91]","[92]","[93]","[94]","[95]","[96]","[97]",
    "[98]","[99]","[9A]","[9B]","[9C]","[9D]","[9E]","[9F]",
    "[A0]","[A1]","[A2]","[A3]","[A4]","[A5]","[A6]","[A7]",
    "[A8]","[A9]","[AA]","[AB]","[AC]","[AD]","[AE]","[AF]",
    "[B0]","[B1]","[B2]","[B3]","[B4]","[B5]","[B6]","[B7]",
    "[B8]","[B9]","[BA]","[BB]","[BC]","[BD]","[BE]","[BF]",
    "[C0]","[C1]","[C2]","[C3]","[C4]","[C5]","[C6]","[C7]",
    "[C8]","[C9]","[CA]","[CB]","[CC]","[CD]","[CE]","[CF]",
    "[D0]","[D1]","[D2]","[D3]","[D4]","[D5]","[D6]","[D7]",
    "[D8]","[D9]","[DA]","[DB]","[DC]","[DD]","[DE]","[DF]",
    "[E0]","[E1]","[E2]","[E3]","[E4]","[E5]","[E6]","[E7]",
    "♠"   , "♥"  , "♦"  , "♣"  ,"[EC]","[ED]","[EE]","[EF]", /* Graphic characters here are necessary. */
    "[F0]","円"  ,"年"   , "月" ,"日"   ,"時"  ,"分"   ,"秒", /* The conversion takes place in ConvertByteToBas, */
    "[F8]","[F9]","[FA]","[FB]","[FC]","[FD]","[FE]","[FF]", /* whereby several variants are supported. */
};
/* PC-G850 series with Japanese chars for transfer to UTF-8 */
static char* CodeG850U[] = {
    "[00]","[01]","[02]","[03]","[04]","[05]","[06]","[07]",
    "[08]","[09]","[0A]","[0B]","[0C]","[0D]","[0E]","[0F]",
    "[10]","[11]","[12]","[13]","[14]","[15]","[16]","[17]",
    "[18]","[19]","[1A]","[1B]","[1C]","[1D]","[1E]","[1F]",
    " ","!","\"","#","$" ,"%","&","'"   ,
    "(",")","*" ,"+","," ,"-",".","/"   ,
    "0","1","2" ,"3","4" ,"5","6","7"   ,
    "8","9",":" ,";","<" ,"=",">","?"   ,
    "@","A","B" ,"C","D" ,"E","F","G"   ,
    "H","I","J" ,"K","L" ,"M","N","O"   ,
    "P","Q","R" ,"S","T" ,"U","V","W"   ,
    "X","Y","Z" ,"[","¥","]","^","_"   ,
    "`","a","b" ,"c","d" ,"e","f","g"   ,
    "h","i","j" ,"k","l" ,"m","n","o"   ,
    "p","q","r" ,"s","t" ,"u","v","w"   ,
    "x","y","z" ,"{","|" ,"}","~","[7F]",
    "[80]","[81]","[82]","[83]","[84]","[85]","[86]","[87]",
    "[88]","[89]","[8A]","[8B]","[8C]","[8D]","[8E]","[8F]",
// "⊥","⊤","⊣","⊢","[94]","[95]","[96]","[97]", Mathematical-Operator U+2200(8704)-U+22FF(8959)
    "[90]","[91]","[92]","[93]","[94]","[95]","[96]","[97]",
    "[98]","[99]","[9A]","[9B]","[9C]","[9D]","[9E]","[9F]",
    "[A0]","｡","｢", "｣", "､" , "･", "ｦ", "ｧ",
    "ｨ",  "ｩ", "ｪ", "ｫ", "ｬ" , "ｭ", "ｮ", "ｯ",
    "ｰ",  "ｱ", "ｲ", "ｳ", "ｴ", "ｵ", "ｶ", "ｷ",
    "ｸ",  "ｹ", "ｺ", "ｻ", "ｼ", "ｽ", "ｾ", "ｿ",
    "ﾀ",  "ﾁ", "ﾂ", "ﾃ", "ﾄ", "ﾅ", "ﾆ", "ﾇ",
    "ﾈ",  "ﾉ", "ﾊ", "ﾋ", "ﾌ", "ﾍ", "ﾎ", "ﾏ",
    "ﾐ",  "ﾑ", "ﾒ", "ﾓ", "ﾔ", "ﾕ", "ﾖ", "ﾗ",
    "ﾘ",  "ﾙ", "ﾚ", "ﾛ", "ﾜ", "ﾝ", "ﾞ" , "ﾟ",
//"[E0]","⊧","≠","[E3]","◢","◣","◥","◤", Geometric Shapes U+25A0 - U+25FF
    "[E0]","[E1]","[E2]","[E3]","[E4]","[E5]","[E6]","[E7]",
    "♠", "♥", "♦", "♣","[EC]","[ED]","[EE]","[EF]",//"∕","∖", Miscellaneous Symbols
    "[F0]","円" ,"年", "月" ,"日" ,"時","分","秒" ,//f0:""...[HOUR] [MINUTE] [SECOND]
    "[F8]","[F9]","[FA]","[FB]","[FC]","[FD]","[FE]","[FF]",// f8: "”"
};

static char* CodeE2[] = {
    "[FE][00]","[FE][01]","[FE][02]","[FE][03]","[FE][04]","[FE][05]","[FE][06]","[FE][07]", //[FE][00] RESERVED
    "[FE][08]","[FE][09]","[FE][0A]","BTEXT$ " ,"BDATA$ " ,"MEM$ "   ,"[FE][0E]","MON "    ,
    "RUN "    ,"NEW "    ,"CONT "   ,"PASS "   ,"LIST "   ,"LLIST "  ,"CLOAD "  ,"MERGE "  , //G850V BLOAD->CLOAD, BSAVE->CSAVE
    "LOAD "   ,"RENUM "  ,"AUTO "   ,"DELETE " ,"FILES "  ,"INIT "   ,"CONVERT ","LCOPY "  , //G850 MERGE-> RENUM?, LCOPY, OUT
    "CSAVE "  ,"OPEN "   ,"CLOSE "  ,"SAVE "   ,"CONSOLE ","RANDOMIZE ","DEGREE ","RADIAN ",
    "GRAD "   ,"BEEP "   ,"WAIT "   ,"GOTO "   ,"TRON "   ,"TROFF "  ,"CLEAR "  ,"USING "  ,
    "DIM "    ,"CALL "   ,"POKE "   ,"GPRINT " ,"PSET "   ,"PRESET " ,"BASIC "  ,"TEXT "   ,
    "WIDTH "  ,"[FE][39]","ERASE "  ,"LFILES " ,"KILL "   ,"COPY "   ,"NAME "   ,"SET "    ,
    "LTEXT "  ,"GRAPH "  ,"LF "     ,"CSIZE "  ,"COLOR "  ,"OUT "    ,"DEFDBL " ,"DEFSNG " ,
    "PIOSET " ,"PIOPUT " ,"SPOUT "  ,"SPINP "  ,"HDCOPY " ,"ENDIF "  ,"REPEAT " ,"UNTIL "  , // G850 PIOSET, PIOPUT, SPOUT, SPINP, HDCOPY
    "CLS "    ,"LOCATE " ," TO "    ," STEP "  ," THEN "  ,"ON "     ,"IF "     ,"FOR "    ,
    "LET "    ,"REM "    ,"END "    ,"NEXT "   ,"STOP "   ,"READ "   ,"DATA "   ,"PAUSE "  , /* see also variable REMstr */
    "PRINT "  ,"INPUT "  ,"GOSUB "  ,"LNINPUT ","LPRINT " ,"RETURN " ,"RESTORE ","CHAIN "  , //G850 LNINPUT
    "GCURSOR ","LINE "   ,"LLINE "  ,"RLINE "  ,"GLCURSOR ","SORGN " ,"CROTATE ","CIRCLE " ,
    "PAINT "  ,"OUTPUT " ,"APPEND " ,"AS "     ,"ARUN "   ,"AUTOGOTO "," ELSE " ,"RESUME " , /* see variable ELSEid_E2 */
    "ERROR "  ,"KEY "    ,"WHILE "  ,"WEND "   ,"SWITCH " ,"CASE "   ,"DEFAULT ","ENDSWITCH ",
    "MDF "    ,"REC "    ,"POL "    ,"ROT "    ,"DECI "   ,"HEX "    ,"TEN "    ,"RCP "    ,
    "SQU "    ,"CUR "    ,"HSN "    ,"HCS "    ,"HTN "    ,"AHS "    ,"AHC "    ,"AHT "    ,
    "FACT "   ,"LN "     ,"LOG "    ,"EXP "    ,"SQR "    ,"SIN "    ,"COS "    ,"TAN "    ,
    "INT "    ,"ABS "    ,"SGN "    ,"DEG "    ,"DMS "    ,"ASN "    ,"ACS "    ,"ATN "    ,
    "RND "    ," AND "   ," OR "    ,"NOT "    ,"PEEK "   ," XOR "   ,"INP "    ,"EVAL "   , //G850 INP, PIOGET, MOD
    "PIOGET " ,"[FE][A9]","[FE][AA]","[FE][AB]","[FE][AC]","POINT "  ,"PI "     ,"FRE"     ,
    "EOF "    ,"DSKF "   ,"LOF "    ,"LOC "    ,"[FE][B4]","[FE][B5]","NCR "    ,"NPR"     ,
    "[FE][B8]","[FE][B9]","[FE][BA]","[FE][BB]","[FE][BC]","[FE][BD]","AER "    ,"CUB "    ,
    "ERN "    ,"ERL "    ,"[FE][C2]","[FE][C3]","[FE][C4]","[FE][C5]","MOD "    ,"FIX "    , // C7 ?FIX/?UPDATE
    "[FE][C8]","[FE][C9]","[FE][CA]","[FE][CB]","[FE][CC]","[FE][CD]","[FE][CE]","[FE][CF]",
    "ASC "    ,"VAL "    ,"LEN "    ,"VDEG "   ,"[FE][D4]","[FE][D5]","[FE][D6]","[FE][D7]", //G850 VDEG, DMS$
    "[FE][D8]","[FE][D9]","[FE][DA]","[FE][DB]","[FE][DC]","[FE][DD]","[FE][DE]","[FE][DF]",
    "AKCNV$ " ,"KACNV$ " ,"JIS$ "   ,"[FE][E3]","[FE][E4]","[FE][E5]","[FE][E6]","[FE][E7]",
    "OPEN$ "  ,"INKEY$ " ,"MID$ "   ,"LEFT$ "  ,"RIGHT$ " ,"KMID$ "  ,"KLEFT$ " ,"KRIGHT$ ",
    "CHR$ "   ,"STR$ "   ,"HEX$ "   ,"DMS$ "   ,"[FE][F4]","[FE][F5]","[FE][F6]","[FE][F7]",
    "[FE][F8]","[FE][F9]","[FE][FA]","[FE][FB]","[FE][FC]","[FE][FD]","[FE][FE]","[FE][FF]", //G850V &HF8
};

static char* CodePc1500_1[] = {
    "[00]","[01]","[02]","[03]","[04]","[05]","[06]","[07]",
    "[08]","[09]","[0A]","[0B]","[0C]","[0D]","[0E]","[0F]",
    "[10]","[11]","[12]","[13]","[14]","[15]","[16]","[17]",
    "[18]","[19]","[1A]","[1B]","[1C]","[1D]","[1E]","[1F]",
    " ","!","\"","#","$","%","&","□",                         // 27=InsFrame □
    "(",")","*","+",",","-",".","/",
    "0","1","2","3","4","5","6","7",
    "8","9",":",";","<","=",">","?",
    "@","A","B","C","D","E","F","G",
    "H","I","J","K","L","M","N","O",
    "P","Q","R","S","T","U","V","W",
    "X","Y","Z","√","¥","Π","^","_",
    "`","a","b","c","d","e","f","g",
    "h","i","j","k","l","m","n","o",
    "p","q","r","s","t","u","v","w",
    "x","y","z","{","|","}","~","■",                          // 7F=FullFrame ■
    "[80]","[81]","[82]","[83]","[84]","[85]","[86]","[87]",
    "[88]","[89]","[8A]","[8B]","[8C]","[8D]","[8E]","[8F]",
    "[90]","[91]","[92]","[93]","[94]","[95]","[96]","[97]",
    "[98]","[99]","[9A]","[9B]","[9C]","[9D]","[9E]","[9F]",
    "[A0]","[A1]","[A2]","[A3]","[A4]","[A5]","[A6]","[A7]",
    "[A8]","[A9]","[AA]","[AB]","[AC]","[AD]","[AE]","[AF]",
    "[B0]","[B1]","[B2]","[B3]","[B4]","[B5]","[B6]","[B7]",
    "[B8]","[B9]","[BA]","[BB]","[BC]","[BD]","[BE]","[BF]",
    "[C0]","[C1]","[C2]","[C3]","[C4]","[C5]","[C6]","[C7]",
    "[C8]","[C9]","[CA]","[CB]","[CC]","[CD]","[CE]","[CF]",
    "[D0]","[D1]","[D2]","[D3]","[D4]","[D5]","[D6]","[D7]",
    "[D8]","[D9]","[DA]","[DB]","[DC]","[DD]","[DE]","[DF]",
    "[E0]","[E1]","[E2]","[E3]","[E4]","[E5]","[E6]","[E7]",
    "[E8]","[E9]","[EA]","[EB]","[EC]","[ED]","[EE]","[EF]",
    "[F0]","[F1]","[F2]","[F3]","[F4]","[F5]","[F6]","[F7]",
    "[F8]","[F9]","[FA]","[FB]","[FC]","[FD]","[FE]","[FF]",
};

static char* CodePc1500_1J[] = {
    "[00]","[01]","[02]","[03]","[04]","[05]","[06]","[07]",
    "[08]","[09]","[0A]","[0B]","[0C]","[0D]","[0E]","[0F]",
    "[10]","[11]","[12]","[13]","[14]","[15]","[16]","[17]",
    "[18]","[19]","[1A]","[1B]","[1C]","[1D]", "□" , "[1F]",
    " ","!","\"","#","$","%","&","□",
    "(",")","*","+",",","-",".","/",
    "0","1","2","3","4","5","6","7",
    "8","9",":",";","<","=",">","?",
    "@","A","B","C","D","E","F","G",
    "H","I","J","K","L","M","N","O",
    "P","Q","R","S","T","U","V","W",
    "X","Y","Z","√","¥","Π","^","_",
    "`","a","b","c","d","e","f","g",
    "h","i","j","k","l","m","n","o",
    "p","q","r","s","t","u","v","w",
    "x","y","z","{","|","}","~","■",
    "[80]","[81]","[82]","[83]","[84]","[85]","[86]","[87]",
/* Kanji see PC-1600K manual, codepoints file */
    "[88]","[89]","[8A]","[8B]","[8C]","[8D]","[8E]","[8F]",
    "[90]","[91]","[92]","[93]","[94]","[95]","[96]","[97]",
    "[98]","[99]","[9A]","[9B]","[9C]","[9D]","[9E]","[9F]",
    "[A0]","｡","｢", "｣", "､" , "･", "ｦ", "ｧ",
    "ｨ",  "ｩ", "ｪ", "ｫ", "ｬ" , "ｭ", "ｮ", "ｯ",
    "ｰ",  "ｱ", "ｲ", "ｳ", "ｴ", "ｵ", "ｶ", "ｷ",
    "ｸ",  "ｹ", "ｺ", "ｻ", "ｼ", "ｽ", "ｾ", "ｿ",
    "ﾀ",  "ﾁ", "ﾂ", "ﾃ", "ﾄ", "ﾅ", "ﾆ", "ﾇ",
    "ﾈ",  "ﾉ", "ﾊ", "ﾋ", "ﾌ", "ﾍ", "ﾎ", "ﾏ",
    "ﾐ",  "ﾑ", "ﾒ", "ﾓ", "ﾔ", "ﾕ", "ﾖ", "ﾗ",
    "ﾘ",  "ﾙ", "ﾚ", "ﾛ", "ﾜ", "ﾝ", "ﾞ" , "ﾟ",
/* more from codepoints file */
    "[E0]","[E1]","[E2]","[E3]","[E4]","[E5]","[E6]","[E7]",
    "[E8]","[E9]","[EA]","[EB]","[EC]","[ED]","[EE]","[EF]",
    "[F0]","[F1]","[F2]","[F3]","[F4]","[F5]","[F6]","[F7]",
    "[F8]","[F9]","[FA]","[FB]","[FC]","[FD]","[FE]","[FF]",
};

static char* CodePc1600_1J[] = {
    "[00]","[01]","[02]","[03]","[04]","[05]","[06]","[07]",
    "[08]","[09]","[0A]","[0B]","[0C]","[0D]","[0E]","[0F]",
    "[10]","[11]","[12]","[13]","[14]","[15]","[16]","[17]",
    "[18]","[19]","[1A]","[1B]","[1C]","[1D]", "□" , "[1F]",
    " ","!","\"","#","$","%","&","'",
    "(",")","*","+",",","-",".","/",
    "0","1","2","3","4","5","6","7",
    "8","9",":",";","<","=",">","?",
    "@","A","B","C","D","E","F","G",
    "H","I","J","K","L","M","N","O",
    "P","Q","R","S","T","U","V","W",
    "X","Y","Z","[","¥","]","^","_",
    "`","a","b","c","d","e","f","g",
    "h","i","j","k","l","m","n","o",
    "p","q","r","s","t","u","v","w",
    "x","y","z","{","|","}","~","■",
    "[80]","[81]","[82]","[83]","[84]","[85]","[86]","[87]",
    "[88]","[89]","[8A]","[8B]","[8C]","[8D]","[8E]","[8F]",
    "[90]","[91]","[92]","[93]","[94]","[95]","[96]","[97]",
    "[98]","[99]","[9A]","[9B]","[9C]","[9D]","[9E]","[9F]",
    "[A0]","｡","｢", "｣", "､" , "･", "ｦ", "ｧ",
    "ｨ",  "ｩ", "ｪ", "ｫ", "ｬ" , "ｭ", "ｮ", "ｯ",
    "ｰ",  "ｱ", "ｲ", "ｳ", "ｴ", "ｵ", "ｶ", "ｷ",
    "ｸ",  "ｹ", "ｺ", "ｻ", "ｼ", "ｽ", "ｾ", "ｿ",
    "ﾀ",  "ﾁ", "ﾂ", "ﾃ", "ﾄ", "ﾅ", "ﾆ", "ﾇ",
    "ﾈ",  "ﾉ", "ﾊ", "ﾋ", "ﾌ", "ﾍ", "ﾎ", "ﾏ",
    "ﾐ",  "ﾑ", "ﾒ", "ﾓ", "ﾔ", "ﾕ", "ﾖ", "ﾗ",
    "ﾘ",  "ﾙ", "ﾚ", "ﾛ", "ﾜ", "ﾝ", "ﾞ" , "ﾟ",
    "[E0]","[E1]","[E2]","[E3]","[E4]","[E5]","[E6]","[E7]",
    "[E8]","[E9]","[EA]","[EB]","[EC]","[ED]","[EE]","[EF]",
    "[F0]","[F1]","[F2]","[F3]","[F4]","[F5]","[F6]","[F7]",
    "[F8]","[F9]","[FA]","[FB]","[FC]","[FD]","[FE]","[FF]",
};
/*   // Template for other PC-1500/1600 devices
static char* CodePc1500_E3c[] = {
    "[E3][00]","[E3][01]","[E3][02]","[E3][03]","[E3][04]","[E3][05]","[E3][06]","[E3][07]",
    "[E3][08]","[E3][09]","[E3][0A]","[E3][0B]","[E3][0C]","[E3][0D]","[E3][0E]","[E3][0F]",
    "[E3][10]","[E3][11]","[E3][12]","[E3][13]","[E3][14]","[E3][15]","[E3][16]","[E3][17]",
    "[E3][18]","[E3][19]","[E3][1A]","[E3][1B]","[E3][1C]","[E3][1D]","[E3][1E]","[E3][1F]",
    "[E3][20]","[E3][21]","[E3][22]","[E3][23]","[E3][24]","[E3][25]","[E3][26]","[E3][27]",
    "[E3][28]","[E3][29]","[E3][2A]","[E3][2B]","[E3][2C]","[E3][2D]","[E3][2E]","[E3][2F]",
    "[E3][30]","[E3][31]","[E3][32]","[E3][33]","[E3][34]","[E3][35]","[E3][36]","[E3][37]",
    "[E3][38]","[E3][39]","[E3][3A]","[E3][3B]","[E3][3C]","[E3][3D]","[E3][3E]","[E3][3F]",
    "[E3][40]","[E3][41]","[E3][42]","[E3][43]","[E3][44]","[E3][45]","[E3][46]","[E3][47]",
    "[E3][48]","[E3][49]","[E3][4A]","[E3][4B]","[E3][4C]","[E3][4D]","[E3][4E]","[E3][4F]",
    "[E3][50]","[E3][51]","[E3][52]","[E3][53]","[E3][54]","[E3][55]","[E3][56]","[E3][57]",
    "[E3][58]","[E3][59]","[E3][5A]","[E3][5B]","[E3][5C]","[E3][5D]","[E3][5E]","[E3][5F]",
    "[E3][60]","[E3][61]","[E3][62]","[E3][63]","[E3][64]","[E3][65]","[E3][66]","[E3][67]",
    "[E3][68]","[E3][69]","[E3][6A]","[E3][6B]","[E3][6C]","[E3][6D]","[E3][6E]","[E3][6F]",
    "[E3][70]","[E3][71]","[E3][72]","[E3][73]","[E3][74]","[E3][75]","[E3][76]","[E3][77]",
    "[E3][78]","[E3][79]","[E3][7A]","[E3][7B]","[E3][7C]","[E3][7D]","[E3][7E]","[E3][7F]",
    "[E3][80]","[E3][81]","[E3][82]","[E3][83]","[E3][84]","[E3][85]","[E3][86]","[E3][87]",
    "[E3][88]","[E3][89]","[E3][8A]","[E3][8B]","[E3][8C]","[E3][8D]","[E3][8E]","[E3][8F]",
    "[E3][90]","[E3][91]","[E3][92]","[E3][93]","[E3][94]","[E3][95]","[E3][96]","[E3][97]",
    "[E3][98]","[E3][99]","[E3][9A]","[E3][9B]","[E3][9C]","[E3][9D]","[E3][9E]","[E3][9F]",
    "[E3][A0]","[E3][A1]","[E3][A2]","[E3][A3]","[E3][A4]","[E3][A5]","[E3][A6]","[E3][A7]",
    "[E3][A8]","[E3][A9]","[E3][AA]","[E3][AB]","[E3][AC]","[E3][AD]","[E3][AE]","[E3][AF]",
    "[E3][B0]","[E3][B1]","[E3][B2]","[E3][B3]","[E3][B4]","[E3][B5]","[E3][B6]","[E3][B7]",
    "[E3][B8]","[E3][B9]","[E3][BA]","[E3][BB]","[E3][BC]","[E3][BD]","[E3][BE]","[E3][BF]",
    "[E3][C0]","[E3][C1]","[E3][C2]","[E3][C3]","[E3][C4]","[E3][C5]","[E3][C6]","[E3][C7]",
    "[E3][C8]","[E3][C9]","[E3][CA]","[E3][CB]","[E3][CC]","[E3][CD]","[E3][CE]","[E3][CF]",
    "[E3][D0]","[E3][D1]","[E3][D2]","[E3][D3]","[E3][D4]","[E3][D5]","[E3][D6]","[E3][D7]",
    "[E3][D8]","[E3][D9]","[E3][DA]","[E3][DB]","[E3][DC]","[E3][DD]","[E3][DE]","[E3][DF]",
    "[E3][E0]","[E3][E1]","[E3][E2]","[E3][E3]","[E3][E4]","[E3][E5]","[E3][E6]","[E3][E7]",
    "[E3][E8]","[E3][E9]","[E3][EA]","[E3][EB]","[E3][EC]","[E3][ED]","[E3][EE]","[E3][EF]",
    "[E3][F0]","[E3][F1]","[E3][F2]","[E3][F3]","[E3][F4]","[E3][F5]","[E3][F6]","[E3][F7]",
    "[E3][F8]","[E3][F9]","[E3][FA]","[E3][FB]","[E3][FC]","[E3][FD]","[E3][FE]","[E3][FF]",
}; */

static char* CodePc1500_E1[] = { /*  Tramsoft Tools2 */
    "[E1][00]","[E1][01]","[E1][02]","[E1][03]","[E1][04]","[E1][05]","[E1][06]","[E1][07]",
    "[E1][08]","[E1][09]","[E1][0A]","[E1][0B]","[E1][0C]","[E1][0D]","[E1][0E]","[E1][0F]",
    "[E1][10]","[E1][11]","[E1][12]","[E1][13]","[E1][14]","[E1][15]","[E1][16]","[E1][17]",
    "[E1][18]","[E1][19]","[E1][1A]","[E1][1B]","[E1][1C]","[E1][1D]","[E1][1E]","[E1][1F]",
    "[E1][20]","[E1][21]","[E1][22]","[E1][23]","[E1][24]","[E1][25]","[E1][26]","[E1][27]",
    "[E1][28]","[E1][29]","[E1][2A]","[E1][2B]","[E1][2C]","[E1][2D]","[E1][2E]","[E1][2F]",
    "[E1][30]","[E1][31]","[E1][32]","[E1][33]","[E1][34]","[E1][35]","[E1][36]","[E1][37]",
    "[E1][38]","[E1][39]","[E1][3A]","[E1][3B]","[E1][3C]","[E1][3D]","[E1][3E]","[E1][3F]",
    "[E1][40]","[E1][41]","[E1][42]","[E1][43]","[E1][44]","[E1][45]","[E1][46]","[E1][47]",
    "[E1][48]","[E1][49]","[E1][4A]","[E1][4B]","[E1][4C]","[E1][4D]","[E1][4E]","[E1][4F]",
    "[E1][50]","[E1][51]","[E1][52]","[E1][53]","[E1][54]","[E1][55]","[E1][56]","[E1][57]",
    "[E1][58]","[E1][59]","[E1][5A]","[E1][5B]","[E1][5C]","[E1][5D]","[E1][5E]","[E1][5F]",
    "[E1][60]","[E1][61]","[E1][62]","[E1][63]","[E1][64]","[E1][65]","[E1][66]","[E1][67]",
    "[E1][68]","[E1][69]","[E1][6A]","[E1][6B]","[E1][6C]","[E1][6D]","[E1][6E]","[E1][6F]",
    "[E1][70]","[E1][71]","[E1][72]","[E1][73]","[E1][74]","[E1][75]","[E1][76]","[E1][77]",
    "[E1][78]","[E1][79]","[E1][7A]","[E1][7B]","[E1][7C]","[E1][7D]","[E1][7E]","[E1][7F]",
    "FLOAD "  ,"FSAVE "  ,"FCHAIN " ,"VERIFY " ,"[E1][84]","[E1][85]","[E1][86]","[E1][87]",
    "[E1][88]","[E1][89]","[E1][8A]","[E1][8B]","[E1][8C]","[E1][8D]","[E1][8E]","[E1][8F]",
    "[E1][90]","[E1][91]","[E1][92]","[E1][93]","[E1][94]","[E1][95]","[E1][96]","[E1][97]",
    "[E1][98]","[E1][99]","[E1][9A]","[E1][9B]","[E1][9C]","[E1][9D]","[E1][9E]","[E1][9F]",
    "[E1][A0]","[E1][A1]","[E1][A2]","[E1][A3]","[E1][A4]","[E1][A5]","[E1][A6]","[E1][A7]",
    "[E1][A8]","[E1][A9]","[E1][AA]","[E1][AB]","[E1][AC]","[E1][AD]","[E1][AE]","[E1][AF]",
    "[E1][B0]","[E1][B1]","[E1][B2]","[E1][B3]","[E1][B4]","[E1][B5]","[E1][B6]","[E1][B7]",
    "[E1][B8]","[E1][B9]","[E1][BA]","[E1][BB]","[E1][BC]","[E1][BD]","[E1][BE]","[E1][BF]",
    "[E1][C0]","[E1][C1]","[E1][C2]","[E1][C3]","[E1][C4]","[E1][C5]","[E1][C6]","[E1][C7]",
    "[E1][C8]","[E1][C9]","[E1][CA]","[E1][CB]","[E1][CC]","[E1][CD]","[E1][CE]","[E1][CF]",
    "[E1][D0]","[E1][D1]","[E1][D2]","[E1][D3]","[E1][D4]","[E1][D5]","[E1][D6]","[E1][D7]",
    "[E1][D8]","[E1][D9]","[E1][DA]","[E1][DB]","[E1][DC]","[E1][DD]","[E1][DE]","[E1][DF]",
    "[E1][E0]","[E1][E1]","[E1][E2]","[E1][E3]","[E1][E4]","[E1][E5]","[E1][E6]","[E1][E7]",
    "[E1][E8]","[E1][E9]","[E1][EA]","[E1][EB]","[E1][EC]","[E1][ED]","[E1][EE]","[E1][EF]",
    "[E1][F0]","[E1][F1]","[E1][F2]","[E1][F3]","[E1][F4]","[E1][F5]","[E1][F6]","[E1][F7]",
    "[E1][F8]","[E1][F9]","[E1][FA]","[E1][FB]","[E1][FC]","[E1][FD]","[E1][FE]","[E1][FF]",
};
static char** CodePc1600_E1 = CodePc1500_E1 ;

static char* CodePc1500_E2[] = { /*  Tramsoft Tools3 */
    "[E2][00]","[E2][01]","[E2][02]","[E2][03]","[E2][04]","[E2][05]","[E2][06]","[E2][07]",
    "[E2][08]","[E2][09]","[E2][0A]","[E2][0B]","[E2][0C]","[E2][0D]","[E2][0E]","[E2][0F]",
    "[E2][10]","[E2][11]","[E2][12]","[E2][13]","[E2][14]","[E2][15]","[E2][16]","[E2][17]",
    "[E2][18]","[E2][19]","[E2][1A]","[E2][1B]","[E2][1C]","[E2][1D]","[E2][1E]","[E2][1F]",
    "[E2][20]","[E2][21]","[E2][22]","[E2][23]","[E2][24]","[E2][25]","[E2][26]","[E2][27]",
    "[E2][28]","[E2][29]","[E2][2A]","[E2][2B]","[E2][2C]","[E2][2D]","[E2][2E]","[E2][2F]",
    "[E2][30]","[E2][31]","[E2][32]","[E2][33]","[E2][34]","[E2][35]","[E2][36]","[E2][37]",
    "[E2][38]","[E2][39]","[E2][3A]","[E2][3B]","[E2][3C]","[E2][3D]","[E2][3E]","[E2][3F]",
    "[E2][40]","[E2][41]","[E2][42]","[E2][43]","[E2][44]","[E2][45]","[E2][46]","[E2][47]",
    "[E2][48]","[E2][49]","[E2][4A]","[E2][4B]","[E2][4C]","[E2][4D]","[E2][4E]","[E2][4F]",
    "FRE "    ,"PGM "    ,"PSIZE "  ,"VKEEP "  ,"[E2][54]","[E2][55]","[E2][56]","[E2][57]",
    "[E2][58]","[E2][59]","[E2][5A]","[E2][5B]","[E2][5C]","[E2][5D]","[E2][5E]","[E2][5F]",
    "[E2][60]","[E2][61]","[E2][62]","[E2][63]","[E2][64]","[E2][65]","[E2][66]","[E2][67]",
    "[E2][68]","[E2][69]","[E2][6A]","[E2][6B]","[E2][6C]","[E2][6D]","[E2][6E]","[E2][6F]",
    "[E2][70]","FRC "    ,"STRING$ ","INSTR "  ,"[E2][74]","[E2][75]","[E2][76]","[E2][77]",
    "[E2][78]","[E2][79]","[E2][7A]","[E2][7B]","[E2][7C]","[E2][7D]","[E2][7E]","[E2][7F]",
    "[E2][80]","[E2][81]","[E2][82]","[E2][83]","[E2][84]","[E2][85]","[E2][86]","[E2][87]",
    "[E2][88]","[E2][89]","[E2][8A]","[E2][8B]","[E2][8C]","[E2][8D]","[E2][8E]","[E2][8F]",
    "[E2][90]","[E2][91]","[E2][92]","[E2][93]","[E2][94]","[E2][95]","[E2][96]","[E2][97]",
    "[E2][98]","[E2][99]","[E2][9A]","[E2][9B]","[E2][9C]","[E2][9D]","[E2][9E]","[E2][9F]",
    "[E2][A0]","[E2][A1]","[E2][A2]","[E2][A3]","[E2][A4]","[E2][A5]","[E2][A6]","[E2][A7]",
    "[E2][A8]","[E2][A9]","[E2][AA]","[E2][AB]","[E2][AC]","[E2][AD]","[E2][AE]","[E2][AF]",
    "[E2][B0]","[E2][B1]","[E2][B2]","[E2][B3]","[E2][B4]","[E2][B5]","[E2][B6]","[E2][B7]",
    "[E2][B8]","[E2][B9]","[E2][BA]","[E2][BB]","[E2][BC]","[E2][BD]","[E2][BE]","[E2][BF]",
    "CLR "    ,"PURGE "  ,"REDIM "  ,"RESUME " ,"SWAP "   ,"VLIST "  ,"[E2][C6]","[E2][C7]",
    "[E2][C8]","[E2][C9]","[E2][CA]","[E2][CB]","[E2][CC]","[E2][CD]","[E2][CE]","[E2][CF]",
    "[E2][D0]","[E2][D1]","[E2][D2]","[E2][D3]","[E2][D4]","[E2][D5]","[E2][D6]","[E2][D7]",
    "[E2][D8]","[E2][D9]","[E2][DA]","[E2][DB]","[E2][DC]","[E2][DD]","[E2][DE]","[E2][DF]",
    "[E2][E0]","[E2][E1]","[E2][E2]","[E2][E3]","[E2][E4]","[E2][E5]","[E2][E6]","[E2][E7]",
    "[E2][E8]","[E2][E9]","[E2][EA]","[E2][EB]","[E2][EC]","[E2][ED]","[E2][EE]","[E2][EF]",
    "[E2][F0]","[E2][F1]","[E2][F2]","[E2][F3]","[E2][F4]","[E2][F5]","[E2][F6]","[E2][F7]",
    "[E2][F8]","[E2][F9]","[E2][FA]","[E2][FB]","[E2][FC]","[E2][FD]","[E2][FE]","[E2][FF]",
};
static char** CodePc1600_E2 = CodePc1500_E2 ;

static char* CodePc1500_E3b[] = { /* Priority BMC MC-12 (A) */
    "[E3][00]","[E3][01]","SECONDS ","[E3][03]","PRON "   ,"[E3][05]","[E3][06]","[E3][07]", // Ursoft only part of commands
    "[E3][08]","[E3][09]","[E3][0A]","[E3][0B]","[E3][0C]","[E3][0D]","[E3][0E]","[E3][0F]",
    "[E3][10]","[E3][11]","[E3][12]","[E3][13]","[E3][14]","[E3][15]","[E3][16]","[E3][17]",
    "[E3][18]","[E3][19]","[E3][1A]","[E3][1B]","[E3][1C]","[E3][1D]","[E3][1E]","[E3][1F]",
    "[E3][20]","[E3][21]","[E3][22]","[E3][23]","[E3][24]","[E3][25]","[E3][26]","[E3][27]",
    "[E3][28]","[E3][29]","[E3][2A]","[E3][2B]","[E3][2C]","[E3][2D]","[E3][2E]","[E3][2F]",
    "[E3][30]","[E3][31]","[E3][32]","[E3][33]","[E3][34]","[E3][35]","[E3][36]","[E3][37]",
    "[E3][38]","[E3][39]","[E3][3A]","[E3][3B]","[E3][3C]","[E3][3D]","[E3][3E]","[E3][3F]",
    "[E3][40]","[E3][41]","[E3][42]","[E3][43]","[E3][44]","[E3][45]","[E3][46]","[E3][47]",
    "[E3][48]","[E3][49]","[E3][4A]","[E3][4B]","[E3][4C]","[E3][4D]","[E3][4E]","[E3][4F]",
    "BUFLEN " ,"BUFNUM " ,"CORR "  ,"SCANTIME ","TRIGGER ","PREHIST ","POSITION ","ROM# "  , // BMC MC-12(A), Trams4: CORR
    "SDVY "   ,"[E3][59]","[E3][5A]","[E3][5B]","[E3][5C]","[E3][5D]","ZEIT$ "  ,"ELAST "  , // Trams4
    "CLEN "   ,"CHA "    ,"RANGE " ,"BUFFER " ,"BUFRANGE ","ELIST$ " ,"[E3][66]","[E3][67]", // BMC MC-12(A), Trams4: CLEN, ELIST$
    "[E3][68]","[E3][69]","[E3][6A]","[E3][6B]","[E3][6C]","[E3][6D]","[E3][6E]","[E3][6F]",
    "STAT "   ,"STX "    ,"STY "    ,"[E3][73]","[E3][74]","[E3][75]","[E3][76]","[E3][77]", // Trams4
    "[E3][78]","[E3][79]","[E3][7A]","[E3][7B]","[E3][7C]","[E3][7D]","[E3][7E]","[E3][7F]",
    "SWITCH " ,"SCREEN " ,"OUTCHA ","REPEAT " ,"AUTORANGE ","WHILE " ,"INCHA " ,"[E3][87]", // CE-1600P: E381=PAPER
    "SWAP "  ,"SETRANGE ","MCON "  ,"MCOFF "  ,"MAL "     ,"INC "    ,"DEC "   ,"SORT "   , // Ursoft
    "INIT " ,"[E3][91]","CLOCK ","OUTSCREEN ","INITLOOP ","SETTRIGGER ","SETSCANTIME ","SETPREHIST ",// BMC MC-12(A)
    "SETFUNCTION ","INFUNCTION ","PLOT ","MULTIMETER ","TRANSREC ","RELAY ","SLEEP ","[E3][9F]",
    "[E3][A0]","BUFINIT ","[E3][A2]","BUFREAD ","BUFOPEN ","BUFWRITE ","LOADBUFFER ","[E3][A7]",
    "[E3][A8]","SELECT " ,"INSCAN ","DBUFINIT ","[E3][AC]","[E3][AD]","COM "    ,"SETCOM " ,
    "[E3][B0]","[E3][B1]","[E3][B2]","[E3][B3]","[E3][B4]","[E3][B5]","[E3][B6]","[E3][B7]",
    "[E3][B8]","[E3][B9]","[E3][BA]","[E3][BB]","[E3][BC]","[E3][BD]","[E3][BE]","[E3][BF]",
    "STATON " ,"STATOFF ","STATCLR ","STATIN " ,"STATOUT ","[E3][C5]","[E3][C6]","[E3][C7]", // Trams4
    "[E3][C8]","[E3][C9]","[E3][CA]","[E3][CB]","[E3][CC]","[E3][CD]","[E3][CE]","[E3][CF]",
    "ENTER "  ,"[E3][D1]","[E3][D2]","[E3][D3]","[E3][D4]","[E3][D5]","[E3][D6]","[E3][D7]",
    "[E3][D8]","[E3][D9]","[E3][DA]","[E3][DB]","[E3][DC]","[E3][DD]","[E3][DE]","[E3][DF]",
    "[E3][E0]","[E3][E1]","[E3][E2]","[E3][E3]","[E3][E4]","[E3][E5]","[E3][E6]","[E3][E7]",
    "[E3][E8]","[E3][E9]","[E3][EA]","[E3][EB]","[E3][EC]","[E3][ED]","[E3][EE]","[E3][EF]",
    "[E3][F0]","[E3][F1]","[E3][F2]","[E3][F3]","[E3][F4]","[E3][F5]","[E3][F6]","[E3][F7]",
    "[E3][F8]","[E3][F9]","[E3][FA]","[E3][FB]","[E3][FC]","[E3][FD]","[E3][FE]","[E3][FF]",
};
static char** CodePc1600_E3b = CodePc1500_E3b ;

static char* CodePc1500_E3[] = { /* Priority CE-1600P, Tramsoft Tools4 */
    "[E3][00]","[E3][01]","SECONDS ","[E3][03]","PRON "   ,"[E3][05]","[E3][06]","[E3][07]", // Ursoft only part of commands
    "[E3][08]","[E3][09]","[E3][0A]","[E3][0B]","[E3][0C]","[E3][0D]","[E3][0E]","[E3][0F]",
    "[E3][10]","[E3][11]","[E3][12]","[E3][13]","[E3][14]","[E3][15]","[E3][16]","[E3][17]",
    "[E3][18]","[E3][19]","[E3][1A]","[E3][1B]","[E3][1C]","[E3][1D]","[E3][1E]","[E3][1F]",
    "[E3][20]","[E3][21]","[E3][22]","[E3][23]","[E3][24]","[E3][25]","[E3][26]","[E3][27]",
    "[E3][28]","[E3][29]","[E3][2A]","[E3][2B]","[E3][2C]","[E3][2D]","[E3][2E]","[E3][2F]",
    "[E3][30]","[E3][31]","[E3][32]","[E3][33]","[E3][34]","[E3][35]","[E3][36]","[E3][37]",
    "[E3][38]","[E3][39]","[E3][3A]","[E3][3B]","[E3][3C]","[E3][3D]","[E3][3E]","[E3][3F]",
    "[E3][40]","[E3][41]","[E3][42]","[E3][43]","[E3][44]","[E3][45]","[E3][46]","[E3][47]",
    "[E3][48]","[E3][49]","[E3][4A]","[E3][4B]","[E3][4C]","[E3][4D]","[E3][4E]","[E3][4F]",
    "AVGX "   ,"AVGY "   ,"CORR "   ,"GRA "    ,"SDNX "   ,"SDNY "   ,"SEG "    ,"SDVX "   , // Trams4
    "SDVY "   ,"[E3][59]","[E3][5A]","[E3][5B]","[E3][5C]","[E3][5D]","ZEIT$ "  ,"ELAST "  , // Trams4
    "CLEN "   ,"ELINE "  ,"CONV "   ,"CONVL$ " ,"CONVS$ " ,"ELIST$ " ,"[E3][66]","[E3][67]", // Trams4: CLEN, ELIST$
    "[E3][68]","[E3][69]","[E3][6A]","[E3][6B]","[E3][6C]","[E3][6D]","[E3][6E]","[E3][6F]",
    "STAT "   ,"STX "    ,"STY "    ,"[E3][73]","[E3][74]","[E3][75]","[E3][76]","[E3][77]", // Trams4
    "[E3][78]","[E3][79]","[E3][7A]","[E3][7B]","[E3][7C]","[E3][7D]","[E3][7E]","[E3][7F]",
    "SWITCH " ,"PAPER "  ,"OUTCHA " ,"REPEAT ","AUTORANGE ","WHILE " ,"INCHA " ,"[E3][87]", // BMCMC12: E381=SCREEN
    "SWAP "  ,"SETRANGE ","MCON "  ,"MCOFF "  ,"MAL "     ,"INC "    ,"DEC     ","SORT "  , // Ursoft
    "INIT " ,"[E3][91]","CLOCK ","OUTSCREEN ","INITLOOP ","SETTRIGGER ","SETSCANTIME ","SETPREHIST ",// BMC MC-12(A)
    "SETFUNCTION ","INFUNCTION ","PLOT ","MULTIMETER ","TRANSREC ","RELAY ","SLEEP ","[E3][9F]",
    "[E3][A0]","BUFINIT ","[E3][A2]","BUFREAD ","BUFOPEN ","BUFWRITE ","LOADBUFFER ","[E3][A7]",
    "[E3][A8]","SELECT " ,"INSCAN ","DBUFINIT ","[E3][AC]","[E3][AD]","COM "    ,"SETCOM " ,
    "[E3][B0]","[E3][B1]","[E3][B2]","[E3][B3]","[E3][B4]","[E3][B5]","[E3][B6]","[E3][B7]",
    "[E3][B8]","[E3][B9]","[E3][BA]","[E3][BB]","[E3][BC]","[E3][BD]","[E3][BE]","[E3][BF]",
    "STATON " ,"STATOFF ","STATCLR ","STATIN " ,"STATOUT ","[E3][C5]","[E3][C6]","[E3][C7]", // Trams4
    "[E3][C8]","[E3][C9]","[E3][CA]","[E3][CB]","[E3][CC]","[E3][CD]","[E3][CE]","[E3][CF]",
    "ENTER "  ,"[E3][D1]","[E3][D2]","[E3][D3]","[E3][D4]","[E3][D5]","[E3][D6]","[E3][D7]",
    "[E3][D8]","[E3][D9]","[E3][DA]","[E3][DB]","[E3][DC]","[E3][DD]","[E3][DE]","[E3][DF]",
    "[E3][E0]","[E3][E1]","[E3][E2]","[E3][E3]","[E3][E4]","[E3][E5]","[E3][E6]","[E3][E7]",
    "[E3][E8]","[E3][E9]","[E3][EA]","[E3][EB]","[E3][EC]","[E3][ED]","[E3][EE]","[E3][EF]",
    "[E3][F0]","[E3][F1]","[E3][F2]","[E3][F3]","[E3][F4]","[E3][F5]","[E3][F6]","[E3][F7]",
    "[E3][F8]","[E3][F9]","[E3][FA]","[E3][FB]","[E3][FC]","[E3][FD]","[E3][FE]","[E3][FF]",
};
static char** CodePc1600_E3 = CodePc1500_E3 ;

static char* CodePc1500_E6[] = {
    "[E6][00]","[E6][01]","[E6][02]","[E6][03]","[E6][04]","[E6][05]","[E6][06]","[E6][07]",
    "[E6][08]","[E6][09]","[E6][0A]","[E6][0B]","[E6][0C]","[E6][0D]","[E6][0E]","[E6][0F]",
    "[E6][10]","[E6][11]","[E6][12]","[E6][13]","[E6][14]","[E6][15]","[E6][16]","[E6][17]",
    "[E6][18]","[E6][19]","[E6][1A]","[E6][1B]","[E6][1C]","[E6][1D]","[E6][1E]","[E6][1F]",
    "[E6][20]","[E6][21]","[E6][22]","[E6][23]","[E6][24]","[E6][25]","[E6][26]","[E6][27]",
    "[E6][28]","[E6][29]","[E6][2A]","[E6][2B]","[E6][2C]","[E6][2D]","[E6][2E]","[E6][2F]",
    "[E6][30]","[E6][31]","[E6][32]","[E6][33]","[E6][34]","[E6][35]","[E6][36]","[E6][37]",
    "[E6][38]","[E6][39]","[E6][3A]","[E6][3B]","[E6][3C]","[E6][3D]","[E6][3E]","[E6][3F]",
    "[E6][40]","[E6][41]","[E6][42]","[E6][43]","[E6][44]","[E6][45]","[E6][46]","[E6][47]",
    "[E6][48]","[E6][49]","[E6][4A]","[E6][4B]","[E6][4C]","[E6][4D]","[E6][4E]","[E6][4F]",
    "[E6][50]","[E6][51]","[E6][52]","[E6][53]","[E6][54]","[E6][55]","[E6][56]","[E6][57]",
    "[E6][58]","[E6][59]","[E6][5A]","[E6][5B]","[E6][5C]","[E6][5D]","[E6][5E]","[E6][5F]",
    "[E6][60]","[E6][61]","[E6][62]","[E6][63]","[E6][64]","[E6][65]","[E6][66]","[E6][67]",
    "[E6][68]","[E6][69]","[E6][6A]","[E6][6B]","[E6][6C]","[E6][6D]","[E6][6E]","[E6][6F]",
    "[E6][70]","[E6][71]","[E6][72]","[E6][73]","[E6][74]","[E6][75]","[E6][76]","[E6][77]",
    "[E6][78]","[E6][79]","[E6][7A]","[E6][7B]","[E6][7C]","[E6][7D]","[E6][7E]","[E6][7F]",
    "CSIZE "  ,"GRAPH " ,"GLCURSOR ","LCURSOR ","SORGN "  ,"ROTATE " ,"TEXT "   ,"[E6][87]", //CE-150
    "[E6][88]","[E6][89]","[E6][8A]","[E6][8B]","[E6][8C]","[E6][8D]","[E6][8E]","[E6][8F]",
    "[E6][90]","[E6][91]","[E6][92]","[E6][93]","[E6][94]","[E6][95]","[E6][96]","[E6][97]",
    "[E6][98]","[E6][99]","[E6][9A]","[E6][9B]","[E6][9C]","[E6][9D]","[E6][9E]","[E6][9F]",
    "[E6][A0]","[E6][A1]","[E6][A2]","[E6][A3]","[E6][A4]","[E6][A5]","[E6][A6]","[E6][A7]",
    "[E6][A8]","[E6][A9]","[E6][AA]","[E6][AB]","[E6][AC]","[E6][AD]","[E6][AE]","[E6][AF]",
    "[E6][B0]","[E6][B1]","[E6][B2]","[E6][B3]","[E6][B4]","[E6][B5]","[E6][B6]","[E6][B7]",
    "[E6][B8]","[E6][B9]","[E6][BA]","[E6][BB]","[E6][BC]","[E6][BD]","[E6][BE]","[E6][BF]",
    "[E6][C0]","[E6][C1]","[E6][C2]","[E6][C3]","[E6][C4]","[E6][C5]","[E6][C6]","[E6][C7]",
    "[E6][C8]","[E6][C9]","[E6][CA]","[E6][CB]","[E6][CC]","[E6][CD]","[E6][CE]","[E6][CF]",
    "[E6][D0]","[E6][D1]","[E6][D2]","[E6][D3]","[E6][D4]","[E6][D5]","[E6][D6]","[E6][D7]",
    "[E6][D8]","[E6][D9]","[E6][DA]","[E6][DB]","[E6][DC]","[E6][DD]","[E6][DE]","[E6][DF]",
    "[E6][E0]","[E6][E1]","[E6][E2]","[E6][E3]","[E6][E4]","[E6][E5]","[E6][E6]","[E6][E7]",
    "[E6][E8]","[E6][E9]","[E6][EA]","[E6][EB]","[E6][EC]","[E6][ED]","[E6][EE]","[E6][EF]",
    "[E6][F0]","[E6][F1]","[E6][F2]","[E6][F3]","[E6][F4]","[E6][F5]","[E6][F6]","[E6][F7]",
    "[E6][F8]","[E6][F9]","[E6][FA]","[E6][FB]","[E6][FC]","[E6][FD]","[E6][FE]","[E6][FF]",
};
static char** CodePc1600_E6 = CodePc1500_E6 ;

static char* CodePc1500_E7[] = { /*E7: RMT */
    "[E7][00]","[E7][01]","[E7][02]","[E7][03]","[E7][04]","[E7][05]","[E7][06]","[E7][07]",
    "[E7][08]","[E7][09]","[E7][0A]","[E7][0B]","[E7][0C]","[E7][0D]","[E7][0E]","[E7][0F]",
    "[E7][10]","[E7][11]","[E7][12]","[E7][13]","[E7][14]","[E7][15]","[E7][16]","[E7][17]",
    "[E7][18]","[E7][19]","[E7][1A]","[E7][1B]","[E7][1C]","[E7][1D]","[E7][1E]","[E7][1F]",
    "[E7][20]","[E7][21]","[E7][22]","[E7][23]","[E7][24]","[E7][25]","[E7][26]","[E7][27]",
    "[E7][28]","[E7][29]","[E7][2A]","[E7][2B]","[E7][2C]","[E7][2D]","[E7][2E]","[E7][2F]",
    "[E7][30]","[E7][31]","[E7][32]","[E7][33]","[E7][34]","[E7][35]","[E7][36]","[E7][37]",
    "[E7][38]","[E7][39]","[E7][3A]","[E7][3B]","[E7][3C]","[E7][3D]","[E7][3E]","[E7][3F]",
    "[E7][40]","[E7][41]","[E7][42]","[E7][43]","[E7][44]","[E7][45]","[E7][46]","[E7][47]",
    "[E7][48]","[E7][49]","[E7][4A]","[E7][4B]","[E7][4C]","[E7][4D]","[E7][4E]","[E7][4F]",
    "[E7][50]","[E7][51]","[E7][52]","[E7][53]","[E7][54]","[E7][55]","[E7][56]","[E7][57]",
    "[E7][58]","[E7][59]","[E7][5A]","[E7][5B]","[E7][5C]","[E7][5D]","[E7][5E]","[E7][5F]",
    "[E7][60]","[E7][61]","[E7][62]","[E7][63]","[E7][64]","[E7][65]","[E7][66]","[E7][67]",
    "[E7][68]","[E7][69]","[E7][6A]","[E7][6B]","[E7][6C]","[E7][6D]","[E7][6E]","[E7][6F]",
    "[E7][70]","[E7][71]","[E7][72]","[E7][73]","[E7][74]","[E7][75]","[E7][76]","[E7][77]",
    "[E7][78]","[E7][79]","[E7][7A]","[E7][7B]","[E7][7C]","[E7][7D]","[E7][7E]","[E7][7F]",
    "[E7][80]","[E7][81]","[E7][82]","[E7][83]","[E7][84]","[E7][85]","[E7][86]","[E7][87]",
    "[E7][88]","[E7][89]","[E7][8A]","[E7][8B]","[E7][8C]","[E7][8D]","[E7][8E]","[E7][8F]",
    "[E7][90]","[E7][91]","[E7][92]","[E7][93]","[E7][94]","[E7][95]","[E7][96]","[E7][97]",
    "[E7][98]","[E7][99]","[E7][9A]","[E7][9B]","[E7][9C]","[E7][9D]","[E7][9E]","[E7][9F]",
    "[E7][A0]","[E7][A1]","[E7][A2]","[E7][A3]","[E7][A4]","[E7][A5]","[E7][A6]","[E7][A7]",
    "[E7][A8]","RMT "    ,"[E7][AA]","[E7][AB]","[E7][AC]","[E7][AD]","[E7][AE]","[E7][AF]", // PMT? TRM S.158
    "[E7][B0]","[E7][B1]","[E7][B2]","[E7][B3]","[E7][B4]","[E7][B5]","[E7][B6]","[E7][B7]",
    "[E7][B8]","[E7][B9]","[E7][BA]","[E7][BB]","[E7][BC]","[E7][BD]","[E7][BE]","[E7][BF]",
    "[E7][C0]","[E7][C1]","[E7][C2]","[E7][C3]","[E7][C4]","[E7][C5]","[E7][C6]","[E7][C7]",
    "[E7][C8]","[E7][C9]","[E7][CA]","[E7][CB]","[E7][CC]","[E7][CD]","[E7][CE]","[E7][CF]",
    "[E7][D0]","[E7][D1]","[E7][D2]","[E7][D3]","[E7][D4]","[E7][D5]","[E7][D6]","[E7][D7]",
    "[E7][D8]","[E7][D9]","[E7][DA]","[E7][DB]","[E7][DC]","[E7][DD]","[E7][DE]","[E7][DF]",
    "[E7][E0]","[E7][E1]","[E7][E2]","[E7][E3]","[E7][E4]","[E7][E5]","[E7][E6]","[E7][E7]",
    "[E7][E8]","[E7][E9]","[E7][EA]","[E7][EB]","[E7][EC]","[E7][ED]","[E7][EE]","[E7][EF]",
    "[E7][F0]","[E7][F1]","[E7][F2]","[E7][F3]","[E7][F4]","[E7][F5]","[E7][F6]","[E7][F7]",
    "[E7][F8]","[E7][F9]","[E7][FA]","[E7][FB]","[E7][FC]","[E7][FD]","[E7][FE]","[E7][FF]",
};
static char** CodePc1600_E7 = CodePc1500_E7 ;

static char* CodePc1500_E8[] = {
    "[E8][00]","[E8][01]","[E8][02]","[E8][03]","[E8][04]","[E8][05]","[E8][06]","[E8][07]",
    "[E8][08]","[E8][09]","[E8][0A]","[E8][0B]","[E8][0C]","[E8][0D]","[E8][0E]","[E8][0F]",
    "[E8][10]","[E8][11]","[E8][12]","[E8][13]","[E8][14]","[E8][15]","[E8][16]","[E8][17]",
    "[E8][18]","[E8][19]","[E8][1A]","[E8][1B]","[E8][1C]","[E8][1D]","[E8][1E]","[E8][1F]",
    "[E8][20]","[E8][21]","[E8][22]","[E8][23]","[E8][24]","[E8][25]","[E8][26]","[E8][27]",
    "[E8][28]","[E8][29]","[E8][2A]","[E8][2B]","[E8][2C]","[E8][2D]","[E8][2E]","[E8][2F]",
    "[E8][30]","[E8][31]","[E8][32]","[E8][33]","[E8][34]","[E8][35]","[E8][36]","[E8][37]",
    "[E8][38]","[E8][39]","[E8][3A]","[E8][3B]","[E8][3C]","[E8][3D]","[E8][3E]","[E8][3F]",
    "[E8][40]","[E8][41]","[E8][42]","[E8][43]","[E8][44]","[E8][45]","[E8][46]","[E8][47]",
    "[E8][48]","[E8][49]","[E8][4A]","[E8][4B]","[E8][4C]","[E8][4D]","[E8][4E]","[E8][4F]",
    "[E8][50]","[E8][51]","[E8][52]","[E8][53]","[E8][54]","[E8][55]","[E8][56]","DEV$ "   ,
    "COM$ "   ,"INSTAT " ,"RINKEY$ ","[E8][5B]","[E8][5C]","[E8][5D]","[E8][5E]","[E8][5F]",
    "[E8][60]","[E8][61]","[E8][62]","[E8][63]","[E8][64]","[E8][65]","[E8][66]","[E8][67]",
    "[E8][68]","[E8][69]","[E8][6A]","[E8][6B]","[E8][6C]","[E8][6D]","[E8][6E]","[E8][6F]",
    "[E8][70]","[E8][71]","[E8][72]","[E8][73]","[E8][74]","[E8][75]","[E8][76]","[E8][77]",
    "[E8][78]","[E8][79]","[E8][7A]","[E8][7B]","[E8][7C]","[E8][7D]","[E8][7E]","[E8][7F]",
    "OUTSTAT ","[E8][81]","SETCOM " ,"TERMINAL ","DTE "   ,"TRANSMIT ","SETDEV ","[E8][87]", // CE-158A
    "[E8][88]","[E8][89]","[E8][8A]","[E8][8B]","[E8][8C]","[E8][8D]","[E8][8E]","[E8][8F]",
    "[E8][90]","[E8][91]","[E8][92]","[E8][93]","[E8][94]","[E8][95]","[E8][96]","[E8][97]",
    "[E8][98]","[E8][99]","[E8][9A]","[E8][9B]","[E8][9C]","[E8][9D]","[E8][9E]","[E8][9F]",
    "[E8][A0]","[E8][A1]","[E8][A2]","[E8][A3]","[E8][A4]","[E8][A5]","[E8][A6]","[E8][A7]",
    "[E8][A8]","[E8][A9]","[E8][AA]","[E8][AB]","[E8][AC]","[E8][AD]","[E8][AE]","[E8][AF]",
    "[E8][B0]","[E8][B1]","[E8][B2]","[E8][B3]","[E8][B4]","[E8][B5]","[E8][B6]","[E8][B7]",
    "[E8][B8]","[E8][B9]","[E8][BA]","[E8][BB]","[E8][BC]","[E8][BD]","[E8][BE]","[E8][BF]",
    "[E8][C0]","[E8][C1]","[E8][C2]","[E8][C3]","[E8][C4]","[E8][C5]","[E8][C6]","[E8][C7]",
    "[E8][C8]","[E8][C9]","[E8][CA]","[E8][CB]","[E8][CC]","[E8][CD]","[E8][CE]","[E8][CF]",
    "[E8][D0]","[E8][D1]","[E8][D2]","[E8][D3]","[E8][D4]","[E8][D5]","[E8][D6]","[E8][D7]",
    "[E8][D8]","[E8][D9]","[E8][DA]","[E8][DB]","[E8][DC]","[E8][DD]","[E8][DE]","[E8][DF]",
    "[E8][E0]","[E8][E1]","[E8][E2]","[E8][E3]","[E8][E4]","[E8][E5]","[E8][E8]","[E8][E7]",
    "[E8][E8]","[E8][E9]","[E8][EA]","[E8][EB]","[E8][EC]","[E8][ED]","[E8][EE]","[E8][EF]",
    "[E8][F0]","[E8][F1]","[E8][F2]","[E8][F3]","[E8][F4]","[E8][F5]","[E8][F6]","[E8][F7]",
    "[E8][F8]","[E8][F9]","[E8][FA]","[E8][FB]","[E8][FC]","[E8][FD]","[E8][FE]","[E8][FF]",
};
static char** CodePc1600_E8 = CodePc1500_E8 ;

static char* CodePc1500_F0[] = {
    "[F0][00]","[F0][01]","[F0][02]","[F0][03]","[F0][04]","[F0][05]","[F0][06]","[F0][07]",
    "[F0][08]","[F0][09]","[F0][0A]","[F0][0B]","[F0][0C]","[F0][0D]","[F0][0E]","[F0][0F]",
    "[F0][10]","[F0][11]","[F0][12]","[F0][13]","[F0][14]","[F0][15]","[F0][16]","[F0][17]",
    "[F0][18]","[F0][19]","[F0][1A]","[F0][1B]","[F0][1C]","[F0][1D]","[F0][1E]","[F0][1F]",
    "[F0][20]","[F0][21]","[F0][22]","[F0][23]","[F0][24]","[F0][25]","[F0][26]","[F0][27]",
    "[F0][28]","[F0][29]","[F0][2A]","[F0][2B]","[F0][2C]","[F0][2D]","[F0][2E]","[F0][2F]",
    "[F0][30]","[F0][31]","[F0][32]","[F0][33]","[F0][34]","[F0][35]","[F0][36]","[F0][37]",
    "[F0][38]","[F0][39]","[F0][3A]","[F0][3B]","[F0][3C]","[F0][3D]","[F0][3E]","[F0][3F]",
    "[F0][40]","[F0][41]","[F0][42]","[F0][43]","[F0][44]","[F0][45]","[F0][46]","[F0][47]",
    "[F0][48]","[F0][49]","[F0][4A]","[F0][4B]","[F0][4C]","[F0][4D]","[F0][4E]","[F0][4F]",
    "VPCURSOR ","[F0][51]","ERN "   ,"ERL "   ,"HCURSOR ","HPCURSOR ","VCURSOR ","[F0][57]", // Tramsoft3
    "[F0][58]","[F0][59]","[F0][5A]","[F0][5B]","[F0][5C]","[F0][5D]","TTIME$ " ,"DATE$ "  , // JK tools
    "FRAC "   ,"SPACE$ " ,"HEX$ "   ,"[F0][63]","[F0][64]","[F0][65]","[F0][66]","[F0][67]",
    "[F0][68]","[F0][69]","[F0][6A]","[F0][6B]","[F0][6C]","[F0][6D]","[F0][6E]","FN "     ,
    "DEC "    ,"HEX$ "   ,"[F0][72]","[F0][73]","[F0][74]","FAC "    ,"[F0][76]","[F0][77]", // Tramsoft3
    "[F0][78]","[F0][79]","NAME$ "  ,"DEEK "   ,"ROUND " ,"INTEGRAL ","[F0][7E]","[F0][7F]",
    "QLOAD "  ,"QSAVE "  ,"[F0][82]","QVERIFY ","CURSOR " ,"USING "  ,"[F0][86]","WIDTH "  , // [F0][82] QCHAIN, PC-1600: LOAD, SAVE, WIDTH
    "CLS "    ,"CLOAD "  ,"[F0][8A]","[F0][8B]","[F0][8C]","[F0][8D]","[F0][8E]","MERGE "  ,
    "LIST "   ,"INPUT "  ,"GCURSOR ","GCURSOR ","[F0][94]","CSAVE "  ,"[F0][96]","PRINT "  , // PC-1600: GCURSOR 92
    "FILES "  ,"LINE "   ,"PRESET " ,"PSET "   ,"[F0][9C]","[F0][9D]","[F0][9E]","GPRINT " , // PC-1600: 90-9B
    "BYE "    ,"CATALOG ","CHECK "  ,"COPY "   ,"PITCH "  ,"LCURSOR ","INPT "   ,"MOVE "   , // PC-1600 LFILES
    "SEARCH " ,"RMT "    ,"SORT "   ,"DOKE "   ,"RPU "    ,"SPU "    ,"PURGE "  ,"GSB "    , // RWErelics
    "FEED "   ,"CONSOLE ","CHAIN "  ,"BREAK "  ,"ZONE "   ,"COLOR "  ,"LF "     ,"LINE "   , // PC-1600: BREAK, LINE->LLINE
    "LLIST "  ,"LPRINT " ,"RLINE "  ,"TAB "    ,"TEST "   ,"[F0][BD]","[F0][BE]","[F0][BF]",
    "APPEND " ,"CHANGE " ,"REPKEY " ,"ERASE "  ,"FIND "   ,"KEEP "   ,"PLIST "  ,"PROGRAM ", // Tramsoft1 [F0C3]: DELETE
    "RENUMBER ","PLAST " ,"LINK "   ,"SPLIT "  ,"IF# "    ,"ENDIF "  ,"EXIT "   ,"ELSE "   , // RVS PC-BASIC 84
    "SELECT ","ENDSELECT ","DEFFN " ,"CASE "   ,"DO "     ,"LOOP "   ,"WHILE "  ,"[F0][D7]",
    "SUB "    ,"SUBEND " ,"SUBCLR " ,"[F0][DB]","[F0][DC]","[F0][DD]","EDIT "   ,"MODE "   ,
    "DIR "    ,"GCLS "   ,"KEY "    ,"[F0][E3]","[F0][E4]","[F0][E5]","[F0][E6]","SLEEP "  , // IWS
    "[F0][E8]","[F0][E9]","[F0][EA]","[F0][EB]","[F0][EC]","[F0][ED]","[F0][EE]","[F0][EF]",
    "[F0][F0]","[F0][F1]","[F0][F2]","[F0][F3]","[F0][F4]","[F0][F5]","[F0][F6]","[F0][F7]",
    "[F0][F8]","[F0][F9]","[F0][FA]","RVSLOAD ","POSTLOAD ","[F0][FD]","[F0][FE]","[F0][FF]",// BMCMC12A
};

static char* CodePc1600_F0[] = {
    "[F0][00]","[F0][01]","[F0][02]","[F0][03]","[F0][04]","[F0][05]","[F0][06]","[F0][07]",
    "[F0][08]","[F0][09]","[F0][0A]","[F0][0B]","[F0][0C]","[F0][0D]","[F0][0E]","[F0][0F]",
    "[F0][10]","[F0][11]","[F0][12]","[F0][13]","[F0][14]","[F0][15]","[F0][16]","[F0][17]",
    "[F0][18]","[F0][19]","[F0][1A]","[F0][1B]","[F0][1C]","[F0][1D]","[F0][1E]","[F0][1F]",
    "[F0][20]","[F0][21]","[F0][22]","[F0][23]","[F0][24]","[F0][25]","[F0][26]","[F0][27]",
    "[F0][28]","[F0][29]","[F0][2A]","[F0][2B]","[F0][2C]","[F0][2D]","[F0][2E]","[F0][2F]",
    "[F0][30]","[F0][31]","[F0][32]","[F0][33]","[F0][34]","[F0][35]","[F0][36]","[F0][37]",
    "[F0][38]","[F0][39]","[F0][3A]","[F0][3B]","[F0][3C]","[F0][3D]","[F0][3E]","[F0][3F]",
    "[F0][40]","[F0][41]","[F0][42]","[F0][43]","[F0][44]","[F0][45]","[F0][46]","[F0][47]",
    "[F0][48]","[F0][49]","[F0][4A]","[F0][4B]","[F0][4C]","[F0][4D]","[F0][4E]","[F0][4F]",
    "VPCURSOR ","[F0][51]","ERN "   ,"ERL "   ,"HCURSOR ","HPCURSOR ","VCURSOR ","[F0][57]", // Tramsoft3
    "[F0][58]","[F0][59]","[F0][5A]","[F0][5B]","[F0][5C]","[F0][5D]","[F0][5E]","[F0][5F]",
    "[F0][60]","SPACE$ " ,"[F0][62]","[F0][63]","[F0][64]","[F0][65]","[F0][66]","[F0][67]",
    "[F0][68]","[F0][69]","[F0][6A]","[F0][6B]","[F0][6C]","[F0][6D]","[F0][6E]","[F0][6F]",
    "DEC "    ,"HEX$ "   ,"[F0][72]","[F0][73]","[F0][74]","[F0][75]","[F0][76]","[F0][77]", // Tramsoft3
    "[F0][78]","[F0][79]","[F0][7A]","[F0][7B]","[F0][7C]","[F0][7D]","[F0][7E]","[F0][7F]",
    "[F0][80]","[F0][81]","[F0][82]","[F0][83]","CURSOR " ,"USING "  ,"[F0][86]","WIDTH "  ,
    "CLS "    ,"CLOAD "  ,"[F0][8A]","[F0][8B]","[F0][8C]","[F0][8D]","[F0][8E]","MERGE "  ,
    "LIST "   ,"INPUT "  ,"GCURSOR ","GCURSOR ","[F0][94]","CSAVE "  ,"[F0][96]","PRINT "  , // PC-1500: GCURSOR 93
    "FILES "  ,"LINE "   ,"PRESET " ,"PSET "   ,"[F0][9C]","[F0][9D]","[F0][9E]","GPRINT " ,
    "LFILES " ,"[F0][A1]","[F0][A2]","[F0][A3]","PITCH "  ,"LCURSOR ","[F0][A6]","[F0][A7]", // PC-1500 BYE
    "[F0][A8]","RMT "    ,"[F0][AA]","[F0][AB]","[F0][AC]","[F0][AD]","[F0][AE]","[F0][AF]",
    "FEED "   ,"CONSOLE ","CHAIN "  ,"BREAK "  ,"ZONE "   ,"COLOR "  ,"LF "     ,"LLINE "  , // PC-1500: BREAK, LLINE->LINE
    "LLIST "  ,"LPRINT " ,"RLINE "  ,"TAB "    ,"TEST "   ,"[F0][BD]","[F0][BE]","[F0][BF]",
    "APPEND " ,"CHANGE " ,"DELETE " ,"ERASE "  ,"FIND "   ,"KEEP "   ,"PLIST "  ,"PROGRAM ", // Tramsoft1, IWS[F0C3]: REPKEY
    "RENUMBER ","PLAST " ,"LINK "   ,"SPLIT "  ,"[F0][CC]","[F0][CD]","[F0][CE]","[F0][CF]",
    "[F0][D0]","[F0][D1]","[F0][D2]","[F0][D3]","[F0][D4]","[F0][D5]","[F0][D6]","[F0][D7]",
    "[F0][D8]","[F0][D9]","[F0][DA]","[F0][DB]","[F0][DC]","[F0][DD]","[F0][DE]","MODE "   ,
    "[F0][E0]","GCLS "   ,"KEY "    ,"[F0][E3]","[F0][E4]","[F0][E5]","[F0][E6]","SLEEP "  ,
    "[F0][E8]","[F0][E9]","[F0][EA]","[F0][EB]","[F0][EC]","[F0][ED]","[F0][EE]","[F0][EF]",
    "[F0][F0]","[F0][F1]","[F0][F2]","[F0][F3]","[F0][F4]","[F0][F5]","[F0][F6]","[F0][F7]",
    "[F0][F8]","[F0][F9]","[F0][FA]","RVSLOAD ","POSTLOAD ","[F0][FD]","[F0][FE]","[F0][FF]",// BMCMC12A
};

static char* CodePc1500_F1[] = {
    "[F1][00]","[F1][01]","[F1][02]","[F1][03]","[F1][04]","[F1][05]","[F1][06]","[F1][07]",
    "[F1][08]","[F1][09]","[F1][0A]","[F1][0B]","[F1][0C]","[F1][0D]","[F1][0E]","[F1][0F]",
    "[F1][10]","[F1][11]","[F1][12]","[F1][13]","[F1][14]","[F1][15]","[F1][16]","[F1][17]",
    "[F1][18]","[F1][19]","[F1][1A]","[F1][1B]","[F1][1C]","[F1][1D]","[F1][1E]","[F1][1F]",
    "[F1][20]","[F1][21]","[F1][22]","[F1][23]","[F1][24]","[F1][25]","[F1][26]","[F1][27]",
    "[F1][28]","[F1][29]","[F1][2A]","[F1][2B]","[F1][2C]","[F1][2D]","[F1][2E]","[F1][2F]",
    "[F1][30]","[F1][31]","[F1][32]","[F1][33]","[F1][34]","[F1][35]","[F1][36]","[F1][37]",
    "[F1][38]","[F1][39]","[F1][3A]","[F1][3B]","[F1][3C]","[F1][3D]","[F1][3E]","[F1][3F]",
    "[F1][40]","[F1][41]","[F1][42]","[F1][43]","[F1][44]","[F1][45]","[F1][46]","[F1][47]",
    "[F1][48]","[F1][49]","[F1][4A]","[F1][4B]","[F1][4C]","[F1][4D]","[F1][4E]","[F1][4F]",
    " AND "   ," OR "    ,"[F1][52]","[F1][53]","[F1][54]","[F1][55]","[F1][56]","[F1][57]",
    "MEM "    ,"[F1][59]","[F1][5A]","TIME "   ,"INKEY$ " ,"PI "     ,"[F1][5E]","[F1][5F]",
    "ASC "    ,"STR$ "   ,"VAL "    ,"CHR$ "   ,"LEN "    ,"DEG "    ,"DMS "    ,"STATUS " ,
    "POINT "  ,"[F1][69]","[F1][6A]","SQR "    ,"[F1][6C]","NOT "    ,"PEEK# "  ,"PEEK "   , //PC-1600: XPEEK...
    "ABS "    ,"INT "    ,"RIGHT$ " ,"ASN "    ,"ACS "    ,"ATN "    ,"LN "     ,"LOG "    ,
    "EXP "    ,"SGN "    ,"LEFT$ "  ,"MID$ "   ,"RND "    ,"SIN "    ,"COS "    ,"TAN "    ,
    "AREAD "  ,"ARUN "   ,"BEEP "   ,"CONT "   ,"[F1][84]","[F1][85]","GRAD "   ,"CLEAR "  ,
    "[F1][88]","[F1][89]","CALL "   ,"DIM "    ,"DEGREE " ,"DATA "   ,"END"     ,"[F1][8F]", //PC-1600: XCALL...
    "[F1][90]","[F1][91]","GOTO "   ,"[F1][93]","GOSUB "  ,"[F1][95]","IF "     ,"[F1][97]",
    "LET "    ,"RETURN " ,"NEXT "   ,"NEW "    ,"ON "     ,"OPN "    ,"OFF "    ,"[F1][9F]",
    "POKE# "  ,"POKE "   ,"PAUSE "  ,"[F1][A3]","RUN "    ,"FOR "    ,"READ "   ,"RESTORE ", //[F1][A3]"P    ", PC-1600: XPOKE...
    "RANDOM " ,"[F1][A9]","RADIAN " ,"REM "    ,"STOP "   ," STEP "  ," THEN "  ,"TRON "   ,
    "TROFF "  ," TO "    ,"[F1][B2]","WAIT "   ,"ERROR "  ,"LOCK "   ,"UNLOCK " ,"[F1][B7]",
    "[F1][B8]","[F1][B9]","[F1][BA]","[F1][BB]","[F1][BC]","[F1][BD]","[F1][BE]","[F1][BF]",
    "[F1][C0]","[F1][C1]","[F1][C2]","[F1][C3]","[F1][C4]","[F1][C5]","[F1][C6]","[F1][C7]",
    "[F1][C8]","[F1][C9]","[F1][CA]","[F1][CB]","[F1][CC]","[F1][CD]","[F1][CE]","[F1][CF]",
    "[F1][D0]","[F1][D1]","[F1][D2]","[F1][D3]","[F1][D4]","[F1][D5]","[F1][D6]","[F1][D7]",
    "[F1][D8]","[F1][D9]","[F1][DA]","[F1][DB]","[F1][DC]","[F1][DD]","[F1][DE]","[F1][DF]",
    "[F1][E0]","[F1][E1]","[F1][E2]","[F1][E3]","[F1][E4]","[F1][E5]","[F1][E6]","[F1][E7]",
    "[F1][E8]","[F1][E9]","[F1][EA]","[F1][EB]","[F1][EC]","[F1][ED]","[F1][EE]","[F1][EF]",
    "[F1][F0]","[F1][F1]","[F1][F2]","[F1][F3]","[F1][F4]","[F1][F5]","[F1][F6]","[F1][F7]",
    "[F1][F8]","[F1][F9]","[F1][FA]","[F1][FB]","[F1][FC]","[F1][FD]","[F1][FE]","[F1][FF]",
};

static char* CodePc1600_F1[] = {
    "[F1][00]","[F1][01]","[F1][02]","[F1][03]","[F1][04]","[F1][05]","[F1][06]","[F1][07]",
    "[F1][08]","[F1][09]","[F1][0A]","[F1][0B]","[F1][0C]","[F1][0D]","[F1][0E]","[F1][0F]",
    "[F1][10]","[F1][11]","[F1][12]","[F1][13]","[F1][14]","[F1][15]","[F1][16]","[F1][17]",
    "[F1][18]","[F1][19]","[F1][1A]","[F1][1B]","[F1][1C]","[F1][1D]","[F1][1E]","[F1][1F]",
    "[F1][20]","[F1][21]","[F1][22]","[F1][23]","[F1][24]","[F1][25]","[F1][26]","[F1][27]",
    "[F1][28]","[F1][29]","[F1][2A]","[F1][2B]","[F1][2C]","[F1][2D]","[F1][2E]","[F1][2F]",
    "[F1][30]","[F1][31]","[F1][32]","[F1][33]","[F1][34]","[F1][35]","[F1][36]","[F1][37]",
    "[F1][38]","[F1][39]","[F1][3A]","[F1][3B]","[F1][3C]","[F1][3D]","[F1][3E]","[F1][3F]",
    "[F1][40]","[F1][41]","[F1][42]","[F1][43]","[F1][44]","[F1][45]","[F1][46]","[F1][47]",
    "[F1][48]","[F1][49]","[F1][4A]","[F1][4B]","[F1][4C]","[F1][4D]","[F1][4E]","[F1][4F]",
    " AND "   ," OR "    ,"[F1][52]","[F1][53]","[F1][54]","[F1][55]","[F1][56]","[F1][57]",
    "MEM "    ,"[F1][59]","[F1][5A]","TIME "   ,"INKEY$ " ,"PI "     ,"[F1][5E]","[F1][5F]",
    "ASC "    ,"STR$ "   ,"VAL "    ,"CHR$ "   ,"LEN "    ,"DEG "    ,"DMS "    ,"STATUS " ,
    "POINT "  ,"[F1][69]","[F1][6A]","SQR "    ,"[F1][6C]","NOT "    ,"XPEEK# " ,"XPEEK "  , //PC-1500: PEEK#, PEEK
    "ABS "    ,"INT "    ,"RIGHT$ " ,"ASN "    ,"ACS "    ,"ATN "    ,"LN "     ,"LOG "    ,
    "EXP "    ,"SGN "    ,"LEFT$ "  ,"MID$ "   ,"RND "    ,"SIN "    ,"COS "    ,"TAN "    ,
    "AREAD "  ,"ARUN "   ,"BEEP "   ,"CONT "   ,"[F1][84]","[F1][85]","GRAD "   ,"CLEAR "  ,
    "[F1][88]","[F1][89]","XCALL "  ,"DIM "    ,"DEGREE " ,"DATA "   ,"END"     ,"[F1][8F]", //PC-1500: CALL
    "[F1][90]","[F1][91]","GOTO "   ,"[F1][93]","GOSUB "  ,"[F1][95]","IF "     ,"[F1][97]",
    "LET "    ,"RETURN " ,"NEXT "   ,"NEW "    ,"ON "     ,"OPN "    ,"OFF "    ,"[F1][9F]",
    "XPOKE# " ,"XPOKE "  ,"PAUSE "  ,"[F1][A3]","RUN "    ,"FOR "    ,"READ "   ,"RESTORE ", //PC-1500: POKE
    "RANDOM " ,"[F1][A9]","RADIAN " ,"REM "    ,"STOP "   ," STEP "  ," THEN "  ,"TRON "   ,
    "TROFF "  ," TO "    ,"[F1][B2]","WAIT "   ,"ERROR "  ,"LOCK "   ,"UNLOCK " ,"[F1][B7]",
    "[F1][B8]","[F1][B9]","[F1][BA]","[F1][BB]","[F1][BC]","[F1][BD]","[F1][BE]","[F1][BF]",
    "[F1][C0]","[F1][C1]","[F1][C2]","[F1][C3]","[F1][C4]","[F1][C5]","[F1][C6]","[F1][C7]",
    "[F1][C8]","[F1][C9]","[F1][CA]","[F1][CB]","[F1][CC]","[F1][CD]","[F1][CE]","[F1][CF]",
    "[F1][D0]","[F1][D1]","[F1][D2]","[F1][D3]","[F1][D4]","[F1][D5]","[F1][D6]","[F1][D7]",
    "[F1][D8]","[F1][D9]","[F1][DA]","[F1][DB]","[F1][DC]","[F1][DD]","[F1][DE]","[F1][DF]",
    "[F1][E0]","[F1][E1]","[F1][E2]","[F1][E3]","[F1][E4]","[F1][E5]","[F1][E6]","[F1][E7]",
    "[F1][E8]","[F1][E9]","[F1][EA]","[F1][EB]","[F1][EC]","[F1][ED]","[F1][EE]","[F1][EF]",
    "[F1][F0]","[F1][F1]","[F1][F2]","[F1][F3]","[F1][F4]","[F1][F5]","[F1][F6]","[F1][F7]",
    "[F1][F8]","[F1][F9]","[F1][FA]","[F1][FB]","[F1][FC]","[F1][FD]","[F1][FE]","[F1][FF]",
};

static char* CodePc1600_F2[] = {
    "[F2][00]","[F2][01]","[F2][02]","[F2][03]","[F2][04]","[F2][05]","[F2][06]","[F2][07]",
    "[F2][08]","[F2][09]","[F2][0A]","[F2][0B]","[F2][0C]","[F2][0D]","[F2][0E]","[F2][0F]",
    "[F2][10]","[F2][11]","[F2][12]","[F2][13]","[F2][14]","[F2][15]","[F2][16]","[F2][17]",
    "[F2][18]","[F2][19]","[F2][1A]","[F2][1B]","[F2][1C]","[F2][1D]","[F2][1E]","[F2][1F]",
    "[F2][20]","[F2][21]","[F2][22]","[F2][23]","[F2][24]","[F2][25]","[F2][26]","[F2][27]",
    "[F2][28]","[F2][29]","[F2][2A]","[F2][2B]","[F2][2C]","[F2][2D]","[F2][2E]","[F2][2F]",
    "[F2][30]","[F2][31]","[F2][32]","[F2][33]","[F2][34]","[F2][35]","[F2][36]","[F2][37]",
    "[F2][38]","[F2][39]","[F2][3A]","[F2][3B]","[F2][3C]","[F2][3D]","[F2][3E]","[F2][3F]",
    "[F2][40]","[F2][41]","[F2][42]","[F2][43]","[F2][44]","[F2][45]","[F2][46]","[F2][47]",
    "[F2][48]","[F2][49]","[F2][4A]","[F2][4B]","[F2][4C]","[F2][4D]","[F2][4E]","[F2][4F]",
    "MOD "    ," XOR "   ,"[F2][52]","[F2][53]","AIN "    ,"[F2][55]","RXD$ "   ,"DATE$ "  , // TechRef 4.1.1: AIN
    "TIME$ "  ,"DATE$ "  ,"AIN "    ,"[F2][5B]","ALARM$ " ,"[F2][5D]","ALARM$ " ,"WAKE$ "  , // TechRef 4.2.5: AIN
    "[F2][60]","WAKE$ "  ,"[F2][62]","HEX$ "   ,"[F2][64]","HEX$ "   ,"INP "    ,"INSTR "  , // TechRef 4.1.1: HEX$
    "[F2][68]","[F2][69]","[F2][6A]","[F2][6B]","INSTR "  ,"PEEK "   ,"PEEK# "  ,"[F2][6F]", // TechRef 4.1.1: INSTR
    "[F2][70]","EOF "    ,"LOC "    ,"LOF "    ,"DSKF "   ,"[F2][75]","[F2][76]","[F2][77]",
    "[F2][78]","[F2][79]","[F2][7A]","[F2][7B]","[F2][7C]","[F2][7D]","[F2][7E]","[F2][7F]",
    "ADIN "   ,"[F2][81]","CALL "   ,"ELSE "   ,"XBUFF$ " ,"KEY "    ,"KEYSTAT" ,"KILL "   ,
    "MAXFILES","[F2][89]","OUT "    ,"POWER "  ,"POKE "   ,"RESUME " ,"RETI "   ,"[F2][8F]",
    "BLOAD "  ,"BSAVE "  ,"CLOSE "  ,"COPY "   ,"INIT "   ,"LOAD "   ,"OPEN "   ,"NAME "   ,
    "SET "    ,"SAVE "   ,"[F2][9A]","[F2][9B]","[F2][9C]","[F2][9D]","[F2][9E]","[F2][9F]",
    "PHONE "  ,"SNDBRK " ,"SNDSTAT ","COM "    ,"RSVSTAT" ,"[F2][A5]","[F2][A6]","[F2][A7]",
    "[F2][A8]","[F2][A9]","[F2][AA]","[F2][AB]","[F2][AC]","[F2][AD]","[F2][AE]","[F2][AF]",
    "[F2][B0]","PCONSOLE ","[F2][B2]","MODE "  ,"PZONE"   ,"RENUM "  ,"AUTO "   ,"ERASE "  ,
    "PASS "   ,"DELETE " ,"TITLE "  ,"[F2][BB]","AOFF "   ,"AS "     ,"OUTPUT " ,"APPEND " ,
    "KBRD "   ,"[F2][C1]","[F2][C2]","[F2][C3]","[F2][C4]","[F2][C5]","[F2][C6]","[F2][C7]", // spellbound
    "[F2][C8]","[F2][C9]","[F2][CA]","[F2][CB]","[F2][CC]","[F2][CD]","[F2][CE]","[F2][CF]",
    "[F2][D0]","[F2][D1]","[F2][D2]","[F2][D3]","[F2][D4]","[F2][D5]","[F2][D6]","[F2][D7]",
    "[F2][D8]","[F2][D9]","[F2][DA]","[F2][DB]","[F2][DC]","[F2][DD]","[F2][DE]","[F2][DF]",
    "[F2][E0]","[F2][E1]","[F2][E2]","[F2][E3]","[F2][E4]","[F2][E5]","[F2][E6]","[F2][E7]",
    "[F2][E8]","[F2][E9]","[F2][EA]","[F2][EB]","[F2][EC]","[F2][ED]","[F2][EE]","[F2][EF]",
    "[F2][F0]","[F2][F1]","[F2][F2]","[F2][F3]","[F2][F4]","[F2][F5]","[F2][F6]","[F2][F7]",
    "[F2][F8]","[F2][F9]","[F2][FA]","[F2][FB]","[F2][FC]","[F2][FD]","[F2][FE]","[F2][FF]",
};
/* MORE TOKEN for PC-1600 ? - see TechRef 4.2.5. Page 161 */

bool ishex ( char chr )
{
  if ( (chr >= '0' && chr <= '9') ||
       (chr >= 'A' && chr <= 'F')  ) return true ;
  return false ;
}

/* String-change UPPER */
char *strupr( char  *string )
{
  int  i = 0;
  while ( ( string[i] = toupper( string[i] ) ) != '\0') ++i;
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

void CvStringIToShort (char*  ptrStr,
                       uint*  ptrVal)
{
    /* Convert the String to a short value with msb first (INTEL) */
    *ptrVal =   (uint) ptrStr[0] & 0xFF ;
    *ptrVal += ((uint) ptrStr[1] & 0xFF) << 8 ;
}


void CvStringIToLong (char*   ptrStr,
                      ulong*  ptrVal)
{
//    ulong  tmp ;

    /* Convert the String to a long value with msb first (INTEL) */
    *ptrVal =   (uint) ptrStr[0] & 0xFF ;
    *ptrVal += ((uint) ptrStr[1] & 0xFF) << 8 ;
    *ptrVal += ((uint) ptrStr[2] & 0xFF) << 16 ;
    *ptrVal += ((uint) ptrStr[3] & 0xFF) << 24 ;
}

int count_errors ( int error, FileInfo*  ptrFile)
{
        ptrFile->err_last = error ;
        if ((error == ERR_SUM || error == ERR_ORD) &&
             ptrFile->err_exit <= ERR_OK) ptrFile->err_exit = error ;
        if (++ptrFile->err_cnt >= ERR_CNT_MAX) return (ERR_MULTI + error);

 /* misplaces checksums from losing bytes after other errors not corrected*/
    return (ERR_OK) ;
}


int WriteQuaterToTap (uchar  byte,
                       FILE** ptrFd)
{
      int  error ;

	do {
		error = fputc (0xF0 | byte, *ptrFd) ;
    	if (error == EOF) {
        	printf ("%s: Can't write in the file\n", argP) ;
        	error = ERR_NOK ;
        	break ;
    	}
    	else
        	error = ERR_OK ;
	} while (0);
    return (error);
}

int WriteByteToTap  ( uchar  byte,
                        FILE** ptrFd)
{
  uchar  msq, lsq ;
    int  error = ERR_NOK ;

    do {
            lsq = byte & 0x0F ;
            msq = (byte >> 4) & 0x0F ;

            if (TAPw == 1) { /* ORDER_INV */
                error = WriteQuaterToTap (lsq, ptrFd) ;
                if (error != ERR_OK) break ;
                error = WriteQuaterToTap (msq, ptrFd) ;
        	}
            else { /* not used at moment */
                error = WriteQuaterToTap (msq, ptrFd) ;
                if (error != ERR_OK) break ;
                error = WriteQuaterToTap (lsq, ptrFd) ;
            }

	} while (0);
    return (error);
}


int WriteByteToFile (uchar   byte,
                      FILE** ptrFd)
{
    int  error = ERR_OK ;

    if (TAPw != 0 ) return ( WriteByteToTap(byte, ptrFd) );

    if (*ptrFd != NULL) {
        error = fputc (byte, *ptrFd) ;
        if (error == EOF) {
            printf ("\n%s: Can't write in the file\n", argP) ;
            error = ERR_FILE ;
        }
        else
            error = ERR_OK ;
    }
    return (error);
}

int WriteCharToFile (char   byte,
                     FILE** ptrFd)
{
    int  error ;

    error = ERR_OK ;
    if (*ptrFd != NULL) {
        error = fputc (byte, *ptrFd) ;
        if (error == EOF) {
            printf ("\n%s: Can't write in the file\n", argP) ;
            error = ERR_FILE ;
        }
        else
            error = ERR_OK ;
    }
    return (error);
}

int WriteStringToFile (char*  ptrStr,
                       FILE**  ptrFd)
{
    int  error ;

    error = ERR_OK ;
    if (*ptrFd != NULL) {
        error = fputs (ptrStr, *ptrFd) ;
        if (error == EOF) {
            printf ("\n%s: Can't write in the file\n", argP) ;
            error = ERR_FILE ;
        }
        else
            error = ERR_OK ;
    }
    return (error);
}


int ReadStringFromFile (char*  ptrStr,
                        long  nb,
                        FILE**  ptrFd)
{
    int  ii ;
    int  inVal ;
    int  error ;

    error = ERR_OK ;

    for ( ii = 0 ; ii < nb ; ++ii  ) {
        inVal = fgetc (*ptrFd) ;
        if (inVal == EOF) {
            printf ("\n%s:rstring - Can't read over End Of File\n", argP) ;
            error = ERR_FILE ;
            break ;
        }
        *ptrStr++ = (char) inVal ;
    }
    *ptrStr = 0 ;
    return (error);
}


int ReadLongFromFile (ulong*  ptrVal,
                      FILE**  ptrFd)
{
    char  str[10] ;
     int  error ;

    error = ReadStringFromFile (str, 4, ptrFd) ;
    CvStringIToLong (str, ptrVal) ;

    return (error);
}


int ReadShortFromFile (uint*  ptrVal,
                       FILE**  ptrFd)
{
    char  str[10] ;
     int  error ;

    error = ReadStringFromFile (str, 2, ptrFd) ;
    CvStringIToShort (str, ptrVal) ;

    return (error);
}


int ReadWavHead (ulong*  ptrFreq,
                 FileInfo*  ptrFile)
{
     char  str[20] ;
    ulong  tmpL, chunkSize ;
     uint  tmpS, formatTag, ii=0 ;
     uint  channels ; /* Mono =1 , Stereo = 2 */
     long  position ;
      int  error ;

    do {
        error = ReadStringFromFile (str, 4, &ptrFile->ptrFd) ;
        if (error != ERR_OK) break ;
        if (strcmp (str, "RIFF") != 0) {
            printf ("\n%s: The contents of the file does not begin with 'RIFF'. Unsupported file!\n", argP) ;
            error = ERR_FMT ;
            break ;
        }
        /* file length -8 (offset) */
        error = ReadLongFromFile (&tmpL, &ptrFile->ptrFd) ;
        if (error != ERR_OK) break ;

        error = ReadStringFromFile (str, 8, &ptrFile->ptrFd) ;
        if (error != ERR_OK) break ;
        if (strcmp (str, "WAVEfmt ") != 0) { /* format chunk has to be the first */
            printf ("\n%s: File header format isn't 'WAVEfmt'. This is not a supported format.\n", argP) ;
            error = ERR_FMT ;
            break ;
        }
        /* header length (offset) */
        error = ReadLongFromFile (&chunkSize, &ptrFile->ptrFd) ;
        if (error != ERR_OK) break ;

        error = ReadShortFromFile (&tmpS, &ptrFile->ptrFd) ;
        if (error != ERR_OK) break ;
        formatTag = tmpS ;
        if (tmpS != 1 && tmpS != 0xFFFE ) { /* PCM or WAVE_FORMAT_EXTENSIBLE */
            printf ("\n%s: Wav data format tag %d isn't pure PCM. Unsupported!\n", argP, tmpS) ;
            error = ERR_FMT ;
            break ;
        }

        error = ReadShortFromFile (&tmpS, &ptrFile->ptrFd) ;
        if (error != ERR_OK) break ;
        channels = tmpS ;
        /* channels = 1 mono, 2 = stereo, data has to be in the first channel */
        if (tmpS != 1) {
            if (Qcnt == 0) printf ("%s: Audio format has %d channels, not Mono\n", argP, channels) ;
            if (tmpS > 4) {
                printf ("%s: To much audio channels are included.\n", argP) ;
                error = ERR_FMT ;
                break ;
            }
        }
        /* sample rate /s */
        error = ReadLongFromFile (ptrFreq, &ptrFile->ptrFd) ;
        if (error != ERR_OK) break ;
        error = ReadLongFromFile (&tmpL, &ptrFile->ptrFd) ;
        if (error != ERR_OK) break ;            /* rate * frame size B/s */

        error = ReadShortFromFile (&tmpS, &ptrFile->ptrFd) ;
        if (error != ERR_OK) break ;
        ptrFile->blockAlign = tmpS ;            /* blockAlign = Data block size of a sample block (bytes) */
        ptrFile->bytesPerP = tmpS / channels ;  /* byte length of a sample point */
        if (ptrFile->bytesPerP == 1) {
            /* 8_bit_wave */
            error = ReadShortFromFile (&tmpS, &ptrFile->ptrFd) ;
            if (error != ERR_OK) break ;
            if (tmpS != 8) {
                printf ("\n%s: Wav format error - %d isn't 8 bits/sample\n", argP, tmpS) ;
                error = ERR_FMT ;
                break ;
            }
        }
        else if (ptrFile->bytesPerP <= 4) {     /* max. 32 bit allowed */
            /* 16_bit_wave and more */
            error = ReadShortFromFile (&tmpS, &ptrFile->ptrFd) ;
            if (error != ERR_OK) break ;
            if (tmpS % 8 != 0) {
                printf ("\n%s-Warning: Format has %d bits/sample value - experimentally.\n", argP, tmpS) ;
                // error = ERR_FMT ;
                // break ;
            }
            else if (Qcnt == 0 && (tmpS != 16  ||
                     ptrFile->debug > 0) ) printf ("%s: Format has %d bits/sample value.\n", argP, tmpS) ;

        }
        else {
            printf ("\n%s: Format %d bytes/sample is unsupported.\n", argP, tmpS ) ;
            error = ERR_FMT ;
            break ;
        }
        if (formatTag == 0xFFFE && chunkSize == 40 ) { /* WAVE_FORMAT_EXTENSIBLE */
            error = fseek (ptrFile->ptrFd, 8, SEEK_CUR) ;
            if (error != ERR_OK) {
                printf ("\n%s:wavheadext - Can't seek the wav file\n", argP) ;
                break ;
            }
            error = ReadShortFromFile (&tmpS, &ptrFile->ptrFd) ;
            if (error != ERR_OK) break ;
            if (tmpS != 1 ) { /* PCM  */
                printf ("\n%s: Wavex data format tag %d isn't non-float PCM. Unsupported!\n", argP, tmpS) ;
                error = ERR_FMT ;
                break ;
            }
            chunkSize -= 10 ;
        }
        if (chunkSize > 0x10) { /* read additional bytes for 46 byte or longer headers or wavex */
            error = fseek (ptrFile->ptrFd, (long) chunkSize - 0x10, SEEK_CUR) ;
            if (error != ERR_OK) {
                printf ("\n%s:wavhead44x - Can't seek the wav file\n", argP) ;
                break ;
            }
        }
        error = ReadStringFromFile (str, 4, &ptrFile->ptrFd) ;
        if (error != ERR_OK) break ;

        position = ftell( ptrFile->ptrFd ) ; /* Pos.0x28 usually */
            if (position <= 0) {
                printf ("\n%s:wavhead search1 'data' - Can't ftell the wav file\n", argP) ;
                error = ERR_FILE ;
                break ;
        }

        if (strcmp (str, "data") != 0) { /* check always for wav header 46 byte from ffmpeg */
            error = fseek (ptrFile->ptrFd, -2, SEEK_CUR) ;
            if (error != ERR_OK) {
                printf ("\n%s:wavhead46 - Can't seek the wav file\n", argP) ;
                break ;
            }
            error = ReadStringFromFile (str, 4, &ptrFile->ptrFd) ;
            if (error != ERR_OK) break ;

            if (strcmp (str, "data") != 0) {
                error = ReadStringFromFile (str, 8, &ptrFile->ptrFd) ;
                if (error != ERR_OK) break ;

                /* check for wav 46 + fact chunk = 58 byte header */
                error = ReadStringFromFile (str, 4, &ptrFile->ptrFd) ;
                if (error != ERR_OK) break ;

                while (strcmp (str, "data") != 0 && ii <7) { /* maximum chunks */

                    if (ii==0) {
                        error = fseek (ptrFile->ptrFd, position, SEEK_SET) ; /* rewind to first try*/
                        if (error != ERR_OK) {
                            printf ("\n%s:wavhead search1 'data' - Can't seek the file\n", argP) ;
                            error = ERR_FILE ;
                            break ;
                        }
                    }
                    else {
                        error = ReadLongFromFile (&tmpL, &ptrFile->ptrFd) ;
                        if (error != ERR_OK) break ;
                        if (tmpL%2 > 0) ++tmpL; /* 0-byte follows for word boundary */
                        position += 4;

                        if ( (ulong) position + tmpL +4 >  ptrFile->endSamples ) {
                            error = ERR_FMT ;
                            break ;
                        }

                        error = fseek (ptrFile->ptrFd, (long) tmpL, SEEK_CUR) ; /* rewind */
                        position += (long) tmpL;
                        if (error != ERR_OK) {
                            printf ("\n%s:wavhead search 'data' - Can't seek the file\n", argP) ;
                            error = ERR_FILE ;
                            break ;
                        }
                        error = ReadStringFromFile (str, 4, &ptrFile->ptrFd) ;
                        position += 4;
                        if (error != ERR_OK) break ;
                    }
                    ++ii;
                }
                // ToDo Last try: search for begin of file for string 'data'
            }
        }
        if (error != ERR_OK || strcmp (str, "data") != 0) {
            printf ("\n%s: Header %u after 'fmt ' isn't 'data'\n", argP, ii) ;
            error = ERR_FMT ;
            break ;
        }

        /* length off audio data block */
        error = ReadLongFromFile (&tmpL, &ptrFile->ptrFd) ;
        if (error != ERR_OK) break ;

        position = ftell( ptrFile->ptrFd ) ;
        if (position <= 0) {
            printf ("\n%s:wavhead - Can't ftell the wav file\n", argP) ;
            error = ERR_FILE ;
            break ;
        }
        ptrFile->bgnSamples = (ulong) position ;
        ptrFile->endSamples = ptrFile->bgnSamples - 1 + tmpL ;

    } while (0) ;
    if (error == ERR_NOK) error = ERR_FILE ;
    return (error);
}


int ReadSampleFromWav (int *ptrSampleVal,
                       FileInfo*  ptrFile)
{
     int  inVal, inValL ;
    short val16 ;
    long  val ;
    uint  jj ;
     int  error = ERR_OK ;

    do {
            inVal = fgetc (ptrFile->ptrFd) ;                         /* 8_bit_wav original implemented (uchar) */
            if (inVal == EOF) {
                if (Qcnt == 0) printf ("\nEnd of File\n") ;
                error = ERR_EOF ;
                break ;
            }
            if (ptrFile->bytesPerP > 1) {                            /* 16_bit_wav and longer */
                for (jj = 1 ; jj < ptrFile->bytesPerP ; ++jj ) {
                    inValL = inVal ;                                 /* 16 bit L */
                    inVal = fgetc (ptrFile->ptrFd) ;                 /* 16 bit H, wav build with signed int */
                    if (inVal == EOF) {
                        if (Qcnt == 0) printf ("\nEnd of File\n") ;
                        error = ERR_EOF ;
                        break ;
                    }
                }
                if (error != ERR_OK) break ;

                if (ptrFile->pre_amp > 1) {                         /* Amplification of 16-bit low level recordings */
                    val16 = inVal<<8 | inValL ;

                    val = ptrFile->pre_amp * (long) val16 ;
                    if (val > 0x7FFF) val = 0x7FFF ;       /* clipping */
                    else if (val < -32768) val = -32768 ;  /* clipping */

                    val16 = (short) val ;
                    inValL = val16     & 0xFF ;
                    inVal  = val16 >>8 & 0xFF ;
                }

                if (inValL > 0x7F) inValL = 1 ; else inValL = 0 ;  /* 16 bit L, compensate rounding errors */
                inVal = (((inVal == 0x7F)? 0: inValL) + inVal + 0x80) & 0xFF ; /* convert 16-bit-H to 8-bit-L */
            }
            else if (ptrFile->pre_amp > 1) {                       /* Amplification of 8-bit low level recordings */
                if ( inVal > TRANS_MID ) {
                    inVal = TRANS_MID + (inVal - TRANS_MID) * ptrFile->pre_amp ;
                    if (inVal > 0xFF) inVal = 0xFF ; /* clipping */
                }
                else if (inVal < TRANS_MID) {
                    inVal = TRANS_MID - (TRANS_MID - inVal) * ptrFile->pre_amp ;
                    if (inVal < 0 ) inVal = 0 ; /* clipping */
                }
            }
            if (ptrFile->blockAlign > ptrFile->bytesPerP) {        /* if not mono, then skip other channels */
                /* read is much faster than fseek, fread would be faster than fgetc */
                for (jj = ptrFile->bytesPerP ; jj < ptrFile->blockAlign ; ++jj ) {
                    inValL = fgetc (ptrFile->ptrFd) ;
                    if (inValL == EOF) {
                        if (Qcnt == 0) printf ("\nEnd of File\n") ;
                        error = ERR_EOF ;
                        break ;
                    }
                }
                if (error != ERR_OK) break ;
            }

    } while (0) ;
    *ptrSampleVal = inVal ;
    return (error);
}


int AnalyseSoundLevelOfWav (FileInfo*  ptrFile)
{
        /*           nb of samples with level greater  */
        /*                   >50% 25% 12% 6% 3% 2% 1%  */
         ulong  distrib[7] = { 0,  0,  0, 0, 0, 0, 0 } ;
         ulong  ii, all_samples, clip_samples, sum_samples,
                interval, interval1, position = ptrFile->startSampl ;
           uint jj, jmax, level, levelmin, levelmed, levelmed1, levelsum,
                high_intervals = 0, hmax = 4 ;
           int  inVal ,
                error = ERR_OK ;

    all_samples = (ptrFile->endSamples - ptrFile->startSampl) / ptrFile->blockAlign ;
    ptrFile->pre_amp = 1 ;

    do {
        for (ii = 0; ii < all_samples ; ++ii ) {

            error = ReadSampleFromWav (&inVal, ptrFile);
            if (error != ERR_OK) break ;

            if (inVal > TRANS_MID) level = inVal - TRANS_MID ;
            else level = TRANS_MID - inVal ; /* level from axis absolute */

            /* Quantisation of levels */
            for (jj = 0; jj < 7 ; ++jj) {
                if (level > 0x3F) {
                        ++distrib[jj] ;
                        break ;
                }
                else level <<=1 ;
            }
        }
        clip_samples = all_samples /256 ; /* part of samples, that may be clipped */
        ii = 0 ;

        if (ptrFile->bytesPerP > 1 ) jmax = 6 ;
        else jmax = 4 ; /* gain max. 16 with 8-bit */

        /* Analyse the distribution of the sound level */
        for (jj = 0; jj < jmax ; ++jj) {
            ii += distrib[jj] ;
            if (ii > clip_samples ) break ;
            ptrFile->pre_amp <<=1 ;
        }
        if (Qcnt == 0 && ( ptrFile->pre_amp > 2 || (ptrFile->debug != 0 && ptrFile->pre_amp > 1 ) ) )
            printf ("Wav file was not normalized. %s pre-amplify with factor %i internally\n", argP, ptrFile->pre_amp);

        error = fseek (ptrFile->ptrFd, ptrFile->startSampl, SEEK_SET) ; /* rewind */
        if (error != ERR_OK) {
            printf ("\n%s:analyse1 - Can't seek the file\n", argP) ;
            error = ERR_FILE ;
            break ;
        }
        if (Scnt==0) { /* Automatic search for the beginning of the usable synchronization */
            /* Calculate the mean of the sound level */
            level = ptrFile->pre_amp * 0x60 ; /* Mean within distrib[0] */
            sum_samples = 0 ;
            for (jj = 0; jj < jmax ; ++jj) {
                if ( level > 0x80) sum_samples += distrib[jj] * 0x80 ;
                else sum_samples += distrib[jj] * level ;
                level >>=1 ;
            }
            /* Medium volume required for recognizing the synchronization tone */
            levelmin = sum_samples / all_samples * Sync_Lev_Min/16 ; /* 0.7 * factors of tolerance */

            interval = ptrFile->wav_freq / 10 ; /* 0.1 seconds, number of sample points for averaging the volume */
            jmax = all_samples / interval ;
            levelsum = 0 ;
            jj=0 ;

            /* Automatic search for the beginning of the usable synchronization based on the volume at the beginning of the recording */
            while (jmax > jj && high_intervals < hmax) {
                /* Save position in wav file*/
                if (high_intervals == 0) {
                    position = ptrFile->startSampl + interval * jj * ptrFile->blockAlign ;
                    levelsum = 0 ;
                }
                sum_samples = 0 ;

                for (ii = 0; ii < interval ; ++ii ) {
                    error = ReadSampleFromWav (&inVal, ptrFile); /* pre_amp is used */
                    if (error != ERR_OK) break ;

                    if (inVal > TRANS_MID) level = inVal - TRANS_MID ;
                    else level = TRANS_MID - inVal ; /* level from axis absolute */
                    sum_samples += level ;
                }
                if (error != ERR_OK) break ;
                levelmed = sum_samples / interval ;
                if (levelmed > levelmin) {      /* Volume in the interval like sync signal */
                    if (high_intervals == 0) levelmed1 = levelmed ;
                    else levelsum += levelmed ; /* first interval starts with silence normally */
                    ++high_intervals ;
                }
                else high_intervals = 0 ;
                ++jj ;
            }
            if (error != ERR_OK) break ;

            if (high_intervals == hmax) {
                    level = (levelsum + hmax/2) / (hmax -1) ;    /* Medium volume after the interval 0 */
                    interval1 = (interval * levelmed1) / level ; /* Time portion of the sync signal in the first interval 0 */
                    if (interval1 > interval) interval1 = interval ; /* This interval does not contain leading silence */
                    ptrFile->startSampl = position + (interval - interval1) * ptrFile->blockAlign ;
            }
            error = fseek (ptrFile->ptrFd, ptrFile->startSampl, SEEK_SET) ; /* rewind */
            if (error != ERR_OK) {
                printf ("\n%s:analyse2 - Can't seek the file\n", argP) ;
                error = ERR_FILE ;
                break ;
            }
        }
    } while (0) ;

    return (error); /* result stored in ptrFile->pre_amp */
}

/* Preparations for input caching (or later: input from other source)
   No Cache for Begin of ConvertWavToBin, ReadWavHead, AnalyseSoundLevelOfWav */
/* Cache is NOT implemented until now!
   Use ptrFile->Cache[CACHESIZE], CacheState, CacheEnd, CachePos */

int ReadSampleValue (int *ptrSampleVal, FileInfo*  ptrFile)
{
    int  error = ReadSampleFromWav (ptrSampleVal, ptrFile);
    return (error);
}

int sseek(FileInfo* ptrFile, long offset, int whence)
/* Switch cache of, if IMGc > 0 or TAPc > 0 */
{
    int error = fseek (ptrFile->ptrFd, offset, whence) ;
    return (error) ;
}

long stell (FileInfo* ptrFile) // int* ptrError, uchar cause
/* Switch cache of, if IMGc > 0 or TAPc > 0 */
{
    long sft = ftell( ptrFile->ptrFd);
    return (sft) ;
}

/* returns the exact time stamp of a sample, usually the time AFTER a bit or byte        */
/* this can be used, to correct signal errors with an audio editor, tested with Audacity */

double WavTime (FileInfo*  ptrFile)
{
    long position = stell( ptrFile ) ;
    if (IMGc > 0 || TAPc > 0 || KHXc > 0) return ( (double) position ) ;

    if (position <= 0) {
        printf ("\n%s:wavtime - Can't ftell the wav file\n", argP) ;
        exit ( ERR_FILE ) ;
    }
    return (( position - ptrFile->blockAlign - (long) ptrFile->bgnSamples)/(float) (ptrFile->wav_freq * ptrFile->blockAlign)) ;
}
//Debug
void PrtWavTime (FileInfo*  ptrFile)
{
    printf (" wav position %.5lf s ", WavTime(ptrFile));
}

/* Check if we are inside of the debug window */
bool IsDbgWavTime (ulong debug_option,      /* ask for window of debug type */
                   FileInfo*  ptrFile)      /* compare with option set */
{
    double wvtime, dbg_time_bgn, dbg_time_end ;
    bool isdwt ;
    if ( ( debug_option & ptrFile->debug) == 0) return (false) ;
    if (IMGc > 0 || TAPc > 0 || KHXc > 0) return (false) ;

    if (Scnt < 2) { /* no debug time exist */
        if ( ( debug_option & 0x0001) == (ptrFile->debug & 0x0001) ||   /* trans(amps), bit type symbols */
             ( debug_option & 0x0002) == (ptrFile->debug & 0x0002) ||   /* bit range shifted because trans(amps) shifted  */
             ( debug_option & 0x0004) == (ptrFile->debug & 0x0004) ||   /* bit level debugging */
             ( debug_option & 0x0008) == (ptrFile->debug & 0x0008)  )   /* sum up skipped bits traces */
            return (true) ;          /* not full file for 0x10000 - sample and amps and rating level */
    }
    dbg_time_bgn = Debug_Time;
    dbg_time_end = Debug_Time_End;

    if ((debug_option & 0x000C)>0 && (ptrFile->debug & 0x000C)>0) {
        dbg_time_bgn -= DEBUG_TIME_L4 ;
        dbg_time_end += DEBUG_TIME_L4 ;
    }
    else if ((debug_option & 0x0003)>0 && (ptrFile->debug & 0x0003)>0) {
        dbg_time_bgn -= DEBUG_TIME_L1 ;
        dbg_time_end += DEBUG_TIME_L1 ;
    }
    wvtime = WavTime(ptrFile) ;
    isdwt = (dbg_time_bgn < wvtime && wvtime < dbg_time_end) ;
    return ( isdwt ) ;
}

/* Detect wave amplitudes in sample value triples */
int DetectAmpsFromVals (int* inVals, int* ptrAmpd_min, int* ptrAmpd_max, int* ptrLast_ampd, int* ptrDampd_min)
{
    int ampd = 0 ;
    int amp2 ; /* last difference Max-Min (sample value) is one filter criteria */

    if ( inVals[0] >= inVals[1] && inVals[1] <  inVals[2] ) { /* is a Min? */
            amp2 = (*ptrAmpd_max - *ptrAmpd_min)/Amp_Diff_Rel ;
            if (amp2 < *ptrDampd_min ) amp2 = *ptrDampd_min ; /* filter false amps */
            if (inVals[1] < Amp_Min_Below && inVals[1] < *ptrAmpd_max - amp2) {
                if ( *ptrLast_ampd != -1 || inVals[1] < *ptrAmpd_min) *ptrAmpd_min = inVals[1] ; /* depress steps */
                ampd = -1 ;
            } // end if: Min!
    } // end if: Min?
    else if ( inVals[0] <= inVals[1] && inVals[1] >  inVals[2] ) { /* is a Max? */
            amp2 = (*ptrAmpd_max - *ptrAmpd_min)/Amp_Diff_Rel ;
            if (amp2 < *ptrDampd_min ) amp2 = *ptrDampd_min ; /* filter false amps */
            if (inVals[1] > Amp_Max_Above && inVals[1] > *ptrAmpd_min + amp2) {
                if (*ptrLast_ampd != 1 || inVals[1] > *ptrAmpd_max) *ptrAmpd_max = inVals[1] ; /* depress steps */
                ampd = 1 ;
            } // end if: Max!
    } // end if: Max?
    return (ampd) ;
}

/* Bit detection with mean length difference of amplitudes or amplification of values from
   the last amplitude needs to know the last both amps before the actual position of bit */

int FindAmpsFromWav (int* inVals, int* ptrAmpd_min, int* ptrAmpd_max, int* ptrAmp, int* ptrApos, int* ptrDampd_min, FileInfo*  ptrFile)
{
    long  position ;
    long  tmp, tmpS ;
     int  ampd, ii ;
     int  error = ERR_OK ;

    position = stell( ptrFile ) ;
    if (position <= 0) {
            printf ("\n%s:famps - Can't ftell the wav file\n", argP) ;
            error = ERR_FILE ;
            return (error) ;
    }
    /* One wave of freq of Bit_0 */
    ii = - ( ptrFile->wavLenMax + 0 ) ; /* relative position in samples from start of actual bit */
    *ptrApos = ii * 2 ; /* start value for position of last amp */

    tmpS = (long) ptrFile->blockAlign * ii ;
    /* Rewind one wave of the frequency of Bit_0 */
    if (position >= (long) ptrFile->bgnSamples - tmpS ) error = sseek (ptrFile, tmpS , SEEK_CUR) ;
    if (error != ERR_OK) {
            printf ("\n%s:famps - Can't seek the file: %ld\n", argP, position) ;
            error = ERR_FILE ;
            return (error) ;
    }

    error = ReadSampleValue (&inVals[0], ptrFile) ;
    if (error != ERR_OK) return (error) ;
    ++ii ;

    if (inVals[0] > Trans_High) *ptrAmpd_max = inVals[0] ;
    else                        *ptrAmpd_max = Trans_High ;
    if (inVals[0] < Trans_Low)  *ptrAmpd_min = inVals[0] ;
    else                        *ptrAmpd_min = Trans_Low ;

    error = ReadSampleValue (&inVals[1], ptrFile) ;
    if (error != ERR_OK) return (error) ;
    ++ii ;

    if (inVals[1] > *ptrAmpd_max) *ptrAmpd_max = inVals[1] ;
    if (inVals[1] < *ptrAmpd_min) *ptrAmpd_min = inVals[1] ;

    do {

        error = ReadSampleValue (&inVals[2], ptrFile) ;
        if (error != ERR_OK) break ;
        ++ii ;

        ampd = DetectAmpsFromVals (inVals, ptrAmpd_min, ptrAmpd_max, ptrAmp, ptrDampd_min) ;
        if (ampd != 0 ) {
                *ptrAmp = ampd ;
                *ptrApos = ii ;
        }
         /* DEBUG CODE
        if  ( (Qcnt == 0) && IsDbgWavTime(0x10000, ptrFile) ) {
            error = ERR_OK;
        }  END DEBUG */
        inVals[0] = inVals[1] ;
        inVals[1] = inVals[2] ;

        tmp = stell( ptrFile ) ;
        if (tmp <= 0) {
            printf ("\n%s:famps - Can't ftell the wav file\n", argP) ;
            error = ERR_FILE ;
            break ;
        }

    } while (position > tmp) ;
    if (error != ERR_OK) return (error) ;

    error = sseek (ptrFile, position, SEEK_SET) ;
    if (error != ERR_OK) {
            printf ("\n%s:famps - Can't seek the file: %ld\n", argP, position) ;
            error = ERR_FILE ;
    }
    return (error) ;
}
/* The following algorithm improves the 1. classic algorithm for PC-12xx-14xx, not only to     */
/* weight the fixed levels Trans_High and Trans_Low but also the difference to last amplitude. */
/* It builds a transformed "asymmetric amplified" wavy line from the original curve*/
/* This helps to push most misplaced amplitudes over the High/Low-axis */

void AmplifySampleValue (int* ptrInVal, int* ptrAmpd_min, int* ptrAmpd_max, int* ptrLast_ampd, FileInfo*  ptrFile)

{
    int  amplic_base, amplic_limit ;

    /*last amplitude is the base point of the amplification till next amplitude */
    if (*ptrLast_ampd < 0) {        /* was a minimum */
        if ( *ptrInVal < *ptrAmpd_min) *ptrAmpd_min = *ptrInVal ; /* after "false" max */
        amplic_base = *ptrAmpd_min ;
    }
    else if (*ptrLast_ampd > 0) {   /* was a maximum */
        if ( *ptrInVal > *ptrAmpd_max) *ptrAmpd_max = *ptrInVal ; /* after "false" min */
        amplic_base = *ptrAmpd_max ;
    }
    else                        /* other signal, starting */
        amplic_base = (Trans_High + Trans_Low) /2 ;

    /* The difference between the actual sample value and the last amplitude will amplified */
    /* but not furthermore, when the transmission limit was reached */

    if   (   *ptrLast_ampd < 0 && *ptrInVal > Trans_High) {/* Min, more amplification not needed */
        if (amplic_base < Trans_High) amplic_limit = Trans_High ; /* correct placed Min */
        else amplic_limit = amplic_base ;                         /* false placed Min */
    }
    else if (*ptrLast_ampd > 0 && *ptrInVal < Trans_Low) { /* Max, more amplification not needed */
        if (amplic_base > Trans_Low)  amplic_limit = Trans_Low ; /* correct placed Max */
        else amplic_limit = amplic_base ;                        /* false placed Max */
    }
    else  /* amplify the difference from actual sample value to the last amplitude */
             amplic_limit = *ptrInVal ;

    /* makes a combined value of the actual value with the differential part to the last amplitude */
    *ptrInVal = (amplic_limit - amplic_base) * ptrFile->rate_amp / RATE_SCALE + *ptrInVal ;
}


int AmplitudesDistanceCheck (int ampd, int* dpos, FileInfo*  ptrFile)
{
    static bool amp_dpos_err = false ;
    static long amp_dpos_errPos = 0 ;
    long amp_dpos_errLast = amp_dpos_errPos ;
    int error = ERR_OK ;

    if (*dpos == 0) amp_dpos_err = false ;
    else if (ptrFile->debug != 0 && ptrFile->status != STAT_EOT && ptrFile->synching == 0 &&
             !ptrFile->sync_bit && !ptrFile->pause ){
        if (*dpos > Amp_Dpos_Max ) {
                if (!amp_dpos_err) {
                    amp_dpos_err = true ;
                    amp_dpos_errPos = stell( ptrFile ) ;
                    if (amp_dpos_errPos > amp_dpos_errLast ) {
                        ++ ptrFile->wrn_cnt ;
                        if (Qcnt == 0 && ptrFile->synching ==0)
                            printf ("Dropout found at: %.5lf s\n", WavTime(ptrFile) );
                    }
                    error = ERR_DROP ;
                }
        }
        else if (*dpos < Amp_Dpos_Min && ampd != 0 ) {
                if (!amp_dpos_err) {
                    amp_dpos_err = true ;
                    amp_dpos_errPos = stell( ptrFile ) ;
                    if (amp_dpos_errPos > amp_dpos_errLast ) {
                        ++ ptrFile->wrn_cnt ;
                        if (Qcnt == 0 && ptrFile->synching ==0)
                            printf ("Glitch found at: %.5lf s\n", WavTime(ptrFile) );
                    }
                    error = ERR_GLIT ;
                }
        }
        else amp_dpos_err = false ;

        if (amp_dpos_errPos < 0) {
            printf ("\n%s:ampdchk - Can't ftell the wav file\n", argP) ;
            error = ERR_FILE ;
        }
    }
    return (error);
}

/* Helps to collect data for the second bit reading method using time differences
   between amplitudes, here is calculated a trimmed arithmetic mean of all
   inner (no borders) time differences between minimum and maximum amplitudes.
   This will be used for the calculation "how many mean amplitude differences would fit
   into one bit length" */

int AmplitudesDistanceStatData (int ampd, int* acnt, int* dpos, int* dpos_max, int* dpos_min, int* dpos_sum, //, int* dpos_sum2
                                 FileInfo*  ptrFile)
{
    if   ( *acnt == 1 ) {
               *dpos_max = *dpos ;  /* 1. distance = 2. value, start to collect */
               *dpos = 0 ;          /* init DistanceCheck */
    }
    else if  ( *acnt == 2 ) {               /* feed the min and max field */
        if   ( *dpos <= *dpos_max )   *dpos_min = *dpos ;
        else { *dpos_min = *dpos_max; *dpos_max = *dpos ; }
    }
    else {     // acnt  > 2
        if  (    *dpos  >  *dpos_max ) {
             *dpos_sum  += *dpos_max ;
             //  *dpos_sum2 += *dpos_max * *dpos_max ; //variances not used at moment
             *dpos_max   = *dpos ;    /* greatest time difference will not included in sum */
        }
        else if (*dpos  <  *dpos_min ) {
             *dpos_sum  += *dpos_min ;
             //  *dpos_sum2 += *dpos_min * *dpos_min ;
             *dpos_min   = *dpos ;    /* lowest time difference not included in sum */
        }
        else {
             *dpos_sum  += *dpos ;
             //  *dpos_sum2 += *dpos * *dpos ;
        }
    }
    return (AmplitudesDistanceCheck (ampd, dpos, ptrFile) );
}
/* This procedure counts the transitions inside a bit frame and works edge triggered.

   The original CLOAD sync edge trigged (ESR-H ASM: TEST 0x80) also, but read the bits
   by a Schmitt-Trigger hardware, counting the time, how long every level is present.
   (ESR-H CPU uses Operation: 0x4F, 0x6F,  ASM: IPXL, IPXH)

   Therefore, the result may be different if a file from Wav2bin or a pocket is readable.

   Short pits in a level can lead to retransmissions of this bit from hardware.
   This cannot corrected here. Some errors have seen, all not correctable are:
   1-bit errors, sometimes HIGH bits are detected but LOW bits was send
   2-bit-error (bits swapped), combined stop/start-bit: one bit lost

   These errors were found in wav files. The causes are close to the hardware
   or are the software for recording and processing the files. */

int ReadBitFromWav (ulong*  ptrTrans, ulong*  ptrAmps, FileInfo*  ptrFile)
{
    int  sign = 1 ;
    int  inVal ;
    int  inVals[3] ;
    int  ampd = 0, last_ampd = 0,
         /* Value at the last Min- or Max- amplitude and relative position + 1 */
         ampd_min, ampd_max, last_apos ;        /* start value set in FindAmps */
    int  dampd_min = 0 ;  /* Required minimum size of an amplitude relative to the last calculated
                             from main value of differences max-min amplitudes from the entire file */
    int  acnt = -1, pos_min = -1, pos_max = -1,
         dpos, dpos_max = -1, dpos_min = -1,   /* all distances incremented +1 */
         dpos_sum = 0, // dpos_sum2 = 0, vrcdpos ;
         acnt_scal = 0;

         (void) acnt_scal;

    int  ii, imax = ptrFile->bitLen ;
    long position ;
    int  error ;
    //DEBUG code double Debug_wavtime = WavTime(ptrFile) ;

    *ptrTrans = 0 ;
    *ptrAmps  = 0 ;

    position = stell( ptrFile ) ;
    if (position <= 0) {
            printf ("\n%s:rbit - Can't ftell the wav file\n", argP) ;
            return ( ERR_FILE ) ;
    }

    if ( (ulong) position + ptrFile->bitLen * ptrFile->blockAlign -1 > ptrFile->endSamples ) {
        if (Qcnt == 0 && ptrFile->synching == 0) printf ("End of audio data reached: %lu, %.5lf s\n",
                               ptrFile->endSamples, WavTime(ptrFile) ) ; // Bgn. Text data
        error = ERR_EOF ;
    }
    else {
        error = ERR_OK ;

        /*  Modified algorithm will used with amplitude based amplification of sample values */
        if (ptrFile->rate_amp >= 0) {

                if ( ptrFile->ampd_cnt > Bit_0 ) dampd_min = ptrFile->ampd_sum / ptrFile->ampd_cnt / Amp_Diff_Mid ;
                if ( dampd_min < Amp_Diff_Min )  dampd_min = Amp_Diff_Min ;

                /*  Find last Max/Min-amplitude preceding this bit from wav */
                error = FindAmpsFromWav (inVals, &ampd_min, &ampd_max, &last_ampd, &last_apos, &dampd_min, ptrFile) ;
                if (error != ERR_OK) return (error) ;

            /* Start point is the sample value before the actual position */
            inVal = inVals[1] ;
            /* also the start point has to amplify for a smooth undistorted transformation */
            if (ptrFile->rate_amp > 0) AmplifySampleValue ( &inVal, &ampd_min, &ampd_max, &last_ampd, ptrFile) ;

        }
        else { /* set of first sign for original classic method */
            /* Rewind one sample point */
            if ( (ulong) position >= ptrFile->bgnSamples + ptrFile->blockAlign ) {
                    error = sseek (ptrFile, - ptrFile->blockAlign , SEEK_CUR) ;
                    if (error != ERR_OK) {
                        printf ("\n%s:rbit - Can't seek the file: %ld\n", argP, position) ;
                        error = ERR_FILE ;
                        return (error) ;
                    }
                    error = ReadSampleValue (&inVal, ptrFile);
                    if (error != ERR_OK) return (error) ;
                }
                else inVal = 0xFF   ;   /* sign = original: 1, most common ptrFd will point to the first Max amplitude
                                        of a bit, but data and old Basic often other */
            }
            if (inVal > Trans_High) sign = 1;
            else if (inVal < Trans_Low) sign = -1;
            else sign = 0;

        for ( ii = 0 ; ii < imax ; ++ii ) {
            /* read a sample value from wav file and convert it to 8-bit */
            error = ReadSampleValue (&inVal, ptrFile);
            if (error != ERR_OK) break ;

            if (ptrFile->rate_amp >= 0) {
                /* the improved methods only used, if this parameter was set from FindSyncAnd */

                inVals[2] = inVal ;
                /* check, if the sample value before was an amplitude */
                ampd = DetectAmpsFromVals (inVals, &ampd_min, &ampd_max, &last_ampd, &dampd_min) ;

                if (ampd != 0 ) {
                    /* This is an additional 2. method to read bits, based on distance between amplitudes */
                    /* It is most independent from the absolute values of samples.                        */
                    /* This length based calculation method is an alternative to count level transitions  */
                    /* The result has more "contrast" and helps, to decide how to handle Bit_MID and more */
                    /* robust start bit detection. For syncing should be used the 1. algorithm instead.   */
                    if (ampd > 0 && !(last_ampd > 0) ) { /* was a real maximum */
                        pos_max = ii ;
                        if ( ++acnt > 0 ) {
                            dpos = ii - pos_min ; /* time difference MaxAmp - LastMinAmp [Samples] */
                            error = AmplitudesDistanceStatData (ampd, &acnt, &dpos, &dpos_max, &dpos_min, &dpos_sum, //&dpos_sum2,
                                                                ptrFile) ;
                        }
                        if ( !ptrFile->sync_bit ) { /* value difference stat data */
                            ptrFile->ampd_sum += inVals[1] - ampd_min ;
                            ++ptrFile->ampd_cnt ;
                        }
                        last_apos = ii ;
                    }
                    else if (ampd < 0 && !(last_ampd < 0) ) { /* was a real minimum */
                        pos_min = ii ;
                        if ( ++acnt > 0 ) {
                            dpos = ii - pos_max ; /* time difference MinAmp - LastMaxAmp [Samples] */
                            error = AmplitudesDistanceStatData (ampd, &acnt, &dpos, &dpos_max, &dpos_min, &dpos_sum, //&dpos_sum2,
                                                                ptrFile) ;
                        }
                        if ( !ptrFile->sync_bit ) { /* value difference stat data */
                            ptrFile->ampd_sum += ampd_max - inVals[1] ;
                            ++ptrFile->ampd_cnt ;
                        }
                        last_apos = ii ;
                    }
                    else if (acnt > 0) { /* double (after after little opposite) amps, check only */
                        if ( ampd > 0 ) dpos = ii - pos_min;
                        else            dpos = ii - pos_max;
                        error = AmplitudesDistanceCheck (ampd, &dpos, ptrFile) ;
                    }
                    last_ampd = ampd ; /* amplitude found (all pos one sample before exactly) */
                }
                else if (last_ampd > 0 && inVals[1] >= ampd_max ){  /* maximum plateau */
                     dpos = ii - pos_min;
                     error = AmplitudesDistanceCheck (ampd, &dpos, ptrFile) ;
                }
                else if (last_ampd < 0 && inVals[1] <= ampd_min ){  /* minimum plateau */
                     dpos = ii - pos_max;
                     error = AmplitudesDistanceCheck (ampd, &dpos, ptrFile) ;
                }
                if (error == ERR_DROP) acnt_scal += 1 ; /* only for debug purposes at moment */
                else if (error == ERR_GLIT) --acnt_scal ;
                else if (error != ERR_OK) break ;
                error = ERR_OK ;

                /* shift left sample values for the next amplitude detection */
                inVals[0] = inVals[1] ;
                inVals[1] = inVal ;//[2]

                /* The following call is the extension of the 1. classic method for PC1245-1475 */
                /* Compensation of some errors, when the mean level of the signal may swing */
                /* caused by DC voltage, line frequency or other hardware problems */

                if (ptrFile->rate_amp > 0) AmplifySampleValue ( &inVal, &ampd_min, &ampd_max, &last_ampd, ptrFile) ;

            }
            if ( (Qcnt == 0) && IsDbgWavTime(0x10000, ptrFile)){

                if (ampd > 0 ) printf("^") ;
                else if  (ampd < 0 ) printf("v") ;

                if (ptrFile->rate_amp > 0) {

                    if (inVal < 0) printf("~%02X>-%03X", inVals[2], -inVal) ;
                    else printf("~%02X>+%03X", inVals[2], inVal) ;

                }
                else printf("~%02X", inVal) ;
                if (((stell( ptrFile)- (long) ptrFile->bgnSamples)/ ptrFile->blockAlign) % 8 == 0 )
                    printf("[%.5lf] ", WavTime(ptrFile)) ;
            }

            /* This is the original 1. algorithm of Wav2bin 1.5, uses the fixed (or resulting amplified)
               levels */

            if (sign > 0) {
                if (inVal > Trans_High) {
                    continue ;
                }
                if (inVal < Trans_Low) {
                    sign = -1;
                    ++ *ptrTrans ;
                }
            }
            else if (sign < 0) {
                if (inVal < Trans_Low) {
                    continue ;
                }
                if (inVal > Trans_High) {
                    sign = 1;
                    ++ *ptrTrans ;
                }
            }
            else {
                if (inVal < Trans_Low) {
                    sign = -1;
                    ++ *ptrTrans ;
                }
                if (inVal > Trans_High) {
                    sign = 1;
                    ++ *ptrTrans ;
                }
            }
        }   // end for, sample values of a bit
        /* calculate, how many mean time differences between opposite amplitudes fit into bit length */
        /* with an ideal signal both methods should return the same value */
        if ( acnt > 4 && dpos_sum > 0) {

                *ptrAmps  = ( ptrFile->bitLen * (acnt-2) *2 / dpos_sum +1)/2 ; /* with rounding */

                 /* Experimentally include calculation standard deviation */
                 /* vrcdpos  = ( dpos_sum2 - dpos_sum * dpos_sum / (acnt-2) ) ; // Variance of dpos * N
                 if (Qcnt == 0 && ptrFile->synching == 0 && vrcdpos > (acnt-2) * ptrFile->bitLen * ptrFile->bitLen * 2 /(3 * Bit_1 * Bit_1 ))
                        printf ("Inhomogeneous Bit before %.5lf s\n", WavTime(ptrFile)); */
        }
        else *ptrAmps  = *ptrTrans ; /* if the alternative method is non-applicable, return classic value */
    } // end if: No end of audio data

    if ( (Qcnt == 0) && IsDbgWavTime(0x10000, ptrFile) ) {
        if (*ptrTrans == *ptrAmps)
            printf(" %ld: %3lu,  %.5lf s\n", (stell( ptrFile)- (long) ptrFile->bgnSamples)/ ptrFile->blockAlign,
                   *ptrTrans, WavTime(ptrFile)) ;
        else
            printf(" %ld: %3lu(%3lu),  %.5lf s\n", (stell( ptrFile)- (long) ptrFile->bgnSamples)/ ptrFile->blockAlign,
                   *ptrTrans, *ptrAmps, WavTime(ptrFile)) ;
    }
    else if ( ( IsDbgWavTime( 0x0001, ptrFile) || position > Debug_Position ) && (Qcnt == 0) ) {
        if (*ptrTrans == *ptrAmps) printf(" %lu", *ptrTrans) ;
        else printf(" %lu<%lu>", *ptrTrans, *ptrAmps) ;
    }

    return (error);
}

/* correct length of borders because of quantisation error from sampling */
int AmplitudesBorderInterpolation (int sVal, int bVal,
                                   int eVal, int nVal,
                                   FileInfo*  ptrFile)
{
    long deltaB, deltaE, deltaLen  ;    /* correction at begin, end of amplitude(s) and total */
    long skalmin = 16, skal = skalmin ; /* based on the mean of all amplitudes of first sync */
    if (ptrFile->ampd_sum > 0) skal *= 0xFE * ptrFile->ampd_cnt / ptrFile->ampd_sum ;

    if ((sVal > Trans_High && bVal > Trans_High ) ||
        (sVal < Trans_Low && bVal < Trans_Low )  ) deltaB = 0 ;
    else deltaB = bVal - sVal ;
    if  (deltaB != 0) deltaB = (bVal - TRANS_MID) * skal /deltaB ;

    if ((eVal > Trans_High && nVal > Trans_High ) ||
        (eVal < Trans_Low && nVal < Trans_Low )  ) deltaE = 0 ;
    else deltaE = nVal - eVal ;
    if  (deltaE != 0) deltaE = (nVal - TRANS_MID) * skal /deltaE ;

    deltaLen = (deltaB - deltaE);
    if (deltaLen < 0) deltaLen = (deltaLen - skalmin/2) /skalmin ;
    else  deltaLen = (deltaLen + skalmin/2) /skalmin ; /* with rounding */

    return (deltaLen);
}


int ReadAmpFromEWav (ulong*  ptrAmpL1, /* length of 1. amplitude + border interpolation (-1...+1) */
                     ulong*  ptrAmpL2, /* length of 2. amplitude or sign */
                  FileInfo*  ptrFile)
{
    int  inVals[3] ;
    int  ampd = 0, last_ampd = 0,
         /* Value at the last Min- or Max- amplitude and relative position + 1 */
         ampd_min, ampd_max,                    /* start value set in FindAmps */
         last_apos ;                            /* amplitude count not used for E-Wav */
    int  dampd_min = 0 ;  /* from main value of differences max-min amplitudes */
    int  rate_amp = ptrFile->rate_amp ;

    int  sign = 0 ;
    int  inVal, lastVal, sVal, bVal = TRANS_MID ;
    bool isTrans ;
   ulong trans ;
    int  error ;
    long  position ;

    int  ii, imax = ptrFile->wavLenMax * 2 ;
    int last_tpos = 0 ;

    trans = 0 ;
    *ptrAmpL1 = *ptrAmpL2 = 0 ;

    position = stell( ptrFile ) ;
    if (position <= 0) {
            printf ("\n%s:rbit - Can't ftell the wav file\n", argP) ;
            return ( ERR_FILE ) ;
    }

    if ( (ulong) position + ptrFile->wavLenMin * ptrFile->blockAlign -1 > ptrFile->endSamples ) {
        if (Qcnt == 0 && ptrFile->synching == 0) printf ("End of audio data reached: %lu, %.5lf s\n", ptrFile->endSamples, WavTime(ptrFile) ) ; // Bgn. Text data
        error = ERR_EOF ;
    }
    else {
        error = ERR_OK ;

        if ( (ulong) position >= ptrFile->bgnSamples + ptrFile->blockAlign *2 ) {

            /*  Modified algorithm will used with amplitude based amplification of sample values */
            if (rate_amp >= 0) {

                /* Rewind one of two sample points, so point after trans could be read again */
                error = sseek (ptrFile, - (long) ( ptrFile->blockAlign * 1 ) , SEEK_CUR) ;
                if (error != ERR_OK) {
                    printf ("\n%s:rAmpE - Can't seek the file: %ld\n", argP, position) ;
                    error = ERR_FILE ;
                    return (error) ;
                }

                if ( ptrFile->ampd_cnt > Bit_0 ) dampd_min = ptrFile->ampd_sum / ptrFile->ampd_cnt / Amp_Diff_Mid ;
                if ( dampd_min < Amp_Diff_Min )  dampd_min = Amp_Diff_Min ;

                /*  Find last Max/Min-amplitude preceding this bit from wav */
                error = FindAmpsFromWav (inVals, &ampd_min, &ampd_max, &last_ampd, &last_apos, &dampd_min, ptrFile) ;
                if (error != ERR_OK) return (error) ;

                /* Start point is the sample value before the actual position */
                inVal = inVals[1] ;
                /* also the start point has to amplify for a smooth undistorted transformation */
                if (rate_amp > 0) AmplifySampleValue ( &inVal, &ampd_min, &ampd_max, &last_ampd, ptrFile) ;

            }
            else { /* set of first sign for original classic method */
                 /* Rewind both of two sample points, both points of trans had to read again */

                    error = sseek (ptrFile, - (long) ( ptrFile->blockAlign * 2 ) , SEEK_CUR) ;
                    if (error != ERR_OK) {
                        printf ("\n%s:rAmpE - Can't seek the file: %ld\n", argP, position) ;
                        error = ERR_FILE ;
                        return (error) ;
                    }
                    error = ReadSampleValue (&inVal, ptrFile);
                    if (error != ERR_OK) return (error) ;
            }

        }
        else {
                inVal = TRANS_MID ;
                rate_amp = 0 ; /* temporary */
        }

        /* set of first sign */
        if (inVal > Trans_High) sign = 1;
        else if (inVal < Trans_Low) sign = -1;
        else sign = 0;

        sVal = inVal ;

        for ( ii = 0 ; ii < imax ; ++ii ) {

            lastVal = inVal ;

            /* read a sample value from wav file and convert it to 8-bit */
            error = ReadSampleValue (&inVal, ptrFile);
            if (error != ERR_OK) break ;

            if (rate_amp >= 0) {
                /* the improved methods only used, if the device parameter used and from FindSyncAnd allowed */

                inVals[2] = inVal ;
                /* check, if the sample value before was an amplitude */
                ampd = DetectAmpsFromVals (inVals, &ampd_min, &ampd_max, &last_ampd, &dampd_min) ;

                if (ampd != 0 ) {

                    if (ampd > 0 && !(last_ampd > 0) ) { /* was a real maximum */
                        if ( !ptrFile->sync_bit ) { /* value difference stat data */
                            ptrFile->ampd_sum += inVals[1] - ampd_min ;
                            ++ptrFile->ampd_cnt ;
                        }
                    }
                    else if (ampd < 0 && !(last_ampd < 0) ) { /* was a real minimum */
                        if ( !ptrFile->sync_bit ) { /* value difference stat data */
                            ptrFile->ampd_sum += ampd_max - inVals[1] ;
                            ++ptrFile->ampd_cnt ;
                        }
                    }
                    last_ampd = ampd ; /* amplitude found (all pos one sample before exactly) */
                }

                /* shift left sample values for the next amplitude detection */
                inVals[0] = inVals[1] ;
                inVals[1] = inVal ;//[2]

                /* Compensation of some errors, when the mean level of the signal may swing */
                if (rate_amp > 0) AmplifySampleValue ( &inVal, &ampd_min, &ampd_max, &last_ampd, ptrFile) ;
            }

            if ( (Qcnt == 0) && IsDbgWavTime(0x10000, ptrFile) ) {

                if (ampd > 0 ) printf("^") ;
                else if  (ampd < 0 ) printf("v") ;

                if (rate_amp > 0) {
                    if (inVal < 0) printf("~%02X>-%03X", inVals[2], -inVal) ;
                    else printf("~%02X>+%03X", inVals[2], inVal) ;
                }
                else printf("~%02X", inVal) ;
                if (((stell( ptrFile)- (long) ptrFile->bgnSamples)/ ptrFile->blockAlign) % 8 == 0 )
                    printf("[%.5lf] ", WavTime(ptrFile)) ;
            }

            if (ii==0) bVal = inVal ;
            isTrans = false ;

            /* This is the classic algorithm of Wav2bin extended to length based reading */

            if (sign > 0) {
                if (inVal > Trans_High) {
                    continue ;
                }
                if (inVal < Trans_Low) {
                    sign = -1;
                    isTrans = true ;
                    ++ trans ;
                }
            }
            else if (sign < 0) {
                if (inVal < Trans_Low) {
                    continue ;
                }
                if (inVal > Trans_High) {
                    sign = 1;
                    isTrans = true ;
                    ++ trans ;
                }
            }
            else {
                if (inVal < Trans_Low) {
                    sign = -1;
                    isTrans = true ;
                    ++ trans ;
                }
                if (inVal > Trans_High) {
                    sign = 1;
                    isTrans = true ;
                    ++ trans ;
                }
            }
            if (isTrans) {

                if ( trans == 2 ) {
                    *ptrAmpL1 = ii - last_tpos ;
                    if (ptrFile->sync_bit) {
                        *ptrAmpL2 = TRANS_MID - sign ; /* return last phase */
                        break ;
                    }
                }
                else if ( trans == 3 ) {
                    *ptrAmpL2 = ii - last_tpos ;
                    break ;
                }
                last_tpos = ii ;
            }
        }   // end for, sample values of a bit

        /* Interpolation with scaled ampL was not necessary for E-series, but Qtape needs this */
        sign = AmplitudesBorderInterpolation (sVal, bVal, lastVal, inVal, ptrFile) ;

        if ( (Qcnt == 0) && IsDbgWavTime(0x10000, ptrFile) ) {
            printf(" %ld: %3lu+%i/%3lu,  %.5lf s\n", (stell( ptrFile)- (long) ptrFile->bgnSamples)/ ptrFile->blockAlign,
               *ptrAmpL1, sign, *ptrAmpL2, WavTime(ptrFile)) ;
        }
        else if ( ( IsDbgWavTime( 0x0001, ptrFile)  // || position > Debug_Position
            ) && (Qcnt == 0) ) {
            printf(" %lu%+1i/%lu", *ptrAmpL1, sign, *ptrAmpL2) ;
//            PrtWavTime (ptrFile) ;
        }

        *ptrAmpL1 += sign ;

    } // end if: No end of audio data
    return (error);
}

/* Move the position in the wav file exactly before the first amplitude of the start bit */
/* Precondition: The rough positioning was done with the robust method for the old Pocket Computer. */
/* Read operations for 1600 / E-/ G-Series but also for PC-1500 Quick-Tape must be initiated with this routine.*/

int SyncStartBitFromEWav ( uint* ptrStart_Amp, FileInfo*  ptrFile)
{
    ulong ampL1, ampL2 , tmpL, ampLenMid = ptrFile->wavLenMid >>1 ;
    uint  ii, jj, imax = 10 ; /* 6 amps possible (-)tolerance + 4 amps rewind + 1 amp of start-bit -1 (ii start) */
    long position, bgnSearch ;
    int  rwd = 0 ;
    int  error = ERR_OK ;

    ptrFile->sync_bit = true ; /* flag for ReadAmpFromEWav */

    if ( ( (ptrFile->debug & 0x10001) > 0 ) && (Qcnt == 0) ) { // || position > Debug_Position, position=stell(ptrFile);
            if (IsDbgWavTime(0x10001, ptrFile) ) printf(" *s(");
            if (IsDbgWavTime(0x10000, ptrFile) ) printf("\n");
    }
    bgnSearch = stell( ptrFile ) ;
    if (bgnSearch <= 0) {
        printf ("\n%s:syncE_1 - Can't ftell the wav file\n", argP) ;
        return ( ERR_FILE ) ;
    }

    jj = 1 ;
    do {
        /* Rewind */
        rwd = ptrFile->wavLenMin *2 * jj ; /* long sync is not exact, rewind two waves (short bits) */
        error = sseek (ptrFile, bgnSearch -rwd * (long) ptrFile->blockAlign, SEEK_SET) ; /*rewind to start position */
        if (error != ERR_OK) {
            printf ("\n%s:syncE - Can't seek the file\n", argP) ;
            return ( ERR_FILE ) ;
        }

        ii = -1 ;
        /* adjust the position in the wav file between last sync and to left the start bit */
        do {
            ++ii ;
            position = stell( ptrFile ) ;
            if (position <= 0) {
                printf ("\n%s:syncE - Can't ftell the wav file\n", argP) ;
                return ( ERR_FILE ) ;
            }

            error = ReadAmpFromEWav ( &ampL1, &ampL2, ptrFile);
            if (error != ERR_OK) break ;
            *ptrStart_Amp = ampL2 ;     /* sign of phase */

            if (ampL1 >= ampLenMid) {
                tmpL = ampL1;
                error = ReadAmpFromEWav ( &ampL1, &ampL2, ptrFile);
                if (error != ERR_OK) break ;
                ampL1 += tmpL;
            }
            else

                ampL1 <<= 1 ; /* ampL -> wavLen */

        } while (ampL1 <= ptrFile->wavLenMid && ii < imax ) ;   /* start bit not found and not too much amps */
        if   (   ampL1 > ptrFile->wavLenMid && ii > 0 ) break ; /* ii>0 because: read one short first */

        imax = 5 ; /* 1 amps tolerance + 4 amps rewind + 1 amp of start-bit -1 (ii) */

    } while ( jj++ < SYNC_TR_TOL && error == ERR_OK) ;

    if (error != ERR_OK) return (error) ;
    if ( jj >= SYNC_TR_TOL) {
        printf ("\n%s:syncE - Can't find the start bit position around %.5lf s\n", argP, WavTime(ptrFile)) ;
        error = ERR_SYNC ;
    }
    else {
        /* Rewind to the begin of the StartBit */
        error = sseek (ptrFile, position, SEEK_SET) ; /*rewind to start position */
        if (error != ERR_OK) {
            printf ("\n%s:syncE - Can't seek the file: %ld\n", argP, position) ;
            error = ERR_FILE ;
        }

    }
    if (Qcnt == 0 && error == ERR_OK && (ptrFile->debug & 0x700)>0 )
        printf ("Start bit position at %.5lf s\n", WavTime(ptrFile)) ;

    if ( ( (ptrFile->debug & 0x10001) > 0 ) && (Qcnt == 0) ) {  // || position > Debug_Position
            if (IsDbgWavTime(0x10001, ptrFile) ) printf(")s ");
            if (IsDbgWavTime(0x10000, ptrFile) ) printf("\n");
    }

    ptrFile->sync_bit = false ;

    return (error);
}


int SkipBitFromQWav ( uint bitmax, FileInfo*  ptrFile)
{
    ulong ampL1, ampL2, //tmpL,
          ampLenMid = ptrFile->wavLenMid >>1 ;
    uint  ii, imax ;
    long position ;
    int  error = ERR_OK ;

    imax = bitmax * (Wav_Nb_Bit1 <<1) + 1 ; /* Bits to amps */
    ptrFile->sync_bit = true ; /* flag for ReadAmpFromEWav */

    if ( ( (ptrFile->debug & 0x10001) > 0 ) && (Qcnt == 0) ) { // || position > Debug_Position, position=stell(ptrFile);
            if (IsDbgWavTime(0x10001, ptrFile) ) printf(" *sk(");
            if (IsDbgWavTime(0x10000, ptrFile) ) printf("\n");
    }
    ii = -1 ;
    /* skip bits and adjust the position in the wav file to left between last sync and the start bit */

    do {
        ++ii ;
        position = stell( ptrFile ) ;
        if (position <= 0) {
            printf ("\n%s:skipQ - Can't ftell the wav file\n", argP) ;
            return ( ERR_FILE ) ;
        }

        error = ReadAmpFromEWav ( &ampL1, &ampL2, ptrFile);
        if (error != ERR_OK) break ;

        if (ampL1 > ampLenMid || (ampL1 == ampLenMid && ampL2 == ptrFile->start_amp) ) {

            /* read always two amps in this case */
            error = sseek (ptrFile, position, SEEK_SET) ; /*rewind to start position */
            if (error != ERR_OK) {
                printf ("\n%s:skipQ - Can't seek the file: %ld\n", argP, position) ;
                error = ERR_FILE ;
            }
            ptrFile->sync_bit = false ;
            error = ReadAmpFromEWav ( &ampL1, &ampL2, ptrFile);
            if (error != ERR_OK) break ;

            ampL1 += ampL2;
            ptrFile->sync_bit = true ;
        }
        else
            ampL1 <<= 1 ;

    } while (ampL1 <=  ptrFile->wavLenMid && ii < imax ) ;
    if (error != ERR_OK) return (error) ;

    if ( (ii > 0) && IsDbgWavTime( 0x0008, ptrFile) && (Qcnt == 0) )
            printf (" Skip %d amps\n", ii) ;

    if   (   ampL1 < ptrFile->wavLenMid ) {
        printf ("\n%s:skipQ - Can't find the start bit position around %.5lf s\n", argP, WavTime(ptrFile)) ;
        error = ERR_SYNC ;
    }
    else {
        /* Rewind to the begin of the StartBit */
        error = sseek (ptrFile, position, SEEK_SET) ; /*rewind to start position */
        if (error != ERR_OK) {
            printf ("\n%s:skipQ - Can't seek the file: %ld\n", argP, position) ;
            error = ERR_FILE ;
        }
    }
    if (Qcnt == 0 && error == ERR_OK && (ptrFile->debug & 0x700)>0 )
        printf ("Start bit position of block at %.5lf s\n", WavTime(ptrFile)) ;

    if ( ( (ptrFile->debug & 0x10001) > 0 ) && (Qcnt == 0) ) { // || position > Debug_Position
            if (IsDbgWavTime(0x10001, ptrFile) ) printf(")sk ");
            if (IsDbgWavTime(0x10000, ptrFile) ) printf("\n");
    }
    ptrFile->sync_bit = false ;

    return (error);
}


/* shifts the start position in the wav file to right or left for a optimal window of transitions for Bit_1 or Bit_0 */
int SyncBitFromWav (int  sign,          /* sync 1 to high bit or -1 to low or 0 StartBit */
                    ulong*  ptrTrans,
                    ulong*  ptrAmps,
                    ulong*  ptrLimit,
                    FileInfo*  ptrFile)
{
    uint  ii, jj ;
    long position, position2 ;
    int  tmp = 0 ;
    int  error ;
    uint  imax   = *ptrLimit;

    ptrFile->sync_bit = true ;

    if ( ( (ptrFile->debug & 0x10001) > 0 ) && (Qcnt == 0) ) { // || position > Debug_Position, position=stell(ptrFile);
            if (IsDbgWavTime(0x10001, ptrFile) ) {
                if (sign > 0 ) printf(" +s("); else if (sign < 0 ) printf(" -s("); else printf(" *s(");
            }
            if (IsDbgWavTime(0x10000, ptrFile) ) printf("\n");
    }
    if ( IsDbgWavTime( 0x0002, ptrFile) && (Qcnt == 0) ) { // printf ("%.5lf ", WavTime(ptrFile));
        if (sign > 0 ) printf("."); else if (sign < 0 ) printf("o"); else printf("*");
        if (sign == 0) {
            if ( (ptrFile->debug & TRANS_OLD) > 0)
                printf("   -> ");
            else
                printf("       -> ");
        }
        else {
            if ( (ptrFile->debug & TRANS_OLD) > 0)
                printf("%2lu -> ", *ptrTrans);
            else
                printf("%2lu(%2lu) -> ", *ptrTrans, *ptrAmps);
        }
    }

    position = stell( ptrFile ) ;
    if (position <= 0) {
            printf ("\n%s:sync - Can't ftell the wav file\n", argP) ;
            return ( ERR_FILE ) ;
    }
    if ( sign == 0) {
            /* Sync StartBit to Bit_MID,  Rewind a half bit */
            tmp = ptrFile->bitLen/2  ; // tmp = (ptrFile->bitLen +1)/3 ; /* Rewind (1 -1/3) bit  */
            error = sseek (ptrFile, tmp * (long) ptrFile->blockAlign, SEEK_CUR) ;
            if (error != ERR_OK) {
                printf ("\n%s:sync1 - Can't seek the file\n", argP) ;
                return ( ERR_FILE ) ;
            }
    }

    /* first search for Bit_1 or Bit_0 exactly, if not successful then accept one or two transition less */
    jj = 0 ;
    do { /* first sync is done classic to the point, then get what is possible */
        if ( sign !=0 && jj < 2 ) ii = 1 ;
        else ii = 0 ; /* First read the bit again to check if conditions for j>=2 are met */
        do {
            if ( (ii % 2) == 0 )
                tmp = - ptrFile->bitLen + ii ;
            else
                tmp = - ptrFile->bitLen - ii ;

            /* check for that not coming outside bgnSamples and endSamples is done one higher level */
            error = sseek (ptrFile, tmp * (long) ptrFile->blockAlign, SEEK_CUR) ;
            if (error != ERR_OK) {
                printf ("\n%s:sync2 - Can't seek the file\n", argP) ;
                error = ERR_FILE ;
                break ;
            }
            error = ReadBitFromWav (ptrTrans, ptrAmps, ptrFile);
            if (error != ERR_OK) break ;

            /* support sync with result of bit reading method 2 in cases of poor signal quality */
            if (jj == 2 ) {
                if (sign >  0 && *ptrAmps - 1 > *ptrTrans ) *ptrTrans = *ptrAmps - 1 ;
                if (sign <  0 && *ptrAmps + 1 < *ptrTrans ) *ptrTrans = *ptrAmps + 1 ;
                if (sign == 0 ) {
                    if (*ptrTrans < Bit_MID && *ptrAmps < Bit_MID ) {
                        if ( *ptrAmps - 1 > *ptrTrans ) *ptrTrans = *ptrAmps - 1 ;
                    }
                    else if (*ptrTrans > Bit_MID && *ptrAmps > Bit_MID ) {
                        if ( *ptrAmps + 1 < *ptrTrans) *ptrTrans = *ptrAmps + 1 ;
                    }
                    else  *ptrTrans = (*ptrAmps + *ptrAmps +1)/2 ;
                }
            }
            else if (jj > 2 ) {
                /* not real synced, but hopes, that the following audio data will be better*/
                if (sign > 0 && *ptrAmps > *ptrTrans ) *ptrTrans = *ptrAmps ;
                if (sign < 0 && *ptrAmps < *ptrTrans ) *ptrTrans = *ptrAmps ;
                if (sign == 0 ) {
                    if (*ptrTrans < Bit_MID && *ptrAmps < Bit_MID ) {
                        if ( *ptrAmps > *ptrTrans ) *ptrTrans = *ptrAmps ;
                    }
                    else if (*ptrTrans > Bit_MID && *ptrAmps > Bit_MID ) {
                        if ( *ptrAmps < *ptrTrans) *ptrTrans = *ptrAmps ;
                    }
                    else  *ptrTrans = (*ptrAmps + *ptrAmps +1)/2 ;
                }
            }

            ++ii;

        } while ( (ii < imax + 0) &&
                 ( ( (sign >  0) && (*ptrTrans < Bit_1 - jj) ) ||
                   ( (sign <  0) && (*ptrTrans > Bit_0 + jj) ) ||
                   ( (sign == 0) && ((*ptrTrans > Bit_MID + jj) || (*ptrTrans < Bit_MID - jj)) )
                 )) ;
        if (error != ERR_OK) break ;

        if ( (sign >  0 && *ptrTrans < Bit_1 - jj) ||
             (sign <  0 && *ptrTrans > Bit_0 + jj) ||
            ((sign == 0) && ((*ptrTrans > Bit_MID + jj) || (*ptrTrans < Bit_MID - jj)) )
           ) {
            /* no sync found */
            *ptrLimit = 0 ;
            error = sseek (ptrFile, position, SEEK_SET) ; /*rewind to start position */
            if (error != ERR_OK) {
                printf ("\n%s:sync3 - Can't seek the file: %ld\n", argP, position) ;
                error = ERR_FILE ;
                break ;
            }
            ++jj ;
        }
        else {
            *ptrLimit = ii ; /* steps left + right needed for syncing */
            if (jj > 1 && ptrFile->synching == 0 && sign != 0 ) {
                if ( *ptrTrans > Bit_0 + 2 && *ptrTrans < Bit_1 - 2 ) {
                    if (Qcnt == 0)
                        printf ("Signal synchronisation error: %lu transitions before %.5lf s\n", *ptrTrans, WavTime(ptrFile));
                    error = count_errors( ERR_SYNC, ptrFile );
                    if (error != ERR_OK) break ;
                }
                else if (*ptrTrans > Bit_0 + 1 && *ptrTrans < Bit_1 - 1 ){
                    ++ ptrFile->wrn_cnt ;
                    if (Qcnt == 0) {
                        if ((ptrFile->debug & (0x41F | IGN_ERR_SUM) ) > 0)
                            printf ("Poorly synchronised signal: %lu trans. before %.5lf s\n", *ptrTrans, WavTime(ptrFile));
                        else if ((ptrFile->debug & 0x60 ) > 0) printf ("!");
                    }
                }
            }
        }

    } while ( *ptrLimit == 0 && jj <= SYNC_TR_TOL ) ;
    if (error != ERR_OK) return (error) ;

    if ( sign == 0) {
            /* Rewind 1 -3/8 to the begin of the start bit (3 high waves in 12 trans included) */
            tmp = -( ( ptrFile->bitLen *5) >>3) ;
            /* adjust the position in the wav file between last sync and to left of the start bit exactly */
            error = sseek (ptrFile, tmp * (long) ptrFile->blockAlign, SEEK_CUR) ;
            if (error != ERR_OK) {
                printf ("\n%s:sync4 - Can't seek the file\n", argP) ;
                return ( ERR_FILE ) ;
            }
    }

    if ( IsDbgWavTime( 0x0002, ptrFile) && (Qcnt == 0) ) {
        position2 = stell( ptrFile ) ;
        printf("%+3i samples -> ", (int) (position2 - position) / (int) ptrFile->blockAlign); //(int) ptrFile->bitLen + tmp
        if ( (ptrFile->debug & TRANS_OLD) > 0)
            printf("%2lu", *ptrTrans);
        else
            printf("%2lu(%2lu)", *ptrTrans, *ptrAmps);
        if ( (ptrFile->debug & 0x10000)==0) printf (" [%.5lf] ", WavTime(ptrFile));
        if ( (ptrFile->debug &  0x0001)==0) printf ("\n");
    }
    if ( ( (ptrFile->debug & 0x10001) > 0 ) && (Qcnt == 0) ) { // || position2 > Debug_Position
            if (IsDbgWavTime(0x10001, ptrFile) ) printf(")s ");
            if (IsDbgWavTime(0x10000, ptrFile) ) printf("\n");
    }

    ptrFile->sync_bit = false ;

    return (error);
}


int ReadBitFieldFromEWav (ulong  nbBits,
                          char*  ptrBits,
                      FileInfo*  ptrFile)
{
     uint  ii ;
    ulong  ampL1, ampL2, wavLen ;
      int  error ;

    if ( IsDbgWavTime( 0x0004, ptrFile) && (Qcnt == 0) && (ptrFile->synching == 0) ) {
        if ( nbBits>1 ) printf ("\nBits") ;
        else if ((ptrFile->debug & 0x0008)==0) printf (" ") ;
    }

    for ( ii = 0 ; ii < nbBits ; ++ii ) {

        error = ReadAmpFromEWav ( &ampL1, &ampL2, ptrFile);
        if (error != ERR_OK) break ;

        wavLen = ampL1 + ampL2 ;
        if ( ampL1 == 0 || ampL2 == 0 || wavLen > ptrFile->wavLenMax *3/2 ) {
            /* end of transmission found */
            error = ERR_NSYNC ;
            break ;
        }

        if (wavLen < ptrFile->wavLenMid)
            ptrBits[ii] = 0;     /* Bit a 0 */
        else
            ptrBits[ii] = 1;     /* Bit a 1 */

        if ( IsDbgWavTime( 0x0004, ptrFile) && (Qcnt == 0) && ( nbBits>1 || (ptrFile->debug & 0x0008)==0) )
            printf (" %d", ptrBits[ii]) ;
    } // next ii
//    if ( IsDbgWavTime( 0x0004, ptrFile) && (Qcnt == 0) && (ptrFile->synching == 0) )
//        printf ("\n") ;

    return (error);
}


int ReadBitFieldFromQWav (ulong  nbBits,
                          char*  ptrBits,
                      FileInfo*  ptrFile)
{
     uint  ii ;
    ulong  ampL1, ampL2, wavLen ;
      int  error ;

    if ( IsDbgWavTime( 0x0004, ptrFile) && (Qcnt == 0) && (ptrFile->synching == 0) ) {
        if ( nbBits>1 ) printf ("\nBits") ;
        else if ((ptrFile->debug & 0x0008)==0) printf (" ") ;
    }

    for ( ii = 0 ; ii < nbBits ; ++ii ) {

        error = ReadAmpFromEWav ( &ampL1, &ampL2, ptrFile);
        if (error != ERR_OK) break ;

        wavLen = ampL1 + ampL2 ;
        if ( ampL1 == 0 || ampL2 == 0 || wavLen > ptrFile->wavLenMax *3/2 ) {
            /* end of transmission found */
            error = ERR_NSYNC ;
            break ;
        }

        if (wavLen < ptrFile->wavLenMid) {
            ptrBits[ii] = 1;     /* Bit a 1 */

            error = ReadAmpFromEWav ( &ampL1, &ampL2, ptrFile); // BITL_Q wavs
            if (error != ERR_OK) break ;

            wavLen = ampL1 + ampL2 ;
            if ( wavLen > ptrFile->wavLenMid ) {
                    error = count_errors( ERR_SYNC, ptrFile );
                    printf (" Incomplete signal for bit 1 found before %.5lf s.\n", WavTime(ptrFile));
            }
        }
        else
            ptrBits[ii] = 0;     /* Bit a 0 */

        if ( IsDbgWavTime( 0x0004, ptrFile) && (Qcnt == 0) && ( nbBits>1 || (ptrFile->debug & 0x0008)==0) )
            printf (" %d", ptrBits[ii]) ;
    } // next ii
//    if ( IsDbgWavTime( 0x0004, ptrFile) && (Qcnt == 0) && (ptrFile->synching == 0) )
//        printf ("\n") ;

    return (error);
}


/* Cycled use of functions ReadBitFieldFromWav := FindFreqAndSyncFromWav := FindSyncFromWav := SkipBitsFromWav := ReadBitFieldFromWav
   int FindFreqAndSyncFromWav (FileInfo*  ptrFile);
   recursive call was dissolved */

int ReadBitFieldFromWav (ulong  nbBits,
                         char*  ptrBits,
                         FileInfo*  ptrFile)
{
     uint  ii , jj ;
    ulong  trans, amps, atrans ;
    ulong  limit ;
     long  position ;
     bool  isPc15, isPc15Q, isPc121, isStart, isStop, isSkip ;
      int  error ;

    if ( IsDbgWavTime( 0x0004, ptrFile) && (Qcnt == 0) && (ptrFile->synching == 0) ) {
        if ( nbBits>1 ) printf ("\nBits") ;
        else if ((ptrFile->debug & 0x0008)==0) printf (" ") ;
    }
    isPc15  = ptrFile->base_freq == Base_FREQ2 || pcgrpId == IDENT_PC1500 ; /* also for Qtape to help to detect the 1. data block start bit */
    isPc15Q = ptrFile->base_freq == Base_FREQ4 && Bit_1 == BIT_1_Q ;        /* Qtape 2. block syncing */
    isPc121 = ptrFile->base_freq == Base_FREQ1 && pcgrpId == IDENT_PC1211 ; /* last skip bit not with bit length, sync start bit */
    isSkip  = (nbBits == 1 ) ;
    isStart = (nbBits == 6 ) ; /* in case of some transmission errors ReadQuater does not read the start bit */
    if ( isStart && ptrFile->skip_bits > 0 ) {
        /* This prohibits the error, where the bit position is shifted half a bit in cases */
        /* if an additional amplitude sits in the middle of the start bit and a Bit_0 follows */
        limit = ptrFile->bitLen ;
        /* set more precise position to the begin of the start bit */
        error = SyncBitFromWav (0, &trans, &amps, &limit, ptrFile);
        if (error != ERR_OK) return (error) ;
    }
    for ( ii = 0 ; ii < nbBits ; ++ii , isStart = false ) {
        isStop = (nbBits > 1 && ii == nbBits - 1) ;
        ptrBits[ii] = -1;     /* Bit unread */

        error = ReadBitFromWav (&trans, &amps, ptrFile);
        if (error != ERR_OK) break ;

        position = stell( ptrFile ) ;
        if (position <= 0) {
            printf ("\n%s:rbits - Can't ftell the wav file\n", argP) ;
            return ( ERR_FILE ) ;
        }

        /* weight values from different calculation methods */
        // New controlled by ReadBitParameterAdj
        if ( ptrFile->amp_weight < 50 ) atrans = (amps + trans * 2 + 1 )/3 ;/* trans better */
        else atrans = (amps * 2 + trans + (isPc15? 0:2) )/3 ; /* rounding different because of different problematic frequencies */

        if (atrans == Bit_MID ) {                   /* This may correct some errors in following situations */
            if      (atrans == trans && amps > Bit_MID) ++atrans ; /* compensate lost transitions on border of the bit */
            else if (atrans == trans && amps < Bit_MID) --atrans ; /* compensate one little peek that splits an amplitude */
            else if (isPc15) --atrans ;             /* PC-1500 low frequency is more problematic with amps split */
            else ++atrans ;                         /* other PCs: High Freq is more problematic with lost amplitudes, DC */
        }

        if  (((atrans > Bit_MID)
                && !isStart ) || isStop ) {        /* first stop bit after a quarter here read */

            /* Bit 1 processing */
            if (trans < Bit_1) {
                jj = 0 ;
                do {
                    /* try to shift the position to a optimal window for a bit 1 */
                    limit = ptrFile->bitLen ;
                    if ( ii != 0 && !isStop ) limit >>=1 ; /* don´t shift to much in case of signal errors */
                    error = SyncBitFromWav (1, &trans, &amps, &limit, ptrFile);
                    if ( !isStop || limit !=0 || error != ERR_OK) break ;
                    ++jj ; /* transmission error, search the next stop bit */
                    error = ReadBitFromWav (&trans, &amps, ptrFile);
                    if ( trans >= Bit_1 || amps >= Bit_1 ) limit = 1 ;

                } while ( jj < 11 && error == ERR_OK && limit == 0 );
                if (error != ERR_OK) break ;

                if (limit == 0) {
                    printf ("\n%s: ERROR: Synchro %lu Hz bit1 lost at %.5lf s after %lu transitions/b\n", argP, ptrFile->freq, WavTime(ptrFile), trans) ;
                    // error = ERR_NSYNC ;
                    // break ;
                    trans = atrans ;
                    error = count_errors( ERR_NSYNC, ptrFile );
                    error = sseek (ptrFile, position, SEEK_SET) ; /*rewind to last position */
                    if (error != ERR_OK) {
                        printf ("\n%s:rbits2 - Can't seek the file: %ld\n", argP, position) ;
                        error = ERR_FILE ;
                    }
                }
                else if ( jj  > 0 ) {
                    printf ("Synchro Stopbit1, %i bits lost before %.5lf s\n", jj , WavTime(ptrFile)) ;
                    error = count_errors( ERR_SYNC, ptrFile );
                }
            }
        }
        else {

            /* Bit 0 processing */
            if (trans > Bit_0 ) {
                jj = 0 ;
                do {
                    /* try to shift the position to a optimal window for a bit 0 */
                    limit = ptrFile->bitLen ;
                    /* EndOfSkip == StartBit of nibble is supported by a separate sync procedure */
                    if ( ii != 0 || isStart || (!isPc121 && isSkip) ) limit >>=1 ; /* don´t shift to much */
                    error = SyncBitFromWav (-1, &trans, &amps, &limit, ptrFile);
                    if ( !isStart || limit !=0 || error != ERR_OK) break ;

                    ++jj ; /* transmission error, search the next start bit */
                    error = ReadBitFromWav (&trans, &amps, ptrFile);
                    if ( trans <= Bit_0 || amps <= Bit_0 ) limit = 1 ;

                } while ( jj < 11 && error == ERR_OK && limit == 0 );
                if (error != ERR_OK) break ;

                if (limit == 0) {
                    printf ("\n%s: ERROR: Synchro %lu Hz bit0 lost at %.5lf s after %lu transitions/b\n",
                            argP, ptrFile->freq, WavTime(ptrFile), trans) ;
                    // error = ERR_NSYNC ;
                    // break ;
                    trans = atrans ;
                    error = count_errors( ERR_NSYNC, ptrFile );
                    error = sseek (ptrFile, position, SEEK_SET) ; /*rewind to last position */
                    if (error != ERR_OK) {
                        printf ("\n%s:rbits3 - Can't seek the file: %ld\n", argP, position) ;
                        error = ERR_FILE ;
                    }
                }
                else if ( jj  > 0 ) {
                    printf ("Synchro Startbit0, %i bits lost before %.5lf s\n", jj , WavTime(ptrFile)) ;
                    error = count_errors( ERR_SYNC, ptrFile );
                }
                else if ( isSkip && isPc15Q && trans == Bit_MID ) {
                    ++trans ; /* start bit not found,  suppose this is was a sync bit with trans at border */
                }
            } // end if: trans > Bit_0

            else if ( trans < Bit_LOW && amps < Bit_LOW) {
                /* end of transmission or a gap found */
                if ( ptrFile->status != STAT_EOT && ptrFile->synching == 0 ) {  /* FindSync will retry on a higher level */

                    error = ReadBitFromWav (&trans, &amps, ptrFile);    /* read bit after the assumed gap */
                        if (error != ERR_OK) break ;

                    error = sseek (ptrFile, position, SEEK_SET) ; /*rewind to last position */
                    if (error != ERR_OK) {
                        printf ("\n%s:rbits4 - Can't seek the file: %ld\n", argP, position) ;
                        error = ERR_FILE ;
                        break ;
                    }
                }   /* try again after one bit length, to test if it's only a one bit gap or more */
                if ( trans < Bit_LOW2 && amps < Bit_LOW2) { /* if the bit after also low trans */
                        if (Qcnt == 0 ) {
                            if (ptrFile->debug >0)
                                printf ("\n%s: Synchronisation %lu Hz ended at %.5lf s after %lu transitions/bit\n",
                                argP, ptrFile->freq, WavTime(ptrFile), trans) ;
                            else printf ("\n%s: Synchronous transmission ended at wav time %.5lf sec\n", argP, WavTime(ptrFile)) ;
                        }
                        error = ERR_NSYNC ;
                        break ;
                }
                else {
                    error = count_errors( ERR_SYNC, ptrFile );
                    printf ("Gap in signal found before %.5lf s, one bit lost, padded with bit 0.\n", WavTime(ptrFile));
                    trans = 0 ;
                }

            } // end if: gap or end of transmission
        } // end if: Bit 0
        if (error != ERR_OK) break ;
        /*  return FindFreqAndSyncFromWav( ptrFile );
            restart moved to higher level */

        if (trans > Bit_MID)
            ptrBits[ii] = 1;     /* Bit a 1 */
        else
            ptrBits[ii] = 0;     /* Bit a 0 */

        if ( IsDbgWavTime( 0x0004, ptrFile) && (Qcnt == 0) && ( nbBits>1 || (ptrFile->debug & 0x0008)==0) )
            printf (" %d", ptrBits[ii]) ;
    } // next ii
//    if ( IsDbgWavTime( 0x0004, ptrFile) && (Qcnt == 0) && (ptrFile->synching == 0) )
//        printf ("\n") ;

    return (error);
}

/* forward synch bits or stop bits */
int SkipBitsFromWav (ulong*  ptrNb,
                     FileInfo*  ptrFile)
{
      int  ii ;
      int  max_ii ;
     char  bit ;
//    ulong  sum_trans = 0 ;
     long  position ;
      int  error ;

    position = stell( ptrFile );
    if (position <= 0) {
            printf ("\n%s:skip - Can't ftell the wav file\n", argP) ;
            return ( ERR_FILE ) ;
    }

    if ( ( (ptrFile->debug & 0x10001) > 0 ) && (Qcnt == 0) ) { // || position > Debug_Position
            if (IsDbgWavTime(0x10001, ptrFile) ) printf("...");
            if (IsDbgWavTime(0x10000, ptrFile) ) printf("\n");
    }

    do {
        max_ii = ptrFile->synching ? SYNC_BIT_MAX : Stop_Bit_Max ;
        *ptrNb = 0 ;
        ii = 0 ;
        do {                        // Skip sync bits or stop bits

            error = ReadBitFieldFromWav (1, &bit, ptrFile) ;
            if (error != ERR_OK) break ;
            ++ii ;

        } while (bit > 0 && ii < max_ii ) ;
        if (error != ERR_OK) break ;

        if ( bit > 0 ) {
            /* max_ii read, new long synch required */
            error = sseek (ptrFile, position, SEEK_SET) ;
            if (error != ERR_OK) {
                printf ("\n%s:skip - Can't seek the file: %ld\n", argP, position) ;
                error = ERR_FILE ;
                break ;
            }
            /* Restart moved to a higher level, no recursion */
            /* return FindFreqAndSyncFromWav( ptrFile ); */
            *ptrNb = ii ;
            return ( ERR_NSYNC ) ;
        }
        /* else  Rewind before the beginning of a start bit or where sync was lost */
        --ii ;
        error = sseek (ptrFile, - (long) (ptrFile->bitLen * ptrFile->blockAlign), SEEK_CUR) ;
        if (error != ERR_OK) {
            printf ("\n%s:skip - Can't seek the file: %ld\n", argP, position) ;
            error = ERR_FILE ;
            break ;
        }

        ptrFile->skip_bits = ii ;
        *ptrNb = ii ;
        if ( (ii > 0) && IsDbgWavTime( 0x0008, ptrFile) && (Qcnt == 0) )
            printf (" Skip %d ", ii) ;

     /*  An accurate determination of the rate and frequency of the recording would be realizable here
         if that would be read over the entire length the number of transitions again,
         without that the position would be changed by sync in the meantime - NOT implemented. */

    } while (0) ;

    return (error) ;
}


ulong BitLen (uint byte_nbits, FileInfo*  ptrFile)
{
ulong bitLen ;
    /* Calculate the number of WAV samples for one bit of the pocket file */
    /* for newer series only used for sync and FindAmp */
    bitLen = (( ptrFile->wav_freq * Wav_Nb_Bit1 * 2) / ptrFile->freq + 1)/2 ; // with rounding
    if (byte_nbits > 0) ptrFile->byteLen = \
             (( ptrFile->wav_freq * Wav_Nb_Bit1 * byte_nbits * 2) / ptrFile->freq + 1)/2 ; // with rounding

    /* Len not for 16/G/E-Series but also for Qtape */
    ptrFile->wavLenMax = (( ptrFile->wav_freq * Bit_1 / Bit_0 * 2) / ptrFile->freq + 1)/2 ;
    ptrFile->wavLenMin = ptrFile->wavLenMax/2;
    ptrFile->wavLenMid= (ptrFile->wavLenMin + ptrFile->wavLenMax +1)/2 ;

    /* Calculate the minimum number of samples between to amps, time filter  */
    Amp_Dpos_Bas = ( ptrFile->wav_freq / ptrFile->freq + 1)/2 ; // with rounding
    Amp_Dpos_Max = ( ptrFile->wav_freq * Wav_Nb_Bit1 * AMP_DPOS_MAXB /BIT_0 /ptrFile->freq + 1)/2 ; // more than Bit_0
    Amp_Dpos_Min = ( ptrFile->wav_freq / ptrFile->freq + 1)/4 ;// half of Bit_1
    if (Amp_Dpos_Min > 1) --Amp_Dpos_Min ;

    return ( bitLen ) ;
}


int FindSyncFromWav (ulong*  ptrNb,
                     FileInfo*  ptrFile)
{
      int  ii, jj, kk = 0 ;
      int  cntBit_1, bitLenTol=0 ;
    ulong  bitLen_before ;
    ulong  sum_trans ;
    ulong  trans, amps, Tol ;
    ulong  limit ;
     long  position ;
     long  MinPosSync ;
      int  error ;

    do {
        *ptrNb = 0  ;
        Tol = 1 ;
        if (devId == DEV_EMU) Tol += 2; /* Emulator needs more speed tolerance */

        /* Calculate the number of WAV samples for one bit of the pocket file */
        ptrFile->bitLen = BitLen (0, ptrFile) ;

        position = stell( ptrFile ) ;
        if (position <= 0) {
            printf ("\n%s:fsync - Can't ftell the wav file\n", argP) ;
            return ( ERR_FILE ) ;
        }
        if ( (ulong) position + ptrFile->bitLen * ptrFile->blockAlign -1 > ptrFile->endSamples ) {
            if (Qcnt == 0 || ptrFile->debug != 0) printf ("%s:Found no (new) Sync - End of audio data reached\n", argP) ;
            return ( ERR_EOF ) ;
        }

        if ( ( (ptrFile->debug & 0x0100) > 0 ) && (Qcnt == 0) ) printf ("Searching frequency %lu, transitions: ", ptrFile->freq ) ;
        else if (ptrFile->debug != 0 && Qcnt == 0 ) printf ("\nTrying to synchronise %lu Hz ", ptrFile->freq);
        ii = 0; /* how often tried to sync */
        do {
            cntBit_1 = 0 ;
            do { /* frequency and bitLen calculation */
                ++ii ;
                bitLen_before = ptrFile->bitLen ;
                MinPosSync = ptrFile->bgnSamples + (bitLen_before + 1) * ptrFile->blockAlign * 3/2 ; // SyncBit can shift +-1/2 bitLen

                do { /* Skip low freq and silence before the lead in */
                    error = ReadBitFromWav (&trans, &amps, ptrFile);
                    if (error != ERR_OK) break ;

                    if ( ( (ptrFile->debug & 0x0100) > 0 ) && (Qcnt == 0) )
                        printf ("-%lu", trans) ;

                } while (trans < ( Bit_MID ) ) ; // ( old version: Bit_MID / 2)
                if (error != ERR_OK) break ;

                /* Try to sync one bit or read next */
                if (trans < Bit_1) {
                    position = stell( ptrFile ) ;
                    if (position <= 0) {
                        printf ("\n%s:fsync - Can't ftell the wav file\n", argP) ;
                        return ( ERR_FILE ) ;
                    }
                    if (position >= MinPosSync) { /* not at begin of file */
                        limit = bitLen_before ;
                        error = SyncBitFromWav (1, &trans, &amps, &limit, ptrFile);
                        if (error != ERR_OK) break ;
                        if ( ( (ptrFile->debug & 0x0100) > 0 ) && (Qcnt == 0) )
                            printf ("~%lu", trans) ;
                   }
                    else limit = 0 ;
                    if (limit == 0 ) { /* no sync found to Bit_1 */
                        error = ReadBitFromWav (&trans, &amps, ptrFile); /* try next */
                        if (error != ERR_OK) break ;
                        if ( ( (ptrFile->debug & 0x0100) > 0 ) && (Qcnt == 0) )
                            printf (".%lu", trans) ;
                        break ;
                    }
                }
                sum_trans = trans ;
                cntBit_1 = (trans < Bit_1)? 0 : 1 ;

                /* more high Bit_1 for first start of sync to distinguish from accidental and cloudy BASE_FRQ */
                /* sequence of Bit_1 +-Tol can used to tune the BASE_FRQ */

                /* Try to read a block of ptrFile->synching bits with trans of Bit_1 */
                for( jj = 1 ; (Bit_1 - Tol <= trans && trans <= Bit_1 + Tol )&& jj < ptrFile->synching ; ++jj ) {
                    error = ReadBitFromWav (&trans, &amps, ptrFile);
                    if (error != ERR_OK) break ;

                    if ( ( (ptrFile->debug & 0x0100) > 0 ) && (Qcnt == 0) )
                        printf ("+%lu", trans) ;

                    /* mean value can used for speed correction of ptrFile->bitLen */
                    sum_trans += trans ;
                    if (trans == Bit_1 || trans == Bit_1 +1 ) ++cntBit_1 ; /* number of accepted Bit_1 */
                }
                if (error != ERR_OK) break ;

                /* frequency and bitLen calculation: only for the first sync: syncing>1 */
                if ( jj + 1 >= ptrFile->synching && ptrFile->synching > 1 && (ptrFile->debug & BASE_FRQ_FIX) == 0 ) {
                /* compensate different mean tape speed or emulator speed with changed bit length */

                     /* middle of new frequency and last found frequency */
                    ptrFile->freq = (ptrFile->freq + ( ptrFile->freq * sum_trans)/ptrFile->synching/Bit_1)/2 ;

                    if ( ptrFile->freq > ptrFile->base_freq * (Bit_1 + Tol)/ Bit_1 )
                         ptrFile->freq = ptrFile->base_freq; /* upper limit, reset */

                    if ( ptrFile->freq < ptrFile->base_freq * (Bit_1 - Tol)/ Bit_1 )
                         ptrFile->freq = ptrFile->base_freq * (Bit_1 - Tol)/ Bit_1 ;

                    ptrFile->bitLen = BitLen (0, ptrFile) ;                                /* with rounding */
                    ptrFile->freq = ptrFile->wav_freq * Wav_Nb_Bit1 / ptrFile->bitLen ; /* calculate from rounded bitLen */
                    bitLenTol = bitLen_before * BIT_LEN_RTOL ;             /* tolerance before calculating new frequency */
                }

            } while ( bitLen_before < ptrFile->bitLen - bitLenTol ||
                      bitLen_before > ptrFile->bitLen + bitLenTol ||
                      cntBit_1 < ptrFile->synching * SYNC_FRAC_1 ) ; /* part of accepted Bit_1 from all bits of block */

            if (error != ERR_OK) break ;
            if (Qcnt == 0 && ptrFile->debug != 0) printf ("."); /* block accepted */

        } while ((( trans != Bit_1  && trans != Bit_1 + 1 ) /* last bit was 1x High Bit found */
                 || cntBit_1 < ptrFile->synching * SYNC_FRAC_1 )
                 && ii < SYNC_NB_TRY ) ;

        // if (Qcnt == 0 && ptrFile->debug != 0) printf ("\n");
        if (ii >= SYNC_NB_TRY || error != ERR_OK) break;

        /* Skip the Synchro */
        if ( ( (ptrFile->debug & 0x0100) > 0 ) && (Qcnt == 0) ) {
                printf ("\nSkipping from") ; PrtWavTime (ptrFile) ;
        }
        error = SkipBitsFromWav (ptrNb, ptrFile);
        if ( ( (ptrFile->debug & 0x0100) > 0 ) && (Qcnt == 0) ) {
                printf (" End Skip at") ; PrtWavTime (ptrFile) ;
        }

        ++kk ;
        if ( *ptrNb == (uint) Stop_Bit_Max && ptrFile->base_freq == Base_FREQ5 ) { /* start bit with higher frequency cannot be found*/
            return (ERR_OK) ;
        }
        if ( error == ERR_NSYNC || *ptrNb < 2 ) { /* sync was lost */
            if ((ptrFile->synching > 1 && kk < FSYNC_NB_TRY) || kk < 2 ) continue ;
            else break ; /* No more syncing - End of Transmission ? */
        }
        if (error != ERR_OK) break ;

    } while (error == ERR_NSYNC || *ptrNb * 1000 * Wav_Nb_Bit1 / ptrFile->base_freq < SYNC_TIME_MIN ) ; // length as time [msec]

    return (error);
}


void ReadBitParamAdjust (FileInfo*  ptrFile)
{
ulong trans_diff2 ;

    if ( pcgrpId == IDENT_PC1211 ) {
        if (ptrFile->rate_amp != RATE_AMP_OFF ) {
            if  ( (ptrFile->debug & NO_RATE_AMP) == 0 ) {
                if (devId == DEV_CAS)
                        Rate_Amp_Def = Rate_Amp_Cas ;
                else if (ptrFile->ampd_cnt > Bit_0 ) {
                    if ( ptrFile->ampd_sum / ptrFile->ampd_cnt / ptrFile->pre_amp > RATE_AMP_12_ABV )
                        Rate_Amp_Def = RATE_AMP_12_MAX ;
                    else
                        Rate_Amp_Def = RATE_AMP_12 ;
                }
                else
                    Rate_Amp_Def = RATE_AMP_12 ;
            }
            else    Rate_Amp_Def = 0 ;
            ptrFile->rate_amp = Rate_Amp_Def ;
            ptrFile->amp_weight = AMP_WEIGHT_LOW ;
        }
        if ( ptrFile->ampd_cnt > Bit_0 && (ptrFile->debug & TRANS_OLD) == 0 ) {
                trans_diff2 = ( TRANS_HIGH_121 - TRANS_LOW_121 ) * ptrFile->ampd_sum / ptrFile->ampd_cnt / 0x200 ;
                if (devId == DEV_CAS )
                     trans_diff2 >>=Trans_Weak_Exp ; /* Cassette low signal points */  //changed 209c2b5(4a)
                if ( trans_diff2 < 1) trans_diff2 = 1 ;
                if (ptrFile->bytesPerP == 1 && trans_diff2 < (uint) ptrFile->pre_amp)
                    trans_diff2 = (uint) ptrFile->pre_amp ;  /* 8 bit */

                Trans_High = Trans_High_def = TRANS_MID + trans_diff2 ;
                Trans_Low  = Trans_Low_def  = TRANS_MID - trans_diff2 ;
        }
        Amp_Diff_Mid = AMP_DIFF_MID_121 ;
    }  // End if IDENT_PC1211

    else if ( pcgrpId == IDENT_PC1500 ) {

        if ( ptrFile->rate_amp != RATE_AMP_OFF) {
            if  ( (ptrFile->debug & NO_RATE_AMP) == 0 ) {
                if ( ptrFile->ampd_cnt > Bit_0 ) {

                    if (ptrFile->base_freq == Base_FREQ4 && Base_FREQ4 > 0) { /* Qtape */
                        if (devId == DEV_CAS)
                            Rate_Amp_Def = RATE_AMP_Q_CAS ;
                        else
                            Rate_Amp_Def = RATE_AMP_15 ;
                    }
                    else if (devId == DEV_CAS)
                        Rate_Amp_Def = Rate_Amp_Cas ;
                    else if ( ptrFile->ampd_sum / ptrFile->ampd_cnt / ptrFile->pre_amp > RATE_AMP_15_ABV )
                        Rate_Amp_Def = RATE_AMP_15_MAX ;
                    else
                        Rate_Amp_Def = RATE_AMP_15 ;
                }
                else {
                    if (devId == DEV_CAS) Rate_Amp_Def = Rate_Amp_Cas ;
                    else Rate_Amp_Def = RATE_AMP_15 ;
                }
            }
            else    Rate_Amp_Def = 0 ;
            ptrFile->rate_amp = Rate_Amp_Def ;
        }

        if ( ptrFile->ampd_cnt > Bit_0 && (ptrFile->debug & TRANS_OLD) == 0 ) {

            trans_diff2 = ptrFile-> ampd_sum / ptrFile->ampd_cnt / ( 2 * AMP_DIFF_MID_15  ) ;
            if (devId == DEV_CAS )
                trans_diff2 >>=Trans_Weak_Exp ; /* Cassette low signal points */  //changed 209c2b5(4a)
            else if ( (ptrFile->base_freq == Base_FREQ4 && Base_FREQ4 > 0))
                trans_diff2 >>=1 ; /* Qtape */

            if ( trans_diff2 < 2) trans_diff2 = 2 ;
            if (ptrFile->bytesPerP == 1 && trans_diff2 < (uint) ptrFile->pre_amp)
                trans_diff2 = (uint) ptrFile->pre_amp ;  /* 8 bit */

            Trans_High = Trans_High_15 = TRANS_MID + trans_diff2 ;
            Trans_Low  = Trans_Low_15  = TRANS_MID - trans_diff2 ;

            if ( trans_diff2 < 4) trans_diff2 = 4 ;
            Amp_Max_Above = TRANS_MID + trans_diff2 ;
            Amp_Min_Below = TRANS_MID - trans_diff2 ;

        }
        if (devId == DEV_CAS) Amp_Diff_Mid = AMP_DIFF_CAS_15 ;      //changed 209c2b5(4a)
        else Amp_Diff_Mid = AMP_DIFF_MID_15 ;
    }  // End if IDENT_PC1500

    else if (ptrFile->base_freq == Base_FREQ1 && Base_FREQ1 > 0) { /* PC-1245-1475 */
        if (ptrFile->rate_amp != RATE_AMP_OFF ) {
            if  ( (ptrFile->debug & NO_RATE_AMP) == 0 ) {
                if (devId == DEV_CAS)
                    Rate_Amp_Def = Rate_Amp_Cas ;
                else
                    Rate_Amp_Def = RATE_AMP_4 ;
                if ( ptrFile->ampd_cnt > Bit_0 ) {
                    if ( ptrFile->ampd_sum / ptrFile->ampd_cnt / ptrFile->pre_amp < RATE_AMP_4_BLW )
                        Rate_Amp_Def = RATE_AMP_4_MIN ;
                }
                if (devId == DEV_AIR)
                    Rate_Amp_Def = RATE_AMP_4_AIR ;
            }
            else    Rate_Amp_Def = 0 ;
            ptrFile->rate_amp = Rate_Amp_Def ;
        }
        if (devId == DEV_CAS) {      /* wav was recorded from tape */
            Amp_Diff_Mid = AMP_DIFF_MID_CAS ;
        }
        else if (devId == DEV_AIR) { /* wav was recorded with microphone from buzzer */
            Amp_Diff_Mid = AMP_DIFF_MID/2 ;
            Amp_Diff_Rel = AMP_DIFF_REL/2 ;

            if ( (ptrFile->debug & TRANS_OLD) == 0 ) {
                if ( ptrFile->ampd_cnt > Bit_0 ) {
                    trans_diff2 = ptrFile-> ampd_sum / ptrFile->ampd_cnt /4 ;
                    if ( trans_diff2 < TRANS_DIFF_AIR /2) trans_diff2 = TRANS_DIFF_AIR /2 ;
                }
                else
                    trans_diff2 = TRANS_DIFF_AIR ;

                if (ptrFile->bytesPerP == 1 && trans_diff2 < (uint) ptrFile->pre_amp)
                    trans_diff2 = (uint) ptrFile->pre_amp ;  /* 8 bit */

                Trans_High = TRANS_MID + trans_diff2 ;
                Trans_Low  = TRANS_MID - trans_diff2 ;
            }
            trans_diff2 = 4 ;
            Amp_Max_Above = TRANS_MID + trans_diff2 ;
            Amp_Min_Below = TRANS_MID - trans_diff2 ;
        }
        else if (devId == DEV_EMU) { /* wav from emulator with system sound */
            Amp_Diff_Mid = AMP_DIFF_MID*2 ;
            Amp_Diff_Rel = AMP_DIFF_REL*2 ;
            ptrFile->rate_amp = Rate_Amp_Def = RATE_AMP_4_CAS ;
        }
    }  // End if PC-1245-1475

    else if (ptrFile->base_freq == Base_FREQ3 && Base_FREQ3 > 0) { /* PC-E/G-series */

        if ( ptrFile->rate_amp != RATE_AMP_OFF && ptrFile->synching == 0) {
            if  ( (ptrFile->debug & NO_RATE_AMP) == 0 ) {
                if (devId == DEV_CAS)
                    ptrFile->rate_amp = Rate_Amp_Cas ;
                else
                    ptrFile->rate_amp = RATE_AMP_E ;
            }
            else    ptrFile->rate_amp = 0 ;
        }

        /* for better intermediate sync only, NOT byte reading */
        if ( ptrFile->ampd_cnt > Bit_0 && (ptrFile->debug & TRANS_OLD) == 0 ) {

            trans_diff2 = ptrFile-> ampd_sum / ptrFile->ampd_cnt / ( AMP_DIFF_MID  ) ;
            if (devId == DEV_CAS )
                 trans_diff2 >>=Trans_Weak_Exp ; /* Cassette weak signal */     //changed 209c2b5(4a)
            if ( trans_diff2 < 2) trans_diff2 = 2 ;

            if (ptrFile->bytesPerP == 1 && trans_diff2 < (uint) ptrFile->pre_amp)
                trans_diff2 = (uint) ptrFile->pre_amp ;  /* 8 bit */

            Trans_High = Trans_High_def = TRANS_MID + trans_diff2 ;
            Trans_Low  = Trans_High_def = TRANS_MID - trans_diff2 ;

            if ( trans_diff2 < 4) trans_diff2 = 4 ;
            Amp_Max_Above = TRANS_MID + trans_diff2 ;
            Amp_Min_Below = TRANS_MID - trans_diff2 ;
        }
    }   // End if PC-1600, E, G


    if (devId == DEV_CAS) Amp_Diff_Min = Amp_Diff_Min_Cas ;
    else Amp_Diff_Min = AMP_DIFF_MIN ;          /* depending from signal form */
    if ( Amp_Diff_Min < Trans_High - Trans_Low) Amp_Diff_Min = Trans_High - Trans_Low ;

    if ( Qcnt == 0 && (ptrFile->debug & (0xFFFF - 0xC0)) > 0 && ptrFile->synching ==0 ) {//&& ( ptrFile->base_freq != Base_FREQ3 || pcgrpId != GRP_E )
                    printf ("\nNew detection parameters: Trigger H/L: %02X/%02X, ",
                            Trans_High, Trans_Low );
                    if ( ptrFile->rate_amp < 0) printf ("amplitudes detection: OFF\n");
                    else if ( ptrFile->rate_amp == 0) printf ("amplitudes based gain: %d\n", ptrFile->rate_amp );
                    else printf ("amplitudes based gain: ON(%d/%i)\n", ptrFile->rate_amp, RATE_SCALE );

                    if ( ptrFile->rate_amp >= 0)
                        printf ("Amplitudes maxima > %02X, minima < %02X,\nAmplitudes differences (dec) min: %d, relative to main: 1/%d, to last: 1/%d\n",
                            Amp_Max_Above, Amp_Min_Below, Amp_Diff_Min, Amp_Diff_Mid, Amp_Diff_Rel );

                    printf ("\n" );
    }
}

int FindFreqAndSyncFromWav (FileInfo*  ptrFile)
{
static  ulong   base_freq_before = 0 ;

        ulong   freq_before ;
        ulong   length ;
         long   position ;
       double   cspeed ;
         uint   start_amp;
          int   error, synching, longs, shorts, stop_bit_max_tmp ;
          char  bit[1] ;

    if (TAPc > 0 || KHXc > 0) {
            ptrFile->count = 0;
            return (ERR_OK);
    }
    freq_before = ptrFile->freq ; /* 0 before first find */

    /* for interim syncing start with one Bit_1 only */
    if (ptrFile->synching == 0) ptrFile->synching = 1;
    synching = ptrFile->synching ;

    if (ptrFile->synching > 1) {   /* First or incomplete syncs at start of file, before user data was read*/
        ptrFile->ampd_cnt = 0 ;    /* reset counter for detection of mean level of sample values */
        ptrFile->ampd_sum = 0 ;
    }

    position = stell( ptrFile ) ;
    if (position <= 0) {
            printf ("\n%s:freq - Can't ftell the wav file\n", argP) ;
            return ( ERR_FILE ) ;
    }
    do {

        if ((freq_before == 0 || ptrFile->base_freq == Base_FREQ1) &&
             Base_FREQ1 > 0 && ptrFile->wav_freq >= (Base_FREQ1 * 2)) {

            /* Search the Synchro for the 4000 Hz frequency */
            if (freq_before == 0 ||  base_freq_before != Base_FREQ1 ) {
                    ptrFile->freq = ptrFile->base_freq = Base_FREQ1 ;

                    if (ptrFile->base_freq * FRQ_AMPS <= ptrFile->wav_freq && (ptrFile->debug & TRANS_OLD) == 0)
                         ptrFile->rate_amp = Rate_Amp_Def ;
                    else ptrFile->rate_amp = RATE_AMP_OFF ; /* amplitudes detection and amplification off */

                    Amp_Max_Above = AMP_MAX_ABOVE ;         /* this series has more problems with DC-shifted signal*/
                    Amp_Min_Below = AMP_MIN_BELOW ;

                    Trans_High = Trans_High_def ;           /* Higher sample value accept transition to high */
                    Trans_Low  = Trans_Low_def ;            /* Lower sample value accept transition to high */
            }
            ReadBitParamAdjust( ptrFile ) ;                 /* special settings for PC 121x hardware */

            error = FindSyncFromWav (&length, ptrFile) ;
            if (error > ERR_OK) break ;                     /* ERR_NSYNC/EOF/NOK from end of audio data */
            if ( length == 0 || error < ERR_OK) {
                error = sseek (ptrFile, ptrFile->startSampl, SEEK_SET) ; /* rewind to start of audio data */
                if (error != ERR_OK) {
                    printf ("\n%s:freq - Can't seek the file, rewind from: %ld\n", argP, position) ;
                    error = ERR_FILE ;
                    break ;
                }
            }
        }
        else length = 0 ;

        if ( length == 0 && (freq_before == 0 || ptrFile->base_freq == Base_FREQ2 ) && Base_FREQ2 > 0) {

            /* Search the Synchro for the 2500 Hz frequency */
            if (freq_before == 0 ||  base_freq_before != Base_FREQ2 ) {
                ptrFile->freq = ptrFile->base_freq = Base_FREQ2 ;

                if (ptrFile->base_freq * FRQ_AMPS <= ptrFile->wav_freq && (ptrFile->debug & TRANS_OLD) == 0)
                     ptrFile->rate_amp = RATE_AMP_15 ;
                else ptrFile->rate_amp = RATE_AMP_OFF ;

                Amp_Max_Above = AMP_MAX_ABV_15 ; /* problematic curve because of base frequency switching to low frequency signal */
                Amp_Min_Below = AMP_MIN_BLW_15 ; /* first time */

                Trans_High = Trans_High_15 ;
                Trans_Low  = Trans_Low_15 ;
            }
            ReadBitParamAdjust( ptrFile ) ;  /* special settings for PC 1500 hardware */

            error = FindSyncFromWav (&length, ptrFile) ;
            if (error > ERR_OK ) break ; /* ERR_NSYNC/EOF/NOK from end of audio data */
            if ( length == 0 || error < ERR_OK) {
                error = sseek (ptrFile, ptrFile->startSampl, SEEK_SET) ; /* rewind */
                if (error != ERR_OK) {
                    printf ("\n%s:freq - Can't seek the file, rewind from: %ld\n", argP, position) ;
                    error = ERR_FILE ;
                    break ;
                }
            }
        }
        if (length == 0 && (freq_before == 0 || ptrFile->base_freq == Base_FREQ3 ) && Base_FREQ3 > 0) {

            /* Search the Synchro for the frequency of PC-1600 and PC-E/G-Series */
            if (freq_before == 0 ||  base_freq_before != Base_FREQ3 ) {
                ptrFile->freq = ptrFile->base_freq = Base_FREQ3 ;

                if (ptrFile->base_freq * FRQ_AMPS <= ptrFile->wav_freq && (ptrFile->debug & TRANS_OLD) == 0)
                    ptrFile->rate_amp = Rate_Amp_Def ;
                else ptrFile->rate_amp = RATE_AMP_OFF ;

                Amp_Max_Above = AMP_MAX_ABOVE ;
                Amp_Min_Below = AMP_MIN_BELOW ;

                Trans_High = TRANS_HIGH_E ;
                Trans_Low  = TRANS_LOW_E  ;
            }
            ReadBitParamAdjust( ptrFile ) ;

            error = FindSyncFromWav (&length, ptrFile) ;
            if ( length == 0 || error < ERR_OK) {
                error = sseek (ptrFile, ptrFile->startSampl, SEEK_SET) ; /* rewind */
                if (error != ERR_OK) {
                    printf ("\n%s:freq - Can't seek the file, rewind from: %ld\n", argP, position) ;
                    error = ERR_FILE ;
                    break ;
                }
            }
        }
        if (length == 0 && (freq_before == 0 || ptrFile->base_freq == Base_FREQ4 ) && Base_FREQ4 > 0) {

            /* Search the Synchro for the frequency of Quick-Tape for PC-1500 intermediate */
            if (freq_before == 0 ||  base_freq_before != Base_FREQ4 ) {
                ptrFile->freq = ptrFile->base_freq = Base_FREQ4 ;

                if (ptrFile->base_freq * FRQ_AMPS <= ptrFile->wav_freq && (ptrFile->debug & TRANS_OLD) == 0)
                    ptrFile->rate_amp = RATE_AMP_15 ;
                else ptrFile->rate_amp = RATE_AMP_OFF ;

                Amp_Max_Above = AMP_MAX_ABV_15 ;
                Amp_Min_Below = AMP_MIN_BLW_15 ;

                Trans_High = Trans_High_15 ;
                Trans_Low  = Trans_Low_15  ;
            }
            ReadBitParamAdjust( ptrFile ) ;

            error = FindSyncFromWav (&length, ptrFile) ;
            if ( length == 0 || error < ERR_OK) {
                error = sseek (ptrFile, ptrFile->startSampl, SEEK_SET) ; /* rewind */
                if (error != ERR_OK) {
                    printf ("\n%s:freq - Can't seek the file, rewind from: %ld\n", argP, position) ;
                    error = ERR_FILE ;
                    break ;
                }
            }
        }
        if (length == 0 && (freq_before == 0 || ptrFile->base_freq == Base_FREQ5 ) && Base_FREQ5 > 0) {

            /* Search the Synchro for the frequency of SuperTape for PC-1500 lead in */
            if (freq_before == 0 ||  base_freq_before != Base_FREQ5 ) {
                ptrFile->freq = ptrFile->base_freq = Base_FREQ5 ;

                if (ptrFile->base_freq * FRQ_AMPS <= ptrFile->wav_freq && (ptrFile->debug & TRANS_OLD) == 0)
                    ptrFile->rate_amp = RATE_AMP_15 ;
                else ptrFile->rate_amp = RATE_AMP_OFF ;

                Amp_Max_Above = AMP_MAX_ABV_15 ;
                Amp_Min_Below = AMP_MIN_BLW_15 ;

                Trans_High = Trans_High_15 ;
                Trans_Low  = Trans_Low_15  ;
            }
            ReadBitParamAdjust( ptrFile ) ;

            ptrFile->synching = 0;  /* start bit has higher frequency than lead in for SuperTape */
            stop_bit_max_tmp = Stop_Bit_Max ;
            Stop_Bit_Max = 60 ;     /* ~0.4 s*/
            error = FindSyncFromWav (&length, ptrFile) ;
            ptrFile->synching = synching ;
            Stop_Bit_Max = stop_bit_max_tmp ;

            if ( length == 0 || error < ERR_OK) {
                error = sseek (ptrFile, ptrFile->startSampl, SEEK_SET) ; /* rewind */
                if (error != ERR_OK) {
                    printf ("\n%s:freq - Can't seek the file, rewind from: %ld\n", argP, position) ;
                    error = ERR_FILE ;
                    break ;
                }
            }
        }

        if (Qcnt == 0 && ptrFile->total > 0) {
            /* for data variable blocks the byte counter because of checksums can be manipulated */
            if (ptrFile->debug !=0 ) printf ("\n") ;
            if ( ptrFile->ident != IDENT_NEW_DAT && ptrFile->ident != IDENT_PC121_DAT &&
                 ptrFile->ident != IDENT_PC15_DAT && ptrFile->ident != IDENT_QT_DAT && ptrFile->ident != IDENT_PC16_DAT &&
                 ptrFile->ident != IDENT_OLD_DAT) printf ("Last block counter : %ld, ", ptrFile->count );
            printf ("Total bytes read and written : %ld\n", ptrFile->total );
        }
        if (length > 0 && ptrFile->base_freq > 0) {
            ptrFile->synching = 0;

            length = (length * 10 * Wav_Nb_Bit1 + ptrFile->freq / 2) / ptrFile->freq ;
            if (Qcnt == 0)  {
                if (ptrFile->debug !=0 ) printf ("\n") ;
                    if ( ptrFile->base_freq == Base_FREQ5)
                        printf ("Synchronisation %ld Hz with a length of %ld.%ld sec or longer found.\n",
                                ptrFile->freq, length / 10, length % 10);
                    else printf ("Synchronisation %ld Hz with a length of %ld.%ld sec found up to %.5lf s\n",
                                ptrFile->freq, length / 10, length % 10, WavTime(ptrFile));
                cspeed = (double) ptrFile->freq / ptrFile->base_freq ;
                if ( 0.97 > cspeed || cspeed > 1.03 ) printf ("Setting of --cspeed=%.3lf is recommended for this device.\n", cspeed * speed) ;
                if ( ( ptrFile->debug & (0xFFFF - 0xC0) ) > 0 ) {
                        printf ("Bit length %lu samples, trigger: %02X/%02X (8bit), ",
                            ptrFile->bitLen, Trans_High, Trans_Low );
                    if ( ptrFile->rate_amp < 0) printf ("amplitudes detection: OFF\n");
                    else if ( ptrFile->rate_amp == 0) printf ("amplitudes based gain: %d\n", ptrFile->rate_amp );
                    else printf ("amplitudes based gain: ON(%d/%i)\n", ptrFile->rate_amp, RATE_SCALE );
                    if ( ptrFile->base_freq == Base_FREQ3)
                        printf ("(for first synchronisation), start length based reading now, sync bits: ") ;
                }
            }
            if ( ptrFile->base_freq == Base_FREQ3 ) {
            /* switch to bit reading method of PC-1600, E/G-series series now */

            /*  BASE_FREQ3 3000/1200 Hz (0/1), 2 transmissions/bit with variable length (1T) 1A 1T 1A (1T),
                Byte = 1 start bit1 + data bit 7...0, see also SHARP TRM PC-E500, P64-66 and TRM PC-1600, P117-121
                1. Header Block = Sync_b0/40b1/40b0/1b1/File ID + Filename + header = 30B + CSum+ 1b1, Pause,
                2. Data Block = Sync_b0/20b1/20b0/1b1/ (may include 2. file header types) */

                    ptrFile->wavLenMin= (ptrFile->bitLen + Wav_Nb_Bit1/4 +1 )/Wav_Nb_Bit1 ;     /* bit = 0 */
                    ptrFile->wavLenMax= (ptrFile->bitLen *BITL_E1 + Wav_Nb_Bit1/2)/Wav_Nb_Bit1 ;/* bit = 1 */
                    ptrFile->wavLenMid= (ptrFile->wavLenMin + ptrFile->wavLenMax +1)/2 ;
                    // ptrFile->bitLen= (ptrFile->bitLen +3)/8 ; /* bit length not constant */

                    ReadBitParamAdjust( ptrFile ) ;  /* set ptrFile->synching == 0 for length based method */

                    /* Adjust to sample point before the first bit 1, must be the
                       sample point direct after the axis or on the axis */

                    error = SyncStartBitFromEWav (&start_amp, ptrFile) ;
                    if (error != ERR_OK) break ;
                    longs  = -1 ;
                    shorts = 0 ;

                    do { /* read longs */
                        error = ReadBitFieldFromEWav(1, bit, ptrFile) ;
                        ++longs;
                    } while ( bit[0] == 1 && error == ERR_OK) ;
                    if (error != ERR_OK) break ;

                    do { /* read shorts and the start bit (long) */
                        error = ReadBitFieldFromEWav(1, bit, ptrFile) ;
                        ++shorts;
                    } while ( bit[0] == 0 && error == ERR_OK) ;
                    if (error != ERR_OK) break ;

                    if (Qcnt == 0 && ptrFile->debug !=0 ) printf ("(%i=%i)\n", longs, shorts) ;
                    if ((synching  > 1 && (longs != SYNC_E_HEAD || shorts != SYNC_E_HEAD )) ||
                        (synching == 1 && (longs != SYNC_E_DATA || shorts != SYNC_E_DATA ))  ) {

                        printf ("\n%s: Illegal start bit synchronisation at %.5lf s\n", argP, WavTime(ptrFile));
                        if (synching > 1 && (longs == SYNC_E_DATA || shorts == SYNC_E_DATA )) {
                                printf ("\n%s: File header not found. File starts with a data block.\n", argP);
                                error = ERR_FMT;
                        }
                        else ++ ptrFile->wrn_cnt ;
                    }
            }
            else if ( ptrFile->base_freq == Base_FREQ4 ) {
//                    printf ("\nThis frequency could be from Quick-Tape of PC-1500 - experimentally supported.\n") ;

                    Bit_0 = BIT_0_Q ;
                    Bit_1 = BIT_1_Q ;
                    Bit_MID   = ((Bit_0 + Bit_1) / 2) ;
                    Bit_LOW   = ((Bit_0 / 4) * 2 + 1) ;
                    Bit_LOW2  =  (Bit_0 * 3) / 4 ;
                    Wav_Nb_Bit1 = Bit_1 / 2 ;

                    ptrFile->bitLen = BitLen(11, ptrFile);
                    ReadBitParamAdjust( ptrFile ) ;     /* for length based reading method*/

                    /* Adjust to sample point before the first bit 1, must be the
                       sample point direct after the axis or on the axis */
                    error = SyncStartBitFromEWav (&start_amp, ptrFile) ;
                    if (ptrFile->start_amp == 0) ptrFile->start_amp = start_amp ;
                    if (error != ERR_OK) break ;

            }
            else if ( ptrFile->base_freq == Base_FREQ5 ) {
                    printf ("\nThis frequency could be a part from CE-1600P, PC-G series or PC-E series.\n") ;
                    printf ("Check, if the --pc parameter was used correctly.\n") ;
                    printf ("Otherwise it's typical for 'SuperTape of PC-1500' - NOT supported by %s.\n", argP) ;
                    printf ("c't SuperTape for Windows can convert a SuperTape wav file to an image file.\n") ;
//                  printf ("After that, you can use %s --img %i to convert .ST to .BAS\n", argP, SUPT_HEAD_L ) ;
                    error = ERR_NSYNC;
            }
        } // end sync found
        else { /* Sync not found */
            if (Qcnt == 0 || ptrFile->debug != 0) {
                if (WavTime(ptrFile) < 10000) /* not undefined at end of audio file */
                    printf ("%s: None synchronisation found from %.5lf s\n", argP, WavTime(ptrFile));
                else if (freq_before == 0) {
                    printf ("%s: None synchronisation found\n", argP);
                    printf ("Check, if the --pc parameter (and --cspeed) used correctly, or read the manual.\n") ;
//                    printf ("Was the signal recorded loud and clear without interferences?\n") ;
//                    printf ("If something has been recorded before the useful signal, cut it out.\n") ;
                }
            }
            // ptrFile->freq = 0 ; no more, because next synchronisation has to be frequency specific /
            error = ERR_NSYNC ;
            break ;
        }
        ptrFile->count = 0;

    } while (0) ;

    base_freq_before = ptrFile->base_freq ;

    return (error);
}


int ReadQuaterFromKhx ( ulong*  ptrQuat, /* PC-1500 start quater, not used with DSave-30 */
                     FileInfo*  ptrFile) /* 0-9, A-F: NO other characters (garbage) tolerated */
{
    int  inVal;
    int  error;

    * ptrQuat = UNREAD ;

    do {
        inVal = fgetc (ptrFile->ptrFd) ;
        if (inVal == EOF) {
            if (Qcnt == 0 && ptrFile->debug!=0) printf ("\nUnexpected end of File\n") ;
            error = ERR_EOF ;
            break ;
        }
        else if ( inVal < '0' || inVal > 'F'||
                 (inVal > '9' && inVal < 'A') ) {
                printf ("Unexpected quater %i at %lu \n", inVal, ptrFile->total) ;
                error = ERR_FMT ;
        }
        else {
            error = ERR_OK ;
            if (inVal < 'A') inVal -= '0' ;
            else             inVal -= ('A'-0xA) ;
            *ptrQuat = (uint) inVal & 0x0F ;
        }

	} while (0);
    return (error);
}


int ReadQuaterFromTap ( ulong*  ptrQuat,
                     FileInfo*  ptrFile)
{
    int  inVal;
    int  error;

    * ptrQuat = UNREAD ;

    do {
        inVal = fgetc (ptrFile->ptrFd) ;
        if (inVal == EOF) {
            if (Qcnt == 0 && ptrFile->debug!=0) printf ("\nEnd of File\n") ;
            error = ERR_EOF ;
            break ;
        }
        else {
            error = ERR_OK ;
            *ptrQuat = (uint) inVal & 0x0F ;

            if  (((uint) inVal & 0xF0 ) != 0xF0 ) {
                error = count_errors( ERR_FMT, ptrFile) ;
                if (error > ERR_OK ) printf ("Unexpected quater formats up to %lu \n", ptrFile->total) ;
            }
        }

	} while (0);
    return (error);
}


int ReadQuaterFromWav (ulong*  ptrQuat,
                       ulong*  ptrNb,
                       FileInfo*  ptrFile)
{
    static bool StopBitMissed = false ;
    static long StopBitMisPos = -1 ;

    ulong  code ;
     char  bit[6] ;
     uint  ii ;
      int  error ;

 /* The khx format is not used for the PC-1500 with DSave-30, but a separate tap format for the Android emulator. */
    if (KHXc > 0) return (ReadQuaterFromKhx (ptrQuat, ptrFile));
    if (TAPc > 0) return (ReadQuaterFromTap (ptrQuat, ptrFile));
//    DEBUG code
//    if ( ( (ptrFile->debug & 0x1000F) > 0 ) && (Qcnt == 0)&& IsDbgWavTime(0x1000F, ptrFile) ) {
//            if ( (ptrFile->debug & 0x10002) == 0) printf ("[%.5lf]", WavTime(ptrFile));
//    }
    if ( ( (ptrFile->debug & 0x10001) > 0 ) && (Qcnt == 0) ) {
            if (IsDbgWavTime(0x10001, ptrFile) ) printf(" q{");
            if (IsDbgWavTime(0x10000, ptrFile) ) printf("\n");
    }

    do {
        *ptrQuat = UNREAD ;
        /* corrects some transmission errors when the first stop bit is combined stop-start-bit */
        if (StopBitMissed && StopBitMisPos == stell( ptrFile ) ) {
            if (Qcnt == 0) printf ("Start bit skipped because stop bit error in nibble before %.5lf s\n", WavTime(ptrFile));
            bit[0]= 0 ;
            error = ReadBitFieldFromWav (5, &bit[1], ptrFile) ;
        }
        /* reads one start bit, 4 bits and the first stop bit */
        else {
            error = ReadBitFieldFromWav (6, bit, ptrFile) ;
        }
        StopBitMissed = false ;
        if (error != ERR_OK) break ;

        if (bit[0] != 0 ) {
            if (Qcnt == 0) printf ("Start bit expected in nibble before %.5lf s\n", WavTime(ptrFile));
            error = count_errors( ERR_SYNC, ptrFile );
            if (error != ERR_OK) break ;

            /*  correction would possible with try and error from new start position behind the error,
                read nibbles so long while they match regular expression  _????.+  with
                _ = start bit(0),  .+ = one ore more stop bits(1),
                set new position dependent on the longest matching of this bit pattern, NOT implemented */
        }

        code = 0 ;
        for ( ii = 4 ; ii > 0 ; --ii) {
            if ( bit[ii] < 0 ) {
                code = UNREAD ;
                break ;
            }
            else
                code = (code << 1) + (ulong) bit[ii] ;
        }
        *ptrQuat = code ;

        if ( ( (ptrFile->debug & 0x0010) > 0 ) && (Qcnt == 0) && code < UNREAD )
            printf(" %1X", (uint) code);

        if (code >= UNREAD) { /* Should never appear */
            if (Qcnt == 0 ) printf ("Incomplete nibble before %.5lf s\n", WavTime(ptrFile));
        }
        /* Read one mandatory stop bit to stay synchronously after some bit errors */
        /* from hardware, such as combined start/stop bit */
        else if (bit[5] != 1 ) {
            if (Qcnt == 0) printf ("Stop bit missed in nibble before %.5lf s\n", WavTime(ptrFile));
            StopBitMissed = true ;
            StopBitMisPos = stell( ptrFile ) ;
            if (StopBitMisPos <= 0) {
                printf ("\n%s:readq - Can't ftell the wav file\n", argP) ;
                return ( ERR_FILE ) ;
            }
            error = count_errors( ERR_SYNC, ptrFile );
            if (error != ERR_OK) break ;
        }
        else {
            /* in cases of errors sometimes help not to skip, to stay synchronously in the byte */
            error = SkipBitsFromWav (ptrNb, ptrFile);
            if (error != ERR_OK) break ;
        }

    } while (0) ;

    if ( (Qcnt == 0) && (IsDbgWavTime( 0x10001, ptrFile) ) ) printf("}q ");

    return (error);
}

/* Data Blocks and Data Header are not swapped */
int SwapByte (ulong byte)
{
    return ( (byte >> 4) + (byte << 4 & 0xF0) );
}

int WriteByteToDatFile (uchar  byte,
                      FILE**  ptrFd)
{
    int  error ;

    if (SHCc == 0) error = WriteByteToFile (byte, ptrFd) ;
    else error = WriteByteToFile ( SwapByte(byte),ptrFd) ;

    return (error);
}


/* Read byte from DSave khx file */
int ReadByteFromKhx (   ulong  order,
                       ulong*  ptrByte,
                    FileInfo*  ptrFile)
{
  ulong  msq=0, lsq=0 ;
    int  inVal = UNREAD;
    int  ii, error = ERR_OK;
    *ptrByte = UNREAD ;

    for ( ii = 0 ; ii < 2 ; ++ii ) {
        do {
            inVal = fgetc (ptrFile->ptrFd) ;
            if (inVal == EOF) {
                printf ("\n%s:readkhx - End of data 'G' not found in src (khx) file\n", argP) ;
                error = ERR_EOF ;
                break ;
            }
            else if (inVal == 'G') {
                error = ERR_NSYNC ;
                break ;
            }
        } while ( inVal < '0' || inVal > 'F'||
                 (inVal > '9' && inVal < 'A') ) ;
        if (error != ERR_OK) break ;

        if (inVal < 'A') inVal -= '0' ;
        else             inVal -= ('A'-0xA) ;
        if (ii==0)  msq = inVal ;
        else        lsq = inVal ;
    }
    if (error == ERR_OK) {
        if (order == ORDER_INV)
              *ptrByte = lsq<<4 | msq ;
        else  *ptrByte = msq<<4 | lsq ;
        if (Qcnt == 0) ptrFile->position = stell(ptrFile);
    }
    return (error);
}


/* Read byte from emulator tap file or from IMG file */
int ReadByteFromTap (   ulong  order,
                       ulong*  ptrByte,
                    FileInfo*  ptrFile)
{
static int eof_cnt = 0 ;
static int eof_max = 0 ;
/* Note - The image does not have to start with the first byte and does not have to end with the last byte. */

  ulong  msq, lsq ;
    int  inVal = UNREAD;
    int  error = ERR_OK;

    *ptrByte = UNREAD ;

    do {
        if ( IMGc == 0 && ptrFile->base_freq == Base_FREQ2 && Base_FREQ2 > 0 ) { /* PC-1500 tap */

            if (order == ORDER_INV) {
                error = ReadQuaterFromTap (&lsq, ptrFile) ;
                if (error != ERR_OK) break ;
                error = ReadQuaterFromTap (&msq, ptrFile) ;
            }
            else {
                error = ReadQuaterFromTap (&msq, ptrFile) ;
                if (error != ERR_OK) break ;
                error = ReadQuaterFromTap (&lsq, ptrFile) ;
            }
            if (error != ERR_OK) break ;
            *ptrByte = (msq << 4) + lsq ;
        }
        else {  /* PC-1234 or IMG */
            if (eof_cnt == 0) {
                inVal = fgetc (ptrFile->ptrFd) ;
                if (inVal == EOF) ++eof_cnt;
            }
            else ++eof_cnt;

            if (IMGc > 0 && eof_cnt > 0 && pcgrpId != GRP_G) { /* simulate EOF marks for image files */
                if (pcgrpId == GRP_NEW || pcgrpId == GRP_EXT) eof_max = 2;
                else eof_max = 1;

                if (pcgrpId == GRP_OLD || pcgrpId == IDENT_PC1211) inVal = BAS_OLD_EOF;
                else inVal = BAS_NEW_EOF ;
                if (eof_cnt < eof_max && ptrFile->total > 0) --ptrFile->total; /* correct read count of simulated mark */
                if (eof_cnt == eof_max) error = ERR_EOT;
            }

            if (inVal == EOF || eof_cnt > eof_max) {
                if (Qcnt == 0 && ptrFile->debug!=0) printf ("\nEnd of File\n") ;
                error = ERR_EOF ;
                break ;
            }
            else {
                if  (eof_cnt < eof_max) error = ERR_OK ;
                if (order == ORDER_INV && IMGc == 0)
                    *ptrByte = (uint) SwapByte( (uint) inVal) ;
                else
                    *ptrByte = (uint) inVal ;
            }
        }

	} while (0);

    if (error == ERR_OK && Qcnt==0 ) ptrFile->position = stell(ptrFile);
    return (error);
}


int ReadByteFromEWav (  ulong*  ptrByte,
                     FileInfo*  ptrFile)
{
    ulong  code ;
     char  bit[10] ;
      int  ii, error ;

    if (KHXc > 0) return (ReadByteFromKhx (ORDER_E, ptrByte, ptrFile)) ;
    if (TAPc > 0) return (ReadByteFromTap (ORDER_E, ptrByte, ptrFile)) ;

    if ( ( (ptrFile->debug & 0x1000D) > 0 ) && (Qcnt == 0) ) {
            if (IsDbgWavTime(0x1000D, ptrFile) ) {
                if ( (ptrFile->debug & 0x10002) == 0) printf ("[%.5lf]", WavTime(ptrFile));
                printf(" {{");
//                if ( (ptrFile->debug & 0x1000D) == 0) printf("\n"); /* for 0x0002 */
            }
    }
    do {
        *ptrByte = 0 ;

        error = ReadBitFieldFromEWav (9, bit, ptrFile) ;
        if (error != ERR_OK) {
                    if (error == ERR_NSYNC && ptrFile->type != TYPE_RAW ) error = ERR_SYNC;
                    break ;
        }

        if (bit[0] != 1 ) {
            if (Qcnt == 0) printf ("Start bit expected in byte before %.5lf s\n", WavTime(ptrFile));
            error = count_errors( ERR_SYNC, ptrFile );
            if (error != ERR_OK) break ;
        }

        code = 0 ;
        for ( ii = 1 ; ii < 9 ; ++ii ) {
            code = (code << 1) + (ulong) bit[ii] ;
        }
        *ptrByte = code ;

        if ( ( (ptrFile->debug & 0x60) == 0x20 ) && (Qcnt == 0) )
            printf(" %02X", (uchar) *ptrByte);

    } while (0) ;

    if (error == ERR_OK && Qcnt==0 ) ptrFile->wavtime = WavTime(ptrFile);
    if ( (Qcnt == 0) && (IsDbgWavTime( 0x1000D, ptrFile) ) ) printf("}} ");

    return (error);
}


int ReadByteFromQWav (  ulong*  ptrByte,
                     FileInfo*  ptrFile)
{
    ulong  code ;
     char  bit[12] ;
     long  position ;
      int  ii, error ;

    if (KHXc > 0) return (ReadByteFromKhx (ORDER_INV, ptrByte, ptrFile)) ;
    if (TAPc > 0) return (ReadByteFromTap (ORDER_INV, ptrByte, ptrFile)) ;

    if ( ( (ptrFile->debug & 0x1000D) > 0 ) && (Qcnt == 0) ) {
            if (IsDbgWavTime(0x1000D, ptrFile) ) {
                if ( (ptrFile->debug & 0x10002) == 0) printf ("[%.5lf]", WavTime(ptrFile));
                printf(" {{");
//              if ( (ptrFile->debug & 0x1000D) == 0) printf("\n"); /* for 0x0002 */
            }
    }

    *ptrByte = UNREAD ;

    position = stell( ptrFile ) ;
    if (position <= 0) {
        printf ("\n%s:rbytQ - Can't ftell the wav file\n", argP) ;
        return ( ERR_FILE ) ;
    }

    do {

        error = ReadBitFieldFromQWav (11, bit, ptrFile) ;
        if (error != ERR_OK) {
                    if (error == ERR_NSYNC && ptrFile->type != TYPE_RAW ) error = ERR_SYNC;
                    break ;
        }

        if (bit[0] != 0 ) {
            if (Qcnt == 0) printf ("\nStart bit expected in byte before %.5lf s !\n", WavTime(ptrFile));
            // error = count_errors( ERR_SYNC, ptrFile );
            error = ERR_SYNC;
            if (error != ERR_OK) break ;
        }

        code = 0 ;
        for ( ii = 8 ; ii > 0 ; --ii ) {
            code = (code << 1) + (ulong) bit[ii] ;
        }
        *ptrByte = code ;

        if (bit[9] != 1 || bit[10] != 1  ) {
            if (Qcnt == 0) printf ("\nTwo stop bits expected in byte before %.5lf s !\n", WavTime(ptrFile));
            error = count_errors( ERR_SYNC, ptrFile );
            if (error != ERR_OK) break ;

            /* Try to correct the position */
            position += ( ptrFile->byteLen -(ptrFile->wavLenMin>>1) ) * ptrFile->blockAlign ;
            error = sseek (ptrFile, position, SEEK_SET) ;
            if (error != ERR_OK) {
                printf ("\n%s:rbytQ - Can't seek the file\n", argP) ;
                return ( ERR_FILE ) ;
            }
        }

        if ( ( (ptrFile->debug & 0x60) == 0x20 ) && (Qcnt == 0) )
            printf(" %02X", (uchar) *ptrByte);

    } while (0) ;

    if (error == ERR_OK && Qcnt==0 ) ptrFile->wavtime = WavTime(ptrFile);
    if ( (Qcnt == 0) && (IsDbgWavTime( 0x1000D, ptrFile) ) ) printf("}} ");

    return (error);
}


int ReadByteFromWav (ulong  order,
                     ulong*  ptrByte,
                     FileInfo*  ptrFile)
{
    static ulong MissStopBitsCnt = 0 ;
    ulong  msq, lsq ;
    ulong  nbStopBits ; /* additional stop bits was read for error compensation */
      int  error ;

    if (KHXc > 0) return (ReadByteFromKhx (order, ptrByte, ptrFile)) ;
    if (TAPc > 0) return (ReadByteFromTap (order, ptrByte, ptrFile)) ;

    if (order == ORDER_E) return (ReadByteFromEWav ( ptrByte, ptrFile)) ;
    if (order == ORDER_Q) return (ReadByteFromQWav ( ptrByte, ptrFile)) ;

    if ( ( (ptrFile->debug & 0x1000F) > 0 ) && (Qcnt == 0) ) {
            if (IsDbgWavTime(0x1000F, ptrFile) ) {
                if      ( (ptrFile->debug & 0x10002) == 0) printf ("[%.5lf]", WavTime(ptrFile));
                else if ( (ptrFile->debug & 0x10400) == 0) printf ("%ld:", ptrFile->total+1);
                if      ( (ptrFile->debug & 0x10407) == 0x0004) printf (" %ld:", ptrFile->total+1);
                printf(" {{");
                if ( (ptrFile->debug & 0x1000D) == 0) printf("\n"); /* for 0x0002 */
            }
    }
    do {
        *ptrByte = UNREAD ;
        if (order == ORDER_INV) {
            error = ReadQuaterFromWav (&lsq, &nbStopBits, ptrFile) ;
            if (error != ERR_OK) {          /* For DATA files exist a defined end of block but not end of file */
                    if ((error == ERR_NSYNC || error == ERR_EOF)
                        && ptrFile->type  != TYPE_RAW
                    /*  && ptrFile->ident != IDENT_PC15_DAT // should not needed because of EOF_15 mark */
                        && ptrFile->ident != IDENT_NEW_DAT
                        && ptrFile->ident != IDENT_PC121_DAT
                        && ptrFile->ident != IDENT_OLD_DAT      )
                                                error = ERR_SYNC; /*Data fields ends without mark*/
                    break ;
            }
            error = ReadQuaterFromWav (&msq, &nbStopBits, ptrFile) ;
        }
        else {
            error = ReadQuaterFromWav (&msq, &nbStopBits, ptrFile) ;
            if (error != ERR_OK) {
                    if ((error == ERR_NSYNC || error == ERR_EOF)
                        && ptrFile->type  != TYPE_RAW )
                                                error = ERR_SYNC;
                    break ;
            }
            error = ReadQuaterFromWav (&lsq, &nbStopBits, ptrFile) ;
        }
        ptrFile->pause = (nbStopBits > 10 )? true : false ;

        if (lsq < UNREAD && msq < UNREAD)
             *ptrByte = (msq << 4) + lsq ;
        else *ptrByte = UNREAD ;

        /* If exit would be done before the calculation of last the Byte,
        then the last Checksum of a file could be skipped */
        if (error != ERR_OK) break ;

        if ( nbStopBits < ptrFile->nbStopBMin ) { /* first stop bit was separate read and has number 0 */
            if (Qcnt == 0 && ptrFile->debug != 0)
                printf ("More stop bits for a byte expected before %.5lf s\n", WavTime(ptrFile));

            if (ptrFile->err_last == ERR_ORD) ++MissStopBitsCnt ;
            error = count_errors( ERR_ORD, ptrFile );
            if (error != ERR_OK) break ;

            if (MissStopBitsCnt > CNT_ERR_ORD) { /* for NEW_series most likely nibbles are shifted between bytes */
                printf ("Trying to shift a nibble to the next byte, minimum one nibble [%1x] lost.\n", (uchar) msq );
                msq = lsq ;
                error = ReadQuaterFromWav (&lsq, &nbStopBits, ptrFile) ;
                *ptrByte = (msq << 4) + lsq ;
                MissStopBitsCnt = 0 ;
                if (error != ERR_OK) break ;
            }
        }

        if ( ( (ptrFile->debug & 0x70) == 0x20 ) && (Qcnt == 0) && *ptrByte < UNREAD )
            printf(" %02X", (uchar) *ptrByte);

    } while (0) ;

    if (error == ERR_OK && Qcnt==0 ) ptrFile->wavtime = WavTime(ptrFile);
    if ( (Qcnt == 0) && (IsDbgWavTime( 0x1000F, ptrFile) ) ) printf("}} ");

    return (error);
}

int ReadByteTraceFromWav (ulong  order,
                         ulong*  ptrByte,
                      FileInfo*  ptrFile)
{
    int error ;

    do {
        error = ReadByteFromWav (order, ptrByte, ptrFile);
        if (error != ERR_OK && error != ERR_NSYNC ) break ; // Data block ends with NewSYNC

        if (ptrFile->writing) ++ ptrFile->total ;

        if ( ( (ptrFile->debug & 0x20000) != 0 ) && (Qcnt == 0) )
                printf(" %lu:", ptrFile->count);

        if ( ( (ptrFile->debug & 0x0400) > 0 ) && (Qcnt == 0) ) {
            if ( (ptrFile->ident == IDENT_OLD_BAS || ptrFile->ident == IDENT_PC1211) &&
                  *ptrByte > 0x0F && *ptrByte < 0x6B && strlen(CodeOld[*ptrByte]) == 1 )
                    printf("%ld: %3lu [%02X]  %c  %.5f s\n", ptrFile->total, *ptrByte, (uchar) *ptrByte, (uchar) *CodeOld[*ptrByte], WavTime(ptrFile) ) ;
            else if ( *ptrByte > 32 && *ptrByte < 128 )
                    printf("%ld: %3lu [%02X]  %c  %.5f s\n", ptrFile->total, *ptrByte, (uchar) *ptrByte, (uchar) *ptrByte, WavTime(ptrFile) ) ;
            else
                    printf("%ld: %3lu [%02X]     %.5f s\n", ptrFile->total, *ptrByte, (uchar) *ptrByte, WavTime(ptrFile) ) ;
        }
        else if ( (ptrFile->debug & 0x0040) > 0 && Qcnt == 0 ) {
                printf(" %02X", (uchar) *ptrByte);
                if ( (ptrFile->debug & 0xC0) == 0x40 && ptrFile->writing && ptrFile->total %0x100 == 0 ) printf("\n");
        }

    } while (0) ;

return (error) ;

}


int CheckSum (ulong  order,
              ulong*  ptrByte,
              FileInfo*  ptrFile)
{
    ulong  sum ;

    /* This backup of the checksum must be used after this EOF/B marks,
       that has not to include in the checksum */
    ptrFile->sum_before = ptrFile->sum ;

    /* Update the checksum */
    if (order == ORDER_INV) {
        /* INV uses the same algorithm but Byte swapped before */
        sum = ptrFile->sum + (*ptrByte & 0x0F) ;
        if (sum > 0xFF) {
            ++sum ;
            sum &= 0xFF ;
            }
        /* this sum is always unswapped,
           so use ORDER_STD to read the comparative sum from file */
        ptrFile->sum = (sum + ((*ptrByte & 0xF0) >> 4)) & 0xFF ;
        }
    else {
        sum = ptrFile->sum + ((*ptrByte & 0xF0) >> 4) ;
        if (sum > 0xFF) {
            ++sum ;
            sum &= 0xFF ;
            }
        ptrFile->sum = (sum + (*ptrByte & 0x0F)) & 0xFF ;
    }
    return (0);
}


int ReadUsedatLenFromQTWav (ulong  order,
                        FileInfo*  ptrFile)
{  ulong  byte  ;
     int  error ;

    error = ReadByteFromWav (order, &byte, ptrFile);
    if (error != ERR_OK) return (error) ;

    if ( ( (ptrFile->debug & 0x0040) > 0 ) && (Qcnt == 0) ) printf(" (L:%02X)", (uint) byte);

    if (byte + 1 > ptrFile->block_len ) { /* useful bytes of next block */
        printf("False length of data block after byte %ld, before %.4f s\n", ptrFile->total, WavTime(ptrFile) );
        error = count_errors( ERR_MEM, ptrFile) ;
    }
    else if (byte + 1 < ptrFile->block_len) ptrFile->usedat_len = byte + 1 ;
    ptrFile->sum = byte ;

    return (error);
}


int ReadByteSumFromWav (ulong  order,
                        ulong*  ptrByte,
                        FileInfo*  ptrFile)
{
    ulong  sum, sumH, byte, byte1 ;
     long  position ;
      int  ii, error ;

     bool  writing = ptrFile->writing,
           read_full_block = false ;

    do {
        error = ReadByteTraceFromWav (order, ptrByte, ptrFile);
        if (error != ERR_OK && error != ERR_NSYNC ) break ; // Data block ends with NewSYNC
        ++ ptrFile->count ;
        if (error != ERR_OK) break ;

        if ( ptrFile->usedat_len > 0) { /* QTape incomplete Block */
            if (--ptrFile->usedat_len == 0) {
                byte1 = *ptrByte;
                ptrFile->writing = false;
                if ( ( (ptrFile->debug & 0x0040) > 0 ) && (Qcnt == 0) ) printf(" Meaningless data:");
                read_full_block = true ;
            }
        }

        switch (ptrFile->ident) {
        case IDENT_PC1500   : /* for first header reading only */
        case IDENT_PC15_BIN :
        case IDENT_PC15_RSV :
        case IDENT_PC15_DEF :
        case IDENT_PC15_DAT :
        case IDENT_PC15_BAS :
            /* Update checksum */
            ptrFile->sum_before = ptrFile->sum ; /* used in cases of double EOF */
            ptrFile->sum += (ulong) *ptrByte ;
            if ( (ptrFile->count % BLK_OLD) == 0) {
                if (IMGc == 0) {
                    error = ReadByteFromWav (order, &sumH, ptrFile);
                    if (error != ERR_OK) break ;
                    error = ReadByteFromWav (order, &sum, ptrFile);
                    sum += (sumH<<8) ;
                }
                else sum = ptrFile->sum ; // simulate for img
                if (sum != ptrFile->sum) {
                    if ((ptrFile->debug & IGN_ERR_SUM) == 0 ) error = ERR_SUM ;
                    else error = count_errors( ERR_SUM, ptrFile) ;
                    if (Qcnt == 0) printf(" ERROR %d, Block end: %ld, %.4f s\n", ERR_SUM, ptrFile->total,
                                            WavTime(ptrFile) ) ;
                }
                if ( ( (ptrFile->debug & 0x0040) > 0 ) && (Qcnt == 0) ) {
                    if (IMGc == 0) printf(" (%04X=%04X)", (uint) sum, (uint) ptrFile->sum);
                    else printf(" (=%04X)", (uint) ptrFile->sum);
                    if ( (ptrFile->debug & 0x400) > 0 ) printf("\n");
                }
                if (error != ERR_OK) break ;
                ptrFile->sum = 0 ;
            }
            break ;

        case IDENT_QTAPE  :   /* for first header reading only */
        case IDENT_QT_BAS :
        case IDENT_QT_RSV :
        case IDENT_QT_BIN :
        case IDENT_QT_DIM :
        case IDENT_QT_DAT :

        case IDENT_PC15QTBAS :
        case IDENT_PC15QTBIN :
            /* Update checksum */
            ptrFile->sum_before = ptrFile->sum ; /* used in cases of double EOF */
            ptrFile->sum += (ulong) *ptrByte ;
            if ( ptrFile->block_len > 0 && ptrFile->count % ptrFile->block_len == 0 ) { // >= ptrFile->block_len
                if (IMGc == 0) {
                    error = ReadByteFromWav (order, &sumH, ptrFile);
                    if (error != ERR_OK) break ;
                    error = ReadByteFromWav (order, &sum, ptrFile);
                    sum += (sumH<<8) ;
                }
                else sum = ptrFile->sum ; // simulate for img
                if (sum != ptrFile->sum) {
                    if ((ptrFile->debug & IGN_ERR_SUM) == 0 ) error = ERR_SUM ;
                    else error = count_errors( ERR_SUM, ptrFile) ;
                    if (Qcnt == 0) printf(" ERROR %d, Block end: %ld, %.4f s\n", ERR_SUM, ptrFile->total,
                                            WavTime(ptrFile) ) ;
                }
                if ( ( (ptrFile->debug & 0x0040) > 0 ) && (Qcnt == 0) ) {
                    if (IMGc == 0) printf(" (%04X=%04X)", (uint) sum, (uint) ptrFile->sum);
                    else printf(" (=%04X)", (uint) ptrFile->sum);
                    if ( (ptrFile->debug & 0x400) > 0 ) printf("\n");
                }
                if (error != ERR_OK) break ;

                ptrFile->sum = 0 ;
                // ptrFile->count = 0 ;
                if (read_full_block) {
                    read_full_block = false ;
                    ptrFile->writing = writing;
                    *ptrByte = byte1 ;
                }
                if ( ptrFile->id_version == 1 ) break ;

                if (order == ORDER_Q) {
                    error = ReadByteFromWav (order, &byte, ptrFile);
                    if (error != ERR_OK) break ;
                    if ( ( (ptrFile->debug & 0x0040) > 0 ) && (Qcnt == 0) ) printf(" (E:%02X)", (uint) byte);
                    if (byte != EOF_15 ) {
                        printf("Missing EOB mark of the header\n");
                        error = count_errors( ERR_MEM, ptrFile) ;
                    }
                    if (ptrFile->status == STAT_OK) { // && ptrFile->total > 0 && ptrFile->ident != IDENT_QT_DAT

                        error = SkipBitFromQWav(Stop_Bit_Max , ptrFile) ;
                        if (error != ERR_OK) break ;

                        error = ReadUsedatLenFromQTWav (order, ptrFile);
                    }
                }
            }  // end if block end
            break ;

        case IDENT_PC1211 :
        case IDENT_OLD_BAS :
        case IDENT_OLD_PAS :
            if ( *ptrByte == BAS_OLD_EOF ) break ; // no checksum follows
        case IDENT_OLD_BIN :                       // EOF not read, because length is known
        case IDENT_OLD_MEM :
        case IDENT_OLD_MEM2 :
            CheckSum (order, ptrByte, ptrFile);
            if ( (ptrFile->count % BLK_OLD_SUM) == 0) {
                if (IMGc == 0) error = ReadByteFromWav (order, &sum, ptrFile);
                else sum = ptrFile->sum ; // simulate for img
                if ( error < ERR_OK && ( (ptrFile->debug & 0x0040) > 0 ) && (Qcnt == 0) )
                    printf(" EOF:"); // End of File, error because of no sync

                if (sum != ptrFile->sum) {
                    if ((ptrFile->debug & IGN_ERR_SUM) == 0 ) error = ERR_SUM ;
                    else error = count_errors( ERR_SUM, ptrFile) ;
                    if (Qcnt == 0) printf(" ERROR %d, Block end: %ld, %.4f s\n", ERR_SUM, ptrFile->total,
                                            WavTime(ptrFile) ) ;
                }

                if ( ( (ptrFile->debug & 0x0040) > 0 ) && (Qcnt == 0) ) {
                    if (IMGc == 0) printf(" (%02X=%02X)", (uchar) sum, (uchar) ptrFile->sum);
                    else printf(" (=%02X)", (uchar) ptrFile->sum);
                    if ( (ptrFile->debug & 0x400) > 0 ) printf("\n");
                }
                if (error != ERR_OK) break ;

                if (ptrFile->count >= BLK_OLD) {
                    ptrFile->count = 0 ;
                    ptrFile->sum = 0 ;
                }
            }
            break ;

        case IDENT_NAMEPAS :
        case IDENT_PC121_DAT :
        case IDENT_OLD_DAT :
        case IDENT_NEW_DAT :
            CheckSum (order, ptrByte, ptrFile);
            if ( (ptrFile->count % BLK_OLD_SUM) == 0) {
                error = ReadByteFromWav (ORDER_STD, &sum, ptrFile);
                if ( ( (ptrFile->debug & 0x0040) > 0 ) && (Qcnt == 0) ) {
                    if (error == ERR_EOF )  printf(" EOF:"); // End of File,
                    if (error == ERR_NSYNC) printf(" EOB:"); // End of Block, error because of NewSync
                }
                if (sum != ptrFile->sum) {
                    if ((ptrFile->debug & IGN_ERR_SUM) == 0 ) error = ERR_SUM ;
                    else error = count_errors( ERR_SUM, ptrFile) ;
                    if (Qcnt == 0) printf(" ERROR %d, Block end: %ld, %.4f s\n", ERR_SUM, ptrFile->total,
                                            WavTime(ptrFile) ) ;
                }
                if ( ( (ptrFile->debug & 0x0040) > 0 ) && (Qcnt == 0) ) {
                    if (IMGc == 0) printf(" (%02X=%02X)", (uchar) sum, (uchar) ptrFile->sum);
                    else printf(" (=%02X)", (uchar) ptrFile->sum);
                    if ( (ptrFile->debug & 0x400) > 0 ) printf("\n");
                }
                // if (error != ERR_OK) break ;
                ptrFile->sum = 0 ;
            }
            break ;

        case IDENT_NEW_TEL :
        case IDENT_NEW_SCD :
        case IDENT_NEW_NOT :
        case IDENT_NEW_CRD :
            CheckSum (order, ptrByte, ptrFile);
            if ( (ptrFile->count % BLK_NEW) == 0) {
                error = ReadByteFromWav (ORDER_STD, &sum, ptrFile);
                if ( ( (ptrFile->debug & 0x0040) > 0 ) && (Qcnt == 0) ) {
                    if (error == ERR_EOF )  printf(" EOF:"); // End of File, unused at moment
                    if (error == ERR_NSYNC) printf(" EOB:"); // End of Block, error because of NewSync
                }
                /* Memo file ends with the last checksum without any further end-of-file characters. */
                if (error == ERR_NSYNC && ptrFile->status == STAT_EOT) error = ERR_OK;

                if (sum != ptrFile->sum) {
                    if ((ptrFile->debug & IGN_ERR_SUM) == 0 ) error = ERR_SUM ;
                    else error = count_errors( ERR_SUM, ptrFile) ;
                    if (Qcnt == 0) printf(" ERROR %d, Block end: %ld, %.4f s\n", ERR_SUM, ptrFile->total,
                                            WavTime(ptrFile) ) ;
                }
                if ( ( (ptrFile->debug & 0x0040) > 0 ) && (Qcnt == 0) ) {
                    if (IMGc == 0) printf(" (%02X=%02X)", (uchar) sum, (uchar) ptrFile->sum);
                    else printf(" (=%02X)", (uchar) ptrFile->sum);
                    if ( (ptrFile->debug & 0x400) > 0 ) printf("\n");
                }
                ptrFile->sum = 0 ;
            }
            break ;

        case IDENT_NEW_BAS :
        case IDENT_NEW_PAS :
        case IDENT_NEW_CSL :
        case IDENT_EXT_BAS :
        case IDENT_EXT_PAS :
        case IDENT_NEW_BIN :
            CheckSum (order, ptrByte, ptrFile);
            if ( (ptrFile->count % BLK_NEW) == 0) {
                if (IMGc == 0) error = ReadByteFromWav (ORDER_STD, &sum, ptrFile);
                else sum = ptrFile->sum ; // simulate for img
                if (error > ERR_OK || sum == UNREAD) break ;

                /* if 0xFF follows a end of line it could be a checksum 0xFF or a BAS_NEW_EOF */
                if ( ptrFile->check_end && sum == BAS_NEW_EOF){          /*check_end set before line end from ReadLine */
                    position = stell( ptrFile ) ;                 /*save position in source file */
                    if (position <= 0) {
                        printf ("\n%s:ByteSum - Can't ftell the wav file\n", argP) ;
                        return ( ERR_FILE ) ;
                    }
                    /* if the second byte is also BAS_NEW_EOF, then end of transmission, else its a merged programs mark*/
                    error = ReadByteFromWav (ORDER_STD, &sumH, ptrFile);
                    if (error != ERR_OK) break ;

                    error = sseek (ptrFile, position, SEEK_SET) ; /*rewind to position before last byte read */
                    if (error != ERR_OK) {
                        printf ("\n%s:ByteSum - Can't seek the file: %ld\n", argP, position) ;
                        error = ERR_FILE ;
                        break ;
                    }
                    if ( sumH == BAS_NEW_EOF ) error = ERR_EOT ; /* the checksum will follow after two EOF marks */
                }
                if ( error <= ERR_OK && error != ERR_EOT ) {
                    if (sum != ptrFile->sum) {
                        if ((ptrFile->debug & IGN_ERR_SUM) == 0) error = ERR_SUM ;
                        else error = count_errors( ERR_SUM, ptrFile) ;
                        if (Qcnt == 0) printf(" ERROR %d, Block end: %ld, %.4f s\n", ERR_SUM,
                                                            ptrFile->total, WavTime(ptrFile) ) ;
                    }
                    if ( ( (ptrFile->debug & 0x0040) > 0 ) && (Qcnt == 0) ) {
                        if (IMGc == 0) printf(" (%02X=%02X)", (uchar) sum, (uchar) ptrFile->sum);
                        else printf(" (=%02X)", (uchar) ptrFile->sum);
                        if ( (ptrFile->debug & 0x400) > 0 ) printf("\n");
                    }
                    if (error != ERR_OK) break ;

                    ptrFile->sum = 0 ;
                }
                else if ( ( (ptrFile->debug & 0x0040) > 0 ) && (Qcnt == 0) )
                        printf(" EOF1:(%02X)", (uchar) sum);   /* if this first of both EOF marks was read instead a checksum,
                        this has to considered by ReadLine */

            }
            break ;

        case IDENT_PC16_BAS :
        case IDENT_PC16_RSV :
        case IDENT_PC16_DAT :

        case IDENT_PC16_IMG :
        case IDENT_PC16_CAS :
        case IDENT_E_ASC :
        case IDENT_E_IMG :

        case IDENT_E_BAS :
        case IDENT_E_BIN :
            ptrFile->sum_before = ptrFile->sum ; /* used in cases of double EOF */
            byte = *ptrByte ;
            for ( ii = 0; ii < 8; ++ii, byte>>=1) {
                ptrFile->sum += byte & 1 ;
                ptrFile->sum &= 0xFFFF ;
            }
            if ( ptrFile->count >= ptrFile->block_len) {
                if (IMGc == 0) {
                    error = ReadByteFromWav (order, &sumH, ptrFile);
                    if (error != ERR_OK) break ;
                    error = ReadByteFromWav (order, &sum, ptrFile);
                    sum += (sumH<<8) ;
                }
                else sum = ptrFile->sum ; // simulate for img
                if (sum != ptrFile->sum) {
                    if ((ptrFile->debug & IGN_ERR_SUM) == 0 ) error = ERR_SUM ;
                    else error = count_errors( ERR_SUM, ptrFile) ;
                    if (Qcnt == 0) printf(" ERROR %d, Block end: %ld, %.4f s\n", ERR_SUM, ptrFile->total,
                                            WavTime(ptrFile) ) ;
                }
                if ( ( (ptrFile->debug & 0x0040) > 0 ) && (Qcnt == 0) ) {
                    if (IMGc == 0) printf(" (%04X=%04X)", (uint) sum, (uint) ptrFile->sum);
                    else if (pcgrpId == GRP_G) printf(" (+Std.Head=%04X)", (uint) ptrFile->sum);
                    else printf(" (BODY=%04X)", (uint) ptrFile->sum);
                    if ( (ptrFile->debug & 0x400) > 0 ) printf("\n");
                }
                if (error != ERR_OK) break ;

                ptrFile->sum = 0 ;
                ptrFile->count = 0 ;
            }
            break ;

        case IDENT_RAW :
            break ;

        default :
            printf ("\n%s:RBSum: Unknown Ident %lu\n", argP, ptrFile->ident) ;
            error = ERR_FMT;
            break ;
        }

    } while (read_full_block) ;

    return (error);
}


int PrintSaveIdFromWav (FileInfo*  ptrFile)
{
    int error = ERR_OK ;
    ulong code = ptrFile->ident ;
    ulong type = TYPE_NOK ;

    if (Qcnt == 0 && (ptrFile->debug & 0x4C0)>0) printf ("\n");
    if (Qcnt == 0) printf ("Pocket Computer format   : 0x%02X -> ", (uchar) code) ;

    if (code == IDENT_PC1211)
        {if (Qcnt == 0) printf ("Basic, PC-121x\n") ; type = TYPE_IMG ; pcgrpId = IDENT_PC1211 ;}
    else if (code == IDENT_PC121_DAT)
        {if (Qcnt == 0) printf ("Data, PC-121x\n") ; type = TYPE_DAT ; pcgrpId = IDENT_PC1211 ;}
    else if (code == IDENT_PC15_BAS)
        {if (Qcnt == 0) printf ("Basic, PC-1500\n") ; type = TYPE_IMG ; pcgrpId = IDENT_PC1500 ;}
    else if (code == IDENT_PC15_BIN)
        {if (Qcnt == 0) printf ("Binary, PC-1500\n") ; type = TYPE_BIN ; pcgrpId = IDENT_PC1500 ;}
    else if (code == IDENT_PC15_RSV)
        {if (Qcnt == 0) printf ("ReSerVe Data, PC-1500\n") ; type = TYPE_RSV ; pcgrpId = IDENT_PC1500 ;}
    else if (code == IDENT_PC15_DEF)
        {if (Qcnt == 0) printf ("Def.Key Data, PC-1500(V2,A)\n") ; type = TYPE_DEF ; pcgrpId = IDENT_PC1500 ;}
    else if (code == IDENT_PC15_DAT)
        {if (Qcnt == 0) printf ("DATA, PC-1500\n") ; type = TYPE_DAT ; pcgrpId = IDENT_PC1500 ;}
    else if (code == IDENT_PC15QTBAS)
        {if (Qcnt == 0) printf ("Quick-Tape Basic, PC-1500\n") ; type = TYPE_IMG ; ptrFile->id_version=1 ;
         pcgrpId = IDENT_PC1500 ; pcId = 1541 ;
        }
    else if (code == IDENT_PC15QTBIN)
        {if (Qcnt == 0) printf ("Quick-Tape Binary, PC-1500\n") ; type = TYPE_BIN ; ptrFile->id_version=1 ;
         pcgrpId = IDENT_PC1500 ; pcId = 1541 ;
        }
    else if (code == IDENT_QT_BAS)
        {if (Qcnt == 0) printf ("Quick-Tape Basic\n") ; type = TYPE_IMG ; pcgrpId = IDENT_PC1500 ; pcId =1544 ;}
    else if (code == IDENT_QT_BIN)
        {if (Qcnt == 0) printf ("Quick-Tape Binary\n") ; type = TYPE_BIN ; pcgrpId = IDENT_PC1500 ; pcId = 1544;}
    else if (code == IDENT_QT_RSV)
        {if (Qcnt == 0) printf ("Quick-Tape ReSerVe Data\n"); type = TYPE_RSV ; pcgrpId = IDENT_PC1500; pcId = 1544;}
    else if (code == IDENT_QT_DIM)
        {if (Qcnt == 0) printf ("Quick-Tape complete Variable DIM Data\n"); type = TYPE_DIM; pcgrpId = IDENT_PC1500; pcId = 1544;}
    else if (code == IDENT_QT_DAT)
        {if (Qcnt == 0) printf ("Quick-Tape Variable Data\n"); type = TYPE_DAT ; pcgrpId = IDENT_PC1500; pcId = 1544;}
    else if (code == IDENT_NEW_TEL)
        {if (Qcnt == 0) printf ("Memo Telephone Data, New DB\n") ; type = TYPE_TEL ; pcgrpId = GRP_NEW; pcId = 1100;}
    else if (code == IDENT_NEW_SCD)
        {if (Qcnt == 0) printf ("Memo Schedule Data, New DB\n") ; type = TYPE_SCD ; pcgrpId = GRP_NEW; pcId = 1100;}
    else if (code == IDENT_NEW_NOT)
        {if (Qcnt == 0) printf ("Memo Notes Data, New DB\n") ; type = TYPE_NOT ; pcgrpId = GRP_NEW; pcId = 1100;}
    else if (code == IDENT_NEW_CRD)
        {if (Qcnt == 0) printf ("Basic, full RAM card, New DB\n") ; type = TYPE_CRD ; pcgrpId = GRP_NEW; pcId = 1100;}
    else if (code == IDENT_NEW_CSL)
        {if (Qcnt == 0) printf ("CASL or CAP-X Assembler, New\n") ; type = TYPE_IMG ; ptrFile->subtype = TYPE_CSL ;
         pcgrpId = GRP_NEW ;
        }
    else if (code == IDENT_NEW_BAS)
        {if (Qcnt == 0) printf ("Basic, New\n") ; type = TYPE_IMG ; pcgrpId = GRP_NEW ;}
    else if (code == IDENT_NEW_PAS)
        {if (Qcnt == 0) printf ("Basic with password, New\n") ; type = TYPE_IMG ; pcgrpId = GRP_NEW ;}
    else if (code == IDENT_EXT_BAS)
        {if (Qcnt == 0) printf ("Basic, Extended\n") ; type = TYPE_IMG ;
         if ( pcgrpId != GRP_E ) pcgrpId = GRP_EXT ;
        }
    else if (code == IDENT_EXT_PAS)
        {if (Qcnt == 0) printf ("Basic with password, Extended\n") ; type = TYPE_IMG ; pcgrpId = GRP_EXT ;}
    else if (code == IDENT_NEW_DAT)
        {if (Qcnt == 0) printf ("Data, New\n") ; type = TYPE_DAT ; pcgrpId = GRP_NEW ;}
    else if (code == IDENT_OLD_MEM)
        {if (Qcnt == 0) printf ("Mem Data 10kB, Old DB\n") ; type = TYPE_MEM ; pcgrpId = GRP_OLD ;
         if (pcAddr == 0) pcAddr = 0x8A00;
        }
    else if (code == IDENT_OLD_MEM2)
        {if (Qcnt == 0) printf ("Mem Data 2kB, Old DB\n") ; type = TYPE_MEM ; pcgrpId = GRP_OLD ;
         if (pcAddr == 0) pcAddr = 0x8A00;
        }
    else if (code == IDENT_OLD_DAT)
        {if (Qcnt == 0) printf ("Data, Old\n") ; type = TYPE_DAT ; pcgrpId = GRP_OLD ;}
    else if (code == IDENT_NEW_BIN)
        {if (Qcnt == 0) printf ("Binary, New\n") ; type = TYPE_BIN ; pcgrpId = GRP_NEW ;}
    else if (code == IDENT_OLD_BAS)
        {if (Qcnt == 0) printf ("Basic, Old\n") ; type = TYPE_IMG ; pcgrpId = GRP_OLD ;}
    else if (code == IDENT_OLD_PAS)
        {if (Qcnt == 0) printf ("Basic with password, Old\n") ; type = TYPE_IMG ; pcgrpId = GRP_OLD ;}
    else if (code == IDENT_OLD_BIN)
        {if (Qcnt == 0) printf ("Binary, Old\n") ; type = TYPE_BIN ; pcgrpId = GRP_OLD ;}
    else if (code == IDENT_E_BAS)
        {if (Qcnt == 0) printf ("Basic Image, PC-E/G/16\n") ; type = TYPE_IMG ;
         if ( pcgrpId != GRP_G && pcgrpId != GRP_16 ) pcgrpId = GRP_E ;
         if (pcgrpId != GRP_16) ll_Img = 255 ;
        }
    else if (code == IDENT_E_BIN)
        {if (Qcnt == 0) printf ("Binary, PC-E/G/16\n") ; type = TYPE_BIN ;
         if ( pcgrpId != GRP_G && pcgrpId != GRP_16 ) pcgrpId = GRP_E ;
        }
    else if (code == IDENT_E_ASC)
        {if (Qcnt == 0) printf ("ASCII data or source file, PC-E/G/16\n") ; type = TYPE_ASC ;
         if ( pcgrpId != GRP_G && pcgrpId != GRP_16 ) pcgrpId = GRP_E ;
        }
    else if (code == IDENT_PC16_CAS &&
             ptrFile->base_freq == Base_FREQ3 && Base_FREQ3 > 0)
        {if (Qcnt == 0) printf ("ASCII data from PRINT# or IMG from SAVE/COPY CAS: PC-1600\n") ; type = TYPE_ASC ;
         pcgrpId = GRP_16 ;
        }
    else if (code == IDENT_PC16_DAT)
        {if (Qcnt == 0) printf ("Binary DATA format of PC-1600, (PC-1500 compatible)\n") ; type = TYPE_DAT ;
         pcgrpId = GRP_16 ;
        }
    else {
        printf ("Unknown Save Id: %02X !\n", (uint) code) ;
        error = ERR_FMT ;
    }
    if (ptrFile->subtype == TYPE_NOK) ptrFile->subtype = type ;

    return (error) ;
}


int SetFileIdForImg (FileInfo*  ptrFile, ulong* ptrLength)
{
    int error = ERR_OK ;
                                        /* length of Img is without header but corrected with simulated eof marks included in the sum*/
    if ( pcgrpId == IDENT_PC1211)
        {if (Qcnt == 0) printf ("Basic Image, PC-121x stated\n") ; ptrFile->ident = IDENT_PC1211  ; ++ *ptrLength;}
    else if (pcgrpId == IDENT_PC1500 )  // NOTE (mr#1#): PC-1500 (and QT, no images) does use block_len also, check calc problems
        {if (Qcnt == 0) printf ("Basic Image, PC-1500 stated\n") ; ptrFile->ident = IDENT_PC15_BAS; ++ *ptrLength;}
    else if (pcgrpId == GRP_OLD)
        {if (Qcnt == 0) printf ("Basic Image, Old PC-124x/125x/11xx stated\n")     ; ptrFile->ident = IDENT_OLD_BAS ; ++ *ptrLength;}
    else if (pcgrpId == GRP_NEW)
        {if (Qcnt == 0) printf ("Basic Image, New PC-126x/135x/1401-1460 stated\n") ; ptrFile->ident = IDENT_NEW_BAS ; *ptrLength +=2;}
    else if (pcgrpId == GRP_EXT)
        {if (Qcnt == 0) printf ("Basic Image, Extended PC-128x/136x/147x stated\n"); ptrFile->ident = IDENT_EXT_BAS ; *ptrLength +=2;}
    else if (pcgrpId == GRP_G || pcgrpId == GRP_E)
        {if (Qcnt == 0) printf ("Basic Image, PC-E/G stated\n"); ptrFile->ident = IDENT_E_BAS ;
         if (pcgrpId == GRP_G) ptrFile->sum = 8 + 2 ; /* Standard Header FF 03 */
         //  else ptrFile->sum = 8+3+cs(L)+3 ; PC-E500S Std Head FF 34 LImg+53 0D (+ endmark FF)
         if (pcgrpId != GRP_G) ++ *ptrLength; /* E-500 FF and included in Cs */
         ll_Img = 255 ;
         ptrFile->block_len = *ptrLength;
        }
    else if (pcgrpId == GRP_16)
        {if (Qcnt == 0) printf ("Basic Image, PC-1600 stated\n"); ptrFile->ident = IDENT_PC16_BAS ;
         ++ *ptrLength;
         ptrFile->block_len = *ptrLength;
        }
    else {
        printf ("Unknown Id for this Bas-Image!\n") ;
        error = ERR_ARG ;
    }
    ptrFile->subtype = TYPE_IMG ;

    return (error) ;
}

int ReadSaveIdFromWav (FileInfo* ptrFile,
                          FILE** ptrFd)
{
    ulong  order = ORDER_STD, codeLow, code = IDENT_UNKNOWN ;
    ulong  nbStopBits ;
    ulong  tmpL ;
      int  ii ;
      int  error ;

    do {
        ptrFile->ident = IDENT_UNKNOWN ;
        if (ptrFile->base_freq == Base_FREQ2 && Base_FREQ2 > 0) {
            /* Ident for 2500 Hz, 4 bits */
            error = ReadQuaterFromWav (&code, &nbStopBits, ptrFile) ;
            if (error != ERR_OK) break ;

            if (ptrFile->writing == true) { /* RAW and TAP format, SHC-format unknown */
                error = WriteQuaterToTap (code, ptrFd) ; /* tap format */
                if (error != ERR_OK) break ;
                ++ ptrFile->total ;
            }

            if (code == IDENT_PC1500) {
                order = ORDER_INV ;
                ptrFile->ident = code ;
                ptrFile->sum = 0 ;
                ptrFile->block_len = BLK_OLD ;
                ptrFile->count = BLK_OLD - 40 ;
                for ( ii = 16 ; ii < 24 ; ++ii ) {

                    error = ReadByteSumFromWav (order, &tmpL, ptrFile); /* 0x10...0x17 */
                    if ((int)tmpL != ii ) {
                            printf("\n%s: Error in file header, position %i := %lu\n", argP, ii - 15, tmpL) ;
                            count_errors( ERR_SUM, ptrFile) ;
                    }
                    if (error != ERR_OK) break ;

                    if (ptrFile->writing == true) { /* RAW format */
                        error = WriteByteToFile (tmpL, ptrFd) ;
                        if (error != ERR_OK) break ;
                    }
                }
                if (error != ERR_OK) break ;

                error = ReadByteSumFromWav (order, &tmpL, ptrFile);
                if (error != ERR_OK) break ;

                if (ptrFile->writing == true) { /* RAW format */
                    error = WriteByteToFile (tmpL, ptrFd) ;
                    if (error != ERR_OK) break ;
                }

                code = ((code << 4) & 0xF0) + (tmpL & 0x0F) ;
                ptrFile->nbStopBMin = 2 ;
            }
            else break ;
        }

        else if (ptrFile->base_freq == Base_FREQ4 && Base_FREQ4 > 0) {

            error = ReadByteFromQWav( &code, ptrFile) ;
            if (error != ERR_OK) break ;

            if (ptrFile->writing == true) { /* RAW format */
                error = WriteByteToTap (code, ptrFd) ;
                if (error != ERR_OK) break ;
                ++ ptrFile->total ;
            }
            if (code == IDENT_PC1500) {
                error = ReadByteFromQWav( &tmpL, ptrFile) ;
                if (error != ERR_OK) break ;

                if (ptrFile->writing == true) { /* RAW format */
                    error = WriteByteToTap (tmpL, ptrFd) ;
                    if (error != ERR_OK) break ;
                    ++ ptrFile->total ;
                }
                code = code<<8 | (tmpL & 0xFF) ;
                ptrFile->nbStopBMin = 1 ;
            }
            else break ;

            if (code == IDENT_QTAPE) {
                order = ORDER_Q ;
                ptrFile->ident = IDENT_QTAPE ;
                ptrFile->id_version = 4 ;
                ptrFile->sum = 0 ;
                ptrFile->block_len = BLK_OLD ;
                ptrFile->count = BLK_OLD - 40 ;
                for ( ii = 16 ; ii < 24 ; ++ii ) {

                    error = ReadByteSumFromWav (order, &tmpL, ptrFile); /* 0x10...0x17 */
                    if ((int)tmpL != ii ) {
                            printf("\n%s: Error in file header, position %i := %lu\n", argP, ii - 15, tmpL) ;
                            count_errors( ERR_SUM, ptrFile) ;
                    }
                    if (error != ERR_OK) break ;

                    if (ptrFile->writing == true) { /* RAW format */
                        error = WriteByteToFile (tmpL, ptrFd) ;
                        if (error != ERR_OK) break ;
                    }
                }
                if (error != ERR_OK) break ;

                error = ReadByteSumFromWav (order, &tmpL, ptrFile);
                if (error != ERR_OK) break ;

                if (ptrFile->writing == true) { /* RAW format */
                    error = WriteByteToFile (tmpL, ptrFd) ;
                    if (error != ERR_OK) break ;
                }

                ptrFile->sum = code = tmpL ;
            }
            else break ;
        }

        else if (ptrFile->base_freq == Base_FREQ1 && Base_FREQ1 > 0) {
            /* Ident for 4000 Hz, 8 bits */
            error = ReadQuaterFromWav (&code, &nbStopBits, ptrFile) ;
            if (error != ERR_OK || !( code == 7 || code == 6 || code == 2 || code == 8 )) break ;

            error = ReadQuaterFromWav (&codeLow, &nbStopBits, ptrFile) ;  // first stop bit nb: 0
            if (error != ERR_OK) break ;

            if ( code == 6 && codeLow < 0xB ) { /* New Memos - Read the length */
                if ( ( (ptrFile->debug & 0x0440) > 0 ) && (Qcnt == 0) ) printf("Length:");
                error = ReadByteTraceFromWav (ORDER_STD, &tmpL, ptrFile); // Length HI
                if (error != ERR_OK) break ;
                ptrFile->length = (tmpL << 8) ;
                error = ReadByteTraceFromWav (ORDER_STD, &tmpL, ptrFile); // Length Low
                if (error != ERR_OK) break ;
                ptrFile->length += tmpL ;
            }
            code = (code << 4) + codeLow ;

            switch (code) {
                case IDENT_NEW_BAS :
                case IDENT_NEW_PAS :
                case IDENT_NEW_BIN :
                    if (nbStopBits < 4) {
                        ptrFile->nbStopBMin = 0 ;       /* PC 1401 V.1, see Bin2wav MODE_B15, MODE_B12 */
                        pcId = 1401 ;
                    }
                    else {
                        ptrFile->nbStopBMin = 1 ;
                        if (pcId == 1401) pcId = 1402 ; /* PC 1401 V.2 identical except for the RAM size */
                    }
                    break ;
                default :
                    ptrFile->nbStopBMin = 1 ;
                    break ;
            }
        }
        else if (ptrFile->base_freq == Base_FREQ3 && Base_FREQ3 > 0) {

            ptrFile->sum = 0 ;
            ptrFile->block_len = BLK_E_HEAD ;
            ptrFile->ident = IDENT_E_BAS ; /*for first identity byte only */

            error = ReadByteSumFromWav (ORDER_E, &code, ptrFile);
            if (error != ERR_OK) break ;
        }
        else error = ERR_ARG;

        ptrFile->ident = code ;

    } while (0) ;

    if ( ptrFile->ident == IDENT_PC1500 ) ptrFile->ident = IDENT_UNKNOWN ; /* no sub ID */

    return (error);
}


int ReadSaveIdFromTap (FileInfo* ptrFile,
                          FILE** ptrFd)
{
    ulong  code, codeH ;
      int  error ;

    do {

        ptrFile->ident = IDENT_UNKNOWN ;

        if (KHXc > 0) {
            error = ReadByteFromKhx (ORDER_STD, &code, ptrFile) ;
            if ((code & 0xF0) >> 4 == IDENT_PC1500) code = IDENT_PC1500 ;
        }
        else
            error = ReadByteFromTap (ORDER_STD, &code, ptrFile) ;
        if (error != ERR_OK) break ;
                                            /* force Id also with false -p*/
        if((code & 0x0F) == IDENT_PC1500)   /* Ident for 2500 Hz, 4 bits */
            ptrFile->base_freq = Base_FREQ2 = BASE_FREQ2 ;
        else if(code < IDENT_PC1500)        /* Ident for 3000 Hz, 8 bits */
            ptrFile->base_freq = Base_FREQ3 = BASE_FREQ3 ;
        else {                              /* Ident for 4000 Hz, 8 bits */
            ptrFile->base_freq = Base_FREQ1 = BASE_FREQ1 ;
            codeH = (code >> 4) & 0x0F ;
            if ( codeH != 7 && codeH != 6 && codeH != 2 && codeH != 8 ) return (ERR_FMT) ;
            ptrFile->ident = code ;
        }
        if (ptrFile->ident == IDENT_UNKNOWN ) {

            if (KHXc > 0) error = sseek (ptrFile, -2, SEEK_CUR) ; /* no garbage allowed */
            else          error = sseek (ptrFile, -1, SEEK_CUR) ;
            if (error != ERR_OK) {
                printf ("\n%s:rId - Can't seek the file\n", argP) ;
                error = ERR_FILE ;
                break ;
            }
            error = ReadSaveIdFromWav (ptrFile, ptrFd);
        }

    } while (0) ;
    return (error);
}

int ReadSaveNameOrPassFromWav (char*  ptrName,
                              ulong*  ptrEaddr,
                             ushort*  ptrFlags,
                           FileInfo*  ptrFile,
                               FILE** ptrFd)
{
    ulong  byte ;
    ulong  tmpL ;
     char  tmpS[10] ;
     uint  ii, jj ;
    ulong  ident = ptrFile->ident ;    /* backup identity */
    ulong  order = ORDER_INV ;
      int  error ;

        ptrName[0] = 0 ;
        tmpS[0]    = 0 ;

        switch (ident) {

        case IDENT_QT_BAS :
        case IDENT_QT_BIN :
        case IDENT_QT_RSV :
        case IDENT_QT_DIM :
        case IDENT_QT_DAT :

            order = ORDER_Q;

        case IDENT_PC15QTBAS :
        case IDENT_PC15QTBIN :

        case IDENT_PC15_BAS :
        case IDENT_PC15_RSV :
        case IDENT_PC15_DEF :
        case IDENT_PC15_BIN :
        case IDENT_PC15_DAT :

            for ( ii = 9 ; ii < 25 ; ++ii ) {
                error = ReadByteSumFromWav (order, &byte, ptrFile);
                if (error != ERR_OK) break ;

                if (byte > 0) strcat (ptrName, CodePc1500_1[byte]) ; /* ASCII transcription only */
            }
            if (error != ERR_OK) break ;

            if (order == ORDER_Q) {
                error = ReadByteSumFromWav (order, &byte, ptrFile);
                if (error != ERR_OK) break ;

                *ptrFlags = byte; /* ME1:4, PV1:2, PU1:1 */
                if ( byte >0 && Qcnt==0 && (ptrFile->debug & 0x440)>0 ) {
                        printf("(F:") ;
                        if ((byte &4)==4 )printf("ME1") ;
                        if ((byte &7) >4 )printf("+") ;
                        if ((byte &2)==2 )printf("PV1") ;
                        if ((byte &3) >2 )printf("+") ;
                        if ((byte &1)==1 )printf("PU1") ;
                        printf(")") ;
                }
                error = ReadByteSumFromWav (order, &byte, ptrFile);
                if (error != ERR_OK) break ;
                if ( (ident == IDENT_QT_BIN && (ushort) (0xFF - byte) != *ptrFlags) ||
                     (ident != IDENT_QT_BIN && (int)byte > 0) ) {
                        printf("\n%s: Unexpected flag descriptor %lu in file name header, position %i\n", argP, byte, ii + 1) ;
                        count_errors( ERR_FMT, ptrFile) ;
                }
                ii = 27 ; /* Qsave M */
                jj = 32 ;
            }
            else { /* PC-1500 */
                ii = 25 ;
                jj = 34 ;
            }
            for ( /* ii = ii */ ; ii < jj ; ++ii ) {
                error = ReadByteSumFromWav (order, &byte, ptrFile);
                if ((int)byte > 0 ) {
                        printf("\n%s: Unexpected byte %lu in file name header, position %i\n", argP, byte, ii + 1) ;
                        count_errors( ERR_FMT, ptrFile) ;
                }
                if (error != ERR_OK) break ;
            }
            if (error != ERR_OK) break ;

            if (order == ORDER_Q) {
                error = ReadByteSumFromWav (order, &byte, ptrFile);
                if (error != ERR_OK) break ;
                *ptrEaddr = byte<<8 ;

                error = ReadByteSumFromWav (order, &byte, ptrFile);
                if (error != ERR_OK) break ;
                *ptrEaddr |= byte ;
            }

            break ;


        case IDENT_E_BAS :
            case IDENT_PC16_BAS :
            case IDENT_PC16_RSV :
        case IDENT_E_BIN :
        case IDENT_E_ASC :
            case IDENT_E_IMG :
        case IDENT_PC16_CAS :
            case IDENT_PC16_IMG :
        case IDENT_PC16_DAT :

            order = ORDER_E;

            ii = 1;
            do { /* read the name, PC-1600 with extension */
                error = ReadByteSumFromWav (order, &byte, ptrFile);
                if (error != ERR_OK) break ;

                if (byte > 0) strcat (ptrName, CodeE437[byte]) ;
                if (ii == 0x0D && byte == 0x20) byte = 0;

            } while ( ++ii < 0x11 && byte > 0 ) ;
            if (error != ERR_OK) break ;

            for ( jj = strlen(ptrName); jj > 0 ; --jj ) { /* remove fill spaces at end of name */
                if (ptrName[jj-1] == 0x20) ptrName[jj-1] = 0 ;
                else break;
            }

            while ( ii < 0x11 ) { /* read fill bytes */
                error = ReadByteSumFromWav (order, &byte, ptrFile);

                if ((int)byte != 0x20 && (int)byte != 0x00 ) {
                    if (ii == 0x0E) {
                         strcat (ptrName, ".") ;
                        /* IDENT_PC16_IMG: BAS,  IDENT_PC16_CAS ASCII Source (,A): BAS,
                           IDENT_PC16_CAS ASCII Source SAVE* (Comments only): TXT,
                           ASCII Data: no extension */
                    }
                    if (ii >= 0x0E)
                         strcat (ptrName, CodeE437[byte]) ;
                    else {
                        printf("\n%s: Unexpected byte %lu in file name header, position %i\n", argP, byte, ii + 1) ;
                        count_errors( ERR_FMT, ptrFile) ;
                    }
                }
                if (error != ERR_OK) break ;

                ++ii;
            }
            if (error != ERR_OK) break ;

            error = ReadByteSumFromWav (order, &byte, ptrFile);
                if ( !( (int)byte == 0x0D || ((int)byte == 0x00 && (ident == IDENT_PC16_CAS || ident == IDENT_E_ASC)) )) {
                        printf("\n%s: Unexpected byte %lu in file name header, position %i\n", argP, byte, ii + 1) ;
                        count_errors( ERR_FMT, ptrFile) ;
                }

            break ;


        default : /* PC-1211 ... 1475*/

            ptrFile->count = 0 ;
            ptrFile->sum = 0 ;
            ptrFile->ident = IDENT_NAMEPAS ; /* change identity for ReadByteSum */
            for ( ii = 0 ; ii < 8 ; ++ii ) { /* +1 byte checksum */
                error = ReadByteSumFromWav (order, &byte, ptrFile);
                if (ptrFile->writing == true) { /* SHC format */
                    error = WriteByteToDatFile (byte, ptrFd) ;
                    if (error != ERR_OK) break ;
                }

                if (error != ERR_OK || ii == 7 ) break ;
                if ( byte > 0) {
                    switch (ident) {
                    case IDENT_PC1211 :
                    case IDENT_PC121_DAT :
                    case IDENT_OLD_BAS :
                    case IDENT_OLD_PAS :
                    case IDENT_OLD_DAT :
                    case IDENT_OLD_MEM :
                    case IDENT_OLD_MEM2 :
                    case IDENT_OLD_BIN :
                        if (strlen (CodeOld[byte]) == 1) strcat (tmpS, CodeOld[byte]) ;
                        else strcat (tmpS, "~") ;
                        break ;

                    case IDENT_NEW_BAS :
                    case IDENT_NEW_PAS :
                    case IDENT_NEW_CSL :
                    case IDENT_NEW_CRD :
                    case IDENT_NEW_TEL :
                    case IDENT_NEW_SCD :
                    case IDENT_NEW_NOT :
                    case IDENT_NEW_DAT :
                    case IDENT_NEW_BIN :
                        if (strlen (CodeNew[byte]) == 1) strcat (tmpS, CodeNew[byte]) ;
                        else strcat (tmpS, "~") ;
                        break ;

                    case IDENT_EXT_BAS :
                    case IDENT_EXT_PAS :
                        if (strlen (CodeExt[byte]) == 1) strcat (tmpS, CodeExt[byte]) ;
                        else strcat (tmpS, "~") ;
                        break ;

                    default :
                        printf ("\n%s:RName: Unknown Ident %lu\n", argP, ident) ;
                        error = ERR_FMT ;
                        break ;
                    } // end switch default
                }
            }
            if ((int)byte != 0xF5 || ii < 7 ) {
                    printf("\n%s: Unexpected byte %lu in file name header, position %i\n", argP, byte, ii + 1 ) ;
                    count_errors( ERR_FMT, ptrFile) ;
            }
            if (error != ERR_OK) break ;
            ptrFile->count  = 0 ;

            tmpL = strlen (tmpS) ;
            for ( ii = 0 ; ii < tmpL ; ++ii )
                ptrName[ii] = tmpS[tmpL - ii - 1] ;
            ptrName[tmpL] = 0 ;

            break ;
    }  // end switch all

    ptrFile->ident = ident ;    /* restore identity */

    return (error);
}


int ReadHeadFromEWav (  ulong*  ptrAddr,
                        ulong*  ptrEaddr,
                        ulong*  ptrSize,
                     FileInfo*  ptrFile)
{
      int  ii ;
     long  position ;
    ulong  addr, eaddr, haddr=0 ;    /* data start address, entry address, BASIC header link address */
    ulong  length=0 ;
    ulong  tmpL[15], byte ;
    ulong  ident = ptrFile->ident ;  /* backup id, new identity, if changes needed*/
     char  tmpS[10] ;
      int  error ;

    do {

            /* read the rest of 1. file block  header */
            for ( ii = 0 ; ii < 7 ; ++ii ) {    /* 7 bytes */
                error = ReadByteSumFromWav (ORDER_E, &tmpL[ii], ptrFile);
                if (error != ERR_OK) break ;
            }
            if (error != ERR_OK) break ;
            for ( ii = 0x19 ; ii < 0x1D ; ++ii ) { /* Date+Time PC-1600: Mon Day Hour Min */
                error = ReadByteSumFromWav (ORDER_E, &byte, ptrFile);
                if ((int)byte != 0x00 ) {
                    if (pcgrpId != GRP_16 ) {
                        pcgrpId  = GRP_16 ;
                        if (Qcnt ==0) printf("\n%s: PC-1600 detected\n", argP) ;
                    }
                }
                if (error != ERR_OK) break ;
            }
            if (error != ERR_OK) break ;

            /* Mode 2 */
            if (ptrFile->ident == IDENT_E_BAS) {
                    if (tmpL[6] == 0x02) {
                        if (Qcnt ==0) printf(" ReSerVe data from 1600-Series, mode 2 ID %lu \n", tmpL[6]) ; // 0x2
                        ident = IDENT_PC16_RSV ;
                        pcgrpId = GRP_16 ;
                        ptrFile->type = TYPE_RSV ;
                        ptrFile->subtype = TYPE_RSV ;
                    }
                    else { //if (tmpL[6] == 0x01)
                        if (Qcnt ==0 && ptrFile->debug != 0)
                                     printf(" BASIC image from E/G/1600-Series, mode 2 ID %lu\n", tmpL[6]) ; //0x1
                    }
            }

            /* PC-1600 Mode 2 (PC-1500) file format */
            if ((ptrFile->ident == IDENT_E_ASC || ptrFile->ident == IDENT_PC16_CAS)
                && Qcnt==0 && ptrFile->debug != 0) {
                    if (tmpL[6] > 0 ) printf(" Data mode 2 ID %lu from E/G-Series\n", tmpL[6]) ; // E:0x4 G-BAS:0x01
                    else printf(" Ascii Data or source file from G/1600-Series\n") ;
            }

            for ( ii = 7 ; ii < 10 ; ++ii ) {    /* 3 bytes */
                error = ReadByteSumFromWav (ORDER_E, &tmpL[ii], ptrFile);
                if (error != ERR_OK) break ;
            }
            eaddr = tmpL[9] ;
            eaddr = (eaddr << 8) + tmpL[5] ;
            eaddr = (eaddr << 8) + tmpL[4] ;
            addr = tmpL[8] ;
            addr = (addr << 8) + tmpL[3] ;
            addr = (addr << 8) + tmpL[2] ;
            length = tmpL[7] ;
            length = (length << 8) + tmpL[1] ;
            length = (length << 8) + tmpL[0] ;

            for ( ii = 0x20 ; ii < BLK_E_HEAD ; ++ii ) { /* 16 bytes */
                error = ReadByteSumFromWav (ORDER_E, &byte, ptrFile);
                if ((int)byte != 0x00 && !(ident==IDENT_PC16_CAS && ii <0x24)) {
                        printf("\n%s: Unexpected byte %lu in file name header, position %i\n", argP, byte, ii + 1) ;
                        count_errors( ERR_FMT, ptrFile) ;
                }
                if (error != ERR_OK) break ;
            }
            if (error != ERR_OK) break ;

            error = FindFreqAndSyncFromWav (ptrFile) ;  /* silence, sync, sync start bit */
            if (error != ERR_OK) break ;

            ptrFile->count = 0 ;
            if (ptrFile->ident == IDENT_E_ASC || ptrFile->ident == IDENT_PC16_CAS )
                ptrFile->block_len = BLK_E_DAT ;
            else
                ptrFile->block_len = length ;


            if ( ptrFile->ident == IDENT_E_BAS ||     /* check if data from PC-1600 CSAVE or other */
                 ptrFile->ident == IDENT_E_ASC ||     // ToDo check if Ascii Data transfer still works
                 ptrFile->ident == IDENT_PC16_BAS ||
                 ptrFile->ident == IDENT_PC16_CAS ) { /* check if PRINT# CAS: data or SAVE CAS: binary image */

                position = stell( ptrFile ) ; /* position after start bit of block */
                if (position <= 0) {
                    printf ("\n%s:rHeadBin - Can't ftell the wav file\n", argP) ;
                    error = ERR_FILE ;
                    break ;
                }
                /* Read first byte of BASIC data block */
                error = ReadByteFromWav (ORDER_E, &byte, ptrFile);
                if (error != ERR_OK) break ;

                if (ptrFile->ident == IDENT_PC16_CAS) {
                    if ((int)byte == 0xFF ) {
                        if (Qcnt ==0) printf("\n%s: PC-1600 COPY TO / SAVE CAS: image detected, IMG will be written\n", argP) ;
                        if (Qcnt ==0) printf  ("%s: Better to use ASCII mode of SAVE CAS: with ',A' or CSAVE\n", argP) ;
                        ident = IDENT_PC16_IMG ;
                        ptrFile->type = TYPE_IMG ;
                        ptrFile->subtype = TYPE_IMG ;
                    }
                    else if ((int)byte != 0xFF && pcgrpId == GRP_16 ) {
                        if (Qcnt ==0) printf("\n%s: PC-1600 PRINT # CAS: detected\n", argP) ;
                    }
                }
                else if (ptrFile->ident == IDENT_E_ASC) {
                    if ((int)byte == 0xFF ) {
                        if (Qcnt ==0) printf("\n%s: PC-E COPY TO / SAVE CAS: image detected, IMG will be written\n", argP) ;
                        if (Qcnt ==0) printf  ("%s: Better to use ASCII mode of SAVE CAS: with ',A' or CSAVE\n", argP) ;
                        ident = IDENT_E_IMG ;
                        ptrFile->type = TYPE_IMG ;
                        ptrFile->subtype = TYPE_IMG ;
                    }
                    else if ((int)byte != 0xFF  ) { // && pcgrpId == GRP_E
                        if (Qcnt ==0) printf("\n%s: PC-E PRINT # CAS: detected\n", argP) ;
                    }
                }
                else if ((int)byte != 0xFF && pcgrpId != GRP_16 ) {
                        pcgrpId = GRP_16 ;
                        if (Qcnt ==0) printf("\n%s: PC-1600 detected\n", argP) ;
                }
                else if ((int)byte == 0xFF && pcgrpId == GRP_16 ) {
                        pcgrpId = GRP_E ;
                        if (Qcnt ==0) printf("\n%s: PC-E/G detected - check parameter\n", argP) ;
                }
                /* Rewind to the beginning of the block data */
                error = sseek (ptrFile, position, SEEK_SET) ;
                    if (error != ERR_OK) {
                        printf ("\n%s:rHeadBin - Can't seek the wav file\n", argP) ;
                        error = ERR_FILE ;
                        break ;
                    }
            }
            if (pcgrpId == GRP_16 && ident != IDENT_PC16_IMG) {
                if (ident == IDENT_E_BAS) ident = IDENT_PC16_BAS ;
            }
            else if (ptrFile->ident == IDENT_E_BAS || ident == IDENT_PC16_IMG || ident == IDENT_E_IMG ) {

            /* Read Basic file header of 2. transmission block */

                error = ReadByteSumFromWav (ORDER_E, &byte, ptrFile);
                if ((int)byte != 0xFF ) {
                        printf("\n%s: Unexpected byte %lu in 2. file header, position %i\n", argP, byte, 1) ;
                        count_errors( ERR_FMT, ptrFile) ;
                }
                if (error != ERR_OK) break ;
                /* check if data from PC-E500 series or PC-G/E2 series */
                for ( ii = 0 ; ii < 3 ; ++ii ) {
                    error = ReadByteSumFromWav (ORDER_E, &tmpL[ii], ptrFile);
                    if (error != ERR_OK) break ;
                }
                if (error != ERR_OK) break ;

                if ((int) tmpL[0] == 16 && pcgrpId == GRP_16 ) {
                    pcgrpId = GRP_16 ;
                    if (Qcnt == 0) printf("%s: PC-1600 Image from SAVE CAS: detected\n", argP) ;
                }
                if ((int) tmpL[1] == 3 && pcgrpId == GRP_E ) {
                    pcgrpId = GRP_G ;
                    if (Qcnt == 0) printf("%s: PC group G detected\n", argP) ;
                }
                else if ((int) tmpL[1] == 0 && pcgrpId == GRP_G ) {
                    pcgrpId = GRP_E ;
                    if (Qcnt == 0) printf("\n%s: PC group E500 detected - check parameter\n", argP) ;
                }
                else if ((int) tmpL[1] == 8 ) {
                    if (Qcnt == 0) printf("\n%s: BASIC Image from Text Modus of E-Series\n", argP) ;
                    ptrFile->subtype = TYPE_TXT ;
                }

                if (pcgrpId == GRP_E) {
                    for ( ii = 3 ; ii < 9 ; ++ii ) {
                        error = ReadByteSumFromWav (ORDER_E, &tmpL[ii], ptrFile);
                        if (error != ERR_OK) break ;
                    }
                    if (error != ERR_OK) break ;
                    if ((int) tmpL[3] != '4' ) {
                        printf("\n%s: Unexpected byte %lu in 2. file header, position %i\n", argP, tmpL[3], 5 ) ;
                        count_errors( ERR_FMT, ptrFile) ;
                    }
                    haddr = tmpL[8] ; /* size with 2 file headers in RAM */
                    haddr = (haddr << 8) + tmpL[7] ;
                    haddr = (haddr << 8) + tmpL[6] ;

                }
                if (pcgrpId == GRP_16) {
                    for ( ii = 3 ; ii < 14 ; ++ii ) {
                        error = ReadByteSumFromWav (ORDER_E, &tmpL[ii], ptrFile);
                        if (error != ERR_OK) break ;
                    }
                    if (error != ERR_OK) break ;
                    if ((int) tmpL[3] != 0x21 && (int) tmpL[3] != 0x10 ) { /* file type IMG or BIN */
                        printf("\n%s: Unexpected byte %lu in 2. file header, position %i\n", argP, tmpL[3], 5 ) ;
                        count_errors( ERR_FMT, ptrFile) ;
                    }
                    if (tmpL[3] == 0x10) ptrFile->subtype = TYPE_BIN ;
                    /* see Tech Ref PC-1600 chap 3.3.1, index -1 */
                    haddr = tmpL[6] ;    /* size without header */
                    haddr = (haddr << 8) + tmpL[5] ;
                    haddr = (haddr << 8) + tmpL[4] ;

                    if (addr == 0) {
                        addr = tmpL[9] ;   /* load address */
                        addr = (addr << 8) + tmpL[8] ;
                        addr = (addr << 8) + tmpL[7] ;
                    }
                    if (eaddr == 0) {
                        eaddr = tmpL[12] ; /* execution address*/
                        eaddr = (eaddr << 8) + tmpL[11] ;
                        eaddr = (eaddr << 8) + tmpL[10] ;
                    }
                }
                else {  /* GRP_E, GRP_G */
                /* else { // if (pcgrpId == GRP_G)
                } */
                    for ( ii = 0 ; ii < 8 ; ++ii ) { /* Password */
                        error = ReadByteSumFromWav (ORDER_E, &byte, ptrFile);
                        if (error != ERR_OK) break ;
                        if (byte > 0x1F)
                            tmpS[ii]= byte ;
                        else
                            tmpS[ii]=0 ;
                    }
                    if (error != ERR_OK) break ;
                    if (Qcnt == 0 && tmpS[0] != 0) printf ("Password      : %s\n", tmpS) ;
                }
                if (pcgrpId == GRP_E) { /* Header end marks */
                    error = ReadByteSumFromWav (ORDER_E, &byte, ptrFile);
                    if ((int)byte != 0x0D ) {
                        printf("\n%s: Unexpected byte %lu in 2. file header, position %i\n", argP, byte, ii + 11) ;
                        count_errors( ERR_FMT, ptrFile) ;
                    }
                    if (error != ERR_OK) break ;
                }
                else if (pcgrpId == GRP_16) {
                    error = ReadByteSumFromWav (ORDER_E, &byte, ptrFile);
                    if ((int)byte != 0x0F ) {
                        printf("\n%s: Unexpected byte %lu in 2. file header, position %i\n", argP, byte, ii + 8) ;
                        count_errors( ERR_FMT, ptrFile) ;
                    }
                    if (error != ERR_OK) break ;
                }
            }

            if ( ptrFile->ident != IDENT_E_ASC && ptrFile->ident != IDENT_PC16_CAS) {

                if (Qcnt == 0) {
                    if (ptrFile->ident == IDENT_E_BIN ) {
                        if (eaddr != 0xFFFFFF) printf (" Entry address : 0x%06X\n", (uint) eaddr);
                        printf (" Image start address : 0x%06X\n", (uint) addr);
                        printf (" Image  end  address : 0x%06X, ", (uint) (addr + length - 1));
                    }
                    printf (" Image size (with 2nd file header) : %lu bytes\n", length);
                    if (haddr > 0 ) printf (" Header+ program length in RAM : 0x%06X bytes\n", (uint) haddr);
                }
            }
            else {
                if (Qcnt == 0 && haddr > 0)
                    printf (" Header+ program length in RAM : %u bytes\n", (uint) haddr);
                if (length == 0) {
                    if (ident == IDENT_PC16_IMG)   length = haddr ; // no header included
                    else if (ident == IDENT_E_IMG) length = haddr -33 -19; // -33 = with 2. header -19 = netto with end mark
                    // ToDo PC-G
                }
            }

        *ptrAddr  = addr ;
        *ptrEaddr = eaddr ;
        *ptrSize  = length ;

    } while (0) ;
    ptrFile->ident = ident ; /* changed identity for PC-1600 */

    return (error);
}


int ReadHeadFrom15Wav (ulong*  ptrOrder,
                       ulong*  ptrAddr,
                       ulong*  ptrEaddr,
                       ulong*  ptrSize,
                       ushort* ptrFlags,
                     FileInfo* ptrFile)
{
      int  ii ;
    ulong  addr, eaddr ;    /* data start address, entry */
    ulong  length ;
    ulong  tmpL[10] ; //, byte
    ulong  ident = ptrFile->ident ;
      int  error ;

    do {

        switch (ident) {
        case IDENT_PC15QTBAS :
        case IDENT_PC15QTBIN :
            Stop_Bit_Max = 80 ; /* 0.25 sec because 5 kHz Signal would be skipped else*/
            break ;
        }
        if (*ptrOrder == ORDER_Q || ident == IDENT_PC15_DAT)
            ptrFile->status= STAT_SYNC; /* find next block with sync, not skip */

        for ( ii = 0 ; ii < 6 ; ++ii ) {    /* Pos. ii + 35, 6 bytes size and addresses + 2 checksum */
                error = ReadByteSumFromWav (*ptrOrder, &tmpL[ii], ptrFile);
                if (error != ERR_OK) break ;
        }
        ptrFile->status= STAT_OK; /* Auto-skip after checksum enabled */

        addr = tmpL[0] ;
        addr = (addr << 8) + tmpL[1] ;
        *ptrAddr = addr ;

        if (*ptrOrder == ORDER_Q)
            eaddr = *ptrEaddr ;
        else {
            eaddr = tmpL[4] ;
            eaddr = (eaddr << 8) + tmpL[5] ;
            *ptrEaddr = eaddr ;
        }

        length = tmpL[2] ;
        length = (length << 8) + tmpL[3] ;

        if (ident == IDENT_PC15QTBAS || ident == IDENT_PC15QTBIN) {
                ptrFile->block_len = length + 1 ;
                ptrFile->count = 0 ;
                ptrFile->sum = 0 ;
        }
        if ((ident == IDENT_PC15_BAS || ident == IDENT_PC15QTBAS  || ident == IDENT_QT_BAS )&& Qcnt == 0)
                printf (" BASIC image size : %lu bytes with an end mark.\n", length + 1);

        else if ( ident == IDENT_PC15_BIN  || ident == IDENT_PC15_RSV || ident == IDENT_PC15_DEF ||
             ident == IDENT_PC15QTBIN || ident == IDENT_QT_BIN || ident == IDENT_QT_RSV || ident == IDENT_QT_DIM ) {
            ++length ;                  /* not for IDENT_PC15_BAS (IDENT_PC15_DAT) */
            if (Qcnt == 0) {
                if ((ptrFile->debug & 0x4C0)>0) printf ("\n");
                if (*ptrFlags > 0)
                    printf (" Flag byte and start address : 0x%01X%04X\n", (uchar) *ptrFlags, (uint) addr);
                else
                    printf (" Start address : 0x%04X\n", (uint) addr);
                printf (" End   address : 0x%04X, Binary image size : %lu bytes\n", (uint) (addr + length - 1), length);
                if (eaddr != 0xFFFF) printf (" Entry address : 0x%04X\n", (uint) eaddr);
            }
        }
        *ptrSize = length ;

        if (ident == IDENT_PC15QTBAS ||
            ident == IDENT_PC15QTBIN) {

                ptrFile->base_freq=Base_FREQ4 ;
                *ptrOrder = ORDER_Q ;
        }
        if (*ptrOrder == ORDER_Q || error == ERR_NSYNC) {   /* QTAPE sync, IDENT_PC15_DAT with 1.2 sec sync */
                error = FindFreqAndSyncFromWav (ptrFile) ;
                if (error != ERR_OK) break ;
        }

        if (*ptrOrder == ORDER_Q) {
            if ( ptrFile->id_version == 1) {
                ptrFile->block_len = BLK_QT1 ;
                ptrFile->count = BLK_QT1-(length & 0xFF) ; /* QTAPE 1 counts backward */
                if (ident == IDENT_PC15QTBAS) -- ptrFile->count ;
            }
            else if ( ptrFile->ident != IDENT_QT_DAT ) {   /* QTAPE 4 only full blocks */
                error = ReadUsedatLenFromQTWav (*ptrOrder, ptrFile);
                ptrFile->count = 0 ;
            }
        }

    } while (0) ;

    return (error);
}

/* Bin PC-1245 ... PC-1475 */
int ReadHeadFromBinWav (ulong*  ptrAddr,
                        ulong*  ptrSize,
                     FileInfo*  ptrFile,
                         FILE** ptrFd)
{
      int  ii ;
    ulong  addr ;    /* data start address */
    ulong  length ;
    ulong  tmpL[10] ;
    ulong  ident = ptrFile->ident ;  /* backup identity */
      int  error ;

    do {
        ptrFile->ident = IDENT_NAMEPAS ; /* change identity for ReadByteSum */

        for ( ii = 0 ; ii < 8 ; ++ii ) {
            error = ReadByteSumFromWav (ORDER_INV, &tmpL[ii], ptrFile);
            if (error != ERR_OK) break ;
            if (ptrFile->writing == true) { /* SHC format */
                error = WriteByteToDatFile (tmpL[ii], ptrFd) ;
                if (error != ERR_OK) break ;
            }
        }
        if (error != ERR_OK) break ;

        ptrFile->count  = 0 ;

        addr   = tmpL[4] ;
        addr   = (addr << 8) + tmpL[5] ;
        length = tmpL[6] ;
        length = (length << 8) + tmpL[7] ;
        /* Checksum read by ReadByteSum automatically */
        ++length ;

        if (Qcnt == 0) {
                printf (" Start address : 0x%04X\n", (uint) addr);
                printf (" End   address : 0x%04X, Binary image size : %lu bytes\n", (uint) (addr + length - 1), length);
        }
        *ptrAddr = addr ;
        *ptrSize = length ;

    } while (0) ;
    ptrFile->ident = ident ;   /* restore identity */

    return (error);
}

/* Mem Data PC-1150/40, 124x-DB */
int ReadHeadFromMemWav (ulong*  ptrAddr,
                        ulong*  ptrSize,
                     FileInfo*  ptrFile,
                         FILE** ptrFd)
{
      int  ii ;
    ulong  addr ;    /* data start address */
    ulong  length ;
    ulong  tmpL[10] ;
    ulong  ident = ptrFile->ident ;  /* backup identity */
      int  error ;

    do {
        ptrFile->ident = IDENT_NAMEPAS ; /* change identity for ReadByteSum */

        /*  BgnDataVarPointerLow BgnDataVarPointerHigh 00 8A 00 00 00 F5
            Checksum read by ReadByteSum automatically */

        for ( ii = 0 ; ii < 8 ; ++ii ) {
            error = ReadByteSumFromWav (ORDER_INV, &tmpL[ii], ptrFile);
            if (error != ERR_OK) break ;
            if (ptrFile->writing == true) { /* SHC format */
                error = WriteByteToDatFile (tmpL[ii], ptrFd) ;
                if (error != ERR_OK) break ;
            }
        }
        if (error != ERR_OK) break ;

        ptrFile->count  = 0 ;

        addr   = tmpL[1] ;
        addr   = (addr << 8) + tmpL[0]; /* Start address: 4-bit (nibbles) */
        length = tmpL[3] ;
        length = (length <<8)+ tmpL[2]; /* End address (+1): 4-bit (nibbles) */
        pcAddr = length ;
        length = length - addr;         /* Length in Nibbles */
        length = (length >> 1) ;        /* Length in Bytes   */

        if (Qcnt == 0) {
                printf (" Start address : 0x%04X (4 bit nibbles)\n", (uint) addr);
                printf (" Binary image size : %lu bytes\n", length);
        }
        *ptrAddr = addr ;
        *ptrSize = length ;

    } while (0) ;
    ptrFile->ident = ident ;   /* restore identity */

    return (error);
}


int ReadHeadFromDataWav (   ulong  order,
                         TypeInfo* ptrType,
                         FileInfo* ptrFile)
{
      int  ii ;
    ulong  tmpL[ DATA_HEAD_LEN ] ; //, byte
      int  error ;

    do {
        if (ptrFile->synching > 0 ) ptrFile->synching = 0 ;
        if (ptrFile->status == STAT_EOT ) ptrFile->status = STAT_OK ;


        if ( ptrFile->ident == IDENT_PC15_DAT || ptrFile->ident == IDENT_QT_DAT)
            ptrFile->count = BLK_OLD - DATA_HEAD_LEN ; /* 80 block - 5 header */

        else if ( ptrFile->ident == IDENT_PC16_DAT ) {
            ptrFile->count = 0 ;
            ptrFile->block_len = DATA_HEAD_LEN ;
        }
        else ptrFile->count = BLK_OLD_SUM - DATA_HEAD_LEN ;
        /* 8 bytes standard block - (2 bytes len + 3 bytes dim) */


        error = ReadByteSumFromWav (order, &tmpL[0], ptrFile);

        if (ptrFile->ident == IDENT_PC15_DAT) {
            if ( error > ERR_OK ) break ;
            if ( tmpL[0] == EOF_15 ) error = ERR_EOT ;
        }
        if (error != ERR_OK) break ;
        ptrFile->status = STAT_SYNC;

        for ( ii = 1 ; ii < DATA_HEAD_LEN ; ++ii ) {
            error = ReadByteSumFromWav (order, &tmpL[ii], ptrFile);
            if (error != ERR_OK) break ;
        }
        if (error != ERR_OK) break ;
        ptrFile->status = STAT_OK;

        ptrType->length = ( (uint) tmpL[ 0 ] << 8 ) + tmpL[ 1 ] ;
        ptrType->dim1    = tmpL[ 2 ];
        ptrType->dim2    = tmpL[ 3 ];
        ptrType->itemLen = tmpL[ 4 ];

        if (ptrFile->ident == IDENT_PC16_DAT || ptrFile->ident == IDENT_QT_DAT ) {
            error = FindFreqAndSyncFromWav (ptrFile) ;
            if (error != ERR_OK) break ;
            ptrFile->count = 0 ;
        }
        if (ptrFile->ident == IDENT_PC16_DAT)
            ptrFile->block_len = ptrType->length - 3 ;

        if (ptrFile->ident == IDENT_QT_DAT)
            error = ReadUsedatLenFromQTWav (order, ptrFile);

    } while (0) ;

    return (error);
}
/* Quick-Tape 4 transfer - only complete blocks */
/* ReadFillDataFromQtWav not needed anymore, new in RBsum */

int ReadNbFromBasEWav  (ulong  order,
                        char*  tmpC,
                        uint*  ptr_ii,
                        FileInfo*  ptrFile)
{
    schar  Exponent ;
    ulong  byte2 ;
    ulong  FPlen ;
     char  tmpF[20] ;
     uint  jj, nn, uExp, lastdigit = 0 ;
      int  error = ERR_OK;

    do {
        error = ReadByteSumFromWav (order, &byte2, ptrFile);
        if (error != ERR_OK) break ;
        ++ *ptr_ii ;

        if (byte2 != 0 ) FPlen = 20 ;
        else FPlen = 10 ;

        error = ReadByteSumFromWav (order, &byte2, ptrFile);
        if (error != ERR_OK) break ;
        ++ *ptr_ii ;
        Exponent = (uchar) byte2 ; /* Note: The exponent can have negative values. */
        if (Exponent < 0) uExp = - Exponent ;
        else uExp = Exponent ;

        for ( jj = 0 ; jj < FPlen; ++jj ) {
            error = ReadByteSumFromWav (order, &byte2, ptrFile);
            if (error != ERR_OK) break ;
            ++ *ptr_ii ;

            tmpF[jj] = (byte2 & 0xF0 ) >> 4  ;
            if ( tmpF[jj] > 0 ) lastdigit = jj ;
            ++jj;
            tmpF[jj] = (byte2 & 0x0F ) ;
            if ( tmpF[jj] > 0 ) lastdigit = jj ;
        }

        /*Convert number to ASCII*/
        nn = 0;
        if ( Exponent > -20 && Exponent < 0 ) {
            tmpC[nn++] = '0';
            tmpC[nn++] = '.';
            for (jj = 1 ; jj < uExp; ++jj ) {
                tmpC[nn++] = '0';
            }
            for (jj = 0 ; jj <= lastdigit; ++jj ) {
                tmpC[nn++] = tmpF [jj] | 0x30 ;
            }
            if (FPlen == 20)  tmpC[nn++] = '#';
        }
/* TODO (mr#3#): Whether a fixed point format or an exponential format is displayed also depends on
   the number of decimal places that are not zero.
   If the fixed point number becomes too long, it can be converted to double precision. */
        else if ( Exponent >= 0 && Exponent < 10 ) {
            if (lastdigit < uExp ) lastdigit = uExp ;
            for (jj = 0 ; jj <= lastdigit; ++jj ) {
                if ( jj == uExp +1 ) tmpC[nn++] = '.' ;
                tmpC[nn++] = tmpF [jj] | 0x30 ;
            }
            if (FPlen > 10)  tmpC[nn++] = '#' ;
        }
        else {
            tmpC[nn++] = tmpF [0] | 0x30 ;
            tmpC[nn++] = '.';
            for (jj = 1 ; jj <= lastdigit; ++jj ) {
                tmpC[nn++] = tmpF [jj] | 0x30 ;
            }
            if (FPlen > 10)  tmpC[nn++] = 'D' ;
            else tmpC[nn++] = 'E' ;
            if (Exponent > 0)  tmpC[nn++] = '+' ;
            else tmpC[nn++] = '-' ;
            tmpC[nn++] = uExp/10 | 0x30 ;
            tmpC[nn++] = uExp%10 | 0x30 ;
        }
        tmpC[nn] = 0 ;

    } while (0) ;

    return (error);
}


/* Search code point in external code space (loadable) */
int SearchCodepoint (ushort sVal)
{
    int kPos = -1 ;
    uint ii = 0 ;

    while ( ii < code_cnt ) {
        if (codepoint[ii] == sVal) break ;
        else ++ii;
    }
    if (ii < code_cnt) kPos = ii ;
    return ( kPos ) ;
}


/* Search value in external token keywords (loadable) */
int SearchToken (ushort sVal)
{
    int kPos = -1 ;
    uint ii = 0 ;

    while ( ii < key_cnt ) {
        if (keyval[ii] == sVal) break ;
        else ++ii;
    }
    if (ii < key_cnt) kPos = ii ;
    return ( kPos ) ;
}


int InsertStarsNeeded (char*  ptrText,
                       char*  ptrCode,
                       int* ptrMaxlen,
                       int* ptrTextlen)
{
    uchar lastChar ;
    int error = ERR_OK ;

    /* Insert multiply sign between old variable names only */
    if (strcmp (ptrCode, "Π") != 0 && (strlen(ptrCode) != 1 ||
               *ptrCode < 'A' || 'Z' < *ptrCode )) return (error) ;

    *ptrTextlen = (uint) strlen(ptrText) ;
    lastChar = ptrText [*ptrTextlen - 1] ;

    /* Token before must end with ' ' or special char from table */
    if (( 'A' <= lastChar && lastChar <= 'Z' ) ||
        ( '0' <= lastChar && lastChar <= '9' ) ||
                             lastChar == '.'    )
    {
            if (*ptrMaxlen <= 1) return (ERR_MEM) ;
            -- *ptrMaxlen ;
            strcat (ptrText, "*") ;
            error = STAT_FMT ;
            ++ *ptrTextlen ;
    }
    return (error) ;
}


int InsertSpaceNeeded (char*  ptrText,
                       char*  ptrCode,
                       int* ptrMaxlen,
                       int* ptrTextlen)
{
    uchar lastChar ;
    int error = ERR_OK ;

    if ( strlen(ptrCode) < 2 ) return (ERR_OK) ; // No Token, Char only
    if ( strlen(ptrCode) < 5 && (uchar) *ptrCode > 0xBF ) return (ERR_OK) ; // Utf8-Char only

    switch ( *ptrCode ) {
        case ' '    :   // Leading space exist for token in table
        case '['    :   // No spaces needed
        case '\\'   :
        case '<'    :   // OLD BAS
        case '>'    :
                        return (ERR_OK) ;
        default     :
                        break ;
    }
    /* Length of UTF8 characters is more than one byte */
    if ( strcmp ( ptrCode , "√" ) == 0) return (ERR_OK) ;
    if ( strcmp ( ptrCode , "Π" ) == 0) return (ERR_OK) ;
    if ( strcmp ( ptrCode , "¥" ) == 0) return (ERR_OK) ;
    if ( strcmp ( ptrCode , "€" ) == 0) return (ERR_OK) ;
    if ( strcmp ( ptrCode , "♠" ) == 0) return (ERR_OK) ;
    if ( strcmp ( ptrCode , "♥" ) == 0) return (ERR_OK) ;
    if ( strcmp ( ptrCode , "♦" ) == 0) return (ERR_OK) ;
    if ( strcmp ( ptrCode , "♣" ) == 0) return (ERR_OK) ;
    if ( strcmp ( ptrCode , "□" ) == 0) return (ERR_OK) ;
    if ( strcmp ( ptrCode , "■" ) == 0) return (ERR_OK) ;
    /* Japanese chars */
    if ( strcmp ( ptrCode , "円" ) == 0) return (ERR_OK) ;
    if ( strcmp ( ptrCode , "年" ) == 0) return (ERR_OK) ;
    if ( strcmp ( ptrCode , "月" ) == 0) return (ERR_OK) ;
    if ( strcmp ( ptrCode , "日" ) == 0) return (ERR_OK) ;
    if ( strcmp ( ptrCode , "時" ) == 0) return (ERR_OK) ;
    if ( strcmp ( ptrCode , "分" ) == 0) return (ERR_OK) ;
    if ( strcmp ( ptrCode , "秒" ) == 0) return (ERR_OK) ;
    if ( ( (uchar) ptrCode[0] == UTF8_SET) &&
         ( (uchar) ptrCode[1] == UTF8_KATAKANA1 ||
           (uchar) ptrCode[1] == UTF8_KATAKANA2 ) )
                                        return (ERR_OK);
    /* Kanji supported with codepoints from external file only */
    if ( (code_cnt > 0 || (pcMode & 8)>0 ) && (pcgrpId == GRP_EXT || pcgrpId == GRP_16 || pcgrpId == IDENT_PC1500) ) {
        if (  ( 0xE2 < (uchar) ptrCode[0] && (uchar) ptrCode[0] < 0xEA ) /* E3: grafics */
//         || ( 0xCD < (uchar) ptrCode[0] && (uchar) ptrCode[0] < 0xD2 ) /* greek, russian */
            ) return (ERR_OK);
    }

    *ptrTextlen = (uint) strlen(ptrText) ;
    if (*ptrTextlen==0) return (error);
    lastChar = ptrText [*ptrTextlen - 1] ;

    if (
         (spc_level >= 1 &&  'A' <= lastChar &&
                                    lastChar <= 'Z' ) ||
         (spc_level >= 1 && (lastChar == '$' ||
                             lastChar == '#'  )     ) ||

         (spc_level >= 2 &&  '0' <= lastChar &&
                                    lastChar <= '9' ) ||
         (spc_level >= 3 && (lastChar == '.' ||
                             lastChar == ')'  )     ) ||

         (spc_level >= 4 &&  lastChar == apostrophe ) ||
         (spc_level >= 5 && lastChar == ':'         ) || // SPC_LSTD

         (spc_level >= 6 && (lastChar == ';' ||
                             lastChar == '(' ||
                             lastChar == ','  )     ) ||

         (spc_level >= 7 && (lastChar == '+' ||
                             lastChar == '-' ||
                             lastChar == '*' ||
                             lastChar == '/' ||
                             lastChar == '='  )     ) ||

         (spc_level >= SPC_LMAX && lastChar != ' '  )
        ) {
//        if (('A' <= lastChar && lastChar <= 'Z') ||
//            ('0' <= lastChar && lastChar <= '9') ||
//                                lastChar == ')'  ||
//                                lastChar == '$'  ||
//                                lastChar == '#'  ||
//                                lastChar == apostrophe ||
//                                lastChar == '.'  ||
//                                lastChar == ':'    ) {
                if (*ptrMaxlen <= 1) return (ERR_MEM) ;
                -- *ptrMaxlen ;
                strcat (ptrText, " ") ;
                ++ *ptrTextlen ;
    }
    return (error) ;
}


int ConvertTokenToBas ( char*  ptrText,
                        char*  ptrCode)
{             /* global bool   DelSpcAfterCmd; uint CnvCmdLor, spc_level */
    char  tmpCode[cLTK] ;
    int   error = 0 ;
    int   maxlen, codelen, textlen = (uint) strlen (ptrText) ;
    maxlen = cLL -1 - textlen ;
    if (maxlen <= 0) return (ERR_MEM) ;

    if (textlen >0 &&
        *ptrCode == ' ' && ptrText[textlen-1] == ' ') ptrCode++ ; /* 1. space of cmd not needed*/
    if (*ptrCode == ' ' && spc_level < SPC_LSTD) ptrCode++ ; /* ignore 1. space of cmd */
    /* Insert spaces before tokens */
    error = InsertSpaceNeeded (ptrText, ptrCode, &maxlen, &textlen) ;
    if (error != ERR_OK) return (error) ;

    if ((CnvCmdLor & 2)>0 && *ptrCode >=' ') {
        strncpy(tmpCode, ptrCode, cLTK -1) ; /* copy to local memory */
        strlor( tmpCode) ;
        ptrCode = tmpCode ;
    }
    codelen = strlen(ptrCode)-1 ;
    if (codelen <2 || ptrCode[codelen] != ' ' ) codelen++ ; /* with last spc */
    else if ( DelSpcAfterRem && strcmp (ptrCode, REMstr)== 0 ) ;
    else if ( DelSpcAfterCmd ) ;
    else
        codelen++ ;
//    if ( !( DelSpcAfterCmd && codelen >1 && ptrCode[codelen] == ' ') ) codelen++ ; /* with last spc */
    if ((int) codelen > maxlen) error = ERR_MEM ;
    else
        strncat (ptrText, ptrCode, codelen) ;

    return (error) ;
}


int ConvertTokenToHexS ( char*  ptrText,
                         uchar  byte,
                         uchar  byte2,
                         ulong  graph  )
{
    char keyword_hex[cLTK] ; /* min 8 + 1 */
    int error;

    if (graph == UTF8_ASC || graph == UTF8_ESC) {
        keyword_hex[0] = (char) byte ; // transfer chars 1:1
        keyword_hex[1] = (char) byte2 ;
        keyword_hex[2] = 0 ;
    }
    else if  (graph == UTF8_ESCX) {
        strcpy (keyword_hex, "\\x") ; // "\x00\x00"
        sprintf(&keyword_hex[2], "%02X", (uchar) byte);
        strcat(keyword_hex, "\\x") ;
        sprintf(&keyword_hex[6], "%02X", (uchar) byte2);
    }
    else {
        strcpy (keyword_hex, "[") ; // "[00][00]"
        sprintf(&keyword_hex[1], "%02X", (uchar) byte);
        strcat(keyword_hex, "][") ;
        sprintf(&keyword_hex[5], "%02X", (uchar) byte2);
        strcat(keyword_hex, "]") ;
    }
    error = ConvertTokenToBas (ptrText, keyword_hex) ;
    return (error) ;
}


int ConvertKanjiSJIS1ToBas (char*  ptrText,
                            uchar  byte,
                            uchar  byte2,
                            ulong  graph,
                            bool  instring)   /* --utf8 parameter */
{
    ulong  word ;
    char   tmpC[cLTK];
    char*  ptrCode=tmpC ;
    int codepoint_pos = -1 ;
    int error ;

    tmpC[0] = 0 ;
    word = byte << 8 | byte2 ;

    if ( code_cnt > 0 && graph == 1 ) { /* Sharp code points of two byte for Kanji models only */
            codepoint_pos = SearchCodepoint(word) ;  /* code point from external file */
            if (codepoint_pos > -1) {
                    ptrCode = chrstring[codepoint_pos] ;
            }
    }
    if (codepoint_pos >= 0 && graph == 1) error = ConvertTokenToBas  (ptrText, ptrCode) ;
    else {
        if (graph == 1) { /* chars compatible with non-Kanji models without codepoints from file */
            if      (word == 0x83AE) sprintf(tmpC, "Π");
            else if (word == 0x83CE) sprintf(tmpC, "π");
            else if (word == 0x81A0) sprintf(tmpC, "□");
            else if (word == 0x81A1) sprintf(tmpC, "■");
            else if (word == 0x897E) sprintf(tmpC, "円");
            else if (word == 0x944E) sprintf(tmpC, "年");
            else if (word == 0x8C8E) sprintf(tmpC, "月");
            else if (word == 0x93FA) sprintf(tmpC, "日");
            else if (word == 0x8E9E) sprintf(tmpC, "時");
            else if (word == 0x95AA) sprintf(tmpC, "分");
            else if (word == 0x9562) sprintf(tmpC, "秒");
        }
        else if (graph == UTF8_ESC || graph == UTF8_ESCX) { /* Shift JIS-1 Kanji codes */
            if ((word == 0x83AE || strcmp (ptrCode, "Π") == 0) && instring) sprintf(tmpC, "\\PI");
            else if (word == 0x83AE || strcmp (ptrCode, "Π") == 0) sprintf(tmpC, "\\PI");
            else if (word == 0x81A0 || strcmp (ptrCode, "□") == 0) sprintf(tmpC, "\\INS");
            else if (word == 0x81A1 || strcmp (ptrCode, "■") == 0) sprintf(tmpC, "\\BX");
            else if (word == 0x897E || strcmp (ptrCode, "円") == 0) sprintf(tmpC, "\\YEN");
            else if (word == 0x944E || strcmp (ptrCode, "年") == 0) sprintf(tmpC, "\\YEAR");
            else if (word == 0x8C8E || strcmp (ptrCode, "月") == 0) sprintf(tmpC, "\\MONTH");
            else if (word == 0x93FA || strcmp (ptrCode, "日") == 0) sprintf(tmpC, "\\DAY");
            else if (word == 0x8E9E || strcmp (ptrCode, "時") == 0) sprintf(tmpC, "\\HOUR");
            else if (word == 0x95AA || strcmp (ptrCode, "分") == 0) sprintf(tmpC, "\\MINUTE");
            else if (word == 0x9562 || strcmp (ptrCode, "秒") == 0) sprintf(tmpC, "\\SECOND");
        }
        else if (graph != UTF8_ASC) {
            if      (word == 0x83AE || strcmp (ptrCode, "Π") == 0) sprintf(tmpC, "[PI]");
            else if (word == 0x83CE || strcmp (ptrCode, "π") == 0) sprintf(tmpC, "[pi]");
            else if (word == 0x81A0 || strcmp (ptrCode, "□") == 0) sprintf(tmpC, "[INS]");
            else if (word == 0x81A1 || strcmp (ptrCode, "■") == 0) sprintf(tmpC, "[FUL]");
            else if (word == 0x897E || strcmp (ptrCode, "円") == 0) sprintf(tmpC, "[YEN]");
            else if (word == 0x944E || strcmp (ptrCode, "年") == 0) sprintf(tmpC, "[YEAR]");
            else if (word == 0x8C8E || strcmp (ptrCode, "月") == 0) sprintf(tmpC, "[MONTH]");
            else if (word == 0x93FA || strcmp (ptrCode, "日") == 0) sprintf(tmpC, "[DAY]");
            else if (word == 0x8E9E || strcmp (ptrCode, "時") == 0) sprintf(tmpC, "[HOUR]");
            else if (word == 0x95AA || strcmp (ptrCode, "分") == 0) sprintf(tmpC, "[MINUTE]");
            else if (word == 0x9562 || strcmp (ptrCode, "秒") == 0) sprintf(tmpC, "[SECOND]");
        }
        if (strlen(tmpC)>0 ) error = ConvertTokenToBas  (ptrText, tmpC) ;
        else error = ConvertTokenToHexS (ptrText, byte, byte2, graph) ;
    }
//    else    error = ConvertTokenToBas  (ptrText, ptrCode) ;
    return (error) ;
}


int ConvertByteToBas (char*  ptrText,   /* Output line (BASIC) to which the command or character is to be appended*/
                      char*  ptrCode,   /* Command, Transcription, UTF8 or Ascii char, result of internal character table*/
                      ulong  word,      /* Read in word or byte pointing in the code table*/
                      ulong  graph,     /* --utf8 parameter */
                      ulong  CodeId,    /* BASIC version of the pocket computer */
                       bool  instring)  /* whether the word is in a string or a comment line */
{            /* global bool  DelSpcAfterCmd; uint CnvCmdLor, spc_level, keyword[], chrstring[] */
    ulong  tmp ;
    char  tmpC[cLTK], tmpCode[cLTK] ;
    char keyword_hex[5] ;
    char CodeModFul[] = "■",  CodeModCol[] = ": " ;
    int maxlen=0, textlen=0, codelen=0 ;
    int keyword_pos = -1, codepoint_pos = -1,
        error = 0 ;
    ulong byte = word & 0xFF ;


    if ( key_cnt > 0 && word < 0x100) { /* token of one byte, 2-byte done before */
        if ( (CodeId == IDENT_OLD_BAS && ( word > 0x6A || /* Japanese chars*/
                                          (word > 0x39 && word < 0x40) ||
                                          (word > 0x00 && word < 0x10)
                                         ) )  ||
            ((CodeId == IDENT_EXT_BAS || /* Japanese chars at 161 to 223 */
              CodeId == IDENT_NEW_BAS) && word > 0x7E && word < BAS_EXT_CODE) // changed 0xF5
                                                ) {
            keyword_pos = SearchToken(word) ; /* token from external file */
            if (keyword_pos > -1) {
                    ptrCode = keyword[keyword_pos] ;
            }
            else if ( KeysFromFileOnly ) {
                    strcpy (keyword_hex, "[") ; // "[00]"
                    sprintf(&keyword_hex[1], "%02X", (uchar) word);
                    strcat(keyword_hex, "]") ;
                    ptrCode = keyword_hex ;
            }
        }
    }
    if ( code_cnt > 0 || keyword_pos < 0) { /* Sharp code points of one byte or 2. page of NEW_BAS only */
            codepoint_pos = SearchCodepoint(word) ;  /* code point from external file */
            if (codepoint_pos > -1) {
                    ptrCode = chrstring[codepoint_pos] ;
            }
    }
    /* Modify result of E437 table for PC-1600 */
    if (codepoint_pos < 0 && CodeId == IDENT_PC16_BAS && word == 0x7F) ptrCode = CodeModFul ;

    textlen = (uint) strlen (ptrText) ;
    maxlen = cLL -1 - textlen ;
    if (maxlen <= 0) return (ERR_MEM) ;

    if (lineformat == LNFRM_SCOLS && strcmp (ptrCode, ":")==0 && !instring) {
        ptrCode = CodeModCol ;
        error = InsertSpaceNeeded (ptrText, ptrCode, &maxlen, &textlen) ;
    }
    /* Insert spaces before tokens or delete unwanted of cmd(code)string */
    else if (codepoint_pos < 0 &&
        !(instring && (CodeId == IDENT_E_BAS || CodeId == IDENT_PC16_BAS)) ) { /* 16/E_BAS-Str are without tokens*/
        if (textlen >0 &&
            strlen (ptrCode) > 2 && *ptrCode ==' ' && ptrText[textlen-1] == ' ') ptrCode++ ; /* 1. space of cmd not needed*/
        if (strlen (ptrCode) > 2 && *ptrCode ==' ' && spc_level < SPC_LSTD ) ptrCode++ ; /* ignore a space of cmd */

        error = InsertSpaceNeeded (ptrText, ptrCode, &maxlen, &textlen) ;
    }
    if (error != ERR_OK) return (error) ;

    /* Insert multiply stars between old variable names */
    if (graph == UTF8_ASC && CodeId == IDENT_OLD_BAS && !instring) {
        error = InsertStarsNeeded (ptrText, ptrCode, &maxlen, &textlen) ;
        if (error > ERR_OK) return (error) ;
    }

    strncpy(tmpCode, ptrCode, cLTK -1) ; /* copy to local memory */
    if (CnvCmdLor > 0 &&  *tmpCode >=' ' ) {
        if (((CnvCmdLor & 1)>0 && strlen (tmpCode)==1) ||
            ((CnvCmdLor & 2)>0 && strlen (tmpCode) >1 ) )
            strlor( tmpCode) ;
    }
    ptrCode = tmpCode ;
    codelen = strlen(ptrCode)-1 ;
    if (DelSpcAfterCmd && codelen >1 && ptrCode[codelen] == ' ') ptrCode[codelen] = 0 ; /* del spc */
    else codelen++ ;

    if ((int)strlen (ptrCode) > maxlen) error = ERR_MEM ;
    if (graph == 1) {
        strncat (ptrText, ptrCode, maxlen) ; /* UTF-8 char from token table */
    }
    else {
        tmp = (ulong) *ptrCode ; /* first char of new string is ASCII char, not empty or special char from table  */
        if (  tmp > 0x1F && tmp < 0x80 ) { /* Ascii 7 bit, Placeholder or Command */

            strncpy(tmpC, ptrCode,  cLTK -1) ;
            /* Write Sharp special characters 1:1 into the Ascii text */
            if (graph == UTF8_DOS ) {  /* Format for transfers to DOS-US */
                if ( (pcgrpId == GRP_E  && (pcMode &3) < 2 && byte > 0x7E)||  // No conversion
                     (pcgrpId == GRP_16 && (pcMode & 0xF) == 1 && byte > 0x7F) ) {
                    tmpC[0] = (char) byte ;       // worked only for E437, ASCII text and one-byte chars
                    tmpC[1] = 0 ;
                }
            }
            else if((graph == UTF8_ASC || graph == UTF8_ESC) && byte > 0x7E ) {  /* Format for later serial retransfer */

                if (CodeId == IDENT_E_BAS || CodeId == IDENT_EXT_BAS  || CodeId == IDENT_EXT_PAS ||
                    CodeId == IDENT_PC16_BAS || CodeId == IDENT_PC15_BAS ) { // No conversion
                    tmpC[0] = (char) byte ;       // transfer chars 1:1
                    tmpC[1] = 0 ;
                }
                else if (*ptrCode == '[' && ptrCode[ strlen(ptrCode)-1 ] == ']' ) { /* no token */
                    if (word < 0x100) {
                        tmpC[0] = (char) byte ;
                        tmpC[1] = 0 ;
                    }
                    else {
                        tmpC[0] = (char) (word >>8) ;
                        tmpC[1] = (char) byte ;
                        tmpC[2] = 0 ;
                    }
                }
            }
            else if (graph == UTF8_ESCX) {  /* For transfer to escape sequence format*/
                tmp = strlen(ptrCode)-1 ;
                if (tmp > 1 && *ptrCode == '[' && ptrCode[tmp] == ']') {
                    if ( tmp > 2 && ishex( ptrCode[1]) && ishex( ptrCode[2]) &&  ptrCode[3] ==']' ) {
                        tmpC[0] = '\\' ;
                        tmpC[1] = 'x' ;
                        strncpy(&tmpC[2], &ptrCode[1], tmp -1) ;
                        if (tmp == 7 && ptrCode[4] =='[' && ishex( ptrCode[5]) && ishex( ptrCode[6]) ) {
                            tmpC[4] = '\\' ;
                            tmpC[5] = 'x' ;
                            strncpy(&tmpC[6], &ptrCode[5], 2) ;
                        }
                    }
                    else { /* no byte, other placeholder */
                        tmpC[0] = '\\' ;
                        strncpy(&tmpC[1], &ptrCode[1], tmp -1) ;
                        if (strcmp (tmpC, "\\FUL") == 0) sprintf(tmpC, "\\BX");
                        if (strlen(tmpC)==2) strcat (tmpC, "X") ;
                    }
                }
            }
            if ((int)strlen (tmpC) > maxlen) error = ERR_MEM ;
            else strncat (ptrText, tmpC, maxlen) ;
        }
        else { /* for special Sharp chars in non-utf8 code table only */
            if (graph == UTF8_DOS) {  /* Format for transfers to DOS-US */
                if (strcmp (ptrCode, "√") == 0) sprintf(tmpC, "\xFB"); /* supported by DOS-Software */
                else if (strcmp (ptrCode, "Π") == 0) sprintf(tmpC, "\xE3");
                else if (strcmp (ptrCode, "¥") == 0) sprintf(tmpC, "\x9D");
                else if (strcmp (ptrCode, "€") == 0) sprintf(tmpC, "\x90");
                else if (strcmp (ptrCode, "□") == 0) sprintf(tmpC, "\xF0");
                else if (strcmp (ptrCode, "■") == 0) sprintf(tmpC, "\xDB");
                else if (strcmp (ptrCode, "♠") == 0) sprintf(tmpC, "\x06");
                else if (strcmp (ptrCode, "♥") == 0) sprintf(tmpC, "\x03");
                else if (strcmp (ptrCode, "♦") == 0) sprintf(tmpC, "\x04");
                else if (strcmp (ptrCode, "♣") == 0) sprintf(tmpC, "\x05");
                else if (strcmp (ptrCode, "円") == 0) sprintf(tmpC, "[YEN]");
                else if (strcmp (ptrCode, "年") == 0) sprintf(tmpC, "[YEAR]");
                else if (strcmp (ptrCode, "月") == 0) sprintf(tmpC, "[MONTH]");
                else if (strcmp (ptrCode, "日") == 0) sprintf(tmpC, "[DAY]");
                else if (strcmp (ptrCode, "時") == 0) sprintf(tmpC, "[HOUR]");
                else if (strcmp (ptrCode, "分") == 0) sprintf(tmpC, "[MINUTE]");
                else if (strcmp (ptrCode, "秒") == 0) sprintf(tmpC, "[SECOND]");
                else sprintf(tmpC, "[%02X]", (uchar) byte); /* unknown, should not in non-utf8 table */
            }
            else if (graph == UTF8_ASC) {  /* Format for later serial transfers or NEW_BAS, no return to OLD_BAS */
                if (strcmp (ptrCode, "√") == 0) sprintf(tmpC, "SQR "); /* supported by serial LOAD */
                else if (strcmp (ptrCode, "Π") == 0) sprintf(tmpC, "PI ");
                else if (strcmp (ptrCode, "¥") == 0) sprintf(tmpC, "\\");
                else if (strcmp (ptrCode, "€") == 0) sprintf(tmpC, "E");
                else if((strcmp (ptrCode, "円")== 0) /* These codes are different for the different models. */
                    ||  (strcmp (ptrCode, "年")== 0) /* Unchanged for serial transfer to the same model */
                    ||  (strcmp (ptrCode, "月")== 0)
                    ||  (strcmp (ptrCode, "日")== 0)
                    ||  (strcmp (ptrCode, "時")== 0)
                    ||  (strcmp (ptrCode, "分")== 0)
                    ||  (strcmp (ptrCode, "秒")== 0)
                    ||  (strcmp (ptrCode, "♠") == 0)
                    ||  (strcmp (ptrCode, "♥") == 0)
                    ||  (strcmp (ptrCode, "♦") == 0)
                    ||  (strcmp (ptrCode, "♣") == 0)
                    ||  (strcmp (ptrCode, "■") == 0)
                    ||  (strcmp (ptrCode, "□") == 0)
                                                    ) { /* only known codes, e.g. NOT 0x00 0x1A 0xFF */
                        tmpC[0] = byte ;
                        tmpC[1] = 0 ;
                }
                else sprintf(tmpC, "[%02X]", (uchar) byte); /* unknown, should not in non-utf8 table */
            }
/* for import scripts that require escape sequences for special chars */
            else if (graph == UTF8_ESC || graph == UTF8_ESCX) {
                if (strcmp (ptrCode, "√") == 0 && instring) sprintf(tmpC, "\\SQR");
                else if (strcmp (ptrCode, "√") == 0) sprintf(tmpC, "\\SQR");
                else if (strcmp (ptrCode, "Π") == 0 && instring) sprintf(tmpC, "\\PI");
                else if (strcmp (ptrCode, "Π") == 0) sprintf(tmpC, "\\PI");
                else if (strcmp (ptrCode, "¥") == 0) sprintf(tmpC, "\\");
                // NOTE (Mr#4#): Coding of old BASIC exponent char for PokecomGO clarified
                else if (strcmp (ptrCode, "€") == 0) sprintf(tmpC, "\\EX"); /* ? */
                else if (strcmp (ptrCode, "□") == 0) sprintf(tmpC, "\\INS");
                else if (strcmp (ptrCode, "■") == 0) sprintf(tmpC, "\\BX");
                else if (strcmp (ptrCode, "円") == 0) sprintf(tmpC, "\\YEN");
                else if (strcmp (ptrCode, "年") == 0) sprintf(tmpC, "\\YEAR");
                else if (strcmp (ptrCode, "月") == 0) sprintf(tmpC, "\\MONTH");
                else if (strcmp (ptrCode, "日") == 0) sprintf(tmpC, "\\DAY");
                else if (strcmp (ptrCode, "時") == 0) sprintf(tmpC, "\\HOUR");
                else if (strcmp (ptrCode, "分") == 0) sprintf(tmpC, "\\MINUTE");
                else if (strcmp (ptrCode, "秒") == 0) sprintf(tmpC, "\\SECOND");
                else if (strcmp (ptrCode, "♠") == 0) sprintf(tmpC, "\\SPADE");
                else if (strcmp (ptrCode, "♥") == 0) sprintf(tmpC, "\\HEART");
                else if (strcmp (ptrCode, "♦") == 0) sprintf(tmpC, "\\DIAMOND");
                else if (strcmp (ptrCode, "♣") == 0) sprintf(tmpC, "\\CLUB");
                else sprintf(tmpC, "\\x%02X", (uchar) byte); /* unknown, should not in non-utf8 table */
            }
            else {             /* Reversible between generations with Bas2img */
                if (strcmp (ptrCode, "√") == 0) sprintf(tmpC, "[SQR]");
                else if (strcmp (ptrCode, "Π") == 0) sprintf(tmpC, "[PI]");
                else if (strcmp (ptrCode, "π") == 0) sprintf(tmpC, "[pi]");
                else if (strcmp (ptrCode, "¥") == 0) sprintf(tmpC, "[Y]");
                else if (strcmp (ptrCode, "€") == 0) sprintf(tmpC, "[E]");
                else if (strcmp (ptrCode, "□") == 0) sprintf(tmpC, "[INS]");
                else if (strcmp (ptrCode, "■") == 0) sprintf(tmpC, "[FUL]");
                else if (strcmp (ptrCode, "円") == 0) sprintf(tmpC, "[YEN]");
                else if (strcmp (ptrCode, "年") == 0) sprintf(tmpC, "[YEAR]");
                else if (strcmp (ptrCode, "月") == 0) sprintf(tmpC, "[MONTH]");
                else if (strcmp (ptrCode, "日") == 0) sprintf(tmpC, "[DAY]");
                else if (strcmp (ptrCode, "時") == 0) sprintf(tmpC, "[HOUR]");
                else if (strcmp (ptrCode, "分") == 0) sprintf(tmpC, "[MINUTE]");
                else if (strcmp (ptrCode, "秒") == 0) sprintf(tmpC, "[SECOND]");
                else if (strcmp (ptrCode, "♠") == 0) sprintf(tmpC, "[SPADE]");
                else if (strcmp (ptrCode, "♥") == 0) sprintf(tmpC, "[HEART]");
                else if (strcmp (ptrCode, "♦") == 0) sprintf(tmpC, "[DIAMOND]");
                else if (strcmp (ptrCode, "♣") == 0) sprintf(tmpC, "[CLUB]");
                else sprintf(tmpC, "[%02X]", (uchar) byte); /* unknown, should not in non-utf8 table */
            }
            if ((int)strlen (tmpC) > maxlen) error = ERR_MEM ;
            else strncat (ptrText, tmpC, maxlen) ;
        }
    }
    return (error) ;
}


int ReadLineFromBasWav (ulong  order,
                        ulong  size,
                         long  imgbgn,
                        char*  ptrText,
                       ulong*  ptrLen,
                    FileInfo*  ptrFile)
{
 static ulong StoredByte = UNREAD ;
 static ulong LastLineNb = 0 ;
 static bool  LastLineEot = false ;
 static bool  WarnPC156M1 = true, ErrAddInfo = true ;

    uint   ii, lineNbPos = 0 ;
    ulong  byte ;
    ulong  byte2, byte3 ;
    ulong  sum, sumH ;
    ulong  length ;
    ulong  tmpL ;
    ulong  lineNb ;
    char   tmpC[cLNB] = "" ;     /* Buffer for line nb or full e500 number */
    int    maxlen;
    uint   REM_line_cnt = 0;
    bool   REM_line = false, REM_E_jmp = false, BeforeCR = false, BeforeCR2 = false ;
    bool   string_open = false ; /* bas2img: string_auf */
    bool   FN_old = false ;      /* for old basic expression conversion warning */
    int    keyword_pos ;
    long   position, lineNb_pos; /* temporary image file (for input) position */
    int    error = ERR_OK;

    (void) REM_line_cnt;

    ulong  ident = ptrFile->ident ; /* local, handle PC-1600 image inside PC-1500 device */

    char** CodePc1500_C = CodePc1500_1 ;
    char** CodeC = CodeExt ;
    char** CodeT = CodeExt2 ;
    if (ptrFile->utf8 == 1) {
        CodePc1500_C = CodePc1500_1J ;
        CodeC = CodeExtU ;
    }
    /* Switch code tab between extended new BASIC and PC-E series */
    if ( pcgrpId == GRP_E || pcgrpId == GRP_G ) {
        if (ptrFile->count == 0 && ptrFile->total > 0) return (ERR_EOT); // && pcgrpId == GRP_G

        if ( pcId == 220 ) CodeC = CodeE220 ; /* separate character code table without Japanese chars, use -o */
        else if (pcgrpId == GRP_G || (pcgrpId == GRP_E && (pcMode & 0x1C) >0) ) {
            if (ptrFile->utf8 == 1) CodeC = CodeG850U ; /* PC-G850 with Japanese chars */
            else CodeC = CodeG850 ;
        }
        else if ((pcMode &3) == 2) CodeC = CodeE220 ; /* PC-E500 series 2. table, for utf8 use code points file -o */

        else {
            if (ptrFile->utf8 == 1) CodeC = CodeE437U ; /* PC-E500 with URF-8 chars */
            else CodeC = CodeE437 ; /* PC-E500 series 1. (standard) table without utf-8 chars */
        }
        CodeT = CodeE2 ;
    }
    else if ( pcgrpId == GRP_16 || pcgrpId == IDENT_PC1500) { /* PC-1500 may be switched to PC-1600 */
        if (ptrFile->utf8 == 1) {
            if ( (pcMode & 8) >0) CodeC = CodePc1600_1J ;
            else if ( (pcMode & 4) >0) CodeC = CodePc1500_1J ;
            else CodeC = CodeE437U ;
        }
        else CodeC = CodeE437 ;
    }
    if ( pcgrpId == GRP_16 ) {
        if (ptrFile->count == 0 && ptrFile->total != 0 ) return (ERR_EOT);
    }

    if ( pcId == 1600 && ptrFile->ident == IDENT_PC15_BAS) ident = IDENT_PC16_BAS ; /* switch token tab and line model */
    else if (ptrFile->ident == IDENT_EXT_PAS) ident = IDENT_EXT_BAS ; /* for byte conversion */


    do {
        *ptrText = 0 ;
        length   = 0 ;

        if  ( ptrFile->ident == IDENT_QT_BAS && size <= ptrFile->total ) {
              ptrFile->status = STAT_EOT ; /* Quick-Tape STAT_EOT before end mark: no new sync  */
        }

        if ( (ptrFile->ident == IDENT_PC1211)  ||
             (ptrFile->ident == IDENT_OLD_BAS) ||
             (ptrFile->ident == IDENT_OLD_PAS) ) ptrFile->status = STAT_EOT ; /* possible EOF */

        ptrFile->check_end = false ; /* no end of file mark should follow the next byte instead a possible sum */
        if (LastLineEot) {
            /* seldom: first BAS_NEW_EOF mark was read at the end of last line instead of a checksum */
            byte = BAS_NEW_EOF ;
            CheckSum (order, &byte, ptrFile) ;
            LastLineEot = false ;
        }
        else if (StoredByte != UNREAD) { /* used for the byte read after a merge mark */
            byte = StoredByte ;
            StoredByte = UNREAD ;
        }
        else /* read first byte of line */
            error = ReadByteSumFromWav (order, &byte, ptrFile);
        if ( IMGc > 0 && ptrFile->total >= size - 3 && error == ERR_EOF ) {
            error = ERR_EOT ; /* workaround if size not exactly */
            if (Qcnt == 0) printf ("\nShort line at and of image ignored.\n" );
        }
        if (error > ERR_OK ) break ; /* OLD_BAS ends with ERR_NSYNC */

        if ( (ptrFile->ident == IDENT_PC1211)  ||
             (ptrFile->ident == IDENT_OLD_BAS) ||
             (ptrFile->ident == IDENT_OLD_PAS) ) {
            if (byte == BAS_OLD_EOF) {  /* End of OLD Basic File */
                /* Last checksum not exist */
                error = ERR_EOT;
            }
            else ptrFile->status = STAT_OK ;
        }
        if (error != ERR_OK ) break ;

        if (ptrFile->ident == IDENT_PC15_BAS || ptrFile->ident == IDENT_PC15QTBAS ||  ptrFile->ident == IDENT_QT_BAS ||
            ptrFile->ident == IDENT_PC16_BAS || ptrFile->ident == IDENT_PC16_IMG  ||  ptrFile->ident == IDENT_E_IMG  ||
            ptrFile->ident == IDENT_E_BAS) {
            if (byte == BAS_1500_EOF) { /* Is the End of Basic File or merged programs*/

                if ( (ptrFile->ident == IDENT_PC15_BAS || ptrFile->ident == IDENT_PC15QTBAS) &&
                      size - 1 < ptrFile->total ) {    /* EOF or MERGE?,-1 because of check for double EOF */
                  if (ptrFile->block_len > 0 && ptrFile->count % ptrFile->block_len > 0) {  /* Last checksum has not read by ReadByteSum before */
                                                                                            /* block_len == 0 when source is an image */
                    if ( ( (ptrFile->debug & 0x0040) > 0 ) && (Qcnt == 0) ) printf(" EOF:(");

                    ptrFile->writing = false ;
                    if (IMGc == 0) error = ReadByteTraceFromWav (order, &sumH, ptrFile);
                    else { /* simulate sum for img only */
                        sumH = ptrFile->sum>>8;
                        if ( ( (ptrFile->debug & 0x0040) > 0 ) && (Qcnt == 0) )
                                printf("%02X", (uint) sumH ) ;
                    }
                    if (error != ERR_OK ) {
                        if ((ptrFile->debug & IGN_ERR_SUM) == 0) error = ERR_SUM ;
                        else {
                            count_errors( ERR_SUM, ptrFile) ;
                            error = ERR_EOT ;
                        }
                        break ;
                    }
                    else error = ERR_EOT ;

                    if (sumH == BAS_1500_EOF && ptrFile->sum >>8 != BAS_1500_EOF ) {
                        /* Probably wav file was made from old image made by Bas2img, often found  */
                        /* Images with double EOF survive editing in the PC-1500 until the next NEW */
                        ptrFile->sum += sumH ;
                        ++ ptrFile->wrn_cnt ;
                        if (Qcnt == 0) printf ("\nDouble end of file found, maybe Bas2img used before\n" );

                            if (IMGc == 0) error = ReadByteFromWav (order, &sumH, ptrFile);
                            else sumH = ptrFile->sum>>8;
                            if (error != ERR_OK ) {
                                if ((ptrFile->debug & IGN_ERR_SUM) == 0) error = ERR_SUM ;
                                else {
                                    count_errors( ERR_SUM, ptrFile) ;
                                    error = ERR_EOT ;
                                }
                                break ;
                            }
                            else error = ERR_EOT ;
                            if ( ( (ptrFile->debug & 0x0040) > 0 ) && (Qcnt == 0) )
                                    printf("%02X", (uint) sumH ) ;
                    }

                    ptrFile->status = STAT_EOT ;

                    if (IMGc == 0) ReadByteFromWav (order, &sum, ptrFile);   /* Last checksum low byte */
                    else sum = ptrFile->sum & 0xFF; // simulate for img
                    sum += (sumH<<8) ;

                    /* Last checksum */
                    if (sum != ptrFile->sum) {
                        if ((ptrFile->debug & IGN_ERR_SUM) == 0 ) error = ERR_SUM ;
                        else count_errors( ERR_SUM, ptrFile) ;
                        if (Qcnt == 0) printf(" ERROR %d found: %ld\n", ERR_SUM, ptrFile->total ) ;
                    }
                    if ( ( (ptrFile->debug & 0x0040) > 0 ) && (Qcnt == 0) )
                        printf("%02X=%04X)", (uint) sum & 0xFF, (uint) ptrFile->sum);

                    if (error <= ERR_OK ) error = ERR_EOT ;
                  } // End if: Checksum of PC-1500 was not read before, last block was shorter than standard
                  else error = ERR_EOT ; // 2.00a, 2.09 beta 8a
                } // End if PC-1500 size

                if ( (ptrFile->ident == IDENT_QT_BAS) &&  size - 1 < ptrFile->total ) {
                    /* Q_BAS End - be done in RBsum */
                    if (error <= ERR_OK ) error = ERR_EOT ;
                }
                else if ( (ptrFile->ident != IDENT_E_BAS) &&
                           ptrFile->count != 0 ) { /* E/G/16 one program data block only, 0 = end */
                    /* In IDENT_15_BAS, IDENT_PC16_BAS between merged programs is an EOF mark */
                    LastLineNb = 0 ;
                    if (ptrFile->type == TYPE_IMG ) {
                        if (strlen (ptrText) < (cLL - 1)) ptrText[length++] = (char) byte ;
                        else error = ERR_MEM ;
                    }
                    else {
                        tmpL = MERGE_MARK ;
                        if (!linenbr_del && linewidth > 5 )
                             sprintf(ptrText, "%*ld", (int) linewidth, tmpL);
                        else if (!linenbr_del)
                             sprintf(ptrText, "%ld", tmpL);
                        if (strlen (ptrText) < (cLL - 4)) {
                            if (lineformat>3) (void) strcat (ptrText, " :");
                            else if (lineformat>1) (void) strcat (ptrText, ":"); else if (lineformat>0) (void) strcat (ptrText, " ");
                            (void) strncat (ptrText, Eol, 2) ;
                        }
                        else error = ERR_MEM ;
                        if ( ( (ptrFile->debug & 0x0080) > 0 ) && (Qcnt == 0) ) printf(" %s", ptrText);
                    }
                    *ptrLen  = length ;
                    break;  /* next line */
                }
                else error = ERR_EOT ; /* EOT mark at end of transmission block with standard length */
                break;
            }  // End if: END OF PC-1500, 1600, E/G Basic File MARK
        } // End if: IDENT_PC15_BAS, IDENT_PC16_BAS, IDENT_E_BAS

        error = ReadByteSumFromWav (order, &byte2, ptrFile);
        if (error != ERR_OK) break ;

        /* calculate the line number */
        if ( (ptrFile->ident == IDENT_PC1211)  ||
             (ptrFile->ident == IDENT_OLD_BAS) ||
             (ptrFile->ident == IDENT_OLD_PAS) ) {
            if (byte < 224) {
                error = count_errors( ERR_LINE, ptrFile) ;
                if (Qcnt==0) printf(" Invalid line number format at: %ld\n", ptrFile->total-1 );
            }
            tmpL = 100 * (byte & 0x0F) ;
            tmpL = tmpL + (10 * (byte2 >> 4)) + (byte2 & 0x0F) ;
        }
        else { /* NEW and EXT BAS */
            tmpL = byte ;
            tmpL = (tmpL << 8) + byte2 ;
            if (tmpL == BAS_NEW_EOFFF) {  /* End of New, Ext Basic File */
                error = ERR_EOT;
                ptrFile->status = STAT_EOT ;
                /* Last checksum with sum_before, because 2. EOF byte
                   has not to include in the checksum */
                if (IMGc == 0) ReadByteFromWav (ORDER_STD, &sum, ptrFile); /* always error because end of sync */
                else sum = ptrFile->sum_before ; // simulate for img
                if (sum != ptrFile->sum_before) {
                    if ((ptrFile->debug & IGN_ERR_SUM) == 0 ) error = ERR_SUM ;
                    else count_errors( ERR_SUM, ptrFile) ;
                    if (Qcnt == 0) printf(" ERROR %d at EOF: %ld\n", ERR_SUM, ptrFile->total ) ;
                }
                if ( ( (ptrFile->debug & 0x0040) > 0 ) && (Qcnt == 0) )
                    printf(" EOF:(%02X=%02X)", (uchar) sum, (uchar) ptrFile->sum_before);
                break;
            }
            else if (byte == BAS_NEW_EOF) { /* merged program blocks */
                StoredByte = byte2 ;
                LastLineNb = 0 ;
                if (ptrFile->type == TYPE_IMG ) {
                    if (strlen (ptrText) < (cLL - 1)) ptrText[length++] = (char) byte ;
                    else error = ERR_MEM ;
                }
                else {
                    tmpL = MERGE_MARK ;
                    if (!linenbr_del && linewidth > 5 )
                         sprintf(ptrText, "%*ld", (int) linewidth, tmpL);
                    else if (!linenbr_del)
                         sprintf(ptrText, "%ld", tmpL);
                    if (strlen (ptrText) < (cLL - 4)) {
                            if (lineformat>3) (void) strcat (ptrText, " :");
                            else if (lineformat>1) (void) strcat (ptrText, ":"); else if (lineformat>0) (void) strcat (ptrText, " ");
                            (void) strncat (ptrText, Eol, 2) ;
                    }
                    else error = ERR_MEM ;
                    if ( ( (ptrFile->debug & 0x0080) > 0 ) && (Qcnt == 0) ) printf(" %s", ptrText);
                }
                *ptrLen  = length ;
                break; /* next line */
            }
        } // End if: Not old bas

        /* Write the line number */
        if (ptrFile->type == TYPE_IMG) {
            ptrText[length++] = (char) byte ;
            ptrText[length++] = (char) byte2 ;
        }
        else {
            if (linenbr_del) {
                if (linewidth > 0)
                    sprintf(tmpC, "%*s", (int) linewidth, " ");
            }
            else {
                if (linewidth > 0)
                    sprintf(tmpC, "%*ld", (int) linewidth, tmpL);
                else
                    sprintf(tmpC, "%ld", tmpL);
            }
            if (strlen (tmpC) < (cLNB - 3)) {
                    if (lineformat>3) (void) strcat (tmpC, " : "); /* LNFRM_SCOLS */
                    else if (lineformat>2) (void) strcat (tmpC, ": ");
                    else (void) strcat (tmpC, " ");  /* SPC is later replaced for lineformat ==2, deleted for ==00 */
            }
            else error = ERR_MEM ;
            strncat (ptrText, tmpC, cLL-1-strlen(ptrText)) ;
            lineNbPos = strlen(ptrText) ;
            if (error != ERR_OK) break ;
        }
        if (tmpL <= LastLineNb ) {
            if (Qcnt == 0) printf ("Wrong line number sequence found: %lu: >= %lu:\n", LastLineNb, tmpL);
            error = count_errors( ERR_LINE, ptrFile );
            if (error != ERR_OK) break ;
        }
        LastLineNb = tmpL ;

        /* Read the line */
        if ( (ptrFile->ident == IDENT_PC1211)  ||
             (ptrFile->ident == IDENT_OLD_BAS) ||
             (ptrFile->ident == IDENT_OLD_PAS) ) {
            ii = 0 ;
            do {
                error = ReadByteSumFromWav (order, &byte, ptrFile);
                if (error != ERR_OK) break ;
                ++ii ;

                if (ptrFile->type == TYPE_IMG) {
                    ptrText[length++] = (char) byte ;
                }
                else {
                    if (strcmp (CodeOld[byte], REMstr)== 0) REM_line = true ;
                    if (byte == apostrophe && !(REM_line)) string_open = !string_open ;

                    if (ii == 1 && (ptrFile->debug & DEL_APST)>0 && byte == apostrophe ) {
                        error = ReadByteSumFromWav (order, &byte, ptrFile); /* delete it, for asm sources */
                        if (error != ERR_OK) break ;
                        ++ii ;
                    }
                    if ( byte == 0x1A  || ( 0x9F < byte && byte < 0xB0 ) ||
                        ( 0x7C < byte && byte < 0x80 ) || byte == 0x87 ) FN_old = true ; /* token of a function */
                    else if ( byte > 0x6A || byte == 0x1D || string_open ) FN_old = false ;

                    if (byte > 0) {
                        if (string_open && (pcMode & 4)>0)
                            error = ConvertByteToBas (ptrText, CodeOldSJ[byte], byte, ptrFile->utf8,
                                                      IDENT_OLD_BAS, REM_line || string_open) ;
                        else
                            error = ConvertByteToBas (ptrText, CodeOld[byte], byte, ptrFile->utf8,
                                                      IDENT_OLD_BAS, REM_line || string_open) ;
                        if (error == STAT_FMT) {
                            if ( FN_old == true ) {
                                ++ ptrFile->wrn_cnt ;
                                if (Qcnt == 0)
                                    printf ("* Star added in %lu: before %c at %lu. Check for function brackets manually!\n",
                                            LastLineNb, CodeOld[byte][0], (ulong) strlen (ptrText)-1 ); // PI -> x
                            }
                            error = ERR_OK ;
                        }
                        if (error != ERR_OK) break ;
                    }
                }
            } while (byte != 0) ;
            if (error != ERR_OK) break ;
            if (ii > ll_Img ) {
                printf ("ERROR: Image line %lu with %i bytes is not editable, end at byte: %lu\n", LastLineNb, (int) ii, ptrFile->total) ;
                error = count_errors( ERR_MEM, ptrFile) ;
                if (error != ERR_OK) break ;
            }
        }  // End if: Body Old bas
        else {
            /* Read the Line length */
            error = ReadByteSumFromWav (order, &tmpL, ptrFile);
            if (error != ERR_OK) break ;
            if (tmpL > ll_Img ) {
                printf ("NOTE: Image line %lu with %lu bytes is to long, begin at byte: %lu\n", LastLineNb, tmpL, ptrFile->total) ;
                if ( tmpL > ll_Img + 8) error = count_errors( ERR_MEM, ptrFile) ;
                else ++ ptrFile->wrn_cnt ;
                if (error != ERR_OK) break ;
            }

            if (ptrFile->type == TYPE_IMG)
                ptrText[length++] = (char) tmpL ;

            /* read first byte of the line body */
            error = ReadByteSumFromWav (order, &byte, ptrFile);
            if (error != ERR_OK) break ;

            /* line body processing */
            ii = 1;
            if (((ptrFile->debug & DEL_APST)>0 && byte == apostrophe ) ||
                ((ptrFile->debug & DEL_REMC)>0 && byte>0 && byte == REMidC) ) { /* delete it, for asm/c sources */
                    error = ReadByteSumFromWav (order, &byte, ptrFile);
                    if (error != ERR_OK) break ;
                    ++ii ;
            }
            // NOTE (mr#2#): Test use the line length for check of end of line mark (half token @ EoL etc.)
            for ( /* ii = ii */ ; ii < tmpL ; ++ii ) {
                BeforeCR  = ii + 1 >= tmpL ;
                BeforeCR2 = ii + 2 >= tmpL ;
                /* after errors this check can help to stay synchronous in line, but only if the nibbles in right order */
                if ((ptrFile->type != TYPE_IMG || pcgrpId == IDENT_PC1500 || pcgrpId == GRP_NEW)
                    && byte == 0x0D) {    /* Note: Binary coded line numbers etc. may contain 0D in line
                                             and should be processed after BAS_EXT_LINE_NB etc. */
                    printf ("Unexpected 'End of Line' %lu at byte: %lu\n", LastLineNb, ptrFile->total) ;
                    error = count_errors( ERR_MEM, ptrFile) ;
                    if ((ptrFile->debug & CR_DEF_EOL)>0 || /*Assumption that byte(s) has been lost*/
                         error != ERR_OK) break; //if (pcgrpId != GRP_E || error != ERR_OK) break;
                }

                if (ptrFile->type == TYPE_IMG) {
                    ptrText[length++] = (char) byte ;
                }
                else { /* BAS text, not image */
                    if (REM_line == true) ++REM_line_cnt; /* Switching the token table not for the REM token itself */
                    /* for check of external keyword file, PC-1500 ... */
                    keyword_pos = -1 ;

                    switch (ident) { /* masked identity because PC-1600 can save in Mode of PC-1500 */
                    case IDENT_NEW_BAS :
                    case IDENT_NEW_PAS :

                        if (!string_open && strcmp (CodeNew[byte], REMstr)== 0) REM_line = true ;
                        if (byte == apostrophe && !(REM_line)) string_open = !string_open ;

                        if (pcId == 1421 || pcId == 1401 || pcId == 1402 )
                            error = ConvertByteToBas (ptrText, CodeNew1421[byte], byte, ptrFile->utf8,
                                                      IDENT_NEW_BAS, REM_line || string_open) ;

                        else if (byte == BAS_NEW_CODE && !BeforeCR ) { /* 2-byte token, PC-1403 and newer */
                            error = ReadByteSumFromWav (order, &byte2, ptrFile);
                            if (error != ERR_OK) break ;
                            ++ii ;
                            if (key_cnt > 0) keyword_pos = SearchToken(byte << 8 | byte2) ;
                            if (keyword_pos > -1) {
                                error = ConvertTokenToBas (ptrText, keyword[keyword_pos]) ;
                            }
                            else if ( KeysFromFileOnly ) {
                                error = ConvertTokenToHexS (ptrText, byte, byte2, ptrFile->utf8) ;
                            }
                            else error = ConvertTokenToBas (ptrText, CodeNew2[byte2]) ;
                        }
                        else if (byte == BAS_EXT_CODE && !BeforeCR &&
                                ((pcId >= 1260 && pcId <  1401)||             /* for 1401 etc. 0xFE is used other  */
                                  pcId == 1403 || pcId == 1425 ||
                                  pcId >= 1440 ||
                                 (pcMode &4)>0  )) { /* PC-126X and jap. version: 2-byte Japanese chars at 161-248 */
                            error = ReadByteSumFromWav (order, &byte2, ptrFile);
                            if (error != ERR_OK) break ;
                            ++ii ;
                            if (key_cnt > 0) keyword_pos = SearchToken(byte << 8 | byte2) ;
                            if (keyword_pos > -1) {
                                error = ConvertTokenToBas (ptrText, keyword[keyword_pos]) ;
                            }
                            // TODO (mr#2#): Check if loaded code points needed with other -u parameters
                            else if (ptrFile->utf8 == 1)
                                error = ConvertByteToBas (ptrText, CodeNewJ[byte2], byte << 8 | byte2, ptrFile->utf8,
                                                          IDENT_NEW_BAS, REM_line || string_open) ;
                            else error = ConvertTokenToHexS (ptrText, byte, byte2, ptrFile->utf8) ;
                        }
                        else {                  /* do not detokenise Japanese characters within REM line */
                            if ( string_open ) {   //( (pcMode &4)>0 && (string_open || REM_line_cnt>0) ) {
                                error = ConvertByteToBas (ptrText, CodeNewS[byte], byte, ptrFile->utf8,
                                                          IDENT_NEW_BAS, REM_line || string_open) ;
                            }
                            else /* also for REM lines */
                                error = ConvertByteToBas (ptrText, CodeNew[byte], byte, ptrFile->utf8,
                                                          IDENT_NEW_BAS, REM_line || string_open) ;
                        }
                        break ;

                    case IDENT_E_IMG :
                    case IDENT_E_BAS :

                        if ( (pcgrpId == GRP_E || pcgrpId == GRP_G) && byte == REMidC && !string_open && !REM_line) {
                            if (ptrText[strlen (ptrText)-1] == ':') /* Remove ':' before the REM-Character */
                                ptrText[strlen (ptrText)-1] =  0  ;
                            REM_line = true ;
                            error = ERR_OK ;
                            if ((ptrFile->debug & DEL_REMC)>0 && ii<3 ) {
                                error = ReadByteSumFromWav (order, &byte, ptrFile);
                                if (error != ERR_OK) break ;
                                ++ii ;
                                BeforeCR = BeforeCR2;
                                BeforeCR2 = ii + 2 >= tmpL ;
                            }
                        }

                    case IDENT_EXT_BAS :
                    case IDENT_EXT_PAS :
                                                                            /* SP but DP length not checked */
                       if (byte == BAS_E_NB && !(string_open || REM_line) && ii+7 < tmpL) {   /* !BeforeCR7 */
                            /* Convert a binary fixed numeric value to ASCII */
                            error = ReadNbFromBasEWav  (order, tmpC, &ii, ptrFile) ;
                            if (error != ERR_OK) break ;

                            maxlen = cLL -1 - (uint) strlen (ptrText) ;
                            if ((int) strlen (tmpC) > maxlen ) error = ERR_MEM ;
                            else strncat (ptrText, tmpC, maxlen) ;

                        }
                        else if (byte == BAS_E_JMP && !(string_open || REM_E_jmp || BeforeCR)) {
                            if (REM_line) REM_E_jmp = true ; /* Remove once after REMid, other may be chars */
                            /* Number of bytes to skip see Tech.Ref. PC-E500 P.88 */
                            error = ReadByteSumFromWav (order, &byte2, ptrFile);
                            if (error != ERR_OK) break ;
                            ++ii ;
                        }
                        else if (byte == BAS_E_LBL && !(string_open || REM_line || BeforeCR2)) {
                            /* Intermediate code for a long jump */
                            error = ReadByteSumFromWav (order, &byte, ptrFile);
                            if (error != ERR_OK) break ;
                            ++ii ;

                            error = ReadByteSumFromWav (order, &byte2, ptrFile);
                            if (error != ERR_OK) break ;
                            ++ii ;
                        }
                        else if (byte == 0 && pcgrpId == GRP_E && !(string_open || REM_line || BeforeCR2)){
                            /* Intermediate raw code for a absolute jump */
                            error = ReadByteSumFromWav (order, &byte2, ptrFile);
                            if (error != ERR_OK) break ;
                            ++ii ;

                            error = ReadByteSumFromWav (order, &byte3, ptrFile);
                            if (error != ERR_OK) break ;
                            ++ii ;

                            if (IMGc == 0) {
                                if (Qcnt == 0 && ErrAddInfo == true) {
                                        printf ("\nWarning: 1st create complete image --type=IMG, 2nd from this --IMG the BAS file\n");
                                        ErrAddInfo = false;
                                }
                                if ((ptrFile->debug & 0x0040)>0) printf("\n"); else printf(" ");
                                printf ("Run replaced nb in line %lu with jump to byte %lu from %lu, Write 1st-tIMG\n",
                                        LastLineNb , (byte3<<8) + byte2 - FILE_HEAD_E_LEN, ptrFile->total ) ;
                                /* points to the address of a line number relative to the start of file header (FB) */
                                ptrFile->err_exit = ERR_LINE ;
                                error = count_errors( ERR_LINE, ptrFile) ;
                                sprintf(tmpC, "[%02X][%02X][%02X]", (uchar) byte, (uchar) byte2, (uchar) byte3 );
                            }
                            else {

                                lineNb_pos  =  (ulong) (byte3<<8) + byte2 ;
                                lineNb_pos -=  FILE_HEAD_E_LEN ;
                                if (imgbgn > 0) lineNb_pos += imgbgn ;

                                if (lineNb_pos < 0 || lineNb_pos + 3 > (long) ptrFile->endSamples ) {

                                    printf ("\nBASIC line %lu, illegal jump from image byte %lu to %lu.\n",
                                        LastLineNb , ptrFile->total, (byte3<<8) + byte2 - FILE_HEAD_E_LEN ) ;
                                    ptrFile->err_exit = ERR_LINE ;
                                    error = count_errors( ERR_LINE, ptrFile) ;
                                    sprintf(tmpC, "[%02X][%02X][%02X]", (uchar) byte, (uchar) byte2, (uchar) byte3 );
                                }
                                else{
                                    position = stell( ptrFile ) ; /*save position in source file */
                                    if (position <= 0) {
                                        printf ("\n%s:rLine - Can't ftell the wav file\n", argP) ;
                                        return ( ERR_FILE ) ;
                                    }
                                    /* jump to the position of the line number */
                                    error = sseek (ptrFile, lineNb_pos, SEEK_SET) ;
                                    if (error != ERR_OK) {
                                        printf ("\n%s:rLine - Can't seek to the branch line number: %ld\n", argP, lineNb_pos) ;
                                        error = ERR_FILE ;
                                        break ;
                                    }
                                    error = ReadByteFromWav (order, &byte, ptrFile);
                                    if (error != ERR_OK) break ;

                                    error = ReadByteFromWav (order, &byte2, ptrFile);
                                    if (error != ERR_OK) break ;

                                    /*rewind to position before last byte read */
                                    error = sseek (ptrFile, position, SEEK_SET) ;
                                    if (error != ERR_OK) {
                                        printf ("\n%s:rLine - Can't seek the file: %ld\n", argP, position) ;
                                        error = ERR_FILE ;
                                        break ;
                                    }
                                    lineNb = byte ;
                                    lineNb = (lineNb << 8) + byte2 ;
                                    sprintf(tmpC, "%u", (ushort) lineNb);
                                }
                            }
                            maxlen = cLL -1 - (uint) strlen (ptrText) ;
                            if ((int) strlen (tmpC) > maxlen ) error = ERR_MEM ;
                            else strncat (ptrText, tmpC, maxlen) ;
                        } // end if absolute jump

                        else if (byte == BAS_EXT_LINE_NB && !(string_open || REM_line || BeforeCR2)) {
                            /* fixed line numbers in intermediate code (line body) */
                            error = ReadByteSumFromWav (order, &byte, ptrFile);
                            if (error != ERR_OK) break ;
                            ++ii ;

                            error = ReadByteSumFromWav (order, &byte2, ptrFile);
                            if (error != ERR_OK) break ;
                            ++ii ;

                            lineNb = byte ;
                            lineNb = (lineNb << 8) + byte2 ;
                            sprintf(tmpC, "%u", (ushort) lineNb); // old "%ld " space removed

                            maxlen = cLL -1 - (uint) strlen (ptrText) ;
                            if ((int) strlen (tmpC) > maxlen ) error = ERR_MEM ;
                            else strncat (ptrText, tmpC, maxlen) ;
                        }
                        else if ( byte == BAS_EXT_CODE && !string_open && !BeforeCR &&  /* Is a token */
                                    !(REM_line && ident == IDENT_E_BAS) ) {     /* E/G not tokens after REM but in EXT_BAS */
                            error = ReadByteSumFromWav (order, &byte2, ptrFile);
                            if (error != ERR_OK) break ;
                            ++ii ;

                            if ( (pcgrpId == GRP_E || pcgrpId == GRP_G) && byte2 == ELSEid_E2 && !string_open && !REM_line) {
                                if (ptrText[strlen (ptrText)-1] == ':') /* Remove ':' before ELSE of G/E series */
                                    ptrText[strlen (ptrText)-1] =  0  ;
                            }

                            if (strcmp (CodeT[byte2], REMstr)== 0) REM_line = true ;
                            if ( !string_open && ( pcgrpId == GRP_E || pcgrpId == GRP_G ) && byte2 == REMidC)
                                                                   REM_line = true ;

                            if (key_cnt > 0) keyword_pos = SearchToken(byte << 8 | byte2) ;
                            if (keyword_pos > -1) {
                                error = ConvertTokenToBas (ptrText, keyword[keyword_pos]) ;
                            }
                            else if ( KeysFromFileOnly ) {
                                error = ConvertTokenToHexS (ptrText, byte, byte2, ptrFile->utf8) ;
                            }
                            else {
//                                if (ident == IDENT_E_BAS)
                                error = ConvertTokenToBas (ptrText, CodeT[byte2]) ;
//                                else error = ConvertByteToBas (ptrText, CodeT[byte2], byte << 8 | byte2, ptrFile->utf8,
//                                                                IDENT_EXT_BAS, REM_line || string_open) ;
                            }
                        }
                        else if ( ( KANJI_CODE_MIN <= byte && byte <= Kanji_Code_Max) && !BeforeCR &&  /* S JIS-1 part 1 */
                                  ( ident == IDENT_EXT_BAS ||                       /* PC-1360K / 1365K */
                                   (ident == IDENT_E_BAS && (pcMode & 8) >0) ) ) {  /* PC-E500K (PC-E500J + Kanji driver) */
                            error = ReadByteSumFromWav (order, &byte2, ptrFile);
                            if (error != ERR_OK) break ;
                            ++ii ;

                            error = ConvertKanjiSJIS1ToBas (ptrText, byte, byte2, ptrFile->utf8,
                                                            REM_line || string_open) ;
                        }
                        else if ( ( KANJI_CODE_MIN2 <= byte && byte <= KANJI_CODE_MAX2) && !BeforeCR &&  /* S JIS-1 part 2 */
                                  ( ident == IDENT_E_BAS && (pcMode & 0x10) >0 ) ) {  /* PC-E500K (PC-E500J + Kanji driver) */
                            error = ReadByteSumFromWav (order, &byte2, ptrFile);
                            if (error != ERR_OK) break ;
                            ++ii ;

                            error = ConvertKanjiSJIS1ToBas (ptrText, byte, byte2, ptrFile->utf8,
                                                            REM_line || string_open) ;
                        }
                        else {
                            if (byte == apostrophe && !(REM_line)) string_open = !string_open ;
                            error = ConvertByteToBas (ptrText, CodeC[byte], byte, ptrFile->utf8,
                                                                ident, REM_line || string_open) ;
                        }
                        break ;

                    case IDENT_PC15_BAS :
                    case IDENT_PC15QTBAS :
                    case IDENT_QT_BAS :

                        if ( byte < 0xE0 || (byte < 0xE6 && (pcMode & 0xC)>0 && string_open) ||
                             byte > 0xF1 || BeforeCR ) {

                            if ( byte == 0xF2 || byte == BAS_EXT_LINE_NB ) { /* PC-1600 with CE-150 or bin. code detected */
                                if ((Qcnt == 0 || ptrFile->debug > 0) && WarnPC156M1 ){
                                    printf ("\n%s: Token of PC-1600 found in the wav format of PC-1500.\n", argP );
                                    printf ("         For PC-1600 set option --pc=1600M1 and start again!\n" );
                                    printf ("         If binary code is included in lines use --type=imB\n" );
                                }
                                WarnPC156M1 = false ;
                                ++ ptrFile->wrn_cnt ;
                                pcId = 1601 ;
                                pcMode |= 1 ;
                                ident = IDENT_PC16_BAS ;
                            }
                            else {
                                if (byte == apostrophe && !(REM_line)) string_open = !string_open ;
                                error = ConvertByteToBas (ptrText, CodePc1500_C[byte], byte, ptrFile->utf8,
                                                        IDENT_PC1500, REM_line || string_open) ;
                            }
                        }
                        else {
                            ++ii ;
                            error = ReadByteSumFromWav (order, &byte2, ptrFile);
                            if (error != ERR_OK) break ;

                                if (key_cnt > 0) keyword_pos = SearchToken(byte << 8 | byte2) ;
                                if (keyword_pos > -1) {
                                    error = ConvertTokenToBas (ptrText, keyword[keyword_pos]) ;
                                }
                                else if ( KeysFromFileOnly ||
                                          byte == 0xE0     ||
                                          byte == 0xE4     ||
                                          byte == 0xE5     ||
                                         (byte >  0xE8 && byte < 0xF0) ) {

                                    error = ConvertTokenToHexS (ptrText, byte, byte2, ptrFile->utf8) ;
                                }
                                else
                                    switch (byte) {
                                    case 0xE1 :
                                        error = ConvertTokenToBas (ptrText, CodePc1500_E1[byte2]) ;
                                        break ;

                                    case 0xE2 :
                                        error = ConvertTokenToBas (ptrText, CodePc1500_E2[byte2]) ;
                                        break ;

                                    case 0xE3 :
                                        if ( (ptrFile->debug & BMC_TOKEN) > 0 ) {
                                            error = ConvertTokenToBas (ptrText, CodePc1500_E3b[byte2]) ;
                                        }
                                        else {
                                            error = ConvertTokenToBas (ptrText, CodePc1500_E3[byte2]) ;
                                        }
                                        break ;

                                    case 0xE6 :
                                        error = ConvertTokenToBas (ptrText, CodePc1500_E6[byte2]) ;
                                        break ;

                                    case 0xE7 :
                                        error = ConvertTokenToBas (ptrText, CodePc1500_E7[byte2]) ;
                                        break ;

                                    case 0xE8 :
                                        error = ConvertTokenToBas (ptrText, CodePc1500_E8[byte2]) ;
                                        break ;

                                    case 0xF0 :
                                        error = ConvertTokenToBas (ptrText, CodePc1500_F0[byte2]) ;
                                        break ;

                                    case 0xF1 :
                                        if (strcmp (CodePc1500_F1[byte2], REMstr)== 0) REM_line = true ;
                                        error = ConvertTokenToBas (ptrText, CodePc1500_F1[byte2]) ;
                                        break ;

                                    default :
                                        printf ("%s: Internal error, unknown token table [%02X] for PC-1500!\n", argP, (uint) byte);
                                    }   // End if: is a token with table
                        }   // End if: is a token
                        if (ident != IDENT_PC16_BAS)
                            break ;
                     /* else switch to PC-16_BAS */

                    case IDENT_PC16_IMG :
                    case IDENT_PC16_BAS :

                        if ( byte == REMidC && !string_open && !REM_line) REM_line = true ;

// TODO (mr#3#): Move 1 byte detokenisation to the end of if-then-elseif construction
                        if (BeforeCR || (
                            ( (pcMode & 0x8) ==0 || byte < KANJI_CODE_MIN || byte > Kanji_Code_Max) &&
                            (REM_line || string_open ||                     /* in strings */
                            (byte == BAS_EXT_LINE_NB  && ii+3 >= tmpL) || ( /* BeforeCR3 */
                             (byte != BAS_EXT_LINE_NB) &&
                             // (byte <  0x80 || byte > 0x86) &&
                             (byte < 0xE0 || byte > 0xF2) ) ) ) ) {         /* token tables */
                            if (byte == apostrophe) {
                                    if (!REM_line) string_open = !string_open ;
                            }
                            else if ( !string_open && byte == REMidC) REM_line = true ;
                            error = ConvertByteToBas (ptrText, CodeC[byte], byte, ptrFile->utf8,
                                                      ident, REM_line || string_open) ;
                        }
                        else {
                            ++ii ;
                            error = ReadByteSumFromWav (order, &byte2, ptrFile);
                            if (error != ERR_OK) break ;

                            if (byte == BAS_EXT_LINE_NB) {

                                    error = ReadByteSumFromWav (order, &byte3, ptrFile);
                                    if (error != ERR_OK) break ;
                                    ++ii ;

                                    lineNb = byte2 ;
                                    lineNb = (lineNb << 8) + byte3 ;
                                    sprintf(tmpC, "%u", (ushort) lineNb);

                                    error = ReadByteSumFromWav (order, &byte2, ptrFile);
                                    if (byte2 != 0x00) {
                                        printf ("Unexpected byte %lu at: %lu\n", byte2, ptrFile->total) ;
                                        if (error == ERR_OK) error = count_errors( ERR_LINE, ptrFile) ;
                                    }
                                    if (error != ERR_OK) break ;
                                    ++ii ;

                                    maxlen = cLL -1 - (uint) strlen (ptrText) ;
                                    if ((int) strlen (tmpC) > maxlen ) error = ERR_MEM ;
                                    else strncat (ptrText, tmpC, maxlen) ;
                            }
                            else if ( ( (pcMode & 8) >0 && KANJI_CODE_MIN <= byte && byte <= Kanji_Code_Max ) ) {
                                /* PC-1600K, S JIS-1 part */
                                error = ConvertKanjiSJIS1ToBas (ptrText, byte, byte2, ptrFile->utf8,
                                                                REM_line || string_open) ;
                            }
                            else { /* is a token */

                                if (key_cnt > 0) keyword_pos = SearchToken(byte << 8 | byte2) ;
                                if (keyword_pos > -1) {
                                    error = ConvertTokenToBas (ptrText, keyword[keyword_pos]) ;
                                }
                                else if ( KeysFromFileOnly ||
                                          byte == 0xE0     ||
                                          byte == 0xE4     ||
                                          byte == 0xE5     ||
                                         (byte >  0xE8 && byte < 0xF0) ) {

                                    error = ConvertTokenToHexS (ptrText, byte, byte2, ptrFile->utf8) ;
                                }
                                else
                                    switch (byte) {
                                    case 0xE1 :
                                        error = ConvertTokenToBas (ptrText, CodePc1600_E1[byte2]) ;
                                        break ;

                                    case 0xE2 :
                                        error = ConvertTokenToBas (ptrText, CodePc1600_E2[byte2]) ;
                                        break ;

                                    case 0xE3 :
                                        if ( (ptrFile->debug & BMC_TOKEN) > 0 ) {
                                            error = ConvertTokenToBas (ptrText, CodePc1600_E3b[byte2]) ;
                                        }
                                        else {
                                            error = ConvertTokenToBas (ptrText, CodePc1600_E3[byte2]) ;
                                        }
                                        break ;

                                    case 0xE6 :
                                        error = ConvertTokenToBas (ptrText, CodePc1600_E6[byte2]) ;
                                        break ;

                                    case 0xE7 :
                                        error = ConvertTokenToBas (ptrText, CodePc1600_E7[byte2]) ;
                                        break ;

                                    case 0xE8 :
                                        error = ConvertTokenToBas (ptrText, CodePc1600_E8[byte2]) ;
                                        break ;

                                    case 0xF0 :
                                        error = ConvertTokenToBas (ptrText, CodePc1600_F0[byte2]) ;
                                        break ;

                                    case 0xF1 :
                                        if (strcmp (CodePc1600_F1[byte2], REMstr)== 0) REM_line = true ;
                                        error = ConvertTokenToBas (ptrText, CodePc1600_F1[byte2]) ;
                                        break ;

                                    case 0xF2 :
                                        error = ConvertTokenToBas (ptrText, CodePc1600_F2[byte2]) ;
                                        break ;

                                    default :
                                        printf ("%s: Internal error, unknown token table [%02X] for PC-1600!\n", argP, (uint) byte);
                                    }   // End if: is a token with table
                            }  // End if: is a token
                        }  // End if: is a line NB or a token
                        break ;

                    default :
                        printf ("\n%s:RLine: Unknown Ident\n", argP) ;
                        error = ERR_FMT;
                        break ;
                    }  // End switch: Ident
                }  // End if: not (type == TYPE_IMG)
                if (error != ERR_OK) break ;

                if (ii + 1 == tmpL && (                 /* CR could be followed by BAS_NEW_EOF instead a possible sum */
                    ptrFile->ident == IDENT_NEW_BAS ||
                    ptrFile->ident == IDENT_NEW_PAS ||
                    ptrFile->ident == IDENT_EXT_BAS ||
                    ptrFile->ident == IDENT_EXT_PAS  )) ptrFile->check_end = true ; /*for ReadByteSum */

                /* Read next byte/token or the CR */
                error = ReadByteSumFromWav (order, &byte, ptrFile); /* Next Byte CR */

                if (ptrFile->check_end && error == ERR_EOT ) {
                    LastLineEot = true ; /* BAS_NEW_EOF was read instead of Checksum */
                    error = ERR_OK ;
                }
                if (error != ERR_OK) break ;
            }  // NEXT: byte or token in the line (New- to E-Bas)
            if (error != ERR_OK ) break ;

            /* check CR read before, not used for text output */
            if (byte != 0x0D) {
                    printf ("Missing End of Line at byte: %lu\n", ptrFile->total) ;
                    error = count_errors( ERR_MEM, ptrFile) ;
            }

            if (ptrFile->type == TYPE_IMG ) {
                if (strlen (ptrText) < (cLL - 1)) ptrText[length++] = (char) byte ;
                else error = ERR_MEM ;
            }
        }  // End if: Body Not old bas

        *ptrLen  = length ;
        if (ptrFile->type != TYPE_IMG) {
            if (lineformat == 0 && lineNbPos > 0 && ptrText[lineNbPos-1] == ' ') shift_left( ptrText + lineNbPos - 1);
            if (lineformat == 2 && lineNbPos > 0) ptrText[lineNbPos-1] = ':';
            if (strlen (ptrText) < (cLL - 2))
                (void) strncat (ptrText, Eol, 2) ;
            else error = ERR_MEM ;
            if (Qcnt == 0) {
                if ( (ptrFile->debug & 0xC0) == 0xC0 ) printf("\n>");
                else if ( (ptrFile->debug & 0xC0) > 0) printf(" ");
                if ( (ptrFile->debug & 0x80) > 0 )     printf("%s", ptrText);
            }
        }

    } while (0) ;

    return (error);
}

/* Read line of CASL /CAP-X assembler source from an image of source code, New group */
int ReadLineFromAsmNWav (ulong  order,
                        ulong  size,
                        char*  ptrText,
                       ulong*  ptrLen,
                    FileInfo*  ptrFile)
{
 static ulong LastLineNb = 0 ;
 static bool  LastLineEot = false ;

     uint  ii, lineNbPos = 0 ;
    ulong  byte ;
    ulong  byte2, byte3 ;
    ulong  sum ;
    ulong  length ;
    ulong  tmpL ;
     char  tmpC[cLNB] = "" ;     /* Buffer for line nb */
     bool  REM_line = false ;
     bool  string_open = false ; /* bas2img: string_auf */
      int  error = ERR_OK;

    ulong  ident = ptrFile->ident ; /* local copy */
//    if (ptrFile->ident == IDENT_EXT_PAS) ident = IDENT_EXT_BAS ; /* for byte conversion */

    do {
        *ptrText = 0 ;
        length   = 0 ;

        ptrFile->check_end = false ; /* no end of file mark should follow the next byte instead a possible sum */
        if (LastLineEot) {
            /* seldom: first BAS_NEW_EOF mark was read at the end of last line instead of a checksum */
            byte = BAS_NEW_EOF ;
            CheckSum (order, &byte, ptrFile) ;
            LastLineEot = false ;
        }
        else /* read first byte of line */
            error = ReadByteSumFromWav (order, &byte, ptrFile);
        if ( IMGc > 0 && ptrFile->total >= size - 3 && error == ERR_EOF ) {
            error = ERR_EOT ; /* workaround if size not exactly */
            if (Qcnt == 0) printf ("\nShort line at and of image ignored.\n" );
        }
        if (error > ERR_OK ) break ; /* possible ends with ERR_NSYNC */

        error = ReadByteSumFromWav (order, &byte2, ptrFile);
        if (error != ERR_OK) break ;

        { /* NEW (and EXT BAS) */
            tmpL = byte ;
            tmpL = (tmpL << 8) + byte2 ;
            if (tmpL == BAS_NEW_EOFFF) {  /* End of New, Ext Basic File */
                error = ERR_EOT;
                ptrFile->status = STAT_EOT ;
                /* Last checksum with sum_before, because 2. EOF byte
                   has not to include in the checksum */
                if (IMGc == 0) ReadByteFromWav (ORDER_STD, &sum, ptrFile); /* always error because end of sync */
                else sum = ptrFile->sum_before ; // simulate for img
                if (sum != ptrFile->sum_before) {
                    if ((ptrFile->debug & IGN_ERR_SUM) == 0 ) error = ERR_SUM ;
                    else count_errors( ERR_SUM, ptrFile) ;
                    if (Qcnt == 0) printf(" ERROR %d at EOF: %ld\n", ERR_SUM, ptrFile->total ) ;
                }
                if ( ( (ptrFile->debug & 0x0040) > 0 ) && (Qcnt == 0) )
                    printf(" EOF:(%02X=%02X)", (uchar) sum, (uchar) ptrFile->sum_before);
                break;
            } // no merged program blocks

            /* With CASL, the order of the bytes in the line header is exactly the opposite of that with BASIC images. */
            error = ReadByteSumFromWav (order, &byte3, ptrFile);
            if (error != ERR_OK) break ;
            tmpL = byte3 ;
            tmpL = (tmpL << 8) + byte2 ;
        } // Not for old bas


        /* Write length an the line number */
        if (ptrFile->type == TYPE_IMG) {
            ptrText[length++] = (char) byte ;
            ptrText[length++] = (char) byte2 ;
            ptrText[length++] = (char) byte3 ;
        }
        else {
            if (linenbr_del) {
                if (linewidth > 0)
                    sprintf(tmpC, "%*s", (int) linewidth, " ");
            }
            else {
                if (linewidth > 0)
                    sprintf(tmpC, "%*ld", (int) linewidth, tmpL);
                else
                    sprintf(tmpC, "%ld", tmpL);
            }
            if (strlen (tmpC) < (cLNB - 3)) {
                    if (lineformat>3) (void) strcat (tmpC, " : "); /* LNFRM_SCOLS */
                    else if (lineformat>2) (void) strcat (tmpC, ": ");
                    else (void) strcat (tmpC, " ");  /* SPC is later replaced for lineformat ==2, deleted for ==00 */
            }
            else error = ERR_MEM ;
            strncat (ptrText, tmpC, cLL-1-strlen(ptrText)) ;
            lineNbPos = strlen(ptrText) ;
            if (error != ERR_OK) break ;
        }
        if (tmpL <= LastLineNb ) {
            if (Qcnt == 0) printf ("Wrong line number sequence found: %lu: >= %lu:\n", LastLineNb, tmpL);
            error = count_errors( ERR_LINE, ptrFile );
            if (error != ERR_OK) break ;
        }
        LastLineNb = tmpL ;
        /* Read the line */
        {
            /* Calculate the Line length of the line body */
            tmpL = byte-2 ;
            if (tmpL > ll_Img ) {
                printf ("NOTE: Image line %lu with %lu bytes is to long, begin at byte: %lu\n", LastLineNb, tmpL, ptrFile->total) ;
                if ( tmpL > ll_Img + 8) error = count_errors( ERR_MEM, ptrFile) ;
                else ++ ptrFile->wrn_cnt ;
                if (error != ERR_OK) break ;
            }
            /* read first byte of the line body */
            error = ReadByteSumFromWav (order, &byte, ptrFile);
            if (error != ERR_OK) break ;

            /* line body processing */
            ii = 1;
            if (((ptrFile->debug & DEL_APST)>0 && byte == apostrophe ) ||
                ((ptrFile->debug & DEL_REMC)>0 && byte>0 && byte == REMidC) ) { /* delete it, for asm/c sources */
                    error = ReadByteSumFromWav (order, &byte, ptrFile);
                    if (error != ERR_OK) break ;
                    ++ii ;
            }
            for ( /* ii = ii */ ; ii < tmpL ; ++ii ) {

                if (ptrFile->type == TYPE_IMG) {
                    ptrText[length++] = (char) byte ;
                }
                else { /* BAS text, not image */

                    switch (ident) {
                    case IDENT_NEW_CSL :

                        if (strcmp (CodeNew[byte], REMstr)== 0) REM_line = true ;
                        if (byte == apostrophe && !(REM_line)) string_open = !string_open ;

                        error = ConvertByteToBas (ptrText, CodeNew[byte], byte, ptrFile->utf8,
                                                      IDENT_NEW_BAS, REM_line || string_open) ;
                        break ;

                    default :
                        printf ("\n%s:RLineAsm: Unknown Ident\n", argP) ;
                        error = ERR_FMT;
                        break ;
                    }  // End switch: Ident
                }  // End if: not (type == TYPE_IMG)
                if (error != ERR_OK) break ;

                if (ii + 2 == tmpL ) ptrFile->check_end = true ;    /* for New ReadByteSum */
                /* Last byte could be followed by BAS_NEW_EOF instead a possible sum */

                /* CASL lines do not contain a CR char */
                if (ii + 1 < tmpL )
                    error = ReadByteSumFromWav (order, &byte, ptrFile); /* Last Byte, no CR */

                if (ptrFile->check_end && error == ERR_EOT ) {
                    LastLineEot = true ; /* BAS_NEW_EOF was read instead of Checksum */
                    error = ERR_OK ;
                }
                if (error != ERR_OK) break ;
            }  // NEXT: byte in the line (New-Grp)
            if (error != ERR_OK ) break ;
            //  Code for CR removed
        }  // Body not for old bas

        *ptrLen  = length ;
        if (ptrFile->type != TYPE_IMG) {
            if (lineformat == 0 && lineNbPos > 0 && ptrText[lineNbPos-1] == ' ') shift_left( ptrText + lineNbPos - 1);
            if (lineformat == 2 && lineNbPos > 0) ptrText[lineNbPos-1] = ':';
            if (strlen (ptrText) < (cLL - 2))
                (void) strncat (ptrText, Eol, 2) ;
            else error = ERR_MEM ;
            if (Qcnt == 0) {
                if ( (ptrFile->debug & 0xC0) == 0xC0 ) printf("\n>");
                else if ( (ptrFile->debug & 0xC0) > 0) printf(" ");
                if ( (ptrFile->debug & 0x80) > 0 )     printf("%s", ptrText);
            }
        }

    } while (0) ;

    return (error);
}


void DebugReadEndFromBinWav (ulong  order,
                             FileInfo*  ptrFile)
{
      int  ii ;
    ulong  byte ;
      int  error ;

    ptrFile->writing  = false ;

    if ( (ptrFile->debug & 0x400) > 0) {
        if (Qcnt == 0) printf ("\nEnd @%06lX, checking again: ", stell( ptrFile ) ) ;
        for ( ii = 0 ; ii < 0x10 ; ++ii ) {
            error = ReadByteFromWav (order, &byte, ptrFile);
            if (error > ERR_OK) break ;

            if ( ( (ptrFile->debug & 0x30) == 0) && (Qcnt == 0) )
                printf(" %02X", (uchar) byte);

            if (error != ERR_OK) break ;
        }
    }
    else if  ((ptrFile->debug & 0x70) > 0) {
        if (Qcnt == 0) printf (" End, debug checking again: ") ;
        /* Read one byte from the Wav file */
        byte = UNREAD ;
        error = ReadByteFromWav (order, &byte, ptrFile);
        if (error > ERR_OK) return ;

        if (byte != UNREAD && Qcnt == 0) printf(" (%02X)", (uchar) byte);
    }
}


int OpenDstFile     (char*  ptrDstFile,
                     char*  ptrText,
                     FILE** ptrDstFd)
{
    /* Compare the destination file to "NULL", if not open the file */
    if ( strcmp (ptrDstFile, "NULL") != 0) {
        /* Open the destination file */
        *ptrDstFd = fopen (ptrDstFile, "wb") ;
        if (*ptrDstFd == NULL) {
            printf ("\n%s: Can't open the destination file: %s\n", argP, ptrDstFile) ;
            return (ERR_FILE) ;
        }
        ptrText[0] = 0 ;
    }
    else
        (void) strcpy (ptrText, " (file = NULL)") ;

    return (ERR_OK);
}


int ConvertWavToBin (char*  ptrSrcFile, /* Source file string*/
                     char*  ptrDstFile, /* Destination file string*/
                     char*  ptrParFile, /* Parameter file string*/
                     char*  ptrPcName,  /* PC name string*/
                     ulong  type,       /* SHARP file type */
                     ulong  order,      /* Order of nibbles in a Byte for old generations or ORDER_E for PC-1600 and newer */
                     ulong  utf8,       /* destination type of a special char */
                     long  imgbgn,      /* Offset, if the source is a binary image file */
                     ulong  debug)      /* special options or debug traces */
{
    FileInfo  fileInfo ;                /* source file pointer and variables, that used near global */
    TypeInfo  typeInfo ;                /* data variable header */
        FILE  *dstFd = NULL,            /* destination file pointer */
              *parFd = NULL ;           /* parameter file pointer */
        char  name[cLC], ntext[cLC],    /* Pocket file name, general temporary text */
              text[cLL], ftext[cLC],    /* general temporary text, one line of SHARP BASIC */
              tmpS[cLTK] ;
        uint  ii, rsvmax, fillc ;
  const uint  rsvmin = 48;              /* minimal length of SHARP ReSerVe memory (keys) */
        long  nbByte ;                  /* length of wav file */
       ulong  byte2, byte ;             /* SHARP byte read from wav file */
       ulong  addr = 0, eaddr = 0 ;     /* data start address, entry */
       ushort flags = 0 ;               /* flags of 3rd party formats, QSAVE M ... */
       ulong  ident ;                   /* mask real id with a replacement */
      ushort  grpId = pcgrpId ;         /* save global pcgrpId of PcName (changed in PrintSaveIdFromWav) */
        uint  pcNameId = pcId ;         /* save global pcId of PcName (sometimes changed later) */
       ulong  freq ;                    /* wav frequency */
       ulong  length = 0, llength ;     /* file length, SHARP data variable length, line length*/
        long  position ;                /* temporary wav file position */
         int  error, error_tmp, inVal ;
       uchar  eof_mark = 0 ;            /* for parameter --endmark */
        bool  eof_mark_write = false ;  /* EOF end mark was added to an image */
        bool  bom_mark_write = false ;  /* UTF-8 BOM mark at the begin of text image */

    do {
        if (utf8 == UTF8_BOM) {
            utf8 = 1 ;
            bom_mark_write = true ;
        }
        ftext[0]='\0' ;

        fileInfo.ptrFd      = NULL ;
        fileInfo.ident      = IDENT_UNKNOWN ;
        fileInfo.id_version = 0 ;
        fileInfo.length     = 0 ;     // Database Memo files
        fileInfo.base_freq  = 0 ;

        fileInfo.writing    = false ; // most header data and end mark not written
        fileInfo.check_end  = false ;
        fileInfo.pause      = false ;
        fileInfo.total      = 0 ;
        fileInfo.count      = 0 ;
        fileInfo.sum        = 0 ;
        fileInfo.block_len  = 0 ;   // used for E-Series, Qtape, PC-1500 end
        fileInfo.usedat_len = 0 ;   // used for Qtape

        fileInfo.blockAlign = 1 ;   // 8-bit mono
        fileInfo.bytesPerP  = 1 ;   // 8-bit = 1, 16-bit = 2
        fileInfo.bgnSamples = 44 ;
        fileInfo.startSampl = fileInfo.bgnSamples ;
        fileInfo.pre_amp    = 1 ;

        fileInfo.start_amp  = 0 ;
        fileInfo.bitLen     = 0 ;
        fileInfo.wavLenMin  = 0 ;
        fileInfo.wavLenMax  = 0 ;
        fileInfo.wavLenMid  = 0 ;
        fileInfo.byteLen    = 0 ;

        fileInfo.synching   = 0 ;

        fileInfo.rate_amp   = 0 ;
        fileInfo.amp_weight = AMP_WEIGHT_HIGH ;

        fileInfo.ampd_sum   = 0 ;
        fileInfo.ampd_cnt   = 0 ;
        fileInfo.nbStopBMin = 1 ;   // first stop bit has number 0
        fileInfo.skip_bits  = SYNC_NB_CNT ;
        fileInfo.sync_bit   = false ;

        fileInfo.type       = type ;
        fileInfo.subtype    = TYPE_NOK ;
        fileInfo.utf8       = utf8 ;

        fileInfo.debug      = debug ;
        fileInfo.wrn_cnt    = 0 ;
        fileInfo.err_cnt    = 0 ;
        fileInfo.err_last   = ERR_OK ;
        fileInfo.err_exit   = ERR_OK ;
        fileInfo.status     = STAT_OK ; /*status of processing */
        fileInfo.position   = 0 ;
        fileInfo.wavtime    = 0 ;

        error               = ERR_OK ;
        dstFd               = NULL ;

        /* Open the source file */
        fileInfo.ptrFd = fopen (ptrSrcFile, "rb") ;
        if (fileInfo.ptrFd == NULL) {
            printf ("\n%s: Can't open the src (wav) file: %s\n", argP, ptrSrcFile) ;
            error = ERR_FILE ;
            break ;
        }

        /* Seek to the end of the source file */
        error = fseek (fileInfo.ptrFd, 0, SEEK_END) ;
        if (error != ERR_OK) {
            printf ("\n%s:endwav - Can't seek the src (wav) file\n", argP) ;
            error = ERR_FILE ;
            break ;
        }

        /* Get the length of the source file */
        nbByte = ftell (fileInfo.ptrFd) ;
        if (nbByte <= 0) {
            printf ("\n%s:endwav - Can't ftell the src (wav) file\n", argP) ;
            error = ERR_FILE ;
            break ;
        }
        fileInfo.endSamples = (ulong) nbByte - 1 ; // without EOF

        /* Seek to the beginning of the source file */
        error = fseek (fileInfo.ptrFd, 0, SEEK_SET) ;
        if (error != ERR_OK) {
            printf ("\n%s:bgnwav - Can't seek the src (wav) file\n", argP) ;
            error = ERR_FILE ;
            break ;
        }

        if ( type == TYPE_RAW || SHCc != 0 ) {
            error = OpenDstFile (ptrDstFile, ftext, &dstFd) ;
            if (error != ERR_OK) break ;

            fileInfo.writing  = true ; /* total write counter on */
        }

        if (IMGc > 0 ) {
            if (Qcnt == 0) printf ("Input format  : Switched to binary image format (no wav file)\n") ;

            length = (ulong) nbByte ; // < c2b3f: = fileInfo.endSamples ;
            error = fseek (fileInfo.ptrFd, fileInfo.endSamples, SEEK_SET) ;
            if (error != ERR_OK) {
                printf ("\n%s:endimg - Can't seek the src (img) file\n", argP) ;
                error = ERR_FILE ;
                break ;
            }
            inVal = fgetc (fileInfo.ptrFd) ;   /* check for EOF mark(s) included */
            if (inVal == EOF) {
                error = ERR_FILE ;
                break ;
            }
            else if (inVal == BAS_1500_EOF) {
                length-- ; /* End mark was included from Bas2IMG and other images */
                ii = 1;
                if (length > 0) {
                    error = fseek (fileInfo.ptrFd, -2, SEEK_CUR) ;
                    if (error != ERR_OK) {
                        printf ("\n%s:endimg2 - Can't seek the src (img) file\n", argP) ;
                        error = ERR_FILE ;
                        break ;
                    }
                    inVal = fgetc (fileInfo.ptrFd) ;   /* check for one unexpected EOF mark */
                    if (inVal == EOF) {
                        error = ERR_FILE ;
                        break ;
                    }
                    else if (inVal == BAS_1500_EOF) {
                        length-- ; /* End mark2 */
                        ++ii;
                    }
                }
                if (inVal != BAS_1500_EOF) inVal = BAS_1500_EOF -1 ;
                if (Qcnt == 0) printf ("%s: Ignored %u additional end mark(s) at the end of the image.\n", argP, ii) ;
            }

            if ( (ulong) imgbgn < length ) {
                /* Seek to the Begin of the binary image */
                error = fseek (fileInfo.ptrFd, imgbgn, SEEK_SET) ;
                length -= imgbgn ;
            }
            else {
                printf ("\n%s: Begin of the Image %lu is to high\n", argP, imgbgn) ;
                error = fseek (fileInfo.ptrFd, 0, SEEK_SET) ;
            }
            if (error != ERR_OK) {
                printf ("\n%s:bgnimg - Can't seek the image file\n", argP) ;
                error = ERR_FILE ;
                break ;
            }
        } // end if IMGc
        else if (KHXc > 0 ) {
            if (Qcnt == 0) printf ("Input format  : Forced DSave khx format (no wav file)\n") ;
            do { /* find start position of data in the Khx file*/
                inVal = fgetc (fileInfo.ptrFd) ;
                if (inVal == EOF) {
                    printf ("\n%s:bgnkhx - Start of data (colon) not found in src (khx) file\n", argP) ;
                    error = ERR_SYNC ;
                    break ;
                }
            } while (inVal != ':' ) ;
            if (error != ERR_OK) break ;
            error = ReadSaveIdFromTap (&fileInfo, &dstFd);
        }
        else if (TAPc > 0 ) {
            if (Qcnt == 0) printf ("Input format  : Forced emulator tap format (no wav file)\n") ;
            error = ReadSaveIdFromTap (&fileInfo, &dstFd);
        }
        else { /* Wav File */

            if (nbByte <= 58) {
                printf ("\n%s: Source file is not a valid WAV File\n", argP) ;
                error = ERR_FMT ;
                break ;
            }

            /* Read the header of the source WAV file */
            error = ReadWavHead (&freq, &fileInfo) ;
            if (error != ERR_OK) break ;

            /* Check the lower frequency limit */
            if (freq < 5000) {
                printf ("\n%s: Sampling frequency is lower than 5000 Hz: %lu Hz\n", argP, freq);
                error = ERR_FMT ;
                break ;
            }

            /* Check the recommended higher frequency limit, old 22050 */
            if (freq > 48000)
                if (Qcnt == 0) printf ("Sampling frequency is: %lu Hz, higher than it is recommended.\n", freq);

            /* Check the higher frequency limit */
            if (freq > 192000) {
                printf ("\n%s: Sampling frequency is greater than 192 kHz: %lu Hz!\n", argP, freq);
                error = ERR_FMT ;
                break ;
            }
            fileInfo.wav_freq = freq;

            if (Scnt > 0 && StartTime > 0.000001) {
                fileInfo.startSampl = fileInfo.bgnSamples +
                                      fileInfo.blockAlign * (long) (StartTime * (float) (fileInfo.wav_freq)) ;
                if (fileInfo.startSampl > fileInfo.endSamples - fileInfo.blockAlign * 1024){
                    printf ("\n%s: Start time %5.1f is at the end of this wav file!\n", argP, StartTime);
                    error = ERR_ARG ;
                    break ;
                }
                else {
                    error = fseek (fileInfo.ptrFd, fileInfo.startSampl, SEEK_SET) ; /* forward to start */
                    if (error != ERR_OK) {
                        printf ("\n%s:ConvertW2B - Can't seek the file\n", argP) ;
                        error = ERR_FILE ;
                        break ;
                    }
                }
            }
            else fileInfo.startSampl = fileInfo.bgnSamples ;

            if ((debug & NO_PRE_AMP)==0) {
                    if (Qcnt == 0 && (debug) >0 ) printf ("Quantise the levels of the wav file...\n");
                    error = AnalyseSoundLevelOfWav (&fileInfo) ;
                    if (Qcnt == 0 && Scnt == 0 && fileInfo.startSampl - fileInfo.bgnSamples > fileInfo.wav_freq / 64 )
                        printf ("Search for sync signal starts at time of %.2lf s. Use -s to be more specific.\n", WavTime(&fileInfo));
            }
            else if (Qcnt == 0) printf ("The analysis of the wav file and pre-amplification had been turned off.\n");
            if (error != ERR_OK) break ;
            Debug_Time_End = Debug_Time + DEBUG_TIME_LEN ;

            /* First search from begin of wav SYNC_NB_CNT-times BID_1 */
            fileInfo.freq = 0 ;     // flag, that no freq was searched
            ii = 0 ;
            do {
                if (ii++ > FSYNC_NB_TRY) { /* how often ReadId */
                    error = ERR_SYNC ;
                    break ;
                }
                fileInfo.synching = SYNC_NB_CNT;
                /* Search the Synchro and the Frequency of the wav */
                error = FindFreqAndSyncFromWav (&fileInfo) ;
                if (error < ERR_OK ) { /* Sync not found with first found frequency */
                    if (fileInfo.base_freq == Base_FREQ1){
                        if ( Base_FREQ2 > 0) fileInfo.base_freq  = Base_FREQ2 ;
                        else if ( Base_FREQ3 > 0) fileInfo.base_freq  = Base_FREQ3 ;
                        else if ( Base_FREQ4 > 0) fileInfo.base_freq  = Base_FREQ4 ;
                        else error = ERR_SYNC ;
                    }
                    else if (fileInfo.base_freq == Base_FREQ2){
                        if ( Base_FREQ3 > 0) fileInfo.base_freq  = Base_FREQ3 ;
                        else if ( Base_FREQ4 > 0) fileInfo.base_freq  = Base_FREQ4 ;
                        else error = ERR_SYNC ;
                    }
                    else if (fileInfo.base_freq == Base_FREQ3){
                        if ( Base_FREQ4 > 0) fileInfo.base_freq  = Base_FREQ4 ;
                        else error = ERR_SYNC ;
                    }
                    else error = ERR_SYNC ;
                }
                if (error > ERR_OK) break ;
                else if ( error < ERR_OK ) {
                    ii = 0 ; /*  for new frequency */
                    continue ;
                }
                if (fileInfo.base_freq == Base_FREQ2) Debug_Time_End = Debug_Time + DEBUG_TIME_L15 ;

                /* Read the Save Id */
                error = ReadSaveIdFromWav (&fileInfo, &dstFd);
                if (error == ERR_NSYNC ) continue ; /* false sync found */
                if (error != ERR_OK) break ;

            } while ( ( error == ERR_NSYNC ||
                        (type != TYPE_RAW && fileInfo.ident == IDENT_UNKNOWN )
                      ) && devId != DEV_BIN  ) ; /* synthetic wav only onetime */

        } // End if is wav
        if (error != ERR_OK) break ;

        /* Check ID, set pcgrpId */
        if (IMGc > 0)
            error = SetFileIdForImg (&fileInfo, &length) ;
        else
            error = PrintSaveIdFromWav (&fileInfo) ;
        ident = fileInfo.ident ;

        if ( type == TYPE_BAS) { /* check, if type BAS was used correctly */
            if ( ident == IDENT_E_ASC ) {
                 if (Qcnt == 0) printf ("%s: ASCII file detected, type is changed from 'bas' to 'img'/'asc' now.\n", argP);
                 ++ fileInfo.wrn_cnt;
                 fileInfo.type = type = TYPE_IMG ; // for TYPE_ASC
                 fileInfo.subtype = TYPE_ASC ;
            }
            else if ( ident == IDENT_PC16_CAS ) {
                 if (Qcnt == 0) printf ("%s: This file is an image that has to be converted to 'bas' in a 2nd step.\n", argP);
                 printf ("%s: Only an IMaGe is created now, not 'bas'.\n", argP);
                 ++ fileInfo.wrn_cnt;
                 fileInfo.type = type = TYPE_IMG ; // for TYPE_ASC
                 fileInfo.subtype = TYPE_ASC ;
            }
        }
        else if ( type == TYPE_ASC) { /* check, if type ASC was used correctly */
            if ( ident == IDENT_E_BAS   || ident == IDENT_PC16_BAS ||
                 ident == IDENT_EXT_BAS || ident == IDENT_EXT_PAS  ||
                 ident == IDENT_NEW_BAS || ident == IDENT_NEW_PAS  ||
                 ident == IDENT_OLD_BAS || ident == IDENT_OLD_PAS  || ident == IDENT_QT_BAS ||
                 ident == IDENT_PC1211  || ident == IDENT_PC15_BAS || ident == IDENT_PC15QTBAS ) {
                 if (Qcnt == 0) printf ("%s: Image detected, file type is changed from 'asc' to 'bas' now.\n", argP);
                 linewidth = 0 ;
                 fileInfo.utf8 = utf8 = UTF8_ASC ;
                 fileInfo.type = type = TYPE_BAS ;
            }
            else fileInfo.type = type = TYPE_IMG ; /* always for TYPE_ASC further processing */
        }

        if (TAPc == 0 && KHXc == 0) ReadBitParamAdjust (&fileInfo) ; /* for user data */

        if ( SHCc != 0 ) {
            if  (pcgrpId != IDENT_PC1211 && /* GRP_OLD is used for this */
                 pcgrpId != GRP_OLD && pcgrpId != GRP_NEW && pcgrpId != GRP_EXT) {
                printf ("\n%s: SHC file format is not supported for this ident.\n", argP);
                printf ("\n%s: Only PC-12.. to 1475 are implemented for this.\n", argP);
                error = ERR_FMT ;
                break ;
            }
            else if (fileInfo.ident == IDENT_PC121_DAT) ident = IDENT_OLD_DAT ;
            else if (fileInfo.ident == IDENT_PC1211) ident = IDENT_OLD_BAS ;
            if (fileInfo.ident != ident && Qcnt==0 )
                printf ("\n%s: Pocket Pctyp PC1251 is used for this SHC file.\n", argP);
        }

        if (type == TYPE_RAW || SHCc != 0 ){
            if (fileInfo.base_freq == Base_FREQ2 && Base_FREQ2 > 0 ) order = ORDER_INV ;
            else if (fileInfo.base_freq == Base_FREQ4 && Base_FREQ4 > 0 ) order = ORDER_Q ;
            /* only for PC-1500 the id (and the counter in the first header) has written by ReadSaveId */
            else {
                TAPw = 0 ; /* Destination TAP-Format is flat for other series than PC-1500 */

                error = WriteByteToFile (ident, &dstFd) ;
                if (error != ERR_OK) break ;
                if (fileInfo.base_freq == Base_FREQ1 && Base_FREQ1 > 0)
                                          ++fileInfo.total ; /* id read in quaters */
            }
            if (fileInfo.base_freq == Base_FREQ3 && Base_FREQ3 > 0 ) order = ORDER_E ;
        }
        /* Map IDs here, if needed */

        if ( IMGc == 0 && type != TYPE_RAW )  {
            if (error != ERR_OK) break ;

            /* Read the Save Name */
            error = ReadSaveNameOrPassFromWav (name, &eaddr, &flags, &fileInfo, &dstFd);
            if (error != ERR_OK) break ;
            if ((debug & 0x4C0)>0) printf ("\n");
            if (Qcnt == 0) printf (" Save name     : %s\n", name) ;

            /* Read the PassWord if necessary */
            if ((fileInfo.ident == IDENT_OLD_PAS) ||
                (fileInfo.ident == IDENT_NEW_PAS) ||
                (fileInfo.ident == IDENT_EXT_PAS) ) {

                error = ReadSaveNameOrPassFromWav (ntext, &eaddr, &flags, &fileInfo, &dstFd);
                if (error != ERR_OK) break ;
                if ((debug & 0x4C0)>0) printf ("\n");
                if (Qcnt == 0) printf (" Password      : %s\n", ntext) ;
            }
        }  //end if not source img or target raw

        if ( fileInfo.ident == IDENT_PC1211 ||
             fileInfo.ident == IDENT_PC121_DAT ||
             type == TYPE_RAW ) {
                Stop_Bit_Max = STOP_BIT_M11 ;
        }
        if (type == TYPE_RAW){
            fileInfo.ident = IDENT_RAW ;
            fileInfo.count = 0 ;
            /* read the save name or pwd will be done with the first block of raw data */
        }
        else {
            if (SHCc == 0 && Xcnt == 0) error = OpenDstFile (ptrDstFile, ftext, &dstFd) ;
            if (error != ERR_OK) break ;

            order = ORDER_STD ;
        } // end if not raw
        if (Mcnt > 0) {
            error = OpenDstFile (ptrParFile, text, &parFd) ;
            if (error != ERR_OK) break ;
            strncpy(text, "name=", cLL-1) ;
            strncat(text, name, cLL-8) ;
            strncat(text, "\r\n", 3) ;
            error = WriteStringToFile (text, &parFd) ;
            if (error != ERR_OK) break ;

            strncpy(text, "ident=", cLL-1) ;
            sprintf(ntext, "%lu\r\n", fileInfo.ident);
            strncat(text, ntext, cLL-7) ;
            error = WriteStringToFile (text, &parFd) ;
            if (error != ERR_OK) break ;

            if (strlen(ptrPcName) > 0) {
                if (grpId == pcgrpId && pcNameId == pcId) strncpy(text, "pc=", cLL-1) ;
                else strncpy(text, "; pc=", cLL-1) ;
                strncat(text, ptrPcName, cLL-8) ;
                strncat(text, "\r\n", 3) ;
                error = WriteStringToFile (text, &parFd) ;
                if (error != ERR_OK) break ;
            }
            strncpy(text, "pcid=", cLL-1) ;
            if (pcId > 0 && grpId == pcgrpId && pcNameId == pcId) {
                sprintf(ntext, "%u", pcId);
            }
            else {
                switch (pcgrpId) {
                case IDENT_PC1211 :
                    sprintf(ntext, "%u", 1211);
                    break ;
                case GRP_OLD :
                    sprintf(ntext, "%u", 1251);
                    break ;
                case GRP_NEW :
                    if (fileInfo.nbStopBMin == 0) sprintf(ntext, "%u", 1401);
                    else if (pcNameId == 1401 && pcId == 1402) sprintf(ntext, "%u", 1402); /* see ReadSaveIdFromWav */
                    else sprintf(ntext, "%u", 1460);
                    break ;
                case GRP_EXT :
                    sprintf(ntext, "%u", 1475);
                    break ;
                case GRP_E :
                    sprintf(ntext, "%u", 500);
                    break ;
                case IDENT_PC1500 :
                    sprintf(ntext, "%u", 1500);
                    break ;
                case GRP_16 :
                    sprintf(ntext, "%u", 1600);
                    break ;
                case GRP_G :
                    sprintf(ntext, "%u", 850);
                    break ;
                default :
                    sprintf(ntext, "%u", 0);
                }
            }
            strncat(text, ntext, cLL-8) ;
            strncat(text, "\r\n", 3) ;
            error = WriteStringToFile (text, &parFd) ;
            if (error != ERR_OK) break ;

            if (IMGc == 0 && TAPc == 0 && KHXc == 0) {
                strncpy(text, "basefreq=", cLL-1) ;
                sprintf(ntext, "%lu\r\n", (ulong)((double)fileInfo.base_freq/speed + 0.5 )); //%.0lf
                strncat(text, ntext, cLL-10) ;
                error = WriteStringToFile (text, &parFd) ;
                if (error != ERR_OK) break ;

                strncpy(text, "realfreq=", cLL-1) ;
                sprintf(ntext, "%lu\r\n", fileInfo.freq);
                strncat(text, ntext, cLL-10) ;
                error = WriteStringToFile (text, &parFd) ;
                if (error != ERR_OK) break ;
            }
            text[0]='\0' ;
        }

        /* set order, also for raw data */
        if (fileInfo.base_freq == Base_FREQ3 && Base_FREQ3 > 0) order = ORDER_E ;
        else if (fileInfo.base_freq == Base_FREQ2 && Base_FREQ2 > 0) order = ORDER_INV ;
        else if (fileInfo.base_freq == Base_FREQ4 && Base_FREQ4 > 0) order = ORDER_Q ;

        /* Read the rest of the Header from the Wav file */
        if (IMGc == 0) switch (fileInfo.ident) {

        case IDENT_E_BAS :      /* Check Mode 2 ID of E-Header for PC-1600 BAS or RSV */
            case IDENT_PC16_BAS :
            case IDENT_PC16_RSV :
        case IDENT_E_BIN :
        case IDENT_E_ASC :
            case IDENT_E_IMG :
        case IDENT_PC16_CAS :   /* Check if PC-1600 BAS Image or ASCII Data */
            case IDENT_PC16_IMG :
        case IDENT_PC16_DAT :

            error = ReadHeadFromEWav (&addr, &eaddr, &length, &fileInfo);
            break ;

        case IDENT_QT_BAS :
        case IDENT_QT_RSV :
        case IDENT_QT_BIN :
        case IDENT_QT_DIM :
        case IDENT_QT_DAT :

        case IDENT_PC15QTBAS :
        case IDENT_PC15QTBIN :

        case IDENT_PC15_BAS :
        case IDENT_PC15_RSV :
        case IDENT_PC15_DEF :
        case IDENT_PC15_BIN :
        case IDENT_PC15_DAT :

            error = ReadHeadFrom15Wav (&order, &addr, &eaddr, &length, &flags, &fileInfo);
            break ;

        case IDENT_NEW_TEL :
        case IDENT_NEW_SCD :
        case IDENT_NEW_NOT :
        case IDENT_NEW_CRD :

            /* Read by ReadSaveIdFromWav */
            length = fileInfo.length +1;
            break ;

        case IDENT_OLD_MEM :
        case IDENT_OLD_MEM2:

            /* Read the Header from Old Mem Wav file */
            error = ReadHeadFromMemWav (&addr, &length, &fileInfo, &dstFd);
            break ;

        case IDENT_OLD_BIN :
        case IDENT_NEW_BIN :

            /* Read the Header from Old New Bin Wav file */
            error = ReadHeadFromBinWav (&addr, &length, &fileInfo, &dstFd);
            break ;

        } // end switch Header
        if (error != ERR_OK) break ;

        if ( type == TYPE_BAS &&
           (fileInfo.ident != IDENT_PC1211    &&
            fileInfo.ident != IDENT_OLD_BAS   && fileInfo.ident != IDENT_OLD_PAS &&
            fileInfo.ident != IDENT_NEW_BAS   && fileInfo.ident != IDENT_NEW_PAS &&
            fileInfo.ident != IDENT_NEW_CSL   &&
            fileInfo.ident != IDENT_EXT_BAS   && fileInfo.ident != IDENT_EXT_PAS &&
            fileInfo.ident != IDENT_QT_BAS    &&
            fileInfo.ident != IDENT_PC15QTBAS &&
            fileInfo.ident != IDENT_PC15_BAS  &&
            fileInfo.ident != IDENT_PC16_BAS  &&
            fileInfo.ident != IDENT_E_BAS      )) {
                printf ("\n%s: Only images are supported for this file type from wav, not 'bas'.\n", argP) ;
                printf ("         Use option --type=img (or with the correct file type)\n") ;
                error = ERR_ARG ;
                break ;
        }
        if ( type == TYPE_RSV &&
           (fileInfo.ident != IDENT_PC1211    &&
            fileInfo.ident != IDENT_OLD_BAS   &&
            fileInfo.ident != IDENT_OLD_PAS   &&
            fileInfo.ident != IDENT_NEW_BAS   &&
            fileInfo.ident != IDENT_NEW_PAS   &&
            fileInfo.ident != IDENT_EXT_BAS   &&
            fileInfo.ident != IDENT_EXT_PAS   &&
            fileInfo.ident != IDENT_QT_RSV    &&
            fileInfo.ident != IDENT_PC15_RSV  &&
            fileInfo.ident != IDENT_PC15_DEF  &&
            fileInfo.ident != IDENT_PC16_RSV   )) {
                printf ("\n%s: No RSV images are supported for this file type.\n", argP) ;
                error = ERR_ARG ;
                break ;
        }
        if ( type == TYPE_DEF &&
            fileInfo.ident != IDENT_PC15_DEF    ) {
                printf ("\n%s: No Def.images are supported for this file type.\n", argP) ;
                error = ERR_ARG ;
                break ;
        }

        ident = fileInfo.ident ;
        if ( IMBc != 0 ) {
           if (fileInfo.ident == IDENT_PC15_BAS  ||
               fileInfo.ident == IDENT_PC15QTBAS ||
               fileInfo.ident == IDENT_QT_BAS) {
                        ident = IDENT_PC15_IMG ;
                        ++length ;
           }
           else if (fileInfo.ident == IDENT_PC16_BAS) ident = IDENT_E_BIN ;
           else if (fileInfo.ident == IDENT_E_BAS) {
                        ident = IDENT_E_BIN ;
                        if (pcgrpId == GRP_E) length -= 19 ;
                        if (pcgrpId == GRP_G) length -= 12 ;
           }
           else if (fileInfo.ident == IDENT_NEW_PAS) ident = IDENT_NEW_BAS ;
           else if (fileInfo.ident == IDENT_EXT_PAS) ident = IDENT_EXT_BAS ;

           if ( type != TYPE_IMG ||
                (    ident != IDENT_NEW_BAS   &&
                     ident != IDENT_NEW_CSL   &&
                     ident != IDENT_EXT_BAS   &&
                     ident != IDENT_PC15_IMG  &&
            fileInfo.ident != IDENT_PC16_BAS  &&
            fileInfo.ident != IDENT_E_BAS      )) {
                if (Qcnt == 0) {
                    printf ("\n%s: Only line images are supported for this file type, not 'imb'.\n", argP) ;
                    printf ("         Use option --type=img (or with the correct file type)\n") ;
                    printf ("         The 'imB' option is ignored and is now replaced by 'imG'.\n") ;
                }
                ++ fileInfo.wrn_cnt;
                IMBc = 0 ;
           }
        }

        if (Mcnt > 0) {

            if (fileInfo.type != TYPE_NOK && fileInfo.type != TYPE_RAW ) {
                strncpy(text, "type=", cLL-1) ;
                switch (fileInfo.type) {
                case TYPE_BAS :
                    if (fileInfo.subtype == TYPE_CSL)
                        strncpy(ntext, "casl", cLC-1) ;
                    else
                        strncpy(ntext, "img", cLC-1) ;
                    break ;
                case TYPE_IMG :
                    if (fileInfo.subtype == TYPE_BIN)
                        strncpy(ntext, "bin", cLC-1) ;
                    else if (fileInfo.subtype == TYPE_DAT)
                        strncpy(ntext, "dat", cLC-1) ;
                    else if (fileInfo.subtype == TYPE_RSV)
                        strncpy(ntext, "rsv", cLC-1) ;
                    else if (fileInfo.subtype == TYPE_ASC)
                        strncpy(ntext, "asc", cLC-1) ;
                    else if (fileInfo.subtype == TYPE_BAS)
                        strncpy(ntext, "bas", cLC-1) ;
                    else if (fileInfo.subtype == TYPE_TXT)
                        strncpy(ntext, "txt", cLC-1) ;
                    else if (fileInfo.subtype == TYPE_DEF)
                        strncpy(ntext, "def", cLC-1) ;
                    else if (fileInfo.subtype == TYPE_DIM)
                        strncpy(ntext, "dim", cLC-1) ;
                    else if (fileInfo.subtype == TYPE_MEM)
                        strncpy(ntext, "mem", cLC-1) ;
                    else if (fileInfo.subtype == TYPE_CRD)
                        strncpy(ntext, "crd", cLC-1) ;
                    else if (fileInfo.subtype == TYPE_TEL)
                        strncpy(ntext, "tel", cLC-1) ;
                    else if (fileInfo.subtype == TYPE_SCD)
                        strncpy(ntext, "scd", cLC-1) ;
                    else if (fileInfo.subtype == TYPE_NOT)
                        strncpy(ntext, "not", cLC-1) ;
                    else if (fileInfo.subtype == TYPE_CSL)
                        strncpy(ntext, "casl", cLC-1) ;
                    else
                        strncpy(ntext, "img", cLC-1) ;
                    break ;
                case TYPE_RSV :
                    strncpy(ntext, "rsv", cLC-1) ;
                    break ;
                case TYPE_ASC :
                    strncpy(ntext, "asc", cLC-1) ;
                    break ;
                case TYPE_DEF :
                    strncpy(ntext, "def", cLC-1) ;
                    break ;
                }
                strncat(text, ntext, cLL-8) ;
                strncat(text, "\r\n", 3) ;
                error = WriteStringToFile (text, &parFd) ;
                if (error != ERR_OK) break ;

                strncpy(text, "typew=", cLL-1) ;
                switch (fileInfo.type) {
                case TYPE_BAS :
                    strncpy(ntext, "bas", cLC-1) ;
                    break ;
                case TYPE_IMG :
                    if (IMBc > 0)
                        strncpy(ntext, "imb", cLC-1) ;
                    else
                        strncpy(ntext, "img", cLC-1) ;
                    break ;
                }
                strncat(text, ntext, cLL-9) ;
                strncat(text, "\r\n", 3) ;
                error = WriteStringToFile (text, &parFd) ;
                if (error != ERR_OK) break ;
            }
            if (addr > 0 || fileInfo.subtype == TYPE_BIN) {
                strncpy(text, "startaddr=", cLL-1) ;
                sprintf(ntext, "%lu\r\n", addr);
                strncat(text, ntext, cLL-11) ;
                error = WriteStringToFile (text, &parFd) ;
                if (error != ERR_OK) break ;
            }
            if ((eaddr > 0 || fileInfo.subtype == TYPE_BIN) && (eaddr & 0xffff) < 0xffff ) {
                if (eaddr>0) strncpy(text, "entryaddr=", cLL-1) ;
                else {
                    strncpy(text, "; entryaddr=", cLL-1) ; /* QT1 writes 0 */
                    if (Qcnt == 0 && debug >0) printf ("Uncomment 'entryaddr=%lu' in the parameter file to really autostart code there!\n", eaddr);
                }
                sprintf(ntext, "%lu\r\n", eaddr);
                strncat(text, ntext, cLL-11) ;
                error = WriteStringToFile (text, &parFd) ;
                if (error != ERR_OK) break ;
            }
            if (pcAddr > 0 || fileInfo.subtype == TYPE_MEM) {
                strncpy(text, "entryaddr=", cLL-1) ; /* 4bit end addr +1 */
                sprintf(ntext, "%lu\r\n", pcAddr);
                strncat(text, ntext, cLL-11) ;
                error = WriteStringToFile (text, &parFd) ;
                if (error != ERR_OK) break ;
            }
            if (flags > 0) {
                strncpy(text, "headerflags=", cLL-1) ;
                sprintf(ntext, "%u\r\n", flags);
                strncat(text, ntext, cLL-13) ;
                error = WriteStringToFile (text, &parFd) ;
                if (error != ERR_OK) break ;
            }
            if (length > 0) {
                strncpy(text, "datasize=", cLL-1) ;
                sprintf(ntext, "%lu\r\n", length);
                strncat(text, ntext, cLL-10) ;
                error = WriteStringToFile (text, &parFd) ;
                if (error != ERR_OK) break ;
            }
            text[0]='\0' ;
        }

        if (Xcnt>0) {
                if (Qcnt==0) printf ("\n%s: --exit after header was selected\n", argP) ;
                break ; // ConvertWavToBin main part
        }
        if (type == TYPE_BAS) {
            if ( bom_mark_write ){
                strcpy  (text, utf8_BOMstr) ;

                error = WriteStringToFile (text, &dstFd) ;
                if (error != ERR_OK) break ;
            }
            if (SHAc != 0 ) {
                strcpy  (text, ".BAS \"" ) ;
                strncat (text, name, 16) ;
                strcat  (text, "\"") ;
                strncat (text, Eol, 2) ;
                error = WriteStringToFile (text, &dstFd) ;
                if (error != ERR_OK) break ;
            }
        }
        strncpy (text, ftext, cLC-1) ;
        /* Init the read counter was done by ReadSaveNameOrPassFromWav */

        /* Read the body of the Wav file */
        switch (ident) {

        case IDENT_PC15_BIN :
        case IDENT_PC15_IMG :   /* not line by line */
        case IDENT_PC15_RSV :
        case IDENT_PC15_DEF :
        case IDENT_PC15QTBIN :
        case IDENT_QT_BIN :
        case IDENT_QT_RSV :
        case IDENT_QT_DIM :

        case IDENT_PC16_RSV :
        case IDENT_E_BIN :

        case IDENT_OLD_BIN :
        case IDENT_NEW_BIN :

        case IDENT_OLD_MEM :
        case IDENT_OLD_MEM2:
        case IDENT_NEW_TEL :
        case IDENT_NEW_SCD :
        case IDENT_NEW_NOT :
        case IDENT_NEW_CRD :

            if (order != ORDER_Q || fileInfo.id_version != 1 )   /* QT1 counts backward */
                fileInfo.count  = 0 ;   /* Reset the checksum counter after header */
            // fileInfo.sum = 0 ;
            fileInfo.writing  = true ; /* total write counter on */
            if (Qcnt == 0) printf (" Output format : Binary%s\n", text) ;

            for ( ii = 0 ; ii < length ; ++ii ) {
                /* Read a byte from the Wav file */
                if ( ii + 1 == length && fileInfo.ident != IDENT_NEW_BIN )
                    fileInfo.status = STAT_EOT ;

                if ( ii + 1 == length && fileInfo.ident == IDENT_NEW_BIN ) {
                    /* prevent collision of mark BAS_NEW_EOF with checksum */
                    fileInfo.check_end = true ;
                    error = ReadByteTraceFromWav (order, &byte, &fileInfo);
                    CheckSum( order, &byte, &fileInfo) ;
                }
                else error = ReadByteSumFromWav (order, &byte, &fileInfo);
                if (error > ERR_OK || byte == UNREAD) break ;
                error_tmp = error;

                if ( ii + 1 < length ||
                    !( (fileInfo.ident == IDENT_E_BAS && pcgrpId == GRP_E) ||
                        ident == IDENT_PC15_IMG ) ) /* Write IMB without end mark */
                    /* Write it in the destination file queue */
                    error = WriteByteToFile (byte, &dstFd) ;

                if (error != ERR_OK || error_tmp != ERR_OK) {
                    if (error == ERR_OK) error = error_tmp;
                    break ;
                }

                if ( ii + 2 == length && (fileInfo.ident == IDENT_PC15_BIN || /* force checksum reading */
                                          fileInfo.ident == IDENT_PC15_DEF || fileInfo.ident == IDENT_PC15_RSV ||
                                          fileInfo.ident == IDENT_NEW_TEL  || fileInfo.ident == IDENT_NEW_SCD  ||
                                          fileInfo.ident == IDENT_NEW_NOT  || fileInfo.ident == IDENT_NEW_CRD  ||
                                          ( ident == IDENT_PC15_IMG && fileInfo.id_version < 2) )) /* QT4 full block only */
                                            fileInfo.count = fileInfo.block_len - 1 ;
            } // next byte
            fileInfo.writing = false ;
            if (fileInfo.total < length) {
                printf(" Unexpected end of file, %lu bytes missing\n", length-fileInfo.total) ;
                error = ERR_FMT;
            }
            if (error > ERR_OK) break ;

            if ( fileInfo.ident == IDENT_NEW_BIN) { /* End and checksum reading */
                    error = ReadByteFromWav (order, &byte2, &fileInfo);
                    if (error != ERR_OK) break ;
                    if ( ( (fileInfo.debug & 0x0040) > 0 ) && (Qcnt == 0) )
                        printf(" EOF:(%02X)", (uchar) byte2 ) ; /* Mark 1 of 2, real 2. not in checksum */

                    if ( SHCc != 0 ) { /* End mark 1 included in SHC image */
                        error = WriteByteToFile (byte2, &dstFd);
                        if (error != ERR_OK) break ;
                    }

                    fileInfo.count = BLK_NEW - 1 ;
                    fileInfo.status = STAT_EOT ;
                    error = ReadByteSumFromWav (order, &byte, &fileInfo);

                    if (error > ERR_OK || byte == UNREAD) break ;
                    if ((byte2 << 8) + byte != BAS_NEW_EOFFF ) {  /* End of New, Ext File */
                        if ((fileInfo.debug & IGN_ERR_SUM) == 0 ) error = ERR_SUM ;
                        else count_errors( ERR_SUM, &fileInfo) ;
                    }
                    else error = ERR_EOT ;
            }
            if ( fileInfo.ident == IDENT_OLD_BIN || fileInfo.ident == IDENT_OLD_MEM
                                                 || fileInfo.ident == IDENT_OLD_MEM2) { /* End reading */
                    if (error==ERR_EOF || error==ERR_NSYNC) {
                        byte=BAS_OLD_EOF;  /* EOF mark was in old versions and YASM61860 not included */
                        if (Qcnt==0) printf(" Missing EOF mark %02X\n", (uchar) byte) ;
                        ++ fileInfo.wrn_cnt;
                    }
                    else {
                        error = ReadByteFromWav (order, &byte, &fileInfo);
                        if (error > ERR_OK || byte == UNREAD) break ;
                        if ( ( (fileInfo.debug & 0x0040) > 0 ) && (Qcnt == 0) )
                            printf(" EOF:(%02X)", (uchar) byte ) ; /* Mark not in checksum */
                    }
                    if ( SHCc != 0 ) { /* End mark included in SHC image */
                        error = WriteByteToFile (byte, &dstFd);
                        if (error != ERR_OK) break ;
                    }

                    if (byte != BAS_OLD_EOF ) {  /* End of Old File */
                        if ((fileInfo.debug & IGN_ERR_SUM) == 0 ) error = ERR_SUM ;
                        else count_errors( ERR_SUM, &fileInfo) ;
                    }
                    else error = ERR_EOT ;
            }

            break ;

        case IDENT_E_IMG :
        case IDENT_PC16_IMG : /*Saved PC-1600 device CAS: without option ",A" */

            fileInfo.writing  = true ; /* total write counter on */
            if (Qcnt == 0) printf (" Output format : Image Data%s\n", text) ;

            do {
                for ( ii = fileInfo.count ; ii < BLK_E_DAT ; ++ii ) {
                    /* Read a byte from the Wav file */
                    error = ReadByteSumFromWav (order, &byte, &fileInfo);
                    if (error != ERR_OK) break ;

                    if (fileInfo.writing) {
                        /* Write it in the destination file queue */
                        error = WriteByteToFile (byte, &dstFd) ;
                        if (error != ERR_OK) break ;

                        if (byte == 0x0D && ident == IDENT_PC16_IMG ) {
                            fileInfo.writing  = false ; // E-series false length
                            fillc = 0 ;
                        }
                    }
                    else if (byte == 0) ++fillc ;
                    else {
                        fileInfo.writing  = true ;
                        while ( fillc > 0 ) {
                            --fillc ;
                            error = WriteByteToFile (0, &dstFd) ;
                            if (error != ERR_OK) break ;
                        }
                        if (error != ERR_OK) break ;
                        error = WriteByteToFile (byte, &dstFd) ;
                        if (error != ERR_OK) break ;
                    }
                }
                if (error == ERR_OK && fileInfo.writing )
                    error = FindFreqAndSyncFromWav (&fileInfo) ;
                else if (error == ERR_OK ) error = ERR_EOT ;

            } while (error == ERR_OK) ;

            if (fileInfo.count ==0 && error < ERR_OK ) {
                if (error == ERR_EOF || error == ERR_NSYNC )
                    if (fileInfo.total >= length)
                        error = ERR_EOT ;
            }

            break ;


        case IDENT_PC16_CAS :
        case IDENT_E_ASC :

            fileInfo.writing  = true ; /* total write counter on */
            if (Qcnt == 0) printf (" Output format : Data%s\n", text) ;

            do {
                for ( ii = fileInfo.count ; ii < BLK_E_DAT ; ++ii ) {
                    /* Read a byte from the Wav file */
                    error = ReadByteSumFromWav (order, &byte, &fileInfo);
                    if (error != ERR_OK) break ;

                    if (byte == EOF_ASC) {
                        fileInfo.writing  = false ; /* total write counter on */
                        if ( ( (fileInfo.debug & 0x0040) > 0 ) && (Qcnt == 0) ) printf(" Meaningless data:");
                    }
                    else if (fileInfo.writing) {
                        /* Write it in the destination file queue */
                        error = WriteByteToFile (byte, &dstFd) ;
                        if (error != ERR_OK) break ;
                    }
                }
                if (error == ERR_OK && fileInfo.writing )
                    error = FindFreqAndSyncFromWav (&fileInfo) ;
                else if (error == ERR_OK ) error = ERR_EOT ;

            } while (error == ERR_OK) ;

            if (fileInfo.count ==0 && error < ERR_OK ) {
                if (error == ERR_EOF || error == ERR_NSYNC )
                    error = ERR_EOT ;
            }

            break ;


        case IDENT_PC121_DAT :
            fillc = 0 ;

        case IDENT_OLD_DAT :
        case IDENT_NEW_DAT :

        case IDENT_PC15_DAT :
            order = ORDER_INV ;

        case IDENT_QT_DAT :
        case IDENT_PC16_DAT :

            if (Qcnt == 0) printf (" Output format : Data%s\n", text) ;
            fileInfo.writing  = true ; /* total counter on */

            while ( error == ERR_OK ) {

                fileInfo.sum = 0 ;          /* Sum checked for data header */

                if (fileInfo.ident == IDENT_PC121_DAT) {
                    fileInfo.count = 0 ;
                    typeInfo.length = DATA_VARIABLE ;
                    typeInfo.dim1 = 0 ;
                    typeInfo.dim2 = 0 ;
                    typeInfo.itemLen = 0 ;
                }
                else {

                    if ( fileInfo.ident == IDENT_QT_DAT) {
                        fileInfo.count = fileInfo.block_len - DATA_HEAD_LEN - 2 ;
                        fileInfo.writing = false;
                        error = ReadByteSumFromWav(order, &byte, &fileInfo);
                        if (error != ERR_OK) break ;

                        if (byte == BAS_1500_EOF){ // && byte2 == BAS_1500_EOF
                            if ( ( (fileInfo.debug & 0x0040) > 0 ) && (Qcnt == 0))
                                    printf(" EOD:");

                            fileInfo.status = STAT_EOT;
                            fileInfo.usedat_len = 1;
                            error = ReadByteSumFromWav(order, &byte2, &fileInfo);
//                            error = ReadFillDataFromQtWav (order, &fileInfo) ;
                            if (error == ERR_EOF || error == ERR_NSYNC || error == ERR_OK){
                                if (byte2 == BAS_1500_EOF )
                                    error = ERR_EOT ;
                                else
                                    error = ERR_FMT ;
                            }
                            break ;
                        }
                        else {
                            ii= 0;
                            tmpS[ii++] = byte;
                            error = ReadByteSumFromWav(order, &byte2, &fileInfo);
                            if (error != ERR_OK) break ;

                            fileInfo.writing = true;
                            fileInfo.count = 0 ;
                            tmpS[ii] = (byte2 & 0x5F) ;
                            tmpS[ii] += (tmpS[ii] >0 && tmpS[ii] < 0x20) ? 0x20 : 0;
                            if (tmpS[ii] > 0 ) ++ii;
                            if ((byte2 & 0x20)>0) tmpS[ii++] = '$';
                            if ((byte2 & 0x80)>0) {
                                tmpS[ii++] = '('; tmpS[ii++] = '*'; tmpS[ii++] = ')';
                            }
                            tmpS[ii] =0;
                            if (Qcnt == 0) printf (" Quick-Tape data block with variable name: %s [%02X%02X]\n",
                                                    tmpS, (uint) byte, (uint)byte2 ) ;
                        }
                    }

                    /* Read the data block header from data wav file */
                    error = ReadHeadFromDataWav (order, &typeInfo, &fileInfo);
                    if (error != ERR_OK ) {
                        if ( fileInfo.total > DATA_HEAD_LEN && /* minimum 1 Data block written */
                            (error == ERR_EOF || error == ERR_NSYNC || error == ERR_EOT ))
                            error = ERR_EOT ;
                        break ;
                    }
                } // end if not PC121x data

                if (error != ERR_OK) break ;
                length = typeInfo.length;

                /* write the header back to file */
                byte = ( typeInfo.length >> 8 ) & 0xff;
                error = WriteByteToDatFile (byte, &dstFd) ;
                if (error != ERR_OK) break ;

                byte = typeInfo.length & 0xff;
                error = WriteByteToDatFile (byte, &dstFd) ;
                if (error != ERR_OK) break ;

                byte = typeInfo.dim1;
                error = WriteByteToDatFile (byte, &dstFd) ;
                if (error != ERR_OK) break ;

                byte = typeInfo.dim2;
                error = WriteByteToDatFile (byte, &dstFd) ;
                if (error != ERR_OK) break ;

                byte = typeInfo.itemLen;
                error = WriteByteToDatFile (byte, &dstFd) ;
                if (error != ERR_OK) break ;

                if ( length == DATA_VARIABLE ) {
                    /* Variable length block, read until end of data */
                    if (Qcnt == 0) printf (" Variable length block\n") ;

                    length = DATA_HEAD_LEN;
                    do {
                        /* Read a byte from the Wav file */
                        error = ReadByteSumFromWav (order, &byte, &fileInfo);
                        if (error > ERR_OK ) break ; /* Last Byte of Block with ERR_NOK/EOx ERR_NSYNC must written */
                        error_tmp = error ;

                        if (fileInfo.pause) fileInfo.status = STAT_EOT ;
                        else fileInfo.status = STAT_OK ;

                        if (fileInfo.ident == IDENT_PC121_DAT && (debug & WRT_NUL_DATA)==0 ){
                            /* cut data variable memory filled with zeros after fixed standard variables */
                            if (length >= DATA_HEAD_LEN + DATA_STD_LEN * 26){
                                if ( byte == 0 && ( length - DATA_HEAD_LEN) % DATA_STD_LEN == 0){
                                    fileInfo.writing =false;
                                    ++fillc;
                                }
                                else if (!fileInfo.writing && byte == 0) ++fillc;
                                else if (byte == DATA_EOF && ( length - DATA_HEAD_LEN) % DATA_STD_LEN == 0) {
                                    fileInfo.status = STAT_EOT ;
                                    fileInfo.writing =true;
                                    if (Qcnt == 0 && fillc > 0 )
                                        printf ("\nEmpty variables was removed from end, use -l 0x%05X for full image\n", WRT_NUL_DATA) ;
                                }
                                else {
                                    fileInfo.writing  = true ;
                                    while ( fillc > 0 ) {
                                        --fillc ;
                                        error = WriteByteToDatFile (0, &dstFd) ;
                                        if (error != ERR_OK) break ;
                                    }
                                    if (error != ERR_OK) break ;
                                }
                            }
                        }  // end if IDENT_PC121_DAT

                        /* Write it in the destination file queue */
                        if (fileInfo.writing) error = WriteByteToDatFile (byte, &dstFd) ;
                        if (error != ERR_OK) break ;

                        ++length;
                        if (error_tmp != ERR_OK) {
                                error = error_tmp ;
                                break ;
                        }
                    }
                    while ( ( length - DATA_HEAD_LEN -1 ) % DATA_STD_LEN != 0 || byte != DATA_EOF );
                    if (Qcnt == 0) printf ("...length with envelope: %ld\n", length) ;
                }
                else {
                    fileInfo.status = STAT_OK ;
                    length += 2;
                    if (Qcnt == 0) printf (" Data block + header, length: %lu\n", length) ;
                    for ( ii = DATA_HEAD_LEN ; ii < length ; ++ii ) {
                        /* Read a byte from the Wav file */
                        error = ReadByteSumFromWav (order, &byte, &fileInfo);
                        if (error > ERR_OK ) break ; // Last Byte with ERR_NOK/EOx must written
                        error_tmp = error ;

                        /* Write it in the destination file queue */
                        error = WriteByteToDatFile (byte, &dstFd) ;
                        if (error != ERR_OK) break ;

                        if (error_tmp != ERR_OK) {
                                error = error_tmp ;
                                break ;
                        }
                        /* Force reading of last checksum after next byte
                           for string data blocks, if the itemLen != 8 */
                        if ( ii + 2 >= length ) {
                            if ( fileInfo.ident == IDENT_PC15_DAT ) fileInfo.count = BLK_OLD - 1 ;
                            else if ( fileInfo.ident != IDENT_PC16_DAT && fileInfo.ident != IDENT_QT_DAT )
                                      fileInfo.count = BLK_OLD_SUM - 1 ;
                            fileInfo.status = STAT_EOT ;
                        //  fileInfo.synching = 1 ;
                        }
                    } //next byte of data block
                }

                /* FindFreqAndSyncFromWav was called automatic after reading last byte before 1.61b7d */
                if (fileInfo.ident == IDENT_PC121_DAT) {
                        error = ERR_EOT ;
                        break ; /* one variable length block only */
                }
                if (error == ERR_NSYNC || fileInfo.ident == IDENT_PC16_DAT || fileInfo.ident == IDENT_QT_DAT ) {
                        error = FindFreqAndSyncFromWav (&fileInfo) ;
                        if (error != ERR_OK ) {
                            if (error == ERR_EOF || error == ERR_NSYNC )
                                error = ERR_EOT ;
                            break ;
                        }
                }
            } // wend of data blocks

            break ;


        case IDENT_PC15_BAS :
        case IDENT_PC15QTBAS :
        case IDENT_QT_BAS :

        case IDENT_PC16_BAS : /*was set before select in ReadHeadFromBinWav */
        case IDENT_E_BAS :

        case IDENT_PC1211  :
        case IDENT_OLD_BAS :
        case IDENT_OLD_PAS :
            if (pcgrpId == GRP_OLD || pcgrpId == IDENT_PC1211) apostrophe = ApostOld ;

        case IDENT_NEW_BAS :
        case IDENT_NEW_PAS :
        case IDENT_NEW_CSL :
        case IDENT_EXT_BAS :
        case IDENT_EXT_PAS :
            fileInfo.writing  = true ; /* total write counter on */

            if (fileInfo.type == TYPE_RSV && fileInfo.ident != IDENT_PC15_BAS
                                          && fileInfo.ident != IDENT_PC16_BAS
                                          && fileInfo.ident != IDENT_E_BAS) {
                /* RSV for PC-1500 has a separate ID but other are compatible with IMG of BASIC */
                if (Qcnt == 0) printf (" Output format : Forced to Binary RSV-Data%s\n", text) ;

                if (pcId < 1280 && pcId >= 1100) rsvmax = rsvmin ;
                else rsvmax = 144 ;

                for ( ii = 0 ; ii < rsvmax + 1 ; ++ii ) { //ToDo Rewrite this code for RSV
                    if ( ii == rsvmax &&     /* Reserve data of EXT/NEW_BAS max. 144 bytes */
                         fileInfo.ident != IDENT_PC1211 &&
                         fileInfo.ident != IDENT_OLD_BAS &&
                         fileInfo.ident != IDENT_OLD_PAS  ) {

                            fileInfo.writing = false ; /* no end mark written */
                            error = ReadByteFromWav (order, &byte, &fileInfo);
                            if (error != ERR_OK) break ;
                            if ( ( (fileInfo.debug & 0x0040) > 0 ) && (Qcnt == 0) ) printf(" EOF:%02X", (uchar) byte);
                            /* 2. EOF and Last Checksum */
                            fileInfo.count = BLK_NEW - 1 ;
                            fileInfo.status = STAT_EOT ;
                    }

                    /* Read a byte from the Wav file */
                    error = ReadByteSumFromWav (order, &byte, &fileInfo);
                    if (error > ERR_OK) break ;

                    if ( ii == rsvmin && byte == BAS_NEW_EOF && pcId < 1280
                        && fileInfo.writing == true ) {  /* Reserve data of PC-126x max. 48 bytes */

                            /* unexpected EOF */
                            if ( ( (fileInfo.debug & 0x0040) > 0 ) && (Qcnt == 0) ) printf(":EOF");
                            rsvmax = rsvmin ;
                            --fileInfo.total;
                            fileInfo.sum = fileInfo.sum_before;
                            fileInfo.writing = false ;      /* no end mark written */

                            /* 2. EOF and Last Checksum */
                            fileInfo.count = BLK_NEW - 1 ;
                            fileInfo.status = STAT_EOT ;
                            error = ReadByteSumFromWav (order, &byte, &fileInfo);
                            if (error > ERR_OK) break ;
                    }

                    if ( (fileInfo.ident == IDENT_PC1211)  ||
                         (fileInfo.ident == IDENT_OLD_BAS) ||
                         (fileInfo.ident == IDENT_OLD_PAS) ) {
                        if (ii == rsvmin -1 ) {
                                fileInfo.writing = false ;
                                fileInfo.status = STAT_EOT ; /* OLD_BAS RSV 48 bytes */
                        }
                        if (ii >= rsvmin ) {
                            if ( byte != BAS_OLD_EOF ) printf(" EOF mark missed%s\n", text) ;
                            else if ( error < ERR_OK) error = ERR_EOT ;
                            break;
                        }
                    } // end if OLD RSV
                    else if (!fileInfo.writing) { /* NEW RSV End */
                        if ( error < ERR_OK) error = ERR_EOT ;
                        continue; /* don't write EOF mark */
                    }
                    else if (error != ERR_OK) break ;

                    error = WriteByteToFile (byte, &dstFd) ;
                    if (error != ERR_OK) break ;
                }
            }   // end RSV
            else if (IMBc != 0 && (ident == IDENT_NEW_BAS || ident == IDENT_EXT_BAS ||
                                   ident == IDENT_NEW_CSL  )) {
                if (Qcnt == 0)
                        printf (" Output format : Forced to Binary block (not lines)%s\n", text) ;
                fileInfo.check_end  = true ;
                do {
                    error = ReadByteSumFromWav (order, &byte, &fileInfo);
                    if (error > ERR_OK) break ;

                    if (byte == BAS_NEW_EOF) {

                        position = stell( &fileInfo ) ; /*save position in source file */
                        if (position <= 0) {
                            printf ("\n%s:ByteSum - Can't ftell the wav file\n", argP) ;
                            return ( ERR_FILE ) ;
                        }
                        error = ReadByteFromWav (order, &byte2, &fileInfo);

                        /*rewind to position before last byte read */
                        error = sseek (&fileInfo, position, SEEK_SET) ;
                        if (error != ERR_OK) {
                            printf ("\n%s:ByteSum - Can't seek the file: %ld\n", argP, position) ;
                            error = ERR_FILE ;
                            break ;
                        }

                        if (byte2 == BAS_NEW_EOF) { /* constellation of "checksum bug" is NOT supported by this way */
                            fileInfo.sum = fileInfo.sum_before ; /* remove 1. EOF from checksum */
                            fileInfo.count = BLK_NEW - 1 ;
                            fileInfo.status = STAT_EOT ;
                            error = ReadByteSumFromWav (order, &byte2, &fileInfo);
                            if (error <= ERR_OK && byte2 != UNREAD) error = ERR_EOT ;
                            break ;
                        }
                    }
                    error = WriteByteToFile (byte, &dstFd) ;
                    // if (error != ERR_OK) break ;

                } while (error == ERR_OK) ;
            } //end IMB new ext
            else {
                if (Qcnt == 0) {
                    if (fileInfo.type == TYPE_IMG)
                        printf (" Output format : Forced to Binary (line by line)%s\n", text) ;
                    else if (fileInfo.utf8 == 1)
                        printf (" Output format : UTF-8%s\n", text) ;
                    else if (fileInfo.utf8 == UTF8_ASC)
                        printf (" Output format : ASCII for later serial transfer %s\n", text) ;
                    else if (fileInfo.utf8 == UTF8_DOS)
                        printf (" Output format : DOS-US 437 for older DOS based Software %s\n", text) ;
                    else if (fileInfo.utf8 == UTF8_ESC)
                        printf (" Output format : ASCII with masks '\\' for some special codes %s\n", text) ;
                    else if (fileInfo.utf8 == UTF8_ESCX)
                        printf (" Output format : ASCII with masks for '\\' (special) and '\\x' (extended) chars %s\n", text) ;
                    else
                        printf (" Output format : ASCII [reversible with Bas2img] %s\n", text) ;
                }
                do {
                    /* Read the Basic line from the Wav file */
                    if (ident == IDENT_NEW_CSL)
                         error = ReadLineFromAsmNWav (order, length, text, &llength, &fileInfo);
                    else error = ReadLineFromBasWav (order, length, imgbgn, text, &llength, &fileInfo);

                    if ( error != ERR_OK && (error != ERR_NSYNC || fileInfo.type == TYPE_IMG)) break ;
                    error_tmp = error ; /* if error then write the last basic line after ERR_NSYNC */

                    if (fileInfo.type == TYPE_IMG) {
                        for ( ii = 0 ; ii < llength ; ++ii ) {
                            error = WriteCharToFile ( text[ii], &dstFd) ;
                            if (error != ERR_OK) break ;
                        }
                    }
                    else {
                        /* Write it in the destination file */
                        error = WriteStringToFile (text, &dstFd) ;
                        if (error != ERR_OK) break ;
                    }
                    error = error_tmp ;
                    if (error != ERR_OK) break ;
                    /*  count 0, EOT  managed in ReadLine */

                } while (1) ;
            }  // end basic
            error_tmp = error ;

            if ( SHCc != 0 && type == TYPE_IMG) { /* End marks included in SHC image */
                if ( pcgrpId == GRP_NEW || pcgrpId == GRP_EXT ) {
                        error = WriteByteToFile (BAS_NEW_EOF, &dstFd);
                        if (error != ERR_OK) break ;
                }
                if ( pcgrpId == GRP_OLD) error = WriteByteToFile (BAS_OLD_EOF, &dstFd);
                else error = WriteByteToFile (BAS_NEW_EOF, &dstFd);
                if (error != ERR_OK) break ;
            }
            else if (SHAc != 0) {
                error = WriteByteToFile (EOF_ASC, &dstFd);
                if (error != ERR_OK) break ;
                error = WriteByteToFile (EOF_ASC, &dstFd);
                if (error != ERR_OK) break ;
            }
            else if ( (fileInfo.debug & BAS_EOF_INCL ) > 0 ) {
/* RSV of series 1234 also an end mark in the RAM, but here is not supported */
                if (type == TYPE_IMG || type == TYPE_TXT) {
                        eof_mark = BAS_NEW_EOF ;
                        eof_mark_write = true ;
                }
                else if (type == TYPE_BAS || type == TYPE_ASC ) {
                        eof_mark = EOF_ASC ;
                        eof_mark_write = true ;
                }
                if ( eof_mark_write == true ) {
                        if (Qcnt == 0) printf ("The requested end mark %02X is appended to the file.\n", eof_mark );
                        error = WriteByteToFile (eof_mark, &dstFd); /* EOF in RAM or for Asc file */
                        if (error != ERR_OK) break ;
                }
            }
            error = error_tmp ;

            if (fileInfo.count ==0 && error < ERR_OK ) {
                if (error == ERR_EOF || error == ERR_NSYNC )
                    error = ERR_EOT ;
            }

            break ;


        case IDENT_RAW :
            if (Qcnt == 0) printf (" Output format : Forced to Binary raw data%s\n", text) ;
            while ( error == ERR_OK ) {
                        byte = UNREAD;
                        error = ReadByteFromWav (order, &byte, &fileInfo);
                        if (error > ERR_OK || byte == UNREAD ) {
                                /* Raw format can not find structural EOT */
                                if (error < ERR_OK )  error = ERR_OK ;
                                break ;
                        }

                        if ( ( (fileInfo.debug & 0x0040) > 0 ) && (Qcnt == 0) )
                            printf(" %02X", (uchar) byte);

                        error_tmp = error ;
                        // Write it in the destination file queue
                        error = WriteByteToFile (byte, &dstFd) ;
                        if (error != ERR_OK) break ;
                        ++ fileInfo.total ;

                        if (error_tmp != ERR_OK) {
                                error = error_tmp ;
                        }
                if (error == ERR_NSYNC) { /* needed for data files */
                    error = FindFreqAndSyncFromWav (&fileInfo) ;
                }
            }

            if (error != ERR_OK ) {
                if (error == ERR_EOF || error == ERR_NSYNC || error == ERR_SYNC )
                    error = ERR_EOT ;
            }
            break ;


        default :
            printf ("\n%s:Convert: Unknown Ident %lu\n", argP, ident) ;
            error = ERR_FMT;
            break ;
        } // end switch ident

        if ( pcgrpId == IDENT_PC1500 && IMGc == 0) { /* End mark reading */
                if (error==ERR_EOF || error==ERR_NSYNC) { /* EOF mark not included */
                    byte=EOF_15;
                    if (Qcnt==0) printf(" Missing EOT mark %02X\n", (uchar) byte) ;
                    if ((debug & IGN_ERR_SUM) >0 ) error = count_errors( ERR_SYNC, &fileInfo) ;
                    else error = ERR_SYNC;
                }
                else if ((fileInfo.ident == IDENT_PC15QTBAS || fileInfo.ident == IDENT_PC15QTBIN)
                           && fileInfo.id_version == 1 ) { /* in QTAPE 1 */
                    error = ReadByteFromWav (order, &byte, &fileInfo);
                    if (error > ERR_OK || byte == UNREAD) break ;

                    error = ReadByteFromWav (order, &byte2, &fileInfo);
                    if (error > ERR_OK || byte2 == UNREAD) break ;

                    if ( ( (fileInfo.debug & 0x0040) > 0 ) && (Qcnt == 0) )
                            printf(" EOT:(%02X%02X)", (uchar) byte, (uchar) byte2 ) ; /* last bytes */

                    byte  = byte<<4 & 0xF0 ; /* 2x F5 ->55 */
                    byte |= byte2   & 0x0F ;
                }
                else if (fileInfo.ident == IDENT_PC15_DAT || order == ORDER_Q) {
                    /* read from ReadHeadFromDataWav, in QTAPE 4 mark EOF_15 follows every Checksum */
                    byte=EOF_15;
                    if ( ( (fileInfo.debug & 0x0040) > 0 ) && (Qcnt == 0) )
                            printf(":EOT") ;
                }
                else {
                    error = ReadByteFromWav (order, &byte, &fileInfo);
                    if (error > ERR_OK || byte == UNREAD) break ;
                    if ( ( (fileInfo.debug & 0x0040) > 0 ) && (Qcnt == 0) )
                            printf(" EOT:(%02X)", (uchar) byte ) ; /* last byte */
                }
                /* if ( SHCc != 0 ) { //End mark included in SHC image
                    error = WriteByteToFile (byte, &dstFd);
                    if (error != ERR_OK) break ;
                } */

                if (byte != EOF_15 ) {  /* End of PC-1500 File */
                        if ((fileInfo.debug & IGN_ERR_SUM) == 0 ) error = ERR_SUM ;
                        else count_errors( ERR_SUM, &fileInfo) ;
                }
                else if (error <= ERR_OK) error = ERR_EOT ;
        }
        if ((error != ERR_OK || (fileInfo.debug & 0xF00)>0) &&
            error != ERR_EOT) DebugReadEndFromBinWav (order, &fileInfo);

    } while (0) ; // end of ConvertWavToBin main part
    if ( error == ERR_EOT) error = ERR_OK ;
    error_tmp = error ;

    if ( error != ERR_OK && fileInfo.err_cnt < ERR_CNT_MAX ) ++fileInfo.err_cnt ; /* last error not counted */

    if (Qcnt == 0) {
        if ( (fileInfo.debug & DEBUG_TRACES)>0 ) {
            printf ("\n");
            if (IMGc==0 && TAPc==0 && KHXc ==0) {
                if (fileInfo.wavtime > 0.1)
                    printf (" Last complete byte was read before the position %.5lf s (%i:%2.1lf)\n", fileInfo.wavtime,
                              (int) fileInfo.wavtime /60, fileInfo.wavtime-(double)(60*((int)fileInfo.wavtime/60)));
            }
            else if (fileInfo.position > 0) printf (" Last byte was read at the position %ld\n", fileInfo.position);
        }

        if (fileInfo.total > 0 )  printf (" Total bytes read (without header and sums): %ld", fileInfo.total );
        else printf (" No data could be read");
        if ( (fileInfo.debug & DEBUG_TRACES)==0) {
            if (IMGc==0 && TAPc==0 && KHXc ==0) {
                if( fileInfo.wavtime > 0.1) printf (" until %.3lf s", fileInfo.wavtime);
            }
            else if (fileInfo.position > 0) printf (" to pos. %ld\n", fileInfo.position);
        }
        if (fileInfo.wrn_cnt > 0 && (fileInfo.debug > 0 || fileInfo.err_cnt == 0) )
                                  printf (" with %ld warning(s)", fileInfo.wrn_cnt );
        if (fileInfo.err_cnt > 0) printf (", %ld transmission error(s)!\n", fileInfo.err_cnt );
        else printf ("\n");
    }

    if (Mcnt > 0 && parFd != NULL) {

        if (eof_mark_write == true ) {
            strncpy(text, "endmark=", cLL-1) ;
            sprintf(ntext, "%u\r\n", eof_mark);
            strncat(text, ntext, cLL-9) ;
            error = WriteStringToFile (text, &parFd) ;
            if (error != ERR_OK) error_tmp = ERR_FILE ;
        }
        if (fileInfo.total > 0 ) {
            strncpy(text, "total=", cLL-1) ;
            sprintf(ntext, "%lu\r\n", fileInfo.total);
            strncat(text, ntext, cLL-7) ;
            error = WriteStringToFile (text, &parFd) ;
            if (error != ERR_OK) error_tmp = ERR_FILE ;
        }
        if (error_tmp != ERR_OK ) {
            strncpy(text, "error=", cLL-1) ;
            sprintf(ntext, "%i\r\n", error_tmp);
            strncat(text, ntext, cLL-7) ;
            error = WriteStringToFile (text, &parFd) ;
            if (error != ERR_OK) error_tmp = ERR_FILE ;
        }
        if (fileInfo.err_cnt > 0 ) {
            strncpy(text, "errors=", cLL-1) ;
            sprintf(ntext, "%lu\r\n", fileInfo.err_cnt);
            strncat(text, ntext, cLL-8) ;
            error = WriteStringToFile (text, &parFd) ;
            if (error != ERR_OK) error_tmp = ERR_FILE ;
        }
        if (fileInfo.wrn_cnt > 0 ) {
            strncpy(text, "warnings=", cLL-1) ;
            sprintf(ntext, "%lu\r\n", fileInfo.wrn_cnt);
            strncat(text, ntext, cLL-10) ;
            error = WriteStringToFile (text, &parFd) ;
            if (error != ERR_OK) error_tmp = ERR_FILE ;
        }
        text[0]='\0' ;

     /* Close the parameter file */
        error = fclose (parFd) ;
        if (error != ERR_OK) {
            printf ("\n%s: Can't close the parameter file\n", argP) ;
            error_tmp = ERR_FILE ;
        }
    }

     /* Close the destination file */
    if (error_tmp != ERR_ARG && dstFd != NULL) {
        error = fclose (dstFd) ;
        if (error != ERR_OK) {
            printf ("\n%s: Can't close the destination file\n", argP) ;
            error_tmp = ERR_FILE ;
        }
    }

   /* Close the source file */
    if (fileInfo.ptrFd != NULL) {
        error = fclose (fileInfo.ptrFd) ;
        if (error != ERR_OK) {
            printf ("\n%s: Can't close the source file\n", argP) ;
            error_tmp = ERR_FILE ;
        }
    }

    error = error_tmp ;
    if (error == ERR_OK) error = fileInfo.err_exit ;

    if ( Qcnt == 0 && (error == ERR_NSYNC || error == ERR_SYNC || error == ERR_ORD || error == ERR_SUM || error == ERR_MULTI )) {
                if (fileInfo.pre_amp == 16) printf
                    ("\n%s: The input level of this recording is low.\n Optimize your audio setup to avoid errors.\n", argP );
                else if (fileInfo.pre_amp > 16) printf
                    ("\n%s: The input level of this recording is too low.\n Use microphone amplification!\n", argP );
    }
    if (Xcnt==EXIT_TYPE) exit( fileInfo.subtype ) ;
    else if (Xcnt==EXIT_IDENT) exit( fileInfo.ident) ;
    else if (Xcnt==EXIT_PCGRPID) exit( pcgrpId ) ;
    else
       return (error);
}

/* Remove BOM if was written by UTF-8 editor*/
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
	  int  igot = 0;
	 char  cgot = 0;
 	 bool  ineol = false;
	 bool  afteol = false;
     uint  line_cntR = *ptrLine_cnt = *ptrLine_cntN;

	while ( ( igot != EOF ) && ( afteol != true ) && ( cin < maxchars ) ) {
		igot = getc( datei );
		if ( igot != EOF ) {
			cgot = igot;
			if ( ( cgot != '\x0D' ) && ( cgot != '\x0A' ) ) {
				if (ineol != true) {
					retstring[cin++] = cgot;
				}
				else {
					ungetc( igot, datei );
					afteol = true;
				}
			}
			else { /* retstring[cin] = '\0'; Manfred Nosswitz, Bas2img 2011 */
				if ( cgot == '\x0A') ++(*ptrLine_cntN); /* line counter with last empty lines */
				else if ( cgot == '\x0D') ++line_cntR ;
				ineol = true;
			}
		}
	}
	retstring[cin] = '\0'; /* Finish string */
    if ( line_cntR > *ptrLine_cntN) *ptrLine_cntN = line_cntR ;
	if ( ( cin == 0 ) && ( igot == EOF ) )
	  return NULL;
	else {
      ++(*ptrLine_cnt); /* line counter without last empty lines */
	  return retstring;
    }
}


int ReadCodepointsFromFile (char*  ptrCodeSpaceFile) /* Characters code file string */
{ /* globals    uint code_cnt = 0  ;  number of tokens from character code definition file
    char chrstring[cMAXNBCH][cLCH] ;  ushort codepoint [cMAXNBCH] ; */

    char    line_buffer[cLL] = "" ,
            key_buffer[7] = "0x",
            *ptrErr, *ptrToken, *ptrToken2 ;
    uint    codeval = 0 ;
    uint    code_table = 0 ;
    uint    line_cnt = 0, line_cntN = 0 ;
    int     error_tmp, error = ERR_OK ;
    FILE*   ptrFk = NULL ;      /* codepoint file pointer */
    bool    ign_long_codes = false, has_placeholders = false;

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

            if (*ptrToken == '[') has_placeholders = true ;
            else {
                /* convert token code from hex string to binary */
                strncpy (&key_buffer[2], ptrToken, 4) ;
                codeval = strtoul( key_buffer, &ptrErr, 0) ;
                if (*ptrErr != 0) {
                    printf ("%s: Code point '%s' is not a valid hex in line %i of\n file %s.\n", argP, ptrToken, line_cnt, ptrCodeSpaceFile) ;
                    error = ERR_FMT ;
                    break ;
                }
                else if (codeval > 0xFFFF || (codeval & 0xFF) == 0) {
                    printf ("%s: Code point %s value is out of range in line %i of file %s.\n", argP, ptrToken, line_cnt, ptrCodeSpaceFile) ;
                    error = ERR_FMT ;
                    break ;
                }
                else {
                    code_table = codeval >> 8 & 0xFF ;
                    if (codeval > 0xFF) {
                        if (pcgrpId == GRP_E) {
                            if ((pcMode & 8) >0) {
                                if (code_table > Kanji_Code_Max && code_table < KANJI_CODE_MAXE +1)
                                    Kanji_Code_Max = KANJI_CODE_MAXE ; /* extend area for E500K */
                                else if (code_table > KANJI_CODE_MIN2 -1 && code_table < KANJI_CODE_MAX2 +1)
                                    pcMode |= 0x10 ;  /* activate 2. area */
                            }
                        }
                        if (!(   (pcgrpId == GRP_NEW && code_table == BAS_EXT_CODE) || /* 2. char table Katakana of BAS_NEW */
                               ( (pcgrpId == GRP_16 || pcgrpId == GRP_EXT || pcgrpId == GRP_E ) &&
                                                    KANJI_CODE_MIN  -1 < code_table && code_table <= Kanji_Code_Max ) ||
                               (pcgrpId == GRP_E && KANJI_CODE_MIN2 -1 < code_table && code_table < KANJI_CODE_MAX2 +1 )
                             )
                           ) ign_long_codes = true ;
                    }
                    codepoint[code_cnt] = codeval;
                    strncpy(chrstring[code_cnt++], line_buffer, cLCH-1);
                }
            } // no placeholder
        }
        else printf ("%s Missing '=' in file %s, line %i.\n", argP, ptrCodeSpaceFile, line_cnt) ;
    }
    if (ign_long_codes)
        if (Qcnt == 0) printf ("%s ignores long code points of %s \n", argP, ptrCodeSpaceFile) ;
    if (has_placeholders)
        if (Qcnt == 0) printf ("%s ignores place holders of %s \n", argP, ptrCodeSpaceFile) ;

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


void PrintHelp (char* argH)
{
  if (strcmp (argH, "l")==0 || strcmp (argH, "1")==0 || strcmp (argH, "level")==0 || strcmp (argH, "debug")==0 ||
      strcmp (argH, "d")==0 || strcmp (argH, "device")==0 || strcmp (argH, "raw")==0) {
                       /* 1         2         3         4         5         6         7         8 */
              /* 12345678901234567890123456789012345678901234567890123456789012345678901234567890 */
	printf ("%s -l, --level=VALUE : Special and debug options, 2-times\n", argP) ;
	printf ("                            a hexadecimal integer (0x____) or sum of it\n") ;
	printf (" 0x800  Ignore false checksums and continue: Result must be corrected manually.\n") ;
	printf (" 0x1000 Depress base frequency tuning and use fixed base frequency only\n") ;
	printf (" 0x2000 Use flat method of Wav2Bin 1.5 to detect H/L-transitions, no amplitudes\n") ;
	printf (" 0x4000 No amplitudes based gain, count amplitudes only\n") ;
	printf (" 0x8000 No analysis of wav file, no pre-amplification\n\n") ;
	printf (" 0x80   Print lines of text written (BASIC only)   0x200: CR starts a new line \n") ; /*CR_DEF_EOL*/
	printf (" 0x40   Print all Bytes and (Checksum_readed=Sum_calculated) - see also Bin2wav\n") ;
	printf (" 0x400  ByteList + Wav Time(after the Byte) \n") ;
	printf ("        More options exist for low level debugging - see the source code\n") ;
  	printf (" 0x80000 BASIC commands of BMC MC-12 are used (BASIC of PC-1500/1600 only)\n\n") ;
	/*  Debug Wav2bin -l 1:Transitions/Bit (or set Debug_Position and uncomment code)
                            *s(sync start bit)s +s(. sync high )s  -s(o sync low )s
                            q{ quater }q        ... skip bits
                            *sk(skip QT bits)sk     Trans<Amps>, if equal, then only one value
                         2:SyncBits (only Series 1100-1500)
                         4:ReadBits (in Nibbles) 8=Skiped Bits Nb
                     0x10 Nibble    (only Series 1100-1500)
                     0x20 Byte/Sum 0x40 Byte<Sum> 0x80=TEXT 0x100 sync process
                     0x400 ByteList+Wav Time (after Byte) and 1500 Debug after End, 0x200 Lines end with CR
                     0x10000 LowLevel traces and sample(above debug_time) 0x20000 with Byte Position
                        ~Sample value > +- Transformed rated value
                        ^ high amp      v low amp
                     IGN_ERR_SUM = 0x800 ignore false checksums and continue
                     BASE_FRQ_FIX = 0x1000 use fixed base frequency only, no tuning
                     TRANS_OLD = 0x2000 Use old definitions of TRANS_HIGH and TRANS_LOW
                     NO_RATE_AMP = 0x4000 No amplitudes based gain, count amplitudes only
                     NO_PRE_AMP = 0x8000 No Analysis, no Pre-Amplification of wav file
                     WRT_NUL_DATA = 0x40000 Write zero variable data at end of file PC121_DAT
                     BMC_TOKEN = 0x80000 Priority for token of BMC MC-12 (not Tramsoft Tools4 or CE-1600P)
                     0x100000 KeysFromFileOnly, Deactivate build in token, use loaded tokens only
                     BAS_EOF_INCL = 0x200000 -e Add EOF mark to an image file, can used with IMG for BIN
                     0xC00000 CnvCmdLor, convert 0x400000 characters or 0x800000 commands to lower cases
                     DEL_REMC = 0x1000000 Delete a comment character at the beginning of each line
                     DEL_APST = 0x2000000 Delete an apostrophe at the beginning of each line
                     0x4000000 DelSpcAfterRem, Delete spaces after REM command, for CE-158
                     */
	printf ("-k, --keywords=KeywordFile (only for special hardware, maximum use: 3 times)\n") ;
	printf ("-o, --codepoints=CodepointFile (code points def. file, maximum use: 2 times)\n") ;
	printf ("-m, --parameters=ParametersFile : write header data to file -x --exit header\n") ;
	printf ("-t  Write tap-format or debugging: --type=tap, raw, rawdat (quaters swapped)\n") ;
	printf ("    =imb (BASIC img, not line by line), =def (def-keys of PC-1500)\n\n") ;
	printf (" Device specific filters  -dBIN : No filter, for synthetic wav like Bin2wav\n") ;
	printf (" --device=CAS2: For wav made directly from recorder, better DC compensation\n") ;
	printf (" --device=EMU : For wav from emulator via system sound, set cspeed and pc\n") ;
	printf (" --device=AIR : PC-1245-1475 buzzer -> Mic (tricky, clear 2 kHz wavs only)") ;
  }
  else if (strcmp (argH, "r")==0 || strcmp (argH, "2")==0 || strcmp (argH, "recording")==0) {
                       /* 1         2         3         4         5         6         7         8 */
              /* 12345678901234567890123456789012345678901234567890123456789012345678901234567890 */
	printf ("\nHow to record the wav file from a Pocket Computer?     Also read the manual!\n") ;
	printf ("The recording must consistently contain a clear, undisturbed and strong signal.\n") ;
	printf ("You may use new batteries and avoid the use of an old power supply (mains hum).\n") ;
	printf ("Plug a power supply out before and then in the CE. Avoid a long audio cable.\n") ;
	printf ("Connect only the microphone plug, not the headphone in case of effects.\n") ;
//	printf ("Signal monitoring, cables and low levels may generate uncorrectable bit errors.\n") ;
	printf ("If you must digitize from cassette, use a cassette deck with a flutter < 3%%.\n\n") ;
	printf ("Record PC-1500 with a minimum sample rate of 11025 Hz, other with 22050 Hz.\n") ;
	printf ("For sound from modified Pocket Computers with a hardware speedup switched on:\n") ;
	printf ("use 48000 Hz or more and set the %s -cspeed parameter +-5%% accurate.\n", argP) ;
	printf ("Record high levels with 8-bit. If not supported or LOW level: Record 16-bit!\n") ;
	printf ("Record monophonic. If the software does not support this, then record stereo.\n") ;
	printf ("Unplug and plug again the microphone plug in the sound card to select the port.\n") ;
	printf ("Pre-intensification should be switched on for the microphone in the sound card.\n") ;
	printf ("Record with higher level but not with 95%% above, no mixer, only DC filter.\n") ;
	printf ("If the level is only less than 5%%, then you must use a good mic preamps.\n\n") ;
	printf ("First start CSAVE or cassette, wait a second for stable sound, then record it.\n") ;
	printf ("Normally dont cut the lead in! If necessary, then cut direct on a sample point:\n") ;
	printf ("Preceding speech or other sound can preclude the detection of base frequency.\n") ;
	printf ("Before you normalize low sound, cut the noise minimal 10 ms after the signal.\n") ;
	printf ("Dont convert the sample rate! For sound from emulator see speed and set -dEMU.\n") ;
	printf ("If you get constant errors from a tape, use -dCAS and debug levels to find the\n") ;
	printf ("wav time. Normalization and wav editing was tested with SoX and Audacity.") ;
  }
  else {
                       /* 1         2         3         4         5         6         7         8 */
              /* 12345678901234567890123456789012345678901234567890123456789012345678901234567890 */
	printf ("\nUsage: %s [Options] SrcFile(.wav/tap/img) [DstFile(.typ)]\n", argP) ;
	printf ("SrcFile           : WAV file (PCM, normalized, recommended is mono 16-bit with\n") ;
	printf ("                    a minimum sample rate from 22050 Hz to 48 kHz or original\n") ; // (PC-1500 >=11025 Hz)
	printf ("                    wav files made by Bin2Wav), also an binary IMaGe, TAP file\n") ;
	printf ("DstFile           : Destination file (BASIC-program text or Binary image file)\n") ;
	printf ("Options               -s, --start (default: 0.0 seconds) time of 1. sync signal\n") ;
	printf ("-t, --type=TYPE   : Destination file type\n") ;
	printf ("                     bas  BASIC-program text file (default), sha  shc Transfile\n") ;
	printf ("                     img  Binary image file (BASIC program, machine code, data)\n") ;
	printf ("                     rsv  ReSerVe mode data (image),   tap  Emulator raw format\n") ;
	printf ("-p, --pc=NUMBER   : SHARP pocket computer, (for BASIC-program text,\n") ;
	printf ("                     is required for 1421, 1600 Mode 1, optionally for other)\n") ;
	printf ("-c, --cspeed=VALUE: Ratio of CPU frequency to original (use it with a modified\n") ;
	printf ("                     Pocket Computer, if speedup was switched on, 0.94 to 2.7)\n") ;
	printf ("-u, --utf8=TYPE   : Convert special characters (only for BASIC-program text)\n") ;
	printf ("       default -u : (no) to ASCII transcription with brackets [reversible]\n") ;
	printf ("   without option : yes, BOM: to UTF-8,  2esc: Escape seq,  2dos: to DOS-US\n") ;
	printf ("                     2asc to ASCII transcription for later serial transfer\n") ;
	printf ("-w, --width=VALUE : Minimum width of line number (only for BASIC-program text)\n") ;
	printf ("  | VAL[:|;|,|.|!]   2 to 10 (default: 5_), indentation off: 0, =VAL; for (: )\n") ;
	printf ("-q, --quiet       : Quiet mode (No display output)     2nd use: -w space_level.\n") ;
	printf ("    --tap --khx   : from emulator tap, khx --img=OFFSET:Image (Src file no wav)\n") ;
	printf ("    --version     : Display version information  -e, --endmark : write end mark\n") ;
	printf ("    --help        : Display this, more:  --help=r:recoding FAQ, =l:level(debug)") ;

  }
  #ifdef __APPLE__
    /* Mac specific here, not for _WIN32 */
    printf ("\n") ;
  #endif
  #ifdef __linux__
    /* For Linux shell */
    printf ("\n") ;
  #endif
  exit( EXIT_SUCCESS );
}


/* Copying conditions: GNU Lesser General Public License version (GPLv3), see COPYING.LESSER and this supplement:
   You may not use any code from the "Pocket Tools for SHARP Pocket Computers" project if you do not name
   the original authors in the code and documentation or if you remove this notice or the following function. */
void PrintVersion (void)
{   char argPU[cLPF] = "" ;
	strcpy(argPU, argP) ;
	printf ("%s (%s) version: %s for Pocket Tools 2.1, %s \n", argP, strupr(argPU), PVERSION, PDATE ) ;
	if (!Qcnt) {
	printf ("Author: Pocket -> www.pocketmuseum.com\n") ; /* Please do not remove */
	printf ("        2013-2022 Torsten Muecker\n") ;      /* Please do not remove */
	printf ("        for complete list see the manual and the source code\n") ;
	printf ("This is free software; see the source for copying conditions. There is NO\n") ;
    printf ("warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE,\n") ;
    printf ("to the extent permitted by law.\n") ;
	}
	exit( EXIT_SUCCESS );
}


void MoreInfo (int error)
{	printf("%s: '%s --help' gives you more information\n", argP, argP);
	exit( error ); // for debugging set here a breakpoint and at end of of main() before return(error) and return(EXIT_SUCCESS)
}


int main( int argc, char **argv )  /* (int argc, char* argv[]) */
{	/* 0=SrcFile 1=[DstFile] 2=[-t] 3=[-p] 4=[-d] 5=[-c] 6=[-u] 7=[-w] 8=[-h] 9=[-l] 10=[-l] 11=[-k] 12=[-k] 13=[-k] 14=[-i] 15=[-m] 16=[-x] 17=[-o] 18=[-o] 19=[2.-w] 20=[-s] 21=[-s]*/
	  char  argD[22][cLPF] = { "", "", "bas", "", "pc", "1.0", "no", "5", "", DEBUG_ARG, "0", "", "", "", "-1", "", "", "", "", "5", "0.0", DEBUG_TIME_ARG }, *ptrErr = NULL ;
      char  argS[cLPF] = "", argPc[cLPF] = "", *ptrToken ;
	  uint  ii, FILEcnt = 0, Tcnt = 0, PCcnt=0, Dcnt = 0, Ccnt = 0, Ucnt = 0, Wcnt = 0, Ecnt = 0, Lcnt = 0, Kcnt = 0, Hcnt = 0, Ocnt = 0 ;
 	 ulong  type = TYPE_NOK, utf8 = 16, debug = 0 ;
 	  long  imgbgn = 0, tmpbgn = 0 ;
 	 ulong  order = ORDER_STD ;
	   int  option_index, i, j, k, l, error = ERR_OK, c = 0, len ;
static int  longval;
      bool  new_arg = false, old_arg = false ;

 const int  Token_Nb = 3 ;
     char*  oldToken[] = { "T:", "G:", "D:" } ; /* TOKEN_NB */
     char*  newToken[] = { "-t", "-u", "-l" } ; /* strlen 2 only */

	struct option long_options[] =
	{
		{"type",    required_argument, 0,        't'},
		{"pc",	    required_argument, 0,        'p'},
		{"device",	required_argument, 0,        'd'},
		{"cspeed",	required_argument, 0,        'c'},
		{"utf8",    optional_argument, 0,        'u'},
		{"width",   required_argument, 0,        'w'},
		{"khx",     no_argument,       0,        'y'},
		{"tap",     no_argument,       0,        'r'},
		{"quiet",   no_argument,       0,        'q'},
		{"exit",    optional_argument, 0,        'x'},
		{"endmark", no_argument,       0,        'e'},
		{"level",   required_argument, 0,        'l'},
        {"keywords",required_argument, 0,        'k'}, /* keyword definition file */
        {"img",     optional_argument, 0,        'i'}, /* input from IMG pos, delimiter must `=` with opt_arg */
        {"parameters",optional_argument, 0,      'm'}, /* write header parameters to file */
        {"codepoints",required_argument, 0,      'o'}, /* code space definition file */
        {"start",   optional_argument, 0,        's'}, /* start processing at wav time */
		{"version", no_argument,       &longval, 'v'}, /* long option only */
		{"help",    optional_argument, &longval, 'h'}, /* long option only, delimiter must `=` */
	        {0, 0, 0, 0}
	};

    /* ProgramName */
    if      (strrchr (argv[0], '\\')) strncpy(argP, 1 + strrchr (argv[0], '\\'), cLPF-1);  /* Windows path separator '\' */
    else if (strrchr (argv[0], '/')) strncpy(argP, 1 + strrchr (argv[0], '/'), cLPF-1);    /* Linux   path separator '/' */
    else strncpy(argP, argv[0], cLPF-1);
    if ( strrchr (argP, '.')) *(strrchr (argP, '.')) = '\0';                      /* Extension separator '.'    */


    /* check, if the old argument format is used */
    for (i = 1; i < argc; ++i) {// 1. argument is program
        if ( *argv[i] == '-' ) {
                new_arg = true ;
                break ;
        }
        strncpy (argS, argv[i], cLPF -1) ;
        strupr(argS) ;

        if ( strcmp(argS, "T:IMG") == 0 ) old_arg = true ;
        if ( strcmp(argS, "T:BAS") == 0 ) old_arg = true ;
        if ( strcmp(argS, "G:YES") == 0 ) old_arg = true ;
        if ( strcmp(argS, "G:NO")  == 0 ) old_arg = true ;
    }
    if ( !new_arg && old_arg) {
        printf("%s: Old format of arguments was detected", argP);
        for (i = 2; i < argc; ++i) { // 1. argument is program, 2. a file name
            strncpy (argS, argv[i], cLPF -1) ;
            strupr(argS) ;
            for ( j = 0 ; j < Token_Nb ; ++j ) { // old TOKEN_NB /
                ptrToken = strstr (argS, oldToken[j]) ;
                if (ptrToken == argS) { // replace on old argument token /
                    for ( k = 0 ; k < 2 ; ++k ) { // new_token length 2 /
                        argv[i][k] = newToken[j][k] ;
                    }  // next char
                    k = 2 ;
                    l = (uint) strlen (oldToken[j]) ;
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


    do {
        while (1) {

            /* getopt_long stores the option index here. */
            option_index = 0;

            c = getopt_long (argc, argv, "t:p:d:c:u::w:yrqx::el:k:i::m::o:s::vh::", long_options, &option_index);

            /* Detect the end of the options. */
            if (c == -1) break;

            switch (c) {
            case 't': strncpy( argD[2], optarg, cLPF-1); ++Tcnt; break;
            case 'p': strncpy( argD[3], optarg, cLPF-1); ++PCcnt; break;
            case 'd': strncpy( argD[4], optarg, cLPF-1); ++Dcnt; break;
            case 'c': strncpy( argD[5], optarg, cLPF-1); ++Ccnt; break;
            case 'u':  { if ( optarg != 0 ) strncpy( argD[6], optarg, cLPF-1);
                        ++Ucnt; break; }
            case 'w': { if (Wcnt < 2) strncpy( argD[7+12*Wcnt], optarg, cLPF-1);
                        ++Wcnt; break; }
            case 'y': ++KHXc; break;
            case 'r': ++TAPc; break;
            case 'q': ++Qcnt; break;
            case 'x': { if ( optarg != 0 ) strncpy( argD[16], optarg, cLPF-1);
                        ++Xcnt; break; }
            case 'e': ++Ecnt; break;
            case 'l': { if (Lcnt < 2) strncpy( argD[9+Lcnt], optarg, cLPF-1);
                        ++Lcnt; break; }
            case 'k': { if (Kcnt < 3) strncpy( argD[11+Kcnt], optarg, cLPF-1);
                        ++Kcnt; break; }
            case 'i': { if ( optarg != 0 ) {
                                      strncpy( argD[14], optarg, cLPF-1);
                                      tmpbgn = -1 ; }
                        ++IMGc; break; }
            case 'm': { if ( optarg != 0 ) strncpy( argD[15], optarg, cLPF-1);
                        ++Mcnt; break; }
            case 'o': { if (Ocnt < 2) strncpy( argD[17+Ocnt], optarg, cLPF-1);
                        ++Ocnt; break; }
            case 's': { if ( optarg != 0 && Scnt < 2 ) strncpy( argD[20+Scnt], optarg, cLPF-1);
                        ++Scnt; break; }
            case 0:
                switch (longval) {
                    case 'v': PrintVersion (); break;
                    case 'h': { if ( optarg != 0 ) strncpy( argD[8], optarg, cLPF-1);
                            ++Hcnt; break; }
                } break;
            case '?':
                      printf("%s: Unknown argument for '%s'\n", argP, argP);
            default : MoreInfo (ERR_SYNT); break;
            }
        }

        if (optind < argc) { /* get non-option ARGV-elements */
            while (optind < argc) {
                strncpy(argD[FILEcnt!=0], argv[optind++], cLPF-1);
                ++FILEcnt;
            }
        }

        if ((FILEcnt > 2) || (Tcnt > 1) || (PCcnt> 1) || (Dcnt > 1) || (Ccnt > 1) ||
               (Ucnt > 1) || (Wcnt > 2) || (Xcnt > 1) || (Lcnt > 2) || (Kcnt > 3) ||
               (IMGc > 1) || (Mcnt > 1) || (Hcnt > 1) || (Ocnt > 2) || (Scnt > 2) ) {
                printf("%s: [E] Too many arguments of same type for '%s'\n", argP, argP);
                MoreInfo (ERR_SYNT);
        }
        else if ((KHXc > 1) || (TAPc > 1) || (Qcnt > 1) || (Ecnt > 1) ) {
                printf("%s: [W] Too many arguments of same type for '%s'\n", argP, argP);
        }
        if ( Hcnt == 1 ) {
            (void) strlor (argD[8]) ;
            PrintHelp (argD[8]) ;
            break;
        }
        if (FILEcnt < 1) { printf("%s: Missing Operand after '%s'\n", argP, argP); MoreInfo (ERR_SYNT); }

        /* Convert debug in a long */
        debug = (ulong) strtol (argD[9], &ptrErr, 0) ;
        if (*ptrErr != 0) {
            debug = 0 ;
            printf ("%s: Convert debug level number from '%s' is not valid\n", argP, argD[9]) ;
            MoreInfo (ERR_ARG);
        }
        debug = debug | (ulong) strtol (argD[10], &ptrErr, 0) ;
        if (*ptrErr != 0) {
            debug = 0 ;
            printf ("%s: Convert debug level number2 from '%s' is not valid\n", argP, argD[10]) ;
            MoreInfo (ERR_ARG);
        }

        (void) strlor(argD[2]) ;
        type = TYPE_NOK ;

        if (strcmp (argD[2], "bas") == 0 || strcmp (argD[2], "c") == 0) // differences in handling of C and ASM
            type = TYPE_BAS ;

        else if (strcmp (argD[2], "asm") == 0 || strcmp (argD[2], "asm8") == 0 || strcmp (argD[2], "asm4") == 0 ||
                 strcmp (argD[2], "capx")== 0 || strcmp (argD[2], "casl") == 0  ) { // CAP-X, CASL
            type = TYPE_BAS ;
            type_asm = true ;
        }
        else if (strcmp (argD[2], "asm5") == 0) {
            type = TYPE_BAS ;
            type_asm = true ;
            debug |= DEL_APST ;
        }
        else if (strcmp (argD[2], "asm6") == 0) {
            type = TYPE_BAS ;
            type_asm = true ;
            debug |= DEL_REMC ;
        }
        else if (strcmp (argD[2], "sha") == 0) {
            type = TYPE_BAS ;
            SHAc = 1 ;
        }
        else if (strcmp (argD[2], "img") == 0 || strcmp (argD[2], "dat") == 0 ||
                 strcmp (argD[2], "crd") == 0 || strcmp (argD[2], "tel") == 0 ||
                 strcmp (argD[2], "scd") == 0 || strcmp (argD[2], "not") == 0 ||
                 strcmp (argD[2], "txt") == 0  )
            type = TYPE_IMG ;
        else if (strcmp (argD[2], "asc") == 0)
            type = TYPE_ASC ;     /* Convert will switch it to IMG (or BAS) */
        else if (strcmp (argD[2], "shc") == 0) {
            type = TYPE_IMG ;
            SHCc = 1 ;
        }
        else if (strcmp (argD[2], "bin") == 0 ) {
            type = TYPE_IMG ;
        }
        else if (strcmp (argD[2], "imb") == 0 ) { // || strcmp (argD[2], "bin") == 0   25.01.2020\Mr
            type = TYPE_IMG ;
            IMBc = 1 ;
        }
        else if (strcmp (argD[2], "rsv") == 0)
            type = TYPE_RSV ;
        else if (strcmp (argD[2], "mem") == 0)
            type = TYPE_MEM ;
        else if (strcmp (argD[2], "def") == 0)
            type = TYPE_DEF ;
        else if (strcmp (argD[2], "tap") == 0) {
            type = TYPE_RAW ;
            TAPw = 1 ;
        }
        else if (strcmp (argD[2], "raw") == 0)
            type = TYPE_RAW ;
        else if (strcmp (argD[2], "rawdat") == 0 ) {
            type = TYPE_RAW ;
            order = ORDER_INV ;   /* for raw data debug */
        }
        else {
            printf ("%s: Destination file type '%s' is not valid\n", argP, argD[2]) ;
            MoreInfo (ERR_ARG);
        }

        ptrToken = strrchr (argD[0], '.') ;
        if (FILEcnt == 1) {

            if (strcmp (argD[2], "rawdat") == 0) strcpy(argS, "raw");
            else if (strcmp (argD[2], "imb") == 0) strcpy(argS, "img");
            else if (strcmp (argD[2], "txt") == 0) strcpy(argS, "img");
            else if (strcmp (argD[2], "casl")== 0) strcpy(argS, "cas");
            else if (type_asm) strcpy(argS, "asm");
            else strncpy (argS, argD[2], cLPF -1) ;

            if (ptrToken != NULL) strncpy (argD[1], argD[0], strrchr (argD[0], '.') - argD[0] ); /* GetSrcFile */
            else strncpy (argD[1], argD[0], cLPF -1) ;
            len = cLPF - 1 - strlen(argD[1]);
            if (len > (int)strlen(argS)) {
                strncat (argD[1], ".", len );
                strncat (argD[1], argS, len-1);  /* DstFile=SrcFile.extension */
            }
        }
        len = cLPF - 1 - strlen(argD[0]);
        if (ptrToken != NULL) {
            strncpy (argS, ptrToken, cLPF -1) ;
            (void) strlor(argS) ;
            if (strcmp (argS, ".khx") == 0) {
                if (KHXc==0 && Qcnt==0) printf("%s: Switched input format from wav to --khx implicitly\n", argP);
                KHXc |= 1;
            }
            else if (strcmp (argS, ".tap") == 0) {
                if (TAPc==0 && Qcnt==0) printf("%s: Switched input format from wav to --tap implicitly\n", argP);
                TAPc |= 1;
            }
            else if (strcmp (argS, ".img") == 0) {
                if (IMGc==0 && Qcnt==0) printf("%s: Switched input format from wav to --img implicitly\n", argP);
                IMGc |= 1;
            }
            else if (strcmp (argS, ".st") == 0) {
                imgbgn = SUPT_HEAD_L ;
                if (tmpbgn == 0 && Qcnt==0) printf("%s: Switched input to SuperTape Binary --img %lu implicitly\n", argP, imgbgn);
                IMGc |= 1;
            }
            else if (strcmp (argS, ".shc") == 0) {
                imgbgn = SHC_HEAD_L ;
                if (tmpbgn == 0 && Qcnt==0) {
                        printf("%s: Switched input to SHC Binary --img %lu implicitly\n", argP, imgbgn);
                        printf("Make sure that this SHC file contains a BASIC image without a password.\n");
                }
                IMGc |= 1;
            }
        }
        // NOTE (mr#4#):  --device argD[4] "khx")
        else if (KHXc !=0) strncat (argD[0], ".khx", len);
        else if (TAPc !=0) strncat (argD[0], ".tap", len);
        else strncat (argD[0], ".wav", len);

        if (Mcnt > 0) {
            ptrToken = strrchr (argD[1], '.') ;
            if (argD[15][0] == '\0') {
                if (ptrToken != NULL) strncpy (argD[15], argD[1], strrchr (argD[1], '.') - argD[1] ); /* GetDstFile */
                else strncpy (argD[15], argD[1], cLPF -1) ;
                ptrToken = NULL ;
            }
            else {
                ptrToken = strrchr (argD[15], '.') ;
            }
            if (ptrToken == NULL) {
                len = cLPF - 1 - strlen(argD[15]);
                strncat (argD[15], ".CFG", len );
            }
        }

        if (Qcnt == 0) {
            if (TAPw !=0 ) printf ("%s: Writes Emulator TAP format with name, header and checksums.\n", argP) ;
            else if (type == TYPE_RAW ) printf ("%s: Writes raw data with name, header and checksums.\n", argP) ;
        }

        if ( type != TYPE_BAS ) {
            if (Wcnt != 0) printf ("%s: Use option -w only for BASIC-program text file\n", argP) ;
            if (Ucnt != 0) printf ("%s: Use option -u only for BASIC-program text file\n", argP) ;
            // MoreInfo (ERR_ARG);
        }


        i = 3 ;
        if (strlen (argD[i]) == 0)
            pcId = 0 ;      /* default pcId, because only needed for special token tab or to select frequency */
        else {
            strupr (argD[i]) ;
            strncpy(argPc, argD[i], cLPF-1); /* save the full name */

            if (strlen(argD[i])>2 && strcmp(&argD[i][strlen(argD[i])-3], "JAP")==0) 
                argD[i][strlen(argD[i])-2]='\0'; /* Naming in PockEmul */
            else if (strlen(argD[i])>1 && strcmp(&argD[i][strlen(argD[i])-2], "K2")==0) {
                argD[i][strlen(argD[i])-1]='\0'; /* E500K2 */
                pcMode|=0x1C ;
            }
            if (strcmp(&argD[i][strlen(argD[i])-1], "J")== 0)  pcMode|=4 ;       /* Japanese version, E500 series */
            else if (strcmp(&argD[i][strlen(argD[i])-1], "K")== 0) 
                pcMode|=0xC ;                                                    /* E500 series with Kanji driver */

            if (strcmp      (argD[i], "PA-500") == 0){strcpy (argD[i],  "1100") ; pcMode|=4;}
            else if (strcmp (argD[i], "EL-6300")== 0) strcpy (argD[i],  "1100") ;
            else if (strcmp (argD[i], "6300")   == 0) strcpy (argD[i],  "1100") ;
            else if (strcmp (argD[i], "1110")   == 0) strcpy (argD[i],  "1245") ;
//            else if (strcmp (argD[i], "1140")   == 0) strcpy (argD[i],  "1140") ;
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
            else if (strcmp (argD[i], "1404")   == 0) strcpy (argD[i],  "1403") ;
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
            else if (strcmp (argD[i], "1470U")  == 0){strcpy (argD[i],  "1475") ; pcMode|=4;}
            else if (strcmp (argD[i], "1475J")  == 0){strcpy (argD[i],  "1475") ; pcMode|=4;}
            else if (strcmp (argD[i], "1500A")  == 0) strcpy (argD[i],  "1500") ;
            else if (strcmp (argD[i], "1500D")  == 0){strcpy (argD[i],  "1500") ; pcMode|=4;} /* minimal Kanji */
            else if (strcmp (argD[i], "1500J")  == 0){strcpy (argD[i],  "1500") ; pcMode|=4;}
            else if (strcmp (argD[i], "1501")   == 0){strcpy (argD[i],  "1500") ; pcMode|=4;}
            else if (strcmp (argD[i], "1500QT4") == 0) strcpy (argD[i], "1544") ;    /* FAST/Quick-Tape with fast header*/
            else if (strcmp (argD[i], "1500QT1") == 0) strcpy (argD[i], "1541") ;    /* FAST/Quick-Tape with standard header */
            else if (strcmp (argD[i], "1500QT") == 0) strcpy (argD[i],  "1541") ;    /* FAST/Quick-Tape */
            else if (strcmp (argD[i], "QT")  ==  0)   strcpy (argD[i],  "1541") ;
            else if (strcmp (argD[i], "QUICKTAPE")== 0) strcpy (argD[i],"1541") ;
            else if (strcmp (argD[i], "150")    == 0) {                              /* CE-150 original format*/
                                                      Base_FREQ4 = Base_FREQ5 = 0 ;
                                                      strcpy (argD[i],  "1500") ;
            }
            else if (strcmp (argD[i], "158")    == 0) {                              /* for retransfer with CE-158 */
                                                      DelSpcAfterRem = true ;        /* CE-158 adds SPC after REM */
                                                      strcpy (argD[i],  "1500") ;
            }
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
            else if (strcmp (argD[i], "PTA-4000+16")== 0) strcpy (argD[i], "1500") ; /* Hiradas Technika */
            else if (strcmp (argD[i], "PTA-4000")== 0) strcpy (argD[i], "1500") ;
            else if (strcmp (argD[i], "MC-2200") == 0) strcpy (argD[i], "1245") ;    /* Seiko */
            else if (strcmp (argD[i], "2200")   == 0) strcpy (argD[i],  "1245") ;
            else if (strcmp (argD[i], "34")     == 0) strcpy (argD[i],  "1250") ;    /* Tandy */
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
                                                      strcpy (argD[i],  "1600") ; pcMode|=0xC;    /* also Kanji */
            }
            else if (strcmp (argD[i], "1600K1") == 0) {                              /* CE-150, PC-1600K Mode 1 */
                                                      pcMode |= 1 ;  /* min. Kanji as PC-1500D, with 1500J file */
                                                      strcpy (argD[i],  "1601") ; pcMode|=4;
            }
            else if (strcmp (argD[i], "1600P")  == 0) strcpy (argD[i],  "1609") ;    /* CE-1600P, PC-1600 Mode 0 */
            else if (strcmp (argD[i], "1600M1") == 0
                                                    ) {
                                                      pcMode |= 1 ;
                                                      strcpy (argD[i],  "1601") ;    /* CE-150, PC-1600 Mode 1 */
            }
            else if (strcmp (argD[i], "E220")   == 0
                 ||  strcmp (argD[i], "220")    == 0
                                                    ) {
                                                      strcpy (argD[i],   "220") ;
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
                                                      strcpy (argD[i],   "850") ; pcMode|=4;
            }
            else if (strcmp (argD[i], "G850VS") == 0
                 ||  strcmp (argD[i], "G850V")  == 0
                 ||  strcmp (argD[i], "850V")   == 0
                                                    ) {
                                                      strcpy (argD[i],   "852") ; pcMode|=4;
            }
            else if (strcmp (argD[i], "E500S")  == 0
                 ||  strcmp (argD[i], "E500M2") == 0
                 ||  strcmp (argD[i], "E500J")  == 0
                 ||  strcmp (argD[i], "E500K")  == 0
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
                 if (strstr(argD[i], "500")== NULL) pcMode|=4;
                 if (strcmp(&argD[i][strlen(argD[i])-2], "M2")== 0) pcMode |= 2 ;   // with 2nd character table
                                                      strcpy (argD[i],   "500") ;  /* the native mode of PC-E500  */
            }
            else if (strcmp (argD[i], "E1475")  == 0
                 ||  strcmp (argD[i], "E475")   == 0) {
                 if (Qcnt == 0) printf ("\n%s: Files from Bin2wav in mode 'PC-1475' are supported with PC-%s.\n", argP, argD[i]) ;
                                                      strcpy (argD[i],   "475") ;
            }

            if (strcmp (argD[i], "J") == 0) {         /* unknown Japanese model */
                                                      strcpy (argD[i],   "0") ; pcMode|=4;
                                                      pcId = 0 ;
            }
            else {
                pcId = (ulong) strtol (argD[i], &ptrErr, 0) ;
                if (pcId < 200 || pcId > 7100) {
                    printf ("%s: Pocket computer %s is not valid\n", argP, argD[i]) ;
                    MoreInfo (ERR_ARG); // exit ;
                    break ;
                }
            }
            /* Compare the PC Ident to the allowed tokens */
            switch (pcId) {
            case 1211 :
                pcgrpId=IDENT_PC1211 ;
                Base_FREQ2 = Base_FREQ3 = Base_FREQ4 = Base_FREQ5 = 0 ;
                break ;

            case 1234 : /* force detection of frequency to 4 kHz */
                // pcgrpId == GRP_OLD || GRP_NEW || GRP_EXT;
                Base_FREQ2 = Base_FREQ3 = Base_FREQ4 = Base_FREQ5 = 0 ;
                break ;

            case 1140 :
            case 1146 : /* 1246DB */
            case 1148 : /* 1248DB */
            case 1150 :
                pcAddr = 0x8A00 ; /* 4 bit nibbles */
            case 1245 :
            case 1246 :
            case 1247 :
            case 1248 :
            case 1250 :
            case 1251 :
            case 1255 :
                pcgrpId = GRP_OLD ;
                Base_FREQ2 = Base_FREQ3 = Base_FREQ4 = Base_FREQ5 = 0 ;
                break ;

            case 1100 :
            case 1260 :
            case 1261 :
            case 1262 :
            case 1350 :
            case 1403 :
            case 1425 :
            case 1430 :
            case 1431 :
            case 1440 :
            case 1445 :
            case 1450 :
            case 1460 :

            case 1421 :     /* for this the option -p is necessary */
            case 1401 :     /* for this optionally, Yen-sign only */
            case 1402 :
                pcgrpId = GRP_NEW ;
                Base_FREQ2 = Base_FREQ3 = Base_FREQ4 = Base_FREQ5 = 0 ;
                break ;

            case 1280 :
            case 1360 :
            case 1475 :
                pcgrpId = GRP_EXT ;
                Base_FREQ2 = Base_FREQ3 = Base_FREQ4 = Base_FREQ5 = 0 ;
                break ;

            case 1544 :
                order = ORDER_Q ;
                Base_FREQ2 = 0 ;
            case 1541 :
                Base_FREQ5 = 0 ;
            case 1500 :
                pcgrpId = IDENT_PC1500 ;
                Base_FREQ1 = 0 ;
                Base_FREQ3 = 0 ;
                if (type == TYPE_RAW) order = ORDER_INV ; /* for debug of raw data set here */
                break ;

            case 1609 : /* PC-1600 Mode 0 */
                Base_FREQ2 = 0 ;
            case 1601 : /* PC-1600 Mode 1 */
                if (pcId == 1601) Base_FREQ3 = 0 ;
            case 1600 :
            case 1560 :
                Base_FREQ1 = 0 ;
                if (type == TYPE_RAW) order = ORDER_INV ;
                pcgrpId = GRP_16 ;  /* Mode 1 Id changed in PrintSaveId to IDENT_PC1500 */
                pcId = 1600 ;  /* used to select token table when saved from mode 1500 */
                break ;

            case  500 :
                Base_FREQ1 = 0 ;
            case  475 :  /* for E500 files from Bin2wav in the format of 1475 */
                Base_FREQ2 = Base_FREQ4 = Base_FREQ5 = 0 ;
                ll_Img = 255 ;
                pcgrpId = GRP_E ;
                break ;

            case  220 :
            case  850 :
            case  852 :
                Base_FREQ1 = Base_FREQ2 = Base_FREQ4 = Base_FREQ5 = 0 ;
                ll_Img = 255 ;
                pcgrpId = GRP_G ;
                break ;

            case  0 : /* "J" */
                break ;

            default :
                /* Organizer and newest Series, newer than G850VS */
                printf ("%s: ERROR: Pocket computer %s not implemented\n", argP, argD[i]) ;
                error = ERR_ARG ;
                break ;
            }
        }
        if (error != ERR_OK) break ;

        if (Xcnt > 0) {
            strlor(argD[16]) ;
            if (strlen(argD[16])==0) Xcnt = EXIT_ERR;
            else if (strcmp (argD[16], "e") == 0 || strcmp (argD[16], "err") || strcmp (argD[16], "error") == 0)
                Xcnt = EXIT_ERR ;
            else if (strcmp (argD[16], "t") == 0 || strcmp (argD[16], "type") == 0)
                Xcnt = EXIT_TYPE ;
            else if (strcmp (argD[16], "i") == 0 || strcmp (argD[16], "id") == 0 || strcmp (argD[16], "ident") == 0)
                Xcnt = EXIT_IDENT ;
            else if (strcmp (argD[16], "g") == 0 || strcmp (argD[16], "grpid") == 0 || strcmp (argD[16], "pcgrpid") == 0)
                Xcnt = EXIT_PCGRPID ;
            else {
                printf ("%s: Exit parameter '%s' is not valid\n", argP, argD[16]) ;
                MoreInfo (ERR_ARG);
            }
        }

        /* Read files with external code points, set code_cnt */
        for ( ii = 0 ; ii < Ocnt ; ++ii ){
            error = ReadCodepointsFromFile ( argD[17 + ii]) ;
            if (error != ERR_OK) break ;
        }
        if (error != ERR_OK) return (error) ;
        if (code_cnt > 0 && Qcnt == 0 ) printf ("%s: %u code points loaded from file(s)\n", argP, code_cnt) ;

        /* Read files with external token keywords, set key_cnt */
        for ( ii = 0 ; ii < Kcnt ; ++ii ){
            error = ReadKeywordsFromFile ( argD[11 + ii] ) ;
            if (error != ERR_OK) break ;
        }
        if (error != ERR_OK) return (error) ;
        if (key_cnt > 0 && Qcnt == 0 ) printf ("%s: %u tokens loaded from keyword file(s)\n", argP, key_cnt) ;

        /* Add space to token */
        for ( ii = 0 ; ii < key_cnt ; ++ii ){
            if (strlen (keyword [ii]) > 0 && strlen (keyword [ii]) < cLTK - 1 ) {
                if ( keyword [ii][strlen (keyword [ii] - 1 ) ] != ' ' ) strcat(keyword [ii], " ") ;
            }
        }

        strlor(argD[4]) ;
        if (strcmp (argD[4], "pc") == 0 || strcmp (argD[4], "150") == 0 || strcmp (argD[4], "162E") == 0 || strcmp (argD[4], "1600P") == 0 )
            devId = DEV_PC ;

        else if (strcmp (argD[4], "cas") == 0 || strcmp (argD[4], "cs") == 0) {
            devId = DEV_CAS ;
            /* default TRANS_WEAK_EXP 2, RATE_AMP_4_CAS 40 */
            if      (pcgrpId == IDENT_PC1500) Rate_Amp_Cas = RATE_AMP_15_MAX;
            else if (pcgrpId == IDENT_PC1211) Rate_Amp_Cas = RATE_AMP_12_MAX;
            else if (pcgrpId == GRP_E || pcgrpId == GRP_G || pcgrpId == GRP_16)
                Rate_Amp_Cas = RATE_AMP_E_CAS;
        }
        /* increase Trans_Weak_Exp for 15/16/E/121 areas of weak signals in the stream;
           increase Rate_Amp_4_Cas for PC-1234 high instable signals */
        else if (strcmp (argD[4], "cas0")== 0 || strcmp (argD[4], "cs0") == 0)
                                { devId = DEV_CAS ; Trans_Weak_Exp = 0; Rate_Amp_Cas =  0; } /* AMP_DIFF_MIN */
        else if (strcmp (argD[4], "cas1")== 0 || strcmp (argD[4], "cs1") == 0)
                                { devId = DEV_CAS ; Trans_Weak_Exp = 1; Rate_Amp_Cas = 14; Amp_Diff_Min_Cas = 8; }
        else if (strcmp (argD[4], "cas2")== 0 || strcmp (argD[4], "cs2") == 0)
                                { devId = DEV_CAS ; Trans_Weak_Exp = 2; Rate_Amp_Cas = 26; Amp_Diff_Min_Cas = 7; }
        else if (strcmp (argD[4], "cas3")== 0 || strcmp (argD[4], "cs3") == 0)
                                { devId = DEV_CAS ; Trans_Weak_Exp = 3; Rate_Amp_Cas = 40; Amp_Diff_Min_Cas = 6; }
        else if (strcmp (argD[4], "cas4")== 0 || strcmp (argD[4], "cs4") == 0)
                                { devId = DEV_CAS ; Trans_Weak_Exp = 4; Rate_Amp_Cas = 52; Amp_Diff_Min_Cas = 5; }

        else if (strcmp (argD[4], "air") == 0)
            devId = DEV_AIR ;
        else if (strcmp (argD[4], "emu") == 0)
            devId = DEV_EMU ;
        else if (strcmp (argD[4], "khx") == 0 || strncmp (argD[4], "dsave", 5) == 0)
            KHXc |= 1 ;
        else if (strcmp (argD[4], "tap") == 0)
            TAPc |= 1 ;
        else if (strcmp (argD[4], "img") == 0)
            IMGc |= 1 ;
        else if (strcmp (argD[4], "bin") == 0) {
            if (PCcnt == 0) {
                printf ("%s: Missing --pc parameter, mandatory with device BIN\n", argP) ;
                MoreInfo (ERR_ARG);
            }
            devId = DEV_BIN ;
        }
        else {
            printf ("%s: Source device of digitalization '%s' is not valid\n", argP, argD[4]) ;
            MoreInfo (ERR_ARG);
        }
        if (Qcnt == 0 ) {
            if ( devId != DEV_PC ) printf ("%s: Device filter for wavs recorded from '%s' was selected\n", argP, argD[4]) ;

            if ( devId == DEV_AIR ) {
                if (pcgrpId == IDENT_PC1211 || pcgrpId == IDENT_PC1500 || pcgrpId == GRP_E || pcgrpId == GRP_G || pcgrpId == GRP_16)
                    printf ("%s: Option 'device=%s' is not applicable for this PC group\n", argP, argD[4]) ;
            }
//            else if ( devId == DEV_CAS ) {
//                if (pcgrpId == GRP_E || pcgrpId == GRP_G || pcgrpId == GRP_16)
//                    printf ("%s: Option 'device=%s' has no effect for this PC \n", argP, argD[4]) ;
//            }
        }
        if ( devId == DEV_EMU ) {
            if (PCcnt == 0) {
                printf ("%s: Option 'pc' is required with option 'device=%s' \n", argP, argD[4]) ;
                MoreInfo (ERR_ARG);
            }
            /* only one base frequency allowed with wav files recorded from emulator */
            if (Base_FREQ3 > 0) { Base_FREQ1 = Base_FREQ2 = Base_FREQ4 = Base_FREQ5 = 0; } /* no backward compatibility with Emulator */
        }

        if (IMGc > 0) {
            tmpbgn = (ulong) strtol (argD[14], &ptrErr, 0) ;
            if ((*ptrErr != 0) ) {
                printf ("%s: Relative position for the begin of image data %s is not valid\n", argP, argD[14]) ;
                MoreInfo (ERR_ARG);
            }
            if (tmpbgn > -1) imgbgn = tmpbgn ;
            if (TAPc != 0) {
                printf ("%s: You may use only one of the two parameters 'tap' or 'img'.\n", argP) ;
                MoreInfo (ERR_ARG);
            }
            if (PCcnt == 0) {
                printf ("%s: Missing --pc parameter, mandatory with source from IMG\n", argP) ;
                MoreInfo (ERR_ARG);
            }
            if (type != TYPE_BAS && type != TYPE_IMG ) {
                printf ("%s: Invalid --type %s for source from IMG\n", argP, argD[2]) ;
                MoreInfo (ERR_ARG);
            }
            TAPc |= 1 ;
        }

        /* Check the range of CPU (or cassette) speed factor from modified hardware */
        speed = strtod (argD[5], &ptrErr) ;
        if ((*ptrErr != 0) || 0.16 > speed || speed > 5.701 ||
            (devId != DEV_EMU && (0.939 > speed || speed > 2.701))) {
                printf ("%s: A ratio of CPU frequency to an unmodified %s is not supported.\n", argP, argD[5]) ;
                MoreInfo (ERR_ARG);
        }
        else if ((float) speed < 0.9998 || (float) speed > 1.0002) {
            if (Qcnt == 0) printf ("%s: Option cspeed, ratio to original CPU frequency: %1.2f\n", argP, speed) ;
            Base_FREQ1 *= speed ;
            Base_FREQ2 *= speed ;
            Base_FREQ3 *= speed ;
            Base_FREQ4 *= speed ;
            Base_FREQ5 *= speed ;
        }

        /* Check the time (seconds) in the wav file at which signal processing is to be started  */
        StartTime = strtod (argD[20], &ptrErr) ;
        if ((*ptrErr != 0) || StartTime < -0.000001 || StartTime > 10000 ) {
                printf ("%s: Invalid start time %s (seconds) for processing of the wav file.\n", argP, argD[20]) ;
                MoreInfo (ERR_ARG);
        }
        else if (Scnt>0 && (IMGc > 0 || TAPc > 0 || KHXc > 0) ) {
                printf ("%s: The start time %s (seconds) is useful for a wav file but not for another file. Ignored.\n", argP, argD[20]) ;
        }
        else if (Scnt>0 && Qcnt==0)
                printf ("%s: Option -start processing %5.1f second(s) after the begin of recording.\n", argP, StartTime) ;

        if (pcgrpId == IDENT_PC1500 || pcgrpId == GRP_E || pcgrpId == GRP_G || pcgrpId == GRP_16)
            Sync_Lev_Min = SYNC_LEV_E;

        /* Check the debug_time (seconds) in the wav file at which debug processing is to be started  */
        if (Scnt>1) {
            Debug_Time = strtod (argD[21], &ptrErr) ;
            if ((*ptrErr != 0) || Debug_Time < -0.000001 || Debug_Time > 10000.000001 ) {
                printf ("%s: Invalid debug time %s (seconds) for processing of the wav file.\n", argP, argD[21]) ;
                MoreInfo (ERR_ARG);
            }
        }

        /* Check the utf8 conversion flag */
        (void) strlor (argD[6]) ;
        utf8 = 0 ;
        if (SHAc != 0 ) utf8 = UTF8_DOS ;
        else if (type == TYPE_BAS) {
            if ( Ucnt==0 || strcmp (argD[6], "yes") == 0) utf8 = 1 ;
            else if (strcmp (argD[6], "no") == 0) utf8 = 0 ;
            else if (strcmp (argD[6], "asc") == 0 || strcmp (argD[6], "2asc") == 0) utf8 = UTF8_ASC ;
            else if (strcmp (argD[6], "dos") == 0 || strcmp (argD[6], "2dos") == 0) utf8 = UTF8_DOS ;
            else if (strcmp (argD[6], "esc") == 0 ) utf8 = UTF8_ESC ;
            else if (strcmp (argD[6], "escx")== 0 ) utf8 = UTF8_ESCX;
            else if (strcmp (argD[6], "bom") == 0 ) utf8 = UTF8_BOM ;
            if (utf8 > 8) {
                printf ("%s: Wrong value for -u\n", argP) ;
                MoreInfo (ERR_ARG);
            }
        }
        if ( (pcMode & 8)>0 && code_cnt<65 && (utf8==1 || utf8==UTF8_BOM) && Qcnt==0 )
            printf ("Extra utf8 chars from a file --cOdepoints=Kanji.cfg required for full Kanji!\n") ;

        if (Wcnt == 0) {
            if (utf8 == UTF8_ASC && pcgrpId == GRP_G) strcpy (argD[7], "0.");
            else if (utf8 == UTF8_ASC || utf8 == UTF8_DOS || utf8 == UTF8_ESC || utf8 == UTF8_ESCX )
                strcpy (argD[7], "0") ; /* default: lines without indents */
        }
        /* Check the minimum width of line number */
        if (SHAc != 0 || strlen(argD[7]) == 0) linewidth = 0 ;
        else {
            if ( Wcnt>0 ) {
                strlor(argD[7]) ;
                len = strlen(argD[7])-1 ;
                if ( argD[7][len] == 'n' ) {      /* LF */
                        *(strrchr (argD[7], 'n')) = '\0';
                        Eol = Eol_n ;
                }
                else if ( argD[7][len] == 'r' ) { /* CR */
                        *(strrchr (argD[7], 'r')) = '\0';
                        Eol = Eol_r ;
                }
                len = strlen(argD[7])-1 ;
                if (len < 0) linewidth = 0 ;
                else if ( argD[7][len] == ':' ) { /* ":" */
                        *(strrchr (argD[7], ':')) = '\0';
                        lineformat = 2 ;
                }
                else if ( argD[7][len] == ';' ) { /* ": " */
                        *(strrchr (argD[7], ';')) = '\0';
                        lineformat = 3 ;
                }
                else if ( argD[7][len] == ',' ) { /* " : " */
                        *(strrchr (argD[7], ',')) = '\0';
                        lineformat = LNFRM_SCOLS ;
                }
                else if ( argD[7][len] == '.' ) { /* no space */
                        *(strrchr (argD[7], '.')) = '\0';
                        lineformat = 0 ;
                }
                else if ( argD[7][len] == '!' ) { /* no space */
                        *(strrchr (argD[7], '!')) = '\0';
                        lineformat = 0 ;
                        linenbr_del = true;
                }
                else if ( argD[7][len] == '_' ) { /* " " default */
                        *(strrchr (argD[7], '_')) = '\0';
                        lineformat = 1 ;
                }
            }
            if (strlen(argD[7]) == 0) linewidth = 0 ;
            else linewidth = (ulong) strtol (argD[7], &ptrErr, 0) ;
        }
        if ((*ptrErr != 0) || (linewidth !=0 && linewidth < 2) || (linewidth > 10)) {
                printf ("%s: Minimum width of line number %s is not valid\n", argP, argD[7]) ;
                MoreInfo (ERR_ARG);
        }
        /* Check the level of spaces generated before commands  */
        if (SHAc != 0 || strlen(argD[19]) == 0) spc_level = SPC_LSTD ;
        else {
            if ( Wcnt>1 ) {
                len = strlen(argD[19])-1 ;
                if ( argD[19][len] == '.' ) { /* remove space after command from table*/
                        *(strrchr (argD[19], '.')) = '\0';
                        DelSpcAfterCmd = true ;
                }
                else if ( argD[19][len] == '_' ) { /* " " default not remove */
                        *(strrchr (argD[19], '_')) = '\0';
                        DelSpcAfterCmd = false ;
                }
            }
            if (strlen(argD[19]) == 0) spc_level = 0 ;
            else spc_level = (ulong) strtol (argD[19], &ptrErr, 0) ;
        }
        if ( *ptrErr != 0 || spc_level > SPC_LMAX) {
                printf ("%s: Level of spaces before commands %s is not valid\n", argP, argD[19]) ;
                MoreInfo (ERR_ARG);
        }
        else if (spc_level == 0 && (pcgrpId == GRP_E || pcgrpId == GRP_G)) {
                printf ("%s: Never spaces before commands -w%s is not valid for this PC\n", argP, argD[19]) ;
                spc_level++ ;
        }
        if ( Wcnt < 2 && utf8 == UTF8_ASC) spc_level = 1 ;

        if (Ecnt > 0) debug |= BAS_EOF_INCL ;

        if (type_asm || strcmp (argD[2], "c") == 0) {
            if (Ucnt ==0) utf8 = UTF8_ASC ;

        /*  With CASL and PIC, there must be NO spaces in front of the assembler jump labels,
            but spaces are necessary in front of the commands. */
            if (Wcnt ==0 && type_asm && (pcgrpId == GRP_G || pcgrpId == GRP_NEW)) {
                    lineformat = 0 ; /* no spc after lnb, CASL and PIC */
                    linewidth  = 0 ;
            }
            if ((debug & (DEL_REMC | DEL_APST))==0 && pcgrpId == GRP_G && pcId >851 ) /* 852: G850V */
                debug |= DEL_REMC ;
        }
        if ((debug & 0x400000) > 0) CnvCmdLor |= 1 ; /* Convert characters to lower */
        if ((debug & 0x800000) > 0) CnvCmdLor |= 2 ; /* Convert commands to lower */

        if ((debug & 0x4000000) > 0) DelSpcAfterRem = true ; /* CE-158 */
        if (key_cnt > 0 && (debug & 0x100000) > 0) KeysFromFileOnly = true ;

        if (strncmp (argD[4], "cs", 2) == 0) debug |= NO_RATE_AMP ;
        if (devId == DEV_BIN) debug |= (BASE_FRQ_FIX | TRANS_OLD | NO_RATE_AMP | NO_PRE_AMP) ;

        if ((debug & BASE_FRQ_FIX) > 0 && Qcnt == 0) {
            printf ("%s: Base frequency tuning deactivated", argP );
            if (devId == DEV_EMU ) {
                    printf (", device option '%s' ignored\n", argD[4]);
                    devId = DEV_PC ;
            }
            else printf ("\n" );
        }

        if ((debug & NO_RATE_AMP) > 0) Rate_Amp_Def = 0 ;
        if ((debug & NO_RATE_AMP) > 0 && Qcnt == 0) {
            printf ("%s: Rate amp was deactivated", argP );
            if (devId == DEV_AIR ) printf (", device option '%s' will be ignored\n", argD[4]);
            else printf ("\n" );
        }

        if ((debug & TRANS_OLD) > 0) {        /* use old definitions */
            Trans_High_def = TRANS_HIGH_15 ;  /* audio level, for older more noisy lead ins */
            Trans_Low_def  = TRANS_LOW_15  ;
        }
        if ((debug & TRANS_OLD ) > 0 && Qcnt == 0) printf
                ("%s: will use the method of sample processing up to Wav2bin 1.5.\n", argP );

        if ((debug & CR_DEF_EOL) > 0 && Qcnt == 0) {
                if ((pcgrpId == IDENT_PC1211 || pcgrpId == GRP_OLD) && (type == TYPE_BAS || type == TYPE_IMG)) printf
                ("%s: Option --level=0x%04X unnecessary (standard procedure for this PC)\n", argP, CR_DEF_EOL);
                else if (type == TYPE_BAS ||
                        (type == TYPE_IMG && IMBc == 0 && (pcgrpId == IDENT_PC1500 || pcgrpId == GRP_NEW))) printf
                ("%s: Force new line after a CR is found (effective in case of lost bytes)\n", argP );
                else printf
                ("%s: Option --level=0x%04X not applicable to this type for this PC\n", argP, CR_DEF_EOL);
        }
        if ((debug & IGN_ERR_SUM) > 0 && Qcnt == 0) printf
                ("%s: Exit from Error %d is disabled. Correct destination file manually!\n", argP, ERR_SUM );

        /* Convert the Wav file */
        error = ConvertWavToBin (argD[0], argD[1], argD[15], argPc, type, order, utf8, imgbgn, debug) ;

    } while (0) ;
    if (error != ERR_OK && error != ERR_EOT) {
            if (error == ERR_EOF) error = ERR_FILE ;
            if (error == ERR_NSYNC) error = ERR_SYNC ;
            if ( Qcnt == 0 && (error == ERR_ORD || error == ERR_SYNC || error == ERR_SUM )) {
              if ((debug & DEBUG_TRACES)==0)
                printf ("Read the manual about possible device and type parameters and audio setup.\n") ;
              else {
                if (type == TYPE_BAS || (type == TYPE_IMG && IMBc == 0)) printf
                    ("If the image contains also non-BASIC binary code, try with '--type=imB' first.\n" );
                if (devId != DEV_CAS) printf
                    ("You can try device parameter '--device=CAS|CAS2|CS0|CS3' and read the manual.\n" );
              }
            }
            if (error == ERR_SUM && Qcnt == 0) printf
                ("Note: Immediate exit from Error %d can disabled with the option '-l 0x%03X'\n", ERR_SUM, IGN_ERR_SUM );
            if (debug != 0) printf ("Exit with error %d\n", error) ;
            return (error) ; // for debugging set here a breakpoint and in MoreInfo()
    }
    else return (EXIT_SUCCESS) ;
// printf("Debug# error: %i", error);
// DEBUG
// if (ptrFile->total > 0000)
// PrtWavTime(ptrFile);
}
