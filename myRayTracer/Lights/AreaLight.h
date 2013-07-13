#ifndef __AREALIGHT__
#define __AREALIGHT__

#include "Light.h"
#include "../GeometricObjects/GeometricObject.h"
#include "../Tracers/AreaLighting.h"

class AreaLight : public Light
{
	public:

		AreaLight() ;

		AreaLight( const AreaLight& ls ) ;

		AreaLight& operator = (const AreaLight& rhs ) ;

		virtual Light* clone() const ;

		virtual ~AreaLight(void);

		virtual Vector3D
		get_direction(ShadeRec& sr) ;

		virtual bool
		in_shadow(const Ray& ray, const ShadeRec& sr) const ;

		virtual RGBColor
		L(ShadeRec& sr);

		virtual float
		G(const ShadeRec& sr)const ;

		virtual float
		pdf(const ShadeRec& sr)const ;

		virtual void
		set_object( GeometricObject* obj ) ;

	private:

		GeometricObject* object_ptr;
		Material* material_ptr;
		Point3D sample_point;
		Normal light_normal;
		Vector3D wi;
};

#endif
