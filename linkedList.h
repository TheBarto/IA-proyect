#ifndef LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

//PUEDE SER NECESARIA UNA REVISION DEL CÓDIGO

#define TRUE 1
#define FALSE 0
 
typedef int (*comparator)(const void *a, const void *b);
 
typedef struct{
    void * data;
    struct Node* next;
}Node;

typedef struct {
    comparator cmp;
    Node * first;
    Node * last;
}LinkedList;


LinkedList* create_list(comparator comparacion);

void *  destroy_node(Node * n);

int delete_elem_list(LinkedList * l, void * elem);

int is_empty_list(LinkedList * l);

void* find(void *clave, LinkedList *l);

int insert_list(LinkedList * l, void * elem);

int destroy_all_nodes (Node * first);

int destroy_list (LinkedList * lista);
 
void* return_element_by_pos(int pos, LinkedList *l);

void delete_elem_by_pos(int pos, LinkedList *l);

void add_datos_lista(LinkedList * l, double** datos, int n_datos);
 
#endif 

