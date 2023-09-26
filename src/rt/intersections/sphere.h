/* FILE NAME  : sphere.h
 * PROGRAMMER : ND4
 * LAST UPDATE: 01.08.2021
 * PURPOSE    : Sphere intersection module.
 */

#ifndef __sphere_h_
#define __sphere_h_

#include "../rtdef.h"

namespace nirt
{
  class sphere : public shape
  {
  public:
    DBL R2;
    vec3 C;

    sphere( VOID )
    {
      R2 = 1;
      C = vec3(0, 0, 0);
      //this->Color = 0x023A91F;
      this->Color = vec3(0, 1, 1);
    }

    sphere( DBL Rad, const vec3 &P = vec3(0, 0, 0), vec3 Clr = vec3(0.3, 0.5, 0.8) )
    {
      R2 = Rad * Rad;
      C = P;
      this->Color = Clr;
    }

    sphere( DBL Rad, const vec3 &P, surface Surf )
    {
      R2 = Rad * Rad;
      C = P;
      this->Color = vec3(0);
      this->Mtl = Surf;
    }

    /* Intersection function.
     * ARGUMENTS:
     *   - ray to find intersection:
     *       const ray &R;
     *   - intersection pointer:
     *       intr *Intr;
     * RETURNS:
     *   (BOOL) Intersection value.
    */
    BOOL Intersection( const ray &R, intr *Intr ) override
    {
      vec3 a = C - R.Org;
      DBL OC2, OK, OK2, h2;

      OC2 = a & a;
      OK = a & R.Dir;
      OK2 = OK * OK;
      h2 = this->R2 - (OC2 - OK2);

      if (OK < TRESHOLD || h2 < TRESHOLD)
        return FALSE;

      if (OC2 < this->R2)
      {
        Intr->T = OK + sqrt(h2);

        Intr->P = R.RayApply(Intr->T);
        Intr->IsP = TRUE;

        Intr->N = (Intr->P - C).Normalizing();
        Intr->IsN = TRUE;

        Intr->Shp = this;
        return TRUE;
      }

      Intr->T = OK - sqrt(h2);

      Intr->P = R.RayApply(Intr->T);
      Intr->IsP = TRUE;

      Intr->N = (Intr->P - C).Normalizing();
      Intr->IsN = TRUE;

      Intr->Shp = this;

      for (INT i = 0; i < 5; i++)
        Intr->add[i] = 0;

      return TRUE;
    }
  };
}

#endif /* __sphere_h_ */

/* END OF 'sphere.h' FILE */