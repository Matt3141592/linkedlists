//
//  main.c
//  linked_list.c
//
//  Created by Matthew Lee on 27/08/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node
{
    int x;
    struct node *next;
} node;

void freelist(node *list);
void printlistr(node *list);
void printlist(node *list);
node  *reverse(node *list);
node *append(node *list, int x);
int len(node *list);
int go(node *list, int x);
void insert_end(node *list, int x);
node *delete_start(node *list);

int main(void)
{
    clock_t begin = clock();
    node *numbers = NULL;

    for (int i = 0; i < 1000; i++)
    {
        node *add = malloc(sizeof(node));
        add -> x = i;
        add -> next = numbers;
        numbers = add;
    }
    int n;
    printf("Enter your number to append: ");
    scanf("%i", &n);
    numbers = append(numbers, n);
    numbers = reverse(numbers);
    insert_end(numbers, 69);
    int x = len(numbers);
    //printlistr(numbers);
    //printf("======================\n");
    numbers = delete_start(numbers);
    printlist(numbers);
    printf("Length: %i\n", x);
    printf("%f\n", (double)(clock() - begin) /CLOCKS_PER_SEC);
    printf("%i\n", go(numbers, 1000));
    freelist(numbers);
}

// frees the linked list
void freelist(node *list)
{
    node *prev = list;
    while (list != NULL)
    {
        list = list -> next;
        free(prev);
        prev = list;
    }
}

// prints linked list in reverse order
void printlistr(node *list)
{
    if (list == NULL)
        return;
    printlistr(list -> next);
    printf("%i\n", list -> x);
}

// prints linked list in order
void printlist(node *list)
{
    while (list != NULL)
    {
        printf("%i\n", list -> x);
        list = list -> next;
    }
}

// length of linked list
int len(node *list)
{
    int count = 0;
    while (list != NULL)
    {
        count++;
        list = list -> next;
    }
    return count;
}

// reverse linked list
node *reverse(node *list)
{
    node *prev = NULL;
    node *temp = NULL;
    while (list != NULL)
    {
        temp = list -> next;
        list -> next = prev;
        prev = list;
        list = temp;
    }
    return prev;
}

// add item to a linked list, adds to the start
node *append(node *list, int x)
{
    node *n = malloc(sizeof(node));
    n -> next = list;
    n -> x = x;
    return n;
}

// indexs into a linked list. Returns 1 if there is an error
int go(node *list, int x)
{
    if (x > len(list))
        return 1;
    
    for (int i = 0; i < x; i++)
        list = list -> next;
    return list -> x;
}

// inserts a node at the end of the list
void insert_end(node *list, int x)
{
    node *n = malloc(sizeof(node));
    n -> x = x;
    n -> next = NULL;
    
    while (list -> next != NULL)
        list = list -> next;
    list -> next = n;
}

// deletes the first node
node *delete_start(node *list)
{
    node *temp = NULL;
    if (list != NULL)
        temp = list -> next;
    free(list);
    return temp;
}

/*
 Notes:
 
 - Not good using recursion as it limits the number of items in the list
 - Limit is around 170k.
 - Could improve by passing through the address of the list and updating there instead of returning new pointer
 - insert_end does not work for empty lists. will need to change return type too
 */
