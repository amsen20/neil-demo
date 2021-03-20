#ifndef __ERR_H__
#define __ERR_H__

#include <iostream>

void fin(const char *msg){
    std::cerr << msg << "\n";
    exit(0);
}

void ensuref(bool cond, const char *msg){
    if(cond)
        return;
    fin(msg);
}

#endif