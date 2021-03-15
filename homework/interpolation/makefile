CFLAGS +=  $(shell gsl-config --cflags)
LDLIBS +=  $(shell gsl-config --libs)
CC		  =  gcc
PIPE    =  cat
LDLIBS +=  -lm
INPUT   =  cos_tabulated.txt
OUTPUT  =  spline_output.txt
EXECS   =  main
OBJCTS  =  main.o linSpline.o binarySearch.o inputToArray.o gslIntFunc.o quadSpline.o
HDRS    =  linSpline.h binarySearch.h gslIntFunc.h quadSpline.h
IMGFLS  =  spline_plot.png
TXT     =  output.txt

.PHONEY: default
default: $(IMGFLS) print

print: $(TXT)
	$(PIPE) $<

spline_plot.png: spline_plot.gpi spline_output.txt cos_tabulated.txt
	pyxplot $<

$(OUTPUT) $(TXT): $(EXECS) $(INPUT)
	./$< $(INPUT) $(OUTPUT) 1> $(TXT)

$(EXECS): $(OBJCTS) $(HDRS)

clean:
	$(RM) $(EXECS) $(OUTPUT) $(OBJCTS) $(IMGFLS) $(TXT)
