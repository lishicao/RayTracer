#ifndef __POINTLIGHT__
#define __POINTLIGHT__

#include "Light.h"
#include "../Utilities/Vector3D.h"
#include "../Utilities/ShadeRec.h"
#include "../GeometricObjects/GeometricObject.h"

class PointLight : public Light {
    public :

        PointLight() ;

        PointLight( const PointLight & a ) ;

        virtual Light* clone() const ;

        PointLight& operator = ( const PointLight & rhs ) ;

        virtual ~PointLight() ;

        void  scale_radiance( const float b ) ;

        void  set_color( const float c ) ;

        void  set_color( const RGBColor & c ) ;

        void  set_color( const float r , const float g , const float b ) ;

        void  set_location( const Point3D & Location ) ;

        void  set_location( const double x , const double y , const double z ) ;

        virtual Vector3D get_direction( ShadeRec & sr ) ;

        virtual RGBColor L ( ShadeRec & sr ) ;

        virtual bool  in_shadow( const Ray& ray , const ShadeRec& sr ) const ;

    private :
        float ls ;
        RGBColor color ;
        Point3D location ;
} ;

inline void PointLight :: scale_radiance ( const float b ) {
	ls = b;
}

inline void PointLight :: set_color( const float c ) {
    color.r = c ; color.g = c ; color.b = c ;
}

inline void PointLight :: set_color( const RGBColor & c ) {
    color = c ;
}

inline void PointLight :: set_color( const float r , const float g , const float b ) {
    color.r = r ; color.g = g ; color.b = b ;
}

inline void PointLight :: set_location( const Point3D & Location ) {
    location = Location ;
}

inline void PointLight :: set_location( const double x , const double y , const double z ) {
    location.x = x ; location.y = y ; location.z = z ;
}

#endif
