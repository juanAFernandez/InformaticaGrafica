#ifndef _FIGURA
#define _FIGURA
/*Cuidado: �� Siempre hay que incluir la librer�a de la STL que vamos a usar !!
Y si no siendo as� nos ha funcionado es porque en otro lugar se estaba incluyendo y nosotros la
est�bamos arrastrando sin saberlo.
*/
#include <vector>
/*Incluimos la librer�a para usar vertices que incluye muchas funcionalidades muy �tiles
como usar el acceso a trav�s de coordenada Vertices[0].x
*/
#include "vertex.h"
#include <GL/gl.h>
#include "windows.h"
#include "file_ply_stl.h"

#include "colores.h"

using namespace std;



class figura{

    private:
        /*Una figura tendr� un vector de puntos (v�rtices, usando uno de los tipos vertex.h)
        en nuestro caso _vertex3f ya que los vectores son coordenadas de tres flotantes y para facilitar el
        trabajo usaremos "vector" de la STL para poder aprovecharnos de tods sus funciones ya implementadas.
        */
        vector<_vertex3f> vertices;

        /*Una figura tambi�n tendr� un vector de caras donde se escriben los �ndices del vector de v�rtices que
        compone la figura. Tambi�n usamos uno de los tipos de vertex.h
        */
        vector<_vertex3i> caras;


        //Variables de dibujado



    public:

        //Funci�n que abre el fichero, lee los datos para cargarlos en nuestra estructura y lo cierra.
        void leerFichero(char *nombre){

            _file_ply fichero;
            fichero.open(nombre);

            vector<float>verticitos;
            vector<int>caritas;

            fichero.read(verticitos,caritas);

            //Carga de los vertices en nuestro formato _vertex3f
            unsigned tamVertices=verticitos.size();

            _vertex3f swap;
            for(int i=0; i<tamVertices; i=i+3){
                swap.x=verticitos[i];
                swap.y=verticitos[i+1];
                swap.z=verticitos[i+2];
                //Habr�a que cambiar la forma de introducir los vertices.
                vertices.push_back(swap);
            }


            //Carga de las caras en nuestro formato

            unsigned tamCaras=caritas.size();
            _vertex3i swapCaras;
            for(int i=0; i<tamCaras; i=i+3){
                swapCaras.x=caritas[i];
                swapCaras.y=caritas[i+1];
                swapCaras.z=caritas[i+2];
                //Habr�a que cambiar la forma de introducir los vertices.
                caras.push_back(swapCaras);
            }

            fichero.close();

        }


        int numeroVertices(){
            return vertices.size();
        }

        int numeroCaras(){
            return caras.size();
        }

        void setVerticeManual(GLfloat x, GLfloat y, GLfloat z){
            _vertex3f verticeTemporal;
            verticeTemporal.x=x;
            verticeTemporal.y=y;
            verticeTemporal.z=z;
            /*Podr�amos usar push_back de "vector" de la STL pero cada vez que llena el vector dobla su tama�o porque
            se ha demostrado que de media es la necesitada que se suele tener, en nuestro caso no y puede hacernos
            desperdiciar mucha memoria.
            */
            //Vamos a usar push_back mientras descrubrimos otra forma de hacerlo.
            vertices.push_back(verticeTemporal);
        };


        //Funci�n para introducir a mano las caras del modelo
        void setCaraManual(unsigned int verticeA, unsigned int verticeB, unsigned int verticeC){
            _vertex3i caraTemporal;
            caraTemporal.x=verticeA;
            caraTemporal.y=verticeB;
            caraTemporal.z=verticeC;
            caras.push_back(caraTemporal);
        }


        //Funci�n para dibujar s�lo los v�rtices
        void dibujarVertices(string seccion){


            glColor3fv(NEGRO);
            glPointSize(2);

            //Si el parametro es "todo" se dibujan todos los vertices del modelo.
            if(seccion=="todo"){
                glBegin(GL_POINTS);
                    for(unsigned int i=0; i<vertices.size(); i++)
                        glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
                glEnd();
            }

            //Con "solo x+" s�lo se dibujan los v�rtices se situan en la parte posivita del eje X
            if(seccion=="solo x+"){
                glBegin(GL_POINTS);
                    for(unsigned int i=0; i<vertices.size(); i++)
                        //Comprobaci�n de la posici�n respecto al eje X de los v�rtices.
                        if(vertices[i].x>0)
                        glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
                glEnd();
            }

            //Con "solo x-" s�lo se dibujan los v�rtices se situan en la parte negativa del eje X
            if(seccion=="solo x-"){
                glBegin(GL_POINTS);
                    for(unsigned int i=0; i<vertices.size(); i++)
                        //Comprobaci�n de la posici�n respecto al eje X de los v�rtices.
                        if(vertices[i].x<0)
                        glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
                glEnd();
            }

            //Con "solo y+" s�lo se dibujan los v�rtices se situan en la parte posivita del eje Y
            if(seccion=="solo y+"){
                glBegin(GL_POINTS);
                    for(unsigned int i=0; i<vertices.size(); i++)
                        //Comprobaci�n de la posici�n respecto al eje Y de los v�rtices.
                        if(vertices[i].y>0)
                        glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
                glEnd();
            }

            //Con "solo y-" s�lo se dibujan los v�rtices se situan en la parte negativa del eje Y
            if(seccion=="solo y-"){
                glBegin(GL_POINTS);
                    for(unsigned int i=0; i<vertices.size(); i++)
                        //Comprobaci�n de la posici�n respecto al eje Y de los v�rtices.
                        if(vertices[i].y<0)
                        glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
                glEnd();
            }


            //Con "solo z+" s�lo se dibujan los v�rtices se situan en la parte posivita del eje Z
            if(seccion=="solo z+"){
                glBegin(GL_POINTS);
                    for(unsigned int i=0; i<vertices.size(); i++)
                        //Comprobaci�n de la posici�n respecto al eje Z de los v�rtices.
                        if(vertices[i].z>0)
                        glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
                glEnd();
            }

            //Con "solo z-" s�lo se dibujan los v�rtices se situan en la parte negativa del eje Z
            if(seccion=="solo z-"){
                glBegin(GL_POINTS);
                    for(unsigned int i=0; i<vertices.size(); i++)
                        //Comprobaci�n de la posici�n respecto al eje Z de los v�rtices.
                        if(vertices[i].z<0)
                        glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
                glEnd();
            }


            /*

            Antiguo c�digo que funcionaba pero era menos eficiente:

            ##EXPLICACI�N##

            Existe p�rdida de eficiencia por el elevado n�mero de comparaciones que se tienen que realizar.
            En �l compruebo cual ha sido el string pasado a la funci�n para comprobar que secci�n quiere el
            usuario que se dibuje, eso es lo de menos. El caso es que estas siete comprobaciones que se hacen
            dentro del bucle se hacen por cada v�rtice. Claro beethoven tiene 2521 vertices, tantos como pasadas
            tiene que dar el for y entonces estar�amos haciendo 17647 comprobaciones.


            ##CODIGO:

            glBegin(GL_POINTS);
                //Bucle que recorrer� todos los elementos del vector de v�rtices para dibujarlos.
                for(unsigned int i=0; i<vertices.size(); i++){

                    //Dibujado de los v�rtices
                    if(seccion=="todo")
                        glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);

                    //Opciones del eje X
                    if(seccion=="solo x+")
                        if(vertices[i].x>0)
                            glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
                    if(seccion=="solo x-")
                        if(vertices[i].x<0)
                            glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);

                    //Opciones del eje Y
                    if(seccion=="solo y+")
                        if(vertices[i].y>0)
                            glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
                    if(seccion=="solo y-")
                        if(vertices[i].y<0)
                            glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);

                    //Opciones del eje Z
                    if(seccion=="solo z+")
                        if(vertices[i].z>0)
                            glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
                    if(seccion=="solo z-")
                        if(vertices[i].z<0)
                            glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
                }

            glEnd();
            */

        }



        //Par�metros:
        //      si modo == "solido" se dibujan todas las caras del mismo color.
        //      si modo == "ajedrez" cada cara se dibujar� de un color.
        void dibujarCaras(string seccion, string modo){

            //Usamos la directiva GL_TRIANGLES que necesita que se le pasen tres vectores.
            glBegin(GL_TRIANGLES);
                /*Accedemos a los vectores usando como �ndices los enteros almacenados en el vector
                de caras teniendo en cuenta que dentro de este vector caras[0]._0 se refiere al primer
                vertice de la cara 0, caras[0]._1 al segundo v�rtice y caras[0]._2 al tercer v�rtice, con
                esta nomenclatura se hace m�s f�cil entender como se est� accediendo.
                */

                //En cada pasada del bucle for se dibuja una de las caras almacenadas.

                for(unsigned i=0; i<caras.size(); i++){

                    /*

                    if(modo=="ajedrez"){
                    //Gesti�n del color de las caras si el modo es "ajedrez"
                    if(i%2==0)
                        //Para las caras pares:
                        glColor3fv(GRIS_OSCURO);
                    else
                        //Para las caras impares:
                        glColor3fv(GRIS_CLARO);
                    }

                    //Cuando se quiere dibujar pareciendo formar un �nico s�lido.
                    if(modo=="solido")
                        glColor3fv(GRIS_CLARO);

                    */

                    if(seccion=="todo"){

                        /*Para dibujar una cara se necesitan tres v�rtices y como nosotros guardamos en el vector de caras
                        los vertices de cada cara usamos los valores x, y y z de los vertices de cada vertice de la cara i.
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

                        //  caras[0]._0  Primer v�rtice de la cara 0
                        glVertex3f(vertices[caras[i]._0].x, vertices[caras[i]._0].y ,vertices[caras[i]._0].z);
                        //  caras[0]._1  Segundo v�rtice de la cara 0
                        glVertex3f(vertices[caras[i]._1].x, vertices[caras[i]._1].y ,vertices[caras[i]._1].z);
                        //  caras[0]._2  Tercer v�rtice de la cara 0
                        glVertex3f(vertices[caras[i]._2].x, vertices[caras[i]._2].y ,vertices[caras[i]._2].z);
                    }

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


        //Para dibujar las aristas usa el vector de caras.
        //Par�metros:
        //      si seccion == "todo" se dibuja todo el modelo completo
        //      si seccion == "solo x+" se dibuja s�lo las aristas que se encuentren en el lado positivo del eje X
        void dibujarAristas(string seccion){

            //Configuraci�n del color (RGB [0-1] )
            glColor3f(0.1,0.6,0.1);

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



};

#endif
