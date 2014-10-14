#ifndef NODE_H
#define NODE_H

#include <vector>

class Node;
class Edge;

class Node {
private:
	int id;
	int label;
    
	std::vector<Edge *> out_edges;
	std::vector<Edge *> in_edges;
    
public:
	int number;

	Node(int _id, int _label, int _number);
	Node(int _id);

	int get_id();
	int get_label();

	void add_out_edge(Edge *edge);
	void add_in_edge(Edge *edge);

	int is_connected(Node *node);
	int is_connected_id(int _id);
	
	void set_edge_color(Node *n_end, bool color);

	void print();
};

class Edge {
private:
    Node *start;
	Node *end;
	bool color;
public:
	Edge(Node *_start, Node *_end);

	Node *get_end();
    Node *get_start();
	bool get_color();
	void set_color(bool _color);
};

#endif
