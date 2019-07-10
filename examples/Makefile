includeFlags = -I ../src
cFlags = -std=c++11

all: LowPassFilterExample MovingAverageFilter

LowPassFilterExample: LowPassFilterExample.cpp ../src/FIRFilter.hpp ../src/FIRFilter.h ../src/Filter.h
	g++ -o LowPassFilterExample LowPassFilterExample.cpp $(includeFlags) ${cFlags}

MovingAverageFilter: MovingAverageFilter.cpp ../src/FIRFilter.hpp ../src/FIRFilter.h ../src/Filter.h
	g++ -o MovingAverageFilter MovingAverageFilter.cpp $(includeFlags) ${cFlags}

clean:
	rm -f LowPassFilterExample
	rm -f MovingAverageFilter
	rm -f *.o
