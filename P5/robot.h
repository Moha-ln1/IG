#ifndef ROBOT_H
#define ROBOT_H

#include "objeto3d.h"
#include "practicasIG.h"
#include "cubo.h"

class Cabeza : public Objeto3D {
public:
    Cabeza();
    void draw() override;
};

class Brazo : public Objeto3D {
public:
    Brazo(float posicionX);
    void draw() override;
};

class Pierna : public Objeto3D {
public:
    Pierna(float posicionX);
    void draw() override;
};

class Robot : public Objeto3D {
public:
    Cabeza cabeza;
    Brazo brazoDerecho;
    Brazo brazoIzquierdo;
    Pierna piernaDerecha;
    Pierna piernaIzquierda;
    


    Robot();

    void draw() override;
    void cabezaLeft();
    void cabezaRight();
    void brazoDerechoArriba();
    void brazoDerechoAbajo();
    void brazoIzquierdoArriba();
    void brazoIzquierdoAbajo();
    void piernaDerechaAdelante();
    void piernaDerechaAtras();
    void piernaIzquierdaAdelante();
    void piernaIzquierdaAtras();
    void reset();
};

#endif
