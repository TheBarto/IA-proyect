#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "particion.h"
#include "linkedList.h"
#include <math.h>

#define TAM_LINEA 100000

typedef enum {Continuo = 1, Nominal} Tipos;

typedef int (*comparator) (const void *a, const void *b);

typedef struct{
	int n_clases;
	int n_atributos;
	int n_datos;
	//int total_clases;
	//Particion* datos;
	double** datos;
	double max_value;
	double min_value;
	Tipos* tipos_cabecera;
	LinkedList* cambio_nominal_continuo;
}Datos;

int rline(int* fd, char* buffer,int* size);
Datos* inicializar_datos(char* fichero,double porcentaje_train,double porcentaje_test);
Datos* inicializar_estructura(int n_tipos);
void swapear_datos(double** datos,int* n_datos,int n_columnas);
void parsear_valor_tipos(char* linea,Tipos* tipos_cabecera);
void parsear_valor(char* linea, double* entrada);
double** get_datos_train(Datos* d, int* num_datos);
double** get_datos_test(Datos* d, int* num_datos);
void normalizar_datos(double** datos, int* n_atributos, int* n_datos);
/*NominalContinuo* get_nominalcontinuo(Datos* d, int* clase);

typedef struct{
	char valor_nominal[TAM_CLASE];
	int valor_asociado;
}NominalContinuo;

NominalContinuo* crear_Nominal_Continuo(char* clave, int *valor);
void liberar_Nominal_Continuo(NominalContinuo* nc);
int get_valor_continuo(NominalContinuo *nc);
char* get_valor_nominal(NominalContinuo *nc);
int compararClave(NominalContinuo *nc, char *clave);*/