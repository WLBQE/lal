CXX=clang++
CXXFLAGS=-std=c++17 -O2 -Wall -Wextra -pedantic

dummy: dummy.cpp include/matrix.hpp include/constexpr_algorithm.hpp include/vector.hpp
	$(CXX) -o dummy $(CXXFLAGS) dummy.cpp

.PHONY: clean
clean:
	rm -f dummy