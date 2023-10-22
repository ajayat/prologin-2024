#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct City {
    char name[10];
    struct City* next;
    struct City* prev;
} City;

typedef struct Snake {
    City* head;
    City* stomach;
    bool reverse;
} Snake;

City* create_city() 
{
    City* c = malloc(sizeof(City));
    if (c == NULL)
        return NULL;
    scanf("%s\n", c->name);
    c->next = NULL;
    c->prev = NULL;
    return c;
}

Snake* create_snake(int n) 
{
    Snake* snake = malloc(sizeof(Snake));
    City* first = create_city();
    assert(first != NULL);
    snake->head = first;
    snake->stomach = NULL;
    snake->reverse = false;

    City* current = first;
    for (int i = 1; i < n; i++) {
        City* city = create_city();
        assert(city != NULL);
        city->prev = current;
        current->next = city;
        current = city;
    }
    current->next = first;
    first->prev = current;
    return snake;
}

void forward(Snake* snake) 
{
    assert(snake->head != NULL);
    if (snake->reverse)
        snake->head = snake->head->prev;
    else
        snake->head = snake->head->next;
}

void back(Snake* snake) 
{
    snake->reverse = !snake->reverse;
    forward(snake);
}

void eat(Snake* snake) 
{
    City* c = snake->head;
    // adjust links
    snake->head->prev->next = snake->head->next;
    snake->head->next->prev = snake->head->prev;
    forward(snake);
    // add head to stomach stack
    c->next = snake->stomach;
    snake->stomach = c;
}

void insert(Snake* snake)
{
    // remove head from stomach stack
    City* c = snake->stomach;
    assert(c != NULL);
    snake->stomach = snake->stomach->next;
    // adjust links
    if (snake->reverse) {
        c->prev = snake->head;
        c->next = snake->head->next;
        snake->head->next->prev = c;
        snake->head->next = c;
    } else {
        c->prev = snake->head->prev;
        c->next = snake->head;
        snake->head->prev->next = c;
        snake->head->prev = c;
    }
    snake->head = c;
}

void print_snake(Snake* snake) 
{
    City* first = snake->head;
    do {
        printf("%s\n", snake->head->name);
        forward(snake);
    } while (snake->head != first);
}

void free_snake(Snake* snake) 
{
    City* first = snake->head;
    forward(snake);

    while (snake->head != first) {
        City* c = snake->head;
        forward(snake);
        free(c);
    }
    free(first);
    free(snake);
}

/**
n: le nombre de villes autour de Midgard
m: le nombre d'années avant le Ragnarök
*/
void ragnarok(int n, int m) 
{
    Snake* snake = create_snake(n);

    char c;
    for (int i = 0; i < m; i++) {
        scanf("%c", &c);
        if (c == 'A')
            forward(snake);
        else if (c == 'M')
            eat(snake);
        else if (c == 'R')
            back(snake);
        else if (c == 'C')
            insert(snake);
    }
    print_snake(snake);
    free_snake(snake);
}

int main() 
{
    int n, m;
    scanf("%d %d\n", &n, &m);
    ragnarok(n, m);
    return 0;
}