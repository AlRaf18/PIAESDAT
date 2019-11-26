#include <stdio.h>
#include <string.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"

typedef struct node
{
    int idUsuario;
    int idTrabajador;
    int password;
    char nombre[20];
    struct node *next;
} usuario;

struct contacto
{
    char nombre[20];
    int idCurrentUser;
    int idUsuarioContacto;
    struct contacto *next;
};

int validarLogin();
int registro();
void leerPassword(char password[]);
void insert_at_begin(int id, int password, char nombre[20]);
void setCurrentUser(int id);
void contactos();
void mensajes();
void notificaciones();
void cerrarsesion();
void anadirContacto();
void eliminarContacto();
void verSolicitudes();
void verConversaciones();
void enviarMensaje();

struct node *start = NULL;

int count = 0;
char current_user_name[20];
int current_user_id;

int main()
{
    int IDusr = 0;
    int resp;
    int salir = 0;
    while(IDusr == 0 && salir == 0)
    {
        system("cls");
        printf(ANSI_COLOR_CYAN     "-- Bienvenido --"     ANSI_COLOR_RESET "\n");
        printf(" 1.- Iniciar sesion\n");
        printf(" 2.- Registrarse\n");
        printf(" 3.- Salir\n");
        scanf("%d", &resp);
        if(resp == 1)
        {
            IDusr = validarLogin();
        }
        else if(resp == 2 )
        {
            registro();
            system("pause");
        }
        else if(resp == 3 )
        {
            salir = 1;
            printf(ANSI_COLOR_MAGENTA     "Hasta la proxima!"     ANSI_COLOR_RESET "\n");
            getch();
        }
        else
        {
            printf(ANSI_COLOR_RED     "Seleccione una opcion valida"     ANSI_COLOR_RESET "\n");
            getch();
        }
        while(IDusr != 0)
        {
            system("cls");
            setCurrentUser(IDusr);
            printf(ANSI_COLOR_CYAN "Bienvenido %s\n", current_user_name);
            printf(ANSI_COLOR_RESET);

            printf("1.- Contactos\n");
            printf("2.- Mensajes\n");
            printf("3.- Notificaciones\n");
            printf("4.- Cerrar sesion\n");
            scanf("%d", &resp);
            if(resp == 1)
            {
                contactos();
            }
            else if(resp == 2)
            {
                mensajes();
            }
            else if(resp == 3)
            {
                notificaciones();
            }
            else if(resp == 4)
            {
                cerrarsesion();
                IDusr = 0;
            }
            else
            {
                printf(ANSI_COLOR_RED     "Seleccione una opcion valida"     ANSI_COLOR_RESET "\n");
                getch();
            }
        }
    }
}

/* ------------------------------ FUNCIONES PARA LOGIN ----------------------------------------------- */
int validarLogin()
{
    system("cls");
    printf(ANSI_COLOR_CYAN     "-- Iniciar Sesion --"     ANSI_COLOR_RESET "\n");
    int id;
    char password[12];
    int intpass;
    int correct;
    int idUsuario = 0;
    struct node *t;
    t = start;
    if (t == NULL)
    {
        printf(ANSI_COLOR_RED     "Aun no hay usuarios."     ANSI_COLOR_RESET "\n");
        getch();
        return 0;
    }

    printf("id de trabajador: ");
    scanf("%d",&id);
    printf("Password: ");
    leerPassword(password);

    intpass = atoi(password);
    while (t->next != NULL)
    {
        if(id == t->idTrabajador)
        {
            if(intpass == t->password)
            {
                correct = 1;
                idUsuario = t->idUsuario;
                return idUsuario;
            }
            else
            {
                printf("\n");
                printf(ANSI_COLOR_RED     "Error en password."     ANSI_COLOR_RESET "\n");
                system("pause");
            }
        }
        else
        {
            printf("\n");
            printf(ANSI_COLOR_RED     "Error en usuario."     ANSI_COLOR_RESET "\n");
        }
        t = t->next;
    }
    if(correct == 0)
    {
        idUsuario = 0;
    }
    return idUsuario;
}

int registro()
{
    system("cls");

    printf(ANSI_COLOR_CYAN     "-- Registro --"     ANSI_COLOR_RESET "\n");
    int idTrabajador;
    int password;
    char nombre[20];

    printf("Nombre: ");
    scanf("%s",&nombre);
    printf("\n");
    printf(ANSI_COLOR_MAGENTA "Nota: " ANSI_COLOR_RESET "Solo se permiten valores numericos en " ANSI_COLOR_MAGENTA "ID " ANSI_COLOR_RESET "y " ANSI_COLOR_MAGENTA "Password" ANSI_COLOR_RESET  "\n");
    printf("ID de trabajador: ");
    scanf("%d",&idTrabajador);
    printf("password: ");
    scanf("%d",&password);
    insert_at_begin(idTrabajador, password, nombre);
    struct contacto *start = NULL;

    return idTrabajador;
}

void leerPassword(char password[])
{
    int p=0;
    do
    {
        password[p]=getch();
        if(password[p]!='\r')
        {
            printf("*");
        }
        p++;
    }
    while(password[p-1]!='\r');
    password[p-1]='\0';
}

void insert_at_begin(int id, int password, char nombre[20])
{
    struct node *t;

    t = (struct node*)malloc(sizeof(struct node));
    count++;

    if (start == NULL)
    {
        start = t;
        start->idUsuario = count;
        start->idTrabajador = 000;
        start->password = password;
        start->next = NULL;
        insert_at_begin(id, password, nombre);
        return;
    }
    t->idUsuario = count;
    t->idTrabajador = id;
    t->password = password;
    t->next = start;
    strcpy(t->nombre,nombre);
    start = t;
    printf(ANSI_COLOR_GREEN     "Registro exitoso"     ANSI_COLOR_RESET "\n");
}


void setCurrentUser(int id)
{
    struct node *t;
    t = start;
    while (t->next != NULL)
    {
        if(t->idUsuario == id)
        {
            strcpy(current_user_name,t->nombre);
            current_user_id = t->idUsuario;
        }
        t = t->next;
    }
}

/* ------------------------------ FUNCIONES PRINCIPALES ----------------------------------------------- */

void contactos()
{
    int volver = 0;
    do
    {
        system("cls");
        printf(ANSI_COLOR_CYAN     "-- Contactos --"     ANSI_COLOR_RESET "\n");
        int resp;
        printf("1.- Anadir\n");
        printf("2.- Eliminar\n");
        printf("3.- Solicitudes\n");
        printf("4.- Volver\n");
        scanf("%d", &resp);
        if(resp == 1)
        {
            anadirContacto();
        }
        else if(resp == 2)
        {
            eliminarContacto();
        }
        else if(resp == 3)
        {
            verSolicitudes();
        }
        else if(resp == 4)
        {
            volver = 1;
        }
        else
        {
            printf(ANSI_COLOR_RED     "Seleccione una opcion valida"     ANSI_COLOR_RESET "\n");
            getch();
        }
    }
    while(volver == 0);
}
void mensajes()
{
    int volver = 0;
    do
    {
        system("cls");
        printf(ANSI_COLOR_CYAN     "-- Mensajes --"     ANSI_COLOR_RESET "\n");
        int resp;
        printf("1.- Enviar\n");
        printf("2.- Conversaciones\n");
        printf("3.- Volver\n");
        scanf("%d", &resp);
        if(resp == 1)
        {
            enviarMensaje();
        }
        else if(resp == 2)
        {
            verConversaciones();
        }
        else if(resp == 3)
        {
            volver = 1;
        }
        else
        {
            printf(ANSI_COLOR_RED     "Seleccione una opcion valida"     ANSI_COLOR_RESET "\n");
            getch();
        }
    }
    while(volver == 0);
}
void notificaciones()
{
}
void cerrarsesion()
{
    current_user_name[20] = NULL;
    current_user_id = NULL;
}

/* --------------------------------------- SUBFUNCIONES ----------------------------------------------- */

void anadirContacto()
{
}
void eliminarContacto()
{
}
void verSolicitudes()
{
}
void verConversaciones()
{
}
void enviarMensaje()
{
}
