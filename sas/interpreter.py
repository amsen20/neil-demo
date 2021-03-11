import sys, core

filename = sys.argv[1]

with open(filename, "r") as f:
    lines = f.read().split("\n")

instructions = []

for line in lines:
    content = line.split()
    tmp = []
    for it in content:
        if it.startswith("#"):
            break
        if not it.isspace():
            tmp.append(it)
        
    content = tmp
    if content:
        instructions.append(content)
print(instructions)
"""
for i in range(len(instructions)):
    instructions[i] = core.get_function( instructions[i] )

env = core.get_env(instructions)
while env['pc'] < len(instructions):
    env = instructions[ env['pc'] ](env)

print(env)
"""