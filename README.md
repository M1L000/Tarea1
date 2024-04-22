**Sistema de Gestión de Pacientes en Hospital**

Este sistema permite a los usuarios gestionar la atención de pacientes en un hospital. Los usuarios pueden registrar nuevos pacientes, asignar prioridades, ver la lista de espera, y más. Esta herramienta está diseñada para mejorar la eficiencia en la atención de los pacientes, asegurando que aquellos en situaciones críticas reciban atención lo más pronto posible.

---
## Cómo compilar y ejecutar

Para compilar y ejecutar el programa seguiremos los siguientes pasos:

1) Entraremos al link de replit en el el cual se encuentra el codigo: [Repl.it](https://replit.com/join/tzxllripsx-milovanfuentesl)
2) Haremos click en el apartado de arriba, en el botón verde que dice Run y así se empezara a ejecutar el programa.

## Funcionalidades

### Funcionando correctamente:

- Registrar pacientes con sus datos básicos y una prioridad inicial.
- Asignar o modificar la prioridad de los pacientes.
- Ver la lista de espera de pacientes, ordenada por prioridad y hora de registro.
- Atender al siguiente paciente, respetando el orden de prioridad.
- Ver lista de paciente de cierta prioridad.

### Problemas conocidos:
Al ingresar pacientes en la función  registrar_paciente, solo se puede ingresar una palabra en el nombre, en el apellido y en el síntoma.

### A mejorar:
- Implementar una interfaz de usuario más amigable.
- Implementar sistema para leer una frase y no una palabra.

### Ejemplo de uso:
  **Paso 1: Registrar un Nuevo Paciente**

Se comienza registrando un nuevo paciente que acaba de llegar al hospital.

````c
Ingrese su opción: 1
Registrar nuevo paciente

Nombre: Milovan
Apellido: Fuentes
Edad: 19
Sintoma: Cancer
Hora de ingreso del paciente: 
23:41:43
Presione una tecla para continuar...
````
El sistema inscribe a Milovan Fuentes con una prioridad inicial clasificada como "BAJA" y registra la hora actual de inscripción. Posteriormente, la prioridad inicial podría modificarse según una evaluación médica más exhaustiva.

**Paso 2: Asignar Prioridad a un Paciente**

Tras una evaluación inicial, el médico determina que el estado de Milovan Fuentes requiere atención prioritaria.
````c
Ingrese su opción: 2
Ingrese el nombre del paciente a asignar prioridad: 
1) Milovan = BAJA
2) Jose = BAJA
Ingresar nombre: Milovan
Asignar prioridad al paciente
1) 'BAJA'
2) 'MEDIA'
3) 'ALTA'
Para asignar prioridad al paciente Milovan, ingrese el número correspondiente: 3
¿Desea cambiar la prioridad de otro paciente?
1) Si
2) No
2
Presione una tecla para continuar...
````
El sistema actualiza la prioridad de Milovan Fuentes a "ALTA", asegurando que será uno de las próximos pacientes en ser atendido.
**Paso 3: Ver la Lista de Espera**

El usuario revisa la lista de espera para ver todos los pacientes y sus prioridades.
````c
Ingrese su opción: 3
Pacientes en espera: 

Paciente 1:
Nombre: Milovan Fuentes
Edad: 19
Síntoma: Cancer
Prioridad: ALTA
Hora de llegada: 23:44:31

Paciente 2:
Nombre: Jose Cabrera
Edad: 20
Síntoma: Fiebre
Prioridad: BAJA
Hora de llegada: 23:44:56

Presione una tecla para continuar...
````
La lista muestra a Milovan Fuentes en la parte superior, indicando su prioridad alta y que es la siguiente en línea para recibir atención.
**Paso 4: Atender al Siguiente Paciente**

Milovan Fuentes es llamada para ser atendida basándose en su prioridad.
````c
Ingrese su opción: 4
Atendiendo al siguiente paciente...

Nombre del paciente atendido: Milovan
Presione una tecla para continuar...

````
El sistema muestra que Milovan Fuentes está siendo atendida y la elimina de la lista de espera.

**Paso 5: Mostrar pacientes por prioridad**
En esta opción se mostrara los pacientes los cuales tengan la prioridad la cual el usuario entregue:
````c
Ingrese su opción: 5
Mostrar pacientes por prioridad

1) 'BAJA'
2) 'MEDIA'
3) 'ALTA'
Ingrese el número correspondiente a la prioridad que desea mostrar: 3
Pacientes con prioridad 'ALTA':

Nombre: Milovan Fuentes
Edad: 19
Síntoma: Cancer
Prioridad: ALTA
Hora de llegada: 23:49:51

Nombre: Jose Cabrera
Edad: 20
Síntoma: Fiebre
Prioridad: ALTA
Hora de llegada: 23:50:08

Presione una tecla para continuar...
````
Aquí se muestra los datos de los pacientes los cuales tienen prioridad “ALTA”. 

### Contribuciones
## Milovan Fuentes:
- Desarrollo del algoritmo.
- Desarrollo de lógica de funciones.
- Desarrollo de las funciones.
- Desarrollo de todo el programa.
- **Auto-evaluación**: 3 (Aporte excelente)
