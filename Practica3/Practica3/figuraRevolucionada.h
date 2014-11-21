#ifndef _FIGURAREVOLUCIONADA
#define _FIGURAREVOLUCIONADA

//Esta clase hereda de figuraSolida.h
#include "figuraSolida.h"
//Necesitamos la librería de funciones matemáticas
#include <math.h>
//Necesitamos esta librería para poder leer ficheros ply
#include "file_ply_stl.h"

//#include "variablesControl.h"


class figuraRevolucionada: public figuraSolida{

    private:

        vector<_vertex3f> perfil; /** < Vector de vertices que conforman el perfil */

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

    public:

        figuraRevolucionada(){};

        /**
        * @brief Constructor que invoca al constructor de la clase padre.
        */
        figuraRevolucionada(string nuevoNombre): figuraSolida(nuevoNombre){};

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
        * @brief Para mostrar los vértics del perfil por consola de forma legible.
        */
        void muestraPerfil();

        /**
        * @brief Función que revoluciona el perfil que pasamos.
        * @param perfil Vector de vertices del tipo _verte3f que forman el perfil.
        * @param numRev Número de revoluciones con las que queremos formar nuestro objeto a partir del perfil.
        */
        void revoluciona(int numRev, float gradosInicial, float gradosFinal);

        /**
        * @brief Función que vacía los vectores de contenido generado, todo (caras, vértices, normales de caras y de vértices y baricentros)
        * a excepción del perfil que no cambia. Estos cambios se deben a que el programa permite cambiar el nº de revoluciones en tiempo de
        * ejecución.
        */
        void vaciaFigura();
};
#endif

