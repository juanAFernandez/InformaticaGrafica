#ifndef ROVER
#define ROVER
#include <math.h>
//#include "colores.h"
#include "figuraCargada.h"
#include "parametrosRover.h"
//#include "figuraRevolucionada.h"


/*
Cada vez que el coche se gira hay que calcular la ecuación de la recta para que siga una normal cuando avanza hacia adelante.
*/



class rover{

    private:

        //Figuras primitivas a partir de las cuales construiremos nuestro modelo más completo.

        figuraCargada cubo; /** < Figura primitiva #1: Cubo centrado en el origen y de tamaño unidad */
        figuraRevolucionada cilindro;

        void dibujarCuerpo(){
            //Cada vez que se dibuje de nuevo el cuerpo vamos a mostrar la directriz:
            mostrarDirectriz();
            glPushMatrix();
                glRotated(GRADOS_GIRO_ROVER,0,1,0);
                glTranslated(0,9.5,0);
                dibujarRuedas();
                //Dibujar chasis gris
                dibujarChasis(GRIS_CLARO);
            glPopMatrix();
        }

        void dibujarChasis(const GLfloat color[]){
            glPushMatrix();
                glScaled(20,8,50);
                dibujarCubo(color);
                //cubo.dibujarAristas("todo");
            glPopMatrix();
        }

        void dibujarRuedas(){
            dibujarRuedasIzquierdas();
            dibujarRuedasDerechas();
        }

        void dibujarRuedasIzquierdas(){
            //Rueda delantera izquierda:
            glPushMatrix();
                glTranslated(10.5,0,15);
                glRotated(GRADOS_RUEDA_IZQUIERDA,1,0,0);
                dibujarRueda();
            glPopMatrix();
            //Rueda trasera izquierda:
            glPushMatrix();
                glTranslated(10.5,0,-15);
                glRotated(GRADOS_RUEDA_IZQUIERDA,1,0,0);
                dibujarRueda();
            glPopMatrix();
        }

        void dibujarRuedasDerechas(){
            //Rueda delantera derecha:
            glPushMatrix();
                glTranslated(-10.5,0,15);
                glRotated(GRADOS_RUEDA_DERECHA,1,0,0);
                dibujarRueda();
            glPopMatrix();

            //Rueda trasera derecha:
            glPushMatrix();
                glTranslated(-10.5,0,-15);
                glRotated(GRADOS_RUEDA_DERECHA,1,0,0);
                dibujarRueda();
            glPopMatrix();
        }

        void dibujarRueda(){
            int numRadios=10;
            double grados=360./numRadios;
            for(int i=0; i<numRadios; i++){
                glPushMatrix();
                    glRotated(grados*i,1,0,0);
                    glTranslated(0,5.5,0);
                    glScaled(1,8,1);
                    cubo.dibujarAristas("todo");
                    cubo.dibujarCaras("todo","solido",GRIS_OSCURO);
                glPopMatrix();
            }
        }

        void dibujarCubo(const GLfloat color[]){
            cubo.dibujarCaras("todo","solido",color);
            cubo.dibujarAristas("todo");
            cubo.dibujarNormales();
        }

        void mostrarDirectriz(){
            cout << "Normal directriz: " << normalDirectriz.x << " " << normalDirectriz.y << " " << normalDirectriz.z << endl;
        }

    public: //Todas menos el contructor deberían ser privadas ??¿¿

        /**
        * @brief Constructur de la clase que carga el modelo y topología de las figuras primitivas de las que se partirá para cosntruir.
        */
        rover(){
            //Cargamos el modelo del cubo desde un fichero ply
            cubo.leerFichero("cubo.ply");
            cubo.setNombre("cubo");
            //Calculamos las normales de las caras:
            cubo.calculaNormalesCaras();
            //Cargamos la normal directriz de rover a partir de la normal del frontal del cubo que forma el chasis
            normalDirectriz=cubo.getNormal(0);
            //mostrarDirectriz();

            //Definimos su nombre:
            cilindro.setNombre("cilindro");
            //Cargamos un perfil:

            //Revolucionamos de la forma que queramos:
        }

        //Función para dibujar el rover completo.
        void dibujarRover(){

            glPushMatrix();
                //También podría ser con las izquierdas. Lo que acemos es aprovechar el mismo valor para mover el cuerpo completo.
                glTranslated(0,0,GRADOS_RUEDA_DERECHA*AGARRE_SUELO);
                //glTranslated(normalDirectriz.x*1,normalDirectriz.y*1,0);
                dibujarCuerpo();
            glPopMatrix();
        }

};


#endif
