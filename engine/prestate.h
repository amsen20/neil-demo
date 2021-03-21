#ifndef __DATA_H__
#define __DATA_H__

#include <vector>
#include <map>
#include <string>

struct Type{
    bool solid;
    std::string name;
    std::vector<std::string> inputs, outputs;

    Type(
        bool solid,
        std::string name,
        std::vector<std::string> inputs,
        std::vector<std::string> outputs
    ):
        solid(solid),
        name(name),
        inputs(inputs),
        outputs(outputs)
        {}
};

struct Node{
    std::string name;
    Type *type;
    std::vector<Node*> out;
};

struct Graph{
    std::vector<Node*> nodes;

    Graph(){
    }

    Graph(const Graph &other){
        operator=(other);
    }

    Graph& operator = (const Graph &other){
        nodes = other.nodes;
        
        return *this;
    }

};

#endif