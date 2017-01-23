#ifndef LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

//Hacer pruebas de funcionamiento

#define TRUE 1
#define OK 1
#define FALSE 0
#define ERR -1

#define FIRST(x) x->first
#define LAST(x) x->last
#define CMP(x) x->cmp
#define ELEMS(x) x->n_elems
#define DATA(x) x->data
#define NEXT(x) x->next
#define PREVIOUS(x) x->previous

typedef int (*comparator)(const void *a, const void *b);

typedef struct{
    void * data;
    struct Node* next;
    struct Node* previous;
}Node;

typedef struct {
    comparator cmp;
    Node * first;
    Node * last;
    int n_elems;
}LinkedList;

typedef int (*lcmp)(LinkedList *l, const int *pos1, const int *pos2);
typedef int (*pfunc_pivote)(LinkedList *, int* , int* );

LinkedList* create_list(comparator comparacion);

void *  destroy_node(Node * n);

int delete_elem_list(LinkedList * l, void * elem);

int is_empty_list(LinkedList * l);

void* find(void *clave, LinkedList *l);

int insert_list(LinkedList * l, void * elem);

int destroy_all_nodes (Node * first);

int destroy_list (LinkedList * lista);
 
void* return_element_by_pos(int* pos, LinkedList *l);

int delete_elem_by_pos(int pos, LinkedList *l);

int add_datos_lista(LinkedList * l, double** datos, int n_datos);

int int_int_to_int_comparator(LinkedList * l, int* i, int* j);

int int_int_to_void_comparator(LinkedList * l, int* i, void* elem);

int medio(LinkedList * l,int* ini, int* fin);

/*  Estas funciones son para comprobar que la lista
    funcione correctamente */

void print_all_elems_ini(LinkedList * l);

void print_all_elems_fin(LinkedList * l);

#endif 

