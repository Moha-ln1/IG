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
    printf("S: Cambiar a modo Sombreado Suave (SMOOTH)\n");
    printf("G: Cambiar a modo Sombreado Plano (FLAT)\n");
    printf("ESC: Salir\n");
    printf("\n\n\n");
}
/**************************************************************************/
// Manejo del teclado para cambiar el modo de visualización y la iluminación
/**************************************************************************/

// Inicializamos el índice del objeto seleccionado
extern int objetoSeleccionado;
extern std::vector<Objeto3D*> escena;


float rotxCamara = 30, rotyCamara = 45;
float dCamara = 10;
void letra(unsigned char k, int x, int y) {
    static bool sombreadoSuave1 = true;  // Para alternar el sombreado del primer objeto
    static bool sombreadoSuave2 = true;  // Para alternar el sombreado del segundo objeto

    switch (k) {
        case 'h':
        case 'H':
            printHelp();  // Imprimir ayuda
            break;
        case '+':  // Acerca la cámara
            dCamara -= 5.0;
            break;
        case '-':  // Aleja la cámara
            dCamara += 5.0;
            break;
        case 'P':
        case 'p':
            escena[objetoSeleccionado]->estadoVisualizacion.setModo(GL_POINT);
            printf("Modo de visualización cambiado a: PUNTOS\n");
            break;
        case 'L':
        case 'l':
            escena[objetoSeleccionado]->estadoVisualizacion.setModo(GL_LINE);
            printf("Modo de visualización cambiado a: LÍNEAS\n");
            break;
        case 'F':
        case 'f':
            escena[objetoSeleccionado]->estadoVisualizacion.setModo(GL_FILL);
            printf("Modo de visualización cambiado a: RELLENO\n");
            break;
        case 'I':
        case 'i':
            escena[objetoSeleccionado]->estadoVisualizacion.setIluminacion(
                !escena[objetoSeleccionado]->estadoVisualizacion.iluminacionActivada);
            printf("Iluminación %s\n", escena[objetoSeleccionado]->estadoVisualizacion.iluminacionActivada ? "ACTIVADA" : "DESACTIVADA");
            break;
        case 'S':
        case 's':
            // Alternar sombreado del primer objeto
            if (sombreadoSuave1) {
                escena[0]->estadoVisualizacion.setSombreado(GL_FLAT);
                printf("Modo de sombreado del objeto 1 cambiado a: PLANO (FLAT)\n");
            } else {
                escena[0]->estadoVisualizacion.setSombreado(GL_SMOOTH);
                printf("Modo de sombreado del objeto 1 cambiado a: SUAVE (SMOOTH)\n");
            }
            sombreadoSuave1 = !sombreadoSuave1;  // Cambia el estado para la próxima vez
            break;
        case 'G':
        case 'g':
            // Alternar sombreado del segundo objeto
            if (sombreadoSuave2) {
                escena[1]->estadoVisualizacion.setSombreado(GL_FLAT);
                printf("Modo de sombreado del objeto 2 cambiado a: PLANO (FLAT)\n");
            } else {
                escena[1]->estadoVisualizacion.setSombreado(GL_SMOOTH);
                printf("Modo de sombreado del objeto 2 cambiado a: SUAVE (SMOOTH)\n");
            }
            sombreadoSuave2 = !sombreadoSuave2;  // Cambia el estado para la próxima vez
            break;
        case '1':
            objetoSeleccionado = 0;
            printf("Objeto seleccionado: 1 (MallaPLY)\n");
            break;
        case '2':
            objetoSeleccionado = 1;
            printf("Objeto seleccionado: 2 (Cubo)\n");
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
