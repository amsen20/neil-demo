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

//PINS
#define IN_PIN "input-pin"
#define OUT_PIN "output-pin"

Box *add, *sub, *mul, *con, *in_pin, *out_pin;

void set_up(std::map<std::string, Box*> &types){
    add = new Box(true, ADD, {"a", "b"}, {"c"});
    types[add->name] = add;
    
    sub = new Box(true, SUB, {"a", "b"}, {"c"});
    types[sub->name] = sub;

    mul = new Box(true, MUL, {"a", "b"}, {"c"});
    types[mul->name] = mul;

    con = new Box(true, CON, {"a", "b"}, {"c"});
    types[con->name] = con;

    in_pin = new Box(true, IN_PIN, {}, {"a"});
    types[in_pin->name] = in_pin;

    out_pin = new Box(true, OUT_PIN, {"a"}, {});
    types[out_pin->name] = out_pin;
}

#endif