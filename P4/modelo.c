#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <GL/glut.h>    // Libreria de utilidades de OpenGL
#include "practicasIG.h"
#include "robot.h"
#include "material.h"

// Definimos las escenas como un vector de punteros a Objeto3D
std::vector<Objeto3D*> escena1; // Escena con cubo y objeto PLY
std::vector<Objeto3D*> escena2; // Escena con el robot
std::vector<Objeto3D*> escena3; // Nueva escena con un cubo con textura

// Índice de la escena seleccionada
int escenaSeleccionada = 1;

// Instancia del modelo PLY y del cubo
MallaPLY modeloPLY("./ply_models/ant.ply");
Cubo cubo(10.0f);
Robot robot;

// Cubo con textura y su material
Cubo cuboConTextura(10.0f);

// Declaraciones globales (en un archivo de encabezado o en el archivo de implementación)
MallaPLY beethovenRojo("./ply_models/beethoven.ply");
MallaPLY beethovenVerde("./ply_models/beethoven.ply");
MallaPLY beethovenAzul("./ply_models/beethoven.ply");
MallaPLY beethovenMadera("./ply_models/beethoven.ply");
   
// Definición de materiales
Material materialRojo(
    {0.3f, 0.0f, 0.0f, 1.0f},  // Ambiental
    {0.8f, 0.0f, 0.0f, 1.0f},  // Difuso
    {1.0f, 1.0f, 1.0f, 1.0f},  // Especular
    50.0f                      // Brillo
);

Material materialVerde(
    {0.0f, 0.3f, 0.0f, 1.0f},
    {0.0f, 0.8f, 0.0f, 1.0f},
    {1.0f, 1.0f, 1.0f, 1.0f},
    50.0f
);

Material materialAzul(
    {0.0f, 0.0f, 0.3f, 1.0f},
    {0.0f, 0.0f, 0.8f, 1.0f},
    {1.0f, 1.0f, 1.0f, 1.0f},
    50.0f
);


// Estado de visualización global
EstadoVisualizacion estadoGlobal;

void initModel() {
    printf("Inicializando el modelo y las variables globales...\n");

    // Configuración de la luz 1 (GL_LIGHT0)
    GLfloat light0_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat light0_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat light0_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

    // Configuración de la luz 2 (GL_LIGHT1)
    GLfloat light1_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat light1_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat light1_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);

    // Configuración de la luz 3 (GL_LIGHT2) ubicada arriba de la escena
    GLfloat light2_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat light2_diffuse[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat light2_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat posLight2[] = { 0.0f, 30.0f, 0.0f, 1.0f }; // Luz desde arriba, sobre el Beethoven de madera
    glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
    glLightfv(GL_LIGHT2, GL_POSITION, posLight2);



    // Inicializar las escenas
    cubo.inicializarTransformaciones(25.0f, 0.0f, 0.0f, 0, 0, 0, 1.0f, 1.0f, 1.0f); 
    escena1.push_back(&cubo);
    escena1.push_back(&modeloPLY);
    robot.inicializarTransformaciones(0.0f, 0.0f, 0.0f, 0, 0, 0, 3.0f, 3.0f, 3.0f);
    escena2.push_back(&robot);

    // Añadir el cubo con textura al centro
    cuboConTextura.cargarTextura("textures/dado.jpg");
    cuboConTextura.inicializarTransformaciones(0.0f, 0.0f, 0.0f, 0, 0, 0, 1.0f, 1.0f, 1.0f); // Tamaño y posición central
    escena3.push_back(&cuboConTextura);

    // Tamaño uniforme para los modelos de Beethoven en la base
    float escalaBeethoven = 1.5f;

    // Configuración de materiales y posiciones para formar un triángulo alrededor del cubo
    beethovenRojo.asignarMaterial(materialRojo);
    beethovenVerde.asignarMaterial(materialVerde);
    beethovenAzul.asignarMaterial(materialAzul);

    // Distancia aumentada para una formación de base en forma de triángulo más amplia
    beethovenRojo.inicializarTransformaciones(-20.0f, 0.0f, -20.0f, 0, 0, 0, escalaBeethoven, escalaBeethoven, escalaBeethoven);
    beethovenVerde.inicializarTransformaciones(20.0f, 0.0f, -20.0f, 0, 0, 0, escalaBeethoven, escalaBeethoven, escalaBeethoven);
    beethovenAzul.inicializarTransformaciones(0.0f, 0.0f, 20.0f, 0, 0, 0, escalaBeethoven, escalaBeethoven, escalaBeethoven);

    // Añadir los modelos de Beethoven a la escena como base de la pirámide
    escena3.push_back(&beethovenRojo);
    escena3.push_back(&beethovenVerde);
    escena3.push_back(&beethovenAzul);

    // Configurar el modelo de Beethoven de madera en la punta de la pirámide
    beethovenMadera.cargarTextura("textures/madera.jpg"); // Cargar textura de madera
    beethovenMadera.asignarCoordenadasUVDinamicas();
    beethovenMadera.inicializarTransformaciones(0.0f, 25.0f, 0.0f, 0, 0, 0, escalaBeethoven, escalaBeethoven, escalaBeethoven); // Elevado sobre el cubo

    // Añadir el modelo de Beethoven de madera a la escena
    escena3.push_back(&beethovenMadera);

    estadoGlobal.setModo(GL_FILL); // Modo de dibujo por defecto
    estadoGlobal.setIluminacion(true);
}



/**************************************************************************/
//  Implementación de los ejes.
/**************************************************************************/
class Ejes : public Objeto3D {
public:
    float longitud = 30;
    void draw() override {
        glDisable(GL_LIGHTING);
        glBegin(GL_LINES);
        {
            glColor3f(0, 1, 0);
            glVertex3f(0, 0, 0);
            glVertex3f(0, longitud, 0);

            glColor3f(1, 0, 0);
            glVertex3f(0, 0, 0);
            glVertex3f(longitud, 0, 0);

            glColor3f(0, 0, 1);
            glVertex3f(0, 0, 0);
            glVertex3f(0, 0, longitud);
        }
        glEnd();
        glEnable(GL_LIGHTING);
    }
};

Ejes ejesCoordenadas;

/**************************************************************************/
//  Función de dibujo
/**************************************************************************/
void Dibuja(void) {
    // Posiciones de las luces
    static GLfloat posLight0[4] = { 5.0f, 5.0f, 10.0f, 1.0f };
    static GLfloat posLight1[4] = { -5.0f, 10.0f, -10.0f, 1.0f };
    static GLfloat posLight2[4] = { 0.0f, 30.0f, 0.0f, 1.0f }; // Luz superior

    glPushMatrix();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    transformacionVisualizacion();

    // Establecer posiciones de las luces
    glLightfv(GL_LIGHT0, GL_POSITION, posLight0);
    glLightfv(GL_LIGHT1, GL_POSITION, posLight1);
    glLightfv(GL_LIGHT2, GL_POSITION, posLight2); 

    // Dibujar ejes de coordenadas sin iluminación
    glDisable(GL_LIGHTING);
    ejesCoordenadas.draw();

    // Seleccionar la escena actual en función del índice seleccionado
    std::vector<Objeto3D*>* escenaActual;
    if (escenaSeleccionada == 1) {
        escenaActual = &escena1;
    } else if (escenaSeleccionada == 2) {
        escenaActual = &escena2;
    } else if (escenaSeleccionada == 3) {
        escenaActual = &escena3; 
    }

    // Activar o desactivar las luces en función del estado de iluminación global
    if (estadoGlobal.iluminacionActivada) {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
        glEnable(GL_LIGHT2); 
    } else {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
        glDisable(GL_LIGHT2);
    }

    // Dibujar cada objeto en la escena
    for (Objeto3D* obj : *escenaActual) {
        obj->estadoVisualizacion = estadoGlobal;

        if (escenaSeleccionada == 3) {
            obj->cargarTexturaAOpenGL();
        }

        obj->draw();
    }

    glPopMatrix();
    glutSwapBuffers();
}


void animacion(int value) {
    // Movimiento de brazos
    static int brazoDerechoDireccion = 1;
    static int brazoIzquierdoDireccion = -1;
    
    // Movimiento de piernas
    static int piernaDerechaDireccion = 1;
    static int piernaIzquierdaDireccion = -1;

    // Movimiento de los brazos: sincronizar brazos opuestos
    if (brazoDerechoDireccion == 1) {
        robot.brazoDerechoArriba();
        if (robot.brazoDerecho.rotacion[0] <= -45.0f) {
            brazoDerechoDireccion = -1;
        }
    } else {
        robot.brazoDerechoAbajo();
        if (robot.brazoDerecho.rotacion[0] >= 0.0f) {
            brazoDerechoDireccion = 1;
        }
    }

    if (brazoIzquierdoDireccion == -1) {
        robot.brazoIzquierdoArriba();
        if (robot.brazoIzquierdo.rotacion[0] <= -45.0f) {
            brazoIzquierdoDireccion = 1;
        }
    } else {
        robot.brazoIzquierdoAbajo();
        if (robot.brazoIzquierdo.rotacion[0] >= 0.0f) {
            brazoIzquierdoDireccion = -1;
        }
    }

    // Movimiento de las piernas: sincronizar piernas opuestas
    if (piernaDerechaDireccion == 1) {
        robot.piernaDerechaAdelante();
        if (robot.piernaDerecha.rotacion[0] >= 30.0f) {
            piernaDerechaDireccion = -1;
        }
    } else {
        robot.piernaDerechaAtras();
        if (robot.piernaDerecha.rotacion[0] <= -30.0f) {
            piernaDerechaDireccion = 1;
        }
    }

    if (piernaIzquierdaDireccion == -1) {
        robot.piernaIzquierdaAdelante();
        if (robot.piernaIzquierda.rotacion[0] >= 30.0f) {
            piernaIzquierdaDireccion = 1;
        }
    } else {
        robot.piernaIzquierdaAtras();
        if (robot.piernaIzquierda.rotacion[0] <= -30.0f) {
            piernaIzquierdaDireccion = -1;
        }
    }

    // Movimiento de la cabeza: de lado a lado
    static int direccionCabeza = 1;
    if (direccionCabeza == 1) {
        robot.cabezaLeft();
        if (robot.cabeza.rotacion[1] >= 15.0f) {
            direccionCabeza = -1;
        }
    } else {
        robot.cabezaRight();
        if (robot.cabeza.rotacion[1] <= -15.0f) {
            direccionCabeza = 1;
        }
    }

    // Redibuja y establece un temporizador para la siguiente animación
    glutPostRedisplay();
    glutTimerFunc(30, animacion, 0);
}



void idle(int v) {
    glutPostRedisplay();
    glutTimerFunc(30, idle, 0);
}
