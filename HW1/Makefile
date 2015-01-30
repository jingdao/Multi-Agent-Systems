CC = g++
INCLUDE_DIRS =
CFLAGS = -O2  
debug: CFLAGS = -O0 -ggdb3
LDFLAGS = -lglpk
SOURCES = hw1.cpp Profiler.c
ALL_SOURCES = $(SOURCES)
HEADERS = hw1.h Profiler.h 
OBJ = hw1.o Profiler.o 
ALL_OBJ = $(OBJ)
EXECUTABLE = hw1

all: $(ALL_SOURCES) $(EXECUTABLE)

debug: all

$(EXECUTABLE): $(ALL_OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(EXECUTABLE) $(SHARED_OBJECT)
