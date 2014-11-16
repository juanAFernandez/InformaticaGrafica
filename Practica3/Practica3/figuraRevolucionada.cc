#include "figuraRevolucionada.h"
//#include "variablesControl.h"

bool DEBUGG=false;

void figuraRevolucionada::generaCarasCentral(int numRev, int numVP){


            int verticeA, verticeB, verticeC;
            int elementosVector=vertices.size();

            /*
            if(DEBUGG){
                cout << "Numero de revoluciones: " << numRev << endl;
                cout << "Numero de vertices por perfil: " << numVP << endl;
                cout << "Numero total de vertices generados: " << elementosVector << endl;
            }*/


            //Descomentar aqu�:

            //##############################################

            //No olvidar: descomentar lineas siguientes cuando se resuelva la inclusi�n de las variables de control para que
            //genere las �ltimas caras que faltan.

            //#############################################

            //if(GRADOS_INICIAL==0.0 && GRADOS_FINAL==360.0)
              //  numRev++;



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

void figuraRevolucionada::generaCarasTapaInferior(int numRev, int posTi, int nVPST){
            /*
            cout << "numero de revoluciones: " << numRev << endl;
            cout << "posici�n del vertice central de la tapa inferior: " << posTi << endl;
            cout << "numero de vertices del perfil sin tapa: " << nVPST << endl;
            cout << ((0+1)*nVPST) << endl;
            */
            //No es necesario generar el verticeA porque siempre ser� el mismo: posTi
            int verticeB, verticeC;
            for(int i=0; i<numRev-1; i++){
                verticeC=((i+1)*nVPST)%posTi;
                verticeB=((i*nVPST)%posTi);
                setCaraManual(posTi,verticeB,verticeC);
                //cout << "Cara tapa inferior generada: ["<<posTi<<" "<<verticeB <<" "<<verticeC <<"]"<<endl;
            }

}

void figuraRevolucionada::generaCarasTapaSuperior(int numRev, int posTs, int nVPST, int nVST){
            //No es necesario general el v�rtice B ya que es siempre el mismo
             //cout << "numero de revoluciones: " << numRev << endl;
             //cout << "posici�n del vertice central de la tapa inferior: " << posTs << endl;
             //cout << "numero de vertices del perfil sin tapa: " << nVPST << endl;
             //cout << "numero de vertices  sin tapa: " << nVST << endl;
             int verticeA, verticeC;
            for(int i=0; i<numRev-1; i++){
                verticeC=((nVPST*(i+1))+(nVPST-1))%nVST;
                verticeA=(verticeC+(nVST-nVPST))%nVST;
                setCaraManual(verticeA, posTs, verticeC);
                //cout << "Cara tapa superior generada: ["<<verticeA<<" "<<posTs <<" "<<verticeC <<"]"<<endl;
            }
}

void figuraRevolucionada::revoluciona(int numRev, float gradosInicial, float gradosFinal){





            //Atenci�n: El perfil es una estructura de datos distinta de nuestro vector de vertices, hay que pasar la informaci�n a este,
            //que es lo que se hace cuando se pasa a revolucionar, se leen datos del perfil y se introducen en el vector de v�rtices
            //de nuestra nueva figura revolucionada.

            // #ALGORITMO# //

            //Si activamos esto se hace un corte por cada revolci�n.
//            numRev=gradosFinal-gradosInicial;

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

            //Mostramos por pantalla los v�rtices tapar superior e inferior en el caso de existir.
            if(tapaInferior)
                cout << "TAPA INFERIOR: " << "[" << perfil[0].x << " " << perfil[0].y << " " << perfil[0].z << "]" << endl;
            if(tapaSuperior)
                cout << "TAPA SUPERIOR: " << "[" << perfil[perfil.size()-1].x << " " << perfil[perfil.size()-1].y << " " << perfil[perfil.size()-1].z << "] " << endl;


            // ##2## Detectadas las tapas las sacamos del perfil (recordamos que perfil es del tipo vector de la STL, usamos algunas funciones)

            //Mostramos el perfil.

            muestraPerfil();

            //Declaramos un par de v�rtices temporales.
            _vertex3f verticeTapaSuperior, verticeTapaInferior;

            if(tapaInferior){
                //Copiamos el v�rtice en el temporal
                verticeTapaInferior=perfil.front();
                //Eliminamos el v�rtice del perfil.
                perfil.erase(perfil.begin());
            }

            if(tapaSuperior){
                //Copiamos el v�rtice en el temporal
                verticeTapaSuperior=perfil.back();
                //Eliminamos el v�rtice del perfil.
                perfil.erase(perfil.end());
            }

            //Guardamos en una variable el n�mero de v�rtices del perfil sin tapas. nVPST
            int nVPST=perfil.size();

            muestraPerfil();


            // ##3## Revolucionamos los vectores del perfil sin los v�rtices tapas (si los hubiera). Que ser�a la secci�n central s�lo.


                //Revolucionado de los v�rtices de perfil y a�adidos a nueestro vector de v�rtices de nuestra figura.

                //gradosFinal+=gradosInicial;

                //##Inicio de la revoluci�n
                _vertex3f nuevoVertice;
                //La circuferencia la componen 360�
                //En el caso de ser 360� ser�an 90� cada porci�n, es decir el perfil de la primera revoluci�n formar�a
                //90� respecto al original, as� con todos.


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


                    //N�cleo del algoritmo, que se realiza por cada revoluci�n.
                    for(int j=0; j<perfil.size(); j++){
                        //Ejecutado tantas veces como vertices tenga el perfil para general otro pero con una ferencia de
                        //grados como se pretende.

                        //Se obtiene el radio del vertice del perfil.
                        radio=perfil[j].x;



                            cout << "gradosPerfilActual: " << gradosPerfilActual << endl;


                        nuevoVertice.x=fabs(radio)*cos(gradosARadianes(gradosPerfilActual));
                        //La coordenada Y del v�rtice del perfil en cuesti�n NO CAMBIA por ser el eje de rotaci�n. (la altura del punto se mantiene)
                        nuevoVertice.y=perfil[j].y;
                        nuevoVertice.z=fabs(radio)*sin(gradosARadianes(gradosPerfilActual));


                        if(false)
                            cout << "Generado v�rtice x:" << nuevoVertice.x << " y:" << nuevoVertice.y << " z:" << nuevoVertice.z <<endl;

                        setVerticeManual(nuevoVertice.x, nuevoVertice.y, nuevoVertice.z);

                    }
                    //Cuando terminamos con un perfil sumamos los grados necesarios para general el siguiente.
                    gradosPerfilActual=gradosPerfilActual+gradosPorcion;
                }
                //##Fin de la revoluci�n

               // cout << "Numero de vertices generados sin tapas: " << vertices.size() << endl;

                //Necesitamos la variable n�mero de v�rtices totales sin tapa para la funci�n generadora de las tapas superiores.
                int nVST=vertices.size();

                //3.1 Antes de volver a introducir los "vertices tapas" procesamos las caras centrales
                //Procesa caras centrales

                //Una vez revolucionado se procede a generar las caras usando el vector de v�rtices obtenido:
                generaCarasCentral(numRev, perfil.size());

            // ##4## A�adimos al final del nuevo vector de v�rtices los v�rtices que componen las tapas

                //Primero a�adimos la tapa inferior (podr�a haber sido de otra manera) si es que se ha detectado que hay.
                if(tapaInferior)
                    vertices.push_back(verticeTapaInferior);
                //Despu�s lo hacemos con la superior
                if(tapaSuperior)
                    vertices.push_back(verticeTapaSuperior);

                //cout << "Numero de vertices generados con tapas: " << vertices.size() << endl;

                //## 4.1 Como es posible que queramos repetir el proceso de revolucionar (en tiempo de ejecuci�n) no se cargar� de nuevo el perfil.
                //       Entonces tendremos que devolver los vertices tapas a sus lugares de origen para que el proceso pueda volver a realizarse
                //       tantas veces como queramos.
                         if(tapaInferior)
                            //Introducimos el vertice de la tapa inferior al princio del vector
                            perfil.insert(perfil.begin(),verticeTapaInferior);

                         if(tapaSuperior)
                            //Introducimos el v�rtice de la tapa superior al final del perfil.
                            perfil.insert(perfil.end(),verticeTapaSuperior);

            // ##5## Generamos las caras seg�n tengamos o no tapas. Podemos tener una (cualquiera de las dos), las dos o ninguna en cuyo cas pasar�amos de esta secci�n.

                //Decisi�n de procesado de las caras inferiores.
                if(tapaInferior){
                    //1�Obtenemos la posici�n en el vector de v�rtices del v�rtice Tapa Inferior (Ti)
                    int posTi=0;
                    //Si s�lo existe el v�rtice de tapa inferior esta posici�n ser� la ultima del vector.
                    if(!tapaSuperior)
                        posTi=vertices.size()-1;
                    //Si existen ambos v�rtices la tapa inferior se encontrar� en la pen�ltima posici�n del vector.
                    if(tapaSuperior)
                        posTi=vertices.size()-2;

                    cout << "posTi" << posTi << endl;

                    //2�Procesamos las caras  de la tapa inferior, usando ese valor.
                        //llamada a la funci�n procesa tapas inferiores.
                        generaCarasTapaInferior(numRev, posTi,nVPST);
                }

                if(tapaSuperior){
                    //1�Obtenemos la posici�n el vector del v�rtice que compone la Tapa Superior (Ts)
                    int posTs=0;
                    //Si s�lo existe el v�rtice de tapa inferior esta posici�n ser� la �ltima del vector, pero a�n exisiendo esta, el vertice
                    //tambi�n estar�a en la �ltima posici�n en el caso de existir por lo que entonces:
                    posTs=vertices.size()-1;

                    cout << "posTs" << posTs << endl;

                    //2�Procesamos las caras de la tapa superior
                        generaCarasTapaSuperior(numRev,posTs,nVPST,nVST);
                }



            //Despu�s de revolucionar realizamos la gesti�n de las normales para iluminaci�n.

                calculaNormalesCaras();
                calculaBaricentrosCaras();
                calculaNormalesVertices();




}

_vertex3f figuraRevolucionada::productoVectorial(_vertex3f ab, _vertex3f ac){
                _vertex3f producto;
                producto.x=(ab.y*ac.z)-(ab.z*ac.y);
                producto.y=(ab.z*ac.x)-(ab.x*ac.z);
                producto.z=(ab.x*ac.y)-(ab.y*ac.x);
            return producto;
}

void figuraRevolucionada::calculaNormalesCaras(){

            //Dado una cara (un tri�ngulo formado por tres v�rtices) vamos a obtener la normal que forman los vectores que definen esta.

            /*Sacamos dos vectores y como queremos que la normal vaya hacia el exterior de la cara somos cuidadosos a la hora de
            elegir los v�rtices y los vectores para los que sacamos la normal. Como tenemos tres v�rtices v1, v2 y v3 tendremos los vectores
            A y B que ir�n de V3 a v1 y de V3 a V2 respectivamente. El c�lculo de un vector mediantes dos puntos se reliza mediante la resta
            de los puntos del v�rtice extremo al origen. As� si tenemos que B=v3-->v2, el vector B son las coordenadas de v2 - las de v3.*/

            //Variables que usaremos en el proceso:
            _vertex3f a, b, c; //V�rtices que extraeremos de la cara.
            _vertex3f ab,ac; //Vectores rsultantes de los puntos.
            _vertex3f normal; //Vector normal resultante del proceso.

            float modulo; //Para la normalizci�n de la normal.

            //cout << endl << endl << " ### Procesamiento de normales ### " << endl;

            //El proceso debe repetirse en tantas caras como tengamos.
            for(unsigned int i=0; i<caras.size(); i++){

                //cout << "Procesando cara " << i << endl;

                //Extraemos los v�rtices de la cara:
                a=vertices[caras[i]._0];
                b=vertices[caras[i]._1];
                c=vertices[caras[i]._2];

                //cout << "Extracci�n de los vertices" << endl;
                //cout << "Vertices de la cara " << i << " :" << endl;
                //muestraVertice(a); muestraVertice(b); muestraVertice(c);
                //cout << endl;


                //A partir de esos v�rtices obtenemos los vectores

                    //A= v1-->v2 ==> v2-v1 = [(v2x-v1x),(v2y-v1y),(v2x-v1y)]
                    ab.x=b.x-a.x; ab.y=b.y-a.y; ab.z=b.z-a.z;

                    //cout << "Vector A: "<< endl;
                    //muestraVertice(A);

                    //B= v1-->v3 ==> v3-v1 = [(v3x-v1x),(v3y-v1y),(v3z-v1z)]
                    ac.x=c.x-a.x; ac.y=c.y-a.y; ac.z=c.z-a.z;

                    //cout << "Vector B: "<< endl;
                    //muestraVertice(B);

                //Hacemos el producto vectorial mediante la f�rumla abreviada extraida de (http://es.wikipedia.org/wiki/Producto_vectorial)


                normal=productoVectorial(ab,ac);

                //cout << "NORMAL antes de normalizar: " << endl;
                //muestraVertice(normal);

                //Antes de finalizar hay que normalizar la normal (divi�ndola entre su m�dulo)
                normal.normalize();

                //cout << "NORMAL **normalizada**: " << endl;
                //muestraVertice(normal);

                //cout << "normal:" << normal.x << " " << normal.y << " " << normal.z << endl;

                //Introducimos la normal en el vector de normales.
                normales.push_back(normal);

                //cout << "normal:" << normal.x << " " << normal.y << " " << normal.z << endl;
               // cout << endl << endl;

            }

            //cout << "N�mero de normales generadas: " << normales.size() << endl;
            calculaBaricentrosCaras();

        }

void figuraRevolucionada::calculaNormalesVertices(){
            //Sumaresmoa la normal de cada cara a la normal de sus tres v�rtices.
            _vertex3f normal(0,0,0);
            //Inicializo todos las normales de los vectores a 0
            for(unsigned int i=0; i<vertices.size(); i++)
                normalesVertices.push_back(normal);

            //Despu�s recorro todos las caras y le sumo su normal a los v�rtices que la forman:
            for(unsigned int i=0; i<caras.size(); i++){
                normalesVertices[caras[i]._0]+=normales[i];
                normalesVertices[caras[i]._1]+=normales[i];
                normalesVertices[caras[i]._2]+=normales[i];
            }

            //Por �ltimo normalizamos todos las normales de los v�rtices que hemos calculado:
            for(unsigned int i=0; i<normalesVertices.size(); i++)
                normalesVertices[i].normalize();
}

void figuraRevolucionada::dibujaBaricentros(){
            glColor3fv(NEGRO);
            glPointSize(5);
            glBegin(GL_POINTS);
                for(unsigned int i=0; i<caras.size(); i++)
                    glVertex3f(baricentros[i].x,baricentros[i].y,baricentros[i].z);
            glEnd();
}

void figuraRevolucionada::dibujarNormalesVertices(){
            glColor3fv(ROJO);
            glBegin(GL_LINES);
                for(unsigned int i=0; i<normalesVertices.size(); i++){
                    glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
                    glVertex3f(vertices[i].x+normalesVertices[i].x, vertices[i].y+normalesVertices[i].y, vertices[i].z+normalesVertices[i].z);
                }
            glEnd();
}

void figuraRevolucionada::dibujarNormales(){
            //Teniendo la normal y el baricentro, �C�mo dibujo una linea que salga de la caras?
            glBegin(GL_LINES);
                for(unsigned int i=0; i<caras.size(); i++){
                    glVertex3f(baricentros[i].x,baricentros[i].y,baricentros[i].z);
                    glVertex3f(baricentros[i].x+normales[i].x, baricentros[i].y+normales[i].y, baricentros[i].z+normales[i].z);
                }
            glEnd();
}

void figuraRevolucionada::calculaBaricentrosCaras(){
            //Proceso que se repite como tantas caras tengamos.
            _vertex3f baricentro;
            for(int i=0; i<caras.size(); i++){
                baricentro.x=((vertices[caras[i]._0].x + vertices[caras[i]._1].x + vertices[caras[i]._2].x)/3);
                baricentro.y=((vertices[caras[i]._0].y + vertices[caras[i]._1].y + vertices[caras[i]._2].y)/3);
                baricentro.z=((vertices[caras[i]._0].z + vertices[caras[i]._1].z + vertices[caras[i]._2].z)/3);

                //cout << "Baricentro de la cara " << i << endl;
                //muestraVertice(baricentro);

                baricentros.push_back(baricentro);
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
                //Habr�a que cambiar la forma de introducir los vertices.
                perfil.push_back(swap);
            }

            //Cerramos el fichero.
            fichero.close();
}

void figuraRevolucionada::cargarPerfil(vector <_vertex3f> vectorPerfil){
            for(int i=0; i<vectorPerfil.size(); i++)
                perfil.push_back(vectorPerfil[i]);
}

void figuraRevolucionada::vaciaFigura(){

            /*Si queremos aumentar el n�mero de revoluciones en tiempo de ejecuci�n el objeto debe de nuevo revolocionarse ya que los
            nuevos v�rtices tendr�n posiciones totalmente distintas a las anteriores adem�s se creara�n otras caras totalmente distintas
            a las anteriores. Por esto debemos de vaciar cualquier contenido que tuvieramos en ambos vectors previamente para almacenar el nuevo.
            */
            //Eliminamos todos lo v�rtices almacenados.
            vertices.clear();
            //Eliminamos todas las caras generadas almacenadas.
            caras.clear();

            normales.clear();

            normalesVertices.clear();

            baricentros.clear();

            //El perfil no se vac�a porque su contenido 1� tiene que seguir leyendose y 2� no va a variar.
        }
