/* FILE NAME  : def.h
 * PROGRAMMER : ND4
 * LAST UPDATE: 01.08.2021
 * PURPOSE    : Default header.
 */

#ifndef __def_h_
#define __def_h_

#include <iostream>
#include <cassert>

#ifndef WIN32
#define WIN32
#include <commondf.h>
#undef WIN32
#else
#include <commondf.h>
#endif /* WIN32 */

#include "mth/mth.h"

#include "rt/frame/frame.h"

#include "stock.h"

//#pragma comment(lib, "opengl32")

//#define GLEW_STATIC
//#include <glew.h>
//
//#include <wglew.h>
//#include <wglext.h>

//#pragma comment(lib, "src/lib/ALut")
//#pragma comment(lib, "src/lib/openal32")

//#include "al/al.h" 
//#include "al/alc.h" 
//#include "al/alut.h" 

#define TRESHOLD 0.000001

typedef float FLT;
typedef long long INT64;

namespace mth
{
  template<typename Type> class vec2;
  template<typename Type> class vec3;
  template<typename Type> class vec4;
  template<typename Type> class matr;
  template<typename Type> class camera;
  template<typename Type> class ray;
}

namespace nirt
{
  typedef mth::matr<FLT> matr;
  typedef mth::vec2<FLT> vec2;
  typedef mth::vec3<FLT> vec3;
  typedef mth::vec4<FLT> vec4;
  typedef mth::ray<FLT> ray;
  typedef mth::camera<FLT> camera;
}

/* Debug memory allocation support */ 
#ifndef NDEBUG 
# define _CRTDBG_MAP_ALLOC
# include  <crtdbg.h>
# define SetDbgMemHooks() \
  _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
  _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))

static class __Dummy 
{ 
public: 
  /* Class constructor */
  __Dummy( VOID ) 
  { 
    SetDbgMemHooks(); 
  } /* End of '__Dummy' constructor */
} __ooppss;
#endif /* _DEBUG */ 

#ifdef _DEBUG 
# ifdef _CRTDBG_MAP_ALLOC 
#   define new new(_NORMAL_BLOCK, __FILE__, __LINE__) 
# endif /* _CRTDBG_MAP_ALLOC */ 
#endif /* _DEBUG */

#endif /* __def_h_ */
