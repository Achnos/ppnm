CFLAGS = -Wall -O1 -std=gnu11
CFLAGS += -pthread
CFLAGS += -fopenmp
LDLIBS = -lm -lgomp -lpthread

OBJECTS = main.o rndNum.o piApproxMultithreaded.o
HDRS = rndNum.h piApproxMultithreaded.h
EXECS = main

default: $(EXECS)
	./$<

$(EXECS): $(OBJECTS)

$(OBJECTS): $(HDRS)

clean:
	rm main main.o
