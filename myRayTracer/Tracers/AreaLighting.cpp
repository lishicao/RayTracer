#include "AreaLighting.h"
#include "../World/World.h"
#include "../Utilities/ShadeRec.h"
#include "../Materials/Material.h"

AreaLighting :: AreaLighting()
             : Tracer()
{}

AreaLighting :: AreaLighting( World* world_ptr )
             : Tracer( world_ptr )
{}

AreaLighting :: ~AreaLighting() {}

RGBColor AreaLighting :: trace_ray( const Ray& ray , const int depth ) const
{
    ShadeRec sr( world_ptr -> hit_objects( ray ) ) ;
	if ( sr.hit_an_object ) {
		sr.ray = ray ;
		RGBColor res = sr.material_ptr -> area_light_shade ( sr ) ;
		return ( res ) ;
	}
	else
		return ( world_ptr -> background_color ) ;
}
