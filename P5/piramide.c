#include "piramide.h"
#include <GL/glut.h>

Piramide::Piramide(float lado, float altura) {
    float l = lado / 2.0f;

    // Definir los vértices de la pirámide
    vertices = {
        -l, 0, l,   // Vértice 0 (base)
        l, 0, l,    // Vértice 1 (base)
        l, 0, -l,   // Vértice 2 (base)
        -l, 0, -l,  // Vértice 3 (base)
        0, altura, 0   // Vértice 4 (punta)
    };

    // Definir las caras de la pirámide en términos de triángulos (índices de vértices)
    caras = {
        0, 1, 4,  // Cara frontal
        1, 2, 4,  // Cara derecha
        2, 3, 4,  // Cara trasera
        3, 0, 4,  // Cara izquierda
        0, 3, 2,  0, 2, 1  // Base cuadrada (dos triángulos)
    };

    // Inicializar las normales
    calcularNormales();
}


void Piramide::draw() {

        // Aplicar material si está definido
    material.aplicar();

    glPushMatrix();
    aplicarTransformaciones();

    // Activar textura si es válida
    if (textura.esValida()) {
        textura.activar();
    }

    if (estadoVisualizacion.modoSombreado == GL_FLAT) {
        dibujarFlat();
    } else {
        dibujarSmooth();
    }

    glPopMatrix();
}
