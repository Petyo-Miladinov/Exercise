#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 

#define RESIZE 2

struct pair_t {
    char *name; 
    int salary; 
    int years; 
}; 

struct hash_table_t {
    struct pair_t** pairs; 
    size_t size, capacity;  
}; 

size_t hash(char *key) {
    size_t len = strlen(key), total; 

    for(size_t i = 0; i < len; i++) {
        total += key[i]; 
    }

    return total; 
} 

struct hash_table_t *init_table(int size) {
    struct hash_table_t *new_table = (struct hash_table_t *)malloc(sizeof(struct hash_table_t)); 

    new_table->size = 0; 
    new_table->capacity = size; 

    return new_table; 
} 

void destroy_table(struct hash_table_t *table) {
    for(size_t i = 0; i < table->capacity; i++) {
        free(table->pairs[i]->name); 
    }
    free(table->pairs); 
    free(table); 
}

struct hash_table_t *resize(struct hash_table_t *table) {
    struct hash_table_t *new_table = (struct hash_table_t *)malloc(table->capacity * RESIZE); 

    for(size_t i = 0; i < table->capacity; i++) {
        strcpy(new_table->pairs[i]->name, table->pairs[i]->name); 
        new_table->pairs[i]->salary = table->pairs[i]->salary; 
        new_table->pairs[i]->years = table->pairs[i]->years; 
        new_table->size++; 
    }

    destroy_table(table); 

    return new_table; 
}

struct hash_table_t *add(struct hash_table_t *table, char *name, int salary, int years) {
    if(table->size == table->capacity) {
        resize(table); 
    } 

    size_t index = hash(name) % table->capacity; 

    for(size_t i = 0; i < table->capacity; i++) {
        if(!table->pairs[index]->name) 
            index = (index + 1) % table->capacity; 
        strcpy(table->pairs[index]->name, name); 
        table->pairs[index]->salary = salary; 
        table->pairs[index]->years = years; 
    }

    return table; 
}

int contains(struct hash_table_t *table, char *name) {
    if(table == NULL) 
        return 0; 
    
    size_t index = hash(name) % table->capacity; 

    for(size_t i = 0; i < table->capacity; i++) {
        if(table->pairs[index]->name == name) {
            return 1; 
        }
        index = (index + 1) % table->capacity; 
    }
    return 0; 
}

void print(struct hash_table_t *table, char *name, size_t salary, int years) {

}

int main() {

    // int n, m, j = 0, k = 0, salary, years; 
    // char line[50], name[30], bonus[2], *p = line; 
    // scanf("%d", &n); 

    // for(size_t i = 0; i < n; i++) {
    //     fflush(stdin); 
    //     gets(line); 
    //     while(*(line + j) != ' ') {
    //         name[k] = *(line + k);
    //         j++; 
    //         k++; 
    //     }
    //     j++; 
    //     k = 0; 

    //     // if(*(line + j) == ' ') 
    //     //     j++; 
    //     // if ( isdigit(*p) || ( (*p=='-'||*p=='+') && isdigit(*(p+1)) )) 
    //     //     salary = strtol(p, &p, 10); 
    // }

    char *name = malloc(10 * sizeof(char)); 
    int salary, years; 
    scanf("%s %d %d", name, &salary, &years); 
    printf("%s %d %d", name, salary, years); 

    return 0; 
}