//***************************************************************************************************************
//  figuraSimple.h
//
//  Esta clase es la figura m�s simple que podemos tener. Se trata de un conjunto de v�rtices cuyos �nicos m�todos
//  son introducir v�rtices de forma manual, obtener el n�mero de esos v�rtices y dibujar la figura.
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
        * @brief Para introducir un v�rtice de forma manual al vector de v�rtices.
        * @param x Coordenada x del v�rtice.
        * @param y Coordenada y del v�rtice.
        * @param z Coordeanda z del v�rtice.
        */
        void setVerticeManual(GLfloat x, GLfloat y, GLfloat z);

        /**
        * @brief Para conocer el n�mero de v�rtices almacenados en el vector "vertices".
        * @return Devuelve el n�mero de v�rtices, un entero.
        */
        int numeroVertices();

        /**
        * @brief Para pintar los dibujar los vertices.
        * @param seccion Con este par�metro podemos configurar que secci�n de que eje dibujar. Acepta 7 par�metros distintos:
        * 1. "todo"    : Dibuja todas los v�rtices sin excepci�n.
        * 2. "solo x+" : Dibuja s�lo los v�rtices que se encuentran el parte positiva del eje X
        * 3. "solo x-" : Dibuja s�lo los v�rtices que se encuentran el parte negativa del eje X
        * 4. "solo y+" : Dibuja s�lo los v�rtices que se encuentran el parte positiva del eje Y
        * 5. "solo y-" : Dibuja s�lo los v�rtices que se encuentran el parte negativa del eje Y
        * 6. "solo z+" : Dibuja s�lo los v�rtices que se encuentran el parte positiva del eje Z
        * 7. "solo z-" : Dibuja s�lo los v�rtices que se encuentran el parte negativa del eje Z
        */
        void dibujarVertices(string seccion);

};

#endif
