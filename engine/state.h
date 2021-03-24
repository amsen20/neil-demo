#ifndef __STATE_H__
#define __STATE_H__

#include <utility>
#include <vector>
#include <queue>

#include "prestate.h"

struct NodeClone{
    Node *node;
    NodeClone *par;
    std::vector<NodeClone*> childs;

    /*
    * for solid boxes
    */
    std::vector<Value> inputs;
    int filled_inputs;

    Box *get_box(){
        return node->box;
    }

    NodeClone(Node *node=NULL, NodeClone *par=NULL):
        node(node), par(par) {
            if(node){
                if(get_box()->graph)
                    for(auto child : get_box()->graph->nodes)
                        childs.push_back(NULL);
                for(auto input : get_box()->inputs)
                    inputs.push_back(Value(-1));
            }
            filled_inputs = 0;
        }
};

typedef std::pair<NodeClone*, int> ClonePin;
typedef std::pair<Value, ClonePin> Flow;
typedef std::queue<Flow> Queue;

#endif