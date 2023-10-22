#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_VALUE 1000

typedef struct couple {
    int begin;
    int end;
} couple;

int compare(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}

char* order(int k, int n, int* sizes)
{
    int* sizes_sorted = malloc(n * sizeof(int));
    memcpy(sizes_sorted, sizes, n * sizeof(int));
    qsort(sizes_sorted, n, sizeof(int), compare);

    couple* mapping = malloc(MAX_VALUE * sizeof(couple));
    for (int i = 0; i < n;) {
        int end = i+1;
        while (end < n && sizes_sorted[end] == sizes_sorted[i])
            end++;
        mapping[sizes_sorted[i]] = (couple){.begin = i, .end = end};
        i = end;
    }

    for (int i = 0; i < n; i++) {
        couple wanted = mapping[sizes[i]];
        bool swap = false;
        for (int pos = wanted.begin; pos < wanted.end; pos++) {
            if ((pos - i + k) % k == 0)
                swap = true;
        }
        if (!swap) {
            free(sizes_sorted);
            free(mapping);
            return "NON";
        }
    }
    free(sizes_sorted);
    free(mapping);
    return "OUI";
}

int main(void)
{
    int k, n;
    scanf("%d %d", &k, &n);
    int* sizes = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%d", &sizes[i]);

    printf("%s\n", order(k, n, sizes));
    free(sizes);
    return 0;
}