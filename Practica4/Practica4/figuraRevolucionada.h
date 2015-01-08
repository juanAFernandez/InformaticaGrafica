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
        void generaCarasCentral(int numRev, int numVP, double gradosInicial=0.0, double gradosFinal=360.0);

        /**
        * @brief Para generar las caras de la tapa inferior en caso de que esta existiera.
        * @param numRev Número de revoluciones que se han aplicado sobre el perfil.
        * @param posTi Posición en el vector de vértices del punto en el eje Y representativo de la tapa inferior.
        * @param nVPST Número de vertices del perfil original con el que formamos la figura sin contar los vértices de las tapas.
        */
        void generaCarasTapaInferior(int numRev, int posTi, int nVPST, double gradosInicial=0.0, double gradosFinal=360.0);

        /**
        * @brief Para generar las caras de la tapa superior en caso de que esta existiera.
        * @param numRev Número de revoluciones que se han aplicado sobre el perfil.
        * @param posTs Posición en el vector de vértices del punto en el eje Y representativo de la tapa superior.
        * @param nVPST Número de vertices del perfil original con el que formamos la figura sin contar los vértices de las tapas.
        * @param nVST Número de vertices del vector vértices sin contar los vértices de las tapas, como máximo sin dos.
        */
        void generaCarasTapaSuperior(int numRev, int posTs, int nVPST, int nVST, double gradosInicial=0.0, double gradosFinal=360.0);

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



        float distanciaEntreVertices(_vertex3f verticeA, _vertex3f verticeB){
            return sqrt( ((verticeB.x-verticeA.x)*(verticeB.x-verticeA.x)) +  ((verticeB.y-verticeA.y)*(verticeB.y-verticeA.y))   );
        }

        vector<float> calculaDistancias(){

            // ## Cálculo acumulado, nos es útil para el algoritmo posterior de calculo de texturas.
            // ## Podrías haberse calculado sólo por secciones sin el acumulado.

            //muestraPerfil();
            float acumulado=0.0;
            vector<float> distanciasTemporal;
            for(int i=0; i<perfil.size()-1; i++){
                acumulado+=distanciaEntreVertices(perfil[i],perfil[i+1]);
                distanciasTemporal.push_back(acumulado);
            }
            return distanciasTemporal;
        }

        float reglaTresSimplificada(float valor, float max){
            //Teniendo en cuenta que siempre se usa 1
            return (valor/max);
        }

        vector<float> calculaDistanciasRelativas( vector <float> distancias){
            /*Nuestro perfil está dividido en secciones de longitud variable que suman un total de la longitud total
             del perfil, que será n. Pero en el calculo de las coordenadas de textura nos hace falta que mediante una
             regla de tres estas distancias se ajusten como si la longitud del segmento fuera 1, ques como será la imagen
             que se utilizará de textura. Por esto se debe de realizar esta transformación.
            */
            vector <float> distanciasRelativasTemporal;

            for(int i=0; i<distancias.size(); i++)
                distanciasRelativasTemporal.push_back(reglaTresSimplificada(distancias[i],distancias[distancias.size()-1]));

            return distanciasRelativasTemporal;
        }


        void generaCoordenadasTextura(int numRevoluciones){


            if(vertices.empty()){
                cout << "El perfil aún no ha sido revolucionado" << endl;
            }

            if(cTs.empty()){

            cout << endl << endl << "Generando coordenadas de TEXTURA" << endl;
            cout << "Vertices en el vector de vértices: " << vertices.size() << endl;
            cout << "Número de revoluciones: " << numRevoluciones << endl;
            cout << "Número de vértices en el perfil: " << perfil.size() << endl;
            //cout << "Generadas " << cTs.size() << "coordenadas";

            //Calulamos la longitud de todos los vertices del pefil de forma acumulada, podría hacerse de otra manera
            //pero así ahorramos operaciones después.
            vector<float>distancias;
            distancias=calculaDistancias();

            cout << "Contenido de. vector distancias" << endl;
            for(int i=0; i<distancias.size(); i++)
                cout << "Longitud seccion: " << i << " : " << distancias[i] << endl;

            //Una vez que tenemos las distancias acumuladas del perfil calculamos las distancias relativas:
            vector<float>distanciasRelativas;
            distanciasRelativas=calculaDistanciasRelativas(distancias);

            cout << "Contenido de. vector distanciasRelativas" << endl;
            for(int i=0; i<distanciasRelativas.size(); i++)
                cout << "Longitud seccion: " << i << " : " << distanciasRelativas[i] << endl;


           // --> ultimo!//Una vez calculadas las distancias pasamos a calcular las coordenadas de textura:
            /* Debe de haber tantas coordenadas de textura como vértices en el vector de vértices para procesar
            después el dibujado de la textura. Por tanto necesitaremos un vector que repita tantas veces como revoluciones
            el vertices superior e inferior (tapas) del perfil en el caso de que los haya.*/

            //Es por tanto probable que haya que volver a revolucionar el perfil para conseguir el objetivo.


            //En esta segunda versión al no considerara tapas no vamos a necesitar modificar nada de nada!
            float razon=(float)1/numRevoluciones;

            //Inicializamos las primeras coordenadas de textura correspondientes al perfil inicial de nuestro modeo revolucionado.
            cTs.push_back({1,0});
            for(int i=0; i<perfil.size()-1; i++){
                //El valor de X se mantiene constante a 1 durante todo el perfil.
                //Es el valor de Y el que varía desde 0 hasta 1 siguiendo el vector de distancias relativas.
                cTs.push_back({1,distanciasRelativas[i]});
            }

            //Por depuración para ver el estado después de inicializar el primer vértice de texturas:
            //muestraCoordenadasTextura();

            //Una vez inicializado el primer vértice en texturas se completa el resto:

            float distancia=1.0;
            for(int i=0; i<numRevoluciones; i++){
                distancia-=razon;
                //Rellenamos el perfil
                for(int i=0; i<perfil.size()-1; i++){
                    if(i==0)
                        cTs.push_back({distancia,0});
                    cTs.push_back({distancia,distanciasRelativas[i]});
                }
            }

             //Por depuración para ver el estado después de añadir el resto de coor. de textura.
             //muestraCoordenadasTextura();


            }else{
                cout << "Ya han sido calculadas" << endl;
                muestraCoordenadasTextura();
            }

        }

        void dibujarPerfil(){

            //Dibujo de los vértices del perfil
            glColor3fv(VERDE);
            glPointSize(4);
            glBegin(GL_POINTS);
                    for(unsigned int i=0; i<perfil.size(); i++)
                        glVertex3f(perfil[i].x,perfil[i].y,perfil[i].z);
            glEnd();

            //Dibujo de las aristas del perfil:
            glColor3fv(GRIS_CLARO);
            for(unsigned int i=0; i<perfil.size()-1; i++){
                glBegin(GL_LINES);
                    //Recordando que caras[0]._0 es: cara nº 0 vértice nº0
                    glVertex3f(perfil[i].x, perfil[i].y ,perfil[i].z);
                    glVertex3f(perfil[i+1].x, perfil[i+1].y ,perfil[i+1].z);
                glEnd();
            }


        }








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

