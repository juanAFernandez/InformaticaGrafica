//***************************************************************************************************************
//  figuraSimple.h
//
//  Esta clase e la figura m�s simple que podemos tener. Se trata de un conjunto de v�rtices cuyos �nicos m�todos
//  son introducir v�rtices de forma manual, obtener el n�mero de esos v�rtices y dibujar la figura.
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
            /*Podr�amos usar push_back de "vector" de la STL pero cada vez que llena el vector dobla su tama�o porque
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

        };

};

#endif
