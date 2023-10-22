from typing import List


def buildings(n: int, r: int, k: int, villes: List[int]) -> None:
    """
    :param n: le nombre de villes
    :param r: le nombre de mouvements du serpent
    :param k: le nombre de villes impliquées dans chaque mouvement
    :param villes: le nombre de bâtiments cassés dans chaque ville
    """
    solution = villes.copy()
    maximum = [0] * k
    inc = 0
    head = 0

    for i in range(k - 1 + r):
        x = solution[i % n]
        if x >= maximum[head]:
            maximum[0] = x
            head = 0
            inc = 1
        else:
            if inc >= k:
                maximum[head] = x
                head = (head + 1) % k
            else:
                maximum[inc] = x
                inc += 1

        if i >= k - 1:
            solution[(i - k + 1) % n] = maximum[head]

    return solution


if __name__ == "__main__":
    n = int(input())
    r = int(input())
    k = int(input())
    villes = list(map(int, input().split()))
    print(*buildings(n, r, k, villes))
