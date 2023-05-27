/***************************************************************************
                          ihxconv.h 

Intel Hex to WAV and Basic conversion for Sharp pocket computers

                             -------------------
    begin                : 2003.04.17
    copyright            : (C) 2003 by Edgar Puehringer
    email                : edgar_pue@yahoo.com
    modifications        : 2004.05.07 conversion function for destroyed
                           lolo's emulator added
                           2004.10.16 conversion function for POEMS
                           emulator added
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef __IHEXCONV_H__
#define __IHEXCONV_H__

#include <stdio.h>

#define MODE_WAV_OLD 0
#define MODE_WAV_NEW 1
#define MODE_COMPACT_STD 2
#define MODE_COMPACT_STUB 3
#define MODE_BASIC_STD 4
#define MODE_BASIC_STUB 5
#define MODE_LOLO 6
#define MODE_POEM 7

#define MODEL_1245 1
#define MODEL_1250 2
#define MODEL_1251 3
#define MODEL_1255 4
#define MODEL_1260 5
#define MODEL_1261 6
#define MODEL_1262 7
#define MODEL_1350 8

int ihexconv(FILE * srcfile, FILE * outfile, int mode, FILE * romfile, int model); 

#endif
