DIR = ./
CXX = g++
EXE = program
FLAGS = -Wall -Wextra -Wpedantic -std=c++23

# Create the single executable
$(EXE): main.cpp memory.cpp memory.hpp main.hpp utils.h
	$(CXX) $(FLAGS) main.cpp memory.cpp -o $(EXE)

# Execute the test file on the executable
test:
	python3 tests2.py $(DIR)$(EXE)

# Removes executable file
clean:
	rm $(EXE)