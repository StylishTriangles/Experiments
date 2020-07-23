CC = g++
CPPFLAGS = -O3 -march=native
CXXFLAGS = -std=c++17
OBJ_FILES = ../common/random.o branchless.o benchmark.o
INCLUDE_PATHS = -I../common

all: $(OBJ_FILES)
	$(CC) $(CPP_FLAGS) $^ -o branchless.app

%.o: %.cpp
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDE_PATHS) -c -o $@ $<

clean:
	rm *.o
	rm *.app
	rm ../common/.o
