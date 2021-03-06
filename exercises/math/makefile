# This is a makefile.
# make is a utillity to manage project in computer filesystems, where objects are manipulated according to certain rules. A makefile should always have the name 'makefile' otherwise it must,
# if it is called SomethingElse, the make utility is called with 'make -f SomethingElse'.
# When make is run it automatically reads the descriptions in the makefile and updates the project if  necessary.

### Macro definitions
# A macro definition looks like a normal assignment in a programming language,

CC       =  gcc
CFLAGS   =  -Wall # This is a macro definition
LDFLAGS  =  -lm
# The macro can be called as $(CFLAGS) and will return the string "-Wall -std=gnu99".


### Rules
# A rule looks very much like an instruction for preparing a dish. It has the following syntax,
# dish : ingredients
# ⊣ recipe
# or
# target : prerequisites
# 	recipe
# By default make only builds the first target, so one usually defines a PHONEY target to handle  more than one targets, that depends on the targets that must be built by default.

#.PHONEY: default
#	default : target1 target2 target3

default : out.txt
	cat out.txt

out.txt : math                 # math.txt depends on math
	./$< > $@       # this is how you make out.txt from math
              		       # This target basically runs the program and sends it into a .txt file called out.txt

math : math.o       	       		# math depends on math.o
	$(CC) $< -o $@ $(CFLAGS) $(LDFLAGS)    # Now we link the object file to an output program ('-o') called math.

math.o : math.c      	       # math.o depends on math.c
	$(CC) -c $<          # '-c' flag means compile only and do not link.

.PHONEY: clean
clean:                 	       # this is "clean" target it does not depend on anything
	rm -f out.txt math math.o
