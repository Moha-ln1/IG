#ifndef MODELO_H
#define MODELO_H

// Incluye el archivo de encabezado que contiene la definición de Objeto3D, o usa una declaración anticipada
#include "objeto3d.h" // Asegúrate de que esta es la ubicación correcta de la definición de Objeto3D

// Si no puedes incluir el archivo que define Objeto3D, utiliza una declaración anticipada:
// class Objeto3D;

/**
	Funcion de redibujado. Se ejecuta con los eventos postRedisplay
**/
void Dibuja(void);

/**
	Funcion de fondo
**/
void idle(int v);

/**
	Funcion de inicializacion del modelo y de las variables globales
**/
void initModel(void);

/**
	Cambia el modo de visualización (GL_POINT, GL_LINE, GL_FILL).
	@param M: Modo de visualización que se aplicará.
**/
void setModo(int M);

/**
	Activa o desactiva la iluminación de la escena.
	@param estado: Si es 1, la iluminación se activará. Si es 0, se desactivará.
**/
void setIluminacion(int estado);

void animacion(int value);

void procesarSeleccion(int x, int y);
void asignarColoresSeleccion(void);
void manejarSeleccion(Objeto3D* objeto);

#endif
