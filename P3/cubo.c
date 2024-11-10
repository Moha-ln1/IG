#include <GL/glut.h>
#include "cubo.h"

Cubo::Cubo(float lado) {
    float l = lado / 2.0f;

    // Definir los vértices del cubo
    vertices = {
        -l, -l, l, l, -l, l, l, l, l, -l, l, l,
        -l, -l, -l, l, -l, -l, l, l, -l, -l, l, -l
    };

    // Definir las caras del cubo
    caras = {
        0, 1, 2, 0, 2, 3,  // Cara frontal
        4, 7, 6, 4, 6, 5,  // Cara trasera
        0, 3, 7, 0, 7, 4,  // Cara izquierda
        1, 5, 6, 1, 6, 2,  // Cara derecha
        3, 2, 6, 3, 6, 7,  // Cara superior
        0, 4, 5, 0, 5, 1   // Cara inferior
    };

    // Inicializamos las normales
    calcularNormales();
}



void Cubo::draw() {
   // Aplicar transformaciones y configurar el estado de visualización
    glPushMatrix();
    aplicarTransformaciones();

    estadoVisualizacion.setModo(estadoVisualizacion.modo);        // Configuramos el modo (puntos, líneas o relleno)
    estadoVisualizacion.setSombreado(estadoVisualizacion.modoSombreado);  // Configuramos el modo de sombreado

    if (estadoVisualizacion.modoSombreado == GL_FLAT) {
        dibujarFlat();
    } else {
        dibujarSmooth();
    }

    glPopMatrix();
}
