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
#include "material.h"


//Al incluir figuraSimple.h estamos incluyendo todos los include de la primera.


//La clase figuraSolida hereda de figuraSimple
class figuraSolida : public figuraSimple {

    protected:

        vector<_vertex3i> caras;
        vector<_vertex3f> normales;
        vector<_vertex3f> normalesVertices;
        vector<_vertex3f> baricentros;

        //Textura:

        GLuint texName; //Textura
        vector<_vertex2f> cTs; //Coordenadas de textura

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


        void dibujarCarasIluminacionPlana(material materialParaAplicar);

        void dibujarCarasIluminacionSuave(material materialParaAplicar);


        /**
        * @brief Función para dibujar las aristas (conexiones entre dos puntos)
        * @param seccion La sección que queremos dibujar
        */
        void dibujarAristas(string seccion);

        /**
        * @brief Funcion para dibujar las normales de los vertices.
        */
        void dibujarNormalesVertices();

        void dibujarNormales();

        void calculaNormalesVertices();

        void calculaNormalesCaras();
        void dibujaBaricentros();
        void calculaBaricentrosCaras();


        void muestraNormales();



        _vertex3f getNormal(int pos){

            return normales[pos];

        }

        _vertex3f getBaricentro(int pos){
            return baricentros[pos];
        }


        void generaCoordenadasTextura(int numRevoluciones, int numVerticesPerfil, int numVerticesTotal){

            cout << numVerticesPerfil << numVerticesTotal;

            //Inicialización de las primeras coordenadas de textura del extremos inf. y sup. de la parte derecha de la imagen.

            cTs.push_back({1,0});
            cTs.push_back({1,1});


            float razon=(float)1/numRevoluciones;


            _vertex2f tmp;

            for(int i=numVerticesPerfil; i<=numVerticesTotal-1; i+=2){
                tmp.x=(cTs[i-2].x-razon); tmp.y=cTs[i-2].y;
                cTs.push_back(tmp);
                tmp.x=(cTs[i-1].x-razon); tmp.y=cTs[i-1].y;
                cTs.push_back(tmp);
            }

            cout << "Generadas " << cTs.size() << "coordenadas";
        }







        void muestraCoordenadasTextura(){

            cout << endl;
            cout << "Coordenadas de textura para la figura " << nombreFigura << endl;
            for(int i=0; i<cTs.size(); i++){
                cout << "Coordenada de Textura " << i <<  ": (" << cTs[i].x << "," << cTs[i].y << ")" << endl;

            }


        }


        void dibujarTextura(GLuint texName){



             glEnable(GL_TEXTURE_2D);
             glBindTexture(GL_TEXTURE_2D, texName);



        glBegin(GL_TRIANGLES);
        glColor3f(1.0f,1.0f,1.0f);
        for(int i=0; i<caras.size(); i++){
            glTexCoord2f(cTs[caras[i]._0].x, cTs[caras[i]._0].y);
            glVertex3f(vertices[caras[i]._0].x, vertices[caras[i]._0].y ,vertices[caras[i]._0].z);
            glTexCoord2f(cTs[caras[i]._1].x, cTs[caras[i]._1].y);
            glVertex3f(vertices[caras[i]._1].x, vertices[caras[i]._1].y ,vertices[caras[i]._1].z);
            glTexCoord2f(cTs[caras[i]._2].x, cTs[caras[i]._2].y);
            glVertex3f(vertices[caras[i]._2].x, vertices[caras[i]._2].y ,vertices[caras[i]._2].z);

        }


    glEnd();


   glFlush();
   glDisable(GL_TEXTURE_2D);


        }





};

#endif
