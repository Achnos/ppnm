# This is a makefile. 
# make is a utillity to manage project in computer filesystems, where objects are manipulated according to certain rules. A makefile should always have the name 'makefile' otherwise it must,
# if it is called SomethingElse, the make utility is called with 'make -f SomethingElse'.
# When make is run it automatically reads the descriptions in the makefile and updates the project if  necessary. 

### Macro definitions
# A macro definition looks like a normal assignment in a programming language,

CFLAGS = -Wall -std=gnu99 # This is a macro definition
# The macro can be called as $(CFLAGS) and will return the string "-Wall -std=gnu99".


### Rules
# A rule looks very much like an instruction for preparing a dish. It has the following syntax,
# dish : ingredients
# ⊣ recipe
# or
# target : prerequisites
# 	recipe
# By default make only builds the first target, so one usually defines a PHONEY target to handle  more than one targets, that depends on the targets that must be built by default.

.PHONEY: default
	default : target1 target2 target3


out.txt : hello                # out.txt depends on hello
	./hello > out.txt      # this is how you make out.txt from hello
			       # This target basically runs the program and sends it into a .txt file called out.txt

hello : hello.o       	       # hello depends on hello.o
	gcc hello.o -o hello   # Now we link the object file to an output program ('-o') called hello. This is how you make hello from hello.o

hello.o : hello.c      	       # hello.o depends on hello.c
	gcc -c hello.c         # '-c' flag means compile only and do not lin. This is how you make hello.o from hello.c

.PHONEY: clean
clean:                 	       # this is "clean" target it does not depend on anything
	rm -f out.txt hello hello.o
