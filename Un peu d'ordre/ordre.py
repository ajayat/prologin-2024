from typing import List

def order(k: int, n: int, sizes: List[int]) -> None:
    """
    :param k: le nombre magique
    :param n: le nombre de personnes
    :param sizes: la liste des tailles de chaque personne
    """
    mapping = sorted(sizes)
    mapping_dict = {sizes[i]: [] for i in range(n)}
    for i in range(n):
        mapping_dict[mapping[i]].append(i)

    for i in range(n):
        wanted_pos = mapping_dict[sizes[i]]
        swap = False
        for index in wanted_pos:
            if (index - i) % k == 0:
                swap = True
        if (not swap):
            return "NON"
        
    return "OUI"


if __name__ == "__main__":
    k = int(input())
    n = int(input())
    sizes = list(map(int, input().split()))
    print(order(k, n, sizes))
