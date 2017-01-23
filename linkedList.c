#include "linkedList.h"

/**
 * @page create_list \b create_list
 *
 * @brief Creates a new list.
 * 
 * @param comparacion Pointer to function that campares the key of the data.
 * @return The new list if all was OK, NULL otherwise.
 * @section SYNOPSIS
 *  \b #include \b "/includes/lista.h"
 *  \b lib/libLista.a 
 *
 * \b LinkedList* \b create_list(\b comparator comparacion \b)
 *
 * @section descripcion DESCRIPCIÓN
 *
 * This funcition creates a linked list and returns it. 
 *
 * recives:
 * 	-A pointer type function that compares two argumets.
 * 	the ponter type funcition must be as this:
 * 	int compare(const void *a, const void *b);
 *
 * @section return RETORNO
 *
 * Retrurn an empty linked list.
 *
 * @section seealso VER TAMBIÉN
 * \b destroy_node(3), \b destroy_list(3), \b delete_elem_list(3),\b is_empty_list(3), \b find(3), \b insert_list(3), \b destroy_all_nodes(3)
*/
 
LinkedList* create_list(comparator comparacion) {
    //if(comparacion == NULL) return NULL;
    
    LinkedList * lista = (LinkedList *) malloc(sizeof(LinkedList));
    if(lista == NULL) return NULL;
 
 	CMP(lista) = comparacion;
    //lista->cmp = comparacion;
    FIRST(lista) = NULL;
    //lista->first = NULL;
    LAST(lista) = NULL;
    //lista->last = NULL;
    ELEMS(lista) = 0;
    //lista->n_elems = 0;
 
    return lista;
}

/**
 * @page destroy_node \b destroy_node
 *
 * @brief Destroys a node.
 *
 * @param n Node to be destroyed.
 * @return The destroyed node.
 * @section SYNOPSIS
 *  \b #include \b "/includes/lista.h"
 *  \b lib/libLista.a 
 *
 * \b void* \b destroy_node(\b Node * n \b)
 *
 * @section descripcion DESCRIPCIÓN
 *
 * This funcition destroys a node.
 *
 * recives:
 * 	-A node.
 *
 * @section return RETORNO
 *
 * A destroyed node.
 *
 *
 * @section seealso VER TAMBIÉN
 * \b create_list(3), \b destroy_list(3), \b delete_elem_list(3),\b is_empty_list(3), \b find(3), \b insert_list(3), \b destroy_all_nodes(3)
*/
void *  destroy_node(Node * n) {
    DATA(n) = NULL;
    //n->data = NULL;
    NEXT(n) = NULL;
    //n->next = NULL;
    PREVIOUS(n) = NULL;
    //n->previous = NULL;
    free(n);
    n = NULL;
    
    return (void*) n;
}


/**
 * @page delete_elem_list \b delete_elem_list
 *
 * @brief Deletes a element of a list
 * @param l A list.
 * @param elem The element to be deleted.
 * @return int.
 *
 * @section SYNOPSIS
 *  \b #include \b "/includes/lista.h"
 *  \b lib/libLista.a 
 *
 *  \b int \b delete_elem_list (\b Lista * l \b , \b void * elem \b )
 * 
 * @section descripcion DESCRIPCIÓN
 *
 * This function deletes an element elem of the lis l if this element is in the list.
 * 
 * Recives:
 *    - l The list.
 *    - elem The element to be deleted.
 *
 * @section retorno RETORNO
 * 
 * 1 On succes, 0 on faliure.
 *
 * @section seealso VER TAMBIÉN
 * \b create_list(3), \b destroy_node(3), \b destroy_list(3), \b is_empty_list(3), \b find(3), \b insert_list(3), \b destroy_all_nodes(3)
 *
 * @section authors AUTOR
 * Manuel Reyes (manuel.reyes@estudiante.uam.es)
 * Jorge Guillen (jorge.guillen@estudiante.uam.es)
*/
int delete_elem_list(LinkedList * l, void * elem){
    Node * node;
    Node * node_anterior;

    /*Error en el paso de argumentos*/
    if (l == NULL || elem == NULL){
        return ERR;
    }

    /*La lista esta vacia*/
    if (is_empty_list(l)==TRUE){
        return ERR;
    }
 
    /*Si el elemento fuera el primero de todos*/
    //node = l->first;
    node = FIRST(l);
    if(CMP(l)(elem, node->data)==TRUE){
    	FIRST(l) = (Node *)NEXT(node);
        //l->first = (Node *)node->next;
        PREVIOUS(FIRST(l)) = NULL;
        //l->first->previous = NULL;
        node = destroy_node(node);
        return TRUE;
    }

    /*Busqueda del elemento*/
    node_anterior = FIRST(l);
    //node_anterior = l->first;
    node = (Node *)NEXT(FIRST(l));
    //node = (Node *)l->first->next;
    Node *e = NULL;
    ELEMS(l)--;
    //l->n_elems--;
    while(node!=NULL){
        if(CMP(l)(elem, node->data)==TRUE){ 
            /*Hemos encontrado el elemento*/
            if(node->next==NULL){
                /*El elemento es el ultimo, redefinimos last*/
                LAST(l) = node_anterior;
                //l->last = node_anterior;
            }
            NEXT(node_anterior) = NEXT(node);
            //node_anterior->next = node->next;
            e = (Node *)NEXT(node);
            //e = (Node *)node->next;
            PREVIOUS(e) = (struct Node *)node_anterior;
            //e->previous = (struct Node *)node_anterior;
            node = destroy_node(node);
            return TRUE;
        }
        /*No era el objetivo, continuamos buscando*/
        node_anterior = node;
        node =(Node *) NEXT(node);
        //node =(Node *) node->next;
    }
    /*El elemento no ha sido encontrado*/
    return FALSE;
}

/**
 * @page delete_elem_list \b delete_elem_list
 *
 * @brief Tells if the list is empty or not.
 * @param l List to check
 * @return -1 if an error happened, TRUE if empty or FALSE if not empty.
 *
 * @section SYNOPSIS
 *  \b #include \b "/includes/lista.h"
 *  \b lib/libLista.a 
 *
 *  \b int \b is_empty_list(\b LinkedList * l \b)
 * 
 * @section descripcion DESCRIPCIÓN
 * This function tells if the list is empty.
 *
 * recives:
 * 	- l A list
 * @section retorno RETORNO
 * 
 * 1 When TRUE, 0 When FALSE, -1 On ERROR.
 *
 * @section seealso VER TAMBIÉN
 * \b create_list(3), \b destroy_node(3), \b destroy_list(3), \b delete_elem_list(3), \b find(3), \b insert_list(3), \b destroy_all_nodes(3)
 */
int is_empty_list(LinkedList * l) {
    if(l == NULL){
        return ERR;
    }
    if(FIRST(l) == NULL){
        return TRUE;
    }
    return FALSE;
}

/**
 * @page find \b find
 *
 * @brief This function is used when you want to find something in the list
 * @param clave Key to be find
 * @param l List to check
 * @return NULL if an error happened, the element of the list.
 *
 * @section SYNOPSIS
 *  \b #include \b ""
 *
 *  \b void \b find \b (\b void *\b )
 * 
 * @section descripcion DESCRIPCIÓN
 *
 * When you want to find some element than you introduced in the list
 * 
 * 
 * You have to pass the key of the element that you want to find, and the list where the element is.
 *
 * @section retorno RETORNO
 * Returns the element
 *
 * @section seealso VER TAMBIÉN
 * \b create_list(3), \b destroy_node(3), \b destroy_list(3), \b delete_elem_list(3),\b is_empty_list(3), \b insert_list(3), \b destroy_all_nodes(3)
 * @section authors AUTOR
 * Silvia Anguita (silvia.anguita@estudiante.uam.es)
 * Ángel Fuente (angel.fuente@estudiante.uam.es)
*/
void* find(void *clave, LinkedList *l) {
    Node *nodoaux = NULL;

    if (!clave || !l) {
        syslog(LOG_ERR, "Error al buscar un elemento en la lista, debido a un puntero nulo");
        exit(EXIT_FAILURE);
    }


    for (nodoaux = FIRST(l); nodoaux != NULL; nodoaux = (Node *)NEXT(nodoaux)) {
        if (CMP(l)(DATA(nodoaux),clave) == TRUE) {
            return DATA(nodoaux);
        }
    }
    return NULL;
}


/**
 * @page insert_list \b insert_list
 *
 * @brief Insert an element on a list.
 * @param elem Element to be inserted.
 * @param l List to check.
 * @return -1 if an error ocurred, 1 on succes.
 *
 * @section SYNOPSIS
 *  \b #include \b ""
 *
 *  \b int \b insert_list( \b LinkedList * l \b, \b void * elem \b){
 * 
 * @section descripcion DESCRIPCIÓN
 *
 * Inserts an elemet at the end of a linked list.
 * 
 * recives:
 * 	- l a linked list.
 *	- elem the element to be inserted.
 *
 * @section retorno RETORNO
 * -1 if an error ocurred, 1 on succes.
 *
 * @section seealso VER TAMBIÉN
 * \b create_list(3), \b destroy_node(3), \b destroy_list(3), \b delete_elem_list(3),\b is_empty_list(3), \b find(3), \b destroy_all_nodes(3)
 */
int insert_list(LinkedList * l, void * elem){
    Node * node;
    if (l == NULL || elem == NULL){
        return ERR;
    }
    node = (Node *) malloc(sizeof (Node));
    if (node == NULL){
        return ERR;
    }
    DATA(node) = elem;
    //node->data = elem;
    NEXT(node) = NULL;
    //node->next = NULL;
    ELEMS(l)++;
    //l->n_elems++;
    if (is_empty_list(l)==TRUE){
        FIRST(l) = node;
        //l->first = node;
        LAST(l) = node;
        //l->last = node;
        PREVIOUS(node) = NULL;
        //node->previous = NULL;
        return TRUE;
    }
    PREVIOUS(node) = (struct Node *) LAST(l);
    //node->previous = (struct Node *) l->last;
    NEXT(LAST(l)) = (struct Node *) node;
    //l->last->next = (struct Node *) node;
    LAST(l) = node;
    //l->last = node;
    return TRUE;
}

/**
 * @page destroy_all_nodes \b destroy_all_nodes
 *
 * @brief Destroy all nodes of a list.
 *
 * @param first Node to be destroyed.
 * @return 0 always.
 *
 * @section SYNOPSIS
 *  \b #include \b "/includes/lista.h"
 *  \b lib/libLista.a 
 *
 *  \b int \b destroy_all_nodes (\b Nodo * first \b)
 * 
 * @section descripcion DESCRIPCIÓN
 *
 * Deletes the "first" node of a list an al the "next" nodes of that node.
 * This function shuld be called from destroy_list(3)
 * 
 * recives:
 *    - first The first node of the list
 *
 * @section return RETORNO
 * 0 always.
 *
 * @section seealso VER TAMBIÉN
 * \b create_list(3), \b destroy_node(3), \b destroy_list(3), \b delete_elem_list(3),\b is_empty_list(3), \b find(3), \b insert_list(3)
 *
 * @section authors AUTOR
 * Nestor Campillo (nestor.campillo@estudiante.uam.es)
 * Adrian Bueno (adrian.buenoj@estudiante.uam.es)
*/
int destroy_all_nodes (Node * first){

    if (first != NULL){ 
        destroy_all_nodes((Node *)NEXT(first));
        
        first = destroy_node(first);
    }
    return FALSE;
}

/**
 * @page destroy_list \b destroy_list
 *
 * @brief Destroya a linked list.
 *
 * @param lista List to be destroyed.
 * @return 0 On succes, -1 if an error ocurred..
 *
 * @section SYNOPSIS
 *  \b #include \b "/includes/lista.h"
 *  \b lib/libLista.a 
 *
 *  \b int \b destroy_list (\b Lista * lista \b)
 * 
 * @section descripcion DESCRIPCIÓN
 *
 * Destroys the whole list.
 * 
 * recives:
 *    - lista List to be destroyed
 *
 * @section return RETORNO
 * 0 On succes, -1 if an error ocurred.
 *
 * @section seealso VER TAMBIÉN
 * \b create_list(3), \b destroy_node(3), \b delete_elem_list(3),\b is_empty_list(3), \b find(3), \b insert_list(3), \b destroy_all_nodes(3)
 *
 * @section authors AUTOR
 * Nestor Campillo (nestor.campillo@estudiante.uam.es)
 * Adrian Bueno (adrian.buenoj@estudiante.uam.es)
*/
int destroy_list (LinkedList * lista){
 
    if (lista == NULL)
        return ERR;
 
    if (is_empty_list(lista) == FALSE){
        destroy_all_nodes(FIRST(lista));
    }
 
    FIRST(lista) = NULL;
    //lista->first = NULL;
    LAST(lista) = NULL;
    //lista->last = NULL;
    CMP(lista) = NULL;
    //lista->cmp = NULL;
    ELEMS(lista) = 0;
    //lista->n_elems = 0;
    free(lista);
 
    return TRUE;
}

void* return_element_by_pos(int* pos, LinkedList *l) {
    Node *nodoaux = NULL;

    if (!l) {
        //syslog(LOG_ERR, "Error al buscar un elemento en la lista, debido a un puntero nulo");
        return NULL;
    }
    int i = 0;

    for (nodoaux = FIRST(l); nodoaux != NULL; nodoaux = (Node *)NEXT(nodoaux),i++) {
        if (i == *pos) {
            return DATA(nodoaux);
        }
    }
    return NULL;
}

Node* return_node_by_pos(int* pos, LinkedList *l) {
    Node *nodoaux = NULL;

    if (!l) {
        //syslog(LOG_ERR, "Error al buscar un elemento en la lista, debido a un puntero nulo");
        return NULL;
    }
    int i = 0;
    for (nodoaux = FIRST(l); nodoaux != NULL; nodoaux = (Node *)NEXT(nodoaux),i++) {
        if (i == *pos) {
            return nodoaux;
        }
    }
    return NULL;
}

int delete_elem_by_pos(int pos, LinkedList *l){
    Node * node;
    Node * node_anterior;
    /*Error en el paso de argumentos*/
    if (l == NULL){
        return ERR;
    }

    /*La lista esta vacia*/
    if (is_empty_list(l)==TRUE){
        return ERR;
    }
 
    /*Si el elemento fuera el primero de todos*/
    //node = l->first;
    node = FIRST(l);
    if(pos == 0){
        PREVIOUS(FIRST(l)) = NULL;
        //l->first->previous = NULL;
        FIRST(l) = (Node *)NEXT(node);
        //l->first = (Node *)node->next;
        node = destroy_node(node);
        return TRUE;
    }

    /*Busqueda del elemento*/
    //node_anterior = l->first;
    node_anterior = FIRST(l);
    //node = (Node *)l->first->next;
    node = (Node *) NEXT(FIRST(l));
    int i = 1;
    Node* e = NULL;
    ELEMS(l)--;
    //l->n_elems--;
    while(node!=NULL){
        if(i == pos){ 
            /*Hemos encontrado el elemento*/
            if(NEXT(node)==NULL){
                /*El elemento es el ultimo, redefinimos last*/
                LAST(l) = node_anterior;
                //l->last = node_anterior;
            }
            NEXT(node_anterior) = NEXT(node);
            //node_anterior->next = node->next;
            e = (Node *)NEXT(node);
            //e = (Node *)node->next;
       		PREVIOUS(e) = (struct Node *)node_anterior;
            //e->previous = (struct Node *)node_anterior;
            node = destroy_node(node);
            return TRUE;
        }
        /*No era el objetivo, continuamos buscando*/
        node_anterior = node;
        node = (Node *) NEXT(node); 
        //node = (Node *) node->next;
        i++;
    }
    /*El elemento no ha sido encontrado*/
    return FALSE;
}

int add_datos_lista(LinkedList * l, double** datos, int n_datos) {

	int i = 0;

    //Insertamos los datos en la lista por filas
	for(i = 0; i < n_datos; i++)
		insert_list(l,(void *)datos[i]);
	
	return TRUE;
}

int int_int_to_int_comparator(LinkedList * l, int* i, int* j) {

    int elem1 = *(int *)return_element_by_pos(i,l);
    int elem2 = *(int *)return_element_by_pos(j,l);

    if (elem1 < elem2)
        return 1;
    else if (elem1 == elem2)
        return 0;
    else
        return -1;
}

int int_int_to_void_comparator(LinkedList * l, int* i, void* elem) {

	int elem1 = *(int *)return_element_by_pos(i,l);
	int elem2 = *(int *)elem;

	if (elem1 < elem2)
        return 1;
    else if (elem1 == elem2)
        return 0;
    else
        return -1;
}

//The element which it must to swap it's the element in pos2
int pseudoswap(LinkedList * l, int* pos1, int* pos2) {

    Node* node1 = NULL;
    Node* node2 = NULL;
    Node* naux = NULL;
    int i = 0;

    if(*pos1 == *pos2)
    	return OK;

    for (naux = FIRST(l); node1 == NULL || node2 == NULL;naux = (Node *)NEXT(naux),i++) {
        if (i == *pos1) 
            node1 = (Node*)naux;
        if (i == *pos2)
            node2 = (Node*)naux;
    }

    if (*pos1 - 1 == *pos2 || *pos1 + 1 == *pos2 || *pos2 - 1 == *pos1 || *pos2 + 1 == *pos1){
        void *aux = DATA(node1);
        DATA(node1) = DATA(node2);
        DATA(node2) = aux;
        //void *aux = node1->data;
        //node1->data = node2->data;
        //node2->data = aux;
    }else {
        Node* node_posj = return_node_by_pos(pos2,l); // swap
        Node* node = (Node *) malloc(sizeof (Node));
        DATA(node) = DATA(node_posj);
        //node->data = node_posj->data;

        //Change the order of the nodes previous and next of the node which we're going to change
        if(NEXT(node_posj) != NULL) {
        	naux = (Node *)NEXT(node_posj);
            //naux = (Node *)node_posj->next;
            PREVIOUS(naux) = PREVIOUS(node_posj);
            //naux->previous = node_posj->previous;
            naux = (Node *)PREVIOUS(node_posj);
            //naux = (Node *)node_posj->previous;
            NEXT(naux) = NEXT(node_posj);
            //naux->next = node_posj->next;
        }else{
        	LAST(l) = (Node*)PREVIOUS(node_posj);
        	//l->last = (Node*)node_posj->previous;
        	naux=(Node*)PREVIOUS(node_posj);
        	//naux=(Node*)node_posj->previous;
        	NEXT(naux) = NULL;
        	//naux->next = NULL;
        }
              	
        destroy_node(node_posj);

        int var_aux = *pos1-1;

        Node* node_posi = NULL;
        if(var_aux < 0) { //En caso de devolver un nodo nulo
        	var_aux = 0;
        	node_posi = return_node_by_pos(&var_aux,l); 
        	NEXT(node) = (struct Node *)node_posi;
        	//node->next = (struct Node *)node_posi;
        	PREVIOUS(node_posi) = (struct Node *)node;
        	//node_posi->previous = (struct Node *)node;
        	FIRST(l) = (Node *)node;
        	//l->first = (Node *)node;
        }else {
        	node_posi = return_node_by_pos(&var_aux,l); // i - 1
        	NEXT(node) = NEXT(node_posi);
        	//node->next = node_posi->next;
        	PREVIOUS(node) = (struct Node *)node_posi;
        	//node->previous = (struct Node *)node_posi;
        	NEXT(node_posi) = (struct Node *)node; 
        	//node_posi->next = (struct Node *)node;
        	naux = (Node *)NEXT(node);
        	//naux = (Node *)node->next;
        	PREVIOUS(naux) = (struct Node *)node;
        	//naux->previous = (struct Node *)node;
        }        
    }
   
   return OK;
}

int merge(LinkedList * l, int* ini, int* fin, int* medio,lcmp cmp) {

    int i = *ini;
    int j = *medio + 1;

    for (;i<=*medio && j <=*fin;i++) {
        if(cmp(l,&i,&j) == -1){
            //El caso de que el valor de i sea mayor o igual a j.
            pseudoswap(l,&i,&j);
            j++; 
        }
    }
    
    return OK;
}

int mergersort(LinkedList * l, int* ini, int* fin,lcmp cmp) {

    int medio = (*ini + *fin)/2;
    int c1 = -1;
    int c2 = -1;

    if (l == NULL || *ini > *fin)
        return ERR;
    else if(*ini == *fin)
        return FALSE;
    else{
        c1 = mergersort(l,ini,&medio,cmp);
        medio++;
        c2 = mergersort(l,&medio,fin,cmp);
        medio--;
    }
    if (c1 == ERR && c2 == ERR)
        return ERR;
    if (merge(l,ini,fin,&medio,cmp) == ERR)
        return ERR;

    return OK;
}

int swap(LinkedList* l,int* pos1,int* pos2) {

	Node* node1 = NULL;
    Node* node2 = NULL;
    Node* naux = NULL;
    int i = 0;

	for (naux = FIRST(l); node1 == NULL || node2 == NULL;naux = (Node *)NEXT(naux),i++) {
        if (i == *pos1) 
            node1 = (Node*)naux;
        if (i == *pos2)
            node2 = (Node*)naux;
    }

    void *aux = DATA(node1);
	DATA(node1) = DATA(node2);
	DATA(node2) = aux;
    //void* void_aux = node1->data;
    //node1->data = node2->data;
    //node2->data = void_aux;

    return OK;
}

//Función de pivote que coge el elemento del medio
int medio(LinkedList * l,int* ini, int* fin){

    return *ini;
}

int partir(LinkedList * l, int* ini, int* fin, pfunc_pivote pivote, lcmp comparator){

    int b = pivote(l,ini,fin);
    void* a = (int *)return_element_by_pos(&b,l);
    swap(l,ini,&b);
    int i=0;
    b=*ini;
    
    for(i=*ini+1;i<=*fin;i++){
        if(comparator(l,&i,a) == 1){
            b++;
            swap(l,&i,&b);
        }
    }
    swap(l,ini,&b);

    return b;
}

int quicksort(LinkedList * l, int* ini, int* fin, pfunc_pivote pivote, lcmp comparator) {

    if(l==NULL)
        return ERR;
    else if(*ini > *fin)
        return ERR;
    else if(*ini == *fin)
        return OK;
    else {
        int a=partir(l,ini,fin,pivote,comparator);   
        if(*ini < a-1){
        	a--;
            quicksort(l,ini,&a,pivote,comparator);
            a++;
        }
        if(a+1 < *fin){
        	a++;
            quicksort(l,&a,fin,pivote,comparator);
            a--;
        }
   }

    return OK;
}

/*  Estas funciones son para comprobar que la lista
    funcione correctamente */
void print_all_elems_ini(LinkedList * l) {

    Node * node = (Node *)l->first;

    while(node!=NULL) {
        printf("%d ",*((int *)node->data));
        node = (Node *)node->next;
    }
    printf("\n");

    return;
}

void print_all_elems_fin(LinkedList * l) {

    Node * node = l->last;

    while(node!=NULL) {
        printf("%d ",*(int *)node->data);
        node = (Node *)node->previous;
    }
    printf("\n");

    return;
}