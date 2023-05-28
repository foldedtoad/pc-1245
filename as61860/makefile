######################################################################
#  Makefile
#		LINUX Version
#		=============
#
#   30 November 2018			Created for LINUX     / make /
#
######################################################################

ASXBASE:=	./
BLDDIR:=    ./build

CC=			gcc
CCOPT=		-O3
CCFLAGS=	-Wall -funsigned-char $(CCOPT)

LD=			gcc
LDFLAGS=	-Wall

# Set ASXBASE relative to this makefile.

SRCASX:=	$(ASXBASE)asxxsrc
BUILD:=		$(BLDDIR)

.PHONY:	all clean

all: blddir $(BUILD)/as61860
	
clean:
	rm -f *.o
	rm -f $(SRCASX)/*.o
	rm -f $(BUILD)as61860

.SUFFIXES:	.c .o

%.o: %.c
	$(CC) $(CCFLAGS) -I$(SRCASX) -c $< -o $@

####################################################################

SRC61860=	$(ASXBASE)

ASXX =	asdata.o asexpr.o aslex.o aslist.o	\
	asmain.o asmcro.o asout.o assubr.o	\
	assym.o	asdbg.o

ASXXSRC =	$(addprefix $(SRCASX)/,$(ASXX))

$(ASXXSRC):	alloc.h $(SRCASX)/asxxxx.h

####################################################################

blddir: 
	mkdir -p $(BLDDIR)

####################################################################
# AS61860
####################################################################

AS61860 = s6186adr.o s6186mch.o s6186pst.o

AS61860SRC = $(addprefix $(SRC61860),$(AS61860))

$(AS61860SRC): $(SRCASX)/asxxxx.h $(ASXBASE)/s61860.h

$(BUILD)/as61860: $(ASXXSRC) $(AS61860SRC)
	$(LD) $(LDFLAGS) $(ASXXSRC) $(AS61860SRC) -o $(BUILD)/as61860
	strip $(BUILD)/as61860
	chmod 755 $(BUILD)/as61860

### end ############################################################
