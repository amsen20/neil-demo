#ifndef __PARSER_H__
#define __PARSER_H__

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <utility>

#include "err.h"
#include "commands.h"
#include "prestate.h"
#include "tools.h"

std::map<Box*, Graph*> parse(std::string path){
    std::fstream file(path, std::fstream::in);
    std::vector<std::string> code;
    std::map<std::string, Box*> types;
    std::map<Box*, Graph*> box_to_graph;

    set_up(types);

    std::string line;
    while(std::getline(file, line))
        code.push_back(line);
    
    for(int line_num=0 ; line_num<code.size() ; line_num++){
        auto line = split(code[line_num]);

        if(line[0] == DEF){
            std::string name = line[1];
            ensuref(
                !types.count(name),
                "All boxes names must be unique line: ",
                to_str(line_num)
            );
            Box *box = new Box();
            types[name] = box;
            box->name = name;

            for(int i=line_num+1 ; i<code.size() ; i++){
                auto cline = split(code[i]);
                if(cline[0] == IN){
                    box->inputs.push_back(cline[1]);
                    continue;
                }
                if(cline[0] == OUT){
                    box->outputs.push_back(cline[1]);
                    continue;
                }
                break;
            }
        }
    }

    for(int line_num=0 ; line_num<code.size() ; line_num++){
        auto line = split(code[line_num]);
        if(line[0] != DEF)
            continue;

        int it=line_num+1;
        while(it < code.size()){
            auto cline = split(code[it]);
            if(cline[0] != IN && cline[0] != OUT)
                break;
            it ++;
        }
        std::map<std::string, Pin> env; // wires
        auto box = types[ line[1] ];
        Graph *graph = new Graph();

        for(auto input_name : box->inputs){
            Node *input = new Node(in_pin);
            input->out.push_back(Pin(NULL, -1));
            graph->nodes.push_back(input);
            graph->sources.push_back(input);
            env[input_name] = {input, 0};
        }

        while(it < code.size()){
            auto cline = split(code[it]);
            int ind = 0;
            if(cline[ind ++] != GATE)
                break;
            std::string gate_name = cline[ind ++];
            ensuref(
                types.count(gate_name),
                "Box is not defined in line: ",
                to_str(line_num)
            );
            auto box = types[gate_name];
            Node *cur = new Node(box);
            graph->nodes.push_back(cur);
            
            for(int i=0 ; i<box->inputs.size() ; i++){
                Pin output_pin = env[ cline[ind ++] ];
                Pin input_pin = {cur, i};
                output_pin.first->out[ output_pin.second ] = input_pin;
            }

            for(int i=0 ; i<box->outputs.size() ; i++){
                Pin output_pin = {cur, i};
                env[ cline[ind ++] ] = output_pin;
            }
        }

        for(auto output_name : box->outputs){
            Node *output = new Node(out_pin);
            graph->nodes.push_back(output);
            graph->sinks.push_back(output);
            Pin output_pin = env[output_name];
            output_pin.first->out[ output_pin.second ] = {output, 0};
        }

        box_to_graph[box] = graph;
    }

    return box_to_graph;
}

#endif