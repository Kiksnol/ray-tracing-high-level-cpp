/* FILE NAME  : mth_ray.h
 * PROGRAMMER : ND4
 * LAST UPDATE: 01.08.2021
 * PURPOSE    : Intersections.
 */

#ifndef __mth_ray_h
#define __mth_ray_h

#include "mthdef.h"

/* Math support namespace */
namespace mth
{
  /* Ray handle class */
  template <typename Type>
  class ray
  {
  public:
    vec3<Type> 
      Org, // Ray origin
      Dir; // Ray Direction

    /* Default constructor */
    ray( VOID )
    {
    } /* End of 'ray' function */

    /* Class constructor.
     * ARGUMENTS:
     *   - ray origin:
     *       const vec3<type> &Origin;
     *   - ray direction:
     *       const vec3<type> &Direction;
     */
    ray( const vec3<Type> Origin, const vec3<Type> Direction ) : 
      Org(Origin), Dir(static_cast<vec3<Type>>(Direction).Normalizing())
    {
    } /* End of 'ray' constructor */

    /* Class constructor.
     * ARGUMENTS:
     *   - Ray point parameter:
     *       Type T;
     * RETURNS:
     *   (vec3<Type>) ray point.
    */
    vec3<Type> operator()( Type T )
    {
      return Org + Dir * T;
    }

    vec3<Type> RayApply( Type T ) const
    {
      return Org + Dir * T;
    }


  }; /* End of 'ray' class */
} /* End of 'mth' namespace */


#endif /* __mth_ray_h */

/* END OF 'mth_ray.h' FILE */