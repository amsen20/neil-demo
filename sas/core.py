import sys, insts
from err import err
from insts import instructions_set, Label

def extract(instruction):
    for instruction_cls in insts.instructions_set:
        if instruction_cls.check(instruction):
            return instruction_cls.extract(instruction)

    err("invalid syntax " + str(instruction))

def get_function(instruction):
    def func(env):
        return instruction['cls'].func(env, instruction)
    return func, instruction

def get_env(instructions):
    labels = {}
    for i in range(len(instructions)):
        if instructions[i]['cls'] == Label:
            label = instructions[i]['name']
            if label in labels:
                err("same label duplication.")
            labels[label] = i
    return {
        "pc": 0,
        "labels": labels
    }