#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static long long X = 0, Y = 0, Z = 0 ;  

bool bit_count(int number)
{
    int count = 0 ;
    while (number) {
        count += number & 1 ;
        number >>= 1 ;
    }
    return ((count & 1) == 0) ;
}

int R(int *cities, int subcities, int n, int delta)
{
    int nbr = 0 ;
    for (int i = 0 ; i < n ; i++) {
        int j = i ^ delta ;
        if (j < i && bit_count(cities[i] & cities[j] & subcities))
                nbr += 2 ;
    }
    return nbr ;
}

void hashe(int value) {
    X = (X * value + Z + 37) % 1000000007 ;
    Y = (X * 13 + 36 * Y + 257) % 1000000009 ;
    Z = (Y * value + 4 * value + X * X + 7) % 998244353 ;
}

int main() {
    int n, v, r ;
    scanf("%d\n%d", &v, &n) ;
    int* cities = malloc(n * sizeof(int)) ;
    char num[v] ;
    for (int i=0 ; i<n ; i++) {
        scanf("%s", num) ;
        cities[i] = strtoll(num, NULL, 2) ;
    }
    scanf("%d", &r) ;
    for (int i=0 ; i<r ; i++) {
        scanf("%s", num) ;
        int subcities = strtoll(num, NULL, 2) ;
        for (int delta = 1 ; delta < n ; delta++)
            hashe(R(cities, subcities, n, delta)) ;
        printf("%lld %lld %lld\n", X, Y, Z) ;
    }
    free(cities);
    return 0 ;
}