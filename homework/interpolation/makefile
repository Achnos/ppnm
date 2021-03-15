CFLAGS 		 +=  $(shell gsl-config --cflags)
LDLIBS 		 +=  $(shell gsl-config --libs)
CC		  		=  gcc
PIPE     		=  cat
LDLIBS 		 +=  -lm
INPUT   		=  cos_tabulated.txt
LINOUTPUT   =  lin_spline_output.txt
QUADOUTPUT  =  quad_spline_output.txt
EXECS   	  =  main
OBJCTS  	  =  main.o linSpline.o binarySearch.o inputToArray.o gslIntFunc.o quadSpline.o
HDRS    	  =  linSpline.h binarySearch.h gslIntFunc.h quadSpline.h
IMGFLS  	  =  lin_spline_plot.png quad_spline_plot.png
TXT     		=  output.txt

.PHONEY: default
default: $(IMGFLS) print

print: $(TXT)
	$(PIPE) $<

lin_spline_plot.png: lin_spline_plot.gpi lin_spline_output.txt cos_tabulated.txt
	pyxplot $<

quad_spline_plot.png: quad_spline_plot.gpi quad_spline_output.txt cos_tabulated.txt
	pyxplot $<

$(LINOUTPUT) $(TXT): $(EXECS) $(INPUT)
	./$< $(INPUT) $(LINOUTPUT) $(QUADOUTPUT) 1> $(TXT)

$(EXECS): $(OBJCTS) $(HDRS)

clean:
	$(RM) $(EXECS) $(OUTPUT) $(OBJCTS) $(IMGFLS) $(TXT)
