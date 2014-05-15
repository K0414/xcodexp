
class Node(object):

    def __init__(self, v):
        self.value = v
        self.neighbors = list()


class Solution(object):

    def __init__(self):
        self._visited = list()

    def clone_graph(self, node):
        if not node:
            return None

        cloned = Node(node.value)
        self._clone(node, cloned)

        return cloned


    def _clone(self, node, cloned):
        for c in node.neighbors:
            if self._visited[c]:
                continue

            n = Node(c.value)
            cloned.neighbors.append(n)
            self._visited.append(c)
            clone_graph(self, c, n)

