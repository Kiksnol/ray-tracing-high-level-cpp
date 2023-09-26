/* FILE NAME   : point.h
 * PURPOSE     : Ray Tracing project.
 *               Point light class
 * PROGRAMMER  : AU3
 * LAST UPDATE : 03.08.2021
 * NOTE        : Module namespace 'nirt'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __point_h_
#define __point_h_

#include "../rtdef.h"

/* Project namespace */
namespace nirt
{
  /* Light source point class */
  class point : public light
  {
  public:
    DBL R1, R2, Cr;
    vec3 Loc; // Location of light

    point( DBL RR1 = 1, DBL RR2 = 20, vec3 L = vec3(1), vec3 C = vec3(1) )
    {
      R1 = RR1;
      R2 = RR2;
      Cr = R2 - R1;
      Loc = L;
      LI.Color = C;
    }

    /* Shadow coef function
     * ARGUMENTS:
     *   - Position:
     *       const vec3f &P;
     * RETURNS:
     *   (DBL) att coef.
     */
    DBL Shadow( vec3 &P, light_info *L ) override
    {
      vec3 Direction = (Loc - P).Normalizing();
      DBL Dist = !(P - Loc), att = 1 / (Cq * Dist * Dist + Cl * Dist + Cc);

      L->L = Direction;
      L->Color = LI.Color;
      L->Dist = Dist;
      return COM_MIN(att, 1);
    } /* End of 'Shadow' function */

  };  /* End of 'point' class */
} /* End of 'nirt' namespace */

#endif // __point_h_

/* END OF 'point.h' FILE */