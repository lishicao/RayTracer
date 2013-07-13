#ifndef __GEOMETRIC_OBJECT__
#define __GEOMETRIC_OBJECT__

#include <math.h>
#include "../Utilities/RGBColor.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Vector3D.h"
#include "../Utilities/Normal.h"
#include "../Utilities/Ray.h"
#include "../Utilities/ShadeRec.h"
#include "../Utilities/Constants.h"
#include "../Materials/Material.h"

//class Material ;

class GeometricObject {

	public:

		GeometricObject() ;

		GeometricObject( const GeometricObject& object ) ;

		virtual GeometricObject* clone() const = 0 ;

		virtual  ~GeometricObject () ;

		virtual bool hit( const Ray& ray , double& t , ShadeRec& s ) const = 0 ;

        virtual void set_material(  Material* m_ptr ) ;

        virtual bool shadow_hit( const Ray& ray , float &tmin ) const = 0 ;

        Material* get_material() const ;

        virtual float pdf( const ShadeRec& sr ) ;

        virtual Point3D sample() ;

        virtual Normal get_normal( const Point3D& p ) ;

	protected:

        mutable Material*   material_ptr ;

		GeometricObject& operator = ( const GeometricObject& rhs ) ;
};

#endif
