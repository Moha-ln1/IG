#include "MallaPLY.h"
#include <GL/gl.h>
#include <iostream>

MallaPLY::MallaPLY(const std::string& archivoPLY) {
    ply::read(archivoPLY.c_str(), vertices, caras);  // Convertir std::string a const char*
    calcularNormales();
}

void MallaPLY::draw() {

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
