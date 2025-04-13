#ifndef TICKET_H
#define TICKET_H
#include "list.h"
#include <stdbool.h>

typedef struct ticket ticket;  // Declaración adelantada del tipo

// Muestra el menú principal
void mostrarMenuPrincipal();

// Función para obtener la hora del sistema como int (ej: 1230 para 12:30)
int asignarHoraActual();

// Solicita al usuario un número entero validado desde consola
int leerEntero(const char *texto);

// Verifica si un ID ya existe en alguna de las tres listas de tickets
bool idExisteEnListas(List *listaBaja, List *listaMedia, List *listaAlta, int idBuscar);

// Registrar un nuevo ticket
void registrar_ticket(List * listaTickets, List * listaTicketMedia, List *listaTicketAlta);

// Mostrar un ticket individual
void mostrarTicket(ticket *actual);

// Mostrar todos los tickets en una lista
void mostrar_tickets(List *listaAMostrar);

// Mostrar listas según prioridad
void mostrar_listas_Tickets(List *listaBaja, List *listaMedia, List *listaAlta);

// Inserta un ticket ordenado por hora
void insersionOrdenada(List *listaOrigen, List *listaNueva, int idBuscar, int cambiarPrioridad);

// Asigna prioridad a un ticket
void asignarPrioridad(List *listaOrigen, List *media, List *alta);

// Atender siguiente ticket
void atender_siguiente_ticket(List *listaBaja, List *listaMedia, List *listaAlta);

// Busca y muestra un ticket por ID dentro de una lista. Marca si fue encontrado.
void buscarMostrarTicket(List *lista, int idBuscar, bool *esta);

// Busca el ticket en todas las listas y lo muestra si existe.
void buscarMostrarTicketSiExiste(List *listaBaja, List *listaMedia, List *listaAlta);


#endif
