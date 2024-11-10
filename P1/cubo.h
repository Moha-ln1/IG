#ifndef CUBO_H
#define CUBO_H


#include "modelo.h"

class Cubo: public Objeto3D {
public:
    float lado;
    Cubo(float l);
    void draw();
    void colorear(float color[4]);
    void dibujar(float color[4]);
};

#endif

