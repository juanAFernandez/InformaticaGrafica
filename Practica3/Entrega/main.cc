//**************************************************************************
// Práctica 3
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

/*
    Modificaciones:
        -Se ha mejorado la forma de visualizar los objetos, colores, etc.
        -La función de revolución la usaremos para construir objtemos con más detalle a partir de perfiles simples.


*/

#include "stdlib.h"
#include "stdio.h"
#include <windows.h>
#include <GL/glut.h>
#include <ctype.h>
#include <iostream>

#include "figuraCargada.h"

//También incluimos figuraRevolucionada.h (epicentro de esta práctica)
#include "figuraRevolucionada.h"

#include "variablesControl.h"

#include "rover.h"
#include "suelo.h"
#include "parametrosRover.h"


//Sólo para pruebas, eliminar luego:
//#include "Robot.h"

       // Robot brazo;

        rover curiosity;
        suelo base(20);

        figuraRevolucionada cilindro;
        figuraRevolucionada semicilindro;

        boolean animacion=true;
        int contadorAnimacion=0;


//###############d

/*Sección de definición de figuras (el modelado). Donde esta se realiza tan sólo una vez dejando clara la
diferencia entre el modelado (definición de sus puntos y configuración de sus aristas) y la parte de la visualización
de la que se encargará un función independiente.
*/
    //Declaramos algunas figuras básicas.
    figuraSimple triangulo("triangulo");
    figuraSolida cubo("cubo");




    //Correspondiente a la práctica 2 ############

    //Introducimos vertices a un perfil para que a partir de ellos e genere la figura
    vector<_vertex3f> perfil;

    //La figura del peon (cuyo perfil será cargado desde un .ply)
    figuraRevolucionada peon("peon");

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


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects()
{

    curiosity.dibujarRover();
    base.dibujarSuelo();


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


//***************************************************************************
// Funcion llamada cuando se pulsa sobre una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y){

//Para salir del programa:
if(toupper(Tecla1)=='Q') exit(0);

/*Cada vez que se presiona una tecla se modifica algunad de las variables globales
y se llama a draw_scene(); que llama a draw_objects(); donde segun el estado
de esas variables se dibujará una cosa u otra.
*/



if (toupper(Tecla1)=='1') {curiosity.brazo.girarPositivo("brazo1");curiosity.brazo.girarNegativo("brazo2"); animacion=false; draw_scene();};
if (toupper(Tecla1)=='2') {curiosity.brazo.girarNegativo("brazo1");curiosity.brazo.girarPositivo("brazo2");draw_scene();};
if(toupper(Tecla1)=='3'){curiosity.brazo.girarPositivo("brazo2");draw_scene();}
if(toupper(Tecla1)=='4'){curiosity.brazo.girarNegativo("brazo2");draw_scene();}
if(toupper(Tecla1)=='5'){curiosity.brazo.girarPositivo("brazo3"); draw_scene();}
if(toupper(Tecla1)=='6'){curiosity.brazo.girarNegativo("brazo3"); draw_scene();}
if(toupper(Tecla1)=='7'){curiosity.brazo.girarBasePositivo(); draw_scene();}
if(toupper(Tecla1)=='8'){curiosity.brazo.girarBaseNegativo(); draw_scene();}


//Ahora seleccionamos el modo, VERTICES, ALAMBRE O SÓLID y el especial de 4 colores del examen.
//Para dibujar el modelo sólo los VERTICES.
if(toupper(Tecla1)=='V'){MODO=1; draw_scene();}

//Para dibujar el modelo sólo con ARISTAS.
if(toupper(Tecla1)=='A'){MODO=2; draw_scene();}

//Para dibujar el modelo sólo SÓLIDO
if(toupper(Tecla1)=='S'){MODO=3; draw_scene();}



//Para el control del número de revoluciones ------------------------------------------------

//Pulsar la tecla + aumenta el número y vuelve a dibujar
if(Tecla1=='+'){
    //###Aumentamos el número de revoluciones:
    REVOLUCIONES++;

        //Eliminamos el contenido de vertices y caras ya que hay que generarlos de nuevo:
        for(int i=0; i<NUM_FIGURAS; i++)
            vectorFiguras[i].vaciaFigura();

        //Volvemos a realizar la revolución en todas las figuras:
        for(int i=0; i<NUM_FIGURAS; i++)
            vectorFiguras[i].revoluciona(REVOLUCIONES, GRADOS_INICIAL, GRADOS_FINAL);

        //Llamamos a dibujar escena donde se decide que y como dibujar
        draw_scene();
}
//Control de parámetros del rover
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
//Control de parámetros del rover
if(toupper(Tecla1)=='G'){
    //###Aumentamos el número de revoluciones:
    //GRADOS_RUEDA_DERECHA--;
    //GRADOS_RUEDA_IZQUIERDA--;
    //Llamamos a dibujar escena donde se decide que y como dibujar

    curiosity.desplazaAtras();

    draw_scene();
}
//Control de parámetros del rover
if(toupper(Tecla1)=='H'){
    //###Aumentamos el número de revoluciones:
 //   GRADOS_GIRO_ROVER--;

    curiosity.giraDerecha();

    //Llamamos a dibujar escena donde se decide que y como dibujar
    draw_scene();
}
//Control de parámetros del rover
if(toupper(Tecla1)=='F'){
    //###Aumentamos el número de revoluciones:
  //  GRADOS_GIRO_ROVER++;
    //Llamamos a dibujar escena donde se decide que y como dibujar

    curiosity.giraIzquierda();

    draw_scene();
}

//Pulsar la tecla - reduce  el número y vuelve a dibujar
if(Tecla1=='-'){
    //###Disminuimos el número de revoluciones:
    if(REVOLUCIONES>3){ //No permitiremos realizar el proceso con menos de tres revoluciones.
        REVOLUCIONES--;

        //Eliminamos el contenido de vertices y caras ya que hay que generarlos de nuevo:
        for(int i=0; i<NUM_FIGURAS; i++)
            vectorFiguras[i].vaciaFigura();

        //Volvemos a realizar la revolución en todas las figuras:
        for(int i=0; i<NUM_FIGURAS; i++)
            vectorFiguras[i].revoluciona(REVOLUCIONES, GRADOS_INICIAL, GRADOS_FINAL);

        //Llamamos a dibujar escena donde se decide que y como dibujar
        draw_scene();
    }
}

//Pulsar la tecla * aumenta los grados de revolución hasta 360.0 de máximo
if(Tecla1=='*'){

    //if(GRADOS<=360.0){ //No permitiremos subir más de 360 grados
      //  GRADOS++;

        //Eliminamos el contenido de vertices y caras ya que hay que generarlos de nuevo:
        for(int i=0; i<NUM_FIGURAS; i++)
            vectorFiguras[i].vaciaFigura();

        //Volvemos a realizar la revolución en todas las figuras:
        for(int i=0; i<NUM_FIGURAS; i++)
            vectorFiguras[i].revoluciona(REVOLUCIONES, GRADOS_INICIAL, GRADOS_FINAL);

        //Llamamos a dibujar escena donde se decide que y como dibujar
        draw_scene();
    //}
}

//Pulsar la tecla _ reduce los grados de revolución hasta 0.0 de mínimo
if(Tecla1=='_'){

   // if(GRADOS>=0.0){ //No permitiremos bajar de 0 grados.
     //   GRADOS--;

        //Eliminamos el contenido de vertices y caras ya que hay que generarlos de nuevo:
        for(int i=0; i<NUM_FIGURAS; i++)
            vectorFiguras[i].vaciaFigura();

        //Volvemos a realizar la revolución en todas las figuras:
        for(int i=0; i<NUM_FIGURAS; i++)
            vectorFiguras[i].revoluciona(REVOLUCIONES, GRADOS_INICIAL, GRADOS_FINAL);

        //Llamamos a dibujar escena donde se decide que y como dibujar
        draw_scene();
    //}
}

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
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;
         break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	}
glutPostRedisplay();
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
Observer_distance=150*Front_plane;
Observer_angle_x=40;
Observer_angle_y=-40;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
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


        glutPostRedisplay();
        cout << "Animacion paso " << contadorAnimacion << endl;
        contadorAnimacion++;
        if(contadorAnimacion==70)
            contadorAnimacion=0;

}

}




int main(int argc, char **argv)
{



    //Definimos los perfiles para el examen dándoles vértices:

        /*
           Hubiera sido interesante tener los ficheros en ficheros .ply pero windows se niega a leer ficheros que
           no sean bajados de la plataforma, parece que su codificación al guardar la información hace que no puedan
           abrirse y para lo que se va a conseguir, se ha optado por esta solución.
        */




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


    //Inicializamos las figuras del tipo "figuraRevolucionada" con estos perfiles y les damos la revolución general mínima:


        //Para pruebas:
        /*
            cilindro.cargarPerfil(perfilCompleto);
            cilindro.revoluciona(8,0,180);

            semicilindro.cargarPerfil(perfilCompleto);
            semicilindro.revoluciona(8,0,360);

        */
        //Fin de pruebas


        figuraPerfilCompleto.cargarPerfil(perfilCompleto);
        figuraPerfilCompleto.revoluciona(REVOLUCIONES, GRADOS_INICIAL, GRADOS_FINAL);
        figuraPerfilCompleto.muestraVertices();


        figuraPerfilParcialSinTapaAbajo.cargarPerfil(perfilParcialSinTapaAbajo);
        //figuraPerfilParcialSinTapaAbajo.revoluciona(REVOLUCIONES,GRADOS_INICIAL, GRADOS_FINAL);

        figuraPerfilParcialSinTapaArriba.cargarPerfil(perfilParcialSinTapaArriba);
        //figuraPerfilParcialSinTapaArriba.revoluciona(REVOLUCIONES, GRADOS_INICIAL, GRADOS_FINAL);

        figuraPerfilSinTapas.cargarPerfil(perfilSinTapas);
        //figuraPerfilSinTapas.revoluciona(REVOLUCIONES, GRADOS_INICIAL, GRADOS_FINAL);

        //Después de inicializarlas las meto en un vector para poder trabajar con ellas mejor.

        vectorFiguras.push_back(figuraPerfilCompleto);
        vectorFiguras.push_back(figuraPerfilParcialSinTapaAbajo);
        vectorFiguras.push_back(figuraPerfilParcialSinTapaArriba);
        vectorFiguras.push_back(figuraPerfilSinTapas);

    //Introducimos vertices a un perfil para que a partir de ellos e genere la figura
    //vector<_vertex3f> perfil; //Es declarado globlal para poder ser usado en draw_objects()

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
      peon.cargarPerfil("perfil.ply");
     // peon.revoluciona(REVOLUCIONES, GRADOS_INICIAL, GRADOS_FINAL);

      vectorFiguras.push_back(peon);

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
    cubo.setCaraManual(0,1,2);
    //Seguimos definiendo el resto de las caras del cubo:
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


    // ########################## FIN CUBO ##############################################



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

    // posicion de la esquina inferior izquierdad de la ventana
    glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

    // tamaño de la ventana (ancho y alto)
    glutInitWindowSize(UI_window_width,UI_window_height);

    // llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
    // al bucle de eventos)
    glutCreateWindow("Practica 3");

    // asignación de la funcion llamada "dibujar" al evento de dibujo
    glutDisplayFunc(draw_scene);
    // asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
    glutReshapeFunc(change_window_size);
    // asignación de la funcion llamada "tecla_normal" al evento correspondiente
    glutKeyboardFunc(normal_keys);
    // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
    glutSpecialFunc(special_keys);

    // funcion de inicialización
    initialize();

    // inicio del bucle de eventos
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
