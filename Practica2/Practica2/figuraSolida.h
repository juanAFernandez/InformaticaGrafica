//***************************************************************************************************************
//  figuraSolida.h
//
//  Clase que hereda todos los atributos y m�todos de su padre figuraSimple.
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

        //Las figuras solidas necesitan un vector de caras con el que darle la topolog�a (conexi�n entre
        // v�rtices) al objeto.
        vector<_vertex3i> caras;

    public:

        //Funci�n que devuelve el n�mero de caras alojadas en el vector caras.
        int numeroCaras(){
            return caras.size();
        }
        //Funci�n para introducir a mano las caras del modelo
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
        //Funci�n que dibuja las caras ajustable a la secci�n y al modo de dibujado.
        void dibujarCaras(string seccion, string modo){

            //Usamos la directiva GL_TRIANGLES que necesita que se le pasen tres vectores.
            glBegin(GL_TRIANGLES);
                /*Accedemos a los vectores usando como �ndices los enteros almacenados en el vector
                de caras teniendo en cuenta que dentro de este vector caras[0]._0 se refiere al primer
                vertice de la cara 0, caras[0]._1 al segundo v�rtice y caras[0]._2 al tercer v�rtice, con
                esta nomenclatura se hace m�s f�cil entender como se est� accediendo.
                */

                //En cada pasada del bucle for se dibuja una de las caras almacenadas.

                for(unsigned i=0; i<caras.size(); i++){

                    if(seccion=="todo"){

                        /*Para dibujar una cara se necesitan tres v�rtices y como nosotros guardamos en el vector de caras
                        los vertices de cada cara usamos los valores x, y y z de los vertices de cada vertice de la cara i.
                        */

                        if(modo=="solido")
                            glColor3fv(GRIS_CLARO);

                        if(modo=="ajedrez"){
                            //Gesti�n del color de las caras si el modo es "ajedrez"
                            if(i%2==0)
                                //Para las caras pares:
                                glColor3fv(GRIS_OSCURO);
                            else
                                //Para las caras impares:
                                glColor3fv(GRIS_CLARO);
                        }

                        if(modo=="caras"){
                            if(i<(caras.size()/2))
                                glColor3fv(VERDE);
                            else
                                glColor3fv(GRIS_OSCURO);

                        }



                        //  caras[0]._0  Primer v�rtice de la cara 0
                        glVertex3f(vertices[caras[i]._0].x, vertices[caras[i]._0].y ,vertices[caras[i]._0].z);
                        //  caras[0]._1  Segundo v�rtice de la cara 0
                        glVertex3f(vertices[caras[i]._1].x, vertices[caras[i]._1].y ,vertices[caras[i]._1].z);
                        //  caras[0]._2  Tercer v�rtice de la cara 0
                        glVertex3f(vertices[caras[i]._2].x, vertices[caras[i]._2].y ,vertices[caras[i]._2].z);


                    }

                    if(seccion=="solo y+" && modo=="especial"){

                        /*Para que una cara sea dibujada los tres v�rtices que la componen tendr�n que tener sus
                        coordenadas x en la versi�n positiva del eje, para que as� la cara entera pertenezca a esa
                        secci�n del eje. Esto es extrapolable a cualquier eje y sentido.
                        */

                        //Vamos a realizar la gesti�n del color para el examen:

                        //Comprobaci�n para ver si la cara pertenece al lado positivo del eje Y
                        if( vertices[caras[i]._0].y>0 && vertices[caras[i]._1].y>0 && vertices[caras[i]._2].y>0 ){

                            //Comprobaci�n para establecer el color de si

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

                            //  caras[0]._0  Primer v�rtice de la cara 0
                            glVertex3f(vertices[caras[i]._0].x, vertices[caras[i]._0].y ,vertices[caras[i]._0].z);
                            //  caras[0]._1  Segundo v�rtice de la cara 0
                            glVertex3f(vertices[caras[i]._1].x, vertices[caras[i]._1].y ,vertices[caras[i]._1].z);
                            //  caras[0]._2  Tercer v�rtice de la cara 0
                            glVertex3f(vertices[caras[i]._2].x, vertices[caras[i]._2].y ,vertices[caras[i]._2].z);
                        }
                    }

                     if(seccion=="solo y+" && modo=="ajedrez"){

                        /*Para que una cara sea dibujada los tres v�rtices que la componen tendr�n que tener sus
                        coordenadas x en la versi�n positiva del eje, para que as� la cara entera pertenezca a esa
                        secci�n del eje. Esto es extrapolable a cualquier eje y sentido.
                        */


                        if(modo=="ajedrez"){
                            //Gesti�n del color de las caras si el modo es "ajedrez"
                            if(i%2==0)
                                //Para las caras pares:
                                glColor3fv(GRIS_OSCURO);
                            else
                                //Para las caras impares:
                                glColor3fv(GRIS_CLARO);
                        }


                        //Comprobaci�n para ver si la cara pertenece al lado positivo del eje Y
                        if( vertices[caras[i]._0].y>0 && vertices[caras[i]._1].y>0 && vertices[caras[i]._2].y>0 ){

                            //  caras[0]._0  Primer v�rtice de la cara 0
                            glVertex3f(vertices[caras[i]._0].x, vertices[caras[i]._0].y ,vertices[caras[i]._0].z);
                            //  caras[0]._1  Segundo v�rtice de la cara 0
                            glVertex3f(vertices[caras[i]._1].x, vertices[caras[i]._1].y ,vertices[caras[i]._1].z);
                            //  caras[0]._2  Tercer v�rtice de la cara 0
                            glVertex3f(vertices[caras[i]._2].x, vertices[caras[i]._2].y ,vertices[caras[i]._2].z);
                        }

                    }
                }


            glEnd();


        }
        //Funci�n que usando las caras dibuja las aristas y a la que tambi�n se le especifica secci�n.
        void dibujarAristas(string seccion){

            //Configuraci�n del color (RGB [0-1] )
            glColor3f(0.1,0.6,0.1);

            //Configuraci�n del grosor de las lineas, por si queremos que se vean m�s gruesas.
            glLineWidth(0.5);

            /*Una cara est� compuesta por tres v�rtices, que forman tres aristas entre ellos. Entonces mandaremos
            a dibujar a OpenGl la arista que conecta los v�rtices 0 y 1 de la cara, la que forman los v�rtices
            1 y 2 y la restante con los v�rtices 2 y de nuevo 0. Con eso la cara queda formada por tres aristas.
            S�lo tenemos que repetir esa acci�n con tantas caras como tengamos => bucle for.
            */

            if(seccion=="todo"){
                for(unsigned int i=0; i<caras.size(); i++){

                    //Dibujado de la arista que conecta el v�rtice 0 con el 1
                    glBegin(GL_LINES);
                        //Recordando que caras[0]._0 es: cara n� 0 v�rtice n�0
                        glVertex3f(vertices[caras[i]._0].x, vertices[caras[i]._0].y ,vertices[caras[i]._0].z);
                        glVertex3f(vertices[caras[i]._1].x, vertices[caras[i]._1].y ,vertices[caras[i]._1].z);
                    glEnd();

                    //Dibujado de la arista que conecta el v�rtice 1 con el v�rtice 2
                    glBegin(GL_LINES);
                        glVertex3f(vertices[caras[i]._1].x, vertices[caras[i]._1].y ,vertices[caras[i]._1].z);
                        glVertex3f(vertices[caras[i]._2].x, vertices[caras[i]._2].y ,vertices[caras[i]._2].z);
                    glEnd();

                    //Dibujado de la arita que conecta el v�rtice 2 con el v�rtice 0
                    glBegin(GL_LINES);
                        glVertex3f(vertices[caras[i]._2].x, vertices[caras[i]._2].y ,vertices[caras[i]._2].z);
                        glVertex3f(vertices[caras[i]._0].x, vertices[caras[i]._0].y ,vertices[caras[i]._0].z);
                    glEnd();
                }
            }

            /*Si especificamos "s�lo x+" s�lo deben dibujarse las aristas de la cara que estamos trabajando
            //que esten en la parte positiva del eje X. Es decir, que tengan los dos v�rtices en esa secci�n.
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

            //Restauraci�n del grosor de lineas, recordamos que OpenGl es una m�quina de estados que quedan constantes.
            glLineWidth(0.5);

        }


};

#endif
