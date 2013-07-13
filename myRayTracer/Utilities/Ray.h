#ifndef __RAY__
#define __RAY__

#include "Point3D.h"
#include "Vector3D.h"

class Ray {
	public:

		Point3D			o;    // 原点
		Vector3D		d; 	  // 方向

		Ray(void);

		Ray(const Point3D& origin, const Vector3D& dir);

		Ray(const Ray& ray);

		Ray&
		operator= (const Ray& rhs);

		~Ray(void);
};

#endif
