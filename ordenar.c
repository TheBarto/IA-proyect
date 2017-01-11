/**
 *
 * Descripcion: Implementacion de funciones de ordenacion 
 *
 * Fichero: ordenar.c
 * Autor: Angel Fuente, Rodrigo Amaducci
 * Version: 1.0
 * Fecha: 22-09-2011
 *
 */


#include "ordenar.h"

/***************************************************/
/* Funcion: aleat_num Fecha: 7/10/2013             */
/* Autores: Angel Fuente, Rodrigo Amaducci         */
/*                                                 */
/* Rutina que genera un numero aleatorio           */
/* entre dos numeros dados                         */
/*                                                 */
/* Entrada:                                        */
/* int inf: limite inferior                        */
/* int sup: limite superior                        */
/* Salida:                                         */
/* int: numero aleatorio                           */

/***************************************************/
int aleat_num(int inf, int sup) {
    int random;

    random = rand() % (sup - inf + 1) + inf;
    return random;
}

/***************************************************/
/* Funcion: genera_perm Fecha: 7/10/2013           */
/* Autores: Angel Fuente, Rodrigo Amaducci         */
/*                                                 */
/* Rutina que genera una permutacion               */
/* aleatoria                                       */
/*                                                 */
/* Entrada:                                        */
/* int n: Numero de elementos de la                */
/* permutacion                                     */
/* Salida:                                         */
/* int *: puntero a un array de enteros            */
/* que contiene a la permutacion                   */
/* o NULL en caso de error                         */

/***************************************************/
int* genera_perm(int n) {
    int i;
    int * perm = malloc(n * sizeof (perm[0]));

    if (perm == NULL) return NULL;

    for (i = 1; i <= n; i++) {
        perm[i - 1] = i;
    }

    for (i = 0; i < n; i++) {
        swap(&perm[i], &perm[aleat_num(i, n - 1)]);
    }

    return perm;
}

void swap(int * a, int * b) {
    int buffer = *a;
    *a = *b;
    *b = buffer;
    return;
}

/***************************************************/
/* Funcion: genera_permutaciones Fecha: 7/10/2013  */
/* Autores: Angel Fuente, Rodrigo Amaducci         */
/*                                                 */
/* Funcion que genera n_perms permutaciones        */
/* aleatorias de tamanio elementos                 */
/*                                                 */
/* Entrada:                                        */
/* int n_perms: Numero de permutaciones            */
/* int tamanio: Numero de elementos de cada        */
/* permutacion                                     */
/* Salida:                                         */
/* int**: Array de punteros a enteros              */
/* que apuntan a cada una de las                   */
/* permutaciones                                   */
/* NULL en caso de error                           */

/***************************************************/
int** genera_permutaciones(int n_perms, int tamanio) {
    int i = 0;
    int **perms = (int **) malloc(n_perms * sizeof (perms[0]));
    if (perms == NULL) return NULL;
    for (i = 0; i < n_perms; i++) {
        perms[i] = genera_perm(tamanio);
        if (perms[i] == NULL) {
            int j = 0;
            for (j = 0; j < i; j++) {
                free(perms[j]);
            }
            free(perms);
            return NULL;
        }
    }

    return perms;
}

/***************************************************/
/* Funcion: BubbleSort    Fecha: 7/10/2013         */
/* Autores: Angel Fuente, Rodrigo Amaducci         */
/*                                                 */
/* Función que ordena según el algoritmo           */
/* BubbleSort, con una bandera que indica cuando   */
/* está la tabla ordenada.                         */
/*                                                 */
/* Entrada:                                        */
/* int * tabla: tabla a ordenar.                   */
/* int ip: posición del primer elemento de la tabla*/
/* int iu: posición del último elemento de la tabla*/
/*                                                 */
/* Salida:                                         */
/* int: veces ejecutada la OB.                     */
/* ERR: en caso de error.                          */    
                                               
/***************************************************/
int BubbleSort(int *tabla, int ip, int iu) {
    int flag = 1;
    int i, j;
    int counter = 0;

    if (tabla == NULL) return ERR;

    for (i = iu; flag == 1 && i >= ip + 1; i--) {
        flag = 0;
        for (j = ip; j <= i - 1; j++) {
            if (tabla[j] > tabla[j + 1]) {
                swap(&tabla[j], &tabla[j + 1]);
                flag = 1;
            }
            counter++;
        }
    }
    return counter;
}

/***************************************************/
/* Funcion: tiempo_medio_ordenacion                */
/* Fecha: 7/10/2013                                */
/* Autores: Angel Fuente, Rodrigo Amaducci         */
/*                                                 */
/* Calcula los tiempos de ordenacion de una tabla  */
/* segun un determinado metodo y los guarda en     */
/* la estructura ptiempo.                          */
/*                                                 */
/* Entrada:                                        */
/* pfunc_ordena: metodo de ordenacion              */
/* int n_perms: numero de permutaciones            */
/* int tamanio: tamaño del array                   */
/* PTIEMPO ptiempo: estructura de almacenamiento   */
/*                                                 */
/* Salida:                                         */
/* OK si va todo bien, ERR en caso de error        */

/***************************************************/
short tiempo_medio_ordenacion(pfunc_ordena metodo, int n_perms, int tamanio, PTIEMPO ptiempo) {
    int i = 0;
    int ob = 0, min_ob = INT_MAX, max_ob = 0;
    int acc = 0;
    int **tabla = genera_permutaciones(n_perms, tamanio);
    clock_t ini = clock();

    if (tabla == NULL) return ERR;

    for (i = 0; i < n_perms; i++) {
        ob = metodo(tabla[i], 0, tamanio - 1);
        acc += ob;
        if (ob < min_ob)
            min_ob = ob;
        else if (ob > max_ob)
            max_ob = ob;
    }

    ptiempo->n_perms = n_perms;
    ptiempo->tamanio = tamanio;
    ptiempo->min_ob = min_ob;
    ptiempo->max_ob = max_ob;
    ptiempo->medio_ob = (double) (acc / n_perms);
    ptiempo->tiempo = (clock() - ini) / (double) CLOCKS_PER_SEC / n_perms;

    for (i = 0; i < n_perms; i++) {
        free(tabla[i]);
    }
    free(tabla);

    return OK;
}

/***************************************************/
/* Funcion: genera_tiempos_ordenacion              */
/* Fecha: 7/10/2013                                */
/* Autores: Angel Fuente, Rodrigo Amaducci         */
/*                                                 */
/* Calcula los tiempos de ordenación de un         */
/* algoritmo y los guarda en fichero.              */
/*                                                 */
/* Entrada:                                        */
/* pfunc_ordena metodo: metodo de ordenación       */
/* char * fichero: nombre del fichero de salida    */
/* int num_min: tamaño minimo                      */
/* int num_max: tamaño maximo                      */
/* int incr: incremento de tamaño                  */
/* int n_perms: numero de permutaciones            */
/*                                                 */
/* Salida:                                         */
/* OK si todo va bien, ERR en caso de error.       */
/*                                                 */
/***************************************************/
short genera_tiempos_ordenacion(pfunc_ordena metodo, char* fichero, int num_min, int num_max, int incr, int n_perms) {


    short status = ERR;
    int i, j;
    PTIEMPO ptiempo = (PTIEMPO) malloc((((num_max - num_min) / incr) + 1) * sizeof (ptiempo[0]));

    if (fichero == NULL) return ERR;

    for (i = num_min, j = 0; i <= num_max; i += incr, j++) {
        status = tiempo_medio_ordenacion(metodo, n_perms, i, &ptiempo[j]);
    }
    if (status != OK) {
        free(ptiempo);
        return ERR;
    }

    status = guarda_tabla_tiempos(fichero, ptiempo, j);
    if (status != OK) {
        free(ptiempo);
        return ERR;
    }

    free(ptiempo);
    return OK;
}

/***************************************************/
/* Funcion: guarda_tabla_tiempos Fecha: 7/10/2013  */
/* Autores: Angel Fuente, Rodrigo Amaducci         */
/* Calcula los tiempos de ordenación de un         */
/* algoritmo y los guarda en fichero.              */
/*                                                 */
/* Entrada:                                        */
/* char * fichero: nombre del fichero de salida    */
/* PTIEMPO ptiempo: estructura de almacenamiento   */
/* int N: numero de permutaciones                  */
/*                                                 */
/* Salida:                                         */
/* OK si todo va bien, ERR en caso de error.       */
/*                                                 */
/***************************************************/
short guarda_tabla_tiempos(char* fichero, PTIEMPO tiempo, int N) {

    FILE * f = fopen(fichero, "w");
    int i;

    if (fichero == NULL) return ERR;

    for (i = 0; i < N; i++) {
        fprintf(f, "%d\t%d\t%f\t%f\t%d\t%d\n", tiempo[i].n_perms, tiempo[i].tamanio, tiempo[i].tiempo, tiempo[i].medio_ob, tiempo[i].min_ob, tiempo[i].max_ob);
    }

    fclose(f);

    return OK;
}

/*Copiamos en tabla los elementos de t_aux*/
short copiar(int * t_aux, int * tabla, int ip, int iu){
    int i;
    
    if(t_aux==NULL || tabla==NULL || ip>iu) return ERR;
    
    t_aux -= ip;
    
    for(i=ip; i<=iu; i++){
        tabla[i]=t_aux[i];
    }

    t_aux += ip;
    
    return OK;
}

int merge(int* tabla, int ip, int iu, int imedio){
    int * t_aux = (int*) malloc ((iu-ip+1) * sizeof(t_aux[0]));
    int i, j, k;
    
    if(tabla==NULL || t_aux==NULL) return ERR;
    
    for(i=ip, j=imedio+1, k=0; i<=imedio && j<=iu; k++){/*Aqui cogemos la tabla que nos dan, la partimos por la "mitad", y vamos comparando 	elementos uno a uno, hasta tener ordenada toda la tabla. */
        //Lo que se hace en esta parte es ir comparando e ir copiando los "menores" en t_aux
        if(tabla[i]<tabla[j]){
            t_aux[k]=tabla[i];
            i++;
        }
        else{
            t_aux[k]=tabla[j];
            j++;
        }
    }
    
    if(i>imedio){/*Tanto esta parte como la siguiente cogemos las*/
    /*Copiamos el resto de la tabla en t_aux*/
        for(;j<=iu;j++, k++){
            t_aux[k]=tabla[j];
        }
    }
    else if(j>iu){
        for(;i<=imedio; i++, k++){
            t_aux[k]=tabla[i];
        }	

    }
    
    if(copiar(t_aux, tabla, ip, iu)!=0) return ERR;
    
    free(t_aux);
    
    return counter; 
}

int mergesort (int * tabla, int ip, int iu){
    int counter1=0, counter2=0, counter3=0;
    int medio = (ip+iu)/2;
    
    if(tabla==NULL || ip>iu) return ERR;
    
    if(ip==iu){
        return 0;
    }else{/*Partimos la tabla en tablas mas pequenas*/
        counter1=mergesort(tabla, ip, medio);
        counter2=mergesort(tabla, medio+1, iu);
    }
    if(counter1==ERR || counter2==ERR) return ERR;    

    counter3=merge(tabla, ip, iu, medio);/*Aqui vamos ordenando las tablas que partimos antes.*/
    if(counter3==ERR) return ERR;
    
    return counter1+counter2+counter3;   
}

int medio(int *tabla, int ip, int iu){

    return ip;
}

int medio_rand(int *tabla, int ip, int iu){

    return aleat_num(ip,iu);
}

int medio_stat(int *tabla, int ip, int iu){

    int medio = (ip + iu)/2;
    medio = tabla[medio];

    if(tabla[ip] < tabla[medio]){
	if(tabla[medio] < tabla[iu])
		return medio;
	else if(tabla[ip] < tabla[iu])
		return iu;
	else 
		return ip;
    }else if(tabla[ip] > tabla[medio]){
	if(tabla[medio] > tabla[iu])
		return medio;
	else if(tabla[ip] > tabla[iu])
		return iu;
	else 	
		return ip;
    }
}


int partir(int* tabla, int ip, int iu, pfunc_pivote pivote){

     int b = pivote(tabla,ip,iu);
     int a = tabla[b];
     swap(&tabla[ip],&tabla[b]);
     int i=0;
     b=ip;
     for(i=ip+1;i<=iu;i++)
     {
	if(tabla[i]<a)
	{
	   b++;
	   swap(&tabla[i],&tabla[b]);
	}
	
     }
     swap(&tabla[ip],&tabla[b]);
     
return b;
}
int quicksort(int* tabla, int ip, int iu, pfunc_pivote pivote) {
	int contob=0;
   if(tabla==NULL)
	return ERR;

   if(ip > iu)
	return ERR;
   
   else if(ip == iu)
	return OK;

   else
   {
	int a=partir(tabla,ip,iu,pivote);	
	
	if(ip < a-1)
	{
	  contob+=quicksort(tabla,ip,a-1,pivote);
	   
	
	}
	if(a+1 < iu)
	{
	  contob+=quicksort(tabla,a+1,iu,pivote);
	        

	}
   }
 
return contob + iu -ip;}


int quicksort1(int *tabla,int ip,int iu){

	
	
	int a = quicksort(tabla,ip,iu,medio);

return a;
}

int quicksort2(int *tabla,int ip,int iu){

	
	
	int a = quicksort(tabla,ip,iu,medio_rand);

return a;
}

int quicksort3(int *tabla,int ip,int iu){

	
	
	int a = quicksort(tabla,ip,iu,medio_stat);

return a;
}
