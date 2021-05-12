#
# DELANNOY NUMBERS
# https://codegolf.stackexchange.com/questions/225203
#

# def fact(n: int) -> int:
# 	out = 1
# 	for x in range(1, n+1):
# 		out *= x
# 	return out
# def ncr(n: int, r: int) -> int:
# 	return fact(n) // (fact(n-r) * fact(r))
# def D2(m: int, n: int) -> int:
# 	"""Calculate Delannoy number"""
# 	out = 0
# 	for k in range(min(m, n) + 1):
# 		out += ncr(m, k) * ncr(n, k) * 2**k
# 	return out

# def D(n,m):
# 	if 0 in [n,m]:
# 		return 1
# 	else:
# 		return D(n-1,m)+D(n-1,m-1)+D(n,m-1)

# Optimal Py solution (?)
D=lambda n,m:m*n<1or D(n-1,m)+D(n-1,m-1)+D(n,m-1)

# Driver
inp = input()
spl = [int(x) for x in inp.split(' ')]
n, m = spl
print(f"D({n}, {m}) = {D(n, m)}")
