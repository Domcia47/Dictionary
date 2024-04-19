CXX := g++
CXXFLAGS := -Wall
LDFLAGS := -s

# Lista plików źródłowych i docelowych
SOURCES := Dict.cpp
EXECUTABLES := Dict.x

# Pliki obiektowe
OBJECTS := $(SOURCES:.cpp=.o)

.PHONY: all clean make

all: $(EXECUTABLES)

Dict.x: Dict.o LinkedList.hpp

%.o: %.cpp LinkedList.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.x: %.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

make: $(OBJECTS) $(EXECUTABLES)

clean:
	$(RM) $(EXECUTABLES) $(OBJECTS)