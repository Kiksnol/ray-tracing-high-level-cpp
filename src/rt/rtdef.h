/* FILE NAME   : rt.h
 * PURPOSE     : Ray Tracing project.
 *               Base classes defines
 * PROGRAMMER  : AU3
 * LAST UPDATE : 01.08.2021
 * NOTE        : Module namespace 'nirt'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __rtdef_h_
#define __rtdef_h_

#include "../def.h"

#define THRESHOLD 0.001

/* Project namespace */
namespace nirt
{
  class shape;

  /* Light info class */
  class light_info
  {
  public:
    vec3 L;     // light source direction
    vec3 Color; // light source color
    DBL Dist;   // distance to light source
  };

  /* Light source class */
  class light
  {
  public:
    DBL Cc = 0, Cl = 0.1, Cq = 0; // Linear, quadratic, cube coeffs
    light_info LI;

    /* Get shadow function.
     * ARGUMENTS: 
     *   - point to eval direction:
     *       vec3 &P;
     *   - pointer to write direction:
     *       light_info *L;
     * RETURNS: (vec3) light color
     */
    virtual DBL Shadow( vec3 &P, light_info *L )
    {
      return 1.0;
    } /* End of 'GetColor' function */

  };  /* End of 'light' class */

  /* Environment class */
  class envi
  {
  public:
    DBL RefractionCoef = 0;
    DBL DecayCoef = 0;;

    envi( VOID )
    {
      RefractionCoef = 0;
      DecayCoef = 0;
    }

    envi( DBL R, DBL D )
    {
      RefractionCoef = R;
      DecayCoef = D;
    }
  };

  /* Material class */
  class surface
  {
  public:
    vec3 Ka = vec3(0.1, 0.5, 0.4), Kd = vec3(0.7, 0.8, 0.7), Ks = vec3(0.4, 0.3, 0.7); // ambient, diffuse, specular
    DBL Ph = 12.5;                                                                     // Bui Tong Phong coefficient
    DBL Kr = 0.4, Kt;                                                                  // reflected, transmitted

    surface( VOID )
    {
      Ka = vec3(0.1, 0.5, 0.4), Kd = vec3(0.7, 0.8, 0.7), Ks = vec3(0.4, 0.3, 0.7); // ambient, diffuse, specular
      Ph = 12.5;                                                                     // Bui Tong Phong coefficient
      Kr = 0.4, Kt = 0;                                                                  // reflected, transmitted
    }

    surface( vec3 rKa, vec3 rKd, vec3 rKs, DBL rPh = 30, DBL rKr = 0.5, DBL rKt = 0 )
    {
      Ka = rKa;
      Kd = rKd;
      Ks = rKs;
      Ph = rPh;
      Kr = rKr;
      Kt = rKt;
    }

  }; /* End of 'surface' class */

  /* Intersection class */
  class intr
  {
  public:
    DBL T;                // Intersection dist
    shape *Shp = nullptr; // Shape
    vec3 N;               // Normal
    BOOL IsN = FALSE;     // Flag eval normal
    vec3 P;               // Position
    BOOL IsP = FALSE;     // Flag eval pos

    BOOL add[5] = {0};
    INT I[5];             // Addon (int)
    DBL D[5];             // Addon (double)
  }; /* End of 'intr' class */

  /* Base shape class */
  class shape
  {
  public:
    vec3 Color = vec3(1, 0, 0); // Color
    vec3 N;               // Normal
    surface Mtl;
    envi M;


    /* Default constructor */
    shape( VOID ) : Color(vec3(0))
    {
      M = envi(0, 1);
    } /* End of 'shape' function */

    /* Intersection function. 
     * ARGUMENTS:
     *   - ray to find intersection:
     *       const ray &R;
     *   - intersection pointer to write result:
     *       intr *Intr;
     * RETURNS: (BOOL) intersection value
     */
    virtual BOOL Intersection( const ray &R, intr *Intr )
    {
      return FALSE;
    } /* End of 'Intersect' function */

    /* Get shape normal function.
     * ARGUMENTS:
     *   - intersection to set normal:
     *       intr *Intr;
     * RETURNS: None.
     */
    virtual VOID GetNormal( intr *Intr )
    {
      Intr->N = N;
      Intr->IsN = TRUE;
    } /* End of 'GetNormal' function */
  }; /* End of 'shape' class */

  /* Scene class */
  class scene
  {
  public:
    stock<shape *> Shapes;
    stock<light *> Lights;
    INT CurRec = 0, MaxRec = 13;
    vec3 Ambient = vec3(1), BackGnd = vec3(0);
    envi Air;

    ~scene( VOID )
    {
      Shapes.Walk([]( shape *sh ) {delete sh;});
      Lights.Walk([]( light *lgh ) {delete lgh;});
    }

    /* Intersection function. 
     * ARGUMENTS:
     *   - ray to find intersection:
     *       const ray &R;
     *   - intersection pointer to write result:
     *       intr *Intr;
     * RETURNS: (BOOL) intersection value
     */
    BOOL Intersection( const ray &R, intr *Intr )
    {
      intr ci, in;

      for (INT i = 0; i < Shapes.Size(); i++)
      {
        if (Shapes[i]->Intersection(R, &in) &&
          (ci.Shp == nullptr || ci.T > in.T))
          ci = in;
      }
      *Intr = ci;
      return ci.Shp != nullptr;
    } /* End of 'Intersect' function */

    vec3 GetKa( const vec3 &P )
    {
      vec3 c = vec3(((INT)(P[0]) ^ (INT)(P[1]) ^ (INT)(P[2])) & 1);

      if (c[0] == 1)
        c = vec3(0.5, 0, 1);

      return c;
    }

    vec3 GetKa2( const vec3 &P )
    {
      DBL a = ((INT)((P[0] * P[0] + P[1] * P[1] + P[2] * P[2]) * 50) % 256) / 255.0;
      vec3 c = vec3(a, a, a);

      return c;
    }

    vec3 GetKa3( const vec3 &P )
    {
      DBL n = (abs((INT)(P[0] * P[1] * P[2] * 50)) % 256) / 255.0;
      vec3 c = vec3(0, n, n);

      return c;
    }

    vec3 GetKa4( const vec3 &P )
    {
      DBL a = (((((INT)P[0] ^ 20) + ((INT)P[1] ^ 20) + ((INT)P[2] ^ 20) + 16) * 2500) % 255) / 255.0;

      vec3 c = vec3(0, a, -a);

      return c;
    }

    /* Shade function.
     * ARGUMENTS:
     *   - direction:
     *       vec3 &D;
     *   - enviroment to shade:
     *       envi &Media;
     *   - intersection to write data:
     *       intr *Intr;
     *   - weight:
     *       DBL Weight;
     */
    vec3 Shade( vec3 &Dir, envi &Media, intr *Intr, light_info *L, DBL Weight = 1 )
    {
      DBL vn = Intr->N & Dir;
      if (vn > 0)
        vn = -vn, Intr->N = -Intr->N;
      vec3 diff(0), specular(0);
      vec3 color(0);
      vec3 Res = vec3(0);

      vec3 R = Dir - Intr->N * (2 * (Dir & Intr->N));
      for (INT i = 0; i < Lights.Size(); i++)
      {
        vec3 gg = Intr->P + L->L * TRESHOLD;
        DBL Att = Lights[i]->Shadow(gg, L);
        intr I;

        /* Shadows */
        ray Sh(Intr->P + L->L * THRESHOLD, L->L);
        if (Intersection(Sh, &I))
          L->Color *= 0.30;


        // diffuse
        DBL nl = Intr->N & L->L;
        if (nl > THRESHOLD)
          diff = diff + L->Color * nl * Att;

        // specular
        DBL rl = R & L->L;
        if (rl > THRESHOLD)
          specular = specular + L->Color * pow(rl, Intr->Shp->Mtl.Ph);
      }
      //vec3 Res = Intr->Shp->Color * Intr->Shp->Mtl.Ka + Intr->Shp->Mtl.Kd * Intr->Shp->Color * diff + 
      //  Intr->Shp->Mtl.Ks * specular;

      if (!Intr->add[4])
        Res = Intr->Shp->Mtl.Ka + Intr->Shp->Mtl.Kd * diff + Intr->Shp->Mtl.Ks * specular;
      else
        Res = GetKa(Intr->P + R * TRESHOLD) + Intr->Shp->Mtl.Kd * diff + Intr->Shp->Mtl.Ks * specular;

      //Res = Intr->Shp->Mtl.Ka + Intr->Shp->Mtl.Kd * diff + Intr->Shp->Mtl.Ks * specular;

      // Reflection
      DBL wr = Weight * Intr->Shp->Mtl.Kr;
      if (wr > 0.01)
      {
        ray RR(Intr->P + R * TRESHOLD, R);
      
        Res += Trace(RR, Media, wr) * Intr->Shp->Mtl.Kr; 
      }

      // Transparecy
      //DBL cs = Dir & Intr->N;
      //DBL n = Intr->Shp->M.RefractionCoef / Media.RefractionCoef, coef = 1 - (1 - cs * cs) * n * n;
      //vec3 T = (Dir - Intr->N * (Dir & Intr->N)) * n - Intr->N * sqrt(coef);
      //
      //ray RT(Intr->P + T * TRESHOLD, T);
      //
      //Res += Trace(RT, Media); // Incorrect ~media~
      

      return Res;
    } /* End of 'Shade' function */

    BOOL ShadowCast( intr *Intr, vec3 LPos )
    {
      ray A(Intr->P + LPos * 0.0001, LPos);
      if (Intersection(A, Intr))
        return TRUE;

      return FALSE;
    }

    /* Trace function.
     * ARGUMENTS:
     *   - ray to trace:
     *       ray &R;
     *   - environment to trace:
     *       envi &Media;
     *   - envi weight:
     *       DBL Weight;
     * RETURNS: (vec3) traced color
     */
    vec3 Trace( ray &R, envi &Media, DBL Weight = 1.0 )
    {
      vec3 color = vec3(0);
      intr Intr;
      //envi Air();

      if (CurRec < MaxRec)
      {
        CurRec++;
        if (Intersection(R, &Intr))
        {
          light_info L;
      
          //if (!Intr.IsN)
          //  Intr.Shp->GetNormal(&Intr);
          if (!Intr.IsP)
          {
            Intr.IsP = TRUE;
            Intr.P = R(Intr.T);
          }

          color += Shade(R.Dir, Media, &Intr, &L);
          //vec3 L = vec3(1).Normalizing();
          //DBL nl = Intr.N & L;
          //ray Sh(R(Intr.T) + L.L * 0.01, L.L);
          //                                      // EMERGENCY USE ONLY
          //color = vec3(0.30, 0.47, 0.8) * nl;
          //
          //if (Intersection(Sh, &Intr))
          //  color *= 0.3;
        }
        CurRec--;
      }

      return color;
    } /* End of 'Trace' function */
  }; /* End of 'scene' class */
} /* End of 'nirt' namespace */

#endif // __rtdef_h_

/* END OF 'rt.h' FILE */