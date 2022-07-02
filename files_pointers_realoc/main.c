#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct info
{
    short med_num;
    float temperatura;
    char nom_maquina[10];
};
void leerArchivo(FILE *); // lee el archivo binario directamente
void guardarVector(struct info **, int *, FILE *); // lee y guarda los datos del archivo binario en un vector dinamico (usa realloc)
void guardarTexto(struct info *, int, FILE *); // guarda los datos del vector en un archivo de texto en formato de columnas
int main(void)
{
    FILE *archivo1, *archivo2;

    struct info *datos;
    int cantidad = 0, op;
    do
    {

        printf("\nElija una opcion:\n\n");
        printf("1: Leer todos los datos\n");
        printf("2: Guardar datos de todas las maquinas en vector\n");
        printf("3: Guardar datos de maquina en archivo de texto\n");
        printf("4: Salir\n");

        scanf("%d",&op);

        switch(op)
        {
        case 1:
        {
            system("cls");
            leerArchivo(archivo1);
            break;
        }
        case 2:
        {
            system("cls");
            guardarVector(&datos, &cantidad, archivo1);
            break;
        }
        case 3:
        {
            system("cls");
            if(datos == NULL)
            {
                printf("\r\r(Vector vacio, use opcion 2 para llenarlo) ");
                fflush(stdin);
                system("PAUSE");
            }
            else
            {
                guardarTexto(datos, cantidad, archivo2);
            }
            break;
        }
        case 4:
        {
            break;
        }
        default:
        {
            system("cls");
            printf("\r\r(Opcion incorrecta) ");
            fflush(stdin);
            system("PAUSE");
            break;
        }

        }
    }
    while(op!=4);
    return 0;

}
void leerArchivo(FILE *archivo1)
{
    archivo1 = fopen("temperaturas.bin", "rb");
    struct info datos;
    if(archivo1 != NULL)
    {
        fread(&datos, sizeof(struct info),1,archivo1); // lee la primera estructura del archivo binario y la guarda en el buffer osea la estructura "datos" que iniciamos
        while(!feof(archivo1))
        {

            printf("numero: %hd\n",datos.med_num);
            printf("temperatura: %.2f\n",datos.temperatura);
            printf("nombre maquina: %s\n",datos.nom_maquina);

            fread(&datos, sizeof(struct info),1,archivo1); // iteramos el resto del archivo haciendo lo mismo que antes con cada estructura (el buffer se sobreeescribe)
        }
    }
    fclose(archivo1);
}
void guardarVector(struct info** datos, int* cantidad, FILE *archivo1)
{
    *cantidad = 0;
    archivo1 = fopen("temperaturas.bin", "rb");
    if(archivo1 != NULL)
    {
        *datos = (struct info *)realloc(*datos,sizeof (struct info)*((*cantidad)+1)); // en esta funcion agrandamos cada vez mas segun la cantidad de estructuras que vaya encontrando y la guardamos en el vector
        fread(&(*datos)[*cantidad], sizeof(struct info),1,archivo1);
        while(!feof(archivo1))
        {
            (*cantidad)++;

            *datos = (struct info *)realloc(*datos,sizeof(struct info)*((*cantidad)+1)); // cada vez que pasa por una estructura antes de guardarla en el vector, agranda el espacio para poder soportarla
            fread(&(*datos)[*cantidad], sizeof(struct info),1,archivo1);
        }
        for(int i = 0; i < *cantidad; i++)
            printf("dato %hd guardado\n",(*datos+i)->med_num);
        printf("\nCantidad de datos almacenados: %d\n",(*cantidad));
    }
    fclose(archivo1);
}
void guardarTexto(struct info* datos, int cantidad, FILE *archivo2)
{
    archivo2 = fopen("mensaje.txt","w+");
    char nombre[10];
    int cont = 0;
    double promedio = 0, suma = 0;

    if(archivo2 == NULL)
    {
        printf("ERROR de creacion");
        exit(0);
    }
    printf("A continuacion ingrese la maquina que desea guardar en su archivo de texto\n");

    scanf("%s",nombre);
    for(int i = 0; i < cantidad; i++)
    {
        int result = strcmp(nombre, datos[i].nom_maquina);
        if(result == 0)
        {
            fprintf(archivo2,"%hd   %s   %.2f\n",datos[i].med_num, datos[i].nom_maquina, datos[i].temperatura);
            cont++;
        }
    }

    for(int i = 0; i <= cont; i++)
        suma = suma + datos[i].temperatura;

    promedio = suma / cont;
    fprintf(archivo2,"\nPROMEDIO: %.2f\nCANTIDAD: %d", promedio, cont);
    fclose(archivo2);
    printf("\nDatos de %s guardados\n", nombre);

}
