######################################################################
#  Makefile
#		LINUX Version
#		=============
######################################################################
BLDDIR:= ./build

all: blddir bas2img bin2wav wav2bin

blddir: 
	mkdir -p $(BLDDIR)

bas2img: bas2img_611c1d2.c 
	 gcc -Wall -o $(BLDDIR)/bas2img bas2img_611c1d2.c

bin2wav: bin2wav_211c1d2.c
	 gcc -Wall -o $(BLDDIR)/bin2wav bin2wav_211c1d2.c

wav2bin: wav2bin_211c1d2.c
	 gcc -Wall -o $(BLDDIR)/wav2bin wav2bin_211c1d2.c
	 
clean: 
	 rm $(BLDDIR)/bas2img $(BLDDIR)/bin2wav $(BLDDIR)/wav2bin
