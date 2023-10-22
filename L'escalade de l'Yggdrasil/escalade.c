#include <stdio.h>

int biggest_jump(int n)
{
    int max_jump_before = 0;
    int max_jump = -1;
    int cum_sum = 0;
    int max_cum_sum = -1;

    for (int i = 0; i < n; i++) {
        int jump;
        scanf("%d", &jump);
        cum_sum += jump;

        if (jump > max_jump)
            max_jump = jump;

        if (cum_sum > max_cum_sum) {
            max_cum_sum = cum_sum;
            max_jump_before = max_jump;
        }
    }
    return max_jump_before;
}

int main(void)
{
    int n;
    scanf("%d", &n);
    printf("%d\n", biggest_jump(n));
    return 0;
}