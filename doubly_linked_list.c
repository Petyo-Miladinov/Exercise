#include<stdio.h>
//#include<sys/types.h> 
#include<stdlib.h> 
#include<string.h>
#include<unistd.h> 

#define _XOPEN_SOURCE 600

struct node_t {
    int data; 
    struct node_t *next; 
    struct node_t *prev; 
};

void push(struct node_t **head, int new) {
    struct node_t *new_node = (struct node_t*)malloc(sizeof(struct node_t)); 

    new_node->data = new; 

    // if(!(*head)) {
    //     new_node->prev = NULL; 
    //     new_node->next = head; 
    // }

    // new_node = (*head);

    new_node->next = (*head); 
    new_node->prev = NULL; 

    if((*head) != NULL) 
        (*head)->prev = new_node; 

    (*head) = new_node;  
}

void insert_after(struct node_t *prev_node, int new) {
    if(prev_node == NULL) 
        printf("Can't perform this action!"); 
    
    struct node_t *new_node = (struct node_t*)malloc(sizeof(struct node_t)); 

    new_node->data = new; 

    new_node->next = prev_node->next; 

    prev_node->next = new_node; 

    new_node->prev = prev_node; 

    if(new_node->next != NULL) 
        new_node->next->prev = new_node; 
}

void append(struct node_t **head, int new) {
    struct node_t *new_node = (struct node_t*)malloc(sizeof(struct node_t)); 

    struct node_t *last; 

    new_node->data = new; 

    new_node->next = NULL; 

    if((*head) == NULL) {
        new_node->prev = NULL; 
        (*head) = new_node; 
        return; 
    }

    while(last->next != NULL) {
        last = last->next; 
    } 

    last->next = new_node; 

    new_node->prev = last; 

    return; 
}

void print_list(struct node_t *node) {
    struct node_t *last; 

    printf("Forward: "); 
    while(node != NULL) {
        printf("%d ", node->data); 
        last = node; 
        node = node->next; 
    }

    printf("\nReverse: "); 

    while(last != NULL) {
        printf("%d ", last->data); 
        last = last->prev; 
    }
    printf("\n"); 
}

int main() {

    printf("Done!\n");

    char *arr = "This should be typewritten!"; 

    int len = strlen(arr); 
 
    for(int i = 0; i < len; i++) {
        printf("%c", arr[i]); 
        usleep(100000); 
    }
    printf("\n"); 

    sleep(2); 

    fprintf(stdout, "Hello from fprintf!\n"); 

    return 0; 
}