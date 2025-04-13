# Sistema de Gestión de Tickets de Soporte Técnico

Este programa fue desarrollado como parte de un trabajo para la asignatura **Estructura de Datos**. Aunque el escenario es ficticio —una empresa que gestiona solicitudes de soporte técnico—, su objetivo es demostrar el uso de **listas enlazadas** y la organización eficiente de información con distintos niveles de prioridad.

---

## Descripción

El sistema permite registrar, visualizar y atender tickets de soporte técnico. Cada ticket contiene:

- Un **ID único**
- Una **descripción del problema**
- Un **nivel de prioridad**: Bajo, Medio o Alto
- La **hora de registro**

Los tickets se almacenan en una única lista enlazada ordenada primero por **prioridad** (de mayor a menor) y, en caso de empate, por la **hora de ingreso**. Esto garantiza que los casos más urgentes se atiendan primero.

---

## Cómo compilar y ejecutar

### Requisitos

- Tener instalado **Visual Studio Code**, junto con la extensión **C/C++** de Microsoft.
- Tener un compilador de C como **GCC**. En Windows se recomienda usar **MinGW**.

### Pasos para compilar y ejecutar

1. Descargar el archivo `.zip` del proyecto (por ejemplo, `TAREA1.zip`).
2. Descomprimir el contenido en una carpeta local (se creará una carpeta llamada `TAREA1` con todos los archivos).
3. Abrir la carpeta `TAREA1` en **Visual Studio Code**.
4. Abrir un terminal dentro del editor (recomendado: **Git Bash** si estás en Windows).
5. Compilar el proyecto ejecutando el siguiente comando dentro del terminal:
```gcc main.c Tdas/ticket.c Tdas/list.c Tdas/extra.c -o programa.exe```
6. Ejecutar el programa con el comando : ```./programa```

## Comportamiento de las funcionalidades

A continuación se detallan las funcionalidades implementadas, indicando cuáles funcionan correctamente y cuáles pueden presentar fallos, junto con sus posibles causas:

- **Registro de nuevo ticket:**  
  Funciona correctamente. Se solicita al usuario el **ID** (único) y una **descripción del problema**. El sistema asigna automáticamente la **hora actual** y una **prioridad por defecto de 3 (Baja)**. La descripción se limita internamente a los primeros 1000 caracteres.  

  **Notas importantes:**  
  - El usuario **no ingresa la prioridad manualmente** durante el registro. Todos los tickets se registran inicialmente con prioridad **Baja (3)**.
  - La prioridad **solo se puede cambiar si el ticket está en la lista original** (la lista de prioridad Baja). Una vez que el ticket se mueve a la lista de prioridad Media o Alta, **ya no puede volver a cambiarse**. Por esta razón, en la práctica, **solo se puede modificar la prioridad de un ticket una vez**.
  - Si el usuario ingresa un valor incorrecto o más de un número al ingresar el **ID** (por ejemplo, `123 5`), el sistema puede interpretar mal la entrada (por ejemplo, usar `5` como ID final) y **saltarse el ingreso de la descripción**. Esto ocurre por el manejo inadecuado del búfer de entrada (`stdin`) y puede generar tickets incompletos o con datos erróneos.

  Se recomienda ingresar los datos cuidadosamente, usando un único número por campo, y evitando escribir varios valores en una sola línea.

- **Asignación de prioridad:**  
  Funciona correctamente. Los tickets de la **lista original (prioridad Baja)** se reordenan y redistribuyen en las listas correspondientes según su nueva prioridad.  
  Una vez que un ticket ha sido movido a una lista de prioridad Media o Alta, **no puede volver a ser reasignado**, lo que significa que **la prioridad solo puede cambiarse una vez por ticket**.

- **Visualización de tickets:**  
  Funciona correctamente. Muestra los tickets separados en listas por prioridad (Alta, Media y Baja), respetando el orden de llegada dentro de cada nivel.

- **Atención del siguiente ticket:**  
  Funciona correctamente. Atiende siempre el ticket más urgente disponible (prioridad Alta > Media > Baja), tomando en cuenta el orden de ingreso dentro de cada lista.

- **Búsqueda de ticket por ID:**  
  Funciona correctamente. Recorre todas las listas (Baja, Media y Alta) y muestra la información del ticket correspondiente si existe.

- **Validación de entradas numéricas:**  
  Funciona parcialmente. Aunque se controla que ciertos datos como ID y hora sean numéricos, **no se limita adecuadamente el rango ni la cantidad de dígitos**. Esto puede llevar a interpretaciones incorrectas, como tomar solo el primer dígito de una entrada larga.  
  Además, si se ingresan letras o símbolos, es posible que el sistema falle o se comporte de manera inesperada.

- **Manejo de errores por ingreso incorrecto:**  
  Funciona parcialmente. El sistema detecta algunas entradas no válidas, pero no siempre ofrece retroalimentación clara. En algunos casos, como en la selección del menú o en campos numéricos, puede aceptar entradas inválidas sin advertir al usuario, o incluso saltar pasos del flujo.

- **Longitud de la descripción:**  
  Funciona parcialmente. La descripción del problema está limitada internamente a 1000 caracteres, pero no se le informa al usuario que su texto será recortado si excede ese límite.

---

## Ejemplo de uso

A continuación se muestra un ejemplo de cómo el usuario interactúa con el programa al ejecutarlo:

# ====== MENÚ PRINCIPAL ======

1. Registrar nuevo ticket  
2. Mostrar lista de tickets  
3. Atender siguiente ticket  
4. Buscar ticket por ID  
5. Salir  

============================

**Seleccione una opción:** `1`  
**Ingrese ID del ticket:** `101`  
**Ingrese descripción del problema:** `No funciona el mouse`  
**Ingrese prioridad (1 = Baja, 2 = Media, 3 = Alta):** `2`  
**Ingrese hora de registro (en formato HHMM):** `1430`

**Ticket registrado exitosamente.**

## Estructura del Proyecto

El proyecto está organizado de la siguiente manera:

- `main.c`: Función principal que controla el flujo del programa.
- `Tdas/ticket.c`: Funciones para gestionar los tickets.
- `Tdas/list.c`: Implementación de listas enlazadas.
- `Tdas/extra.c`: Funciones auxiliares de utilidad.
- `Tdas/ticket.h`, `Tdas/list.h`, `Tdas/extra.h`: Archivos de cabecera asociados.

---

## Funcionalidades principales

El sistema tiene varias funcionalidades clave que permiten gestionar los tickets:

- **Registro de nuevos tickets**: Permite ingresar un ticket con su ID único, descripción del problema, prioridad y hora de ingreso.
- **Asignación de prioridad**: Los tickets son asignados a una prioridad (Baja, Media, Alta) de acuerdo con su nivel de urgencia.
- **Visualización de tickets**: Muestra todos los tickets registrados, organizados por prioridad y hora de registro.
- **Atención de tickets**: Permite atender tickets en orden de urgencia, comenzando por los de mayor prioridad.
- **Búsqueda de tickets**: Permite buscar y mostrar un ticket por su ID.
- **Validación de entradas numéricas**: Se asegura de que los valores ingresados por el usuario sean válidos (por ejemplo, para el ID o la prioridad).