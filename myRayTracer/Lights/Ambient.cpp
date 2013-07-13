#include "Ambient.h"

Ambient :: Ambient()
        : Light() ,
          ls( 1.0 ) ,
          color( 1.0 )
{}

Ambient :: Ambient( const Ambient & a )
        : Light( a ) ,
          ls( a.ls ) ,
          color( a.color )
{}

Light* Ambient :: clone() const
{
    return ( new Ambient( *this ) ) ;
}

Ambient& Ambient :: operator = ( const Ambient & rhs )
{
    if( this == &rhs ) return * this ;

    Light :: operator = ( rhs ) ;

    ls = rhs.ls ;
    color = rhs.color ;
    return *this ;
}

Ambient::~Ambient () {}

Vector3D Ambient :: get_direction( ShadeRec & sr ) {
    return ( Vector3D( 0.0 ) ) ;
}

RGBColor Ambient :: L( ShadeRec & sr ) {
    return ( ls * color ) ;
}

bool Ambient :: in_shadow( const Ray& ray , const ShadeRec& sr ) const
{
    return false ;
}
