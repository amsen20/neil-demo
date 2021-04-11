import core

def parse(path):
    with open(path, "r") as f:
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
        
    return [core.extract(ins) for ins in instructions]