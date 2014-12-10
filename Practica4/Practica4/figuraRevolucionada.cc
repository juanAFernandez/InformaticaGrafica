#include "figuraRevolucionada.h"
//#include "variablesControl.h"

bool DEBUGG=false;

void figuraRevolucionada::generaCarasCentral(int numRev, int numVP, double gradosInicial, double gradosFinal){


            int verticeA, verticeB, verticeC;
            int elementosVector=vertices.size();

            /*
            if(DEBUGG){
                cout << "Numero de revoluciones: " << numRev << endl;
                cout << "Numero de vertices por perfil: " << numVP << endl;
                cout << "Numero total de vertices generados: " << elementosVector << endl;
            }*/


            //Descomentar aquí:

            //##############################################

            //No olvidar: descomentar lineas siguientes cuando se resuelva la inclusión de las variables de control para que
            //genere las últimas caras que faltan en el caso de que la figura sea de 0 a 360 grados.

            //#############################################


            //Si la figura es completa hay que procesar las últimas caras
            if(gradosInicial==0.0 && gradosFinal==360.0)
                numRev++;



            //### Generando las caras PAR:
            for(int i=0; i<numVP-1; i++){
                for(int j=0; j<numRev-1; j++){
                    verticeA=(((j*numVP)+i)%elementosVector);
                    verticeC=(((j*numVP)+(numVP+i))%elementosVector);
                    verticeB=(((j*numVP)+(1+i))%elementosVector);

                        //cout << "Cara PAR generada n. "<< verticeA << " "<< verticeB << " "<< verticeC << endl;
                    //Introduciendo la cara
                    setCaraManual(verticeA,verticeB,verticeC);


                }
            }

            cout << "Generadas " << caras.size() << " caras." << endl;


            //### Generando las caras IMPAR:
            for(int i=0; i<numVP-1; i++)
                for(int j=0; j<numRev-1; j++){
                    verticeA=(((j*numVP)+(numVP+i))%elementosVector);
                    verticeC=((verticeA+1)%elementosVector);
                    verticeB=(((j*numVP)+(1+i))%elementosVector);
                   // if(DEBUGG)
                     //   cout << "Cara IMPAR generada n. "<< verticeA << " "<< verticeB << " "<< verticeC << endl;
                    //Introduciendo la cara
                    setCaraManual(verticeA,verticeB,verticeC);

                }
            cout << "Generadas " << caras.size() << " caras." << endl;
            //eliminarUltimaCara();
            //eliminarUltimaCara();
          //  if(DEBUGG){
            //    cout << "Numero total de caras generados: " << caras.size() << endl;


}

void figuraRevolucionada::generaCarasTapaInferior(int numRev, int posTi, int nVPST, double gradosInicial, double gradosFinal){
            /*
            cout << "numero de revoluciones: " << numRev << endl;
            cout << "posición del vertice central de la tapa inferior: " << posTi << endl;
            cout << "numero de vertices del perfil sin tapa: " << nVPST << endl;
            cout << ((0+1)*nVPST) << endl;
            */

            //Si la figura es completa hay que procesar la última cara
            if(gradosInicial==0.0 && gradosFinal==360.0)
                numRev++;


            //No es necesario generar el verticeA porque siempre será el mismo: posTi
            int verticeB, verticeC;
            for(int i=0; i<numRev-1; i++){
                verticeC=((i+1)*nVPST)%posTi;
                verticeB=((i*nVPST)%posTi);
                setCaraManual(posTi,verticeB,verticeC);
                //cout << "Cara tapa inferior generada: ["<<posTi<<" "<<verticeB <<" "<<verticeC <<"]"<<endl;
            }

}

void figuraRevolucionada::generaCarasTapaSuperior(int numRev, int posTs, int nVPST, int nVST, double gradosInicial, double gradosFinal){
            //No es necesario general el vértice B ya que es siempre el mismo
             //cout << "numero de revoluciones: " << numRev << endl;
             //cout << "posición del vertice central de la tapa inferior: " << posTs << endl;
             //cout << "numero de vertices del perfil sin tapa: " << nVPST << endl;
             //cout << "numero de vertices  sin tapa: " << nVST << endl;

             //Si la figura es completa hay que procesar la última cara
            if(gradosInicial==0.0 && gradosFinal==360.0)
                numRev++;

             int verticeA, verticeC;
            for(int i=0; i<numRev-1; i++){
                verticeC=((nVPST*(i+1))+(nVPST-1))%nVST;
                verticeA=(verticeC+(nVST-nVPST))%nVST;
                setCaraManual(verticeA, posTs, verticeC);
                //cout << "Cara tapa superior generada: ["<<verticeA<<" "<<posTs <<" "<<verticeC <<"]"<<endl;
            }
}

void figuraRevolucionada::cargarPerfil(char *nombreFichero){

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

void figuraRevolucionada::cargarPerfil(vector <_vertex3f> vectorPerfil){
            for(int i=0; i<vectorPerfil.size(); i++)
                perfil.push_back(vectorPerfil[i]);
}

void figuraRevolucionada::muestraPerfil(){
    cout << "Vertices del perfil de la figura " << nombreFigura << " :" << endl;
    for(int i=0; i<perfil.size(); i++)
        cout << "Vertice n." << i << " [" << perfil[i].x << " " << perfil[i].y << " " << perfil[i].z << "]" << endl;
}

void figuraRevolucionada::revoluciona(int numRev, float gradosInicial, float gradosFinal){

            //Atención: El perfil es una estructura de datos distinta de nuestro vector de vertices, hay que pasar la información a este,
            //que es lo que se hace cuando se pasa a revolucionar, se leen datos del perfil y se introducen en el vector de vértices
            //de nuestra nueva figura revolucionada.

            // #ALGORITMO# //

            //Si activamos esto se hace un corte por cada revolción.
//            numRev=gradosFinal-gradosInicial;

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

                //gradosFinal+=gradosInicial;

                //##Inicio de la revolución
                _vertex3f nuevoVertice;
                //La circuferencia la componen 360º
                //En el caso de ser 360º serían 90º cada porción, es decir el perfil de la primera revolución formaría
                //90º respecto al original, así con todos.


                float gradosPerfilActual, gradosPorcion;

                if(gradosInicial==0.0 && gradosFinal==360.0){
                    cout << "All right!";
                    gradosPorcion=gradosFinal/numRev;
                    gradosPerfilActual=gradosPorcion;
                    for(int i=0; i<perfil.size(); i++)
                        setVerticeManual(perfil[i].x, perfil[i].y, perfil[i].z );
                }else{

                    gradosPorcion=(gradosFinal-gradosInicial)/(numRev-1);

                    gradosPerfilActual=gradosInicial;

                }


                float radio;



                //Repetimos el proceso tantas veces como revoluciones queramos hacer.

                for(int i=0; i<numRev; i++){


                    //Núcleo del algoritmo, que se realiza por cada revolución.
                    for(int j=0; j<perfil.size(); j++){
                        //Ejecutado tantas veces como vertices tenga el perfil para general otro pero con una ferencia de
                        //grados como se pretende.

                        //Se obtiene el radio del vertice del perfil.
                        radio=perfil[j].x;



                            cout << "gradosPerfilActual: " << gradosPerfilActual << endl;


                        nuevoVertice.x=fabs(radio)*cos(gradosARadianes(gradosPerfilActual));
                        //La coordenada Y del vértice del perfil en cuestión NO CAMBIA por ser el eje de rotación. (la altura del punto se mantiene)
                        nuevoVertice.y=perfil[j].y;
                        nuevoVertice.z=fabs(radio)*sin(gradosARadianes(gradosPerfilActual));


                        if(false)
                            cout << "Generado vértice x:" << nuevoVertice.x << " y:" << nuevoVertice.y << " z:" << nuevoVertice.z <<endl;

                        setVerticeManual(nuevoVertice.x, nuevoVertice.y, nuevoVertice.z);

                    }
                    //Cuando terminamos con un perfil sumamos los grados necesarios para general el siguiente.
                    gradosPerfilActual=gradosPerfilActual+gradosPorcion;
                }
                //##Fin de la revolución

               // cout << "Numero de vertices generados sin tapas: " << vertices.size() << endl;

                //Necesitamos la variable número de vértices totales sin tapa para la función generadora de las tapas superiores.
                int nVST=vertices.size();

                //3.1 Antes de volver a introducir los "vertices tapas" procesamos las caras centrales
                //Procesa caras centrales

                //Una vez revolucionado se procede a generar las caras usando el vector de vértices obtenido:
                generaCarasCentral(numRev, perfil.size(), gradosInicial, gradosFinal);

            // ##4## Añadimos al final del nuevo vector de vértices los vértices que componen las tapas

                //Primero añadimos la tapa inferior (podría haber sido de otra manera) si es que se ha detectado que hay.
                if(tapaInferior)
                    vertices.push_back(verticeTapaInferior);
                //Después lo hacemos con la superior
                if(tapaSuperior)
                    vertices.push_back(verticeTapaSuperior);

                //cout << "Numero de vertices generados con tapas: " << vertices.size() << endl;

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
                        generaCarasTapaInferior(numRev, posTi,nVPST,gradosInicial,gradosFinal);
                }

                if(tapaSuperior){
                    //1ºObtenemos la posición el vector del vértice que compone la Tapa Superior (Ts)
                    int posTs=0;
                    //Si sólo existe el vértice de tapa inferior esta posición será la última del vector, pero aún exisiendo esta, el vertice
                    //también estaría en la última posición en el caso de existir por lo que entonces:
                    posTs=vertices.size()-1;

                    cout << "posTs" << posTs << endl;

                    //2ºProcesamos las caras de la tapa superior
                        generaCarasTapaSuperior(numRev,posTs,nVPST,nVST,gradosInicial,gradosFinal);
                }



            //Después de revolucionar realizamos la gestión de las normales para iluminación.

                calculaNormalesCaras();
                calculaBaricentrosCaras();
                calculaNormalesVertices();




}

void figuraRevolucionada::vaciaFigura(){

            /*Si queremos aumentar el número de revoluciones en tiempo de ejecución el objeto debe de nuevo revolocionarse ya que los
            nuevos vértices tendrán posiciones totalmente distintas a las anteriores además se crearaán otras caras totalmente distintas
            a las anteriores. Por esto debemos de vaciar cualquier contenido que tuvieramos en ambos vectors previamente para almacenar el nuevo.
            */
            //Eliminamos todos lo vértices almacenados.
            vertices.clear();
            //Eliminamos todas las caras generadas almacenadas.
            caras.clear();

            normales.clear();

            normalesVertices.clear();

            baricentros.clear();

            //El perfil no se vacía porque su contenido 1º tiene que seguir leyendose y 2º no va a variar.
        }
