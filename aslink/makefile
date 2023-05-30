######################################################################
#  Makefile
#		LINUX Version
#		=============
#
#   30 November 2018			Created for LINUX     / make /
#
######################################################################

ASXBASE:=	.
BLDDIR:=    ./build

CC=			gcc
CCOPT=		-O3
CCFLAGS=	-Wall -funsigned-char $(CCOPT)
#CCFLAGS+=	-save-temps

LD=			gcc
LDFLAGS=	-Wall

#  Set ASXBASE relative to this makefile.

SRCLNK:=	$(ASXBASE)/
BUILD:=  	$(BLDDIR)/

.PHONY:	all clean

all: blddir $(BUILD)aslink

clean:
	rm -f *.o
	rm -f $(BUILD)aslink	

.SUFFIXES:	.c .o

%.o: %.c
	$(CC) $(CCFLAGS) -I$(SRCLNK) -c $< -o $@

####################################################################

blddir: 
	mkdir -p $(BLDDIR)

####################################################################
# ASLINK
####################################################################

ASLINK = lkmain.o lkhead.o lkarea.o lkbank.o	\
		lkdata.o lkeval.o lklex.o lklibr.o	\
		lklist.o lkrloc.o lkrloc3.o lkrloc4.o	\
		lksym.o lkout.o lknoice.o lksdcdb.o

ASLINKSRC =	$(addprefix $(SRCLNK),$(ASLINK))

$(ASLINK):	$(SRCLNK)alloc.h $(SRCLNK)aslink.h

$(BUILD)aslink: $(ASLINKSRC)
	$(LD) $(LDFLAGS) $(ASLINKSRC) -o $(BUILD)aslink
	strip $(BUILD)aslink
	chmod 755 $(BUILD)aslink

### end ############################################################
