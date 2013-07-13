#ifndef __GLOOSYREFLECTOR__
#define __GLOOSYREFLECTOR__

#include "Phong.h"
#include "../Tracers/Tracer.h"

class GlossyReflector: public Phong{
    public:
        GlossyReflector() ;

        GlossyReflector( const GlossyReflector& p ) ;

        virtual Material* clone() const ;

        GlossyReflector& operator= ( const GlossyReflector& rhs ) ;

        ~GlossyReflector() ;

        void set_samples( const int num_samples, const float exp ) ;

        void set_kr( const float k ) ;

        void  set_cr( const RGBColor& c ) ;

        void  set_cr( float r , float g , float b ) ;

        void  set_cr( float c ) ;


        void set_exponent( const float exp ) ;

        virtual RGBColor area_light_shade( ShadeRec& sr ) ;

        virtual RGBColor shade( ShadeRec& sr ) ;

    private:
        GlossySpecular* glossy_specular_brdf ;

};

inline void GlossyReflector :: set_cr( const RGBColor& c )
{
    glossy_specular_brdf->set_cs( c ) ;
}

inline void GlossyReflector :: set_cr( float r , float g , float b )
{
    glossy_specular_brdf->set_cs( r , g , b ) ;
}

inline void GlossyReflector :: set_cr( float c )
{
    glossy_specular_brdf->set_cs( c ) ;
}

#endif
