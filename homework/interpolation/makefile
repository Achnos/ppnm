CC		  =  gcc
PIPE    =  cat
LDLIBS  =  -lm
INPUT   =  exp_tabulated.txt
OUTPUT  =  spline_output.txt
EXECS   =  main
OBJCTS  =  main.o linSpline.o binarySearch.o inputToArray.o
HDRS    =  linSpline.h binarySearch.h
IMGFLS  =  spline_plot.png

.PHONEY: default
default: $(IMGFLS)

spline_plot.png: spline_plot.gpi spline_output.txt exp_tabulated.txt
	pyxplot $<

$(OUTPUT): $(EXECS) $(INPUT)
	./$< $(INPUT) $(OUTPUT)

$(EXECS): $(OBJCTS) $(HDRS)

clean:
	$(RM) $(EXECS) $(OUTPUT) $(OBJCTS) $(IMGFLS)
