#############################################
# ----------------------------------------- #
# ---- This is a VERY GENERAL makefile ---- #
# ----------------------------------------- #
#############################################

# Marc Breiner Sørensen (February, 2021)


# --- ABOUT MAKEFILES, BASIC SYNTAX, MACRO DEFINITIONS, VARIABLES AND RULES ----------------------------------------------------------------------------------------------------------------------- #
# ---
# make is a utillity to manage project in computer filesystems, where objects are manipulated according to certain rules. A makefile should always have the name 'makefile' otherwise it must,
# if it is called SomethingElse, the make utility is called with 'make -f SomethingElse'.
# When make is run it automatically reads the descriptions in the makefile and updates the project if  necessary.
# ---
### Macro definitions
# A macro definition looks like a normal assignment in a programming language,
# ---
# CFLAGS = -Wall -lm # This is a macro definition
# ---
# The macro can be called as $(CFLAGS) and will return the string "-Wall -std=gnu99".
# ---
# ---
### Rules
# A rule looks very much like an instruction for preparing a dish. It has the following syntax,
# dish : ingredients
# ⊣ recipe
# or
# target : prerequisites
# 	recipe
# By default make only builds the first target, so one usually defines a PHONEY target to handle  more than one targets, that depends on the targets that must be built by default.
# ---
# .PHONEY: default
# 	default : target1 target2 target3
# ---
# --- END ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- #



# --- SPECIFY COMPILER FLAGS  --- #
CFLAGS      =  -Wall #-O
CC 					=  gcc 			# the C compiler
LDLIBS 			=  -lm 			# libraries to link


# --- SPECIFY HYPERPARAMETERS --- #
FILES       =  somefile.c
OBJECTS     =  someobject.o
OUTPUTFILE  =  someoutput.txt
ERRFILE			=  errors.txt
PROGRAM     =  someprogram
DISPLAY     =  cat


default: $(OUTPUTFILE)									  		# default target is to make out.txt
	$(DISPLAY) $(OUTPUTFILE) 										# show out.txt on the screen

$(OUTPUTFILE) : $(PROGRAM)                  	# someoutput.txt depends on someprogram
	./$(PROGRAM) 1> $(OUTPUTFILE) 2> $(ERRFILE)	# Generate someoutput.txt and send the terminal output of someprogram into it.
			        	 															# This target basically runs the program and sends it into a .txt file called someoutput.txt


$(PROGRAM) : $(OBJECTS)     	      			  	# Someprogram depends on someobject.o
	$(CC) $(OBJECTS) -o $(PROGRAM)   				  	# Now we link the object file, someobject.o to an output program ('-o') called someprogram.
																							# This is how you make someprogram from someobject.o


$(OBJECTS) : $(FILES)          								# someobject.o depends on somefile.c
	$(CC) -c $(FILES) $(CFLAGS) -o $(OBJECTS) 	# '-c' flag means compile only and do not link. This is how you make the object file someobject.o from somefile.c


.PHONEY: clean
clean:                 	      		 	  				# This is "clean" target it does not depend on anything
	rm -f $(OUTPUTFILE) $(OBJECTS) $(PROGRAM) 	# This target functions as expected, it cleans up the directory of program files.
