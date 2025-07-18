# asaf0604@gmail.com   325362457
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
TARGET = main
OBJS = main.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp my_container.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

test: test.cpp my_container.hpp
	$(CXX) $(CXXFLAGS) -o test test.cpp

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

valgrind-test: test
	valgrind --leak-check=full --show-leak-kinds=all ./test

clean:
	rm -f $(TARGET) test *.o
