#ifndef SEARCH_TRAVERSE_H
#define SEARCH_TRAVERSE_H

#include <vector>

#include "traverse_history.h"

class Graph;
class Node;

std::vector<Graph *> search_traverse(Graph *gl, Node *v1, Node *v2, traverse_history_t h);

#endif