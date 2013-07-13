#ifndef __OPEN_CYLINDER__
#define __OPEN_CYLINDER__

#include "../GeometricObject.h"

class OpenCylinder: public GeometricObject {

	public:

		OpenCylinder();

		OpenCylinder(const double bottom, const double top, const double radius);

		OpenCylinder(const OpenCylinder& c);

		virtual OpenCylinder* clone () const;

		OpenCylinder& operator= (const OpenCylinder& rhs);

		virtual ~OpenCylinder();

		virtual bool hit(const Ray& ray, double& t, ShadeRec& sr) const;

		virtual bool shadow_hit( const Ray& ray , float &tmin ) const ;

	protected:

		double		y0;
		double		y1;
		double		radius;
		double		inv_radius;
};

#endif
