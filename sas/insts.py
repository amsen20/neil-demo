from err import err

instruction_set = []

def register_instruction(**kwargs):
    def decorator_register_instruction(func):
        instruction_set.append({
            **kwargs,
            'func': func
        })
        return func
    return decorator_register_instruction

def get_val(env, val :str):
    if val.isnumeric():
        return int(val)
    if not val in env:
        err("bad var name: " + str(val))
    return env[val]

def can_be_var(var :str):
    return var.isalpha() and var.islower()

@register_instruction(type='label')
def __label(env, data):
    ret = env # TODO deep copy
    ret['pc'] += 1
    return ret

@register_instruction(type='operation', operation='SET')
def __set(env, data):
    ret = env
    ret['pc'] += 1
    arg = get_val(env, data['args'][0])
    if can_be_var(data['target']):
        ret[ data['target'] ] = arg
        return ret
    else:
        err("set is not valid" + str(data))

@register_instruction(type='operation', operation='ADD')
def __add(env, data):
    ret = env
    ret['pc'] += 1
    arg1 = get_val(env, data['args'][0])
    arg2 = get_val(env, data['args'][1])
    if can_be_var(data['target']):
        ret[ data['target'] ] = arg1 + arg2
        return ret
    else:
        err("set is not valid" + str(data))

@register_instruction(type='operation', operation='SUB')
def __sub(env, data):
    ret = env
    ret['pc'] += 1
    arg1 = get_val(env, data['args'][0])
    arg2 = get_val(env, data['args'][1])
    if can_be_var(data['target']):
        ret[ data['target'] ] = arg1 - arg2
        return ret
    else:
        err("set is not valid" + str(data))

@register_instruction(type='operation', operation='MUL')
def __mul(env, data):
    ret = env
    ret['pc'] += 1
    arg1 = get_val(env, data['args'][0])
    arg2 = get_val(env, data['args'][1])
    if can_be_var(data['target']):
        ret[ data['target'] ] = arg1 * arg2
        return ret
    else:
        err("set is not valid" + str(data))

@register_instruction(type='operation', operation='CMP')
def __cmp(env, data):
    ret = env
    ret['pc'] += 1
    arg1 = get_val(env, data['args'][0])
    arg2 = get_val(env, data['args'][1])
    if can_be_var(data['target']):
        ret[ data['target'] ] = int(arg1 < arg2)
        return ret
    else:
        err("set is not valid " + str(data))

@register_instruction(type='branch')
def __goto(env, data):
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
