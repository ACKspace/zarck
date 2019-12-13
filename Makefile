#
# No Copyright
#
# The person who associated a work with this deed has dedicated the work to the public domain by waiving all of his or her rights to the work worldwide under copyright law, including all related and neighboring rights, to the extent allowed by law.
#
# You can copy, modify, distribute and perform the work, even for commercial purposes, all without asking permission.
#
# See https://creativecommons.org/share-your-work/public-domain/cc0/ for more information on the license.
#


# programs
CC	:= gcc
LD	:= $(CC)

# flags
CFLAGS	:= -g -O2 -Wall
LDFLAGS	:= -g -Wall
LIBS	:=

# sources
HEADERS := vanalles.h world.h
SOURCES := vanalles.c world.c main.c
OBJECTS := $(SOURCES:.c=.o)
TARGET	:= zarck

# targets
.PHONY:	all clean
all:	$(TARGET)

$(TARGET): $(OBJECTS)
	$(LD) -o $@ $(LDFLAGS) $(OBJECTS) $(LIBS)

.o: $< $(HEADERS)
	$(CC) -o $@ $(CFLAGS) $<

clean:
	-@ $(RM) $(TARGET) $(OBJECTS) $(TARGET).html $(TARGET).js $(TARGET).wasm

wasm:
	-@ emcc -o $(TARGET).html $(SOURCES) $(CFLAGS) -s WASM=1 --shell-file template.html -s NO_EXIT_RUNTIME=1  -s "EXTRA_EXPORTED_RUNTIME_METHODS=['ccall']" --emrun


# end of Makefile
