#include "EstadoVisualizacion.h"
#include <stdio.h>

// Constructor que inicializa los valores por defecto
EstadoVisualizacion::EstadoVisualizacion() {
    modo = GL_FILL;  // Inicializa el modo de visualización como relleno
    iluminacionActivada = 1;  // Iluminación activada por defecto
    modoSombreado = GL_SMOOTH;  // Inicializa el modo de sombreado como SMOOTH
}

// Función para cambiar el modo de visualización
void EstadoVisualizacion::setModo(int M) {
    modo = M;
    glPointSize(5.0f);  // Configura el tamaño de los puntos
    glPolygonMode(GL_FRONT_AND_BACK, modo);  // Aplica el modo de visualización
}

// Función para cambiar el estado de la iluminación
void EstadoVisualizacion::setIluminacion(int estadoIluminacion) {
    iluminacionActivada = estadoIluminacion;
    if (iluminacionActivada) {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
    } else {
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHTING);
    }
}

// Función para cambiar el modo de sombreado (FLAT o SMOOTH)
void EstadoVisualizacion::setSombreado(int modoS) {
    modoSombreado = modoS;
    if (modoSombreado == GL_FLAT) {
        glShadeModel(GL_FLAT);
    } else if (modoSombreado == GL_SMOOTH) {
        glShadeModel(GL_SMOOTH);
    }

}