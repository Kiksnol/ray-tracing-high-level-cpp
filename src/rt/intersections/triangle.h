/* FILE NAME  : triangle.h
 * PROGRAMMER : ND4
 * LAST UPDATE: 01.08.2021
 * PURPOSE    : Triangle intersection module.
 */

#ifndef __triangle_h_
#define __triangle_h_

#include "../rtdef.h"

/* Main support namespace */
namespace nirt
{
  /* Triangle intersection class */
  class triangle : public shape
  {
  public:
    DBL D;       // Plane coefficient
    vec3 U1, V1; // triangle
    DBL u0, v0;  // Triangle coefficients


    /* Class constructor */
    triangle( VOID ) : D(1), U1(0), V1(0), u0(0), v0(0)
    {
      this->N = vec3(0, 1, 0);
    } /* End of 'triangle' function */

    /* Class constructor */
    triangle( vec3 P0, vec3 P1, vec3 P2, surface Surf )
    {
      N = ((P1 - P0) % (P2 - P0)).Normalizing();
      vec3 M0 = P0, P;
      D = N[0] * M0[0] + N[1] * M0[1] + N[2] * M0[2];

      vec3 r = P - P0, s1 = P1 - P0, s2 = P2 - P0;
      FLT s12 = s1 & s1, s22 = s2 & s2;

      U1 = ((s1 * s22) - (s2 * (s1 & s2))) / ((s12 * s22) - (s1 & s2) * (s1 & s2));
      u0 = P0 & U1; 

      V1 = ((s2 * s12) - (s1 * (s1 & s2))) / ((s12 * s22) - (s1 & s2) * (s1 & s2));
      v0 = P0 & V1; 

      this->Mtl = Surf;

    } /* End of 'triangle' function */

    /* Check intersection with triangle.
     * ARGUMENTS:
     *   - ray:
     *       const ray<DBL>;
     *   - intersection point:
     *       intr *Intr;
     * RETURNS: (TRUE) if intersected.
     */
    BOOL Intersection( const ray &R, intr *Intr ) override
    {
      DBL Treshold = 0.00001;

      Intr->T = (D - (N & R.Org)) / (N & R.Dir);
      if (Intr->T < Treshold)
        return FALSE;

      vec3 P = R.RayApply(Intr->T);
      
      DBL u = (P & U1) - u0;
      DBL v = (P & V1) - v0;
      if (u >= Treshold && v >= Treshold && (u + v) <= 1)
      {
        this->N = N;
        Intr->Shp = this;
        return TRUE;
      }
      return FALSE;
    } /* End of 'Intersection' function */

    /* Get shape normal function.
     * ARGUMENTS:
     *   - intersection to set normal:
     *       intr *Intr;
     * RETURNS: None.
     */
    VOID GetNormal( intr *Intr ) override
    {
      Intr->N = N;
      Intr->IsN = TRUE;
    } /* End of 'GetNormal' function */
  }; /* End of 'triangle' class */
} /* End of 'nirt' namespace */

#endif /* __triangle_h_ */

/* END OF 'triangle.h' FILE */