/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : plane.h
 * PURPOSE     : Ray tracing project.
 *               Mathematics library.
 *               Ray module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               Nikolay V. Diakonov.
 * LAST UPDATE : 02.08.2021
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef _plane_h_
#define _plane_h_

#include "../rtdef.h"

/* Main support namespace */
namespace nirt
{
  /* sphere intersection class */
  class plane : public shape
  {
  public:
    vec3 N; // Plane normal
    DBL D;  // Plane coefficient

    /* Class constructor */
    plane( VOID ) : N(vec3(0, 1, 0)), D(3)
    {
      this->Color = vec3(0.3, 0.5, 0.8);
    } /* End of 'plane' function */

    /* Class constructor */
    plane( vec3 NewN, DBL NewD ) : N(NewN.Normalizing()), D(NewD)
    {
      this->Color = vec3(0.3, 0.5, 0.8);
    } /* End of 'plane' function */

    /* Class constructor */
    plane( vec3 NewN, DBL NewD, surface Surf ) : N(NewN.Normalizing()), D(NewD)
    {
      this->Mtl = Surf;
    } /* End of 'plane' function */

    /* Class constructor.
     * ARGUMENTS:
     *   - ray:
     *       const ray<DBL>;
     *   - intersection point:
     *       intr *Intr;
     * RETURNS: (TRUE) if intersected.
     */
    BOOL Intersection( const ray &R, intr *Intr ) override
    {
      DBL nd = N & R.Dir;

      if (fabs(nd) < TRESHOLD)
        return FALSE;

      Intr->T = -((N & R.Org) - D) / nd;
      if (Intr->T < TRESHOLD)
        return FALSE;
      Intr->Shp = this;

      Intr->P = R.RayApply(Intr->T);
      Intr->IsP = TRUE;

      Intr->N = N;
      Intr->IsN = TRUE;

      for (INT i = 0; i < 5; i++)
        Intr->add[i] = 0;

      Intr->add[4] = 1;

      return TRUE;
    } /* End of 'Intersection' function */

  }; /* End of 'plane' class */
} /* End of 'nirt' namespace */

#endif // !_plane_h_

/* END OF 'plane.h' FILE */

