#include "publicaciones.h"
#include "categorias.h"
#include "Login.h"
///FUNCION QUE CARGA CONTENIDO AL SISTEMA DE A UNO PORQUE LO CARGA EL USER
void cargaDeContenidoArchivo(char nombre_archivo_contenido[], stUsuario usuario)///
{

    stContenido contenido; stUsuario aux;

    FILE * archivo = fopen(nombre_archivo_contenido,"ab");
    FILE * archivoU = fopen("registroUsuarios.bin","r+b");
    if(archivo!=NULL && archivoU!=NULL)
    {
        contenido = cargaUnContenido();

        int valor = sizeof(stUsuario) * (usuario.idUsuario -1);
        fseek(archivoU, valor, SEEK_SET);

        fread(&aux, sizeof(stUsuario), 1, archivoU);

        contenido.idContenido = calcularPeso(nombre_archivo_contenido); ///id autoincrementa
        contenido.idUser = usuario.idUsuario; ///ususario que crea el post
        aux.puntaje = aux.puntaje + 10;///los puntos que obtiene por cargar un post
        if(aux.puntaje == 50)
        {

            aux.nivel=aux.nivel +1;

            aux.puntaje = 0;

        }///en caso de llegar a 50 sube un nivel osea 5 post

            fseek(archivoU, (-1)*sizeof(stUsuario), SEEK_CUR);
            fwrite(&aux,sizeof(stUsuario),1,archivoU);
        fwrite(&contenido,sizeof (stContenido),1,archivo);

        //sleep(3000); ///nose para q
        system("cls");
        fclose(archivo);
        fclose(archivoU);
    }
    else
        printf("Error en el servidor.\n");

    system("pause");
}

//FUNCION CARGA UN CONTENIDO-------------------------
stContenido cargaUnContenido()
{
    //variables
    stContenido dato;
    cuadro(40,1,80,3);
    int flag=0,flag2=0,posicionSalto=31;
    char inputmax[30];
    srand(time(NULL));

    //codigo


    gotoxy(54,2);
    printf("CREA TU POST");
    //printf("Crea tu POST");


    printf("\n\n Titulo: ");
    fflush(stdin);
    gets(dato.titulo);

    ///de aca
    while (flag == 0)
    {
        printf("\nDescripcion:\n");
        fflush(stdin);
        gets(dato.descripcion);

        if (strlen(dato.descripcion) > 100)
        {
            printf("Ups, parece que te has pasado del límite de caracteres (%d). Vuelve a intentarlo: ", 100);
            flag=0;
        }
        else
        {
            flag = 1;
        }
    }
    ///hasa taca la reversion
    //gets(dato.descripcion);
    dato.likes = rand()%50;
    dato.activo = 1; ///si esta activo es 1 inactivo =0

    ///aca trae las categorias manejarse con el id por eso tiene un numero al lado de la categoria!!
    mostrarTodasCategorias();

    printf("\nElija la categoria del post: ");
    scanf("%d", &dato.categoria);

    system("cls");

    return dato;
}

//FUNCION MUESTRO CONTENIDO X UNO
stContenido mostrarContenido(stContenido contenido, int rol, stUsuario usuarios[], int validosUsuarios)
{
    stCategorias categoria; int posicionUsuario;

    if (rol){
        printf("\n \n \n \n \t \t \t  Id usuario creador: %d", contenido.idUser);
        printf("\n\t \t \t  idcontenido: %d", contenido.idContenido);
        printf("\n \t \t \t Esta activo: %d", contenido.activo);
    }
    printf("\n\t\t\t Creador: %s",usuarios[encontrarUsuarioPorId(usuarios, validosUsuarios, contenido.idUser)].userName);
    printf("\n\t \t \t  Titulo: ");
    saltoDeLineaCada60Caracteres(contenido.titulo);
    printf("\n \t \t \t  Descripcion : ");
    saltoDeLineaCada60Caracteres(contenido.descripcion);
    printf("\n\t \t \t  <3: %d ", contenido.likes);
    ///aca trae la categoria y la muestra
    printf("\n\t \t \t  Categoria: %s ", traerCategorias(contenido.categoria).categorias);
    printf("\n\t \t \t --------------------------------------------------------------------\n");
}
//FUNCION PARA SALTAR LINEA 40 CARACTERES
void saltoDeLineaCada60Caracteres(const char* texto) {
    int longitud = strlen(texto);
    int i;

    for (i = 0; i < longitud; i++) {
        printf("%c", texto[i]);

        if ((i + 1) % 60 == 0) {
            printf("\n \t \t \t \t ");
        }
    }
}
//FUNCION MUESTRO CONTENIDOS
/*void mostrarArchivoContenido(char nombre_archivo_contenido[], stUsuario usuario)
{
    stContenido contenido;

    FILE * archivo = fopen(nombre_archivo_contenido,"rb");

    if(archivo != NULL)
    {
        while(fread(&contenido,sizeof(stContenido),1,archivo)>0)
        {
            //MUESTRO
            if (usuario.idUsuario == contenido.idUser)
                mostrarContenido(contenido, usuario.rol,usuarios, validosUsuarios);
        }
    }
    else
    {
        printf("Error en el servidor.\n");
    }
    fclose(archivo);

}*/
///MODIFICAR CONTENIDO: FALTA ID DE USUARIO Y CONTENIDO
int calcularPeso(char nombreArchivo[])
{

    int peso;
    FILE * file = fopen(nombreArchivo, "rb");

    if (file != NULL)
    {
        fseek(file, sizeof(stContenido), SEEK_END); ///tiene que ser una variable con el nombre de la estructura
        peso = ftell(file) / sizeof(stContenido);
        fclose(file);
    }

    return peso;
}

int traerTodosPostArray(stContenido contenidos[],char nombreArchivo[])
{

    FILE * file = fopen(nombreArchivo,"rb");
    int i=0;

    if (file!=NULL)

        while (fread(&contenidos[i],sizeof(stContenido),1,file) > 0)
        {
            if (contenidos[i].activo)
                i++;
        }

    fclose(file);
    return i;
}

int buscarContenidoPorPalabra(stContenido contenidos[],int validosContenido, char palabra[])
{

    int flag=0, i=0;

    while (flag == 0 && i < validosContenido)
    {
        //printf("AAA");
        if (strstr(contenidos[i].descripcion,palabra) != NULL || strstr(contenidos[i].titulo,palabra) != NULL)
            flag = i;
        i++;
    }

    ///test
    //if (flag)
    //mostrarContenido(contenidos[flag]);

    return flag;
}

void darBajaPostAdmin(int idPost, char nombreArchivo[])
{

    FILE * file = fopen(nombreArchivo,"r+b");
    int valor;
    stContenido aux;

    valor = sizeof(stContenido) * (idPost-1);
    fseek(file, valor, SEEK_SET);

    fread(&aux, sizeof(stContenido), 1, file);

    aux.activo = 0;

    fseek(file, (-1)*sizeof(stContenido), SEEK_CUR);

    fwrite(&aux,sizeof(stContenido),1,file);


    fclose(file);
}

void misPosteos(stContenido contenidos[], int validosContenidos, stUsuario usuario)
{

    int i =0, cont=0; stUsuario usuarios[1];

    usuarios[0]=usuario;
    while (i < validosContenidos)
    {

        if (usuario.idUsuario == contenidos[i].idUser)
        {
            mostrarContenido(contenidos[i], usuario.rol, usuarios,1);///revisar esta linea
            cont++;
        }
        i++;

    }

    if(cont ==0)
        printf("\nUsted no tiene ningun post creado!.");

}

int buscarContenidoPorId(stContenido contenidos[], int validosContenidos, int idContenido)
{

    int i=0, flag = -1;

    while(flag == -1 && i<validosContenidos)
    {
        if (contenidos[i].idContenido == idContenido)
            flag = i;
        i++;
    }
    return flag;
}
int modificarPosteo(stContenido contenido, int idUsuario, char nombreArchivo[])
{

    if (contenido.idUser == idUsuario)
    {

        FILE * file = fopen(nombreArchivo,"r+b");
        int valor;
        char option;
        stContenido aux;

        valor = sizeof(stContenido) * (contenido.idContenido -1);
        fseek(file, valor, SEEK_SET);

        fread(&aux, sizeof(stContenido), 1, file);

        do
        {
            system("cls");
             cuadro(40,2,79,4);
            gotoxy(44,3);
            printf("[1] Modificar Titulo publicacion\n");
            cuadro(40,6,79,8);
            gotoxy(44,7);
            printf("[2] Modificar Descripcion\n");
            option=getch();
            switch (option)
            {
            case '1':
                printf("\n \nIngrese Titulo: ");
                fflush(stdin);
                gets(aux.titulo);
                break;
            case '2':
                printf("\n \nIngrese descripcion: ");///hacer una funcion que valide mail
                fflush(stdin);
                gets(aux.descripcion);
                break;
            default:
                printf("Ingreso una opcion no valida...");
                break;
            }
            printf("\nDesea realizar otro cambio? s/n");
            option=getch();
        }
        while (option != 'n');

        fseek(file, (-1)*sizeof(stContenido), SEEK_CUR);

        fwrite(&aux,sizeof(stContenido),1,file);


        fclose(file);
        return 1;

    }
    else
        return 0;

}

int filtrarPostCategoria(stContenido contenidos[], int validosContenidos, int idCategoria, stUsuario usuarios[], int validosUsuarios)
{

    int i = 0, cont = 0;

    while (i<validosContenidos)
    {

        if (contenidos[i].categoria == idCategoria)
        {
            mostrarContenido(contenidos[i],0, usuarios, validosUsuarios);///revisar esto mas adelante
            cont++;
        }
        i++;

    }
    return cont;
}
int filtrarPorMisCatgorias(stContenido contenidos[],int validosContenidos, stUsuario usuario)
{

    int i = 0, cont = 0; stUsuario usuarios[1];

    usuarios[0]=usuario;
    while (i<validosContenidos)
    {

        if (contenidos[i].categoria==usuario.listadoCategorias)
        {
            mostrarContenido(contenidos[i],0, usuarios,1);///revisar esto mas adelante
            cont++;
        }
        i++;
        /*FILE*archivo=fopen("contenidos.bin","rb");
        while(fread()){
            if(auxCat.idCategorias==auxU.listadoCategorias)

        }
        */
        return cont;

    }
}

void funcionDarLike(stContenido contenido, char nombreArchivo[]){

    FILE * file = fopen(nombreArchivo,"r+b");
    int valor;
    stContenido aux;

    valor = sizeof(stContenido) * (contenido.idContenido -1);
    fseek(file, valor, SEEK_SET);

    fread(&aux, sizeof(stContenido), 1, file);

    aux.likes = aux.likes + 1;

    fseek(file, (-1) * sizeof(stContenido), SEEK_CUR);

    fwrite(&aux,sizeof(stContenido),1,file);

    fclose(file);


}

void funcionDarDislike(stContenido contenido, char nombreArchivo[]){

    FILE * file = fopen(nombreArchivo,"r+b");
    int valor;
    stContenido aux;

    valor = sizeof(stContenido) * (contenido.idContenido -1);
    fseek(file, valor, SEEK_SET);

    fread(&aux, sizeof(stContenido), 1, file);

    aux.likes = aux.likes - 1;

    fseek(file, (-1) * sizeof(stContenido), SEEK_CUR);

    fwrite(&aux,sizeof(stContenido),1,file);

    fclose(file);


}

int traerTodosPostAdmin(stContenido contenidos[], char nombreArchivo[]){

    FILE * file = fopen(nombreArchivo,"rb");
    int i=0;

    if (file!=NULL)

        while (fread(&contenidos[i],sizeof(stContenido),1,file) > 0)
        {
            i++;
        }

    fclose(file);
    return i;
}



