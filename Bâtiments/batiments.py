from typing import List

class CircularQueue:
    def __init__(self, k: int):
        self.queue = [0] * k
        self._head = 0
        self.length = 0
        self.size = k
    
    def enqueue(self, x: int):
        self.queue[(self._head + self.length) % self.size] = x
        self.length += 1

    def pop(self):
        self.length -= 1
    
    def popleft(self):
        self._head = (self._head + 1) % self.size
        self.length -= 1

    def head(self) -> int:
        return self.queue[self._head]

    def tail(self) -> int:
        return self.queue[(self._head + self.length - 1) % self.size]
    
    def clear(self):
        self._head = 0
        self.length = 0


def buildings(n: int, r: int, k: int, cities: List[int]) -> None:
    """
    :param n: le nombre de villes
    :param r: le nombre de mouvements du serpent
    :param k: le nombre de villes impliquées dans chaque mouvement
    :param cities: le nombre de bâtiments cassés dans chaque ville
    """
    maximum = CircularQueue(k)

    for i in range(k - 1 + r):
        x = cities[i % n]

        if x >= cities[maximum.head() % n]:
            maximum.clear()
        else:
            while maximum.length > 0 and maximum.head() <= i - k:
                maximum.popleft()
                           
            while cities[maximum.tail() % n] < x:
                maximum.pop()
        maximum.enqueue(i)

        if i >= k - 1:
            cities[(i - k + 1) % n] = cities[maximum.head() % n]

    return cities


if __name__ == "__main__":
    n = int(input())
    r = int(input())
    k = int(input())
    cities = list(map(int, input().split()))
    print(*buildings(n, r, k, cities))
