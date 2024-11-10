#ifndef MALLAPLY_H
#define MALLAPLY_H

#include <vector>
#include <string>
#include "practicasIG.h"

class MallaPLY : public Objeto3D {
public:
    MallaPLY(const std::string& archivoPLY);
    
    void draw() override;
};

#endif // MALLAPLY_H

