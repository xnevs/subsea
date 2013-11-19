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

void Node::add_edge(Edge *edge) {
	edges.push_back(edge);
}

bool Node::is_connected(Node *node) {
	for(std::vector<Edge *>::iterator it = edges.begin(); it != edges.end(); it++)
		if((*it)->get_color() && node == (*it)->get_end())
			return true;
	
	return false;
}

bool Node::is_connected_id(int _id) {
	for(std::vector<Edge *>::iterator it = edges.begin(); it != edges.end(); it++)
		if((*it)->get_color() && _id == (*it)->get_end()->get_id())
			return true;
	
	return false;
}

void Node::set_edge_color(Node *n_end, bool color) {
	for(std::vector<Edge *>::iterator it = edges.begin(); it != edges.end(); it++)
		if((*it)->get_end() == n_end)
			(*it)->set_color(color);
}

void Node::print() {
	printf("%3d(%d): [", id, label);
	for(std::vector<Edge *>::iterator it = edges.begin(); it != edges.end(); it++) {
		printf("%d, ", (*it)->get_end()->id);
	}
	printf("]\n");
}


Edge::Edge(Node * _end) {
	end = _end;
	color = true; //true is white
}
Node *Edge::get_end() {
	return end;
}
bool Edge::get_color() {
	return color;
}
void Edge::set_color(bool _color) {
	color = _color;
}