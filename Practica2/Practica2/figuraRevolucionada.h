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

        //Vector para el almacenaje de los vectores normales de las caras para la iluminación.
        vector<_vertex3f> normales;
        vector<_vertex3f> baricentros;


        /**
        * @brief Función para generar las caras en la sección central de las figuras.
        * @param numRev El número de revoluciones con la que queremos formar nuestro objeto.
        * @param numVP El número de vértices por perfil que tiene nuestra figura. (POSIBLEMENTE SE ELIMINE POR CAMBIO DE FUNCINOALIDAD)
        **/
        void generaCarasCentral(int numRev, int numVP){


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
                    verticeC=(((j*numVP)+(numVP+i))%elementosVector);
                    verticeB=(((j*numVP)+(1+i))%elementosVector);
                    if(DEBUGG)
                        cout << "Cara PAR generada n. "<< verticeA << " "<< verticeB << " "<< verticeC << endl;
                    //Introduciendo la cara
                    setCaraManual(verticeA,verticeB,verticeC);
                }


            //### Generando las caras IMPAR:
            for(int i=0; i<numVP-1; i++)
                for(int j=0; j<numRev; j++){
                    verticeA=(((j*numVP)+(numVP+i))%elementosVector);
                    verticeC=((verticeA+1)%elementosVector);
                    verticeB=(((j*numVP)+(1+i))%elementosVector);
                    if(DEBUGG)
                        cout << "Cara IMPAR generada n. "<< verticeA << " "<< verticeB << " "<< verticeC << endl;
                    //Introduciendo la cara
                    setCaraManual(verticeA,verticeB,verticeC);

                }
            if(DEBUGG){
                cout << "Numero total de caras generados: " << caras.size() << endl;
            }
        }

        void generaCarasTapaInferior(int numRev, int posTi, int nVPST){
            /*
            cout << "numero de revoluciones: " << numRev << endl;
            cout << "posición del vertice central de la tapa inferior: " << posTi << endl;
            cout << "numero de vertices del perfil sin tapa: " << nVPST << endl;
            cout << ((0+1)*nVPST) << endl;
            */
            //No es necesario generar el verticeA porque siempre será el mismo: posTi
            int verticeB, verticeC;
            for(int i=0; i<numRev; i++){
                verticeC=((i+1)*nVPST)%posTi;
                verticeB=((i*nVPST)%posTi);
                setCaraManual(posTi,verticeB,verticeC);
                //cout << "Cara tapa inferior generada: ["<<posTi<<" "<<verticeB <<" "<<verticeC <<"]"<<endl;
            }

        }

        void generaCarasTapaSuperior(int numRev, int posTs, int nVPST, int nVST){
            //No es necesario general el vértice B ya que es siempre el mismo
             //cout << "numero de revoluciones: " << numRev << endl;
             //cout << "posición del vertice central de la tapa inferior: " << posTs << endl;
             //cout << "numero de vertices del perfil sin tapa: " << nVPST << endl;
             //cout << "numero de vertices  sin tapa: " << nVST << endl;
             int verticeA, verticeC;
            for(int i=0; i<numRev; i++){
                verticeC=((nVPST*(i+1))+(nVPST-1))%nVST;
                verticeA=(verticeC+(nVST-nVPST))%nVST;
                setCaraManual(verticeA, posTs, verticeC);
                //cout << "Cara tapa superior generada: ["<<verticeA<<" "<<posTs <<" "<<verticeC <<"]"<<endl;
            }
        }


        /**
        * @brief Función para realizar la conversión de ángulos a radianes que necesitamos para trabajar con OpenGL
        * @param angulo Grados del ángulo a convertir
        * @return Devuelve los grados del ángulo convertidos a radianes.
        **/
        double gradosARadianes(double angulo){return angulo*(M_PI/180);}

        void muestraVertice(_vertex3f vertice){
            //cout << "[ " << vertice.x << " " << vertice.y << " " << vertice.z << " ]" << endl;
        }

        _vertex3f productoVectorial(_vertex3f ab, _vertex3f ac){
                _vertex3f producto;
                producto.x=(ab.y*ac.z)-(ab.z*ac.y);
                producto.y=(ab.z*ac.x)-(ab.x*ac.z);
                producto.z=(ab.x*ac.y)-(ab.y*ac.x);
            return producto;
        }

    public:

        void calculaNormalesCaras(){

            //Dado una cara (un triángulo formado por tres vértices) vamos a obtener la normal que forman los vectores que definen esta.

            /*Sacamos dos vectores y como queremos que la normal vaya hacia el exterior de la cara somos cuidadosos a la hora de
            elegir los vértices y los vectores para los que sacamos la normal. Como tenemos tres vértices v1, v2 y v3 tendremos los vectores
            A y B que irán de V3 a v1 y de V3 a V2 respectivamente. El cálculo de un vector mediantes dos puntos se reliza mediante la resta
            de los puntos del vértice extremo al origen. Así si tenemos que B=v3-->v2, el vector B son las coordenadas de v2 - las de v3.*/

            //Variables que usaremos en el proceso:
            _vertex3f a, b, c; //Vértices que extraeremos de la cara.
            _vertex3f ab,ac; //Vectores rsultantes de los puntos.
            _vertex3f normal; //Vector normal resultante del proceso.

            float modulo; //Para la normalizción de la normal.

            //cout << endl << endl << " ### Procesamiento de normales ### " << endl;

            //El proceso debe repetirse en tantas caras como tengamos.
            for(unsigned int i=0; i<caras.size(); i++){

                //cout << "Procesando cara " << i << endl;

                //Extraemos los vértices de la cara:
                a=vertices[caras[i]._0];
                b=vertices[caras[i]._1];
                c=vertices[caras[i]._2];

                //cout << "Extracción de los vertices" << endl;
                //cout << "Vertices de la cara " << i << " :" << endl;
                //muestraVertice(a); muestraVertice(b); muestraVertice(c);
                //cout << endl;


                //A partir de esos vértices obtenemos los vectores

                    //A= v1-->v2 ==> v2-v1 = [(v2x-v1x),(v2y-v1y),(v2x-v1y)]
                    ab.x=b.x-a.x; ab.y=b.y-a.y; ab.z=b.z-a.z;

                    //cout << "Vector A: "<< endl;
                    //muestraVertice(A);

                    //B= v1-->v3 ==> v3-v1 = [(v3x-v1x),(v3y-v1y),(v3z-v1z)]
                    ac.x=c.x-a.x; ac.y=c.y-a.y; ac.z=c.z-a.z;

                    //cout << "Vector B: "<< endl;
                    //muestraVertice(B);

                //Hacemos el producto vectorial mediante la fórumla abreviada extraida de (http://es.wikipedia.org/wiki/Producto_vectorial)


                normal=productoVectorial(ab,ac);

                //cout << "NORMAL antes de normalizar: " << endl;
                //muestraVertice(normal);

                //Antes de finalizar hay que normalizar la normal (diviéndola entre su módulo)
                normal.normalize();

                //cout << "NORMAL **normalizada**: " << endl;
                //muestraVertice(normal);

                //cout << "normal:" << normal.x << " " << normal.y << " " << normal.z << endl;

                //Introducimos la normal en el vector de normales.
                normales.push_back(normal);

                //cout << "normal:" << normal.x << " " << normal.y << " " << normal.z << endl;
               // cout << endl << endl;

            }

            //cout << "Número de normales generadas: " << normales.size() << endl;
            calculaBaricentrosCaras();

        }

        void dibujaBaricentros(){
            glColor3fv(NEGRO);
            glPointSize(5);
            glBegin(GL_POINTS);
                for(unsigned int i=0; i<caras.size(); i++)
                    glVertex3f(baricentros[i].x,baricentros[i].y,baricentros[i].z);
            glEnd();
        }

        void dibujarNormales(){
            //Teniendo la normal y el baricentro, ¿Cómo dibujo una linea que salga de la caras?
            glBegin(GL_LINES);
                for(unsigned int i=0; i<caras.size(); i++){
                    glVertex3f(baricentros[i].x,baricentros[i].y,baricentros[i].z);
                    glVertex3f(baricentros[i].x+normales[i].x, baricentros[i].y+normales[i].y, baricentros[i].z+normales[i].z);
                }
            glEnd();
        }

        void calculaBaricentrosCaras(){
            //Proceso que se repite como tantas caras tengamos.
            _vertex3f baricentro;
            for(int i=0; i<caras.size(); i++){
                baricentro.x=((vertices[caras[i]._0].x + vertices[caras[i]._1].x + vertices[caras[i]._2].x)/3);
                baricentro.y=((vertices[caras[i]._0].y + vertices[caras[i]._1].y + vertices[caras[i]._2].y)/3);
                baricentro.z=((vertices[caras[i]._0].z + vertices[caras[i]._1].z + vertices[caras[i]._2].z)/3);

                //cout << "Baricentro de la cara " << i << endl;
                muestraVertice(baricentro);

                baricentros.push_back(baricentro);
            }

        }

        /**
        * @brief Función para cargar el perfil a partir de un fichero .ply
        * @param nombreFichero El nombre dle fichero que vamos a usar.
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
        void revoluciona(int numRev, float grados){

           // cout << endl << "Numero de revoluciones: " << numRev << endl;

            //Atención: El perfil es una estructura de datos distinta de nuestro vector de vertices, hay que pasar la información a este,
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

            //Mostramos por pantalla los vértices tapar superior e inferior en el caso de existir.
            if(tapaInferior)
                cout << "TAPA INFERIOR: " << "[" << perfil[0].x << " " << perfil[0].y << " " << perfil[0].z << "]" << endl;
            if(tapaSuperior)
                cout << "TAPA SUPERIOR: " << "[" << perfil[perfil.size()-1].x << " " << perfil[perfil.size()-1].y << " " << perfil[perfil.size()-1].z << "] " << endl;


            // ##2## Detectadas las tapas las sacamos del perfil (recordamos que perfil es del tipo vector de la STL, usamos algunas funciones)

            //Mostramos el perfil.

            muestraPerfil();

            //Declaramos un par de vértices temporales.
            _vertex3f verticeTapaSuperior, verticeTapaInferior;

            if(tapaInferior){
                //Copiamos el vértice en el temporal
                verticeTapaInferior=perfil.front();
                //Eliminamos el vértice del perfil.
                perfil.erase(perfil.begin());
            }

            if(tapaSuperior){
                //Copiamos el vértice en el temporal
                verticeTapaSuperior=perfil.back();
                //Eliminamos el vértice del perfil.
                perfil.erase(perfil.end());
            }

            //Guardamos en una variable el número de vértices del perfil sin tapas. nVPST
            int nVPST=perfil.size();

            muestraPerfil();


            // ##3## Revolucionamos los vectores del perfil sin los vértices tapas (si los hubiera). Que sería la sección central sólo.


                //Revolucionado de los vértices de perfil y añadidos a nueestro vector de vértices de nuestra figura.

                //##Inicio de la revolución
                _vertex3f nuevoVertice;
                //La circuferencia la componen 360º
                //En el caso de ser 360º serían 90º cada porción, es decir el perfil de la primera revolución formaría
                //90º respecto al original, así con todos.
                const float gradosPorcion=grados/numRev;

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

                        //Se obtiene el radio del vertice del perfil.
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
                //##Fin de la revolución

                cout << "Numero de vertices generados sin tapas: " << vertices.size() << endl;

                //Necesitamos la variable número de vértices totales sin tapa para la función generadora de las tapas superiores.
                int nVST=vertices.size();

                //3.1 Antes de volver a introducir los "vertices tapas" procesamos las caras centrales
                //Procesa caras centrales

                //Una vez revolucionado se procede a generar las caras usando el vector de vértices obtenido:
                generaCarasCentral(numRev, perfil.size());

            // ##4## Añadimos al final del nuevo vector de vértices los vértices que componen las tapas

                //Primero añadimos la tapa inferior (podría haber sido de otra manera) si es que se ha detectado que hay.
                if(tapaInferior)
                    vertices.push_back(verticeTapaInferior);
                //Después lo hacemos con la superior
                if(tapaSuperior)
                    vertices.push_back(verticeTapaSuperior);

                cout << "Numero de vertices generados con tapas: " << vertices.size() << endl;

                //## 4.1 Como es posible que queramos repetir el proceso de revolucionar (en tiempo de ejecución) no se cargará de nuevo el perfil.
                //       Entonces tendremos que devolver los vertices tapas a sus lugares de origen para que el proceso pueda volver a realizarse
                //       tantas veces como queramos.
                         if(tapaInferior)
                            //Introducimos el vertice de la tapa inferior al princio del vector
                            perfil.insert(perfil.begin(),verticeTapaInferior);

                         if(tapaSuperior)
                            //Introducimos el vértice de la tapa superior al final del perfil.
                            perfil.insert(perfil.end(),verticeTapaSuperior);

            // ##5## Generamos las caras según tengamos o no tapas. Podemos tener una (cualquiera de las dos), las dos o ninguna en cuyo cas pasaríamos de esta sección.

                //Decisión de procesado de las caras inferiores.
                if(tapaInferior){
                    //1ºObtenemos la posición en el vector de vértices del vértice Tapa Inferior (Ti)
                    int posTi=0;
                    //Si sólo existe el vértice de tapa inferior esta posición será la ultima del vector.
                    if(!tapaSuperior)
                        posTi=vertices.size()-1;
                    //Si existen ambos vértices la tapa inferior se encontrará en la penúltima posición del vector.
                    if(tapaSuperior)
                        posTi=vertices.size()-2;

                    cout << "posTi" << posTi << endl;

                    //2ºProcesamos las caras  de la tapa inferior, usando ese valor.
                        //llamada a la función procesa tapas inferiores.
                        generaCarasTapaInferior(numRev, posTi,nVPST);
                }

                if(tapaSuperior){
                    //1ºObtenemos la posición el vector del vértice que compone la Tapa Superior (Ts)
                    int posTs=0;
                    //Si sólo existe el vértice de tapa inferior esta posición será la última del vector, pero aún exisiendo esta, el vertice
                    //también estaría en la última posición en el caso de existir por lo que entonces:
                    posTs=vertices.size()-1;

                    cout << "posTs" << posTs << endl;

                    //2ºProcesamos las caras de la tapa superior
                        generaCarasTapaSuperior(numRev,posTs,nVPST,nVST);
                }




                calculaNormalesCaras();
                calculaBaricentrosCaras();




        } //###Fin de revoluciona




        void vaciaFigura(){

            /*Si queremos aumentar el número de revoluciones en tiempo de ejecución el objeto debe de nuevo revolocionarse ya que los
            nuevos vértices tendrán posiciones totalmente distintas a las anteriores además se crearaán otras caras totalmente distintas
            a las anteriores. Por esto debemos de vaciar cualquier contenido que tuvieramos en ambos vectors previamente para almacenar el nuevo.
            */
            //Eliminamos todos lo vértices almacenados.
            vertices.clear();
            //Eliminamos todas las caras generadas almacenadas.
            caras.clear();

            normales.clear();

            baricentros.clear();

            //El perfil no se vacía porque su contenido 1º tiene que seguir leyendose y 2º no va a variar.
        }
};
#endif

