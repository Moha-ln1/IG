#ifndef ESTADOVISUALIZACION_H
#define ESTADOVISUALIZACION_H

#include <GL/glut.h>

class EstadoVisualizacion {
public:
    int modo;
    int iluminacionActivada;
    int modoSombreado;  // Modo de sombreado (GL_FLAT o GL_SMOOTH)


    EstadoVisualizacion();

    void setModo(int M);
    void setIluminacion(int estadoIluminacion);
    void setSombreado(int modoS);  

};

#endif

