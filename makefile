 #danieldaniel2468@gmail.com
 

CXX         := g++
CXXFLAGS    := -std=c++17 -Wall -Wextra -g

SRC_MAIN    := Demo.cpp
SRC_IMPL    := MyContainer.cpp
SRC_HEADER  := MyContainer.hpp
SRC_TEST    := test.cpp

TARGET_DEMO := Main
TARGET_TEST := test

.PHONY: all Main test valgrind clean

all: Main test

# build & run demo
Main: $(SRC_MAIN) $(SRC_IMPL) $(SRC_HEADER)
	$(CXX) $(CXXFLAGS) $(SRC_MAIN) -o $(TARGET_DEMO)
	@echo
	@echo "===== Running Demo ====="
	./$(TARGET_DEMO)
	@echo "========================"
	@echo

# build & run tests
test: $(SRC_TEST) $(SRC_IMPL) $(SRC_HEADER)
	$(CXX) $(CXXFLAGS) $(SRC_TEST) -o $(TARGET_TEST)
	@echo
	@echo "===== Running Tests ====="
	./$(TARGET_TEST)
	@echo "========================"
	@echo

valgrind: Main test
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET_DEMO)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET_TEST)

clean:
	rm -f $(TARGET_DEMO) $(TARGET_TEST)
