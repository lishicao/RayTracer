#include "GlossyReflector.h"

GlossyReflector::GlossyReflector() :
    Phong(),
    glossy_specular_brdf( new GlossySpecular())
    {}

GlossyReflector::GlossyReflector( const GlossyReflector& p ) :
    Phong(p)
    {
        if( p.glossy_specular_brdf )
            glossy_specular_brdf = p.glossy_specular_brdf ;
        else  glossy_specular_brdf = NULL ;
    }

Material* GlossyReflector::clone() const {
    return (new GlossyReflector( *this ) ) ;
}

GlossyReflector& GlossyReflector::operator= ( const GlossyReflector& rhs ) {
    if( this == &rhs ) return *this ;

    Phong :: operator = ( rhs ) ;

    if (glossy_specular_brdf) {
		delete glossy_specular_brdf;
		glossy_specular_brdf = NULL;
	}

	if (rhs.glossy_specular_brdf)
		glossy_specular_brdf = rhs.glossy_specular_brdf -> clone();
}

GlossyReflector::~GlossyReflector() {
    if (glossy_specular_brdf) {
		delete glossy_specular_brdf;
		glossy_specular_brdf = NULL;
	}
}

void GlossyReflector::set_samples( const int num_samples, const float exp ) {
    glossy_specular_brdf->set_samples( num_samples , exp ) ;
}

void GlossyReflector::set_kr( const float k ) {
    glossy_specular_brdf->set_ks(k) ;
}

void GlossyReflector::set_exponent( const float exp ) {
    glossy_specular_brdf->set_exp( exp ) ;
}

RGBColor GlossyReflector::area_light_shade( ShadeRec& sr ) {

    RGBColor L( Phong::area_light_shade( sr ) ) ;
    Vector3D wo( -sr.ray.d ) ;
    Vector3D wi ;
    float pdf ;
    RGBColor fr( glossy_specular_brdf->sample_f( sr, wo, wi, pdf ) ) ;
    Ray reflected_ray( sr.hit_point, wi ) ;
    L += fr * sr.w.tracer_ptr->trace_ray( reflected_ray, sr.depth + 1 ) * ( sr.normal * wi ) / pdf ;

    return ( L ) ;
}

RGBColor GlossyReflector::shade( ShadeRec& sr ) {

    RGBColor L( Phong::shade( sr ) ) ;
    Vector3D wo( -sr.ray.d ) ;
    Vector3D wi ;
    float pdf ;
    RGBColor fr( glossy_specular_brdf->sample_f( sr, wo, wi, pdf ) ) ;
    Ray reflected_ray( sr.hit_point, wi ) ;
    L += fr * sr.w.tracer_ptr->trace_ray( reflected_ray, sr.depth + 1 ) * ( sr.normal * wi ) / pdf ;

    return ( L ) ;
}
