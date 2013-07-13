#ifndef __SHADE_REC__
#define __SHADE_REC__


class  World ;

#include "Point3D.h"
#include "Normal.h"
#include "RGBColor.h"
#include "Ray.h"
#include "../Materials/Material.h"

class ShadeRec {
	public:

		bool				hit_an_object ;
		Material* 			material_ptr ;
		Point3D 			hit_point ;
		Point3D				local_hit_point ;
		Normal				normal ;
		RGBColor			color ;
		Ray                 ray ;
		int                 depth ;
		Vector3D            dir ;
		int                 t ;

		World &				w ;
		ShadeRec( World& wr ) ;
		ShadeRec( const ShadeRec& sr ) ;
};

#endif
