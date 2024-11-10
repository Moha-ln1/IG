#ifndef PIRAMIDE_H
#define PIRAMIDE_H

#include <vector>
#include "objeto3d.h"

class Piramide : public Objeto3D {
public:
    Piramide(float lado, float altura);  
    
    void draw() override; 
};

#endif
