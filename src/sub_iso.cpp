#include "sub_iso.h"

#include <cstdio>

#include "Graph.h"
#include "Node.h"
#include "bisection.h"
#include "traverse_history.h"
#include "search_traverse.h"

int sub_iso(std::set<traverse_history_t> A, Graph *Gl) {
	if(Gl->get_nodes().size() < (*(A.begin())).size())
		return 0;
		
	int num_of_subisomorphisms = 0;
	
	Graph *g1 = new Graph();
	Graph *g2 = new Graph();
	
	bisection(Gl, g1, g2);
	
	for(std::vector<Node *>::iterator it1 = g1->get_nodes().begin(); it1 != g1->get_nodes().end(); it1++) {
		for(std::vector<Node *>::iterator it2 = g2->get_nodes().begin(); it2 != g2->get_nodes().end(); it2++) {
			if((*it1)->is_connected(*it2)) {
				for(std::set<traverse_history_t>::iterator it3 = A.begin(); it3 != A.end(); it3++){
					std::vector<Graph *> S = search_traverse(Gl, *it1, *it2, *it3);
					
					Gl->set_edge_color((*it1)->get_id(), (*it2)->get_id(), false);
					Gl->set_edge_color((*it2)->get_id(), (*it1)->get_id(), false);
					
					num_of_subisomorphisms += S.size();
					
					for(std::vector<Graph *>::iterator it4 = S.begin(); it4 != S.end(); it4++) {
						printf("-----FOUND------------------------------------------\n");
						(*it4)->print();
						printf("----------------------------------------------------\n");
					}
				}
			}
		}
	}
	
	num_of_subisomorphisms += sub_iso(A, g1);
	num_of_subisomorphisms += sub_iso(A, g2);
	
	return num_of_subisomorphisms;
}