#ifndef _FIGURACARGADA
#define _FIGURACARGADA

#include "figuraSolida.h"
//Incluimos librer�a para que puedan leerse los ficheros .ply
#include "file_ply_stl.h"

class figuraCargada : public figuraSolida {

    private:

    public:

        //Este tipo de objeto s�lo a�ade la funci�n de carga de los ficheros .ply
        void leerFichero(char *nombre);

};
#endif
