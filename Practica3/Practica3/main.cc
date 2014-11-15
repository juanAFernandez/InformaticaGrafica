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

//###############d

/*Sección de definición de figuras (el modelado). Donde esta se realiza tan sólo una vez dejando clara la
diferencia entre el modelado (definición de sus puntos y configuración de sus aristas) y la parte de la visualización
de la que se encargará un función independiente.
*/
    //Declaramos algunas figuras básicas.
    figuraSimple triangulo;
    figuraSolida cubo;

    //### Varialbes de Control de Visualización

        //Declaramos una variable para controlar el modelo que se visualiza.
        int FIGURA=1; //Por defecto seleccionamos la primera.
        //Otra para controlar el modo de visualización: VERTICES, ALAMBRE y SÓLIDO
        int MODO=0;
        //Para controlar el número de revoluciones en las figuras de este tipo
        int REVOLUCIONES=7;
        //Para algunos bucles que limpian el código:
        int NUM_FIGURAS=1;
        //Grados de revolución:
//        float GRADOS=360.0;
        //Grados de sección:
        float GRADOS_INICIAL=90.0;
        float GRADOS_FINAL=180.0;

    //### Fin de variable de control de Visualización


    //Correspondiente a la práctica 2 ############

    //Introducimos vertices a un perfil para que a partir de ellos e genere la figura
    vector<_vertex3f> perfil;

    //La figura del peon (cuyo perfil será cargado desde un .ply)
    figuraRevolucionada peon;

    //Una figura extra con la que probar cosas.
    figuraRevolucionada figuraPrueba;

    //Perfiles simples para el examen:
    vector<_vertex3f> perfilCompleto;
    vector<_vertex3f> perfilParcialSinTapaArriba;
    vector<_vertex3f> perfilParcialSinTapaAbajo;
    vector<_vertex3f> perfilSinTapas;

    //Figuras para cargar y revolucionar los perfiles simples:

    vector <figuraRevolucionada> vectorFiguras;

    figuraRevolucionada figuraPerfilCompleto;
    figuraRevolucionada figuraPerfilParcialSinTapaArriba;
    figuraRevolucionada figuraPerfilParcialSinTapaAbajo;
    figuraRevolucionada figuraPerfilSinTapas;


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
    /*Aquí mandaremos a dibujar todos las figuras que hayamos declarado
    y definido al inicio del .cc para que al ser globales puedan ser accedidos
    por todas las funciones declaradas tras ellos.
    */

    /*
    figuraPrueba.dibujarVertices("todo");
    figuraPrueba.dibujarCaras("todo","caras");
    figuraPrueba.dibujarAristas("todo");
    */
    //Llamadas a algunas figuras básicas:

    //triangulo.dibujarVertices();
    //cubo.dibujarVertices();
    //cubo.dibujarCaras("solido");
    //cubo.dibujarAristas();


    /*A través de la variable global FIGURA controlamos la figura a visualizar mientras
    que con la variable también global MODO contolamos la forma de visualización, sólo vertices
    aristas o módo sólido. Dentro de cada función puede llamarse de una forma u otra, así puede llamarse a
    dibujar vértices sólo en la sección positiva del eje X. Para conocer más ver la definición de las funciones
    en el figura.h
    */

    if(false){
    cout << "NORMALES DIABOLICAS" << endl;


    _vertex3f a; a.x=1; a.y=0; a.z=0;
    _vertex3f b; b.x=0; b.y=1; b.z=0;
    _vertex3f c; c.x=0.5; c.y=0.5; c.z=1;

        glColor3fv(NEGRO);
    glPointSize(5);
    glBegin(GL_POINTS);
        glVertex3f(a.x, a.y, a.z);
        glVertex3f(b.x, b.y, b.z);
        glVertex3f(c.x, c.y, c.z);
    glEnd();

    glBegin(GL_LINES);
        glVertex3f(a.x,a.y,a.z);
        glVertex3f(b.x,b.y,b.z);
    glEnd();

    glBegin(GL_LINES);
        glVertex3f(a.x,a.y,a.z);
        glVertex3f(c.x,c.y,c.z);
    glEnd();

    glBegin(GL_LINES);
        glVertex3f(c.x,c.y,c.z);
        glVertex3f(b.x,b.y,b.z);
    glEnd();


    _vertex3f ab;
    _vertex3f ac;

    ab.x=b.x-a.x; ab.y=b.y-a.y; ab.z=b.z-a.z;
    cout << "ab" << ab.x << ab.y << ab.z << endl;
    ac.x=c.x-a.x; ac.y=c.y-a.y; ac.z=c.z-a.z;
    cout << "ac" << ac.x << ac.y << ac.z << endl;


    //Producto vectorial:
    _vertex3f n;
    n.x=(ab.y*ac.z)-(ab.z*ac.y);
    n.y=(ab.z*ac.x)-(ab.x*ac.z);
    n.z=(ab.x*ac.y)-(ab.y*ac.x);

    cout << "n" << n.x << n.y << n.z << endl;
    n.normalize();

    _vertex3f baric;

    baric.x=((a.x+b.x+c.x)/3);
    baric.y=((a.y+b.y+c.y)/3);
    baric.z=((a.z+b.z+c.z)/3);

    glBegin(GL_POINTS);
        glVertex3f(baric.x, baric.y, baric.z);
    glEnd();

    glBegin(GL_LINES);
        glVertex3f(baric.x,baric.y,baric.z);
        glVertex3f(baric.x+n.x, baric.y+n.y, baric.z+n.z);
    glEnd();



    cout << "FIN" << endl;
    }


    if(true){
    //Dibujamos la figura FIGURA en el modo MODO que tengamos seleciconado

        //Sólo vértices
        if(MODO==1)
            vectorFiguras[FIGURA-1].dibujarVertices("todo");
        //Sólo aristas
        if(MODO==2)
            vectorFiguras[FIGURA-1].dibujarAristas("todo");
        //Modo sólido
        if(MODO==3)
            vectorFiguras[FIGURA-1].dibujarCaras("todo","solido");
        //Modo sólido especial: vertices + aristas + caras + representación de normales.
        if(MODO==4){
            vectorFiguras[FIGURA-1].dibujarVertices("todo");
            vectorFiguras[FIGURA-1].dibujarAristas("todo");
            vectorFiguras[FIGURA-1].dibujarCaras("todo","ajedrez");
            //vectorFiguras[FIGURA-1].dibujaBaricentros();
            //vectorFiguras[FIGURA-1].dibujarNormales();
            //vectorFiguras[FIGURA-1].dibujarNormalesVertices();
        }
    }



    /*
    switch(FIGURA){

        //Si FIGURA==1 dibujamos la figura 1 según el modo que queramos:
        case 1:
            //Sólo vertices
            if(MODO==1)
                figuraPerfilCompleto.dibujarVertices("todo");
            //Sólo aristas
            if(MODO==2)
                figuraPerfilCompleto.dibujarAristas("todo");
            //Módo sólido
            if(MODO==3)
                figuraPerfilCompleto.dibujarCaras("todo", "ajedrez");
            //Modo detalle: vertices + aristas + caras + representación de normales.
            if(MODO==4){
                figuraPerfilCompleto.dibujarVertices("todo");
                figuraPerfilCompleto.dibujarCaras("todo","caras");
                figuraPerfilCompleto.dibujarAristas("todo");
                //figuraPrueba.dibujarNormales();
                //figuraPrueba.dibujaBaricentros();

            }
            break;

        //Perfil del peón
        case 2:
           if(MODO==1) //Dibujar vértices
                peon.dibujarVertices("todo");
            if(MODO==2) //Dibujar aristas
                peon.dibujarAristas("todo");
            if(MODO==3) //Dibujar sólido
                peon.dibujarCaras("solo y+","ajedrez");
            if(MODO==4){ //Dibujar mezcla
                peon.dibujarVertices("todo");
                peon.dibujarCaras("todo","caras");
                peon.dibujarAristas("todo");
            }
            break;



    }; */


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

/*Para la práctica dos vamos a tener 6 figuras. Las cuatro a partir de la revolución de los
cuatro perfiles de examen, una quinta con la que nosostros hacemos pruebas y como sexta y última
el peón cargado desde el fichero .ply*/

//Para dibujar la figura 1 pulsamos la techa 1
if(toupper(Tecla1)=='1'){FIGURA=1; draw_scene();}

//Para dibujar la figura 2 pulsamos la techa 2
if(toupper(Tecla1)=='2'){FIGURA=2; draw_scene();}

//Para dibujar la figura 3 pulsamos la techa 3
if(toupper(Tecla1)=='3'){FIGURA=3; draw_scene();}

//Para dibujar la figura 4 pulsamos la techa 4
if(toupper(Tecla1)=='4'){FIGURA=4; draw_scene();}

//Para dibujar la figura 5 pulsamos la techa 5
if(toupper(Tecla1)=='5'){FIGURA=5; draw_scene();}

//Para dibujar la figura 6 pulsamos la techa 6
if(toupper(Tecla1)=='6'){FIGURA=6; draw_scene();}


//Ahora seleccionamos el modo, VERTICES, ALAMBRE O SÓLID y el especial de 4 colores del examen.

//Para dibujar el modelo sólo los VERTICES.
if(toupper(Tecla1)=='V'){MODO=1; draw_scene();}

//Para dibujar el modelo sólo con ARISTAS.
if(toupper(Tecla1)=='A'){MODO=2; draw_scene();}

//Para dibujar el modelo sólo SÓLIDO
if(toupper(Tecla1)=='S'){MODO=3; draw_scene();}

//Para dibujar el modelo con colores especiales de examen
if(toupper(Tecla1)=='D'){MODO=4; draw_scene();}

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
	case GLUT_KEY_UP:Observer_angle_x--;break;
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
Observer_distance=12*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

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

        figuraPerfilCompleto.cargarPerfil(perfilCompleto);
        figuraPerfilCompleto.revoluciona(REVOLUCIONES, GRADOS_INICIAL, GRADOS_FINAL);

        figuraPerfilParcialSinTapaAbajo.cargarPerfil(perfilParcialSinTapaAbajo);
        figuraPerfilParcialSinTapaAbajo.revoluciona(REVOLUCIONES,GRADOS_INICIAL, GRADOS_FINAL);

        figuraPerfilParcialSinTapaArriba.cargarPerfil(perfilParcialSinTapaArriba);
        figuraPerfilParcialSinTapaArriba.revoluciona(REVOLUCIONES, GRADOS_INICIAL, GRADOS_FINAL);

        figuraPerfilSinTapas.cargarPerfil(perfilSinTapas);
        figuraPerfilSinTapas.revoluciona(REVOLUCIONES, GRADOS_INICIAL, GRADOS_FINAL);

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
    figuraPrueba.revoluciona(REVOLUCIONES, GRADOS_INICIAL, GRADOS_FINAL);

    vectorFiguras.push_back(figuraPrueba);

    //Ahora mismo prueba sólo contiene el perfil de la figura

    //De la siguiente manera se carga el perfil una sola vez y en tiempo de ejecución con el control de las teclas + y -
    //puede variarse el número de revoluciones.

    //El perfil puede ser un fichero ply.
      peon.cargarPerfil("perfil.ply");
      peon.revoluciona(REVOLUCIONES, GRADOS_INICIAL, GRADOS_FINAL);

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
    glutMainLoop();
    return 0;
}
