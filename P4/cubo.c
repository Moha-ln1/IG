#include "cubo.h"

Cubo::Cubo(float lado) : Objeto3D() {
    float l = lado / 2.0f;

    vertices = {
        // Cara frontal (2)
        -l, -l, l,   // Vértice 0 (Frontal inferior izquierdo)
        l, -l, l,    // Vértice 1 (Frontal inferior derecho)
        l, l, l,     // Vértice 2 (Frontal superior derecho)
        -l, l, l,    // Vértice 3 (Frontal superior izquierdo)

        // Cara trasera (3)
        -l, -l, -l,  // Vértice 4 (Trasera inferior izquierda)
        l, -l, -l,   // Vértice 5 (Trasera inferior derecho)
        l, l, -l,    // Vértice 6 (Trasera superior derecho)
        -l, l, -l,   // Vértice 7 (Trasera superior izquierdo)

        // Cara izquierda (4)
        -l, -l, l,   // Vértice 8 (Izquierda inferior izquierdo)
        -l, l, l,    // Vértice 9 (Izquierda superior izquierdo)
        -l, l, -l,   // Vértice 10 (Izquierda superior derecho)
        -l, -l, -l,  // Vértice 11 (Izquierda inferior derecho)

        // Cara derecha (6)
        l, -l, l,    // Vértice 12 (Derecha inferior izquierdo)
        l, l, l,     // Vértice 13 (Derecha superior izquierdo)
        l, l, -l,    // Vértice 14 (Derecha superior derecho)
        l, -l, -l,   // Vértice 15 (Derecha inferior derecho)

        // Cara superior (5)
        -l, l, l,    // Vértice 16 (Superior inferior izquierdo)
        l, l, l,     // Vértice 17 (Superior inferior derecho)
        l, l, -l,    // Vértice 18 (Superior superior derecho)
        -l, l, -l,   // Vértice 19 (Superior superior izquierdo)

        // Cara inferior (1)
        -l, -l, l,   // Vértice 20 (Inferior inferior izquierdo)
        l, -l, l,    // Vértice 21 (Inferior inferior derecho)
        l, -l, -l,   // Vértice 22 (Inferior superior derecho)
        -l, -l, -l   // Vértice 23 (Inferior superior izquierdo)
    };

    // Cambiamos el orden de los vértices a sentido horario
    caras = {
        0, 1, 2, 0, 2, 3,       // Frontal
        4, 6, 5, 4, 7, 6,       // Trasera
        8, 10, 11, 8, 9, 10,    // Izquierda
        12, 14, 13, 12, 15, 14, // Derecha
        16, 18, 19, 16, 17, 18, // Arriba
        20, 22, 21, 20, 23, 22  // Abajo
    };

    // Tamaño del lado en las coordenadas de textura
    float t = 0.25f;

    coordenadasTextura = {
        // Cara frontal (2)
        {3 * t, 2 * t}, {3 * t, 3 * t}, {2 * t, 3 * t}, {2 * t, 2 * t},

        // Cara trasera (3)
        {2 * t, t}, {3 * t, t}, {3 * t, 2 * t}, {2 * t, 2 * t},

        // Cara izquierda (4)
        {0.0f, 2 * t}, {0.0f, 3 * t}, {t, 3 * t}, {t, 2 * t},

        // Cara derecha (6)
        {3 * t, 2 * t}, {4 * t, 2 * t}, {4 * t, 3 * t}, {3 * t, 3 * t},

        // Cara superior (5)
        {0.0f, 2 * t}, {t, 2 * t}, {t, 3 * t}, {0.0f, 3 * t},

        // Cara inferior (1)
        {2 * t, 3 * t}, {3 * t, 3 * t}, {3 * t, 4 * t}, {2 * t, 4 * t}
    };

    calcularNormales();
}



void Cubo::draw() {

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
