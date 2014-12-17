#ifndef ROBOT_H_INCLUDED
#define ROBOT_H_INCLUDED
//Incluimos figuraRevolucionada para poder usar los objetos de este T.D.A.
#include "figuraRevolucionada.h"
//#include "variablesGenerales.h"
#include "variablesControl.h"
#include "parametrosRover.h"

class Robot{

    //Como atributos privados contaremos con las figuras más primitivas.
    private:

        figuraSolida cubo;
        figuraRevolucionada semiCilindro;
        //Para examen:
        figuraRevolucionada cilindro;

        figuraCargada beethoven;

        double traslacion;
        double gradosBrazo3;
        double gradosBrazo2;
        double gradosBrazo1;
        double gradosSoldador;
        double add;
        double soldar;
        double gradosBase;


       // void dibujarCubo(GLfloat *color);
       // void dibujarSemiCilindro(GLfloat *color);

    public:

        //Constructor, sin trabajo.
        Robot();
        /*
        void dibujarSoporte();
        void dibujarBrazo(double medida);
        void dibujarArticulacion();
        void dibujarSoldador();
        */


        void dibujarCubo(const GLfloat color[]);
        void dibujarSemiCilindro(const GLfloat color[]);
        //Para examen:
        void dibujarCilindro(const GLfloat color[]);

        void dibujarSoporte();
        void dibujarBrazo(double medida);
        void dibujarSoldador();
        void dibujarArticulacion();
        void dibujarRobot();
        void dibujarBeethoven();

        void girarPositivo(string brazo);
        void girarNegativo(string brazo);

        void girarBasePositivo();
        void girarBaseNegativo();

        void infoGrados(){
            cout << "brazo1" << gradosBrazo1;
            cout << "brazo2" << gradosBrazo2;
            cout << "brazo3" << gradosBrazo3;
        }

};



void Robot::girarPositivo(string brazo){
    cout << "Giro Positivo";
    if(brazo=="brazo1"){
        if(gradosBrazo1<120)
            gradosBrazo1+=add;
        infoGrados();
    }
    if(brazo=="brazo2"){
        gradosBrazo2+=add;
        infoGrados();
    }
    if(brazo=="brazo3"){
        gradosBrazo3+=add;
        infoGrados();
    }
}

void Robot::girarNegativo(string brazo){
    cout << "Giro Negativo";
    if(brazo=="brazo1")
        if(gradosBrazo1>0)
            gradosBrazo1-=add;
    if(brazo=="brazo2")
        if(gradosBrazo2>-145)
            gradosBrazo2-=add;
    if(brazo=="brazo3")
        gradosBrazo3-=add;
}

void Robot::girarBasePositivo(){gradosBase++;}
void Robot::girarBaseNegativo(){gradosBase--;}

Robot::Robot(){

        //Inicializamos las primitivas gráficas necesarias para la construcción de nuestro modelo.

        //### SEMICILINDRO ###
        //Declaramos un perfil:
        vector<_vertex3f> perfilCompleto;
        //Cargamos el perfil simple completo (con tapas) con los puntos:
        perfilCompleto.push_back({0,-0.5,0});
        perfilCompleto.push_back({0.5,-0.5,0});
        perfilCompleto.push_back({0.5,0.5,0});
        perfilCompleto.push_back({0,0.5,0});
        /*Esto tb podría haberse realizado mediante la lectura de un fichero .ply */
        //Cargamos el perfil en la figura:
        semiCilindro.cargarPerfil(perfilCompleto);
        semiCilindro.revoluciona(8,0,180);

        //Para exmane:
        cilindro.cargarPerfil(perfilCompleto);
        cilindro.revoluciona(8,0,360);


        //### CUBO ###

        //Añadimos los ocho puntos que conforman nuestro cubo. Los nº con la nomen. de indices de vértices.

        //Primero la cara delantera:
        cubo.setVerticeManual(-0.5,-0.5,0.5); //0
        cubo.setVerticeManual(0.5,-0.5,0.5);  //1
        cubo.setVerticeManual(0.5,0.5,0.5);   //2
        cubo.setVerticeManual(-0.5,0.5,0.5);  //3

        //Después la cara trasera:
        cubo.setVerticeManual(-0.5,-0.5,-0.5);//4
        cubo.setVerticeManual(0.5,-0.5,-0.5); //5
        cubo.setVerticeManual(0.5,0.5,-0.5);  //6
        cubo.setVerticeManual(-0.5,0.5,-0.5); //7


        //Ahora definimos las caras de este cubo
        cubo.setCaraManual(0,1,2);
        cubo.setCaraManual(0,2,3);
        cubo.setCaraManual(1,5,6);
        cubo.setCaraManual(1,6,2);
        cubo.setCaraManual(4,5,7);
        cubo.setCaraManual(5,6,7);
        cubo.setCaraManual(0,4,7);
        cubo.setCaraManual(0,3,7);
        cubo.setCaraManual(2,3,6);
        cubo.setCaraManual(3,6,7);
        cubo.setCaraManual(0,1,5);
        cubo.setCaraManual(0,5,4);

        //Inicialización de las variables de control:
        traslacion=0.0;
        gradosBrazo3=-30.0;
        gradosBrazo2=-80.0;
        gradosBrazo1=90.0;
        gradosSoldador=0.0;
        add=2;
        soldar=0.0;
        gradosBase=0.0;

        beethoven.leerFichero("beethoven.ply");

}

    void Robot::dibujarCubo(const GLfloat color[]){
            if(MODO==1) //Vertices
                cubo.dibujarVertices("todo");
            if(MODO==2) //Aristas
                cubo.dibujarAristas("todo");
            if(MODO==3){ //Solido
                cubo.dibujarCaras("todo","solido",color);
                cubo.dibujarAristas("todo");
            }
    }

        void Robot::dibujarCilindro(const GLfloat color[]){
            if(MODO==1) //Vertices
                cilindro.dibujarVertices("todo");
            if(MODO==2) //Aristas
                cilindro.dibujarAristas("todo");
            if(MODO==3){ //Solido
                cilindro.dibujarCaras("todo","solido",color);
                cilindro.dibujarAristas("todo");
            }
        }

        void Robot::dibujarSemiCilindro(const GLfloat color[]){
            if(MODO==1) //Vertices
                semiCilindro.dibujarVertices("todo");
            if(MODO==2) //Aristas
                semiCilindro.dibujarAristas("todo");
            if(MODO==3){ //Solido
                semiCilindro.dibujarCaras("todo","solido",color);
                semiCilindro.dibujarAristas("todo");
            }
        }

        void Robot::dibujarBeethoven(){
            if(MODO==1) //Vertices
                beethoven.dibujarVertices("todo");
            if(MODO==2) //Aristas
                beethoven.dibujarAristas("todo");
            if(MODO==3){ //Solido
                beethoven.dibujarCaras("todo","solido",ROJO);
                beethoven.dibujarAristas("todo");
            }
        }

//beethoven.dibujarCaras("todo","ajedrez",ROJO);

void Robot::dibujarSoporte(){
    //La base del suelo

    //Puente izquierdo:
    glPushMatrix();
        glTranslated(0,-0.5,1);
        glScaled(2,2,1);
        glRotated(-90,1,0,0);
        dibujarSemiCilindro(GRIS_OSCURO);
    glPopMatrix();

    //Puente derecho:
    glPushMatrix();
        glTranslated(0,-0.5,-1);
        glScaled(2,2,1);
        glRotated(-90,1,0,0);
        dibujarSemiCilindro(GRIS_OSCURO);
    glPopMatrix();

    //Base circular
    glPushMatrix();
        glTranslated(0,-1,0);
        glScaled(3.8,1,3.8);
        dibujarSemiCilindro(VERDE);
    glPopMatrix();
    glPushMatrix();
        glTranslated(0,-1,0);
        glScaled(3.8,1,3.8);
        glRotated(180,0,1,0);
        dibujarSemiCilindro(VERDE);
    glPopMatrix();
}

void Robot::dibujarBrazo(double medida){

    int razon=6.0;
    if(medida!=1.0)
        razon=4.0;

    //Semiesfera izquierda del brazo:
    glPushMatrix();
        glRotated(-90,0,1,0);
        dibujarSemiCilindro(GRIS_CLARO);
    glPopMatrix();

    //Sección central del brazo:
    glPushMatrix();
        glTranslated(razon/2,0,0);
        glScaled(razon,1,1);
        dibujarCubo(AMARILLO);
    glPopMatrix();

    //Semiesfera derecha del brazo:
    glPushMatrix();
        glTranslated(razon,0,0);
        glRotated(90,0,1,0);
        dibujarSemiCilindro(GRIS_CLARO);
    glPopMatrix();
}

void Robot::dibujarSoldador(){

    //Primer semicirculo.
    glPushMatrix();
        glTranslated(0,0,-0.25);
        dibujarSemiCilindro(ROJO);
    glPopMatrix();

    //Segundo semicirculo.
    glPushMatrix();
        glTranslated(0,0,0.25);
        glRotated(180,0,1,0);
        dibujarSemiCilindro(ROJO);
    glPopMatrix();

    //Soldador.
    glPushMatrix();
        glScaled(1,1,0.5);
        glTranslated(soldar,0,0);
        dibujarCubo(NARANJA);
    glPopMatrix();

}

void Robot::dibujarArticulacion(){
    //La rotación de la articulación se configura antes de llamar a dibujarArcitulación

    //Primer brazo.
    glPushMatrix();
        glRotated(gradosBrazo1,0,0,1); //Esta rotación rota todo lo que haya detrás.
        glRotated(90,1,0,0); //Rotación que nos servirá para todos los brazos ya que se hereda dentro del PushMatrix();
        dibujarBrazo(1.0);


    //Segundo brazo.
    glPushMatrix();
        glTranslated(6,1,0);
        glRotated(gradosBrazo2,0,1,0);
        dibujarBrazo(1.0);

        //Sección de examen:
        /*
        glPushMatrix();
            glTranslated(-1,0,0); //En el extremo interior.
            //glTranslated(7,0,0); //En el extremo exterior
            dibujarCilindro(VIOLETA);
        glPopMatrix();
        */
        //Fin de sección de examen

     glPushMatrix();
                glTranslated(6,1,0);
                glRotated(gradosBrazo3,0,1,0);
                dibujarBrazo(0.5);

                //Sección examen:
                /*
                glPushMatrix();
                    glTranslated(10,1,0);
                    glRotated(90,0,0,1);
                    dibujarBeethoven();
                glPopMatrix();
                */
                //Fin sección examen

    glPopMatrix();

    glPopMatrix();

    glPopMatrix();

}

void Robot::dibujarRobot(){


    glPushMatrix();
        glRotated(gradosBase,0,1,0);
        dibujarSoporte();
        dibujarArticulacion();
    glPopMatrix();

}






#endif // ROBOT_H_INCLUDED
