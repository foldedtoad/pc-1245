# Intel Hex to WAV file converter
Version: 0.8.1
Author:  Edgar Puehringer
Date:    2004.05.07

These tools were made to get the output of the ASXXXX/ASLINK assembler/linker into some old Sharp pocket computers.  
Most of the models PC-12XX, PC-13XX and PC-14XX are supported.

"**ihex2wav**" converts to a WAV file. You can transfer the resulting file to your pocket computer using the tape interface connected to your sound card. 

```
  usage: ihex2wav [-old] [-o wavfile] [ihexfile]
```

The "**-old**" parameter must be specified for some older models of the PC-12XX series (I think PC-124X and PC-125X).

## Building an Executeable
You need GNU make and a C compiler. Just make the directory containing 'makefile' the current directory and type 'make'.

Should work on any platform (Linux with gcc v3.2.2 or later)

## Copying
GNU public licence, see 'COPYING' for details

## Thanks to
Yagshi (http://www-matsuo-lab.ctrl.titech.ac.jp/~hkoba/pocketcom/index.html) for his Yagshi's SC61860 assembler which showed me how to create WAV files for Sharp pocket computers.
