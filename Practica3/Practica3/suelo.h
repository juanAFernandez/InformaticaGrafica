#ifndef SUELO
#define SUELO
#include "figuraCargada.h"

class suelo{

    private:

        figuraCargada cubo;

        double tam;
        int numBloques;

        bool versionA;
        bool versionB;


    public:

        /**
        * @brief Constructor de la clase m�s simple que s�lo carga la figura primitiva.
        */
        suelo(){
            cubo.leerFichero("cubo.ply");
            versionA=false;
            versionB=false;
        }

        /**
        * @brief Segundo constructor que establece que el suelo ser� conformado por un �nico bloque de tama�o
        * ancho x largo (ancho=largo).
        * @parm anchoLargo Tama�o del suelo, formato cuadrado.
        */
        suelo(double anchoLargo){
            cubo.leerFichero("cubo.ply");
            versionA=true;
            versionB=false;
            tam=anchoLargo;
        }

        /**
        * @brief Tercer constructor que establece que el suelo ser� un ajedrez de cubos de distinto color donde
        * en cada sector de los 4 habr� una cuadr�cula de nxn cubos, parametro pasado.
        * @param numBloquesCuadrado es el numero de bloques cuadrados que tendr� en cada sector el ajedrez.
        */
        suelo(int numBloquesCuadrado){
            cubo.leerFichero("cubo.ply");
            versionA=false;
            versionB=true;
            numBloques=numBloquesCuadrado;
        }

        /**
        * @brief Funci�n que dibuja el suelo seg�n se haya definido. Para eso se usan los atributos de la clase.
        */
        void dibujarSuelo(){

            if(versionA){
                glPushMatrix();
                    glTranslated(0,-0.25,0);
                    glScaled(tam,0.5,tam);
                    dibujarBloque("gris");
                glPopMatrix();
            }


            if(versionB){

            for( int j=0; j<numBloques; j++){

            //Ambos lados de X, z negativo.
            for(int i=0; i<numBloques; i++){
                //X NEGATIVO
                glPushMatrix();
                    glTranslated(-0.5-i,-0.5,-0.5-j);
                    if(j%2==0){
                        if(i%2==0)
                            dibujarBloque("gris");
                        else
                            dibujarBloque("amarillo");
                    }else{
                        if(i%2==0)
                            dibujarBloque("amarillo");
                        else
                            dibujarBloque("gris");
                    }

                glPopMatrix();
                //X POSITIVO
                glPushMatrix();
                    glTranslated(0.5+i,-0.5,-0.5-j);
                    if(j%2==0){
                        if(i%2==0)
                            dibujarBloque("amarillo");
                        else
                            dibujarBloque("gris");
                    }else{
                        if(i%2==0)
                            dibujarBloque("gris");
                        else
                            dibujarBloque("amarillo");
                    }
                glPopMatrix();
            }

            //Ambos lados de X, z positivo.
            for(int i=0; i<numBloques; i++){
                glPushMatrix();
                    glTranslated(-0.5-i,-0.5,0.5+j);
                    if(j%2==0){
                        if(i%2==0)
                            dibujarBloque("amarillo");
                        else
                            dibujarBloque("gris");
                    }else{
                        if(i%2==0)
                            dibujarBloque("gris");
                        else
                            dibujarBloque("amarillo");
                    }
                glPopMatrix();
                glPushMatrix();
                    glTranslated(0.5+i,-0.5,0.5+j);
                    if(j%2==0){
                        if(i%2==0)
                            dibujarBloque("gris");
                        else
                            dibujarBloque("amarillo");
                    }else{
                        if(i%2==0)
                            dibujarBloque("amarillo");
                        else
                            dibujarBloque("gris");
                    }
                glPopMatrix();
            }
            }//Fin del bucle j


            }//Fin de la versi�n B

        }//Fin de dibujar

        /**
        * @brief Para dibujar un �nico bloque.
        * @param color El color con el que se desea dibujar el bloque.
        */
        void dibujarBloque(string color){
            cubo.dibujarCaras("todo","solido",color);
            //cubo.dibujarAristas("todo");
        }

};
#endif
