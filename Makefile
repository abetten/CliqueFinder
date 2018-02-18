# -*- MakeFile -*-

all: *.cpp *.h
	g++ -O3 -march=native -mtune=native -I . -Wall *.cpp -o main

clean:
	rm -rfv ./main
	rm -rfv ./*.o

run:
	@./main -v 2 \
	       -list_of_cases ~/Desktop/11/G/list_of_cases_BLT_11_5_0_1.txt ~/Desktop/11/G/graph_BLT_11_5_%ld.bin \
	       -output_file ~/Desktop/11/SOLUTIONS/BLT_11_solutions_5_0_1.txt
