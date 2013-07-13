#include "../Materials/Material.h"
#include "../Utilities/Constants.h"
#include "../GeometricObjects/GeometricObject.h"


GeometricObject :: GeometricObject()
	:  material_ptr( NULL )
{}


GeometricObject::GeometricObject (const GeometricObject& object)
{
    if( object.material_ptr )
        material_ptr = object.material_ptr -> clone() ;
    else material_ptr = NULL ;
}


GeometricObject& GeometricObject::operator= (const GeometricObject& rhs) {

	if (this == &rhs)
		return (*this);

	if( material_ptr )
	{
	    delete material_ptr ;
	    material_ptr = NULL ;
	}

    if( rhs.material_ptr )
        material_ptr = rhs.material_ptr -> clone() ;

	return ( *this ) ;
}


GeometricObject::~GeometricObject (void) {
    if( material_ptr ){
        delete material_ptr ;
        material_ptr = NULL ;
    }
}


void  GeometricObject :: set_material( Material* m_ptr ){
    material_ptr = m_ptr ;
}

Material* GeometricObject :: get_material() const {
    return material_ptr ;
}

float GeometricObject :: pdf( const ShadeRec& sr )
{
    return 1.0 ;
}

Point3D GeometricObject :: sample()
{
    return ( Point3D( 0 , 0 , 0 ) ) ;
}

Normal GeometricObject :: get_normal( const Point3D& p )
{
    return ( Normal( 0 , 0 , 0 ) ) ;
}
