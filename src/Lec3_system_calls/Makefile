########################################
#
#  IUPUI CSCI 503 -- Operating Systems
#
########################################

## Compiler, tools and options
CC      = gcc
LINK    = gcc
OPT     = -g

CCFLAGS = $(OPT) -Wall
LDFLAGS = $(OPT)

## Libraries
LIBS =
INC  = -I.

## FILES
OBJECTS1 = fork1.o
TARGET1  = fork1
OBJECTS2 = fork2.o
TARGET2  = fork2
OBJECTS3 = fork3.o
TARGET3  = fork3
OBJECTS4 = fork4.o
TARGET4  = fork4
OBJECTS5 = fork5.o
TARGET5  = fork5


## Implicit rules
.SUFFIXES: .c
.c.o:
	$(CC) -c $(CCFLAGS) $(INC) $<

## Build rules
all: $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4) $(TARGET5)

$(TARGET1): $(OBJECTS1)
	$(LINK) -o $@ $(OBJECTS1) $(LDFLAGS) $(LIBS)

$(TARGET2): $(OBJECTS2)
	$(LINK) -o $@ $(OBJECTS2) $(LDFLAGS) $(LIBS)

$(TARGET3): $(OBJECTS3)
	$(LINK) -o $@ $(OBJECTS3) $(LDFLAGS) $(LIBS)

$(TARGET4): $(OBJECTS4)
	$(LINK) -o $@ $(OBJECTS4) $(LDFLAGS) $(LIBS)

$(TARGET5): $(OBJECTS5)
	$(LINK) -o $@ $(OBJECTS5) $(LDFLAGS) $(LIBS)

clean:
	rm -f $(OBJECTS1) $(TARGET1) $(OBJECTS2) $(TARGET2) \
              $(OBJECTS3) $(TARGET3) $(OBJECTS4) $(TARGET4) \
	      $(OBJECTS5) $(TARGET5)	
	rm -f *~ core
