#ifndef CUBO_H
#define CUBO_H

#include <vector>
//#include "objeto3d.h"
#include "practicasIG.h"


class Cubo : public Objeto3D {
public:
    Cubo(float lado);  // Constructor
    void draw() override;  // Implementación del método draw
};

#endif
