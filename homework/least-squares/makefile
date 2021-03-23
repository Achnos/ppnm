CFLAGS 		 +=  $(shell gsl-config --cflags)
LDLIBS 		 +=  $(shell gsl-config --libs)
LDLIBS 		 +=  -lm -Wall

CC		  		=  gcc
PIPE     		=  cat

INPUT   		=  data.txt
OUTPUT      =  fit.txt
#LINOUT   		=  lin_spline_output.txt
#QUADOUT  		=  quad_spline_output.txt
#CUBICOUT  	=  cubic_spline_output.txt
EXE   	  	=  main
OBJ  	  		=  main.o gramSchmidt.o backsub.o input2Array.o
HDRS    	  =  gramSchmidt.h backsub.h input2Array.h
#IMGFLS  	  =  lin_spline_plot.png quad_spline_plot.png cubic_spline_plot.png
TXT     		=  output.txt

.PHONEY: default
default: print #$(IMGFLS)

print: $(TXT)
	$(PIPE) $<

#lin_spline_plot.png: lin_spline_plot.gpi lin_spline_output.txt cos_tabulated.txt
#	pyxplot $<

#quad_spline_plot.png: quad_spline_plot.gpi quad_spline_output.txt cos_tabulated.txt
#	pyxplot $<

#cubic_spline_plot.png: cubic_spline_plot.gpi cubic_spline_output.txt cos_tabulated.txt
#	pyxplot $<

$(TXT) : $(EXE) $(INPUT)
	./$< $(INPUT) $(OUTPUT) 1> $(TXT)

#$(LINOUT) $(QUADOUT) $(CUBICOUT)
#$(INPUT) $(LINOUT) $(QUADOUT) $(CUBICOUT)

$(EXE): $(OBJ) $(HDRS)

clean:
	$(RM) $(EXE) $(TXT) # $(OUTPUT) $(OBJ) $(IMGFLS)
