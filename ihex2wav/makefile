####################################################################
#  Makefile
#		Linux 'GNU make' Version
#		========================
#
#  24  March  2003
#
####################################################################

IHEXCONV = ihex2wav

####################################################################
# Special
####################################################################

.PHONY:	all clean

all:	$(IHEXCONV)

clean:
	rm -fv *.o
	rm -fv ihex2wav

####################################################################
# Option Definitions
####################################################################

CC=		gcc
CCOPT=		-O3
CCFLAGS=	-Wall -funsigned-char $(CCOPT)

LD=		gcc
LDFLAGS=	-Wall


####################################################################
# IHEXCONV Directories
####################################################################

#  Set RELDIR relative to this make file.

RELDIR=		.

SRC=		$(RELDIR)/
DSTEXE=		./

####################################################################
# IHXCONV FILES
####################################################################

IHEX2WAV = ihex2wav.o ihexconv.o

ihex2wav.o : $(SRC)ihex2wav.c $(SRC)ihexconv.h
		$(CC) $(CCFLAGS) -c $< -o $(@F)

ihexconv.o : $(SRC)ihexconv.c $(SRCASX)ihexconv.h
		$(CC) $(CCFLAGS) -c $< -o $(@F)

ihex2wav :	$(IHEX2WAV)
		$(LD) $(LDFLAGS) -o $(DSTEXE)ihex2wav $(IHEX2WAV)
		strip $(DSTEXE)ihex2wav


### end #########################################################


