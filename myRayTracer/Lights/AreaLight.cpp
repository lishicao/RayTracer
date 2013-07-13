#include "AreaLight.h"
#include <iostream>
AreaLight::AreaLight()
	:Light(),
	 object_ptr(NULL),
	 material_ptr(NULL),
	 sample_point(NULL),
	 light_normal(0),
	 wi(0)
{}

AreaLight::AreaLight(const AreaLight& ls)
	: Light(ls),
	object_ptr(ls.object_ptr),
	material_ptr(ls.material_ptr),
	sample_point(ls.sample_point),
	light_normal(ls.light_normal),
	wi(ls.wi)
{}

AreaLight& AreaLight::operator= (const AreaLight& rhs){
	if (this == &rhs)
		return (*this);

	Light::operator= (rhs);

	object_ptr = rhs.object_ptr;
	material_ptr = rhs.material_ptr;
	sample_point = rhs.sample_point;
	light_normal = rhs.light_normal;
	wi = rhs.wi;

	return (*this);
}

Light* AreaLight :: clone() const
{
	return ( new AreaLight( *this ) );
}

AreaLight::~AreaLight(void){
    if (object_ptr) {
		delete object_ptr;
		object_ptr = NULL;
	}

	if (material_ptr) {
		delete material_ptr;
		material_ptr = NULL;
	}
}

Vector3D AreaLight::get_direction(ShadeRec& sr)
{
	sample_point = object_ptr->sample();
	light_normal = object_ptr->get_normal(sample_point);
	wi = sample_point - sr.hit_point;
	wi.normalize();

	return (wi);
}

bool AreaLight::in_shadow(const Ray& ray, const ShadeRec& sr)const{
    float t;
	int num_objects = sr.w.objects.size();
	float ts = ( sample_point - ray.o ) * ray.d;

	for( int j = 0; j < num_objects; j++ ){
	    if( sr.w.objects[j]->shadow_hit(ray, t) && t < ts )
			return (true);
	}

}

RGBColor AreaLight::L(ShadeRec& sr){
	float ndotd = -light_normal * wi;
	if( ndotd > 0.0 )  return ( object_ptr->get_material()->get_Le(sr) );
	else               return (black);
}

float AreaLight::G(const ShadeRec& sr)const{
     float ndotd = -light_normal * wi;
	 float d2 = sample_point.d_squared(sr.hit_point);

	 return ( ndotd /2 );
}

float AreaLight::pdf(const ShadeRec& sr)const{
     return ( object_ptr->pdf( sr )	 );
}

void AreaLight :: set_object( GeometricObject* obj )
{
    object_ptr = obj ;
}
