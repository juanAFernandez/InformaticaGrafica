#ifndef _FIGURACARGADA
#define _FIGURACARGADA

#include "figuraSolida.h"
//Incluimos librería para que puedan leerse los ficheros .ply
#include "file_ply_stl.h"

class figuraCargada : public figuraSolida {

    private:

    public:

        //Este tipo de objeto sólo añade la función de carga de los ficheros .ply

        void leerFichero(char *nombre){

            _file_ply fichero;
            fichero.open(nombre);

            vector<float>verticitos;
            vector<int>caritas;

            fichero.read(verticitos,caritas);

            //Carga de los vertices en nuestro formato _vertex3f
            unsigned tamVertices=verticitos.size();

            _vertex3f swap;
            for(unsigned int i=0; i<tamVertices; i=i+3){
                swap.x=verticitos[i];
                swap.y=verticitos[i+1];
                swap.z=verticitos[i+2];
                //Habría que cambiar la forma de introducir los vertices.
                vertices.push_back(swap);
            }


            //Carga de las caras en nuestro formato

            unsigned tamCaras=caritas.size();
            _vertex3i swapCaras;
            for(unsigned int i=0; i<tamCaras; i=i+3){
                swapCaras.x=caritas[i];
                swapCaras.y=caritas[i+1];
                swapCaras.z=caritas[i+2];
                //Habría que cambiar la forma de introducir los vertices.
                caras.push_back(swapCaras);
            }

            fichero.close();

        }

};
#endif
