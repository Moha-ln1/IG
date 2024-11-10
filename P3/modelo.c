#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <GL/glut.h>    // Libreria de utilidades de OpenGL
#include "practicasIG.h"
#include "robot.h"

// Definimos las escenas como un vector de punteros a Objeto3D
std::vector<Objeto3D*> escena1; // Escena con cubo y objeto PLY
std::vector<Objeto3D*> escena2; // Escena con el robot

// Índice de la escena seleccionada
int escenaSeleccionada = 1;

// Instancia del modelo PLY y del cubo
MallaPLY modeloPLY("./ply_models/ant.ply");
Cubo cubo(10.0f);
Robot robot;

// Estado de visualización global
EstadoVisualizacion estadoGlobal;

// Crear un objeto Cubo
void initModel() {
    printf("Inicializando el modelo y las variables globales...\n");

    // Inicializar las escenas
    escena1.push_back(&cubo);
    escena1.push_back(&modeloPLY);
    escena2.push_back(&robot);

    estadoGlobal.setModo(GL_FILL); // Modo de dibujo por defecto
    estadoGlobal.setIluminacion(true);
}

/**************************************************************************/
//  Implementación de los ejes.
/**************************************************************************/
class Ejes : public Objeto3D {
public:
    float longitud = 30;
    void draw() override {
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
void Dibuja(void) {
    static GLfloat pos[4] = { 5.0, 5.0, 10.0, 1.0 };

    glPushMatrix();
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    transformacionVisualizacion();
    glLightfv(GL_LIGHT0, GL_POSITION, pos);

    glDisable(GL_LIGHTING);
    ejesCoordenadas.draw();

    std::vector<Objeto3D*>* escenaActual;
    if (escenaSeleccionada == 1) {
        escenaActual = &escena1;
    } else {
        escenaActual = &escena2;
    }

    if (estadoGlobal.iluminacionActivada) {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
    } else {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
    }

    for (Objeto3D* obj : *escenaActual) {
        obj->estadoVisualizacion = estadoGlobal;
        obj->draw();
    }

    glPopMatrix();
    glutSwapBuffers();
}


void animacion(int value) {
    // Movimiento de brazos
    static int brazoDerechoDireccion = 1;
    static int brazoIzquierdoDireccion = -1;
    
    // Movimiento de piernas
    static int piernaDerechaDireccion = 1;
    static int piernaIzquierdaDireccion = -1;

    // Movimiento de los brazos: sincronizar brazos opuestos
    if (brazoDerechoDireccion == 1) {
        robot.brazoDerechoArriba();
        if (robot.brazoDerecho.rotacion[0] <= -45.0f) {
            brazoDerechoDireccion = -1;
        }
    } else {
        robot.brazoDerechoAbajo();
        if (robot.brazoDerecho.rotacion[0] >= 0.0f) {
            brazoDerechoDireccion = 1;
        }
    }

    if (brazoIzquierdoDireccion == -1) {
        robot.brazoIzquierdoArriba();
        if (robot.brazoIzquierdo.rotacion[0] <= -45.0f) {
            brazoIzquierdoDireccion = 1;
        }
    } else {
        robot.brazoIzquierdoAbajo();
        if (robot.brazoIzquierdo.rotacion[0] >= 0.0f) {
            brazoIzquierdoDireccion = -1;
        }
    }

    // Movimiento de las piernas: sincronizar piernas opuestas
    if (piernaDerechaDireccion == 1) {
        robot.piernaDerechaAdelante();
        if (robot.piernaDerecha.rotacion[0] >= 30.0f) {
            piernaDerechaDireccion = -1;
        }
    } else {
        robot.piernaDerechaAtras();
        if (robot.piernaDerecha.rotacion[0] <= -30.0f) {
            piernaDerechaDireccion = 1;
        }
    }

    if (piernaIzquierdaDireccion == -1) {
        robot.piernaIzquierdaAdelante();
        if (robot.piernaIzquierda.rotacion[0] >= 30.0f) {
            piernaIzquierdaDireccion = 1;
        }
    } else {
        robot.piernaIzquierdaAtras();
        if (robot.piernaIzquierda.rotacion[0] <= -30.0f) {
            piernaIzquierdaDireccion = -1;
        }
    }

    // Movimiento de la cabeza: de lado a lado
    static int direccionCabeza = 1;
    if (direccionCabeza == 1) {
        robot.cabezaLeft();
        if (robot.cabeza.rotacion[1] >= 15.0f) {
            direccionCabeza = -1;
        }
    } else {
        robot.cabezaRight();
        if (robot.cabeza.rotacion[1] <= -15.0f) {
            direccionCabeza = 1;
        }
    }

    // Redibuja y establece un temporizador para la siguiente animación
    glutPostRedisplay();
    glutTimerFunc(30, animacion, 0);
}



void idle(int v) {
    glutPostRedisplay();
    glutTimerFunc(30, idle, 0);
}
