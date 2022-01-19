SRC=$(wildcard *.cpp)

OBJ=$(SRC:%.cpp=%.o)

DEP=$(OBJ:%.o=%.d)

CXXFLAGS=-MMD -O2 -Wall -Wextra
LDFLAGS=

exe: $(OBJ)
	g++ -O2 $(OBJ) $(LDFLAGS) -o exe

%.o: %.cpp
	g++ -o $@ -c $< $(CXXFLAGS)


