includeFlags = -I ../src
cFlags = -std=c++11

all: FIRTestSuite

FIRTestSuite: FIRTestSuite.cpp ../src/FIRFilter.hpp ../src/FIRFilter.h ../src/Filter.h
	g++ -o FIRTestSuite FIRTestSuite.cpp $(includeFlags) ${cFlags}

clean:
	rm -f FIRTestSuite
	rm -f *.o
