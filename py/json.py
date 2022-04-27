# A very simple json parser
# Only works with minified json (no spaces)
# All values must have a comma on the end (even when it's the last kv pair)
# Will parse some invalid json forms, such as strings with no quotation marks
# Doesn't convert ints, etc
# This is probably quite slow

from typing import Union

def _next_key(s: str, st: int, ed: int) -> int:
    for i, c in enumerate(s[st:ed]):
            if c == ':':
                return st + i

def _next_value(s: str, st: int, ed: int) -> int:
    bcount = 0
    strn = False
    comm = False
    for i, c in enumerate(s[st:ed]):
        if c in ('{', '['):
            bcount += 1
        elif c in ('}', ']'):
            bcount -= 1
        elif c == '"':
            strn = not strn
        elif c == ',' or comm:
            comm = True
            if bcount == 0 and not strn:
                return st + i

def trim(s: str) -> str:
    return s.removeprefix('"').removesuffix('"')

def _parse(s: str, st: int = 0, ed: int = 0) -> Union[dict, list]:
    if s[st] == "{":
        st += 1
        ed -= 1
        data = {}
        while st < ed:
            col = _next_key(s, st, ed)
            key = trim(s[st + 1:col - 1])
            vidx = _next_value(s, col, ed)
            val = trim(s[col + 1: vidx])
            if val[0] in ('{', '['):
                val = parse(val)
            data[key] = val
            st = vidx + 1
        return data
    elif s[st] == '[':
        st += 1
        ed -= 1
        data = []
        while st < ed:
            idx = _next_value(s, st, ed)
            val = trim(s[st : idx])
            if val[0] in ('{', '['):
                val = parse(val)
            data.append(val)
            st = idx + 1
        return data
    else:
        raise ValueError

def parse(s: str):
    return _parse(s, 0, len(s))

x = parse('{"k":"v","b":"t","q":"r","m":{"t":"p",},"L":[5,7,"ff",],"Q":",,,","DDD D": f f f f,"obj":{"1":2,"3":4,"L":[1,2,3,{"a":"b",},],},}')

print(x)