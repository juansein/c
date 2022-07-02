#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct registro
{
    int indice;
    int vector[4000];
};
// Funcion para crear vector de estructuras dinamico (recibe como parametro el largo del mismo)
void crear_vector(int );
// Funcion para incializar los valores de los indices del vector creado (recibe como parametro un puntero al vector y el tama�o del mismo)
void iniciar_vector(struct registro *, int);
// Funcion recursiva para el ordenamiento del vector (recibe como parametro un puntero al vector, la primera y ultima posicion del mismo)
void quickSort(struct registro *, int, int);
// Funcion de ordenamiento del vector con metodo burbuja (recibe como parametro un puntero al vector y el tama�o del mismo)
void ord_burbujeo(struct registro *, int);
// Funcion para imprimir en pantalla los elementos indice del vector (recibe como parametro un puntero al vector y el tama�o del mismo)
void mostrar_vector(struct registro *, int);


int main()
{

    printf("\n\tPrograma vectores\n\n");
    int largo=500;
    crear_vector(largo);
    largo=1000;
    crear_vector(largo);
    largo=2000;
    crear_vector(largo);
    largo=4000;
    crear_vector(largo);

    return 0;

}

void crear_vector(int largo)
{
    double segundos;
    struct registro * soporte;
    soporte = (struct registro*)malloc(largo*sizeof(struct registro));
    if (soporte==NULL)
    {
        printf("\tproblema con memoria dinamica\n");
        exit(1);
    }
    iniciar_vector(soporte, largo);

    clock_t tiempo_inicio, tiempo_final;
    tiempo_inicio = clock();

    quickSort(soporte, 0, largo);
    //ord_burbujeo(soporte, largo);
    mostrar_vector(soporte, largo);

    tiempo_final = clock();
    segundos = (double)(tiempo_final - tiempo_inicio) / CLOCKS_PER_SEC;
    printf("\n\n\nTiempo de ejecucion de metodo Quick Sort: %f\n\n\n",segundos);
    //printf("\n\n\n\t Tiempo de ejecucion de metodo Burbujeo: %f\n\n\n",segundos);
    free (soporte);

}

void iniciar_vector(struct registro * v,int tam)
{
    for(int x=0; x<tam; x++)
    {
        (v+x)->indice=(rand()%(tam+1));
    }
}

void mostrar_vector(struct registro* v, int tam)
{
    for(int x=0; x<tam; x++)
    {
        printf("%d -",(v+x)->indice);
    }
}

void quickSort(struct registro* v, int primero, int ultimo)
{

    int i, j, central;
    int pivote, temp;

    central = (primero + ultimo) / 2;
    pivote = (v+central)->indice;
    i = primero;
    j = ultimo;
    do
    {
        while ((v+i)->indice < pivote) i++;
        while ((v+j)->indice > pivote) j--;
        if (i <= j)
        {
            temp = (v+i)->indice;
            (v+i)->indice = (v+j)->indice;
            (v+j)->indice = temp;
            i++;
            j--;
        }

    }
    while (i <= j);

    if (primero < j)
        quickSort(v, primero, j);
    if(i < ultimo)
    {
        quickSort(v, i, ultimo);
    }
}
void ord_burbujeo(struct registro * v, int tam)
{
    int aux;

    for (int i=0; i < tam-1; i++)
    {
        for (int j=0; j < tam-i-1; j++)
        {
            if ((v+j)->indice > (v+j+1)->indice)
            {

                aux = (v+j)->indice;
                (v+j)->indice = (v+j+1)->indice;
                (v+j+1)->indice = aux;
            }
        }
    }

}
