#include "Graph.h"

#include <cstdio>

#include "Node.h"

Graph::Graph() {}

Graph::Graph(Graph *g) {
	for(std::vector<Node *>::iterator it = g->nodes.begin(); it != g->nodes.end(); it++)
		nodes.push_back(new Node((*it)->get_id(), (*it)->get_label(), (*it)->number));
		
	
	for(std::vector<Node *>::iterator it1 = g->nodes.begin(); it1 != g->nodes.end(); it1++)
		for(std::vector<Node *>::iterator it2 = g->nodes.begin(); it2 != g->nodes.end(); it2++)
			if((*it1)->is_connected(*it2)) {
				add_edge((*it1)->get_id(), (*it2)->get_id());
				add_edge((*it2)->get_id(), (*it1)->get_id());
			}
}

std::vector<Node *> &Graph::get_nodes() {
	return nodes;
}

void Graph::init(std::vector<Node *> &_nodes) {
	for(std::vector<Node *>::iterator it = _nodes.begin(); it != _nodes.end(); it++)
		nodes.push_back(*it);
}
void Graph::add_node() {
	Node *node = new Node(nodes.size(), 0, 0);
	nodes.push_back(node);
}
void Graph::add_node(int _id, int _label) {
	Node *node = NULL;
	for(std::vector<Node *>::iterator it = nodes.begin(); it != nodes.end(); it++)
		if((*it)->get_id() == _id && (*it)->get_label())
			node = *it;
	if(node == NULL) {
		node = new Node(_id, _label, 0);
		nodes.push_back(node);
	}
}
void Graph::add_node(int _id, int _label, int _number) {
	Node *node = NULL;
	for(std::vector<Node *>::iterator it = nodes.begin(); it != nodes.end(); it++)
		if((*it)->get_id() == _id && (*it)->get_label())
			node = *it;
	if(node == NULL) {
		node = new Node(_id, _label, _number);
		nodes.push_back(node);
	}
}
void Graph::add_edge(int start, int end) {
	Node *n_start = NULL;
	Node *n_end = NULL;
	for(std::vector<Node *>::iterator it = nodes.begin(); it != nodes.end(); it++) {
		if((*it)->get_id() == start)
			n_start = *it;
		if((*it)->get_id() == end)
			n_end = *it;
	}
	
	if(n_start != NULL && n_end != NULL && !n_start->is_connected(n_end))
		n_start->add_edge(new Edge(n_end));
	//nodes[start]->add_edge(new Edge(nodes[end]));
}

void Graph::set_edge_color(int start, int end, bool color) {
	Node *n_start = NULL;
	Node *n_end = NULL;
	for(std::vector<Node *>::iterator it = nodes.begin(); it != nodes.end(); it++) {
		if((*it)->get_id() == start)
			n_start = *it;
		if((*it)->get_id() == end)
			n_end = *it;
	}
	
	if(n_start != NULL & n_end != NULL)
		n_start->set_edge_color(n_end, color);
}


void Graph::print() {
	for(std::vector<Node *>::iterator it = nodes.begin(); it!=nodes.end(); it++) {
		(*it)->print();
	}
}
