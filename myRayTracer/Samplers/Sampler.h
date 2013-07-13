#ifndef __SAMPLER__
#define __SAMPLER__

#include <vector>
#include <math.h>
#include "../Utilities/Point2D.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Maths.h"
using namespace std;
class Sampler {
	public:

		Sampler(void);

		Sampler(const int num);

		Sampler(const int num, const int num_sets);

		Sampler(const Sampler& s);

		Sampler&
		operator= (const Sampler& rhs);

		virtual Sampler*
		clone(void) const = 0;

		virtual
		~Sampler(void);

		void
		set_num_sets(const int np);

		virtual void
		generate_samples(void) = 0;

		int
		get_num_samples(void);

		void
		shuffle_x_coordinates(void);

		void
		shuffle_y_coordinates(void);

		void
		setup_shuffled_indices(void);

		void
		map_samples_to_unit_disk(void);

		void
		map_samples_to_hemisphere(const float p);

		void
		map_samples_to_sphere(void);



		Point2D
		sample_unit_square(void);

		Point2D
		sample_unit_disk(void);

		Point3D
		sample_hemisphere(void);

		Point3D
		sample_sphere(void);

		Point2D
		sample_one_set(void);

	protected:

		int 					num_samples;
		int 					num_sets;
		vector<Point2D>			samples;
                                                        //采样点指的是是平面上的采样点
                                                        //而不是物体上的碰撞点
		vector<int>				shuffled_indices;

		vector<Point2D>			disk_samples;
                                                        //圆盘采样
		vector<Point3D> 		hemisphere_samples;
                                                        //半球体采样
		vector<Point3D> 		sphere_samples;
		                                                //球体采样
		unsigned long 			count;
                                                        //目前使用的采样点个数
		int 					jump;
};

#endif
