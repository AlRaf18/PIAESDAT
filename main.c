#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

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

struct solicitudes
{
    int idCurrentUser;
    int idContact;
    struct solicitudes *next;
};

struct contactos
{
    int idUser1;
    int idUser2;
    struct contactos *next;
};

struct mensajes
{
	int idCurrentUser;
	int idContact;
	char mensaje[100];
	struct mensajes *next;
};

struct notificaciones
{
    int idUserReceiver;
    char kind[20];
    int idUserReminder;
    struct notificaciones *next;
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
struct solicitudes *start_solicitudes = NULL;
struct notificaciones *start_notificaciones = NULL;
struct contactos *start_contactos = NULL;
struct mensajes *start_mensajes = NULL;

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
            printf("3.- Notificaciones");
            printf("(");
            cantidadDeNotificaciones();
            printf(")\n");
            printf("4.- Mi informacion\n");
            printf("5.- Cerrar sesion\n");
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
                verInformacionDelContacto(current_user_id);
                getch();
            }
            else if(resp == 5)
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
        printf("2.- Ver contactos\n");
        printf("3.- Solicitudes\n");
        printf("4.- Volver\n");
        scanf("%d", &resp);
        if(resp == 1)
        {
            anadirContacto();
        }
        else if(resp == 2)
        {
            verContactos();
        }
        else if(resp == 3)
        {
            verSolicitudes();
            aceptarSolicitudes();

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
        int idNuevoMensaje;
        char mensaje[100];
        printf("1.- Enviar\n");
        printf("2.- Conversaciones\n");
        printf("3.- Volver\n");
        scanf("%d", &resp);
        if(resp == 1)
        {
            system("cls");
        	printf(ANSI_COLOR_CYAN     "-- Enviar Mensaje --"     ANSI_COLOR_RESET "\n");
        	printf("idUnico de usuario a mensajear: ");
    		scanf("%d", &idNuevoMensaje);
    		printf("Mensaje: ");
    		fflush(stdin);
    		gets(mensaje);
    		fflush(stdin);
    		printf("\n");
            enviarMensaje(idNuevoMensaje, mensaje);
            crearNotificacion(current_user_id,"mensaje",idNuevoMensaje);
        }
        else if(resp == 2)
        {
            system("cls");
        	printf(ANSI_COLOR_CYAN     "-- Conversaciones --"     ANSI_COLOR_RESET "\n");
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
    system("cls");
    printf(ANSI_COLOR_CYAN     "-- Notificaciones --"     ANSI_COLOR_RESET "\n");
    verNotificaciones();
}
void cerrarsesion()
{
    current_user_name[20] = NULL;
    current_user_id = NULL;
}

/* --------------------------------------- SUBFUNCIONES ----------------------------------------------- */

void anadirContacto()
{
    system("cls");
    int idNuevoAmigo;
    int existe;
    int confirm;
    printf(ANSI_COLOR_CYAN     "-- Agregar contacto --"     ANSI_COLOR_RESET "\n");
    printf("idUnico de usuario a agregar: ");
    scanf("%d", &idNuevoAmigo);
    if(idNuevoAmigo == current_user_id)
    {
        printf(ANSI_COLOR_RED "No te puedes agregar a ti mismo" ANSI_COLOR_RESET "\n");
        getch();
        return;
    }
    existe = verificarExistenciaDelContacto(idNuevoAmigo);
    if(existe == 1)
    {
        system("cls");
        int repetida;
        if (validarSolicitudRepetida(idNuevoAmigo) == 0)
        {
            printf(ANSI_COLOR_CYAN     "-- Agregar contacto --"     ANSI_COLOR_RESET "\n");
            printf(ANSI_COLOR_RED "Ya se envio solicitud a este contacto" ANSI_COLOR_RESET "\n");
            getch();
            return;
        };
        printf(ANSI_COLOR_CYAN     "-- Confirmar --"     ANSI_COLOR_RESET "\n");
        verInformacionDelContacto(idNuevoAmigo);
        printf("\n");
        printf(ANSI_COLOR_MAGENTA "Enviar solicitud a este contacto?" ANSI_COLOR_RESET "\n");
        printf("1.- Si, enviar\n");
        printf("2.- Cancelar\n");
        scanf("%d", &confirm);
        if(confirm == 1)
        {
            enviarSolicitud(idNuevoAmigo);
            crearNotificacion(current_user_id,"solicitud",idNuevoAmigo);
        }
    }
    else
    {
        printf(ANSI_COLOR_RED "No existe el contacto" ANSI_COLOR_RESET "\n");
        system("pause");
    }
}
void verSolicitudes()
{
    struct solicitudes *t;
    t = start_solicitudes;

    if (t == NULL)
    {
        printf(ANSI_COLOR_RED "No hay solicitudes aun" ANSI_COLOR_RESET "\n");
        getch();
        return;
    }

    printf(" -- ENVIADAS -- \n");
    while(t->next != NULL)
    {
        if(t->idCurrentUser == current_user_id)
        {
            imprimirSolicitud(t->idContact);
        }
        t = t->next;
    }
    printf("\n -- RECIBIDAS -- \n");
    t = start_solicitudes;
    while(t->next != NULL)
    {
        if(t->idContact == current_user_id)
        {
            imprimirSolicitud(t->idCurrentUser);
        }
        t = t->next;
    }
    getch();
}
void verConversaciones()
{
    struct mensajes *m;
	m = start_mensajes;

	if(m == NULL)
	{
		printf(ANSI_COLOR_RED "No hay mensajes aun" ANSI_COLOR_RESET "\n");
        getch();
        return;
	}

	imprimirMensaje();
	getch();
}
void enviarMensaje(int idNuevoMensaje, char mensaje[100])
{
    struct mensajes *m;
	m = ( struct mensajes*)malloc(sizeof(struct mensajes));

	if ( start_mensajes == NULL)
	{
		start_mensajes = m;
		start_mensajes->idContact = 000;
		start_mensajes->idCurrentUser = current_user_id;
		start_mensajes->next = NULL;
		enviarMensaje(idNuevoMensaje, mensaje);
		return;
	}
	m->idContact = idNuevoMensaje;
	m->idCurrentUser = current_user_id;
	strcpy(m->mensaje,mensaje);
	m->next = start_mensajes;
	start_mensajes = m;

	printf(ANSI_COLOR_GREEN "Mensaje Enviado" ANSI_COLOR_RESET "\n");
    getch();
}

int verificarExistenciaDelContacto(int IDusr)
{
    int existe = 1, no_existe = 0;

    struct node *t;
    t = start;
    while(t->next != NULL)
    {
        if(t->idUsuario == IDusr)
        {
            return existe;
        }
        t = t->next;
    }
    return no_existe;
}

void enviarSolicitud(int idNuevoAmigo)
{
    struct solicitudes *s;

    s = (struct solicitudes*)malloc(sizeof(struct solicitudes));

    if (start_solicitudes == NULL)
    {
        start_solicitudes = s;
        start_solicitudes->idContact = 000;
        start_solicitudes->idCurrentUser = current_user_id;
        start_solicitudes->next = NULL;
        enviarSolicitud(idNuevoAmigo);
        return;
    }
    s->idContact = idNuevoAmigo;
    s->idCurrentUser = current_user_id;
    s->next = start_solicitudes;
    start_solicitudes = s;

    printf(ANSI_COLOR_GREEN "Solicitud enviada exitosamente" ANSI_COLOR_RESET "\n");
    getch();
}

void verInformacionDelContacto(int IDusr)
{
    struct node *t;
    t = start;
    while(t->next != NULL)
    {
        if(t->idUsuario == IDusr)
        {
            printf("ID de usuario: %d\n", t->idUsuario);
            printf("Nombre: %s\n", t->nombre);
            printf("ID de trabajador: %d\n", t->idTrabajador);
        }
        t = t->next;
    }
}

void imprimirSolicitud(int idContact)
{
    struct node *t;
    t = start;

    while(t->next != NULL)
    {
        if(t->idUsuario == idContact)
        {
            printf("\n");
            printf("%d \t %s \t", t->idUsuario, t->nombre);
            printf(ANSI_COLOR_YELLOW "Pendiente" ANSI_COLOR_RESET);
        }
        t = t->next;
    }
}

void imprimirNombre(int IDusr)
{
    struct node *t;
    t = start;

    while(t->next != NULL)
    {
        if(t->idUsuario == IDusr)
        {
            printf("%s", t->nombre);
        }
        t = t->next;
    }
}

void crearNotificacion(int idUserReminder, char kind[],int idUserReceiver)
{
    struct notificaciones *t;

    t = (struct notificaciones*)malloc(sizeof(struct notificaciones));

    if (start_notificaciones == NULL)
    {
        start_notificaciones = t;
        start_notificaciones->next = NULL;
        crearNotificacion(idUserReminder,kind,idUserReceiver);
        return;
    }
    t->idUserReceiver = idUserReceiver;
    t->idUserReminder = idUserReminder;
    strcpy(t->kind,kind);
    t->next = start_notificaciones;
    start_notificaciones = t;
}

void verNotificaciones()
{
    struct notificaciones *t;
    t = start_notificaciones;

    if (t == NULL)
    {
        printf(ANSI_COLOR_RED "No hay notificaciones aun" ANSI_COLOR_RESET "\n");
        getch();
        return;
    }

    while(t->next != NULL)
    {
        if(t->idUserReceiver == current_user_id)
        {
            if(strcmp(t->kind,"mensaje") == 0)
            {
                printf("\n");
                printf("Tienes un nuevo mensaje de ");
                imprimirNombre(t->idUserReminder);
                printf("\n");
            }
            else if(strcmp(t->kind,"solicitud") == 0)
            {
                printf("Tienes una nueva solicitud de ");
                imprimirNombre(t->idUserReminder);
                printf("\n");
            }
        }

        t = t->next;
    }
    getch();
}

void cantidadDeNotificaciones()
{
    struct notificaciones *t;
    t = start_notificaciones;
    int contador = 0;
    if (t == NULL)
    {
        printf("%d",contador);
        return;
    }
    while(t->next != NULL)
    {
        if(t->idUserReceiver == current_user_id)
        {
            contador++;
        }

        t = t->next;
    }
    printf("%d",contador);
}

void aceptarSolicitudes()
{
    printf("\nQuieres aceptar una solicitud?\n1.- Si\n2.- No");
    int aceptar = 0;
    int idNuevoAmigo = 0;
    printf("\n");
    scanf("%d",&aceptar);
    if(aceptar == 1)
    {
        printf("Introduce el id del usuario que quieres aceptar: ");
        scanf("%d",&idNuevoAmigo);
        if(verificarExistenciaDelContacto(idNuevoAmigo) == 1)
        {
            agregarAContactos(idNuevoAmigo);
        }
        else
        {
            printf(ANSI_COLOR_RED "No existe el contacto" ANSI_COLOR_RESET "\n");
        }

    }
}

void agregarAContactos(int idNuevoAmigo)
{
    struct contactos *c;
    c = (struct contactos*)malloc(sizeof(struct contactos));
    if (start_contactos == NULL)
    {
        start_contactos = c;
        start_contactos->idUser2 = 000;
        start_contactos->idUser1 = 000;
        start_contactos->next = NULL;
        agregarAContactos(idNuevoAmigo);

        return;
    }
    c->idUser2 = idNuevoAmigo;
    c->idUser1 = current_user_id;
    c->next = start_contactos;
    start_contactos = c;
    printf(ANSI_COLOR_GREEN "Amigo anadido" ANSI_COLOR_RESET "\n");
    getch();
}

int validarSolicitudRepetida(int idNuevoAmigo)
{
    struct solicitudes *t;
    t = start_solicitudes;
    int repetido = 0;
    int no_repetido = 1;

    if(t == NULL)
    {
        return no_repetido;
    }

    while(t->next != NULL)
    {
        if(t->idCurrentUser == current_user_id && t->idContact == idNuevoAmigo )
        {
            return repetido;
        }
        t = t->next;
    }
    return no_repetido;
}

void verContactos()
{
    struct contactos *t;
    t = start_contactos;

    if (t == NULL)
    {
        printf(ANSI_COLOR_RED "No hay contactos aun" ANSI_COLOR_RESET "\n");
        getch();
        return;
    }

    while(t->next != NULL)
    {
        if(t->idUser1 == current_user_id)
        {
            printf("Contacto: ");
            imprimirNombre(t->idUser2);
            printf("\n");
        }
        if(t->idUser2 == current_user_id)
        {
            printf("Contacto: ");
            imprimirNombre(t->idUser1);
            printf("\n");
        }

        t = t->next;
    }
    getch();
}
void imprimirMensaje()
{
	struct mensajes *m;
	m = start_mensajes;

	while(m->next != NULL)
	{
		if(m->idContact == current_user_id || m->idCurrentUser == current_user_id )
		{
			printf("\n");
			printf("%d\t", m->idContact); imprimirNombre(m->idContact); printf("\t%s",m->mensaje);
		}
		m = m->next;
	}
}
