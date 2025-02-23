DIR = ./
EXE := main

run :
	g++ main.cpp -o main

test :
	python3 tests1.py /home/isaac/Documents/C++/phase1/main

clean :
	rm main