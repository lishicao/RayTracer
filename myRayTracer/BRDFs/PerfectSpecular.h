#ifndef __PERFECTSPECULAR__
#define __PERFECTSPECULAR__

#include "BRDF.h"
#include <math.h>

class PerfectSpecular : public BRDF
{
    private :

        RGBColor cr ;

        float    kr ;

        Sampler* sampler ;

    public :

        PerfectSpecular() ;

        PerfectSpecular( const PerfectSpecular& rhs ) ;

        virtual ~PerfectSpecular() ;

        virtual PerfectSpecular* clone() const ;

        virtual RGBColor
        f( const ShadeRec& sr , const Vector3D& wo , const Vector3D& wi ) const;

        virtual RGBColor rho( const ShadeRec& sr , const Vector3D& wo ) const;

        virtual RGBColor
        sample_f( const ShadeRec& sr, const Vector3D& wo , Vector3D& wi ) const;

        void set_kr( float k ) ;

        void set_cr( const RGBColor &c ) ;

        void set_cr( float R , float G , float B ) ;

        void set_cr( float c ) ;
} ;

inline void PerfectSpecular :: set_kr( float k )
{
    kr = k ;
}

inline void PerfectSpecular :: set_cr( const RGBColor& c )
{
    cr = c ;
}

inline void PerfectSpecular :: set_cr( float R , float G , float B )
{
    cr.r = R ; cr.g = G ; cr.b = B ;
}

inline void PerfectSpecular :: set_cr( float c )
{
    cr.r = cr.g = cr.b = c ;
}
#endif
