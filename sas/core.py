import sys, insts
from err import err
from insts import instruction_set

def islabel(instruction):
    if len(instruction) == 1 and instruction[:-1] == ':':
        return True
    return False

def isop(instruction):
    return instruction[0] in {"SET", "ADD", "SUB", "MUL", "CMP"}

def issame(ins, data):
    if ins['type'] != data['type']:
        return False
    if 'operation' in data:
        if 'operation' not in ins or ins['operation'] == data['operation']:
            return False
    return True

def extract(instruction):
    if islabel(instruction):
        return {
            'type': "label",
            'name': instruction[0][-1]
        }
    if isop(instruction):
        return {
            'type': "operation",
            'operation': instruction[0],
            'target': instruction[1],
            'args': instruction[2:]
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

def get_env(instructions): # TODO
    return {
        "pc": 0
    }