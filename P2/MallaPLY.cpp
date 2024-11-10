#include "MallaPLY.h"
#include <GL/gl.h>
#include <iostream>

MallaPLY::MallaPLY(const std::string& archivoPLY) {
    ply::read(archivoPLY.c_str(), vertices, caras);  // Convertir std::string a const char*
    calcularNormales();
}


void MallaPLY::draw() {
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
