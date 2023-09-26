/* FILE NAME   : box.h
 * PURPOSE     : Ray Tracing project.
 *               Sphere intersection module.
 * PROGRAMMER  : AU3
 * LAST UPDATE : 01.08.2021
 * NOTE        : Module namespace 'nirt'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __box_h_
#define __box_h_

#include "../rt.h"

/* Project namespace */
namespace nirt
{
  /* Box class */
  class box : public shape
  {
  public:
    vec3 B1, B2;

    /* Default constructor */
    box( VOID )
    {
      B1 = vec3(0, 5, 4);
      B2 = vec3(1, 6, 5);
      this->Color = vec3(1, 0, 0);
    } /* End of 'sphere' function */

    box( vec3 MinBB, vec3 MaxBB, surface Surf ) : B1(MinBB), B2(MaxBB)
    {
      this->Color = vec3(1, 0, 0);
      this->Mtl = Surf;

    }

    /* Intersection function. 
     * ARGUMENTS:
     *   - ray to find intersection:
     *       const ray &R;
     *   - intersection pointer to write result:
     *       intr *Intr;
     * RETURNS: (BOOL) intersection value
     */
    BOOL Intersection( const ray &R, intr *Intr ) override
    {
      INT i = 0;
      BOOL Flags[3] = {TRUE};
      DBL t0, t1, tn = 0, tf = HUGE_VAL, tmp;
      INT Ind = 1, tind = 0;
      vec3 Norm[6] = 
      {
        vec3(1, 0, 0), vec3(-1,  0,  0),
        vec3(0, 1, 0), vec3( 0, -1,  0),
        vec3(0, 0, 1), vec3( 0,  0, -1),
      };

      /* X intersect */
      if (R.Dir[i] == 0)
      {
        if (R.Org[i] < B1[i] || R.Org[i] > B2[i])
          Flags[i] = FALSE;
      }
      else
      {
        t0 = (B1[i] - R.Org[i]) / R.Dir[i], t1 = (B2[i] - R.Org[i]) / R.Dir[i];
        if (t0 > t1)
          COM_SWAP(t0, t1, tmp), Ind = 0;
        if (t0 > tn)
          tn = t0;
        if (t1 < tf)
          tf = t1;
        if (tn > tf || tf < 0)
          return FALSE;
      }
      i++;

      /* Y intersection */
      if (R.Dir[i] == 0)
      {
        if (R.Org[i] < B1[i] || R.Org[i] > B2[i])
          Flags[i] = FALSE;
      }
      else
      {
        tind = 3;

        t0 = (B1[i] - R.Org[i]) / R.Dir[i], t1 = (B2[i] - R.Org[i]) / R.Dir[i];
        if (t0 > t1)
          COM_SWAP(t0, t1, tmp), tind = 2;
        if (t0 > tn)
          tn = t0, Ind = tind;
        if (t1 < tf)
          tf = t1;
        if (tn > tf || tf < 0)
          return FALSE;
      }
      i++;

      /* Z intersection */
      if (R.Dir[i] == 0)
      {
        if (R.Org[i] < B1[i] || R.Org[i] > B2[i])
          Flags[i] = FALSE;
      }
      else
      {
        tind = 5;

        t0 = (B1[i] - R.Org[i]) / R.Dir[i], t1 = (B2[i] - R.Org[i]) / R.Dir[i];
        if (t0 > t1)
          COM_SWAP(t0, t1, tmp), tind = 4;
        if (t0 > tn)
          tn = t0, Ind = tind;
        if (t1 < tf)
          tf = t1;
        if (tn > tf || tf < 0)
          return FALSE;
      }
      if (!Flags[0] && !Flags[1] && !Flags[2])
        return FALSE;
      Intr->T = tn;
      Intr->Shp = this;
      Intr->IsN = TRUE;
      Intr->N = Norm[Ind];

      Intr->P = R.RayApply(Intr->T);
      Intr->IsP = TRUE;

      return TRUE;
    } /* End of 'Intersect' function */

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

  
  }; /* End of 'sphere' class */
} /* End of 'nirt' namespace */

#endif /* __box_h_ */

/* END OF 'box.h' FILE */