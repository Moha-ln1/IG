#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "practicasIG.h"

/** 
    Imprime en la consola las instrucciones del programa
**/
void printHelp() {
    printf("\n\n     Prácticas de Informática Gráfica   Curso 2023-2024");
    printf("\n\n Dpto. Lenguajes y Sistemas Informaticos");
    printf("\n E.T.S.I. Informatica       Univ. de Granada ");
    printf("\n");
    printf("\n Opciones: \n\n");
    printf("h, H: Imprime informacion de ayuda \n");
    printf("PgUp, PgDn: avanza y retrocede la cámara \n\n");
    printf("+, -: avanza y retrocede la cámara \n\n");
    printf("Teclas de movimiento de cursor: giran la camara\n");
    printf("P: Cambiar a modo Puntos\n");
    printf("L: Cambiar a modo Líneas\n");
    printf("F: Cambiar a modo Relleno\n");
    printf("I: Activar/Desactivar la iluminación\n");
    printf("ESC: Salir\n");
    printf("\n\n\n");
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
            printHelp();  // H y h imprimen ayuda
            break;
        case '+':  // Acerca la cámara
            dCamara -= 5.0;
            break;
        case '-':  // Aleja la cámara
            dCamara += 5.0;
            break;
        case 'P':
        case 'p':
            if (estado.modo != GL_POINT) {
                estado.setModo(GL_POINT);
                printf("Modo de visualización cambiado a: PUNTOS\n");
            }
            break;
        case 'L':
        case 'l':
            if (estado.modo != GL_LINE) {
                estado.setModo(GL_LINE);
                printf("Modo de visualización cambiado a: LÍNEAS\n");
            }
            break;
        case 'F':
        case 'f':
            if (estado.modo != GL_FILL) {
                estado.setModo(GL_FILL);
                printf("Modo de visualización cambiado a: RELLENO\n");
            }
            break;
        case 'I':
        case 'i':
            estado.setIluminacion(!estado.iluminacionActivada);
            printf("Iluminación %s\n", estado.iluminacionActivada ? "ACTIVADA" : "DESACTIVADA");
            break;
        case 27:  // Tecla ESC para salir
            exit(0);
        default:
            return;
    }
    glutPostRedisplay();  // Actualiza la visualización
}

/** 
    Manejo de teclas especiales
**/
void especial(int k, int x, int y) {
    switch (k) {
        case GLUT_KEY_UP:
            rotxCamara += 5.0;  // Cursor arriba + rotacion x
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
        case GLUT_KEY_PAGE_DOWN:  // Acerca la cámara
            dCamara -= 5.0;
            break;
        case GLUT_KEY_PAGE_UP:  // Aleja la cámara
            dCamara += 5.0;
            break;
        default:
            return;
    }
    setCamara(rotxCamara, rotyCamara, 0.0, dCamara);
    glutPostRedisplay();  // Actualiza la imagen
}
