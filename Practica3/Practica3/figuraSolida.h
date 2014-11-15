//***************************************************************************************************************
//  figuraSolida.h
//
//  Clase que hereda todos los atributos y m�todos de su padre figuraSimple.
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

        //Las figuras solidas necesitan un vector de caras con el que darle la topolog�a (conexi�n entre
        // v�rtices) al objeto.
        vector<_vertex3i> caras;

    public:

        //Funci�n que devuelve el n�mero de caras alojadas en el vector caras.
        int numeroCaras();

        //Funci�n para introducir a mano las caras del modelo
        void setCaraManual(unsigned int verticeA, unsigned int verticeB, unsigned int verticeC);

        void eliminarUltimaCara();

        //Funci�n que dibuja las caras ajustable a la secci�n y al modo de dibujado.
        void dibujarCaras(string seccion, string modo);

        //Funci�n que usando las caras dibuja las aristas y a la que tambi�n se le especifica secci�n.
        void dibujarAristas(string seccion);


};

#endif
