#ifndef __AREALIGHTING__
#define __AREALIGHTING__

#include "Tracer.h"

class AreaLighting: public Tracer
{
    public :
        AreaLighting() ;
        AreaLighting( World* world_ptr ) ;
        virtual ~AreaLighting() ;
        virtual RGBColor trace_ray( const Ray& ray , const int depth ) const ;
} ;

#endif
