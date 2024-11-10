#include "material.h"

Material::Material() 
    : ambient{0.2f, 0.2f, 0.2f, 1.0f},
      diffuse{0.8f, 0.8f, 0.8f, 1.0f},
      specular{0.0f, 0.0f, 0.0f, 1.0f},
      shininess(0.0f) {}

Material::Material(const std::array<GLfloat, 4>& amb,
                   const std::array<GLfloat, 4>& diff,
                   const std::array<GLfloat, 4>& spec,
                   GLfloat shine)
    : ambient(amb), diffuse(diff), specular(spec), shininess(shine) {}

void Material::aplicar() {
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient.data());
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse.data());
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular.data());
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}
