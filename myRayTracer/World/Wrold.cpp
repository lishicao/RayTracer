#include "World.h"
#include "../Paint/Paint.h"
#include "../Tracers/RayCast.h"
#include "../Tracers/Whitted.h"
#include "../Tracers/AreaLighting.h"
#include "../Cameras/Pinhole.h"
#include "../Cameras/Thinlens.h"
#include "../Lights/PointLight.h"
#include "../Lights/Directional.h"
#include "../Lights/Ambient.h"
#include "../Lights/AreaLight.h"

#include "../Materials/Matte.h"
#include "../Materials/Reflective.h"
#include "../Materials/Emissive.h"
#include "../Materials/GlossyReflector.h"

#include "../Utilities/RGBColor.h"
#include "../Materials/Phong.h"
#include "../GeometricObjects/Primitives/Sphere.h"
#include "../GeometricObjects/Primitives/Plane.h"
#include "../GeometricObjects/Primitives/Cube.h"


World :: World()
    : camera_ptr( NULL ) ,
      background_color( black ) ,
      tracer_ptr( NULL ) ,
      ambient_ptr( new Ambient() )
{}

World :: ~World()
{
    if( tracer_ptr ) {
        delete tracer_ptr ;
        tracer_ptr = NULL ;
    }
    delete_objects() ;
}

RGBColor  World :: max_to_one( const RGBColor & c ) const
{
    float  max_value = max ( c.r , max ( c.g , c.b ) ) ;
	if ( max_value > 1.0 )  return ( c / max_value ) ;
	else return ( c ) ;
}

RGBColor  World :: clamp_to_color ( const RGBColor & raw_color ) const
{
	RGBColor c ( raw_color ) ;
	if ( raw_color.r > 1.0 || raw_color.g > 1.0 || raw_color.b > 1.0) {
		c.r = 1.0; c.g = 0.0; c.b = 0.0;
	}
	return ( c ) ;
}


void  World :: display_pixel( const int row , const int column , const RGBColor &raw_color ) const
{
    RGBColor  mapped_color ;
    if ( vp.show_out_of_gamut ) mapped_color = clamp_to_color ( raw_color ) ;
    else  mapped_color = max_to_one ( raw_color ) ;
    if ( vp.gamma != 1.0 ) mapped_color = mapped_color.powc ( vp.inv_gamma ) ;

    int  x = column - vp.hres / 2 ;
    int  y = row - vp.vres / 2 ;
    paintArea -> setPixel( x , y , mapped_color.r , mapped_color.g , mapped_color.b ) ;
}

ShadeRec World :: hit_bare_bones_objects ( const Ray & ray )
{

	float		tmin 			= kHugeValue ;
    ShadeRec	sr ( * this ) ;
	double 		t ;
	Normal      normal ;
	Point3D     local_hit_point ;
	int 		num_objects 	= objects.size() ;

	for ( int j = 0 ; j < num_objects ; j ++ )
		if ( objects[j] -> hit( ray , t , sr ) && ( t < tmin ) ) {
			sr.hit_an_object	= true ;
			tmin 				= t ;
			sr.material_ptr     = objects[j] -> get_material() ;
			//sr.color			= objects[j] -> get_color() ;
			sr.hit_point        = ray.o + t * ray.d ;
			normal              = sr.normal ;
			local_hit_point     = sr.local_hit_point ;
		}
    if( sr.hit_an_object ) {
        sr.t = tmin ;
        sr.normal = normal ;
        sr.local_hit_point = local_hit_point ;
    }
	return ( sr ) ;
}

ShadeRec World :: hit_objects( const Ray& ray , float & tmin )
{
	ShadeRec	sr ( * this ) ;
	double 		t ;
	Normal      normal ;
	Point3D     local_hit_point ;
	int 		num_objects 	= objects.size() ;

	for ( int j = 0 ; j < num_objects ; j ++ )
		if ( objects[j] -> hit( ray , t , sr ) && ( t < tmin ) ) {
			sr.hit_an_object	= true ;
			tmin 				= t ;
			sr.material_ptr     = objects[j] -> get_material() ;
			//sr.color			= objects[j] -> get_color() ;
			sr.hit_point        = ray.o + t * ray.d ;
			normal              = sr.normal ;
			local_hit_point     = sr.local_hit_point ;
		}
    if( sr.hit_an_object ) {
        sr.t = tmin ;
        sr.normal = normal ;
        sr.local_hit_point = local_hit_point ;
    }
	return ( sr ) ;
}

ShadeRec World :: hit_objects( const Ray& ray )
{
    float		tmin 			= kHugeValue ;
	ShadeRec	sr ( * this ) ;
	double 		t ;
	Normal      normal ;
	Point3D     local_hit_point ;
	int 		num_objects 	= objects.size() ;

	for ( int j = 0 ; j < num_objects ; j ++ ){
	    objects[j] -> hit( ray , t , sr ) ;
		if ( objects[j] -> hit( ray , t , sr ) && ( t < tmin ) ) {
			sr.hit_an_object	= true ;
			tmin 				= t ;
			sr.material_ptr     = objects[j] -> get_material() ;
			sr.hit_point        = ray.o + t * ray.d ;
			normal              = sr.normal ;
			local_hit_point     = sr.local_hit_point ;
		}
	}
    if( sr.hit_an_object ) {
        sr.t = tmin ;
        sr.normal = normal ;
        sr.local_hit_point = local_hit_point ;
    }
	return ( sr ) ;
}

void  World :: delete_objects ()
{
	int num_objects = objects.size() ;

	for ( int j = 0 ; j < num_objects ; j ++ )
	{
		delete objects[j] ;
		objects[j] = NULL ;
	}

	objects.erase ( objects.begin() , objects.end() ) ;
}

/*
    建立场景
*/

void World::build(void) {
	int num_samples = 16 ;

	vp.set_hres( 800 ) ;
	vp.set_vres( 800 ) ;
	vp.set_samples( num_samples ) ;
	vp.set_max_depth( 10 ) ;

	tracer_ptr = new AreaLighting(this);

	Pinhole* pinhole_ptr = new Pinhole ;
	pinhole_ptr->set_eye( 0 , 2 , 0 )  ;
	pinhole_ptr->set_lookat( 0 , 2 , 100 ) ;
	pinhole_ptr->set_view_distance( 700 ) ;
	pinhole_ptr->compute_uvw() ;
	set_camera( pinhole_ptr )  ;


	// four point lights near the ceiling
	// these don't use distance attenuation

    MultiJittered *sampler_ptr = new MultiJittered ;

    Emissive *emissive_ptr = new Emissive ;
    emissive_ptr ->set_ce( 1 , 1 , 1 ) ;
    emissive_ptr ->scale_randiance( 30.0 ) ;

    Sphere   *object_ptr1 = new Sphere ;
    object_ptr1 ->set_center( 3 , 3 , 5 ) ;
    object_ptr1 ->set_radius( 2.0 ) ;
    object_ptr1 ->set_sampler( sampler_ptr ) ;
    object_ptr1 ->set_material( emissive_ptr ) ;
    add_object( object_ptr1 ) ;

    /*Rectangles *object_ptr2 = new Rectangles( Point3D( 0 , 0 , 5 ) , Vector3D(1,0,0) , Vector3D(0,1,0) , Normal(0,0,-1) ) ;
    object_ptr2 ->set_material( emissive_ptr ) ;
    object_ptr2 ->set_sampler( sampler_ptr ) ;
    add_object( object_ptr2 ) ;*/


    AreaLight *light_ptr1 = new AreaLight ;
    light_ptr1 ->set_object( object_ptr1 ) ;
    light_ptr1 ->set_shadows( true ) ;
    add_light( light_ptr1 ) ;

	/*PointLight* light_ptr_1 = new PointLight;
	light_ptr_1->set_location( 10 , 10 , 0 ) ;
	light_ptr_1->scale_radiance(2.0) ;
	light_ptr_1->set_shadows(true);
    add_light(light_ptr_1);*/

    /*PointLight* light_ptr2 = new PointLight;
	light_ptr2->set_location(0, 10, 10);
	light_ptr2->scale_radiance(2.0);
	light_ptr2->set_shadows(true);
    add_light(light_ptr2);

    PointLight* light_ptr3 = new PointLight;
	light_ptr3->set_location(-10, 10, 0);
	light_ptr3->scale_radiance(2.0);
	light_ptr3->set_shadows(true);
    add_light(light_ptr3);

    PointLight* light_ptr4 = new PointLight;
	light_ptr4->set_location(0, 10, -10);
	light_ptr4->scale_radiance(2.0);
	light_ptr4->set_shadows(true);
    add_light(light_ptr4);*/


	Reflective* reflective_ptr1 = new Reflective;
	reflective_ptr1->set_ka(0.0);
	reflective_ptr1->set_kd(0.0);
	reflective_ptr1->set_cd(0.0);
	reflective_ptr1->set_ks(0.0);
	reflective_ptr1->set_exp(1000.0);
	reflective_ptr1->set_kr(0.75);
	reflective_ptr1->set_cr(1 , 1 , 1 );



	double room_size = 11.0;

	Matte* matte_ptr1 = new Matte;
	matte_ptr1->set_ka( 0.1  );
	matte_ptr1->set_kd( 0.8 );
	matte_ptr1->set_cd( 1 , 1 , 1 ) ;


	Sphere*	sphere_ptr1 = new Sphere( Point3D( -5 , 5 , 15 ) , 3 );
	sphere_ptr1->set_material(matte_ptr1);
	add_object(sphere_ptr1);


	Phong* phong_ptr = new Phong ;
	phong_ptr ->set_cd( 1 , 1 , 1 ) ;
	phong_ptr ->set_cs( 1 , 1 , 1 ) ;
	phong_ptr ->set_exp( 10 ) ;
	phong_ptr ->set_ka( 0.5 ) ;
	phong_ptr ->set_ks( 0.5 ) ;

	Plane* floor_ptr = new Plane( Point3D ( 0 , -0.5,  0), Normal(0, 1, 0));
	floor_ptr->set_material( matte_ptr1 );
	add_object( floor_ptr ) ;

	Matte* matte_ptr2 = new Matte;
	matte_ptr2->set_ka(0.35);
	matte_ptr2->set_kd(0.50);
	matte_ptr2->set_cd(white);

	Plane* ceiling_ptr = new Plane(Point3D( 0 , 15 ,  0), Normal(0, -1, 0));
	ceiling_ptr->set_material( matte_ptr2 );
	add_object( ceiling_ptr );

	Matte* matte_ptr3 = new Matte;
	matte_ptr3->set_ka(0.15);
	matte_ptr3->set_kd(0.80);
	matte_ptr3->set_cd(0.5, 0.75, 0.75);

	Plane* backWall_ptr = new Plane(Point3D( 0 , 0 ,  -room_size), Normal(0, 0, 1));
	backWall_ptr->set_material(matte_ptr3);
	add_object(backWall_ptr);


	Plane* frontWall_ptr = new Plane(Point3D( 0 , 0 ,  20 ), Normal(0, 0, -1));
	frontWall_ptr->set_material(reflective_ptr1);
	add_object(frontWall_ptr);

	Matte* matte_ptr4 = new Matte;
	matte_ptr4->set_ka(0.15);
	matte_ptr4->set_kd(0.90);
	matte_ptr4->set_cd(0.71, 0.40, 0.20);

	Plane* leftWall_ptr = new Plane(Point3D(-10, 0, 0), Normal(1, 0, 0));
	leftWall_ptr->set_material(matte_ptr4);
	add_object(leftWall_ptr);



	Plane* rightWall_ptr = new Plane(Point3D(10, 0, 0), Normal(-1, 0, 0));
	rightWall_ptr->set_material(matte_ptr4);
	add_object(rightWall_ptr);

/*


	double mirror_size 	= 8;  	// the mirror size
	double offset 		= 1.0;  // the mirror offset from the walls



	Reflective* reflective_ptr2 = new Reflective;
	reflective_ptr2->set_ka(0);
	reflective_ptr2->set_kd(0);
	reflective_ptr2->set_cd(black);
	reflective_ptr2->set_ks(0);
	reflective_ptr2->set_kr(0.9);
	reflective_ptr2->set_cr(0.9, 1.0, 0.9);  // light green

	// glossy reflector material for the back and front mirrors

	float exp = 25000.0;
	GlossyReflector* glossy_reflector_ptr = new GlossyReflector;
	glossy_reflector_ptr->set_samples(num_samples, exp);
	glossy_reflector_ptr->set_ka(0.0);
	glossy_reflector_ptr->set_kd(0.0);
	glossy_reflector_ptr->set_ks(0.0);
	glossy_reflector_ptr->set_exp(exp);
	glossy_reflector_ptr->set_cd(black);
	glossy_reflector_ptr->set_kr(0.9);
	glossy_reflector_ptr->set_exponent(exp);
	glossy_reflector_ptr->set_cr(0.9, 1.0, 0.9);  // light green


	// back wall mirror  (-ve zw)

	Point3D p0;
	Vector3D a, b;

	p0 = Point3D(-mirror_size, -mirror_size, -(room_size - offset));
	a = Vector3D(2.0 * mirror_size, 0, 0);
	b = Vector3D(0, 2.0 * mirror_size, 0);
	Normal n(0, 0, 1);
	Rectangles* rectangle_ptr1 = new Rectangles(p0, a, b, n);
//	rectangle_ptr1->set_material(reflective_ptr2);
	rectangle_ptr1->set_material(glossy_reflector_ptr);
	add_object(rectangle_ptr1);


	// front wall mirror  (+ve zw)

	p0 = Point3D(-mirror_size, -mirror_size, +(room_size - offset));
	n = Normal(0, 0, -1);
	Rectangles* rectangle_ptr2 = new Rectangles(p0, a, b, n);
//	rectangle_ptr2->set_material(reflective_ptr2);
	rectangle_ptr2->set_material(glossy_reflector_ptr);
	add_object(rectangle_ptr2);


	// left wall mirror  (-ve xw)

	p0 = Point3D(-(room_size - offset), -mirror_size, +mirror_size);
	a = Point3D(0, 0, -2.0 * mirror_size);
	n = Normal(1, 0, 0);
	Rectangles* rectangle_ptr3 = new Rectangles(p0, a, b, n);
	rectangle_ptr3->set_material(reflective_ptr2);
	add_object(rectangle_ptr3);


	// horizontal mirror underneath the sphere
	// this has no direct illumination and a lemon color

	Reflective* reflective_ptr3 = new Reflective;
	reflective_ptr3->set_ka(0);
	reflective_ptr3->set_kd(0);
	reflective_ptr3->set_cd(black);
	reflective_ptr3->set_ks(0);
	reflective_ptr3->set_kr(1);
	reflective_ptr3->set_cr(1, 1, 0.5);  // lemon

	double yw = -4.0;   // the yw location of the mirror

	p0 = Point3D(-mirror_size, yw, -mirror_size);
	a = Vector3D(0, 0, 2.0 * mirror_size);
	b = Vector3D(2.0 * mirror_size, 0, 0);
	n = Normal(0, 1, 0);
	Rectangles* rectangle_ptr4 = new Rectangles(p0, a, b, n);
	rectangle_ptr4->set_material(reflective_ptr3);
	add_object(rectangle_ptr4);*/
}
