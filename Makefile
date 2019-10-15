sources  = cpu6502.cpp
sources += decode.cpp
sources += main.cpp
objects = $(sources:.cpp=.o)
depends = $(sources:.cpp=.d)
CC = gcc
DEFINES  = -Wall -Wextra -O3
#DEFINES  = -Wall -O3 -g -pg
#DEFINES += -DNDEBUG

all: cpu6502 rom.bin
	echo

cpu6502: $(objects) Makefile
	$(CC) -o $@ $(DEFINES) $(objects) -lstdc++
	mv $@ $(HOME)/bin

%.d: %.cpp Makefile
	set -e; $(CC) -M $(CPPFLAGS) $(DEFINES) $(INCLUDE_DIRS) $< \
		| sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
		[ -s $@ ] || rm -f $@

include $(depends)

%.o :
	$(CC) $(DEFINES) $(INCLUDE_DIRS) -c $< -o $@

rom.o: 6502_functional_test.s
	ca65 $< -o $@
rom.bin: rom.o
	ld65 -C ld.cfg $<


clean: Makefile
	-rm $(objects)
	-rm $(depends)
	-rm rom.o
	-rm rom.bin
	-rm a.out

