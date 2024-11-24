#include <stdio.h>
#include <GL/glut.h>
#include "practicasIG.h"
#include "robot.h"
#include "modelo.h"

// Variables externas para compartir entre archivos
extern int escenaSeleccionada;
extern EstadoVisualizacion estadoGlobal;
extern Objeto3D* objetoSeleccionado;
extern Robot robot;
extern bool modoSeleccion;

/** 
    Imprime en la consola las instrucciones del programa
**/
void printHelp() {
    printf("\n\n     Prácticas de Informática Gráfica   Curso 2023-2024");
    printf("\n\n Dpto. Lenguajes y Sistemas Informaticos");
    printf("\n E.T.S.I. Informatica       Univ. de Granada ");
    printf("\n");
    printf("\n Opciones: \n\n");
    printf("h, H: Imprime información de ayuda \n");
    printf("1: Activar escena 1 (cubo y objeto PLY)\n");
    printf("2: Activar escena 2 (robot)\n");
    printf("3: Activar escena 3 (cubo con textura y modelos con materiales)\n");
    printf("PgUp, PgDn: Avanza y retrocede la cámara \n");
    printf("+, -: Acerca o aleja la cámara\n");
    printf("Teclas de movimiento de cursor: Giran la cámara\n");
    printf("P: Cambiar a modo Puntos\n");
    printf("L: Cambiar a modo Líneas\n");
    printf("F: Cambiar a modo Relleno\n");
    printf("I: Activar/Desactivar la iluminación\n");
    printf("t: Cambiar a sombreado plano (Flat)\n");
    printf("T: Cambiar a sombreado suave (Smooth)\n");
    printf("y, Y: Alterna entre sombreado Flat y Smooth\n");
    printf("C: Girar la cabeza a la izquierda\n");
    printf("V: Girar la cabeza a la derecha\n");
    printf("Q: Mover brazo derecho hacia arriba\n");
    printf("A: Mover brazo derecho hacia abajo\n");
    printf("W: Mover brazo izquierdo hacia arriba\n");
    printf("S: Mover brazo izquierdo hacia abajo\n");
    printf("Z: Mover pierna derecha hacia adelante\n");
    printf("X: Mover pierna derecha hacia atrás\n");
    printf("E: Mover pierna izquierda hacia adelante\n");
    printf("R: Mover pierna izquierda hacia atrás\n");
    printf("0: Activar animación del robot\n");
    printf("ESC: Salir\n");
}

/**************************************************************************/
// Manejo del teclado para cambiar el modo de visualización y la iluminación
/**************************************************************************/

float rotxCamara = 30, rotyCamara = 45;
float dCamara = 10;


void letra(unsigned char k, int x, int y) {

    switch (k) {
        case 'h':
        case 'H':
            printHelp();
            break;
        case '1':
            escenaSeleccionada = 1;
            printf("Escena 1 seleccionada\n");
            break;
        case '2':
            escenaSeleccionada = 2;
            printf("Escena 2 seleccionada (Robot)\n");
            break;
        case '3':
            escenaSeleccionada = 3;
            printf("Escena 3 seleccionada (Cubo con Textura)\n");
            break;
        case '+':
            dCamara -= 5.0;
            break;
        case '-':
            dCamara += 5.0;
            break;
        case 'p':  // Visualización en Puntos
            estadoGlobal.setModo(GL_POINT);
            printf("Modo de visualización cambiado a: PUNTOS\n");
            break;
        case 'l':  // Visualización en Líneas
            estadoGlobal.setModo(GL_LINE);
            printf("Modo de visualización cambiado a: LÍNEAS\n");
            break;
        case 'f':  // Visualización en Relleno
            estadoGlobal.setModo(GL_FILL);
            printf("Modo de visualización cambiado a: RELLENO\n");
            break;
        case 'y':  // Alternar sombreado
            estadoGlobal.setSombreado(estadoGlobal.modoSombreado == GL_FLAT ? GL_SMOOTH : GL_FLAT);
            break;
        case 'i':  // Alternar iluminación
            estadoGlobal.setIluminacion(!estadoGlobal.iluminacionActivada);
            printf("Iluminación %s\n", estadoGlobal.iluminacionActivada ? "ACTIVADA" : "DESACTIVADA");
            break;
        case 'u': // Cambia el modo de sombreado a Flat
            estadoGlobal.setSombreado(GL_FLAT);
            printf("Modo de sombreado cambiado a FLAT para la escena\n");
            break;
        case 'U': // Cambia el modo de sombreado a Smooth
            estadoGlobal.setSombreado(GL_SMOOTH);
            printf("Modo de sombreado cambiado a SMOOTH para la escena\n");
            break;

        // Transformaciones del objeto seleccionado
        case 'm': // Trasladar en +X
            if (objetoSeleccionado) {
                objetoSeleccionado->posicion[0] += 1.0f;
                printf("Objeto trasladado en +X\n");
            }
            break;
        case 'M': // Trasladar en -X
            if (objetoSeleccionado) {
                objetoSeleccionado->posicion[0] -= 1.0f;
                printf("Objeto trasladado en -X\n");
            }
            break;
        case 'b': // Rotar en +Y
            if (objetoSeleccionado) {
                objetoSeleccionado->rotacion[1] += 15.0f;
                printf("Objeto rotado en +Y\n");
            }
            break;
        case 'B': // Rotar en -Y
            if (objetoSeleccionado) {
                objetoSeleccionado->rotacion[1] -= 15.0f;
                printf("Objeto rotado en -Y\n");
            }
            break;
        case 'n': // Escalar más grande
            if (objetoSeleccionado) {
                objetoSeleccionado->escala[0] *= 1.1f;
                objetoSeleccionado->escala[1] *= 1.1f;
                objetoSeleccionado->escala[2] *= 1.1f;
                printf("Objeto escalado\n");
            }
            break;
        case 'N': // Escalar más pequeño
            if (objetoSeleccionado) {
                objetoSeleccionado->escala[0] *= 0.9f;
                objetoSeleccionado->escala[1] *= 0.9f;
                objetoSeleccionado->escala[2] *= 0.9f;
                printf("Objeto reducido\n");
            }
            break;

        // Movimientos del robot usando los métodos de la clase Robot
        case 'c':
            robot.cabezaLeft();
            printf("Cabeza girada a la izquierda\n");
            break;
        case 'v':
            robot.cabezaRight();
            printf("Cabeza girada a la derecha\n");
            break;
        case 'q': // Brazo derecho hacia arriba
            robot.brazoDerechoArriba();
            printf("Brazo derecho hacia arriba\n");
            break;
        case 'a': // Brazo derecho hacia abajo
            robot.brazoDerechoAbajo();
            printf("Brazo derecho hacia abajo\n");
            break;
        case 'w': // Brazo izquierdo hacia arriba
            robot.brazoIzquierdoArriba();
            printf("Brazo izquierdo hacia arriba\n");
            break;
        case 's': // Brazo izquierdo hacia abajo
            robot.brazoIzquierdoAbajo();
            printf("Brazo izquierdo hacia abajo\n");
            break;
        case 'z': // Pierna derecha hacia adelante
            robot.piernaDerechaAdelante();
            printf("Pierna derecha hacia adelante\n");
            break;
        case 'x': // Pierna derecha hacia atrás
            robot.piernaDerechaAtras();
            printf("Pierna derecha hacia atrás\n");
            break;
        case 'e': // Pierna izquierda hacia adelante
            robot.piernaIzquierdaAdelante();
            printf("Pierna izquierda hacia adelante\n");
            break;
        case 'r': // Pierna izquierda hacia atrás
            robot.piernaIzquierdaAtras();
            printf("Pierna izquierda hacia atrás\n");
            break;
        case '0':
            glutTimerFunc(30, animacion, 0);
            printf("Animación activada\n");
            break;

        case 27:
            exit(0);
        default:
            return;
    }
    glutPostRedisplay();
}

/**************************************************************************/
// Manejo de teclas especiales para mover la cámara
/**************************************************************************/
void especial(int k, int x, int y) {
    switch (k) {
        case GLUT_KEY_UP:
            rotxCamara += 5.0;
            if (rotxCamara > 360)
                rotxCamara -= 360;
            break;
        case GLUT_KEY_DOWN:
            rotxCamara -= 5.0;
            if (rotxCamara < 0)
                rotxCamara += 360;
            break;
        case GLUT_KEY_LEFT:
            rotyCamara += 5.0;
            if (rotyCamara > 360)
                rotyCamara -= 360;
            break;
        case GLUT_KEY_RIGHT:
            rotyCamara -= 5.0;
            if (rotyCamara < 0)
                rotyCamara += 360;
            break;
        case GLUT_KEY_PAGE_DOWN:
            dCamara -= 5.0;
            break;
        case GLUT_KEY_PAGE_UP:
            dCamara += 5.0;
            break;
        default:
            return;
    }
    setCamara(rotxCamara, rotyCamara, 0.0, dCamara);
    glutPostRedisplay();
}

void mouseFunc(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        modoSeleccion = true;
        Dibuja();  // Renderizar en modo selección

        // Procesar selección en la posición del clic
        procesarSeleccion(x, y);

        // Salir del modo de selección y redibujar en modo normal
        modoSeleccion = false;
        Dibuja();
    }
}
