//***************************************************************************************************************
//  figuraSimple.h
//
//  Esta clase e la figura más simple que podemos tener. Se trata de un conjunto de vértices cuyos únicos métodos
//  son introducir vértices de forma manual, obtener el número de esos vértices y dibujar la figura.
//
//***************************************************************************************************************
#ifndef _FIGURASIMPLE
#define _FIGURASIMPLE

//Para poder usar los tipos de OpenGl:
#include <GL/gl.h>
//Para poder usar los vectores de la STL:
#include <vector>
//Para poder usar los tipos de datos vertex:
#include "vertex.h"
//Para poder usar los colores que nosotros definimos al dibujar la figura:
#include "colores.h"

using namespace std;

class figuraSimple{

    //Protected para que sin ser visible fuera de las clases pueda ser directamente accesible desde las clases hijas.
    protected:

        //Vector de vertices usando "vector" de la STL y el tipo vertex.h
        vector<_vertex3f> vertices;

    public:

        void setVerticeManual(GLfloat x, GLfloat y, GLfloat z){
            _vertex3f verticeTemporal;
            verticeTemporal.x=x;
            verticeTemporal.y=y;
            verticeTemporal.z=z;
            /*Podríamos usar push_back de "vector" de la STL pero cada vez que llena el vector dobla su tamaño porque
            se ha demostrado que de media es la necesitada que se suele tener, en nuestro caso no y puede hacernos
            desperdiciar mucha memoria.
            */
            //Vamos a usar push_back mientras descrubrimos otra forma de hacerlo.
            vertices.push_back(verticeTemporal);
        };

        int numeroVertices(){
            return vertices.size();
        };

        void dibujarVertices(string seccion){


            glColor3fv(NEGRO);
            glPointSize(5);

            //Si el parametro es "todo" se dibujan todos los vertices del modelo.
            if(seccion=="todo"){
                glBegin(GL_POINTS);
                    for(unsigned int i=0; i<vertices.size(); i++)
                        glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
                glEnd();
            }

            //Con "solo x+" sólo se dibujan los vértices se situan en la parte posivita del eje X
            if(seccion=="solo x+"){
                glBegin(GL_POINTS);
                    for(unsigned int i=0; i<vertices.size(); i++)
                        //Comprobación de la posición respecto al eje X de los vértices.
                        if(vertices[i].x>0)
                        glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
                glEnd();
            }

            //Con "solo x-" sólo se dibujan los vértices se situan en la parte negativa del eje X
            if(seccion=="solo x-"){
                glBegin(GL_POINTS);
                    for(unsigned int i=0; i<vertices.size(); i++)
                        //Comprobación de la posición respecto al eje X de los vértices.
                        if(vertices[i].x<0)
                        glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
                glEnd();
            }

            //Con "solo y+" sólo se dibujan los vértices se situan en la parte posivita del eje Y
            if(seccion=="solo y+"){
                glBegin(GL_POINTS);
                    for(unsigned int i=0; i<vertices.size(); i++)
                        //Comprobación de la posición respecto al eje Y de los vértices.
                        if(vertices[i].y>0)
                        glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
                glEnd();
            }

            //Con "solo y-" sólo se dibujan los vértices se situan en la parte negativa del eje Y
            if(seccion=="solo y-"){
                glBegin(GL_POINTS);
                    for(unsigned int i=0; i<vertices.size(); i++)
                        //Comprobación de la posición respecto al eje Y de los vértices.
                        if(vertices[i].y<0)
                        glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
                glEnd();
            }


            //Con "solo z+" sólo se dibujan los vértices se situan en la parte posivita del eje Z
            if(seccion=="solo z+"){
                glBegin(GL_POINTS);
                    for(unsigned int i=0; i<vertices.size(); i++)
                        //Comprobación de la posición respecto al eje Z de los vértices.
                        if(vertices[i].z>0)
                        glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
                glEnd();
            }

            //Con "solo z-" sólo se dibujan los vértices se situan en la parte negativa del eje Z
            if(seccion=="solo z-"){
                glBegin(GL_POINTS);
                    for(unsigned int i=0; i<vertices.size(); i++)
                        //Comprobación de la posición respecto al eje Z de los vértices.
                        if(vertices[i].z<0)
                        glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
                glEnd();
            }


            /*

            Antiguo código que funcionaba pero era menos eficiente:

            ##EXPLICACIÓN##

            Existe pérdida de eficiencia por el elevado número de comparaciones que se tienen que realizar.
            En él compruebo cual ha sido el string pasado a la función para comprobar que sección quiere el
            usuario que se dibuje, eso es lo de menos. El caso es que estas siete comprobaciones que se hacen
            dentro del bucle se hacen por cada vértice. Claro beethoven tiene 2521 vertices, tantos como pasadas
            tiene que dar el for y entonces estaríamos haciendo 17647 comprobaciones.


            ##CODIGO:

            glBegin(GL_POINTS);
                //Bucle que recorrerá todos los elementos del vector de vértices para dibujarlos.
                for(unsigned int i=0; i<vertices.size(); i++){

                    //Dibujado de los vértices
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

        };

};

#endif
