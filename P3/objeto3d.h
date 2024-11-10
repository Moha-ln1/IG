#ifndef OBJETO3D_H
#define OBJETO3D_H

#include <vector>
#include "EstadoVisualizacion.h"

class Objeto3D {
public:
    std::vector<float> vertices;  // Coordenadas de los vértices
    std::vector<int> caras;       // Índices de los triángulos
    std::vector<float> normalesVertices; // Normales por vértice
    std::vector<float> normalesCaras;    // Normales por triángulo

    float posicion[3];  // Vector de traslación (x, y, z)
    float rotacion[3];  // Vector de rotación (ángulos en grados para x, y, z)
    float escala[3];    // Vector de escala (x, y, z)

    EstadoVisualizacion estadoVisualizacion;
    Objeto3D();

    // Método que aplicará las transformaciones
    void aplicarTransformaciones();

    // Función auxiliar para inicializar las transformaciones
    void inicializarTransformaciones(float posX, float posY, float posZ,
                                     float rotX, float rotY, float rotZ,
                                     float escX, float escY, float escZ);



    // Cálculo de normales (por caras y vértices)
    void calcularNormales();
    void calcularNormalesPorCara();
    void calcularNormalesPorVertice();


    void dibujarFlat();  // Función de dibujado en modo FLAT
    void dibujarSmooth();  // Función de dibujado en modo SMOOTH
    // Método virtual para dibujar (será implementado por las clases derivadas)
    virtual void draw() = 0;
};

#endif
