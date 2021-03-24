#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <string>
#include <algorithm>
#include <sstream>
#include <vector>

std::string get_str(std::string s){
    return s;
}

template<typename ...Args>
std::string get_str(std::string first, Args&&... msg){
    return first + get_str(msg...);
}

std::string to_str(int x){
    if(!x)
        return "0";

    std::string ret;
    while(x){
        int d = x%10;
        x /= 10;
        ret.push_back(d + '0');
    }
    
    std::reverse(ret.begin(), ret.end());
    return ret;
}

std::vector<std::string> split(std::string line){
    std::istringstream iss(line);
    std::vector<std::string> ret;

    std::string s;
    while(iss >> s)
        ret.push_back(s);
    return ret;
}

#endif