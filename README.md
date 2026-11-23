# 🏹 El Torneo de Artemisa: El desafío de los dioses

Proyecto académico desarrollado en **C++** para la materia **Programación Estructurada**, correspondiente a la carrera Analista Programador Universitario de la Universidad Nacional de Jujuy (UNJu).

## 📖 Descripción

*El Torneo de Artemisa: El desafío de los dioses* es un juego desarrollado en C++ que simula un torneo de arquería ambientado en un mundo de inspiración mitológica.

Los participantes deben demostrar su habilidad realizando disparos sobre una diana de 9 × 9 casillas. Cada casilla contiene un número con propiedades matemáticas particulares, que determinan los puntos y las recompensas obtenidas.

El sistema permite gestionar arqueros, generar dianas aleatorias, desarrollar partidas y consultar un podio con los mejores resultados.

## 🎮 Funcionalidades principales

El programa cuenta con cuatro opciones principales:

### 1. 🛡️ Gestión de arqueros

Permite administrar los arqueros que participan en el torneo mediante operaciones de ABMC:

- **Agregar:** registrar nuevos arqueros con apellido, nombre, apodo y signo zodiacal.
- **Consultar:** buscar arqueros mediante su apodo.
- **Modificar:** actualizar los datos personales de un arquero.
- **Eliminar:** quitar arqueros del registro.
- **Listar:** mostrar todos los arqueros registrados.

Cada arquero también posee estadísticas relacionadas con sus dracmas, mejor puntaje, torneos ganados y torneos disputados.

El registro se administra mediante un arreglo estático con capacidad máxima para 100 arqueros. Los elementos se mantienen ordenados alfabéticamente por apodo, permitiendo utilizar búsqueda binaria para las consultas.

### 2. 🎯 Gestión de la diana

Permite generar y visualizar una diana de **9 filas por 9 columnas**.

Cada casilla contiene un número aleatorio entre 1 y 999, sin repeticiones dentro de la misma diana.

La generación contempla diferentes propiedades matemáticas:

- Números primos.
- Números de Fibonacci.
- Números capicúa.
- Cuadrados perfectos.
- Números de Niven.

La diana solamente se considera válida cuando contiene al menos un número de cada una de estas propiedades.

Además, las casillas se distribuyen en diferentes zonas, asignando recompensas y puntajes según su ubicación respecto del centro.

### 3. ⚔️ Jugar

Es el módulo donde se desarrolla el torneo de arquería.

Sus principales características son:

- Selección de los arqueros participantes.
- Desarrollo de hasta cinco rondas.
- Disparos aleatorios sobre casillas que todavía no fueron ocupadas.
- Acumulación de puntaje y dracmas.
- Finalización anticipada cuando un participante consigue una flecha perfecta en el centro de la diana.
- Resolución de empates mediante disparos adicionales.

Cada participante realiza un disparo por ronda. Las casillas ocupadas no pueden volver a utilizarse durante la partida.

Si no se consigue una flecha perfecta, el ganador se determina comparando los puntajes acumulados.

En caso de empate, los arqueros involucrados realizan nuevos disparos y gana quien obtiene una posición más cercana al centro de la diana.

### 4. 🏆 Podio

Permite visualizar el ranking de los arqueros que ganaron al menos un torneo.

El podio se puede consultar en dos modalidades:

- **Orden creciente:** de menor a mayor mejor puntaje.
- **Orden decreciente:** de mayor a menor mejor puntaje.

Para realizar el ordenamiento se utiliza una variante del método de ordenamiento Cocktail Shaker Sort, trabajando sobre un arreglo auxiliar de posiciones.

Finalmente, se utiliza una función recursiva para mostrar los tres primeros puestos.

## 🧩 Conceptos y herramientas aplicados

Durante el desarrollo se aplicaron diferentes contenidos de programación estructurada:

| Concepto | Aplicación |
|---|---|
| Arreglos estáticos | Administración de los arqueros y participantes. |
| Matrices | Representación de la diana de 9 × 9 casillas. |
| Estructuras (`struct`) | Representación de arqueros y casillas. |
| Funciones y procedimientos | División de las funcionalidades del programa. |
| Recursividad | Listado de arqueros y visualización del podio. |
| Búsqueda binaria | Consulta de arqueros por apodo. |
| Ordenamiento | Inserción ordenada de arqueros y ordenamiento del podio. |
| Aleatoriedad | Generación de la diana y selección de disparos. |
| Validaciones | Control de datos ingresados y propiedades matemáticas. |

## 📁 Organización del proyecto

El proyecto está desarrollado en un único archivo fuente:

```text
El_Torneo_de_Artemisa/
│
└── El_torneo_de_Artemisa.cpp
```

Todo el código se encuentra dentro de `El_torneo_de_Artemisa.cpp`, incluyendo:

- Definición de constantes y estructuras.
- Prototipos de funciones.
- Función principal (`main`).
- Menús de navegación.
- Gestión de arqueros.
- Generación y validación de la diana.
- Desarrollo de las partidas.
- Cálculo de puntajes y desempates.
- Gestión y visualización del podio.

## ⚙️ Tecnologías utilizadas

- **Lenguaje de programación:** C++.
- **Bibliotecas:** `iostream`, `string.h`, `time.h` e `iomanip`.
- **Compilador:** GCC o Clang.
- **Entorno de desarrollo:** compatible con C++.

## 🚀 Compilación y ejecución

Para compilar el proyecto es necesario contar con un compilador de C++.

Desde una terminal, ubicarse en la carpeta donde se encuentra el archivo y ejecutar:

```bash
g++ -std=c++11 El_torneo_de_Artemisa.cpp -o torneo_artemisa
```

Para ejecutar el programa:

**macOS / Linux:**
```bash
./torneo_artemisa
```

**Windows:**
```bash
torneo_artemisa.exe
```

## 🎯 Objetivos académicos

El objetivo principal fue integrar los conocimientos adquiridos en Programación Estructurada mediante el desarrollo de un juego completo en C++.

El proyecto permitió trabajar con:

- Diseño y organización de algoritmos.
- Modularización mediante funciones.
- Manipulación de arreglos y matrices.
- Búsquedas y métodos de ordenamiento.
- Recursividad.
- Validación de datos.
- Generación de valores aleatorios.
- Resolución de problemas mediante lógica de programación.

## 👨‍💻 Autor

**Alejandro Imanol Cruz**

Analista Programador Universitario – Universidad Nacional de Jujuy (UNJu).

Proyecto académico desarrollado para la materia Programación Estructurada.
