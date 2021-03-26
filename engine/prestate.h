#ifndef __PRESTATE_H__
#define __PRESTATE_H__

#include <vector>
#include <map>
#include <string>
#include <utility>
#include <functional>

struct Box;
struct Node;
struct Graph;

typedef int Value;
typedef std::pair<Node*, int> Pin;

struct Box{
    bool solid, sync;
    std::string name;
    std::vector<std::string> inputs, outputs;
    Graph *graph;
    
    /*
    * for solid boxes.
    */
    std::function<std::vector<Value>(std::vector<Value>)> func;

    Box():
        solid(false), sync(true), name(""), inputs({}), outputs({}), graph(NULL) {}
    
    Box(
        bool solid,
        std::string name,
        std::vector<std::string> inputs,
        std::vector<std::string> outputs,
        Graph *graph=NULL,
        bool sync=true
    ):
        solid(solid),
        name(name),
        inputs(inputs),
        outputs(outputs),
        graph(graph),
        sync(sync)
        {}
};

struct Node{
    Box *box;
    std::vector<std::vector<Pin>> out;

    /*
    * index: index in graph
    * in_index: index in sources if it is an input pin for the graph
    * out_index: same as in_index but for output pins
    */
    int index, in_index, out_index;

    Node(Box *box, int index=-1, int in_index=-1, int out_index=-1):
        box(box), index(index), in_index(in_index), out_index(out_index) {
            for(auto output : box->outputs)
                out.push_back(std::vector<Pin>());
        }

};

struct Graph{
    std::vector<Node*> nodes, sinks, sources;

    Graph(){
    }

    Graph(const Graph &other){
        operator=(other);
    }

    Graph& operator = (const Graph &other){
        nodes = other.nodes;
        sinks = other.sinks;
        sources = other.sources;
        
        return *this;
    }

    void add_node(Node *node, bool in=false, bool out=false){
        node->index = nodes.size();
        nodes.push_back(node);
        
        if(in){
            node->in_index = sources.size();
            sources.push_back(node);
        }
        
        if(out){
            node->out_index = sinks.size();
            sinks.push_back(node);
        }
    }

};

#endif