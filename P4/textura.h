#ifndef TEXTURA_H
#define TEXTURA_H

#include <GL/glut.h>
#include <string>

class Textura {
public:
    GLuint textureId;      // ID de la textura
    bool isLoadedToGL;     // Indica si la textura ha sido cargada en OpenGL
    unsigned char* data;   // Datos de la textura
    unsigned width, height; // Dimensiones de la textura

    Textura();
    ~Textura();

    // Cargar la textura desde un archivo
    void loadFromFile(const char* filename);

    // Cargar la textura en OpenGL
    void loadToOpenGL();

    void activar();
    bool esValida() const;
};

#endif // TEXTURA_H
