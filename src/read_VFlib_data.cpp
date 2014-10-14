#include <cstdio>

#include "Graph.h"

void read_graph(Graph *g, FILE *f) {
	short n;
	fread(&n, 1, 2, f);

	for(int i=0; i<n; i++)
		g->add_node();
	
	short num_edges;
	short end;
	for(int start=0; start<n; start++) {
		fread(&num_edges, 1, 2, f);
		for(int i=0; i<num_edges; i++) {
			fread(&end, 1, 2, f);
			g->add_edge(start, end);
		}
	}
}
