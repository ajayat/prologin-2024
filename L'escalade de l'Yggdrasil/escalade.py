from math import inf
from typing import List


def biggest_jump(n: int, differences: List[int]) -> None:
    """
    Parameters:
        n: le nombre de branches de l'arbre moins 1
        differences: la liste des différences en hauteur des branches consécutives
    """
    max_jump_before = 0
    max_jump = -inf
    cum_sum = 0
    max_cum_sum = -inf

    for i in range(n):
        cum_sum += differences[i]
        if differences[i] > max_jump:
            max_jump = differences[i]
        if cum_sum > max_cum_sum:
            max_cum_sum = cum_sum
            max_jump_before = max_jump

    return max_jump_before

if __name__ == "__main__":
    n = int(input())
    differences = list(map(int, input().split()))
    max_jump = biggest_jump(n, differences)
    print(max_jump)
