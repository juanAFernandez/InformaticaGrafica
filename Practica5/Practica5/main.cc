//**************************************************************************
// Práctica 4
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

/*
    Modificaciones:
        -Trabajando con la luz
*/

#include "stdlib.h"
#include "stdio.h"
#include <windows.h>
#include <GL/glut.h>
#include <ctype.h>
#include <iostream>

// ## Extra para texto en el viewport ## //
//#include "display.h"



#include "figuraCargada.h"


//También incluimos figuraRevolucionada.h (epicentro de esta práctica)
#include "figuraRevolucionada.h"

#include "perfil.h"

#include "variablesControl.h"


#include "rover.h"
#include "suelo.h"
#include "parametrosRover.h"

//#include "TextureManager.h"

    //TextureManager texLoader;


#include "FreeImage.h"
//(http://freeimage.sourceforge.net/)
#include "TextureLoader.h"

#include "materiales.h"

//#include "loadBMP.cpp"

const int PICK=1;


/*  Create checkerboard texture  */
#define checkImageWidth 64
#define checkImageHeight 64
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];

//static GLuint texName;

static GLuint texturaLata;
static GLuint texturaMadera;
static GLuint texturaIG;

static GLuint identificadorImagen;

void makeCheckImage(void)
{
   int i, j, c;

   for (i = 0; i < checkImageHeight; i++) {
      for (j = 0; j < checkImageWidth; j++) {
         c = ((((i&0x8)==0)^((j&0x8))==0))*255;
         checkImage[i][j][0] = (GLubyte) c;
         checkImage[i][j][1] = (GLubyte) c;
         checkImage[i][j][2] = (GLubyte) c;
         checkImage[i][j][3] = (GLubyte) 255;
      }
   }
}











Perfil perfilSinTapasPrueba("perfilSinTapas");


// Texto:

//Display display("Despliegue de texto");

//Imágenes:

//#include "jpg_imagen.hpp"

//Declaramos un puntero a la imagen y cargamos en memoria esta:
//jpg::Imagen * pimg = new ::Imagen("text-lata-1.jpg");



    rover curiosity;
    suelo base(20);

    figuraRevolucionada cilindro;
    figuraRevolucionada semicilindro;
    figuraRevolucionada cono;

    figuraRevolucionada ejemploCubo("ejemploCubo");


    boolean animacion=false;
    int contadorAnimacion=0;

    boolean ejercicioBeethoven=false;
    boolean ejercicioTextura=false;



/*Sección de definición de figuras (el modelado). Donde esta se realiza tan sólo una vez dejando clara la
diferencia entre el modelado (definición de sus puntos y configuración de sus aristas) y la parte de la visualización
de la que se encargará un función independiente.
*/
    //Declaramos algunas figuras básicas.
    figuraSimple triangulo("triangulo");
    figuraSolida cubo("cubo");



    //Perfil para un cono para P4 que simule la fuente de luz:
    vector<_vertex3f>perfilCono;

    int velocidadCono=2;
    double gradoCono=0.0;

    figuraCargada beethoven;



    //Correspondiente a la práctica 2 ############

    //Introducimos vertices a un perfil para que a partir de ellos e genere la figura
    vector<_vertex3f> perfil;

    //La figura del peon (cuyo perfil será cargado desde un .ply)
    figuraRevolucionada peon("peon");


    //Peonees del escenario 2
    figuraRevolucionada peonA("peonA");
    figuraRevolucionada peonB("peonB");
    figuraRevolucionada peonC("peonC");

    figuraRevolucionada cuerpoLata("cuerpoLata");
    figuraRevolucionada culoLata("culoLata");
    figuraRevolucionada bocaLata("bocaLata");




    //Una figura extra con la que probar cosas.
    figuraRevolucionada figuraPrueba("figura de prueba");

    //Perfiles simples para el examen:
    vector<_vertex3f> perfilCompleto;
    vector<_vertex3f> perfilParcialSinTapaArriba;
    vector<_vertex3f> perfilParcialSinTapaAbajo;
    vector<_vertex3f> perfilSinTapas;

    //Figuras para cargar y revolucionar los perfiles simples:

    vector <figuraRevolucionada> vectorFiguras;

    figuraRevolucionada figuraPerfilCompleto("h");
    figuraRevolucionada figuraPerfilParcialSinTapaArriba("a");
    figuraRevolucionada figuraPerfilParcialSinTapaAbajo("b");
    figuraRevolucionada figuraPerfilSinTapas("c");


//###############




// tamaño de los ejes
const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=500,UI_window_pos_y=30,UI_window_width=800,UI_window_height=730;

//**************************************************************************
//
//***************************************************************************

void clear_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
//  Front_plane>0  Back_plane>PlanoDelantero)
glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);




    if(EJERCICIO==1){

    //Establezco la posición de la luz 0

    /*

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            //glLoadIdentity();
            //glTranslatef(0,0,-Observer_distance);
            //glRotatef(Observer_angle_x,1,0,0);
            //glRotatef(Observer_angle_y,0,1,0);
            //Definición de la posición de la luz local:
            const GLfloat posicionLuzLocal[]={8.0, 0.0, 8.0, 1.0};

            glColor3fv(VERDE);
            //Establecemos el grosor de los vértices (al dibujarlos)
            glPointSize(40);
                glBegin(GL_POINTS);
                        glVertex3f(8.0, 0.0, 0.0);
                glEnd();

            glLightfv(GL_LIGHT0, GL_POSITION, posicionLuzLocal);
        glPopMatrix();

    */

       //Ajuste de luz a movimiento de cámara:

       const GLfloat posicionLuzLocal1[]={8.0, 0.0, 0.0, 1.0};

       //Cono de light 1 //FIJO
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glLoadIdentity();

            glTranslatef(0,0,-Observer_distance);
            glRotatef(Observer_angle_x,1,0,0);
            glRotatef(Observer_angle_y,0,1,0);

            glLightfv(GL_LIGHT0, GL_POSITION, posicionLuzLocal1);
        glPopMatrix();


        const GLfloat posicionLuzLocal2[]={0.0, 8.0, 0.0, 1.0};

       //Cono de light 2 //MOVIL
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glLoadIdentity();


            glTranslatef(0,0,-Observer_distance);
            glRotatef(Observer_angle_x,1,0,0);
            glRotatef(Observer_angle_y,0,1,0);

            glRotated(gradoCono,1,0,0);

            glLightfv(GL_LIGHT1, GL_POSITION, posicionLuzLocal2);
        glPopMatrix();



    }

    if(EJERCICIO==2 || EJERCICIO==3){
         const GLfloat posicionLuzLocal2[]={0.0, 16.0, 0.0, 1.0};

       //Cono de light 2 //MOVIL
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glLoadIdentity();


            glTranslatef(0,0,-Observer_distance);
            glRotatef(Observer_angle_x,1,0,0);
            glRotatef(Observer_angle_y,0,1,0);

            glRotated(gradoCono,1,0,0);

            glLightfv(GL_LIGHT1, GL_POSITION, posicionLuzLocal2);
        glPopMatrix();


    }

    if(EJERCICIO==4){
        const GLfloat posicionLuzLocal2[]={0.0, 32.0, 0.0, 1.0};

       //Cono de light 2 //MOVIL
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glLoadIdentity();


            glTranslatef(0,0,-Observer_distance);
            glRotatef(Observer_angle_x,1,0,0);
            glRotatef(Observer_angle_y,0,1,0);

            //glRotated(gradoCono,1,0,0);

            glLightfv(GL_LIGHT1, GL_POSITION, posicionLuzLocal2);
        glPopMatrix();


        const GLfloat posicionLuzLocal1[]={0.0, 7.5, 50, 1.0};

       //Cono de light 2 //MOVIL
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glLoadIdentity();


            glTranslatef(0,0,-Observer_distance);
            glRotatef(Observer_angle_x,1,0,0);
            glRotatef(Observer_angle_y,0,1,0);

            //glRotated(gradoCono,1,0,0);

            glLightfv(GL_LIGHT0, GL_POSITION, posicionLuzLocal1);
        glPopMatrix();
    }
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}



/*
* Lee una textura desde una imagen en formato BMP
*/
/*
void cargarTextura(char *filename)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   glEnable(GL_DEPTH_TEST);

   RgbImage theTexMap( filename );

   // Pixel alignment: each row is word aligned (aligned to a 4 byte boundary)
   //    Therefore, no need to call glPixelStore( GL_UNPACK_ALIGNMENT, ... );


   glGenTextures(1, &texName);                  // Create The Texture
   glBindTexture(GL_TEXTURE_2D, texName);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

   // Typical Texture Generation Using Data From The Bitmap


    //glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    //glTexImage2D(GL_TEXTURE_2D, 0, 3, theTexMap.GetNumCols(), theTexMap.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData() );
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3,theTexMap.GetNumCols(), theTexMap.GetNumRows(), GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData() );
    cout << "Imagen cargada! " << theTexMap.GetNumRows() << "x" << theTexMap.GetNumCols() << endl;
}
*/
void cargarTextura(GLuint &nombreTextura, char *filename){

   //Debemos parasr el primer parámetro por referencia para que no se pierda su modificación.
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   glEnable(GL_DEPTH_TEST);

   RgbImage theTexMap( filename );

   // Pixel alignment: each row is word aligned (aligned to a 4 byte boundary)
   //    Therefore, no need to call glPixelStore( GL_UNPACK_ALIGNMENT, ... );


   glGenTextures(1, &nombreTextura);                  // Create The Texture
   glBindTexture(GL_TEXTURE_2D, nombreTextura);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

   // Typical Texture Generation Using Data From The Bitmap


    //glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    //glTexImage2D(GL_TEXTURE_2D, 0, 3, theTexMap.GetNumCols(), theTexMap.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData() );
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3,theTexMap.GetNumCols(), theTexMap.GetNumRows(), GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData() );

}

//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects()
{

    if(EJERCICIO==1){ // ## Beethoven con dos luces ## //

        //Examen:

        //Modo sólo vértices
        if(MODO==1){
            figuraPerfilCompleto.dibujarVertices("todo");
        }

        //Modo sólo aristas
        if(MODO==2){
            figuraPerfilCompleto.dibujarAristas("todo");
        }

        //Modo sólido. Sólido más aristas.
        if(MODO==3){
            //figuraPerfilSinTapas.dibujarCaras("todo","solido",VERDE);
            //figuraPerfilSinTapas.dibujarAristas("todo");
            //glEnable(GL_LIGHTING);

                figuraPerfilCompleto.dibujarCaras("todo","solido",BLANCO);
                cout << figuraPerfilCompleto.numeroVertices();
                //figuraPerfilCompleto.dibujarTextura(texturaLata);
            //glDisable(GL_LIGHTING);
        }

        //Mondo normales. Sólido, aristas más normales.
        if(MODO==6){
            figuraPerfilCompleto.dibujarCaras("todo","solido",VERDE);
            figuraPerfilCompleto.dibujarAristas("todo");
            figuraPerfilCompleto.dibujarNormales();
        }
        //Mondo normales. Sólido, aristas más normales.
        if(MODO==7){
            figuraPerfilCompleto.dibujarCaras("todo","solido",VERDE);
            figuraPerfilCompleto.dibujarAristas("todo");
            figuraPerfilCompleto.dibujarNormalesVertices();
        }

        //Modo sólido con iluminación PLANA
        if(MODO==4){
            glEnable(GL_LIGHTING); //Activo la iluminación.
            beethoven.dibujarCarasIluminacionPlana(plasticoVerde);
            glDisable(GL_LIGHTING); //Desactivo la iluminación.

        }

        if(MODO==5){
            glEnable(GL_LIGHTING);
            figuraPerfilCompleto.dibujarCarasIluminacionSuave(plasticoVerde);
            glDisable(GL_LIGHTING);
        }

    //Si vemos la escena iluminada, dibujamos los "focos de luz":
    if(MODO==4 || MODO==5 ||MODO==3){

    //Cono de light 0
    glPushMatrix();
     glTranslated(8,0,0);
     glRotated(-90,0,0,1);
     cono.dibujarCaras("todo","solido",AMARILLO);
     cono.dibujarAristas("todo");
    glPopMatrix();

    //Cono de light 1
    glPushMatrix();
     glRotated(gradoCono,1,0,0);
     glTranslated(0,8,0);
     cono.dibujarCaras("todo","solido",AMARILLO);
     cono.dibujarAristas("todo");
    glPopMatrix();

    }

    }



    if(EJERCICIO==2){ // ## Lata CocaCola y peones con distintos materiales con una luz ## //


        /*

        //ejemploCubo.dibujarTextura(texName);
        ejemploCubo.dibujarTextura(texturaMadera);
        //ejemploCubo.muestraCoordenadasTextura();

        glPushMatrix();
            glTranslated(3,0,0);
            peonA.dibujarVertices("todo");
            peonA.dibujarAristas("todo");
        glPopMatrix();

        */

        /*
        if(MODO==4){
            glEnable(GL_LIGHTING); //Activo la iluminación.
            glPushMatrix();
                glScaled(4,4,4);
                //cuerpoLata.dibujarCarasIluminacionPlana(plasticoRojo);
                peonB.dibujarCarasIluminacionPlana(plasticoVerde);
                //peonB.dibujarNormales();
            glPopMatrix();
            glDisable(GL_LIGHTING); //Desactivo la iluminación.

        }
        */

    /*
    if(MODO==4 || MODO==5){

    //Cono de light 1
    glPushMatrix();
     glRotated(gradoCono,1,0,0);
     glTranslated(0,8,0);
     cono.dibujarCaras("todo","solido",AMARILLO);
     cono.dibujarAristas("todo");
    glPopMatrix();

    } */



      glEnable(GL_LIGHTING);

        //Para que la textura se combine con el color del objeto
      //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); --> se ve iluminada
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);

         //Lata (con sus tres partes):
         glPushMatrix();
            glScaled(2,2,2);
            //glTranslated(0,2,0);
            //cuerpoLata.dibujarPerfil();
            //cuerpoLata.dibujarCarasIluminacionPlana(plasticoBlanco);
            //cuerpoLata.dibujarNormales();
            cuerpoLata.dibujarTextura(texturaLata);
            //cuerpoLata.dibujarNormales();

            //cuerpoLata.dibujarNormales();
            //bocaLata.dibujarPerfil();
            //bocaLata.dibujarAristas("todo");
            //bocaLata.dibujarCaras("todo","solido", ROJO);

            //bocaLata.dibujarCarasIluminacionPlana(chrome);

            //culoLata.dibujarPerfil();
            //culoLata.dibujarAristas("todo");
            //culoLata.dibujarCaras("todo","solido", ROJO);

            //culoLata.dibujarCarasIluminacionPlana(chrome);

            //culoLata.dibujarNormales();
        glPopMatrix();




        glPushMatrix();
            glTranslated(3,2,0);
            //peonA.dibujarPerfil();
            //peonA.dibujarNormales();
            //peonA.dibujarAristas("todo");
            //peonA.dibujarTextura(texturaMadera);
            peonA.dibujarCarasIluminacionPlana(plasticoAmarillo);
            //peonA.dibujarNormales();
        glPopMatrix();

        glPushMatrix();
            glTranslated(6,2,0);
            //peonB.dibujarPerfil();
            peonB.dibujarCarasIluminacionPlana(plasticoVerde);
        glPopMatrix();

        glPushMatrix();
            glTranslated(9,2,0);
            //peonC.dibujarPerfil();
            peonC.dibujarCarasIluminacionPlana(plasticoRojo);
            peonC.dibujarNormales();
        glPopMatrix();


        glDisable(GL_LIGHTING);





    }

    if(EJERCICIO==3){ // ## Cubo en el que se aplica una imagen con un texto. ## //


        //Dibujamos una pantalla con la imagen:
        glDisable(GL_LIGHTING);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texturaIG);

        glBegin(GL_QUADS);
        glColor3f(1.0f,1.0f,1.0f);

            glTexCoord2f(0,0);
            glVertex3f(-5,0,-5);

            glTexCoord2f(1,0);
            glVertex3f(5,0,-5);

            glTexCoord2f(1,1);
            glVertex3f(5,5,-5);

            glTexCoord2f(0,1);
            glVertex3f(-5,5,-5);



        glEnd();


        glFlush();
        glDisable(GL_TEXTURE_2D);



        //Modo sólo vértices
        if(MODO==1){
            cubo.dibujarVertices("todo");
        }
        //Modo sólo aristas
        if(MODO==2){
            cubo.dibujarAristas("todo");
        }
        //Modo sólido. Sólido más aristas.
        if(MODO==3){
            //cubo.dibujarCaras("todo","solido",VERDE);
            //cubo.dibujarAristas("todo");
            //cubo.dibujarTextura(texturaIG);

            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texturaMadera);
            glColor3f(1.0f,1.0f,1.0f);

            //DANDO LAS COORDENADAS DE TEXTURA DE UN CUBO A MANO DE FORMA MUY ESPECÍFICA

            int a,b,c,d;

            //Cara A:
            a=0;b=1;c=2;d=3;
            glBegin(GL_QUADS);
                glTexCoord2f(0,0.33);
                glVertex3f(cubo.getVertice(a).x, cubo.getVertice(a).y, cubo.getVertice(a).z );
                glTexCoord2f(0.25,0.33);
                glVertex3f(cubo.getVertice(b).x, cubo.getVertice(b).y, cubo.getVertice(b).z );
                glTexCoord2f(0.25,0.66);
                glVertex3f(cubo.getVertice(c).x, cubo.getVertice(c).y, cubo.getVertice(c).z );
                glTexCoord2f(0,0.66);
                glVertex3f(cubo.getVertice(d).x, cubo.getVertice(d).y, cubo.getVertice(d).z );
            glEnd();

            //Cara B:
            a=1;b=5;c=6;d=2;
            glBegin(GL_QUADS);
                glTexCoord2f(0.25,0.33);
                glVertex3f(cubo.getVertice(a).x, cubo.getVertice(a).y, cubo.getVertice(a).z );
                glTexCoord2f(0.50,0.33);
                glVertex3f(cubo.getVertice(b).x, cubo.getVertice(b).y, cubo.getVertice(b).z );
                glTexCoord2f(0.50,0.66);
                glVertex3f(cubo.getVertice(c).x, cubo.getVertice(c).y, cubo.getVertice(c).z );
                glTexCoord2f(0.25,0.66);
                glVertex3f(cubo.getVertice(d).x, cubo.getVertice(d).y, cubo.getVertice(d).z );
            glEnd();

            //Cara C:
            a=5;b=4;c=7;d=6;
            glBegin(GL_QUADS);
                glTexCoord2f(0.50,0.33);
                glVertex3f(cubo.getVertice(a).x, cubo.getVertice(a).y, cubo.getVertice(a).z );
                glTexCoord2f(0.75,0.33);
                glVertex3f(cubo.getVertice(b).x, cubo.getVertice(b).y, cubo.getVertice(b).z );
                glTexCoord2f(0.75,0.66);
                glVertex3f(cubo.getVertice(c).x, cubo.getVertice(c).y, cubo.getVertice(c).z );
                glTexCoord2f(0.50,0.66);
                glVertex3f(cubo.getVertice(d).x, cubo.getVertice(d).y, cubo.getVertice(d).z );
            glEnd();


            //Cara D:
            a=4;b=0;c=3;d=7;
            glBegin(GL_QUADS);
                glTexCoord2f(0.75,0.33);
                glVertex3f(cubo.getVertice(a).x, cubo.getVertice(a).y, cubo.getVertice(a).z );
                glTexCoord2f(1,0.33);
                glVertex3f(cubo.getVertice(b).x, cubo.getVertice(b).y, cubo.getVertice(b).z );
                glTexCoord2f(1,0.66);
                glVertex3f(cubo.getVertice(c).x, cubo.getVertice(c).y, cubo.getVertice(c).z );
                glTexCoord2f(0.75,0.66);
                glVertex3f(cubo.getVertice(d).x, cubo.getVertice(d).y, cubo.getVertice(d).z );
            glEnd();

            //Cara E:
            a=2;b=6;c=7;d=3;
            glBegin(GL_QUADS);
                glTexCoord2f(0.25,0.66);
                glVertex3f(cubo.getVertice(a).x, cubo.getVertice(a).y, cubo.getVertice(a).z );
                glTexCoord2f(0.50,0.66);
                glVertex3f(cubo.getVertice(b).x, cubo.getVertice(b).y, cubo.getVertice(b).z );
                glTexCoord2f(0.50,1);
                glVertex3f(cubo.getVertice(c).x, cubo.getVertice(c).y, cubo.getVertice(c).z );
                glTexCoord2f(0.25,1);
                glVertex3f(cubo.getVertice(d).x, cubo.getVertice(d).y, cubo.getVertice(d).z );
            glEnd();

            //Cara F:
            a=0;b=4;c=5;d=1;
            glBegin(GL_QUADS);
                glTexCoord2f(0.25,0);
                glVertex3f(cubo.getVertice(a).x, cubo.getVertice(a).y, cubo.getVertice(a).z );
                glTexCoord2f(0.50,0);
                glVertex3f(cubo.getVertice(b).x, cubo.getVertice(b).y, cubo.getVertice(b).z );
                glTexCoord2f(0.50,0.33);
                glVertex3f(cubo.getVertice(c).x, cubo.getVertice(c).y, cubo.getVertice(c).z );
                glTexCoord2f(0.25,0.33);
                glVertex3f(cubo.getVertice(d).x, cubo.getVertice(d).y, cubo.getVertice(d).z );
            glEnd();


            glFlush();
            glDisable(GL_TEXTURE_2D);





            cubo.muestraCoordenadasTextura();
        }
        //Modo sólido con iluminación PLANA
        if(MODO==4){
            glEnable(GL_LIGHTING); //Activo la iluminación.
            cubo.dibujarCarasIluminacionPlana(plasticoVerde);
            glDisable(GL_LIGHTING); //Desactivo la iluminación.
        }
        //Modo sólido con iluminación SUAVE
        if(MODO==5){
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHTING);
            cubo.dibujarCarasIluminacionSuave(plasticoVerde);
            glDisable(GL_LIGHTING);
        }
        //Mondo normales. Sólido, aristas más normales.
        if(MODO==6){
            cubo.dibujarCaras("todo","solido",VERDE);
            cubo.dibujarAristas("todo");
            cubo.dibujarNormales();
        }
        //Mondo normales. Sólido, aristas más normales de los vértices
        if(MODO==7){
            cubo.dibujarCaras("todo","solido",VERDE);
            cubo.dibujarAristas("todo");
            cubo.dibujarNormalesVertices();
        }
        //Si vemos la escena iluminada, dibujamos los "focos de luz":
        if(MODO==4 || MODO==5){
            //Cono de light 1
            glPushMatrix();
                glRotated(gradoCono,1,0,0);
                glTranslated(0,8,0);
                cono.dibujarCaras("todo","solido",AMARILLO);
                cono.dibujarAristas("todo");
            glPopMatrix();

        }
    }

    if(EJERCICIO==4){
    /* ## Escena práctica 3 con iluminación superior rotatoria e iluminación en faros del curiosity.
    Además de una imagen de tierra en el suelo o de un mosaico con todas las imágenes. ## */

        //glDisable(GL_LIGHTING);

        glPushMatrix();
            //base.dibujarSuelo();
            curiosity.dibujarRover();
            base.dibujarSuelo();
        glPopMatrix();
    }





}



//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{

clear_window();
change_observer();
draw_axis();

//Función que en última instancia manda a dibujar los objetos.
draw_objects();

//Dibujo de texto
#define ORANGE          1.0f, 0.7f, 0.0f

//display.displayText("Esto es un titulo", 15, 25, Window_width, Window_height, ORANGE);

glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}



void ajusteEscena(int escena){

    //Parámetros de iluminación, son los tres colores más el canal alfa.
    GLfloat luzAmbiente[4];
    GLfloat luzDifusa[4];
    GLfloat luzEspecular[4];

    //Parámetros de posición de luces:


    if(escena==1){

        glClearColor(0,0,0,1); //Fondo blanco



        //Especificamos las características de las luces:
        luzAmbiente={1, 1, 1, 1.0};
        luzDifusa={1, 1, 1, 1.0};
        luzEspecular={0, 0, 0, 1.0};


        //Aplicamos las tres componentes a la luz número 0
        glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
        glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);

        //Aplicamos las tres componentes a la luz número 1 (no tienen por qué ser las mismas)
        glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa);
        glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecular);

        //Activamos dos luces:

        //Activamos la luz 0 (DERECHA FIJA)
        glEnable(GL_LIGHT0);
        //Activamos la luz 1 (SUPERIOR ROTATORIA)
        glEnable(GL_LIGHT1);

/*

        const GLfloat posicionLuzLocal1[]={8.0, 0.0, 0.0, 1.0};

       //Cono de light 1
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glLoadIdentity();

            glTranslatef(0,0,-Observer_distance);
            glRotatef(Observer_angle_x,1,0,0);
            glRotatef(Observer_angle_y,0,1,0);

            glLightfv(GL_LIGHT0, GL_POSITION, posicionLuzLocal1);
        glPopMatrix();


        const GLfloat posicionLuzLocal2[]={0.0, 8.0, 0.0, 1.0};

       //Cono de light 2
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glLoadIdentity();


            glTranslatef(0,0,-Observer_distance);
            glRotatef(Observer_angle_x,1,0,0);
            glRotatef(Observer_angle_y,0,1,0);

            glRotated(gradoCono,1,0,0);

            glLightfv(GL_LIGHT1, GL_POSITION, posicionLuzLocal2);
        glPopMatrix();

*/

    }


    if(escena==2){

        glClearColor(0,0,0,1); //Fondo blanco

        //Especificamos las características de las luces:
        luzAmbiente={1, 1, 1, 1.0};
        luzDifusa={1, 1, 1, 1.0};
        luzEspecular={0, 0, 0, 1.0};



        //Aplicamos las tres componentes a la luz número 0
        glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa);
        glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecular);

        //Activamos una sola luz general:

        glDisable(GL_LIGHT0);
        glEnable(GL_LIGHT1);

    }

    if(escena==3){


        //Especificamos las características de las luces:
        luzAmbiente={1, 1, 1, 1.0};
        luzDifusa={1, 1, 1, 1.0};
        luzEspecular={0, 0, 0, 1.0};

        //Aplicamos las tres componentes a la luz número 1 (no tienen por qué ser las mismas)
        glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa);
        glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecular);


        //Desactivamos toda iluminación
        glDisable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
    }

    if(escena==4){



        glClearColor(0,0,0,1); //Fondo negro

        luzAmbiente={1, 1, 1, 1.0};
        luzDifusa={intensidadLuz, intensidadLuz, intensidadLuz , 1.0};
        luzEspecular={0, 0, 0, 1.0};

        //Aplicamos las tres componentes a la luz número 1 (no tienen por qué ser las mismas)
        glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa);
        glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecular);

        //La delantera del coche
        //Aplicamos las tres componentes a la luz número 1 (no tienen por qué ser las mismas)
        glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
        glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);


        glEnable(GL_LIGHT0);
        //Activamos la luz 1 (SUPERIOR)
        glEnable(GL_LIGHT1);
        glEnable(GL_NORMALIZE);

    }
}


//***************************************************************************
// Funcion llamada cuando se pulsa sobre una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y){

//## CONTROL DE INTERACCIÓN POR TECLADO ##//


//Para salir del programa:
if(toupper(Tecla1)=='Q') exit(0);

//Control del ejercicio seleccionado:
//## 1: Beethoven para iluminacion (plana/suave) con dos focos, uno giratorio y otro fijo.
if(toupper(Tecla1)=='1'){EJERCICIO=1; ajusteEscena(1); draw_scene(); cout << "Seleccionada escena 1:  Beethoven con dos focos" << endl;}
//## 2: EJERCICIO CENTRAL--> Lata más tres peones.
if(toupper(Tecla1)=='2'){EJERCICIO=2; ajusteEscena(2); draw_scene(); cout << "Seleccionada escena 2:  Lata más tres peones de distintos materiales" << endl;}
//## 3: EJERCICIO TRES--> Cubo con imagen texturizada a modo de dado.
if(toupper(Tecla1)=='3'){EJERCICIO=3, ajusteEscena(3); draw_scene(); cout << "Seleccionada escena 3: Cubo con imagen texturizada simple" << endl;}
//## 4: EJERCICIO CUATRO--> curiosity
if(toupper(Tecla1)=='4'){EJERCICIO=4; ajusteEscena(4); draw_scene(); cout << "Seleccionada escena 4:  Rover Curiosity" << endl;}




//Control del modo de VSUALIZACIÓN:
//Para dibujar la escena con sólo los VERTICES.
if(toupper(Tecla1)=='V'){MODO=1; draw_scene();}
//Para dibujar la escena con sólo con ARISTAS.
if(toupper(Tecla1)=='A'){MODO=2; draw_scene();}
//Para dibujar la escena en modo SÓLIDO
if(toupper(Tecla1)=='S'){MODO=3; draw_scene();}
//Para dibujar la escena en modo SÓLIDO con las normales de las caras dibujadas.
if(toupper(Tecla1)=='N'){MODO=6; draw_scene();}
//Para dibujar la escena en modo SÓLIDO con las normales de los vértices dibujadas.
if(toupper(Tecla1)=='B'){MODO=7; draw_scene();}
//Para dibujar la escena en modo SÓLIDO con ILUMINACIÓN PLANA (CARAS)
if(toupper(Tecla1)=='Z'){MODO=4; draw_scene();}
//Para dibujar la escena en modo SÓLIDO con ILUMINACIÓN SUAVE (VÉRTICES)
if(toupper(Tecla1)=='X'){MODO=5; draw_scene();}

//Activación de la animación:
if(toupper(Tecla1)=='M'){
    if(animacion==false)
        animacion=true;
    else if(animacion==true)
        animacion=false;
    draw_scene();
}

//## Control MOVIMIENTO del Curiosity ##
//Mov. adelante
if(toupper(Tecla1)=='T'){
    //###Aumentamos el número de revoluciones:
   // GRADOS_RUEDA_DERECHA++;
   // GRADOS_RUEDA_IZQUIERDA++;

    curiosity.desplazaAdelante();

  //  X+=cos(GRADOS_GIRO_ROVER);
  //  Z+=sin(GRADOS_GIRO_ROVER);

    //Llamamos a dibujar escena donde se decide que y como dibujar
    draw_scene();
}
//Mov. atrás
if(toupper(Tecla1)=='G'){
    //###Aumentamos el número de revoluciones:
    //GRADOS_RUEDA_DERECHA--;
    //GRADOS_RUEDA_IZQUIERDA--;
    //Llamamos a dibujar escena donde se decide que y como dibujar

    curiosity.desplazaAtras();

    draw_scene();
}
//Mov. giro derecha
if(toupper(Tecla1)=='H'){
    //###Aumentamos el número de revoluciones:
 //   GRADOS_GIRO_ROVER--;

    curiosity.giraDerecha();

    //Llamamos a dibujar escena donde se decide que y como dibujar
    draw_scene();
}
//Mov. giro izquierda
if(toupper(Tecla1)=='F'){
    //###Aumentamos el número de revoluciones:
  //  GRADOS_GIRO_ROVER++;
    //Llamamos a dibujar escena donde se decide que y como dibujar

    curiosity.giraIzquierda();

    draw_scene();
}

//Control de brazo robótico del Curiosity
if (toupper(Tecla1)=='Y') {curiosity.brazo.girarPositivo("brazo1");curiosity.brazo.girarNegativo("brazo2"); animacion=false; draw_scene();};
if (toupper(Tecla1)=='U') {curiosity.brazo.girarNegativo("brazo1");curiosity.brazo.girarPositivo("brazo2");draw_scene();};
if(toupper(Tecla1)=='I'){curiosity.brazo.girarPositivo("brazo2");draw_scene();}
if(toupper(Tecla1)=='O'){curiosity.brazo.girarNegativo("brazo2");draw_scene();}
if(toupper(Tecla1)=='P'){curiosity.brazo.girarPositivo("brazo3"); draw_scene();}
if(toupper(Tecla1)=='J'){curiosity.brazo.girarNegativo("brazo3"); draw_scene();}
if(toupper(Tecla1)=='K'){curiosity.brazo.girarBasePositivo(); draw_scene();}
if(toupper(Tecla1)=='L'){curiosity.brazo.girarBaseNegativo(); draw_scene();}

//Control de iluminación:
if(toupper(Tecla1)=='+'){intensidadLuz+=0.1; ajusteEscena(4); draw_scene();}
if(toupper(Tecla1)=='-'){intensidadLuz-=0.1; ajusteEscena(4); draw_scene();}



}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{

switch (Tecla1){
    //Tecla izquierda:
	case GLUT_KEY_LEFT:
        Observer_angle_y--;
        break;
    //Tecla derecha:
	case GLUT_KEY_RIGHT:
        Observer_angle_y++;
        break;
    //Tecla arriba:
	case GLUT_KEY_UP:
        Observer_angle_x--;
        break;
    //Tecla abajo:
	case GLUT_KEY_DOWN:
        Observer_angle_x++;
        break;
	case GLUT_KEY_PAGE_UP:
        Observer_distance*=1.2;
        break;
	case GLUT_KEY_PAGE_DOWN:
        Observer_distance/=1.2;
        break;
	}

	//cout << "Angulos del observador y distancia:" << endl;
    //cout << "x: " << Observer_angle_x << " y: " << Observer_angle_y << " distancia: " << Observer_distance << endl;

glutPostRedisplay();
}

void mensaje(){
cout << "hola";}



void controlRaton(int boton, int estado, int x, int y){


if( (boton==GLUT_LEFT_BUTTON) && (estado==GLUT_DOWN))
            cout << "Clap your hand say yeah!";
}

void ratonMovido(int x, int y){
    //Info por terminal:
    cout << "Raton x: " << x << " y:" << y << endl;
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Window_width=.5;
Window_height=.5;
Front_plane=1;
Back_plane=1000;

// se inicia la posicion del observador, en el eje z
Observer_distance=24*Front_plane;
Observer_angle_x=4;
Observer_angle_y=0;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...

//if(ejercicioTextura)
    //glClearColor(1,1,1,1); //Fondo blanco

//if(EJERCICIO==1)

    //Para esta práctica el fondo de todos los escenarios será negro
    glClearColor(0,0,0,1); //Fondo negro

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);

//glEnable(GL_NORMALIZE);
change_projection();
glViewport(0,0,UI_window_width,UI_window_height);
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************


//Animación.
void idle(void){


if(animacion){
        Sleep(50);

        if(EJERCICIO==1){
            //Animamos el foco de luz superior.
            gradoCono+=velocidadCono;
            //Giramos toda la escena hacia la derecha.
            Observer_angle_y++;
        }else if(EJERCICIO==2){
            //Animamos el foco de luz superior.
            gradoCono+=velocidadCono;
        }else{
            curiosity.desplazaAdelante();
            curiosity.giraDerecha();
            curiosity.giraDerecha();


            curiosity.brazo.girarBasePositivo();

            if(contadorAnimacion<25){
                curiosity.brazo.girarPositivo("brazo1");
            }
            if(contadorAnimacion>40 && contadorAnimacion<70){
                curiosity.brazo.girarNegativo("brazo1");
                curiosity.brazo.girarPositivo("brazo2");
            }

            curiosity.brazo.girarPositivo("brazo3");

        }
        glutPostRedisplay();

    /*

        cout << "Animacion paso " << contadorAnimacion << endl;
        contadorAnimacion++;
        if(contadorAnimacion==70)
            contadorAnimacion=0;
    */
}

}




int main(int argc, char **argv)
{




        beethoven.leerFichero("beethoven.ply");
        //Al hacer lo anterior se cargan las caras y las normales de las caras pero no las de los vértices.
        //Esas tenemos que calcularlas nosotros para la iluminación suave
        beethoven.calculaNormalesVertices();


    //Definimos los perfiles para el examen dándoles vértices:

        /*
           Hubiera sido interesante tener los ficheros en ficheros .ply pero windows se niega a leer ficheros que
           no sean bajados de la plataforma, parece que su codificación al guardar la información hace que no puedan
           abrirse y para lo que se va a conseguir, se ha optado por esta solución.
        */

        //Perfil del cono para la simulación de una fuente de luz:

        perfilCono.push_back({0.5,-0.5,0});
        perfilCono.push_back({0.25,0.5,0});
        perfilCono.push_back({0,0.5,0});





        //El perfil simple completo (con tapas):
        perfilCompleto.push_back({0,-1,0});
        perfilCompleto.push_back({1,-1,0});
        perfilCompleto.push_back({1,1,0});
        perfilCompleto.push_back({0,1,0});

        //El pefil simple sin tapa abajo:
        perfilParcialSinTapaAbajo.push_back({2,-1,0});
        perfilParcialSinTapaAbajo.push_back({1,1,0});
        perfilParcialSinTapaAbajo.push_back({0,1,0});

        //El perfil simple sin tapa arriba:
        perfilParcialSinTapaArriba.push_back({0,-1,0});
        perfilParcialSinTapaArriba.push_back({1,-1,0});
        perfilParcialSinTapaArriba.push_back({2,1,0});

        //El perfil simple sin tapas:
        perfilSinTapas.push_back({1,-1,0});
        perfilSinTapas.push_back({1,1,0});



        perfilSinTapasPrueba.setVerticeManual(1,-1,0);
        perfilSinTapasPrueba.setVerticeManual(1,1,0);


    //Inicializamos las figuras del tipo "figuraRevolucionada" con estos perfiles y les damos la revolución general mínima:


        //Para pruebas:

            cilindro.cargarPerfil(perfilCompleto);
            cilindro.revoluciona(64,0,360);

            semicilindro.cargarPerfil(perfilCompleto);
            semicilindro.revoluciona(8,0,360);

            cono.cargarPerfil(perfilCono);
            cono.revoluciona(16,0,360);


            ejemploCubo.cargarPerfil(perfilSinTapas);
            ejemploCubo.revoluciona(4,0,360);


            //Cargo la textura
            //ejemploCubo.cargarTextura("./text-lata-1.bmp");
            //Genero las coordenadas de textura según la revolución que he realizado
            //ejemploCubo.generaCoordenadasTextura(16,perfilSinTapas.size(),ejemploCubo.numeroVertices());
            //peonA.generaCoordenadasTextura(16);


            //ejemploCubo.muestraVertices();


        //Fin de pruebas


        //figuraPerfilCompleto.cargarPerfil(perfilCompleto);
        //figuraPerfilCompleto.revoluciona(REVOLUCIONES, GRADOS_INICIAL, GRADOS_FINAL);
        //figuraPerfilCompleto.muestraVertices();


        figuraPerfilParcialSinTapaAbajo.cargarPerfil(perfilParcialSinTapaAbajo);
        //figuraPerfilParcialSinTapaAbajo.revoluciona(REVOLUCIONES,GRADOS_INICIAL, GRADOS_FINAL);

        figuraPerfilParcialSinTapaArriba.cargarPerfil(perfilParcialSinTapaArriba);
        //figuraPerfilParcialSinTapaArriba.revoluciona(REVOLUCIONES, GRADOS_INICIAL, GRADOS_FINAL);

        //figuraPerfilSinTapas.cargarPerfil(perfilSinTapas);
        //figuraPerfilSinTapas.revoluciona(REVOLUCIONES, GRADOS_INICIAL, GRADOS_FINAL);

        //Después de inicializarlas las meto en un vector para poder trabajar con ellas mejor.

        vectorFiguras.push_back(figuraPerfilCompleto);
        vectorFiguras.push_back(figuraPerfilParcialSinTapaAbajo);
        vectorFiguras.push_back(figuraPerfilParcialSinTapaArriba);
        vectorFiguras.push_back(figuraPerfilSinTapas);

    //Introducimos vertices a un perfil para que a partir de ellos e genere la figura
    //vector<_vertex3f> perfil; //Es declarado globlal para poder ser usado en draw_obdraw_objects()

    //Ojo, aquí se dan los perfiles por orden inverso a como se dibujarían. El primero dado es el de abajo y así hacia arriba. !!
    //perfil.push_back({0,-1,0});
    perfil.push_back({1,-1,0});
    perfil.push_back({2.5,0,0});
    perfil.push_back({1,1,0});
    //perfil.push_back({0,1,0});

    figuraPrueba.cargarPerfil(perfil);
    //figuraPrueba.revoluciona(REVOLUCIONES, GRADOS_INICIAL, GRADOS_FINAL);

    vectorFiguras.push_back(figuraPrueba);

    //Ahora mismo prueba sólo contiene el perfil de la figura

    //De la siguiente manera se carga el perfil una sola vez y en tiempo de ejecución con el control de las teclas + y -
    //puede variarse el número de revoluciones.

    //El perfil puede ser un fichero ply.
     // peon.cargarPerfil("perfil.ply");
     // peon.revoluciona(16, 0, 360);

    //Los peones de la ESCENA 2 de la PRÁCTICA 4

      //Primer peón con textura de madera:
      peonA.cargarPerfil("perfil.ply");
      peonA.revoluciona(32,0,360);
      peonA.generaCoordenadasTextura(32); /*En figuraRevolucionada.h*/

      //Segundo peón sin textura. Material: puramente difuso, sin brillos especulares, de color blanco.
      peonB.cargarPerfil("perfil.ply");
      peonB.revoluciona(16,0,360);

      //Tercer peón sin textura. Material: especular sin apenas reflectividad difusa, de color negro.
      peonC.cargarPerfil("perfil.ply");
      peonC.revoluciona(16,0,360);

    //La lata de la ESCENA 2 de la PRÁCTICA 4

      int numRevLata=32;
      cuerpoLata.cargarPerfil("lata-pcue.ply");
      cuerpoLata.revoluciona(numRevLata,0,360);
      cuerpoLata.generaCoordenadasTextura(numRevLata);

      culoLata.cargarPerfil("lata-pinf.ply");
      culoLata.revoluciona(numRevLata,0,360);
      //culoLata.generaCoordenadasTextura(numRevLata);

      bocaLata.cargarPerfil("lata-psup.ply");
      bocaLata.revoluciona(numRevLata,0,360);
      //bocaLata.generaCoordenadasTextura(numRevLata);






      //vectorFiguras.push_back(peon);

    //El perfil tb puede ser un vector de _vertex3f

    //figuraPerfilCompleto.cargarPerfil("perfilPeon.ply");





    //figuraPrueba.calculaNormalesCaras();
    //figuraPrueba.calculaBaricentrosCaras();



    //cout << prueba.numeroVertices();
    //cout << prueba.numeroCaras();
    //prueba.muestraCaras();
    //prueba.muestraVertices();


    //Añadimos tres puntos a nuestra figura triángulo
    triangulo.setVerticeManual(0.5,0,0);
    triangulo.setVerticeManual(0,0.5,0);
    triangulo.setVerticeManual(-0.5,0,0);


    // ######################## CUBO ################################################################

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
    /*Al hacer esta operación estamos diciéndole que la cara 1 está compuesta
    por los vértices 0 1 y 2.
    */
    //Cara delantera:
    cubo.setCaraManual(0,1,2);
    cubo.setCaraManual(0,2,3);

    //Cara derecha:
    cubo.setCaraManual(1,5,6);
    cubo.setCaraManual(1,6,2);

    //Cara trasera:
    cubo.setCaraManual(5,4,7);
    cubo.setCaraManual(5,7,6);

    //Cara izquierda:
    cubo.setCaraManual(4,0,3);
    cubo.setCaraManual(4,3,7);

    //Cara superior
    cubo.setCaraManual(3,2,6);
    cubo.setCaraManual(3,6,7);

    //Cara inferior
    cubo.setCaraManual(5,1,0);
    cubo.setCaraManual(5,0,4);

    cubo.calculaNormalesCaras();
    cubo.calculaNormalesVertices();












    // ########################## FIN CUBO ##############################################



    //EXAMEN P4 :

    figuraPerfilCompleto.cargarPerfil(perfilCompleto);
    figuraPerfilCompleto.revoluciona(4, 0, 360);
    figuraPerfilCompleto.generaCoordenadasTextura(4);

    //FIN EXAMEN P4

    figuraPerfilSinTapas.cargarPerfil(perfilSinTapas);
    figuraPerfilSinTapas.revoluciona(16, 0, 360);
    figuraPerfilSinTapas.generaCoordenadasTextura(16);

    // se llama a la inicialización de glut
    glutInit(&argc, argv);

    // se indica las caracteristicas que se desean para la visualización con OpenGL
    // Las posibilidades son:
    // GLUT_SIMPLE -> memoria de imagen simple
    // GLUT_DOUBLE -> memoria de imagen doble
    // GLUT_INDEX -> memoria de imagen con color indizado
    // GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
    // GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
    // GLUT_DEPTH -> memoria de profundidad o z-bufer
    // GLUT_STENCIL -> memoria de estarcido
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    // Posicion de la esquina inferior izquierdad de la ventana
    glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

    // Tamaño de la ventana (ancho y alto)
    glutInitWindowSize(UI_window_width,UI_window_height);

    // Llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
    // al bucle de eventos)
    glutCreateWindow("Practica 5");

    // asignación de la funcion llamada "dibujar" al evento de dibujo
    glutDisplayFunc(draw_scene);
    // asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
    glutReshapeFunc(change_window_size);
    // asignación de la funcion llamada "tecla_normal" al evento correspondiente
    glutKeyboardFunc(normal_keys);
    // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
    glutSpecialFunc(special_keys);



    //## ILUMINACIÓN ##//

    GLfloat new_model_ambient[]={0,0,0,1};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, new_model_ambient);
    /*Detección:
    Al habilitar sólo la componente difusa en la iluminación y tener una luz frente al objeto
    notamos que al girar el objeto y dejar el foco de luz detras del objeto el objeto sigue viéndose. Esto sucede porque
    por defecto OpenGL establece la componente difusa a 0.2 0.2 0.2. Por eso rectificamos esto para ver exactaente donde y como
    incide la luz.
    */


    //Los parámetros de la luz son los tres colores más el canal alfa.

    //const GLfloat luzAmbiente[]={1, 1, 1, 1.0};
    //const GLfloat luzDifusa[]={1, 1, 1, 1.0};
    //const GLfloat luzEspecular[]={0, 0, 0, 1.0};

/*
    //Aplicamos las tres componentes a la luz número 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);

    //Aplicamos las tres componentes a la luz número 1 (no tienen por qué ser las mismas)
    glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecular);
*/
    //Establezo el tipo de iluminación plano
    glShadeModel(GL_FLAT);

    //Rectificamos el valor por defecto de la luz ambiente:


    //Activamos la luz 0 (DERECHA FIJA)
  //  glEnable(GL_LIGHT0);

    //Activamos la luz 1 (SUPERIOR ROTATORIA)
   // glEnable(GL_LIGHT1);

    /*La operación de activación de iluminación general glEnable(GL_LIGHTING) y la posterior de desactivación glDisable(GL_LIGHTING)
    debe de hacerse sólo cuando se quiera dibujar un objeto al que queramos que se le aplique la iluminación. Así podremos tener
    los ejes sin iluminación (con su coloración normal) y los conos mientras que otro modelo como el beethoven sea aplicado por la
    ilumación.*/

    // ## FIN ILUMINACIÓN ## //





    // ## TEXTURAS [INICIALIZACIÓN]## //

    //cargarTextura("./text-lata-1.bmp");
    cargarTextura(texturaLata, "./text-lata-1.bmp");
    cargarTextura(texturaMadera, "./text-madera.bmp");
    cargarTextura(texturaIG, "./ig.bmp");

        /*
        cout << "Proceso de imagen" << endl;
        cout << "Proceso de imagen" << endl;
        //1ºExtraemos el formato del que es la imagen:
        FREE_IMAGE_FORMAT formatoImagen = FIF_UNKNOWN;
        formatoImagen=FreeImage_GetFileType("text-lata-1.jpg",0);
        FIBITMAP *dib(0);

        if(formatoImagen==FIF_UNKNOWN)
            cout << "Ha ocurrido un problema";

         // check that the plugin has reading capabilities ...
        if((formatoImagen != FIF_UNKNOWN) && FreeImage_FIFSupportsReading(formatoImagen)){
            // ok, let's load the file
            dib = FreeImage_Load(formatoImagen, "text-lata-1.bmp");

            cout << "todo bien" << endl;
        }

        //Obtenemos los datos de la imagen
        BYTE* bits = FreeImage_GetBits(dib); //Cargando los datos de la imgen
        unsigned int width = FreeImage_GetWidth(dib);
        unsigned int height = FreeImage_GetHeight(dib);

        if((bits != 0) && (width != 0) && (height != 0))
            cout << "La imagen mide " << width << " x " << height << endl;
        else{
            cout << "Ha ocurrido un error" << endl;
            }




        //La siguiente función nombra y crea un objeto de tipo textura para una imagen de textura
        glGenTextures(1, &identificadorImagen);
        glBindTexture(GL_TEXTURE_2D, identificadorImagen);


       glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
     //   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     //   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        // parametros de aplicacion de la textura
        //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

        glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &bits);

        */



    // ## FIN TEXTURAS ## //



    // funcion de inicialización
    initialize();


    /*Para controlar la cámara con el ratón es necesario hacer que los cambios de posición del ratón afecten a la posición de
    la cámara y en glut eso se hace indicando las funciones que queremos que procesen los eventos del ratón, antes de glutMainLoop*/
    /**Interesante de la práctica 5 */
    glutMouseFunc(controlRaton);
    //glutMotionFunc(controlMovimientoRaton);
    //glutMotionFunc(controlMovimientoRaton);
    /**-----------------------------*/


    // inicio del bucle de eventos
    glutIdleFunc(idle);



    glutMainLoop();
    return 0;
}

