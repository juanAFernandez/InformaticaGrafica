#include "display.h"


Display::Display(char *_projectName)
{
	frame = time = timebase = 0;
	sprintf(msj, "Frames per second: 0.0");
	projectName = _projectName;
}

Display::~Display(void){}

void Display::displayText(char *text, float x, float y, int width, int height, float R, float G, float B, void* font){
	char *c;

	// deshabilito la luz, textura y buffer de profundidad
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);

	// seteo el color de la letra
	glColor3f(R, G, B);

	// para cambiar la matriz de proyeccion que tendra que ser ortho ahora
	glMatrixMode(GL_PROJECTION);
	// salvo la matriz de proyeccion actual
	glPushMatrix();
	// reseto la matriz
	glLoadIdentity();
	// coloco la matriz de proyeccion ortogonal
//	gluOrtho2D(0, width, 0, height);
	// invierto el eje de las y y coloco abajo +y
//	glScalef(1.0f, -1.0f, 1.0f);
	// muevo el origen de la esquina izquierda inferior a la esquina izquierda superior
	glTranslatef(0.0f, -height, 0.0f);

	// guardo la matriz del modelview
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// seteo la posicion donde voy a comenzar a dibujar el texto
//	glRasterPos2f(x, y);

	// despligo el mensaje
//	for(c = text; *c != '\0'; c++)
//		glutBitmapCharacter(font, *c);

	// desapilo la matriz del modelview
	glPopMatrix();

	// seteo la matriz actual del proyeccion
	glMatrixMode(GL_PROJECTION);
	// restauro la previa
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);

	// habilito lo que al principio deshabilite y dejo todo como estaba
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}




