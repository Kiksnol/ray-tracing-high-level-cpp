/* FILE NAME  : mth_vec2.h
 * PROGRAMMER : ND4
 * LAST UPDATE: 01.08.2021
 * PURPOSE    : Default math preferences
 */

#ifndef __mth_vec2_h_
#define __mth_vec2_h_

#include "mthdef.h"

/* Math support namespace */
namespace mth
{
  /* Vec2 handle class */
  template <typename Type>
  class vec2
  {
  private:
    Type X, Y;
  public:
    /* Vector construction function.
     * ARGUMENTS:
     *   - None.
    */
    vec2( VOID ) : X(0), Y(0)
    {
    } /* End of 'vec2 constructor' function */

    /* Vector construction function.
     * ARGUMENTS:
     *   - 2 coords:
     *       Type A, B;
    */
    vec2( Type A, Type B ) : X(A), Y(B)
    {
    } /* End of 'vec2 constructor' function */

    /* Vector construction function.
     * ARGUMENTS:
     *   - 1 coord for all:
     *       Type A;
    */
    vec2( Type A ) : X(A), Y(A)
    {
    } /* End of 'vec2 constructor' function */

    /* Operator + redefinition function.
     * ARGUMENTS:
     *   - Vector to add:
     *       const vec2 &val;
     * RETURNS:
     *   (vec2) result vector;
    */
    vec2 operator +( const vec2 &val )
    {
      return vec2(X + val.X, Y + val.Y);
    } /* End of 'operator +' function */

    /* Operator - redefinition function.
     * ARGUMENTS:
     *   - Vector to sub:
     *       const vec2 &val;
     * RETURNS:
     *   (vec2) result vector;
    */
    vec2 operator -( const vec2 &val )
    {
      return vec2(X - val.X, Y - val.Y);
    } /* End of 'operator -' function */

    /* Operator & redefinition function.
     * ARGUMENTS:
     *   - Vector to dot:
     *       const vec2 &val;
     * RETURNS:
     *   (vec2) result vector;
    */
    Type operator &( const vec2 &val )
    {
      return X * val.X + Y * val.Y;
    } /* End of 'operator &' function */

    /* Operator - redefinition function. Negative.
     * ARGUMENTS:
     *   - None.
     * RETURNS:
     *   (vec2) result vector;
    */
    vec2 operator -( void )
    {
      return vec2(-X, -Y);
    } /* End of 'operator -' function */

    /* Operator ! redefinition function.
     * ARGUMENTS:
     *   - None.
     * RETURNS:
     *   (DBL) vector length;
    */
    DBL operator !( VOID )
    {
      return sqrt(X * X + Y * Y);
    } /* End of 'operator !' function */

    /* Operator * redefinition function.
     * ARGUMENTS:
     *   - Number to multiply:
     *       const Type N;
     * RETURNS:
     *   (vec2) result vector;
    */
    vec2 operator *( const Type N )
    {
      return vec2(X * N, Y * N);
    } /* End of 'operator *' function */

    /* Operator / redefinition function.
     * ARGUMENTS:
     *   - Number to divide:
     *       const Type N;
     * RETURNS:
     *   (vec2) result vector;
    */
    vec2 operator /( const Type N )
    {
      return vec2(X / N, Y / N);
    } /* End of 'operator /' function */

    /* Operator += redefinition function.
     * ARGUMENTS:
     *   - Vector to add:
     *       const vec2 &val;
     * RETURNS:
     *   (vec2) result vector;
    */
    vec2 operator +=( const vec2 &val )
    {
      X += val.X;
      Y += val.Y;

      return *this;
    } /* End of 'operator +=' function */

    /* Operator -= redefinition function.
     * ARGUMENTS:
     *   - Vector to sub:
     *       const vec2 &val;
     * RETURNS:
     *   (vec2) result vector;
    */
    vec2 operator -=( const vec2 &val )
    {
      X -= val.X;
      Y -= val.Y;

      return *this;
    } /* End of 'operator -=' function */

    /* Operator *= redefinition function.
     * ARGUMENTS:
     *   - Number to multiply:
     *       const Type N;
     * RETURNS:
     *   (vec2) result vector;
    */
    vec2 operator *=( const Type N )
    {
      X *= N;
      Y *= N;

      return *this;
    } /* End of 'operator *=' function */

    /* Operator /= redefinition function.
     * ARGUMENTS:
     *   - Number to divide:
     *       const Type N;
     * RETURNS:
     *   (vec2) result vector;
    */
    vec2 operator /=( const Type N )
    {
      X /= N;
      Y /= N;

      return *this;
    } /* End of 'operator /=' function */

    /* Squared length function.
     * ARGUMENTS:
     *   - None.
     * RETURNS:
     *   (Type) vector length;
    */
    Type Length2( VOID )
    {
      return X * X + Y * Y;
    } /* End of 'Length2' function */

    /* Distance finder function.
     * ARGUMENTS:
     *   - Vector to find dist:
     *       const vec2 &val;
     * RETURNS:
     *   (DBL) distance;
    */
    DBL Distance( const vec2 &val )
    {
      return sqrt((X - val.X) * (X - val.X) + (Y - val.Y) * (Y - val.Y));
    } /* End of 'Distance' function */

    /* Operator * redefinition function.
     * ARGUMENTS:
     *   - Vector to mul:
     *       const vec2 &val;
     * RETURNS:
     *   (vec2) result vector;
    */
    vec2 operator *( const vec2 &val )
    {
      return vec2(X * val.X, Y * val.Y);
    } /* End of 'operator *' function */

    /* Operator *= redefinition function.
     * ARGUMENTS:
     *   - Vector to mul:
     *       const vec2 &val;
     * RETURNS:
     *   (vec2) result vector;
    */
    vec2 operator *=( const vec2 &val )
    {
      X *= val.X;
      Y *= val.Y;

      return *this;
    } /* End of 'operator *=' function */

    /* Normalize function.
     * ARGUMENTS:
     *   - None.
     * RETURNS:
     *   None.
    */
    VOID Normalize( VOID )
    {
      *this /= !*this;
    } /* End of 'Normalize' function */

    /* Normalize function.
     * ARGUMENTS:
     *   - None.
     * RETURNS:
     *   (vec2 &) normalized vector.
    */
    vec2 & Normalizing( VOID )
    {
      return *this /= !*this;
    } /* End of 'Normalizing' function */

    /* Zero vector function.
     * ARGUMENTS:
     *   - None.
     * RETURNS:
     *   (vec2) zero vector.
    */
    vec2 Zero( VOID )
    {
      return vec2(0);
    } /* End of 'Zero' function */

    /* Operator [] redefinition function.
     * ARGUMENTS:
     *   - Element number:
     *       INT i;
     * RETURNS:
     *   (Type &) element.
    */
    Type & operator []( INT i )
    {
      switch(i)
      {
      case 0:
        return this->X;
      case 1:
        return this->Y;
      default:
        if (i < 0)
          return this->X;
        else
          return this->Y;
      }
    } /* End of 'operator []' function */

    /* Vector output function.
     * ARGUMENTS:
     *   - None.
     * RETURNS:
     *   None.
    */
    VOID Out( VOID )
    {
      std::cout << "<" << X << " " << Y << ">";
    } /* End of 'Out' function */

    /* Operator << redefinition function.
     * ARGUMENTS:
     *   - String to output:
     *       std::ostream &C;
     *   - Vector to output:
     *       vec2 &V;
     * RETURNS:
     *   (std::ostream &) string.
    */
    friend std::ostream & operator << ( std::ostream &C, vec2 &V )
    {
      C << "<";
      C << V[0] << " ";
      C << V[1] << ">";

      return C;
    } /* End of 'operator <<' function */

    template <typename Type1>
    friend class matr;
  }; /* End of 'vec2' class */
} /* End of 'mth' namespace */


#endif /* __mth_vec2_h_ */

/* END OF 'mth_vec2.h' FILE */
