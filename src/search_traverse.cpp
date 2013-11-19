//vtime za 1 zamaknjen (indeks v h se zacne pri 0)

#include "search_traverse.h"

#include <vector>
#include <map>
#include <algorithm>

#include "traverse_history.h"
#include "Graph.h"
#include "Node.h"

#include <cstdio>

bool check_condition(Graph *gl, traverse_history_pair_t &h_vtime, Node *v) {
	if(h_vtime.first != v->get_label())
		return false;

	Node *v_ = NULL;
	for(std::vector<Node *>::iterator it=gl->get_nodes().begin(); it != gl->get_nodes().end(); it++)
		if((*it)->get_id() == v->get_id())
			v_ = *it;

	for(std::set<int>::iterator it=h_vtime.second.begin(); it!=h_vtime.second.end(); it++) {
		bool contains = false;
		for(std::vector<Node *>::iterator it1=gl->get_nodes().begin(); it1 != gl->get_nodes().end(); it1++)
			if((*it1)->number > 0)
				if(v_->is_connected(*it1))
					if(*it == (*it1)->number)
						contains = true;
		if(!contains)
			return false;
	}
	return true;
}

std::vector<Graph *> search_visit(Graph *gl, traverse_history_t &h, Graph *gr, int level) {
	std::vector<Graph *> s;
	
	int vtime = gr->get_nodes().size();

	Node *v_ = gr->get_nodes().back(); //v_ je zadnji dodan node
	
	if(!check_condition(gl, h[vtime-1], v_)) {
		return s;
	}
	else {  //to je glavni del
		for(std::vector<Node *>::iterator it = gr->get_nodes().begin(); it != gr->get_nodes().end(); it++) //po grafu gr
			for(std::set<int>::iterator it1 = h[vtime-1].second.begin(); it1 != h[vtime-1].second.end(); it1++) //po H[vtime].N
				if( (*it)->number == *it1 ) {
					gr->add_edge(v_->get_id(), (*it)->get_id());
					gr->add_edge((*it)->get_id(), v_->get_id());
				}
		
	
		if(h.size() == vtime) {
			s.push_back(gr);
			return s;
		}
		else {
			std::vector<Node *> L;
			for(std::vector<Node *>::iterator it = gl->get_nodes().begin(); it != gl->get_nodes().end(); it++) {
				bool in_L = true;
				for(std::set<int>::iterator it_h = h[vtime].second.begin(); it_h != h[vtime].second.end(); it_h++)
					if(!(*it)->is_connected_id((gr->get_nodes()[(*it_h)-1])->get_id())) {
						in_L = false;
						break;
					}
				if(in_L)
					L.push_back(*it);
			}
			
			for(std::vector<Node *>::iterator it = L.begin(); it != L.end(); it++) {
				if((*it)->number == 0) { //number v Gl!!!!!
					
					(*it)->number = vtime + 1;
					
					Graph *gr_new = new Graph(gr);
					
					gr_new->add_node((*it)->get_id(), (*it)->get_label(), vtime+1);
					
					std::vector<Graph *>s_rec = search_visit(gl, h, gr_new, level+1);
					
					for(std::vector<Graph *>::iterator it1 = s_rec.begin(); it1 != s_rec.end(); it1++)
							s.push_back(*it1);
					
					(*it)->number = 0;
				}
			}
		}
		
	}
	
	return s;
}

std::vector<Graph *> search_traverse(Graph *gl, Node *v1, Node *v2, traverse_history_t h) {
	std::vector<Graph *> ret;

	v1->number = 1;
	v2->number = 2;


	if(v1->get_label() == h[0].first) { //check_condition za prvega (mogoce ima napacen label)
		Graph *gr = new Graph();
		gr->add_node(v1->get_id(), v1->get_label(), 1);
		gr->add_node(v2->get_id(), v2->get_label(), 2);
	
		ret = search_visit(gl, h, gr, 0);
	}
	
	v1->number = 0;
	v2->number = 0;
	
	return ret;
}
