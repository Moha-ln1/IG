#ifndef OBJETO3D_H
#define OBJETO3D_H

#include <vector>
#include <GL/glut.h>
#include "EstadoVisualizacion.h"
#include "textura.h"  // Incluir la clase Textura
#include "material.h"

class Objeto3D {
public:
    std::vector<float> vertices;  // Coordenadas de los vértices
    std::vector<int> caras;       // Índices de los triángulos
    std::vector<float> normalesVertices; // Normales por vértice
    std::vector<float> normalesCaras;    // Normales por triángulo
    std::vector<std::pair<float, float>> coordenadasTextura;

    Textura textura;  // Instancia de Textura para gestionar la textura
    Material material;  // Instancia de Material para gestionar el material

    float posicion[3];  // Vector de traslación (x, y, z)
    float rotacion[3];  // Vector de rotación (ángulos en grados para x, y, z)
    float escala[3];    // Vector de escala (x, y, z)

    EstadoVisualizacion estadoVisualizacion;

    Objeto3D();
    virtual ~Objeto3D();

    // Método que aplicará las transformaciones
    void aplicarTransformaciones();

    // Función auxiliar para inicializar las transformaciones
    void inicializarTransformaciones(float posX, float posY, float posZ,
                                     float rotX, float rotY, float rotZ,
                                     float escX, float escY, float escZ);

    // Métodos para cálculo de normales (por caras y vértices)
    void calcularNormales();
    void calcularNormalesPorCara();
    void calcularNormalesPorVertice();

    // Métodos de dibujado
    void dibujarFlat();
    void dibujarSmooth();

    // Cargar textura desde archivo JPG
    bool cargarTextura(const std::string& archivo);
    void cargarTexturaAOpenGL();
       
    void asignarCoordenadasUVDinamicas();  // Nueva función para el mapeo dinámico de UV
 
    // Nuevo método para asignar un material
    void asignarMaterial(const Material& mat);

    // Método virtual para dibujar (será implementado por las clases derivadas)
    virtual void draw() = 0;
};

#endif // OBJETO3D_H
