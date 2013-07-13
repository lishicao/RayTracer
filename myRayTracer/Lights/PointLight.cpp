#include "PointLight.h"

PointLight :: PointLight()
        : Light() ,
          ls( 1.0 ) ,
          color( 1.0 ) ,
          location( 0.0 , 0.0 , 0.0)
{}

PointLight :: PointLight( const PointLight & a )
        : Light( a ) ,
          ls( a.ls ) ,
          color( a.color ) ,
          location( a.location )
{}

Light* PointLight :: clone() const
{
    return ( new PointLight( *this ) ) ;
}

PointLight& PointLight :: operator = ( const PointLight & rhs )
{
    if( this == &rhs ) return * this ;

    Light :: operator = ( rhs ) ;

    ls = rhs.ls ;
    color = rhs.color ;
    location = rhs.location ;
    return *this ;
}

PointLight::~PointLight () {}

Vector3D PointLight :: get_direction( ShadeRec & sr ) {
    return ( location - sr.hit_point ).hat() ;
}

RGBColor PointLight :: L( ShadeRec & sr ) {
    return ( ls * color ) ;
}

bool     PointLight :: in_shadow( const Ray& ray , const ShadeRec& sr) const
{
    float t ;
    int  num_objects = sr.w.objects.size() ;
    float d = location.distance( ray.o ) ;

    for( int i = 0 ; i < num_objects ; i ++ )
        if( sr.w.objects[i] -> shadow_hit( ray , t ) && t < d )
            return true ;
    return false ;
}
