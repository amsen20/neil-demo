import sys
from insts import Input, Label, Print
import sparser
from tools import get_ided

instructions = sparser.parse(sys.argv[1])

vars = set()
inputs = set()
outputs = set()
for instruction in instructions:
    for var in instruction['cls'].get_vars(instruction):
        vars.add(var)

neil = ""

def get_circuit(start):
    env = {'vars': vars, 'wire-id': 0}
    ret = ""
    for j in range(start, len(instructions)):
        ins = instructions[j]
        code, env = ins['cls'].get_circuit(env, ins)
        ret += code
    
    for id in range(env['wire-id']):
        for var in env['vars']:
            if id == 0:
                ls = var
            else:
                ls = get_ided(var, id-1)
            cur = get_ided(var, id)
            ret += "gate >- {} {} {}\n".format(ls, cur, ls)
    return ret

for i in range(len(instructions)):
    instruction = instructions[i]
    if instruction['cls'] == Input:
        inputs.add(instruction['arg'])
    if instruction['cls'] == Print:
        outputs.add(instruction['arg'])
    if instruction['cls'] == Label:
        neil += "def {}\n".format(instruction['name'])
        for var in vars:
            neil += "in {}\n".format(var)
        for var in vars:
            neil += "out {}\n".format(var)
        neil += get_circuit(i)

neil += "def main\n"
for var in inputs:
    neil += "in {}\n".format(var)
for var in vars:
    if var not in inputs:
        neil += "const {} -1\n".format(var)
for var in outputs:
    neil += "out {}\n".format(var)
neil += get_circuit(0)

print(neil)