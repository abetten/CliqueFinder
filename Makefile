# -*- MakeFile -*-

all: *.cpp *.h
	g++ -I . -Wall *.cpp -o main

clean:
	rm -rfv ./main
	rm -rfv ./*.o

run:
	@./main -v 2 \
	       -list_of_cases ~/Desktop/G/list_of_cases_BLT_41_5_0_1.txt ~/Desktop/G/graph_BLT_41_5_%ld.bin \
	       -output_file ~/Desktop/SOLUTIONS/BLT_41_solutions_5_0_1.txt