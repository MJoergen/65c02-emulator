sources  = cpu.cpp
sources += main.cpp
objects = $(sources:.cpp=.o)
depends = $(sources:.cpp=.d)
CC = gcc
DEFINES  = -Wall -O3 
#DEFINES  = -Wall -O3 -g -pg
#DEFINES += -DNDEBUG

cpu: $(objects) Makefile
	$(CC) -o $@ $(DEFINES) $(objects) -lstdc++
	mv $@ $(HOME)/bin

%.d: %.cpp Makefile
	set -e; $(CC) -M $(CPPFLAGS) $(DEFINES) $(INCLUDE_DIRS) $< \
		| sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
		[ -s $@ ] || rm -f $@

include $(depends)

%.o :
	$(CC) $(DEFINES) $(INCLUDE_DIRS) -c $< -o $@

clean: Makefile
	-rm $(objects)
	-rm $(depends)

