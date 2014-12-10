#include "figuraSimple.h"

figuraSimple::figuraSimple(string nuevoNombre){
    nombreFigura=nombreFigura;
}

void figuraSimple::setVerticeManual(GLfloat x, GLfloat y, GLfloat z){
    _vertex3f verticeTemporal;
    verticeTemporal.x=x;
    verticeTemporal.y=y;
    verticeTemporal.z=z;
    /*Podr�amos usar push_back de "vector" de la STL pero cada vez que llena el vector dobla su tama�o porque
    se ha demostrado que de media es la necesitada que se suele tener, en nuestro caso no y puede hacernos
    desperdiciar mucha memoria.
    */
    //Vamos a usar push_back mientras descrubrimos otra forma de hacerlo.
    vertices.push_back(verticeTemporal);
};

int figuraSimple::numeroVertices(){
    return vertices.size();
};

void figuraSimple::dibujarVertices(string seccion){



            //Establecemos el color de los v�rtices
            glColor3fv(NEGRO);
            //Establecemos el grosor de los v�rtices (al dibujarlos)
            glPointSize(5);

            //Si el parametro es "todo" se dibujan todos los vertices del modelo.
            if(seccion=="todo"){
                glBegin(GL_POINTS);
                    for(unsigned int i=0; i<vertices.size(); i++)
                        glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
                glEnd();
            }

            //Con "solo x+" s�lo se dibujan los v�rtices se situan en la parte posivita del eje X
            if(seccion=="solo x+"){
                glBegin(GL_POINTS);
                    for(unsigned int i=0; i<vertices.size(); i++)
                        //Comprobaci�n de la posici�n respecto al eje X de los v�rtices.
                        if(vertices[i].x>0)
                        glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
                glEnd();
            }

            //Con "solo x-" s�lo se dibujan los v�rtices se situan en la parte negativa del eje X
            if(seccion=="solo x-"){
                glBegin(GL_POINTS);
                    for(unsigned int i=0; i<vertices.size(); i++)
                        //Comprobaci�n de la posici�n respecto al eje X de los v�rtices.
                        if(vertices[i].x<0)
                        glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
                glEnd();
            }

            //Con "solo y+" s�lo se dibujan los v�rtices se situan en la parte posivita del eje Y
            if(seccion=="solo y+"){
                glBegin(GL_POINTS);
                    for(unsigned int i=0; i<vertices.size(); i++)
                        //Comprobaci�n de la posici�n respecto al eje Y de los v�rtices.
                        if(vertices[i].y>0)
                        glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
                glEnd();
            }

            //Con "solo y-" s�lo se dibujan los v�rtices se situan en la parte negativa del eje Y
            if(seccion=="solo y-"){
                glBegin(GL_POINTS);
                    for(unsigned int i=0; i<vertices.size(); i++)
                        //Comprobaci�n de la posici�n respecto al eje Y de los v�rtices.
                        if(vertices[i].y<0)
                        glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
                glEnd();
            }

            //Con "solo z+" s�lo se dibujan los v�rtices se situan en la parte posivita del eje Z
            if(seccion=="solo z+"){
                glBegin(GL_POINTS);
                    for(unsigned int i=0; i<vertices.size(); i++)
                        //Comprobaci�n de la posici�n respecto al eje Z de los v�rtices.
                        if(vertices[i].z>0)
                        glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
                glEnd();
            }

            //Con "solo z-" s�lo se dibujan los v�rtices se situan en la parte negativa del eje Z
            if(seccion=="solo z-"){
                glBegin(GL_POINTS);
                    for(unsigned int i=0; i<vertices.size(); i++)
                        //Comprobaci�n de la posici�n respecto al eje Z de los v�rtices.
                        if(vertices[i].z<0)
                        glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
                glEnd();
            }


};

void figuraSimple::muestraVertices(){
    cout << "Vector de vertices de la figura " << nombreFigura << ": " << endl;
    for(int i=0; i<vertices.size(); i++){
        cout << "Vertice n." << i;
        cout << " [" << vertices[i].x <<" , "<< vertices[i].y << " , "<< vertices[i].z << "]" << endl;
    }
}

