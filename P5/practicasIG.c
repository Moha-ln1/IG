
/*	Prácticas de Informática Gráfica

    Grupos C y D				Curso 2023-24
 	
	Codigo base para la realización de las practicas de IG
	
	Estudiante: Mohammed Lahssaini Nouijah

	Programa principal
=======================================================
	G. Arroyo, J.C. Torres 
	Dpto. Lenguajes y Sistemas Informticos
	(Univ. de Granada)

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details 
 http://www.gnu.org/copyleft/gpl.html

=======================================================

	practicasIG.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "practicasIG.h"
#include "modelo.h"



/*=================================================*/

/**	int main( int argc, char *argv[] )	
	Programa principal.
	
	Inicializa glut y openGL
	Crea la ventana X
	Inicializa las variables globales
	lanza los gestores de eventos	
**/

int main(int argc, char *argv[]) {
    // Inicializa GLUT y configura la ventana
    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 800);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("IG. Curso 2024/25. Autor: Mohammed Lahssaini Nouijah");


    // Inicializa parámetros de OpenGL
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Inicializa las variables del modelo (después de configurar OpenGL)
    initModel();

    // Configura funciones de dibujo y redimensionamiento de la ventana
    glutDisplayFunc(Dibuja);
    glutReshapeFunc(inicializaVentana);

    // Configura funciones de interacción
    glutKeyboardFunc(letra);
    glutSpecialFunc(especial);
    glutMouseFunc(clickRaton);
    glutMouseFunc(mouseFunc); // Registro de la función de manejo de ratón
    glutMotionFunc(RatonMovido);

    // Configura función de temporizador
    glutTimerFunc(30, idle, 0);

    // Inicia el gestor de eventos de GLUT
    glutMainLoop();
    return 0;
}
