CFLAGS +=  $(shell gsl-config --cflags)
LDLIBS +=  $(shell gsl-config --libs)
LDLIBS +=  -lm -Wall

CC   	=  gcc
PIPE    =  cat

EXE   	=  main
OBJ  	=  main.o integration_tri.o # functions.o
HDRS    =  integration_tri.h #functions.h
TXT     =  output.txt

.PHONEY: default
default: print

print: $(TXT)
	$(PIPE) $<

$(TXT) : $(EXE)
	./$< 1> $(TXT)

$(EXE): $(OBJ) $(HDRS)

clean:
	$(RM) $(EXE) $(TXT) $(OBJ)
