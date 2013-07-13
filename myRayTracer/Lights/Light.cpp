#include "Light.h"
#include "../Utilities/Constants.h"


Light :: Light() {}

Light :: Light( const Light & ls ) {}

Light & Light :: operator = ( const Light & rhs )
{
    if( this == & rhs ) return *this ;
    return *this ;
}

Light :: ~Light() {}

RGBColor Light :: L( ShadeRec & sr )
{
    return black ;
}

float Light :: G( const ShadeRec & sr ) const
{
    return 1.0 ;
}

float Light :: pdf( const ShadeRec & sr ) const
{
    return 1.0 ;
}

void Light :: set_object( GeometricObject* obj )
{
}
