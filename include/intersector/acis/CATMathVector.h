#ifndef CATMathVector_H
#define CATMathVector_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

class CATMath3x3Matrix;
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

#include "CATMathematics.h"
#include "CATMathPoint.h"
#include "CATMathInline.h"

 
#include "CATMathDef.h"

/**
 * Class representing a mathematical vector in dimension 3. 
 */ 
class ExportedByCATMathematics CATMathVector
{
 public:
//=============================================================================
//- Constructors
//============================================================================
/**
 * Constructs a (0,0,0) vector.
 */ 
  INLINE CATMathVector ();

/**
 * Constructs a CATMathVector from three coordinates.
 */
  INLINE CATMathVector (const double iX,
                  const double iY, const double iZ);

/**
 * Constructs a CATMathVector from an array of three coordinates.
 */
  INLINE CATMathVector (const double  iCoord[]);
 
/**
 * Copy constructor.
 */
  INLINE CATMathVector (const CATMathVector & iVectorToCopy);

//============================================================================ 
//- Get/Set
//============================================================================
/**
 * Retrieves the coordinates of <tt>this</tt> CATMathVector.
 */
  INLINE void GetCoord (double & ioX, double & ioY,
                        double & ioZ) const;

/**
 * Modifies the coordinates of <tt>this</tt> CATMathVector from 3 doubles.
 */
  INLINE void SetCoord (const double iX,
                        const double iY, const double iZ);

/**
 * Retrieves the coordinates of <tt>this</tt> CATMathVector in an array.
 */
  INLINE void GetCoord (double iCoord[]) const;
  
/**
 * Modifies the coordinates of <tt>this</tt> CATMathVector from an array of 3 doubles.
 */
  INLINE void SetCoord (const double iCoord[]);

/**
 * Returns the X coordinate of <tt>this</tt> CATMathVector.
 */
  INLINE double GetX () const;
  
/**
 * Modifies the X coordinate of <tt>this</tt> CATMathVector.
 */
  INLINE void SetX (const double iX);

/**
 * Returns the Y coordinate of <tt>this</tt> CATMathVector.
 */
  INLINE double GetY () const;
  
/**
 * Modifies the Y coordinate of <tt>this</tt> CATMathVector.
 */
  INLINE void SetY (const double iY);

/**
 * Returns the Z coordinate of <tt>this</tt> CATMathVector.
 */
  INLINE double GetZ () const;

  /**
 * Modifies the Z coordinate of <tt>this</tt> CATMathVector.
 */
  INLINE void SetZ (const double iZ);

/**
 * Retrieves <tt>this</tt> CATMathVector, expressed in its spherical coordinates.
 * <br><tt>ioLongitudeAngle</tt> and <tt>ioLatitudeAngle</tt> 
 * are expressed in radians.
 */
  void GetSphericalCoord(double & ioRadius, CATAngle & ioLongitudeAngle,
                         CATAngle & ioLatitudeAngle) const;
  
/**
 * Modifies <tt>this</tt> CATMathVector with its spherical coordinates.
 * <br><tt>iLongitudeAngle</tt> and <tt>iLatitudeAngle</tt>
 *  are expressed in radians.
 */
  void SetSphericalCoord(const double  iRadius, const CATAngle iLongitudeAngle, 
						const CATAngle  iLatitudeAngle);

/**
 * Retrieves of <tt>this</tt> CATMathVector, expressed in its cylindrical coordinates.
 * <br><tt>oAngle</tt> is expressed in radians.
 */
  void GetCylindricalCoord(double & ioRadius, CATAngle & ioAngle,
                           double & ioHeight) const;

/**
 * Modifies <tt>this</tt> CATMathVector with its cylindrical coordinates.
 * <br><tt>iAngle</tt> is expressed in radians.
 */
  void SetCylindricalCoord(const double iRadius, const CATAngle iAngle,
			   const double iHeight);

//============================================================================
//- Norm
//============================================================================

/** 
 * Normalizes <tt>this</tt> CATMathVector.
 * </br>Simply returns if <tt>this</tt> is null.
  */
  void Normalize ();
/**
 * Returns the euclidean norm of <tt>this</tt> CATMathVector.
 */
  double Norm () const;

/**
 * Returns the square of the euclidean norm of <tt>this</tt> CATMathVector.
 */
  double SquareNorm () const;

//============================================================================
//- Angle To
//============================================================================

/**
 * Returns the angle (between 0 and CATPI radians) with another CATMathVector.
 * <br> Returns <tt>0</tt> if the vector is null.
 */
  CATAngle GetAngleTo (const CATMathVector & iOtherVector) const; 

/**
 * Returns the signed angle (between 0 and CAT2PI radians), with another CATMathVector,
 *  oriented by a reference vector.
 * <br> Returns <tt>0</tt> if the vector is null.
 */
  CATAngle GetAngleTo (const CATMathVector & iOtherVector,
                    const CATMathVector & iRefVector) const;

//============================================================================
//- Test for parallel and orthogonal vectors (with a numerical tolerence).
//============================================================================
/**
 * Returns the diagnosis of parallelism.
 * <br>The method uses the numerical
 * tolerance. For a user tolerance, use the <tt>GetAngleTo</tt> method.
 * @return 
 * <dl>
 * <dt><tt>TRUE</tt>        <dd>if they are parallel or one vector is null.
 * <dt><tt>FALSE</tt>        <dd>otherwise.
 * </dl>
 */
  CATBoolean IsParallel(const CATMathVector & iOtherVector) const;

/**
 * Returns the diagnosis of orthogonality.
  * <br>The method uses the numerical
 * tolerance. For a user tolerance, use the <tt>GetAngleTo</tt> method.
 * @return 
 * <dl>
 * <dt><tt>TRUE</tt>        <dd>if they are orthogonal or one vector is null.
 * <dt><tt>FALSE</tt>        <dd>otherwise.
 * </dl>
 */
  CATBoolean IsOrthogonal(const CATMathVector & iOtherVector) const;

/**
 * Retrieves the orthogonal decomposition of a CATMathVector related to 
 * a reference vector.
 */
  void OrthoComponents(const CATMathVector & iRefVector,
       CATMathVector & ioParallelComponent, CATMathVector & ioNormalComponent) const;


//============================================================================
//- Overloaded Operators
//============================================================================
/**
 * Defines the addition of two CATMAthVectors.
 * @param iVector1
 * The CATMathVector of <tt>(u1,u2,u3)</tt> coordinates.
 * @param iVector2
 * The CATMathVector of <tt>(v1,v2,v3)</tt> coordinates.
 * @return
 * The CATMathVector of <tt>(u1+v1,u2+v2,u3+v3</tt>) coordinates.
 */
  INLINE friend ExportedByCATMathematics CATMathVector operator +
    (const CATMathVector & iVector1, const CATMathVector & iVector2);

/**
 * Translates a CATMathPoint by a CATMathVector.
 * @param iPoint
 * The CATMathPoint of <tt>(p1,p2,p3)</tt> coordinates.
 * @param iVector
 * The CATMathVector of <tt>(u1,u2,u3)</tt> coordinates.
 * @return 
 * The CATMathPoint of <tt>(p1+u1,p2+u2,p3+u3)</tt> coordinates.
 */ 
  INLINE friend ExportedByCATMathematics CATMathPoint operator +
    (const CATMathPoint & iPoint, const CATMathVector & iVector);

/**
 * Modifies a CATMathPoint by using a tranlation by a CATMathVector.
 * @param iPoint
 * The CATMathPoint of <tt>(p1,p2,p3)</tt> coordinates.
 * @param iVector
 * The CATMathVector of <tt>(u1,u2,u3)</tt> coordinates.
 * @return 
 * The CATMathPoint of <tt>(p1=p1+u1,p2=p2+u2,p3=p3+u3)</tt> coordinates.
 */  
  INLINE friend void operator +=
    (CATMathPoint & iPoint, const CATMathVector & iVector);

/**
 * Builds a CATMathVector as the difference of two CATMathPoints.
 * <br> Note that the iPoint1iPoint2 vector is given by iPoint2-iPoint1.
 * @param iPoint1
 * The CATMathPoint of <tt>(p1,p2,p3)</tt> coordinates.
 * @param iPoint2
 * The CATMathPoint of <tt>(q1,q2,q3)</tt> coordinates.
 * @return 
 * The CATMathVector of <tt>(p1-q1,p2-q2,p3-q3)</tt> coordinates.
 */
  INLINE friend ExportedByCATMathematics CATMathVector operator -
    (const CATMathPoint & iPoint1, const CATMathPoint & iPoint2);

/**
 * Translates a CATMathPoint by a CATMathVector.
 * @param iPoint
 * The CATMathPoint of <tt>(p1,p2,p3)</tt> coordinates.
 * @param iVector
 * The CATMathVector of <tt>(u1,u2,u3)</tt> coordinates.
 * @return 
 * The CATMathPoint of <tt>(p1-u1,p2-u2,p3-u3)</tt> coordinates.
 */ 
  INLINE friend ExportedByCATMathematics CATMathPoint operator -
    (const CATMathPoint & iPoint, const CATMathVector & iVector);

/**
 * Modifies a CATMathPoint by using a tranlation by a CATMathVector.
 * @param iPoint
 * The CATMathPoint of <tt>(p1,p2,p3)</tt> coordinates.
 * @param iVector
 * The CATMathVector of <tt>(u1,u2,u3)</tt> coordinates.
 * @return 
 * The CATMathPoint of <tt>(p1=p1-u1,p2=p2-u2,p3=p3-u3)</tt> coordinates.
 */
  INLINE friend void operator -=
    (CATMathPoint & iPoint, const CATMathVector & iVector);


/**
 * Defines the substraction of two CATMAthVectors.
 * @param iVector1
 * The CATMathVector of <tt>(u1,u2,u3)</tt> coordinates.
 * @param iVector2
 * The CATMathVector of <tt>(v1,v2,v3)</tt> coordinates.
 * @return
 * The CATMathVector of <tt>(u1-v1,u2-v2,u3-v3</tt>) coordinates.
 */
  INLINE friend ExportedByCATMathematics CATMathVector operator -
    (const CATMathVector & iVector1, const CATMathVector & iVector2);

/**
 * Defines the opposite of a CATMathVector.
 * @param iVector
 * The CATMathVector of <tt>(u1,u2,u3)</tt> coordinates.
 * @return
 * The CATMathVector of <tt>(-u1,-u2,-u3)</tt> coordinates.
 */
  INLINE friend ExportedByCATMathematics CATMathVector operator -
    (const CATMathVector & iVector);

/**
 * Defines the left scalar multiplication.
 * @param iScalar
 * The scalar.
 * @param iVector
 * The CATMathVector of <tt>(u1,u2,u3)</tt> coordinates.
 * @return 
 * The CATMathVector of <tt>(iScalar*u1,iScalar*u2,iScalar*u3)</tt>
 *  coordinates.
 */
  INLINE friend ExportedByCATMathematics CATMathVector operator *
    (const double iScalar, const CATMathVector & iVector);

/**
 * Defines the right scalar multiplication.
 * @param iVector
 * The CATMathVector of <tt>(u1,u2,u3)</tt> coordinates.
 * @param iScalar
 * The scalar.
 * @return 
 * The CATMathVector of <tt>(u1*iScalar,u2*iScalar,u3*iScalar)</tt>
 *  coordinates.
 */
  INLINE friend ExportedByCATMathematics CATMathVector operator *
    (const CATMathVector & iVector, const double iScalar);

/**
 * Modifies a CATMathPoint by using the right scalar multiplication.
 * @param iVector
 * The CATMathVector of <tt>(u1,u2,u3)</tt> coordinates.
 * @param iScalar
 * The scalar.
 * @return 
 * The CATMathVector of <tt>(u1=u1*iScalar,u2=u2*iScalar,u3=u3*iScalar)</tt>
 *  coordinates.
 */ 
  INLINE friend void operator *=
    (CATMathVector & iVector, const double iScalar);

/**
 * Defines the scalar division.
 * @param iVector
 * The CATMathVector of <tt>(u1,u2,u3)</tt> coordinates.
 * @param iScalar
 * The (not null) scalar.
 * @return 
 * The CATMathVector of <tt>(u1/iScalar,u2/iScalar,u3/iScalar)</tt>
 *  coordinates.
 */
  INLINE friend ExportedByCATMathematics CATMathVector operator /
    (const CATMathVector & iVector, const double iScalar);

/**
 * Modifies a CATMathPoint by using the scalar division.
 * @param iVector
 * The CATMathVector of <tt>(u1,u2,u3)</tt> coordinates.
 * @param iScalar
 * The (not null) scalar.
 * @return 
 * The CATMathVector of <tt>(u1=u1/iScalar,u2=u2/iScalar,u3=u3/iScalar)</tt>
 *  coordinates.
 */
  INLINE friend void operator /=
    (CATMathVector & iVector, const double iScalar);

/**
 * Defines the dot product of two CATMathVectors.
 * @param iVector1
 * The CATMathVector of <tt>(u1,u2,u3)</tt> coordinates.
 * @param iVector2
 * The CATMathVector of <tt>(v1,v2,v3)</tt> coordinates.
 * @return
 * <tt>u1*v1 + u2*v2 + u3*v3</tt>.
 */
  INLINE friend ExportedByCATMathematics double operator *
    (const CATMathVector & iVector1, const CATMathVector & iVector2);

/**
 * Defines the cross product of two CATMathVectors.
 * @param iVector1
 * The CATMathVector of <tt>(u1,u2,u3)</tt> coordinates.
 * @param iVector2
 * The CATMathVector of <tt>(v1,v2,v3)</tt> coordinates.
 * @return
 * The CATMathVector (u2*iv3-u3*v2, u3*iv1-u1*v3, u1*v2-u2*v1).
 */
  INLINE friend ExportedByCATMathematics CATMathVector operator ^
    (const CATMathVector & iVector1, const CATMathVector & iVector2);

/**
 * Dumps the coordinates of a CATMathVector.
 * <br>This writes the following line on the ostream:
 * <br><tt>( FirstCoord , SecondCoord , ThirdCoord )</tt>
 * @param iStream
 * A pointer to the output. If <tt>0L</tt>, the method dumps the 
 * coordinates on the <tt>cout</tt> output.
 */
    void Dump(ostream * iStream=0L) const;
/**
 * @nodoc
 * Use now the Dump() method.
 */
  friend ExportedByCATMathematics ostream& operator << (ostream& s,
						const CATMathVector & iVector);

/**
 * @nodoc
 * @deprecated V5R20 GetAngleTo
  * Use now the <tt>GetAngleTo</tt> method, in radian.
 *<br>
 * Returns the angle (between 0 and 180 degrees) with another CATMathVector.
 * <br> Returns <tt>0</tt> if the vector is null.
 */
 CATAngle AngleTo (const CATMathVector & iOtherVector) const; 

/**
 * @nodoc
 * @deprecated V5R20 GetAngleTo
 *  Use now the <tt>GetAngleTo</tt> method, in radian.
 *<br>
 * Returns the angle (in degree) with another CATMathVector,
 *  oriented by a reference vector.
 */
  CATAngle AngleTo (const CATMathVector & iOtherVector,
                    const CATMathVector & iRefVector) const;
/**
 * @nodoc
 * @deprecated V5R20.
 */
  friend ExportedByCATMathematics CATMath3x3Matrix operator %
    (const CATMathVector & iVector1, const CATMathVector & iVector2);

//======================================================================
// Internal data
//======================================================================
 protected:
  double _x, _y, _z;
};

//======================================================================
// INLINE IMPLEMENTATIONS
//======================================================================

INLINE CATMathVector::CATMathVector() { _x = 0.; _y = 0.; _z = 0.; }
 
INLINE CATMathVector::CATMathVector (const double iX, const double iY,
                                     const double iZ) {
  _x = iX; _y = iY; _z = iZ;
}

INLINE CATMathVector::CATMathVector (const double iXYZ[]) {
  if (iXYZ == 0) { _x = 0.; _y = 0.; _z = 0.; }
  else { _x = iXYZ[0]; _y = iXYZ[1]; _z = iXYZ[2]; }
}

INLINE CATMathVector::CATMathVector (const CATMathVector & iU) {
  _x = iU._x; _y = iU._y; _z = iU._z;
}
 
INLINE void CATMathVector::GetCoord (double & oX, double & oY, double & oZ) const { 
  oX = _x; oY = _y; oZ = _z;
}

INLINE void CATMathVector::GetCoord (double oXYZ[]) const { 
  oXYZ[0] = _x; oXYZ[1] = _y; oXYZ[2] = _z; 
}

INLINE double CATMathVector::GetX() const { return _x; }

INLINE double CATMathVector::GetY() const { return _y; }

INLINE double CATMathVector::GetZ() const { return _z; }

INLINE void CATMathVector::SetCoord (const double iX,
			             const double iY,
			             const double iZ) { 
  _x = iX; _y = iY; _z = iZ;
}

INLINE void CATMathVector::SetCoord (const double iXYZ[]) { 
  _x = iXYZ[0]; _y = iXYZ[1]; _z = iXYZ[2]; 
}

INLINE void CATMathVector::SetX (const double iX) { _x = iX; }

INLINE void CATMathVector::SetY (const double iY) { _y = iY; }

INLINE void CATMathVector::SetZ (const double iZ) { _z = iZ; }

INLINE double CATMathVector::Norm () const {return sqrt(_x*_x+_y*_y+_z*_z);}

INLINE double CATMathVector::SquareNorm () const {return _x*_x+_y*_y+_z*_z;}

INLINE CATMathVector operator +
                    (const CATMathVector & iU, const CATMathVector & iV) { 
  return CATMathVector (iU._x + iV._x, iU._y + iV._y, iU._z + iV._z);
} 

INLINE CATMathPoint operator +
                    (const CATMathPoint & iP, const CATMathVector & iV) { 
  return CATMathPoint (iP._x + iV._x, iP._y + iV._y, iP._z + iV._z);
}

INLINE void operator +=
                   (CATMathPoint & iP, const CATMathVector & iV) {
  iP._x += iV._x; 
  iP._y += iV._y;
  iP._z += iV._z;
}

INLINE CATMathVector operator -
                    (const CATMathPoint & iP, const CATMathPoint & iQ) { 
  return CATMathVector (iP._x - iQ._x, iP._y - iQ._y, iP._z - iQ._z);
}

INLINE CATMathPoint operator -
                   (const CATMathPoint & iP, const CATMathVector & iV) {
  return CATMathPoint (iP._x - iV._x, iP._y - iV._y, iP._z - iV._z);
}

INLINE void operator -=
                   (CATMathPoint & iP, const CATMathVector & iV) {
  iP._x -= iV._x; 
  iP._y -= iV._y;
  iP._z -= iV._z;
}

INLINE CATMathVector operator -
                    (const CATMathVector & iU, const CATMathVector & iV) {
  return CATMathVector (iU._x - iV._x, iU._y - iV._y, iU._z - iV._z);
}

INLINE CATMathVector operator -
                     (const CATMathVector & iU) {
  return CATMathVector (-iU._x, -iU._y , -iU._z);
}

INLINE CATMathVector operator *
                    (const double iScalar, const CATMathVector & iU) { 
  return CATMathVector (iScalar*iU._x, iScalar*iU._y, iScalar*iU._z); 
}

INLINE CATMathVector operator *
                     (const CATMathVector & iU, const double iScalar) {
  return CATMathVector (iScalar*iU._x, iScalar*iU._y, iScalar*iU._z);
}

INLINE void operator *=
    (CATMathVector & iU, const double iScalar) {
  iU._x *= iScalar;
  iU._y *= iScalar;
  iU._z *= iScalar;
} 

INLINE CATMathVector operator /
                     (const CATMathVector & iU, const double iScalar) {
  double Invert = 1./iScalar;
  return CATMathVector (iU._x*Invert, iU._y*Invert, iU._z*Invert);
}

INLINE void operator /=
    (CATMathVector & iU, const double iScalar) {
  double Invert = 1./iScalar;
  iU._x *= Invert;
  iU._y *= Invert;
  iU._z *= Invert;
} 

INLINE double operator *
              (const CATMathVector & iU, const CATMathVector & iV) {
  return (iU._x*iV._x + iU._y*iV._y + iU._z*iV._z);
}

INLINE CATMathVector operator ^
                    (const CATMathVector & iU, const CATMathVector & iV) {
  return CATMathVector (iU._y*iV._z-iU._z*iV._y, iU._z*iV._x-iU._x*iV._z,
			iU._x*iV._y-iU._y*iV._x);
}
#endif
