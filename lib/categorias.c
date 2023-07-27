#include "categorias.h"
#include "Login.h"
void cargarCategorias(){

    stCategorias categorias;
    FILE * archivo = fopen("categorias.bin","ab");
    if(archivo!=NULL)
    {

        //DEJE EN UN CICLO POR SI ACASO CAMBIAMOS LA DIMENSION PERO PARA MI ES UNA SOLA
        printf("\nIngrese categoria: ");
        fflush(stdin);
        scanf("%s", categorias.categorias);
        categorias.idCategorias = totalCategorias("categorias.bin");
        fwrite(&categorias,sizeof (stCategorias),1,archivo);

        fclose(archivo);
    }
    else
    {
        printf("Error en el servidor.\n");
    }
    system("pause");
}

void mostrarTodasCategorias(){

    stCategorias categorias;

    FILE * archivo = fopen("categorias.bin","rb");
    if(archivo != NULL)
    {


        printf("\n \n CATEGORIAS \n ");
        while (fread(&categorias,sizeof(stCategorias),1,archivo)>0){

            printf("[%d]",categorias.idCategorias);
            printf("%s\n ", categorias.categorias);
            //printf("\n");
        }
        fclose(archivo);
    }
    else
    {
        printf("Error en el servidor.\n");
    }
}

stCategorias traerCategorias(int idCategoria){

    stCategorias categorias; int flag = 0;
    FILE * archivo = fopen("categorias.bin","rb");
    if(archivo != NULL)

    {
        while (flag ==0 && fread(&categorias,sizeof(stCategorias),1,archivo)>0){
            if (categorias.idCategorias == idCategoria)
                flag =1;
        }
    }

    fclose(archivo);
    return categorias;
}

int totalCategorias(char nombreArchivo[]){

    int peso;
    FILE * file = fopen(nombreArchivo, "rb");

    if (file != NULL){
        fseek(file, sizeof(stCategorias), SEEK_END); ///tiene que ser una variable con el nombre de la estructura
        peso = ftell(file) / sizeof(stCategorias);
        fclose(file);
    }

    return peso;
}
