#ifndef __STATE_H__
#define __STATE_H__

#include <utility>
#include <vector>
#include <queue>

#include "prestate.h"

struct NodeClone{
    Node *node;
    NodeClone *par;
    std::vector<int> child_indexes;
    std::vector<NodeClone*> childs;

    NodeClone(Node *node=NULL, NodeClone *par=NULL):
        node(node), par(par) {
            if(node != NULL)
                for(auto child : node->box->graph->nodes)
                    child_indexes.push_back(-1);
        }
};

typedef int Value;
typedef std::pair<NodeClone*, int> ClonePin;
typedef std::pair<Value, ClonePin> Flow;
typedef std::queue<Flow> Queue;

#endif