#include"Paint.h"
#include <iostream>
using namespace std ;

Paint::Paint(void){}
Paint::~Paint(void){}

void Paint::setPixel(int x,int y,float r, float g, float b)
{
    glColor3f(r,g,b);
    glBegin(GL_POINTS);
		glVertex2i( x, y );
	glEnd();
	//glFlush() ;
}
