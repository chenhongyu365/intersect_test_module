#ifndef CATMathPoint_H
#define CATMathPoint_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

class CATMathVector;
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

#if (defined(_MSC_VER) && (_MSC_VER >= 1900))
#include <cmath>
#else
#include <math.h>
#endif

#include "CATMathematics.h"

#include "CATMathDef.h"
#include "CATMathInline.h"



/**
 * Class representing a mathematical cartesian point in dimension 3.
 *<br>
 * Mathematical points are mostly used as results of evaluation methods
 * on curves and surfaces.
 */
class ExportedByCATMathematics CATMathPoint
{
  public:
//----------------------------------------------------------  
//- Constructors
//----------------------------------------------------------
/** 
 * Constructs a CATMathPoint with <tt>(0,0,0)</tt> coordinates.
 */ 
    INLINE CATMathPoint ();
/**
 * Constructs a CATMathPoint from coordinates.
 */
    INLINE CATMathPoint (const double iX, const double iY,
                         const double iZ);
/**
 * Constructs a CATMathPoint from an array of 3 coordinates.
 */
    INLINE CATMathPoint (const double iCoord[]);
/**
 * Constructs a CATMathPoint as the barycenter of two CATMathPoints.
 * <br>Resulting point = <tt>(iA1*Point1 + iA2*Point2)/(iA1+iA2)</tt>.
 */
		/*
    CATMathPoint (const CATMathPoint & iPoint1,const CATMathPoint & iPoint2,
						const double iA1,const double iA2 );
						*/
/**
 * Copy constructor.
 */
    INLINE CATMathPoint (const CATMathPoint & iPointToCopy);

//----------------------------------------------------------  
//- Get/Set
//----------------------------------------------------------
/**
 * Retrieves the coordinates of <tt>this</tt> CATMathPoint.
 */
    INLINE void GetCoord (double & ioX, double & ioY,
                          double & ioZ) const;

/**
 * Modifies the coordinates of <tt>this</tt> CATMathPoint from 3 doubles.
 */
    INLINE void SetCoord (const double iX, const double iY,
                          const double iZ);

/**
 * Retrieves the coordinates of a CATMathPoint in an array of 3 doubles.
 */
    INLINE void GetCoord (double iCoord[]) const;

/**
 * Modifies the coordinates of <tt>this</tt> CATMathPoint from an array of 3 doubles.
 */
    INLINE void SetCoord (const double  iCoord[]); 

/**
 * Returns the X coordinate of <tt>this</tt> CATMathPoint.
 */
    INLINE double GetX() const;
	
/**
 * Modifies the X coordinate of <tt>this</tt> CATMathPoint.
 */
    INLINE void SetX (const double iFirstCoord);

/**
 * Returns the Y coordinate of <tt>this</tt> CATMathPoint.
 */
    INLINE double GetY() const;
	
/**
 * Modifies the Y coordinate of <tt>this</tt> CATMathPoint.
 */
    INLINE void SetY (const double iSecondCoord);

/**
 * Returns the Z coordinate of <tt>this</tt> CATMathPoint.
 */
    INLINE double GetZ() const;
	
/**
 * Modifies the Z coordinate of <tt>this</tt> CATMathPoint.
 */
    INLINE void SetZ (const double iThirdCoord);

/**
 * Retrieves <tt>this</tt> CATMathPoint in its spherical coordinates.
 * <br><tt>ioLongitudeAngle</tt> and <tt>ioLatitudeAngle</tt> 
 * are expressed in radians.
 */
    void GetSphericalCoord(double & oRadius, CATAngle & ioLongitudeAngle,
                           CATAngle & ioLatitudeAngle) const;
	
/**
 * Modifies <tt>this</tt> CATMathPoint with its spherical coordinates.
 * <br><tt>iLongitudeAngle</tt> and <tt>iLatitudeAngle</tt>
 *  are expressed in radians.
 */
    void SetSphericalCoord   (const double iRadius,
                              const CATAngle iLongitudeAngle,
                              const CATAngle iLatitudeAngle);

/**
 * Retrieves <tt>this</tt> CATMathPoint in its cylindrical coordinates.
 * <br><tt>ioAngle</tt> is expressed in radians.
 */
    void GetCylindricalCoord(double & ioRadius, CATAngle & ioAngle,
                             double & ioHeight) const;

/**
 * Modifies <tt>this</tt> CATMathPoint with its cylindrical coordinates.
 * <br><tt>iAngle</tt> is expressed in radians.
 */
    void SetCylindricalCoord (const double iRadius, const CATAngle iAngle,
			      const double iHeight);
/**
 * Returns the distance between <tt>this</tt> CATMathPoint and another CATMathPoint.
 */
    double DistanceTo (const CATMathPoint & iOtherPoint) const;

/**
 * Returns the square distance between <tt>this</tt> CATMathPoint and another CATMathPoint.
 */
    double SquareDistanceTo (const CATMathPoint & iOtherPoint) const;

/**
 * Returns the distance between <tt>this</tt> CATMathPoint  and an array of CATMathPoints.
 * @param iOtherPoint[]
 *   The array of CATMathPoints to which the distance is computed.
 * @param iNbPt
 *   The number of points of the array.
 * @param ioIndex
 *   The index of the closest point in the <tt>iOtherPoint[]</tt> array.
 */
    double DistanceTo (const CATMathPoint iOtherPoint[], const int iNbPt,
                       int & ioIndex) const;

/**
 * Returns the square distance between <tt>this</tt> CATMathPoint and the origin.
 */
    double SquareDistanceToOrigin () const;


//- Overloaded Operators


/**
 * Defines the left side scalar multiplication.
 * @param iScalar
 * The scalar.
 * @param iPoint
 * The CATMathPoint of <tt>(p1,p2,p3)</tt> coordinates.
 * @return 
 * The CATMathPoint of <tt>(iScalar*p1,iScalar*p2,iScalar*p3</tt>) coordinates.
 */
    INLINE friend CATMathPoint operator *
      (const double iScalar, const CATMathPoint & iPoint);

/**
 * Defines the right side scalar multiplication.
 * @param iPoint
 * The CATMathPoint of <tt>(p1,p2,p3</tt>) coordinates.
 * @param iScalar
 * The scalar.
 * @return 
 * The CATMathPoint of <tt>(p1*iScalar,p2*iScalar,p3*iScalar)</tt> coordinates.
 */
    INLINE friend CATMathPoint operator *
      (const CATMathPoint & iPoint, const double iScalar);

/**
 * Defines the scalar division.
 * @param iPoint
 * The CATMathPoint of <tt>(p1,p2,p3)</tt> coordinates.
 * @param iScalar
 * The scalar.
 * @return 
 * The CATMathPoint of <tt>(p1/iScalar,p2/iScalar,p3/iScalar)</tt> coordinates.
 */
    INLINE friend CATMathPoint operator /
      (const CATMathPoint & iPoint, const double iScalar);

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
 * The CATMathPoint of <tt>(p1+u1,p2+u2,p3+u3)</tt> coordinates.
 */ 
    INLINE friend ExportedByCATMathematics CATMathPoint  operator +
      (const CATMathPoint & iPoint, const CATMathVector & iVector);

/**
 * Translates a CATMathPoint by a CATMathVector.
 * @param iPoint
 * The CATMathPoint of <tt>(p1,p2,p3)</tt> coordinates.
 * @param iVector
 * The CATMathVector of <tt>(u1,u2,u3)</tt> coordinates.
 * @return 
 * The CATMathPoint of <tt>(p1=p1+u1,p2=p2+u2,p3=p3+u3)</tt> coordinates.
 */ 
    INLINE friend void          operator +=
      (CATMathPoint & iPoint, const CATMathVector & iVector);

/**
 * Translates a CATMathPoint by a CATMathVector.
 * @param iPoint
 * The CATMathPoint of <tt>(p1,p2,p3)</tt> coordinates,
 * @param iVector
 * The CATMathVector of <tt>(u1,u2,u3)</tt> coordinates,
 * @return
 * The CATMathPoint of <tt>(p1-u1,p2-u2,p3-u3)</tt> coordinates.
 */ 
    INLINE friend ExportedByCATMathematics CATMathPoint  operator -
      (const CATMathPoint & iPoint, const CATMathVector & iVector);

/**
 * Translates a CATMathPoint by a CATMathVector.
 * @param iPoint
 * The CATMathPoint of <tt>(p1,p2,p3)</tt> coordinates,
 * @param iVector
 * The CATMathVector of <tt>(u1,u2,u3)</tt> coordinates,
 * @return
 * The CATMathPoint of <tt>(p1=p1-u1,p2=p2-u2,p3=p3-u3)</tt> coordinates.
 */ 
    INLINE friend void          operator -=
      (CATMathPoint & iPoint, const CATMathVector & iVector);

	/**
 * Dumps the coordinates of a CATMathPoint.
 * <br>This writes the following line on the ostream:
 * <br><tt>( FirstCoord , SecondCoord , ThirdCoord )</tt>
 * @param iStream
 * A pointer to the output. If <tt>0L</tt>, the method dumps the 
 * coordinates on the <tt>cout</tt> output.
 */
    void Dump(ostream * iStream=0L) const;

/**
 * @nodoc
 * @deprecated V5R20.
 */
    friend ExportedByCATMathematics ostream& operator << (ostream& s,
						const CATMathPoint & iPoint);


/**
 * @nodoc
 * @deprecated V5R20.
 */
    INLINE friend CATMathPoint operator +
      (const CATMathPoint & iPoint1, const CATMathPoint & iPoint2);
/**
 * @nodoc
 * @deprecated V5R20.
 */
    INLINE friend void operator +=
      (CATMathPoint & iPoint1, const CATMathPoint & iPoint2);


#ifndef PLATEFORME_DS64
/**
 * @nodoc
 * @deprecated V5R20.
 */
    double DistanceTo (const CATMathPoint iOtherPoint[], const CATLONG32 iNbPt,
                       CATLONG32 & oIndex) const;
#endif

//----------------------------------------------------------  
//- Private data
//----------------------------------------------------------
 private:
   double _x, _y, _z;
};

//======================================================================
// INLINE IMPLEMENTATIONS
//======================================================================

INLINE CATMathPoint::CATMathPoint() { _x = 0.; _y = 0.; _z = 0.; }
 
INLINE CATMathPoint::CATMathPoint (const double iX, const double iY,
                                   const double iZ) {
  _x = iX; _y = iY; _z = iZ;
}

INLINE CATMathPoint::CATMathPoint (const double iXYZ[]) {
  if (iXYZ == 0) { _x = 0.; _y = 0.; _z = 0.; }
  else { _x = iXYZ[0]; _y = iXYZ[1]; _z = iXYZ[2]; }
}

INLINE CATMathPoint::CATMathPoint (const CATMathPoint & iP) {
  _x = iP._x; _y = iP._y; _z = iP._z;
}
 
INLINE void CATMathPoint::GetCoord (double & oX, double & oY, double & oZ) const { 
  oX = _x; oY = _y; oZ = _z;
}

INLINE void CATMathPoint::GetCoord (double oXYZ[]) const { 
  oXYZ[0] = _x; oXYZ[1] = _y; oXYZ[2] = _z; 
}

INLINE double CATMathPoint::GetX() const { return _x; }

INLINE double CATMathPoint::GetY() const { return _y; }

INLINE double CATMathPoint::GetZ() const { return _z; }

INLINE void CATMathPoint::SetCoord (const double iX,
			            const double iY,
			            const double iZ) { 
  _x = iX; _y = iY; _z = iZ;
}

INLINE void CATMathPoint::SetCoord (const double iXYZ[]) { 
  _x = iXYZ[0]; _y = iXYZ[1]; _z = iXYZ[2]; 
}

INLINE void CATMathPoint::SetX (const double iX) { _x = iX; }

INLINE void CATMathPoint::SetY (const double iY) { _y = iY; }

INLINE void CATMathPoint::SetZ (const double iZ) { _z = iZ; }

INLINE CATMathPoint operator +
                    (const CATMathPoint & iP, const CATMathPoint & iQ) {
  return CATMathPoint (iP._x + iQ._x, iP._y + iQ._y, iP._z + iQ._z);
}

INLINE void operator +=
                    (CATMathPoint & iPoint1, const CATMathPoint & iPoint2) {
  iPoint1._x += iPoint2._x; iPoint1._y += iPoint2._y; iPoint1._z += iPoint2._z;
}

INLINE CATMathPoint operator *
                    (const double iScalar, const CATMathPoint & iP) {
  return CATMathPoint (iScalar*iP._x, iScalar*iP._y, iScalar*iP._z);
}

INLINE CATMathPoint operator *
                    (const CATMathPoint & iP, const double iScalar) {
  return CATMathPoint (iScalar*iP._x, iScalar*iP._y, iScalar*iP._z);
}

INLINE CATMathPoint operator /
                    (const CATMathPoint & iP, const double iScalar) {
  return CATMathPoint (iP._x/iScalar, iP._y/iScalar, iP._z/iScalar);
}
/**
 * Defines the canonical origin (<tt>0,0,0</tt>) in 3D.
 */
extern ExportedByCATMathematics const CATMathPoint CATMathO;
#endif
