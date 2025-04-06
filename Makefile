DIR = ./
EXE := main

#runs the main file
run :
	g++ main.cpp -o main -Wall -Wextra -Wpedantic -std=c++23
	g++ memory.cpp -o memory -Wall -Wextra -Wpedantic -std=c++23
# Execute the test file on the executable
test :
	python3 tests2.py $(DIR)$(EXE)

# Removes executable file
clean :
	rm $(EXE)