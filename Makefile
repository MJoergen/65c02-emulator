sources  = cpu6502.cpp
sources += main.cpp
objects = $(sources:.cpp=.o)
depends = $(sources:.cpp=.d)
CC = gcc
DEFINES  = -Wall -O3 
#DEFINES  = -Wall -O3 -g -pg
#DEFINES += -DNDEBUG

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

rom.o: rom.s
	ca65 $<
rom.bin: rom.o
	ld65 -C ld.cfg $<


clean: Makefile
	-rm $(objects)
	-rm $(depends)
	-rm rom.o
	-rm rom.bin

