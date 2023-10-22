#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_VALUE 1000

int* counting_sort(int k, int n, int* array)
{
    int counting[MAX_VALUE + 1] = {0};
    int* sorted = calloc(n, sizeof(int));

    for (int i = 0; i < k; i++) {
        for (int j = i; j < n; j += k)
            counting[array[j]]++;
        
        int j = i;
        for (int v = 0; v <= MAX_VALUE; v++) {
            while (counting[v] > 0) {
                sorted[j] = v;
                j += k;
                counting[v]--;
            }
        }
    }
    return sorted;
}

bool is_sorted(int n, int* array)
{
    for (int i = 1; i < n; i++) {
        if (array[i-1] > array[i])
            return false;
    }
    return true;
}

void order(int k, int n, int* sizes)
{
    int* sorted = counting_sort(k, n, sizes);
    if (is_sorted(n, sorted))
        puts("OUI");
    else
        puts("NON");
    free(sorted);
}

int main(void)
{
    int k, n;
    scanf("%d %d", &k, &n);
    int* sizes = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%d", &sizes[i]);

    order(k, n, sizes);
    free(sizes);
    return 0;
}