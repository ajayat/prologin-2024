from typing import List

MAX_VALUE = 1000

def counting_sort(k: int, n: int, array: List[int]) -> List[int]:
    counting = [0] * (MAX_VALUE + 1)
    sorted = [0] * n

    for i in range(k):
        for j in range(i, n, k):
            counting[array[j]] += 1

        j = i
        for v in range(MAX_VALUE+1):
            while counting[v] > 0:
                sorted[j] = v
                j += k
                counting[v] = counting[v] - 1
    return sorted

def is_sorted(n: int, array: List[int]) -> bool:
    for i in range(n-1):
        if array[i] > array[i + 1]:
            return False
    return True

def order(k: int, n: int, sizes: List[int]) -> None:
    """
    :param k: le nombre magique
    :param n: le nombre de personnes
    :param sizes: la liste des tailles de chaque personne
    """
    if is_sorted(n, counting_sort(k, n, sizes)):
        return "OUI"
    else:
        return "NON"


if __name__ == "__main__":
    k = int(input())
    n = int(input())
    sizes = list(map(int, input().split()))
    print(order(k, n, sizes))
