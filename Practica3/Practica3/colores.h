#ifndef _COLORES
#define _COLORES

#include <GL/gl.h>

/*
  Constantes para colores, de 0 a 100% de las componentes RGB
    primer valor:  % de ROJO  (red)
    segunda valor: % de VERDE (green)
    tercer valor:  % de AZUL  (blue)
*/

const GLfloat ROJO[]={1.0,0.0,0.0}; //100% de ROJO, 0% de Verde, 0% de Azul
const GLfloat VERDE[]={0.0,1.0,0.0};
const GLfloat AZUL[]={0.0,0.0,1.0};
const GLfloat NEGRO[]={0.0,0.0,0.0};
const GLfloat AMARILLO[]={1.0,1.0,0};

const GLfloat GRIS_OSCURO[]={0.5,0.5,0.5};
const GLfloat GRIS_CLARO[]={0.8,0.8,0.8};

#endif
