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
//#include "objeto3d.h"


/** void initModel()

Inicializa el modelo y las variables globales

**/
// Definimos la escena como un vector de punteros a Objeto3D
std::vector<Objeto3D*> escena;

// Índice del objeto seleccionado
int objetoSeleccionado = 0;

// Instancia del modelo PLY
MallaPLY modeloPLY= MallaPLY("./ply_models/ant.ply"); 
Cubo cubo(10.0f);
// Crear un objeto Cubo


void initModel()
{

    escena.push_back(&modeloPLY);
    escena.push_back(&cubo);
    printf("Inicializando el modelo y las variables globales...\n");
    objetoSeleccionado = 0;  // Seleccionar el primer objeto de la escena por defecto

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


/**************************************************************************/
//  Función de dibujo
/**************************************************************************/



void Dibuja(void)
{
    // Configuramos la posición de la fuente de luz
    static GLfloat pos[4] = { 5.0, 5.0, 10.0, 0.0 };

    // Limpiamos el buffer de color y profundidad
    glPushMatrix();  // Guardamos el estado actual de la matriz

    glClearColor(1.0, 1.0, 1.0, 1.0);  // Color de fondo blanco
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Limpiamos el buffer de color y profundidad

    // Establecemos la transformación de visualización (cámara)
    transformacionVisualizacion();

    // Configuramos la posición de la luz
    glLightfv(GL_LIGHT0, GL_POSITION, pos);

    // Dibujamos los ejes sin iluminación
    glDisable(GL_LIGHTING);
    ejesCoordenadas.draw();

    EstadoVisualizacion& estado = escena[objetoSeleccionado]->estadoVisualizacion;

    // Si la iluminación está activada, la habilitamos de nuevo
    if (estado.iluminacionActivada) {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
    } else {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
    }

    glPushMatrix();  // Guardamos la matriz antes de aplicar transformaciones
    //modeloPLY.inicializarTransformaciones(3.0f, 0.0f, -5.0f, 45.0f, 30.0f, 0.0f, 1.2f, 1.2f, 1.2f);
    modeloPLY.draw();  // Dibuja el modelo PLY
    glPopMatrix();  // Restauramos la matriz original

    // Dibuja la pirámide con una traslación
    glPushMatrix();
    cubo.inicializarTransformaciones(25.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
    cubo.draw();
    glPopMatrix();


    glPopMatrix();  // Restauramos la matriz de transformación global


/*
    glPushMatrix();
    // Dibujamos todos los objetos en la escena
    for (auto obj : escena) {
        obj->draw();  // Llamamos a la función dibujar de cada objeto
    }
    glPopMatrix();
    glPopMatrix();
*/
    
    // Intercambiamos los buffers para mostrar lo dibujado
    glutSwapBuffers();
}


/** void idle()

    Procedimiento de fondo. Es llamado por glut cuando no hay eventos pendientes.
**/
void idle(int v)
{
    glutPostRedisplay();  // Forzar el redibujado
    glutTimerFunc(30, idle, 0);  // Repetir dentro de 30 ms
}
