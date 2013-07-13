#include "Material.h"

Material :: Material() {}

Material :: Material( const Material & material ) {}

Material& Material :: operator = ( const Material& rhs )
{
    if( this == &rhs ) return *this ;
    else return *this ;
}

Material :: ~Material() {}

RGBColor Material :: shade( ShadeRec& sr )
{
    return black ;
}

RGBColor Material :: area_light_shade( ShadeRec& sr )
{
    return black ;
}

RGBColor Material :: get_Le( ShadeRec& sr ) const
{
    return black ;
}
