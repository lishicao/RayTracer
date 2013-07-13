#ifndef __MATERIAL__
#define __MATERIAL__

class ShadeRec;

#include "../World/World.h"
#include "../Utilities/RGBColor.h"

class Material
{
    public :
        Material() ;

        Material( const Material & material ) ;

        virtual Material* clone() const = 0 ;

        virtual ~Material() ;

        virtual RGBColor get_Le( ShadeRec& sr ) const ;

        virtual RGBColor shade( ShadeRec & sr ) ;

        virtual RGBColor area_light_shade( ShadeRec & sr ) ;

    protected :
        Material& operator = ( const Material & rhs ) ;
} ;

#endif
