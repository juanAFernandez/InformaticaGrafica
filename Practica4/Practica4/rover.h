#ifndef ROVER
#define ROVER
#include <math.h>
//#include "colores.h"
#include "materiales.h"
#include "figuraCargada.h"
#include "parametrosRover.h"
//#include "v.h"

#include "Robot.h"


/*
Cada vez que el coche se gira hay que calcular la ecuación de la recta para que siga una normal cuando avanza hacia adelante.
*/



class rover{

    private:

        //Figuras primitivas a partir de las cuales construiremos nuestro modelo más completo.

        figuraCargada cubo; /** < Figura primitiva #1: Cubo centrado en el origen y de tamaño unidad */
        figuraRevolucionada cilindro;
        figuraRevolucionada semiCilindro;


        double Cx;
        double Cz;
        int gradosRotacionCoche;
        _vertex3f vectorDireccion;

        float RAD_TO_DEG;
        double gradosRuedasDerechas;
        double gradosRuedasIzquierdas;

        double gradosAntena;

        void dibujarDetalles(){

        //Detalles


            //Cubos rojos:
            //Derecho:
            glPushMatrix();
                glTranslated(5,16,-20);
                glScaled(5,5,5);
                dibujarCubo(ROJO, plasticoRojo);
            glPopMatrix();
            //Izquierdo:
            glPushMatrix();
                glTranslated(-5,16,-20);
                glScaled(5,5,5);
                dibujarCubo(ROJO, plasticoRojo);
            glPopMatrix();

            //Parachoques trasero:
            glPushMatrix();
                glTranslated(0,6,-25.5);
                glScaled(20,1,1);
                dibujarCubo(GRIS_OSCURO, silver);
            glPopMatrix();

            //Tanques de combustible:

            //Izquierdo:
            glPushMatrix();
                glTranslated(6,13,6);
                glScaled(5,5,30);
                glRotated(-90,1,0,0);
                dibujarSemiCilindro(AZUL, plasticoAzul);
            glPopMatrix();

            //Derecho:
            glPushMatrix();
                glTranslated(-6,13,6);
                glScaled(5,5,30);
                glRotated(-90,1,0,0);
                dibujarSemiCilindro(AZUL, plasticoAzul);
            glPopMatrix();


            //Antena:
            glPushMatrix();
                glTranslated(0,22,-20);
                glScaled(7,2.5,7);
                glRotated(gradosRotacionCoche*10,0,1,0);
                dibujarSemiCilindro(GRIS_CLARO, silver);
            glPopMatrix();



            //BaseAntena
            glPushMatrix();
                glTranslated(0,20,-20);
                glScaled(1,10,1);
                dibujarCilindro(GRIS_OSCURO, silver);
            glPopMatrix();


        }

        void dibujarCuerpo(){
            //Cada vez que se dibuje de nuevo el cuerpo vamos a mostrar la directriz:
            //mostrarVerctorDireccion();

            //Chasis metálico
            glPushMatrix();
               glRotated(GRADOS_GIRO_ROVER,0,1,0);
               glTranslated(0,9.5,0);
               dibujarRuedas();
                //Dibujar chasis gris
               dibujarChasis(GRIS_CLARO, silver);
            glPopMatrix();

            //Brazo robótico:
            glPushMatrix();
                glTranslated(0,12.5,29);
                glScaled(2,2,2);
                glRotated(-90,0,1,0);
                brazo.dibujarRobot();
            glPopMatrix();

            dibujarDetalles();


        }

        //El chasis se dibuja del mismo color:
        void dibujarChasis(const GLfloat color[], material materialPasado){

            //Parte grande del chasis:
            glPushMatrix();
                glScaled(20,8,50);
                dibujarCubo(color, materialPasado);
            glPopMatrix();

            //Delantera del chasis:
            glPushMatrix();
                glTranslated(0,-2,29);
                glScaled(20,4,8);
                dibujarCubo(color, materialPasado);
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
                glRotated(gradosRuedasIzquierdas*5,1,0,0);
                dibujarRueda();
            glPopMatrix();
            //Rueda trasera izquierda:
            glPushMatrix();
                glTranslated(10.5,0,-15);
                glRotated(gradosRuedasIzquierdas*5,1,0,0);
                dibujarRueda();
            glPopMatrix();
        }

        void dibujarRuedasDerechas(){
            //Rueda delantera derecha:
            glPushMatrix();
                glTranslated(-10.5,0,15);
                glRotated(gradosRuedasDerechas*5,1,0,0);
                dibujarRueda();
            glPopMatrix();

            //Rueda trasera derecha:
            glPushMatrix();
                glTranslated(-10.5,0,-15);
                glRotated(gradosRuedasDerechas*5,1,0,0);
                dibujarRueda();
            glPopMatrix();
        }

        void dibujarRueda(){
            glEnable(GL_NORMALIZE);
            int numRadios=10;
            double grados=360.0/numRadios;
            for(int i=0; i<numRadios; i++){
                glPushMatrix();
                    glRotated(grados*i,1,0,0);
                    glTranslated(0,5.5,0);
                    glScaled(1,8,1);
                    glEnable(GL_NORMALIZE);
                        dibujarCubo(GRIS_CLARO, silver);
                    //glDisable(GL_NORMALIZE);
                    glEnable(GL_NORMALIZE);
                glPopMatrix();
            }
            //glDisable(GL_NORMALIZE);
        }

        void dibujarCubo(const GLfloat color[], material materialPasado){


            if(MODO==1) //Vertices
                cubo.dibujarVertices("todo");
            if(MODO==2) //Aristas
                cubo.dibujarAristas("todo");
            if(MODO==3){ //Solido
                cubo.dibujarCaras("todo","solido",color);
                cubo.dibujarAristas("todo");
            }
            if(MODO==4){//Modo sólido con ILUMINACIÓN PLANA
                glEnable(GL_LIGHTING); //Activo la iluminación.
                cubo.dibujarCarasIluminacionPlana(materialPasado);
                glDisable(GL_LIGHTING); //Desactivo la iluminación.
            }
            if(MODO==5){//Modo sólido con ILUMINACIÓN SUAVE o de Gouraud
                glEnable(GL_LIGHTING);
                cubo.dibujarCarasIluminacionSuave(materialPasado);
                glDisable(GL_LIGHTING);
            }
            if(MODO==6){ //Solido + Aristas + Normales
                cubo.dibujarCaras("todo","solido",color);
                cubo.dibujarAristas("todo");
                cubo.dibujarNormales();
            }
        }

        void dibujarCilindro(const GLfloat color[], material materialPasado){
            if(MODO==1) //Vertices
                cilindro.dibujarVertices("todo");
            if(MODO==2) //Aristas
                cilindro.dibujarAristas("todo");
            if(MODO==3){ //Solido
                cilindro.dibujarCaras("todo","solido",color);
                cilindro.dibujarAristas("todo");
            }
            if(MODO==4){//Modo sólido con ILUMINACIÓN PLANA
                glEnable(GL_LIGHTING); //Activo la iluminación.
                cilindro.dibujarCarasIluminacionPlana(materialPasado);
                glDisable(GL_LIGHTING); //Desactivo la iluminación.
            }
            if(MODO==5){//Modo sólido con ILUMINACIÓN SUAVE o de Gouraud
                glEnable(GL_LIGHTING);
                cilindro.dibujarCarasIluminacionSuave(materialPasado);
                glDisable(GL_LIGHTING);
            }
            if(MODO==6){ //Solido + Aristas + Normales
                cilindro.dibujarCaras("todo","solido",color);
                cilindro.dibujarAristas("todo");
                cilindro.dibujarNormales();
            }
        }

        void dibujarSemiCilindro(const GLfloat color[], material materialPasado){
            if(MODO==1) //Vertices
                semiCilindro.dibujarVertices("todo");
            if(MODO==2) //Aristas
                semiCilindro.dibujarAristas("todo");
            if(MODO==3){ //Solido
                semiCilindro.dibujarCaras("todo","solido",color);
                semiCilindro.dibujarAristas("todo");
            }
            if(MODO==4){//Modo sólido con ILUMINACIÓN PLANA
                glEnable(GL_LIGHTING); //Activo la iluminación.
                semiCilindro.dibujarCarasIluminacionPlana(materialPasado);
                glDisable(GL_LIGHTING); //Desactivo la iluminación.
            }
            if(MODO==5){//Modo sólido con ILUMINACIÓN SUAVE o de Gouraud
                glEnable(GL_LIGHTING);
                semiCilindro.dibujarCarasIluminacionSuave(materialPasado);
                glDisable(GL_LIGHTING);
            }
            if(MODO==6){ //Solido + Aristas + Normales
                semiCilindro.dibujarCaras("todo","solido",color);
                semiCilindro.dibujarAristas("todo");
                semiCilindro.dibujarNormales();
            }
        }

        void mostrarVerctorDireccion(){
            cout << "Vector Direccion: " << vectorDireccion.x << " " << vectorDireccion.y << " " << vectorDireccion.z << endl;
           // cout << "Angulo cUerpo: " << anguloCue << endl;
        }



    public: //Todas menos el contructor deberían ser privadas ??¿¿

        Robot brazo;

        /**
        * @brief Constructur de la clase que carga el modelo y topología de las figuras primitivas de las que se partirá para cosntruir.
        */
        rover(){



            RAD_TO_DEG=(M_PI/180);
            gradosRotacionCoche=0; Cx=0.0; Cz=0.0;
            gradosRuedasDerechas=0.0;
            gradosRuedasIzquierdas=0.0;
            gradosAntena=0.0;


            //Cargamos el modelo del cubo desde un fichero ply
            cubo.leerFichero("cubo.ply");
            cubo.setNombre("cuboPrimitivo para Curiosity");
            //Calculamos las normales de las caras:
            cubo.calculaNormalesCaras();
            //Depuracion: mostramos las normales por terminal:
            cubo.muestraNormales();

            //Cargamos la normal directriz de rover a partir de la normal del frontal del cubo que forma el chasis
            vectorDireccion=cubo.getNormal(0);


           // anguloDiferenciaOrigen=atan(baricentro.x/baricentro.z);
            //mostrarDirectriz();

        //### CILINDRO ###
        //Declaramos un perfil:
        vector<_vertex3f> perfilCompleto;
        //Cargamos el perfil simple completo (con tapas) con los puntos:
        perfilCompleto.push_back({0,-0.5,0});
        perfilCompleto.push_back({0.5,-0.5,0});
        perfilCompleto.push_back({0.5,0.5,0});
        perfilCompleto.push_back({0,0.5,0});
        /*Esto tb podría haberse realizado mediante la lectura de un fichero .ply */
        //Cargamos el perfil en la figura:
        cilindro.cargarPerfil(perfilCompleto);
        cilindro.revoluciona(16,0,360);

        semiCilindro.cargarPerfil(perfilCompleto);
        semiCilindro.revoluciona(16,0,180);



        }

        //Función para dibujar el rover completo.
        void dibujarRover(){

            //cout << "Dibujando rover " << endl;

            //cout << "baricentro x:" << baricentro.x  << " y: " << baricentro.y << " z: " << baricentro.z << endl;

            glPushMatrix();
                glTranslated(Cx,0,Cz);
                glRotated(gradosRotacionCoche,0,1,0);
                dibujarCuerpo();
            glPopMatrix();


        }

        void rotarVectorDireccion(double grados){

            cout << "Grados" << grados;

            double tmpX=0.0;
            double tmpZ=0.0;

            //Implementación de la matriz de rotación:
            tmpX=( (cos(grados*RAD_TO_DEG)*vectorDireccion.x) + (sin(grados*RAD_TO_DEG)*vectorDireccion.z) );
            tmpZ=( (-sin(grados*RAD_TO_DEG)*vectorDireccion.x) + (cos(grados*RAD_TO_DEG)*vectorDireccion.z)  );

            vectorDireccion.x=tmpX;
            vectorDireccion.z=tmpZ;

        }

        void desplazaAdelante(){
            gradosRuedasDerechas++;
            gradosRuedasIzquierdas++;
            Cx+=vectorDireccion.x*AGARRE_SUELO;
            Cz+=vectorDireccion.z*AGARRE_SUELO;
        }

        void desplazaAtras(){
            gradosRuedasDerechas--;
            gradosRuedasIzquierdas--;
            Cx-=vectorDireccion.x*AGARRE_SUELO;
            Cz-=vectorDireccion.z*AGARRE_SUELO;
        }

        void giraDerecha(){

            gradosRuedasDerechas--;
            gradosRuedasIzquierdas++;

            gradosRotacionCoche--;
            if(gradosRotacionCoche==360)
                gradosRotacionCoche=0;
            rotarVectorDireccion(-1.0);
        }

        void giraIzquierda(){

            gradosRuedasDerechas++;
            gradosRuedasIzquierdas--;

            gradosRotacionCoche++;
            if(gradosRotacionCoche==360)
                gradosRotacionCoche=0;
            rotarVectorDireccion(1.0);
        }


};


#endif
