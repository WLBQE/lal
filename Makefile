CXX=clang++
CXXFLAGS=-std=c++17 -O2 -Wall -Wextra -pedantic

dummy: dummy.cpp include/matrix.hpp
	$(CXX) -o dummy $(CXXFLAGS) dummy.cpp

.PHONY: clean
clean:
	rm -f dummy