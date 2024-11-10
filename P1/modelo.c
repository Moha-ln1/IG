/*  Prácticas de Informática Gráfica

  Grupos C y D        Curso 2023-24
  
  Codigo base para la realización de las practicas de IG
  
  Estudiante: 

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

=======================================================/
modulo modelo.c
    Representación del modelo
    Funciones de dibujo
    Función Idle
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>    // Libreria de utilidades de OpenGL
#include "practicasIG.h"


/** void initModel()

Inicializa el modelo y las variables globales

**/
void initModel()
{
    printf("Inicializando el modelo y las variables globales...\n");
}

/**************************************************************************/
//  Implementacion de los ejes.
/**************************************************************************/

class Ejes:Objeto3D 
{ 
public: 
    float longitud = 30;
    // Dibuja el objeto
    void draw()
    {
        glDisable(GL_LIGHTING);
        glBegin(GL_LINES);
        {
            glColor3f(0, 1, 0);
            glVertex3f(0, 0, 0);
            glVertex3f(0, longitud, 0);

            glColor3f(1, 0, 0);
            glVertex3f(0, 0, 0);
            glVertex3f(longitud, 0, 0);

            glColor3f(0, 0, 1);
            glVertex3f(0, 0, 0);
            glVertex3f(0, 0, longitud);
        }
        glEnd();
        glEnable(GL_LIGHTING);
    }
}; 

Ejes ejesCoordenadas;

/************************************************************************/
/******************Definicion de objetos de la escena********************/
/************************************************************************/

Cubo cubo = Cubo(5.0f);
Piramide piramide = Piramide(5.0f, 7.0f);

/**************************************************************************/
//  Función de dibujo
/**************************************************************************/

void Dibuja(void)
{
    // Configuramos la posición de la fuente de luz
    static GLfloat pos[4] = { 5.0, 5.0, 10.0, 0.0 };

    // Colores para los objetos
    float colorCubo[4] = { 1.0, 0.0, 1.0, 1.0 };  // Magenta
    float colorPiramide[4] = { 0.0, 1.0, 1.0, 1.0 };  // Cian

    // Limpiamos el buffer de color y profundidad
    glPushMatrix();  // Guardamos el estado actual de la matriz

    glClearColor(0.0, 0.0, 0.0, 1.0);  // Color de fondo negro
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Limpiamos el buffer de color y profundidad

    // Establecemos la transformación de visualización (cámara)
    transformacionVisualizacion();

    // Configuramos la posición de la luz
    glLightfv(GL_LIGHT0, GL_POSITION, pos);

    // Dibujamos los ejes sin iluminación
    glDisable(GL_LIGHTING);
    ejesCoordenadas.draw();

    // Si la iluminación está activada, la habilitamos de nuevo
    if (estado.iluminacionActivada) {
        estado.setIluminacion(1);  // Activar iluminación
    }

    // Dibuja el cubo
    glPushMatrix();  // Guardamos la matriz antes de aplicar transformaciones
    cubo.dibujar(colorCubo);
    glPopMatrix();  // Restauramos la matriz original

    // Dibuja la pirámide con una traslación
    glPushMatrix();
    glTranslatef(10.0, 0.0, 0.0);  // Movemos la pirámide 10 unidades a la derecha
    piramide.dibujar(colorPiramide);
    glPopMatrix();

    estado.setModo(estado.modo);  // Aplicamos el modo de visualización antes de dibujar
    
    glPopMatrix();  // Restauramos la matriz de transformación global

    // Intercambiamos los buffers para mostrar lo dibujado
    glutSwapBuffers();

    // Depuración: Mostrar en consola el estado de visualización y objetos
    const char* modoTexto = (estado.modo == GL_FILL) ? "RELLENO" : (estado.modo == GL_LINE) ? "LINEAS" : "PUNTOS";
    const char* iluminacionTexto = estado.iluminacionActivada ? "ACTIVADA" : "DESACTIVADA";

    printf("Modo de visualización: %s, Iluminación: %s\n", modoTexto, iluminacionTexto);
}


/** void idle()

    Procedimiento de fondo. Es llamado por glut cuando no hay eventos pendientes.
**/
void idle(int v)
{
    glutPostRedisplay();  // Forzar el redibujado
    glutTimerFunc(30, idle, 0);  // Repetir dentro de 30 ms
}
