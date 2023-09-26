/* FILE NAME  : mthdef.h
 * PROGRAMMER : ND4
 * LAST UPDATE: 01.08.2021
 * PURPOSE    : Default math preferences
 */

#ifndef __mthdef_h_
#define __mthdef_h_

#include <cmath>

#include "../def.h"

/* Pi math constant */
#define PI 3.14159265358979323846
 
/* Degrees to radians conversion */
#define D2R(A) ((A) * (PI / 180.0))
#define Degree2Radian(a) D2R(a)

typedef double DBL;
typedef float FLT;
typedef unsigned __int64 UINT64;
typedef unsigned char BYTE;

/* Math namespace */
namespace mth
{
  // Forward declarations
  template<typename Type> class vec3;  /* 3D vector class */
  template<typename Type1> class matr; /* Matrix class */

  /* Clamp function.
   * ARGUMENTS:
   *   - value to clamp:
   *       Type X;
   *   - min value:
   *       Type Mi;
   *   - max value:
   *       Type Ma;
   * RETURNS: (Type) clamped X
   */
  template <typename Type>
  Type Clamp( Type X, Type Mi = 0, Type Ma = 1 )
  {
    if (X < Mi)
      return Mi;
    if (X > Ma)
      return Ma;
    return X;
  } /* End of 'Clamp' function */

  /* Linear Interpolate function.
   * ARGUMENTS:
   *   - values to interpolate:
   *       Type A, B;
   *   - factor to interpolate:
   *       Type T;
   * RETURNS: (Type) interpolated value
   */
  template<typename Type>
  Type LinearInterpolate( Type A, Type B, Type T )
  {
    return A * (1 - T) + B * T;
  } /* End of 'LinearInterpolate' function */

  template<typename Type>
  VOID Swap( Type *A, Type *B )
  {
    Type tmp = *A;

    *A = *B;
    *B = tmp;
  }

} /* End of 'mth' namespace */


#endif /* __mthdef_h_ */

/* END OF 'mthdef.h' FILE */