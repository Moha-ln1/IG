#include "objeto3d.h"
#include <cmath>
#include <iostream>
#include <string>

using namespace std;

Objeto3D::Objeto3D() {
    // Inicializamos las transformaciones por defecto
    posicion[0] = 0.0f; posicion[1] = 0.0f; posicion[2] = 0.0f;
    rotacion[0] = 0.0f; rotacion[1] = 0.0f; rotacion[2] = 0.0f;
    escala[0] = 1.0f;   escala[1] = 1.0f;   escala[2] = 1.0f;
}

Objeto3D::~Objeto3D() {}

void Objeto3D::inicializarTransformaciones(float posX, float posY, float posZ,
                                           float rotX, float rotY, float rotZ,
                                           float escX, float escY, float escZ) {
    // Asignamos los valores de traslación
    posicion[0] = posX; posicion[1] = posY; posicion[2] = posZ;

    // Asignamos los valores de rotación
    rotacion[0] = rotX; rotacion[1] = rotY; rotacion[2] = rotZ;

    // Asignamos los valores de escala
    escala[0] = escX; escala[1] = escY; escala[2] = escZ;
}

void Objeto3D::aplicarTransformaciones() {
    glTranslatef(posicion[0], posicion[1], posicion[2]);
    glRotatef(rotacion[0], 1.0f, 0.0f, 0.0f);  // Rotación en el eje X
    glRotatef(rotacion[1], 0.0f, 1.0f, 0.0f);  // Rotación en el eje Y
    glRotatef(rotacion[2], 0.0f, 0.0f, 1.0f);  // Rotación en el eje Z
    glScalef(escala[0], escala[1], escala[2]);
}

void Objeto3D::calcularNormales() {
    calcularNormalesPorCara();
    calcularNormalesPorVertice();
}

void Objeto3D::calcularNormalesPorCara() {
    normalesCaras.resize(caras.size(), 0.0f);
    for (size_t i = 0; i < caras.size(); i += 3) {
        int i0 = caras[i], i1 = caras[i + 1], i2 = caras[i + 2];
        float v0[3] = { vertices[i0 * 3], vertices[i0 * 3 + 1], vertices[i0 * 3 + 2] };
        float v1[3] = { vertices[i1 * 3], vertices[i1 * 3 + 1], vertices[i1 * 3 + 2] };
        float v2[3] = { vertices[i2 * 3], vertices[i2 * 3 + 1], vertices[i2 * 3 + 2] };

        // Producto vectorial para obtener la normal de la cara
        float normal[3];
        normal[0] = (v1[1] - v0[1]) * (v2[2] - v0[2]) - (v1[2] - v0[2]) * (v2[1] - v0[1]);
        normal[1] = (v1[2] - v0[2]) * (v2[0] - v0[0]) - (v1[0] - v0[0]) * (v2[2] - v0[2]);
        normal[2] = (v1[0] - v0[0]) * (v2[1] - v0[1]) - (v1[1] - v0[1]) * (v2[0] - v0[0]);

        // Normalizar la normal de la cara
        float length = sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
        if (length > 0.0f) {
            for (int j = 0; j < 3; j++) normal[j] /= length;
        }

        normalesCaras[i] = normal[0];
        normalesCaras[i + 1] = normal[1];
        normalesCaras[i + 2] = normal[2];
    }
}

void Objeto3D::calcularNormalesPorVertice() {
    normalesVertices.resize(vertices.size(), 0.0f);
    for (size_t i = 0; i < vertices.size(); i++) {
        normalesVertices[i] = 0.0f;
    }
    for (size_t i = 0; i < caras.size(); i += 3) {
        int i0 = caras[i], i1 = caras[i + 1], i2 = caras[i + 2];
        for (int j = 0; j < 3; j++) {
            normalesVertices[i0 * 3 + j] += normalesCaras[i + j];
            normalesVertices[i1 * 3 + j] += normalesCaras[i + j];
            normalesVertices[i2 * 3 + j] += normalesCaras[i + j];
        }
    }
    for (size_t i = 0; i < normalesVertices.size(); i += 3) {
        float length = sqrt(normalesVertices[i] * normalesVertices[i] +
                            normalesVertices[i + 1] * normalesVertices[i + 1] +
                            normalesVertices[i + 2] * normalesVertices[i + 2]);
        if (length > 0.0f) {
            normalesVertices[i] /= length;
            normalesVertices[i + 1] /= length;
            normalesVertices[i + 2] /= length;
        }
    }
}

void Objeto3D::dibujarFlat() {
    glShadeModel(GL_FLAT);
    glBegin(GL_TRIANGLES);
    for (size_t i = 0; i < caras.size(); i += 3) {
        glNormal3f(normalesCaras[i], normalesCaras[i + 1], normalesCaras[i + 2]);
        for (int j = 0; j < 3; j++) {
            int indiceVertice = caras[i + j];
            if (textura.esValida()) {
                // Ahora usamos directamente el par (u, v) sin cálculos adicionales
                glTexCoord2f(
                    coordenadasTextura[indiceVertice].first, 
                    coordenadasTextura[indiceVertice].second
                );
            }
            glVertex3f(
                vertices[indiceVertice * 3], 
                vertices[indiceVertice * 3 + 1], 
                vertices[indiceVertice * 3 + 2]
            );
        }
    }
    glEnd();
}


void Objeto3D::dibujarSmooth() {
    glShadeModel(GL_SMOOTH);
    glBegin(GL_TRIANGLES);
    for (size_t i = 0; i < caras.size(); i += 3) {
        for (int j = 0; j < 3; j++) {
            int indiceVertice = caras[i + j];
            glNormal3f(normalesVertices[indiceVertice * 3], normalesVertices[indiceVertice * 3 + 1], normalesVertices[indiceVertice * 3 + 2]);
            if (textura.esValida()) {               
                glTexCoord2f(
                    coordenadasTextura[indiceVertice].first, 
                    coordenadasTextura[indiceVertice].second
                );
            }
            glVertex3f(
                vertices[indiceVertice * 3], 
                vertices[indiceVertice * 3 + 1], 
                vertices[indiceVertice * 3 + 2]
            );
        }
    }
    glEnd();
}

bool Objeto3D::cargarTextura(const std::string& archivo) {
    textura.loadFromFile(archivo.c_str()); // Convierte std::string a const char*
    return textura.esValida();
}

void Objeto3D::cargarTexturaAOpenGL(){
    textura.loadToOpenGL(); // Cargar en OpenGL    
}

void Objeto3D::asignarMaterial(const Material& mat) {
    material = mat;
}


void Objeto3D::asignarCoordenadasUVDinamicas() {
    // Calcular los límites en Y para normalizar la altura de los vértices
    float minY = vertices[1], maxY = vertices[1];
    for (size_t i = 1; i < vertices.size(); i += 3) {
        if (vertices[i] < minY) minY = vertices[i];
        if (vertices[i] > maxY) maxY = vertices[i];
    }
    float altura = maxY - minY;

    coordenadasTextura.clear();
    for (size_t i = 0; i < vertices.size(); i += 3) {
        float x = vertices[i];
        float y = vertices[i + 1];
        float z = vertices[i + 2];

        // Calcular coordenada U como ángulo alrededor del eje Y
        float u = (atan2(z, x) + M_PI) / (2 * M_PI);

        // Calcular coordenada V en función de la altura normalizada en Y
        float v = (y - minY) / altura;

        coordenadasTextura.push_back({u, v});
    }
}