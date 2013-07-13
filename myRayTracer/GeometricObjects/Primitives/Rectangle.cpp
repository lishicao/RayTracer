#include "Rectangle.h"
const double Rectangles :: kEpsilon = 0.001 ;

Rectangles::Rectangles()
	: 	GeometricObject(),
		p0(-1, 0, -1),
		a(0, 0, 2), b(2, 0, 0),
		a_len_squared(4.0),
		b_len_squared(4.0),
		normal(0, 1, 0),
		area(4.0),
		inv_area(0.25),
		sampler_ptr(NULL)
{}

Rectangles::Rectangles(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b)
	:	GeometricObject(),
		p0(_p0),
		a(_a),
		b(_b),
		a_len_squared(a.len_squared()),
		b_len_squared(b.len_squared()),
		area(a.length() * b.length()),
		inv_area(1.0 / area),
		sampler_ptr(NULL)
{
	normal = a ^ b;
	normal.normalize();
}

Rectangles::Rectangles(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b, const Normal& n)
	:	GeometricObject(),
		p0(_p0),
		a(_a),
		b(_b),
		a_len_squared(a.len_squared()),
		b_len_squared(b.len_squared()),
		area(a.length() * b.length()),
		inv_area(1.0 / area),
		normal(n),
		sampler_ptr(NULL)
{
	normal.normalize();
}

Rectangles* Rectangles :: clone() const {
	return (new Rectangles(*this));
}


Rectangles :: Rectangles (const Rectangles& r)
	:	GeometricObject(r),
		p0(r.p0),
		a(r.a),
		b(r.b),
		a_len_squared(r.a_len_squared),
		b_len_squared(r.b_len_squared),
		normal(r.normal),
		area(r.area),
		inv_area(r.inv_area)
{
	if(r.sampler_ptr)
		sampler_ptr	= r.sampler_ptr->clone();
	else  sampler_ptr = NULL;
}


Rectangles& Rectangles :: operator= ( const Rectangles& rhs ) {
	if ( this == &rhs )
		return (*this) ;

	GeometricObject::operator=(rhs);

	p0				= rhs.p0;
	a				= rhs.a;
	b				= rhs.b;
	a_len_squared	= rhs.a_len_squared;
	b_len_squared	= rhs.b_len_squared;
	area			= rhs.area;
	inv_area		= rhs.inv_area;
	normal			= rhs.normal;

	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	if (rhs.sampler_ptr)
		sampler_ptr= rhs.sampler_ptr->clone();

	return (*this);
}


Rectangles::~Rectangles () {

	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}
}

bool
Rectangles::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {

	double t = (p0 - ray.o) * normal / (ray.d * normal);

	if (t <= kEpsilon)
		return (false);

	Point3D p = ray.o + t * ray.d;
	Vector3D d = p - p0;

	double ddota = d * a;

	if (ddota < 0.0 || ddota > a_len_squared)
		return (false);

	double ddotb = d * b;

	if (ddotb < 0.0 || ddotb > b_len_squared)
		return (false);

	tmin 				= t;
	sr.normal 			= normal;
	sr.local_hit_point 	= p;

	return (true);
}


void
Rectangles::set_sampler(Sampler* sampler) {
	sampler_ptr = sampler;
}


Point3D
Rectangles::sample(void) {
	Point2D sample_point = sampler_ptr->sample_unit_square();
	return (p0 + sample_point.x * a + sample_point.y * b);
}


Normal
Rectangles::get_normal(const Point3D& p) {
	return (normal);
}


float
Rectangles::pdf(ShadeRec& sr) {
	return (inv_area);
}

bool Rectangles :: shadow_hit( const Ray& ray , float &tmin ) const
{
	double t = (p0 - ray.o) * normal / (ray.d * normal);

	if (t <= kEpsilon)
		return (false);

	Point3D p = ray.o + t * ray.d;
	Vector3D d = p - p0;

	double ddota = d * a;

	if (ddota < 0.0 || ddota > a_len_squared)
		return (false);

	double ddotb = d * b;

	if (ddotb < 0.0 || ddotb > b_len_squared)
		return (false);

	tmin 				= t;

	return (true);
}
