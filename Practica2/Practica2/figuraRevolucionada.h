#ifndef _FIGURAREVOLUCIONADA
#define _FIGURAREVOLUCIONADA

//Esta clase hereda de figuraSolida.h
#include "figuraSolida.h"
//Necesitamos la librería de funciones matemáticas
#include <math.h>
//Necesitamos esta librería para poder leer ficheros ply
#include "file_ply_stl.h"

//Si queremos depurar mediante mensajes el proceso de cálculo.
bool DEBUGG=false;


class figuraRevolucionada: public figuraSolida{

    private:

        vector<_vertex3f> perfil;

        /**
        * @brief Función para leer el perfil a partir de un fichero .ply .
        * @param nombreFichero Nombre del fichero a abrir con la librería file_ply
        * @warning Esta función es privada de la clase y sólo podrá accederse a ella por sus métodos y no desde fuera.
        **/


        /**
        * @brief Función para generar las caras en la sección central de las figuras.
        * @param numRev El número de revoluciones con la que queremos formar nuestro objeto.
        * @param numVP El número de vértices por perfil que tiene nuestra figura. (POSIBLEMENTE SE ELIMINE POR CAMBIO DE FUNCINOALIDAD)
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
        * @brief Función para realizar la conversión de ángulos a radianes que necesitamos para trabajar con OpenGL
        * @param angulo Grados del ángulo a convertir
        * @return Devuelve los grados del ángulo convertidos a radianes.
        **/
        double gradosARadianes(double angulo){return angulo*(M_PI/180);}

    public:

        /**
        * @brief Función para cargar el perfil a partir de un fichero .ply
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
                //Habría que cambiar la forma de introducir los vertices.
                perfil.push_back(swap);
            }

            //Cerramos el fichero.
            fichero.close();
        }

        /**
        * @brief Función para cargar el perfil a partir de un vector.
        * param vectorPerfil Elvector de _vertex3f que almacena el perfil.
        */
        void cargarPerfil(vector <_vertex3f> vectorPerfil){
            for(int i=0; i<vectorPerfil.size(); i++)
                perfil.push_back(vectorPerfil[i]);
        }

        /**
        * @brief Función que nos muestra en terminal las caras almacenadas en el vector de caras con un formato legible.
        */
        void muestraCaras(){
            for(int i=0; i<caras.size(); i++)
                cout << "Cara n." << i << " [" << caras[i]._0 << " " << caras[i]._1 << " " << caras[i]._2 << "]" << endl;

        }

        /**
        * @brief Función que nos muestra en el terminal los vértices almacenados en el vector de vértices en formato legible.
        */
        void muestraVertices(){
            cout << "Vector de vertices: " << endl;
            for(int i=0; i<vertices.size(); i++){
                cout << "Vertice n." << i;
                cout << " [" << vertices[i].x <<" , "<< vertices[i].y << " , "<< vertices[i].z << "]" << endl;
            }
        }

        /**
        * @brief Función que revoluciona el perfil que pasamos.
        * @param perfil Vector de vertices del tipo _verte3f que forman el perfil.
        * @param numRev Número de revoluciones con las que queremos formar nuestro objeto a partir del perfil.
        */
        void revoluciona(int numRev){

            //Atención: El pefil es una estructura de datos distinta de nuestro vector de vertices, hay que pasar la información a este,
            //que es lo que se hace cuando se pasa a revolucionar, se leen datos del perfil y se introducen en el vector de vértices
            //de nuestra nueva figura revolucionada.

            // #ALGORITMO# //

            // ##1## Lo primero que nuestro algoritmo va a hacer es detectar la presencia de las tapas:
            bool tapaSuperior=false;
            bool tapaInferior=false;

            //Proceso de detección de tapas:
            //Los puntos del perfil en el eje Y los buscaremos en el primer y último vertice del perfil

            //Primer vértice del perfil. Si existe y cumple ciertas condiciones deducimos que se trata del vértice de tapa inferior.
            if( (perfil[0].x==0) && (perfil[0].z==0) )
               tapaInferior=true;

            //Último vértice del perfil. Si existe y cumple ciertas condiciones deducimos que se trata del vértice de tapa superior.
            if( (perfil[perfil.size()-1].x==0) && (perfil[perfil.size()-1].z==0) )
               tapaSuperior=true;



            if(tapaInferior)
                cout << "TAPA INFERIOR: " << perfil[0].x << perfil[0].y << perfil[0].z << endl;
            if(tapaSuperior)
                cout << "TAPA SUPERIOR: " << perfil[perfil.size()-1].x << perfil[perfil.size()-1].y << perfil[perfil.size()-1].z << endl;


            // ##2## Detectadas las tapas las sacamos de perfil


            // ##3## Revolucionamos los vectores del perfil sin tapas (si las hubiera). Que sería la sección central sólo.

                //3.1 Antes de volver a introducir los "vertices tapas" procesamos las caras centrales
                //Procesa caras centrales

            // ##4## Añadimos al final del nuevo vector de vértices los vértices que componen las tapas

            // ##5## Generamos las caras según tengamos o no tapas. Podemos tener una (cualquiera de las dos), las dos o ninguna en cuyo cas pasaríamos de esta sección.

                if(tapaSuperior){
                    //Procesa caras tapa superior
                }

                if(tapaInferior){
                    //Procesa caras tapa inferior
                }






            _vertex3f nuevoVertice;

            //La circuferencia la componen 360º
            //En el caso de ser 360º serían 90º cada porción, es decir el perfil de la primera revolución formaría
            //90º respecto al original, así con todos.
            const float gradosPorcion=360.0/numRev;

            float gradosPerfilActual=gradosPorcion;

            //El valor de x del anterior vértice por el coseno del grado que queremos colocarlo en el eje de rotación
            //(en nuestro caso Y) en radianes que es como funciona openGL
            //float radio=vertices[i].x;
            float radio;

            //Introducimos el primer  perfil en el vector de vértices de la figura
            for(int i=0; i<perfil.size(); i++)
                setVerticeManual(perfil[i].x, perfil[i].y, perfil[i].z );

            //Repetimos el proceso tantas veces como revoluciones queramos hacer.
            for(int i=0; i<numRev-1; i++){


                //Núcleo del algoritmo, que se realiza por cada revolución.
                for(int j=0; j<perfil.size(); j++){
                    //Ejecutado tantas veces como vertices tenga el perfil para general otro pero con una ferencia de
                    //grados como se pretende.

                    //Se obtiene el readio del vertice del perfil.
                    radio=perfil[j].x;


                    if(DEBUGG)
                        cout << "gradosPerfilActual: " << gradosPerfilActual << endl;


                    nuevoVertice.x=fabs(radio)*cos(gradosARadianes(gradosPerfilActual));
                    //La coordenada Y del vértice del perfil en cuestión NO CAMBIA por ser el eje de rotación. (la altura del punto se mantiene)
                    nuevoVertice.y=perfil[j].y;
                    nuevoVertice.z=fabs(radio)*sin(gradosARadianes(gradosPerfilActual));


                    if(DEBUGG)
                        cout << "Generado vértice x:" << nuevoVertice.x << " y:" << nuevoVertice.y << " z:" << nuevoVertice.z <<endl;
                    setVerticeManual(nuevoVertice.x, nuevoVertice.y, nuevoVertice.z);

                }
                //Cuando terminamos con un perfil sumamos los grados necesarios para general el siguiente.
                gradosPerfilActual+=gradosPorcion;
            }

            //Una vez revolucionado se procede a generar las caras usando el vector de vértices obtenido:
            generaCaras(numRev, perfil.size());
            cout << "Número de vértices generado: " << vertices.size() << endl;


        }




        void vaciaFigura(){

            /*Si queremos aumentar el número de revoluciones en tiempo de ejecución el objeto debe de nuevo revolocionarse ya que los
            nuevos vértices tendrán posiciones totalmente distintas a las anteriores además se crearaán otras caras totalmente distintas
            a las anteriores. Por esto debemos de vaciar cualquier contenido que tuvieramos en ambos vectors previamente para almacenar el nuevo.
            */
            //Eliminamos todos lo vértices almacenados.
            vertices.clear();
            //Eliminamos todas las caras generadas almacenadas.
            caras.clear();

            //El perfil no se vacía porque su contenido 1º tiene que seguir leyendose y 2º no va a variar.
        }
};
#endif

