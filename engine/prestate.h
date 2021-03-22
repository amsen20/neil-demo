#ifndef __PRESTATE_H__
#define __PRESTATE_H__

#include <vector>
#include <map>
#include <string>
#include <utility>

struct Box{
    bool solid;
    std::string name;
    std::vector<std::string> inputs, outputs;
    Graph *graph;

    Box():
        solid(false), name(""), inputs({}), outputs({}), graph(NULL) {}
    
    Box(
        bool solid,
        std::string name,
        std::vector<std::string> inputs,
        std::vector<std::string> outputs,
        Graph *graph=NULL
    ):
        solid(solid),
        name(name),
        inputs(inputs),
        outputs(outputs),
        graph(graph)
        {}
};

struct Node{
    Box *box;
    std::vector<Pin> out;

    Node(Box *box=NULL):
        box(box) {}

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

};

typedef std::pair<Node*, int> Pin;

#endif