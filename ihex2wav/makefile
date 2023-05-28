####################################################################
#  Makefile
#		Linux 'GNU make' Version
#		========================
#
#  24  March  2003
#
####################################################################

BLDDIR:=    ./build

IHEXCONV = ihex2wav

####################################################################
# Special
####################################################################

.PHONY:	all clean

all:	$(BLDDIR) $(IHEXCONV)

clean:
	rm -f *.o
	rm -f $(BLDDIR)/ihex2wav

####################################################################
# Option Definitions
####################################################################

CC=			gcc
CCOPT=		-O3
CCFLAGS=	-Wall -funsigned-char $(CCOPT)

LD=			gcc
LDFLAGS=	-Wall

####################################################################

blddir: 
	mkdir -p $(BLDDIR)

####################################################################
# IHXCONV FILES
####################################################################

IHEX2WAV = ihex2wav.o ihexconv.o

ihex2wav.o : $(SRC)ihex2wav.c $(SRC)ihexconv.h
		$(CC) $(CCFLAGS) -c $< -o $(@F)

ihexconv.o : $(SRC)ihexconv.c $(SRCASX)ihexconv.h
		$(CC) $(CCFLAGS) -c $< -o $(@F)

ihex2wav :	$(IHEX2WAV)
		$(LD) $(LDFLAGS) -o $(BLDDIR)/ihex2wav $(IHEX2WAV)
		strip $(BLDDIR)/ihex2wav


### end #########################################################


