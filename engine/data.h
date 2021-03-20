#ifndef __DATA_H__
#define __DATA_H__

#include <vector>
#include <map>
#include <string>

struct graph{
    std::vector<std::vector<int> > in;
    std::vector<std::vector<int> > out;

    std::map<std::string, int> name_to_node;
};

#endif