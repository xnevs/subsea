#include "traverse_history.h"

#include "Graph.h"
#include "Node.h"

#include <vector>
#include <set>
#include <utility>

#include <climits>

#include <cstdio>


std::pair<int, int> estimate_next(Graph *g, std::vector<int> &d, Node *w, Node *v) {
	std::set<Node *> s;
	s.insert(w);

	int len = 1;

	std::set<Node *> ns;
	do {
		int p = 0;
		for(std::set<Node *>::iterator it_s = s.begin(); it_s != s.end(); it_s++)
			for(std::vector<Node *>::iterator it_g=g->get_nodes().begin(); it_g != g->get_nodes().end(); it_g++) {
				Node *z = *it_s;
				Node *other = *it_g;

				if( !( (z==w && other==v) || (other==w && z==v) ) && z->is_connected(other)) {
					ns.insert(other);
					if(d[ v->get_id() ] > 0)
						p++;
				}
			}

		if(p > 0)
			return std::pair<int, int> (len, -p);

		len++;
		s = ns;

	} while(!ns.empty());

	return std::pair<int, int> (INT_MAX, -s.size());
}

void visit(Graph *g, std::vector< std::pair<int, std::set<int> > > &h, std::vector<int> &d, int &vtime, Node *v1, Node *v2, Node *v) {
	d[v->get_id()] = vtime;

	traverse_history_pair_t traverse_history_pair;
	traverse_history_pair.first = v->get_label();
	
	for(std::vector<Node *>::iterator it = g->get_nodes().begin(); it != g->get_nodes().end(); it++)
		if(v->is_connected(*it))
			if(d[(*it)->get_id()] > 0 && d[(*it)->get_id()] < d[v->get_id()])
				traverse_history_pair.second.insert( d[(*it)->get_id()] );
	
	h.push_back(traverse_history_pair);
	vtime++;

	if(v == v1)
		visit(g, h, d, vtime, v1, v2, v2);
	
	std::vector<Node *> n0;
	for(std::vector<Node *>::iterator it = g->get_nodes().begin(); it != g->get_nodes().end(); it++)
		if(v->is_connected(*it))
			if(d[ (*it)->get_id() ] == 0)
				n0.push_back(*it);
	
	while(!n0.empty()) {
		Node *w = NULL;
		std::pair<int, int> w_estimate_next (INT_MAX, INT_MAX);
		std::vector<Node *>::iterator w_iterator;

		std::pair<int, int> crnt_estimate_next;

		for(std::vector<Node *>::iterator it=n0.begin(); it!=n0.end(); it++) {
			crnt_estimate_next = estimate_next(g, d, *it, v);
			if( crnt_estimate_next < w_estimate_next) {
				w = *it;
				w_iterator = it;
				w_estimate_next = crnt_estimate_next;
			}
		}
		if(d[w->get_id()] == 0)
			visit(g, h, d, vtime, v1, v2, w);

		n0.erase(w_iterator);

	}

}

traverse_history_t traverse_history(Graph *g, Node *v1, Node *v2) {
	traverse_history_t h; //traverse history is a vector of pairs of labels and Ni-s

	std::vector<int> d (g->get_nodes().size(), 0);

	int vtime = 1;

	visit(g, h, d, vtime, v1, v2, v1);

	return h;
}




std::set<traverse_history_t> all_traverse_histories(Graph *g) {
	std::set<traverse_history_t> a;

	for(std::vector<Node *>::iterator it1 = g->get_nodes().begin(); it1 != g->get_nodes().end(); it1++)
		for(std::vector<Node *>::iterator it2 = g->get_nodes().begin(); it2 != g->get_nodes().end(); it2++)
			if((*it1)->is_connected(*it2))
				a.insert(traverse_history(g, *it1, *it2));
	
	return a;
}



void print_traverse_history(traverse_history_t h) {
	printf("< ");
	for(traverse_history_t::iterator it1 = h.begin(); it1 != h.end(); it1++) {
		printf("( %d, { ", (*it1).first);

		for(std::set<int>::iterator it2 = (*it1).second.begin(); it2 != (*it1).second.end(); it2++) {
			printf("%d, ", (*it2));
		}
		
		printf(" } ), ");
	}
	printf(" >\n");
}
