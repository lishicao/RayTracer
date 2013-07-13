#ifndef __EMISSIVE__
#define __EMISSIVE__

#include "Material.h"
#include "../BRDFs/Lambertian.h"
#include "../BRDFs/GlossySpecular.h"

class Emissive: public Material
{
    private :
        float ls ;
        RGBColor ce ;

    public :
        Emissive() ;
        Emissive( const Emissive& e ) ;
        virtual Material* clone() const ;
        Emissive& operator= ( const Emissive& rhs ) ;
        ~Emissive() ;

        void scale_randiance( const float _ls ) ;
        void set_ce( const float r , const float g , const float b ) ;
        void set_ce( const RGBColor& _ce ) ;
        virtual RGBColor get_Le( ShadeRec& sr ) const ;
        virtual RGBColor shade( ShadeRec& sr ) ;
        virtual RGBColor area_light_shade( ShadeRec& sr ) ;
} ;

inline void Emissive :: scale_randiance( const float _ls )
{
    ls = _ls ;
}

inline void Emissive :: set_ce( const float r , const float g , const float b )
{
    ce.r = r ; ce.g = g ; ce.b = b ;
}

inline void Emissive :: set_ce( const RGBColor& _ce )
{
    ce = _ce ;
}
#endif
