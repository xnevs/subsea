#include "Node.h"

#include <cstdio>

Node::Node(int _id, int _label, int _number) {
	id = _id;
	label = _label;
	number = _number;
}
Node::Node(int _id) {
	id = _id;
}

int Node::get_id() {
	return id;
}
int Node::get_label() {
	return label;
}

void Node::add_out_edge(Edge *edge) {
	out_edges.push_back(edge);
}
void Node::add_in_edge(Edge *edge) {
	in_edges.push_back(edge);
}

int Node::is_connected(Node *node) {
	for(std::vector<Edge *>::iterator it = out_edges.begin(); it != out_edges.end(); it++)
		if((*it)->get_color() && node == (*it)->get_end())
			return 1;
    
	for(std::vector<Edge *>::iterator it = in_edges.begin(); it != in_edges.end(); it++)
		if((*it)->get_color() && node == (*it)->get_end())
			return -1;
	
	return 0;
}

int Node::is_connected_id(int _id) {
	for(std::vector<Edge *>::iterator it = out_edges.begin(); it != out_edges.end(); it++)
		if((*it)->get_color() && _id == (*it)->get_end()->get_id())
			return 1;
    
	for(std::vector<Edge *>::iterator it = in_edges.begin(); it != in_edges.end(); it++)
		if((*it)->get_color() && _id == (*it)->get_end()->get_id())
			return -1;
	
	return 0;
}

void Node::set_edge_color(Node *n_end, bool color) {
	for(std::vector<Edge *>::iterator it = out_edges.begin(); it != out_edges.end(); it++)
		if((*it)->get_end() == n_end)
			(*it)->set_color(color);
}

void Node::print() {
	printf("%3d(%d): [", id, label);
	for(std::vector<Edge *>::iterator it = out_edges.begin(); it != out_edges.end(); it++) {
		printf("%d, ", (*it)->get_end()->id);
	}
	printf("] | [");
	for(std::vector<Edge *>::iterator it = in_edges.begin(); it != in_edges.end(); it++) {
		printf("%d, ", (*it)->get_start()->id);
	}
    printf("]\n");
}


Edge::Edge(Node *_start, Node * _end) {
    start = _start;
	end = _end;
	color = true; //true is white
}
Node *Edge::get_end() {
	return end;
}
Node *Edge::get_start() {
	return start;
}
bool Edge::get_color() {
	return color;
}
void Edge::set_color(bool _color) {
	color = _color;
}