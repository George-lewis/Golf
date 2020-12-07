def disjoint(L):
    out = []
    for i in range(2**len(L)):
        a = []
        b = []
        for j in range(len(L)):
            if (i & (1 << j)):
                a.append(L[j])
            else:
                b.append(L[j])
        out.append((a, b))
    return out

print(disjoint([1,2,3,4,5]))
