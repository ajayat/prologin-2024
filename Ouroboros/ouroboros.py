from collections import deque

class City:
    def __init__(self, name):
        self.name = name
        self.next = None
        self.prev = None

class Snake:
    def __init__(self):
        begin = City(input())
        self.head = begin
        self.stack = deque([])
        self.reverse = False
        
        current = begin
        for i in range(1, n):
            city = City(input())
            city.prev = current
            current.next = city
            current = city

        current.next = begin
        begin.prev = current

    def forward(self):
        if self.reverse:
            self.head = self.head.prev
        else:
            self.head = self.head.next

    def eat(self):
        self.stack.append(self.head)
        self.head.prev.next = self.head.next
        self.head.next.prev = self.head.prev
        self.forward()
    
    def back(self):
        self.reverse = not(self.reverse)
        self.forward()
        
    def insert(self):
        city = self.stack.pop()
        if self.reverse:
            self.head.next.prev = city
            city.prev = self.head
            city.next = self.head.next
            self.head.next = city
        else:
            self.head.prev.next = city
            city.prev = self.head.prev
            city.next = self.head
            self.head.prev = city
            
        self.head = city

    def print(self):
        begin = self.head
        print(begin.name)
        self.forward()

        while (self.head != begin):
            print(self.head.name)
            self.forward()
            

def final_situation(n: int, m: int) -> None:
    """
    :param n: le nombre de villes autour de Midgard
    :param m: le nombre d'années avant le Ragnarök
    """
    midgard = Snake(n)

    for action in input():
        if action == "A":
            midgard.forward()
        elif action == "M":
            midgard.eat()
        elif action == "R":
            midgard.back()
        elif action == "C":
            midgard.insert()

    midgard.print()


if __name__ == "__main__":
    n = int(input())
    m = int(input())
    final_situation(n, m)