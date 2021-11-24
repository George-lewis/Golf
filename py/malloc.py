# Naive malloc implementation

class Allocator:

    def __init__(self, memsize: int):
        self.memsize = memsize * 8
        self.mem = [0] * memsize * 8
        self.freelist = [1] * memsize

    def _alloc(self, start: int, end: int):
        for i in range(start, end):
            self.freelist[i] = 0
            self.mem[i*8] = 1

    def alloc(self, req: int) -> (int, int):
        stride = None
        for i, free in enumerate(self.freelist):
            if not free:
                stride = None
                continue

            if stride is None:
                stride = i
            elif (i - stride) == req:
                self._alloc(stride, i)
                return (stride, i)

    def _free(self, start: int, end: int):
        for i in range(start, end):
            self.freelist[i] = 1
            self.mem[i*8] = 0

    def free(self, id: (int, int)):
        self._free(id[0], id[1])


alc = Allocator(32)
print(alc.alloc(3), alc.freelist)

print(alc.alloc(3), alc.freelist)
print(alc.alloc(3), alc.freelist)

x = alc.alloc(2)
print(alc.freelist)

print(alc.alloc(3), alc.freelist)

alc.free(x)
print(alc.freelist)
