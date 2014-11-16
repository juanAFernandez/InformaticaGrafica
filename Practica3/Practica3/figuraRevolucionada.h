#ifndef _FIGURAREVOLUCIONADA
#define _FIGURAREVOLUCIONADA

//Esta clase hereda de figuraSolida.h
#include "figuraSolida.h"
//Necesitamos la librería de funciones matemáticas
#include <math.h>
//Necesitamos esta librería para poder leer ficheros ply
#include "file_ply_stl.h"

//#include "variablesControl.h"

//Si queremos depurar mediante mensajes el proceso de cálculo.
//bool DEBUGG=false;


class figuraRevolucionada: public figuraSolida{

    private:

        vector<_vertex3f> perfil;
        vector<_vertex3f> normales;
        vector<_vertex3f> normalesVertices;
        vector<_vertex3f> baricentros;

        /**
        * @brief Función para generar las caras en la sección central de las figuras.
        * @param numRev El número de revoluciones con la que queremos formar nuestro objeto.
        * @param numVP El número de vértices por perfil que tiene nuestra figura. (POSIBLEMENTE SE ELIMINE POR CAMBIO DE FUNCINOALIDAD)
        **/
        void generaCarasCentral(int numRev, int numVP);

        /**
        * @brief Para generar las caras de la tapa inferior en caso de que esta existiera.
        * @param numRev Número de revoluciones que se han aplicado sobre el perfil.
        * @param posTi Posición en el vector de vértices del punto en el eje Y representativo de la tapa inferior.
        * @param nVPST Número de vertices del perfil original con el que formamos la figura sin contar los vértices de las tapas.
        */
        void generaCarasTapaInferior(int numRev, int posTi, int nVPST);

        /**
        * @brief Para generar las caras de la tapa superior en caso de que esta existiera.
        * @param numRev Número de revoluciones que se han aplicado sobre el perfil.
        * @param posTs Posición en el vector de vértices del punto en el eje Y representativo de la tapa superior.
        * @param nVPST Número de vertices del perfil original con el que formamos la figura sin contar los vértices de las tapas.
        * @param nVST Número de vertices del vector vértices sin contar los vértices de las tapas, como máximo sin dos.
        */
        void generaCarasTapaSuperior(int numRev, int posTs, int nVPST, int nVST);

        /**
        * @brief Función para realizar la conversión de ángulos a radianes que necesitamos para trabajar con OpenGL
        * @param angulo Grados del ángulo a convertir
        * @return Devuelve los grados del ángulo convertidos a radianes.
        **/
        double gradosARadianes(double angulo){return angulo*(M_PI/180);}


        _vertex3f productoVectorial(_vertex3f ab, _vertex3f ac);



    public:

        void calculaNormalesCaras();

        void calculaNormalesVertices();

        void dibujaBaricentros();

        void dibujarNormalesVertices();

        void dibujarNormales();

        void calculaBaricentrosCaras();

        /**
        * @brief Función para cargar el perfil a partir de un fichero .ply
        * @param nombreFichero El nombre dle fichero que vamos a usar.
        */
        void cargarPerfil(char *nombreFichero);

        /**
        * @brief Función para cargar el perfil a partir de un vector.
        * param vectorPerfil Elvector de _vertex3f que almacena el perfil.
        */
        void cargarPerfil(vector <_vertex3f> vectorPerfil);

        /**
        * @brief Función que nos muestra en terminal las caras almacenadas en el vector de caras con un formato legible.
        */
        void muestraCaras(){
            //for(int i=0; i<caras.size(); i++)
                //cout << "Cara n." << i << " [" << caras[i]._0 << " " << caras[i]._1 << " " << caras[i]._2 << "]" << endl;

        }

        void muestraPerfil(){
            //cout << "Vertices del perfil: " << endl;
            //for(int i=0; i<perfil.size(); i++)
                //cout << "Vertice n." << i << " [" << perfil[i].x << " " << perfil[i].y << " " << perfil[i].z << "]" << endl;
        }

        /**
        * @brief Función que nos muestra en el terminal los vértices almacenados en el vector de vértices en formato legible.
        */
        void muestraVertices(){
            //cout << "Vector de vertices: " << endl;
           // for(int i=0; i<vertices.size(); i++){
              //  cout << "Vertice n." << i;
                //cout << " [" << vertices[i].x <<" , "<< vertices[i].y << " , "<< vertices[i].z << "]" << endl;
            //}
        }

        void muestraNormales(){
            //cout << "Vector de normales" << endl;
            //for(int i=0; i<normales; i++)

        }

        /**
        * @brief Función que revoluciona el perfil que pasamos.
        * @param perfil Vector de vertices del tipo _verte3f que forman el perfil.
        * @param numRev Número de revoluciones con las que queremos formar nuestro objeto a partir del perfil.
        */
        void revoluciona(int numRev, float gradosInicial, float gradosFinal);




        void vaciaFigura();
};
#endif

