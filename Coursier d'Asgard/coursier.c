#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct List {
    int pos;
    int array[3];
} List;

typedef struct Set {
    int size;
    char** array;
} Set; 

List* list_create(void)
{
    List* list = malloc(sizeof(List));
    list->pos = 0;
    return list;
}

bool list_append(List* list, int value)
{
    if (list->pos < 3) {
        list->array[list->pos++] = value;
        return true;
    }
    return false;
}

Set* set_create(int size)
{
    Set* set = malloc(sizeof(Set));
    set->size = 100*size;
    set->array = calloc(set->size, sizeof(char*));
    return set;
}

int hash(char* key, int size)
{
    int hash = 0;
    for (int i = 0; key[i] != '\0'; i++)
        hash = (hash * 31 + key[i]) % size;
    return hash;
}

void set_add(Set* set, char* key, char* value)
{
    int h = hash(key, set->size);
    int inc = 1;
    while (set->array[h] != NULL && strcmp(set->array[h], key)) {
        h = (h + inc) % set->size;
        inc *= 2;
    }
    set->array[h] = value;
}

bool set_contains(Set* set, char* key)
{
    int h = hash(key, set->size);
    int inc = 1;
    while (set->array[h] != NULL && strcmp(set->array[h], key)) {
        h = (h + inc) % set->size;
        inc *= 2;
    }
    return (set->array[h] != NULL) ? true : false;
}

void set_free(Set* set)
{
    free(set->array);
    free(set);
}

void set_clear(Set* set)
{
    for (int i = 0; i < set->size; i++)
        set->array[i] = NULL;
}

int find_god(char gods[][2][33], int n, char* firstname, char* name)
{
    for (int i = 0; i < n; i++)
        if (strcmp(gods[i][0], firstname) == 0 && 
            strcmp(gods[i][1], name) == 0)
            return i;
    return -1;
}

bool all(bool* arr, int n)
{
    for (int i = 0; i < n; i++)
        if (!arr[i])
            return false;
    return true;
}

void free_adj(List* adj[], int n)
{
    for (int i = 0; i < n; i++)
        free(adj[i]);
}

bool dfs(List** adj, char gods[][2][33], int u, bool* visited, Set* firstnames, Set* names)
{
    visited[u] = true;
    bool firstname = false, name = false;

    for (int i = 0; i < adj[u]->pos; i++) {
        int v = adj[u]->array[i];
        if (visited[v]) continue;
        if (u == v) return false;
        if (strcmp(gods[v][0], gods[u][0]) == 0) {
            if (firstname || set_contains(names, gods[v][1]))
                return false;
            firstname = true;
        }
        else if (strcmp(gods[v][1], gods[u][1]) == 0) {
            if (name || set_contains(firstnames, gods[v][0]))
                return false;
            name = true;
        }
        else return false;

        if (!dfs(adj, gods, v, visited, firstnames, names))
            return false;
    }
    if (!firstname)
        set_add(firstnames, gods[u][0], gods[u][0]);
    if (!name)
        set_add(names, gods[u][1], gods[u][1]);

    return true;
}

int main(void)
{
    int n;
    scanf("%d", &n);
    char gods[n][2][33];
    List* adj[n];
    for (int i = 0; i < n; i++) {
        scanf("%s %s", gods[i][0], gods[i][1]);
        adj[i] = list_create();
    }
    int m;
    scanf("%d", &m);
    if (m != n-1) {
        free_adj(adj, n);
        puts("NON");  // not a tree
        return 0;
    }
    char firstname1[33], name1[33], firstname2[33], name2[33];
    for (int i = 0; i < m; i++) {
        scanf("%s %s %s %s", firstname1, name1, firstname2, name2);
        int g1 = find_god(gods, n, firstname1, name1);
        int g2 = find_god(gods, n, firstname2, name2);
        if (g1 == -1 || g2 == -1
            || !list_append(adj[g1], g2) || !list_append(adj[g2], g1)) {
            free_adj(adj, n);
            puts("NON"); 
            return 0;
        }
    }
    bool visited[n];
    Set* firstnames = set_create(n);
    Set* names = set_create(n);
    bool valid = false;
    for (int i = 0; i < n; i++) {
        for (int i = 0; i < n; i++)
            visited[i] = false;
        set_clear(firstnames);
        set_clear(names);
        if (dfs(adj, gods, i, visited, firstnames, names) && all(visited, n)) {
            if (!valid) {
                puts("OUI");
                valid = true;
            }
            printf("%s %s\n", gods[i][0], gods[i][1]);
        }
    }
    if (!valid) 
        puts("NON");
        
    free_adj(adj, n);
    set_free(firstnames);
    set_free(names);
    return 0;
}