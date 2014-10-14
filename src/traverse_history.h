#ifndef TRAVERSE_HISTORY_H
#define TRAVERSE_HISTORY_H

#include <vector>
#include <set>

class Graph;
class Node;

typedef std::pair<int, std::set<int> > traverse_history_pair_t;
typedef std::vector<traverse_history_pair_t> traverse_history_t;

traverse_history_t traverse_history(Graph *g, Node *v1, Node *v2);

std::set<traverse_history_t> all_traverse_histories(Graph *g);

void print_traverse_history(traverse_history_t h);

#endif
