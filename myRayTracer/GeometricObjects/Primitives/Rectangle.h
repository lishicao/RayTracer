#ifndef __Rectangles__
#define __Rectangles__

#include "../../Samplers/Sampler.h"
#include "../GeometricObject.h"

class Rectangles: public GeometricObject {
	public:

		Rectangles();

        Rectangles(const Rectangles& r);

		Rectangles(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b);

		Rectangles(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b, const Normal& n);

		virtual Rectangles* clone() const;

		Rectangles& operator= (const Rectangles& rhs);

		virtual ~Rectangles();

		virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const ;

        virtual bool shadow_hit( const Ray& ray , float &tmin ) const ;

		virtual void
		set_sampler(Sampler* sampler);

		virtual Point3D
		sample();

		virtual Normal
		get_normal(const Point3D& p);

		virtual float
		pdf(ShadeRec& sr);

	private:

		Point3D 		p0;
		Vector3D		a;
		Vector3D		b;
		double			a_len_squared;
		double			b_len_squared;
		Normal			normal;

		float			area;
		float			inv_area;
		Sampler*		sampler_ptr;

		static const double kEpsilon;
};

#endif
