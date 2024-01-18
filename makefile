CXX = g++
CXXFLAGS = -Wall -g

proj0: checkers.o mytest.cpp
	$(CXX) $(CXXFLAGS) checkers.o mytest.cpp -o proj0

checkers.o: checkers.cpp checkers.h
	$(CXX) $(CXXFLAGS) -c checkers.cpp

run:
	./proj0

val1:
	valgrind ./proj0

clean:
	rm ~
	rm.o
