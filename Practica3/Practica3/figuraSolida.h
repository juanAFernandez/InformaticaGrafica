//***************************************************************************************************************
//  figuraSolida.h
//
//  Clase que hereda todos los atributos y métodos de su padre figuraSimple.
//
//***************************************************************************************************************

#ifndef _FIGURASOLIDA
#define _FIGURASOLIDA

//Al heredar de figuraSimple necesita conocerla:
#include "figuraSimple.h"
//Al incluir figuraSimple.h estamos incluyendo todos los include de la primera.


//La clase figuraSolida hereda de figuraSimple
class figuraSolida : public figuraSimple {

    protected:

        //Las figuras solidas necesitan un vector de caras con el que darle la topología (conexión entre
        // vértices) al objeto.
        vector<_vertex3i> caras;

    public:

        //Función que devuelve el número de caras alojadas en el vector caras.
        int numeroCaras();

        //Función para introducir a mano las caras del modelo
        void setCaraManual(unsigned int verticeA, unsigned int verticeB, unsigned int verticeC);

        void eliminarUltimaCara();

        //Función que dibuja las caras ajustable a la sección y al modo de dibujado.
        void dibujarCaras(string seccion, string modo);

        //Función que usando las caras dibuja las aristas y a la que también se le especifica sección.
        void dibujarAristas(string seccion);


};

#endif
