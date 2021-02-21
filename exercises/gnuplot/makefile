CFLAGS     =  -O -Wall -std=gnu11 $(shell gsl-config --cflags)
LDLIBS     =  $(shell gsl-config --libs)
IMGFLS     =  gnuplot_erf.png pyxplot_erf.png pyxplot_tgamma.png #graph_erf.png
EXECS      =  main
TXTS       =  output_data_erf.txt output_data_tgamma.txt err_data.txt
OBJECTS    =  main.o myErf.o myTGamma.o
HDRS     	 =  myErf.h myTGamma.h
TMP 		   =  tmp_script_gnu2pyx_erf.gpi
RMTARGETS  =  $(EXECS) $(OBJECTS) $(IMGFLS) $(TXTS) tmp_script_gnu2pyx_erf.gpi


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

pyxplot_erf.png: tmp_script_gnu2pyx_erf.gpi
	cat $< | sed 's/gnuplot/pyxplot/' | pyxplot

gnuplot_erf.png: output_data_erf.txt tabulated_data_erf.txt
	echo '\
	set terminal png;\
	set output "$@";\
	set key bottom right;\
	set tics in;\
	set xlabel "Query points (X data)";\
	set ylabel "Function value at query points (Y data)";\
	set title "Error function, erf(x)";\
	plot \
	 "$<" using 1:2 with line lw 2 title "erf(x) from math.h"\
	,"$<" using 1:3 with line lw 2 title "erf(x) from gsl-sf-erf"\
	,"$<" using 1:4 with line lw 2 title "myErf(x)"\
	,"tabulated_data_erf.txt" using 1:2 with points pointtype 4 title "Tabulated data"\
	' | tee tmp_script_gnu2pyx_erf.gpi | gnuplot

pyxplot_tgamma.png: output_data_tgamma.txt tabulated_data_tgamma.txt
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
	 "$<" using 1:2 with line lw 2 title "tgamma(x) (math.h)"\
	,"$<" using 1:3 with line lw 2 title "gamma(x) (gsl-sf-gamma)"\
	,"$<" using 1:4 with line lw 2 title "myTGamma(x)"\
	,"tabulated_data_tgamma.txt" using 1:2 with points pointtype 4 title "Tabulated data"\
	' | pyxplot

tmp_script_gnu2pyx_erf.gpi: gnuplot_erf.png
	touch $@

$(TXTS): $(EXECS)
	./$< output_data_erf.txt output_data_tgamma.txt 2> err_data.txt

$(EXECS): $(OBJECTS)
$(OBJECTS): $(HDRS)

.PHONEY: clean
clean:
	$(RM) $(RMTARGETS)
