from typing import List, Tuple

class Q1:
    """
    Given a sorted array of numbers and a value k,
    return an array of the numbers sorted based on distance from k
    """


    def s1(l: List[int], k: int) -> List[int]:
        

        def _split() -> Tuple[List[int], List[int]]:
            def __center() -> int:
                for i in range(len(l) - 1):
                    if l[i] < k < l[i + 1]:
                        return i
                return len(l)

            idx = __center()

            return list(reversed(l[:idx])), l[idx:]

        def _merge(l1, l2) -> List[int]:
            out = []
            while l1 or l2:
                if not l1:
                    out.append(l2.pop(0))
                elif not l2:
                    out.append(l1.pop(0))
                elif abs(l1[0] - k) < abs(l2[0] - k):
                    out.append(l1.pop(0))
                else:
                    out.append(l2.pop(0))
            return out

        first, second = _split()

        return _merge(first, second)

    def s2(l: List[int], k: int) -> List[int]:
        return list(map(lambda z: z[1], sorted(map(lambda x: (abs(x - k), x), l), key=lambda y: y[0])))

print(Q1.s1([-10, 0, 1, 4.1, 10], 2))
print(Q1.s2([-10, 0, 1, 4.1, 10], 2))
