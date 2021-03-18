from err import err

instructions_set = []

def register_instruction(cls):
    instructions_set.append(cls)
    return cls

def get_val(env, val :str):
    if val.isnumeric():
        return int(val)
    if not val in env:
        err("bad var name: " + str(val))
    return env[val]

def can_be_var(var :str):
    return var.isalpha() and var.islower()

@register_instruction
class Label:
    @staticmethod
    def extract(instruction):
        return {
            'cls': Label,
            'name': instruction[0][:-1],
        }

    @staticmethod
    def check(instruction):
        if len(instruction) == 1 and instruction[0][-1] == ':':
            return True
        return False

    @staticmethod
    def func(env, data):
        ret = env # TODO deep copy
        ret['pc'] += 1
        return ret

@register_instruction
class Set:
    @staticmethod
    def extract(instruction):
        return {
            'cls': Set,
            'target': instruction[1],
            'args': instruction[2:],
        }

    @staticmethod
    def check(instruction):
        return instruction[0] == "SET"

    @staticmethod
    def func(env, data):
        ret = env
        ret['pc'] += 1
        arg = get_val(env, data['args'][0])
        if can_be_var(data['target']):
            ret[ data['target'] ] = arg
            return ret
        else:
            err("set is not valid" + str(data))

@register_instruction
class Add:
    @staticmethod
    def extract(instruction):
        return {
            'cls': Add,
            'target': instruction[1],
            'args': instruction[2:]
        }

    @staticmethod
    def check(instruction):
        return instruction[0] == "ADD"

    @staticmethod
    def func(env, data):
        ret = env
        ret['pc'] += 1
        arg1 = get_val(env, data['args'][0])
        arg2 = get_val(env, data['args'][1])
        if can_be_var(data['target']):
            ret[ data['target'] ] = arg1 + arg2
            return ret
        else:
            err("set is not valid" + str(data))

@register_instruction
class Sub:
    @staticmethod
    def extract(instruction):
        return {
            'cls': Sub,
            'target': instruction[1],
            'args': instruction[2:]
        }

    @staticmethod
    def check(instruction):
        return instruction[0] == "SUB"

    @staticmethod
    def func(env, data):
        ret = env
        ret['pc'] += 1
        arg1 = get_val(env, data['args'][0])
        arg2 = get_val(env, data['args'][1])
        if can_be_var(data['target']):
            ret[ data['target'] ] = arg1 - arg2
            return ret
        else:
            err("set is not valid" + str(data))

@register_instruction
class Mul:
    @staticmethod
    def extract(instruction):
        return {
            'cls': Mul,
            'target': instruction[1],
            'args': instruction[2:]
        }

    @staticmethod
    def check(instruction):
        return instruction[0] == "MUL"

    @staticmethod
    def func(env, data):
        ret = env
        ret['pc'] += 1
        arg1 = get_val(env, data['args'][0])
        arg2 = get_val(env, data['args'][1])
        if can_be_var(data['target']):
            ret[ data['target'] ] = arg1 * arg2
            return ret
        else:
            err("set is not valid" + str(data))

@register_instruction
class Cmp:
    @staticmethod
    def extract(instruction):
        return {
            'cls': Cmp,
            'target': instruction[1],
            'args': instruction[2:]
        }

    @staticmethod
    def check(instruction):
        return instruction[0] == "CMP"

    @staticmethod
    def func(env, data):
        ret = env
        ret['pc'] += 1
        arg1 = get_val(env, data['args'][0])
        arg2 = get_val(env, data['args'][1])
        if can_be_var(data['target']):
            ret[ data['target'] ] = int(arg1 < arg2)
            return ret
        else:
            err("set is not valid" + str(data))

@register_instruction
class Goto:
    @staticmethod
    def extract(instruction):
        return {
            'cls': Goto,
            'args': instruction[1:]
        }

    @staticmethod
    def check(instruction):
        if len(instruction) != 3 or instruction[0] != "GOTO":
            return False
        return True

    @staticmethod
    def func(env, data):
        cond = get_val(env, data['args'][0])
        label = data['args'][1]
        if label not in env['labels']:
            err("invalid line label " + label)
        ret = env
        if not cond:
            ret['pc'] += 1
        else:
            ret['pc'] = env['labels'][label]
        return ret
