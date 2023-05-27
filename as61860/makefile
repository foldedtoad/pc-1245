######################################################################
#  Makefile
#		LINUX Version
#		=============
#
#   30 November 2018			Created for LINUX     / make /
#
######################################################################

.PHONY:	all clean prep

all: as61860
	
clean:
	rm -f as61860
	rm -f *.o
	rm -f $(SRCASX)*.o
	rm -f $(SRCMISC)*.o
	rm -f $(BUILD)/as61860

CC=			gcc
CCOPT=		-O3
CCFLAGS=	-Wall -funsigned-char $(CCOPT)

LD=			gcc
LDFLAGS=	-Wall

# Set ASXBASE relative to this make file.

ASXBASE:=	./
ASXBUILD:=	./

SRCASX:=	$(ASXBASE)asxxsrc/
SRCMISC:=	$(ASXBASE)asxxmisc/
BUILD:=		$(ASXBUILD)build/

SRC61860=	$(ASXBASE)

.SUFFIXES:	.c .o

%.o: %.c
	$(CC) $(CCFLAGS) -I$(SRCMISC) -I$(SRCASX) -c $< -o $@


ASXX =	asdata.o asexpr.o aslex.o aslist.o	\
	asmain.o asmcro.o asout.o assubr.o	\
	assym.o	asdbg.o

ASXXSRC =	$(addprefix $(SRCASX),$(ASXX))

$(ASXXSRC):	$(SRCMISC)alloc.h $(SRCASX)asxxxx.h


####################################################################
# AS61860
####################################################################

AS61860 =	s6186adr.o s6186mch.o s6186pst.o

AS61860SRC =	$(addprefix $(SRC61860),$(AS61860))

$(AS61860SRC):	$(SRCMISC)alloc.h $(SRCASX)asxxxx.h $(SRC61860)s61860.h

as61860: $(ASXXSRC) $(AS61860SRC)
	$(LD) $(LDFLAGS) $(ASXXSRC) $(AS61860SRC) -o as61860
	cp as61860 $(BUILD)as61860
	strip $(BUILD)as61860
	chmod 755 $(BUILD)as61860

### end ############################################################
