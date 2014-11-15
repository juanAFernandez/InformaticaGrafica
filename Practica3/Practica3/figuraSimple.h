//***************************************************************************************************************
//  figuraSimple.h
//
//  Esta clase es la figura más simple que podemos tener. Se trata de un conjunto de vértices cuyos únicos métodos
//  son introducir vértices de forma manual, obtener el número de esos vértices y dibujar la figura.
//
//***************************************************************************************************************
#ifndef _FIGURASIMPLE
#define _FIGURASIMPLE

//Para poder usar los tipos de OpenGl:
#include <GL/gl.h>
//Para poder usar el vector de la STL:
#include <vector>
//Para poder usar los tipos de datos vertex:
#include "vertex.h"
//Para poder usar los colores que nosotros hemos definido:
#include "colores.h"

using namespace std;

class figuraSimple{

    //Protected para que sin ser visible fuera de las clases pueda ser directamente accesible desde las clases hijas.
    protected:

        //Vector de vertices usando "vector" de la STL y el tipo vertex.h
        vector<_vertex3f> vertices; /** < vector de vertices del tipo _vertex3f de "vertex.h" usando "vector" de la STL para almacenarlos*/

    public:

        /**
        * @brief Para introducir un vértice de forma manual al vector de vértices.
        * @param x Coordenada x del vértice.
        * @param y Coordenada y del vértice.
        * @param z Coordeanda z del vértice.
        */
        void setVerticeManual(GLfloat x, GLfloat y, GLfloat z);

        /**
        * @brief Para conocer el número de vértices almacenados en el vector "vertices".
        * @return Devuelve el número de vértices, un entero.
        */
        int numeroVertices();

        /**
        * @brief Para pintar los dibujar los vertices.
        * @param seccion Con este parámetro podemos configurar que sección de que eje dibujar. Acepta 7 parámetros distintos:
        * 1. "todo"    : Dibuja todas los vértices sin excepción.
        * 2. "solo x+" : Dibuja sólo los vértices que se encuentran el parte positiva del eje X
        * 3. "solo x-" : Dibuja sólo los vértices que se encuentran el parte negativa del eje X
        * 4. "solo y+" : Dibuja sólo los vértices que se encuentran el parte positiva del eje Y
        * 5. "solo y-" : Dibuja sólo los vértices que se encuentran el parte negativa del eje Y
        * 6. "solo z+" : Dibuja sólo los vértices que se encuentran el parte positiva del eje Z
        * 7. "solo z-" : Dibuja sólo los vértices que se encuentran el parte negativa del eje Z
        */
        void dibujarVertices(string seccion);

};

#endif
