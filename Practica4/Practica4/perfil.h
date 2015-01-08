#ifndef _PERFIL
#define _PERFIL

#include "figuraSimple.h"

class Perfil : public figuraSimple {

    private:

    public:

        /**
        * @brief Constructor "vacío" de la clase.
        */
        Perfil(){ nombreFigura="anonima";};

        /**
        * @brief Constructor de la clase que envía el nombre de la figura al constructor de la clase padre.
        */
        Perfil(string nuevoNombre):figuraSimple(nuevoNombre){};


        void dibujar(){

            //Dibujo de los vértices del perfil
            glColor3fv(VERDE);
            glPointSize(4);
            glBegin(GL_POINTS);
                    for(unsigned int i=0; i<vertices.size(); i++)
                        glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
            glEnd();

            //Dibujo de las aristas del perfil:
            glColor3fv(GRIS_CLARO);
            for(unsigned int i=0; i<vertices.size()-1; i++){
                glBegin(GL_LINES);
                    //Recordando que caras[0]._0 es: cara nº 0 vértice nº0
                    glVertex3f(vertices[i].x, vertices[i].y ,vertices[i].z);
                    glVertex3f(vertices[i+1].x, vertices[i+1].y ,vertices[i+1].z);
                glEnd();
            }


        }




};

#endif
