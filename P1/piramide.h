#ifndef PIRAMIDE_H
#define PIRAMIDE_H

#include "modelo.h"

class Piramide: public Objeto3D {
public:
    float lado, altura;
    Piramide(float l, float h);
    void draw();
    void colorear(float color[4]);
    void dibujar(float color[4]);
};

#endif

