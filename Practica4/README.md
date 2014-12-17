#Práctica 4 Iluminación y texturas.
- - - 

###Iluminación

Para conseguir la ilumación necesitamos tener las normales de todos los modelos. Esto lo tenemos desde que en la práctica anterior conseguimos generar las normales para cada cara y para cada vertice. Esto lo usaremos para conseguir dos tipos de iluminación, la **plana** y la suave o de **Gourach**.

Para conseguir tener la ilumación debemos de tener una luz activa y procesar las caras con las normales.

    //Definimos la posición de la luz de formal local:
    const GLfloat posicionLuzLocal[]={1.0, 1.0, 1.0, 1.0};

    //Definimos una luz en el infinito:
    const GLfloat posicionLuzInfinito[]={1.0, 1.0, 1.0, 0.0};

    //Establezo el tipo de iluminación plano
    glShadeModel(GL_FLAT);

    //Establezco la posición de la luz 0
    glLightfv(GL_LIGHT0, GL_POSITION, posicionLuz);

    //Activamos la luz 0
    glEnable(GL_LIGHT0);

    //Activamos la iluminación definida en OpenGL
    glEnable(GL_LIGHTING);
    


Necesitamos una función que asocie una normal por cara, para el suavizado PLANO:

	void figuraSolida::dibujarCarasIluminacionPlana(const GLfloat color[]){

            //En el tipo de iluminación con Suavizado Plano usamos una normal por cara.

            //Usamos la directiva GL_TRIANGLES que necesita que se le pasen tres vectores.
            glBegin(GL_TRIANGLES);

                //glColor3fv(color);
                //Recorremos todas las caras para dibujar cada una.
                for(unsigned i=0; i<caras.size(); i++){
                    glNormal3f(normales[i].x, normales[i].y, normales[i].z);
                    glVertex3f(vertices[caras[i]._0].x, vertices[caras[i]._0].y ,vertices[caras[i]._0].z);
                    glVertex3f(vertices[caras[i]._1].x, vertices[caras[i]._1].y ,vertices[caras[i]._1].z);
                    glVertex3f(vertices[caras[i]._2].x, vertices[caras[i]._2].y ,vertices[caras[i]._2].z);
                }
            glEnd();
	}
    
    
