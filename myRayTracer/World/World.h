#ifndef WROLD_H_INCLUDED
#define WROLD_H_INCLUDED

class GeometricObject;
class Paint;
class Tracer;

#include "ViewPlane.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/Ray.h"
#include "../Cameras/Camera.h"
#include "../Lights/Light.h"

using namespace std;

class World
{
    public :
        ViewPlane					vp ;                    // 底片
        Camera*                     camera_ptr ;            // 相机
        RGBColor					background_color ;      // 背景颜色
        Tracer*				        tracer_ptr ;            // 跟踪器
        vector<GeometricObject*>	objects ;               // 物体的集合
        Paint* 				        paintArea ;             // 画点
        Light*                      ambient_ptr ;           // 环境光
        vector<Light*>              lights ;                // 光源集合

    public :
        World() ;

        ~World() ;

        void  add_object( GeometricObject* object_ptr ) ;

        void  build() ;                                     // 建立场景

        void  render_sence() const ;

        RGBColor max_to_one    ( const RGBColor & c ) const ;

		RGBColor clamp_to_color( const RGBColor & c ) const ;

		void  display_pixel(const int row, const int column, const RGBColor& pixel_color) const;

        ShadeRec hit_bare_bones_objects ( const Ray & ray ) ;

        void  set_camera( Camera* _camera );

        void  set_ambient_light( Light* a_ptr ) ;

        void  add_light( Light* light_ptr ) ;

        //void  open_window( const int hres , const int vres ) const ;

        ShadeRec hit_objects( const Ray& ray , float & tmin ) ;

        ShadeRec hit_objects( const Ray& ray ) ;

    private :
        void delete_objects() ;
} ;

inline void World :: add_object( GeometricObject* object_ptr ){
    objects.push_back( object_ptr ) ;
}

inline void World :: add_light( Light* light_ptr ) {
    lights.push_back( light_ptr ) ;
}

inline void World :: set_camera( Camera* _camera ) {
    camera_ptr = _camera ;
}

inline void World :: set_ambient_light( Light* a_ptr ) {
    ambient_ptr = a_ptr ;
}

#endif
