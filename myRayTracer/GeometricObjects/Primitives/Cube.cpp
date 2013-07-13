#include "Cube.h"

Cube::Cube()
	:GeometricObject(),
	leftbuttomback(0,5,0),top(0,1,0),right(1,0,0),front(0,0,1)
{
    rectangles.push_back(new Rectangles(leftbuttomback,top,right,right^top));
    rectangles.push_back(new Rectangles(leftbuttomback,front,right,right^front));
    rectangles.push_back(new Rectangles(leftbuttomback,top,front,front^top));
    Point3D righttopfront = leftbuttomback +top+right+front;
    rectangles.push_back(new Rectangles(righttopfront,-top,-right,top^right));
    rectangles.push_back(new Rectangles(righttopfront,-front,-right,front^right));
    rectangles.push_back(new Rectangles(righttopfront,-top,-front,top^front));
}

Cube::Cube(const Point3D& _leftbuttomback,const Vector3D& _top,const Vector3D& _right,const Vector3D& _front )
:GeometricObject(),leftbuttomback(_leftbuttomback),top(_top),right(_right),front(_front){
    rectangles.push_back(new Rectangles(leftbuttomback,top,right,right^top));
    rectangles.push_back(new Rectangles(leftbuttomback,front,right,right^front));
    rectangles.push_back(new Rectangles(leftbuttomback,top,front,front^top));
    Point3D righttopfront = leftbuttomback +top+right+front;
    rectangles.push_back(new Rectangles(righttopfront,-top,-right,top^right));
    rectangles.push_back(new Rectangles(righttopfront,-front,-right,front^right));
    rectangles.push_back(new Rectangles(righttopfront,-top,-front,top^front));
}
Cube*
Cube::clone(void) const {
	return (new Cube(*this));
}
Cube::Cube(const Cube& r)
	:GeometricObject(r),
		rectangles(r.rectangles),
		leftbuttomback(r.leftbuttomback),
		top(r.top),
		right(r.right),
		front(r.front)
{}

Cube::~Cube(void){}

Cube& Cube::operator= (const Cube& rhs){
     if (this == &rhs)
		return (*this);

	GeometricObject::operator=(rhs);
	rectangles  = rhs.rectangles ;
	leftbuttomback = rhs.leftbuttomback;
	top = rhs.top;
	right = rhs.right;
	front = rhs.front;

	return (*this);
}

void
Cube::set_material(Material* mPtr) {
	GeometricObject::set_material(mPtr);
	for( vector<Rectangles*>::iterator i  = rectangles.begin(); i < rectangles.end() ; i++ ){
	     (*i)->set_material(mPtr);
	}
}

bool
Cube::hit( const Ray& ray, double& tmin, ShadeRec& sr ) const{
	//hit干嘛的？他是来获取入射光线是否和本对象碰撞，若碰撞则返回碰撞点的信息(法向量,三维坐标值)，和碰撞点距离光源的最近距离
	double t;
	ShadeRec ss(sr);
	double tm = kHugeValue;
	bool flag = false;
	for(vector<Rectangles*>::const_iterator i = rectangles.begin(); i < rectangles.end(); i++){
		if( (*i)->hit(ray,t,ss) && t < tm ){
			 sr.local_hit_point     = ss.local_hit_point;
			 sr.normal    = ss.normal;
		     tm  = t;
			 flag = true;
		}
	}
	if( flag ){
		tmin = tm;
	    return true;
	}
	else
		return false;
}

bool
Cube::shadow_hit( const Ray& ray , float &tmin )const {
	float t;
	double tm = kHugeValue;
	bool flag = false;
	for(vector<Rectangles*>::const_iterator i = rectangles.begin(); i < rectangles.end(); i++){
		if( (*i)->shadow_hit(ray,t) && t < tm ){
		     tm  = t;
			 flag = true;
		}
	}
	if( flag){
	    return true;
	}
	else
		return false;
}
