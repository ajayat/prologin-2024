#include <stdio.h>
#include <stdlib.h>

void buildings(int n, int r, int k, int* cities)
{
    for (int i = 0; i < r; i++) {
        int max = 0;
        for (int j = i; j < i + k; j++) {
            if (cities[j % n] > max)
                max = cities[j % n];
        }
        cities[i % n] = max;
    }
    for (int i = 0; i < n; i++)
        printf("%d ", cities[i]);
    printf("\n");
}

int main(void)
{
    int n, r, k;
    scanf("%d %d %d", &n, &r, &k);
    int* cities = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%d", &cities[i]);

    buildings(n, r, k, cities);
    free(cities);
    return 0;
}