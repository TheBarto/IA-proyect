#include "Datos.h"

//Añadir opcion de swapear datos
/* Explicacion de la función

Con esta función leemos los datos de un archivo, crea una estructura de tipo datos, particionando los datos y cambiando
los que sean nominales a continuos.

Para ello, el fichero tiene que tener una cabecera específica, con los siguientes datos:
	-	El número de atributos en cada linea(cuantas columnas son atributos, NO LAS CLASES).
	-	El número de clases que hay en cada linea.
	-	El número total de datos que tiene el fichero(las lineas de datos).
	-	El número distinto de clases del fichero.
*/
Datos* inicializar_datos(char* fichero, double porcentaje_train, double porcentaje_test) {

    FILE* f = fopen(fichero, "r");
    if (!f) {
        printf("Error al abrir el fichero, abortando\n");
        return NULL;
    }

    //Reservamos la memoria necesaría para almacenar los datos y leemos la cabecera del fichero
    char *linea = (char *) malloc(TAM_LINEA * sizeof (char));
    double *datos = (double *) malloc(TAM_LINEA * sizeof (double));
    fgets(linea, TAM_LINEA, f);
    parsear_valor(linea, datos);
    Datos* d = inicializar_estructura((int) (datos[0] + datos[1]));

    int i = 0;
    double** total_datos = (double **) malloc(datos[2] * sizeof (double *));
    for (i = 0; i < datos[2]; i++)
        total_datos[i] = (double *) malloc((datos[0] + datos[1]) * sizeof (double));

    //Guardamos los datos en la estructura
    d->n_atributos = datos[0];
    d->n_clases = datos[1];
    d->n_datos = datos[2];
    d->total_clases = datos[3];

    free(datos);

    //Leemos la siguiente linea de la cabecera
    fgets(linea, TAM_LINEA, f);
    parsear_valor_tipos(linea, d->tipos_cabecera);

    int j = 0;
    int n_datos = 0;
    char *ptr = NULL;
    char *aux = NULL;
    i = 0;
    //Vamos leyendo todos los datos
    while (fgets(linea, TAM_LINEA, f)) {
        aux = linea;
        while (ptr = strtok(aux, " |\n|,")) { //Los vamos parseando
            if (d->tipos_cabecera[i] == Continuo) { //En caso de que sea continuo
                total_datos[n_datos][i] = atof(ptr);
            } else { //Si es nominal, creamos un sustituto continuo, y cargamos los datos
                NominalContinuo *nc = (NominalContinuo *) find((void *) ptr, (void *) d->cambio);
                if (nc == NULL) {
                    nc = crear_Nominal_Continuo(ptr, &j);
                    insert_list(d->cambio, (void *) nc);
                    total_datos[n_datos][i] = j;
                    j++;
                } else { 
                    total_datos[n_datos][i] = nc->valor_asociado;
                }
            }
            i++;
            aux = NULL;
        }
        n_datos++;
        i = 0;
    }

    //swapear_datos(total_datos, &n_datos, d->n_atributos + d->n_clases);
    d->datos = crearParticion(total_datos, n_datos, porcentaje_train, porcentaje_test);

    return d;
}
/*
Inicializamos una estructura donde guardar los datos

*/
Datos* inicializar_estructura(int tipos) {

    Datos* d = (Datos *) malloc(sizeof (Datos));
    d->tipos_cabecera = (Tipos *) malloc(tipos * sizeof (Tipos));
    d->cambio = create_list(comparador);
    d->datos = NULL;
    d->max_value = 0;
    d->min_value = 0;
    d->n_atributos = 0;
    d->n_clases = 0;
    d->n_datos = 0;
    d->total_clases = 0;

    return d;
}

void swapear_datos(double** datos, int* n_datos, int n_columnas) {

    double aux = 0;
    int random = 0;
    int i = 0;
    int j = 0;

    for (i = 0; i < *n_datos; i++) {
        random = rand() % n_columnas;
        for (j = 0; j < n_columnas; j++) {
            aux = datos[i][j];
            datos[i][j] = datos[random][j];
            datos[random][j] = aux;
        }
    }

    return;
}

void parsear_valor_tipos(char* linea, Tipos* tipos_cabecera) {
    if (!linea || !tipos_cabecera) return;

    char *ptr = strtok(linea, " |\n,");
    if (strcmp("Continuo", ptr) == 0) {
        tipos_cabecera[0] = Continuo;
    } else
        tipos_cabecera[0] = Nominal;

    int i = 1;
    while ((ptr = strtok(NULL, " |\n,"))) {
        if (strcmp("Continuo", ptr) == 0) {
            tipos_cabecera[i] = Continuo;
        } else
            tipos_cabecera[i] = Nominal;
        i++;
    }

    return;
}

void parsear_valor(char* linea, double* entrada) {
    if (!linea || !entrada) return;

    char *ptr = strtok(linea, " ");
    entrada[0] = atof(ptr);

    int i = 1;
    while ((ptr = strtok(NULL, " |\n"))) {
        entrada[i] = atof(ptr);
        i++;
    }

    return;
}

double** get_datos_train(Datos* d, int* num_datos) {
    return obtenerDatosTrain(d->datos, num_datos);
}

double** get_datos_test(Datos* d, int* num_datos) {
    return obtenerDatosTest(d->datos, num_datos);
}

void normalizar_datos(double** datos, int* n_atributos, int* n_datos){
	
}

NominalContinuo* get_nominalcontinuo(Datos* d, int* clase) {
    return (NominalContinuo *) find((void *) clase,(void *) d->cambio);
}

NominalContinuo* crear_Nominal_Continuo(char* clave, int *valor) {

    NominalContinuo* nc = (NominalContinuo*) malloc(sizeof (NominalContinuo));
    strcpy(nc->valor_nominal, clave);
    nc->valor_asociado = *valor;

    return nc;
}

void liberar_Nominal_Continuo(NominalContinuo* nc) {

    free(nc->valor_nominal);
    strcpy(nc->valor_nominal, "");
    nc->valor_asociado = 0;
    free(nc);
    nc = NULL;
    return;
}

int get_valor_continuo(NominalContinuo *nc) {
    return nc->valor_asociado;
}

char* get_valor_nominal(NominalContinuo *nc) {
    return nc->valor_nominal;
}

int compararClave(NominalContinuo *nc, char *clave) {

    if (strcmp(nc->valor_nominal, clave) == 0) return 1;
    else return 0;
}

int comparador(const void *a, const void *b) {
    NominalContinuo *nc = (NominalContinuo *) a;
    b = (char *) b;

    if (strcmp(nc->valor_nominal, b) == 0) return 1;
    else return 0;
}