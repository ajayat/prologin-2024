import sys
from collections import namedtuple, defaultdict

from typing import List

sys.setrecursionlimit(10000)

God = namedtuple('God', ('firstname', 'name'))

def dfs(adj, u, visited: set, firstnames: set, names: set):
    visited.add(u)
    firstname, name = False, False

    for v in adj[u]:
        if v in visited:
            continue
        if u == v:
            return False 
        if v.firstname == u.firstname:
            if firstname or v.name in names:
                return False
            firstname = True
        elif v.name == u.name:
            if name or v.firstname in firstnames:
                return False
            name = True
        else:
            return False
        
        if not dfs(adj, v, visited, firstnames, names):
            return False
        
    if not firstname:
        firstnames.add(u.firstname)
    if not name:
        names.add(u.name)

    return True
    
def valid_path(n: int, gods: List[str], m: int, passations: List[str]):
    """
    n: le nombre de dieux
    gods: liste des prénoms et noms des dieux séparés par un espace
    m: nombre de passations du message
    passations: liste des échanges de message entre les dieux, 
        les noms complets des deux dieux séparés par un espace
    """
    adj = defaultdict(list)
    for i in range(m):
        fn1, n1, fn2, n2 = passations[i].split()
        god1, god2 = God(fn1, n1), God(fn2, n2)
        adj[god1].append(god2)
        adj[god2].append(god1)
    
    print(adj)
    if m != n-1 or len(adj) != n:
        print("NON") # graph is not a tree
        return
    
    valid = False
    for god in adj:
        visited = set()
        firstnames, names = set(), set()
        if dfs(adj, god, visited, firstnames, names) and len(visited) == n:
            if not valid:
                print("OUI")
                valid = True
            print(god.firstname, god.name)

    if not valid:
        print("NON")

if __name__ == "__main__":
    n = int(input())
    gods = [input() for _ in range(n)]
    m = int(input())
    passations = [input() for _ in range(m)]
    valid_path(n, gods, m, passations)
    