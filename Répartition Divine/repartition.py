from typing import List

X, Y, Z = 0, 0, 0

def hashe(value) -> None:
    global X, Y, Z
    X = (X * value + Z + 37) % 1000_000_007;
    Y = (X * 13 + 36 * Y + 257) % 1000_000_009;
    Z = (Y * value + 4 * value + X * X + 7) % 998_244_353;

def are_compatibles(cities: List[int], subcities: int, i: int, j: int):
    contested = subcities & cities[i] & cities[j]
    s = 0
    while contested:
        s += contested & 1
        contested >>= 1
    return s & 1 == 0

def r_subcities_delta(n, cities: List[int], subcities: int, delta: int):
    n_compatibles = 0
    for i in range(n):
        j = i ^ delta
        if i < j and are_compatibles(cities, subcities, i, j):
            n_compatibles += 2
    return n_compatibles
                           
def sum_compatible(n: int, cities: List[int], r: int):
    for _ in range(r):
        s = int(input(), 2)
        for delta in range(1, n):
            value = r_subcities_delta(n, cities, s, delta)
            print(value)
            hashe(value)
        print(X, Y, Z)

if __name__ == "__main__":
    v = int(input())
    n = int(input())
    cities = [int(input(), 2) for _ in range(n)]
    r = int(input())
    sum_compatible(n, cities, r)