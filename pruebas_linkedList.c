#include "linkedList.h"
#include <assert.h>

int main(int argc,char* argv[]) {

	LinkedList* lista = create_list(NULL);
	int e = 77;
	int e1 = 6;
	int e2 = 5;
	int e3 = 3;
	int e4 = 1;
	int e5 = 8;
	int e6 = 7;
	int e7 = 2;
	int e8 = 4;

	assert(lista != NULL);	
	
	assert(is_empty_list(lista) == TRUE);

	
	printf("Hasta aquí bien 1\n");
	assert(insert_list(lista, (void *)&e) == 1);

	//return_element_by_pos(0, lista);
	printf("Hasta aquí bien 2\n");

	int pos=0;
	int elem = *(int *)return_element_by_pos(&pos, lista);
	printf("%d\n",elem);

	assert(elem == 77);

	printf("Hasta aquí bien 3\n");
	assert(delete_elem_by_pos(0, lista) == 1);

	printf("Hasta aquí bien 4\n");
	insert_list(lista, (void *)&e1);
	insert_list(lista, (void *)&e2);
	insert_list(lista, (void *)&e3);
	insert_list(lista, (void *)&e4);
	/*insert_list(lista, (void *)&e5);
	insert_list(lista, (void *)&e6);
	insert_list(lista, (void *)&e7);
	insert_list(lista, (void *)&e8);*/

	printf("Hasta aquí bien 5\n");
	print_all_elems_ini(lista);

	print_all_elems_fin(lista);

	printf("Hasta aquí bien 6\n");
	int ini = 0;
	int fin = 3;
	mergersort(lista,&ini,&fin,int_comparator);

	printf("Hasta aquí bien 7\n");

	print_all_elems_ini(lista);

	destroy_list (lista);
}