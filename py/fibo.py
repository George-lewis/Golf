#
# For comparing the speed of a regular recursive fibonacci to a cached recursive fibonacci
#

import sys
import time

sys.setrecursionlimit(10 ** 6)

cache = {1: 1, 2: 1}


# cached
def cfibonacci(n):
    if n not in cache:
        cache[n] = cfibonacci(n - 1) + cfibonacci(n - 2)
    return cache[n]


# regular
def fibonacci(n):
    if n == 1 or n == 2:
        return 1
    return fibonacci(n - 1) + fibonacci(n - 2)


def test(f, n=35):
    t = time.time()
    f(n)
    print(f"Time elapsed: {time.time() - t}")


# takes a long time to run
test(fibonacci)

# this is a lot faster
test(cfibonacci)
