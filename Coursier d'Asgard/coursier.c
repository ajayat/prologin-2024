#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct List {
    int value;
    struct List* next;
} List;

List* list_prepend(List* list, int value)
{
    List* new = malloc(sizeof(List));
    new->value = value;
    new->next = list;
    return new;
}

void list_free(List* list)
{
    while (list != NULL) {
        List* next = list->next;
        free(list);
        list = next;
    }
}

bool all(bool* arr, int n)
{
    for (int i = 0; i < n; i++)
        if (!arr[i])
            return false;
    return true;
}

bool has_possible_move(int u, int n, bool* visited, int** possibles)
{
    for (int i = 0; i < n; i++)
        if (!visited[i] && possibles[u][i])
            return true;
    return false;
}

bool path_exists(List** adj, int n, int u, bool* visited, int** possibles)
{
    visited[u] = true;
    for (List* v = adj[u]; v != NULL; v = v->next)
        if (!visited[v->value]) {
            if (!path_exists(adj, n, v->value, visited, possibles))
                return false;
        }
    return !has_possible_move(u, n, visited, possibles);
}

int main(void)
{
    int n;
    scanf("%d", &n);
    char gods[n][2][33];
    for (int i = 0; i < n; i++)
        scanf("%s %s", gods[i][0], gods[i][1]);

    int m;
    scanf("%d", &m);
    bool* visited = calloc(n, sizeof(bool));
    List** adj = calloc(n, sizeof(List*));
    bool valid = true;

    char firstname1[33], name1[33], firstname2[33], name2[33];
    for (int i = 0; i < m; i++) {
        scanf("%s %s %s %s", firstname1, name1, firstname2, name2);
        if (!valid) 
            continue;
        if (strcmp(firstname1, firstname2) && strcmp(name1, name2))
            valid = false;
        int j = 0;
        int god1 = -1, god2 = -1;
        while (god1 < 0 || god2 < 0) {
            puts("----------");
            printf("%s %s\n", gods[j][0], gods[j][1]);
            printf("%s %s\n", firstname1, name1);
    
            if (strcmp(gods[j][0], firstname1) == 0 && 
                strcmp(gods[j][1], name1) == 0)
                god1 = j;
            else if (strcmp(gods[j][0], firstname2) == 0 && 
                strcmp(gods[j][1], name2) == 0)
                god2 = j;
            j++;
        }
        visited[god1] = visited[god2] = true;
        adj[god1] = list_prepend(adj[god1], god2);
        adj[god2] = list_prepend(adj[god2], god1);
    }
    puts("ok");
    if (!valid || m != n-1 || !all(visited, n)) {
        puts("NON");  // not a tree
        goto end;
    }
    int** possibles = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        possibles[i] = calloc(n, sizeof(int));
        for (int j = 0; j < i; j++) {
            if (strcmp(gods[i][0], gods[j][0]) == 0 || 
                strcmp(gods[i][1], gods[j][1]) == 0) {
                possibles[i][j] = possibles[j][i] = 1;
            }
        }
    }
    valid = false;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; i++)
            visited[j] = false;
        if (path_exists(adj, n, i, visited, possibles) && all(visited, n)) {
            if (!valid) {
                puts("OUI");
                valid = true;
            }
            printf("%s %s\n", gods[i][0], gods[i][1]);
        }
    }
    if (!valid) puts("NON");
end:
    for (int i = 0; i < n; i++) {
        list_free(adj[i]);
    }
    free(adj);
    free(visited);
    return 0;
}
