#ifndef SUELO
#define SUELO
#include "figuraCargada.h"
#include "parametrosRover.h"
//#include "colores.h"

class suelo{

    private:

        figuraCargada cubo;

        double tam;
        int numBloques;

        bool versionA;
        bool versionB;


    public:

        /**
        * @brief Constructor de la clase más simple que sólo carga la figura primitiva.
        */
        suelo(){
            cubo.leerFichero("cubo.ply");
            versionA=false;
            versionB=false;
        }

        /**
        * @brief Segundo constructor que establece que el suelo será conformado por un único bloque de tamaño
        * ancho x largo (ancho=largo).
        * @parm anchoLargo Tamaño del suelo, formato cuadrado.
        */
        suelo(double anchoLargo){
            cubo.leerFichero("cubo.ply");
            versionA=true;
            versionB=false;
            tam=anchoLargo;
        }

        /**
        * @brief Tercer constructor que establece que el suelo será un ajedrez de cubos de distinto color donde
        * en cada sector de los 4 habrá una cuadrícula de nxn cubos, parametro pasado.
        * @param numBloquesCuadrado es el numero de bloques cuadrados que tendrá en cada sector el ajedrez.
        */
        suelo(int numBloquesCuadrado){
            cubo.leerFichero("cubo.ply");
            versionA=false;
            versionB=true;
            numBloques=numBloquesCuadrado;
        }

        /**
        * @brief Función que dibuja el suelo según se haya definido. Para eso se usan los atributos de la clase.
        */
        void dibujarSuelo(){

                glScaled(10,1,10);

            //Sólido
            if(versionA){
                glPushMatrix();
                    glTranslated(0,-0.25,0);
                    glScaled(tam,0.5,tam);
                    dibujarBloque(GRIS_CLARO);
                glPopMatrix();
            }

            //Ajedrez
            if(versionB){

            for( int j=0; j<numBloques; j++){

            //Ambos lados de X, z negativo.
            for(int i=0; i<numBloques; i++){
                //X NEGATIVO
                glPushMatrix();
                    glTranslated(-0.5-i,-0.5,-0.5-j);
                    if(j%2==0){
                        if(i%2==0){
                            if(MODO==4)
                                dibujarBloque(plasticoMarronClaro);
                            else
                                dibujarBloque(MARRON_CLARO);
                            }
                            else{
                                if(MODO==4)
                                    dibujarBloque(plasticoMarronOscuro);
                                else
                                    dibujarBloque(MARRON_OSCURO);
                            }
                    }else{
                        if(i%2==0)
                            if(MODO==4)
                                dibujarBloque(plasticoMarronOscuro);
                            else
                                dibujarBloque(MARRON_OSCURO);
                        else
                            if(MODO==4)
                                dibujarBloque(plasticoMarronClaro);
                            else
                                dibujarBloque(MARRON_CLARO);
                    }

                glPopMatrix();
                //X POSITIVO
                glPushMatrix();
                    glTranslated(0.5+i,-0.5,-0.5-j);
                    if(j%2==0){
                        if(i%2==0)
                            if(MODO==4)
                                dibujarBloque(plasticoMarronOscuro);
                            else
                                dibujarBloque(MARRON_OSCURO);
                        else
                            if(MODO==4)
                                dibujarBloque(plasticoMarronClaro);
                            else
                                dibujarBloque(MARRON_CLARO);
                    }else{
                        if(i%2==0)
                            if(MODO==4)
                                dibujarBloque(plasticoMarronClaro);
                            else
                                dibujarBloque(MARRON_CLARO);
                        else
                            if(MODO==4)
                                dibujarBloque(plasticoMarronOscuro);
                            else
                                dibujarBloque(MARRON_OSCURO);
                    }
                glPopMatrix();
            }

            //Ambos lados de X, z positivo.
            for(int i=0; i<numBloques; i++){
                glPushMatrix();
                    glTranslated(-0.5-i,-0.5,0.5+j);
                    if(j%2==0){
                        if(i%2==0)
                            if(MODO==4)
                                dibujarBloque(plasticoMarronOscuro);
                            else
                                dibujarBloque(MARRON_OSCURO);
                        else
                            if(MODO==4)
                                dibujarBloque(plasticoMarronClaro);
                            else
                                dibujarBloque(MARRON_CLARO);
                    }else{
                        if(i%2==0)
                            if(MODO==4)
                                dibujarBloque(plasticoMarronClaro);
                            else
                                dibujarBloque(MARRON_CLARO);
                        else
                            if(MODO==4)
                                dibujarBloque(plasticoMarronOscuro);
                            else
                                dibujarBloque(MARRON_OSCURO);
                    }
                glPopMatrix();
                glPushMatrix();
                    glTranslated(0.5+i,-0.5,0.5+j);
                    if(j%2==0){
                        if(i%2==0)
                            if(MODO==4)
                                dibujarBloque(plasticoMarronClaro);
                            else
                                dibujarBloque(MARRON_CLARO);
                        else
                            if(MODO==4)
                                dibujarBloque(plasticoMarronOscuro);
                            else
                                dibujarBloque(MARRON_OSCURO);
                    }else{
                        if(i%2==0)
                            if(MODO==4)
                                dibujarBloque(plasticoMarronOscuro);
                            else
                                dibujarBloque(MARRON_OSCURO);
                        else
                            if(MODO==4)
                                dibujarBloque(plasticoMarronClaro);
                            else
                                dibujarBloque(MARRON_CLARO);
                    }
                glPopMatrix();
            }
            }//Fin del bucle j


            }//Fin de la versión B

        }//Fin de dibujar

        /**
        * @brief Para dibujar un único bloque.
        * @param color El color con el que se desea dibujar el bloque.
        */
        void dibujarBloque(const GLfloat color[]){
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
                cubo.dibujarCarasIluminacionPlana(plasticoAmarillo);
                glDisable(GL_LIGHTING); //Desactivo la iluminación.
            }
            if(MODO==5){//Modo sólido con ILUMINACIÓN SUAVE o de Gouraud
                glEnable(GL_LIGHTING);
                cubo.dibujarCarasIluminacionSuave(plasticoAmarillo);
                glDisable(GL_LIGHTING);
            }
            if(MODO==6){ //Solido + Aristas + Normales
                cubo.dibujarCaras("todo","solido",AMARILLO);
                cubo.dibujarAristas("todo");
                cubo.dibujarNormales();
            }
        }
        /**
        * @brief Para dibujar un único bloque.
        * @param material Material del que se compone el suelo.
        */
        void dibujarBloque(material materialParaAplicar){
            if(MODO==1) //Vertices
                cubo.dibujarVertices("todo");
            if(MODO==2) //Aristas
                cubo.dibujarAristas("todo");
            if(MODO==3){ //Solido
                cubo.dibujarCaras("todo","solido",AMARILLO);
                cubo.dibujarAristas("todo");
            }
            if(MODO==4){//Modo sólido con ILUMINACIÓN PLANA
                glEnable(GL_LIGHTING); //Activo la iluminación.
                cubo.dibujarCarasIluminacionPlana(materialParaAplicar);
                glDisable(GL_LIGHTING); //Desactivo la iluminación.
            }
            if(MODO==5){//Modo sólido con ILUMINACIÓN SUAVE o de Gouraud
                glEnable(GL_LIGHTING);
                cubo.dibujarCarasIluminacionSuave(materialParaAplicar);
                glDisable(GL_LIGHTING);
            }
            if(MODO==6){ //Solido + Aristas + Normales
                cubo.dibujarCaras("todo","solido",AMARILLO);
                cubo.dibujarAristas("todo");
                cubo.dibujarNormales();
            }
        }

};
#endif
