#ifndef __VM_H__
#define __VM_H__

#include <iostream>
#include <vector>

#include "prestate.h"
#include "state.h"
#include "commands.h"
#include "err.h"

NodeClone *clone_lazy(NodeClone *par, Node *node){
    if(!par->childs[node->index])
        par->childs[node->index] = new NodeClone(node, par);
    return par->childs[node->index];
}

void flow_out(
    Queue &que,
    Value value,
    const std::vector<Pin> &pins,
    NodeClone *nc
    )
{
    for(auto pin : pins){
        auto cln = clone_lazy(nc, pin.first);
        que.push(Flow(value, ClonePin(cln, pin.second)));
    }
}

void run(const std::vector<Box*> &boxes){
    Box *main = NULL;
    for(auto box : boxes)
        if(box->name == MAIN){
            main = box;
            break;
        }
    ensuref(main != NULL, "Main box not found.");

    Node *mainn = new Node(main);
    NodeClone *mainc = new NodeClone(mainn);

    Queue que;
    std::vector<Value> circuit_outs(main->outputs.size());

    for(int i=0 ; i<main->inputs.size() ; i++){
        std::cout << "Enter " << main->inputs[i] << ": ";
        Value dat;
        std::cin >> dat;
        que.push(Flow(dat, ClonePin(mainc, i)));
    }

    while(!que.empty()){
        Flow flow = que.front();
        que.pop();
        auto value = flow.first;
        auto node_clone = flow.second.first;
        auto pin_index = flow.second.second;
        auto node = node_clone->node;
        auto box = node->box;

        if(box->solid){
            ensuref(
                node_clone->inputs[pin_index] == Value(-1),
                "Two values for a same pin."
            );
            node_clone->inputs[pin_index] = value;
            node_clone->filled_inputs ++;
            
            if(box->name == OUT_PIN){
                auto index = node_clone->node->out_index;
                auto par_nc = node_clone->par;

                if(par_nc == mainc){ // main
                    circuit_outs[index] = value;
                    continue;
                }

                flow_out(que, value, par_nc->node->out[index], par_nc->par);
                continue;
            }
            
            if(!box->sync || node_clone->filled_inputs == node_clone->inputs.size()){
                auto outs = box->func(node_clone->inputs);
                for(int i=0 ; i<outs.size() ; i++)
                    flow_out(que, outs[i], node->out[i], node_clone->par);
                
                continue;
            }

            continue;
        }
        
        // not solid
        auto inputn = box->graph->sources[pin_index];

        flow_out(que, value, inputn->out.back(), node_clone);
    }

    for(int i=0 ; i<main->outputs.size() ; i++)
        std::cout << main->outputs[i] << ": " << circuit_outs[i] << "\n";
}

#endif