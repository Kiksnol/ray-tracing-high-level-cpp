/* FILE NAME  : mth_vec3.h
 * PROGRAMMER : ND4
 * LAST UPDATE: 20.07.2021
 * PURPOSE    : Default math preferences
 */

#ifndef __mth_vec3_h_
#define __mth_vec3_h_

#include "mthdef.h"

/* Math namespace */
namespace mth
{
  /* 3D vector class */
  template<typename Type>
  class vec3
  {
  private:
    Type X, Y, Z;
  public:
    /* Default constructor. */
    vec3( VOID ) : X(0), Y(0), Z(0)
    {
    } /* End of 'vec3' constructor */

    /* Constructor by 1 value.
     * ARGUMENTS:
     *   - value to equal:
     *       const Type Val;
     */
    explicit vec3( const Type Val ) : X(Val), Y(Val), Z(Val)
    {
    } /* End of 'vec3' constructor */

    /* Constructor by 3 value.
     * ARGUMENTS:
     *   - value x:
     *       const Type ValX;
     *   - value y:
     *       const Type ValY;
     *   - value z:
     *       const Type ValZ;
     */
    vec3( const Type ValX, const Type ValY, const Type ValZ ) : 
      X(ValX), Y(ValY), Z(ValZ)
    {
    } /* End of 'vec3' constructor */

    /* Vector length operator !
     * ARGUMENTS: None.
     * RETURNS: (DBL) vector length
     */
    DBL operator ! ( VOID )
    {
      return sqrt(X * X + Y * Y + Z * Z);
    } /* End of 'operator !' function */

    /* Vector add operator +
     * ARGUMENTS:
     *   - vector to add:
     *       const vec3 &V;
     * RETURNS: (vec3) result vector
     */
    vec3 operator + ( const vec3 &V ) const
    {
      return vec3(V.X + this->X, V.Y + this->Y, V.Z + this->Z);
    } /* End of 'operator +' function */

    /* Negative vector operator - (prefix)
     * ARGUMENTS: None.
     * RETURNS: (vec3) result vector
     */
    vec3 operator - ( VOID )
    {
      return vec3(-X, -Y, -Z);
    } /* End of 'operator -' function */

    /* Vector substraction operator -
     * ARGUMENTS:
     *   - vector to substract:
     *       const vec3 &V;
     * RETURNS: (vec3) result vector
     */
    vec3 operator - ( const vec3 &V ) const
    {
      return vec3(X - V.X, Y - V.Y, Z - V.Z);
    } /* End of 'operator -' function */

    /* Vector add & equal operator += 
     * ARGUMENTS: 
     *   - vec3 to add & equal:
     *       const vec3 &V;
     * RETURNS: (vec3) this pointer;
     */
    vec3 operator += ( const vec3 &V )
    {
      this->X += V.X;
      this->Y += V.Y;
      this->Z += V.Z;

      return *this;
    } /* End of 'operator +=' function */

    /* Vector substract & equal operator +=
     * ARGUMENTS:
     *   - vec3 to substract & equal:
     *       const vec3 &V;
     * RETURNS: (vec3) this pointer;
     */
    vec3 operator -= ( const vec3 &V )
    {
      this->X -= V.X;
      this->Y -= V.Y;
      this->Z -= V.Z;

      return *this;
    } /* End of 'operator -=' function */

    /* Multiply vectors by components operator * 
     * ARGUMENTS:
     *   - vec3 to myltiply:
     *       const vec3 &V;
     * RETURNS: (vec3) result vector;
     */
    vec3 operator * ( const vec3 &V )
    {
      return vec3(X * V.X, Y * V.Y, Z * V.Z);
    } /* End of 'operator *' function  */

    /* Vector multiply & equal operator +=
     * ARGUMENTS:
     *   - vec3 to multiply & equal:
     *       const vec3 &V;
     * RETURNS: (vec3) this pointer;
     */
    vec3 operator *= ( const vec3 &V )
    {
      this->X *= V.X;
      this->Y *= V.Y;
      this->Z *= V.Z;

      return *this;
    } /* End of 'operator *=' function */

    /* Multiply vector by number function
     * ARGUMENTS:
     *   - number to multiply:
     *       const Type N;
     * RETURNS: (vec3) result vector
     */
    vec3 operator * ( const Type N ) const
    {
      return vec3(X * N, Y * N, Z * N);
    } /* End of 'operator *' function */

    /* Multiply & equal vector by number function.
     * ARGUMENTS:
     *   - number to multiply & equal:
     *       const Type N;
     * RETURNS: (vec3) this pointer
     */
    vec3 operator *= ( const Type N )
    {
      this->X *= N;
      this->Y *= N;
      this->Z *= N;

      return *this;
    } /* End of 'operator *=' function */

    /* Divide vector by num function.
     * ARGUMENTS:
     *   - number to divide:
     *       const Type N;
     * RETURNS: (vec3) result vector
     */
    vec3 operator / ( const Type N )
    {
      return vec3(X / N, Y / N, Z / N);
    } /* End of 'operator /' function */

    /* Divide & equal vector by number function.
     * ARGUMENTS:
     *   - number to divide & equal:
     *       const Type N;
     * RETURNS: (vec3) this pointer
     */
    vec3 operator /= ( const Type N )
    {
      this->X /= N;
      this->Y /= N;
      this->Z /= N;

      return *this;
    } /* End of 'operator /=' function */

    /* Dot vectors product function.
     * ARGUMENTS:
     *   - vec3 to dot:
     *       const vec3 &V;
     * RETURNS: (Type) dot product.
     */
    Type operator & ( const vec3 &V )
    {
      return X * V.X + Y * V.Y + Z * V.Z;
    } /* End of 'operator &' function */

    /* Cross vectors product function.
     * ARGUMENTS:
     *   - vec3 to cross:
     *       const vec3 &V;
     * RETURNS: (vec3) cross product.
     */
    vec3 operator % ( const vec3 &V )
    {
      return vec3(Y * V.Z - Z * V.Y,
                  Z * V.X - X * V.Z,
                  X * V.Y - Y * V.X);
    } /* End of 'operator %' function */

    /* Normalize this vector function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Normalize( VOID )
    {
      try
      {
        *this /= !(*this);
      } catch (...)
      {
      }
    } /* End of 'Normalize' function */

    /* Get this vector normalizing function
     * ARGUMENTS: None.
     * RETURNS: (vec3) this normalizing vector
     */
    vec3 Normalizing( VOID )
    {
      if (!(*this) != 0)
        return *this / !(*this);
      else
        return vec3(0);
    } /* End of 'Normalizing' function */

    /* Sqr of vector length function.
     * ARGUMENTS: None.
     * RETURNS: (Type) this length ^ 2
     */
    Type Length2( VOID )
    {
      return X * X + Y * Y + Z * Z;
    } /* End of 'Length2' function */

    /* Get distance between this vector and given function
     * ARGUMENTS:
     *   - vector to get distance:
     *       const vec3 &P;
     * RETURNS: (DBL) distance
     */
    DBL Distance( const vec3 &P ) const
    {
      return sqrt((X - P.X) * (X - P.X) + (Y - P.Y) * (Y - P.X) + (Z - P.Z) * (Z - P.Z));
    } /* End of 'Distance' function */

    /* Zero vector funciton.
     * ARGUMENTS: None.
     * RETURNS: (vec3) zero vector
     */
    vec3 Zero( VOID ) const
    {
      return vec3(0);
    } /* End of 'Zero' function */

    /* Index operator function (const)
     * ARGUMENTS:
     *   - index:
     *       INT i;
     * RETURNS (Type) vector number by index
     */
    Type operator [] ( INT i ) const
    {
      switch (i)
      {
      case 0:
        return this->X;
      case 1:
        return this->Y;
      case 2:
        return this->Z;
      default:
        if (i < 0)
          return this->X;
        else
          return this->Z;
      }
    } /* End of 'operator [] function */

    /* Index operator function (lvalue)
     * ARGUMENTS:
     *   - index:
     *       INT i;
     * RETURNS (Type) vector number by index
     */
    Type & operator [] ( INT i )
    {
      switch (i)
      {
      case 0:
        return this->X;
      case 1:
        return this->Y;
      case 2:
        return this->Z;
      default:
        if (i < 0)
          return this->X;
        else
          return this->Z;
      }
    } /* End of 'operator [] function */

    /* vec3 --> Type * function
     * ARGUMENTS: None.
     * RETURNS: (Type *) pointer to this->X
     */
    operator Type * ( VOID )
    {
      return &this->X;
    } /* End of 'operator Type *' function */

    /* Ostream rewrite to output vec3.
     * ARGUMENTS:
     *   - ostream to output:
     *       std::ostream &C;
     *   - vector to output:
     *       vec3 &V;
     * RETURNS: (ostream &) result ostream
     */
    friend std::ostream & operator << ( std::ostream &C, vec3 &V )
    {
      C << "{";
      C << V.X << ", ";
      C << V.Y << ", ";
      C << V.Z << "}";

      return C;
    } /* End of 'operator <<' function */

    /* Minimal vector */
    VOID Min( const vec3 &V2 )
    {
      *this = vec3(X > V2.X ? V2.X : X,
                  Y > V2.Y ? V2.Y : Y,
                  Z > V2.Z ? V2.Z : Z);
    } /* End of 'Min' function */

    /* Maximal vector */
    VOID Max( const vec3 &V2 )
    {
      *this = vec3(X < V2.X ? V2.X : X,
                  Y < V2.Y ? V2.Y : Y,
                  Z < V2.Z ? V2.Z : Z);
    } /* End of 'Max' function */

    /* Matrix friend */
    template <typename Type1>
    friend class matr;
  }; /* End of 'vec3' class */

  //typedef vec3<FLT> vec3;            /* Double vector */
} /* End of 'mth' namespace */

#endif /* __mth_vec3_h_*/

/* END OF 'mth_vec3.h' FILE */