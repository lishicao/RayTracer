#ifndef __LIGHT__
#define __LIGHT__

#include "../Utilities/Vector3D.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/Ray.h"

class ShadeRec ;
class GeometricObject ;

class Light
{
    public :
        Light() ;

        Light( const Light & ls ) ;

        Light& operator = ( const Light & rhs ) ;

		virtual Light* clone() const = 0 ;

		virtual ~Light() ;

		virtual Vector3D get_direction ( ShadeRec & sr ) = 0 ;

		virtual RGBColor L( ShadeRec & sr ) ;

		virtual float G( const ShadeRec & sr ) const ;

		virtual float pdf( const ShadeRec & sr) const ;

		virtual bool in_shadow( const Ray& ray , const ShadeRec& sr ) const = 0 ;

		virtual void set_object( GeometricObject* obj ) ;

        void set_shadows( bool flag ) ;

        bool casts_shadows() ;

    protected :

        bool shadows ;
} ;

inline void Light :: set_shadows( bool flag ) {
    shadows = flag ;
}

inline bool Light :: casts_shadows() {
    return shadows ;
}

#endif
