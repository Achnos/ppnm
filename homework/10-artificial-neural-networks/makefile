CFLAGS +=  $(shell gsl-config --cflags)
LDLIBS +=  $(shell gsl-config --libs)
LDLIBS +=  -lm -Wall

CC   	=  gcc
PIPE    =  cat
PLTUTIL =  pyxplot

EXE   	=  main
OBJ  	=  main.o neuralnetwork.o minimization.o utilities.o input2Array.o
HDRS    =  neuralnetwork.h minimization.h utilities.h input2Array.h
TXT     =  output.txt
DATA    =  cos_tabulated.txt predictions.txt
GPI     =  predictions.gpi
IMGFL   =  predictions.png

.PHONEY: default
default: print $(IMGFL)

$(IMGFL): $(GPI) predictions.txt
	pyxplot $<

print: $(TXT)
#	$(PIPE) $<

$(TXT) : $(EXE)
	./$< $(DATA) #1> $(TXT)

$(EXE): $(OBJ) $(HDRS)

clean:
	$(RM) $(EXE) $(TXT) $(OBJ)
