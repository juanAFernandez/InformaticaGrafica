#pragma once

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <stdio.h>
#include <string.h>
#include <GL/glut.h>
#include <GL/glu.h>



#pragma warning(disable:4996)

class Display
{
private:
	int frame;
	int time;
	int timebase;
	char msj[255];
	char msj1[255];
	char *projectName;
	float fps;

public:
	Display(char *_projectName = NULL);
	~Display(void);
	void displayText(char *text, float x, float y, int width, int height, float R = 1.0f, float G = 1.0f, float B = 0.0f, void* font = GLUT_BITMAP_HELVETICA_18);

};

#endif
