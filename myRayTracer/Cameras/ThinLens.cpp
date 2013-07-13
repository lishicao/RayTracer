#include "../Utilities/Constants.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Vector3D.h"
#include "../Tracers/Tracer.h"
#include "ThinLens.h"
#include <math.h>
#include <iostream>

ThinLens :: ThinLens()
        : Camera() ,
          lens_radius( 1 ) ,
          d( 500 ) ,
          f( 500 ) ,
          zoom( 1.0 ) ,
          sampler_ptr( NULL )
{}

ThinLens :: ThinLens( const ThinLens& th )
        : Camera( th ) ,
          lens_radius( th.lens_radius ) ,
          d( th.d ) ,
          f( th.f ) ,
          zoom( th.zoom ) ,
          sampler_ptr( th.sampler_ptr )
{}

Camera* ThinLens :: clone() const {
    return new ThinLens( *this ) ;
}

ThinLens& ThinLens :: operator = ( const ThinLens& rhs ) {
    if( this == &rhs ) return *this ;

    Camera :: operator = ( rhs ) ;

    lens_radius = rhs.lens_radius ;
    d           = rhs.d ;
    f           = rhs.f ;
    zoom        = rhs.zoom ;
    sampler_ptr = rhs.sampler_ptr ;

    return *this ;
}

ThinLens :: ~ThinLens() {}


Vector3D ThinLens :: ray_direction( const Point2D& piexl_point , const Point2D& lens_point ) const {
    Point2D p ;
    p.x = piexl_point.x * f / d ;
    p.y = piexl_point.y * f / d ;

    Vector3D dir = ( p.x - lens_point.x ) * u + ( p.y - lens_point.y ) * v - f * w ;
    dir.normalize() ;

    return dir ;
}

void  ThinLens :: render_scene( const World& w ) {
    RGBColor L   ;
    Ray      ray ;
    ViewPlane vp( w.vp ) ;
    int  depth = 0 ;

    Point2D sp , pp , dp , lp ;

    vp.s /= zoom ;

    for( int r = 0 ; r < vp.vres - 1 ; r ++ )
        for( int c = 0 ; c < vp.hres - 1 ; c ++ ) {
            L = black ;

            for( int n = 0 ; n < vp.num_samples ; n ++ ) {

                sp = vp.sampler_ptr -> sample_unit_square() ;
                pp.x = vp.s * ( c - vp.hres / 2.0 + sp.x ) ;
                pp.y = vp.s * ( r - vp.vres / 2.0 + sp.y ) ;

                dp = sampler_ptr -> sample_unit_disk() ;
                lp = dp * lens_radius ;

                ray.o = eye + lp.x * u + lp.y * v ;
                ray.d = ray_direction( pp , lp ) ;
                L += w.tracer_ptr -> trace_ray( ray , depth ) ;
            }
        L /= vp.num_samples ;
        L *= exposure_time ;
        w.display_pixel( r , c , L ) ;
    }
}
