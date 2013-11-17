#include "bisection.h"

#include "Graph.h"
#include "Node.h"

#include <vector>
#include <cstdlib>
#include <ctime>

void find_adjacent_to_b(std::vector<Node *> &b0, std::vector<Node *> &b, std::vector<Node *> &e0) {
	for(std::vector<Node *>::iterator it_b = b.begin(); it_b != b.end(); it_b++)
		for(std::vector<Node *>::iterator it_b0 = b0.begin(); it_b0 != b0.end(); it_b0++) {
			if( (*it_b)->is_connected(*it_b0) )
				e0.push_back(*it_b0);
		}
		
}

//returns a random node from edges e0
Node *random_node_from_e0(std::vector<Node *> &b0, std::vector<Node *> &e0) {
	int pos = rand() % e0.size();

	Node *node = e0[pos];

	for(std::vector<Node *>::iterator it = b0.begin(); it!=b0.end(); it++) {
		if(*it == node) {
			b0.erase(it);
			break;
		}
	}

	return node;
}

//returns a random node from b0
Node *random_node_from_b0(std::vector<Node *> &b0) {
	int pos = rand() % b0.size();

	Node *node = b0[pos];

	b0.erase(b0.begin() + pos);

	return node;
}

void add_2_hole(std::vector<Node *> &b0, std::vector<Node *> &b) {
	if(b0.empty())
		return;
	
	std::vector<Node *> e0;
	find_adjacent_to_b(b0, b, e0);

	Node *node = NULL;
	if(!e0.empty())
		node = random_node_from_e0(b0, e0);
	else
		node = random_node_from_b0(b0);

	b.push_back(node);
}

void bisection(Graph *g, Graph *g1, Graph *g2) {
	//Black holes bisection

	srand(time(NULL));

	std::vector<Node *> b1;
	std::vector<Node *> b2;

	std::vector<Node *> b0 = g->get_nodes();

	while(!b0.empty()) {
		add_2_hole(b0, b1);
		add_2_hole(b0, b2);
	}
	

	g1->init(b1);
	g2->init(b2);
}
