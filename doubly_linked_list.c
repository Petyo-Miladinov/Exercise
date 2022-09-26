#include<stdio.h>
#include<stdlib.h> 
#include<string.h>
#include<stdbool.h>
#include<unistd.h> 

//#define _XOPEN_SOURCE 600

struct node_t {
    int data; 
    struct node_t *next; 
    struct node_t *prev; 
};

struct tree_t {
    int data; 
    struct tree_t *left, *right; 
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
// ********************** Linked List ********************** 

void moveToFront(struct node_t **head_ref) {
    if (*head_ref == NULL || (*head_ref)->next == NULL)
        return;

    struct node_t* sec_last = NULL;
    struct node_t* last = *head_ref;

    while (last->next != NULL) {
        sec_last = last;
        last = last->next;
    }

    sec_last->next = NULL;

    last->next = *head_ref;

    *head_ref = last;
}

bool iter_search(struct node_t* head, int x) {
    struct node_t* current = head; 
    while (current != NULL) {
        if (current->data == x)
            return true;
        current = current->next;
    }
    return false;
}

bool recur_search(struct node_t* head, int x) {
    if (head == NULL)
        return false;

    if (head->data == x)
        return true;

    return recur_search(head->next, x);
}

int get_nth(struct node_t* head, int index) {
 
    struct node_t* current = head;

    int count = 0;
    while (current != NULL) {
        if (count == index)
            return (current->data);
        count++;
        current = current->next;
    }

    return 0; 
}

/* Counts the no. of occurrences of a node
   (search_for) in a linked list (head)*/
int count(struct node_t* head, int search) {
    struct node_t* current = head;
    int count = 0;

    while (current != NULL) {
        if (current->data == search)
            count++;
        current = current->next;
    }
    return count;
}

void printMiddle(struct node_t* head) {
    int count = 0;
    struct node_t* mid = head;
 
    while (head != NULL) {
        if (count & 1)
            mid = mid->next;
 
        ++count;
        head = head->next;
    }
 
    if (mid != NULL)
        printf("The middle element is [%d]\n\n", mid->data);
}

// ********************** Is Palindrome **********************

void reverse(struct node_t **head); 
bool compareLists(struct node_t *a, struct node_t *b); 

bool isPalindrome(struct node_t *head) { 
    struct node_t *slow_ptr = head, *fast_ptr = head; 
    struct node_t *second_half, *prev_of_slow_ptr = head; 
    struct node_t *midnode = NULL; 
    bool res = true; 
  
    if (head != NULL && head->next != NULL) { 
        while (fast_ptr != NULL && fast_ptr->next != NULL) { 
            fast_ptr = fast_ptr->next->next; 
            prev_of_slow_ptr = slow_ptr; 
            slow_ptr = slow_ptr->next; 
        } 
        if (fast_ptr != NULL) { 
            midnode = slow_ptr; 
            slow_ptr = slow_ptr->next; 
        } 
        second_half = slow_ptr; 
        prev_of_slow_ptr->next = NULL; 
        reverse(&second_half); 
        res = compareLists(head, second_half); 
        reverse(&second_half); 
  
        if (midnode != NULL) { 
            prev_of_slow_ptr->next = midnode; 
            midnode->next = second_half; 
        } 
        else
            prev_of_slow_ptr->next = second_half; 
    } 
    return res; 
} 

void reverse(struct node_t **head_ref)  { 
    struct node_t *prev = NULL; 
    struct node_t *current = *head_ref; 
    struct node_t *next; 
    while (current != NULL) { 
        next = current->next; 
        current->next = prev; 
        prev = current; 
        current = next; 
    } 
    *head_ref = prev; 
} 

bool compareLists(struct node_t* head1, struct node_t* head2)  { 
    struct node_t* temp1 = head1; 
    struct node_t* temp2 = head2; 
  
    while (temp1 && temp2) { 
        if (temp1->data == temp2->data) { 
            temp1 = temp1->next; 
            temp2 = temp2->next; 
        } 
        else
            return 0; 
    } 

    if (temp1 == NULL && temp2 == NULL) 
        return 1; 

    return 0; 
} 

// static void reverse(struct node_t** head_ref) {
//     struct node_t* prev = NULL;
//     struct node_t* current = *head_ref;
//     struct node_t* next = NULL;
//     while (current != NULL) {
//         next = current->next;
//         current->next = prev;
//         prev = current;
//         current = next;
//     }
//     *head_ref = prev;
// }

// ********************** Doubly Linked List **********************

struct node_t *split(struct node_t *head);

struct node_t *merge(struct node_t *first, struct node_t *second) {
    
    if (!first)
        return second;
  
    if (!second)
        return first;

    if (first->data < second->data) {
        first->next = merge(first->next,second);
        first->next->prev = first;
        first->prev = NULL;
        return first;
    } else {
        second->next = merge(first,second->next);
        second->next->prev = second;
        second->prev = NULL;
        return second;
    }
}

struct node_t *mergeSort(struct node_t *head) {
    if (!head || !head->next)
        return head;
    struct node_t *second = split(head);

    head = mergeSort(head);
    second = mergeSort(second);

    return merge(head,second);
}

struct node_t *split(struct node_t *head) {

    struct node_t *fast = head,*slow = head;
    while (fast->next && fast->next->next) {
        fast = fast->next->next;
        slow = slow->next;
    }
    struct node_t *temp = slow->next;
    slow->next = NULL;
    return temp;
}

// ********************** **********************

void BinaryTree2DoubleLinkedList(struct tree_t *root, struct tree_t **head) {
    if (root == NULL)
        return;

    static struct tree_t* prev = NULL;

    BinaryTree2DoubleLinkedList(root->left, head);

    if (prev == NULL)
        *head = root;
    else {
        root->left = prev;
        prev->right = root;
    }
    prev = root;

    BinaryTree2DoubleLinkedList(root->right, head);
}

// ********************** ********************** 

int findSize(struct node_t* node) {
    int res = 0;
    while (node != NULL) {
        res++;
        node = node->next;
    }
    return res; 
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

    // printf("Done!\n");

    // char *arr = "This should be typewritten!"; 

    // int len = strlen(arr); 
 
    // for(int i = 0; i < len; i++) {
    //     printf("%c", arr[i]); 
    //     usleep(100000); 
    // }
    // printf("\n"); 

    // sleep(2); 

    // fprintf(stdout, "Hello from fprintf!\n"); 

    return 0; 
}