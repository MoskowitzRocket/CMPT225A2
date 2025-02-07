CXX = g++

CXXFLAGS = -Wall -Wextra -std=c++20

SRC = TestQuadraticProbing.cpp QuadraticProbing.cpp

OBJS = TestQuadraticProbing.o QuadraticProbing.o

TARGET = main

HEADERS = dsexceptions.h QuadraticProbing.h BiMap.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)


%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@


run:
	./main

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)


.PHONY: all clean run
