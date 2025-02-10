# Prácticas de Informática Gráfica (Curso 2024/2025)

Este repositorio contiene las prácticas resueltas de la asignatura de **Informática Gráfica** correspondientes al curso 2024/2025. Las prácticas están diseñadas para trabajar con OpenGL, y cubren diversos aspectos de la programación gráfica, desde la creación de geometrías simples hasta la implementación de modelos jerárquicos y la interacción con el usuario.

## Prácticas Resueltas

### Práctica 1: Programación con una biblioteca de programación gráfica
- **Objetivos**: Crear programas que dibujen geometrías simples con OpenGL, entender la estructura de programas sencillos usando OpenGL y GLUT, y aprender a utilizar las primitivas de dibujo de OpenGL.
- **Funcionalidad**: Se implementa la visualización de una pirámide de base cuadrada y un cubo en diferentes modos (puntos, alambre, sólido sin iluminación y sólido con iluminación).
- **Código**: `practicasIG.c`, `entradaTeclado.c`, `modelo.c`.

### Práctica 2: Modelos poligonales
- **Objetivos**: Entender la representación de mallas de triángulos, calcular normales de triángulos y vértices, y leer, representar y visualizar mallas de triángulos desde archivos PLY.
- **Funcionalidad**: Se crea una clase para representar mallas de triángulos, se implementa la lectura de archivos PLY, y se calculan las normales de cara y vértice. Además, se visualizan los modelos en modos FLAT y SMOOTH.
- **Código**: `file_ply_stl.cc`, `modelo.c`, `visual.c`.

### Práctica 3: Modelos jerárquicos
- **Objetivos**: Diseñar e implementar modelos jerárquicos de objetos articulados, crear el grafo de escena, y modificar interactivamente parámetros del modelo.
- **Funcionalidad**: Se diseña un modelo jerárquico con al menos tres grados de libertad (por ejemplo, una grúa), se implementa la visualización del grafo de escena, y se añade interacción para modificar los parámetros del modelo con el teclado.
- **Código**: `entradaTeclado.c`, `modelo.c`.

### Práctica 4: Materiales, fuentes de luz y texturas
- **Objetivos**: Definir fuentes de luz y materiales en OpenGL, generar y representar coordenadas de textura en mallas de triángulos, y visualizar modelos con textura.
- **Funcionalidad**: Se añaden materiales y texturas a las mallas, se implementa la visualización de un dado con textura, y se crea una escena con diferentes materiales y fuentes de luz.
- **Código**: `modelo.c`, `visual.c`, `lector-jpg.cpp`.

### Práctica 5: Interacción
- **Objetivos**: Desarrollar aplicaciones gráficas interactivas, gestionar eventos de entrada de teclado y ratón, e implementar operaciones de selección de objetos de la escena.
- **Funcionalidad**: Se implementa la selección de objetos de la escena usando el ratón, y se controla interactivamente la cámara.
- **Código**: `entradaTeclado.c`, `mouse.c`, `modelo.c`.

### Práctica 6: Proyecto
- **Objetivos**: Diseñar y programar una aplicación gráfica interactiva que integre los conceptos vistos en las prácticas anteriores.
- **Funcionalidad**: Se desarrolla una aplicación gráfica interactiva que incluye modelos jerárquicos, texturas, iluminación, y selección de objetos.
- **Código**: Integración de código de prácticas anteriores.

## Requisitos
- **OpenGL**: Las prácticas están desarrolladas utilizando OpenGL y GLUT.
- **Compilación**: Se incluye un archivo `Makefile` para compilar el código.
- **Dependencias**: Es necesario tener instalada la librería `libjpeg-dev` para la lectura de imágenes JPEG en la Práctica 4.

