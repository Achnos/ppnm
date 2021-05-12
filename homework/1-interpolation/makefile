CFLAGS 		 +=  $(shell gsl-config --cflags)
LDLIBS 		 +=  $(shell gsl-config --libs)
LDLIBS 		 +=  -lm -Wall

CC		  		=  gcc
PIPE     		=  cat

INPUT   		=  cos_tabulated.txt
LINOUT   		=  lin_spline_output.txt
QUADOUT  		=  quad_spline_output.txt
CUBICOUT  	=  cubic_spline_output.txt
EXE   	  	=  main
OBJ  	  		=  main.o linSpline.o integrateFunction.o quadSpline.o cubicSpline.o utilities.o
HDRS    	  =  linSpline.h integrateFunction.h quadSpline.h cubicSpline.h utilities.h
IMGFLS  	  =  lin_spline_plot.png quad_spline_plot.png cubic_spline_plot.png
TXT     		=  output.txt

.PHONEY: default
default: $(IMGFLS) print

print: $(TXT)
	$(PIPE) $<

lin_spline_plot.png: lin_spline_plot.gpi lin_spline_output.txt cos_tabulated.txt
	pyxplot $<

quad_spline_plot.png: quad_spline_plot.gpi quad_spline_output.txt cos_tabulated.txt
	pyxplot $<

cubic_spline_plot.png: cubic_spline_plot.gpi cubic_spline_output.txt cos_tabulated.txt
	pyxplot $<

$(LINOUT) $(QUADOUT) $(CUBICOUT) $(TXT): $(EXE) $(INPUT)
	./$< $(INPUT) $(LINOUT) $(QUADOUT) $(CUBICOUT) 1> $(TXT)

$(EXE): $(OBJ) $(HDRS)

clean:
	$(RM) $(EXE) $(OUTPUT) $(OBJ) $(IMGFLS) $(TXT)
