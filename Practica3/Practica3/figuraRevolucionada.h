#ifndef _FIGURAREVOLUCIONADA
#define _FIGURAREVOLUCIONADA

//Esta clase hereda de figuraSolida.h
#include "figuraSolida.h"
//Necesitamos la librer�a de funciones matem�ticas
#include <math.h>
//Necesitamos esta librer�a para poder leer ficheros ply
#include "file_ply_stl.h"

//#include "variablesControl.h"


class figuraRevolucionada: public figuraSolida{

    private:

        vector<_vertex3f> perfil; /** < Vector de vertices que conforman el perfil */

        /**
        * @brief Funci�n para generar las caras en la secci�n central de las figuras.
        * @param numRev El n�mero de revoluciones con la que queremos formar nuestro objeto.
        * @param numVP El n�mero de v�rtices por perfil que tiene nuestra figura. (POSIBLEMENTE SE ELIMINE POR CAMBIO DE FUNCINOALIDAD)
        **/
        void generaCarasCentral(int numRev, int numVP);

        /**
        * @brief Para generar las caras de la tapa inferior en caso de que esta existiera.
        * @param numRev N�mero de revoluciones que se han aplicado sobre el perfil.
        * @param posTi Posici�n en el vector de v�rtices del punto en el eje Y representativo de la tapa inferior.
        * @param nVPST N�mero de vertices del perfil original con el que formamos la figura sin contar los v�rtices de las tapas.
        */
        void generaCarasTapaInferior(int numRev, int posTi, int nVPST);

        /**
        * @brief Para generar las caras de la tapa superior en caso de que esta existiera.
        * @param numRev N�mero de revoluciones que se han aplicado sobre el perfil.
        * @param posTs Posici�n en el vector de v�rtices del punto en el eje Y representativo de la tapa superior.
        * @param nVPST N�mero de vertices del perfil original con el que formamos la figura sin contar los v�rtices de las tapas.
        * @param nVST N�mero de vertices del vector v�rtices sin contar los v�rtices de las tapas, como m�ximo sin dos.
        */
        void generaCarasTapaSuperior(int numRev, int posTs, int nVPST, int nVST);

        /**
        * @brief Funci�n para realizar la conversi�n de �ngulos a radianes que necesitamos para trabajar con OpenGL
        * @param angulo Grados del �ngulo a convertir
        * @return Devuelve los grados del �ngulo convertidos a radianes.
        **/
        double gradosARadianes(double angulo){return angulo*(M_PI/180);}

    public:

        figuraRevolucionada(){};

        /**
        * @brief Constructor que invoca al constructor de la clase padre.
        */
        figuraRevolucionada(string nuevoNombre): figuraSolida(nuevoNombre){};

        /**
        * @brief Funci�n para cargar el perfil a partir de un fichero .ply
        * @param nombreFichero El nombre dle fichero que vamos a usar.
        */
        void cargarPerfil(char *nombreFichero);

        /**
        * @brief Funci�n para cargar el perfil a partir de un vector.
        * param vectorPerfil Elvector de _vertex3f que almacena el perfil.
        */
        void cargarPerfil(vector <_vertex3f> vectorPerfil);

        /**
        * @brief Para mostrar los v�rtics del perfil por consola de forma legible.
        */
        void muestraPerfil();

        /**
        * @brief Funci�n que revoluciona el perfil que pasamos.
        * @param perfil Vector de vertices del tipo _verte3f que forman el perfil.
        * @param numRev N�mero de revoluciones con las que queremos formar nuestro objeto a partir del perfil.
        */
        void revoluciona(int numRev, float gradosInicial, float gradosFinal);

        /**
        * @brief Funci�n que vac�a los vectores de contenido generado, todo (caras, v�rtices, normales de caras y de v�rtices y baricentros)
        * a excepci�n del perfil que no cambia. Estos cambios se deben a que el programa permite cambiar el n� de revoluciones en tiempo de
        * ejecuci�n.
        */
        void vaciaFigura();
};
#endif

