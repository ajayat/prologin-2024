import sys
from copy import deepcopy

from typing import List

sys.setrecursionlimit(3000*3000)

class Graph:
    def __init__(self, n):
        self.n = n
        # 0 : no edge, 1 : edge, 2 : can be edge
        self.adj = [[0] * n for _ in range(n)]
        self.visited = [False] * n

    def set_edge(self, u, v, value):
        self.adj[u][v] = value
        self.adj[v][u] = value

    def dfs(self, v):
        self.visited[v] = True
        for i in range(self.n):
            if self.adj[v][i] == 1 and not self.visited[i]:
                self.dfs(i)

    def is_connected(self):
        self.dfs(0)
        connected = all(self.visited)
        for i in range(self.n):
            self.visited[i] = False
        return connected
    
    def is_leaf(self, v):
        for i in range(self.n):
            if self.adj[v][i] == 1:
                return False
        return True

    def pop_neighbor(self, u, value):
        for v in range(self.n):
            if self.adj[u][v] == value:
                self.adj[u][v] = 0
                self.adj[v][u] = 0
                return v
        return -1

    def has_possible_move(self, v):
        for i in range(self.n):
            if self.adj[v][i] == 2 and not self.visited[i]:
                return True
        return False

def path_exists(graph, u, parent):
    graph.visited[u] = True

    while not graph.is_leaf(u):
        v = graph.pop_neighbor(u, 1)
        if not path_exists(graph, v, u):
            return False
    
    if parent is None:
        return True
    
    return not graph.has_possible_move(u)


def valid_path(n: int, gods: List[str], m: int, passations: List[str]):
    """
    n: le nombre de dieux
    gods: liste des prénoms et noms des dieux séparés par un espace
    m: nombre de passations du message
    passations: liste des échanges de message entre les dieux, 
        les noms complets des deux dieux séparés par un espace
    """
    for i in range(n):
        gods[i] = gods[i].split()

    graph = Graph(n)
    for i in range(n):
        for j in range(n):
            if i != j and gods[i][0] == gods[j][0] or gods[i][1] == gods[j][1]:
                graph.set_edge(i, j, 2)

    for i in range(m):
        firstname1, name1, firstname2, name2 = passations[i].split()
        if firstname1 != firstname2 and name1 != name2:
            print("NON")
            return
        for j in range(n):
            if gods[j] == [firstname1, name1]:
                god1 = j
            if gods[j] == [firstname2, name2]:
                god2 = j
        graph.set_edge(god1, god2, 1)
    
    if not graph.is_connected() or m != n-1:
        print("NON") # graph is not a tree
        return

    valid = False
    for i in range(n):
        graph_copy = deepcopy(graph)
        if path_exists(graph_copy, i, None):
            if not valid:
                print("OUI")
                valid = True
            print(gods[i][0], gods[i][1])

    if not valid:
        print("NON")

if __name__ == "__main__":
    n = int(input())
    gods = [input() for _ in range(n)]
    m = int(input())
    passations = [input() for _ in range(m)]
    valid_path(n, gods, m, passations)
