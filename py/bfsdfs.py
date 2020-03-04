#######################################################################
# Demonstrates depth first search and breadth first search with trees #
#######################################################################

class node:

    def __init__(self, val, left = None, right = None):
        self.value = val
        self.left = left
        self.right = right

    def __str__(self):
        return str(self.value)

    __repr__ = __str__

def dfs(t):
    if t is not None:
        return [t] + dfs(t.left) + dfs(t.right)
    else:
        return []

def _bfs(t):
    if len(t) > 0:
        
        l = []

        for x in t:
            if x.left:
                l.append(x.left)
            if x.right:
                l.append(x.right)
        
        return t + bfs(l)

    else:
        return []

def bfs(t):
    if type(t) is not list:
        return _bfs([t])
    else:
        return _bfs(t)

if __name__ == '__main__':

    t = node(1, node(2, node(4), node(6)), node(3, node(8), node(10, node(6))))

    print(dfs(t))
    print(bfs(t))
