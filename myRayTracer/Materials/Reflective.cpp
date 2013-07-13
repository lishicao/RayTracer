#include "Reflective.h"
#include "../Tracers/Tracer.h"

Reflective :: Reflective()
        : Phong() ,
          reflective_brdf( new PerfectSpecular )
{}

Reflective :: ~Reflective()
{
    if( reflective_brdf )
    {
        delete reflective_brdf ;
        reflective_brdf = NULL ;
    }
}

Reflective :: Reflective( const Reflective& rhs )
        : Phong( rhs )
{
    if( rhs.reflective_brdf ) reflective_brdf = rhs.reflective_brdf ;
    else reflective_brdf = NULL ;
}

Material* Reflective :: clone() const
{
    return new Reflective( *this ) ;
}

Reflective& Reflective :: operator = ( const Reflective& rhs )
{
    if( this == &rhs ) return *this ;

    Phong :: operator = ( rhs ) ;

    if( reflective_brdf )
    {
        delete reflective_brdf ;
        reflective_brdf = NULL ;
    }

    if( rhs.reflective_brdf ) reflective_brdf = rhs.reflective_brdf->clone() ;

    return *this ;
}

RGBColor Reflective :: shade( ShadeRec &sr )
{
    RGBColor L( Phong :: shade( sr ) ) ;
    Vector3D wo = -sr.ray.d ;
    Vector3D wi ;
    RGBColor fr = reflective_brdf->sample_f( sr , wo , wi ) ;
    Ray reflective_ray( sr.hit_point , wi ) ;

    L += fr * sr.w.tracer_ptr->trace_ray( reflective_ray , sr.depth + 1 ) * ( sr.normal * wi ) ;
    return L ;
}

/*RGBColor Reflective :: area_light_shade( ShadeRec &sr )
{
    RGBColor L( Phong :: area_light_shade( sr ) ) ;
    Vector3D wo = -sr.ray.d ;
    Vector3D wi ;

    RGBColor fr = reflective_brdf->sample_f( sr , wo , wi ) ;
    Ray reflective_ray( sr.hit_point , wi ) ;

    L += fr * sr.w.tracer_ptr->trace_ray( reflective_ray , sr.depth + 1 ) * ( sr.normal * wi ) ;
   // L = red ;
    return L ;
}*/
