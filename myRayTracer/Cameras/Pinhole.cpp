#include "../Utilities/Constants.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Vector3D.h"
#include "../Tracers/Tracer.h"
#include "Pinhole.h"
#include <math.h>
#include <iostream>
Pinhole :: Pinhole()
	:	Camera() ,
		d( 500 ) ,
		zoom( 1.0 )
{}

Pinhole :: Pinhole( const Pinhole& c )
	: 	Camera( c ) ,
		d( c.d ) ,
		zoom( c.zoom )
{}

Camera* Pinhole :: clone() const {
	return new Pinhole(*this) ;
}

Pinhole& Pinhole :: operator = ( const Pinhole& rhs ) {
	if ( this == &rhs )
		return  *this ;

	Camera :: operator = ( rhs ) ;

	d 		= rhs.d ;
	zoom	= rhs.zoom ;

	return  *this ;
}

Pinhole::~Pinhole() {}


Vector3D Pinhole :: get_direction( const Point2D& p ) const {
	Vector3D dir = p.x * u + p.y * v - d * w ;
	dir.normalize() ;

	return dir ;
}


void  Pinhole :: render_scene( const World& w ) {
	RGBColor	L ;
	ViewPlane	vp( w.vp ) ;
	Ray			ray ;
	int 		depth = 0 ;
	Point2D 	pp ;
	int n = ( int ) sqrt ( ( float ) vp.num_samples ) ;

	vp.s  /= zoom ;
	ray.o  = eye ;
	for ( int r = 0 ; r < vp.vres ; r ++ )
		for ( int c = 0 ; c < vp.hres ; c ++ ) {
			L = black ;


			for ( int p = 0 ; p < n ; p ++ )
				for ( int q = 0 ; q < n ; q ++ ) {
					pp.x = vp.s * ( c - 0.5 * vp.hres + ( q + 0.5 ) / n ) ;
					pp.y = vp.s * ( r - 0.5 * vp.vres + ( p + 0.5 ) / n ) ;
					ray.d = get_direction( pp ) ;
					L += w.tracer_ptr->trace_ray( ray , depth ) ;
				}
			L /= vp.num_samples ;
			L *= exposure_time ;
			w.display_pixel( r , c , L ) ;
		}
}
