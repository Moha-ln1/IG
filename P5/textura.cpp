#include "textura.h"
#include <iostream>
#include "lector-jpg.h" // Asegúrate de que esto esté incluido

Textura::Textura() : isLoadedToGL(false), textureId(0), data(nullptr), width(0), height(0) {}

Textura::~Textura() {
    if (isLoadedToGL) {
        glDeleteTextures(1, &textureId);
    }
    delete[] data; // Libera la memoria ocupada por los datos de la textura
}

void Textura::loadFromFile(const char* filename) {
    // Usamos la función que tienes para leer la imagen JPEG
    data = LeerArchivoJPEG(filename, width, height);
    if (!data) {
        std::cerr << "Error al cargar la textura: " << filename << std::endl;
        return;
    } else {
        std::cout << "Leyendo la textura " << filename << std::endl;
    }
}

void Textura::loadToOpenGL() {
    if (isLoadedToGL || !data) {
        return; // Ya se cargó o no hay datos de textura
    }

    // Generar un identificador para la textura en OpenGL
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // Configurar los parámetros de filtrado y envoltura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Interpolación al estar cerca de la cámara
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Interpolación al estar lejos de la cámara
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Limitar las coordenadas U fuera de los márgenes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Limitar las coordenadas V fuera de los márgenes

    // Cargar los datos de la textura en OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    // Desenlazar la textura para evitar modificaciones accidentales
    glBindTexture(GL_TEXTURE_2D, 0);

    // Marcar la textura como cargada en OpenGL
    isLoadedToGL = true;


}

void Textura::activar() {
    if (isLoadedToGL) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureId);
   }
}

bool Textura::esValida() const {
    return isLoadedToGL;
}
