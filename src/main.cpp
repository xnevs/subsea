#include <set>

#include <cstdio>

#include "Graph.h"

#include "bisection.h"
#include "traverse_history.h"
#include "search_traverse.h"
#include "sub_iso.h"

#include "read_VFlib_data.h"

int main(int argc, char *argv[]) {
	//branje velikega grafa v formatu VFlib
	Graph *Gl = new Graph();

	FILE *f = fopen(argv[1], "rb");
	read_graph(Gl, f);

	Gl->print();
	printf("\n==============================================\n\n");


	//branje majhnega grafa v formatu VFlib
	Graph *Gs = new Graph();
	
	f = fopen(argv[2], "rb");
	read_graph(Gs, f);
	
	Gs->print();
	printf("\n==============================================\n\n");



	//algoritem
	std::set<traverse_history_t> A = all_traverse_histories(Gs);
	
	for(std::set<traverse_history_t>::iterator it = A.begin(); it != A.end(); it++)
		print_traverse_history(*it);
	
	printf("num of isomorphisms: %d\n", sub_iso(A, Gl));
}
