#CFLAGS = -Wall -Ofast -std=c1x
#C = F

#all:
#	echo CFLAGS
#	echo $CFLAGS
#	echo $(C)FLAGS
#	echo $(CFLAGS)

#all: main

#main: main.c

        #main: main.o

#        all: main
#        main: main.o
#        main.o: main.c

#        all: main
#        main.o: main.c
#        main: main.o

#        main.o: main.c
#        all: main
#        main: main.o

#main: main.c
#	cc main.c -o main

#main: main.c
#	$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

all: main
main: main.o
	cc main.o -o main

main.o: main.c
	cc -c main.c -o main.o
