#ifndef _PERFIL
#define _PERFIL

#include "figuraSimple.h"

class Perfil : public figuraSimple {

    private:

    public:

        /**
        * @brief Constructor "vac�o" de la clase.
        */
        Perfil(){ nombreFigura="anonima";};

        /**
        * @brief Constructor de la clase que env�a el nombre de la figura al constructor de la clase padre.
        */
        Perfil(string nuevoNombre):figuraSimple(nuevoNombre){};


        void dibujar(){

            //Dibujo de los v�rtices del perfil
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
                    //Recordando que caras[0]._0 es: cara n� 0 v�rtice n�0
                    glVertex3f(vertices[i].x, vertices[i].y ,vertices[i].z);
                    glVertex3f(vertices[i+1].x, vertices[i+1].y ,vertices[i+1].z);
                glEnd();
            }


        }




};

#endif
