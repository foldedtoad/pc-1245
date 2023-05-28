######################################################################
#  Makefile
#		LINUX Version
#		=============
#
#   30 November 2018			Created for LINUX     / make /
#
######################################################################

ASXBASE:=	./
BLDDIR:=	./build

CC=			gcc
CCOPT=		-O3
CCFLAGS=	-Wall -funsigned-char $(CCOPT)

LD=			gcc
LDFLAGS=	-Wall

#  Set ASXBASE relative to this makefile.

SRCASX:=	$(ASXBASE)asxxsrc
BUILD:=		$(BLDDIR)

.PHONY:	all clean

all: blddir $(BUILD)/asxscn

clean:
	rm -f *.o
	rm -f $(SRCASX)/*.o
	rm -f $(BUILD)/asxxscn

.SUFFIXES:	.c .o

%.o: %.c
	$(CC) $(CCFLAGS) -I$(SRCASX) -c $< -o $@

####################################################################

ASXX =	asdata.o asexpr.o aslex.o aslist.o	\
	asmain.o asmcro.o asout.o assubr.o	\
	assym.o	asdbg.o

ASXXSRC =	$(addprefix $(SRCASX),$(ASXX))

$(ASXXSRC):	$(ASXBASE)/alloc.h $(SRCASX)asxxxx.h

####################################################################

blddir: 
	mkdir -p $(BLDDIR)

####################################################################
# ASXSCN
####################################################################

$(SRCMISC)asxxscan.o:	$(ASXBASE)asxxxx.h

$(BUILD)/asxscn:	$(ASXBASE)/asxxscan.o
	$(LD) $(LDFLAGS) $(SRCMISC)asxxscan.o -o $(BUILD)/asxscn
	strip $(BUILD)/asxscn
	chmod 755 $(BUILD)/asxscn

### end ############################################################


