#include "Login.h"
#include "categorias.h"
#include "publicaciones.h"
#define MAX_INTENTOS 3

int verificarExistenciaUsuario(char registroUsuario[], char userName[])
{
    FILE *archi = NULL;
    stUsuario usuarioAux;
    int flag = 0;

    archi = fopen(registroUsuario, "rb"); ///solo lectura
    if (archi != NULL) {
        while (fread(&usuarioAux, sizeof(stUsuario), 1, archi) > 0 && flag == 0) {
            if (strcmpi(usuarioAux.userName,userName) == 0) ///agregue la "i" a la funcion
                flag = 1;
        }
        fclose(archi);
    }

    return flag;
}
int pesoArchivo(char nombreArchivo[], char structura[]) ///pasar un char que sea el tipo de struct.. hacerlo generico!
{
    FILE *archi =fopen(nombreArchivo,"rb");
    int peso;
    if(archi!=NULL)
    {
        fseek(archi,sizeof(stUsuario),SEEK_END);
        peso = ftell(archi);
        peso = peso /sizeof(stUsuario);
        fclose(archi);
    }
    return peso;
}

stUsuario cargarUsuario()
{
    stUsuario aux;
    int existeUsuario = 0, idUsuario, i=0,flag;
    char opcion='0';

    printf("Nombre : ");
    fflush(stdin);
    gets(aux.nombre);

    printf("Apellido : ");
    fflush(stdin);
    gets(aux.apellido);

    do {

        printf("Nombre de usuario : ");
        fflush(stdin);
        gets(aux.userName);

    }while (verificarExistenciaUsuario("registroUsuarios.bin", aux.userName));

    printf("Contrasenia : ");
    fflush(stdin);
    gets(aux.password);///ojo que pasa los espacios

    do
    {
        printf("Mail : ");///hacer una funcion que valide mail
        fflush(stdin);
        gets(aux.mail);
        flag=1;

        if(strstr(aux.mail,"@hotmail.com")== NULL && strstr(aux.mail,"@gmail.com")==NULL)
        {
            printf("El mail debe contener (@hotmail.com) o (@gmail.com)\n");
            flag=NULL;
        }
    }
    while(flag!=1);

    printf("Genero : ");
    fflush(stdin);
    scanf("%c", &aux.genero);


    ///mostrar categorias!
    mostrarTodasCategorias();

    printf("\nIngrese las categorias que son de su interes: ");
    do{
        if(opcion != '0')
            printf("Ingrese otra categoria: ");
        scanf("%d", &aux.listadoCategorias[i]); ///validar categorias
        printf("\nDesea cargar otra categoria? s/n: ");
        fflush(stdin);
        //printf("%d validos", aux.listadoCategorias[i]);
        scanf("%c",&opcion);
        i++;
    } while(opcion != 'n');

    aux.validosCategorias = i-1;
    aux.rol = 0;///0 usuario normal | 1 admin
    aux.nivel = 0;
    aux.validosContenidos = 0;
    aux.puntaje = 0;
    aux.activo = 1;///1 activo | 0 inactivo

    aux.idUsuario = pesoArchivo("registroUsuarios.bin", "stUsuario"); ///revisar porque no suma 1

    return aux;
}

void mostrarUsuario(stUsuario aux, int rol)
{
    int i=0;
    printf("\n \n \n \n =============================================== \n ");
    if (rol){

        printf("\nID: %d\n", aux.idUsuario);
        printf("Password : %s \n", aux.password);
        printf("Esta Activo: %d\n", aux.activo);
    }
    printf("Nombre : %s \n", aux.nombre);
    printf("Apellido : %s \n", aux.apellido);
    printf("Usuario : %s \n", aux.userName);
    printf("Mail : %s \n", aux.mail);
    printf("Categorias: ");

    ///trae las categorias del usuario y las muestra se puede poner en algun lugar de su perfil..
    while(i<=aux.validosCategorias){
        printf("%s\n", traerCategorias(aux.listadoCategorias[i]).categorias);
        i++;
    }
    printf("Genero : %c \n", aux.genero);
    printf("\n =============================================== \n ");
}

void cargarArchivoUsuario(char registroUsuario[])
{
    stUsuario usuarioAux;
    FILE *archi = NULL;

    archi = fopen(registroUsuario, "ab");///OJOTA esta w
    if (archi != NULL) {
        usuarioAux = cargarUsuario();

        fwrite(&usuarioAux, sizeof(stUsuario), 1, archi);
        fclose(archi);
        printf("Usuario registrado correctamente, sera redirigido al login.\n");///crea usuario mandarlo al login

    } else {
        printf("Error al abrir archivo.\n");
    }
}

void mostrarArchivo(char registroUsuario[])
{
    FILE *archi = NULL;
    stUsuario usuarioAux;

    archi = fopen(registroUsuario, "rb");
    if (archi != NULL) {
        while (fread(&usuarioAux, sizeof(stUsuario), 1, archi) > 0) {
            mostrarUsuario(usuarioAux, usuarioAux.rol);
        }
        fclose(archi);
    }
}

///Esta funcion hace la logica para loguear el usuario
int logear(char nombreUsuario[], char password[])
{
    FILE * archi = NULL;
    int logeoExitoso = -1;
    stUsuario usuarioAux;

    archi = fopen("registroUsuarios.bin", "rb");

    if (archi != NULL) {

        while (fread(&usuarioAux, sizeof(stUsuario), 1, archi) > 0 && logeoExitoso == -1) {
            if (strcmpi(usuarioAux.userName, nombreUsuario) == 0 && strcmpi(usuarioAux.password, password) == 0 && usuarioAux.activo) {
                return usuarioAux.idUsuario; ///devuelde el id del usuario que se loguio
            }
        }
        fclose(archi);
    }

    return logeoExitoso; ///devuelvo -1 porque las credenciales son invalidas
}

///este solo toma los parametros y los manda a logear
int menuIniciarSesion()
{

    char nombreUsuario[20];
    char password[20];
    int intento = 0;
    int loginExitoso = -1;
    char caracter;
    int i=0,flag=0;
    memset(password, 0, 10);


    do {
        system("cls");
         cuadro(1,0,118,38);
        cuadro(35,1,75,3);
        gotoxy(45,2);
        printf("INGRESAR AL SISTEMA\n");
        gotoxy(35,5);
        printf("USUARIO: ");
        gotoxy(44,5);
        scanf("%s", nombreUsuario);
        gotoxy(35,6);
        printf("CLAVE: ");

        ///maneja el arreglo de password y tiene un limite de 3 intentos para loguearse
        do
        {

            caracter = getch();
            if(caracter != 13 && caracter!= 8){
                password[i] = caracter;
                printf("*");
                i++;
            }
            if(caracter == 8 && i > 0) {
                printf("\b \b");
                password[i] = 00;  ///password "hoa" backspace 4 "" "chau"
                i--;

            }

        } while(caracter != 13);

        ///toma el valor de loguear -1 error en los datos sino devuelve el id de usuario
        loginExitoso = logear(nombreUsuario, password);

        if (loginExitoso == -1) {
            printf("\n\n\t\tUsuario y/o password incorrectos \n ");
            system("pause");
            memset(password, 0, 10);///con esto se limpia el arreglo para resetear la pass
            i = 0;
            intento++;
        }
    } while (intento < MAX_INTENTOS && loginExitoso == -1);

    return  loginExitoso;
}

stUsuario buscarUnUsuario(int idUsuario, char nombreArchivo[]){

    FILE * archi = fopen(nombreArchivo, "rb"); stUsuario usuario; int flag = 0, valor;

    ///calcula el valor del paso donde hacer el seek
    valor = sizeof(stUsuario) * (idUsuario-1);
    fseek(archi, valor, SEEK_SET);

    ///lee el valor donde quedo el fseek    fread(&usuario, sizeof(stUsuario),1,archi);
    fclose(archi);

    ///devuelve el usuario entero
    return usuario;
}


int traerTodosUsuarioArray(stUsuario usuarios[], char nombreArchivo[]){


    FILE * file; int i=0;

    file = fopen(nombreArchivo, "rb");

    while (fread(&usuarios[i], sizeof(stUsuario),1,file) > 0){
        i++;
    }

    fclose(file);
    return i;
}

void modificarPerfilUsuario(stUsuario usuario, char nombreArchivo[]){

    FILE * file = fopen(nombreArchivo,"r+b"); int valor, flag; char option; stUsuario aux;

    valor = sizeof(stUsuario) * (usuario.idUsuario -1);
    fseek(file, valor, SEEK_SET);

    fread(&aux, sizeof(stUsuario), 1, file);

    do{
        system("cls");
        cuadro(40,2,79,4);
        gotoxy(44,3);
        printf("[1]- Modificar nombre usuario.\n");
        cuadro(40,6,79,8);
        gotoxy(44,7);
        printf("[2]- Modificar Mail.\n");
        cuadro(40,10,79,12);
        gotoxy(44,11);
        printf("[3]- Modificar Nombre/Apellido.\n");
        cuadro(40,14,79,16);
        gotoxy(44,15);
        printf("[4]- Modificar contrasena.\n");
        option=getch();
        switch (option){
        case '1':
            do {
                printf(" \n \nNombre de usuario : ");
                fflush(stdin);
                gets(aux.userName);

            }while (verificarExistenciaUsuario("registroUsuarios.bin", aux.userName));
        break;
        case '2':
            do
            {
                printf("\n \nMail : ");///hacer una funcion que valide mail
                fflush(stdin);
                gets(aux.mail);
                flag=1;

                if(strstr(aux.mail,"@hotmail.com")== NULL && strstr(aux.mail,"@gmail.com")==NULL)
                {
                    printf("El mail debe contener (@hotmail.com) o (@gmail.com)\n");
                    flag=NULL;
                }
            }
            while(flag!=1);
            break;
        case '3':
            printf("\n \nNombre : ");
            fflush(stdin);
            gets(aux.nombre);

            printf("Apellido : ");
            fflush(stdin);
            gets(aux.apellido);
            break;
        case '4':
            printf("\n \nContrasenia : ");
            fflush(stdin);
            gets(aux.password);///ojo que pasa los espacios
            break;
        default:
            printf("\n \nIngreso una opcion no valida...");
            break;
        }
        printf("\nDesea realizar otro cambio? s/n");
        option=getch();
    }while (option != 'n');

    fseek(file, (-1)*sizeof(stUsuario), SEEK_CUR);

    fwrite(&aux,sizeof(stUsuario),1,file);


    fclose(file);
}

void darBajaUsuario(int idUsuario, char nombreArchivo[]){

    FILE * file = fopen(nombreArchivo,"r+b"); int usuario; stUsuario aux;

    if (file != NULL){

        usuario = sizeof(stUsuario) * (idUsuario -1);
        fseek(file, usuario, SEEK_SET);

        fread(&aux, sizeof(stUsuario), 1, file);

        aux.activo = 0;

        fseek(file, (-1)*sizeof(stUsuario), SEEK_CUR);

        fwrite(&aux,sizeof(stUsuario),1,file);


        fclose(file);
    }
}

void darmeBajaUsuario(stUsuario usuario, char nombreArchivo[]){

    char option;


    printf("Esta seguro de darse de baja? s/n ");
    fflush(stdin);
    scanf("%c", &option);

    if (option == 's' || option == 'S'){
        darBajaUsuario(usuario.idUsuario, nombreArchivo);
    }

}
int encontrarUsuario(stUsuario usuarios[], int validosUsuarios, char nombreUsuario[20]){

    int i=0, flag=0;

    while (flag == 0 && i<validosUsuarios){

        if (strcmpi(usuarios[i].userName, nombreUsuario)==0)
            flag = i;
        i++;
    }

    return flag;
}

stUsuario agregarContenidoLike(stUsuario usuario, int idContenido, char nombreArchivo[]){

    FILE * file = fopen(nombreArchivo,"r+b"); int valor,i=0, flag=0; stUsuario aux;

    valor = sizeof(stUsuario) * (usuario.idUsuario -1);
    fseek(file, valor, SEEK_SET);

    fread(&aux, sizeof(stUsuario), 1, file);
    while (flag == 0 && i < aux.validosContenidos){
        if (aux.listadoIdsContenidosGuardados[i] == idContenido)
            flag =i;
        i++;

    }
    if (!flag){
        aux.validosContenidos = aux.validosContenidos + 1;
        aux.listadoIdsContenidosGuardados[i] = idContenido;
    } else
        aux.listadoIdsContenidosGuardados[flag] = -1;

    fseek(file, (-1)*sizeof(stUsuario), SEEK_CUR);

    fwrite(&aux,sizeof(stUsuario),1,file);


    fclose(file);
    return aux;

}
 int yaDioLike(stUsuario usuario, int idContenido){

    int i=0, flag=0;

    while(flag == 0 && i<usuario.validosContenidos){
        //printf("\n%d", usuario.listadoIdsContenidosGuardados[i]);
        if (usuario.listadoIdsContenidosGuardados[i] == idContenido)
            flag = 1;
        i++;
    }
    return flag;
 }

 int encontrarUsuarioPorId(stUsuario usuarios[], int validosUsuarios, int idUsuario){

    int i=0, flag=-1;

    while(flag==-1 && i<validosUsuarios){

        if (usuarios[i].idUsuario == idUsuario)
            flag=i;
        i++;
    }

    return flag;
}
