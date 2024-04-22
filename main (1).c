#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"
#include <time.h>
#define MAX_SIZE 100

const int CHILE_TIME_OFFSET = -4;
int n = 1;

typedef struct
{
  int Npaciente;
  char nombre[MAX_SIZE];
  char apellido[MAX_SIZE];
  int edad;
  char sintoma[MAX_SIZE];
  char prioridad[MAX_SIZE];
  int hora;
  int minuto;
  int segundo;
}Paciente;

// Función para limpiar la pantalla
void limpiarPantalla() { system("clear"); }

void presioneTeclaParaContinuar() {
  puts("Presione una tecla para continuar...");
  getchar(); // Consume el '\n' del buffer de entrada
  getchar(); // Espera a que el usuario presione una tecla
}

// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Gestión Hospitalaria");
  puts("========================================");

  puts("1) Registrar paciente");
  puts("2) Asignar prioridad a paciente");
  puts("3) Mostrar lista de espera");
  puts("4) Atender al siguiente paciente");
  puts("5) Mostrar pacientes por prioridad");
  puts("6) Salir");
}

void registrar_paciente(List *pacientes) 
{
  Paciente *paciente = malloc(sizeof(Paciente));
  if (paciente == NULL) {
      printf("Error: No se pudo asignar memoria para el paciente.\n");
      return;
  }
  paciente->Npaciente = n;
  printf("Registrar nuevo paciente\n\n");
  printf("Nombre: ");
  scanf("%s", paciente->nombre);
  printf("Apellido: ");
  scanf("%s", paciente->apellido);
  printf("Edad: ");
  scanf("%d", &paciente->edad);
  printf("Sintoma: ");
  scanf("%s", paciente->sintoma);
  time_t current_time = time(NULL);
  struct tm* local_time = localtime(&current_time);
  local_time->tm_hour += CHILE_TIME_OFFSET;
  mktime(local_time);

  paciente->hora =local_time->tm_hour;
  paciente->minuto =local_time->tm_min;
  paciente->segundo =local_time->tm_sec;
  puts("Hora de ingreso del paciente: ");
  printf("%02d:%02d:%02d\n", paciente->hora, paciente->minuto, paciente->segundo);
  strcpy(paciente->prioridad,"BAJA");
  list_pushBack(pacientes, paciente);
  n++;
}

void imprimirPaciente(Paciente *paciente)
{
  printf("Nombre: %s %s\n", paciente->nombre, paciente->apellido);
  printf("Edad: %d\n", paciente->edad);
  printf("Síntoma: %s\n", paciente->sintoma);
  printf("Prioridad: %s\n", paciente->prioridad);
  printf("Hora de llegada: %02d:%02d:%02d\n\n", paciente->hora, paciente->minuto, paciente->segundo);
}

void mostrar_lista_pacientes(List *pacientes) {
  // Mostrar pacientes en la cola de espera
  printf("Pacientes en espera: \n\n");
  Paciente *pacienteActual = (Paciente *)list_first(pacientes);
  size_t i = 1;
  while(pacienteActual != NULL)
    {
      printf("Paciente %zu:\n", i);
      imprimirPaciente(pacienteActual);
      pacienteActual = (Paciente *)list_next(pacientes);
      i++;
    }
}

void mostrarNombres(List *pacientes)
{
  Paciente *pacienteActual = (Paciente *)list_first(pacientes);
  int i = 1;
  while(pacienteActual != NULL)
    {
      printf("%d) %s = %s\n", i, pacienteActual->nombre, pacienteActual->prioridad);
      pacienteActual = (Paciente *)list_next(pacientes);
      i++;
    }
}

void ordenarListasPorNumero(List *lista) {
    Paciente *Arreglo[MAX_SIZE];
    Paciente *pacienteActual = (Paciente *)list_first(lista);
    int i = 0;
    while (pacienteActual != NULL) {
        Arreglo[i] = pacienteActual;
        pacienteActual = (Paciente *)list_next(lista);
        i++;
    }
    for (int j = 0; j < i; j++) {
        for (int k = 0; k < i - j - 1; k++) {
            if (Arreglo[k]->Npaciente > Arreglo[k + 1]->Npaciente) {
                Paciente *temp = Arreglo[k];
                Arreglo[k] = Arreglo[k + 1];
                Arreglo[k + 1] = temp;
            }
        }
    }
    list_clean(lista);
    for (int j = 0; j < i; j++) {
        list_pushBack(lista, Arreglo[j]); // Corregido, no es necesario el operador &
    }
}

void OrdenarPrioridad(List *pacientes) {
    List *listaALTA = list_create();
    List *listaMEDIA = list_create();
    List *listaBAJA = list_create();

    Paciente *pacienteActual = (Paciente *)list_first(pacientes);
    while (pacienteActual != NULL) {
        if (strcmp(pacienteActual->prioridad, "ALTA") == 0)
            list_pushBack(listaALTA, pacienteActual);
        else if (strcmp(pacienteActual->prioridad, "MEDIA") == 0)
            list_pushBack(listaMEDIA, pacienteActual);
        else if (strcmp(pacienteActual->prioridad, "BAJA") == 0)
            list_pushBack(listaBAJA, pacienteActual);

        pacienteActual = (Paciente *)list_next(pacientes);
    }

    list_clean(pacientes);
    ordenarListasPorNumero(listaALTA);
    ordenarListasPorNumero(listaMEDIA);
    ordenarListasPorNumero(listaBAJA);

    pacienteActual = (Paciente *)list_first(listaALTA);
    while (pacienteActual != NULL) {
        list_pushBack(pacientes, pacienteActual);
        pacienteActual = (Paciente *)list_next(listaALTA);
    }

    pacienteActual = (Paciente *)list_first(listaMEDIA);
    while (pacienteActual != NULL) {
        list_pushBack(pacientes, pacienteActual);
        pacienteActual = (Paciente *)list_next(listaMEDIA);
    }

    pacienteActual = (Paciente *)list_first(listaBAJA);
    while (pacienteActual != NULL) {
        list_pushBack(pacientes, pacienteActual);
        pacienteActual = (Paciente *)list_next(listaBAJA);
    }

    list_clean(listaALTA);
    list_clean(listaMEDIA);
    list_clean(listaBAJA);
}

void asignar_prioridad(List *pacientes) {
    char nombre[MAX_SIZE];
    printf("Ingrese el nombre del paciente a asignar prioridad: \n");
    mostrarNombres(pacientes);
    printf("Ingresar nombre: ");
    scanf("%s", nombre);

    Paciente *paciente_actual = (Paciente *)list_first(pacientes);
    bool encontrado = false;

    while (paciente_actual != NULL && !encontrado) {
        if (strcmp(nombre, paciente_actual->nombre) == 0) {
            int option;
            printf("Asignar prioridad al paciente\n");
            printf("1) 'BAJA'\n");
            printf("2) 'MEDIA'\n");
            printf("3) 'ALTA'\n");
            printf("Para asignar prioridad al paciente %s, ingrese el número correspondiente: ", paciente_actual->nombre);

            do {
                scanf("%d", &option);
                switch (option) {
                    case 1:
                        strcpy(paciente_actual->prioridad, "BAJA");
                        break;
                    case 2:
                        strcpy(paciente_actual->prioridad, "MEDIA");
                        break;
                    case 3:
                        strcpy(paciente_actual->prioridad, "ALTA");
                        break;
                    default:
                        printf("Opción inválida. Intente de nuevo.\n");
                        break;
                }
            } while (option < 1 || option > 3);

            encontrado = true;
        }

        paciente_actual = (Paciente *)list_next(pacientes);
    }

    if (!encontrado) {
        printf("No se encontró un paciente con el nombre proporcionado.\n");
    }

    printf("¿Desea cambiar la prioridad de otro paciente?\n");
    printf("1) Si\n");
    printf("2) No\n");

    int option2;
    scanf("%d", &option2);
    while (option2 < 1 || option2 > 2) {
        printf("Opción inválida. Intente de nuevo.\n");
        scanf("%d", &option2);
    }

    if (option2 == 1) {
        asignar_prioridad(pacientes); // No recursión, llamada dentro de un bucle
    }
 
}

void MostrarPacientesPorPrioridad(List *pacientes)
{
  int option;
  printf("Mostrar pacientes por prioridad\n\n");
  printf("1) 'BAJA'\n");
  printf("2) 'MEDIA'\n");
  printf("3) 'ALTA'\n");
  printf("Ingrese el número correspondiente a la prioridad que desea mostrar: ");
  scanf("%d", &option);
  switch (option)
    {
      case 1:
      printf("Pacientes con prioridad 'BAJA':\n\n");
      Paciente *paciente_baja = (Paciente *)list_first(pacientes);
      int i = 0;
      while(paciente_baja != NULL)
        {
          if(strcmp(paciente_baja->prioridad, "BAJA") == 0)
          {
            imprimirPaciente(paciente_baja);
            i++;
          }
            paciente_baja = (Paciente *)list_next(pacientes);
        }
        if(i == 0)
        {
          printf("No hay pacientes con prioridad 'BAJA'\n");
        }
      break;
      
      case 2:
      printf("Pacientes con prioridad 'MEDIA':\n\n");
      Paciente *paciente_Media = (Paciente *)list_first(pacientes);
      int j = 0;
      while(paciente_Media != NULL)
          {
            if(strcmp(paciente_Media->prioridad, "MEDIA") == 0)
            {
              imprimirPaciente(paciente_Media);
              j++;
            }
             paciente_Media = (Paciente *)list_next(pacientes);
          }
          if(j == 0)
          {
            printf("No hay pacientes con prioridad 'MEDIA'\n");
          }
      break;
      
      case 3:
      printf("Pacientes con prioridad 'ALTA':\n\n");
      Paciente *paciente_Alta = (Paciente *)list_first(pacientes);
      int k = 0;
      while(paciente_Alta != NULL)
          {
            if(strcmp(paciente_Alta->prioridad, "ALTA") == 0)
            {
              imprimirPaciente(paciente_Alta);
              k++;
            }
              paciente_Alta = (Paciente *)list_next(pacientes);
          }
      if(k==0)
      {
        printf("No hay pacientes con prioridad 'ALTA'\n");
      }
      break;
      
      
    }
}

int main() {
  char opcion;
  List *pacientes = list_create(); // puedes usar una lista para gestionar los pacientes

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                           // newline anterior

    switch (opcion) {
    case '1':
      registrar_paciente(pacientes);
      break;
    case '2':
      asignar_prioridad(pacientes);
      OrdenarPrioridad(pacientes);
      break;
    case '3':
      mostrar_lista_pacientes(pacientes);
      break;
    case '4':
      printf("Atendiendo al siguiente paciente...\n\n");
      Paciente *p = list_first(pacientes);
      printf("Nombre del paciente atendido: %s\n", p->nombre);
      list_popFront(pacientes);
      break;
    case '5':
      MostrarPacientesPorPrioridad(pacientes);
      break;
    case '6':
      puts("Saliendo del sistema de gestión hospitalaria...");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '6');

  // Liberar recursos, si es necesario
  list_clean(pacientes);

  return 0;
}