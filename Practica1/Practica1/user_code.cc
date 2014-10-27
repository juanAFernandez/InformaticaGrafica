//**************************************************************************
// Codigo del usuario
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#include "user_code.h"




//**************************************************************************
// Funcion para dibujar los vertices de un cubo unidad
//***************************************************************************
void draw_cube()
{
    GLfloat Vertices[8][3]= {{-0.5,-0.5,0.5},{0.5,-0.5,0.5},{0.5,0.5,0.5},{-0.5,0.5,0.5},{-0.5,-0.5,-0.5},{0.5,-0.5,-0.5},{0.5,0.5,-0.5},{-0.5,0.5,-0.5}};

    glColor3f(0,1,0);
    glPointSize(4);

    glBegin(GL_POINTS);
    for (unsigned i=0;i<8;i++){
        glVertex3fv((GLfloat *) &Vertices[i]);
        }
    glEnd();
}

//**************************************************************************
//Funci�n para dibujar los vertices de un tri�ngulo
//**************************************************************************

void draw_triangulo(){

    //Como hemos definido un objeto del tipo figura que es unt tri�ngulo y que puede ser llamado como triangulo.dibujarVertices()
    //se ha optado por eliminar el c�dio de esta funci�n.

}


//**************************************************************************
// Funcion para dibujar vertices
//***************************************************************************
void draw_vertices(figura figuraOriginal){


}

/*
void draw_vertices(vector<float> &Vertices)
{
}
*/
