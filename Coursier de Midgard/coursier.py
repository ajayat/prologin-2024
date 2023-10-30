from collections import defaultdict, deque

def hierholzer(firstnames, lastnames, origin, is_firstname):
    stack = deque([(origin, is_firstname)])
    circuit = deque()

    while stack:
        u, is_firstname = stack[-1]
        if is_firstname:
            if firstnames.get(u, False):
                v = firstnames[u].pop()
                lastnames[v].remove(u)
                stack.append((v, False))
            else:
                stack.pop()
                circuit.appendleft(u)
        else:
            if lastnames.get(u, False):
                v = lastnames[u].pop()
                firstnames[v].remove(u)
                stack.append((v, True))
            else:
                stack.pop()
                circuit.appendleft(u)
    
    return circuit

def print_path(n: int, gods: list):
    """
    n: le nombre de dieux
    gods: liste des prénoms et noms des dieux
    """
    firstnames = defaultdict(set)
    lastnames = defaultdict(set)

    for god in gods:
        firstname, name = god.split()
        firstnames[firstname].add(name)
        lastnames[name].add(firstname)

    odd_count = 0
    origin, is_firstname = firstname, True

    for u in firstnames:
        if len(firstnames[u]) & 1 == 1:
            odd_count += 1
            origin, is_firstname = u, True
    for u in lastnames:
        if len(lastnames[u]) & 1 == 1:
            odd_count += 1
            origin, is_firstname = u, False
    
    if odd_count != 0 and odd_count != 2:
        print("IMPOSSIBLE")  # not Eulerian
        return

    circuit = hierholzer(firstnames, lastnames, origin, is_firstname)
    if len(circuit) != n+1:
        print("IMPOSSIBLE")  # not connected
        return
    
    previous = circuit.popleft()
    for current in circuit:
        if is_firstname:
            print(previous, current)
        else:
            print(current, previous)
        is_firstname = not(is_firstname)
        previous = current

if __name__ == "__main__":
    n = int(input())
    gods = [input() for _ in range(n)]
    print_path(n, gods)