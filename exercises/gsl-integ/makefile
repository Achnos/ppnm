CFLAGS = -Wall -O1 $(shell gsl-config --cflags)
LDLIBS += $(shell gsl-config --libs)
CC = gcc

OUTPUTFLS = output_lnxsqrtx.txt output_erfint.txt output_besselint.txt
ERRORFL = error.txt
EXECS = main
OBJECTS = main.o lnXsqrtX.o erfint.o besselint.o
HDRS = lnXsqrtX.h erfint.h besselint.h
PLOTFL = integrated_error_function_plot.png integrated_bessel_function_plot.png

default: $(OUTPUTFLS) $(PLOTFL)
	cat output_lnxsqrtx.txt

integrated_error_function_plot.png: output_erfint.txt
	echo '\
	set terminal png;\
	set output "$@";\
	set key bottom right;\
	set tics in;\
	set fontsize 0.7;\
	set xlabel "Query points (X data)";\
	set ylabel "Function value at query points (Y data)";\
	set title "erf(x) from integral rep.";\
	plot \
	"$<" using 1:3 with line lw 6 col PineGreen title "erf(x) (math.h)"\
	, "$<" using 1:2 with line lw 2 col Seagreen title "My erf(x)"\
	' | pyxplot

integrated_bessel_function_plot.png: output_besselint.txt
	echo '\
	set terminal png;\
	set output "$@";\
	set key top right;\
	set tics in;\
	set fontsize 0.7;\
	set xlabel "Query points (X data)";\
	set ylabel "Function value at query points (Y data)";\
	set title "Jn(x) from integral rep.";\
	plot \
	"$<" using 1:2 with line lw 2 col RubineRed title "J0(x)"\
	,"$<" using 1:3 with line lw 2 col Seagreen title "J1(x)"\
	,"$<" using 1:4 with line lw 2 col ProcessBlue title "J2(x)"\
	' | pyxplot

$(OUTPUTFLS): $(EXECS)
	./$< $(OUTPUTFLS)

$(EXECS): $(OBJECTS)

$(OBJECTS): $(HDRS)

clean:
	$(RM) $(OUTPUTFLS) $(EXECS) $(OBJECTS) $(PLOTFL) $(ERRORFL)
