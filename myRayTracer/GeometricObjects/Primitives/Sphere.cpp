#include "Sphere.h"
#include "math.h"

const double Sphere::kEpsilon = 0.001;


Sphere::Sphere(void)
	: 	GeometricObject(),
		center(0.0),
		radius(1.0),
		sampler_ptr(NULL),
		inv_area(1/(4*radius*radius*PI))
{}


Sphere::Sphere(Point3D c, double r)
	: 	GeometricObject(),
		center(c),
		radius(r),
		sampler_ptr(NULL),
		inv_area(1/(4*radius*radius*PI))
{}


Sphere*
Sphere::clone(void) const {
	return (new Sphere(*this));
}


Sphere::Sphere (const Sphere& sphere)
	: 	GeometricObject(sphere),
		center(sphere.center),
		radius(sphere.radius),
		sampler_ptr(sphere.sampler_ptr),
		inv_area(sphere.inv_area)
{}


Sphere&
Sphere::operator= (const Sphere& rhs)
{
	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);

	center 	= rhs.center;
	radius	= rhs.radius;
    inv_area = rhs.inv_area;
    sampler_ptr = rhs.sampler_ptr;
	return (*this);
}


Sphere::~Sphere(void) {}


bool Sphere::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	double 		t;
	Vector3D	temp 	= ray.o - center ;
	double 		a 		= ray.d * ray.d ;
	double 		b 		= 2.0 * temp * ray.d ;
	double 		c 		= temp * temp - radius * radius ;
	double 		disc	= b * b - 4.0 * a * c ;

	if ( disc < 0.0 )
		return  false ;
	else {
		double  e = sqrt ( disc ) ;
		double  denom = 2.0 * a ;
		t = ( -b - e) / denom ;

		if ( t > kEpsilon ) {
			tmin = t ;
			sr.normal 	 = ( temp + t * ray.d ) / radius ;
			sr.local_hit_point = ray.o + t * ray.d ;
			return  true ;
		}

		t = ( -b + e ) / denom ;

		if (t > kEpsilon) {
			tmin = t ;
			sr.normal   = ( temp + t * ray.d ) / radius ;
			sr.local_hit_point = ray.o + t * ray.d ;
			return  true ;
		}
	}
	return  false ;
}

bool Sphere :: shadow_hit( const Ray& ray , float& tmin ) const {
	double 		t;
	Vector3D	temp 	= ray.o - center ;
	double 		a 		= ray.d * ray.d ;
	double 		b 		= 2.0 * temp * ray.d ;
	double 		c 		= temp * temp - radius * radius ;
	double 		disc	= b * b - 4.0 * a * c ;

	if ( disc < 0.0 )
		return  false ;
	else {
		double  e = sqrt ( disc ) ;
		double  denom = 2.0 * a ;
		t = ( -b - e) / denom ;

		if ( t > kEpsilon ) {
			tmin = t ;
			return  true ;
		}

		t = ( -b + e ) / denom ;

		if (t > kEpsilon) {
			tmin = t ;
			return  true ;
		}
	}
	return  false ;
}

float Sphere ::pdf( const ShadeRec& sr ){
    return inv_area;
}

void Sphere::set_sampler(Sampler* _sampler) {
	sampler_ptr = _sampler;
	sampler_ptr->map_samples_to_sphere();
}

Point3D
Sphere::sample(){
    Point3D sample_point = sampler_ptr->sample_sphere();
    return sample_point*radius+center;
}


Normal
Sphere::get_normal(const Point3D& p){
    return (p - center);
}
