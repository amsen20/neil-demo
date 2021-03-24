#ifndef __ERR_H__
#define __ERR_H__

#include "tools.h"

#include <iostream>
#include <string>

void finish(std::string msg){
    std::cerr << msg << "\n";
    exit(0);
}

template<typename ...Args>
void ensuref(bool cond, Args&&... msg){
    if(cond)
        return;
    finish(get_str(msg...));
}

#endif