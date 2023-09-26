/* FILE NAME   : main.cpp
 * PURPOSE     : Ray Tracing project.
 *               Main program file.
 * PROGRAMMER  : AU3
 * LAST UPDATE : 01.08.2021.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "nirt.h"

#include <thread>
#include <sstream>

using namespace nirt;

#pragma warning(disable : 28251) // WinMain warning

/* Ray tracing class */
class raytracer : public win, public timer
{
public:
  camera Cam; // Current camera
  frame Fr;   // Frame buffer
  scene Sc;   // Scene
  std::thread Tr[11];
  BOOL FlagUp = TRUE;
  INT Saved = 0;

  /* Default constructor */
  raytracer( VOID )
  {
  } /* End of 'anim' constructor */

  ~raytracer( VOID )
  {
  }

  /* Draw function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID Render( VOID )
  {
    //timer::Response();
    //Fr.Clear();

    auto _ThreadFunc([]( raytracer *RT, INT i )
      {
        //vec3 L = vec3(1).Normalizing();
    
        for (INT y = i * (RT->Cam.FrameH / 11); y < (i + 1) * (RT->Cam.FrameH / 11); y++)
          for (INT x = 0; x < RT->Cam.FrameW; x++)
          {
            ray R = RT->Cam.FrameRay(x + 0.5, y + 0.5);
    
            vec3 color = RT->Sc.Trace(R, RT->Sc.Air);
            RT->Fr.PutPixel(x, y, frame::toRGB(color[0], color[1], color[2]));
          }
      });
    
    for (INT i = 0; i < 11; i++)
        Tr[i] = std::thread(_ThreadFunc, this, i);
    for (INT i = 0; i < 11; i++)
      Tr[i].join();

    //for (INT y = 0; y < Fr.H; y++)
    //  for (INT x = 0; x < Fr.W; x++)
    //  {
    //    intr Intr;
    //    ray R = Cam.FrameRay(x + 0.5, y + 0.5);
    //
    //    vec3 color = Sc.Trace(R, Sc.Air);
    //    Fr.PutPixel(x, y, frame::toRGB(color[0], color[1], color[2]));
    //  }

    //if (FlagUp && Cam.Loc[1] <= 8)
    //{
    //  Cam.Move(Cam.Up / 10);
    //  if (Cam.Loc[1] >= 8)
    //    FlagUp = FALSE;
    //}
    //else if (!FlagUp)
    //{
    //  Cam.Move(Cam.Up / -10);
    //  if (Cam.Loc[1] <= 4)
    //    FlagUp = TRUE;
    //}

    Cam.Rotate(vec3(0, 1, 0), 2);
    // Redraw rectangle
    InvalidateRect(hWnd, nullptr, TRUE);
  } /* End of 'Draw' function */

  /* Initialization function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID Init( VOID ) override
  {
    //Fr.Resize(500, 300);
    //Cam.Resize(500, 300);
  } /* End of 'Init' function */

  /* Paint function.
   * ARGUMENTS:
   *   - device context:
   *       HDC hDC;
   * RETURNS: None.
   */
  VOID Paint( HDC hDC ) override
  {
    //CHAR Buf[50];
    //
    //sprintf(Buf, "X: %.3f Y: %.3f Z: %.3f", Cam.Loc[0], Cam.Loc[1], Cam.Loc[2]);

    Fr.Draw(hDC, (W - Fr.W) / 2, (H - Fr.H) / 2);
    //Fr.SaveTGA();
    //Saved++;
    //if (Saved >= 700)
    //  exit(0);
    //TextOut(hDC, 0, 0, Buf, 50); 
    
  } /* End of 'Paint' function */

  /* Timer function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID Timer( VOID ) override
  {
    Idle();
  } /* End of 'Timer' function */

  /* Resize window function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
   VOID Resize( VOID ) override
   {
     Rectangle(GetDC(hWnd), -1, -1, W, H);
     //Cam.Resize(7680, 4320);
     //Fr.Resize(7680, 4320);
     Cam.Resize(W, H);
     Fr.Resize(W, H);
     Render();
   } /* End of 'Resize' function */

   /* Idle function.
    * ARGUMENTS: None.
    * RETURNS: None.
    */
   VOID Idle( VOID ) override
   {
     Render();
   } /* End of 'Idle' function */
}; /* End of 'anim' class */


BOOL Load( raytracer *RT, const CHAR *FN )
{
  std::fstream f;
  stock<vec3> V;
  stock<INT> Ind;
  CHAR Buf[1000];

  f.open(FN, std::fstream::in);
  if (!f.is_open())
    return FALSE;

  while (f)
  {
    f.getline(Buf, sizeof(Buf));
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      vec3 V1;
      DBL x = 0, y = 0, z = 0;
      std::stringstream Str;

      Str << (Buf + 2);
      Str >> x >> y >> z;

      V1 = vec3(x, y, z);
      V.Add(V1);
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n = 0, n0 = 0, n1 = 0, nc;

      for (INT i = 1; Buf[i] != 0; i++)
      {
        if (isspace((UCHAR)Buf[i - 1]) && !isspace((UCHAR)Buf[i]))
        {
          std::stringstream Str1;

          Str1 << (Buf + i);

          Str1 >> nc;
          if (nc < 0)
            nc = V.Size() + nc;
          else
            nc--;

          if (n == 0)
            n0 = nc;
          else if (n == 1)
            n1 = nc;
          else
          {
            Ind.Add(n0);
            Ind.Add(n1);
            Ind.Add(nc);
            n1 = nc;
          }
          n++;
        }
      }
    }
  }

  f.close();

  for (INT i = 0; i < Ind.Size(); i += 3)
    RT->Sc.Shapes << new triangle(V[Ind[i]] * 0.13 + vec3(0, 8, 4), V[Ind[i + 1]] * 0.13 + vec3(0, 8, 4), V[Ind[i + 2]] * 0.13 + vec3(0, 8, 4), surface());


  return TRUE;
}


/* The main program function.
 * ARGUMENTS:
 *   - handle of application instance:
 *       HINSTANCE hInstance;
 *   - dummy handle of previous application instance (not used):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *       CHAR *CmdLine;
 *   - show window command parameter (see SW_***):
 *       INT CmdShow;
 * RETURNS:
 *   (INT) Error level for operation system (0 for success).
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT CmdShow )
{
  raytracer myW;

  myW.Sc.Shapes << new plane(vec3(0, 1, 0), 3, surface(vec3(0.05375, 0.05, 0.06625), vec3(0.18275, 0.17, 0.22525), vec3(0.332741, 0.328634, 0.346435), 38.4, 0.1));

  //surface MtlsV[16];
  //
  //MtlsV[0] =  surface(vec3(0.0, 0.0, 0.0),              vec3(0.01, 0.01, 0.01),           vec3(0.5, 0.5, 0.5),                 32,       0.50, 0.5);
  //MtlsV[1] =  surface(vec3(0.329412,0.223529,0.027451), vec3(0.780392,0.568627,0.113725), vec3(0.992157,0.941176,0.807843),    27.8974,  0.99, 0.5);
  //MtlsV[2] =  surface(vec3(0.2125,0.1275,0.054),        vec3(0.714,0.4284,0.18144),       vec3(0.393548,0.271906,0.166721),    25.6,     0.30, 0.5);
  //MtlsV[3] =  surface(vec3(0.25, 0.25, 0.25),           vec3(0.4, 0.4, 0.4),              vec3(0.774597, 0.774597, 0.774597),  76.8,     0.77, 0.5);
  //MtlsV[4] =  surface(vec3(0.19125,0.0735,0.0225),      vec3(0.7038,0.27048,0.0828),      vec3(0.256777,0.137622,0.086014),    12.8,     0.15, 0.5);
  //MtlsV[5] =  surface(vec3(0.24725,0.1995,0.0745),      vec3(0.75164,0.60648,0.22648),    vec3(0.628281,0.555802,0.366065),    51.2,     0.44, 0.5);
  //MtlsV[6] =  surface(vec3(0.10588,0.058824,0.113725),  vec3(0.427451,0.470588,0.541176), vec3(0.3333,0.3333,0.521569),        9.84615,  0.40, 0.5);
  //MtlsV[7] =  surface(vec3(0.19225,0.19225,0.19225),    vec3(0.50754,0.50754,0.50754),    vec3(0.508273,0.508273,0.508273),    51.2,     0.70, 0.5);
  //MtlsV[8] =  surface(vec3(0.23125,0.23125,0.23125),    vec3(0.2775,0.2775,0.2775),       vec3(0.773911,0.773911,0.773911),    89.6,     0.90, 0.5);
  //MtlsV[9] =  surface(vec3(0.1, 0.18725, 0.1745),       vec3(0.396, 0.74151, 0.69102),    vec3(0.297254, 0.30829, 0.306678),   12.8,     0.30, 0.5);
  //MtlsV[10] = surface(vec3(0.1745, 0.01175, 0.01175),   vec3(0.61424, 0.04136, 0.04136),  vec3(0.727811, 0.626959, 0.626959),  76.8,     0.68, 0.5);
  //MtlsV[11] = surface(vec3(0.24725, 0.2245, 0.0645),    vec3(0.34615, 0.3143, 0.0903),    vec3(0.797357, 0.723991, 0.208006),  83.2,     0.60, 0.5);
  //MtlsV[12] = surface(vec3(0.25, 0.148, 0.06475),       vec3(0.4, 0.2368, 0.1036),        vec3(0.774597, 0.458561, 0.200621),  76.8,     0.50, 0.5);
  //MtlsV[13] = surface(vec3(0.2295, 0.08825, 0.0275),    vec3(0.5508, 0.2118, 0.066),      vec3(0.580594, 0.223257, 0.0695701), 51.2,     0.35, 0.5);
  //MtlsV[14] = surface(vec3(0.135, 0.2225, 0.1575),      vec3(0.135, 0.2225, 0.1575),      vec3(0.316228, 0.316228, 0.316228),  12.8,     0.31, 0.5);
  //MtlsV[15] = surface(vec3(0.05375, 0.05, 0.06625),     vec3(0.18275, 0.17, 0.22525),     vec3(0.332741, 0.328634, 0.346435),  38.4,     0.33, 0.5);
  //
  //for (INT i = 0; i < 4; i++)
  //  for (INT j = 0; j < 4; j++)
  //    myW.Sc.Shapes << new sphere(0.5, vec3(j, 3.5 + i, 4), MtlsV[i * 4 + j]);
  //myW.Cam.SetLocAtUp(vec3(0, 6, -4), vec3(0, 3, 4), vec3(0, 1, 0));

  //myW.Sc.Shapes << new box(vec3(2, 4, 2), vec3(3, 5, 4), surface(vec3(0.25, 0.148, 0.06475), vec3(0.4, 0.2368, 0.1036), vec3(0.774597, 0.458561, 0.200621), 76.8, 0.3));

  myW.Sc.Shapes << new sphere(1, vec3(0, 5, 4), surface(vec3(0.25, 0.148, 0.06475), vec3(0.4, 0.2368, 0.1036), vec3(0.774597, 0.458561, 0.200621), 76.8, 0.3));
  myW.Sc.Shapes << new sphere(1, vec3(3, 4, 4), surface(vec3(0.1986, 0, 0), vec3(0.5922, 0.0166, 0), vec3(0.5974, 0.2084, 0.2084), 100.22, 0.2, 0.9));
  //myW.Sc.Shapes << new sphere(1, vec3(-3, 4, 4), surface(vec3(0.3, 0.3, 0.3), vec3(0.2, 0.2, 0.2), vec3(0.94597, 0.94597, 0.94597), 76.8, 0.3));
  //myW.Sc.Shapes << new sphere(1, vec3(-3, 6, 4), surface(vec3(0.25, 0.20725, 0.20725), vec3(0.5, 0.429, 0.429), vec3(0.156648, 0.156648, 0.156648), 100, 0.3));
  myW.Sc.Shapes << new sphere(3, vec3(6, 6, 15), surface(vec3(0.10588,0.058824,0.113725), vec3(0.427451,0.470588,0.541176), vec3(0.3333,0.3333,0.521569), 10, 0.7));
  //Load(&myW, "cow.obj");

  
  myW.Sc.Lights << new point(1, 30, vec3(12, 8, 1), vec3(0.13, 0.57, 0.7));
  myW.Sc.Lights << new point(1, 30, vec3(2, 20, 4), vec3(0, 1, 0));
  myW.Sc.Lights << new point(1, 30, vec3(4, 10, 4), vec3(0.635, 1, 0));

  //myW.Sc.Shapes << new triangle(vec3(0, 5, 0), vec3(1, 5, 0), vec3(1, 6, 1), surface());

  myW.Sc.Lights << new point(1, 20, vec3(1, 7, 2), vec3(0.5, 0, 1));
  myW.Cam.SetLocAtUp(vec3(8, 6, 4), vec3(0, 5, 4), vec3(0, 1, 0));
  



  myW.Run();

  return 30;
} /* End of 'WinMain' function */

/* END OF 'main.cpp' FILE */