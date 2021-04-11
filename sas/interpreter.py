import sys
import core, sparser

instructions = sparser.parse(sys.argv[1])

env = core.get_env(instructions)

for i in range(len(instructions)):
    instructions[i] = core.get_function( instructions[i] )

while env['pc'] < len(instructions):
    f, cls = instructions[ env['pc'] ]
    env = f(env)
