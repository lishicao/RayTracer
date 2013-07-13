#ifndef __BRDF__
#define __BRDF__

#include "../Utilities/RGBColor.h"
#include "../Utilities/Vector3D.h"
#include "../Utilities/ShadeRec.h"
#include "../Samplers/Sampler.h"
/*
this is lishicao
*/
class BRDF {
	public:

		BRDF() ;

		BRDF( const BRDF& brdf ) ;

		virtual BRDF* clone() const = 0 ;

		BRDF& operator= ( const BRDF& rhs ) ;

		virtual ~BRDF() ;

		void set_sampler( Sampler* sPtr ) ;

		virtual RGBColor
		f( const ShadeRec& sr , const Vector3D& wo , const Vector3D& wi ) const ;

		virtual RGBColor
		sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const ;

		virtual RGBColor
		sample_f( const ShadeRec& sr , const Vector3D& wo, Vector3D& wi , float& pdf ) const ;

		virtual RGBColor
		rho( const ShadeRec& sr, const Vector3D& wo ) const ;


	protected:

		Sampler* sampler_ptr;
};

#endif
