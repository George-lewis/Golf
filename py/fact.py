#
# For comparing the speed of a regular recursive factorial to a cached recursive factorial
#

import time, sys

sys.setrecursionlimit(10**6) 

cache = { 0 : 1, 1 : 1 }

# cached
def cfact(n):

    if n in cache:
        return cache[n]

    res = n*fact(n-1)

    cache[n] = res

    return res

# regular
def fact(n):

  if n <= 1:
    return 1

  return n * fact(n-1)

def test(f, n = 1000):

  t = time.time()

  for i in range(n):
    f(i)

  print(f"Time elapsed: {time.time() - t}")

test(fact)

test(fact)

test(cfact)

test(cfact)

test(cfact, 10000)