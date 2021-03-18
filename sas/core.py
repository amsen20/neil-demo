import sys, insts
from err import err
from insts import instructions_set, Label

def extract(instruction):
    for instruction_cls in insts.instructions_set:
        if instruction_cls.check(instruction):
            return instruction_cls.extract(instruction)

    err("invalid syntax " + str(instruction))

def get_function(instruction):
    data = extract(instruction)
    def func(env):
        return data['cls'].func(env, data)
    return func, data

def get_env(instructions):
    labels = {}
    for i in range(len(instructions)):
        if Label.check(instructions[i]):
            label = Label.extract(instructions[i])['name']
            if label in labels:
                err("same label duplication.")
            labels[label] = i
    return {
        "pc": 0,
        "labels": labels
    }