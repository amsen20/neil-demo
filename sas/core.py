import sys, insts
from err import err
from insts import instruction_set

def islabel(instruction):
    if len(instruction) == 1 and instruction[0][-1] == ':':
        return True
    return False

def isop(instruction):
    return instruction[0] in {"SET", "ADD", "SUB", "MUL", "CMP"}

def issame(ins, data):
    if ins['type'] != data['type']:
        return False
    if 'operation' in data:
        if 'operation' not in ins or ins['operation'] != data['operation']:
            return False
    return True

def isbranch(instruction):
    if len(instruction) != 3 or instruction[0] != "GOTO":
        return False
    return True

def extract(instruction):
    if islabel(instruction):
        return {
            'type': "label",
            'name': instruction[0][:-1]
        }
    if isop(instruction):
        return {
            'type': "operation",
            'operation': instruction[0],
            'target': instruction[1],
            'args': instruction[2:]
        }
    if isbranch(instruction):
        return {
            'type': "branch",
            'args': instruction[1:]
        }
    err("invalid syntax " + str(instruction))

def get_function(instruction):
    data = extract(instruction)
    for ins in instruction_set:
        if issame(ins, data):
            def func(env):
                return ins['func'](env, data)
            return func
    err("bad instruction: " + str(instruction))

def get_env(instructions):
    labels = {}
    for i in range(len(instructions)):
        if islabel(instructions[i]):
            label = extract(instructions[i])['name']
            if label in labels:
                err("same label duplication.")
            labels[label] = i
    return {
        "pc": 0,
        "labels": labels
    }