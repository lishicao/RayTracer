#ifndef __THINLENS__
#define __THINLENS__

#include "../Utilities/Point2D.h"
#include "../World/World.h"
#include "Camera.h"
#include "../Samplers/Sampler.h"

class ThinLens : public Camera
{
    private :
        float lens_radius ;
        float d ;
        float f ;
        float zoom ;
        Sampler* sampler_ptr ;

    public :
        ThinLens() ;

        ThinLens( const ThinLens& th ) ;

        virtual Camera* clone() const ;

        ThinLens& operator=( const ThinLens& rhs ) ;

        virtual ~ThinLens() ;

        void set_vpd( const float ) ;

        void set_view_distance( const float vpd ) ;

        void set_zoom( const float zoom_factor ) ;

        void set_lens_radius( const float lens ) ;

        void set_focal_distance( const float focal ) ;

        void set_sampler( Sampler* sp ) ;

        Vector3D ray_direction( const Point2D& pixel_point , const Point2D& lens_point ) const ;

        virtual void render_scene( const World& w ) ;
} ;

inline void ThinLens :: set_vpd( const float vpd ){
    d = vpd ;
}

inline void ThinLens :: set_view_distance( const float vpd ) {
    d = vpd ;
}

inline void ThinLens :: set_zoom( const float zoom_factor ) {
    zoom = zoom_factor ;
}

inline void ThinLens :: set_lens_radius( const float lens ) {
    lens_radius = lens ;
}

inline void ThinLens :: set_focal_distance( const float focal ) {
    f = focal ;
}

inline void ThinLens :: set_sampler( Sampler* sp ) {
    if( sampler_ptr ) {
        delete sampler_ptr ;
        sampler_ptr = NULL ;
    }
    sampler_ptr = sp ;
    sampler_ptr -> map_samples_to_unit_disk() ;
}

#endif
