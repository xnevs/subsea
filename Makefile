all: subsea

subsea: main.o Graph.o Node.o bisection.o traverse_history.o search_traverse.o sub_iso.o read_VFlib_data.o
	g++ -g main.o Graph.o Node.o bisection.o traverse_history.o search_traverse.o sub_iso.o read_VFlib_data.o -o subsea

main.o: src/main.cpp
	g++ -g -c src/main.cpp

Graph.o: src/Graph.cpp
	g++ -g -c src/Graph.cpp

Node.o: src/Node.cpp
	g++ -g -c src/Node.cpp

bisection.o: src/bisection.cpp
	g++ -g -c src/bisection.cpp

traverse_history.o: src/traverse_history.cpp
	g++ -g -c src/traverse_history.cpp

search_traverse.o: src/search_traverse.cpp
	g++ -g -c src/search_traverse.cpp

sub_iso.o: src/sub_iso.cpp
	g++ -g -c src/sub_iso.cpp

read_VFlib_data.o: src/read_VFlib_data.cpp
	g++ -g -c src/read_VFlib_data.cpp

clean:
	rm main.o
	rm Graph.o
	rm Node.o
	rm bisection.o
	rm traverse_history.o
	rm search_traverse.o
	rm sub_iso.o
	rm read_VFlib_data.o
