#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include "prestate.h"

// commands:
#define ADD "+"
#define SUB "-"
#define MUL "*"
#define CON ">-"

// keywords
#define DEF "def"
#define IN "in"
#define OUT "out"
#define GATE "gate"

Box *add, *sub, *mul, *con;

void set_up(){
    add = new Box(true, ADD, {"a", "b"}, {"c"});
    sub = new Box(true, SUB, {"a", "b"}, {"c"});
    mul = new Box(true, MUL, {"a", "b"}, {"c"});
    con = new Box(true, CON, {"a", "b"}, {"c"});
}

#endif