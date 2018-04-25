CXX = clang++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -pedantic

INCLUDE = include/basics.hpp include/vector.hpp include/matrix.hpp include/iterators.hpp include/dmatrix.hpp \
          include/constexpr_algorithm.hpp

test: test.cpp $(INCLUDE)
	$(CXX) -o test $(CXXFLAGS) test.cpp

.PHONY: clean
clean:
	rm -f test