//***************************************************************************************************************
//  figuraSolida.h
//
//  Clase que hereda todos los atributos y métodos de su padre figuraSimple.
//
//***************************************************************************************************************

#ifndef _FIGURASOLIDA
#define _FIGURASOLIDA

//Al heredar de figuraSimple necesita conocerla:
#include "figuraSimple.h"
//Al incluir figuraSimple.h estamos incluyendo todos los include de la primera.


//La clase figuraSolida hereda de figuraSimple
class figuraSolida : public figuraSimple {

    protected:

        //Las figuras solidas necesitan un vector de caras con el que darle la topología (conexión entre
        // vértices) al objeto.
        vector<_vertex3i> caras;

    public:

        //Función que devuelve el número de caras alojadas en el vector caras.
        int numeroCaras(){
            return caras.size();
        }
        //Función para introducir a mano las caras del modelo
        void setCaraManual(unsigned int verticeA, unsigned int verticeB, unsigned int verticeC){
            _vertex3i caraTemporal;
            caraTemporal.x=verticeA;
            caraTemporal.y=verticeB;
            caraTemporal.z=verticeC;
            caras.push_back(caraTemporal);
        };

        void eliminarUltimaCara(){
            caras.pop_back();
        }
        //Función que dibuja las caras ajustable a la sección y al modo de dibujado.
        void dibujarCaras(string seccion, string modo){

            //Usamos la directiva GL_TRIANGLES que necesita que se le pasen tres vectores.
            glBegin(GL_TRIANGLES);

                //Recorremos todas las caras para dibujar cada una.
                for(unsigned i=0; i<caras.size(); i++){

                    //Para dibujar al completo la figura (todas sus caras) entramos en esta sección:
                    if(seccion=="todo"){

                        //Si queremos que parezca un objeto sólido establecemos el mismo color para todas las caras.
                        if(modo=="solido")
                            //Establecemos el mismo color para todos los pasos del bucle, es decir, para todas las caras.
                            glColor3fv(GRIS_CLARO);

                        //Si queremos dibujar el objeto en modo ajedrez pintamos una cara de un color y otra de otro.
                        if(modo=="ajedrez"){
                            //Las caras impares de un color y las pares de otro.
                            if(i%2==0)
                                //Para las caras pares:
                                glColor3fv(GRIS_OSCURO);
                            else
                                //Para las caras impares:
                                glColor3fv(GRIS_CLARO);
                        }
                        /*Fin de la selección del color. Esto se hace para cada paso del bucle, después de seleccionar
                        el color con el que se va a dibujar la cara se pasa a dibujarla.*/

                        //  caras[0]._0  Primer vértice de la cara 0
                        glVertex3f(vertices[caras[i]._0].x, vertices[caras[i]._0].y ,vertices[caras[i]._0].z);
                        //  caras[0]._1  Segundo vértice de la cara 0
                        glVertex3f(vertices[caras[i]._1].x, vertices[caras[i]._1].y ,vertices[caras[i]._1].z);
                        //  caras[0]._2  Tercer vértice de la cara 0
                        glVertex3f(vertices[caras[i]._2].x, vertices[caras[i]._2].y ,vertices[caras[i]._2].z);
                    }//Fin de la sección TODO

                    //Si queremos visualizar sólo una parte del objeto general, no la vamos a usar más.
                    if(seccion=="solo y+" && modo=="especial"){

                        /*Para que una cara sea dibujada los tres vértices que la componen tendrán que tener sus
                        coordenadas x en la versión positiva del eje, para que así la cara entera pertenezca a esa
                        sección del eje. Esto es extrapolable a cualquier eje y sentido.
                        */

                        //Vamos a realizar la gestión del color para el examen:

                        //Comprobación para ver si la cara pertenece al lado positivo del eje Y
                        if( vertices[caras[i]._0].y>0 && vertices[caras[i]._1].y>0 && vertices[caras[i]._2].y>0 ){

                            //Comprobación para establecer el color de si

                            if(vertices[caras[i]._0].x>0 && vertices[caras[i]._1].x>0 && vertices[caras[i]._2].x>0 &&
                               vertices[caras[i]._0].z<0 && vertices[caras[i]._1].z<0 && vertices[caras[i]._2].z<0)
                               glColor3fv(AMARILLO);

                            else if(vertices[caras[i]._0].x<0 && vertices[caras[i]._1].x<0 && vertices[caras[i]._2].x<0 &&
                               vertices[caras[i]._0].z<0 && vertices[caras[i]._1].z<0 && vertices[caras[i]._2].z<0)
                               glColor3fv(VERDE);

                            else if(vertices[caras[i]._0].x<0 && vertices[caras[i]._1].x<0 && vertices[caras[i]._2].x<0 &&
                               vertices[caras[i]._0].z>0 && vertices[caras[i]._1].z>0 && vertices[caras[i]._2].z>0)
                               glColor3fv(AZUL);

                            else if(vertices[caras[i]._0].x>0 && vertices[caras[i]._1].x>0 && vertices[caras[i]._2].x>0 &&
                               vertices[caras[i]._0].z>0 && vertices[caras[i]._1].z>0 && vertices[caras[i]._2].z>0)
                               glColor3fv(ROJO);

                            else
                               glColor3fv(GRIS_OSCURO);

                            //  caras[0]._0  Primer vértice de la cara 0
                            glVertex3f(vertices[caras[i]._0].x, vertices[caras[i]._0].y ,vertices[caras[i]._0].z);
                            //  caras[0]._1  Segundo vértice de la cara 0
                            glVertex3f(vertices[caras[i]._1].x, vertices[caras[i]._1].y ,vertices[caras[i]._1].z);
                            //  caras[0]._2  Tercer vértice de la cara 0
                            glVertex3f(vertices[caras[i]._2].x, vertices[caras[i]._2].y ,vertices[caras[i]._2].z);
                        }
                    }
                    //Esta función con el modo ajedresz tampoco
                     if(seccion=="solo y+" && modo=="ajedrez"){

                        /*Para que una cara sea dibujada los tres vértices que la componen tendrán que tener sus
                        coordenadas x en la versión positiva del eje, para que así la cara entera pertenezca a esa
                        sección del eje. Esto es extrapolable a cualquier eje y sentido.
                        */


                        if(modo=="ajedrez"){
                            //Gestión del color de las caras si el modo es "ajedrez"
                            if(i%2==0)
                                //Para las caras pares:
                                glColor3fv(GRIS_OSCURO);
                            else
                                //Para las caras impares:
                                glColor3fv(GRIS_CLARO);
                        }


                        //Comprobación para ver si la cara pertenece al lado positivo del eje Y
                        if( vertices[caras[i]._0].y>0 && vertices[caras[i]._1].y>0 && vertices[caras[i]._2].y>0 ){

                            //  caras[0]._0  Primer vértice de la cara 0
                            glVertex3f(vertices[caras[i]._0].x, vertices[caras[i]._0].y ,vertices[caras[i]._0].z);
                            //  caras[0]._1  Segundo vértice de la cara 0
                            glVertex3f(vertices[caras[i]._1].x, vertices[caras[i]._1].y ,vertices[caras[i]._1].z);
                            //  caras[0]._2  Tercer vértice de la cara 0
                            glVertex3f(vertices[caras[i]._2].x, vertices[caras[i]._2].y ,vertices[caras[i]._2].z);
                        }

                    }
                }
            glEnd();
        }

        //Función que usando las caras dibuja las aristas y a la que también se le especifica sección.
        void dibujarAristas(string seccion){

            //Configuración del color (RGB [0-1] )
            glColor3fv(NEGRO);

            //Configuración del grosor de las lineas, por si queremos que se vean más gruesas.
            glLineWidth(0.5);

            /*Una cara está compuesta por tres vértices, que forman tres aristas entre ellos. Entonces mandaremos
            a dibujar a OpenGl la arista que conecta los vértices 0 y 1 de la cara, la que forman los vértices
            1 y 2 y la restante con los vértices 2 y de nuevo 0. Con eso la cara queda formada por tres aristas.
            Sólo tenemos que repetir esa acción con tantas caras como tengamos => bucle for.
            */

            if(seccion=="todo"){
                for(unsigned int i=0; i<caras.size(); i++){

                    //Dibujado de la arista que conecta el vértice 0 con el 1
                    glBegin(GL_LINES);
                        //Recordando que caras[0]._0 es: cara nº 0 vértice nº0
                        glVertex3f(vertices[caras[i]._0].x, vertices[caras[i]._0].y ,vertices[caras[i]._0].z);
                        glVertex3f(vertices[caras[i]._1].x, vertices[caras[i]._1].y ,vertices[caras[i]._1].z);
                    glEnd();

                    //Dibujado de la arista que conecta el vértice 1 con el vértice 2
                    glBegin(GL_LINES);
                        glVertex3f(vertices[caras[i]._1].x, vertices[caras[i]._1].y ,vertices[caras[i]._1].z);
                        glVertex3f(vertices[caras[i]._2].x, vertices[caras[i]._2].y ,vertices[caras[i]._2].z);
                    glEnd();

                    //Dibujado de la arita que conecta el vértice 2 con el vértice 0
                    glBegin(GL_LINES);
                        glVertex3f(vertices[caras[i]._2].x, vertices[caras[i]._2].y ,vertices[caras[i]._2].z);
                        glVertex3f(vertices[caras[i]._0].x, vertices[caras[i]._0].y ,vertices[caras[i]._0].z);
                    glEnd();
                }
            }

            /*Si especificamos "sólo x+" sólo deben dibujarse las aristas de la cara que estamos trabajando
            //que esten en la parte positiva del eje X. Es decir, que tengan los dos vértices en esa sección.
            //Si no los tienen no deben dibujarse. */


            if(seccion=="solo y+"){
                for(unsigned int i=0; i<caras.size(); i++){

                    glBegin(GL_LINES);
                        if(vertices[caras[i]._0].y>0 && vertices[caras[i]._1].y>0 ){
                            glVertex3f(vertices[caras[i]._0].x, vertices[caras[i]._0].y ,vertices[caras[i]._0].z);
                            glVertex3f(vertices[caras[i]._1].x, vertices[caras[i]._1].y ,vertices[caras[i]._1].z);
                        }
                    glEnd();

                    glBegin(GL_LINES);
                        if(vertices[caras[i]._1].y>0 && vertices[caras[i]._2].y>0 ){
                            glVertex3f(vertices[caras[i]._1].x, vertices[caras[i]._1].y ,vertices[caras[i]._1].z);
                            glVertex3f(vertices[caras[i]._2].x, vertices[caras[i]._2].y ,vertices[caras[i]._2].z);
                        }
                    glEnd();

                    glBegin(GL_LINES);
                        if(vertices[caras[i]._2].y>0 && vertices[caras[i]._0].y>0 ){
                            glVertex3f(vertices[caras[i]._2].x, vertices[caras[i]._2].y ,vertices[caras[i]._2].z);
                            glVertex3f(vertices[caras[i]._0].x, vertices[caras[i]._0].y ,vertices[caras[i]._0].z);
                        }
                    glEnd();
                }
            }

            //Restauración del grosor de lineas, recordamos que OpenGl es una máquina de estados que quedan constantes.
            glLineWidth(0.5);

        }


};

#endif
