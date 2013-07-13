#ifndef __AMBIENT__
#define __AMBIENT__

#include "Light.h"

class Ambient : public Light {
    public :

        Ambient() ;

        Ambient( const Ambient & a ) ;

        virtual Light* clone() const ;

        Ambient& operator = ( const Ambient & rhs ) ;

        virtual ~Ambient() ;

        void  scale_radiance( const float b ) ;

        void  set_color( const float c ) ;

        void  set_color( const RGBColor & c ) ;

        void  set_color( const float r , const float g , const float b ) ;

        virtual Vector3D get_direction( ShadeRec & sr ) ;

        virtual RGBColor L ( ShadeRec & sr ) ;

        virtual bool in_shadow( const Ray& ray , const ShadeRec& sr ) const ;

    private :
        float ls ;
        RGBColor color ;
} ;

inline void Ambient :: scale_radiance ( const float b ) {
	ls = b;
}

inline void Ambient :: set_color( const float c ) {
    color.r = c ; color.g = c ; color.b = c ;
}

inline void Ambient :: set_color( const RGBColor & c ) {
    color = c ;
}

inline void Ambient :: set_color( const float r , const float g , const float b ) {
    color.r = r ; color.g = g ; color.b = b ;
}

#endif
