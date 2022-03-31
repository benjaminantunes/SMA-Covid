SRC=$(wildcard *.cpp)

OBJ=$(SRC:%.cpp=%.o)

DEP=$(OBJ:%.o=%.d)

CXXFLAGS=-MMD -O2 -std=c++11
LDFLAGS=

exe: $(OBJ)
	g++ -O2 $(OBJ) $(LDFLAGS) -o exe

%.o: %.cpp
	g++ -o $@ -c $< $(CXXFLAGS)


clean:
	rm -rf *.o
	rm -rf *.d
