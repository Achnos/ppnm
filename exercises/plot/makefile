CFLAGS     =  -O -Wall -std=gnu11 $(shell gsl-config --cflags)
LDLIBS     =  $(shell gsl-config --libs)
IMGFLS     =  gnuplot_erf_plot.png erf_plot.png true_gamma_func_plot.png log_of_gamma_func_plot.png complex_gamma_func_plot.png #graph_erf.png
EXECS      =  main
TXTS       =  output_data_erf.txt output_data_tgamma.txt output_data_lgamma.txt output_data_cgamma.txt err_data.txt
OBJECTS    =  main.o myErf.o myTGamma.o myComplexGamma.o
HDRS     	 =  myErf.h myTGamma.h myComplexGamma.h
TMP 		   =  tmp_script_pyx2gnu_erf.gpi
RMTARGETS  =  $(EXECS) $(OBJECTS) $(IMGFLS) $(TXTS) $(TMP)


.PHONEY: default
default: $(IMGFLS)

# graph_erf.png: output_data_erf.txt tabulated_data_erf.txt
#	awk '{print $$1, $$2}' $< > line1
#	awk '{print $$1, $$3}' $< > line2
#	awk '{print $$1, $$4}' $< > line3
#	awk '{print $$1, $$2}' tabulated_data_erf.txt > line4
#	graph \
#	--output-format png --bitmap-size 1024x768 \
#	--x-label "x" --y-label "y" \
#	--top-label "Error function" \
#	--line-mode 1 line1 \
#	--line-mode 2 line2 \
#	--line-mode 3 line3 \
#	--symbol 4 line4 \
#	> $@
#	$(RM) line*

gnuplot_erf_plot.png: tmp_script_pyx2gnu_erf.gpi
	cat $< | sed 's/pyxplot/gnuplot' | gnuplot

erf_plot.png: output_data_erf.txt tabulated_data_erf.txt
	echo '\
	set terminal png;\
	set output "$@";\
	set key bottom right;\
	set tics in;\
	set xlabel "Query points (X data)";\
	set ylabel "Function value at query points (Y data)";\
	set title "Error function, erf(x)";\
	plot \
	 "$<" using 1:2 with line lw 2 col Black title "erf(x) from math.h"\
	,"$<" using 1:3 with line lw 2 col Seagreen title "erf(x) from gsl-sf-erf"\
	,"$<" using 1:4 with line lw 2 col MidnightBlue title "myErf(x)"\
	,"tabulated_data_erf.txt" using 1:2 with points col ProcessBlue pointtype 4 title "Tabulated data"\
	' | tee tmp_script_pyx2gnu_erf.gpi | pyxplot

true_gamma_func_plot.png: output_data_tgamma.txt tabulated_data_tgamma.txt
	echo '\
	set terminal png;\
	set output "$@";\
	set key bottom right;\
	set tics in;\
	set fontsize 0.7;\
	set xlabel "Query points (X data)";\
	set ylabel "Function value at query points (Y data)";\
	set title "True gamma function, tgamma(x)";\
	plot \
	 "$<" using 1:2 with line lw 2 col Black title "tgamma(x) (math.h)"\
	,"$<" using 1:3 with line lw 2 col Seagreen title "gamma(x) (gsl-sf-gamma)"\
	,"$<" using 1:4 with line lw 2 col MidnightBlue title "myTGamma(x)"\
	,"tabulated_data_tgamma.txt" using 1:2 with points col ProcessBlue pointtype 4 title "Tabulated data"\
	' | pyxplot

log_of_gamma_func_plot.png: output_data_lgamma.txt tabulated_data_lgamma.txt
	echo '\
	set terminal png;\
	set output "$@";\
	set key top left;\
	set tics in;\
	set fontsize 0.7;\
	set xlabel "Query points (X data)";\
	set ylabel "Function value at query points (Y data)";\
	set title "Log of the gamma function, lgamma(x)";\
	plot \
	 "$<" using 1:2 with line col Black lw 2 title "lgamma(x) (math.h)"\
	,"$<" using 1:3 with line col Seagreen lw 2 title "lgamma(x) (gsl-sf-gamma)"\
	,"$<" using 1:4 with line col MidnightBlue lw 2 title "ln(myTGamma(x))"\
	,"tabulated_data_lgamma.txt" using 1:2 with points col ProcessBlue pointtype 4 title "Tabulated data"\
	' | pyxplot

WIDTH = 4.2

complex_gamma_func_plot.png: output_data_cgamma.txt
	echo '\
	set numerics complex;\
	set numeric display latex;\
	set preamble \usepackage{amsmath};\
	set terminal png;\
	set output "$@";\
	set nokey;\
	set nogrid;\
	set xlabel "Re(z)";\
	set ylabel """ Im(z)""";\
	set zlabel " abs(Gamma(z)) ";\
	set title "Absolute value of complex Gamma function";\
	set xrange [-$(WIDTH):$(WIDTH)];\
	set yrange [-$(WIDTH):$(WIDTH)];\
	set zrange [0:6];\
	set xtics -4,1,4 ; set mxtics 1;\
	set ytics -4,1,4 ; set mytics 1;\
	set ztics 1 ; set mztics 1;\
	set size 6 square;\
	set view -50, 20;\
	set samples grid 120x120;\
	plot 3d "output_data_cgamma.txt" using 1:2:3 with surface col MidnightBlue fillc ProcessBlue;\
	' | pyxplot


$(TMP): erf_plot.png
	touch $@

$(TXTS): $(EXECS)
	./$< output_data_erf.txt output_data_tgamma.txt output_data_lgamma.txt output_data_cgamma.txt 2> err_data.txt

$(EXECS): $(OBJECTS)
$(OBJECTS): $(HDRS)

.PHONEY: clean
clean:
	$(RM) $(RMTARGETS)
