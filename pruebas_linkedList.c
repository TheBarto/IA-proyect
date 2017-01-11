#include "linkedList.h"
#include <assert.h>

int main(int argc,char* argv[]) {

	LinkedList* lista = create_list(NULL);

	assert(lista != NULL);

	printf("Hasta aquí bien\n");
	/*assert(is_empty_list(lista) == TRUE);

	assert(insert_list(lista, (void *)77) == 1);

	int elem = *(int *)return_element_by_pos(0, lista);
	assert(elem == 77);

	assert(delete_elem_by_pos(0, lista) == 1);

	insert_list(lista, (void *)4);
	insert_list(lista, (void *)5);
	insert_list(lista, (void *)6);
	insert_list(lista, (void *)7);
	insert_list(lista, (void *)8);

	print_all_elems_ini(lista);

	print_all_elems_fin(lista);*/
}