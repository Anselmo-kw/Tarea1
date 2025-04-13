#include "Tdas/ticket.h"
#include "Tdas/extra.h"
#include "Tdas/list.h"
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main() 
{
    char opcion;
    List * listaTickets = list_create();
    List * listaTicketMedia = list_create();
    List * listaTicketAlta = list_create();
  
    do {
      mostrarMenuPrincipal();
      printf("Ingrese su opción: ");
      scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                             // newline anterior
      getchar();
      switch (opcion) {
      case '1':
        registrar_ticket(listaTickets, listaTicketMedia, listaTicketAlta);
        break;
      case '2':
        asignarPrioridad(listaTickets, listaTicketMedia, listaTicketAlta);
        break;
      case '3':
        mostrar_listas_Tickets(listaTickets, listaTicketMedia, listaTicketAlta);
        break;
      case '4':
        // Lógica para atender al siguiente ticket
        atender_siguiente_ticket(listaTickets, listaTicketMedia, listaTicketAlta);
        break;
      case '5':
        // Buscar ticket por ID y mostrar detalles (ID)
        buscarMostrarTicketSiExiste(listaTickets, listaTicketMedia, listaTicketAlta);
        break;
      case '6':
        puts("Saliendo del sistema de gestión de Tickets...");
        break;
      default:
        puts("Opción no válida. Por favor, intente de nuevo.");
      }
      presioneTeclaParaContinuar();
  
    } while (opcion != '6' );
  
    // Liberar recursos, si es necesario
    list_clean(listaTickets);
    list_clean(listaTicketMedia);
    list_clean(listaTicketAlta);
    return 0;
}
  