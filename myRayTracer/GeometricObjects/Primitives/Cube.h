#ifndef _CUBE_H
#define _CUBE_H
#include <vector>
#include "../GeometricObject.h"
#include "Rectangle.h"
class Cube: public GeometricObject{
private :
	vector<Rectangles*> rectangles ;
	Point3D leftbuttomback ;//leftbuttomback是立方体的一个顶点,top和right和front分别是以该点为起点的方向向量同时包含立方体的边长
	Vector3D top;    //注意此时有top和right组成的面法向量是top*right  法向量指向立方体外边
	Vector3D right;  //注意此时有right和front组成的面法向量是right*front
	Vector3D front;  //注意此时有front和top组成的面法向量是front*top

public :
	Cube();
	Cube(const Point3D& _leftbuttomback,const Vector3D& _top,const Vector3D& _right,const Vector3D& _front );
	virtual Cube*
	clone(void) const;

	Cube(const Cube& r);

	virtual
	~Cube(void);

	Cube& operator= (const Cube& rhs);
	virtual void
	set_material(Material* mPtr) ;

	virtual bool
    hit( const Ray& ray, double& tmin, ShadeRec& sr ) const ;

    virtual bool
    shadow_hit( const Ray& ray , float &tmin )const ;

};

#endif
