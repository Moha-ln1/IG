#include "robot.h"
#include "cubo.h"
#include <GL/glut.h>

// Definición de los colores usados
float color[8][4] = {
    {1.0, 0.8, 0.3, 1.0},    // Color amarillo
    {0.7, 0.7, 0.7, 1.0},    // Color gris
    {1.0, 0.0, 0.0, 1.0},    // Color rojo
    {0.7, 0.6, 0.2, 1.0},    // Color marrón
    {0.2, 1.0, 1.0, 1.0},    // Color celeste
    {1.0, 0.86, 0.3, 1.0},   // Color marrón claro
    {0.0, 1.0, 0.0, 1.0},    // Color verde
    {0.0, 0.0, 1.0, 1.0}     // Color azul
};

Cubo cuboA(1.0f);
// Definición de la clase Cabeza
Cabeza::Cabeza() {
    inicializarTransformaciones(0.0f, 2.25f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f);
}

void Cabeza::draw() {
    glPushMatrix();
    aplicarTransformaciones();
    
    
    // Dibujar cabeza
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[1]);
    glutSolidSphere(0.5f, 20, 20);

    // Dibujar ojos
    glPushMatrix();
    glTranslatef(-0.15f, 0.1f, 0.45f);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[0]);
    glutSolidSphere(0.05f, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.15f, 0.1f, 0.45f);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[0]);
    glutSolidSphere(0.05f, 20, 20);
    glPopMatrix();

    glPopMatrix();
}

// Definición de la clase Brazo
Brazo::Brazo(float posicionX) {
    inicializarTransformaciones(posicionX, 1.75f, 0.0f, 0.0f, 0.0f, 0.0f, 0.35f, 0.8f, 0.35f);
}

void Brazo::draw() {
    glPushMatrix();
    aplicarTransformaciones();

    // Dibujar hombro y brazo juntos para tener una sola transformación
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[3]);

    // Dibujar el hombro como base de rotación del brazo
    glPushMatrix();
    glTranslatef(0.0f, -0.4f, 0.0f); // Colocar el hombro como punto de rotación del brazo
    glutSolidSphere(0.3f, 20, 20); // Esfera para el hombro

    // Dibujar el brazo conectado al hombro
    glTranslatef(0.0f, -0.6f, 0.0f); // Colocar el brazo debajo del hombro
    glScalef(0.7f, 1.2f, 0.7f); // Ajustar la escala del brazo para darle un aspecto más ancho y menos largo
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[2]);
    cuboA.draw();
    glPopMatrix();

    glPopMatrix();
}


// Definición de la clase Pierna
Pierna::Pierna(float posicionX) {
    inicializarTransformaciones(posicionX, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.25f, 1.0f, 0.25f);
}

void Pierna::draw() {
    glPushMatrix();
    aplicarTransformaciones();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[4]);
    cuboA.draw();
    glPopMatrix();
}



// Definición de la clase Robot
Robot::Robot()
    : cabeza(),
      brazoDerecho(0.75f), brazoIzquierdo(-0.75f),
      piernaDerecha(0.25f), piernaIzquierda(-0.25f) {}

void Robot::draw() {
    glPushMatrix();

    // Escalado general del robot
    glScalef(3.0f, 3.0f, 3.0f); // Escalar el robot 3 veces en cada dirección

    aplicarTransformaciones();  // Aplicar las transformaciones generales del robot

    // Dibujar torso
    glPushMatrix();
    glTranslatef(0.0f, 1.0f, 0.0f);  // Elevar el torso
    glScalef(1.0f, 1.5f, 1.0f);      // Escalar para simular el torso
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[5]);
    cuboA.draw();
    glPopMatrix();
    // Dibujar cuello
    glPushMatrix();
    glTranslatef(0.0f, 1.75f, 0.0f); // Posición del cuello, justo encima del torso
    glScalef(0.3f, 0.5f, 0.3f);      // Escalar para simular el tamaño del cuello
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[3]); // Color del cuello
    glutSolidCube(1.0f);             // Dibujar cubo pequeño para el cuello
    glPopMatrix();


    // Dibujar hombro derecho
    glPushMatrix();
    glTranslatef(0.75f, 1.75f, 0.0f); // Ajustar la posición del hombro derecho
    glScalef(0.5f, 0.5f, 0.5f);       // Escalar para simular el hombro como una pequeña conexión
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[1]);
    cuboA.draw();
    glPopMatrix();

    // Dibujar hombro izquierdo
    glPushMatrix();
    glTranslatef(-0.75f, 1.75f, 0.0f); // Ajustar la posición del hombro izquierdo
    glScalef(0.5f, 0.5f, 0.5f);        // Escalar para simular el hombro como una pequeña conexión
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[1]);
    cuboA.draw();
    glPopMatrix();


    // Dibujar cabeza
    cabeza.draw();

    // Dibujar brazo derecho
    brazoDerecho.draw();

    // Dibujar brazo izquierdo
    brazoIzquierdo.draw();

    // Dibujar pierna derecha
    piernaDerecha.draw();

    // Dibujar pierna izquierda
    piernaIzquierda.draw();

    glPopMatrix();  // Fin del dibujado del robot
}

// Métodos para manipular las partes del robot
void Robot::cabezaLeft() {
    if (cabeza.rotacion[1] < 45.0f) {
        cabeza.rotacion[1] += 5.0f;
        cabeza.inicializarTransformaciones(cabeza.posicion[0], cabeza.posicion[1], cabeza.posicion[2],
                                           0.0f, cabeza.rotacion[1], 0.0f,
                                           cabeza.escala[0], cabeza.escala[1], cabeza.escala[2]);
    }
}

void Robot::cabezaRight() {
    if (cabeza.rotacion[1] > -45.0f) {
        cabeza.rotacion[1] -= 5.0f;
        cabeza.inicializarTransformaciones(cabeza.posicion[0], cabeza.posicion[1], cabeza.posicion[2],
                                           0.0f, cabeza.rotacion[1], 0.0f,
                                           cabeza.escala[0], cabeza.escala[1], cabeza.escala[2]);
    }
}

void Robot::brazoDerechoArriba() {
    // Limitar el rango de movimiento entre -90 y 90 grados para que el brazo no gire completamente hacia atrás
    if (brazoDerecho.rotacion[0] > -180.0f) {
        brazoDerecho.rotacion[0] -= 5.0f; // Restamos para mover hacia adelante
        brazoDerecho.inicializarTransformaciones(brazoDerecho.posicion[0], brazoDerecho.posicion[1], brazoDerecho.posicion[2],
                                                 brazoDerecho.rotacion[0], brazoDerecho.rotacion[1], brazoDerecho.rotacion[2],
                                                 brazoDerecho.escala[0], brazoDerecho.escala[1], brazoDerecho.escala[2]);
    }
}

void Robot::brazoDerechoAbajo() {
    if (brazoDerecho.rotacion[0] < 0.0f) { // Limitar el rango para que no gire completamente hacia atrás
        brazoDerecho.rotacion[0] += 5.0f; // Sumamos para mover hacia atrás
        brazoDerecho.inicializarTransformaciones(brazoDerecho.posicion[0], brazoDerecho.posicion[1], brazoDerecho.posicion[2],
                                                 brazoDerecho.rotacion[0], brazoDerecho.rotacion[1], brazoDerecho.rotacion[2],
                                                 brazoDerecho.escala[0], brazoDerecho.escala[1], brazoDerecho.escala[2]);
    }
}

void Robot::brazoIzquierdoArriba() {
    if (brazoIzquierdo.rotacion[0] > -180.0f) { // Limitar el rango entre -90 y 90 para el movimiento hacia adelante
        brazoIzquierdo.rotacion[0] -= 5.0f; // Restamos para mover hacia adelante
        brazoIzquierdo.inicializarTransformaciones(brazoIzquierdo.posicion[0], brazoIzquierdo.posicion[1], brazoIzquierdo.posicion[2],
                                                   brazoIzquierdo.rotacion[0], brazoIzquierdo.rotacion[1], brazoIzquierdo.rotacion[2],
                                                   brazoIzquierdo.escala[0], brazoIzquierdo.escala[1], brazoIzquierdo.escala[2]);
    }
}

void Robot::brazoIzquierdoAbajo() {
    if (brazoIzquierdo.rotacion[0] < 0.0f) { // Limitar el rango entre -90 y 90 para el movimiento hacia atrás
        brazoIzquierdo.rotacion[0] += 5.0f; // Sumamos para mover hacia atrás
        brazoIzquierdo.inicializarTransformaciones(brazoIzquierdo.posicion[0], brazoIzquierdo.posicion[1], brazoIzquierdo.posicion[2],
                                                   brazoIzquierdo.rotacion[0], brazoIzquierdo.rotacion[1], brazoIzquierdo.rotacion[2],
                                                   brazoIzquierdo.escala[0], brazoIzquierdo.escala[1], brazoIzquierdo.escala[2]);
    }
}



void Robot::piernaDerechaAdelante() {
    if (piernaDerecha.rotacion[0] < 45.0f) {
        piernaDerecha.rotacion[0] += 5.0f;
        piernaDerecha.inicializarTransformaciones(piernaDerecha.posicion[0], piernaDerecha.posicion[1], piernaDerecha.posicion[2],
                                                  piernaDerecha.rotacion[0], 0.0f, 0.0f,
                                                  piernaDerecha.escala[0], piernaDerecha.escala[1], piernaDerecha.escala[2]);
    }
}

void Robot::piernaDerechaAtras() {
    if (piernaDerecha.rotacion[0] > -45.0f) {
        piernaDerecha.rotacion[0] -= 5.0f;
        piernaDerecha.inicializarTransformaciones(piernaDerecha.posicion[0], piernaDerecha.posicion[1], piernaDerecha.posicion[2],
                                                  piernaDerecha.rotacion[0], 0.0f, 0.0f,
                                                  piernaDerecha.escala[0], piernaDerecha.escala[1], piernaDerecha.escala[2]);
    }
}

void Robot::piernaIzquierdaAdelante() {
    if (piernaIzquierda.rotacion[0] < 45.0f) {
        piernaIzquierda.rotacion[0] += 5.0f;
        piernaIzquierda.inicializarTransformaciones(piernaIzquierda.posicion[0], piernaIzquierda.posicion[1], piernaIzquierda.posicion[2],
                                                    piernaIzquierda.rotacion[0], 0.0f, 0.0f,
                                                    piernaIzquierda.escala[0], piernaIzquierda.escala[1], piernaIzquierda.escala[2]);
    }
}

void Robot::piernaIzquierdaAtras() {
    if (piernaIzquierda.rotacion[0] > -45.0f) {
        piernaIzquierda.rotacion[0] -= 5.0f;
        piernaIzquierda.inicializarTransformaciones(piernaIzquierda.posicion[0], piernaIzquierda.posicion[1], piernaIzquierda.posicion[2],
                                                    piernaIzquierda.rotacion[0], 0.0f, 0.0f,
                                                    piernaIzquierda.escala[0], piernaIzquierda.escala[1], piernaIzquierda.escala[2]);
    }
}

void Robot::reset() {
    cabeza.inicializarTransformaciones(0.0f, 2.25f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f);
    brazoDerecho.inicializarTransformaciones(0.75f, 1.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.25f, 1.0f, 0.25f);
    brazoIzquierdo.inicializarTransformaciones(-0.75f, 1.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.25f, 1.0f, 0.25f);
    piernaDerecha.inicializarTransformaciones(0.25f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.25f, 1.0f, 0.25f);
    piernaIzquierda.inicializarTransformaciones(-0.25f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.25f, 1.0f, 0.25f);
}

