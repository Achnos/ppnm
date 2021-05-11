CFLAGS +=  $(shell gsl-config --cflags)
LDLIBS +=  $(shell gsl-config --libs)
LDLIBS +=  -lm -Wall

CC   	=  gcc
PIPE    =  cat
PLTUTIL =  pyxplot

EXE   	=  main
OBJ  	=  main.o minimization.o input2Array.o
HDRS    =  minimization.h input2Array.h
TXT     =  output.txt
IMGFL   =  higgs_fit.png
GPI     =  higgs_fit.gpi
DATA    =  higgs_fit.txt

.PHONEY: default
default: print $(IMGFL)

higgs_fit.png: $(GPI) $(DATA)
	pyxplot $<

print: $(TXT)
#	$(PIPE) $<

$(TXT) : $(EXE)
	./$< $(DATA) #1> $(TXT)

$(EXE): $(OBJ) $(HDRS)

clean:
	$(RM) $(EXE) $(TXT) $(OBJ)
