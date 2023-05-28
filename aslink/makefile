######################################################################
#  Makefile
#		LINUX Version
#		=============
#
#   30 November 2018			Created for LINUX     / make /
#
######################################################################

.PHONY:	all clean

all: aslink

clean:
	rm -f aslink
	rm -f *.o
	rm -f $(SRCASX)*.o
	rm -f $(SRCMISC)*.o
	rm -f $(BUILD)aslink	

CC=			gcc
CCOPT=		-O3
CCFLAGS=	-Wall -funsigned-char $(CCOPT)

LD=			gcc
LDFLAGS=	-Wall

#  Set ASXBASE relative to this make file.

ASXBASE:=	.
ASXBUILD:=	./build

SRCLNK:=	$(ASXBASE)/
SRCASX:=	$(ASXBASE)/asxxsrc/
SRCMISC:=	$(ASXBASE)/asxxmisc/
BUILD:=  	$(ASXBUILD)/

.SUFFIXES:	.c .o

%.o: %.c
	$(CC) $(CCFLAGS) -I$(SRCMISC) -I$(SRCASX) -c $< -o $@

ASXX =	asdata.o asexpr.o aslex.o aslist.o	\
	asmain.o asmcro.o asout.o assubr.o	\
	assym.o	asdbg.o

ASXXSRC =	$(addprefix $(SRCASX),$(ASXX))

$(ASXXSRC):	$(SRCMISC)alloc.h asxxxx.h

####################################################################
# ASLINK
####################################################################

ASLINK = lkmain.o lkhead.o lkarea.o lkbank.o	\
		lkdata.o lkeval.o lklex.o lklibr.o	\
		lklist.o lkrloc.o lkrloc3.o lkrloc4.o	\
		lksym.o lkout.o lknoice.o lksdcdb.o

ASLINKSRC =	$(addprefix $(SRCLNK),$(ASLINK))

$(ASLINK):	$(SRCMISC)alloc.h $(SRCLNK)aslink.h

aslink: $(ASLINKSRC)
	$(LD) $(LDFLAGS) $(ASLINKSRC) -o aslink
	cp aslink $(BUILD)aslink
	strip $(BUILD)aslink
	chmod 755 $(BUILD)aslink

### end ############################################################


