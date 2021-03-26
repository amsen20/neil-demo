#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include "prestate.h"

// operations:
#define ADD "+"
#define SUB "-"
#define MUL "*"
#define AND_n "&"
#define OR_n "|"
#define NOT_n "!"
#define CMP ">"

// commands:
#define CONN ">-"
#define COND "?"

// keywords
#define DEF "def"
#define IN "in"
#define OUT "out"
#define GATE "gate"
#define MAIN "main"

//pins
#define IN_PIN "input-pin"
#define OUT_PIN "output-pin"

Box *add, *sub, *mul, *and_n, *or_n, *not_n, *cmp, *conn, *in_pin, *out_pin, *cond;

void set_up(std::map<std::string, Box*> &types){
    add = new Box(true, ADD, {"a", "b"}, {"c"});
    types[add->name] = add;
    add->func = [](std::vector<Value> vec) -> std::vector<Value>{
        return {vec[0] + vec[1]};
    };
    
    sub = new Box(true, SUB, {"a", "b"}, {"c"});
    types[sub->name] = sub;
    sub->func = [](std::vector<Value> vec) -> std::vector<Value>{
        return {vec[0] - vec[1]};
    };

    mul = new Box(true, MUL, {"a", "b"}, {"c"});
    types[mul->name] = mul;
    mul->func = [](std::vector<Value> vec) -> std::vector<Value>{
        return {vec[0] * vec[1]};
    };

    and_n = new Box(true, AND_n, {"a", "b"}, {"c"});
    types[and_n->name] = and_n;
    and_n->func = [](std::vector<Value> vec) -> std::vector<Value>{
        return {vec[0] & vec[1]};
    };

    or_n = new Box(true, OR_n, {"a", "b"}, {"c"});
    types[or_n->name] = or_n;
    or_n->func = [](std::vector<Value> vec) -> std::vector<Value>{
        return {vec[0] | vec[1]};
    };

    not_n = new Box(true, NOT_n, {"a"}, {"c"});
    types[not_n->name] = not_n;
    not_n->func = [](std::vector<Value> vec) -> std::vector<Value>{
        return {!vec[0]};
    };

    cmp = new Box(true, CMP, {"a", "b"}, {"c"});
    types[cmp->name] = cmp;
    cmp->func = [](std::vector<Value> vec) -> std::vector<Value>{
        return {vec[0] > vec[1]};
    };

    conn = new Box(true, CONN, {"a", "b"}, {"c"});
    conn->sync = false;
    types[conn->name] = conn;
    conn->func = [](std::vector<Value> vec) -> std::vector<Value>{
        if(vec[0] != -1)
            return {vec[0]};
        else
            return {vec[1]};
    };

    cond = new Box(true, COND, {"a", "b"}, {"c"});
    cond->controller = true;
    types[cond->name] = cond;
    cond->check = [](std::vector<Value> vec) -> bool{
        return vec[1];
    };
    cond->func = [](std::vector<Value> vec) -> std::vector<Value>{
        return {vec[0]};
    };

    in_pin = new Box(true, IN_PIN, {}, {"a"});
    types[in_pin->name] = in_pin;

    out_pin = new Box(true, OUT_PIN, {"a"}, {});
    types[out_pin->name] = out_pin;
}

#endif