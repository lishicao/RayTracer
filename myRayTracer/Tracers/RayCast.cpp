#include "RayCast.h"
#include "../World/World.h"
#include "../Utilities/ShadeRec.h"
#include "../Materials/Material.h"

RayCast::RayCast()
	: Tracer()
{}


RayCast::RayCast(World* _worldPtr)
	: Tracer(_worldPtr)
{}


RayCast::~RayCast(void) {}


RGBColor RayCast::trace_ray(const Ray& ray, const int depth) const {
	ShadeRec sr( world_ptr -> hit_objects( ray ) ) ;
	if ( sr.hit_an_object ) {
		sr.ray = ray ;
		RGBColor res = sr.material_ptr -> shade ( sr ) ;
		return ( res ) ;
	}
	else
		return ( world_ptr -> background_color ) ;
}
