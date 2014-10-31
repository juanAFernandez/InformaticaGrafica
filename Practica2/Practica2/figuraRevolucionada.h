#ifndef _FIGURAREVOLUCIONADA
#define _FIGURAREVOLUCIONADA

//Esta clase hereda de figuraSolida.h
#include "figuraSolida.h"
//Necesitamos la librer�a de funciones matem�ticas
#include <math.h>
//Necesitamos esta librer�a para poder leer ficheros ply
#include "file_ply_stl.h"

//Si queremos depurar mediante mensajes el proceso de c�lculo.
bool DEBUGG=false;


class figuraRevolucionada: public figuraSolida{

    private:

        vector<_vertex3f> perfil;

        /**
        * @brief Funci�n para leer el perfil a partir de un fichero .ply .
        * @param nombreFichero Nombre del fichero a abrir con la librer�a file_ply
        * @warning Esta funci�n es privada de la clase y s�lo podr� accederse a ella por sus m�todos y no desde fuera.
        **/


        /**
        * @brief Funci�n para generar las caras en la secci�n central de las figuras.
        * @param numRev El n�mero de revoluciones con la que queremos formar nuestro objeto.
        * @param numVP El n�mero de v�rtices por perfil que tiene nuestra figura. (POSIBLEMENTE SE ELIMINE POR CAMBIO DE FUNCINOALIDAD)
        **/
        void generaCaras(int numRev, int numVP){


            int verticeA, verticeB, verticeC;
            int elementosVector=vertices.size();

            if(DEBUGG){
                cout << "Numero de revoluciones: " << numRev << endl;
                cout << "Numero de vertices por perfil: " << numVP << endl;
                cout << "Numero total de vertices generados: " << elementosVector << endl;
            }


            //### Generando las caras PAR:
            for(int i=0; i<numVP-1; i++)
                for(int j=0; j<numRev; j++){
                    verticeA=(((j*numVP)+i)%elementosVector);
                    verticeB=(((j*numVP)+(numVP+i))%elementosVector);
                    verticeC=(((j*numVP)+(1+i))%elementosVector);
                    if(DEBUGG)
                        cout << "Cara PAR generada n. "<< verticeA << " "<< verticeB << " "<< verticeC << endl;
                    //Introduciendo la cara
                    setCaraManual(verticeA,verticeB,verticeC);
                }


            //### Generando las caras IMPAR:
            for(int i=0; i<numVP-1; i++)
                for(int j=0; j<numRev; j++){
                    verticeA=(((j*numVP)+(numVP+i))%elementosVector);
                    verticeB=((verticeA+1)%elementosVector);
                    verticeC=(((j*numVP)+(1+i))%elementosVector);
                    if(DEBUGG)
                        cout << "Cara IMPAR generada n. "<< verticeA << " "<< verticeB << " "<< verticeC << endl;
                    //Introduciendo la cara
                    setCaraManual(verticeA,verticeB,verticeC);

                }
            if(DEBUGG){
                cout << "Numero total de caras generados: " << caras.size() << endl;
            }
        }

        void generaCarasTapaSuperior(){
        }
        void generaCarasTapaInferior(){
        }

        /**
        * @brief Funci�n para realizar la conversi�n de �ngulos a radianes que necesitamos para trabajar con OpenGL
        * @param angulo Grados del �ngulo a convertir
        * @return Devuelve los grados del �ngulo convertidos a radianes.
        **/
        double gradosARadianes(double angulo){return angulo*(M_PI/180);}

    public:

        /**
        * @brief Funci�n para cargar el perfil a partir de un fichero .ply
        * param nombreFichero El nombre dle fichero que vamos a usar.
        */
        void cargarPerfil(char *nombreFichero){

            _file_ply fichero;
            fichero.open(nombreFichero);

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
                perfil.push_back(swap);
            }

            //Cerramos el fichero.
            fichero.close();
        }

        /**
        * @brief Funci�n para cargar el perfil a partir de un vector.
        * param vectorPerfil Elvector de _vertex3f que almacena el perfil.
        */
        void cargarPerfil(vector <_vertex3f> vectorPerfil){
            for(int i=0; i<vectorPerfil.size(); i++)
                perfil.push_back(vectorPerfil[i]);
        }

        /**
        * @brief Funci�n que nos muestra en terminal las caras almacenadas en el vector de caras con un formato legible.
        */
        void muestraCaras(){
            for(int i=0; i<caras.size(); i++)
                cout << "Cara n." << i << " [" << caras[i]._0 << " " << caras[i]._1 << " " << caras[i]._2 << "]" << endl;

        }

        /**
        * @brief Funci�n que nos muestra en el terminal los v�rtices almacenados en el vector de v�rtices en formato legible.
        */
        void muestraVertices(){
            cout << "Vector de vertices: " << endl;
            for(int i=0; i<vertices.size(); i++){
                cout << "Vertice n." << i;
                cout << " [" << vertices[i].x <<" , "<< vertices[i].y << " , "<< vertices[i].z << "]" << endl;
            }
        }

        /**
        * @brief Funci�n que revoluciona el perfil que pasamos.
        * @param perfil Vector de vertices del tipo _verte3f que forman el perfil.
        * @param numRev N�mero de revoluciones con las que queremos formar nuestro objeto a partir del perfil.
        */
        void revoluciona(int numRev){

            //Atenci�n: El pefil es una estructura de datos distinta de nuestro vector de vertices, hay que pasar la informaci�n a este,
            //que es lo que se hace cuando se pasa a revolucionar, se leen datos del perfil y se introducen en el vector de v�rtices
            //de nuestra nueva figura revolucionada.

            // #ALGORITMO# //

            // ##1## Lo primero que nuestro algoritmo va a hacer es detectar la presencia de las tapas:
            bool tapaSuperior=false;
            bool tapaInferior=false;

            //Proceso de detecci�n de tapas:
            //Los puntos del perfil en el eje Y los buscaremos en el primer y �ltimo vertice del perfil

            //Primer v�rtice del perfil. Si existe y cumple ciertas condiciones deducimos que se trata del v�rtice de tapa inferior.
            if( (perfil[0].x==0) && (perfil[0].z==0) )
               tapaInferior=true;

            //�ltimo v�rtice del perfil. Si existe y cumple ciertas condiciones deducimos que se trata del v�rtice de tapa superior.
            if( (perfil[perfil.size()-1].x==0) && (perfil[perfil.size()-1].z==0) )
               tapaSuperior=true;



            if(tapaInferior)
                cout << "TAPA INFERIOR: " << perfil[0].x << perfil[0].y << perfil[0].z << endl;
            if(tapaSuperior)
                cout << "TAPA SUPERIOR: " << perfil[perfil.size()-1].x << perfil[perfil.size()-1].y << perfil[perfil.size()-1].z << endl;


            // ##2## Detectadas las tapas las sacamos de perfil


            // ##3## Revolucionamos los vectores del perfil sin tapas (si las hubiera). Que ser�a la secci�n central s�lo.

                //3.1 Antes de volver a introducir los "vertices tapas" procesamos las caras centrales
                //Procesa caras centrales

            // ##4## A�adimos al final del nuevo vector de v�rtices los v�rtices que componen las tapas

            // ##5## Generamos las caras seg�n tengamos o no tapas. Podemos tener una (cualquiera de las dos), las dos o ninguna en cuyo cas pasar�amos de esta secci�n.

                if(tapaSuperior){
                    //Procesa caras tapa superior
                }

                if(tapaInferior){
                    //Procesa caras tapa inferior
                }






            _vertex3f nuevoVertice;

            //La circuferencia la componen 360�
            //En el caso de ser 360� ser�an 90� cada porci�n, es decir el perfil de la primera revoluci�n formar�a
            //90� respecto al original, as� con todos.
            const float gradosPorcion=360.0/numRev;

            float gradosPerfilActual=gradosPorcion;

            //El valor de x del anterior v�rtice por el coseno del grado que queremos colocarlo en el eje de rotaci�n
            //(en nuestro caso Y) en radianes que es como funciona openGL
            //float radio=vertices[i].x;
            float radio;

            //Introducimos el primer  perfil en el vector de v�rtices de la figura
            for(int i=0; i<perfil.size(); i++)
                setVerticeManual(perfil[i].x, perfil[i].y, perfil[i].z );

            //Repetimos el proceso tantas veces como revoluciones queramos hacer.
            for(int i=0; i<numRev-1; i++){


                //N�cleo del algoritmo, que se realiza por cada revoluci�n.
                for(int j=0; j<perfil.size(); j++){
                    //Ejecutado tantas veces como vertices tenga el perfil para general otro pero con una ferencia de
                    //grados como se pretende.

                    //Se obtiene el readio del vertice del perfil.
                    radio=perfil[j].x;


                    if(DEBUGG)
                        cout << "gradosPerfilActual: " << gradosPerfilActual << endl;


                    nuevoVertice.x=fabs(radio)*cos(gradosARadianes(gradosPerfilActual));
                    //La coordenada Y del v�rtice del perfil en cuesti�n NO CAMBIA por ser el eje de rotaci�n. (la altura del punto se mantiene)
                    nuevoVertice.y=perfil[j].y;
                    nuevoVertice.z=fabs(radio)*sin(gradosARadianes(gradosPerfilActual));


                    if(DEBUGG)
                        cout << "Generado v�rtice x:" << nuevoVertice.x << " y:" << nuevoVertice.y << " z:" << nuevoVertice.z <<endl;
                    setVerticeManual(nuevoVertice.x, nuevoVertice.y, nuevoVertice.z);

                }
                //Cuando terminamos con un perfil sumamos los grados necesarios para general el siguiente.
                gradosPerfilActual+=gradosPorcion;
            }

            //Una vez revolucionado se procede a generar las caras usando el vector de v�rtices obtenido:
            generaCaras(numRev, perfil.size());
            cout << "N�mero de v�rtices generado: " << vertices.size() << endl;


        }




        void vaciaFigura(){

            /*Si queremos aumentar el n�mero de revoluciones en tiempo de ejecuci�n el objeto debe de nuevo revolocionarse ya que los
            nuevos v�rtices tendr�n posiciones totalmente distintas a las anteriores adem�s se creara�n otras caras totalmente distintas
            a las anteriores. Por esto debemos de vaciar cualquier contenido que tuvieramos en ambos vectors previamente para almacenar el nuevo.
            */
            //Eliminamos todos lo v�rtices almacenados.
            vertices.clear();
            //Eliminamos todas las caras generadas almacenadas.
            caras.clear();

            //El perfil no se vac�a porque su contenido 1� tiene que seguir leyendose y 2� no va a variar.
        }
};
#endif

