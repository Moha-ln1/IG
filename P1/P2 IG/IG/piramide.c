#include "piramide.h"
#include <GL/glut.h>  // Librería para OpenGL

Piramide::Piramide(float l, float h): lado(l), altura(h) {}

void Piramide::draw() {
    float l = lado / 2.0f;

    // Dibuja la base de la pirámide (cuadrada)
    glBegin(GL_QUADS);
    glNormal3f(0.0, -1.0, 0.0); // Normal hacia abajo
    glVertex3f(-l, 0, -l);
    glVertex3f(l, 0, -l);
    glVertex3f(l, 0, l);
    glVertex3f(-l, 0, l);
    glEnd();

    // Dibuja las cuatro caras triangulares de la pirámide
    glBegin(GL_TRIANGLES);
    
    // Cara frontal
    glNormal3f(0.0, 0.5, 0.5);
    glVertex3f(-l, 0, l);
    glVertex3f(l, 0, l);
    glVertex3f(0.0, altura, 0.0);

    // Cara trasera
    glNormal3f(0.0, 0.5, -0.5);
    glVertex3f(l, 0, -l);
    glVertex3f(-l, 0, -l);
    glVertex3f(0.0, altura, 0.0);

    // Cara izquierda
    glNormal3f(-0.5, 0.5, 0.0);
    glVertex3f(-l, 0, -l);
    glVertex3f(-l, 0, l);
    glVertex3f(0.0, altura, 0.0);

    // Cara derecha
    glNormal3f(0.5, 0.5, 0.0);
    glVertex3f(l, 0, l);
    glVertex3f(l, 0, -l);
    glVertex3f(0.0, altura, 0.0);

    glEnd();
}

void Piramide::colorear(float color[4]){
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);  
}

void Piramide::dibujar(float color[4]){
    this->colorear(color);
        this->draw();

}