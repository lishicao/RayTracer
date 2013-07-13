#ifndef PAINT_H_INCLUDED
#define PAINT_H_INCLUDED
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include "../Utilities/RGBColor.h"

class Paint{
    Paint() ;
    ~Paint() ;
    public :
        void setPixel( int x , int y , float r, float g, float b) ;
};
#endif
