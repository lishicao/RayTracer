#include "GlossySpecular.h"

GlossySpecular :: GlossySpecular()
            : BRDF() ,
              cs( 0.0 ) ,
              ks( 0.0 ) ,
              sampler( NULL )
{}

GlossySpecular :: GlossySpecular( const GlossySpecular& lamb )
            : BRDF( lamb ) ,
              cs( lamb.cs ) ,
              ks( lamb.ks ) ,
              exp( lamb.exp ) ,
              sampler( lamb.sampler )
{}

GlossySpecular :: ~GlossySpecular() {}

GlossySpecular* GlossySpecular :: clone() const {
	return ( new GlossySpecular (*this) ) ;
}

RGBColor GlossySpecular :: f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const
{
    RGBColor L ;
    float ndotwi = sr.normal * wi ;
    Vector3D r( -wi + 2.0 * sr.normal * ndotwi ) ;
    float rdotwo = r * wo ;
    if( rdotwo > 0 )    L = ks * pow( rdotwo , exp ) ;
    return L ;
}

RGBColor GlossySpecular :: sample_f( const ShadeRec& sr , const Vector3D& wo , Vector3D& wi , float& pdf ) const
{
    float ndotwo = sr.normal * wo ;
    Vector3D r = -wo + 2.0 * sr.normal * ndotwo ;
    Vector3D w = r ;
    Vector3D u = Vector3D( 0.00424 , 1 , 0.00764 ) ^ w ;
    Vector3D v = u ^ w ;

    Point3D sp = sampler_ptr->sample_hemisphere() ;
    wi = sp.x * u + sp.y * v + sp.z * w ;

    if( sr.normal * wi < 0.0 )
        wi = -sp.x * u - sp.y * v + sp.z * w ;

    float phong_lobe = pow( r * wi , exp ) ;
    pdf = phong_lobe * ( sr.normal * wi ) ;

    return ( ks * cs * phong_lobe ) ;
}

RGBColor GlossySpecular :: rho(const ShadeRec& sr, const Vector3D& wo) const
{
    return black ;
}

void  GlossySpecular ::  set_sampler(Sampler* sp, const float exp)
{
    sampler = sp ;
    sampler_ptr -> map_samples_to_hemisphere( exp ) ;
}

void  GlossySpecular ::  set_samples( const int num_samples , const float exp ) {
	sampler_ptr = new MultiJittered( num_samples ) ;
	sampler_ptr -> map_samples_to_hemisphere( exp ) ;
}
