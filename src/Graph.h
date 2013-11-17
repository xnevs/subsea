#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

class Node;

class Graph {
private:
	std::vector<Node *> nodes;
public:
	Graph();
	Graph(Graph *g);
	std::vector<Node *> &get_nodes();

	void init(std::vector<Node *> &_nodes);
	void add_node();
	void add_node(int _id, int _label);
	void add_edge(int start, int end);
	
	void set_edge_color(int start, int end, bool color);

	void print();
};

#endif
