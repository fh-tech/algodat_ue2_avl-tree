all: treecheck

treecheck: *.cpp
	g++ -std=c++14 -ggdb -o treecheck *.cpp Tree.h

clean:
	rm -r treecheck.exe treecheck *.o