#ifndef MATERIAL_H
#define MATERIAL_H

#include <array>
#include <GL/glut.h>

class Material {
public:
    std::array<GLfloat, 4> ambient;    // Color ambiental (RGBA)
    std::array<GLfloat, 4> diffuse;    // Color difuso (RGBA)
    std::array<GLfloat, 4> specular;   // Color especular (RGBA)
    GLfloat shininess;                 // Brillo

    Material();
    Material(const std::array<GLfloat, 4>& ambient,
             const std::array<GLfloat, 4>& diffuse,
             const std::array<GLfloat, 4>& specular,
             GLfloat shininess);

    void aplicar();  // Aplica el material en OpenGL
};

#endif // MATERIAL_H
