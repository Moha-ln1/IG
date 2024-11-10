#ifndef ESTADOVISUALIZACION_H
#define ESTADOVISUALIZACION_H

#include <GL/glut.h>

class EstadoVisualizacion {
public:
    int modo;
    int iluminacionActivada;

    EstadoVisualizacion();

    void setModo(int M);
    void setIluminacion(int estadoIluminacion);
};

// Declaramos una instancia global de EstadoVisualizacion
extern EstadoVisualizacion estado;

#endif

