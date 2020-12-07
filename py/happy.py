from math import floor, log

_cache = {}

def _digits(x):
    return [ (x // (10**i) ) % 10 for i in range(floor(log(x, 10)), -1, -1) ]

def digits(x):
    if x in _cache:
        return _cache[x]
    d = _digits(x)
    _cache[x] = d
    return d

cache = {}

def __happy(x: int, history) -> bool:
    if x == 1:
        return True
    if x in history:
        return False
    return _happy(sum([y*y for y in digits(x)]), history + [x])

def _happy(x, history):
    if x in cache:
        return cache[x]
    d = __happy(x, history)
    cache[x] = d
    return d

def happy(x):
    return _happy(x, [])

for i in range(1, 100):
    print(f"{i} is {'happy' if happy(i) else 'not happy'}")

print(cache)
print(_cache)
