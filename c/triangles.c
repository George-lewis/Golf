////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Calculates number of unique triangles (i.e. where not all the side lengths are the same) using a hashtable //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <stdio.h>

typedef short triangle[3];

typedef struct {
    int cap, size;
    triangle** table;
} HashTable;

int hash(triangle t) {
    return t[0] + t[1] + t[2];
}

HashTable init(size_t n) {
    HashTable ht = { .cap = n, .size = 0 };
    ht.table = malloc(sizeof(triangle*) * n);
    for (int i = 0; i < n; i++) {
        ht.table[i] = calloc( n, sizeof(triangle) );
    }
    return ht;
}

void put(HashTable* ht, triangle t) {

    int idx = hash(t) % ht->cap;

    for (int i = 0; i < ht->cap; i++) {
        if (hash(ht->table[idx][i]) == hash(t)) {
            return;
        }
        if (ht->table[idx][i][0] == 0) {
            ht->table[idx][i][0] = t[0];
            ht->table[idx][i][1] = t[1];
            ht->table[idx][i][2] = t[2];
            ht->size++;
            break;
        }
    }

}

void free_table(HashTable* ht) {
    
    for (int i = 0; i < ht->cap; i++) {
        free(ht->table[i]);
    }
    
    free(ht->table);

}

int unique(triangle *tris, size_t n) {

    HashTable ht = init(n);

    for (int i = 0; i < n; i++) {
        put(&ht, tris[i]);
    }

    printf("There are %d unique triangle kinds\n", ht.size);

}

int main() {

    triangle t[] = {  
                    { 1, 1, 5 },
                    { 3, 3, 1 },
                    { 5, 5, 5 },
                    { 6, 6, 6 },
                    { 2, 2, 3 }
                };

    unique(t, sizeof(t) / sizeof(triangle));

}