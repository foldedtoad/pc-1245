/* Textcoding Unicode (UTF-8, no BOM), End of Line Windows (CRLF)

bin2wav.c

For the copying conditions, please note also the comments in front of and the output (--version) of the "PrintVersion" function.

Development history
-------------------
      until V 1.3	www.pocketmuseum.com

2011-12-05	V 1.4	Manfred NOSSWITZ
	Changed to ANSI-C e.g. strupr()
	Command line parser changed to getopt().
	Quiet mode added.
	32bit compilation with gcc (tdm64-1) 4.6.1 (WindowsXP-prof [32bit]): gcc -pedantic -m32 -o xxx xxx.c
	32bit compilation with gcc-4_5-branch revision 167585 (OpenSUSE 11.4 [32bit]): gcc -pedantic -m32 -o xxx xxx.c
	64bit compilation with gcc (tdm64-1) 4.6.1 (Windows7-prof [64bit]): gcc -pedantic -m64 -o xxx xxx.c
	64bit compilation with gcc-4_5-branch revision 167585 (OpenSUSE 11.4 [64bit]): gcc -pedantic -m64 -o xxx xxx.c
	For testing PC-1402 was available only

2013-11-13	V 1.4.1	Torsten Muecker
	Changed for PC-14xx stop bits after last checksum to 11SS, silence added to var 'bit'
	Tested with PC-1401/02, PC-1403H, PC-1475
2013-12-16	V 1.4.2 beta2 Torsten Muecker
	-DAT for a data variable block added, only ONE data variable block (no list) and for PC-1261-1475 is supported
	-VAR for a data variable block without file name, can be appended by wav editor tools to an existing data wav
     How to concatenate wav data files with SoX (example): "sox DAT1.wav VAR2.wav DAT.wav"
2014-04-21	V 1.4.3 beta 12 Torsten Muecker
    - Debug Option "-l" added
    - Compatibility with new Wav2Bin 1.60:VAR-DAT-Files without all Checksum
    - Arguments buffer length protected, Exit code added
    - Support for Multiple Data Blocks added with Wav2Bin 1.6,
      please use debug option DATA_W2B150 for data files from Wav2Bin 1.5 (limitted)
    - Debug option NO_FILE_HEAD added, ident IDENT_DATA_VAR removed
    - PC-1421, PC-1280 and more PCs added
    - Tidy up --help screen
    - Arg default name corrected
    - Grouping of PCs now
    - Relocate code for Data from Convert to HeadToData
    - Remapping of more PC names implemented
    - removed some compiler warnings
    - All EOF-Labels shown in debug mode now
    - RSV-Data tested with Wav2bin
    - OLD_DAT full implemented, 121_DAT experimentally
      Tested with PC-1251
    - Option cspeed for clock modified Pocket Computers with a Hardware SpeedUp
    - DAT, RSV for PC-1500 added, Tested with PC-1500
2014-06-13	V 1.4.4 beta 5c Torsten Mücker
    - program code compression WriteByte(Sum)toBxxWav with MODE
    - checksums improved, when EOF overlap with end of checksum block, double EOF marks removed
    - check for activating seldom NEW/EXT_BAS CLOAD ERR_SUM bug
    - unified end of file mark of all basic images: appended only by Bin2wav
    - checksum before end of file changed for BAS_NEW, BAS_EXT
    - conversion of data variables between PC-1500 and other
    - PC 1211 program and data added
    - replaced fgetpos with ftell
    - conversion of string variable (with debug flag 0x10 )
    - some changes in categorisation of pocket computers
2014-09-30	V 1.4.5 beta 10L Torsten Mücker
    - PC-E series implemented, E_BIN, E_BAS, E_DAT
    - added entry address for E_BIN, added screen --help=l
    - added old arguments conversion to new arguments for backward compatibility with 3rd-party software
    - added option and destination TAP format for emulators, from Olivier De Smet bin2tap 2013-10-05 v1.5
    - implemented G850, Basic, Binary (with data there exist the same problem as with native wav files)
    - more waveform variants triangle, rectangle, trapezoidal with --level 1, 2: 48kHz (44.1 for PC-1500)
    - changed the default waveform to more stable trapezoidal, use -l 1 if you need the old compact format
    - ASCII modus E/G/1600-series (Data, SAVE CAS:)
    - Text modus of GRP_EXT, GRP_E (CSAVE, CLOAD) implemented
    - implemented support for Transfile PC plus SHC files
    - PC-1403 and newer changed to MODE_14
    - implemented PC-1600 DAT,
    - corrected tap-Format for PC-1500
    - 2. --sync for silence separate command line parameter
    - PC-1211: SHC supported (PC-1251)
2014-11-26	V 1.9.8 beta 08f1 Torsten Mücker
    - device parameter: -dINV mirroring all waveforms because of ASCII data
    - precise sync gaps for data
    - entry address for PC-1500,
    - default start address for most PC
    - Waveform 16 kHz with -l3 for Emulator
    - type detection from file extension
    - allow underline in filename and changed spaces at end and begin of 16/G/E series
    - optimized sync length and debug options for 16/G/E series, especially E-ASC
    - End address for all binaries, nbsamp
2015-03-29	V 1.9.9 beta c4 Torsten Mücker
    - debug traces not longer than print for 256 byte a line
    - New image end of transmission more precise
2015-07-26	V 2.0.9 beta 4 Torsten Mücker
    type DEF Def Keys, file A3 PC-1500
    placeholders [HH]for special chars in the name
    PC-1500 RAM variants for addr
    SuperTape for PC-1500 support with --pc=ST
    Quick-Tape Bas, Bin, RSV
2015-11-18	V 2.0.9 beta 5a1 Torsten Mücker
    ToDo: Public TESTs, Help needed
    code corrected for 64-bit
    --parameters file (-m)
    addr parameter variants priority
2016-02-28	V 2.0.9 RC1 for V 2.1 Torsten Mücker
2019-03-24	V 2.0.9 c2b
    debug option 0x200000 of bas2img and wav2bin (add end marks) is supported with bin2wav now
    check for expected and unexpected end marks, also EOF_ASC
    added parameter --endmark
    more checks between command line parameters and the parameter file
2019-04-11	V 2.0.9 c2b3a
    Data variable conversion, checks for double numeric (unsupported), longer BIN files for 1600
2019-05-05	V 2.0.9 c2b3b compiler warnings and ST header default entry addr
2019-06-20	V 2.0.9 c2b3c
    default Sharp name for Linux/OSX files with path separator
    check for correct tap file name
    tolerance +/- 3% for speed in cfg-file (from wav file) before using
2019-07-29	V 2.0.9  c2b3c(4) PC-E500M2, conditional compilation Linux
2019-08-30           c2b3c(4a) Path length
2019-09-30           c2b7 (0) type asm, 850V, line counter
2019-11-25(10-30)    c2b7 (1) for ihx files: read hex2bin 1.01/2.5 > output "Lowest address"
2019-12-01           c2c  (1a) --type=i16 PC-1600 Image with file header, check start byte for it
2020-01-05           c2c  (2) volume increased for PC-1211 + CE-121, signal form for PC-1500 44,1 kHz
2020-04-01           c2c  (3) Use the Sharp file name of the CFG file with higher priority than the name parameter
2020-10-21           c2c  (4a) PC-1100 group New, Database Memos
2020-10-26           c2c  (4b1) PC-1445 (1417G) CASL, type_asm, PC-1440 CAP-X prepared
2020-11-03           c2c  (4b2) PC-1150 type_mem (for CLOAD MEM)
2020-11-08           c2c  (4b3) PC-1440 CAP-X tested
2020-11-11           c2c  (4b4) compatibility and warnings
2020-12-30           c2d = c2c(4b4a) compiler warnings
2021-02-21	V 2.1.1  b1  Torsten Mücker
                         default sample rate 48/44.1 kHz, PC-1234 optimized 48 kHz waveforms
2021-02-22	V 2.1.1  b1a PC-E/G/16 optimized 48 kHz waveforms, --device=125 volume up
2021-02-26	V 2.1.1  b1b PC-1500/1211 optimized 48 kHz waveforms, shutdown and long silence at the end
2021-03-15	V 2.1.1  b2  Shutdown different forms --device= max | inx | inv | std0...2
2021-04-05	V 2.1.1  b2a -l 0x100 add sync at the end of the wav file (act against faders)
                         -l 0x2000 shorten the end of the wav file (you have to add your own end)
2021-04-19	V 2.1.1  c1(1) corrected stop bits for new/ext series, more sync of extended series at the end
2021-04-29	         c1a Messages, type detection priority, DATA EOF calculation, 1500ST End,
                        Old EOF MODEs_Bxx_2, all modes of PC-1234 series stop bits, syncs with -L SYNCL_STD,
                        bitMirroring: Phasing depends on the PC and (more) device(s)
2021-05-04           c1a(1) Quick-Tape --pc=1500QT1 (IDENT_PC15QTBAS, IDENT_PC15QTBIN), waveform
2021-06-28 	V 2.1.1  c1b(2)b --khx write khx files, -l 0x600, ParamsCnt,
                     snprint increases memory consumption!
2021-07-15 	V 2.1.1  c1b(4)a2 --khx khx_ver, PC-121_DAT EOF sync, "Jap" models
2021-07-21 	V 2.1.1  c1c,  2021-07-20 V 2.1.1 c1c (1) Khx for DSave unsupported (PC-1500),-E2, E5 old (not l0x800)
2021-08-09 	V 2.1.1  c1c (3a) E-Series INV, -k -o dummy options
2021-08-15 	V 2.1.1  c1c (3a) 1246DB MEM with old waveform
2021-08-16 	V 2.1.1  c1c (4) added parameter --waveform 1-3 as debug and older waveforms 4,(5)
2021-08-17 	V 2.1.1  c1c (5) precise speed waveform=5 for E-Series: 88,2 kHz
2021-08-30 	V 2.1.1  c1c (6c) 96 kHz waveform=5, 6 for first Series, -w6 for 1500 more precise speed (-1.05%)
2021-09-27 	V 2.1.1  c1d
2022-10-14  V 2.1.1  c1d (1) PC-1401 V.1 less stop bits
2022-10-18  V 2.1.1  c1d (1a) Default settings for PC-1401V2 and derivative models
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>		/* Command line parser getopt(). */
#include <ctype.h>

#define PDATE           "October 2022"
#define PVERSION        "2.1.1 c1d (2)"
                        /* delete "//" in next line to activate debug modus by default */
//#define DEBUG           1        /* should be commented for final releases */
#ifdef DEBUG
   #define DEBUG_ARG    "0x00C0"   /* Set to 0xC0 for more output with data variable blocks  */
#else
   #define DEBUG_ARG    "0"
#endif // DEBUG

/* Regular Errors such as EOF and recoverable such as End of sync *MUST* have a lower value then ERR_OK */
#define ERR_NOK        -1   /* also normal EOF */
#define ERR_OK          0

/* Unexpected NOT recoverable error *MUST* have a higher value then ERR_OK */
#define ERR_SYNT        1   /* arguments missed, syntax error */
#define ERR_ARG         3   /* arguments problem, pocket not implemented */
#define ERR_FILE        5   /* File I-O */
#define ERR_MEM         6   /* Line to long, buffer overflow, too much lines */
#define ERR_FMT         7   /* Source file format or size */
#define ERR_SUM         8   /* Constellation will generate a checksum error on PC */

#define TYPE_NOK        0
#define TYPE_BIN        1
#define TYPE_IMG        2
#define TYPE_VAR        3   /* one variable block without file type and name*/
#define TYPE_DAT        4
#define TYPE_RSV        5   /* For PC-1500, other re-transfer: IMG-compatible */
#define TYPE_ASC        6   /* For PC-E/G/1600 ASCII Data */
#define TYPE_BAS        7   /* For PC-E/G/1600 ASCII Source */
#define TYPE_TXT        8   /* For GRP_NEW, GRP_EXT and GRP_E text modus Image Data */
#define TYPE_DEF        9   /* For PC-1500 software, binary image for definable keys */
#define TYPE_DIM        10  /* For PC-1500 Quick-Tape, binary image of all dimensioned data variables */
#define TYPE_ARG_TXTS   10  /* for use with TypeArgTxt, higher IDs for database PC-11xx */
#define TYPE_MEM        11      /* Tables and Variables of PC-1140-1248DB, subtype of TYPE_IMG */
#define TYPE_CRD        0x6A    /* PC-1100 full RAM card, subtype of TYPE_IMG */
#define TYPE_TEL        0x61    /* Telephone database export */
#define TYPE_SCD        0x62    /* Scheduler database export  */
#define TYPE_NOT        0x64    /* Notes database export */

#define GRP_OLD         0x20
#define GRP_NEW         0x70
#define GRP_EXT         0x72
#define GRP_DAT         0x74
#define GRP_16          0x10    /* PC-1600 */
#define GRP_E           0x05    /* PC-E500 */
#define GRP_G           0x08    /* PC-G850, E2xx */

#define IDENT_PC1211    0x80
#define IDENT_PC121_DAT 0x8F    /* one variable length block only, not tested */

#define IDENT_PC1500    0xA
#define IDENT_PC15_BIN  0xA0
#define IDENT_PC15_BAS  0xA1
#define IDENT_PC15_RSV  0xA2
#define IDENT_PC15_DEF  0xA3
#define IDENT_PC15_DAT  0xA4
#define IDENT_PC15QTBAS 0xA5
#define IDENT_PC15QTBIN 0xA6

#define IDENT_QTAPE     0x0AA0
#define IDENT_QT_BAS    0x42    // B
#define IDENT_QT_BIN    0x4D    // M
#define IDENT_QT_RSV    0x52    // R
#define IDENT_QT_DIM    0x44    // D = V DIM
#define IDENT_QT_DAT    0x56    /* V NOT implemented, UNSUPPORTED! */

#define IDENT_OLD_BAS   0x20
#define IDENT_OLD_PAS   0x21
#define IDENT_OLD_DAT   0x24
#define IDENT_OLD_BIN   0x26

#define IDENT_NEW_TEL   0x61    // MEMO  TEL  NEW DB
#define IDENT_NEW_SCD   0x62    // MEMO  SCDL NEW DB
#define IDENT_NEW_NOT   0x64    // MEMO  NOTE NEW DB
#define IDENT_NEW_CRD   0x6A    // BASIC RAM Card IN
#define IDENT_OLD_MEM2  0x6D    // MEM 1246DB, old, all DB Tables
#define IDENT_OLD_MEM   0x6E    // MEM 11500, all DB Tables

#define IDENT_NEW_BAS   0x70
#define IDENT_NEW_PAS   0x71
#define IDENT_EXT_BAS   0x72
#define IDENT_EXT_PAS   0x73
#define IDENT_NEW_DAT   0x74    // IDENT_DATA_VAR 0xEF removed
#define IDENT_NEW_BIN   0x76
#define IDENT_NEW_CSL   0x7A    // CASL or CAP-X CMT
#define IDENT_UNKNOWN   0x100

#define IDENT_ST        0x124   /* SuperTape */

#define IDENT_PC16_CAS  0x00    /* PC-1600 ASCII Data or BASIC Image */
#define IDENT_PC16_DAT  0x08    /* Special binary data format PC-1600 */
#define IDENT_E_ASC     0x04    /* ASCII Data or Text Modus BASIC/ASM/C Source */
#define IDENT_E_BAS     0x02    /* Return from Bas2Img also in the format of PC-1475 */
#define IDENT_E_BIN     0x01    /* Binary Data, use --addr parameter 2nd time for entry address */
                                /* also used for Rsv-Data, but different sub id (mode 2) */
#define SYNC_E_HEAD     40      /* additional sync for E-series header block */
#define SYNC_E_DATA     20      /* additional sync for E-series data block */

#define DATA_HEAD_LEN   5       /* length of the header of a data variable element*/
#define DATA_VARIABLE   0xFE00  /* Header element of standard variable, not length */
#define DATA_DBL_LEN    14      /* length of a double numeric data variable element */
#define DATA_STD_LEN    8       /* length of a numeric and standard data variable element*/
#define DATA_NUM_15     0x88    /* ItemLen = Id of numeric data variable of PC-1500 */

#define DATA_NUM        0x98    /* Internal identity of numeric data variable */
#define DATA_STR        0xA8    /* Internal identity of a string data variable */
#define DATA_UNKNOWN    0x00    /* Variable filled with zeros */

#define DATA_STD_STR    0xF5    /* Standard data variable is a string */
#define DATA_EOF        0x0F    /* End of variable Data Block */

#define EOF_ASC         0x1A    /* End of ASCII transfered files, also CAS: of newer series */
#define EOF_15          0x55    /* End of complete file of PC-1500 */
#define EOF_QT1         0xF5    /* End of complete Quick-Tape 1 file, one of two bytes */
#define BAS_1500_EOF    0xFF    /* one of two bytes */
#define BAS_NEW_EOF     0xFF    /* one of two bytes */
#define BAS_OLD_EOF     0xF0    /* one byte only */

#define BLK_OLD_SUM     8       /* Transmission Block (plus checksums), old series bas without, data old/new with checksum reset */
#define BLK_OLD         80      /* Transmission Block (plus checksums) of PC-1500 and old series with checksum reset */
#define BLK_NEW         120     /* Transmission Block (plus checksum) of new series 1260-1475 */
#define BLK_E_DAT       256     /* Checksum of series E500 DAT */
#define BLK_E_HEAD      0x30    /* Length of header1 of series E500, next only after the end of a Transmission Block */
#define BLK_S_HEAD      25      /* Length of SuperTape Header without checksum */
#define BLK_QT1         0x100   /* Length of Block QT1 */

#define SUPT_HEAD_L     26      /* SuperTape length of header block with low byte of checksum included */
#define SUPT_SYN_NB     64      /* SuperTape number of synchronisation char */
#define SUPT_SYNC       0x16    /* SuperTape SYNCHR synchronisation char */
#define SUPT_HEAD       0x2A    /* SuperTape SYNPGM start mark of header block */
#define SUPT_DATA       0xC5    /* SuperTape SYNDAT start mark of program/data block */
#define SUPT_END        0x9B    /* SuperTape end mark after the checksum of a block */
#define SUPT_FLAGS      0x00    /* SuperTape flag byte */

#define BGNSAMPLES      44      /* first sample byte */

#define AMP_MID         0x80    /* Sample value for silence (all 8-bit) */
#define AMP_HIGH        0xDA    /* Sample value for amplitude HIGH */
#define AMP_LOW         0x26    /* Sample value for amplitude LOW */
#define AMP_HIGH_E      0xFC    /* Sample value for amplitude HIGH for E-series */
#define AMP_LOW_E       0x04    /* Sample value for amplitude LOW for E-series */
#define AMP_add_Emax    3       /* max volume */
#define AMP_HIGH_121    0xEF    /* Sample value for amplitude HIGH for CE-121 */
#define AMP_LOW_121     0x11    /* Sample value for amplitude LOW for CE-121 */
#define AMP_add_121     8       /* Some CE-121 + PC-1211 require full volume */
/* Speed of the run-out: twice the difference between two consecutive sample values at full volume and 48 kHz */
#define AMP_F_SHIFT_121 28      /* Relative attenuation of the signal at the EoB PC.121x */
#define AMP_F_SHIFT     8       /* Relative attenuation of the floating signal at the end of transmission or block */
#define AMP_F_SHIFT_E   6       /* Relative attenuation of the signal at the EoB G/E-series  */
#define AMP_F_SHOOT     8       /* Overshoot ratio of the signal at the end */
#define AMP_F_SHOOT_TOL 4       /* Tolerance ratio of overshoot at the end */

#define ORDER_STD       0
#define ORDER_INV       1
#define ORDER_S         8       /* SuperTape Byte */
#define ORDER_E         9       /* 1600-Series and newer, no nibbles, a byte */
#define ORDER_Q         11      /* Quick-Tape PC-1500a byte */

#define BASE_FREQ1      4000
#define BASE_FREQ2      2500    /* PC-1500 */
#define BASE_FREQ3      3015    /* PC-E-series and newer: Wav2bin real 2989-3041/~1200, 1600 TRM: 3056/1222 Hz */
#define BASE_FREQ4      5000    /* Quick-Tape */
#define BASE_FREQS      3600    /* SuperTape */

#define CHAR_SPACE      0x20
#define CHAR_DOT        0x2E
#define CHAR_COLON      0x3A
#ifdef __linux__                /* path separator */
   #define CHAR_SLASH   0x2F
//elif defined __APPLE__
#endif
#ifdef __APPLE__
   #define CHAR_SLASH   0x2F
#endif
#ifndef CHAR_SLASH              /* Windows path separator */
   #define CHAR_SLASH   0x5C
#endif
#define CHAR_UNDERSCORE 0x5F

#define cVL             80		/* Constant value for max. length of a data variable */
#define cLL             512		/* Constant value for max. length of CFG-TEXT lines and max. CFG line Nb */
#define cLPF            260		/* Constant value for max. Length of PathFilenames */
#define cLC             255		/* Constant value for max. length of minor texts or commands */
#define cKHX            32		/* Constant for max. hex values in a khx line */
#define SYNC_KHX_TX2    "-----....."                                /* Delaying the transmission ca. 0.08 s */
#define SYNC_KHX_TX4    "----------.........."                      /* Delaying the transmission ca. 0.15 s */
#define SYNC_KHX_TXT    "----------..........----------.........."  /* Delaying the transmission, for sync signals */

#define DEBUG_TRACES    0x00C0 /* general byte debug traces */
#define BAS_EOF_INCL  0x200000 /* debug flag for one included End Mark from Bas2img or Wav2bin */
#define SYNC_KHX_OFF   0x10000 /* debug flag, don't write sync bytes to khx file */
#define DATA_W2B150     0x8000 /* debug flag for DAT-IMG from Wav2bin 1.5.0 or older */
#define NO_FILE_HEAD    0x4000 /* debug flag, write without file type and -name, for 2. variable block to add */
#define NO_WAV_END      0x2000 /* debug flag, hard end, no shutdown or silence: Add your own end of wav file! */
#define BAS_EXT_FRMT    0x1000 /* debug flag, use FORMAT of BAS_EXT for E-Series */
#define ERR_OFF         0x800  /* debug flag, suppression for some errors */
#define SYNCL_STD       0x400  /* debug flag, for default sync length like the original */
#define SYNCL_TRM       0x200  /* debug flag, for sync length like the Technical Reference Manual or for Khx format */
#define SYNCA_END       0x100  /* debug flag, add sync at the end of the wav file (act against faders) */
#define SYNCA_END_LEN   5 /*sec, length of additional sync at the end of the wav file (against faders) */

#define MODE_B22        0   /* PC-1500 */
#define MODE_B21        1   /* PC-121x tap code */
#define MODE_B20        2   /* PC-121x, in fact, the PC-1211 writes two waves less than these stop bits per quater */
#define MODE_B19        3   /* Old series */
#define MODE_B17        4   /* Some TAP code */
#define MODE_B16        5   /* File names, header of new series and old data */
#define MODE_B15        6   /* Variable data body new series, Header PC-1401 V.1 */
#define MODE_B14        7   /* PC-1403 and newer: filename (reads also B13) */
#define MODE_B13        8   /* New and ext series body, 1402 filename */
#define MODE_B12        11  /* PC-1401 V.1 */
#define MODE_B20_2      9   /* PC-121x EOF */
#define MODE_B19_2      10  /* Old series EOF */
#define MODE_B14_2      11  /* Memo EOF */

#define MODE_B9         25  /* PC-E series and newer */
#define MODE_B10        26  /* SuperTape */
#define MODE_B11        27  /* Quick-Tape */

#define true 1
#define false 0
/*                      used types  */
typedef     int		    bool;
/*			char;	    */
typedef unsigned char	uchar;
// typedef unsigned char   uint8_t;
/*			short;	    */
typedef unsigned short	ushort;
/*			int;	    */
typedef unsigned int	uint;
/*			long;	    */
typedef unsigned long	ulong;

static char* TypeArgTxt[] = { "0", "bin", "img", "var", "dat", "rsv", "asc", "bas", "txt", "def", "dim" } ; /* higher IDs for database PC */

  uchar  Amp_High = AMP_HIGH ;
  uchar  Amp_Low  = AMP_LOW ;
  uchar  Amp2High = (uint) (3*AMP_HIGH + AMP_MID)/4 ;
  uchar  Amp2Low  = (uint) (3*AMP_LOW  + AMP_MID)/4 ;
  uchar  Amp1High = (uint) (3*AMP_HIGH + 5*AMP_MID)/8 ;
  uchar  Amp1Low  = (uint) (3*AMP_LOW  + 5*AMP_MID)/8 ;
  uchar  Amp0High = (uint) AMP_HIGH + AMP_MID/16 ;
  uchar  Amp0Low  = (uint) AMP_LOW  - AMP_MID/16 ;
    int  AmpFshift = AMP_F_SHIFT ;
    int  Shutdown_Form = -1;  /* Variant of the signal shutdown at the end of the transmission  */
                              /* -1(4):shutdown, 0:silence, 1:constant high or low, 2:sync bit, 3:stop bit */
  char  argP[cLPF] = "" ;
  uint  SHCc = 0 ,      /* Read not from bin, but from Transfile PC plus SHC-format (header included) */
        SHCe = 0 ;      /* End marks are the SHC Basic image included only*/
  uint  QTc  = 0 ;      /* Write to Quick-Tape wav format */
  uint  STc  = 0 ;      /* Header of SuperTape or file header of PC-1600 format is in the image included */
  uint  TAPc = 0 ;      /* Write not to wav format but to emulator tap format (raw bytes)*/
  uint  KHXc = 0 ;      /* Write not to wav, for DSAVE-30 khx format (raw ascii hex text)*/
  uint  Qcnt = 0 ;      /* Quiet, minimal output */
  uint  Scnt = 0 ;      /* Number of sync parameters or sync and sync spaces was defined */
  uint  Acnt = 0 ;      /* Number of address parameters, non standard load or entry addresses */
  uint  Mcnt = 0 ;      /* Read header parameter from a file */

double  speed = 1.00 ;  /* Used it for modified Pocket Computer with a CPU Speed Up switched on */

 ulong  pcId  = 1500 ;  /* ID number of the pocket computer */
ushort  pcgrpId = IDENT_UNKNOWN ;
// ulong  pcAddr = 0 ;         /* PC-specific address, used for the end of variable data of PCs with DB-tables */
  bool  cnvstr_upr = false ; /* Convert strings to upper, for Pokecon with SML-key not */
  bool  type_asm = false ;   /* Image contains assembler source code (subtype), true for CASL and CAP-X */

static  char* Eol = "\x0D\x0A" ;
// TODO (mr#2#): Count all warnings and errors
ulong  err_cnt = 0 ;    /* counts minor errors */
ulong  wrn_cnt = 0 ;    /* counts warnings */

typedef struct {
    FILE*  ptrFd ;
   ushort  ident ;
    uchar  mode ;       /* Bit writing mode and stop bits*/
    uchar  mode_h ;     /* Bit writing mode and stop bits for the file header*/
    ulong  nbSync1 ;    /* sync bits per second */
    ulong  nbSync ;     /* sync bits for intermediate syncs */
    ulong  nbByte ;     /* size of bytes to write */
    ulong  total ;      /* total bytes written (without checksums) */
    long   total_diff ; /* difference between bytes read and written (without checksums) */
    ulong  total_raw ;  /* total bytes written (with checksums), used for khx file information only */
    ulong  column_cnt ; /* bytes written (with checksums) to current line, used for khx format only */
    ulong  count ;      /* Counter of bytes in a block for the checksum */
    ulong  sum ;        /* Checksum calculated */
    ulong  block_len ;  /* Block length for checksum, variable used for E-Series */
    ulong  usedat_len ; /* Length of useful data of the next block 1...(0x50), for Qtape L:0...4F */
    ulong  bitLen ;     /* Wav sample blocks per SHARP bit */
     bool  lastSmpHigh; /* for SuperTape phase switching */
    ulong  debug ;
} FileInfo ;

typedef struct {
      uint  length ;  /* Length of one data variable block or marker for standard data variable block */
     uchar  dim1 ;    /* data variable block array vector columns dim1*/
     uchar  dim2 ;    /* data variable block array matrix lines dim2*/
     uchar  itemLen ; /* Len of one data variable element or marker */
} TypeInfo ;

typedef struct {
    uint  stopb1 ;
    uint  stopb2 ;
} ModeInfo ;

static ModeInfo Mode[] = {              /* stop bits of first and second nibble for PC-1100..1475, 1500 */
    { 6, 6 }, { 5, 6 }, { 5, 5 }, { 4, 5 },           /* MODE_B22, B21-20, B19-B18 (PC-1500, 121x, Old) */
    { 1, 6 }, { 1, 5 }, { 1, 4 }, { 1, 3 }, { 1, 2 },  /* B17-15 (Tap, Header, Data), B14-13 (EXT, NEW) */
    { 5, 3 }, { 4, 3}, { 1, 1 }                            /* End of file 121x, Old, Memo End & 1401 V1 */
} ;

static bool bitMirroring = false ; /* 1. half wave above DC, 2. below DC; (true: 1. half wave below DC) */
/* Pattern for WriteBit */
/* Bit low pattern, Bit high pattern, silence, shutdown signal */
/* Amp Max := +     Amp Min := -     Silence := . */

static char* bit1[] = { /* old compressed signal for PC-1210 ... PC-1500 */
    "++--++--++--++--", /* Bit_0 */
    "+-+-+-+-+-+-+-+-", /* Bit_1, sync, waveform: triangle signal */
	"................", /* silence */
	"+--*************", /* shutdown, depending of freq sound hardware +1 bit */
	"****************"  /* continue shutdown 2nd bit */
} ;

static char* bit2[] = {  /* new signal for PC-1210 ... PC-1500, more gain independent */
    "++++----++++----++++----++++----",
    "++--++--++--++--++--++--++--++--",/* Bit_1 trapezoidal signal*/
	"................................",
	"++-----*************************",/* shutdown, not for PC-1500 */
	"********************************"
} ;

static char* bit3[] = {                /* 48 kHz near sinus signal for PC-1210 ... PC-1475 */
    "./+^^^^^^^+/.|-vvvvvvv-|./+^^^^^^^+/.|-vvvvvvv-|./+^^^^^^^+/.|-vvvvvvv-|./+^^^^^^^+/.|-vvvvvvv-|",
    "./+^+/.|-v-|./+^+/.|-v-|./+^+/.|-v-|./+^+/.|-v-|./+^+/.|-v-|./+^+/.|-v-|./+^+/.|-v-|./+^+/.|-v-|",
	"................................................................................................",
    "./+^+/.|-vvvvvvvvvvv****************************************************************************",
    "************************************************************************************************"
} ;
//static char* bit3[] = {              /* 48 kHz near rectangle signal for PC-1210 ... PC-1475 Ver.2.0 */
//    ".+++++++++++.-----------.+++++++++++.-----------.+++++++++++.-----------.+++++++++++.-----------",
//    ".+++++.-----.+++++.-----.+++++.-----.+++++.-----.+++++.-----.+++++.-----.+++++.-----.+++++.-----",
//	  "................................................................................................",
//    ".+++++.-----------------------------------------------------------------------------------------",
//	  "................................................................................................"
//} ;
static char* bit3_v210[] = {           /* 48 kHz near rectangle signal for PC-1140/50, 124xDB MEM */
    ".+++++++++++.-----------.+++++++++++.-----------.+++++++++++.-----------.+++++++++++.-----------",
    ".+++++.-----.+++++.-----.+++++.-----.+++++.-----.+++++.-----.+++++.-----.+++++.-----.+++++.-----",
	"................................................................................................",
    "./**********************************************************************************************",
    "************************************************************************************************"
} ;

static char* bit3_15[] = {             /* 44.1 kHz sample rate signal for PC-1500 */
    ".////+++++^^^^^^+/.||||----vvvvvv-|.////+++++^^^^^^+/.||||----vvvvvv-|.////+++++^^^^^^+/.||||----vvvvvv-|.////+++++^^^^^^+/.||||-----vvvvvv-|",
    "/+^^^^^+/|-vvvvv-./+^^^^+/.-vvvvv-|/+^^^^^+/|-vvvvv-|/+^^^^^+.|-vvvv-|.+^^^^^+/|-vvvvv-|/+^^^^^+/|-vvvvv-./+^^^^+/.-vvvvv-|/+^^^^^+/|-vvvvv-|",
	".............................................................................................................................................",
	";********************************************************************************************************************************************",/* std. not */
	"............................................................................................................................................." /* not used */
} ;
static char* bit3_15_v209[] = {         /* 44.1 kHz sample rate signal for PC-1500 Ver.2.09 */
    "./+++++++++++++++/.|--------------|./+++++++++++++++/.|--------------|./+++++++++++++++/.|--------------|./+++++++++++++++/.|---------------|",
    "/+++++++/|-------./++++++/.-------|/+++++++/|-------|/+++++++.|------|.+++++++/|-------|/+++++++/|-------./++++++/.-------|/+++++++/|-------|",
    ".............................................................................................................................................",
	";********************************************************************************************************************************************",/* std. not */
    "............................................................................................................................................." /* not used */
} ;
static char* bit3_15_v20[] = {         /* 44.1 kHz near rectangle signal for PC-1500 Ver.2.0 */
    "...+++++++++++++++...--------------...+++++++++++++++...--------------...+++++++++++++++...--------------...+++++++++++++++...---------------",
    "..+++++++..-------..++++++..-------..+++++++..-------..+++++++..------..+++++++..-------..+++++++..-------..++++++..-------..+++++++..-------",
    ".............................................................................................................................................",
	"..;******************************************************************************************************************************************",/* std. not */
    "............................................................................................................................................." /* not used */
} ;

static char** bit4 = bit2 ; /* 16kHz waveform */

static char* bit4_15[] = {             /* 16 kHz sample rate signal for PC-1500 */
    ".++++++------++++++.------++++++------.++++++------",
    ".+++---+++---+++.---+++---+++---.+++---+++---+++---",
	"...................................................",
    ".+++---+++---+++.---+++---+++---.+++---+++---+++---",/* not used */
    ".+++---+++---+++.---+++---+++---.+++---+++---+++---"
} ;

static char* bit5[] = {                /* 96 kHz rectangle signal for PC-1100 ... PC-1475 */
    ";+^^^^^^^^^^^^^^^^^^^^+;:-vvvvvvvvvvvvvvvvvvvv-:;+^^^^^^^^^^^^^^^^^^^^+;:-vvvvvvvvvvvvvvvvvvvv-:;+^^^^^^^^^^^^^^^^^^^^+;:-vvvvvvvvvvvvvvvvvvvv-:;+^^^^^^^^^^^^^^^^^^^^+;:-vvvvvvvvvvvvvvvvvvvv-:",
    ";+^^^^^^^^+;:-vvvvvvvv-:;+^^^^^^^^+;:-vvvvvvvv-:;+^^^^^^^^+;:-vvvvvvvv-:;+^^^^^^^^+;:-vvvvvvvv-:;+^^^^^^^^+;:-vvvvvvvv-:;+^^^^^^^^+;:-vvvvvvvv-:;+^^^^^^^^+;:-vvvvvvvv-:;+^^^^^^^^+;:-vvvvvvvv-:",
	"................................................................................................................................................................................................",
    ";***********************************************************************************************************************************************************************************************",
    "************************************************************************************************************************************************************************************************"
} ;//static char* bit5[] = {                /* 96 kHz trapezoid signal for PC-1100 ... PC-1475 */
//    ".;+^^^^^^^^^^^^^^^^^^^+;.:-vvvvvvvvvvvvvvvvvvv-:.;+^^^^^^^^^^^^^^^^^^^+;.:-vvvvvvvvvvvvvvvvvvv-:.;+^^^^^^^^^^^^^^^^^^^+;.:-vvvvvvvvvvvvvvvvvvv-:.;+^^^^^^^^^^^^^^^^^^^+;.:-vvvvvvvvvvvvvvvvvvv-:",
//    ".;+^^^^^^^+;.:-vvvvvvv-:.;+^^^^^^^+;.:-vvvvvvv-:.;+^^^^^^^+;.:-vvvvvvv-:.;+^^^^^^^+;.:-vvvvvvv-:.;+^^^^^^^+;.:-vvvvvvv-:.;+^^^^^^^+;.:-vvvvvvv-:.;+^^^^^^^+;.:-vvvvvvv-:.;+^^^^^^^+;.:-vvvvvvv-:",
//	"................................................................................................................................................................................................",
//    ".;**********************************************************************************************************************************************************************************************",
//    "************************************************************************************************************************************************************************************************"
//} ;

static char* bit6[] = {                /* 96 kHz rounded signal for PC-1100 ... PC-1475 */
    ".;/+^^^^^^^^^^^^^^^^^+/;.:|-vvvvvvvvvvvvvvvvv-|:.;/+^^^^^^^^^^^^^^^^^+/;.:|-vvvvvvvvvvvvvvvvv-|:.;/+^^^^^^^^^^^^^^^^^+/;.:|-vvvvvvvvvvvvvvvvv-|:.;/+^^^^^^^^^^^^^^^^^+/;.:|-vvvvvvvvvvvvvvvvv-|:",
    ".;/+^^^^^+/;.:|-vvvvv-|:.;/+^^^^^+/;.:|-vvvvv-|:.;/+^^^^^+/;.:|-vvvvv-|:.;/+^^^^^+/;.:|-vvvvv-|:.;/+^^^^^+/;.:|-vvvvv-|:.;/+^^^^^+/;.:|-vvvvv-|:.;/+^^^^^+/;.:|-vvvvv-|:.;/+^^^^^+/;.:|-vvvvv-|:",
	"................................................................................................................................................................................................",
    ".;/*********************************************************************************************************************************************************************************************",
    "************************************************************************************************************************************************************************************************"
} ;

static char* bit6_15[] = {             /* 96 kHz rounded rectangle signal for PC-1500, 16 amps(2,5kHz) *19 samples =304 samples (optimum: 307,2 samples) */
    ".;/+^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^+/;.:|-vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv-|:.;/+^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^+/;.:|-vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv-|:\
.;/+^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^+/;.:|-vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv-|:.;/+^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^+/;.:|-vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv-|:",
    ".;/+^^^^^^^^^^^^+/;.:|-vvvvvvvvvvvv-|:.;/+^^^^^^^^^^^^+/;.:|-vvvvvvvvvvvv-|:.;/+^^^^^^^^^^^^+/;.:|-vvvvvvvvvvvv-|:.;/+^^^^^^^^^^^^+/;.:|-vvvvvvvvvvvv-|:\
.;/+^^^^^^^^^^^^+/;.:|-vvvvvvvvvvvv-|:.;/+^^^^^^^^^^^^+/;.:|-vvvvvvvvvvvv-|:.;/+^^^^^^^^^^^^+/;.:|-vvvvvvvvvvvv-|:.;/+^^^^^^^^^^^^+/;.:|-vvvvvvvvvvvv-|:",
	"........................................................................................................................................................\
........................................................................................................................................................",
	".;******************************************************************************************************************************************************\
********************************************************************************************************************************************************",
	"........................................................................................................................................................\
........................................................................................................................................................"
} ;

static char** bit = bit3 ; /* default waveform */


static char* bitQ1[] = {/* compressed signal for Quick-Tape PC-1500 */
    "++--",             /* Bit_0 */
    "+-+-",             /* Bit_1 triangle */
	"....",             /* silence  */
	"+...",             /* shutdown */
	"...."
} ;

static char* bitQ2[] = {/* Ver.2.0 default rectangle signal for Quick-Tape PC-1500 */
    "++++----",         /* Bit_0 */
    "++--++--",         /* Bit_1 */
	"........",         /* silence  */
	"++......",         /* shutdown */
	"........"
} ;

static char* bitQ3[] = {    /* Ver.2.11 default 44.1 kHz sample rate signal for Quick-Tape PC-1500 */
    ".+^^+////.-vv-||||",   /* Bit_0 */
    ".+^^/|vv-.+^^/|vv-",   /* Bit_1 */
	"..................",   /* silence  */
	"./++/.............",   /* shutdown */
	".................."
} ;
//static char* bitQ3[] = {  /* Ver.2.1 default 44.1 kHz sample rate signal for Quick-Tape PC-1500 */
//  ".++++++++.--------",   /* Bit_0 */
//  ".++++----.++++----",   /* Bit_1 */
//  "..................",   /* silence  */
//	".++++.............",   /* shutdown */
//	".................."
//} ;

static char* bitQ4[] = {    /* 16 (15) kHz signal for QuickTape PC-1500, experimentally! */
    "+++---",               /* Bit_0 */
    ".+-.+-",               /* Bit_1 */
	"......",               /* silence  */
	"++....",               /* shutdown */
	"......"
} ;

static char* bitQ6[] = {    /* 96 kHz sample rate signal for Quick-Tape PC-1500 */
    ";/+^^^^^+/////////;:|-vvvvv-|||||||||:",   /* Bit_0 */
    ";/+^^^^^/.|-vvvvv|:;/+^^^^^/.|-vvvvv|:",   /* Bit_1 */
	"......................................",   /* silence  */
	".;/+++++/;............................",   /* shutdown */
	"......................................"
} ;

static char** bitQ = bitQ3 ; /* default waveform, for later switching to QT */


static char* bitS1[] = { /* compressed signal for SuperTape PC-1500 */
    "/++|--",
    "/+++++", /* Bit_1, inverted during writing */
	".++++++++.--------", /* lead in */
	"..................", /* shutdown */
	"."                   /* not used */
} ;

static char* bitS2[] = {  /* Ver.2.0 default 36 kHz signal for SuperTape PC-1500 (3600 baud) and all headers */
    "./+++|----",
    "/+++++++++",
    ".+++++++++++++..-------------",
    ".............................",
	"."
} ;
//static char* bitS2[]
//    ".++++-----",
//    "++++++++++",

//    "++++.-----",
//    "++++++++++",

//    ".++++----.",
//    "++++++++++",

//    ".++++.----",
//    ".+++++++++",

static char* bitS3[] = {  /* Ver.2.1 default 44.1 kHz sample rate signal for SuperTape PC-1500 */
    "./++++|-----",
    "./++++++++++",
    "...+++++++++++++++...---------------",
    "....................................",
	"."
} ;

static char* bitS4[] = {  /* 72 kHz signal for SuperTape 7200 header block, no 16 kHz */
    "./++++++++|---------",
    "./++++++++++++++++++",
    "...++++++++++++++++++++++++++...--------------------------",
    "..........................................................",
	"."
} ;

static char* bitS6[] = {  /* 96 kHz sample rate signal for SuperTape PC-1500 */
    "./+++++++++++.|------------",
    "./+++++++++++++++++++++++++",
    "../++++++++++++++++++++++++++++++++++/..|----------------------------------|",
    "............................................................................",
	"."
} ;

static char** bitS = bitS3 ; /* default waveform */

static char* bitS2_7[] = {  /* 36 kHz signal for SuperTape 7200 data block */
    "./+|-",
    "/++++",
    ".+++++++++++++..-------------",
    ".............................",
	"."
} ;

static char* bitS4_7[] = {  /* 72 kHz signal for SuperTape 7200 data block */
    "./+++|----",
    "/+++++++++",
    "...++++++++++++++++++++++++++...--------------------------",
    "..........................................................",
	"."
} ;

static char** bitS_7 = bitS4_7 ; /* default waveform for 7200 data block */

static uint bitLS[] = {  /* default values from bitS3, will calculated new in ConvertB. */
    12, 12, 36, 36, 1
} ;

/* The following pattern are used for the PC-E500 and PC-G800 series and PC-1600. Especially for
   ASCII Source/Data from the interface dependent have to start with '+' or '-' (see -dINV) */

/* PC-E500 series only: smaller files but longer synchronisation than bitE2 needed, Not for G-800 series */
static char* bitE1[] = { /* compressed format, not readable from all PCs */
    "+-",           /* Bit_0, waveform: triangle signal */
    "+++--",        /* Bit_1 */
	"..",           /* silence */
    "+++---------", /* header stop bit 1 with signal shutdown */
	"."
} ;

/* PC-E500 and newer, G800-series, variable bit length, trapezoidal, stable */
static char* bitE2[] = {
    "++--",                   /* Bit_0 trapezoidal signal */
    "+++++-----",
	"....",
    "+++++------------------",
	"."
} ;

/* This set writes 48 kHz files. Only *near* rectangle works for G-800 series - threshold needed. */
static char* bitE3[] = {
    "./+++++/.|-----|",
    "./+++++++++++++++++/.|-----------------|",
	"................",
    "./+++++++++++++++++/.|------*****************************************************************************************************************************************",
	"."
} ;
static char* bitE3_v20[] = { /* Ver.2.0 */
    ".+++++++.-------",
    ".+++++++++++++++++++.-------------------",
    "................",
    ".+++++++++++++++++++.-----------------------------------------------------------------------",
    "."
} ;

/* 16 kHz sample rate signal  */
static char* bitE4[] = {
    "++.--",
    "++++++.------",
	".....",
    "++++++.------------------------",
	"."
} ;

/* This set writes 88.2 kHz files. */
static char* bitE5[] = {
    ".;/++++++++++/;:|----------|:",
    ".;/+++++++++++++++++++++++++++++++/;.:|-------------------------------|:",
	".............................",
    ".;/+++++++++++++++++++++++++++++++/;.:|-----------*******************************************************************************************************\
*************************************************************************************************************************************************************",
	"."
} ;

/* This set writes 96 kHz files. */
static char* bitE6[] = {
    "./++++++++++++++.|--------------",
    "./++++++++++++++++++++++++++++++++++++++.|--------------------------------------",
	"................................",
    "./++++++++++++++++++++++++++++++++++++++.|--------------****************************************************************************************************************\
****************************************************************************************************************************************************************************",
	"."
} ;

static char** bitE = bitE3 ;  /* default waveform for E/G Series*/

static uint bitLE[] = {  /* default values from bitE3, will calculated new in ConvertB. */
    16, 40,	16, 165, 1
} ;


static ulong CodeOld[] = {
    0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,
    0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,
    0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,
    0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,
    0x11,0x14,0x12,0x15,0x18,0x16,0x1F,0x11, // Pos. 0x24 $ 0x19 -> 0x18, 11/2020
    0x30,0x31,0x37,0x35,0x1B,0x36,0x4A,0x38,
    0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,
    0x48,0x49,0x1D,0x1C,0x33,0x34,0x32,0x13,
    0x1E,0x51,0x52,0x53,0x54,0x55,0x56,0x57,
    0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
    0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,
    0x68,0x69,0x6A,0x11,0x11,0x11,0x39,0x11,
    0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,
    0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,
    0x19,0x11,0x1A,0x11,0x11,0x11,0x11,0x11,
    0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11
} ;


void CvShortToStringI (uint  value,
                       char*  ptrStr)
{
    uint  tmp ;

    /* Convert the short value into a String with msb first (INTEL) */
    tmp = value & 0xFF ;
    *ptrStr ++ = (char) tmp ;
    tmp = value >> 8 ;
    *ptrStr ++ = (char) tmp ;
    *ptrStr = 0 ;
}

void CvLongToStringI (ulong  value,
                      char*  ptrStr)
{
    ulong  tmp ;

    /* Convert the 32bit value into a String with msb first (INTEL) */
    tmp = value & 0xFF ;
    *ptrStr ++ = (char) tmp ;
    tmp = (value >> 8) & 0xFF ;
    *ptrStr ++ = (char) tmp ;
    tmp = (value >> 16) & 0xFF ;
    *ptrStr ++ = (char) tmp ;
    tmp = value >> 24 ;
    *ptrStr ++ = (char) tmp ;
    *ptrStr = 0 ;
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


int WriteStringToFile (char*  ptrStr,
                       FILE**  ptrFd)
{
    int  error ;

    error = fputs (ptrStr, *ptrFd) ;
    if (error == EOF) {
        printf ("%s: Can't write in the file\n", argP) ;
        error = ERR_FILE ;
    }
    else {
        error = ERR_OK ;
    }
    return (error);
}


int WriteLongToFile (ulong  value,
                     FILE**  ptrFd)
{
    char  str[10] ;
     int  ii ;
     int  error ;

    CvLongToStringI (value, str) ;

    for ( ii = 0 ; ii < 4 ; ++ii  ) {
        error = fputc (str[ii], *ptrFd) ;
        if (error == EOF) {
            printf ("%s: Can't write in the file\n", argP) ;
            error = ERR_FILE ;
            break ;
        }
        else
            error = ERR_OK ;
    }
    return (error);
}


int WriteShortToFile (ulong  value,
                      FILE**  ptrFd)
{
    char  str[10] ;
     int  ii ;
     int  error ;

    CvShortToStringI (value, str) ;

    for ( ii = 0 ; ii < 2 ; ++ii ) {
        error = fputc (str[ii], *ptrFd) ;
        if (error == EOF) {
            printf ("%s: Can't write in the file\n", argP) ;
            error = ERR_FILE ;
            break ;
        }
        else
            error = ERR_OK ;
    }
    return (error);
}


int ReadFileLength ( uchar  type,
                    ulong*  ptrLen,
                    FILE**  ptrFd)
{
    long  nbByte ;
     int  inVal, eof_mark = BAS_1500_EOF ;
     int  error ;
    uint  EndCharCnt = 0,  EndCharDef = SHCe ;   /* SHCe is the number of end chars */
    /* SHCc is the length of a SHC header or zero, set in global and ReadHeadFromShc */

    do {
        *ptrLen = 0 ;

        /* Seek to the end of the source file */
        error = fseek (*ptrFd, 0, SEEK_END) ;
        if (error != ERR_OK) {
            printf ("%s: Can't seek the file\n", argP) ;
            error = ERR_FILE ;
            break ;
        }

        /* Get the length of the source file */
        nbByte = ftell (*ptrFd) ;
        if (nbByte == ERR_NOK) {
            printf ("%s: Can't ftell the file\n", argP) ;
            error = ERR_FILE ;
            break ;
        }

        /* check if EOF marks included in the IMG*/
        if (  type == TYPE_ASC || type == TYPE_BAS ) eof_mark = EOF_ASC ;
        if (( type == TYPE_ASC || type == TYPE_BAS || type == TYPE_IMG || type == TYPE_TXT ) && nbByte > (long) SHCe) {
            error = fseek (*ptrFd, -(long)SHCe-1, SEEK_CUR) ;

            if (error != ERR_OK) {
                printf ("%s: Can't seek the file\n", argP) ;
                error = ERR_FILE ;
                break ;
            }
            inVal = fgetc (*ptrFd) ;                /* check of unexpected EOF mark */
            if (inVal == EOF) {
                    error = ERR_FILE ;
                    break ;
            }
            else if (inVal == eof_mark) {
                    ++SHCe ; /* End mark was included from Bas2IMG and other images */
                    if (Qcnt == 0) printf ("%s: Warning: An additional end mark was found at the end of the image.\n", argP) ;
            }
            while ( EndCharCnt++ < EndCharDef ) {   /* check expected EOF marks */
                    inVal = fgetc (*ptrFd) ;
                    if (inVal == EOF) {
                        error = ERR_FILE ;
                        break ;
                    }
                    else if (inVal != eof_mark) {
                        SHCe = EndCharDef - EndCharCnt ; /* Should be an end mark but is not */
                        printf ("%s: Expected end mark %u not found at end of image, check parameters.\n", argP, EndCharCnt ) ;
                    }
            }
        }

        if (STc > 0) { /* SuperTape or I16 binary file with Header included */
            if (STc == 1) { /* no offset, flag only */
                error = fseek (*ptrFd, 0, SEEK_SET) ;
            }
            else { /* offset from ST-binary file */
                error = fseek (*ptrFd, STc, SEEK_SET) ;
                nbByte -= STc;
            }
            if (error != ERR_OK) {
                printf ("%s: Can't seek the file\n", argP) ;
                error = ERR_FILE ;
                break ;
            }
            nbByte -= SHCe;
            /* end mark not included in IMG- or ST-File but in sums of SuperTape header field and body */
            if (type == TYPE_IMG) ++nbByte ;
        }
        else {
        /* Seek to the beginning of the source file or
           after a SHC-Header, if type SHC was used */
            error = fseek (*ptrFd, SHCc, SEEK_SET) ;
            if (error != ERR_OK) {
                printf ("%s: Can't seek the file\n", argP) ;
                error = ERR_FILE ;
                break ;
            }
            nbByte -= ( SHCc + SHCe ); /* SHCe is the length of additional end marks */
        }
        if (nbByte <= 0) {
            printf ("%s: Source file is empty\n", argP) ;
            error = ERR_FILE ;
            *ptrLen = 0 ;
        }
        else
            *ptrLen = nbByte ;

    } while (0) ;
    return (error);
}

/* The setting of Identity is used but length calculation (number of samples) is obsolete now,
   this length calculation is for the old waveform and the identities of older versions only
*/
int LengthAndIdentOfBinWav (uchar  type,
                            ulong  nbByte,
                            ulong  nbSync,
                           ushort*  ptrIdent,
                            ulong*  ptrSamp,
                            ulong*  ptrDebug)
{
    ulong  nbSamp = 0 ;
    ulong  debugInfo ;
   ushort  ident ;
   ushort  grpId = pcgrpId ;
   ulong   lmode;  /* byte length with stop bits*/
      int  error = ERR_OK ;

    debugInfo = *ptrDebug ;

    do {
        if (type == TYPE_DAT && pcgrpId != IDENT_PC1500 && pcgrpId != GRP_E && pcgrpId != GRP_G  && pcgrpId != GRP_16) {
        // GRP_16 special data no pre-calculation of samples supported
            if (pcgrpId == IDENT_PC1211) ident = IDENT_PC121_DAT ;
            else if (pcgrpId == GRP_OLD) ident = IDENT_OLD_DAT ;
            else ident = IDENT_NEW_DAT ; /* EXT_DAT identical format */
            grpId = GRP_DAT ; /* pcgrpId local used only */
        }
        switch (grpId) {
        case GRP_DAT :
            if ((debugInfo & NO_FILE_HEAD) == 0) {
                    nbSamp = 1 + 9 ;     /* File type and name, + 1 Checksum incl. */
            }
            else nbSamp = 0 ;
            if ( ident == IDENT_PC121_DAT || ident == IDENT_OLD_DAT )
                nbSamp = (nbSamp + 6) * 19 * 16 ;  /* Var Header = 16 Byte19, Checksum incl. */
            else
                nbSamp = (nbSamp + 6) * 16 * 16 ;  /* Var Header = 16 Byte16, Checksum incl. */

            if ( (debugInfo & DATA_W2B150) > 0 )
                    nbByte -= 6 ;  /* 5 Byte Data Block def + 1 Byte Checksum wav2bin 1.5 */
            else
                    nbByte -= 5 ;  /* 5 Byte Data Block def */

            nbSamp += nbSync * 16 ;
            /* works only for one array block and not for fixed variables, but will corrected at the end*/
            nbSamp += (nbByte + (1 + (nbByte - 1) / 8)) * 15 * 16 ;
            nbSamp += 15 * 16 ;                     /* EOF */
            nbSamp += (1 + 2) * 16 ;        /* End of Transmission 1 Bit more orig. + 2 */
            break;

        case IDENT_PC1500 :
            if (type == TYPE_IMG) {
                if (QTc>0) {
                    ident = IDENT_PC15QTBAS ;
                    nbSamp = 0 ;
                }
                else {
                    ident = IDENT_PC15_BAS ;
                    /* Footer = 4 bytes : 0xFF, sum, 0x55 */
                    nbSamp = 4 ;
                }
            }
            else if (type == TYPE_RSV) {
                ident = IDENT_PC15_RSV ;
                /* Footer = 3 bytes : sum, 0x55 */
                nbSamp = 3 ;
            }
            else if (type == TYPE_DEF) {
                ident = IDENT_PC15_DEF ;
                /* Footer = 3 bytes : sum, 0x55 */
                nbSamp = 3 ;
            }
            else if (type == TYPE_DAT) {
                ident = IDENT_PC15_DAT ;
                /* Header Name + 8 byte, Footer = 3 bytes : sum, 0x55 */
                nbSamp = 11 ; /* missing interim sync, will corrected at end of processing */
            }
            else { //if (type == TYPE_BIN)
                if (QTc>0) {
                    ident = IDENT_PC15QTBIN ;
                    nbSamp = 0 ;
                }
                else {
                    ident = IDENT_PC15_BIN ;
                    /* Footer = 3 bytes : sum, 0x55 */
                    nbSamp = 3 ;
                }
            }

            /* Header = 42, Lead = nbByte + 2 * (nbByte / 80) */
            /* One Byte = 22 bits, each Bit = 16 Samples      */
            /* One Sync = one Bit = 16 Samples (2500 Hz)      */
            /* Ident  = 11 bits, 3 gaps: 72+  72+ 70 bits     */

            nbSamp += 42 + nbByte + 2 * (nbByte / 80) ;
            nbSamp *= 22 * 16 ;
            nbSamp += nbSync * 16 ;
            nbSamp += 225 * 16 ;
            if (ident == IDENT_PC15_DAT) nbSamp += 239 * 16 ;
            break ;                             /* 311 - 72, 1.0 sec before first data block */

        case GRP_OLD :
        case IDENT_PC1211 : //length of start and end gaps not added, because setting at and of wav is preferred method now
            if (type == TYPE_BIN) {
                ident = IDENT_OLD_BIN ;
                nbSamp = 1 + (2 * 9) ;  /* Header = 19 Byte */
            }
            else if (type == TYPE_MEM) {
                if ( pcId == 1148 || pcId == 1150) ident = IDENT_OLD_MEM ;
                else ident = IDENT_OLD_MEM2 ;
                nbSamp = 1 + (2 * 9) ;
            }
            else {
                ident = IDENT_OLD_BAS ;
                if (grpId == IDENT_PC1211) ident = IDENT_PC1211 ;
                nbSamp = 1 + 9 ;        /* Header = 10 Byte */
            }

            /* Footer = 1, Lead = nbByte + (nbByte / 8)  */
            /* One Byte = 19 bits, each Bit = 16 Samples */
            /* One Sync = one Bit = 16 Samples (4000 Hz) */

            nbSamp += 1 + nbByte + (nbByte / 8) ;
            nbSamp *= 19 * 16 ;
            nbSamp += nbSync * 16 ;
            if (type == TYPE_MEM) nbSamp -= 48 ; /* shorter EOF */
            break ;

        case GRP_NEW :
        case GRP_EXT :
            if (type == TYPE_CRD) ident = IDENT_NEW_CRD ;
            else if (type == TYPE_TEL) ident = IDENT_NEW_TEL ;
            else if (type == TYPE_SCD) ident = IDENT_NEW_SCD ;
            else if (type == TYPE_NOT) ident = IDENT_NEW_NOT ;

            else if (type == TYPE_BIN) {
                ident = IDENT_NEW_BIN ;
                nbSamp = (1 + (2 * 9)) * 16 * 16 ;  /* Header = 19 Byte16 */
            }
            else {
                if (grpId == GRP_EXT)
                    ident = IDENT_EXT_BAS ;
                else if (type_asm && (pcId == 1445 || pcId == 1440 || pcId == 1416 || pcId == 1417))
                    ident = IDENT_NEW_CSL ;         // PC-14xx CASL or CAP-X
                else
                    ident = IDENT_NEW_BAS ;

                nbSamp = (1 + 9) * 16 * 16 ;        /* Header = 10 Byte16 */
            }

            /* Footer = 3 Byte13(14)                        */
            /* Lead = (nbByte + (nbByte / 120)) Byte13      */
            /* Byte = 16 or 13(14) bits, Bit = 16 Samples   */
            /* Sync = one Bit = 16 Samples (4000 Hz)        */
                if (cnvstr_upr) lmode = 13; else lmode = 13 ; // Some lengths not correctly for the header 14
                nbSamp += (nbByte + 3 + (nbByte / 120)) * lmode * 16 ;
                nbSamp += nbSync * 16 ;

	    /* there are 2bits more HIGH at the end of transmission (at least for PC-1402) M. NOSSWITZ */
		/* additional 2bit HIGH or silence at the end of transmission (for PC-14xx ) T. Muecker */
		// NOTE (Mr#4#):Some synchronization lengths are incorrect. The entire code is only used for estimation now.
                nbSamp += 64 ;
            break ;

        case GRP_16 :
        case GRP_E  :
        case GRP_G  :
            if (type == TYPE_BIN)
                ident = IDENT_E_BIN ;  /* mode 2 sub id may be Bin or Rsv */
            else if (type == TYPE_IMG || type == TYPE_TXT || (type == TYPE_RSV && grpId == GRP_16))
                ident = IDENT_E_BAS ;
            else if (type == TYPE_ASC){ /* ASCII Data or Source file from Text Modus */
                if (pcgrpId == GRP_16) ident = IDENT_PC16_CAS ; /*only data, for binary use TYPE_IMG */
                else ident = IDENT_E_ASC ;
            }
            else if (type == TYPE_BAS) ident = IDENT_E_ASC ; /* ASCII Source also for PC-1600 */
            else if (type == TYPE_DAT) /* PC-1600 special data similar to PC-1500 */
                ident = IDENT_PC16_DAT ;
            else
                ident  = IDENT_UNKNOWN ;
            nbSamp = 0 ;
            break ;

        case IDENT_QTAPE :
            if (type == TYPE_IMG)
                ident = IDENT_QT_BAS ;

            else if (type == TYPE_RSV)
                ident = IDENT_QT_RSV ;

            else if (type == TYPE_DAT)
                ident = IDENT_QT_DAT ;

            else if (type == TYPE_DIM)
                ident = IDENT_QT_DIM ;

            else //if (type == TYPE_BIN)
                ident = IDENT_QT_BIN ;

            nbSamp = 0 ;
            break ;

        case IDENT_ST :
            ident  = IDENT_ST ;
            nbSamp = 0 ;
            break ;

        default :
            nbSamp = 0 ;
            ident  = IDENT_UNKNOWN ;
            break ;
        }

        if ((debugInfo & 3) == 0) nbSamp<<=1;
        /* other waveforms not calculated */
        else if ((debugInfo & 3) != 1) nbSamp = 0;
        *ptrIdent = ident ;
        *ptrSamp  = nbSamp ;
        // *ptrDebug = debugInfo ;

    } while (0) ;
    return (error);
}


int WriteSampleCountToHeadOfWav (ulong  nbSamp, FileInfo*  ptrFile)
{
    ulong nbSampP ;
//    fpos_t position ;
    long position ;
    int  error ;

    do {

        /* Seek to the Head of the source file */

        error = fseek (ptrFile->ptrFd, 0, SEEK_END) ;
        if (error != ERR_OK) {
            printf ("%s: Can't seek the wav file\n", argP) ;
            break ;
        }
        if ( (ptrFile->debug & DEBUG_TRACES) > 0 ) printf("\n") ;

//        fgetpos(ptrFile->ptrFd, &position) ;
        position = ftell( ptrFile->ptrFd ) ;

        nbSampP = position ;
        if (nbSampP < BGNSAMPLES) break ;

        nbSampP -= BGNSAMPLES ; /* All Header Bytes from WriteHeadToWav */

        if (nbSampP != nbSamp) {
            if (Qcnt == 0 && nbSamp > 0) {
// The estimate of the number of samples from LengthAndIdentOfBinWav was no longer maintained in the current version
//                    if ( (ptrFile->debug & 0x0080) > 0 && (ptrFile->debug & SYNCA_END)==0 )
//                        printf ("Written %lu Samples (%lu estimated)\n", nbSampP, nbSamp) ;
//                    else
                        if ( (ptrFile->debug & DEBUG_TRACES) > 0)
                            printf ("Written %lu Samples\n", nbSampP) ;
            }
            nbSamp = nbSampP ;

            error = fseek (ptrFile->ptrFd, 4, SEEK_SET) ;
            if (error != ERR_OK) {
                printf ("%s: Can't seek the wav file\n", argP) ;
                break ;
            }
            error = WriteLongToFile ((nbSamp + BGNSAMPLES - 8), &ptrFile->ptrFd) ;
            if (error != ERR_OK) break ;

            error = fseek (ptrFile->ptrFd, BGNSAMPLES - 4, SEEK_SET) ;
            if (error != ERR_OK) {
                printf ("%s: Can't seek the wav file\n", argP) ;
                break ;
            }
            error = WriteLongToFile (nbSamp, &ptrFile->ptrFd) ;  /* Nb Samples */
            if (error != ERR_OK) break ;

            error = fseek (ptrFile->ptrFd, 0, SEEK_END) ;
            if (error != ERR_OK) {
                printf ("%s: Can't seek the wav file\n", argP) ;
                break ;
            }
        }

    } while (0) ;
    return (error);
}


int WriteHeadToWav (ulong  nbSamp,
                    ulong  freq,
                    FileInfo*  ptrFile)
{
    int  error ;

    do {
        error = WriteStringToFile ("RIFF", &ptrFile->ptrFd) ;
        if (error != ERR_OK) break ;

        error = WriteLongToFile ((nbSamp + 36), &ptrFile->ptrFd) ;
        if (error != ERR_OK) break ;

        error = WriteStringToFile ("WAVEfmt ", &ptrFile->ptrFd) ;
        if (error != ERR_OK) break ;

        error = WriteLongToFile (0x10, &ptrFile->ptrFd) ;
        if (error != ERR_OK) break ;

        error = WriteShortToFile (1, &ptrFile->ptrFd) ;      /* PCM */
        if (error != ERR_OK) break ;

        error = WriteShortToFile (1, &ptrFile->ptrFd) ;      /* Mono */
        if (error != ERR_OK) break ;

        error = WriteLongToFile (freq, &ptrFile->ptrFd) ;    /* Samp Freq */
        if (error != ERR_OK) break ;

        error = WriteLongToFile (freq, &ptrFile->ptrFd) ;    /* Byte / sec */
        if (error != ERR_OK) break ;

        error = WriteShortToFile (1, &ptrFile->ptrFd) ;      /* Byte / Samp x Chan */
        if (error != ERR_OK) break ;

        error = WriteShortToFile (8, &ptrFile->ptrFd) ;      /* Bit / Samp */
        if (error != ERR_OK) break ;

        error = WriteStringToFile ("data", &ptrFile->ptrFd) ;
        if (error != ERR_OK) break ;

        error = WriteLongToFile (nbSamp, &ptrFile->ptrFd) ;  /* Nb Samples */
        if (error != ERR_OK) break ;

    } while (0) ;
    return (error);
}


int WriteHeadToKhx (char*  ptrName,
                    uchar  type,
                FileInfo*  ptrFile) /* global KHXc, pcgrpId, pcId, Eol */
{
    char  text[cLL] ;       /* General temporary text */
    int  error= ERR_OK ;
    uint  ii ;
    text[0]='\0' ;

    do {
        if ((ptrFile->debug & SYNC_KHX_OFF) ==0 && KHXc > 15) { /* for DLoad Ver1.6 */

            /* Without these leading empty lines, a key must be pressed before transmission */
            if ((ptrFile->debug & SYNCL_TRM) > 0) {
                for ( ii = 0 ; ii < 3 ; ++ii ) {
                    strncat(text, ".", cLL-1-strlen(text)) ;
                    strncat(text, Eol, cLL-1-strlen(text)) ;
                }
            }
            else {
                snprintf(text, cLL-1, "*khx=%1.1f", ((float) KHXc )/10 );
                strncat(text, Eol, cLL-1-strlen(text)) ;
                error = WriteStringToFile (text, &ptrFile->ptrFd) ;
                if (error != ERR_OK) break ;

                snprintf(text, cLL-1, "*pc=%lu", pcId);
                strncat(text, Eol, cLL-1-strlen(text)) ;
                if (type > TYPE_ARG_TXTS) {
                    strncat(text, "*type=database id", cLL-1-strlen(text)) ;
                }
                else {
                    strncat(text, "*type=", cLL-1-strlen(text)) ;
                    strncat(text, TypeArgTxt[type], cLL-1-strlen(text)) ;
                }
                strncat(text, Eol, cLL-1-strlen(text)) ;
//                strncat(text, "#", cLL-1-strlen(text)) ;
//                strncat(text, Eol, cLL-1-strlen(text)) ;
            }
            error = WriteStringToFile (text, &ptrFile->ptrFd) ;
            if (error != ERR_OK) break ;
        }
        if ((ptrFile->debug & SYNCL_TRM) > 0) {
            if ( pcgrpId == GRP_OLD || pcgrpId == IDENT_PC1211 )
                snprintf(text, cLL-1, "*Bas2HexA [%-7s]:", ptrName);
            else if ( pcgrpId == GRP_NEW || pcgrpId == GRP_EXT )
                snprintf(text, cLL-1, "*Bas2HexB [%-7s]:", ptrName);
            else
                snprintf(text, cLL-1, "*%s [%s]:", argP, ptrName);
        }
        else if (pcgrpId == GRP_OLD || pcgrpId == IDENT_PC1211 ||
                 pcgrpId == GRP_NEW || pcgrpId == GRP_EXT)
            snprintf(text, cLL-1, "*%s [%-7s]:", argP, ptrName);
        else
            snprintf(text, cLL-1, "*%s [%s]:", argP, ptrName);
        strncat(text, Eol, cLL-1-strlen(text)) ;

        if ((ptrFile->debug & SYNC_KHX_OFF) ==0 &&
            KHXc < 15 && pcgrpId != IDENT_PC1211) { /* for some MCU of DLoad Ver1.4 */

            if (pcId == 1350 || pcId == 1450 ) { /* Extend the leader for PC-1350 and other terminal software as TeraTerm */
                strncat(text, "----....", cLL-1-strlen(text)) ;
                strncat(text, Eol, cLL-1-strlen(text)) ;
            }
            else if (pcId ==1403 || pcId ==1425 || pcId ==1416 || pcId ==1417 ||
                     pcId < 1401 || pcId > 1445) {
                for ( ii = 0 ; ii < 3 ; ++ii ) {
                    strncat(text, SYNC_KHX_TXT, cLL-1-strlen(text)) ;
                    strncat(text, Eol, cLL-1-strlen(text)) ;
                }
            }
        }
        error = WriteStringToFile (text, &ptrFile->ptrFd) ;
        if (error != ERR_OK) break ;

    } while (0) ;
    return (error);
}


int WriteFooterToKhx (FileInfo*  ptrFile) /* global argP, Eol,  */
{
    char  text[cLL] ;       /* temporary text */
    int  error= ERR_OK ;
    text[0]='\0' ;

    do {
        if ((ptrFile->debug & SYNCL_TRM) > 0)
            strcpy(text, Eol) ;
        else
            strcpy(text, "") ;
        strncat(text, "Gone", cLL-1-strlen(text)) ;
        if ((ptrFile->debug & SYNCL_TRM) > 0) {
            strncat(text, " from ", cLL-1-strlen(text)) ;
            strncat(text, argP, cLL-1-strlen(text)) ;
        }
        strncat(text, Eol, cLL-1-strlen(text)) ;
        if ((ptrFile->debug & SYNCL_TRM) ==0) strncat(text, "# ", cLL-1-strlen(text)) ;
        error = WriteStringToFile (text, &ptrFile->ptrFd) ;
        if (error != ERR_OK) break ;

        snprintf(text, cLL-1, "Total %lu bytes.", ptrFile->total_raw);
        strncat(text, Eol, cLL-1-strlen(text)) ;
        error = WriteStringToFile (text, &ptrFile->ptrFd) ;
        if (error != ERR_OK) break ;

    } while (0) ;
    return (error);
}


int WriteBitToWav (int  value,
              FileInfo*  ptrFile)
{
static  uint  amp_float = AMP_MID<<8;
static   int  amp_overshoot = 0 ;
static  bool  set_overshoot = true ;

         int  damp_float = 0;
        uint  ii, imax = ptrFile->bitLen ;
         int  error ;
       uchar  outb = AMP_MID;

    if (TAPc > 0 || KHXc > 0) return (ERR_OK);

//    if (value > 7) { /* Currently fractions of a 1 bit only used for test purposes*/
//        imax >>=1 ; /* write syncs 1/2 1/4 or 1/8 of one bit */
//        if (value > 0x0F) imax >>=1 ;
//        if (value > 0x1F) imax >>=1 ;
//        value &= 7 ;
//    }
    if (value > 4) return (ERR_MEM);
    if (value > 2) { /* requested shutdown forms, default -1 (or 4) */
        if      (Shutdown_Form == 0) value = 2; /* change sample pattern to silence */
        else if (Shutdown_Form == 2) value = 1; /* change sample pattern to sync */
        else if (Shutdown_Form == 3) value = 0; /* change sample pattern to start bit */
    }

    for ( ii = 0 ; ii < imax ; ++ii ) {

        if ( bitMirroring) { /* device or debug option */
            if (bit[value][ii] == '-') outb = Amp_High;
            else if (bit[value][ii] == '+') outb = Amp_Low;
            else if (bit[value][ii] == '|') outb = Amp2High;
            else if (bit[value][ii] == '/') outb = Amp2Low;
            else if (bit[value][ii] == ':') outb = Amp1High;
            else if (bit[value][ii] == ';') outb = Amp1Low;
            else if (bit[value][ii] == 'v') outb = Amp0High;
            else if (bit[value][ii] == '^') outb = Amp0Low;
            else if (bit[value][ii] == '*') { /* signal shutdown */
                if (Shutdown_Form == 1) outb = amp_float>>8; /* stay constant high or low */
                else {
                    if (set_overshoot) {
                        amp_overshoot = ((int) amp_float - (AMP_MID<<8)) /AMP_F_SHOOT ;
                        set_overshoot = false ;
                    }
                    damp_float = (int) amp_float + amp_overshoot - (AMP_MID<<8) ;
                    amp_float -= AmpFshift * damp_float /256 ;
                    outb = amp_float>>8;
                    if ( abs(damp_float) < abs(amp_overshoot) /AMP_F_SHOOT_TOL) /* Minimum of overshoot reached  */
                        amp_overshoot = 0 ;
                }
            }
            else outb = AMP_MID; /* '.' */
        }
        else { /* default */
            if (bit[value][ii] == '+') outb = Amp_High;
            else if (bit[value][ii] == '-') outb = Amp_Low;
            else if (bit[value][ii] == '/') outb = Amp2High;
            else if (bit[value][ii] == '|') outb = Amp2Low;
            else if (bit[value][ii] == ';') outb = Amp1High;
            else if (bit[value][ii] == ':') outb = Amp1Low;
            else if (bit[value][ii] == '^') outb = Amp0High;
            else if (bit[value][ii] == 'v') outb = Amp0Low;
            else if (bit[value][ii] == '*') { /* signal shutdown */
                if (Shutdown_Form == 1) outb = amp_float>>8;
                else {
                    if (set_overshoot) {
                        amp_overshoot = ((int) amp_float - (AMP_MID<<8)) /AMP_F_SHOOT ;
                        set_overshoot = false ;
                    }
                    damp_float = (int) amp_float + amp_overshoot - (AMP_MID<<8) ;
                    amp_float -= AmpFshift * damp_float /256 ;
                    outb = amp_float>>8;
                    if ( abs(damp_float) < abs(amp_overshoot) /AMP_F_SHOOT_TOL) /* Maximum of overshoot reached  */
                        amp_overshoot = 0 ;
                }
            }
            else outb = AMP_MID; /* '.' */
        }
        if (bit[value][ii] != '*') {
            amp_float = outb<<8 ;
            set_overshoot = true ;
        }

        error = fputc (outb, ptrFile->ptrFd) ;
        if (error == EOF) {
            printf ("%s: Can't write in the file\n", argP) ;
            error = ERR_NOK ;
            break ;
        }
        else
            error = ERR_OK ;
    }
    return (error);
}


int WriteBitToSWav (int  value,
              FileInfo*  ptrFile)
{
     uint  ii, imax = bitLS[value] ; // ptrFile->bitLen ;
      int  error ;
    uchar  outb;
     bool  lastSmpHigh = ptrFile->lastSmpHigh ;

    if (TAPc > 0 || KHXc > 0) return (ERR_OK);

    for ( ii = 0 ; ii < imax ; ++ii ) {

        if ( ptrFile->lastSmpHigh) { /* phase switching */
            if (bitS[value][ii] == '-') outb = Amp_High;
            else if (bitS[value][ii] == '+') outb = Amp_Low;
            else if (bitS[value][ii] == '|') outb = Amp2High;
            else if (bitS[value][ii] == '/') outb = Amp2Low;
            else outb = AMP_MID;
        }
        else { /* not inverted */
            if (bitS[value][ii] == '+') outb = Amp_High;
            else if (bitS[value][ii] == '-') outb = Amp_Low;
            else if (bitS[value][ii] == '/') outb = Amp2High;
            else if (bitS[value][ii] == '|') outb = Amp2Low;
            else outb = AMP_MID;
        }
        if (outb > AMP_MID) lastSmpHigh = true;
        else if (outb < AMP_MID) lastSmpHigh = false;

        error = fputc (outb, ptrFile->ptrFd) ;
        if (error == EOF) {
            printf ("%s: Can't write in the file\n", argP) ;
            error = ERR_NOK ;
            break ;
        }
        else
            error = ERR_OK ;
    }
    ptrFile->lastSmpHigh = lastSmpHigh;
    return (error);
}


int WriteBitToEWav (int  value,
              FileInfo*  ptrFile)
{
     uint  ii, imax = bitLE[value] ;
      int  error ;
    uchar  outb;
   static  uint  amp_float = AMP_MID<<8;

    if (TAPc > 0 || KHXc > 0) return (ERR_OK);

    if (value > 2) { /* requested shutdown forms */
        if      (Shutdown_Form == 0) value = 2; /* change sample pattern to silence */
        else if (Shutdown_Form == 2) value = 0; /* change sample pattern to sync */
        else if (Shutdown_Form == 3) value = 1; /* change sample pattern to start bit */
        imax = bitLE[value] ;
    }

    for ( ii = 0 ; ii < imax ; ++ii ) {

        if ( bitMirroring) { /* device or debug option */
            if (bitE[value][ii] == '-') outb = Amp_High;
            else if (bitE[value][ii] == '+') outb = Amp_Low;
            else if (bitE[value][ii] == '|') outb = Amp2High;
            else if (bitE[value][ii] == '/') outb = Amp2Low;
            else if (bitE[value][ii] == ':') outb = Amp1High;
            else if (bitE[value][ii] == ';') outb = Amp1Low;
            else if (bitE[value][ii] == '*') {
                if (Shutdown_Form == 1) outb = amp_float>>8;
                else {
                    amp_float -= AmpFshift * ((int) amp_float - (AMP_MID<<8)) /256 ;
                    outb = amp_float>>8;
                }
            }
            else outb = AMP_MID; /* '.' */
        }
        else {
            if (bitE[value][ii] == '+') outb = Amp_High;
            else if (bitE[value][ii] == '-') outb = Amp_Low;
            else if (bitE[value][ii] == '/') outb = Amp2High;
            else if (bitE[value][ii] == '|') outb = Amp2Low;
            else if (bitE[value][ii] == ';') outb = Amp1High;
            else if (bitE[value][ii] == ':') outb = Amp1Low;
            else if (bitE[value][ii] == '*') {
                if (Shutdown_Form == 1) outb = amp_float>>8;
                else {
                    amp_float -= AmpFshift * ((int) amp_float - (AMP_MID<<8)) /256 ;
                    outb = amp_float>>8;
                }
            }
            else outb = AMP_MID; /* '.' */
        }
        if (bitE[value][ii] != '*') amp_float = outb<<8 ;

        error = fputc (outb, ptrFile->ptrFd) ;
        if (error == EOF) {
            printf ("%s: Can't write in the file\n", argP) ;
            error = ERR_NOK ;
            break ;
        }
        else
            error = ERR_OK ;
    }
    return (error);
}


int WriteSyncToKhx (ulong  nbSync,
                FileInfo*  ptrFile)
{
    char  text[cLL] ;       /* General temporary text */
    ulong  ii, nbLines, tmpLines, fsynclen = 12 ;
    int    error = ERR_OK ;

    if ((ptrFile->debug & SYNC_KHX_OFF) > 0 ||
        (KHXc < 15 && pcgrpId != IDENT_PC1211)) return (ERR_OK); /* V. 1.4 special */

    do {
        text[0]='\0' ;

        switch (pcgrpId) {
          case IDENT_PC1211 :
            fsynclen = 56 ; /* before end mark of std var data 2x TXT */
            break ;

          case GRP_OLD :
            fsynclen = 40 ; /* before end mark of std var data 1x TX4 only */
            break ;

          default :
            fsynclen = 40 ;
            break ;
        }
/* TODO (mr#2#): Clarify the calculation of the Khx sync lines */
        tmpLines = fsynclen * nbSync / ptrFile->nbSync1 ;  /* ~0.175 s pro line */

        if (tmpLines > 7) {
            nbLines = (tmpLines +4) /8 ;
            if (nbLines == 1)
                strncat(text, SYNC_KHX_TXT, cLL-1-strlen(text)) ;
        }
        else if (tmpLines > 3) {
            strncat(text, SYNC_KHX_TX4, cLL-1-strlen(text)) ;
            nbLines = 1 ;
        }
        else if (tmpLines > 1) {
            strncat(text, SYNC_KHX_TX2, cLL-1-strlen(text)) ;
            nbLines = 1 ;
        }
        else
            nbLines = 0 ;

        if (nbLines >0 && ptrFile->column_cnt >0 ) {
//            strncat(text, Eol, cLL-1-strlen(text)) ;
            error = WriteStringToFile (Eol, &ptrFile->ptrFd) ;
            if (error != ERR_OK) break ;
            ptrFile->column_cnt = 0 ;
        }
        /* Write the Synchro pattern */
        if (nbLines == 1) {
            strncat(text, Eol, cLL-1-strlen(text)) ;
            error = WriteStringToFile (text, &ptrFile->ptrFd) ;
            if (error != ERR_OK) break ;
            ptrFile->column_cnt = 0 ;
            text[0]='\0' ;
        }
        else
          for ( ii = 0 ; ii < nbLines ; ++ii ) {
            strncat(text, SYNC_KHX_TXT, cLL-1-strlen(text)) ;
            strncat(text, Eol, cLL-1-strlen(text)) ;

            error = WriteStringToFile (text, &ptrFile->ptrFd) ;
            if (error != ERR_OK) break ;
            ptrFile->column_cnt = 0 ;
            text[0]='\0' ;

          }
        if (error != ERR_OK) break ;

    } while (0) ;
    return (error);
}


int WriteSyncToWav (ulong  nbSync,
                FileInfo*  ptrFile)
{
    ulong  ii ;
    int    error = ERR_OK ;

    if (TAPc > 0) return (ERR_OK);
    if (KHXc > 0) return (WriteSyncToKhx(nbSync, ptrFile));

    do {
        /* Write the Synchro patern */
        for ( ii = 0 ; ii < nbSync ; ++ii ) {
            error = WriteBitToWav (1, ptrFile) ;
            if (error != ERR_OK) break ;
        }
        if (error != ERR_OK) break ;

    } while (0) ;
    return (error);
}


int WriteSyncToEWav (ulong  nbSync, /* sync bits */
                     ulong  nbSyncS,/* sync bits for space */
                     ulong  nbSync2,/* long/short intro bits */
                 FileInfo*  ptrFile)
{
    ulong  ii ;
    ulong  nbSyncSmin = 5000 ;        /* Minimal sync bits for space */
    int    error = ERR_OK ;

    static uint SyncCnt = 0 ;       /* 0: Header, 1...n: data blocks */

    if (TAPc > 0 || KHXc > 0) return (ERR_OK);

    do {
        if (nbSync2 != SYNC_E_HEAD || pcgrpId == GRP_E || (ptrFile->debug & (SYNCL_TRM | SYNCL_STD))>0 ) {
            /* for following blocks write space, not for first G/16 */

            if (nbSync2 != SYNC_E_HEAD) { /* not before first header block */
                ++SyncCnt ;
                /* Write the stop bit of the last block and pull down the level */
                error = WriteBitToEWav (3, ptrFile) ;
                if (error != ERR_OK) break ;
            }
            // SyncCnt == 0
            else if ((ptrFile->debug & (SYNCL_TRM | SYNCL_STD))>0)
                 nbSyncSmin = ptrFile->nbSync1 *8 ;         /* 8s leading space */
            else nbSyncSmin = ptrFile->nbSync1 *3 + 375 ;   /* E500S series with CE-126P 3s leading space */

            if (pcgrpId == GRP_G ) {
                if (SyncCnt == 1) {
                     if (Scnt<2 && (ptrFile->debug & (SYNCL_TRM | SYNCL_STD))>0)
                                nbSyncSmin = ptrFile->nbSync1 *2 + 375 ; /* Space after header:   2.00 sec + 1/8 */
                }
                else if (SyncCnt > 1) {
                     if (Scnt<2 && (ptrFile->debug & (SYNCL_TRM | SYNCL_STD))>0)
                                nbSyncSmin = ptrFile->nbSync1 *4 + 375 ; /* Space data block:     4.00 sec + 1/8 */
                }
            }
            else if (pcgrpId == GRP_16) {

                if (SyncCnt == 1) {                                                             /*first data*/
                     if (Scnt<2 && (ptrFile->debug & SYNCL_TRM)>0)
                                nbSyncSmin = ptrFile->nbSync1 *3 + 375 ; /* Spc H: 3s, TRef: 2s, +1 for Rmt off/on from wav */
                }
                else if (ptrFile->ident == IDENT_PC16_DAT && SyncCnt > 1 && SyncCnt % 2 == 0 ){ /*data field body*/
                     if (Scnt<2 && (ptrFile->debug & SYNCL_TRM)>0)
                                nbSyncSmin = ptrFile->nbSync1 *9 + 375 ; /* Spc Ds:9s, TRef: 8s, +1 for Rmt off/on + 1/8 */
                }
                else if (SyncCnt > 0) {                                                         /*data field head, ASC */
                     if (Scnt<2 && (ptrFile->debug & SYNCL_TRM)>0)
                                nbSyncSmin = ptrFile->nbSync1 *5 + 375 ; /* Spc D: 5s, TRef: 4s, +1 for Rmt off/on + 1/8 */
                }

                if (Scnt<1 && SyncCnt > 0 && (ptrFile->debug & (SYNCL_TRM | SYNCL_STD))>0 &&
                    nbSync < 11000) nbSync = 11000 ; /* set shorts for syncing after header */
            }
            /* (pcgrpId == GRP_E) */
            else if (ptrFile->ident == IDENT_E_ASC){                                /* 3.x sec GRP_E ASC*/
                if (SyncCnt == 1) {
                    if (Scnt<2 && (ptrFile->debug & (SYNCL_TRM | SYNCL_STD))>0)
                                nbSyncSmin = ptrFile->nbSync1 *3 + 375 ;
                }
                else if (SyncCnt > 0) {
                    if (Scnt<2 && (ptrFile->debug & SYNCL_TRM)>0)
                                nbSyncSmin = 11* ptrFile->nbSync1 /2 + 375 ;        /* 5.5 sec next block */
                }
            }
            else { // pcgrpId == GRP_E and not E_ASC /
                if (SyncCnt > 0) {
                    if (Scnt<2 && (ptrFile->debug & (SYNCL_TRM | SYNCL_STD))>0)
                                nbSyncSmin = ptrFile->nbSync1 *4 ;
                }
                /* if (Scnt != 2 && SyncCnt > 0) {
                    nbSyncSmin = 11* ptrFile->nbSync1 /4 ;           // min. 2.75 sec, > 8000 + tolerance /
                    // if (nbSyncSmin < nbSync ) nbSyncSmin = nbSync ;
                } */
            }
            if (nbSyncS < nbSyncSmin) nbSyncS = nbSyncSmin ;
            /* Write the space (silence) */
            for ( ii = 0 ; ii < nbSyncS ; ++ii ) {
                error = WriteBitToEWav (2, ptrFile) ;
                if (error != ERR_OK) break ;
            }
        }
        if (error != ERR_OK) break ;
        /* Write the Synchro pattern */
        for ( ii = 0 ; ii < nbSync ; ++ii ) {
            error = WriteBitToEWav (0, ptrFile) ;
            if (error != ERR_OK) break ;
        }
        if (error != ERR_OK) break ;

        /* Write the E block Synchro pattern */
        for ( ii = 0 ; ii < nbSync2 ; ++ii ) {
            error = WriteBitToEWav (1, ptrFile) ;
            if (error != ERR_OK) break ;
        }
        if (error != ERR_OK) break ;
        for ( ii = 0 ; ii < nbSync2 ; ++ii ) {
            error = WriteBitToEWav (0, ptrFile) ;
            if (error != ERR_OK) break ;
        }
        if (error != ERR_OK) break ;
        /* Write the E block start bit */
        error = WriteBitToEWav (1, ptrFile) ;

    } while (0) ;
    return (error);
}


int WriteByteToSWav (ulong value,
                 FileInfo* ptrFile)
{
      uint  tmp ;
      uint  ii ;
      int  error ;

    do {
        /* no start bit */
        tmp = 0x01 ; /* bit mask */
        for ( ii = 0 ; ii < 8 ; ++ii ) {
            if ( (value & tmp) == 0 )
                error = WriteBitToSWav (0, ptrFile) ;
            else
                error = WriteBitToSWav (1, ptrFile) ;
            if (error != ERR_OK) break ;
            tmp <<= 1 ;
        }
        if (error != ERR_OK) break ;
        /* no stop bits */

    } while (0) ;
    return (error);
}


int WriteSyncToSWav (ulong  blocktype, /* sync end mark */
                 FileInfo*  ptrFile)
{
    ulong  ii ;
    int    error = ERR_OK ;

    if (TAPc > 0 || KHXc > 0) return (ERR_OK);

    do {
        /* Write the Synchro patern */
        for ( ii = 0 ; ii < SUPT_SYN_NB ; ++ii ) {
            error = WriteByteToSWav (SUPT_SYNC, ptrFile) ;
            if (error != ERR_OK) break ;
        }
        if (error != ERR_OK) break ;

        error = WriteByteToSWav (blocktype, ptrFile) ;
        if (error != ERR_OK) break ;


    } while (0) ;
    return (error);
}


int WriteQuaterToKhx (uint  value,
                      FileInfo*  ptrFile)
{
     uint  lsq=0, msq='Q' ;
      int  error ;

    lsq = value & 0x0F ;
    if (lsq < 0xA) lsq += '0' ;
    else           lsq += ('A'-0xA) ;

	do {
		error = fputc (msq, ptrFile->ptrFd) ;
    	if (error != EOF) error = fputc (lsq, ptrFile->ptrFd) ;
    	if (error == EOF) {
        	printf ("%s: Can't write in the file\n", argP) ;
        	error = ERR_NOK ;
        	break ;
    	}
    	else {
        	error = ERR_OK ;
            ++ptrFile->total_raw ;
            ++ptrFile->column_cnt;
        }
	} while (0);
    return (error);
}


int WriteQuaterToTap (uint  value,
                      FileInfo*  ptrFile)
{
      int  error ;

	do {
		error = fputc (0xF0 | value, ptrFile->ptrFd) ;
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


int WriteQuaterToWav (uint   value,
                      uint   stopBits,
                 FileInfo*   ptrFile)
{
      uint  tmp ;
      uint  ii ;
       int  error ;

    if (KHXc > 0) return (WriteQuaterToKhx (value, ptrFile)); /* khx format not used for PC-1500 with DSave */
    if (TAPc > 0) return (WriteQuaterToTap (value, ptrFile));

    do {
        error = WriteBitToWav (0, ptrFile) ;
        if (error != ERR_OK) break ;

        for ( ii = 0 ; ii < 4 ; ++ii ) {
            tmp = 1 << ii ;
            if ( (value & tmp) == 0 )
                error = WriteBitToWav (0, ptrFile) ;
            else
                error = WriteBitToWav (1, ptrFile) ;

            if (error != ERR_OK) break ;
        }
        if (error != ERR_OK) break ;

        for ( ii = 0 ; ii < stopBits ; ++ii ) {
            error = WriteBitToWav (1, ptrFile) ;
            if (error != ERR_OK) break ;
        }
        if (error != ERR_OK) break ;

    } while (0) ;
    return (error);
}


int WriteByteToKhx    ( ulong  value,
                        uchar  order,
                    FileInfo*  ptrFile)
{
  ulong  msq=0, lsq=0 ;
    int  error = ERR_OK ;

        lsq = value & 0x0F ;
        if (lsq < 0xA) lsq += '0' ;
        else           lsq += ('A'-0xA) ;

        msq = (value >> 4) & 0x0F ;
        if (msq < 0xA) msq += '0' ;
        else           msq += ('A'-0xA) ;

    do {
        if (order == ORDER_INV) {
            error = fputc (lsq, ptrFile->ptrFd) ;
            if (error == EOF) break ;
            error = fputc (msq, ptrFile->ptrFd) ;
        }
        else {
            error = fputc (msq, ptrFile->ptrFd) ;
            if (error == EOF) break ;
            error = fputc (lsq, ptrFile->ptrFd) ;
        }
	} while (0);
	if (error == EOF)
        error = ERR_FILE ;
    else {
        error = ERR_OK ;
        ++ptrFile->total_raw ;

        if (++ptrFile->column_cnt >= cKHX ) {
            error = WriteStringToFile (Eol, &ptrFile->ptrFd) ;
            ptrFile->column_cnt = 0 ;
        }
    }
    if (error != ERR_OK) {
        printf ("%s: Can't write to the destination file\n", argP) ;
        error = ERR_NOK ;
    }
    return (error);
}


int WriteByteToTap    ( ulong  value,
                        uchar  order,
                    FileInfo*  ptrFile)
{
  ulong  msq, lsq ;
    int  error ;

    do {
        if ( pcgrpId == IDENT_PC1500 ) {
            lsq = value & 0x0F ;
            msq = (value >> 4) & 0x0F ;

            if (order == ORDER_INV) {
                error = WriteQuaterToTap (lsq, ptrFile) ;
                if (error != ERR_OK) break ;
                error = WriteQuaterToTap (msq, ptrFile) ;
        	}
            else {
                error = WriteQuaterToTap (msq, ptrFile) ;
                if (error != ERR_OK) break ;
                error = WriteQuaterToTap (lsq, ptrFile) ;
            }
        }
        else {
            error = fputc (value, ptrFile->ptrFd) ;
            if (error == EOF) {
                printf ("%s: Can't write in the file\n", argP) ;
                error = ERR_NOK ;
                break ;
            }
            else
                error = ERR_OK ;
        }

	} while (0);
    return (error);
}


int WriteByteToEWav (ulong value,
                 FileInfo* ptrFile)
{
      uint  tmp ;
      uint  ii ;
      int  error ;

    do {
        /* write the start bit */
        error = WriteBitToEWav (1, ptrFile) ;
        if (error != ERR_OK) break ;

        tmp = 0x80 ; /* bit mask */
        for ( ii = 0 ; ii < 8 ; ++ii ) {
            if ( (value & tmp) == 0 )
                error = WriteBitToEWav (0, ptrFile) ;
            else
                error = WriteBitToEWav (1, ptrFile) ;
            if (error != ERR_OK) break ;
            tmp >>= 1 ;
        }
        if (error != ERR_OK) break ;
        /* no stop bits */

    } while (0) ;
    return (error);
}


int WriteByteToQWav (ulong value,
                 FileInfo* ptrFile)
{
      uint  tmp ;
      uint  ii ;
      int  error ;

    do {
        /* write the start bit */
        error = WriteBitToWav (0, ptrFile) ;
        if (error != ERR_OK) break ;

        tmp = 0x01 ; /* bit mask */
        for ( ii = 0 ; ii < 8 ; ++ii ) {
            if ( (value & tmp) == 0 )
                error = WriteBitToWav (0, ptrFile) ;
            else
                error = WriteBitToWav (1, ptrFile) ;
            if (error != ERR_OK) break ;
            tmp <<= 1 ;
        }
        if (error != ERR_OK) break ;

        /* stop bits */
        for ( ii = 0 ; ii < 2 ; ++ii ) {
            error = WriteBitToWav (1, ptrFile) ;
            if (error != ERR_OK) break ;
        }
        if (error != ERR_OK) break ;

    } while (0) ;
    return (error);
}


int WriteByteToWav (ulong  value,
                    uchar  order,
                    uchar  mode,
                FileInfo*  ptrFile)
{
      uint  lsq ;
      uint  msq ;
      int  error ;

    if (KHXc > 0) return (WriteByteToKhx (value, order, ptrFile)) ;
    if (TAPc > 0) return (WriteByteToTap (value, order, ptrFile)) ;

    if (order == ORDER_E) return (WriteByteToEWav (value, ptrFile)) ;
    if (order == ORDER_S) return (WriteByteToSWav (value, ptrFile)) ;
    if (order == ORDER_Q) return (WriteByteToQWav (value, ptrFile)) ;

    do {
        lsq = value & 0x0F ;
        msq = (value >> 4) & 0x0F ;
        if (order == ORDER_INV) {
            error = WriteQuaterToWav (lsq, Mode[mode].stopb1, ptrFile) ;
            if (error != ERR_OK) break ;
            error = WriteQuaterToWav (msq, Mode[mode].stopb2, ptrFile) ;
            if (error != ERR_OK) break ;
        }
        else {
            error = WriteQuaterToWav (msq, Mode[mode].stopb1, ptrFile) ;
            if (error != ERR_OK) break ;
            error = WriteQuaterToWav (lsq, Mode[mode].stopb2, ptrFile) ;
            if (error != ERR_OK) break ;
        }

    } while (0) ;
    return (error);
}

/*
int WriteIdentToB22Wav (ulong  value, FileInfo*  ptrFile)
replaced by WriteQuater
*/
/*  WriteByteToB22Wav*/
int WriteByteTo15Wav (ulong value, FileInfo* ptrFile)
{
    return( WriteByteToWav(value, ORDER_INV, ptrFile->mode, ptrFile)) ;
}

int WriteByteTo156Wav (ulong value, FileInfo* ptrFile)
{
    uchar order;
    if (ptrFile->mode == MODE_B9) order = ORDER_E ;
    else if (ptrFile->mode == MODE_B11) order = ORDER_Q ;
    else order = ORDER_INV ; /* PC-1500 originally */

    return( WriteByteToWav(value, order, ptrFile->mode, ptrFile)) ;
}
/*
int WriteByteToB19Wav (ulong  value, FileInfo*  ptrFile)
replaced by WriteByte
int WriteByteToB16Wav (ulong  value, FileInfo*  ptrFile)
replaced by WriteByte
int WriteByteToB13Wav (ulong  value, FileInfo*  ptrFile)
replaced by WriteByte
int WriteByteToDataWav (ulong  value,
                       FileInfo*  ptrFile)
    byte was swapped before because of uniform Checksum calculation
replaced by WriteByte
*/

int CheckSumB1 (  ulong  Byte,
              FileInfo*  ptrFile)
{
    ushort sum ;

    /* Update the checksum */
        sum = ptrFile->sum + ((Byte & 0xF0) >> 4) ;
        if (sum > 0xFF) {
            ++sum ;
            sum &= 0xFF ;
            }
        ptrFile->sum = (sum + (Byte & 0x0F)) & 0xFF ;

    return (0);
}


int CheckSumE (  ulong  Byte,
                ulong*  ptrSum)
//              FileInfo*  ptrFile)
{
    uint tmp, ii ;

    /* Update the checksum */
    tmp = 0x80 ;
    for ( ii = 0 ; ii < 8 ; ++ii, tmp >>= 1 )
        if ( (Byte & tmp) != 0 )  ++ *ptrSum ;//++ ptrFile->sum ;

    return (0);
}


int WriteUsedatLenToQTWav ( uchar  order, /* Quick-Tape incomplete blocks with fill data */
                            uchar  mode,
                        FileInfo*  ptrFile)
{   long tmpL ;
    int  error ;

    tmpL = ptrFile->nbByte - ptrFile->total_diff - ptrFile->total ; //not for IDENT_QT_DAT: variable block in RAM based

    if (tmpL > 0) {
            if (tmpL > BLK_OLD) tmpL = BLK_OLD ;
            --tmpL ;
            if (tmpL < BLK_OLD -1) ptrFile->usedat_len = tmpL + 1 ;
            else ptrFile->usedat_len = 0 ; /* L:0x4F ignored, no effect */

            error = WriteByteToWav (tmpL, order, mode, ptrFile) ;
            if (error != ERR_OK) return (error) ;
            if ( (ptrFile->debug & 0x0040) > 0 ) printf(" (L:%02X)", (uint) tmpL);

            ptrFile->sum = tmpL ;
    }
    else if (tmpL == 0 ) error = ERR_OK ;
    else {
            printf(" WUsedatLQT: End of file was expected");
            error = ERR_FMT ;
    }
    ptrFile->count = 0 ;

    return (error);
}


int WriteByteSumToWav (ulong  value,
                       uchar  order,
                       uchar  mode,
                       FileInfo*  ptrFile)
{
    int   error ;
    bool  writ_full_block = false ;

    do {

        if ( (ptrFile->debug & 0x0040) > 0) {
            printf(" %02X", (uchar) value);
            if ( ptrFile->total %0x100 == 0xFF ) printf("\n");
        }
        error = WriteByteToWav (value, order, mode, ptrFile) ;
        if (error != ERR_OK) break ;

        if (mode == MODE_B22 || mode == MODE_B11) ptrFile->sum += value ;
        else if (mode == MODE_B9 || mode == MODE_B10) CheckSumE (value, &ptrFile->sum) ; //ptrFile
        else CheckSumB1 (value, ptrFile) ;

        ++ptrFile->count ;
        if (!writ_full_block) ++ptrFile->total ;

        if ( ptrFile->usedat_len > 0) { /* QTape incomplete block */
            if (--ptrFile->usedat_len == 0) {
                if ( ( (ptrFile->debug & 0x0040) > 0 ) && (Qcnt == 0) ) printf(" Fill data:");
                value = 0x00 ;
                writ_full_block = true ;
            }
        }


        switch (mode) {
        case MODE_B22 :
            if ( ptrFile->count >= BLK_OLD ) {

                if ( (ptrFile->debug & 0x0040) > 0 )
                    printf(" (%04X)", (uint) ptrFile->sum);

                /* Write the checksum */
                error = WriteByteToWav (ptrFile->sum >> 8 & 0xFF, order, mode, ptrFile) ;
                if (error != ERR_OK) break ;
                error = WriteByteToWav (ptrFile->sum & 0xFF, order, mode, ptrFile) ;
                if (error != ERR_OK) break ;

                ptrFile->count = 0 ;
                ptrFile->sum   = 0 ;
            }
            break ;

        case MODE_B21   :
        case MODE_B20   :
        case MODE_B20_2 :
        case MODE_B19   :
        case MODE_B19_2 :
            if ( (ptrFile->count % BLK_OLD_SUM) == 0) {

                if ( (ptrFile->debug & 0x0040) > 0 )
                    printf(" (%02X)", (uchar) ptrFile->sum);

                /* Write the checksum */
                error = WriteByteToWav (ptrFile->sum, order, mode, ptrFile) ;
                if (error != ERR_OK) break ;

                if ( ptrFile->count >= BLK_OLD ) {
                    ptrFile->count = 0 ;
                    ptrFile->sum   = 0 ;

                    if (ptrFile->ident == IDENT_PC1211) {
                        if ( (ptrFile->debug & SYNCL_STD) > 0 ) /* default 1803 bits, DATA not */
                            error = WriteSyncToWav (1803, ptrFile) ;
                        else
                            error = WriteSyncToWav (ptrFile->nbSync, ptrFile) ;
                    }
                }
            }
            break ;

        case MODE_B17 :
        case MODE_B16 :
        case MODE_B15 :
            if ( ptrFile->count >= BLK_OLD_SUM) {

                if ( (ptrFile->debug & 0x0040) > 0 )
                    printf(" (%02X)", (uchar) ptrFile->sum);

                /* Write the checksum */
                error = WriteByteToWav (ptrFile->sum, order, mode, ptrFile) ;
                if (error != ERR_OK) break ;

                ptrFile->count = 0 ;
                ptrFile->sum   = 0 ;
            }
            break ;

        case MODE_B14   :
        case MODE_B14_2 :
        case MODE_B13   :
            if ( ptrFile->count >= BLK_NEW) {

                if ( (ptrFile->debug & 0x0040) > 0 )
                    printf(" (%02X)", (uchar) ptrFile->sum);

                /* Write the checksum */
                error = WriteByteToWav (ptrFile->sum, order, mode, ptrFile) ;
                if (error != ERR_OK) break ;

                ptrFile->count = 0 ;
                ptrFile->sum   = 0 ;
            }
            break ;

        case MODE_B9 : /* PC-E/G/1600 */
            if ( ptrFile->count >= ptrFile->block_len ) {

                if ( (ptrFile->debug & 0x0040) > 0 )
                    printf(" (%04X)", (uint) ptrFile->sum & 0xFFFF);

                /* Write the checksum */
                error = WriteByteToWav (ptrFile->sum >> 8 & 0xFF, order, mode, ptrFile) ;
                if (error != ERR_OK) break ;
                error = WriteByteToWav (ptrFile->sum & 0xFF, order, mode, ptrFile) ;
                if (error != ERR_OK) break ;

                ptrFile->count = 0 ;
                ptrFile->sum   = 0 ;
            }
            break ;

        case MODE_B10 : /* SuperTape */
            if ( ptrFile->count >= ptrFile->block_len ) {

                if ( (ptrFile->debug & 0x0040) > 0 )
                    printf(" (%04X)", (uint) ptrFile->sum & 0xFFFF);

                /* Write the checksum */
                error = WriteByteToWav (ptrFile->sum & 0xFF, order, mode, ptrFile) ;
                if (error != ERR_OK) break ;
                error = WriteByteToWav (ptrFile->sum >> 8 & 0xFF, order, mode, ptrFile) ;
                if (error != ERR_OK) break ;

                if ( (ptrFile->debug & 0x0040) > 0) printf(" %02X", (uchar) SUPT_END);
                error = WriteByteToWav (SUPT_END, order, mode, ptrFile) ;
                if (error != ERR_OK) break ;

                ptrFile->count = 0 ;
                ptrFile->sum   = 0 ;
            }
            break ;

        case MODE_B11 :
            if (QTc == 1) { /* Quick Tape after a standard header */
                if ( ptrFile->count % BLK_QT1 == 0 ) {

                    if ( (ptrFile->debug & 0x0040) > 0 )
                        printf(" (%04X)", (uint) ptrFile->sum);
                    /* Write the checksum */
                    error = WriteByteToWav (ptrFile->sum >> 8 & 0xFF, order, mode, ptrFile) ;
                    if (error != ERR_OK) break ;
                    error = WriteByteToWav (ptrFile->sum & 0xFF, order, mode, ptrFile) ;
                    if (error != ERR_OK) break ;

                    ptrFile->count = 0 ; /* first block may be shorter, other are full blocks */
                    ptrFile->sum   = 0 ;
                }
                break;
            }
            if ( ptrFile->count >= BLK_OLD ) {

                if ( (ptrFile->debug & 0x0040) > 0 )
                    printf(" (%04X)", (uint) ptrFile->sum);
                /* Write the checksum */
                error = WriteByteToWav (ptrFile->sum >> 8 & 0xFF, order, mode, ptrFile) ;
                if (error != ERR_OK) break ;
                error = WriteByteToWav (ptrFile->sum & 0xFF, order, mode, ptrFile) ;
                if (error != ERR_OK) break ;

                error = WriteByteToWav (EOF_15, order, mode, ptrFile) ;
                if (error != ERR_OK) break ;
                if ( (ptrFile->debug & 0x0040) > 0) printf(" (E:%02X)", (uint) EOF_15);
                writ_full_block = false ;

                error = WriteSyncToWav (50, ptrFile) ; /* 0.02 s */
                if (error != ERR_OK) break ;
                error = WriteUsedatLenToQTWav (order, mode, ptrFile) ;
            }
            break ;

        default :
            printf ("%s: Unknown Mode\n", argP) ;
            break ;
        }

    } while (writ_full_block) ;

    return (error);
}

/*  WriteByteSumToB22Wav */
int WriteByteSumTo15Wav (ulong value, FileInfo* ptrFile)
{
    return( WriteByteSumToWav(value, ORDER_INV, ptrFile->mode, ptrFile)) ;
}

int WriteByteSumTo156Wav (ulong value, FileInfo* ptrFile)
{
    uchar order;
    if (ptrFile->mode == MODE_B9) order = ORDER_E ;
    else if (ptrFile->mode == MODE_B11) order = ORDER_Q ;
    else order = ORDER_INV ;

    return( WriteByteSumToWav(value, order, ptrFile->mode, ptrFile)) ;
}

/* int WriteByteSumToB19Wav (ulong value, FileInfo* ptrFile)
{
    return( WriteByteSumToWav(value, ORDER_STD, MODE_B19, ptrFile)) ;
} */
/* int WriteByteSumToB16Wav (ulong value, FileInfo* ptrFile)
{
    return( WriteByteSumToWav(value, ORDER_STD, MODE_B16, ptrFile)) ;
} */
/* int WriteByteSumToB13Wav (ulong value, FileInfo* ptrFile)
{
    return( WriteByteSumToWav(value, ORDER_STD, MODE_B13, ptrFile)) ;
} */

/* Data Blocks and Data Header are not swapped */
/* Byte swapped before checksum with uniform calculation */

ulong SwapByte (ulong byte)
{
    return ( (byte >> 4) + (byte << 4 & 0xF0) );
}


int WriteByteSumToDataWav (ulong  value, uchar  mode,
                          FileInfo*  ptrFile)
{
      int  error ;

    do {
        if ( (ptrFile->debug & 0x0040) > 0 )
            printf(" %02X", (uchar) value);

        /* byte swapped before because of uniform checksum calculation */
        value = SwapByte(value) ;
        /* Write the byte */
        error = WriteByteToWav (value, ORDER_STD, mode, ptrFile) ;
        if (error != ERR_OK) break ;
        ++ptrFile->total ;

        /* Update the checksum */
        CheckSumB1 (value, ptrFile) ;

        /* Update an check the byte counter */
        if ( ++ptrFile->count >= BLK_OLD_SUM) {

            /* Write the checksum */
            if ( (ptrFile->debug & 0x0040) > 0 )
                printf(" (%02X)", (uchar) ptrFile->sum);

            error = WriteByteToWav (ptrFile->sum, ORDER_STD, mode, ptrFile) ;
            if (error != ERR_OK) break ;

            ptrFile->count = 0 ;
            ptrFile->sum = 0 ;
        }

    } while (0) ;
    return (error);
}

/* File name and header for PC-1500 */
/*  WriteHeadToB22Wav */
int WriteHeadTo15Wav (char*  ptrName,
                       ulong  addr,
                       ulong  eaddr,
                       ulong  size,
/*                     ushort flags, Pos. of Quick-Tape flags in standard header (PC-1500) is unknown. */
                       uchar  type,
                       FileInfo*  ptrFile)
{
     uint  ii ;
    ulong  len ;
    ulong  tmpL ;
     char  tmpS[20] ;
      int  error ;

    do {
        /* Search the length */
        tmpL = strlen (ptrName) ;
        if (tmpL > 16)
            tmpL = 16 ;

        for ( ii = 0 ; ii < tmpL ; ++ii )
            tmpS[ii] = ptrName[ii] ;
        for ( ii = tmpL ; ii < 17 ; ++ii )
            tmpS[ii] = 0 ;

        if (Qcnt == 0) printf ("Save name    : %s\n", tmpS) ;
        strncpy( ptrName, tmpS, cLPF-1) ;

        /* Write the Header */
        ptrFile->count = 0 ;
        ptrFile->sum   = 0 ;
        for ( ii = 0x10 ; ii < 0x18 ; ++ii ) {
            error = WriteByteSumTo15Wav (ii, ptrFile) ;
            if (error != ERR_OK) break ;
        }
        if (error != ERR_OK) break ;

        /* Write the Sub-Ident */
        if (type == TYPE_DAT)
            tmpL = 0x04 ;
        else if (type == TYPE_DEF)
            tmpL = 0x03 ;
        else if (type == TYPE_RSV)
            tmpL = 0x02 ;
        else if (type == TYPE_BIN) {
            if (QTc>0) tmpL = IDENT_PC15QTBIN & 0x0F ;
            else tmpL = 0x00 ;
        }
        else { // TYPE_IMG
            if (QTc>0) tmpL = IDENT_PC15QTBAS & 0x0F ;
            else tmpL = 0x01 ;
        }
        error = WriteByteSumTo15Wav (tmpL, ptrFile) ;
        if (error != ERR_OK) break ;

        /* Write the Name */
        for ( ii = 0 ; ii < 16 ; ++ii ) {
            error = WriteByteSumTo15Wav (tmpS[ii], ptrFile) ;
            if (error != ERR_OK) break ;
        }
        if (error != ERR_OK) break ;

        /* TODO (Mr#3#):  Position of Quick-Tape flags in PC-1500 header */
        /* Write 9 null bytes */
        for ( ii = 0 ; ii < 9 ; ++ii ) {
            error = WriteByteSumTo15Wav (0, ptrFile) ;
            if (error != ERR_OK) break ;
        }
        if (error != ERR_OK) break ;

        /* Write the address */
        if (type==TYPE_IMG && addr==0) addr = 0xC5 ; /* RSV length before BASIC program */

        tmpL = (addr >> 8) & 0xFF ;
        error = WriteByteSumTo15Wav (tmpL, ptrFile) ;
        if (error != ERR_OK) break ;

        tmpL = addr & 0xFF ;
        error = WriteByteSumTo15Wav (tmpL, ptrFile) ;
        if (error != ERR_OK) break ;

        /* Write the Buffer Size */
        if (type == TYPE_DAT)
            len = 0 ;
        else if (type == TYPE_BIN || type == TYPE_RSV || type == TYPE_DEF)
            len = size - 1 ;
        else
            len = size ;

        tmpL = (len >> 8) & 0xFF ;
        error = WriteByteSumTo15Wav (tmpL, ptrFile) ;
        if (error != ERR_OK) break ;

        tmpL = len & 0xFF ;
        error = WriteByteSumTo15Wav (tmpL, ptrFile) ;
        if (error != ERR_OK) break ;

        /* Write the entry address */
        tmpL = (eaddr >> 8) & 0xFF ;
        error = WriteByteSumTo15Wav (tmpL, ptrFile) ;
        if (error != ERR_OK) break ;

        tmpL = eaddr & 0xFF ;
        error = WriteByteSumTo15Wav (tmpL, ptrFile) ;
        if (error != ERR_OK) break ;

        /* Write the checksum */
        tmpL = (ptrFile->sum >> 8) & 0xFF ;
        error = WriteByteTo15Wav (tmpL, ptrFile) ;
        if (error != ERR_OK) break ;

        tmpL = ptrFile->sum & 0xFF ;
        error = WriteByteTo15Wav (tmpL, ptrFile) ;
        if (error != ERR_OK) break ;

        if ( (ptrFile->debug & 0x0040) > 0 )
            printf(" (%04X)", (uint) ptrFile->sum);

        if (type == TYPE_DAT)       /* originally 1 sec */
            error = WriteSyncToWav (ptrFile->nbSync, ptrFile) ;
        else
            error = WriteSyncToWav (75, ptrFile) ;
        if (error != ERR_OK) break ;

        ptrFile->count = 0 ;

        if (QTc>0) { /* switch to QT1 */

            ptrFile->block_len = BLK_QT1 ;
            ptrFile->count = BLK_QT1-(size & 0xFF) ; /* QTAPE 1 counts backward */
            if (ptrFile->ident == IDENT_PC15QTBAS) -- ptrFile->count ;

            if (type == TYPE_IMG) ptrFile->ident = IDENT_QT_BAS ;
            else if (type == TYPE_BIN) ptrFile->ident = IDENT_QT_BIN ;

            pcgrpId = IDENT_QTAPE ;
            ptrFile->mode = MODE_B11 ;
            bit = bitQ ;
            ptrFile->bitLen= strlen (bit[0]) ;

            error = WriteSyncToWav (656, ptrFile) ; /* 0.35 s */
            if (error != ERR_OK) break ;
            ptrFile->total = 0 ;
        }

        ptrFile->sum = 0 ;

        if ( (ptrFile->debug & DEBUG_TRACES) > 0) printf("\n") ;

    } while (0) ;
    return (error);
}

/* File name and header for Quick-Tape PC-1500 */
int WriteHeadToQWav (char*  ptrName,
                       ulong  addr,
                       ulong  eaddr,
                       ulong  size,
                       ushort flags,
                       uchar  type,
                       FileInfo*  ptrFile)
{
     uint  ii ;
    ulong  len ;
    ulong  tmpL ;
     char  tmpS[17] ;
    uchar  tmpH[20] ;
    uchar  order = ORDER_Q;
    uchar  mode = ptrFile->mode_h ;
      int  error ;

    do {
        /* Search the length */
        tmpL = strlen (ptrName) ;
        if (tmpL > 16)
            tmpL = 16 ;

        for ( ii = 0 ; ii < tmpL ; ++ii )
            tmpS[ii] = ptrName[ii] ;
        for ( ii = tmpL ; ii < 17 ; ++ii )
            tmpS[ii] = 0 ;

        if (Qcnt == 0) printf ("Save name    : %s\n", tmpS) ;
        strncpy( ptrName, tmpS, cLPF-1) ;

        /* Write the Header */
        for ( ii = 0x10 ; ii < 0x18 ; ++ii ) {
            error = WriteByteSumToWav (ii, order, mode, ptrFile) ;
            if (error != ERR_OK) break ;
        }
        if (error != ERR_OK) break ;

        ptrFile->count = 0 ;
        ptrFile->sum   = 0 ;
        /* Write the Sub-Ident */
        tmpL = ptrFile->ident ;

        error = WriteByteSumToWav (tmpL, order, mode, ptrFile) ;
        if (error != ERR_OK) break ;

        /* Write the Name */
        for ( ii = 0 ; ii < 16 ; ++ii ) {
            error = WriteByteSumToWav (tmpS[ii], order, mode, ptrFile) ;
            if (error != ERR_OK) break ;
        }
        if (error != ERR_OK) break ;

        /* 9 bytes 0 */
        for ( ii = 0 ; ii < 9 ; ++ii ) {
            tmpH[ii]=0 ;
        }
        if (type == TYPE_BIN ) {

            tmpH[0] = flags ; /* 2.RAM ME1:4, PV1:2, PU1:1 */
            tmpH[1] = 0xFF - flags ;

            /* Entry address */
            tmpH[7] = (eaddr >> 8) & 0xFF ;
            tmpH[8] = eaddr & 0xFF ;
        }
        /* Start address */
        if (type==TYPE_IMG && addr==0) addr = 0xC5 ; /* RSV length before BASIC program */

        tmpH[9] = (addr >> 8) & 0xFF ;
        tmpH[10] = addr & 0xFF ;

        /* Size of file */
        if (type == TYPE_DAT) {
            ptrFile->nbByte = size ;
            len = 0 ;
        }
        else if (type == TYPE_IMG) {
            ptrFile->nbByte = size +1 ;
            len = size ;
        }
        else { //if (type == TYPE_BIN || type == TYPE_RSV || type == TYPE_DIM)
            ptrFile->nbByte = size ;
            len = size - 1 ;
        }
        tmpH[11] = (len >> 8) & 0xFF ;
        tmpH[12] = len & 0xFF ;

        /* Qtape: entry address not here */
        tmpH[13] = 0 ;
        tmpH[14] = 0 ;

        /* Write the rest of header */
        for ( ii = 0 ; ii < 15 ; ++ii ) {
            error = WriteByteSumToWav (tmpH[ii], order, mode, ptrFile) ;
            if (error != ERR_OK) break ;
        }
        if (error != ERR_OK) break ;

        /* Write the checksum and block end mark */
        tmpL = (ptrFile->sum >> 8) & 0xFF ;
        error = WriteByteToWav (tmpL, order, mode, ptrFile) ;
        if (error != ERR_OK) break ;

        tmpL = ptrFile->sum & 0xFF ;
        error = WriteByteToWav (tmpL, order, mode, ptrFile) ;
        if (error != ERR_OK) break ;

        if ( (ptrFile->debug & 0x0040) > 0 )
            printf(" (%04X)", (uint) ptrFile->sum);

        tmpL = EOF_15 ;
        error = WriteByteToWav (tmpL, order, mode, ptrFile) ;
        if (error != ERR_OK) break ;

        if ( (ptrFile->debug & 0x0040) > 0 )
            printf(" (E:%02X)", (uint) tmpL);

        /* Write the sync to next block */
        if (type == TYPE_DAT) {
            error = WriteSyncToWav (ptrFile->nbSync1, ptrFile) ; /* 1s (+20 ms) */
            ptrFile->count = 0 ;
            ptrFile->sum   = 0 ;
            /* Data header follows with 2 bytes of variable name but without useful data_Len */
        }
        else {
            error = WriteSyncToWav (875, ptrFile) ; /* 0.35 s */
            if (error != ERR_OK) break ;
            ptrFile->total = 0 ;
            /* Write the length of the useful data of the next block */
            error = WriteUsedatLenToQTWav (order, mode, ptrFile) ;
        }
        if (error != ERR_OK) break ;

        if ( (ptrFile->debug & DEBUG_TRACES) > 0) printf("\n") ;

    } while (0) ;
    return (error);
}


int WriteHeadToSWav (char*  ptrName,
                       ulong  addr,
                       ulong  eaddr,
                       ulong  size,
                       uchar  type,
                      ushort  flags,
                       FileInfo*  ptrFile)
{
     uint  ii ;
    ulong  len ;
    ulong  tmpL ;
     char  tmpS[20] ;
    uchar  mode = ptrFile->mode_h ;
      int  error ;

    do {
        /* Search the length */
        tmpL = strlen (ptrName) ;
        if (tmpL > 16)
            tmpL = 16 ;

        for ( ii = 0 ; ii < tmpL ; ++ii )
            tmpS[ii] = ptrName[ii] ;
        for ( ii = tmpL ; ii < 17 ; ++ii )
            tmpS[ii] = 0 ;

        if (Qcnt == 0) printf ("Save name    : %s\n", tmpS) ;
        strncpy( ptrName, tmpS, cLPF-1) ;

        /* Write the Header */
        ptrFile->block_len = BLK_S_HEAD ;
        ptrFile->count = 0 ;
        ptrFile->sum   = 0 ;

        /* Write the Name */
        for ( ii = 0 ; ii < 16 ; ++ii ) {
            error = WriteByteSumToWav ( tmpS[ii], ORDER_S, mode, ptrFile) ;
            if (error != ERR_OK) break ;
        }
        if (error != ERR_OK) break ;

        error = WriteByteSumToWav ( flags & 0xFF, ORDER_S, mode, ptrFile) ;
        if (error != ERR_OK) break ;

        /* Write the address */
        if (type==TYPE_IMG && addr==0) addr = 0xC5 ; /* RSV length before BASIC program */

        tmpL = addr & 0xFF ;
        error = WriteByteSumToWav ( tmpL, ORDER_S, mode, ptrFile) ;
        if (error != ERR_OK) break ;

        tmpL = (addr >> 8) & 0xFF ;
        error = WriteByteSumToWav ( tmpL, ORDER_S, mode, ptrFile) ;
        if (error != ERR_OK) break ;

        /* Write the Buffer Size, length was corrected in ReadFileLength */
        len = size ;

        tmpL = len & 0xFF ;
        error = WriteByteSumToWav ( tmpL, ORDER_S, mode, ptrFile) ;
        if (error != ERR_OK) break ;

        tmpL = (len >> 8) & 0xFF ;
        error = WriteByteSumToWav ( tmpL, ORDER_S, mode, ptrFile) ;
        if (error != ERR_OK) break ;

        /* Write the entry address */
        if (type == TYPE_BIN ) {
            if ((eaddr & 0xFFFF) == 0xFFFF) eaddr = 0x0000 ;

            tmpL = eaddr & 0xFF ;
            error = WriteByteSumToWav ( tmpL, ORDER_S, mode, ptrFile) ;
            if (error != ERR_OK) break ;

            tmpL = (eaddr >> 8) & 0xFF ;
            error = WriteByteSumToWav ( tmpL, ORDER_S, mode, ptrFile) ;
            if (error != ERR_OK) break ;

        }
        else {
            tmpL = 0x00 ;
            /* Write 2 null bytes */
            for ( ii = 0 ; ii < 2 ; ++ii ) {
                error = WriteByteSumToWav ( tmpL, ORDER_S, mode, ptrFile) ;
                if (error != ERR_OK) break ;
            }
            if (error != ERR_OK) break ;
        }
        tmpL = 0x00 ;
        error = WriteByteSumToWav ( tmpL, ORDER_S, mode, ptrFile) ;
        if (error != ERR_OK) break ;

        error = WriteByteSumToWav ( tmpL, ORDER_S, mode, ptrFile) ;
        if (error != ERR_OK) break ;
        /* Checksum written in WriteByteSum */

        if ((flags & 0x80) > 0) {     /* switch from 3600 to 7200 baud, not supported with PC-1500 */
            if (Qcnt == 0 ) printf ("%s: SuperTape baud rate switched to 7200\n", argP) ;
            bitS = bitS_7 ;
            for ( ii = 0 ; ii < 4; ++ii ) {bitLS [ii] = (uint) strlen (bitS[ii]); }
        }
        /* write the data block */
        error = WriteSyncToSWav ( SUPT_DATA, ptrFile) ;
        if (error != ERR_OK) break ;

        ptrFile->block_len = len ;
        ptrFile->count = 0 ;
        ptrFile->sum   = 0 ;

        if ( (ptrFile->debug & DEBUG_TRACES) > 0) printf("\n") ;

    } while (0) ;
    return (error);
}


/* File name and header for PC-E Series and newer */
int WriteHeadToEWav (char*  ptrName,
                     char*  ptrDstExt,
                     ulong  addr,
                     ulong  eaddr,
                     ulong  size,
                     ulong  nbSync,
                     ulong  nbSyncS,
                     uchar  type,
                 FileInfo*  ptrFile)
{
    ulong  haddr ; // , eaddr = 0xFFFFFF
   ushort  ident ;
    uchar  mode ;
     uint  ii, imax ;
    ulong  len ;
    ulong  tmpL ;
    ulong  tmpH[20] ;
     char  tmpS[20] ;
      int  error ;

    ident = ptrFile->ident ;
    mode  = ptrFile->mode_h ;

    ptrFile->block_len = BLK_E_HEAD ;
    ptrFile->count = 0 ;
    ptrFile->sum   = 0 ;

    if (ident != IDENT_E_BIN && Acnt < 2) eaddr = 0; /* 2. separate bin2wav parameter -addr, no entry: 0xFFFFFF */

    do {
        /*write the tap code */
        error = WriteByteSumToWav ( (ulong) ident, ORDER_E, mode, ptrFile) ;
        if (error != ERR_OK) break ;

        /* Search the name length */
        if ( pcgrpId == GRP_16) imax = 16 ; else imax = 9 ;
        tmpL = strlen (ptrName) ;
        if (tmpL > imax) tmpL = imax ;
        for ( ii = 0 ; ii < tmpL ; ++ii )
            tmpS[ii] = ptrName[ii] ;
        if ( pcgrpId == GRP_16) {
            for ( ii = tmpL ; ii < 16 ; ++ii ) tmpS[ii] = 0 ;
        }
        else {
            for ( ii = tmpL ; ii < 16 ; ++ii ) tmpS[ii] = 0x20 ;
        }
        /* ASCII: BAS, TXT */
        if (type == TYPE_BAS && pcgrpId != GRP_G)  for ( ii = 0 ; ii < 3 ; ++ii ) tmpS[13 + ii] = ptrDstExt[ii] ;
        if (type == TYPE_ASC && pcgrpId == GRP_16) for ( ii = 0 ; ii < 3 ; ++ii ) tmpS[13 + ii] = 0x20 ;

        /* Write the Name */
        tmpS[16] = 0 ;
        if (Qcnt == 0) printf ("Save name    : %s\n", tmpS) ;
        strncpy( ptrName, tmpS, cLPF-1) ;
        for ( ii = 0 ; ii < 16 ; ++ii ) {
            error = WriteByteSumToWav (tmpS[ii], ORDER_E, mode, ptrFile) ;
            if (error != ERR_OK) break ;
        }
        if (error != ERR_OK) break ;

        if ( ident == IDENT_PC16_CAS || (ident == IDENT_E_ASC && pcgrpId == GRP_16) )
             error = WriteByteSumToWav (0, ORDER_E, mode, ptrFile) ;
        else error = WriteByteSumToWav (0x0D, ORDER_E, mode, ptrFile) ;
        if (error != ERR_OK) break ;
        /* Write the Header */

        /* Add Length of BAS Header with start mark + end mark */
        if (ident == IDENT_E_BAS) {
            if ( pcgrpId == GRP_E)
                len = size + 19 + 1 ;
            else if ( pcgrpId == GRP_G)
                len = size + 12 + 0 ;
            else // pcgrpId == GRP_16
                len = size ;
        }
        else if (ident == IDENT_E_ASC || ident == IDENT_PC16_CAS || ident == IDENT_PC16_DAT)
            len = 0 ;
        else if (ident == IDENT_E_BIN)
            len = size ;
        else
            len = size ;

        /* Write the Buffer Size of the Data Block */
        tmpL = len & 0xFF ;
        error = WriteByteSumToWav (tmpL, ORDER_E, mode, ptrFile) ;
        if (error != ERR_OK) break ;

        tmpL = (len >> 8) & 0xFF ;
        error = WriteByteSumToWav (tmpL, ORDER_E, mode, ptrFile) ;
        if (error != ERR_OK) break ;

        tmpL = addr & 0xFF ;
        error = WriteByteSumToWav (tmpL, ORDER_E, mode, ptrFile) ;
        if (error != ERR_OK) break ;

        tmpL = (addr >> 8) & 0xFF ;
        error = WriteByteSumToWav (tmpL, ORDER_E, mode, ptrFile) ;
        if (error != ERR_OK) break ;

        tmpL = eaddr & 0xFF ;
        error = WriteByteSumToWav (tmpL, ORDER_E, mode, ptrFile) ;
        if (error != ERR_OK) break ;

        tmpL = (eaddr >> 8) & 0xFF ;
        error = WriteByteSumToWav (tmpL, ORDER_E, mode, ptrFile) ;
        if (error != ERR_OK) break ;

        /* Write the Sub-Ident (mode 2) */
        if (pcgrpId == GRP_16 && type == TYPE_RSV ) {
            tmpL = 0x02 ;
            ptrFile->ident = IDENT_E_BIN ;
        }
        else if ( ident == IDENT_E_BAS ||
                 (pcgrpId == GRP_G && type == TYPE_BAS ) )
            tmpL = 0x01 ;
        else if ((ident == IDENT_E_ASC && pcgrpId == GRP_E) ||
                  ident == IDENT_PC16_DAT)
            tmpL = 0x04 ; // GRP_E, IDENT_PC16_DAT
        else   /* All Binary or Data GRP_G */
            tmpL = 0x00 ;
        error = WriteByteSumToWav (tmpL, ORDER_E, mode, ptrFile) ;
        if (error != ERR_OK) break ;

        for ( ii = 0 ; ii < 4 ; ++ii ) { /* Date+Time PC-1600: Mon Day Hour Min */
            if ( ii < 2 && pcgrpId == GRP_16) /* write a valid date */
                  error = WriteByteSumToWav (1, ORDER_E, mode, ptrFile) ;
            else  error = WriteByteSumToWav (0, ORDER_E, mode, ptrFile) ;
            if (error != ERR_OK) break ;
        }
        if (error != ERR_OK) break ;

        tmpL = (len >> 16) & 0xFF ;
        error = WriteByteSumToWav (tmpL, ORDER_E, mode, ptrFile) ;
        if (error != ERR_OK) break ;

        tmpL = (addr >> 16) & 0xFF ;
        error = WriteByteSumToWav (tmpL, ORDER_E, mode, ptrFile) ;
        if (error != ERR_OK) break ;

        tmpL = (eaddr >> 16) & 0xFF ;
        error = WriteByteSumToWav (tmpL, ORDER_E, mode, ptrFile) ;
        if (error != ERR_OK) break ;

        for ( ii = 0 ; ii < 16 ; ++ii ) {
            error = WriteByteSumToWav (0, ORDER_E, mode, ptrFile) ;
            if (error != ERR_OK) break ;
        }
        if (error != ERR_OK) break ;


        /* finish header block and prepare next block */
        mode  = ptrFile->mode ;

        /* Write the block stop bit, space, sync and start bit */
        error = WriteSyncToEWav (nbSync, nbSyncS, SYNC_E_DATA, ptrFile) ;
        if (error != ERR_OK) break ;

        if (ident == IDENT_E_ASC || ident == IDENT_PC16_CAS) len = BLK_E_DAT ;
        else if (ident == IDENT_PC16_DAT) len = DATA_HEAD_LEN ;
        ptrFile->block_len = len ;
        ptrFile->count = 0 ;
        ptrFile->sum   = 0 ;

        if (ident == IDENT_E_BAS && pcgrpId != GRP_16) {
        /* write the 2.part of the internal BASIC file header */

            for ( ii = 0 ; ii < 20 ; ++ii ) tmpH[ii] = 0 ;
            tmpH[0] = 0xFF ;

            if (pcgrpId == GRP_E) {
                tmpH[4] = 0x34 ; // '4'

                haddr = len + 33 ;
                tmpH[7] = haddr & 0xFF ;
                tmpH[8] = haddr >> 8 & 0xFF ;
                tmpH[9] = haddr >> 16 & 0xFF ;

                tmpH[18] = 0x0D ;
                imax = 19;
            }
            else  { // pcgrpId == GRP_G
                tmpH[2] = 0x03 ;
                imax = 12;
            }
            if (type == TYPE_TXT) tmpH[2] = 0x08 ;

            for ( ii = 0 ; ii < imax ; ++ii ) {
                error = WriteByteSumToWav (tmpH[ii], ORDER_E, mode, ptrFile) ;
                if (error != ERR_OK) break ;
            }
            if (error != ERR_OK) break ;
        }
        if ( (ptrFile->debug & DEBUG_TRACES) > 0) printf("\n") ;

    } while (0) ;
    return (error);
}


/* File name for New and Old BASIC */
int WriteSaveNameToWav (char*  ptrName,
                        uchar  mode,
                    FileInfo*  ptrFile)
{
     uint  ii ;
    ulong  byte ;
    ulong  tmpL ;
//    char*  ptrDot ;
     char  tmpS[10] ;
      int  error ;

    do {
        /* Uppercase the name is done in main if needed */
        tmpL = strlen (ptrName) ;
        if (tmpL > 7)
            tmpL = 7 ;

        for ( ii = 0 ; ii < tmpL ; ++ii )
            tmpS[ii] = ptrName[ii] ;
        tmpS[tmpL] = 0 ;
        if (Qcnt == 0) printf ("Save name    : %s\n", tmpS) ;
        strncpy( ptrName, tmpS, cLPF-1) ;

        tmpL = 7 - tmpL ;
        for ( ii = 0 ; ii < tmpL ; ++ii )
            tmpS[ii] = 0 ;

        for ( ii = tmpL ; ii < 7 ; ++ii ) {
            byte = (ulong) ptrName[6 - ii] ;

// NOTE (Mr#3#): Changed switch - mode 20/19 -> pcgrpId
            switch (pcgrpId) {
            case GRP_OLD :
            case IDENT_PC1211 : /* IDENT_PC121_DAT in GRP included */

                if (byte < 0x80)
                    byte = CodeOld[byte] ;
                else
                    byte = CodeOld[0] ;
                break ;

            default :

                if (byte >= 0x80)
                    byte = 0x20 ;
                break ;
            }
            tmpS[ii] = (char) SwapByte(byte) ;
        }
        tmpS[7] = 0x5F ;

        /* Write the Name */
        ptrFile->count = 0 ;
        ptrFile->sum   = 0 ;
        for ( ii = 0 ; ii < 8 ; ++ii ) {
            error = WriteByteSumToWav (tmpS[ii], ORDER_STD, mode, ptrFile) ;
            if (error != ERR_OK) break ;
        }
        if ( (ptrFile->debug & 0x0040) > 0 ) printf(":Name - Bytes was printed swapped.\n");

        if (ptrFile->ident == IDENT_PC1211) {
            if ( (ptrFile->debug & SYNCL_STD) > 0 )
                error = WriteSyncToWav (214, ptrFile) ;
            else
                error = WriteSyncToWav (151, ptrFile) ;
        }
        else if (ptrFile->ident == IDENT_PC121_DAT)
            error = WriteSyncToWav (111, ptrFile) ;
        else if (ptrFile->ident == IDENT_NEW_DAT)
            error = WriteSyncToWav (1, ptrFile) ;

        ptrFile->count = 0 ;
        ptrFile->sum   = 0 ;

    } while (0) ;
    return (error);
}

/*
int WriteSaveNameToB19Wav (char*  ptrName, FileInfo*  ptrFile)
replaced by WriteSaveNameToWav

int WriteSaveNameToB16Wav (char*  ptrName, FileInfo*  ptrFile)
replaced by WriteSaveNameToWav
*/

/* Head of Binary Data for New and Old series */
int WriteHeadToBinWav (ulong  addr,
                       ulong  size,
                       uchar  mode,
                   FileInfo*  ptrFile)
{
      int  ii ;
    ulong  len ;
    ulong  tmpL ;
      int  error ;

    do {
        if (Qcnt == 0)
	{
		printf ("Start Address: 0x%04X\n", (uint) addr);
        printf ("End   Address: 0x%04X, Length: %d bytes\n", (uint) (addr + size -1), (uint) size);
	}

        ptrFile->count = 0 ;
        ptrFile->sum   = 0 ;
        for ( ii = 0 ; ii < 4 ; ++ii ) {
            error = WriteByteSumToWav (0, ORDER_STD, mode, ptrFile) ;
            if (error != ERR_OK) break ;
        }

        /* Write the address, this method is necessary because of swapped checksums in the header. */
        tmpL = ((addr >> 4) & 0xF0) + (addr >> 12) ;        /* H swapped */
        error = WriteByteSumToWav (tmpL, ORDER_STD, mode, ptrFile) ;
        if (error != ERR_OK) break ;

        tmpL = ((addr << 4) & 0xF0) + ((addr >> 4) & 0x0F) ;/* L swapped */
        error = WriteByteSumToWav (tmpL, ORDER_STD, mode, ptrFile) ;
        if (error != ERR_OK) break ;

        /* Write the Length */
        len = size - 1 ;
        tmpL = ((len >> 4) & 0xF0) + (len >> 12) ;
        error = WriteByteSumToWav (tmpL, ORDER_STD, mode, ptrFile) ;
        if (error != ERR_OK) break ;

        tmpL = ((len << 4) & 0xF0) + ((len >> 4) & 0x0F) ;
        error = WriteByteSumToWav (tmpL, ORDER_STD, mode, ptrFile) ;
        if (error != ERR_OK) break ;

        ptrFile->count = 0 ;
        ptrFile->sum   = 0 ;

    } while (0) ;
    return (error);
}
/*
int WriteHeadToB19BinWav (ulong  addr, ulong  size, FileInfo*  ptrFile)
replaced by WriteHeadToBinWav

int WriteHeadToB16BinWav (ulong  addr, ulong  size, FileInfo*  ptrFile)
replaced by WriteHeadToBinWav
*/

/* Head of Binary Mem Data for Old DB series */
int WriteHeadToMemWav (ulong  addr,
                       ulong  eaddr,
                       ulong  size,
                       uchar  mode,
                   FileInfo*  ptrFile)
{
      int  ii ;
    ulong  tmpL ;
     long  tmpA ;
      int  error ;

    do {
        tmpA = eaddr - (size<<1) ;
        if (addr ==0 && tmpA>0 ) addr = tmpA ;
        else if ( (long) addr != tmpA) {
            printf ("\nWARNING: Start address should point to: 0x%04X (4-bit nibbles).", (int) tmpA);
            printf ("\n         File length or end address is wrong, check it!\n");
            ++wrn_cnt;
        }
        if (Qcnt == 0)
        {
		printf ("Start address: 0x%04X (4-bit nibbles), Length: %d bytes\n", (uint) addr, (uint) size);
        printf ("Calculated end address: 0x%04X (4-bit)\n", (uint) (addr + (size<<1) -1));
        printf ("Given end+1 address is: 0x%04X (4-bit)\n", (uint) (eaddr));
        }
        ptrFile->count = 0 ;
        ptrFile->sum   = 0 ;

        /* Write the address (4 bit pointer) */
        tmpL = ((addr << 4) & 0xF0) + ((addr >> 4) & 0x0F) ;/* L swapped */
        error = WriteByteSumToWav (tmpL, ORDER_STD, mode, ptrFile) ;
        if (error != ERR_OK) break ;

        tmpL = ((addr >> 4) & 0xF0) + (addr >> 12) ;        /* H swapped */
        error = WriteByteSumToWav (tmpL, ORDER_STD, mode, ptrFile) ;
        if (error != ERR_OK) break ;

        tmpL = ((eaddr << 4) & 0xF0) + ((eaddr >> 4) & 0x0F) ;/* L swapped */
        error = WriteByteSumToWav (tmpL, ORDER_STD, mode, ptrFile) ;
        if (error != ERR_OK) break ;

        tmpL = ((eaddr >> 4) & 0xF0) + (eaddr >> 12) ;       /* H swapped */
        error = WriteByteSumToWav (tmpL, ORDER_STD, mode, ptrFile) ;
        if (error != ERR_OK) break ;

        for ( ii = 5; ii < 8; ++ii ) {
            error = WriteByteSumToWav (0, ORDER_STD, mode, ptrFile) ;
            if (error != ERR_OK) break ;
        }
        error = WriteByteSumToWav (0x5F, ORDER_STD, mode, ptrFile) ;
        if (error != ERR_OK) break ; // 0xF5 swapped

        ptrFile->count = 0 ;
        ptrFile->sum   = 0 ;

    } while (0) ;
    return (error);
}

int DetectDataType ( uchar* ptrItemType,
                     uchar  itemLen,    // DATA_STD_LEN or DATA_DBL_LEN
                      uint  tmpDim,
                     FILE*  srcFd)
 {
    uint  ii ;
     int  inVal, inVal2 ;
     int  error = ERR_OK ;

    *ptrItemType = DATA_UNKNOWN ;

    for ( ii = 0 ; ii < tmpDim ; ii += itemLen ){
        if ( ii > 0 ) {
            error = fseek (srcFd, itemLen -3, SEEK_CUR) ; /* Begin of next item */
            if (error != ERR_OK) break ;
        }
        inVal = fgetc (srcFd) ;
        if (inVal == EOF) break ;

        if (inVal > 0x7F && inVal < 0xA0 ) {     /* 1. isNumeric */
            *ptrItemType = DATA_NUM ;
            break ;
        }
        else if (inVal > 0x0F && inVal < 0x90 ) { /* 1. isString */
            *ptrItemType = DATA_STR ;
            break ;
        }
        inVal2 = fgetc (srcFd) ;
        if (inVal2 == EOF) break ;
        if (inVal == 0 && inVal2 > 0 ) { /* 2. isNumeric with Exp 0X, DBL: 1+VZ */
            *ptrItemType = DATA_NUM ;
            break ;
        }
        inVal2 = fgetc (srcFd) ;
        if (inVal2 == EOF) break ;
        if (inVal == 0 && inVal2 > 0 ) { /* 3. isNumeric with Exp 0X, 1. digit */
            *ptrItemType = DATA_NUM ;
            break ;
        }
    }
    if (error != ERR_OK) {
        printf ("\n%s:DetectData8 - Can't seek/read the source file\n", argP) ;
        error = ERR_FILE ;
    }
    return (error);
}

int WriteHeadToDataWav (
                     TypeInfo*  ptrSrcHead,
                     TypeInfo*  ptrDstHead,
                        uchar*  ptrItemLen, /* Real length of an item */
                        uchar*  ptrItemType,
                        ulong*  ptrPosEnd,  /* will set to point to the last byte of the data block */
                        ulong*  ptrNbByte,  /*Number of bytes to write*/
                     FileInfo*  ptrFile,
                         FILE*  srcFd)
{
       ulong  length = 0 ;      /* Length of defined variable block or ident of fixed variable block */
       ulong  tmpH, tmpL ;
      // fpos_t  position ;
        long  position ;
         int  inVal ;
         int  error = ERR_OK ;

    do {
        /* Read the length of data block */
        inVal = fgetc (srcFd) ;
        if (inVal == EOF) break ;
        if (SHCc > 0) inVal = SwapByte(inVal);
        tmpH = (uint)inVal ;
        if ( (ptrFile->debug & DEBUG_TRACES) == 0x0080 )
            printf(" LenHL:%02X", (uchar) inVal) ; /* Data block LenH or type */

        inVal = fgetc (srcFd) ;
        if (inVal == EOF) break ;
        if (SHCc > 0) inVal = SwapByte(inVal);
        tmpL = (uint)inVal ;
        if ( (ptrFile->debug & DEBUG_TRACES) == 0x0080 )
            printf("%02X", (uchar) inVal) ;     /* Data block LenL */

        length = ((tmpH << 8) + tmpL) ;
        ptrSrcHead->length = length ;

//        fgetpos(srcFd, &position) ;
        position = ftell( srcFd ) ;
        if (position <= 0) {
            printf ("\n%s:datahead - Can't get position in the source file\n", argP) ;
            return ( ERR_FILE ) ;
        }

        if (length == DATA_VARIABLE) {  /* Fixed variables, block of undefined type and length, itemLen=8 */
            *ptrPosEnd = (ulong) position + ( DATA_HEAD_LEN -2 + 0xFF * DATA_STD_LEN ); /* set to max: A(1)...A(255) */
            /* ConvertBin will find the mark DATA_EOF at block end */
        }
        else {                                    /* Array or simple variables, with defined header block */
            *ptrPosEnd = (ulong) position + length -1 ;   /* Last Data Byte, if not fixed variables block */
        }
        if ( (ptrFile->debug & DEBUG_TRACES) == 0x0080 )
            printf(" EOB:@%d ", (uint) *ptrPosEnd + 1) ;   /* Data End of block */

        /* Write the length and variable head */
        if (Qcnt == 0) {
            if (length == DATA_VARIABLE)
                printf (" Variable length block") ;
            else
                printf (" Data block, length: %d bytes\n", (uint) length + 2) ;
        }

        if (ptrFile->ident != IDENT_PC121_DAT) ptrFile->count = ( BLK_OLD_SUM - DATA_HEAD_LEN ) ;	/* 8-5= 3 bytes less for checksum */
        else ptrFile->count = 0 ;
        ptrFile->sum   = 0 ;

        /* Read and write dim1, dim2, itemLen, 6. Byte is NOT a var type but is
           also a checksum that is included by WAV2BIN 1.5.0 into var data block */

            inVal = fgetc (srcFd) ;
            if (inVal == EOF) break ;
            if (SHCc > 0) inVal = SwapByte(inVal);
            ptrSrcHead->dim1 = (uint)inVal ;

            inVal = fgetc (srcFd) ;
            if (inVal == EOF) break ;
            if (SHCc > 0) inVal = SwapByte(inVal);
            ptrSrcHead->dim2 = (uint)inVal ;

            inVal = fgetc (srcFd) ;
            if (inVal == EOF) break ;
            if (SHCc > 0) inVal = SwapByte(inVal);
            ptrSrcHead->itemLen = (uint)inVal ;

            if (ptrSrcHead->itemLen == DATA_NUM_15 && /* numeric from PC-1500, itemLen=8 */
               ((ptrFile->debug & 0x4) > 0 || ptrFile->ident == IDENT_PC121_DAT )) { /* convert it to standard variable */
                if (Qcnt == 0) printf (" Convert of numeric data format from PC-1500 to Standard variable block\n") ;
                tmpH = DATA_VARIABLE >> 8 ;
                tmpL = DATA_VARIABLE & 0xFF ;
                ptrDstHead->length = DATA_VARIABLE ;
                ptrDstHead->dim1 = 0 ;
                ptrDstHead->dim2 = 0 ;
                ptrDstHead->itemLen = 0 ;
                -- ptrFile->total_diff ; /* block end mark not included in PC-1500 source but for total write counter */
            }
            else {
                ptrDstHead->length = ptrSrcHead->length ;
                ptrDstHead->dim1 = ptrSrcHead->dim1 ;
                ptrDstHead->dim2 = ptrSrcHead->dim2 ;
                if (ptrSrcHead->itemLen == DATA_NUM_15) {
                    if (Qcnt == 0) printf (" Convert of numeric data format from PC-1500 to PC-%lu\n", pcId) ;
                    ptrDstHead->itemLen = DATA_STD_LEN ;
                }
                else ptrDstHead->itemLen = ptrSrcHead->itemLen ;
            }
            if (ptrDstHead->length == DATA_VARIABLE )
                *ptrItemLen = DATA_STD_LEN ;               /* real length */
            else {
                *ptrItemLen = ptrDstHead->itemLen ;
                if ( length != (ptrDstHead->dim1 +1)* (ptrDstHead->dim2 +1)* (*ptrItemLen)+ (ulong) (DATA_HEAD_LEN -2))
                    printf (" Check the data block offset: %lu differs from length for DIM (%i,%i)*%i\n", length,
                            ptrDstHead->dim1, ptrDstHead->dim2, *ptrItemLen ) ;
                // TODO (mr#4#): More Tests with ptrFile->total_diff
                if ( (ulong) (position) + length + ((ptrFile->debug & DATA_W2B150)>0? 1:0) > *ptrNbByte + SHCc) {
                    printf (" Data variable block length %lu exceeds the end of file\n", length) ;
                    error = ERR_FMT ;
                }
            }
            if ( *ptrItemLen < 1 || *ptrItemLen > cVL ) {
                printf (" Data variable items length %i is not supported: %u\n", cVL, *ptrItemLen) ;
                error = ERR_FMT ;
            }
            if (error != ERR_OK) break ;

            /* Item length 8 (14) is undefined if numeric from from PC-1234 or string with length 8 (14) from all PC */
            if (ptrSrcHead->itemLen == DATA_STD_LEN || ptrSrcHead->itemLen == DATA_DBL_LEN) {
                /* unknown if is string or numeric from PC-1234 */

                error = DetectDataType( ptrItemType, ptrSrcHead->itemLen, length - DATA_HEAD_LEN + 2, srcFd) ;
                if (error != ERR_OK) break ;

                error = fseek (srcFd, position -2 + DATA_HEAD_LEN, SEEK_SET) ; /*rewind to position in header */
                if (error != ERR_OK) {
                    printf ("\n%s:datahead-8 - Can't seek the file: %ld\n", argP, position) ;
                    error = ERR_FILE ;
                    break ;
                }
                if (ptrSrcHead->itemLen == DATA_DBL_LEN && *ptrItemType == DATA_NUM && pcgrpId != GRP_EXT ) {
                    printf (" Convert from DOUBLE numeric variable format to PC-%lu is NOT supported\n", pcId) ;
                    if (Qcnt == 0)
                        printf ("WARNING: This data of length %u are NOT usable strings for PC-%lu\n", ptrSrcHead->itemLen, pcId) ;
                }
            }

            if (ptrFile->ident != IDENT_PC121_DAT) {
                error = WriteByteSumToDataWav (tmpH, ptrFile->mode, ptrFile) ;
                if (error != ERR_OK) break ;
                error = WriteByteSumToDataWav (tmpL, ptrFile->mode, ptrFile) ;
                if (error != ERR_OK) break ;

                if ((ptrFile->debug & DEBUG_TRACES) == 0) {
                    if (Qcnt == 0 && ptrDstHead->length != DATA_VARIABLE) {
                        printf(" Variable DIM (%u, %u) * %u\n",
                            ptrDstHead->dim2, ptrDstHead->dim1, ptrDstHead->itemLen & 0x7F);
                    }
                }
                else
                        printf(" Dim1:") ;
                if ( (ptrFile->debug & DEBUG_TRACES) == 0x0080 )
                    printf(" %u", (uchar) ptrDstHead->dim1) ;
                error = WriteByteSumToDataWav (ptrDstHead->dim1, ptrFile->mode, ptrFile) ;
                if (error != ERR_OK) break ;

                if ( (ptrFile->debug & DEBUG_TRACES) > 0) printf(" Dim2:") ;
                if ( (ptrFile->debug & DEBUG_TRACES) == 0x0080 )
                    printf(" %u", (uchar) ptrDstHead->dim2) ;
                error = WriteByteSumToDataWav (ptrDstHead->dim2, ptrFile->mode, ptrFile) ;
                if (error != ERR_OK) break ;

                if ( (ptrFile->debug & DEBUG_TRACES) > 0) printf(" Item/length:") ;
                if ( (ptrFile->debug & DEBUG_TRACES) == 0x0080 )
                    printf(" 0x%02X ", (uchar) ptrDstHead->itemLen) ;
                error = WriteByteSumToDataWav (ptrDstHead->itemLen, ptrFile->mode, ptrFile) ;
                if (error != ERR_OK) break ;

                if ( (ptrFile->debug & DATA_W2B150) > 0 ) { 	/* checksum was in Wav2Bin 1.5 binary Pos 6 */
                    ++ ptrFile->total_diff ; /* old checksum not written and not included in total write counter */
                    if (inVal != EOF) inVal = fgetc (srcFd) ;   /* checksum will be written by WriteByteSumTo automatically */
                }
            }
            if (inVal == EOF) break ;

    } while (0) ;
    if (error == ERR_OK && inVal == EOF ) error = ERR_NOK ;

    return (error);
}


int WriteHeadTo156DataWav (
                        TypeInfo*  ptrSrcHead,
                        TypeInfo*  ptrDstHead,
                           uchar*  ptrItemLen,
                           uchar*  ptrItemType,
                           ulong*  ptrPosEnd,
                           ulong*  ptrNbByte,
                        FileInfo*  ptrFile,
                            FILE*  srcFd)
       // IDENT_QT_DAT + 2 bytes for variable name would needed
{
       ulong  length = 0 ;      /* Length of defined variable block */
       ulong  tmpH, tmpL ;
       ushort dim1 ;
//      fpos_t  position ;
        long  position ;
         int  inVal;
         int  error = ERR_OK ;

    do {
        /* Read the length of data block */
        inVal = fgetc (srcFd) ;
        if (inVal == EOF) break ;
        if (SHCc > 0) inVal = SwapByte(inVal); /* from other series */
        tmpH = (uint)inVal ;
        if ( (ptrFile->debug & DEBUG_TRACES) == 0x0080 )
            printf(" LenHL:%02X", (uchar) inVal) ;  /* Data Block Len H */

        inVal = fgetc (srcFd) ;
        if (inVal == EOF) break ;
        if (SHCc > 0) inVal = SwapByte(inVal); /* from other series */
        tmpL = (uint)inVal ;
        if ( (ptrFile->debug & DEBUG_TRACES) == 0x0080 )
            printf("%02X", (uchar) inVal) ;         /* Data Block Len L */

        length = ((tmpH << 8) + tmpL) ;
        ptrSrcHead->length = length ;

//        fgetpos(srcFd, &position) ;
        position = ftell( srcFd ) ;
        if (position <= 0) {
            printf ("\n%s:datahead15 - Can't get position in the source file\n", argP) ;
            return ( ERR_FILE ) ;
        }

        if (length == DATA_VARIABLE) { /* Fixed variables from series PC-1234, block of undefined length, itemLen=8 */
            /*search from head+1 +8: for DATA_EOF */
            dim1 = 0 ;
            length = DATA_HEAD_LEN-2 ;
            error = fseek (srcFd, DATA_HEAD_LEN-2+1, SEEK_CUR) ; /* Begin of first item + 1 */
            if (error == ERR_OK) {
                    do {
                        length += DATA_STD_LEN ;
                        error = fseek (srcFd, DATA_STD_LEN-1, SEEK_CUR) ; /* Begin of next item */
                        if (error != ERR_OK) break ;
                        inVal = fgetc (srcFd) ;
                        if (inVal == EOF) break ;
                        if (SHCc > 0) inVal = SwapByte(inVal); /* from other series */
                        if (inVal == DATA_EOF ) break ;

                    } while ( dim1++ < 0xFF ) ;
                    if ( dim1 > 0xFF) {
                        printf ("\n%s:datahead15 - Illegal dimension or missing end mark of standard variable block\n", argP) ;
                        error = ERR_FMT ;
                        break ;
                    }
                    else ptrDstHead->dim1 = dim1 & 0xFF ;
            }
            if (error != ERR_OK) {
                    printf ("\n%s:datahead15 - Can't seek/read the source file\n", argP) ;
                    error = ERR_FILE ;
                    break ;
            }
            else {
                tmpH = length >> 8 ;
                tmpL = length & 0xFF ;
            }
            error = fseek (srcFd, position, SEEK_SET) ; /*rewind to position in header */
            if (error != ERR_OK) {
                printf ("\n%s:datahead15 - Can't seek the file: %ld\n", argP, (long) position) ;
                error = ERR_FILE ;
                break ;
            }
            /* Length calculated for conversion to array or PC-1500 numeric standard variables
               with defined header block */
        }
        ptrDstHead->length = length ;
        *ptrPosEnd = (ulong) position + length -1 ;     /* Last data byte */

        if ( (ptrFile->debug & DEBUG_TRACES) == 0x0080 )
            printf(" EOB:@%d ", (uint) *ptrPosEnd + 1) ;   /* Data End of block */

        /* Write the length and variable head */
        if (Qcnt == 0) printf (" Data block, length: %d bytes\n", (uint) length + 2) ;

        if ( ptrFile->ident == IDENT_PC16_DAT) {
            ptrFile->block_len = DATA_HEAD_LEN ;
            ptrFile->count = 0 ;
        }
        else ptrFile->count = ( BLK_OLD - DATA_HEAD_LEN ) ;	/* 80-5= 75 bytes less than B22Wav */
        ptrFile->sum   = 0 ;

        /* Read and write dim1, dim2, itemLen */

            inVal = fgetc (srcFd) ;
            if (inVal == EOF) break ;
            if (SHCc > 0) inVal = SwapByte(inVal); /* from other series */
            ptrSrcHead->dim1 = (uint)inVal ;

            inVal = fgetc (srcFd) ;
            if (inVal == EOF) break ;
            if (SHCc > 0) inVal = SwapByte(inVal); /* from other series */
            ptrSrcHead->dim2 = (uint)inVal ;

            inVal = fgetc (srcFd) ;
            if (inVal == EOF) break ;
            if (SHCc > 0) inVal = SwapByte(inVal); /* from other series */
            ptrSrcHead->itemLen = (uint)inVal ;

            if (ptrSrcHead->length == DATA_VARIABLE) { /* from PC-1234, num expected */
                ptrDstHead->dim2 = 0 ;
                ptrDstHead->itemLen = DATA_NUM_15 ;
                /* Remove additional block end mark, included in variable length block */
                (*ptrPosEnd)++ ; /* End mark DATA_EOF included */
                ++ ptrFile->total_diff ; // Bin2wav 2.09b3b3: moved from convertB2w, for total write counter
                if ( Qcnt==0) printf (" Convert numeric values of other standard variable format to PC-%lu\n", pcId) ;
                if (ptrFile->ident == IDENT_QT_DAT) {
                    error = ERR_FMT;
                    break;
                }
            } // end if: data_variable
            else {
                ptrDstHead->dim1 = ptrSrcHead->dim1 ;
                ptrDstHead->dim2 = ptrSrcHead->dim2 ;
                /* Item length 8 (14) is undefined if numeric from from PC-1234 or string with length 8 (14) from all PC */
                if (ptrSrcHead->itemLen == DATA_STD_LEN) { /* unknown if is string or numeric from PC-1234 */

                        error = DetectDataType( ptrItemType, ptrSrcHead->itemLen, length - DATA_HEAD_LEN + 2, srcFd) ;
                        if (error != ERR_OK) break ;

                        error = fseek (srcFd, position -2 + DATA_HEAD_LEN, SEEK_SET) ; /*rewind to position in header */
                        if (error != ERR_OK) {
                            printf ("\n%s:datahead15-8 - Can't seek the file: %ld\n", argP, position) ;
                            error = ERR_FILE ;
                            break ;
                        }
                        if  ( *ptrItemType == DATA_UNKNOWN ) { /* only empty items found */
                            if ((ptrFile->debug & 0x8) > 0 ) ptrDstHead->itemLen = DATA_NUM_15 ; /* define numeric 0-array from PC-1234 */
                            else ptrDstHead->itemLen = ptrSrcHead->itemLen ;              /* define 0-string data from PC-1500 or other */
                        }
                        else if (*ptrItemType == DATA_NUM) ptrDstHead->itemLen = DATA_NUM_15 ; /* Convert numeric data from other PC */
                        else ptrDstHead->itemLen = ptrSrcHead->itemLen ; /*DATA_STD_LEN*/

                        if ( ptrDstHead->itemLen == DATA_NUM_15 )
                            if ( Qcnt==0) printf (" Convert other numeric variable format to PC-%lu\n", pcId) ;

                } // end if: DATA_STD_LEN
                else if (ptrSrcHead->itemLen == DATA_DBL_LEN) { /* unknown if is string or double numeric from PC-1234 */

                        error = DetectDataType( ptrItemType, ptrSrcHead->itemLen, length - DATA_HEAD_LEN + 2, srcFd) ;
                        if (error != ERR_OK) break ;

                        error = fseek (srcFd, position -2 + DATA_HEAD_LEN, SEEK_SET) ; /*rewind to position in header */
                        if (error != ERR_OK) {
                            printf ("\n%s:datahead15-14 - Can't seek the file: %ld\n", argP, position) ;
                            error = ERR_FILE ;
                            break ;
                        }
                        if (*ptrItemType == DATA_NUM) {
                            printf (" Convert from DOUBLE numeric variable format to PC-%lu is NOT supported\n", pcId) ;
                            if (Qcnt == 0)
                                printf ("WARNING: This data of length %u are NOT usable strings for PC-%lu\n", ptrSrcHead->itemLen, pcId) ;
                        }
                        ptrDstHead->itemLen = ptrSrcHead->itemLen ; /* DATA_DBL_LEN from GRP_EXT ignored */

                } // end if: DATA_DBL_LEN
                else ptrDstHead->itemLen = ptrSrcHead->itemLen ;   /* expect original numeric data from PC-1500 or string data */
            } // end if: no data_variable

            if (ptrDstHead->itemLen == DATA_NUM_15 ) *ptrItemLen = DATA_STD_LEN ; /* real length */
            else *ptrItemLen = ptrDstHead->itemLen ;
            if ( length != (ptrDstHead->dim1 +1)* (ptrDstHead->dim2 +1)* (*ptrItemLen)+ (ulong) (DATA_HEAD_LEN -2))
                    printf (" Check the data block offset: %lu differs from length for DIM (%i,%i)*%i\n", length,
                            ptrDstHead->dim1, ptrDstHead->dim2, *ptrItemLen ) ;
            // TODO (mr#4#): More tests, data length diff -1 or not
            if ( (ulong) position + length > *ptrNbByte + SHCc ) {
                printf (" Data variable block length %lu exceeds the dist %lu to end of file\n", length, *ptrNbByte + SHCc - (ulong) position ) ;
                error = ERR_FMT ;
            }
            if ( *ptrItemLen < 1 || *ptrItemLen > cVL ) {
                printf (" Data variable items length %i is not supported: %u\n", cVL, *ptrItemLen) ;
                error = ERR_FMT ;
            }
            if (error != ERR_OK) break ;
            // IDENT_QT_DAT: Code name with ptrItemType, itemLen and write + 2 bytes for variable name

            error = WriteByteSumTo156Wav (tmpH, ptrFile) ;
            if (error != ERR_OK) break ;
            error = WriteByteSumTo156Wav (tmpL, ptrFile) ;
            if (error != ERR_OK) break ;

            if ((ptrFile->debug & DEBUG_TRACES) == 0) {
                if (Qcnt == 0) {
                    printf(" Variable DIM (%u, %u) * %u\n",
                            ptrDstHead->dim2, ptrDstHead->dim1, ptrDstHead->itemLen & 0x7F);
                }
            }
            else
                    printf(" Dim1:") ;
            if ( (ptrFile->debug & DEBUG_TRACES) == 0x0080 )
                    printf(" %u", (uchar) ptrDstHead->dim1) ;
            error = WriteByteSumTo156Wav (ptrDstHead->dim1, ptrFile) ;
            if (error != ERR_OK) break ;

            if ( (ptrFile->debug & DEBUG_TRACES) > 0) printf(" Dim2:") ;
            if ( (ptrFile->debug & DEBUG_TRACES) == 0x0080 )
                    printf(" %u", (uchar) ptrDstHead->dim2) ;
            error = WriteByteSumTo156Wav (ptrDstHead->dim2, ptrFile) ;
            if (error != ERR_OK) break ;

            if ( (ptrFile->debug & DEBUG_TRACES) > 0) printf(" Item/length:") ;
            if ( (ptrFile->debug & DEBUG_TRACES) == 0x0080 )
                    printf(" 0x%02X\n", (uchar) ptrDstHead->itemLen) ;
            error = WriteByteSumTo156Wav (ptrDstHead->itemLen, ptrFile) ;
            if (error != ERR_OK) break ;

            if ( ptrFile->ident == IDENT_PC16_DAT) {
                /* for checksum */
                ptrFile->block_len = length - 3 ;
                ptrFile->count = 0 ;
            }

    } while (0) ;
    if (error == ERR_OK && inVal == EOF ) error = ERR_NOK ;

    return (error);
}

/*  WriteFooterToB22BinWav */
int WriteFooterTo15Wav (uchar  type,
                    FileInfo*  ptrFile)
{
    ulong  sum ;
    ulong  nbSync ;
     uint  ii ;
      int  error ;

    do {

        if (type != TYPE_DAT) { /* Last checksum of DAT was written inside the footer of the data block */

            if (type == TYPE_IMG) {
                    /* BAS_1500_EOF is not included in images from Wav2bin */
                    error = WriteByteSumTo156Wav (BAS_1500_EOF, ptrFile) ;
                    if (error != ERR_OK) break ;
            }
            if (ptrFile->count > 0) {   /* Last checksum has not written by WriteByteSum before */

                sum = (ptrFile->sum >> 8) & 0xFF ;
                error = WriteByteTo156Wav (sum, ptrFile) ;
                if (error != ERR_OK) break ;

                sum = ptrFile->sum & 0xFF ;
                error = WriteByteTo156Wav (sum, ptrFile) ;
                if (error != ERR_OK) break ;

                if ( (ptrFile->debug & 0x0040) > 0 )
                printf(" (%04X)", (uint) ptrFile->sum);
            }
        }
        if (pcgrpId == IDENT_QTAPE) {

            error = WriteByteTo156Wav ( EOF_QT1 , ptrFile) ;
            if (error != ERR_OK) break ;
            error = WriteByteTo156Wav ( EOF_QT1 , ptrFile) ;
            if (error != ERR_OK) break ;
            if ( (ptrFile->debug & 0x0040) > 0 )
                printf(" (%02X%02X)", (uchar) EOF_QT1, (uchar) EOF_QT1 );

            error = WriteSyncToWav (625, ptrFile) ; /* QTc == 1 */

            break ;
        }
        else { /* PC-1500 org. */
            error = WriteSyncToWav (72, ptrFile) ; /* PC-1500 org. */
            if (error != ERR_OK) break ;

            error = WriteByteTo156Wav ( EOF_15 , ptrFile) ;
            if (error != ERR_OK) break ;

            if ( (ptrFile->debug & 0x0040) > 0 )
                printf(" (%02X)", (uchar) EOF_15 );
        }
        /* PC-1500 org. */
        error = WriteSyncToWav (70, ptrFile) ;
        if (error != ERR_OK) break ;

        /* For some computer /audio interface combinations, the silence at the end of the wav file must be even longer. */
        if ((ptrFile->debug & NO_WAV_END )>0) break ;

        /* WriteShutdownTo15Wav  */
        error = WriteBitToWav (3, ptrFile) ;
        if (error != ERR_OK) break ;
        nbSync = ptrFile->nbSync1 /16 -1;  /* silence of 0.063 sec */
        for ( ii = 0 ; ii < nbSync ; ++ii ) {
            error = WriteBitToWav (2, ptrFile) ;
            if (error != ERR_OK) break ;
        }
        if (error != ERR_OK) break ;

        if ((ptrFile->debug & SYNCA_END )>0) { /* against faders */
            /* Silence of 0.063 sec */
            for ( ii = 0 ; ii < nbSync ; ++ii ) {
                error = WriteBitToWav (2, ptrFile) ;
                if (error != ERR_OK) break ;
            }
            if (error != ERR_OK) break ;

            nbSync = ptrFile->nbSync1 * SYNCA_END_LEN ;
            for ( ii = 0 ; ii < nbSync ; ++ii ) {
                error = WriteBitToWav (1, ptrFile) ;
                if (error != ERR_OK) break ;
            }
        }

    } while (0) ;
    return (error);
}

int WriteShutdownToSWav (FileInfo*  ptrFile)
{
    ulong  nbSync ;
     uint  ii ;
      int  error = ERR_OK ;

    do {
        if ((ptrFile->debug & NO_WAV_END )>0) break ;

        nbSync = ptrFile->nbSync1 /8 ;    /* silence of 0.12 sec */
        for ( ii = 0 ; ii < nbSync ; ++ii ) {
            error = WriteBitToSWav (3, ptrFile) ;
            if (error != ERR_OK) break ;
        }
        if (error != ERR_OK) break ;

        if ((ptrFile->debug & SYNCA_END )>0) { /* against faders */
            /* Silence of 0.12 sec */
            for ( ii = 0 ; ii < nbSync ; ++ii ) {
                error = WriteBitToSWav (3, ptrFile) ;
                if (error != ERR_OK) break ;
            }
            if (error != ERR_OK) break ;

            nbSync = ptrFile->nbSync1 * SYNCA_END_LEN ;
            for ( ii = 0 ; ii < nbSync ; ++ii ) {
                error = WriteBitToSWav (2, ptrFile) ;
                if (error != ERR_OK) break ;
            }
        }

    } while (0) ;
    return (error);
}

int WriteShutdownToQWav (FileInfo*  ptrFile)
{
    ulong  nbSync ;
     uint  ii ;
      int  error = ERR_OK ;

    do {
        if ((ptrFile->debug & NO_WAV_END )>0) break ;

        error = WriteBitToWav (3, ptrFile) ;   /* signal shutdown */
        if (error != ERR_OK) break ;

        nbSync = ptrFile->nbSync1 /16 ;        /* silence of 0.063 sec */
        for ( ii = 0 ; ii < nbSync ; ++ii ) {
            error = WriteBitToWav (4, ptrFile) ;
            if (error != ERR_OK) break ;
        }
        if (error != ERR_OK) break ;

        if ((ptrFile->debug & SYNCA_END )>0) { /* against faders */
            /* Silence of 0.063 sec */
            for ( ii = 0 ; ii < nbSync ; ++ii ) {
                error = WriteBitToWav (4, ptrFile) ;
                if (error != ERR_OK) break ;
            }
            if (error != ERR_OK) break ;

            nbSync = ptrFile->nbSync1 * SYNCA_END_LEN ;
            for ( ii = 0 ; ii < nbSync ; ++ii ) {
                error = WriteBitToWav (1, ptrFile) ;
                if (error != ERR_OK) break ;
            }
        }

    } while (0) ;
    return (error);
}

int WriteShutdownToWav (FileInfo*  ptrFile)
{
    ulong  nbSync ;
     uint  ii ;
      int  error = ERR_OK ;

    do {
        if ((ptrFile->debug & NO_WAV_END )>0) break ;

	/* This puts 2 bits of silence (or 2 HIGH bits alternatively) to the end of the wav file. */
	/* CLOAD does not accept any sound, that could be interpreted as a start bit,             */
    /* during post-processing. Original CSAVE switches the signal low ms after the            */
    /* end of transmission, before the motor of the cassette recorder is switched off.        */
    /* This level out is visible in the CSAVE audio signal after the last bit. T. Muecker     */

        error = WriteBitToWav (3, ptrFile) ; /* begin of signal shutdown */
        if (error != ERR_OK) break ;

        error = WriteBitToWav (4, ptrFile) ; /* continue signal shutdown */
        if (error != ERR_OK) break ;

        nbSync = ptrFile->nbSync1 /16 ;      /* silence of 0.063 sec */
        for ( ii = 0 ; ii < nbSync ; ++ii ) {
            error = WriteBitToWav (2, ptrFile) ;
            if (error != ERR_OK) break ;
        }
        if (error != ERR_OK) break ;

    /*  In reality, the motor of the cassette recorder is switched off after no longer than 60 ms
        after the end of transmission. For some computer / audio interface combinations with
        delayed playback signal , the silence at the end of the wav file must be even longer. */

        if ((ptrFile->debug & SYNCA_END )>0) { /* against faders */
            /* Silence of 0.063 sec */
            for ( ii = 0 ; ii < nbSync ; ++ii ) {
                error = WriteBitToWav (2, ptrFile) ;
                if (error != ERR_OK) break ;
            }
            if (error != ERR_OK) break ;

            nbSync = ptrFile->nbSync1 * SYNCA_END_LEN ;
            for ( ii = 0 ; ii < nbSync ; ++ii ) {
                error = WriteBitToWav (1, ptrFile) ;
                if (error != ERR_OK) break ;
            }
        }

    } while (0) ;
    return (error);
}

/* WriteFooterToB13BinWav */
int WriteFooterToNewWav (FileInfo*  ptrFile)
{
      int  error ;

    do {
        ptrFile->count = 0 ; /* no checksum writing from here until the end */

        error = WriteByteSumToWav(BAS_NEW_EOF, ORDER_STD, ptrFile->mode, ptrFile) ;
        if (error != ERR_OK) break ;

        error = WriteByteToWav(BAS_NEW_EOF, ORDER_STD, ptrFile->mode, ptrFile) ;
        if (error != ERR_OK) break ;

        if ( (ptrFile->debug & DEBUG_TRACES) > 0 )
            printf(" EOF:%02X", (uchar) BAS_NEW_EOF);

        if (pcId==1100) ptrFile->mode = MODE_B14_2 ;

        error = WriteByteToWav(ptrFile->sum, ORDER_STD, ptrFile->mode, ptrFile) ;
        if (error != ERR_OK) break ;

        if ( (ptrFile->debug & 0x0040) > 0 )
            printf(" (%02X) ", (uchar) ptrFile->sum);

        if (pcgrpId == GRP_EXT) {
                error = WriteSyncToWav (9, ptrFile) ;
                if (error != ERR_OK) break ;
        }
        if (pcId != 1100) {
        /* there are 2bits more HIGH at the end of transmission (at least for PC-1402) M. NOSSWITZ */
        /* ... and also the other of GRP_NEW */
            error = WriteBitToWav (1, ptrFile) ;
            if (error != ERR_OK) break ;

            error = WriteBitToWav (1, ptrFile) ;
        }
        /* This puts 2 bits of silence, 2 HIGH bits or floating alternatively to the end of the wav file. */
        if (error == ERR_OK) error = WriteShutdownToWav (ptrFile) ;

    } while (0) ;
    return (error);
}


int WriteFooterToMemoWav (FileInfo*  ptrFile)
{
      int  error = ERR_OK ;

    do {
    // NOTE (Mr#6#): If the last checksum is not written here, there will be too many stop bits at the end
        error = WriteByteToWav(ptrFile->sum, ORDER_STD, MODE_B14_2, ptrFile) ;
        if (error != ERR_OK) break ;

        if ( (ptrFile->debug & 0x0040) > 0 )
            printf(" (%02X) ", (uchar) ptrFile->sum);

	if (error == ERR_OK) error = WriteShutdownToWav (ptrFile) ;

    } while (0) ;
    return (error);
}


int WriteFooterToDataWav (uint  type, /* data type or length */
                          FileInfo*  ptrFile)
{
    int  error = ERR_OK ;

    do {

        if (ptrFile->count != 0) {

            if ( (ptrFile->debug & 0x0040) > 0 )
                printf(" (%02X)", (uchar) ptrFile->sum);

            error = WriteByteToWav(ptrFile->sum, ORDER_STD, ptrFile->mode, ptrFile) ;
            if (error != ERR_OK) break ;

            ptrFile->count = 0 ;
        }

        if (type == DATA_VARIABLE) {

            if (ptrFile->ident != IDENT_PC121_DAT) {    /* PC121_DAT length must be the same as after every field variable */
                error = WriteSyncToWav (97, ptrFile) ;  /* ~ 0.2017 sec = 101 ( - 4 standard from WriteBitToDataWav ) */
                if (error != ERR_OK) break ;
            }
            if (ptrFile->ident == IDENT_PC121_DAT)
                error = WriteByteToWav(BAS_OLD_EOF, ORDER_STD, MODE_B20_2, ptrFile) ;
            else
                error = WriteByteToWav(BAS_OLD_EOF, ORDER_STD, ptrFile->mode, ptrFile) ; //WriteToTAP need this way
//              error = WriteByteToWav(DATA_EOF, ORDER_INV, MODE_B15, ptrFile) ;  //WriteToTAP NOT works this way

            if (error != ERR_OK) break ;
            ++ptrFile->total ;

            if ( (ptrFile->debug & DEBUG_TRACES) > 0 )
                printf(" EOB:%02X", (uchar) DATA_EOF);

        }

	error = WriteBitToWav (1, ptrFile) ;
	if (error != ERR_OK) break ;

    if ( (ptrFile->debug & DEBUG_TRACES) > 0 ) printf("\n");

    } while (0) ;
    return (error);
}

/* Footer of one data block only */
int WriteFooterTo15DataWav (FileInfo*  ptrFile)
{
    ulong  sum ;
      int  error = ERR_OK ;

    do {

        if (ptrFile->count != 0) {

            if ( (ptrFile->debug & 0x0040) > 0 )
                printf(" (%04X)", (uint) ptrFile->sum);

            /* Write the checksum */
            sum = (ptrFile->sum >> 8) & 0xFF ;
            error = WriteByteTo15Wav (sum, ptrFile) ;
            if (error != ERR_OK) break ;

            sum = ptrFile->sum & 0xFF ;
            error = WriteByteTo15Wav (sum, ptrFile) ;
            if (error != ERR_OK) break ;

            ptrFile->count = 0 ;
            ptrFile->sum = 0 ;
        }

    } while (0) ;

    return (error);
}


int WriteFooterToEWav (uchar   type,
                    FileInfo*  ptrFile)
{
       ulong  nbSync ;
        uint  ii ;
         int  error = ERR_OK ;

    do {
        if ((ptrFile->debug & NO_WAV_END )>0) {
            if ((type != TYPE_ASC && type != TYPE_DAT) || (ptrFile->debug & ERR_OFF )>0 ) break ;
            else {
                ++wrn_cnt;
                if (Qcnt == 0)
                    printf ("\n%s: Add the option -l 0x%03X if you really want to shorten this wav!\n", argP, ERR_OFF) ;
            }
        }
        /* write stop bit and pull down the level at the end of the E block */
        error = WriteBitToEWav (3, ptrFile) ;
        if (error != ERR_OK) break ;        /* WriteShutdownToEWav included */

        if ( type == TYPE_ASC || type == TYPE_DAT ||             /* type == TYPE_BAS || */
            (ptrFile->debug & (SYNCL_TRM | SYNCL_STD | SYNCA_END))>0 )
             nbSync = ptrFile->nbSync1 *4 +375 ; /* 4+ sec for ASC-BAS, ASC-DAT, DAT_16 */
        else
             nbSync = ptrFile->nbSync1 /4 ; /* IMG, BIN, RSV can end with silence of 0.25 sec only */

        for ( ii = 0 ; ii < nbSync ; ++ii ) {
            error = WriteBitToEWav (2, ptrFile) ;
            if (error != ERR_OK) break ;
        }
        if (error != ERR_OK || (ptrFile->debug & NO_WAV_END )>0) break ;

        if ((ptrFile->debug & SYNCA_END )>0) { /* against faders */
            nbSync = ptrFile->nbSync1 *SYNCA_END_LEN ;

            for ( ii = 0 ; ii < nbSync ; ++ii ) {
                error = WriteBitToEWav (0, ptrFile) ;
                if (error != ERR_OK) break ;
            }
        }

    } while (0) ;

    return (error);
}


void conv_old2asc( uchar *str, int len )

{
    int ii ;
    uchar asc, old ;

    for ( ii = 0 ; ii < len ; ++ii  ) {
        old=str[ii] ;
        if (old == 0 || old == DATA_STD_STR) break ;
        asc = old ;

        if ((old > 63 && old < 74 ) || /* Numbers */
            (old > 80 && old < 107 ))  /* upper chars */
            asc = old - 16 ;
        else {
            if (old == 17 ) asc = ' ' ;
            if (old == 18 ) asc = 34  ;
            if (old == 19 ) asc = '?' ;
            if (old == 20 ) asc = '!' ;
            if (old == 21 ) asc = 35  ;
            if (old == 22 ) asc = '%' ;
            if (old == 24 ) asc = '$' ;
            if (old == 27 ) asc = ',' ;
            if (old == 28 ) asc = ';' ;
            if (old == 29 ) asc = ':' ;
            if (old == 30 ) asc = '@' ;
            if (old == 31 ) asc = '&' ;
            if (old == 48 ) asc = '(' ;
            if (old == 49 ) asc = ')' ;
            if (old == 50 ) asc = '>' ;
            if (old == 51 ) asc = '<' ;
            if (old == 52 ) asc = '=' ;
            if (old == 53 ) asc = '+' ;
            if (old == 54 ) asc = '-' ;
            if (old == 55 ) asc = '*' ;
            if (old == 56 ) asc = '/' ;
            if (old == 57 ) asc = '^' ;
            if (old == 74 ) asc = '.' ;
            if (old == 75 ) asc = 'E' ;
            if (old == 77 ) asc = '~' ;
            if (old == 78 ) asc = '_' ;
        }
        str[ii] = (uchar)asc ;
    }
}


void conv_asc2old( uchar *str, int len )

{
    int ii ;
    uchar asc, old ;

    for ( ii = 0 ; ii < len ; ++ii  ) {
        asc=str[ii] ;
        if (asc == 0 || old == DATA_STD_STR) break ;
        old = asc ;

        if ((asc > 47 && asc < 58 ) || /* Numbers */
            (asc > 64 && asc < 91 ))   /* upper chars */
            old = asc + 16 ;
        else {
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
            if (asc == '~' ) old = 77 ;
            if (asc == '_' ) old = 78 ;

            if (asc > 96 && asc < 123) old = asc - 16 ; /* lower chars */
        }
        str[ii] = (uchar)old ;
    }
}


int ConvertDataVariableItem (
                        uchar*  VarItem,
                     TypeInfo*  ptrSrcHead,
                     TypeInfo*  ptrDstHead,
                        uchar   ItemLen,
                        uchar   ItemType,
                        ulong   debug)
{
        uchar   tmpB, tmpE, Sign, Exponent ;
        bool    ExpNegative ;
        int     ii, error = ERR_OK ;

        /* Convert from PC-1500 to other */
        if ( ptrSrcHead->itemLen == DATA_NUM_15  &&
            (ptrDstHead->itemLen == DATA_STD_LEN || ptrDstHead->length == DATA_VARIABLE)) {

            /* Convert exponent from binary to BCD and shift sign */
            Sign = ( VarItem [1] & 0xF0 ) >> 4 ;

            ExpNegative = VarItem [0]  > 0x80 ;
            if (ExpNegative) {
                Exponent = 99 - (0xFF - VarItem [0] ) ;
                tmpE = 0x90 ;
            }
            else {
                Exponent = VarItem [0] ;
                tmpE = 0 ;
            }
            VarItem [0] = tmpE | Exponent / 10 ;
            VarItem [1] = Sign | Exponent % 10 << 4 ;

            if (ptrDstHead->length == DATA_VARIABLE){
                /* bring bytes in reverse order */
                for ( ii = 0 ; ii < ItemLen / 2 ; ++ii ) {
                    tmpB = VarItem[ ii ] ;
                    tmpE = VarItem[ ItemLen-1 - ii] ;
                    VarItem[ ii ] = tmpE ;
                    VarItem[ ItemLen-1 - ii] = tmpB ;
                }
            }
        }

        /* Convert from other to PC-1500 */
        else if (ptrDstHead->itemLen == DATA_NUM_15  &&
                (ptrSrcHead->itemLen == DATA_STD_LEN || ptrSrcHead->length == DATA_VARIABLE)) {

            if (ptrSrcHead->length == DATA_VARIABLE){
                if ( VarItem[ItemLen - 1] == DATA_STD_STR ) { /*set string variable to 0*/
                    for ( ii = 0 ; ii < ItemLen ; ++ii ) {
                        VarItem[ ii ] = 0 ;
                    }
                }
                else { /* bring bytes in reverse order */
                    for ( ii = 0 ; ii < ItemLen / 2 ; ++ii ) {
                        tmpB = VarItem[ ii ] ;
                        tmpE = VarItem[ ItemLen-1 - ii] ;
                        VarItem[ ii ] = tmpE ;
                        VarItem[ ItemLen-1 - ii] = tmpB ;
                    }
                }
            }
            /* Convert exponent from BCD to binary and shift sign */
            Sign = ( VarItem [1] & 0x0F ) << 4 ;
            Exponent = ((VarItem [1] & 0xF0 ) >> 4 ) + ( VarItem [0] & 0x0F ) * 10 ;

            ExpNegative = ( VarItem [0] & 0xF0 ) > 0x80 ;
            if (ExpNegative) Exponent = 0xFF - (99 - Exponent ) ;

            VarItem [0] = Exponent ;
            VarItem [1] = Sign ;
        }

        /* Convert strings */
        else if ((debug & 0x10) > 0 &&  ItemType != DATA_NUM && /*convert char code, no numeric (std, dbl) */
                ptrDstHead->itemLen != DATA_NUM_15 && ptrSrcHead->itemLen != DATA_NUM_15 ) {

                if ( pcgrpId == IDENT_PC1500) {
                    /* convert string from OLD_BAS to PC-1500 */
                    conv_old2asc ( VarItem, ItemLen ) ;
                }
                else if ( ItemType == DATA_STR ||
                          ( ptrSrcHead->itemLen != DATA_STD_LEN  &&
                            ptrSrcHead->length  != DATA_VARIABLE  ) ||
                          ( ptrSrcHead->length  == DATA_VARIABLE &&
                            VarItem[ItemLen -1] == DATA_STD_STR   )  )  {
                    /* convert strings between OLD_BAS */
                    if ( pcgrpId == GRP_OLD || pcgrpId == IDENT_PC1211 ) conv_asc2old( VarItem, ItemLen );
                    else conv_old2asc ( VarItem, ItemLen );
                }
        }

    return (error);
}

int ConvertBinToWav (char*  ptrSrcFile,
                     char*  ptrDstFile,
                     char*  ptrDstExt,
                     uchar  type,
                    ushort  flags,
                     ulong  addr,
                     ulong  eaddr,
                     double sync,
                     double syncS,
                     char*  ptrName,
                     ulong  debug)
{
    FileInfo  info ;
        FILE  *srcFd = NULL ;
//        char  text[cLL] ;       /* General temporary text */
         int  inVal ;
       ulong  nbSamp ;
       ulong  freq ;
       ulong  base_freq ;       /* SHARP audio default base frequency for sync bits */
       ulong  nbSync, nbSyncS ; /* number of synchronisation bits */
         int  error, error_tmp ;
//      fpos_t  position;
        long  position;         /* position in the file */
       ulong  nbByte, limit ;
	   ulong  pos_end ;         /* last byte of a data variable block */
       uchar  order = ORDER_STD, mode_t = MODE_B22 ; /* bit writing parameter */
       uchar  itemLen ;         /* variable item real length */
       uchar  itemType ;        /* variable item type */
    TypeInfo  srcHead,
              dstHead ;         /* Variable Header */
       uchar  varItem[cVL] ;
        uint  ii ;
        char  tmpS[25] ;
        int   tmpSPos ;

    do {
//        text[0]='\0' ;
        info.ptrFd = NULL ;
        info.ident = IDENT_UNKNOWN ;
        info.nbByte = 0 ;
        info.total_diff = 0 ;
        info.total = 0 ;
        info.total_raw = 0 ;
        info.column_cnt = 0 ;
        info.count = 0 ;
        info.sum   = 0 ;
        info.usedat_len  = 0 ;            /* Only used with Quick-Tape*/
        info.bitLen= strlen (bit[0]) ;    /* with constant bit length, NOT for 1600/E/G/ST */
        info.lastSmpHigh = bitMirroring ; /* SuperTape phase before start */
        info.debug = debug ;
        srcFd      = NULL ;
        error      = ERR_OK ;

        /* Open the destination file */
        info.ptrFd = fopen (ptrDstFile, "wb") ;
        if (info.ptrFd == NULL) {
            printf ("%s: Can't open the destination file: %s\n", argP, ptrDstFile) ;
            error = ERR_FILE ;
            break ;
        }

        /* Open the source file */
        srcFd = fopen (ptrSrcFile, "rb") ;
        if (srcFd == NULL) {
            printf ("%s: Can't open the source file: %s\n", argP, ptrSrcFile) ;
            error = ERR_FILE ;
            break ;
        }

        error = ReadFileLength (type, &nbByte, &srcFd) ;
        if (error != ERR_OK) break ;

        if ((info.debug & DEBUG_TRACES) > 0) printf ("File length (without header or end marks): %d bytes\n", (uint) nbByte);

        if  ( pcgrpId == GRP_16  &&  type != TYPE_BIN ) limit = 0x14000 ;
        else if (pcgrpId == GRP_16 || pcgrpId == GRP_E) limit = 0x100000 ;
        else limit = 0x10000 ;
        if (nbByte > limit) {
            printf ("%s: Source file contains more than %lu bytes\n", argP, limit) ;
            error = ERR_FMT ;
            break ;
        }
        if (pcgrpId == GRP_16 ) limit = 0x100000 ;
        if ( (addr + nbByte) > limit) {
            printf ("%s: (Address + Size) greater than %lu bytes\n", argP, limit) ;
            error = ERR_FMT ;
            break ;
        }
        if (type == TYPE_RSV) { /* from PC-1500 or PC-1600 only */
                if (pcgrpId == IDENT_PC1500) {
                    limit = 190 ;
                    if ( limit == nbByte +1 ) {
                        ++nbByte;
                        if (Qcnt ==0) printf ("%s: Reserve data are from PC-1600 or QTape!\n", argP) ;
                    }
                }
                else if (pcgrpId == GRP_16 || pcgrpId == IDENT_QTAPE ) {
                    limit = 189 ;
                    if ( limit == nbByte -1 ) {
                        --nbByte;
                        if (Qcnt ==0) printf ("%s: Reserve data are from PC-1500 standard or PC-1600 Mode 1!\n", argP) ;
                    }
                }
                if (nbByte > limit) {
                    printf ("%s: Reserve data greater than 189+%lu bytes\n", argP, limit-189) ;
                    error = ERR_FMT ;
                    break ;
                }
                else if (nbByte != limit) {
                    printf ("%s: Warning: Reserve data shorter than 189+%lu bytes\n", argP, limit-189) ;
                }
        }
        if (type == TYPE_DEF) { /* from PC-1500 only */
                limit = 156 ;
                if (nbByte > limit) {
                    printf ("%s: Def.Key data greater than %lu bytes\n", argP, limit) ;
                    // error = ERR_FMT ;
                    // break ;
                }
                else if (nbByte != limit) {
                    printf ("%s: Warning: Def.Key data shorter than %lu bytes\n", argP, limit) ;
                }
        }

        switch (pcgrpId) { /* Calculate the sample frequency and adapt to standardized ones */

          case IDENT_PC1500 :
            base_freq = BASE_FREQ2 ;
            freq = base_freq * info.bitLen/16 ;
//            if (freq > 21700 && freq <= 22500)
//                freq = 22050 ; /* bit3_15: 2% difference but 44,1 kHz better supported with sound hardware */
//            else if (freq == 7968) freq = 8000 ; /* bit4_15: slightly faster but exactly 16 kHz */
            break ;

          case IDENT_QTAPE :
            base_freq = BASE_FREQ4 ;
            freq = base_freq * info.bitLen/4 ;
//            if (freq == 22500) freq = 22050 ; /* bitQ3: 2% slower but 44,1 kHz better supported with sound hardware */
            if (freq == 7500) freq = 8000 ; /* bitQ4: faster 15 -> 16 kHz, experimentally */
            break ;

          case IDENT_ST :

            for ( ii = 0 ; ii < 4; ++ii ) {bitLS [ii] = (uint) strlen (bitS[ii]); }
            base_freq = BASE_FREQS ;
//            info.bitLen= strlen (bitS[0]) ;
//            freq = base_freq * info.bitLen/2 ;
            freq = base_freq * bitLS[0]/2 ;
//            if (freq == 10800) freq = 11025 ; /* bitS2 22 kHz */
//            if (freq == 21600) freq = 22050 ; /* bitS3 44.1 kHz */
            if (freq ==  7200) freq =  8000 ; /* bitS4 16 kHz */
//            else if (freq >  46500 && freq <  49000) freq = 48000 ; /* 96 kHz */
            break ;

          case GRP_E  :
          case GRP_G  :
          case GRP_16 :

            for ( ii = 0 ; ii < 4; ++ii ) {bitLE [ii] = (uint) strlen (bitE[ii]); }
            base_freq = BASE_FREQ3 ;
            freq = base_freq * bitLE[0]/2 ;
            if (freq == 7500) freq = 8000 ; /* bitE4 16 kHz */
            break ;

          default : /* common types with 4 kHz synchronisation signal */
            base_freq = BASE_FREQ1 ;
            freq = base_freq * info.bitLen/16 ;
            break ;
        }
        if      (freq >=  7800 && freq <=  8200) freq =  8000 ; /* 16 kHz */
        else if (freq >= 10800 && freq <= 11250) freq = 11025 ; /* 22.050 Hz */
        else if (freq >= 21600 && freq <= 22500) freq = 22050 ; /* 44.1 kHz */
        else if (freq >  23500 && freq <  24500) freq = 24000 ; /* 48 kHz */
        else if (freq >= 43200 && freq <= 45000) freq = 44100 ; /* 88.2 kHz */
        else if (freq >  46300 && freq <  49000) freq = 48000 ; /* 96 kHz */

        switch (pcgrpId) { /* Sound level */

            case GRP_E :
            case GRP_G :
            case GRP_16 :
                if (Amp_High < AMP_HIGH_E) Amp_High = AMP_HIGH_E ;
                if (Amp_Low  > AMP_LOW_E)  Amp_Low  = AMP_LOW_E ;
                break ;

            case GRP_OLD :
                if (type != TYPE_MEM) break ; /* because of DB MEM */

            case IDENT_PC1211 :
                if (Amp_High < AMP_HIGH_121) Amp_High = AMP_HIGH_121 ;
                if (Amp_Low  > AMP_LOW_121)  Amp_Low  = AMP_LOW_121 ;
                break ;

            default :
            /* Amp_High; Amp_Low from the initialization or --device in main */
                break ;
        }
        /* 2: Chamfer the edges, 1: Intermediate step for lower ramp slope */
        if (pcgrpId == GRP_E || pcgrpId == GRP_G || pcgrpId == GRP_16) {
            if (freq > 24000) {
                Amp2High = (uint) (15*Amp_High + AMP_MID)/16 ;
                Amp2Low  = (uint) (15*Amp_Low  + AMP_MID)/16 ;
            }
            else {
                Amp2High = (uint) (9*Amp_High + AMP_MID)/10 ;
                Amp2Low  = (uint) (9*Amp_Low  + AMP_MID)/10 ;
            }
            Amp1High = (uint) (Amp2High + AMP_MID)/2 ;
            Amp1Low  = (uint) (Amp2Low  + AMP_MID)/2 ;
        }
        else { /* for PC-1500 44.1 kHz and SuperTape */
            if (freq > 24000) {
                Amp2High = (uint) (7*Amp_High + AMP_MID)/8 ;
                Amp2Low  = (uint) (7*Amp_Low  + AMP_MID)/8 ;
            }
            else {
                Amp2High = (uint) (3*Amp_High + AMP_MID)/4 ;
                Amp2Low  = (uint) (3*Amp_Low  + AMP_MID)/4 ;
            }
            Amp1High = (uint) (Amp_High + AMP_MID)/2 ;
            Amp1Low  = (uint) (Amp_Low  + AMP_MID)/2 ;
            /* PC-1234 peak/min/max */
            Amp0High = (uint) Amp_High + AMP_MID/16 ;
            Amp0Low  = (uint) Amp_Low  - AMP_MID/16 ;
        }

        /* For signal shutdown at end of transmission, PC1234 */
        if (pcgrpId == IDENT_PC1211) AmpFshift = AMP_F_SHIFT_121 * 24000 / freq ;
        else AmpFshift = AMP_F_SHIFT * 24000 / freq ;

        /* Length of the synchronization tone and pauses */
        if (pcgrpId == GRP_E || pcgrpId == GRP_G || pcgrpId == GRP_16) {
            AmpFshift = AMP_F_SHIFT_E * 24000 / freq ;

            if (freq == base_freq && sync < 3) sync = 3; /* min. 3 sec GRP_E with asymmetric waveform 1*/
            info.nbSync1 = base_freq ;

            if (pcgrpId == GRP_E) { // && (type == TYPE_ASC || type == TYPE_BAS)) {
                if (sync < 2.125) nbSync = 17 * info.nbSync1 /8 ;   /* min. ca. 2.125 sec */
                else nbSync = (ulong)(sync*256) * info.nbSync1 /256 ;
            }
            else if (sync < 1.875) nbSync = 15 * info.nbSync1 /8 ;  /* min. ca. 1.875 sec */
            else nbSync = (ulong)(sync*256) * info.nbSync1 /256 ;   /* > 5000 + tolerance */

            if (syncS < 2.125) nbSyncS = 17 * info.nbSync1 /8 ;     /* 1. Spc after header > 2 s */
            else nbSyncS = (ulong)(syncS*256) * info.nbSync1 /256 ; /* min. ca. 2.125 sec */

            if (Scnt<1 || (info.debug & (SYNCL_STD | SYNCL_TRM)) > 0) {
                if (pcgrpId == GRP_16 && nbSync < 10000) nbSync = 10000 ; /* for first sync only */
                if (pcgrpId == GRP_E && (type == TYPE_ASC || type == TYPE_BAS)  &&  nbSync < 11250)
                                                                                    nbSync = 11250 ;
            }
            info.nbSync = nbSync ;
        }
        else if (pcgrpId == IDENT_ST) {
            info.nbSync1 = (2 * freq + bitLS[2]/2 )/ bitLS[2] ;
            info.nbSync = nbSync = sync * info.nbSync1 ;
        }
        else if (pcgrpId == IDENT_QTAPE) {
            info.nbSync1 = (base_freq +1 ) /2 ;
            info.nbSync = nbSync = (ulong)(sync*256) * info.nbSync1 /256 ;
        }
        else { /* PC-1211 to PC-1500 */
            info.nbSync1 = (base_freq +4 ) /8 ;
            info.nbSync = nbSync = (ulong)(sync*256) * info.nbSync1 /256 ;
        }

        /* Calculate the length and Ident of the destination file */
        error = LengthAndIdentOfBinWav (type, nbByte, nbSync, &info.ident, &nbSamp, &info.debug) ;
        if (error != ERR_OK) break ;

        /* Write the header of the destination file */
        if (KHXc > 0) {
            if (Qcnt == 0) printf ("File format  : forced to DSave khx format (no wav)\n") ;
            error = WriteHeadToKhx (ptrName, type, &info) ;
        }
        else if (TAPc > 0) {
            if (Qcnt == 0) printf ("File format  : forced to emulator tap format (no wav)\n") ;
        }
        else
            error = WriteHeadToWav (nbSamp, (ulong) (speed * freq * 2), &info) ;
        if (error != ERR_OK) break ;

        /* Write the synchro pattern for N times and set length of interim syncs  */
        if (Qcnt == 0 && (Scnt>0 || debug>0)) printf ("Synchro size : %lu bits\n", nbSync);

        if (pcgrpId == GRP_E || pcgrpId == GRP_G || pcgrpId == GRP_16) {
            /* for E500S (+ CE-126P) also spaces at start of file, wait until remote relays is switched on */
             error = WriteSyncToEWav (nbSync, nbSyncS, SYNC_E_HEAD, &info) ;

            if (pcgrpId == GRP_E        /* min. ca. 2.375 sec for first data block */
                    && sync < 2.5)  {   /* sync = 2.5 ; for first data block after header only */
                    nbSync = 10 * info.nbSync1 /4 ;
                    /* info.nbSync not changed: min. ca. 2.125 sec */
            }
            /* allow shorter syncs and spaces for interim syncs */
            else if ((info.debug & (SYNCL_STD | SYNCL_TRM)) == 0) {
                nbSyncS = (ulong)(syncS*256) * info.nbSync1 /256 ;

                if (sync < 1.75) nbSync =  7 * info.nbSync1 /4 ; /* min. ca. 1.7 sec */
                else nbSync = (ulong)(sync*256) * info.nbSync1 /256 ;
                info.nbSync = nbSync ;
            }
            // moved to WriteSync. else 16_DAT 5.0 sec, 16_ASC 5...5.175 sec, G8_ASC 3.0839
        }
        else if (pcgrpId == IDENT_ST) { /* SuperTape */
            /* Write the lead in  */
            if ((flags & 0x0100) == 0)
              for ( ii = 0 ; ii < nbSync ; ++ii ) {
                error = WriteBitToSWav (2, &info) ; /* 1250 Hz */
                if (error != ERR_OK) break ;
              }
            if (error != ERR_OK) break ;

            error = WriteSyncToSWav ( SUPT_HEAD, &info) ;
        }
        else { /* PC-1211 to PC-1500, QTape */
            error = WriteSyncToWav (nbSync, &info) ;

            /* TRM PC-1600 P.124 for PC-1500 first sync 1.260: Not so found! (-6 stop b: 1.2408) */
            if (info.ident == IDENT_PC15_DAT && sync > 1.0068)  /* 1.026 - 6 stop bits*/
                                         info.nbSync = (1007 * info.nbSync1)/1000;
            /* Standard sync between data blocks is: 6 ms + 2000 ms + 6 ms +? */
            else if (type == TYPE_DAT && sync > 2.009)  /* 2.017 - 4 stop bits*/
                                         info.nbSync = (2009 * info.nbSync1)/1000;
        }
        if (error != ERR_OK) break ;

        if (Qcnt == 0) {
           if (STc == 0 || pcgrpId != IDENT_ST) {
            if (QTc >1 ) printf ("Quick-Tape format : 0x%02X <- for QLOAD, similar to:\n",
                                 (uchar) info.ident);
            else if (QTc ==1 ) {
                if (type == TYPE_IMG || type == TYPE_BIN)
                    printf ("Quick-Tape with PC-1500 header : 0x%02X <- for QLOAD, similar to:\n",
                                 (uchar) info.ident);
                else {
                    printf ("This Quick-Tape format is not implemented with PC-1500 header.\n") ;
                    ++err_cnt ;
                    return(ERR_ARG);
                }
            }
            else printf ("Pocket format : 0x%02X <- ", (uchar) info.ident) ;
            if (type == TYPE_BIN)
                printf ("Binary for CLOAD M, PC-%lu\n", pcId) ;
            else if (type == TYPE_RSV)
                printf ("ReSerVe data for CLOAD in RSV Mode, PC-%lu\n", pcId) ;
            else if (type == TYPE_DEF)
                printf ("Def.Key data, PC-%lu\n", pcId) ;
            else if (type == TYPE_DAT)
                printf ("Special binary data for INPUT#, PC-%lu\n", pcId) ;
            else if (type == TYPE_MEM)
                printf ("Special binary DB data %u for CLOAD MEM, PC-%lu\n", info.ident, pcId) ;
            else if (type == TYPE_CRD || type == TYPE_TEL || type == TYPE_SCD ||type == TYPE_NOT)
                printf ("Special binary/Memo Database data %u for IN., PC-%lu\n", info.ident, pcId) ;
            else if (type == TYPE_ASC) /* PC-E/G/1600 */
                printf ("ASCII data for INPUT# (or LOAD CAS:) PC-%lu\n", pcId) ;
            else if (type == TYPE_BAS) /* PC-E/G/1600 */
                printf ("ASCII source for Text menu or LOAD CAS: PC-%lu\n", pcId) ; //BASIC
            else if (type == TYPE_TXT && type_asm) /* PC-14xx, CASL, CAP-X */
                printf ("Assembler image for load with CMT menu, PC-%lu\n", pcId) ;
            else if (type == TYPE_TXT) /* GRP_EXT, GRP_E */
                printf ("Basic image for CLOAD in TEXT modus, PC-%lu\n", pcId) ;
            else { /* TYPE_IMG */
                if (pcgrpId == IDENT_PC1500 || pcgrpId == IDENT_QTAPE ||
                    pcgrpId == GRP_16 || pcgrpId == GRP_E || pcgrpId == GRP_G)
                     printf ("Basic image with intermediate code, PC-%lu\n", pcId) ;
                else printf ("Basic (or RSV) image with intermediate code, PC-%lu\n", pcId) ;
            }
          }
          else printf ("SuperTape wav format\n") ;
        }

        /* No file header for TYPE_VAR, following data_variable block */
        if ((info.debug & NO_FILE_HEAD) == 0) {

            if ( (info.debug & DEBUG_TRACES) > 0 && Qcnt != 0 && info.ident < 0x100 )/* not for ST */
                printf(" FileID:%02X   ", (uchar) info.ident) ;     /* File ID */

            if (pcgrpId == IDENT_PC1500) {
                info.mode = info.mode_h = MODE_B22 ;
                order = ORDER_INV;                                    /* DAT: 1 sec originally */
                if (type == TYPE_DAT && (info.debug & SYNCL_STD) >0 ) info.nbSync = info.nbSync1 ;

                /* Write the TAP code */
                error = WriteQuaterToWav (IDENT_PC1500, 6, &info) ;
                if (error != ERR_OK) break ;

                /* Write the name, size, addresses */
                error = WriteHeadTo15Wav (ptrName, addr, eaddr, nbByte, // flags,
                                          type, &info) ;
                if (error != ERR_OK) break ;
                if (pcgrpId == IDENT_QTAPE) { /* Head switched to QT */
                    order = ORDER_Q ;
                    base_freq = BASE_FREQ4 ;
                    info.nbSync1 = (base_freq +1 ) /2 ;
                }
                if ((type == TYPE_BIN || Acnt > 0) && (Qcnt == 0)) {
                        printf ("Start Address: 0x%04X\n", (uint) addr);
                    if (type == TYPE_BIN)
                        printf ("End   Address: 0x%04X, Length: %d bytes\n", (uint) (addr + nbByte -1), (uint) nbByte);
                    if (Acnt > 1 || (type == TYPE_BIN && eaddr < 0xFFFF))
                        printf ("Entry Address: 0x%04X\n", (uint) eaddr);
                }
            }  // end if PC-1500
            else if (pcgrpId == IDENT_QTAPE) {
                info.mode = info.mode_h = mode_t = MODE_B11 ;
                order = ORDER_Q ;

                /* Write the TAP code */
                error = WriteByteToWav ((IDENT_QTAPE >> 8 ) & 0xFF, order, mode_t, &info) ;
                if (error != ERR_OK) break ;
                error = WriteByteToWav (IDENT_QTAPE & 0xFF, order, mode_t, &info) ;
                if (error != ERR_OK) break ;

                /* Write the name, size, addresses */
                error = WriteHeadToQWav (ptrName, addr, eaddr, nbByte, flags, type, &info) ;
                if (error != ERR_OK) break ;

                if ((type == TYPE_BIN || Acnt > 0) && (Qcnt == 0)) {
                    if (type == TYPE_BIN && flags > 0)
                        printf ("Flags: ME%01X, PV%i, PU%i\n", flags>>2, (flags>>1) &1, flags &1);
                    printf     ("Start Address: 0x%04X\n", (uint) addr);
                    if (type == TYPE_BIN)
                        printf ("End   Address: 0x%04X, Length: %d bytes\n", (uint) (addr + nbByte -1), (uint) nbByte);
                    if (Acnt > 1 || (type == TYPE_BIN && eaddr < 0xFFFF))
                        printf ("Entry Address: 0x%04X\n", (uint) eaddr);
                }
            }  // end if Quick-Tape
            else if (pcgrpId == IDENT_ST) {
                info.mode = info.mode_h = MODE_B10 ;
                order = ORDER_S;

                /* Write the Name and Header */
                error = WriteHeadToSWav (ptrName, addr, eaddr, nbByte, type, flags, &info) ;
                if (error != ERR_OK) break ;

                if ((type == TYPE_BIN || Acnt > 0) && (Qcnt == 0)) {
                    printf ("Start Address: 0x%04X\n", (uint) addr);
                    printf ("End   Address: 0x%04X, Length: %d bytes\n", (uint) (addr + nbByte -1), (uint) nbByte);
                    if (eaddr < 0xFFFF && eaddr != 0x0) printf ("Entry Address: 0x%04X\n", (uint) eaddr);
                }
            }
            else if (pcgrpId == GRP_E || pcgrpId == GRP_G || pcgrpId == GRP_16) {
                info.mode = info.mode_h = MODE_B9 ;
                order = ORDER_E;

                /* Write the Name and Header */
                error = WriteHeadToEWav (ptrName, ptrDstExt, addr, eaddr, nbByte, nbSync, nbSyncS, type, &info) ;
                if (error != ERR_OK) break ;

                if ((type == TYPE_BIN || Acnt > 0) && (Qcnt == 0)) {
                        printf ("Start Address: 0x%06X\n", (uint) addr);
                    if (type == TYPE_BIN)
                        printf ("End   Address: 0x%06X, Length: %d bytes\n", (uint) (addr + nbByte -1), (uint) nbByte);
                    if (Acnt > 1 || (type == TYPE_BIN && eaddr < 0xFFFFFF))
                        printf ("Entry Address: 0x%06X\n", (uint) eaddr);
                }
            }
            else { // PC-1100 ... PC-1475
                switch (info.ident) { /* Header Mode */
                case IDENT_PC1211 :
                case IDENT_PC121_DAT :
                    info.mode = info.mode_h = MODE_B20 ;
                    mode_t = MODE_B21 ;
                    break ;

                case IDENT_OLD_BAS :
                case IDENT_OLD_DAT :
                case IDENT_OLD_BIN :
                case IDENT_OLD_MEM :
                case IDENT_OLD_MEM2:
                    info.mode = info.mode_h = mode_t = MODE_B19 ;
                    break ;

                case IDENT_NEW_DAT :
                    info.mode_h = MODE_B16 ;
                    info.mode = mode_t = MODE_B15 ;
                    break ;

                case IDENT_NEW_BAS :
                case IDENT_EXT_BAS :
                case IDENT_NEW_BIN :

                    if (pcId == 1401) { /* PC-1401 V.1 */
                        info.mode_h = mode_t = MODE_B15 ;
                        info.mode = MODE_B12 ;
                    }
                    else {
                        info.mode_h = mode_t = MODE_B16 ;
                        info.mode = MODE_B13 ;
                    }

                    if (pcId != 1100)
                        break ;

                case IDENT_NEW_TEL :
                case IDENT_NEW_SCD :
                case IDENT_NEW_NOT :
                case IDENT_NEW_CRD :
                case IDENT_NEW_CSL :
                    info.mode_h = mode_t = MODE_B17 ;
                    info.mode = MODE_B14 ;
                    break ;

                default :
                    printf ("%s: Unknown Ident\n", argP) ;
                    info.mode = info.mode_h = mode_t = MODE_B22 ;
                    break ;
                }
                /* Write the TAPE code */
                error = WriteByteToWav ( (ulong) info.ident, ORDER_STD, mode_t, &info) ;
                if (error != ERR_OK) break ;

                if (info.ident == IDENT_NEW_TEL || info.ident == IDENT_NEW_SCD ||
                    info.ident == IDENT_NEW_NOT || info.ident == IDENT_NEW_CRD  ) {

                    /* For memo data, write the length after the file id*/
                    info.nbByte = nbByte ;
                    info.nbByte--;
                    if ( (info.debug & 0x0040) > 0) printf(" %04X \n", (uint) info.nbByte);

                    error = WriteByteToWav ( (ulong) (info.nbByte>>8 & 0xFF) , ORDER_STD, info.mode, &info) ;
                    if (error != ERR_OK) break ;
                    error = WriteByteToWav ( (ulong) (info.nbByte & 0xFF) , ORDER_STD, info.mode, &info) ;
                    if (error != ERR_OK) break ;
                    error = WriteSyncToWav (39, &info) ;
                    if (error != ERR_OK) break ;
                }
                /* Write the Name */
                error = WriteSaveNameToWav (ptrName, info.mode_h, &info) ;
                if (error != ERR_OK) break ;
                                           /* DAT: 2 sec between OLD/NEW variable blocks originally */
                if (type == TYPE_DAT && (info.debug & SYNCL_STD) >0 ) info.nbSync = info.nbSync1 <<1 ;

                switch (info.ident) { /* Body Data Mode */
                case IDENT_PC1211 :
                case IDENT_PC121_DAT :
//                    info.mode = MODE_B20 ;
                    break ;

                case IDENT_OLD_BAS :
                case IDENT_OLD_BIN :
                case IDENT_OLD_MEM :
                case IDENT_OLD_MEM2:
                case IDENT_OLD_DAT :
//                    info.mode = MODE_B19 ;
                    break ;

                case IDENT_NEW_DAT :
//                    info.mode = MODE_B15 ;
                    break ;

                case IDENT_EXT_BAS :

                case IDENT_NEW_BAS :
                case IDENT_NEW_CSL :

                case IDENT_NEW_TEL :
                case IDENT_NEW_SCD :
                case IDENT_NEW_NOT :
                case IDENT_NEW_CRD :
                case IDENT_NEW_BIN :

                    break ;

                default :
                    printf ("%s: Unknown Ident\n", argP) ;
                    info.mode = MODE_B22 ;
                    break ;
                }
            }  // PC-121x ... PC-1475
            if (error != ERR_OK) break ;
        }
        info.total = 0 ; /* count bytes of body only */

        switch (info.ident) { /* header was written, write all data now*/
        case IDENT_PC15_BAS :
        case IDENT_QT_BAS :
            /* Write the datas */
            do {
                inVal = fgetc (srcFd) ;
                if (inVal == EOF) break ;

                /* BAS_1500_EOF was included in images from Bas2img but should be no more*/
                if ( inVal == BAS_1500_EOF && info.total >= nbByte ) { // nbByte - 1, changed in ReadFL
                    if (Qcnt == 0) printf
                        ("\nEnd of file mark %02X should not be included in the image\n", inVal) ;
                    /* EOF mark will be written by WriteFooter */
                    break ;
                }

                error = WriteByteSumToWav ( (uint) inVal, order, info.mode, &info) ;
                if (error != ERR_OK) break ;

            } while (1) ;
            if (error != ERR_OK) break ;

            /* Write the END code */
            if (pcgrpId == IDENT_PC1500 || QTc == 1)
                error = WriteFooterTo15Wav (type, &info) ;

            else if (pcgrpId == IDENT_QTAPE) { /* && QTc > 1 Quick-Tape pur */
                error = WriteByteSumToWav ( (uint) BAS_1500_EOF, order, info.mode, &info) ;
                if (error != ERR_OK) break ;
                else        error = WriteSyncToWav (800, &info) ; /* 0.32 s */
                if (error != ERR_OK) break ;
            }
            if (pcgrpId == IDENT_QTAPE) error = WriteShutdownToQWav (&info) ;

            break ; // IDENT_PC15_BAS

        case IDENT_QT_RSV :
        case IDENT_QT_DIM :
        case IDENT_QT_BIN :

        case IDENT_PC15_RSV :
        case IDENT_PC15_DEF :
        case IDENT_PC15_BIN :
            /* Write the datas */
            do {
                inVal = fgetc (srcFd) ;
                if (inVal == EOF) {
                    if (info.ident == IDENT_PC15_RSV && info.total +1 == nbByte)
                        inVal = 0 ; /* append 0 for RSV from PC-1600 Mode 0*/
                    else break ;
                }
                error = WriteByteSumToWav ( (uint) inVal, order, info.mode, &info) ;
                if (error != ERR_OK) break ;

            } while (1) ;
            if (error != ERR_OK) break ;

            /* Write the END code */
            if (pcgrpId == IDENT_PC1500 || QTc == 1)
                error = WriteFooterTo15Wav (type, &info) ;

            else if (pcgrpId == IDENT_QTAPE) {
                error = WriteSyncToWav (800, &info) ; /* 0.32 s */
                if (error != ERR_OK) break ;
            }
            if (pcgrpId == IDENT_QTAPE) error = WriteShutdownToQWav (&info) ;

            break ; // IDENT_PC15_BIN, IDENT_PC15_RSV

        case IDENT_OLD_BAS :
        case IDENT_PC1211 :
            /* Write the datas */
            do {
                inVal = fgetc (srcFd) ;
                if (inVal == EOF) break ;

                if ((inVal == BAS_OLD_EOF  && info.total +1 == nbByte ) ||
                    (inVal == BAS_1500_EOF && info.total  >=  nbByte  ) ) {
                    if (Qcnt == 0 && SHCc == 0) printf
                        ("\nEnd of file mark %02X should not be included in the image\n", inVal) ;
                    break ;
                }
                error = WriteByteSumToWav((uint) inVal, ORDER_STD, info.mode, &info) ;
                if (error != ERR_OK) break ;

            } while (1) ;
            if (error != ERR_OK) break ;

            /* Write the END code */
            error = WriteByteToWav (BAS_OLD_EOF, ORDER_STD, MODE_B19_2, &info) ;
            if ( (info.debug & DEBUG_TRACES) > 0 )
                printf(" EOF:%02X ", (uchar) BAS_OLD_EOF);
            if (error != ERR_OK) break ;

            if ( info.ident == IDENT_PC1211) {
                error = WriteBitToWav (3, &info) ;
                if (error != ERR_OK) break ;
                error = WriteSyncToWav (42, &info) ;
            }
            if (error == ERR_OK) error = WriteShutdownToWav (&info) ;

            break ;  // IDENT_OLD_BAS, IDENT_PC1211

        case IDENT_OLD_BIN :
            /* Write the address and length */
            error = WriteHeadToBinWav (addr, nbByte, info.mode_h, &info) ;
            if (error != ERR_OK) break ;

            /* Write the data */
            do {
                inVal = fgetc (srcFd) ;
                if (inVal == EOF) break ;

                error = WriteByteSumToWav ( (uint) inVal, ORDER_STD, info.mode, &info) ;
                if (error != ERR_OK) break ;

            } while (1) ;
            if (error != ERR_OK) break ;

            /* Write the END code */
            error = WriteByteToWav (BAS_OLD_EOF, ORDER_STD, MODE_B19_2, &info) ;
            if ( (info.debug & DEBUG_TRACES) > 0 )
                printf(" EOF:%02X ", (uchar) BAS_OLD_EOF);
            if (error == ERR_OK) error = WriteShutdownToWav (&info) ;

            break ; // IDENT_OLD_BIN

        case IDENT_OLD_MEM :
        case IDENT_OLD_MEM2:
            /* Write the address (4 bit) and check the length */
            error = WriteHeadToMemWav (addr, eaddr, nbByte, info.mode_h, &info) ;
            if (error != ERR_OK) break ;

            /* Write the data */
            do {
                inVal = fgetc (srcFd) ;
                if (inVal == EOF) break ;

                error = WriteByteSumToWav ( (uint) inVal, ORDER_STD, info.mode, &info) ;
                if (error != ERR_OK) break ;

            } while (1) ;
            if (error != ERR_OK) break ;

            /* Write the END code, Shutdown_Form with less waves */
            error = WriteByteToWav (BAS_OLD_EOF, ORDER_STD, MODE_B19_2, &info) ; /* Mode is 2 waves to long */
            if ( (info.debug & DEBUG_TRACES) > 0 )
                printf(" EOF:%02X ", (uchar) BAS_OLD_EOF);
            if (error == ERR_OK) error = WriteShutdownToWav (&info) ;

            break ; // IDENT_OLD_MEM

        case IDENT_NEW_BAS :
        case IDENT_NEW_CSL :
        case IDENT_EXT_BAS :

            /* Write the datas */
            /* the older simple algorithm seems to work as well, but this is now, what the PC does originally */
            for ( ii = 0 ; ii < nbByte - 1 ; ++ii ) {
                inVal = fgetc (srcFd) ;
                if (inVal == EOF) break ;

                if ( inVal == BAS_NEW_EOF ) {
                    if (info.count + 1 == BLK_NEW && info.sum == 0xE1) { /* Constellation will generate 2-times BAS_NEW_EOF */
                        printf ("\nERROR %i at %lu. byte, usually the low byte of a BASIC line number\n", ERR_SUM, info.total) ;
                        printf ("This binary constellation activates the CLOAD bug of this series. The line\n") ;
                        printf ("number must be changed or minor changes done in the BASIC text before.\n") ;
                        /* Seldom Bug in CLOAD, for PC-1402/(01) at known ROM address: 40666 */
                        if ((info.debug & ERR_OFF) == 0 ) {
                            error = ERR_SUM ;
                            break ;
                        }
                    }
                }
                error = WriteByteSumToWav ( (uint) inVal, ORDER_STD, info.mode, &info) ;
                if (error != ERR_OK) break ;
            }
            if (error != ERR_OK) break ;

            inVal = fgetc (srcFd) ; /* Read the last byte before EOF mark */
            if (inVal == EOF) break ;

            if (inVal == BAS_NEW_EOF) {
                        /* EOF mark should not be included for this file type normally*/
                        if (Qcnt == 0) printf ("End of File mark %i should not be included in the image\n", inVal) ;
                        /* if end of block, then an additional checksum would be written, but this does work anyhow */
            }
            else {
                if ( (info.debug & 0x0040) > 0 ) printf(" %02X", (uchar) inVal);
                error = WriteByteToWav ( (uint) inVal, ORDER_STD, info.mode, &info) ;
                if (error != ERR_OK) break ;
                CheckSumB1 ((uint) inVal, &info) ; /* never write the checksum before BAS_NEW_EOF */
                ++info.total ;
                ++info.count ; /* for debug purposes only, WriteFooter will reset it */
            }

            /* Write the END code */
            error = WriteFooterToNewWav (&info) ;

            break ; // IDENT_NEW_BAS, IDENT_EXT_BAS

        case IDENT_NEW_BIN :
            /* Write the address and length */
            error = WriteHeadToBinWav (addr, nbByte, info.mode_h, &info) ;
            if (error != ERR_OK) break ;
            /* no break */

        case IDENT_NEW_TEL :
        case IDENT_NEW_SCD :
        case IDENT_NEW_NOT :
        case IDENT_NEW_CRD :

            /* Write the datas */
            for ( ii = 0 ; ii < nbByte - 1 ; ++ii ) {
                inVal = fgetc (srcFd) ;
                if (inVal == EOF) break ;

                error = WriteByteSumToWav ( (uint) inVal, ORDER_STD, info.mode, &info) ;
                if (error != ERR_OK) break ;
            }
            if (error != ERR_OK) break ;

            inVal = fgetc (srcFd) ; /* Read the last byte before EOF mark */
            if (inVal == EOF) break ;

            if ( (info.debug & 0x0040) > 0 ) printf(" %02X", (uchar) inVal);
            error = WriteByteToWav ( (uint) inVal, ORDER_STD, info.mode, &info) ;
            if (error != ERR_OK) break ;
            CheckSumB1 ( (uint) inVal, &info) ; /* never write the checksum before BAS_NEW_EOF */
            ++info.total ;
            ++info.count ; /* for debug purposes only, WriteFooter will reset it */

            /* Write the END code */
            if ( info.ident == IDENT_NEW_BIN) error = WriteFooterToNewWav (&info) ;
            else WriteFooterToMemoWav (&info) ;

            break ; // IDENT_NEW_BIN and IDENT_NEW_Memos

        case IDENT_NEW_DAT :
        case IDENT_OLD_DAT :
            if (KHXc > 0) info.nbSync = 97 ; /* force sync length SYNC_KHX_TX4 */

        case IDENT_PC121_DAT :
            /* Do multiple data variable list*/
            do {
                /* One variable block*/
                error = WriteHeadToDataWav ( &srcHead, &dstHead, &itemLen, &itemType, &pos_end, &nbByte, &info, srcFd) ;
                /* Read, write, print info, reset checksum */
                if (error != ERR_OK) break ;

                if ( (info.debug & 0x0060) == 0x0020 )
                    printf("\nPos Byte\n") ;     /* Head of Data Row */

                /* Write the data */
                do {
                    for ( ii = 0 ; ii < itemLen; ++ii ) {
//                        fgetpos(srcFd, &position) ;
                        position = ftell( srcFd ) ;
                        if (position <= 0) {
                            printf ("\n%s:convert - Can't get position in the source file\n", argP) ;
                            return ( ERR_FILE ) ;
                        }
                        inVal = fgetc (srcFd) ;
                        if (inVal == EOF) break ;
                        if (SHCc > 0) inVal = SwapByte(inVal);
                        if ( ii == 0 && inVal == DATA_EOF && srcHead.length == DATA_VARIABLE ) break ;
                        varItem[ii] = (uint) inVal ;
                    }
                    if (inVal == EOF) {
                            printf ("\n%s:convert - file ended with an incomplete data variable block\n", argP) ;
                            return (ERR_FMT) ;
                    }
                    if ((srcHead.length == DATA_VARIABLE) && (info.count == 0 )&& (inVal == DATA_EOF)) break ;
                    /* Mark will written by WriteFooter if needed */

                    /* Convert numeric items from PC-1500 to other series */
                    error = ConvertDataVariableItem (varItem, &srcHead, &dstHead, itemLen, itemType, info.debug) ;

                    for ( ii = 0 ; ii < itemLen; ++ii ) {

                        if ( (info.debug & 0x0060) == 0x0020 )
                            printf("%ld %u \n", position, (uint) varItem[ii]) ;
                        error = WriteByteSumToDataWav ( (ulong) varItem[ii], info.mode, &info) ;
                        if (error != ERR_OK) break ;
                    }

                    if ( info.ident == IDENT_PC121_DAT) { /* length before EOF must be the same as after every item */
                        // if (info.total + info.total_diff < nbByte -(1 + DATA_HEAD_LEN)) /* EOF + no header */
                            error = WriteSyncToWav (111, &info) ;
                            if (error != ERR_OK) break ;
                    }

                } while ( (ulong) position < pos_end && inVal != EOF && error == ERR_OK) ;
                if (error != ERR_OK) break ;

                /* Multiple data variable list was not supported with Ver. 1.4.2, option -VAR needed */
                /* Checksum was included between multiple Variable Blocks if itemLen<>8 and Wav2bin 1.5.0 */
                if ( (ulong) position >= pos_end && (info.debug & DATA_W2B150) > 0 &&
                                                    (srcHead.itemLen & ( DATA_STD_LEN - 1 ) ) == 0 ) {
                    inVal = fgetc (srcFd) ;
                    break ;
                }

                /* Write the END code of one or all data blocks */
                error = WriteFooterToDataWav (dstHead.length, &info) ;
                if (error != ERR_OK) break ;

                if (info.ident == IDENT_PC121_DAT) {
                    error = WriteBitToWav (3, &info) ;
                    if (error != ERR_OK) break ;
                    error = WriteSyncToWav (42, &info) ;
                    break ; /* one variable length block only, original 7 +1 sil. +84 ms*/
                }
                /* Write the synchronization pattern for the next data block */
                if (inVal != EOF && info.total + info.total_diff < nbByte)       /* original length 2s */
                                                            error = WriteSyncToWav (info.nbSync, &info) ;
                else break ;
            } while (inVal != EOF && error == ERR_OK) ;

            if (error == ERR_OK && pcgrpId == GRP_EXT) error = WriteSyncToWav (9, &info) ;
            if (error == ERR_OK) error = WriteShutdownToWav (&info) ;

            break ; // IDENT_NEW_DAT, IDENT_OLD_DAT, IDENT_PC121_DAT

        case IDENT_QT_DAT :/* NOT IMPLEMENTED - see comments for IDENT_QT_DAT! */
                           /* variable name and type would be needed, also usedat_len is depending */
                           /* from variable block length and if it is fragmented in RAM (@$) */

        case IDENT_PC16_DAT :

            /* Switch info.block_len between DATA_HEAD_LEN and BLK_E_DAT for envelope */
            /* content is similar to IDENT_PC15_DAT */
            /* see Tech Ref. Man. PC-1600 Page 117-121 */

        case IDENT_PC15_DAT :

            /* Do multiple data variable list*/
            do {
                /* One variable block*/
                /* Read, write, print info, reset checksum */
                error = WriteHeadTo156DataWav ( &srcHead, &dstHead, &itemLen, &itemType, &pos_end, &nbByte, &info, srcFd) ;
                if (error != ERR_OK) break ;
                if (info.ident == IDENT_PC16_DAT) error = WriteSyncToEWav (nbSync, nbSyncS, SYNC_E_DATA, &info) ;
                else if (info.ident == IDENT_PC15_DAT) error = WriteSyncToWav (73, &info) ;
                // IDENT_QT_DAT, sync 0.26s , calculate info.usedat_len for WriteUsedatLenToQTWav
                if (error != ERR_OK) break ;

                if ( (info.debug & 0x0060) == 0x0020 )
                    printf("\nPos Byte\n") ;     /* Head of Data Row */

                /* Write the data */
                do {
                    for ( ii = 0 ; ii < itemLen; ++ii ) {
//                        fgetpos(srcFd, &position) ;
                        position = ftell( srcFd ) ;
                        if (position <= 0) {
                            printf ("\n%s:convert - Can't get position in the source file\n", argP) ;
                            return ( ERR_FILE ) ;
                        }
                        inVal = fgetc (srcFd) ;
                        if (inVal == EOF) break ;
                        if (SHCc > 0) inVal = SwapByte(inVal); /* data from other series are swapped */
                        if ( ii == 0 && srcHead.length == DATA_VARIABLE && inVal == DATA_EOF) {
                            /* block end mark not written and not included in total write counter */
                            // Bin2wav 2.09b3b3: ++info.total_diff; moved to WHead
                            break ;
                        }
                        varItem[ii] = (uint) inVal ;
                    }
                    if (inVal == EOF) {
                            printf ("\n%s:convert - file ended with an incomplete data variable block\n", argP) ;
                            return (ERR_FMT) ;
                    }
                    if (srcHead.length == DATA_VARIABLE && (ulong) position >= pos_end && inVal == DATA_EOF) break ;
                    /* Mark will written by WriteFooter if needed */

                    /* Convert numeric items (single precision only) from other series to PC-1500 */
                    error = ConvertDataVariableItem (varItem, &srcHead, &dstHead, itemLen, itemType, info.debug) ;

                    for ( ii = 0 ; ii < itemLen; ++ii ) {

                        if ( (info.debug & 0x0060) == 0x0020 )
                            printf("%d %d \n", (uint) position, varItem[ii]) ;
                        error = WriteByteSumTo156Wav ((ulong) varItem[ii], &info) ;
                        if (error != ERR_OK) break ;
                    }
                // TODO (mr#4#): More tests, pos_end
                } while ( (ulong) position < pos_end && inVal != EOF && error == ERR_OK) ;
                if (error != ERR_OK) break ;

                if (info.ident == IDENT_PC15_DAT) {
                /* Write the END code of one data block */
                    error = WriteFooterTo15DataWav (&info) ;
                    if (error != ERR_OK) break ;

                    /* Write the synchro patern for the next data block */
                    if (inVal != EOF && info.total + info.total_diff < nbByte)
                                                            error = WriteSyncToWav (info.nbSync, &info) ;
                }
                else if (info.ident == IDENT_PC16_DAT) {
                    if (inVal != EOF && info.total + info.total_diff < nbByte)
                                     error = WriteSyncToEWav (info.nbSync, nbSyncS, SYNC_E_DATA, &info) ;
                }
                // IDENT_QT_DAT: (fill data from WBsum with usedat_len), to next variable sync 0.76s
                if (error != ERR_OK) break ;

            } while (inVal != EOF && error == ERR_OK) ;
            if (error > ERR_OK) break ;

            /* Write the END code */
            if (info.ident == IDENT_PC15_DAT) error = WriteFooterTo15Wav (type, &info) ;
            else if (info.ident == IDENT_PC16_DAT) error = WriteFooterToEWav (type, &info) ;
            // IDENT_QT_DAT Footer: + one Header 0xFF, 0xFF + 5 meaningless (+CS +EOB), sync 0.5s

            break ; // IDENT_PC15_DAT, IDENT_PC16_DAT

        case IDENT_PC16_CAS :
        case IDENT_E_ASC :

            ii = 0 ;
            do {
                inVal = fgetc (srcFd) ;

                if (inVal == EOF || (inVal == EOF_ASC && SHCe > 0 )) {
                    if ( ii == 0 )      { inVal = 0x0D ; ++ii; }
                    else if ( ii == 1 ) { inVal = 0x0A ; ++ii; }
                    else if ( ii == 2 ) { inVal = EOF_ASC ; ++ii; }
                    else if ( ii == 3 )   inVal = 0x0 ;
                }
                else if ( inVal == 0x0D && ii == 0 ) ++ii ;
                else if ( inVal == 0x0A && ii == 1 ) ++ii ;
                else    ii = 0 ;

                if (info.count == 0 && info.total > 0) {
                    /* Write the block stop bit, space, sync and start bit */
                    error = WriteSyncToEWav (info.nbSync, nbSyncS, SYNC_E_DATA, &info) ;
                    if (error != ERR_OK) break ;
                }
                /* Write the datas */
                error = WriteByteSumToWav ( (uint) inVal, ORDER_E, info.mode, &info) ;
                if (error != ERR_OK) break ;

            } while (info.count > 0 || ii < 3 ) ;
            if (error != ERR_OK) break ;

        error = WriteFooterToEWav (type, &info) ;

        break ; // IDENT_E_ASC, IDENT_PC16_CAS

        case IDENT_E_BIN  :
        case IDENT_E_BAS  : /* or G16 RSV */

        case IDENT_ST  :    /* SuperTape */

            do {
                inVal = fgetc (srcFd) ;
                if (inVal == EOF) break ;

                if ( info.total == 0 && info.ident == IDENT_E_BAS && inVal == 0xFF) {
                    ++wrn_cnt;
                    if (Qcnt == 0) printf
                        ("\nStart byte: %02X. If a file header is included, use --type=i16 for PC-1600.\n", inVal) ;
                }
                if ( inVal == BAS_1500_EOF && info.total >= nbByte ) {
                    ++wrn_cnt;
                    if (Qcnt == 0) printf
                        ("\nEnd of file mark %02X should not be included in the image\n", inVal) ;
                    break ;
                }
                /* Write the datas */
                error = WriteByteSumToWav ( (uint) inVal, order, info.mode, &info) ;
                if (error != ERR_OK) break ;

            } while (1) ;
            if (error != ERR_OK) break ;

            if (   (info.ident == IDENT_E_BAS && pcgrpId == GRP_E) /* not GRP_G, not GRP_16 */
                || (info.ident == IDENT_ST  &&  type == TYPE_IMG ) ) {
                error = WriteByteSumToWav ( BAS_1500_EOF, order, info.mode, &info) ;
                if (error != ERR_OK) break ;
            }
            if (info.ident == IDENT_ST) {
                if (pcId == 36015) error = WriteBitToSWav (0, &info) ; /* one stop bit found originally */
                if (error != ERR_OK) break ;
                for ( ii = 0 ; ii < 311; ++ii ) { /* 0.25 s pause */
                    error = WriteBitToSWav (3, &info) ;
                }
                // TODO (Mr#2#): This SuperTape end was not found for the PC-1500. Where from?
                if (pcId != 36015) {
                    error = WriteByteToSWav(SUPT_SYNC, &info) ;
                    if (error != ERR_OK) break ;
                    error = WriteShutdownToSWav (&info) ;
                }
            }
            else error = WriteFooterToEWav (type, &info) ;

            break ; // IDENT_E_BIN, IDENT_E_BAS, ST

        default :
            printf ("%s:Convert: Unknown Ident\n", argP) ;
            error = ERR_ARG ;
            break ;
        } // end switch ident

        if (KHXc > 0) WriteFooterToKhx (&info) ;

    } while (0) ;
    error_tmp = error ;
    if (error != ERR_OK && err_cnt ==0) ++err_cnt;

    /* Check if the tap file name matches the requirements of the go emulators */
    if (TAPc > 0 ) {
        strncpy( tmpS, ptrName, 20) ;
        if (pcgrpId == IDENT_PC1500) {
            if (info.ident == IDENT_PC15_BAS)      strncat( tmpS, "_B", 20 - strlen(tmpS)) ;
            else if (info.ident == IDENT_PC15_BIN) strncat( tmpS, "_LM",20 - strlen(tmpS)) ;
            else if (info.ident == IDENT_PC15_DAT) strncat( tmpS, "_D", 20 - strlen(tmpS)) ;
            else if (info.ident == IDENT_PC15_RSV) strncat( tmpS, "_R", 20 - strlen(tmpS)) ;
        }
        strncat( tmpS, ".tap", 24 - strlen(tmpS)) ;
        tmpSPos = strlen(ptrDstFile)- strlen(tmpS) ;
        if ( tmpSPos >= 0)
            if  (Qcnt == 0 && strcmp( tmpS, ptrDstFile + tmpSPos) != 0)
                printf ("\nNOTE: For o2s emulators, rename the file exactly to: %s\n", tmpS) ;
    }

    /* Close the source file */
    if (srcFd != NULL) {
        error = fclose (srcFd) ;
        if (error != ERR_OK) {
            printf ("%s: Can't close the source file\n", argP) ;
            error_tmp = ERR_FILE ;
        }
    }

    /* correct the count of samples, for multi data blocks needed */
    if (TAPc == 0 && KHXc == 0 && (error == ERR_OK || error == ERR_NOK)) {
        error = WriteSampleCountToHeadOfWav (nbSamp, &info) ; /* estimated nb for older series */
        if (error != ERR_OK) {
            printf ("%s: Can't change the sample count inside the head of the destination file\n", argP) ;
            error_tmp = ERR_FILE ;
        }
    }

    if (Qcnt == 0)  {
        printf("File %s", ptrDstFile );
        if (wrn_cnt > 0 || err_cnt > 0) printf("\n");
        printf(" was written" );
        if (wrn_cnt > 0 && ((info.debug & DEBUG_TRACES) > 0 || err_cnt == 0) ) printf (", %ld warning(s)", wrn_cnt );
        if (err_cnt > 0) printf (", %ld error(s)!\n", err_cnt );
        else printf (".\n");
    }
    /* Close the destination file */
    if (info.ptrFd != NULL) {
        error = fclose (info.ptrFd) ;
        if (error != ERR_OK) {
            printf ("%s: Can't close the destination file\n", argP) ;
            error_tmp = ERR_FILE ;
        }
    }
    error = error_tmp ;
    return (error);
}

/*Read Header data from SHC-File,  sets SHCc and pcgrpId also */
int ReadHeadFromShc (char*  ptrSrcFile,
                     uchar* ptrType,
                     ulong* ptrAddr,
                     char*  ptrName )
{
        FILE  *srcFd ;
         int  inVal, ii ;
       ulong  byte ;
      ushort  ident ;
       uchar  type = TYPE_NOK ;
       uchar  tmpS[8] ;
        long  position;
         int  error_tmp, error = ERR_NOK ;

    do {
        /* 1. Open the source file */
        srcFd = fopen (ptrSrcFile, "rb") ;
        if (srcFd == NULL) {
            printf ("%s: Can't open the source file: %s\n", argP, ptrSrcFile) ;
            error = ERR_FILE ;
            break ;
        }

        inVal = fgetc (srcFd) ;
        if (inVal == EOF) break ;
        else ident = inVal ;
        error = ERR_OK ;

        switch (ident) {

        case IDENT_OLD_BAS :
            pcgrpId = GRP_OLD ; /*or IDENT_PC1211 encapsulated */
            type = TYPE_IMG ;
            break ;

        case IDENT_OLD_DAT :
            pcgrpId = GRP_OLD ; /*or IDENT_PC1211 encapsulated */
            type = TYPE_DAT ;
            break ;

        case IDENT_OLD_BIN :
            pcgrpId = GRP_OLD ;
            type = TYPE_BIN ;
            break ;

        case IDENT_NEW_BIN :
            pcgrpId = GRP_NEW ; /*or GRP_EXT */
            type = TYPE_BIN ;
            break ;

        case IDENT_NEW_DAT :
            pcgrpId = GRP_NEW ; /*or GRP_EXT */
            type = TYPE_DAT ;
            break ;

        case IDENT_NEW_BAS :
            pcgrpId = GRP_NEW ;
            type = TYPE_IMG ;
            break ;

        case IDENT_EXT_BAS :
            pcgrpId = GRP_EXT ;
            type = TYPE_IMG ;
            break ;

        default :    /* Password or IDENT_PC1500 are NOT supported */
            printf ("%s: Unsupported Identity %i of the SHC file\n", argP, ident) ;
            error = ERR_FMT ;
            break ;
        }
        if ( error != ERR_OK ) break;
        *ptrType = type ;

        for ( ii = 0 ; ii < 8 ; ++ii ) { /* no checksum included*/

            inVal = fgetc (srcFd) ;
            if (inVal == EOF) error = ERR_FMT ;
            else byte = SwapByte( (ulong) inVal) ;
            if (error != ERR_OK || ii == 7 ) break ;

            tmpS[6 - ii] = byte ;
        }
        if ( byte != 0xF5 || ii < 7 ) {
            printf("\n%s: Unexpected byte %lu in SHC file name header, position %i\n", argP, byte, ii + 1 ) ;
            error = ERR_FMT ;
        }
        if ( error != ERR_OK ) break;

        if (pcgrpId == GRP_OLD ) conv_old2asc( tmpS, 7) ;
        if (strlen(ptrName)==0) for ( ii = 0 ; ii < 8 ; ++ii ) ptrName[ii] = tmpS[ii] ;

        if (type == TYPE_BIN ) {
            for ( ii = 0 ; ii < 8 ; ++ii ) { /* no checksum included*/
                inVal = fgetc (srcFd) ;
                if (inVal == EOF) error = ERR_FMT ;
                else byte = SwapByte( (ulong) inVal) ;
                if (error != ERR_OK) break ;
                tmpS[ii] = byte;
            }
            if (error != ERR_OK) break ;

            *ptrAddr   = tmpS[4] ;
            *ptrAddr   = (*ptrAddr << 8) + tmpS[5] ;
            /* length will new calculated from real length */
        }

        /* Get the length of the SHC-Header */
        position = ftell (srcFd) ;
        if (position < ERR_OK) {
            printf ("%s: Can't ftell the file\n", argP) ;
            error = ERR_FILE ;
            break ;
        }
        else {
            SHCc = position ; /* SHC header length */
            if (type == TYPE_IMG) { /* End marks included in SHC image */
                if ( pcgrpId == GRP_NEW || pcgrpId == GRP_EXT ) SHCe = 2;
                else  SHCe = 1;
            }
            else if (type == TYPE_BIN) {
                SHCe = 1;
            }
            error = ERR_OK ;
        }

    } while (0) ;
    error_tmp = error ;

    /* Close the source file */
    if (srcFd != NULL) {
        error = fclose (srcFd) ;
        if (error != ERR_OK) {
            printf ("%s: Can't close the source file\n", argP) ;
            error_tmp = ERR_FILE ;
        }
    }
    error = error_tmp ;
    return (error);
}

/*Read Header data from PC-1600 16 byte file header, sets STc */
int ReadHeadFromI16 (char*  ptrSrcFile,
                     uchar* ptrType,
                     ulong* ptrAddr,
                     ulong* ptrEaddr)
{
        FILE  *srcFd ;
         int  inVal, ii ;
       ulong  length ;
       uchar  tmpS[16] ;
        long  position, nbByte ;
         int  error_tmp, error = ERR_OK ;

    do {
        /* 1. Open the source file */
        srcFd = fopen (ptrSrcFile, "rb") ;
        if (srcFd == NULL) {
            printf ("%s: RhI16 - Can't open the source file: %s\n", argP, ptrSrcFile) ;
            error = ERR_FILE ;
            break ;
        }
//        pcgrpId = GRP_16 ;

        for ( ii = 0 ; ii < 16 ; ++ii ) { /* no checksum */
            inVal = fgetc (srcFd) ;
            if (inVal == EOF) error = ERR_FMT ;
            if (error != ERR_OK) break ;
            tmpS[ii] = (uint) inVal;

            if (( ii == 0  && inVal != 0xFF ) ||
                ( ii == 1  && inVal != 0x10 ) ||
                ((ii == 2  || ii == 3 || ii == 14) && inVal != 0x00 ) ||
                ( ii == 15 && inVal != 0x0F ) ||
                ( ii == 4  && inVal != 0x10 && inVal != 0x21 ) ) {

                printf("\n%s: Unexpected byte %i in I16 file header, position %i\n", argP, inVal, ii + 1 ) ;
                /* unknown params, PC-1600 Tech. Ref. chap 3.3.1 */
            }
        }
        if (error != ERR_OK) break ;

        if (*ptrType == TYPE_NOK) {
                if ( tmpS[4] == 0x10 )
                    *ptrType = TYPE_BIN ;
                else
                    *ptrType = TYPE_IMG ;  /* 0x21 */
        }

        *ptrAddr   = tmpS[10] ;
        *ptrAddr   = (*ptrAddr << 8) + tmpS[9] ;
        *ptrAddr   = (*ptrAddr << 8) + tmpS[8] ;

        *ptrEaddr   = tmpS[13] ;
        *ptrEaddr   = (*ptrEaddr << 8) + tmpS[12] ;
        *ptrEaddr   = (*ptrEaddr << 8) + tmpS[11] ;

        /* length will  calculated new from real length of following image (+ End mark?) */
        length = tmpS[7] ;
        length = (length << 8) + tmpS[6] ;
        length = (length << 8) + tmpS[5] ;

        /* Get the length of the ST-Header */
        position = ftell (srcFd) ;
        if (position < ERR_OK) {
            printf ("%s: RhI16p - Can't ftell the file\n", argP) ;
            error = ERR_FILE ;
            break ;
        }
        else {
            STc = position ; /* I16 header length */

            /* Seek to the end of the source file */
            error = fseek (srcFd, 0, SEEK_END) ;
            if (error != ERR_OK) {
                printf ("%s: RhI16e - Can't seek the file\n", argP) ;
                error = ERR_FILE ;
                break ;
            }
            /* Get the length of the source file */
            nbByte = ftell (srcFd) ;
            if (nbByte == ERR_NOK) {
                printf ("%s: RhI16e - Can't ftell the file\n", argP) ;
                error = ERR_FILE ;
                break ;
            }
            error = fseek (srcFd, position, SEEK_SET) ;
            if (error != ERR_OK) {
                printf ("%s: RhI16p - Can't seek the file\n", argP) ;
                error = ERR_FILE ;
                break ;
            }
            /* End marks not included in ST image */
            if ( length > (ulong) (nbByte - position +( *ptrType == TYPE_IMG ? 1 : 0))) { // ToDo check +1
                    printf("\n%s: Length %lu in the header would expect a longer I16 file. Check if this file is complete.\n", argP, length) ;
            }
            error = ERR_OK ;
        }

    } while (0) ;
    error_tmp = error ;

    /* Close the source file */
    if (srcFd != NULL) {
        error = fclose (srcFd) ;
        if (error != ERR_OK) {
            printf ("%s: RhI16 - Can't close the source file\n", argP) ;
            error_tmp = ERR_FILE ;
        }
    }
    error = error_tmp ;
    return (error);
}

/*Read Header data from ST-File,  sets STc and pcgrpId also */
int ReadHeadFromST (char*  ptrSrcFile,
                     uchar* ptrType,
                    ushort* ptrFlags,
                     ulong* ptrAddr,
                     ulong* ptrEaddr,
                     char*  ptrName )
{
        FILE  *srcFd ;
         int  inVal, ii ;
       ulong  checksum = 0, length ;
       uchar  tmpS[SUPT_HEAD_L] ;
        long  position, nbByte ;
         int  error_tmp, error = ERR_OK ;

    do {
        /* 1. Open the source file */
        srcFd = fopen (ptrSrcFile, "rb") ;
        if (srcFd == NULL) {
            printf ("%s: RhST - Can't open the source file: %s\n", argP, ptrSrcFile) ;
            error = ERR_FILE ;
            break ;
        }
        pcgrpId = IDENT_ST ;

        for ( ii = 0 ; ii < 16 ; ++ii ) {

            inVal = fgetc (srcFd) ;
            if (inVal == EOF) error = ERR_FMT ;
            if (error != ERR_OK ) break ;

            tmpS[ii] = (uint) inVal ;
            CheckSumE (tmpS[ii], &checksum) ;
        }
        if ( error != ERR_OK ) break;

        if (strlen(ptrName)==0) for ( ii = 0 ; ii < 16 ; ++ii ) ptrName[ii] = tmpS[ii] ;

        for ( ii = 16 ; ii < SUPT_HEAD_L ; ++ii ) { /* low byte of checksum included*/
            inVal = fgetc (srcFd) ;
            if (inVal == EOF) error = ERR_FMT ;
            if (error != ERR_OK) break ;
            tmpS[ii] = (uint) inVal;
            if (ii < SUPT_HEAD_L-1) CheckSumE (tmpS[ii], &checksum) ;

            if ( ii >22 && ii < 25 && inVal != 0x00 ) {
                printf("\n%s: Unexpected byte %i in ST file name header, position %i\n", argP, inVal, ii + 1 ) ;
                /* entry addr or other unknown params  */
            }
        }
        if (error != ERR_OK) break ;
        if ((uchar) checksum != tmpS[25]) printf("\n%s: Checksum (%02X != %02X) error in the header of the ST file\n", argP, tmpS[25], (uchar) checksum) ;

        *ptrFlags = tmpS[16] ;
        if (*ptrType == TYPE_NOK) *ptrType = TYPE_IMG ;

        *ptrAddr   = tmpS[18] ;
        *ptrAddr   = (*ptrAddr << 8) + tmpS[17] ;

        *ptrEaddr   = tmpS[22] ; /* not specified by SuperTape original definition */
        *ptrEaddr   = (*ptrEaddr << 8) + tmpS[21] ;

        /* length will  calculated new from real length of following image + End mark */
        length = tmpS[20] ;
        length = (length << 8) + tmpS[19] ;

        /* Get the length of the ST-Header */
        position = ftell (srcFd) ;
        if (position < ERR_OK) {
            printf ("%s: RhSTp - Can't ftell the file\n", argP) ;
            error = ERR_FILE ;
            break ;
        }
        else {
            STc = position ; /* ST header length */

            /* Seek to the end of the source file */
            error = fseek (srcFd, 0, SEEK_END) ;
            if (error != ERR_OK) {
                printf ("%s: RhSTe - Can't seek the file\n", argP) ;
                error = ERR_FILE ;
                break ;
            }
            /* Get the length of the source file */
            nbByte = ftell (srcFd) ;
            if (nbByte == ERR_NOK) {
                printf ("%s: RhSTe - Can't ftell the file\n", argP) ;
                error = ERR_FILE ;
                break ;
            }
            error = fseek (srcFd, position, SEEK_SET) ;
            if (error != ERR_OK) {
                printf ("%s: RhSTp - Can't seek the file\n", argP) ;
                error = ERR_FILE ;
                break ;
            }
            /* End marks not included in ST image */
            if ( length > (ulong) (nbByte - position + 1)) {
                    printf("\n%s: Length %lu in the header would expect a longer ST file. Check if this file is complete.\n", argP, length) ;
            }
            error = ERR_OK ;
        }

    } while (0) ;
    error_tmp = error ;

    /* Close the source file */
    if (srcFd != NULL) {
        error = fclose (srcFd) ;
        if (error != ERR_OK) {
            printf ("%s: RhST - Can't close the source file\n", argP) ;
            error_tmp = ERR_FILE ;
        }
    }
    error = error_tmp ;
    return (error);
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

/*Read Header data from CFG-File */
int ReadParametersFromCfg (char*  ptrCfgFile,
                           char*  ptrPcName,
                           uint*  ptrPCcnt,
                          uchar*  ptrType,
                           uint*  ptrTcnt,
                           char*  ptrName,
                         ushort*  ptrFlags,
                           char*  ptrAddr,
                           char*  ptrEaddr,
                           uint*  ptrAcnt,
                           char*  ptrCspeed,
                           uint*  ptrCcnt,
                           uint*  ptrEcnt)
{
        char  line_buffer[cLL] = "", val_buffer[cLL]  = "", tmpC[cLL]  = "",
              *ptrErr, *ptrToken,
              entryAddrS[cLPF] ;

        bool  hex2bin = false; /* redirected standard output of hex2bin */
        uint  line_cnt = 0, line_cntN = 0, cfAcnt = 0 ;
       ulong  flags, addr, addrOpt ; // eaddr, length
       ulong  basefreq = 0, realfreq = 0 ; // global: pcId
      double  cfspeed ;
        FILE  *cfgFd = NULL ;
         int  error_tmp, error = ERR_OK ;

        /* Open the Cfg-file */
        cfgFd = fopen (ptrCfgFile, "rb") ;
        if (cfgFd == NULL) {
            printf ("%s: RpCfg - Can't open the configuration file: %s\n", argP, ptrCfgFile) ;
            return (ERR_FILE) ;
        }

    while ( getlineF( line_buffer, cLL, cfgFd, &line_cnt, &line_cntN ) != NULL ) {

        if ( strlen(line_buffer) < 3) continue ;
        if (!strncmp(line_buffer, "hex2bin", 7)) {
            hex2bin = true;
            continue ;
        }
        if ((line_buffer[0] == '\'' || line_buffer[0] == ';')) continue ; // && line_buffer[1] != '='

        if (line_cnt >= cLL ) {
            printf ("\n%s: To much (%i ) lines reached in file: %s\n", argP, line_cnt, ptrCfgFile) ;
            error = ERR_MEM ;
            break ;
        }
        ptrToken = strchr (&line_buffer[1], '=') ;
        if (ptrToken == NULL && hex2bin) ptrToken = strchr (&line_buffer[1], ':') ;
        if (ptrToken != NULL) {
            *ptrToken = '\0' ;
            ptrToken++ ;

            strncpy (val_buffer, ptrToken, cLL-1) ;
            strlor (line_buffer) ;

            if (strcmp (line_buffer, "name") == 0) {
                // if (strlen(ptrName)==0)
                    strncpy (ptrName, val_buffer, cLPF-1) ;
            }
            else if (strcmp (line_buffer, "pc") == 0) {
                if (strlen(ptrPcName)==0) strncpy (ptrPcName, val_buffer, cLPF-1) ;
                *ptrPCcnt |=1 ;
            }
            else if (strcmp (line_buffer, "pcid") == 0) { /* If the exact PC is not specified,
                then the number of a compatible PC of the group according to wav format is used.*/
                if (*ptrPCcnt == 0) {
                    /* convert pcid from string to binary */
                    pcId = strtoul( val_buffer, &ptrErr, 0) ;
                    if (*ptrErr != 0) {
                        printf ("%s: PC Id %s is not a valid number in line %i of %s.\n", argP, ptrToken, line_cnt, ptrCfgFile) ;
                        error = ERR_FMT ;
                        break ;
                    }
                }
            }
            else if (strcmp (line_buffer, "basefreq") == 0) {
                if (*ptrCcnt == 0) {
                    basefreq = strtoul( val_buffer, &ptrErr, 0) ;
                    if (*ptrErr != 0) {
                        printf ("%s: Base frequency %s is not valid in line %i of %s.\n", argP, ptrToken, line_cnt, ptrCfgFile) ;
                        error = ERR_FMT ;
                        break ;
                    }
                }
            }
            else if (strcmp (line_buffer, "realfreq") == 0) {
                if (*ptrCcnt == 0) {
                    realfreq = strtoul( val_buffer, &ptrErr, 0) ;
                    if (*ptrErr != 0) {
                        printf ("%s: Real frequency %s is not valid in line %i of %s.\n", argP, ptrToken, line_cnt, ptrCfgFile) ;
                        error = ERR_FMT ;
                        break ;
                    }
                }
            }
            else if (strcmp (line_buffer, "type") == 0) {
                if (*ptrTcnt == 0 || *ptrType == TYPE_NOK ) {
                    strlor (val_buffer) ;
                    if      (strcmp (val_buffer, "img") == 0) *ptrType = TYPE_IMG ;
                    else if (strcmp (val_buffer, "bin") == 0) *ptrType = TYPE_BIN ;
                    else if (strcmp (val_buffer, "dat") == 0) *ptrType = TYPE_DAT ;
                    else if (strcmp (val_buffer, "rsv") == 0) *ptrType = TYPE_RSV ;
                    else if (strcmp (val_buffer, "asc") == 0) *ptrType = TYPE_ASC ;
                    else if (strcmp (val_buffer, "bas") == 0) *ptrType = TYPE_BAS ;
                    else if (strcmp (val_buffer, "txt") == 0) *ptrType = TYPE_TXT ;
                    else if (strcmp (val_buffer, "def") == 0) *ptrType = TYPE_DEF ;
                    else if (strcmp (val_buffer, "dim") == 0) *ptrType = TYPE_DIM ;
                    else if (strcmp (val_buffer, "mem") == 0) *ptrType = TYPE_MEM ;
                    else if (strcmp (val_buffer, "crd") == 0) *ptrType = TYPE_CRD ;
                    else if (strcmp (val_buffer, "tel") == 0) *ptrType = TYPE_TEL ;
                    else if (strcmp (val_buffer, "scd") == 0) *ptrType = TYPE_SCD ;
                    else if (strcmp (val_buffer, "not") == 0) *ptrType = TYPE_NOT ;
                    else if (strcmp (val_buffer, "capx") == 0 || strcmp (val_buffer, "casl") == 0  ||
                             strcmp (val_buffer, "c" ) == 0 || strncmp (val_buffer, "asm", 3) == 0)
                            {*ptrType = TYPE_TXT ; type_asm = true ;}
                    else {
                        printf ("%s: Type %s is not valid in line %i of %s.\n", argP, ptrToken, line_cnt, ptrCfgFile) ;
                        error = ERR_FMT ;
                        break ;
                    }
                    *ptrTcnt |=1 ;
                }
            }
            else if ( hex2bin && strstr (line_buffer, "lowest address")!= NULL) {
                strupr (val_buffer) ;
                ptrToken = strpbrk(val_buffer, "0123456789ABCDEF") ;
                if (ptrToken == NULL) {
                    printf ("%s: Missing 'Lowest address' value in line %i of %s.\n", argP, line_cnt, ptrCfgFile) ;
                    error = ERR_FMT ;
                    break ;
                }
                else {
                    strcpy  (tmpC, "0x") ;
                    strncat (tmpC, ptrToken, cLL-3) ;
                    addr = strtoul( tmpC, &ptrErr, 0) ;
                    if (*ptrErr != 0) {
                        printf ("%s: Lowest address 0x%s is not valid in line %i of %s.\n", argP, ptrToken, line_cnt, ptrCfgFile) ;
                        error = ERR_FMT ;
                        break ;
                    }
                    else {
                        if (*ptrAcnt == 0) strncpy (ptrAddr, tmpC, cLPF-1) ;
                        cfAcnt|=1;
                    }
                }
            }
            else if (strcmp (line_buffer, "startaddr") == 0 ||
                     (strcmp (line_buffer, "addr") == 0 && cfAcnt == 0 )) {
                    /* convert address from string to binary */
                    addr = strtoul( val_buffer, &ptrErr, 0) ;
                    if (*ptrErr != 0) {
                        printf ("%s: Start address %s is not valid in line %i of %s.\n", argP, ptrToken, line_cnt, ptrCfgFile) ;
                        error = ERR_FMT ;
                        break ;
                    }
                    else {
                        if (*ptrAcnt == 0) strncpy (ptrAddr, val_buffer, cLPF-1) ;
                        cfAcnt|=1;
                    }
            }
            else if ( strcmp (line_buffer, "entryaddr") == 0 ||
                     (strcmp (line_buffer, "addr") == 0 && cfAcnt > 0 )) {
                if (*ptrAcnt < 2) {
                    (void) strtoul( val_buffer, &ptrErr, 0) ;
                    if (*ptrErr != 0) {
                        printf ("%s: Entry address %s is not valid in line %i of %s.\n", argP, ptrToken, line_cnt, ptrCfgFile) ;
                        error = ERR_FMT ;
                        break ;
                    }
                    else {
                        strncpy (entryAddrS, val_buffer, cLPF-1) ;
                        cfAcnt|=2;
                    }
                }
            }
            else if (strcmp (line_buffer, "headerflags") == 0) {
                flags = strtoul( val_buffer, &ptrErr, 0) ;
                if (*ptrErr != 0) {
                    printf ("%s: Flag byte %s is not valid in line %i of %s.\n", argP, ptrToken, line_cnt, ptrCfgFile) ;
                    error = ERR_FMT ;
                    break ;
                }
                else {
                    *ptrFlags = flags;
                }
            }
            else if (strcmp (line_buffer, "endmark") == 0) { /* The value of the end mark to check
                                is automatically selected depending on the type of the source file. */
                if (*ptrEcnt == 0) *ptrEcnt |=1 ;
            }
        }
        else {
                if (hex2bin) ++wrn_cnt; else ++err_cnt;
                printf ("%s Missing '=' in file %s, line %i.\n", argP, ptrCfgFile, line_cnt) ;
        }
    }
    error_tmp = error ;

    /* Close the configuration file */
    if (cfgFd != NULL) {
        error = fclose (cfgFd) ;
        if (error != ERR_OK) {
            printf ("%s: RpCfg - Can't close the configuration file\n", argP) ;
            error_tmp = ERR_FILE ;
        }
    }
    error = error_tmp ;

    if (pcId > 0 && *ptrPCcnt == 0) {
        sprintf(ptrPcName, "%lu", pcId) ;
        *ptrPCcnt |= 1 ;
    }

    if( basefreq >0 && realfreq >0 && *ptrCcnt == 0) {
        cfspeed = (double) realfreq / basefreq ;
        if (cfspeed > 1.03 || cfspeed < 0.97) {
            sprintf(ptrCspeed, "%.3lf", cfspeed) ;
            *ptrCcnt |= 1 ;
        }
    }

    if (*ptrAcnt == 0 && cfAcnt == 3 ) {
        strncpy (ptrEaddr, entryAddrS, cLPF-1) ;
    }
    else if (*ptrAcnt == 1 && cfAcnt>1 ) {
        addrOpt = strtoul( ptrAddr, &ptrErr, 0) ;
        if (*ptrErr == 0 && addrOpt == addr) {
            strncpy (ptrEaddr, entryAddrS, cLPF-1) ;
            *ptrAcnt = 2 ;
        }
        else {
            printf ("%s: Warning: For file %s\nthe Entry address is ignored, because the start address is moved to %s \n", argP, ptrCfgFile, ptrAddr) ;
            cfAcnt=1 ;
        }
    }
    if (cfAcnt>2) cfAcnt=2 ;
    if (*ptrAcnt < cfAcnt) *ptrAcnt = cfAcnt ;

    return (error);
}


void PrintHelp (char* argH)  /* 1         2         3         4         5         6         7         8 */
{
  if (strcmp (argH, "l")==0 || strcmp (argH, "level")==0 || strcmp (argH, "debug")==0) {
                       /* 1         2         3         4         5         6         7         8 */
              /* 12345678901234567890123456789012345678901234567890123456789012345678901234567890 */
	printf ("-m, --parameters=ParametersFile : read parameter from file\n") ;
	printf ("-d, --device=TYPE : INV interface with inverting level converter (mirror)\n") ;
	printf ("-l, --level=VALUE : Option bits and Print debug traces\n") ;
	printf ("                    a hexadecimal integer (0x____) or sum of it\n") ;
	printf (" Waveform and frequency (default sample rate is 4* base frequency):\n") ;
	printf ("    1   Force triangle waveform for base frequency (old compact format)\n") ;
	printf ("    2   Force wav with 48 kHz (PC-1500: 44.1) near rectangle waveform\n") ;
	printf ("    3   Force wav with sample rate of 16 kHz (Emulator) or 72 kHz (SuperTape)\n\n") ;
	printf (" Convert Data variables between series:\n") ;
	printf (" 0x04   Convert PC-1500/1600 numeric data to other PC standard variable,\n") ;
	printf ("        otherwise to numeric array,\n") ;
	printf (" 0x08   Data for PC-1500/1600 of length 8 are numeric data from other PC\n") ;
	printf (" 0x10   Convert Strings between ASCII code and Old Basic Code\n\n") ;
	printf (" 0x1000 Use tape format of PC-1475 (slow) for E5-series CLOAD@ of old images\n") ;
	printf (" 0x4000 Write no file header, have to merge data blocks manually\n") ;
	printf (" 0x8000 Data variable block is from Wav2Bin 1.5 or version before\n") ;
	printf (" 0x800  Write also, if checksum bug will be activated (not readable)\n") ;
	printf (" 0x400  Write long synchronisation like the original, 0x200 like TRM\n\n") ;
	printf (" 0x80   Print some global infos more, for all bytes and (sums): 0xC0\n") ;
	printf (" 0x40   Print all bytes and (Sum_calculated) - see also Wav2bin\n") ; // DEBUG_TRACES
	printf (" 0x20   Position and byte list, for data only - more options see source code") ;
    /* Debug Bin2wav -l 0x20=Data only Pos/Byte 0x40=Byte 0x80=only some global Infos,
            SYNC_KHX_OFF = 0x10000 don't write spaces and sync bytes to khx file
            DATA_W2B150 =  0x8000 for older IMG-DAT-Files with some Checksum,
            NO_FILE_HEAD = 0x4000 for variable blocks
            NO_WAV_END  =  0x2000 Hard end, no shutdown of signal, no silence: Add your own end of file!
            BAS_EXT_FRMT = 0x1000 debug flag, use FORMAT of BAS_EXT for E-Series
            SYNCA_END  =   0x100  Add sync at the end of the wav file (act against faders)
            SYNCL_TRM  =   0x200  values like TRM for PC-16/G/E, or format as original khx hex
            SYNCL_STD  =   0x400  Use default sync and syncS like original,
            ERR_OFF    =   0x800  Ignore some errors
            0x4 PC-1234: convert PC-1500 numeric to PC-1234 standard variable, else to numeric array
            0x8 PC-1500: ItemLen 8 = numeric from PC-1234, else text l=8 from PC-1500
            0x10 Convert Strings between Old Basic Code and ASCII code
            BAS_EOF_INCL  = 0x200000 -e Ignore last byte of IMG, typically if BAS_EOF mark included
       Please also customize the debug variable before calling the ConvertBinToWav !
   */
  }
  else {
              /* 12345678901234567890123456789012345678901234567890123456789012345678901234567890 */
	printf ("\nUsage: %s [Options] SrcFile(.typ) [DstFile(.wav/tap)]\n", argP) ;
	printf ("SrcFile          : Binary image file (usually created by BAS2IMG or WAV2BIN)\n") ;
	printf ("DstFile          : WAV file (default: SrcFile.wav) or tap file\n") ;
//	printf ("Options:\n") ;
	printf ("-t, --type=TYPE   : Source file type\n") ;  /* type=VAR is as dat without file name */
	printf ("                     img  BASIC-program binary image (default) txt Text modus\n") ;   /* c, asm# */
	printf ("                     bin  Binary assembly program or data   st,shc Transfile PC\n") ; /* i16 */
	printf ("                     dat  Data variable blocks (binary data)   asc ASCII Data\n") ;
	printf ("                     rsv  ReSerVe data (binary image)          bas ASCII Source\n") ;
	printf ("-p, --pc=NUMBER   : Sharp pocket computer, currently available 1211, 1245, 1251\n") ;
	printf ("                     1261, 1350, 1360, 1401, 1403, 1421, 1450, 1460, 1475, 1600\n") ;
	printf ("                     E500, E220, G850, 1500QT, SuperTape and more, default:1500\n") ;
	printf ("-c, --cspeed=VALUE: Ratio of CPU frequency to original (use it with a modified\n") ;
	printf ("                     Pocket Computer with speedup switched on, 0.2 to 2.7)\n") ;
	printf ("-a, --addr=VALUE  : 1. Start address, needed for BIN type, 2. Entry address\n") ;
	printf ("                     0 to 65535 or 0xFFFF, E500:0xFFFFFF (dflt: Manual. 2. no)\n") ;
	printf ("-s, --sync=VALUE  : Synchronisation duration, expressed in seconds, 2. Space\n") ;
	printf ("                     0.5 to 9 (default: 0.5 or minimum for the PC and waveform)\n") ;
	printf ("-nNAME, --name=   : Sharp file name (7 characters max, 16 for the PC-1500, E:8)\n") ;
	printf ("                     (default: DstFile without extension, nor path)  Subst:[HH]\n") ;
	printf ("-q, --quiet       : Quiet mode (minimal display output)\n") ;
	printf ("    --tap --khx   : Destination: Emulator tap byte / khx hex format (not wav)\n") ;
	printf ("    --version     : Display version information  -e, --endmark : end mark incl.\n") ;
	printf ("    --help        : Display this information,  --help=l : show option screen\n") ;
    printf ("-l, --level=VALUE : Print debug traces, more options, see help option screen") ;
  }
  #ifdef __APPLE__
    /* Mac specific here, not for _WIN32 */
    printf ("\n") ;
  #endif
  #ifdef __linux__
    /* For Linux shell */
    printf ("\n") ;
  #endif
  exit( EXIT_SUCCESS ); /* no arguments were passed */
}


/*  Copying conditions: GNU Lesser General Public License version (GPLv3), see COPYING.LESSER and this supplement:
    You may not use any code from the "Pocket Tools for SHARP Pocket Computers" project if you do not name
    the original authors in the code and documentation or if you remove this notice or the following function. */
void PrintVersion (void) /* global Qcnt */
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
	exit( EXIT_SUCCESS ); /* no arguments were passed */
}


void MoreInfo (int error)
{	printf("%s: '%s --help' gives you more information or the manual in detail.\n", argP, argP);
	exit( error ); /* no arguments were passed */
}


int main ( int argc, char **argv )  /* (int argc, char* argv[]) */
{	/* 0=SrcFile 1=[DstFile] 2=[-t] 3=[-p] 4=[-d] 5=[-c] 6=[-a](start) 7=[-a](entry) 8=[-s] 9=[-s]space 10=[-n] 11=[-h] 12=[-l] 13=[-l|] 14=[-m] 15=[-y] 16=[-w] */
	  char  argD[17][cLPF] = { "", "", "img", "", "std", "1.00", "0x000000", "0xFFFFFF", "0.5", "2.125", "", "", DEBUG_ARG, "0", "", "1.6", "0" } ;
	  char  argS[cLPF] = "", *ptrToken, *ptrErr = 0, tmp ,
            spec_str[]= "[FF]", spec_chr[]= "\xFF";
	  uint  ii, jj, tmpl ;                                                    // to global: Qcnt, TAPc, Scnt, Acnt, Mcnt
	  uint  FILEcnt = 0, Tcnt = 0, PCcnt = 0, Dcnt = 0, Ccnt = 0, Ncnt = 0, Hcnt = 0, Ecnt = 0, Lcnt = 0, Kcnt = 0, Ocnt = 0, Wcnt = 0 ;
	 uchar  type ;
    ushort  grpId = pcgrpId ;                   // to global: pcId, pcgrpId
    ushort  flags = 0 ;                         /* SuperTape or Quick-Tape flag byte */
	 ulong  addr = 0, eaddr = 0, debug = 0,
	        waveform = 0 ;                      /* waveform 1-3: changes sample frequency, waveform 4-5: older forms for std. freq.*/
    double  sync, syncS ;                       /* length of synchronisation signals */
    double  khx_ver ;
	   int  option_index, i, j, k, l, error = ERR_OK, c = 0, len ;
static int  longval ;
      bool  new_arg = false, old_arg = false ; // to global: cnvstr_upr = false, type_asm = false

 const int  Token_Nb = 5 ;
     char*  oldToken[] = { "PC:", "T:", "A:", "S:", "N:" } ; /* TOKEN_NB */
     char*  newToken[] = { "-p" , "-t", "-a", "-s", "-n" } ; /* strlen 2 only */

        struct option long_options[] =
	{                                                   /* free options: f for frequency, b,g,j,z */
		{"type",    required_argument, 0,        't'},
		{"pc",	    required_argument, 0,        'p'},
		{"device",	optional_argument, 0,        'd'}, /*option device needed, for inverting interfaces*/
		{"cspeed",	required_argument, 0,        'c'},
		{"addr",    required_argument, 0,        'a'},
		{"sync",    required_argument, 0,        's'},
		{"name",    optional_argument, 0,        'n'}, /* spaces as delimiter not allowed with opt_arg */
		{"khx",     optional_argument, 0,        'y'},
		{"tap",     no_argument,       0,        'r'},
		{"quiet",   no_argument,       0,        'q'},
		{"endmark", no_argument,       0,        'e'},
        {"level",   required_argument, 0,        'l'},
        {"parameters",optional_argument, 0,      'm'}, /* read header parameters from file */
        {"keywords",required_argument, 0,        'k'}, /* keyword file (not used here) */
        {"codepoints",required_argument, 0,      'o'}, /* code space file (not used) */
        {"waveform", required_argument, 0,       'w'},
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
        ptrToken = strstr (argS, "PC:") ; /* PC: */
        if (ptrToken == argS) {
                old_arg = true ;
                break ;
        }
        if ( strcmp(argS, "T:IMG") == 0 ) old_arg = true ;
        if ( strcmp(argS, "T:BIN") == 0 ) old_arg = true ;
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

    do
    {
        while (1) {

            /* getopt_long stores the option index here. */
            option_index = 0;

            c = getopt_long (argc, argv, "t:p:d::c:a:s:n::y::rqel:m::k:o:w:vh::", long_options, &option_index);

            /* Detect the end of the options. */
            if (c == -1) break;

            switch (c)
            {
            case 't': strncpy( argD[2], optarg, cLPF-1); ++Tcnt; break;
            case 'p': strncpy( argD[3], optarg, cLPF-1); ++PCcnt; break;
            case 'd': { if ( optarg != 0 ) strncpy( argD[4], optarg, cLPF-1);
                    ++Dcnt; break; }
            case 'c': strncpy( argD[5], optarg, cLPF-1); ++Ccnt; break;
            case 'a': { if (Acnt < 2) strncpy( argD[6+Acnt], optarg, cLPF-1);
                    ++Acnt; break; }
            case 's': { if (Scnt < 2) strncpy( argD[8+Scnt], optarg, cLPF-1);
                    ++Scnt; break; }
            case 'n': { if ( optarg != 0 ) strncpy( argD[10], optarg, cLPF-1);
                    ++Ncnt; break; }
            case 'y': { if ( optarg != 0 ) strncpy( argD[15], optarg, cLPF-1);
                    ++KHXc; break; }
            case 'r': ++TAPc; break;
            case 'q': ++Qcnt; break;
            case 'e': ++Ecnt; break;
            case 'l': { if (Lcnt < 2) strncpy( argD[12+Lcnt], optarg, cLPF-1);
                    ++Lcnt; break; }
            case 'm': { if ( optarg != 0 ) strncpy( argD[14], optarg, cLPF-1);
                        ++Mcnt; break; }
            case 'k': { ++Kcnt; break; } /* Unused parameters, only for */
            case 'o': { ++Ocnt; break; } /* compatibility with the other tools */
            case 'w': strncpy( argD[16], optarg, cLPF-1); ++Wcnt; break;
            case 0:
                switch (longval) {
                case 'v': PrintVersion (); break;
                case 'h': { if ( optarg != 0 ) strncpy( argD[11], optarg, cLPF-1);
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

        if ((FILEcnt > 2) || (Tcnt > 1) || (PCcnt > 1) || (Dcnt > 1) || (Ccnt > 1) || (Kcnt > 3) || (Ocnt > 2) ||
               (Acnt > 2) || (Scnt > 2) || (Ncnt > 1)  || (Lcnt > 2) || (Mcnt > 1) || (Wcnt > 1) || (Hcnt > 1)) {
                printf("%s: [E] Too many arguments of same type for '%s'\n", argP, argP);
                MoreInfo (ERR_SYNT);
        }
        else if ((KHXc > 1)  || (TAPc > 1) || (Qcnt > 1) || (Ecnt > 1)) {
                printf("%s: [W] Too many arguments of same type for '%s'\n", argP, argP);
        }
        if ( Hcnt == 1 ) {
            (void) strlor (argD[11]) ;
            PrintHelp (argD[11]) ;
            break;
        }

        if (FILEcnt < 1) { printf("%s: Missing file name(s) after '%s'\n", argP, argP); MoreInfo (ERR_SYNT); }

        if (FILEcnt == 2){
            ptrToken = strrchr (argD[1], '.') ;
            if (ptrToken != NULL) {
                strncpy (argS, ptrToken, cLPF -1) ;
                strlor(argS) ;
                if (strcmp (argS, ".khx") == 0) {
                    if (KHXc==0 && Qcnt==0) printf("%s: Switched output format from wav to --khx implicitly\n", argP);
                    KHXc |= 1;
                }
                else if (strcmp (argS, ".tap") == 0) {
                    if (TAPc==0 && Qcnt==0) printf("%s: Switched output format from wav to --tap implicitly\n", argP);
                    TAPc |= 1;
                }
            }
        }
        ptrToken = strrchr (argD[0], '.') ;
        if (FILEcnt == 1) {
            if (ptrToken != NULL) strncat (argD[1], argD[0], strrchr (argD[0], '.') - argD[0] ); /* GetSrcFile */
            else strncpy (argD[1], argD[0], cLPF -1) ;
            len = cLPF - 1 - strlen(argD[1]);
            if (len > 3) {
                if (KHXc > 0) strncat (argD[1], ".khx", len );
                else if (TAPc > 0) strncat (argD[1], ".tap", len );
                else strncat (argD[1], ".wav", len );  /* DstFile=SrcFile.wav */
            }
        }
        if (ptrToken != NULL) {
            (void) strncpy (argS, ptrToken + 1, cLPF -1) ;
            (void) strupr (argS) ;
        }
        else strcpy (argS, "");

        if (Mcnt > 0) {
            if (argD[14][0] == '\0') {
                if (ptrToken != NULL) strncpy (argD[14], argD[0], strrchr (argD[0], '.') - argD[0] ); /* GetDstFile */
                else strncpy (argD[14], argD[0], cLPF -1) ;
                ptrToken = NULL ;
            }
            else {
                ptrToken = strrchr (argD[14], '.') ;
            }
            if (ptrToken == NULL) {
                len = cLPF - 1 - strlen(argD[14]);
                strncat (argD[14], ".CFG", len );
            }
        }

        (void) strupr (argD[2]) ;
        type = TYPE_NOK ;

        if (Tcnt > 0) {

            if      (strcmp (argD[2], "IMG") == 0) type = TYPE_IMG ;
            else if (strcmp (argD[2], "TXT") == 0) type = TYPE_TXT ;
            else if (strcmp (argD[2], "C"  ) == 0 || strncmp (argD[2], "ASM", 3) == 0 ||
                     strcmp (argD[2], "CAPX")== 0 || strcmp  (argD[2], "CASL")== 0     )
                                                {  type = TYPE_TXT; type_asm = true; } /* also asm4, asm5, asm6, asm8 */
            else if (strcmp (argD[2], "ASC") == 0) type = TYPE_ASC ;
            else if (strcmp (argD[2], "BAS") == 0) type = TYPE_BAS ; /* source, not image */
            else if (strcmp (argD[2], "RSV") == 0) type = TYPE_RSV ;
            else if (strcmp (argD[2], "DEF") == 0) type = TYPE_DEF ;
            else if (strcmp (argD[2], "BIN") == 0) type = TYPE_BIN ; /* binary code, but no BASIC image */
            else if (strcmp (argD[2], "DAT") == 0) type = TYPE_DAT ;
            else if (strcmp (argD[2], "DIM") == 0) type = TYPE_DIM ;
            else if (strcmp (argD[2], "MEM") == 0) type = TYPE_MEM ;
            else if (strcmp (argD[2], "CRD") == 0) type = TYPE_CRD ;
            else if (strcmp (argD[2], "TEL") == 0) type = TYPE_TEL ;
            else if (strcmp (argD[2], "SCD") == 0) type = TYPE_SCD ;
            else if (strcmp (argD[2], "NOT") == 0) type = TYPE_NOT ;

            else if (strcmp (argD[2], "VAR") == 0) /* Variable DATA BLOCK without file type and -name */
                type = TYPE_VAR ;

            else if (strcmp (argD[2], "I16") == 0) { /* Read from PC-1600 binary image format with File header included */
                error = ReadHeadFromI16 (argD[0], &type, &addr, &eaddr ); /* sets global STc */
                if (error != ERR_OK) break ;
            }

        }
        if ((Tcnt >  0 && strcmp (argD[2], "SHC") == 0) ||
            (Tcnt == 0 && strcmp (argS, "SHC") == 0)     ) { /* Read from SHC binary image format, header included */
                error = ReadHeadFromShc (argD[0], &type, &addr, argD[10] ); /* sets global SHCc, SHCe, pcgrpId also */
                if (error != ERR_OK) break ;
        }
        if ((Tcnt >  0 && strcmp (argD[2], "ST") == 0) ||
            (Tcnt == 0 && strcmp (argS, "ST") == 0)     ) { /* Read from ST binary image format, SuperTape header included */
                error = ReadHeadFromST (argD[0], &type, &flags, &addr, &eaddr, argD[10] ); /* sets global STc, pcgrpId also */
                if (error != ERR_OK) break ;
        }
        if (Mcnt > 0) {
                error = ReadParametersFromCfg (argD[14], argD[3], &PCcnt, &type, &Tcnt, argD[10],
                                               &flags, argD[6], argD[7], &Acnt, argD[5], &Ccnt, &Ecnt );
                if (error != ERR_OK) break ;
        }
        if (Tcnt == 0 && type == TYPE_NOK) {  /*No parameter was specified explicitly or through a parameter file.*/
            if (strcmp (argS, "ASC") == 0) type = TYPE_ASC ;
            else if (strcmp (argS, "BAS") == 0) type = TYPE_BAS ;
            else if (strcmp (argS, "RSV") == 0) type = TYPE_RSV ;
            else if (strcmp (argS, "BIN") == 0) type = TYPE_BIN ;
            else if (strcmp (argS, "DAT") == 0) type = TYPE_DAT ;
            if (type != TYPE_NOK) { /* implicit changed the file type */
                if (Qcnt == 0)
                    printf ("%s: Source file type=%s is changed to --type=%s due to file extension.\n", argP, argD[2], argS) ;
                if (type == TYPE_BIN) printf (" Note: The file extension %s should NOT be used for BASIC-IMaGes.\n", argS) ;
                (void) strncpy (argD[2], argS, cLPF -1) ;
            }
            else if (strcmp (argD[2], "IMG") == 0) type = TYPE_IMG ; /* default argument*/
        }
        if (type == TYPE_NOK) {
            printf ("%s: Source file type %s is not valid\n", argP, argD[2]) ;
            MoreInfo (ERR_SYNT);
            break ;
        }

        /* Convert debug in a long */
        debug = (ulong) strtol (argD[12], &ptrErr, 0) ;
        if (*ptrErr != 0) {
            debug = 0 ;
            printf ("%s: Convert debug level number from '%s' is not valid\n", argP, argD[12]) ;
            MoreInfo (ERR_ARG);
        }
        debug = debug | (ulong) strtol (argD[13], &ptrErr, 0) ;
        if (*ptrErr != 0) {
            debug = 0 ;
            printf ("%s: Convert debug level number2 from '%s' is not valid\n", argP, argD[13]) ;
            MoreInfo (ERR_ARG);
        }
        if ((Kcnt > 0 || Ocnt > 0) && Qcnt == 0 && (debug & DEBUG_TRACES) > 0)
            printf ("%s ignores Keywords and cOdepoints options.\n", argP) ;
        if (Ecnt > 0) debug |= BAS_EOF_INCL ;

        i = 3 ;
        /* Compare the PC Ident to the allowed tokens */
        if (strlen (argD[i]) == 0) {
            pcId = 1500 ;      /* default pcId */
        }
        else {
            strupr (argD[i]) ;
            if (strlen(argD[i])>2 &&
                strcmp(&argD[i][strlen(argD[i])-3], "JAP")==0) argD[i][strlen(argD[i])-2]='\0'; /* Naming in PockEmul */
            else if (strlen(argD[i])>1 &&
                strcmp(&argD[i][strlen(argD[i])-2], "K2")==0)  argD[i][strlen(argD[i])-1]='\0'; /* E500K2, 2nd character area */
/*                 if (strcmp (argD[i], "1100")   == 0) strcpy (argD[i],  "1245") ;
          else */if (strcmp (argD[i], "PA-500") == 0) strcpy (argD[i],  "1100") ;
            else if (strcmp (argD[i], "EL-6300")== 0) strcpy (argD[i],  "1100") ;
            else if (strcmp (argD[i], "6300")   == 0) strcpy (argD[i],  "1100") ;
            else if (strcmp (argD[i], "1110")   == 0) strcpy (argD[i],  "1245") ;
            else if (strcmp (argD[i], "1140")   == 0) strcpy (argD[i],  "1150") ;
            else if (strcmp (argD[i], "1210")   == 0) strcpy (argD[i],  "1211") ;
            else if (strcmp (argD[i], "1210H")  == 0) strcpy (argD[i],  "1211") ;
            else if (strcmp (argD[i], "1212")   == 0) strcpy (argD[i],  "1211") ;
            else if (strcmp (argD[i], "1246S")  == 0) strcpy (argD[i],  "1246") ;
            else if (strcmp (argD[i], "1246")   == 0 && type == TYPE_MEM)
                                                      strcpy (argD[i],  "1146") ;
            else if (strcmp (argD[i], "1246DB") == 0) strcpy (argD[i],  "1146") ;
            else if (strcmp (argD[i], "1248")   == 0 && type == TYPE_MEM)
                                                      strcpy (argD[i],  "1148") ;
            else if (strcmp (argD[i], "1248DB") == 0) strcpy (argD[i],  "1148") ;
            else if (strcmp (argD[i], "D200")   == 0) strcpy (argD[i],  "1248") ;
            else if (strcmp (argD[i], "LAMBDA2")== 0) strcpy (argD[i],  "1150") ;
            else if (strcmp (argD[i], "LAMBDA10")== 0) strcpy (argD[i], "1150") ;
            else if (strcmp (argD[i], "RAMUDA10")== 0) strcpy (argD[i], "1150") ;
            else if (strcmp (argD[i], "1250A")  == 0) strcpy (argD[i],  "1250") ;
            else if (strcmp (argD[i], "1251H")  == 0) strcpy (argD[i],  "1251") ;
            else if (strcmp (argD[i], "1252H")  == 0) strcpy (argD[i],  "1251") ;
            else if (strcmp (argD[i], "1252")   == 0) strcpy (argD[i],  "1251") ;
            else if (strcmp (argD[i], "1253H")  == 0) strcpy (argD[i],  "1251") ;
            else if (strcmp (argD[i], "1253")   == 0) strcpy (argD[i],  "1251") ;
            else if (strcmp (argD[i], "1270")   == 0) strcpy (argD[i],  "1248") ;
            else if (strcmp (argD[i], "1260H")  == 0) strcpy (argD[i],  "1260") ;
            else if (strcmp (argD[i], "1260J")  == 0) strcpy (argD[i],  "1260") ;
            else if (strcmp (argD[i], "1261J")  == 0) strcpy (argD[i],  "1261") ;
            else if (strcmp (argD[i], "1262J")  == 0) strcpy (argD[i],  "1262") ;
            else if (strcmp (argD[i], "1280J")  == 0) strcpy (argD[i],  "1280") ;
            else if (strcmp (argD[i], "1285")   == 0) strcpy (argD[i],  "1280") ;
            else if (strcmp (argD[i], "1285J")  == 0) strcpy (argD[i],  "1280") ;
            else if (strcmp (argD[i], "1350J")  == 0) strcpy (argD[i],  "1350") ;
            else if (strcmp (argD[i], "1360J")  == 0) strcpy (argD[i],  "1360") ;
            else if (strcmp (argD[i], "1360K")  == 0) strcpy (argD[i],  "1360") ;
            else if (strcmp (argD[i], "1365")   == 0) strcpy (argD[i],  "1360") ;
            else if (strcmp (argD[i], "1365K")  == 0) strcpy (argD[i],  "1360") ;
            else if (strcmp (argD[i], "1403H")  == 0) strcpy (argD[i],  "1404") ;
            else if (strcmp (argD[i], "1405G")  == 0) strcpy (argD[i],  "1430") ;
            else if (strcmp (argD[i], "1415G")  == 0) strcpy (argD[i],  "1430") ;
            else if (strcmp (argD[i], "1416G")  == 0) strcpy (argD[i],  "1440") ;
            else if (strcmp (argD[i], "1417G")  == 0) strcpy (argD[i],  "1445") ;
            else if (strcmp (argD[i], "1417GS") == 0) strcpy (argD[i],  "1445") ;
            else if (strcmp (argD[i], "1425J")  == 0) strcpy (argD[i],  "1425") ;
            else if (strcmp (argD[i], "1450J")  == 0) strcpy (argD[i],  "1450") ;
            else if (strcmp (argD[i], "1460J")  == 0) strcpy (argD[i],  "1460") ;
            else if (strcmp (argD[i], "1470U")  == 0) strcpy (argD[i],  "1475") ;
            else if (strcmp (argD[i], "1475J")  == 0) strcpy (argD[i],  "1475") ;
            else if (strcmp (argD[i], "1500D")  == 0) strcpy (argD[i],  "1500") ;
            else if (strcmp (argD[i], "1500J")  == 0) strcpy (argD[i],  "1500") ;
            else if (strcmp (argD[i], "1551")   == 0) strcpy (argD[i],  "1500") ;
            else if (strcmp (argD[i], "1560")   == 0) strcpy (argD[i],  "1561") ;
            else if (strcmp (argD[i], "1563")   == 0) strcpy (argD[i],  "1561") ;
            else if (strcmp (argD[i], "1500A")  == 0) strcpy (argD[i],  "1501") ;
            else if (strcmp (argD[i], "1500QT1") == 0) strcpy (argD[i], "1541") ;    /* Quick-Tape with PC-1500 standard header */
            else if (strcmp (argD[i], "1500QT4") == 0) strcpy (argD[i], "1544") ;    /* FAST/Quick-Tape with fast header*/
            else if (strcmp (argD[i], "1500QT") == 0) strcpy (argD[i],  "1544") ;    /* FAST/Quick-Tape */
            else if (strcmp (argD[i], "QT")  ==  0)   strcpy (argD[i],  "1544") ;
            else if (strcmp (argD[i], "QUICKTAPE")== 0) strcpy (argD[i],"1544") ;
            else if (strcmp (argD[i], "150")    == 0) strcpy (argD[i],  "1500") ;    /* CE-150 */
            else if (strcmp (argD[i], "158")    == 0) strcpy (argD[i],  "1500") ;
            else if (strcmp (argD[i], "2500")   == 0) strcpy (argD[i],  "1350") ;
            else if (strcmp (argD[i], "EL-5400")== 0) strcpy (argD[i],  "1430") ;
            else if (strcmp (argD[i], "5400")   == 0) strcpy (argD[i],  "1430") ;
            else if (strcmp (argD[i], "EL-5500III")==0) strcpy (argD[i],"1403") ;
            else if (strcmp (argD[i], "5500III")== 0) strcpy (argD[i],  "1403") ;
            else if (strcmp (argD[i], "1401V1") == 0) strcpy (argD[i],  "1401") ;    /* PC-1401 V.1 */
            else if (strcmp (argD[i], "1404G")   == 0
                 ||  strcmp (argD[i], "EL-5500-T")==0
                 ||  strcmp (argD[i], "5500-T")  == 0
                 ||  strcmp (argD[i], "EL-5500") == 0
                 ||  strcmp (argD[i], "5500")    == 0
                                                    ) {
                 if (type == TYPE_BIN && Acnt==0 && SHCc==0 && addr==0) addr = 0x4000 ;
                                                      strcpy (argD[i],  "1402") ;    /* PC-1401 V.2, less memory */
            }
            else if (strcmp (argD[i], "1401V2")  == 0
                 ||  strcmp (argD[i], "EL-5500II")==0
                 ||  strcmp (argD[i], "5500II")  == 0
                                                    ) {
                 if (type == TYPE_BIN && Acnt==0 && SHCc==0 && addr==0) addr = 0x3800 ;
                                                      strcpy (argD[i],  "1402") ;    /* PC-1401 V.2 */
            }
            else if (strcmp (argD[i], "EL-5510")== 0) strcpy (argD[i],  "1421") ;
            else if (strcmp (argD[i], "5510")   == 0) strcpy (argD[i],  "1421") ;
            else if (strcmp (argD[i], "EL-5520")== 0) strcpy (argD[i],  "1450") ;
            else if (strcmp (argD[i], "5520")   == 0) strcpy (argD[i],  "1450") ;
            else if (strcmp (argD[i], "PTA-4000+16")==0) strcpy (argD[i], "1500") ; /* Hiradas Technika */
            else if (strcmp (argD[i], "PTA-4000")== 0) strcpy (argD[i], "1500") ;
            else if (strcmp (argD[i], "MC-2200") == 0) strcpy (argD[i], "1245") ;    /* Seiko */
            else if (strcmp (argD[i], "2200")   == 0) strcpy (argD[i],  "1245") ;
            else if (strcmp (argD[i], "34")     == 0) strcpy (argD[i],  "1250") ;    /* Tandy*/
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
                 ||  strcmp (argD[i], "1605K")  == 0
                 ||  strcmp (argD[i], "1600P")  == 0) {              /* (1609) CE-1600P, PC-1600 Mode 0 */
/*               ||  strcmp (argD[i], "1600")   == 0) {
                 if (Qcnt == 0) printf ("\n%s: Only the compatibility mode 1 'PC-1500' is supported with PC-%s.\n", argP, argD[i]) ;
                                                      strcpy (argD[i],  "1500") ; */
                                                      strcpy (argD[i],  "1600") ;
            }
            else if (strcmp (argD[i], "1600M1") == 0) strcpy (argD[i],  "1500") ;    /* (1601) CE-150, PC-1600 Mode 1 */
            else if (strcmp (argD[i], "1600K1") == 0) strcpy (argD[i],  "1500") ;    /* (1601) CE-150, PC-1600K Mode 1 */
            else if (strcmp (argD[i], "E220")   == 0
                 ||  strcmp (argD[i], "220")    == 0
                 ||  strcmp (argD[i], "E200")   == 0
                 ||  strcmp (argD[i], "200")    == 0
                                                    ) {
                 if (type == TYPE_IMG && ((debug & BAS_EXT_FRMT)>0 || ( KHXc>0 && (debug & ERR_OFF)==0) ) ) {
                    if (Qcnt == 0) { printf ("\n%s: Use 'CLOAD@' to read this tape format of PC-1460 at PC-%s.\n", argP, argD[i]) ;
                                     printf ("         You MUST create such an BASIC image with Bas2img --pc=1460 implicitly!\n") ;
                                     printf ("         Old tape format selected for PC-E200 series, for files from Bas2img.\n") ;
                    }
                                                      strcpy (argD[i],  "1460") ; /* NOT the native tape format of PC-E2  */
                 }
                 else {
                    if (strcmp(&argD[i][strlen(argD[i])-3], "220")== 0)
                                                      strcpy (argD[i],   "220") ; /* international */
                    else                              strcpy (argD[i],   "200") ; /* Japanese */
                 }
            }
            else if (strcmp (argD[i], "G801")   == 0
                 ||  strcmp (argD[i], "801")    == 0
                 ||  strcmp (argD[i], "G802")   == 0
                 ||  strcmp (argD[i], "802")    == 0
                                                    ) {
                                                      strcpy (argD[i],  "200") ;
            }
            else if (strcmp (argD[i], "G803")   == 0
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
                 ||  strcmp (argD[i], "G850VS") == 0
                 ||  strcmp (argD[i], "G850V")  == 0
                 ||  strcmp (argD[i], "850V")   == 0
                 ||  strcmp (argD[i], "G850S")  == 0
                 ||  strcmp (argD[i], "G850")   == 0
                 ||  strcmp (argD[i], "850")    == 0
                                                    ) {
//                    if (Qcnt == 0 && (debug & 0x18E0 )>0 && type == TYPE_IMG ) {
//                                     printf ("\n%s: If the source file was made by Bas2img and syntax errors are found\n", argP) ;
//                                     printf ("          you can convert it with Text editor to 'TEXT' and back to 'BASIC'.\n");
//                    }
                    if (strchr(argD[i], 'V') == NULL) strcpy (argD[i],   "850") ;
                    else                              strcpy (argD[i],   "852") ; /* G850V(S) */
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
                 if (type == TYPE_IMG && ( (debug & BAS_EXT_FRMT)>0 || (KHXc>0 && (debug & ERR_OFF)==0) ) ) {
                    if (Qcnt == 0) { printf ("\n%s: Use 'CLOAD @' to read this format of PC-1475 on PC-%s.\n", argP, argD[i]) ;
                                     printf ("         There are no particular options for Bas2img necessary.\n") ;
                                     printf ("         Old tape format was selected for PC-E500, for files from Bas2img.\n") ;
                    }
                                                      strcpy (argD[i],  "1475") ; /* NOT the native tape format of PC-E500  */
                 }
                    /*  BASE_FREQ3 2990/1230 Hz (0/1), 2 transmissions/bit with variable length (1T) 1A 1T 1A (1T),
                        Byte = 1 start bit1 + data bit 7...0,
                        1. Header Block = Sync_b0/40b1/40b0/1b1/File ID + Filename + header = 30B + CSum, Pause,
                        see also SHARP: Technical Reference Manual PC-E500, P64-66
                        2. Data Block = Sync_b0/20b1/20b0/1b1/ FF + 7 Header Bytes + 10 Bytes 0, 0D, Program Data
                        Block length 256? bytes ... 0D FF cs 1A */
                 else {
//                    if (type == TYPE_IMG && Qcnt == 0) {
//                                     printf ("\n%s: If the source file was made by Bas2img you have to switch to 'TEXT',\n", argP) ;
//                                     printf ("          back to 'BASIC' on PC-%s or use old tape format with '-l 0x%05X'.\n", argD[i], BAS_EXT_FRMT);
//                                     printf ("          You can transfer Text lines with -t TXT for Bas2Img and here IMG.\n\n");
//                    }
                                                      strcpy (argD[i],   "500") ; /* The native tape format of PC-E500  */
                 }
            }
            else if (strcmp (argD[i], "ST")       == 0
                 ||  strcmp (argD[i], "SUPERTAPE")== 0
                 ||  strcmp (argD[i], "1500ST")   == 0
                                                    ) {
                 if (type == TYPE_IMG || type == TYPE_BIN) {
                    if (Qcnt == 0) {
                                     printf ("\n%s: c't SuperTape format was selected,\n", argP) ;
                                     printf ("         An implementation for the PC is required - see SuperTape for PC-1500.\n");
                                     printf ("         You can transfer back this format with SuperTape for Win32 only.\n");
                                     printf ("         After transferring back convert .ST to .BAS with Wav2bin --img 26\n\n");
                    }
                                                      strcpy (argD[i],   "36015") ; /* c't SuperTape format,for PC-1500 */
                 }
                 else MoreInfo (ERR_ARG);
            }
            else if (strcmp (argD[i], "ST3600")   == 0
                                                    ) {
                 if (type == TYPE_IMG || type == TYPE_BIN) {
                    if (Qcnt == 0) {
                                     printf ("\n%s: c't SuperTape format 3600 baud was selected,\n", argP) ;
                                     printf ("         An implementation for your computer is required - exist for PC-1500.\n");
                                     printf ("         You can transfer back this format with SuperTape for Win32 only.\n");
                    }
                                                      strcpy (argD[i],   "36000") ; /* c't SuperTape format,for PC-1500 and other */
                 }
                 else MoreInfo (ERR_ARG);
            }
            else if (strcmp (argD[i], "ST7200")   == 0
                                                    ) {
                 if (type == TYPE_IMG || type == TYPE_BIN) {
                    if (Qcnt == 0) {
                                     printf ("\n%s: c't SuperTape format 7200 baud was selected,\n", argP) ;
                                     printf ("         An implementation for your computer is required -UNKNOWN for PC-1500.\n");
                                     printf ("         You can transfer back this format with SuperTape for Win32 only.\n");
                    }
                                                      strcpy (argD[i],   "72000") ; /* c't SuperTape format, for other computer */
                 }
                 else MoreInfo (ERR_ARG);
            }
            pcId = (ulong) strtol (argD[i], &ptrErr, 0) ;
            if (pcId == 0) {
                printf ("%s: Pocket computer %s is not valid\n", argP, argD[i]);
                MoreInfo (ERR_ARG);    // exit (ERR_SYNT) ;
                break ;
            }
        }
        switch (pcId) {
        case 1211 :
            {   if (type == TYPE_BIN) addr = 0xFFFF;
                grpId=IDENT_PC1211; cnvstr_upr = true ; bitMirroring = true ; /* PC-1211, CE-121 Service Manual, Page 19 */
                break; }
        case 1140 :
        case 1146 : /* 1246DB */
        case 1148 : /* 1248DB */
        case 1150 :
            if (type == TYPE_MEM && Acnt<2) eaddr = 0x8A00 ; /* 4 bit pointer, after declared = begin of standard variables */
        case 1246 :
        case 1247 :
        case 1248 :
            if (type == TYPE_BIN) addr = 0xFFFF;
        case 1245 :
        case 1250 :
        case 1251 :
        case 1255 :
            {   if (type == TYPE_BIN && Acnt==0 && SHCc==0 && addr==0) addr = 0xB830;
                grpId=GRP_OLD; cnvstr_upr = true ; break; }

        case 1430 :
        case 1431 :
            if (type == TYPE_BIN && Acnt==0 && SHCc==0 && addr==0) addr = 0xFFFF;
        case 1421 :
        case 1401 : /*PC-1401 V.1*/
            if (type == TYPE_BIN && Acnt==0 && SHCc==0 && addr==0) addr = 0x3800;
        case 1402 : /* and for 1401 V.2, addr like V.1 */
            if (type == TYPE_BIN && Acnt==0 && SHCc==0 && addr==0) addr = 0x2000;
        case 1440 : /*Memory map not known exactly, with CAP-X*/
            if (type == TYPE_BIN && Acnt==0 && SHCc==0 && addr==0) addr = 0x3802;
        case 1445 : /*Memory map unknown, with CASL */
            if (type == TYPE_BIN && Acnt==0 && SHCc==0 && addr==0) addr = 0x2002;
            cnvstr_upr = true ;

        case 1100 :
            if (type == TYPE_BIN && Acnt==0 && SHCc==0 && addr==0) addr = 0xFFFF;
        case 1260 :
            if (type == TYPE_BIN && Acnt==0 && SHCc==0 && addr==0) addr = 0x5880;
        case 1261 :
        case 1262 :
            if (type == TYPE_BIN && Acnt==0 && SHCc==0 && addr==0) addr = 0x4080;
        case 1350 :
        case 1450 :
            if (type == TYPE_BIN && Acnt==0 && SHCc==0 && addr==0) addr = 0x2030;
        case 1403 :
            if (type == TYPE_BIN && Acnt==0 && SHCc==0 && addr==0) addr = 0xE030;
        case 1404 :
        case 1425 :
        case 1460 :
            if (type == TYPE_BIN && Acnt==0 && SHCc==0 && addr==0) addr = 0x8030;
            grpId = GRP_NEW ;
            break ;

        case 1280 :
        case 1360 :
        case 1475 :
            if (type == TYPE_BIN && Acnt==0 && SHCc==0 && addr==0) addr = 0x8030;
            grpId = GRP_EXT ;
            break ;

        case 1555 :
            if (type == TYPE_BIN && Acnt==0 && STc==0 && addr==0) addr = 0x38C5;
        case 1559 :
            if (type == TYPE_BIN && Acnt==0 && STc==0 && addr==0) addr = 0x20C5;
        case 1561 :
            if (type == TYPE_BIN && Acnt==0 && STc==0 && addr==0) addr = 0x00C5;
        case 1501 :
            if (type == TYPE_BIN && Acnt==0 && STc==0 && addr==0) addr = 0x7C01;
            pcId = 1500 ;
        case 1500 :
            if (type == TYPE_BIN && Acnt==0 && STc==0 && addr==0) addr = 0x40C5;
            bitMirroring = true ; /* CE-150 Service Manual, Page 9 */
            grpId = IDENT_PC1500 ;
            break ;

        case 1600 :
            if (type == TYPE_BIN && Acnt==0 && addr==0) addr = 0xC0C5;
//            bitMirroring = true ; /* sample pattern of bitE changed in 2.1.1, but TRM S.120 */
            grpId = GRP_16 ;
            break ;

        case  500 :
            if (type == TYPE_BIN && Acnt==0 && addr==0) addr = 0xBE000;
//            bitMirroring = true ; /* ASCII-Data retransmission */
            grpId = GRP_E ;
            break ;

        case  220 :
        case  200 :
        case  850 :
        case  852 :
            if (type == TYPE_BIN && Acnt==0 && addr==0) addr = 0x0100;
//            bitMirroring = true ; /* ASCII-Data retransmission */
            grpId = GRP_G ;
            break ;

        case 1541 :
            pcgrpId = IDENT_PC1500 ;
            QTc = 1 ;
        case 1544 :
            if (type == TYPE_BIN && Acnt==0 && addr==0) addr = 0x40C5;
            bitMirroring = true ;
            flags = 0 ;
            pcId = 1500 ;
            grpId = IDENT_QTAPE ;
            if (pcgrpId == IDENT_UNKNOWN) pcgrpId = IDENT_QTAPE ;
            if (QTc==0) QTc = 4 ;
            break ;

        case 36015 :
            flags = SUPT_FLAGS ;
            flags &= 0xFF7F ;
            bitMirroring = true ;
            grpId = IDENT_ST ;
            pcgrpId = IDENT_ST ;
            if (STc==0) STc = 1 ;
            break ;

        case 36000 :
            flags = SUPT_FLAGS ;
            flags |= 0x0100 ; /* no lead in*/
            flags &= 0xFF7F ;
            grpId = IDENT_ST ;
            pcgrpId = IDENT_ST ;
            if (STc==0) STc = 1 ;
            break ;

        case 72000 :
            flags = SUPT_FLAGS ;
            flags |= 0x0100 ; /* no lead in*/
            flags |= 0x0080 ;
            grpId = IDENT_ST ;
            pcgrpId = IDENT_ST ;
            if (STc==0) STc = 1 ;
            break ;

        default :
            /* Newest of G-Series, G850V and newer */
            printf ("%s: Pocket computer %s is not implemented\n", argP, argD[3]) ;
            // MoreInfo (ERR_ARG);
            error = ERR_ARG ;
            // break ;
        }
        if (error != ERR_OK) break ;

        if (pcgrpId == IDENT_UNKNOWN) pcgrpId = grpId ;
        else if ( SHCc > 0 && pcgrpId != grpId ) { /* grpId from --pc parameter is different from SHC file pcgrpId*/

            if (pcgrpId == GRP_NEW && grpId == GRP_EXT && /* ID for both groups */
                (type == TYPE_BIN || type == TYPE_DAT)) pcgrpId = grpId ;

            else if ( type == TYPE_BIN ) {
                /* Data may be universally valid or nonsense mostly */
                if (Qcnt == 0) printf
                    ("%s: Type mismatch between PC-%s and Binary SHC format. Data may be not valid.\n", argP, argD[3]) ;
                pcgrpId = grpId ;
            }
            else if (grpId == IDENT_PC1211 && pcgrpId == GRP_OLD ) { //  && type != TYPE_BIN
                /* PC-1211 can use SHC data of PC-1251 without data header */
                pcgrpId = grpId ;
            }
            else if (type == TYPE_DAT && (grpId==IDENT_PC1500 || grpId==GRP_16)){
                /* Limited Conversion of other SHC data into PC-1500 data */
                if (Qcnt ==0) printf ("%s: Data is converted by SHC file format to Pocket computer %s\n", argP, argD[3]) ;
                if (pcgrpId == GRP_OLD) debug |= 0x10 ;
                debug |= 8 ;
                pcgrpId = grpId ;
            }
            else if (type == TYPE_DAT && (pcgrpId == GRP_OLD || grpId == GRP_OLD ) ) {
                /* convert ASCII data */
                if (Qcnt ==0) printf ("%s: Strings are converted to Pocket computer %s\n", argP, argD[3]) ;
                debug |= 0x10 ;
                pcgrpId = grpId ;
            }
            else if (type == TYPE_IMG && pcgrpId == GRP_NEW && (grpId == GRP_E || pcId == 220 ) ) {
                if (Qcnt ==0) printf ("%s: SHC of PC-1460 is used for PC-%s, use CLOAD@ to transfer!\n", argP, argD[3]) ;
                debug |= BAS_EXT_FRMT ;
                grpId = pcgrpId ;
            }
            else if (type == TYPE_IMG && pcgrpId == GRP_EXT && (grpId == GRP_E || pcgrpId == GRP_G) ) {
                if (Qcnt ==0) printf ("%s: SHC PC-1475 used for PC-%s, convert it via TEXT mode after transfer!\n", argP, argD[3]) ;
                pcgrpId = grpId ;
            }
            else if ( grpId != IDENT_UNKNOWN && PCcnt > 0 ) {
                printf ("%s: Type mismatch between Pocket computer %s and SHC file format\n", argP, argD[3]) ;
                MoreInfo (ERR_ARG);
            }
        }

        if ( type == TYPE_DAT && (pcgrpId == GRP_E || pcgrpId == GRP_G)) { /* Ascii files used for data */
            type = TYPE_ASC ;
            if (Qcnt == 0 )
                printf ("%s: Source file type %s for group of PC-%lu was changed to 'asc'.\n", argP, argD[2], pcId) ;
        }
        if ( type == TYPE_TXT) {
            if ( pcgrpId == GRP_16 ) type = TYPE_BAS ; /* for comments saved with SAVE* CAS: */
            else if ( pcgrpId != GRP_E && pcgrpId != GRP_EXT && pcgrpId != GRP_NEW) {
                if (!type_asm) printf ("%s: Source file type %s is for TEXT mode, not valid for group of PC-%lu \n", argP, argD[2], pcId) ;
                if (pcgrpId == GRP_G){
                    if (pcId < 852 ) {
                        if (!type_asm) {
                            ++wrn_cnt;
                            printf ("%s: Text MENU needs BAS type! Type '%s' is switched to BAS now.\n", argP, argD[2]) ;
                        }
                        type = TYPE_BAS ;
                    }
                    else {
                        if (!type_asm) ++wrn_cnt;
                        printf ("%s: Text MENU item 'Cmt' was removed for PC-G850V(S)!\n Type '%s' is switched to IMG now.\n", argP, argD[2]) ;
                        type = TYPE_IMG ;
                    }
                }
                else {
//                    MoreInfo (ERR_ARG);
//                    break ;
                    if (!type_asm) {
                        ++err_cnt;
                        printf ("%s: Type '%s' is switched to IMG now.\n", argP, argD[2]) ;
                    }
                    type = TYPE_IMG ;
                }
            }
            else if ( pcgrpId == GRP_E ) { /* That CSAVEd from TEXT modus may not CLOADable*/
                printf ("%s: Source file type %s is not compatible with CLOAD for group of PC-E%lu\n", argP, argD[2], pcId) ;
                if ( (debug & ERR_OFF) ==0 ){
                    ++wrn_cnt;
                    printf ("%s: Option -l 0x%03X not found: Type is switched from %s to IMG now.\n", argP, ERR_OFF, argD[2]) ;
                    type = TYPE_IMG ;
                }
                else ++err_cnt;
            }
        }
        if ( (type == TYPE_BAS || type == TYPE_ASC) && !(pcgrpId == GRP_16 || pcgrpId == GRP_E || pcgrpId == GRP_G)) {
            printf ("%s: Src type %s (Text Menu or device CAS:) not valid for PC-%lu group!\n", argP, argD[2], pcId) ;
            printf (" You need to use an IMaGe here that Bas2img can create from source code before.\n") ;
            MoreInfo (ERR_ARG);
            break ;
        }
        if ( type == TYPE_BAS  &&  pcgrpId == GRP_G  && pcId >= 852) {
            ++err_cnt;
            printf ("%s: Text MENU item 'Cmt' was removed at PC-G850V(S).\n You can use Txt-> 'IMG' for Sources, but not %s!\n\n", argP, argD[2]) ;
        }
        else if
           ((type == TYPE_ASC  && (pcgrpId == GRP_E || (pcgrpId == GRP_G && pcId > 802))) ||
            (type == TYPE_BAS  &&  pcgrpId == GRP_E) ) { /* That SAVEd to CAS: may not LOADable*/
            ++wrn_cnt;
            if (Qcnt == 0) {
                    printf ("%s: Source type %s may not loadable from device CAS: for PC-G/E%lu\n", argP, argD[2], pcId);
                    printf ("         Try high sound level, -dMAX. ");
                    if (pcgrpId == GRP_E) printf ("Sometimes -dINV (-dINX) is needed or not.\n");
                    else printf ("\nFirst test with orig. recordings what your PC-G can read back from this format!\n\n");
            }
        }
        if ( (type == TYPE_RSV) && (pcgrpId == GRP_E || pcgrpId == GRP_G)) {
            printf ("%s: Src type %s (ReSerVe data) is not valid for group of PC-%lu\n", argP, argD[2], pcId) ;
            MoreInfo (ERR_ARG);
            break ;
        }
        if ( (type == TYPE_DEF) && (pcgrpId != IDENT_PC1500) ) {
            printf ("%s: Src type %s (Def.Key data) is not valid for group of PC-%lu\n", argP, argD[2], pcId) ;
            MoreInfo (ERR_ARG);
            break ;
        }
        if ( (type == TYPE_DIM) && (pcgrpId != IDENT_QTAPE) ) {
            printf ("%s: Src type %s (Dim. Var data) is valid only for Quick-Tape\n", argP, argD[2]) ;
            MoreInfo (ERR_ARG);
            break ;
        }
        if ( (type == TYPE_DAT) && (pcgrpId == IDENT_QTAPE) ) {
            printf ("%s: Src type %s (Variable data) is not implemented for Quick-Tape\n", argP, argD[2]) ;
            printf ("         Use DIM and INPUT # or QSAVE D all dim. data complete, --type=DIM\n") ;
            MoreInfo (ERR_ARG);
            break ;
        }
        if ( (type == TYPE_CRD || type == TYPE_TEL || type == TYPE_SCD ||type == TYPE_NOT) && (pcId != 1100) ) {
            printf ("%s: Src type %s (Memo data) is only implemented for PC-1100\n", argP, argD[2]) ;
            MoreInfo (ERR_ARG);
            break ;
        }
        if ( (type == TYPE_MEM) && (pcId < 1140 || 1150 < pcId) ) {
            printf ("%s: Src type %s (Database data) is not implemented for this PC\n", argP, argD[2]) ;
            MoreInfo (ERR_ARG);
            break ;
        }
        if ( (type == TYPE_BIN) && (pcgrpId == IDENT_PC1211 || (1245 < pcId && pcId < 1250) || 1100 == pcId ||
                                    (1140 <= pcId && pcId <= 1150) || pcId == 1430 || pcId == 1431)) {
            printf ("%s: Src type %s (Binary data) is not valid for 4-bit CPU of PC-%lu\n", argP, argD[2], pcId) ;
            MoreInfo (ERR_ARG);
            break ;
        }
        strlor(argD[4]) ;     /* the number after the device name determines the type of signal shutdown */
        if ( strlen(argD[4])==4 && (strncmp (argD[4], "std", 3) == 0 || strncmp (argD[4], "max", 3) == 0 ||
             strncmp (argD[4], "inv", 3) == 0 || strncmp (argD[4], "inx", 3) == 0) ) { /* INv+maX */
                 Shutdown_Form = argD[4][3] - 0x30;
                 if (Shutdown_Form < 0 || Shutdown_Form > 4) { /* 4 also as default -1 */
                    printf ("%s: Property of target device '%s' is not valid\n", argP, argD[4]) ;
                    MoreInfo (ERR_ARG);
                 }
                 else{
                    argD[4][3]= 0;
                 }
        }
        if ((pcgrpId == IDENT_PC1500 || pcgrpId == IDENT_ST) && Shutdown_Form < 0) Shutdown_Form = 0 ;
        if ( pcgrpId == GRP_OLD && type==TYPE_MEM) {
                if (Dcnt==0) strcpy( argD[4], "max") ;
                if (Shutdown_Form < 0) Shutdown_Form = 0 ;      /* waves at end of old DBs */
//              if ((debug & (ERR_OFF | 0x3)) == 0) debug |=2 ; /* default waveform unreliable at eof */
        }
        if (strcmp (argD[4], "std") == 0 || strcmp (argD[4], "126") == 0 || strcmp (argD[4], "ati") == 0 || /* default: std */
            strcmp (argD[4], "129") == 0 || strcmp (argD[4], "123") == 0 || strcmp (argD[4], "120") == 0 ) {
            /*  The retransmission of the original recording of ASCII data
                only works correctly for the E5-Series inverted and G850(S) not */
//            if (pcgrpId == GRP_16 || pcgrpId == GRP_E || pcgrpId == GRP_G) bitMirroring = true ;
            error= ERR_OK ;
        }
        else if (strcmp (argD[4], "124") == 0 || strcmp (argD[4], "ecps") == 0 ||  /* CE-124, CE-120K/C/D */
                 strcmp (argD[4], "162") == 0 || strcmp (argD[4], "150") == 0 ||   /* CE-150 */
                 /* DIY interface of Rik Hartl, Manfred Nosswitz i.a. */
                 strcmp (argD[4], "mfe") == 0 || strcmp (argD[4], "nos") == 0  ) {
//                    bitMirroring = true ;
                    error= ERR_OK ;
        }
        else if (strcmp (argD[4], "125") == 0 ||  /* CE-125 */
                 strcmp (argD[4], "122") == 0) {  /* PC-121x + CE-122 */
                    bitMirroring = false ; /* CE-122 Service Manual, Page 14 */
                    Amp_High = AMP_HIGH_121 ;
                    Amp_Low  = AMP_LOW_121 ;
        }
        else if (strcmp (argD[4], "max") == 0  || strcmp (argD[4], "inx") == 0 ||
                 strcmp (argD[4], "121") == 0) { /* CE-121 */
                if (pcgrpId == GRP_16 || pcgrpId == GRP_E || pcgrpId == GRP_G) {
                    Amp_High = AMP_HIGH_E + AMP_add_Emax ;
                    Amp_Low  = AMP_LOW_E  - AMP_add_Emax ;
                }
                else {
                    Amp_High = AMP_HIGH_121 + AMP_add_121 ;
                    Amp_Low  = AMP_LOW_121  - AMP_add_121 ;
                }
                if (strcmp (argD[4], "121") == 0) bitMirroring = true ;
                if (strcmp (argD[4], "inx") == 0) bitMirroring = !bitMirroring ;
        }
        else if (strcmp (argD[4], "inv") == 0)
            bitMirroring = !bitMirroring ;        /* also changed by the PC group  */
        else if (strcmp (argD[4], "khx") == 0 || strncmp (argD[4], "dsave", 5) == 0)
            KHXc |= 1 ;
        else if (strcmp (argD[4], "tap") == 0)
            {if (TAPc == 0) TAPc = 1; }
        else {
            printf ("%s: Name of target device '%s' is not valid\n", argP, argD[4]) ;
            MoreInfo (ERR_ARG);
        }
        /* Convert waveform in a long */
        waveform = (ulong) strtol (argD[16], &ptrErr, 0) ;
        if (*ptrErr != 0) {
            waveform = 0 ;
            printf ("%s: Convert waveform number from '%s' is not valid\n", argP, argD[16]) ;
            MoreInfo (ERR_ARG);
        }
        if ( waveform > 6) { /* no more until now */
            printf ("%s: Waveform number '%s' is not valid\n", argP, argD[16]) ;
            MoreInfo (ERR_ARG);
        }
        if ((debug & 3)>0) waveform = debug & 3 ; /* debug has priority */
        if (waveform <4) debug |= waveform ;      /* four frequencies per group, 0 with more forms */

        /* Choose the waveform */
        if (TAPc == 0 && KHXc == 0) switch (debug & 0x3) {
        case 1 :
            if (Qcnt == 0 ) printf ("%s: Waveform of base frequency forced to old compact/triangle.\n", argP) ;
            if (pcgrpId == IDENT_QTAPE)
                bit = bitQ1 ;
            else
                bit = bit1 ;    /* set waveform */
            bitQ   = bitQ1 ;
            bitS   = bitS1 ;
            bitS_7 = bitS1 ; /* No 7200 baud possible */
            flags &= 0xFF7F ;
            if (pcgrpId != GRP_G)
                bitE = bitE1 ;  /* asymmetric compressed waveform for E-Series*/
            else  printf ("%s: Waveform not readable with E200/G800 series, using standard.\n", argP) ;
            break ;

        case 0 : /* Ver.2.1 default, similar to Ver.2.0 --level=2 */
            if (pcgrpId == IDENT_PC1500 || pcgrpId == IDENT_ST) {
                if (waveform == 6) bit = bit6_15 ;
                else if (waveform == 5) bit = bit3_15_v20 ;
                else if (waveform > 3) bit = bit3_15_v209 ;
                else bit = bit3_15 ;
                if (Qcnt == 0 && debug != 0) {
                    if (waveform == 6)
                        printf ("%s: Waveform %lu, frequency 96 kHz\n", argP, waveform) ;
                    else
                        printf ("%s: Waveform %lu, frequency 44.1 kHz\n", argP, waveform) ;
                }
            }
            else if (pcgrpId == IDENT_QTAPE) {
                if (waveform == 6) bit = bitQ6 ;
                else bit = bitQ3 ; /* with QTape header */
                if (Qcnt == 0 && debug != 0) {
                    if (waveform == 6)
                        printf ("%s: Waveform %lu, frequency 96 kHz\n", argP, waveform) ;
                    else
                        printf ("%s: Waveform %lu, frequency 44.1 kHz\n", argP, waveform) ;
                }
            }
            else if ( waveform ==0 &&
                      pcgrpId == GRP_OLD && type==TYPE_MEM && (debug & ERR_OFF)==0) {
                bit = bit3_v210 ;
                if (Qcnt == 0 && debug != 0)
                    printf ("%s: Wav frequency 48 kHz, format V2.10 near rectangle\n", argP) ;
            }
            else {
                if (waveform == 6) bit = bit6 ;
                else if (waveform == 5) bit = bit5 ;
                else if (waveform > 3) bit = bit3_v210 ;
                else bit = bit3 ;
                if (Qcnt == 0 && debug != 0) {
                    if (waveform == 6 ) {
                        if (pcgrpId == GRP_E || pcgrpId == GRP_G || pcgrpId == GRP_16)
                             printf ("%s: Waveform %lu, frequency 96 kHz, near rectangle\n", argP, waveform) ;
                        else printf ("%s: Waveform %lu, frequency 96 kHz, rounded\n", argP, waveform) ;
                    }
                    else if (waveform == 5 ) {
                        if (pcgrpId == GRP_E || pcgrpId == GRP_G || pcgrpId == GRP_16)
                             printf ("%s: Waveform %lu, frequency 88.2 kHz, precise rectangle with bevels\n", argP, waveform) ;
                        else printf ("%s: Waveform %lu, frequency 96 kHz, near rectangle with bevels\n", argP, waveform) ;
                    }
                    else if (waveform > 3)
                         printf ("%s: Waveform %lu, frequency 48 kHz, near rectangle\n", argP, waveform) ;
                    else if (pcgrpId == GRP_E || pcgrpId == GRP_G || pcgrpId == GRP_16)
                         printf ("%s: Wav frequency 48 kHz, near rectangle with bevels\n", argP) ;

                    else printf ("%s: Wav frequency 48 kHz, near sinus\n", argP) ;
                }
            }
            if (waveform == 6) {
                bitE = bitE6 ;
                bitQ = bitQ6 ;
                bitS = bitS6 ;
            }
            else {
                if (waveform == 5) bitE = bitE5 ;
                else if (waveform > 3) bitE = bitE3_v20 ;
                else bitE = bitE3 ;

                bitQ  = bitQ3 ; /* switched  after header */
                bitS  = bitS3 ;
            }
            bitS_7 = bitS4_7 ; /* No 44,1 kHz for 7200 baud implemented, 72 kHz used */
            flags &= 0xFF7F ;
            break ;

        case 3 :
            if (Qcnt == 0 ) {
                if (pcgrpId == IDENT_ST) printf ("%s: Wav frequency forced to 72 kHz.\n", argP) ;
                else printf ("%s: Wav frequency forced to 16 kHz.\n", argP) ;
            }
            if (pcgrpId == IDENT_PC1500)
                bit = bit4_15 ;

            else if (pcgrpId == IDENT_QTAPE)
                bit = bitQ4 ;

            else {
                bit = bit4 ;
            }
            bitQ   = bitQ4 ;
            bitS   = bitS4 ;
            bitS_7 = bitS4_7 ; /* 7200 baud data block implemented */
            bitE = bitE4 ;
            break ;

        case 2 : /* identical to Ver.2.0 default */
                if (Qcnt == 0 ) printf ("%s: Wav frequency forced to Version 2.0, trapezoid.\n", argP) ;
                bit = bit2 ;
                bitE = bitE2 ;
                bitQ = bitQ2 ;
                bitS = bitS2 ;
                bitS_7 = bitS2_7 ;

//        default : /* see also global definition */
            if (pcgrpId == IDENT_QTAPE)
                bit = bitQ2 ;

            if ((flags & 0x80) > 0) { /* flag for 7200 baud, not supported with PC-1500 */
                bitS   = bitS4 ;
                bitS_7 = bitS4_7 ; /* 7200 baud data block */
            }
            break ;

        }
        if (TAPc == 0 && KHXc == 0 && Qcnt == 0 && Dcnt > 0 && bitMirroring && debug != 0)
            printf ("%s: Waveform will be mirrored (inverted).\n", argP) ;

        /* Check the range of CPU (or cassette) speed factor from modified hardware */
        speed = strtod (argD[5], &ptrErr) ;
        if ((*ptrErr != 0) || 0.199 > speed || speed > 2.701) {
                printf ("%s: A ratio of CPU frequency to an unmodified %s is not supported.\n", argP, argD[5]) ;
                MoreInfo (ERR_ARG);
        }
        else if (Qcnt == 0 && ((float) speed < 0.9998 || (float) speed > 1.0002 ))
                printf ("%s: Option cspeed, ratio to original CPU frequency: %1.2f\n", argP, speed) ;

        if ( type == TYPE_RSV && pcgrpId != IDENT_PC1500 && pcgrpId != IDENT_QTAPE && pcgrpId != GRP_16 ) type = TYPE_IMG ;

        /* Convert the Address in a ulong if necessary */
        if (type == TYPE_BIN || type == TYPE_MEM || type == TYPE_RSV || type == TYPE_DEF || ( Acnt > 0 &&
            (pcgrpId == GRP_E || pcgrpId == GRP_G || pcgrpId == GRP_16 ||
             pcgrpId == IDENT_PC1500  || pcgrpId == IDENT_QTAPE || pcgrpId == IDENT_ST) ) ) {

            if (Acnt > 0) addr = (ulong) strtol (argD[6], &ptrErr, 0) ;
            if (*ptrErr != 0) { /* was (*ptrErr != NULL) */
                tmp = *ptrErr ;
                *ptrErr = 0 ;
                printf ("%s: Start address is not valid '%s -> ", argP, argD[6]) ;
                *ptrErr = tmp ;
                printf ("%s'\n", ptrErr) ;
                MoreInfo (ERR_ARG);
                break ;
            }
            if (pcgrpId == GRP_E || pcgrpId == GRP_G || pcgrpId == GRP_16 || type == TYPE_MEM ||
                pcgrpId == IDENT_PC1500 || pcgrpId == IDENT_QTAPE || pcgrpId == IDENT_ST) {

                if (pcgrpId == IDENT_QTAPE) {
                    if (flags==0) flags = (addr & 0x70000) >> 16 ;
                    addr &= 0xFFF8FFFF;
                }
                if ( addr > 0xFFFFFF || (addr > 0xFFFF &&
                                        (pcgrpId == GRP_G || pcgrpId == IDENT_PC1500 || type == TYPE_MEM ||
                                         pcgrpId == IDENT_QTAPE || pcgrpId == IDENT_ST))) {

                    printf ("%s: Start address '%s' is out of range\n", argP, argD[6]) ;
                    MoreInfo (ERR_ARG);
                    break ;
                }

                if ( Acnt > 1 || ( (type == TYPE_BIN || type == TYPE_MEM) && eaddr == 0) )
                    eaddr = (ulong) strtol (argD[7], &ptrErr, 0) ;
                if (*ptrErr != 0) { /* was (*ptrErr != NULL) */
                    tmp = *ptrErr ;
                    *ptrErr = 0 ;
                    printf ("%s: Entry address is not valid '%s -> ", argP, argD[7]) ;
                    *ptrErr = tmp ;
                    printf ("%s'\n", ptrErr) ;
                    MoreInfo (ERR_ARG);
                    break ;
                }
                if (eaddr == 0xFFFFFF && pcgrpId == IDENT_PC1500) eaddr = 0xFFFF;
                if ( eaddr > 0xFFFFFF || (eaddr > 0xFFFF && eaddr < 0xFFFFFF &&
                                         (pcgrpId == GRP_G || pcgrpId == IDENT_PC1500 ||
                                          type == TYPE_MEM || pcgrpId == IDENT_ST))) {
                    printf ("%s: Entry address '%s' is out of range\n", argP, argD[7]) ;
                    MoreInfo (ERR_ARG);
                    break ;
                }
                if (pcgrpId == GRP_G && eaddr != 0xFFFFFF && Qcnt == 0)
                    printf ("%s: No autostart, type> MON and *G%04X to start this program!\n", argP, (uint) (eaddr & 0xFFFF)) ;
                /* if ( pcgrpId == GRP_16 &&
                     type == TYPE_RSV && addr == 0) addr = 0xC008 ;  RSV addr PC-1600
                 if (type == TYPE_RSV && addr == 0) addr = 0x4008 ;  RSV addr PC-1500 */
            }
            else {
                if ( addr > 0xFFFF ) { // || (addr < 0)
                    printf ("%s: Start address '%s' is out of range\n", argP, argD[6]) ;
                    MoreInfo (ERR_ARG);
                    break ;
                }
            }
            if (type==TYPE_BIN && addr==0 && Qcnt == 0)
                    printf ("%s: Load address '0' found. Use CLOAD M with the correct start address!\n", argP);
        }
        if ( pcgrpId == IDENT_PC1500 && QTc==1 && flags >0)
            printf ("%s: Quick-Tape flags 0x%02X unsupported for pc=%s\n", argP, (uchar) flags, argD[3]);

        /* Convert the Sync length in a double */
        sync = strtod (argD[8], &ptrErr) ;
        if (*ptrErr != 0) { /* was (*ptrErr != NULL) */
            tmp = *ptrErr ;
            *ptrErr = 0 ;
            printf ("%s: Sync length is not valid '%s -> ", argP, argD[8]) ;
            *ptrErr = tmp ;
            printf ("%s'\n", ptrErr) ;
            MoreInfo (ERR_ARG);
            break ;
        }
        syncS = strtod (argD[9], &ptrErr) ;
        if (*ptrErr != 0) { /* was (*ptrErr != NULL) */
            tmp = *ptrErr ;
            *ptrErr = 0 ;
            printf ("%s: Sync space (silence) length is not valid '%s -> ", argP, argD[9]) ;
            *ptrErr = tmp ;
            printf ("%s'\n", ptrErr) ;
            MoreInfo (ERR_ARG);
            break ;
        }

        if ( Scnt == 0 ) {      /* change default sync length */
            if ((debug & (SYNCL_STD | SYNCL_TRM))>0 ) {
                if (Qcnt == 0) {
                        if (KHXc > 0) printf ("%s: Options for the Khx file format have been set.\n", argP) ;
                        else printf ("%s: Sync length forced to a standard length.\n", argP) ;
                }
                switch (pcgrpId) {
                    case GRP_G :
                    case GRP_16 :
                        sync = 3.5 ; break ;
                    case GRP_E :
                        sync = 4.0 ; break ;
                    case IDENT_ST :
                    case IDENT_QTAPE :
                        sync = 2.0 ; break ;
                    case IDENT_PC1211 :
                        sync = 5.0 ; break ;
                    default :
                        sync = 8.0 ; break ;
                }
            }
            else if (pcgrpId == GRP_G || pcgrpId == GRP_16 ||  /* min 1.7 sec */
                     pcgrpId == GRP_E) sync = 2.125 ; /* change default value */
        }
        if  ( Scnt < 2 && ( pcgrpId == GRP_E || pcgrpId == GRP_16 ||
                            pcgrpId == GRP_G) ) {
            if ((debug & (SYNCL_STD | SYNCL_TRM))==0 )
                Scnt = 3 ; /* use default values from Bin2wav, not from TRM */
        }

        if ( (sync < 0.4999) ||
             (sync > 10.0001) ) {
            printf ("%s: Sync length '%s' is out of range 0.5 - 10\n", argP, argD[8]) ;
            MoreInfo (ERR_ARG);
            break ;
        }
        if ( (syncS < 1.6999) ||
             (syncS > 10.0001) ) {
            printf ("%s: Sync space (silence) length '%s' is out of range 1.7 - 10\n", argP, argD[9]) ;
            MoreInfo (ERR_ARG);
            break ;
        }
        if ((debug & SYNCA_END)>0 && Qcnt==0)
            printf ("%s: Additional sync of %i seconds at the end of the file is enforced.\n", argP, SYNCA_END_LEN) ;
        if ((debug & NO_WAV_END)>0 && Qcnt==0) {
            printf ("%s: Hard end of file was forced.", argP) ;
            if ( pcgrpId == GRP_E || pcgrpId == GRP_16 || pcgrpId == GRP_G )
                printf (" Add your own silence to this wav file!\n") ;
            else printf ("\n") ;
        }
        /* Check if the name-option is used and no name is defined */
        if ( ( Ncnt == 1 ) && ( strlen (argD[10]) == 0 ) ) {
            /* Search the last colon position */
            ptrToken = strrchr (argD[1], CHAR_COLON) ;
            if (ptrToken == NULL)
                (void) strcpy (argS, argD[1]) ;
            else
                (void) strcpy (argS, ptrToken + 1) ;

            /* Search the last slash position */
            ptrToken = strrchr (argS, CHAR_SLASH) ;
            if (ptrToken == NULL)
                (void) strcpy (argD[10], argS) ;
            else
                (void) strcpy (argD[10], ptrToken + 1) ;

            /* Search the dot position */
            ptrToken = strchr (argD[10], CHAR_DOT) ;
            if (ptrToken != NULL)
                *ptrToken = 0 ;
        }
        if (pcgrpId != GRP_16 && pcgrpId != GRP_G && pcgrpId != GRP_E ) {
            /* Replace the underscore with space in the name */
            ptrToken = strchr (argD[10], CHAR_UNDERSCORE) ;
            while (ptrToken != NULL) {
                *ptrToken = CHAR_SPACE ;
                ptrToken = strchr (argD[10], CHAR_UNDERSCORE) ;
            }
        }
        if (pcgrpId == GRP_16 && strlen (argD[10]) > 0 ) {
            if (type == TYPE_ASC || type == TYPE_BAS) strupr(argD[10]) ;
            else if (type == TYPE_IMG) strncat (argD[10], ".BAS", cLPF - 1 - strlen (argD[10]) ) ;
            else if (type == TYPE_BIN) strncat (argD[10], ".BIN", cLPF - 1 - strlen (argD[10]) ) ;
        }
        /* TAPc>0, KHXc>0 special needs for tap or khx format are implemented here */
        if (KHXc > 0) {
            khx_ver = strtod (argD[15], &ptrErr) ;
            if ((*ptrErr != 0) || 0.1001 > khx_ver || khx_ver > 6553.4) {
                printf ("%s: Khx version %s is not supported.\n", argP, argD[15]) ;
                MoreInfo (ERR_ARG);
            }
            else KHXc = (uint) (khx_ver * 10.0001) ;
            if (pcgrpId == GRP_16 || pcgrpId == GRP_G || pcgrpId == GRP_E) // || pcgrpId == IDENT_PC1500
                debug |= SYNC_KHX_OFF ;          /* spaces and long/short intro bits are not supported*/
        }
        /* replace all placeholders for special chars [00] in the name */
        for ( jj = 0 ; jj < 0x102 ; ++jj) {
            if (strchr(argD[10], '[') == NULL) break ;

            if (jj=='[' || jj==']') continue ; /* replace this chars finally */
            else if (jj==0x100)
                ii=']' ;
            else if (jj==0x101)
                ii='[' ;
            else
                ii = jj ;

            tmpl = ii>>4 ;
            if (tmpl > 9) spec_str[1] = tmpl + 0x37 ; else spec_str[1] = tmpl | 0x30 ;
            tmpl = ii & 0x0F ;
            if (tmpl > 9) spec_str[2] = tmpl + 0x37 ; else spec_str[2] = tmpl | 0x30 ;
            spec_chr[0] = ii ;
            replace_str(argD[10], spec_str, spec_chr);
        }
        if ((debug & BAS_EOF_INCL )>0 && (type == TYPE_IMG || type == TYPE_TXT ||
                                          type == TYPE_BAS || type == TYPE_ASC )) ++SHCe ;
        if (Qcnt != 0 ) debug &= ( 0xFFFF1F ) ; /* mask debug traces */
        if (type == TYPE_VAR) {
            debug |= NO_FILE_HEAD ;
            type = TYPE_DAT ;
        }
        else if (cnvstr_upr == true) (void) strupr (argD[10]) ;          /* Uppercase the name*/
                                        /*cnvstr_upr used to adapt the byte writing mode also*/
        /* Call the Convert function */
        error = ConvertBinToWav (argD[0], argD[1], argD[2], type, flags, addr, eaddr, sync, syncS, argD[10], debug) ;

    } while (0) ;
    if (error != ERR_OK && error != ERR_NOK) {
            if (debug != 0) printf ("Exit with error %d\n", error) ;
            return (error) ; // For debugging set here a breakpoint and in MoreInfo
    }
    else return (EXIT_SUCCESS) ;
}
