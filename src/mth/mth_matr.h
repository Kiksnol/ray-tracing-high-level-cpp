/* FILE NAME  : mthmatr.h
 * PROGRAMMER : ND4
 * LAST UPDATE: 20.07.2021
 * PURPOSE    : Default matrix functions
 */

#ifndef __mth_matr_h_
#define __mth_matr_h_

#include <cstring>

#include "mth_vec3.h"

/* Math namespace */
namespace mth
{
  template<typename Type>
  class matr
  {
  private:
    Type M[4][4];                  /* Matrix */
    mutable Type InvM[4][4];       /* Inverse matrix */
    mutable BOOL IsInvEv;          /* Inverse flag */
    mutable Type TransposeM[4][4]; /* Transpose matrix */
    mutable BOOL IsTransEnv;       /* Transpose flag */

    /* Determinant 3x3 matrix function.
     * ARGUMENTS:
     *   - matrix values:
     *       Type A[1..3][1..3];
     * RETURNS: (DBL) determinant
     */
    DBL Determ3x3( Type A11, Type A12, Type A13,
                   Type A21, Type A22, Type A23,
                   Type A31, Type A32, Type A33 )
    {
      return (Type)(A11 * A22 * A33) - (Type)(A11 * A23 * A32 - A12 * A21 * A33) + 
             (Type)A12 * A23 * A31 + (Type)(A13 * A21 * A32 - A13 * A22 * A31);
    } /* End of 'Determ3x3' function */

    /* Evaluate inverse matrix function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID EvalInvMatr( VOID )
    {
      DBL det = this->Determ();
      Type mtr[4][4] = {0};

      if (this->IsInvEv)
        return;

      if (det == 0)
        memcpy(this->InvM, matr::Identity().M, sizeof(this->InvM));

      /* build adjoint matrix */
      mtr[0][0] =
        Determ3x3(M[1][1], M[1][2], M[1][3],
          M[2][1], M[2][2], M[2][3],
          M[3][1], M[3][2], M[3][3]);
      mtr[1][0] =
        -Determ3x3(M[1][0], M[1][2], M[1][3],
          M[2][0], M[2][2], M[2][3],
          M[3][0], M[3][2], M[3][3]);
      mtr[2][0] =
        Determ3x3(M[1][0], M[1][1], M[1][3],
          M[2][0], M[2][1], M[2][3],
          M[3][0], M[3][1], M[3][3]);
      mtr[3][0] =
        -Determ3x3(M[1][0], M[1][1], M[1][2],
          M[2][0], M[2][1], M[2][2],
          M[3][0], M[3][1], M[3][2]);

      mtr[0][1] =
        -Determ3x3(M[0][1], M[0][2], M[0][3],
          M[2][1], M[2][2], M[2][3],
          M[3][1], M[3][2], M[3][3]);
      mtr[1][1] =
        Determ3x3(M[0][0], M[0][2], M[0][3],
          M[2][0], M[2][2], M[2][3],
          M[3][0], M[3][2], M[3][3]);
      mtr[2][1] =
        -Determ3x3(M[0][0], M[0][1], M[0][3],
          M[2][0], M[2][1], M[2][3],
          M[3][0], M[3][1], M[3][3]);
      mtr[3][1] =
        Determ3x3(M[0][0], M[0][1], M[0][2],
          M[2][0], M[2][1], M[2][2],
          M[3][0], M[3][1], M[3][2]);

      mtr[0][2] =
        Determ3x3(M[0][1], M[0][2], M[0][3],
          M[1][1], M[1][2], M[1][3],
          M[3][1], M[3][2], M[3][3]);
      mtr[1][2] =
        -Determ3x3(M[0][0], M[0][2], M[0][3],
          M[1][0], M[1][2], M[1][3],
          M[3][0], M[3][2], M[3][3]);
      mtr[2][2] =
        Determ3x3(M[0][0], M[0][1], M[0][3],
          M[1][0], M[1][1], M[1][3],
          M[3][0], M[3][1], M[3][3]);
      mtr[3][2] =
        -Determ3x3(M[0][0], M[0][1], M[0][2],
          M[1][0], M[1][1], M[1][2],
          M[3][0], M[3][1], M[3][2]);

      mtr[0][3] =
        -Determ3x3(M[0][1], M[0][2], M[0][3],
          M[1][1], M[1][2], M[1][3],
          M[2][1], M[2][2], M[2][3]);
      mtr[1][3] =
        Determ3x3(M[0][0], M[0][2], M[0][3],
          M[1][0], M[1][2], M[1][3],
          M[2][0], M[2][2], M[2][3]);
      mtr[2][3] =
        -Determ3x3(M[0][0], M[0][1], M[0][3],
          M[1][0], M[1][1], M[1][3],
          M[2][0], M[2][1], M[2][3]);
      mtr[3][3] =
        Determ3x3(M[0][0], M[0][1], M[0][2],
          M[1][0], M[1][1], M[1][2],
          M[2][0], M[2][1], M[2][2]);

      /* devide on determinator */
      mtr[0][0] /= det;
      mtr[1][0] /= det;
      mtr[2][0] /= det;
      mtr[3][0] /= det;

      mtr[0][1] /= det;
      mtr[1][1] /= det;
      mtr[2][1] /= det;
      mtr[3][1] /= det;

      mtr[0][2] /= det;
      mtr[1][2] /= det;
      mtr[2][2] /= det;
      mtr[3][2] /= det;

      mtr[0][3] /= det;
      mtr[1][3] /= det;
      mtr[2][3] /= det;
      mtr[3][3] /= det;

      this->IsInvEv = TRUE;
    } /* End of 'EvalInvMatr' function */

    /* Evaluate transpose matrix function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID EvalTransMatr( VOID )
    {
      if (this->IsTransEnv)
        return;
      for (INT i = 0; i < 4; i++)
        for (INT j = 0; j < 4; j++)
          TransposeM[i][j] = M[j][i];
      this->IsTransEnv = TRUE;
    } /* End of 'EvalTransMatr' function */
  public:
    /* Default constructor */
    matr( VOID ) : IsInvEv(FALSE), IsTransEnv(FALSE), M(), InvM(), TransposeM()
    {
    } /* End of 'matr' constructor */

    /* Constructor by array[4][4] */
    matr( const Type Matr[4][4] ) : IsInvEv(FALSE), IsTransEnv(FALSE)
    {
      memcpy(this->M, Matr, sizeof(this->M));
    } /* End of 'matr' constructor */

    /* Constructor by 16 values */
    matr( const Type a00, const Type a01, const Type a02, const Type a03,
          const Type a10, const Type a11, const Type a12, const Type a13,
          const Type a20, const Type a21, const Type a22, const Type a23,
          const Type a30, const Type a31, const Type a32, const Type a33) : IsInvEv(FALSE), IsTransEnv(FALSE)
    {
      M[0][0] = a00;
      M[0][1] = a01;
      M[0][2] = a02;
      M[0][3] = a03;

      M[1][0] = a10;
      M[1][1] = a11;
      M[1][2] = a12;
      M[1][3] = a13;

      M[2][0] = a20;
      M[2][1] = a21;
      M[2][2] = a22;
      M[2][3] = a23;

      M[3][0] = a30;
      M[3][1] = a31;
      M[3][2] = a32;
      M[3][3] = a33;

      ZeroMemory(InvM, sizeof(Type) * 16);
      ZeroMemory(TransposeM, sizeof(Type) * 16);
    } /* End of 'matr' constructor */

    /* Identity matrix function.
     * ARGUMENTS: None.
     * RETURNS: (matr) identity matrix
     */
    static matr Identity( VOID )
    {
      return matr(1, 0, 0, 0,
                  0, 1, 0, 0,
                  0, 0, 1, 0,
                  0, 0, 0, 1);
    } /* End of 'Identity' function */

    /* Transform this matrix to identity function.
     * ARGUMENTS: None.
     * RETURNS: (matr) *this.
     */
    matr toIdentity( VOID )
    {
      *this = matr(1, 0, 0, 0,
                   0, 1, 0, 0,
                   0, 0, 1, 0,
                   0, 0, 0, 1);
      return *this;
    } /* End of 'toIdentity' function */

    /* Inverse matrix function.
     * ARGUMENTS: None.
     * RETURNS: (matr) inversed matrix
     */
    matr Inverse( VOID )
    {
      this->EvalInvMatr();
      return this->InvM;
    } /* End of 'Inverse' matrix */

    /* Determinant of matrix function.
     * ARGUMENTS: None.
     * RETURNS: (DBL) determinant
     */
    DBL Determ( VOID )
    {
      return
        M[0][0] * Determ3x3(M[1][1], M[1][2], M[1][3],
                            M[2][1], M[2][2], M[2][3],
                            M[3][1], M[3][2], M[3][3]) - 
        M[0][1] * Determ3x3(M[1][0], M[1][2], M[1][3],
                            M[2][0], M[2][2], M[2][3],
                            M[3][0], M[3][2], M[3][3]) +
        M[0][2] * Determ3x3(M[1][0], M[1][1], M[1][3],
                            M[2][0], M[2][1], M[2][3],
                            M[3][0], M[3][1], M[3][3]) - 
        M[0][3] * Determ3x3(M[1][0], M[1][1], M[1][2],
                            M[2][0], M[2][1], M[2][2],
                            M[3][0], M[3][1], M[3][2]);
    } /* End of 'Determ' function */

    /* Translate matrix function.
     * ARGUMENTS:
     *   - vector to translate:
     *       const vec3 &T;
     * RETURNS: (matr) matrix translate
     */
    static matr Translate( const vec3<Type> &T )
    {
      return matr(1, 0, 0, 0,
                  0, 1, 0, 0,
                  0, 0, 1, 0,
                  T.X, T.Y, T.Z, 1);
    } /* End of 'Translate' function */

    /* Operator ! (determinant)
     * ARGUMENTS: None.
     * RETURNS: (DBL) determinant
     */
    DBL operator ! ( VOID ) const
    {
      return
        M[0][0] * Determ3x3(M[1][1], M[1][2], M[1][3],
                            M[2][1], M[2][2], M[2][3],
                            M[3][1], M[3][2], M[3][3]) -
        M[0][1] * Determ3x3(M[1][0], M[1][2], M[1][3],
                            M[2][0], M[2][2], M[2][3],
                            M[3][0], M[3][2], M[3][3]) +
        M[0][2] * Determ3x3(M[1][0], M[1][1], M[1][3],
                            M[2][0], M[2][1], M[2][3],
                            M[3][0], M[3][1], M[3][3]) -
        M[0][3] * Determ3x3(M[1][0], M[1][1], M[1][2],
                            M[2][0], M[2][1], M[2][2],
                            M[3][0], M[3][1], M[3][2]);
    } /* End of 'operator !' function */

    /* Transpose matrix function.
     * ARGUMENTS: None.
     * RETURNS: (matr) transposed matrix
     */
    matr Transpose( VOID )
    {
      EvalTransMatr();
      return TransposeM;
    } /* End of 'Transpose' function */

    /* Scale matrix function.
     * ARGUMENTS: 
     *   - vector to scale (vec3):
     *       const vec3 &S;
     * RETURNS: (matr) scaled matrix
     */
    static matr Scale( const vec3<Type> &S )
    {
      return matr(S.X, 0, 0, 0,
                  0, S.Y, 0, 0,
                  0, 0, S.Z, 0,
                  0, 0, 0, 1);
    } /* End of 'Scale' function */

    /* Transforming normal function.
     * ARGUMENTS:
     *   - vector normal:
     *       const vec3<Type> &N;
     * RETURNS: (vec3) transforming vector
     */
    vec3<Type> TransformNormal( const vec3<Type> &N ) const
    {
      EvalInvMatr();
      return vec3<Type>(N.X * InvM[0][0] + N.Y * InvM[0][1] + N.Z * InvM[0][2],
                        N.X * InvM[1][0] + N.Y * InvM[1][1] + N.Z * InvM[1][2],
                        N.X * InvM[2][0] + N.Y * InvM[2][1] + N.Z * InvM[2][2]);
    } /* End of 'TransformNormal' function */

    /* Multiply matrix by matrix function.
     * ARGUMENTS:
     *   - matrix to multiply:
     *       const matr &M1;
     * RETURNS: (matr) result matrix
     */
    matr operator * ( const matr &M1 )
    {
      matr r;

      for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
          for (int k = 0; k < 4; k++)
            r.M[i][j] += M[i][k] * M1.M[k][j];
      return r;
    } /* End of 'operator *' function */

    /* Multiply and equal matrix by matrix function.
     * ARGUMENTS:
     *   - matrix to multiply and equal:
     *       const matr &M1;
     * RETURNS: (matr) this pointer.
     */
    matr operator *= ( const matr &M1 )
    {
      matr r;

      for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
          for (int k = 0; k < 4; k++)
            r.M[i][j] += M[i][k] * M1.M[k][j];
      *this = r;
      return *this;
    } /* End of 'operator *=' function */

    /* Rotate vector by axe X function.
     * ARGUMENTS:
     *   - angle to rotate:
     *       DBL Angle;
     * RETURNS: (matr) result matrix
     */
    static matr RotateX( DBL AngleToDegrees )
    {
      DBL Rad = Degree2Radian(AngleToDegrees);
      DBL c = cos(Rad), s = sin(Rad);

      return matr(1, 0, 0, 0,
                  0, c, s, 0,
                  0, -s, c, 0,
                  0, 0, 0, 1);
    } /* End of 'RotateX' function */

    /* Rotate vector by axe Y function.
     * ARGUMENTS:
     *   - angle to rotate:
     *       DBL Angle;
     * RETURNS: (matr) result matrix
     */
    static matr RotateY( DBL AngleToDegrees )
    {
      DBL Rad = Degree2Radian(AngleToDegrees);
      DBL c = cos(Rad), s = sin(Rad);

      return matr(c, 0, -s, 0,
                  0, 1, 0, 0,
                  s, 0, c, 0,
                  0, 0, 0, 1);
    } /* End of 'RotateY' function */

    /* Rotate vector by axe Z function.
     * ARGUMENTS:
     *   - angle to rotate:
     *       DBL Angle;
     * RETURNS: (matr) result matrix
     */
    static matr RotateZ( DBL AngleToDegrees )
    {
      DBL Rad = Degree2Radian(AngleToDegrees);
      DBL c = cos(Rad), s = sin(Rad);

      return matr(c, s, 0, 0,
                  -s, c, 0, 0,
                  0, 0, 1, 0,
                  0, 0, 0, 1);
    } /* End of 'RotateZ' function */

    /* Rotate vector by vector function.
     * ARGUMENTS:
     *   - angle to rotate:
     *       DBL Angle;
     *   - vector to rotate:
     *       const vec3<Type> &V;
     * RETURNS: (matr) result matrix
     */
    static matr Rotate( DBL AngleToDegrees, vec3<Type> R )
    {
      DBL Rad = Degree2Radian(AngleToDegrees);
      vec3<Type> V = R.Normalizing();
      DBL c = cos(Rad), s = sin(Rad);

      return matr(c + V.X * V.X * (1 - c), V.X * V.Y * (1 - c) + V.Z * s, V.X * V.Z * (1 - c) - V.Y * s, 0,
                  V.X * V.Y * (1 - c) - V.Z * s, c + V.Y * V.Y * (1 - c), V.Y * V.Z * (1 - c) + V.X * s, 0,
                  V.Z * V.X * (1 - c) + V.Y * s, V.Y * V.Z * (1 - c) - V.X * s, c + V.Z * V.Z * (1 - c), 0,
                  0, 0, 0, 1);
    } /* End of 'Rotate' function */

    /* Transform point by matrix function.
     * ARGUMENTS:
     *   - vector to transform:
     *       const vec3<Type> &V;
     * RETURNS: (vec3<Type) result vector
     */
    vec3<Type> TransformPoint( const vec3<Type> &V ) const
    {
      return vec3<Type>(V.X * M[0][0] + V.Y * M[1][0] + V.Z * M[2][0] + M[3][0],
                        V.X * M[0][1] + V.Y * M[1][1] + V.Z * M[2][1] + M[3][1],
                        V.X * M[0][2] + V.Y * M[1][2] + V.Z * M[2][2] + M[3][2]);
    } /* End of 'TransformPoint' function */

    /* Transform vector by matrix function.
    * ARGUMENTS:
    *   - vector to transform:
    *       const vec3<Type> &V;
    * RETURNS: (vec3<Type) result vector
    */
    vec3<Type> TransformVector( const vec3<Type> &V ) const
    {
      return vec3<Type>(V.X * M[0][0] + V.Y * M[1][0] + V.Z * M[2][0],
                        V.X * M[0][1] + V.Y * M[1][1] + V.Z * M[2][1],
                        V.X * M[0][2] + V.Y * M[1][2] + V.Z * M[2][2]);
    } /* End of 'TransformVector' function */

    /* Multiplying vector from matrix function.
     * ARGUMENTS: 
     *   - vector to multiply:
     *       const vec3<Type> &V;
     * RETURNS: (vec3) result vector
     */
    vec3<Type> Transform4x4( const vec3<Type> &V ) const
    {
      FLT w = V.X * M[0][3] + V.Y * M[1][3] + V.Z * M[2][3] + M[3][3];

      return vec3<Type>((V.X * M[0][0] + V.Y * M[1][0] + V.Z * M[2][0] + M[3][0]) / w,
                        (V.X * M[0][1] + V.Y * M[1][1] + V.Z * M[2][1] + M[3][1]) / w,
                        (V.X * M[0][2] + V.Y * M[1][2] + V.Z * M[2][2] + M[3][2]) / w);
    } /* End of 'Transform4x4' function */

    /* Ostream rewrite to output vmatr.
     * ARGUMENTS:
     *   - ostream to output:
     *       std::ostream &C;
     *   - matrix to output:
     *       matr &M1;
     * RETURNS: (ostream &) result ostream
     */
    friend std::ostream & operator << ( std::ostream &C, matr &M1 )
    {
      C << "[";
      for (int i = 0; i < 3; i++)
        C << M1.M[0][i] << ", ";
      C << M1.M[0][3] << "]" << std::endl;

      C << "[";
      for (int i = 0; i < 3; i++)
        C << M1.M[1][i] << ", ";
      C << M1.M[1][3] << "]" << std::endl;

      C << "[";
      for (int i = 0; i < 3; i++)
        C << M1.M[2][i] << ", ";
      C << M1.M[2][3] << "]" << std::endl;
      
      C << "[";
      for (int i = 0; i < 3; i++)
        C << M1.M[3][i] << ", ";
      C << M1.M[3][3] << "]" << std::endl;

      return C;
    } /* End of 'operator <<' function */

    /* Operator type * */
    operator Type * ( VOID )
    {
      return this->M[0];
    } /* End of 'operator type *' function */

    /* Operator type * */
    operator const Type * ( VOID ) const
    {
      return this->M[0];
    } /* End of 'operator type *' function */

    /* Operator[]
     * ARGUMENTS:
     *   - index to access:
     *       INT i;
     * RETURNS: (type &) matrix element (lvalue)
     */
    Type & operator [] ( INT i )
    {
      switch (i)
      {
      case 0:
        return M[0][0];
      case 1:
        return M[0][1];
      case 2:
        return M[0][2];
      case 3:
        return M[0][3];
      case 4:
        return M[1][0];
      case 5:
        return M[1][1];
      case 6:
        return M[1][2];
      case 7:
        return M[1][3];
      case 8:
        return M[2][0];
      case 9:
        return M[2][1];
      case 10:
        return M[2][2];
      case 11:
        return M[2][3];
      case 12:
        return M[3][0];
      case 13:
        return M[3][1];
      case 14:
        return M[3][2];
      case 15:
        return M[3][3];
      default:
        if (i < 0)
          return M[0][0];
        else
          return M[3][3];
      }
    } /* End of 'operator[] function */

    /* View matrix function.
     * ARGUMENTS:
     *   - Position:
     *       const vec3<Type> &Loc;
     *   - Where we looking for:
     *       const vec3<Type> &At;
     *   - Direction to up:
     *       const vec3<Type> &Up1;
     * RETURNS: (matr) view matrix
     */
    static matr View( vec3<Type> &Loc, vec3<Type> &At, vec3<Type> &Up1 )
    {
      vec3<Type> D, U, R;

      D = (At - Loc).Normalizing();
      R = (D % Up1).Normalizing();
      U = R % D;

      return matr(R.X, U.X, -D.X, 0,
                  R.Y, U.Y, -D.Y, 0,
                  R.Z, U.Z, -D.Z, 0,
                  -(Loc & R), -(Loc & U), Loc & D, 1);
    } /* End of 'View' function */

    /* Frustum matrix function.
     * ARGUMENTS:
     *   - Screen factors:
     *       Left and Right:
     *          FLT L, R;
     *       Bottom and Top:
     *          FLT B, T;
     *       Near and Far:
     *          FLT N, F;
     * RETURNS: (matr) result matrix
     */
    static matr Frustum( FLT L, FLT R, FLT B, FLT T, FLT N, FLT F )
    {
      return matr(2 * N / (R - L), 0, 0, 0,
                  0, 2 * N / (T - B), 0, 0,
                  (R + L) / (R - L), (T + B) / (T - B), -(F + N) / (F - N), -1,
                  0, 0, -2 * N * F / (F - N), 0);
    } /* End of 'Frustum' function */

    /* Ortho projection matrix function.
     * ARGUMENTS:
     *   - Screen factors:
     *       Left and Right:
     *          FLT L, R;
     *       Bottom and Top:
     *          FLT B, T;
     *       Near and Far:
     *          FLT N, F;
     * RETURNS:
     *   (matr) viewer matrix.
     */
    static matr Ortho( FLT L, FLT R, FLT B, FLT T, FLT N, FLT F )
    {
      return matr(2 / (R - L),                 0,                             0,                0,
                     0,                           2 / (T - B),                   0,                0,
                     0,                           0,                            -2 / (F - N),      0,
                    -(R + L) / (R - L),          -(T + B) / (T - B),          -(N + F) / (F - N), 1);
    } /* End of 'Ortho' function */
  }; /* End of 'matr' class */

  //typedef matr<FLT> fmatr; /* Float matrix */
} /* End of 'mth' namespace */

#endif /* __mth_matr_h_ */


/* END OF 'mthmatr.h' FILE */