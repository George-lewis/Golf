# There's a staircase with N steps and you can x \in X
# steps at a time. The order of the steps matters.
# How many unique ways can you climb the staircase?

def staircase_rec(N: int, X: set[int]):
    def _staircase(n):
        if n == 0:
            return 1
        if n < 0:
            return 0

        return sum(_staircase(n - x) for x in X)

    return _staircase(N)

def staircase_opt(N: int, X: set[int]):
    OPT = [1] + [0] * N
    for n in range(1, N+1):
        for x in X:
            OPT[n] += OPT.get
            nx = n - x
            if nx < 0:
                continue

            OPT[n] += OPT[nx]

    return OPT[-1]

if __name__ == '__main__':
    assert staircase_rec(4, {1, 2}) == staircase_opt(4, {1, 2}) == 5
