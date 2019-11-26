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
}usuario;

int validarLogin();
int registro();
void leerPassword(char password[]);
void insert_at_begin(int id, int password, char nombre[20]);
void setCurrentUser(int id);

struct node *start = NULL;
int count = 0;
char current_user_name[20];
int current_user_id;

int main()
{
    int IDusr = 0;
    int resp;
    while(IDusr == 0)
    {
        system("cls");
        printf(ANSI_COLOR_CYAN     "-- Bienvenido --"     ANSI_COLOR_RESET "\n");
        printf(" 1.- Iniciar sesion\n");
        printf(" 2.- Registrarse\n");
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
        else
        {
            printf("Seleccione una opcion valida");
        }
    }
    if(IDusr != 0)
    {
        system("cls");
        setCurrentUser(IDusr);
        printf(ANSI_COLOR_CYAN "Bienvenido %s", current_user_name);
        printf(ANSI_COLOR_RESET);
        /* TOOOOODOOOO EL CODIGO DE FUNCIONAMIENTO AQUI */

    }
}

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
        system("pause");
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


void setCurrentUser(int id){
    struct node *t;
    t = start;
    while (t->next != NULL)
    {
        if(t->idUsuario == id){
            strcpy(current_user_name,t->nombre);
            current_user_id = t->idUsuario;
        }
        t = t->next;
    }
}


