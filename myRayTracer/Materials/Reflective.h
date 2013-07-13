#ifndef __REFLECTIVE__
#define __REFLECTIVE__

#include "Phong.h"
#include "../BRDFs/PerfectSpecular.h"

class Reflective : public Phong
{
    private :
        PerfectSpecular* reflective_brdf ;

    public :
        Reflective() ;

        Reflective( const Reflective& rhs ) ;

        virtual Material* clone() const ;

        Reflective& operator = ( const Reflective& rhs ) ;

        ~Reflective() ;

        void  set_cr( const RGBColor& c ) ;

        void  set_cr( float r , float g , float b ) ;

        void  set_cr( float c ) ;

        void  set_kr( float k ) ;

        virtual RGBColor shade( ShadeRec & s ) ;

        virtual RGBColor area_light_shade( ShadeRec & s ) ;
} ;

inline void Reflective :: set_cr( const RGBColor& c )
{
    reflective_brdf->set_cr( c ) ;
}

inline void Reflective :: set_cr( float r , float g , float b )
{
    reflective_brdf->set_cr( r , g , b ) ;
}

inline void Reflective :: set_cr( float c )
{
    reflective_brdf->set_cr( c ) ;
}

inline void Reflective :: set_kr( float k )
{
    reflective_brdf->set_kr( k ) ;
}

#endif
