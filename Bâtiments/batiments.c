#include <stdio.h>
#include <stdlib.h>

typedef struct CircularQueue {
    int* queue;
    int head;
    int length;
    int size;
} CircularQueue;

CircularQueue* queue_create(int k)
{
    CircularQueue* q = malloc(sizeof(CircularQueue));
    q->queue = calloc(k, sizeof(int));
    q->head = 0;
    q->length = 0;
    q->size = k;
    return q;
}

void queue_enqueue(CircularQueue* queue, int x)
{
    queue->queue[(queue->head + queue->length) % queue->size] = x;
    queue->length++;
}

void queue_pop(CircularQueue* queue)
{
    queue->length--;
}

void queue_popleft(CircularQueue* queue)
{
    queue->head = (queue->head + 1) % queue->size;
    queue->length--;
}

int queue_head(CircularQueue* queue)
{
    return queue->queue[queue->head];
}

int queue_tail(CircularQueue* queue)
{
    int pos = queue->head + queue->length - 1;
    return queue->queue[(pos + queue->size) % queue->size];
}

void queue_clear(CircularQueue* queue)
{
    queue->head = 0;
    queue->length = 0;
}

void queue_free(CircularQueue* queue)
{
    free(queue->queue);
    free(queue);
}

void buildings(int n, int r, int k, int* cities)
{
    CircularQueue* maximum = queue_create(k);
    
    for (int i = 0; i < k - 1 + r; i++) {
        int x = cities[i % n];

        if (x >= cities[queue_head(maximum) % n])
            queue_clear(maximum);
        else {
            while (maximum->length > 0 && queue_head(maximum) <= i - k)
                queue_popleft(maximum);

            while (cities[queue_tail(maximum) % n] < x)
                queue_pop(maximum);
        }
        queue_enqueue(maximum, i);

        if (i >= k - 1)
            cities[(i - k + 1) % n] = cities[queue_head(maximum) % n];
    }

    for (int i = 0; i < n; i++)
        printf("%d ", cities[i]);
    
    queue_free(maximum);
}

int main(void)
{
    int n, r, k;
    scanf("%d %d %d", &n, &r, &k);
    int cities[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &cities[i]);

    buildings(n, r, k, cities);
    return 0;
}