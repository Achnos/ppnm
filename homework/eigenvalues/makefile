CFLAGS +=  $(shell gsl-config --cflags)
LDLIBS +=  $(shell gsl-config --libs)
LDLIBS +=  -lm -Wall

CC   	=  gcc
PIPE    =  cat

INPUT   =  data.txt
OUTPUT  =  fit.plt
EXE   	=  main
OBJ  	=  main.o jacobi.o utilities.o
HDRS    =  jacobi.h utilities.h
IMGFL   =  fit.png
TXT     =  output.txt

.PHONEY: default
default: print

print: $(TXT)
	$(PIPE) $<

#$(IMGFL): fit.gpi $(INPUT) $(OUTPUT)
#	pyxplot $<

$(TXT) : $(EXE)
	./$< 1> $(TXT)

$(EXE): $(OBJ) $(HDRS)

clean:
	$(RM) $(EXE) $(TXT) $(OUTPUT) $(OBJ) $(IMGFL)
