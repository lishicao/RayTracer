#include <windows.h>
#ifdef __APPLE__
#include <GL/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include "World/World.h"
#include "GeometricObjects/Primitives/Sphere.h"
#include "Utilities/Point3D.h"
#include <iostream>

#define Width 800
#define Height 800

float modulus = 100.0;

void  setWindow( double , double , double , double ) ;
void  setViewport( int , int , int , int ) ;
void  myDisplay() ;

int  main( int argc , char *argv[] )
{
    glutInit ( & argc , argv ) ;
	glutInitDisplayMode ( GLUT_RGB | GLUT_SINGLE ) ;
	glutInitWindowSize ( Width - 1 , Height - 1 ) ;
	glutCreateWindow("rayTracer");
	glutDisplayFunc( myDisplay ) ;
	setWindow( -400 , 400 , -400 , 400 ) ;
	setViewport( 0 , 200 , 0 , 200 ) ;
	glutMainLoop();
}

void  setWindow( double left , double right , double buttom , double top )
{
    glMatrixMode( GL_PROJECTION ) ;
    glLoadIdentity() ;
    gluOrtho2D( left , right , buttom , top ) ;
}

void  setViewport( int left , int right , int buttom , int top )
{
    glViewport( left , buttom , right - left , top - buttom) ;
}

//  build 建立场景
//  然后照相机跟踪

void  myDisplay()
{
    glClear( GL_COLOR_BUFFER_BIT ) ;
    World *world = new World() ;
	world -> build() ;
	world -> camera_ptr->render_scene( *world ) ;
    glFlush() ;
}
