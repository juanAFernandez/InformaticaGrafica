#include "figuraSolida.h"
#include "materiales.h"

int figuraSolida::numeroCaras(){
    return caras.size();
}

void figuraSolida::setCaraManual(unsigned int verticeA, unsigned int verticeB, unsigned int verticeC){
    _vertex3i caraTemporal;
    caraTemporal.x=verticeA;
    caraTemporal.y=verticeB;
    caraTemporal.z=verticeC;
    caras.push_back(caraTemporal);
}

void figuraSolida::eliminarUltimaCara(){
            caras.pop_back();
}

void figuraSolida::dibujarCaras(string seccion, string modo, const GLfloat color[]){

            //Usamos la directiva GL_TRIANGLES que necesita que se le pasen tres vectores.
            glBegin(GL_TRIANGLES);

                //Recorremos todas las caras para dibujar cada una.
                for(unsigned i=0; i<caras.size(); i++){

                    //Para dibujar al completo la figura (todas sus caras) entramos en esta secci�n:
                    if(seccion=="todo"){

                        //Si queremos que parezca un objeto s�lido establecemos el mismo color para todas las caras.
                       if(modo=="solido")
                            //Establecemos el mismo color para todos los pasos del bucle, es decir, para todas las caras.
                           // if(color=="gris")
                             //   glColor3fv(GRIS_CLARO);
                            //if(color=="amarillo")
                              glColor3fv(color);

                        //Si queremos dibujar el objeto en modo ajedrez pintamos una cara de un color y otra de otro.
                        if(modo=="ajedrez"){
                            //Las caras impares de un color y las pares de otro.
                            if(i%2==0)
                                //Para las caras pares:
                                glColor3fv(GRIS_OSCURO);
                            else
                                //Para las caras impares:
                                glColor3fv(GRIS_CLARO);
                        }
                        /*Fin de la selecci�n del color. Esto se hace para cada paso del bucle, despu�s de seleccionar
                        el color con el que se va a dibujar la cara se pasa a dibujarla.*/

                        //  caras[0]._0  Primer v�rtice de la cara 0
                        glVertex3f(vertices[caras[i]._0].x, vertices[caras[i]._0].y ,vertices[caras[i]._0].z);
                        //  caras[0]._1  Segundo v�rtice de la cara 0
                        glVertex3f(vertices[caras[i]._1].x, vertices[caras[i]._1].y ,vertices[caras[i]._1].z);
                        //  caras[0]._2  Tercer v�rtice de la cara 0
                        glVertex3f(vertices[caras[i]._2].x, vertices[caras[i]._2].y ,vertices[caras[i]._2].z);
                    }//Fin de la secci�n TODO

                    //Si queremos visualizar s�lo una parte del objeto general, no la vamos a usar m�s.
                    if(seccion=="solo y+" && modo=="especial"){

                        /*Para que una cara sea dibujada los tres v�rtices que la componen tendr�n que tener sus
                        coordenadas x en la versi�n positiva del eje, para que as� la cara entera pertenezca a esa
                        secci�n del eje. Esto es extrapolable a cualquier eje y sentido.
                        */

                        //Vamos a realizar la gesti�n del color para el examen:

                        //Comprobaci�n para ver si la cara pertenece al lado positivo del eje Y
                        if( vertices[caras[i]._0].y>0 && vertices[caras[i]._1].y>0 && vertices[caras[i]._2].y>0 ){

                            //Comprobaci�n para establecer el color de si

                            if(vertices[caras[i]._0].x>0 && vertices[caras[i]._1].x>0 && vertices[caras[i]._2].x>0 &&
                               vertices[caras[i]._0].z<0 && vertices[caras[i]._1].z<0 && vertices[caras[i]._2].z<0)
                               glColor3fv(AMARILLO);

                            else if(vertices[caras[i]._0].x<0 && vertices[caras[i]._1].x<0 && vertices[caras[i]._2].x<0 &&
                               vertices[caras[i]._0].z<0 && vertices[caras[i]._1].z<0 && vertices[caras[i]._2].z<0)
                               glColor3fv(VERDE);

                            else if(vertices[caras[i]._0].x<0 && vertices[caras[i]._1].x<0 && vertices[caras[i]._2].x<0 &&
                               vertices[caras[i]._0].z>0 && vertices[caras[i]._1].z>0 && vertices[caras[i]._2].z>0)
                               glColor3fv(AZUL);

                            else if(vertices[caras[i]._0].x>0 && vertices[caras[i]._1].x>0 && vertices[caras[i]._2].x>0 &&
                               vertices[caras[i]._0].z>0 && vertices[caras[i]._1].z>0 && vertices[caras[i]._2].z>0)
                               glColor3fv(ROJO);

                            else
                               glColor3fv(GRIS_OSCURO);

                            //  caras[0]._0  Primer v�rtice de la cara 0
                            glVertex3f(vertices[caras[i]._0].x, vertices[caras[i]._0].y ,vertices[caras[i]._0].z);
                            //  caras[0]._1  Segundo v�rtice de la cara 0
                            glVertex3f(vertices[caras[i]._1].x, vertices[caras[i]._1].y ,vertices[caras[i]._1].z);
                            //  caras[0]._2  Tercer v�rtice de la cara 0
                            glVertex3f(vertices[caras[i]._2].x, vertices[caras[i]._2].y ,vertices[caras[i]._2].z);
                        }
                    }
                    //Esta funci�n con el modo ajedresz tampoco
                     if(seccion=="solo y+" && modo=="ajedrez"){

                        /*Para que una cara sea dibujada los tres v�rtices que la componen tendr�n que tener sus
                        coordenadas x en la versi�n positiva del eje, para que as� la cara entera pertenezca a esa
                        secci�n del eje. Esto es extrapolable a cualquier eje y sentido.
                        */


                        if(modo=="ajedrez"){
                            //Gesti�n del color de las caras si el modo es "ajedrez"
                            if(i%2==0)
                                //Para las caras pares:
                                glColor3fv(GRIS_OSCURO);
                            else
                                //Para las caras impares:
                                glColor3fv(GRIS_CLARO);
                        }


                        //Comprobaci�n para ver si la cara pertenece al lado positivo del eje Y
                        if( vertices[caras[i]._0].y>0 && vertices[caras[i]._1].y>0 && vertices[caras[i]._2].y>0 ){

                            //  caras[0]._0  Primer v�rtice de la cara 0
                            glVertex3f(vertices[caras[i]._0].x, vertices[caras[i]._0].y ,vertices[caras[i]._0].z);
                            //  caras[0]._1  Segundo v�rtice de la cara 0
                            glVertex3f(vertices[caras[i]._1].x, vertices[caras[i]._1].y ,vertices[caras[i]._1].z);
                            //  caras[0]._2  Tercer v�rtice de la cara 0
                            glVertex3f(vertices[caras[i]._2].x, vertices[caras[i]._2].y ,vertices[caras[i]._2].z);
                        }

                    }
                }
            glEnd();
}

void figuraSolida::dibujarCarasIluminacionPlana(const GLfloat color[]){

            //En el tipo de iluminaci�n con Suavizado Plano usamos una normal por cara.

            plasticoVerde.activar();

            glBegin(GL_TRIANGLES);
                for(unsigned i=0; i<caras.size(); i++){
                    glNormal3f(normales[i].x, normales[i].y, normales[i].z); //Normal por cara!
                    glVertex3f(vertices[caras[i]._0].x, vertices[caras[i]._0].y ,vertices[caras[i]._0].z);
                    glVertex3f(vertices[caras[i]._1].x, vertices[caras[i]._1].y ,vertices[caras[i]._1].z);
                    glVertex3f(vertices[caras[i]._2].x, vertices[caras[i]._2].y ,vertices[caras[i]._2].z);
                }
            glEnd();

}

void figuraSolida::dibujarAristas(string seccion){

            //Configuraci�n del color (RGB [0-1] )
            glColor3fv(NEGRO);

            //Configuraci�n del grosor de las lineas, por si queremos que se vean m�s gruesas.
            glLineWidth(0.5);

            /*Una cara est� compuesta por tres v�rtices, que forman tres aristas entre ellos. Entonces mandaremos
            a dibujar a OpenGl la arista que conecta los v�rtices 0 y 1 de la cara, la que forman los v�rtices
            1 y 2 y la restante con los v�rtices 2 y de nuevo 0. Con eso la cara queda formada por tres aristas.
            S�lo tenemos que repetir esa acci�n con tantas caras como tengamos => bucle for.
            */

            if(seccion=="todo"){
                for(unsigned int i=0; i<caras.size(); i++){

                    //Dibujado de la arista que conecta el v�rtice 0 con el 1
                    glBegin(GL_LINES);
                        //Recordando que caras[0]._0 es: cara n� 0 v�rtice n�0
                        glVertex3f(vertices[caras[i]._0].x, vertices[caras[i]._0].y ,vertices[caras[i]._0].z);
                        glVertex3f(vertices[caras[i]._1].x, vertices[caras[i]._1].y ,vertices[caras[i]._1].z);
                    glEnd();

                    //Dibujado de la arista que conecta el v�rtice 1 con el v�rtice 2
                    glBegin(GL_LINES);
                        glVertex3f(vertices[caras[i]._1].x, vertices[caras[i]._1].y ,vertices[caras[i]._1].z);
                        glVertex3f(vertices[caras[i]._2].x, vertices[caras[i]._2].y ,vertices[caras[i]._2].z);
                    glEnd();

                    //Dibujado de la arita que conecta el v�rtice 2 con el v�rtice 0
                    glBegin(GL_LINES);
                        glVertex3f(vertices[caras[i]._2].x, vertices[caras[i]._2].y ,vertices[caras[i]._2].z);
                        glVertex3f(vertices[caras[i]._0].x, vertices[caras[i]._0].y ,vertices[caras[i]._0].z);
                    glEnd();
                }
            }

            /*Si especificamos "s�lo x+" s�lo deben dibujarse las aristas de la cara que estamos trabajando
            //que esten en la parte positiva del eje X. Es decir, que tengan los dos v�rtices en esa secci�n.
            //Si no los tienen no deben dibujarse. */


            if(seccion=="solo y+"){
                for(unsigned int i=0; i<caras.size(); i++){

                    glBegin(GL_LINES);
                        if(vertices[caras[i]._0].y>0 && vertices[caras[i]._1].y>0 ){
                            glVertex3f(vertices[caras[i]._0].x, vertices[caras[i]._0].y ,vertices[caras[i]._0].z);
                            glVertex3f(vertices[caras[i]._1].x, vertices[caras[i]._1].y ,vertices[caras[i]._1].z);
                        }
                    glEnd();

                    glBegin(GL_LINES);
                        if(vertices[caras[i]._1].y>0 && vertices[caras[i]._2].y>0 ){
                            glVertex3f(vertices[caras[i]._1].x, vertices[caras[i]._1].y ,vertices[caras[i]._1].z);
                            glVertex3f(vertices[caras[i]._2].x, vertices[caras[i]._2].y ,vertices[caras[i]._2].z);
                        }
                    glEnd();

                    glBegin(GL_LINES);
                        if(vertices[caras[i]._2].y>0 && vertices[caras[i]._0].y>0 ){
                            glVertex3f(vertices[caras[i]._2].x, vertices[caras[i]._2].y ,vertices[caras[i]._2].z);
                            glVertex3f(vertices[caras[i]._0].x, vertices[caras[i]._0].y ,vertices[caras[i]._0].z);
                        }
                    glEnd();
                }
            }

            //Restauraci�n del grosor de lineas, recordamos que OpenGl es una m�quina de estados que quedan constantes.
            glLineWidth(0.5);

        }

void figuraSolida::muestraCaras(){
    cout << "Vector de caras de la figura " << nombreFigura << ": " << endl;
    for(int i=0; i<caras.size(); i++)
        cout << "Cara n." << i << " [" << caras[i]._0 << " " << caras[i]._1 << " " << caras[i]._2 << "]" << endl;
}

void figuraSolida::muestraNormales(){
    cout << "Vectores normales de la figura " << nombreFigura << " :" << endl;
    for(int i=0; i<normales.size(); i++)
        cout << "Normal " << i << " [" << normales[i].x << " " << normales[i].y << " " << normales[i].z  << " ]" << endl;
}

void figuraSolida::calculaBaricentrosCaras(){
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

void figuraSolida::calculaNormalesCaras(){

            cout << "Calculando normales de caras de la figura " << nombreFigura << endl;

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

_vertex3f figuraSolida::productoVectorial(_vertex3f ab, _vertex3f ac){
                _vertex3f producto;
                producto.x=(ab.y*ac.z)-(ab.z*ac.y);
                producto.y=(ab.z*ac.x)-(ab.x*ac.z);
                producto.z=(ab.x*ac.y)-(ab.y*ac.x);
            return producto;
}

void figuraSolida::dibujaBaricentros(){
            glColor3fv(NEGRO);
            glPointSize(5);
            glBegin(GL_POINTS);
                for(unsigned int i=0; i<caras.size(); i++)
                    glVertex3f(baricentros[i].x,baricentros[i].y,baricentros[i].z);
            glEnd();
}

void figuraSolida::calculaNormalesVertices(){
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

void figuraSolida::dibujarNormales(){

    if(!baricentros.empty() && !normales.empty()){
            //Teniendo la normal y el baricentro, �C�mo dibujo una linea que salga de la caras?
            glBegin(GL_LINES);
                for(unsigned int i=0; i<caras.size(); i++){
                    glVertex3f(baricentros[i].x,baricentros[i].y,baricentros[i].z);
                    glVertex3f(baricentros[i].x+normales[i].x, baricentros[i].y+normales[i].y, baricentros[i].z+normales[i].z);
                }
            glEnd();
    }else{
        //Si uno de los dos est� vac�o el proceso no puede realizarse.
        cout << "No pueden dibujarse las normales de " << nombreFigura << ". El vector de ";
        if(baricentros.empty())
            cout << " baricentros ";
        if(normales.empty())
            cout << " normales ";
        cout << " est� vac�o."<< endl;
    }
}

void figuraSolida::dibujarNormalesVertices(){
            glColor3fv(ROJO);
            glBegin(GL_LINES);
                for(unsigned int i=0; i<normalesVertices.size(); i++){
                    glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
                    glVertex3f(vertices[i].x+normalesVertices[i].x, vertices[i].y+normalesVertices[i].y, vertices[i].z+normalesVertices[i].z);
                }
            glEnd();
}
