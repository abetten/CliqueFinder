# -*- MakeFile -*-

all: *.cpp *.h
	g++ -I . -Wall ./*.cpp -o main

clean:
	rm -rfv ./main
	rm -rfv ./*.o
