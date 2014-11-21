#ifndef ROVER
#define ROVER
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

    public: //Todas menos el contructor deberían ser privadas ??¿¿

        /**
        * @brief Constructur de la clase que carga el modelo y topología de las figuras primitivas de las que se partirá para cosntruir.
        */
        rover(){
            cubo.leerFichero("cubo.ply");
            //Definimos su nombre:
            cilindro.setNombre("cilindro");
            //Cargamos un perfil:

            //Revolucionamos de la forma que queramos:
        }

        void dibujarCuerpo(){
            glPushMatrix();
                glRotated(GRADOS_GIRO_ROVER,0,1,0);
                glTranslated(0,5,0);
                dibujarRuedas();
                dibujarChasis();
            glPopMatrix();
        }

        void dibujarRover(){

            glPushMatrix();
                //También podría ser con las izquierdas
                glTranslated(0,0,GRADOS_RUEDA_DERECHA*0.15);
                dibujarCuerpo();
            glPopMatrix();


        }


        void dibujarChasis(){
            glPushMatrix();
                glScaled(20,8,50);
                cubo.dibujarAristas("todo");
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
                    cubo.dibujarCaras("todo","solido","gris");
                glPopMatrix();
            }
        }



        void dibujarCubo(string color){
            cubo.dibujarCaras("todo","solido","gris");
        }

};


#endif
