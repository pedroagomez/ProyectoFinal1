#include <stdio.h>
#include <stdlib.h>
#include "./lib/publicaciones.h"
#include "./lib/Login.h"
#include "./lib/categorias.h"
#include <conio.h>
#include <windows.h>
#include <unistd.h>
#include "./lib/mensaje.h"


void inicio()
{
    char opcion,opcionPos, opcionMenuPrincipal,opcionmensaje, opcionLike, opcionAdmin, opcionPostAdmin, opcionUsuariosAdmin;
    char archivoRegistro[25];
    char palabraAbuscar[10];
    strcpy(archivoRegistro, "registroUsuarios.bin");

    char archivoContenido[50];
    strcpy(archivoContenido,"contenidos.bin");
    stUsuario usuario1;
    stContenido contenidos[100];
    stUsuario usuarios[50];
    int i=0,posicionContenido, idContenido, idCategoria;
    int validosUsuarios = traerTodosUsuarioArray(usuarios, archivoRegistro);
    int validosContenidos = traerTodosPostArray(contenidos, archivoContenido);
    int validosContenidosAdmin, posicionUsuario;

    do
    {
        system("cls");
        cuadro(1,0,118,38);
        cuadro(35,1,85,3);
        gotoxy(40,2);
        printf("B I E N V E N I D O   A L   S I S T E M A");
        cuadro(46,6,74,8);
        gotoxy(52,7);
        printf("[1] Iniciar sesion ");
        cuadro(46,9,74,11);
        gotoxy(52,10);
        printf("[2] Registrarse ");
        gotoxy(52,11);



        //gotoxy(35,10);
        opcion=getch();


        switch(opcion)
        {
        case '1':

                system("cls");

            int idUsuario = menuIniciarSesion();
            if (idUsuario != -1 && !buscarUnUsuario(idUsuario, archivoRegistro).rol)
            {   cuadro(1,0,118,38);
                system("cls");
                barra();
                validosUsuarios = traerTodosUsuarioArray(usuarios, archivoRegistro);
                validosContenidos = traerTodosPostArray(contenidos, archivoContenido);

                usuario1 = buscarUnUsuario(idUsuario, archivoRegistro);


                do
                {
                    system("cls");

                    menu(usuario1);
                    cuadro(47,8,67,10);
                    gotoxy(50,9);
                    printf(" PUBLICACIONES \n ");

                    i=validosContenidos-1;
                    while(i >= 0)
                    {

                        mostrarContenido(contenidos[i], usuario1.rol,usuarios, validosUsuarios);

                        i--;
                    }
                   ;
                    gotoxy(1,1);
                    opcionMenuPrincipal=getch();

                    switch(opcionMenuPrincipal)///menu principal
                    {
                    case '1'://publicacion
                        do
                        {

                            system("cls");
                            ///menu de publicacion
                            menuPublicaciones();

                            ///termona menu
                            opcionPos=getch();
                            switch(opcionPos)///menu publica
                            {
                            case '1':
                                system("cls");

                                cargaDeContenidoArchivo("contenidos.bin",usuario1);
                                validosContenidos = traerTodosPostArray(contenidos, archivoContenido);///TRAER VALIDOS COMO VARIABLE
                                usuario1 = buscarUnUsuario(idUsuario, archivoRegistro);
                                break;
                            case '2':
                                system("cls");
                                cuadro(47,2,67,4);
                                gotoxy(51,3);
                                printf(" MIS POSTEOS\n ");
                                misPosteos(contenidos, validosContenidos, usuario1);
                                system("pause");
                                break;
                            case '3':
                                system("cls");
                                printf("Ingrese la palabra a buscar: ");
                                fflush(stdin);
                                scanf("%s",palabraAbuscar);
                                posicionContenido=buscarContenidoPorPalabra(contenidos,validosContenidos,palabraAbuscar);
                                if(posicionContenido!= -1)
                                {
                                    mostrarContenido(contenidos[posicionContenido], usuario1.rol,usuarios, validosUsuarios);
                                }
                                else
                                {
                                    printf("No se encontro la palabra\n");
                                }
                                posicionContenido = 0;
                                system("pause");
                                break;
                            case '4'://modificar publicacion
                                system("cls");
                                printf("Ingrese el id de la publicacion a modificar: ");
                                scanf("%d",&idContenido);
                                posicionContenido = buscarContenidoPorId(contenidos, validosContenidos, idContenido);
                                if (!modificarPosteo(contenidos[posicionContenido], usuario1.idUsuario, archivoContenido))
                                    printf("\nUsted no tiene permiso para modificar esta publicacion!.\n\n");
                                else
                                {
                                    validosContenidos = traerTodosPostArray(contenidos, archivoContenido);
                                    printf("\nPosteo modificado con exito!.\n\n");

                                }
                                posicionContenido = 0;
                                system("pause");
                                break;
                            case '5':
                                system("cls");
                                mostrarTodasCategorias();
                                cuadro(1,0,47,2);
                                gotoxy(2,1);
                                printf("Ingrese la categoria para filtrar los post: ");
                                scanf("%d",&idCategoria);
                                if (!filtrarPostCategoria(contenidos,validosContenidos,idCategoria,usuarios, validosUsuarios))
                                    printf("\n \n \n \n \n \n \n \nNo hay posteos con esa categoria.\n");
                                printf("\n\n");
                                system("pause");
                                break;
                            case '6':

                                system("cls");
                                printf("Ingrese el id de la publicacion para interactuar: ");
                                scanf("%d", &idContenido);

                                posicionContenido = buscarContenidoPorId(contenidos, validosContenidos, idContenido);
                                if (posicionContenido){
                                    int dioLike = yaDioLike(usuario1, contenidos[posicionContenido].idContenido);
                                    do{
                                        system("cls");
                                        printf("Dar like/dislike = espacio                              Salir = esc    \n");
                                        mostrarContenido(contenidos[posicionContenido], usuario1.rol,usuarios, validosUsuarios);
                                        /// g=103   space=32
                                        //printf("\n\n\n\n%d",dioLike);
                                        opcionLike=getch();
                                        switch(opcionLike){
                                            case 32:
                                                if(!dioLike){
                                                    dioLike=1;
                                                    contenidos[posicionContenido].likes = contenidos[posicionContenido].likes + 1;

                                                } else {
                                                    dioLike = 0;
                                                    contenidos[posicionContenido].likes = contenidos[posicionContenido].likes - 1;
                                                }
                                                break;

                                        }

                                    }while (opcionLike != 27);
                                    if (dioLike && !yaDioLike(usuario1,contenidos[posicionContenido].idContenido)){
                                            funcionDarLike(contenidos[posicionContenido], archivoContenido);
                                            usuario1 = agregarContenidoLike(usuario1, contenidos[posicionContenido].idContenido, archivoRegistro);
                                    }
                                    else{
                                        if (yaDioLike(usuario1, contenidos[posicionContenido].idContenido)){

                                            funcionDarDislike(contenidos[posicionContenido], archivoContenido);
                                            usuario1 = agregarContenidoLike(usuario1, contenidos[posicionContenido].idContenido, archivoRegistro);
                                        }

                                    validosContenidos = traerTodosPostArray(contenidos, archivoContenido);
                                    }
                                } else
                                    printf("\nNo se encontro publicacion con ese id.");
                                system("pause");
                                break;
                            }
                        }
                        while(opcionPos!=27);

                        break;///case1 nivel 2


                    case '2':///mensajes
                        do
                        {

                            system("cls");
                            cuadro(44,2,72,4);
                            gotoxy(50,3);
                            printf("INGRESE UNA OPCION ");
                            printf("\n");
                            gotoxy(45,6);
                            printf("[1] Mandar mensaje");
                            gotoxy(45,8);
                            printf("[2] Ver casilla de mensajes");
                            printf("\n");
                            fflush(stdin);
                            opcionmensaje=getch();
                            switch(opcionmensaje)
                            {
                            case '1':

                                guardarMensajeenArchivo();
                                break;

                            case '2':

                                //bajarMensajedeArchivo();
                                validarRemitente(usuario1);
                                system("pause");
                                break;

                            }
                        }
                        while(opcionmensaje!=27);

                        break;//break mensajes
                    case '3':
                        system("cls");
                        char nombreUsuario[20];
                        printf("\nIngrese el nombre de usuario a buscar: ");
                        fflush(stdin);
                        scanf("%s", nombreUsuario);
                        int posicionUsuario = encontrarUsuario(usuarios, validosUsuarios, nombreUsuario);
                        if (posicionUsuario)
                            mostrarUsuario(usuarios[posicionUsuario], usuario1.rol);
                        else
                            printf("\n\nNo se encontro usuario con ese nombre.\n");
                        system("pause");
                    break;
                    case '4':
                        //system("cls");
                        modificarPerfilUsuario(usuario1, archivoRegistro);
                        printf("\n\n");
                        system("pause");
                        break;

                    }
                }
                while(opcionMenuPrincipal!=27);

            } else if (idUsuario != -1 && buscarUnUsuario(idUsuario, archivoRegistro).rol){
                usuario1 = buscarUnUsuario(idUsuario, archivoRegistro);

                validosUsuarios = traerTodosUsuarioArray(usuarios, archivoRegistro);
                validosContenidosAdmin = traerTodosPostAdmin(contenidos, archivoContenido);

                do{
                    system("cls");
                    cuadro(1,1,30,3);
                    gotoxy(4,2);
                    printf("VER TODAS PUBLICACIONES\n");
                    cuadro(1,4,30,6);
                    gotoxy(4,5);
                    printf("VER TODOS LOS USUARIOS\n");
                    cuadro(1,7,30,9);
                    gotoxy(4,8);
                    printf("VER TODOS LOS MENSAJES\n\n ");
                    opcionAdmin = getch();
                    switch(opcionAdmin){
                    case '1':
                        system("cls");
                        i=validosContenidosAdmin-1;
                        while(i >= 0)
                        {
                            mostrarContenido(contenidos[i], usuario1.rol,usuarios, validosUsuarios);
                            i--;
                        }
                        cuadro(1,1,20,3);
                        gotoxy(4,2);
                        printf("1-DAR BAJA POST \n");
                        opcionPostAdmin=getch();
                        switch(opcionPostAdmin){
                        case '1':
                            system("cls");
                            cuadro(1,1,47,3);
                            gotoxy(4,2);
                            printf("INGRESE EL ID DEL POST A DAR DE BAJA: ");
                            scanf("%d", &idContenido);
                            posicionContenido = buscarContenidoPorId(contenidos,validosContenidosAdmin,idContenido);
                            if (posicionContenido != -1){
                                mostrarContenido(contenidos[posicionContenido],usuario1.rol,usuarios, validosUsuarios);
                                printf("\nDARA DE BAJA AL POST, ESTA SEGURO? 1 si/ 0 no");
                                opcionPostAdmin = getch();
                                if (opcionPostAdmin=='1'){
                                    darBajaPostAdmin(idContenido,archivoContenido);
                                    validosContenidosAdmin = traerTodosPostAdmin(contenidos, archivoContenido);
                                    puts("POST BDADO DE BAJA!");
                                }
                            }
                            else
                                puts("NOSE ENCONTRO POST CON ESE ID \n!");
                            posicionContenido = 0;
                            system("pause");
                            break;
                        }
                        break;
                    case '2':
                        system("cls");
                        i=validosUsuarios-1;
                        while(i >= 0)
                        {
                            mostrarUsuario(usuarios[i],usuario1.rol);
                            i--;
                        }
                        cuadro(1,1,22,3);
                        gotoxy(4,2);
                        printf("DAR BAJA USUARIO\n \n");
                        opcionUsuariosAdmin = getch();
                        switch(opcionUsuariosAdmin){
                        case '1':
                            system("cls");
                             cuadro(1,1,47,3);
                             gotoxy(4,2);
                            printf("Ingrese el Id del usuairo a dar de baja: ");
                            scanf("%d", &idUsuario);
                            posicionUsuario = encontrarUsuarioPorId(usuarios,validosUsuarios,idUsuario);
                            if (posicionUsuario!=-1){
                                mostrarUsuario(usuarios[posicionUsuario], usuario1.rol);
                                printf("\nDARA DE BAJA AL USUARIO, ESTA SEGURO? 1 si/ 0 no");
                                opcionPostAdmin = getch();
                                if (opcionPostAdmin=='1'){
                                    darBajaUsuario(idUsuario,archivoRegistro);
                                    validosUsuarios = traerTodosUsuarioArray(usuarios, archivoRegistro);
                                    puts("SE DIO DE BAJA EL USUARIO CORRECTAMENTE");
                                }
                            } else
                                puts("NO SE ENCONTRO USUARIO CON ESE ID");
                            break;
                        }
                        system("pause");
                        break;

                        case '3':

                            system("cls");

                            mostrarTodosLosMensajes();
                            system("pause");
                            break;
                    }
                }while(opcionAdmin!=27);
            }
            break;///cierra caso1nivel1

        case '2':
            system("cls");
            cargarArchivoUsuario("registroUsuarios.bin");
            system("pause");
            break;

        default:

            break;



        }
    }
    while(opcion!=27);
}






void menu(stUsuario usuario)
{

    cuadro(40,1,80,3);
    gotoxy(45,2);
    strupr(usuario.nombre);
    printf("  BIENVENIDO AL SISTEMA %s\n Nivel Usuario: %d   Puntaje: %d", usuario.nombre,usuario.nivel, usuario.puntaje);

    cuadro(3,4,115,6);
    gotoxy(5,5);
    printf("[1]Menu posteos");
    gotoxy(26,5);
    printf("[2]Mensajeria");
    gotoxy(45,5);
    printf("\t [3]Buscar usuario");
    gotoxy(73,5);
    printf("[4]Editar Mi perfil");
    gotoxy(97,5);
    printf("[5]SALIR(ESC)");

}
void menuPublicaciones(){
cuadro(40,1,77,3);
gotoxy(53,2);
printf("MENU POSTEO\n");


cuadro(4,5,50,23);
    gotoxy(1,6);
    printf("\t [1]Publicar un Post");
    gotoxy(1,9);
    printf("\t [2]Ver mis Posteos");
    gotoxy(1,12);
    printf("\t [3]Buscar un Post");
    gotoxy(1,15);
    printf("\t [4]Modificar un Post");
    gotoxy(1,18);
    printf("\t [5]Filtrar Post por categoria");
    gotoxy(1,21);
    printf("\t [6]Dar Like");
}
void interfaz()
{
    cuadro(0,0,98,390);

}
void centrarTextoo(char *texto, int y)
{
    int longitud=strlen(texto);
    gotoxy(48-longitud/2,y) ;
    printf(texto);
}
void barra()
{
    gotoxy(50,30);
    printf("CARGANDO ... ");
    for(int i=3; i<114; i++)
    {
        gotoxy(i,33);
        printf("%c",177);
    }
    for(int i=3; i<114; i++)
    {
        gotoxy(i,33);
        printf("%c",219);
        usleep(1000);
    }
}
void gotoxy(int X,int Y)                                                        /// Cambia las coordenadas del cursor
{
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X=X;
    dwPos.Y=Y;
    SetConsoleCursorPosition(hcon,dwPos);
}
void cuadro(int x1, int y1,int x2, int y2)
{
    int i;
    for(i=x1; i<x2; i++)
    {
        gotoxy(i,y1);
        printf("Ä");
        gotoxy(i,y2);
        printf("Ä");
    }
    for(i=y1; i<y2; i++)
    {
        gotoxy(x1,i);
        printf("³");
        gotoxy(x2,i);
        printf("³");
    }
    gotoxy(x1,y1);
    printf("Ú");
    gotoxy(x1,y2);
    printf("À");
    gotoxy(x2,y1);
    printf("¿");
    gotoxy(x2,y2);
    printf("Ù");
}

int main()
{
    system("color A0");
    inicio();





}



