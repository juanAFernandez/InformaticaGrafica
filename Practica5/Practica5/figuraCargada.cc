#include "figuraCargada.h"


 void figuraCargada::leerFichero(char *nombre){

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
                //Habr�a que cambiar la forma de introducir los vertices.
                vertices.push_back(swap);
            }


            //Carga de las caras en nuestro formato

            unsigned tamCaras=caritas.size();
            _vertex3i swapCaras;
            for(unsigned int i=0; i<tamCaras; i=i+3){
                swapCaras.x=caritas[i];
                swapCaras.y=caritas[i+1];
                swapCaras.z=caritas[i+2];
                //Habr�a que cambiar la forma de introducir los vertices.
                caras.push_back(swapCaras);
            }

            fichero.close();

            //Despu�s de cargar los v�rtices y las caras de la figura procesamos para obtener las normales de las caras:
            this->calculaNormalesCaras();

            //Tambi�n debemos procesar las normales de los v�rtices:

}
