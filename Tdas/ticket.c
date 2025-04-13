#include "list.h" 
#include "extra.h"
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

void mostrarMenuPrincipal() {
    limpiarPantalla();
    puts("========================================");
    puts("Sistema de gestión de Tickets de soporte técnico");
    puts("========================================");
  
    puts("1) Registrar Ticket");
    puts("2) Asignar prioridad a Ticket");
    puts("3) Mostrar lista de espera");
    puts("4) Atender al siguiente Ticket");
    puts("5) Buscar Ticket por ID y mostrar detalles");
    puts("6) Salir");
  }
  
typedef struct 
{
int id; //Identifcador unico del ticket
char detalle[1000]; //Detalle del ticket
int hora; //hora en formato 24 horas, 1600 = 16:00
int prioridad; // 1 == ALTA / 2 == MEDIA / 3 == BAJA //
}Ticket;

// Asigna la hora actual en formato 24 horas (Ejemplo: 1230 para 12:30)
int asignarHoraActual()//pero lo asigna en entero
{             
    time_t ahora = time(NULL);
    struct tm *tiempo = localtime(&ahora);
    return tiempo->tm_hour * 100 + tiempo->tm_min; 
}

int leerEntero(const char *texto) 
{
    int numero;
    char c;

    while (1) {
        printf("%s", texto);

        // Intenta leer un entero seguido de un carácter
        if (scanf("%d%c", &numero, &c) != 2 || c != '\n') {
            printf("Entrada inválida. Intente de nuevo.\n");

            // Limpia el buffer si la entrada es incorrecta
            while ((c = getchar()) != '\n' && c != EOF);
        } else {
            return numero; // Entrada válida
        }
    }
}

bool idExisteEnListas(List *listaBaja, List *listaMedia, List *listaAlta, int idBuscar) 
{
    Ticket *actual;

    //Primero reviza la lista baja
    actual = list_first(listaBaja);
    while (actual != NULL) {
        if (actual->id == idBuscar) return true;
        actual = list_next(listaBaja);
    }

    //Si no existe en baja, reviza en lista media
    actual = list_first(listaMedia);
    while (actual != NULL) {
        if (actual->id == idBuscar) return true;
        actual = list_next(listaMedia);
    }

    //Si no está en niguna de las 2 anteriores, reviza en la lista alta
    actual = list_first(listaAlta);
    while (actual != NULL) {
        if (actual->id == idBuscar) return true;
        actual = list_next(listaAlta);
    }

    return false; //significa que despues de buscar, no está en niguna lista
}

void registrar_ticket(List * listaTickets, List * listaTicketMedia, List *listaTicketAlta) 
{
    printf("Registrar nuevo ticket\n");
    //El ticket en sí es un nodo :OOOOOOO
    Ticket *punteroTicket = malloc(sizeof(Ticket)); //reservo memoria para el puntero 
    if(punteroTicket == NULL)
    {
        printf("No se pudo reservar memoria\n");
        return;
    }

    // Pide un ID unico para el ticket
    while (true) {
        punteroTicket->id = leerEntero("Ingrese su ID: ");

        // Verificar que el ID no exista en ninguna lista
        if (idExisteEnListas(listaTickets, listaTicketMedia, listaTicketAlta, punteroTicket->id)) {
            printf("Ese ID ya existe. Intente con otro.\n");
        } else {
            break;
        }
    }
    getchar();// Limpia el buffer después de leer el ID
    printf("Ingrese el detalle del problema \n");
    fgets(punteroTicket->detalle, sizeof(punteroTicket->detalle), stdin); 

   // Asignar la hora actual del sistema al ticket
    punteroTicket->hora = asignarHoraActual();
    punteroTicket->prioridad = 3; //Se inicializa la prioridad baja, osea en 3;

    //Finalmente se añade el ticket a la lista de tickets
    list_pushBack(listaTickets, punteroTicket); 
    printf("Listo, solicitud realizada :D\n");
}

void mostrarTicket(Ticket *actual)
{
    if (actual == NULL) return;

    //Descompone el numero de la hora en horas y minutos;
    //Ejemplo 1230
    int horas = actual->hora / 100; //12
    int minutos = actual->hora % 100; //30
    
     // Mostrar la información del ticket
    printf("\nID: %-4d   Hora: %02d:%02d   Prioridad: ", actual->id, horas, minutos);
    if(actual->prioridad == 1)
    printf("ALTA\n");
    else{
    if(actual->prioridad == 2)
        printf("MEDIA\n");
    else printf("BAJA\n");
    }

    printf("Detalle: %s\n", actual->detalle);
    printf("===========================================================\n");
}

void mostrar_tickets(List *listaAMostrar)
{
    Ticket * actual = list_first(listaAMostrar);

    //Muestra los ticket de una lista hasta que el actual sea nulo
    //En caso de no haber elementos en la lista, simplemnte no entra el bucle y termina
    while (actual != NULL)
    {
        mostrarTicket(actual);
        actual = list_next(listaAMostrar);
    }
}

void mostrar_listas_Tickets(List * listaBaja, List * listaMedia, List * listaAlta) {
    printf("================================\n");
    printf("Lista tickets en espera: \n");
    printf("================================\n");

    //Vereificamos si quedan elementos en las listas//
    if((list_first(listaAlta) == NULL) && (list_first(listaMedia) == NULL) && (list_first(listaBaja) == NULL))
    {
        printf("No quedan tickets en la lista\n");
        return;
    }

    //Muestra todos los tickets de la lista ordenados de Prioridad Alta hacia Baja
    mostrar_tickets(listaAlta);
    mostrar_tickets(listaMedia);
    mostrar_tickets(listaBaja);
}

void insersionOrdenada(List *listaOrigen, List *listaNueva, int idBuscar, int cambiarPrioridad) 
{
    Ticket *actual = list_first(listaOrigen);
    while(actual != NULL)
    {
        if(actual->id == idBuscar)
        {
            Ticket * aMover = list_popCurrent(listaOrigen);
            aMover->prioridad = cambiarPrioridad;

            //Si está vacia se agrega de inmediato al final
            if(list_first(listaNueva) == NULL)
            {
                list_pushBack(listaNueva, aMover);
                return;
            }

            //Si hay más elementos, vemos donde insertarlo segun la hora 
            Ticket * actualListaNueva = list_first(listaNueva);
            Ticket * anteriorListaNueva = NULL;

            //Lo recorremos hasta ver donde abría que insertarlo
            while(actualListaNueva != NULL && aMover->hora >= actualListaNueva->hora)
            {
                anteriorListaNueva = actualListaNueva;
                actualListaNueva = list_next(listaNueva);
            }

            if(anteriorListaNueva == NULL) //Significa que el aMover es el que llego más temprano
            {
                list_pushFront(listaNueva, aMover);
            }
            else
            {
                //Si el aMover no fue el más temprano, se inserta despues de anteriorListaNueva,
                //que fue el que llego antes, osea inserta el ticket justo después del que llegó antes
                Ticket *temp = list_first(listaNueva);
                while(temp != anteriorListaNueva && temp != NULL)
                {
                temp = list_next(listaNueva);
                }
                list_pushCurrent(listaNueva, aMover);
            }
            return;
        }

        actual = list_next(listaOrigen);
    }

}

void mostrarIdDisponibles(List * listaOrigen)
{
    Ticket * actual = list_first(listaOrigen);
    printf("Tickets disponibles :\n");
    //Recorre la lista en busca de los ID y los muestra
    while(actual != NULL)
    {
        printf("[%i]", actual->id);
        actual = list_next(listaOrigen);
    }
    printf("\n");
}

void asignarPrioridad(List *listaOrigen, List *listaMedia, List *listaAlta)
{
    int idBuscar;
    int eleccionPrioridad;
    Ticket *actual = list_first(listaOrigen);
    if(actual == NULL)
    {
        printf("No quedan ticket disponibles para asignar prioridad\n");
        return;
    }

    //Muestra los ID disponibles para luego escojer a cual asignarle una nueva prioridad
    mostrarIdDisponibles(listaOrigen);
    idBuscar = leerEntero("Ingrese el ID del ticket a asignar prioridad:\n");
    actual = list_first(listaOrigen); // "Reinciamos" el actual

    //Busca el ticket ingresado en la lista
    while (actual != NULL)
    {
        if(actual->id == idBuscar)
        {
        printf("Descripcion del problema :\n%s\n", actual->detalle);
        printf("Que prioridad le asignara?\n|| 1 == ALTA || 2 == MEDIA || 3 == BAJA ||\n");
        scanf("%i", &eleccionPrioridad);
        switch (eleccionPrioridad)
        {
        case 1:
            //El ticket ahora pasa a la lista alta con esa prioridad
            insersionOrdenada(listaOrigen, listaAlta, idBuscar, eleccionPrioridad); //Funcion para insertar y ordenar por orden de llegada//
            return;

        case 2:
            //El ticket ahora pasa a la lista media con esa prioridad
            insersionOrdenada(listaOrigen, listaMedia, idBuscar, eleccionPrioridad);
            return;

        case 3:
            //Aqui no hacemos nada, ya que la primera lista es en si la de prioridad baja
            return;
        default:
            printf("Opcion ingresada no valida\n");
            return;
            //break;
        }

        }
        actual = list_next(listaOrigen);
    }

    printf("No se encontro ningun ticket con ese ID.\n");
}

void atender_siguiente_ticket(List * listaBaja, List * listaMedia, List * listaAlta)
{
    Ticket * actual = list_first(listaAlta);
    if(actual == NULL) //Significa que no quedan tickets en la alta
    {
        actual = list_first(listaMedia);
        if(actual == NULL) //No quedan tickets en la media
        {
        actual = list_first(listaBaja);
        if(actual == NULL)//No quedan tickets en ninguna lista
        {
            printf("Ya no quedan tickets por atender\n");
            return;
        }
        else
        {
            printf("Se atendió el ticket:\n");
            printf("===========================================================\n");
            mostrarTicket(actual);
            list_popFront(listaBaja);
        }
        }
        else
        {
            printf("Se atendió el ticket:\n");
            printf("===========================================================\n");
            mostrarTicket(actual);
            list_popFront(listaMedia);
        }
    }
    else
    { 
        printf("Se atendió el ticket:\n");
        printf("===========================================================\n");
        mostrarTicket(actual);
        list_popFront(listaAlta);
    }
}

void buscarMostrarTicket(List * lista, int idBuscar, bool *esta)
{
    Ticket * actual = list_first(lista);
    if(actual == NULL)//Lista vacia
    { 
        return; //Nada que hacer
    }

    //Busca el ticket con el ID a Buscar
    while (actual != NULL)
    {
        if(actual->id == idBuscar) //Si lo encuntra
        {
            mostrarTicket(actual); //Lo muestra
            (*esta) = true; //Actualiza el esta
            return; 
        }
        actual = list_next(lista);
    }
}

void buscarMostrarTicketSiExiste(List *listaBaja, List *listaMedia, List *listaAlta)
{
    int idBuscar;

    if( (list_first(listaBaja) == NULL) && (list_first(listaMedia) == NULL) && (list_first(listaAlta) == NULL) )
    {
        printf("No quedan ticket disponibles para buscar\n");
        return;
    }

    idBuscar = leerEntero("¿Qué ID desea revisar?\n");
    bool estaba = false; //Parte en no esta

    printf("===========================================================\n");
    //Busca en cada lista y se ve si estaba o no
    buscarMostrarTicket(listaAlta, idBuscar, &estaba);
    if(estaba) return; //Si estaba en la lista (estaba == true), se sale del programa, si no, sigue

    buscarMostrarTicket(listaMedia, idBuscar, &estaba);
    if(estaba) return;//Si estaba en la lista (estaba == true), se sale del programa, si no, sigue

    buscarMostrarTicket(listaBaja, idBuscar, &estaba);
    if(estaba) return;//Si estaba en la lista (estaba == true), se sale del programa, si no, sigue

    printf("Error, el ID buscado no se encuentra en la lista\n");
}