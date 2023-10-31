from typing import List

X, Y, Z = 0, 0, 0

def hashe(value) -> None:
    global X, Y, Z
    X = (X * value + Z + 37) % 1000_000_007;
    Y = (X * 13 + 36 * Y + 257) % 1000_000_009;
    Z = (Y * value + 4 * value + X * X + 7) % 998_244_353;

def are_compatibles(cities: List[int], subcities: int, god1: int, god2: int):
    contested = subcities & cities[god1] & cities[god2]
    s = 0
    while contested:
        s += contested & 1
        contested >>= 1
    return s & 1 == 0

def r_subcities_delta(n, cities: List[int], subcities: int, delta: int):
    couples = {frozenset({i, i^delta}) for i in range(n)}
    n_compatibles = 0
    for god1, god2 in couples:
        if are_compatibles(cities, subcities, god1, god2):
            n_compatibles += 1
    return n_compatibles * 2
                           
def sum_compatible(v: int, n: int, cities: List[int], r: int, requests: List[int]):
    for s in requests:
        for delta in range(1, n):
            hashe(r_subcities_delta(n, cities, s, delta))
        print(X, Y, Z)
        

if __name__ == "__main__":
    v = int(input())
    n = int(input())
    cities = [int(input(), 2) for _ in range(n)]
    r = int(input())
    requests = [int(input(), 2) for _ in range(r)]
    sum_compatible(v, n, cities, r, requests)