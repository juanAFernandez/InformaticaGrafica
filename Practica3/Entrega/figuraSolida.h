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
        vector<_vertex3f> normales;
        vector<_vertex3f> normalesVertices;
        vector<_vertex3f> baricentros;

    private:

        _vertex3f productoVectorial(_vertex3f ab, _vertex3f ac);



    public:

        /**
        * @brief Constructor "vacío" de la clase.
        */
        figuraSolida(){}

        /**
        * @brief Constructor de la clase que envía el nombre de la figura al constructor de la clase padre.
        */
        figuraSolida(string nuevoNombre):figuraSimple(nuevoNombre){};

        /**
        * @brief Función que nos muestra en terminal las caras almacenadas en el vector de caras con un formato legible.
        */
        void muestraCaras();

        /**
        * @brief Función que devuelve el número de caras alojadas en el vector caras.
        */
        int numeroCaras();

        /**
        * @brief Para introducir caras de forma manual en el vector de caras.
        */
        void setCaraManual(unsigned int verticeA, unsigned int verticeB, unsigned int verticeC);

        /**
        * @brief Para eliminar la última cara de vector de caras.
        */
        void eliminarUltimaCara();

        /**
        * @brief Función que dibuja las caras ajustable a la sección y al modo de dibujado.
        * @param seccion
        * @param modo
        */
        void dibujarCaras(string seccion, string modo, const GLfloat color[]);

        /**
        * @brief Función para dibujar las aristas (conexiones entre dos puntos)
        * @param seccion La sección que queremos dibujar
        */
        void dibujarAristas(string seccion);


        void dibujarNormalesVertices();

        void dibujarNormales();

        void calculaNormalesVertices();

        void calculaNormalesCaras();
        void dibujaBaricentros();
        void calculaBaricentrosCaras();


        void muestraNormales();


        void prueba(GLfloat color){
            cout << "All right!";
        }



        _vertex3f getNormal(int pos){

            return normales[pos];

        }

        _vertex3f getBaricentro(int pos){
            return baricentros[pos];
        }





};

#endif
