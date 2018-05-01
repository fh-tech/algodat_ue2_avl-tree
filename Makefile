all: treecheck

treecheck: *.cpp
	g++ -std=c++11 -ggdb -o treecheck *.cpp Node.h

clean:
	rm -r treecheck.exe treecheck *.o