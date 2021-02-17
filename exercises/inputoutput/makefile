CC		  =  gcc
LDLIBS  =  -lm
ARGS    =  1 2 3 4 5  # If passing arguments directly, instead of from input.txt
INPUT   =  input.txt
PIPE    =  cat
TXTS    =  out_cmdlread.txt err_cmdlread.txt out_stdinread.txt err_stdinread.txt out_fileread.txt err_fileread.txt
EXECS   =  cmdlread stdinread fileread

default: $(TXTS)
	$(PIPE) out_cmdlread.txt
	$(PIPE) err_cmdlread.txt
	$(PIPE) out_stdinread.txt
	$(PIPE) err_stdinread.txt
	$(PIPE) out_fileread.txt
	$(PIPE) err_fileread.txt


$(TXTS): $(EXECS) $(INPUT)
	./cmdlread  $$(cat input.txt)  1> out_cmdlread.txt  2> err_cmdlread.txt
	$(PIPE) $(INPUT) | ./stdinread 1> out_stdinread.txt 2> err_stdinread.txt
	./fileread $(INPUT) out_fileread.txt 			  				2> err_fileread.txt


clean:
	$(RM) $(EXECS) $(TXTS)
