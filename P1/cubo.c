#include "cubo.h"
#include <GL/glut.h>  // Librería para OpenGL

Cubo::Cubo(float l): lado(l) {}

void Cubo::draw() {
    float l = lado / 2.0f;
    glBegin(GL_QUADS);
    
    // Cara frontal
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(-l, -l, l);
    glVertex3f(l, -l, l);
    glVertex3f(l, l, l);
    glVertex3f(-l, l, l);
    
    // Cara trasera
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(-l, -l, -l);
    glVertex3f(-l, l, -l);
    glVertex3f(l, l, -l);
    glVertex3f(l, -l, -l);
    
    // Cara izquierda
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-l, -l, -l);
    glVertex3f(-l, -l, l);
    glVertex3f(-l, l, l);
    glVertex3f(-l, l, -l);
    
    // Cara derecha
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(l, -l, -l);
    glVertex3f(l, l, -l);
    glVertex3f(l, l, l);
    glVertex3f(l, -l, l);
    
    // Cara superior
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-l, l, -l);
    glVertex3f(-l, l, l);
    glVertex3f(l, l, l);
    glVertex3f(l, l, -l);
    
    // Cara inferior
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(-l, -l, -l);
    glVertex3f(l, -l, -l);
    glVertex3f(l, -l, l);
    glVertex3f(-l, -l, l);

    glEnd();
}

void Cubo::colorear(float color[4]){
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);  
}

void Cubo::dibujar(float color[4]){
    this->colorear(color);
    this->draw();
}