#include "PerfectSpecular.h"

PerfectSpecular :: PerfectSpecular()
            :  BRDF() ,
               cr( 1.0 ) ,
               kr( 0.0 ) ,
               sampler( NULL )
{}

PerfectSpecular :: PerfectSpecular( const PerfectSpecular& rhs )
            :  BRDF( rhs ) ,
               cr( rhs.cr ) ,
               kr( rhs.kr ) ,
               sampler( rhs.sampler )
{}

PerfectSpecular :: ~PerfectSpecular() {}

PerfectSpecular* PerfectSpecular :: clone() const
{
    return ( new PerfectSpecular( *this ) ) ;
}

RGBColor PerfectSpecular :: f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const
{
    return ( black ) ;
}

RGBColor PerfectSpecular :: rho(const ShadeRec& sr, const Vector3D& wo) const
{
	return (black);
}

RGBColor PerfectSpecular :: sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const
{
    float ndotwo = sr.normal * wo ;
    wi = -wo + 2.0 * sr.normal * ndotwo ;
    return ( kr * cr / ( sr.normal * wi ) ) ;
}
