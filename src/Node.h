#ifndef NODE_H
#define NODE_H

#include <vector>

class Node;
class Edge;

class Node {
private:
	int id;
	int label;
	std::vector<Edge *> edges;
public:
	Node(int _id, int _label);
	Node(int _id);

	int get_id();
	int get_label();

	void add_edge(Edge *edge);

	bool is_connected(Node *node);
	
	void set_edge_color(Node *n_end, bool color);

	void print();
};

class Edge {
private:
	Node *end;
	bool color;
public:
	Edge(Node *_end);

	Node *get_end();
	bool get_color();
	void set_color(bool _color);
};

#endif
