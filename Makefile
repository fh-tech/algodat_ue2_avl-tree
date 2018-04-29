all: treecheck

treecheck: *.cpp
	g++ -std=c++11 -ggdb -o treecheck *.cpp

clean:
	rm -r treecheck.exe treecheck *.o