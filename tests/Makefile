includeFlags = -I ../src
cFlags = -std=c++11

all: FIRTestSuite IIRTestSuite FIRIdealFilterSuite

FIRIdealFilterSuite: FIRIdealFilterSuite.cpp ../src/FIRFilter.hpp ../src/FIRFilter.h ../src/Filter.h ../src/FilterUtility.h ../src/FilterUtility.hpp
	g++ -o FIRIdealFilterSuite FIRIdealFilterSuite.cpp $(includeFlags) ${cFlags}

FIRTestSuite: FIRTestSuite.cpp ../src/FIRFilter.hpp ../src/FIRFilter.h ../src/Filter.h
	g++ -o FIRTestSuite FIRTestSuite.cpp $(includeFlags) ${cFlags}

IIRTestSuite: IIRTestSuite.cpp ../src/IIRFilter.hpp ../src/IIRFilter.h ../src/Filter.h
	g++ -o IIRTestSuite IIRTestSuite.cpp $(includeFlags) ${cFlags}

clean:
	rm -f FIRTestSuite
	rm -f FIRIdealFilterSuite
	rm -f IIRTestSuite
	rm -f *.o
