//vtime za 1 zamaknjen (indeks v h se zacne pri 0)

#include "search_traverse.h"

#include <vector>
#include <map>
#include <algorithm>

#include "traverse_history.h"
#include "Graph.h"
#include "Node.h"

bool check_condition(Graph *gl, traverse_history_pair_t &h_vtime, std::map<int, int> &g, Node *v) {
	if(h_vtime.first != v->get_label()) {
		return false;
	}

	Node *v_ = NULL;
	for(std::vector<Node *>::iterator it=gl->get_nodes().begin(); it != gl->get_nodes().end(); it++)
		if((*it)->get_id() == v->get_id())
			v_ = *it;

	for(std::set<int>::iterator it=h_vtime.second.begin(); it!=h_vtime.second.end(); it++) {
		bool contains = false;
		for(std::vector<Node *>::iterator it1=gl->get_nodes().begin(); it1 != gl->get_nodes().end(); it1++)
			if(v_->is_connected(*it1))
				if(g[(*it1)->get_id()] > 0)
					if(*it == g[(*it1)->get_id()])
						contains = true;
		if(!contains)
			return false;
	}
	return true;
}

std::vector<Graph *> search_visit(Graph *gl, traverse_history_t &h, std::map<int, int> &g, Graph *gr) {
	std::vector<Graph *> s;
	
	int vtime = gr->get_nodes().size();
	
	Node *v_ = NULL;
	for(std::vector<Node *>::iterator it = gr->get_nodes().begin(); it != gr->get_nodes().end(); it++)
		if(g[(*it)->get_id()] == vtime)
			v_ = *it;
	
	if(!check_condition(gl, h[vtime-1], g, v_)) {
		return s;
	}
	else {  //to je glavni del
		
		for(std::vector<Node *>::iterator it = gr->get_nodes().begin(); it != gr->get_nodes().end(); it++) //po grafu gr
			for(std::set<int>::iterator it1 = h[vtime-1].second.begin(); it1 != h[vtime-1].second.end(); it1++) //po H[vtime].N
				if( g[(*it)->get_id()] == *it1 ) {
					gr->add_edge(v_->get_id(), (*it)->get_id());
					gr->add_edge((*it)->get_id(), v_->get_id());
				}
		
		if(h.size() == vtime) {
			s.push_back(gr);
			return s;
		}
		else {
			for(std::vector<Node *>::iterator it = gl->get_nodes().begin(); it != gl->get_nodes().end(); it++) {
				bool in_L = true;
				for(std::vector<Node *>::iterator it1 = gl->get_nodes().begin(); it1 != gl->get_nodes().end(); it1++) {
					for(std::set<int>::iterator it2 = h[vtime].second.begin(); it2 != h[vtime].second.end(); it2++)
						if(g[(*it1)->get_id()] == *it2)
							if(!((*it)->is_connected(*it1)))
								in_L = false;
				}
				
				if(in_L) {
					if(g[(*it)->get_id()] == 0) {
						g[(*it)->get_id()] = vtime+1;
					
						Graph *gr_new = new Graph(gr);
						gr_new->add_node((*it)->get_id(), (*it)->get_label());
					
						std::vector<Graph *>s_rec = search_visit(gl, h, g, gr_new);
					
						for(std::vector<Graph *>::iterator it1 = s_rec.begin(); it1 != s_rec.end(); it1++)
							s.push_back(*it1);
					
						g[(*it)->get_id()] = 0;
					}
				}
			}
		}
		
	}
	
	return s;
}

std::vector<Graph *> search_traverse(Graph *gl, Node *v1, Node *v2, traverse_history_t h) {
	std::map<int, int> g;
	
	g[v1->get_id()] = 1;
	g[v2->get_id()] = 2;
	
	
	if(v1->get_label() == h[0].first) { //check_condition za prvega (mogoce ima napacen label)
		Graph *gr = new Graph();
		gr->add_node(v1->get_id(), v1->get_label());
		gr->add_node(v2->get_id(), v2->get_label());
	
		return search_visit(gl, h, g, gr);
	}
	else
		return std::vector<Graph *> ();
}