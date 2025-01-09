#ifndef CATMathBox_H
#define CATMathBox_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CATIACGMLevel.h"
#include "CATMathDef.h"
#include "CATMathInline.h"
#include "CATMathematics.h"
#include "IUnknown.h"

class CATMathPoint;
class CATMathLine;
class CATMathPlane;
class CATMathDirection;

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#    include <iosfwd.h>
#else
class ostream;
#endif

/**
 * Class representing a 3D box, parallel to the canonical axis.
 * <b>Role</b>:
 * <br> The box is defined by two CATMathPoint, the first
 * <tt>(XMin, YMin, ZMin)</tt> called the low
 * extremity, and the other one (<tt>(XMax, YMax, ZMax)</tt>) the high extremity.
 *<br> A box can be seen as a set. If one of the cooordinates of the low
 * extremity is greater
 * than the corresponding coordinate of the high  extremity, the box is empty.
 * In other words, a box is not empty if <tt> XMin < XMax </tt> and
 * <tt> YMin < YMax </tt> and <tt> ZMin < ZMax</tt>.
 */
class ExportedByCATMathematics CATMathBox {
  public:
    //======================================================================
    //  CONSTRUCTORS AND DESTRUCTOR
    //======================================================================

    /**
     * Constructs an empty CATMathBox.
     */
    CATMathBox();

    /**
     * Constructs a CATMathBox from two CATMathPoint.
     * @param iCheck
     * <dl>
     * <dt><tt>FALSE</tt><dd>The two CATMathPoint are assumed to be the
     * lowest one and the highest one. This can create an empty box if it is not
     * the case.
     * <dt><tt>TRUE</tt> <dd>It creates the smallest box that contains
     * the two CATMathPoint (default mode).
     * </dl>
     *
     */
    CATMathBox(const CATMathPoint& iLowExtremity, const CATMathPoint& iHighExtremity, const CATBoolean iCheck = TRUE);

    /**
     * Constructs a CATMathBox from its extremities.
     *<br>No verification is performed.
     */
    CATMathBox(const double iXMin, const double iXMax, const double iYMin, const double iYMax, const double iZMin, const double iZMax);

    /**
     * Copy Constructor.
     */
    CATMathBox(const CATMathBox& iBoxToCopy);

#ifndef CATIACGMV5R23
    /**
     * Destructor.
     */
    ~CATMathBox();
#endif

    //======================================================================
    // SET AND GET THE EXTREMITIES
    //=====================================================================

    /**
     * @nodoc
     * @deprecated V5R15 GetLimits
     * Retrieves the extremities of <tt>this</tt> CATMathBox.
     * <br>Throws an error if the box is empty.
     */
    void GetExtremities(double& ioXMin, double& ioXMax, double& ioYMin, double& ioYMax, double& ioZMin, double& ioZMax) const;

    /**
     * Retrieves the extremities of <tt>this</tt> CATMathBox.
     * @return
     * <tt>E_FAIL</tt> if the box is empty, <tt>S_OK</tt> otherwise.
     */
    HRESULT GetLimits(double& ioXMin, double& ioXMax, double& ioYMin, double& ioYMax, double& ioZMin, double& ioZMax) const;

    /**
     * Sets the extremities of <tt>this</tt> CATMathBox.
     *<br>No verification is done.
     */
    void SetExtremities(const double iXMin, const double iXMax, const double iYMin, const double iYMax, const double iZMin, const double iZMax);

    /**
     * @nodoc
     * @deprecated V5R15 GetLowLimit
     * Retrieves the low extremity of <tt>this</tt> CATMathBox.
     * <br>Throws an error if the box is empty.
     */
    void GetLow(CATMathPoint& ioLowPoint) const;

    /**
     * Retrieves the low extremity of <tt>this</tt> CATMathBox.
     * @return
     * <tt>E_FAIL</tt> if the box is empty, <tt>S_OK</tt> otherwise.
     */
    HRESULT GetLowLimit(CATMathPoint& ioLowPoint) const;

    /**
     * Modifies the low extremity of <tt>this</tt> CATMathBox.
     *<br>No verification is performed.
     */
    void SetLow(const CATMathPoint& iLowPoint);

    /**
     * @nodoc
     * @deprecated V5R15 GetHighLimit
     * Retrieves the high extremity of <tt>this</tt> CATMathBox.
     * <br>Throws an error if the box is empty.
     */
    void GetHigh(CATMathPoint& ioHighPoint) const;

    /**
     * Retrieves the high extremity of <tt>this</tt> CATMathBox.
     * @return
     * <tt>E_FAIL</tt> if the box is empty, <tt>S_OK</tt> otherwise.
     */
    HRESULT GetHighLimit(CATMathPoint& ioHighPoint) const;

    /**
     * Modifies the high extremity of <tt>this</tt> CATMathBox.
     *<br>No verification is performed.
     */
    void SetHigh(const CATMathPoint& iHighPoint);

    /**
     * Resets <tt>this</tt> CATMathBox to an empty one.
     */
    INLINE void SetToEmpty();

    /**
     * Retrieves the center of <tt>this</tt> CATMathBox.
     * @return
     * <tt>E_FAIL</tt> if the box is empty, <tt>S_OK</tt> otherwise.
     */
    HRESULT GetBoxCenter(CATMathPoint& ioCenterPoint) const;

    /**
     * Tests if <tt>this</tt> CATMathBox is empty.
     * @return
     * <tt>TRUE</tt> if the CATMathBox is empty, <tt>FALSE</tt> otherwise.
     */
    INLINE CATBoolean IsEmpty() const;

    //=====================================================================
    // COMPUTATION THAT MODIFIES THE BOX
    //======================================================================

    /**
     * Replaces <tt>this</tt> CATMathBox with the intersection of two other
     * CATMathBox.
     *<br>It can lead to  an empty CATMathBox.
     */
    void SetToIntersection(const CATMathBox& iBox1, const CATMathBox& iBox2);

    /**
     * Replaces <tt>this</tt> CATMathBox with the union of two
     * other CATMathBox.
     */
    void SetToUnion(const CATMathBox& iBox1, const CATMathBox& iBox2);

    /**
     * Modifies <tt>this</tt> CATMathBox by forcing a CATMathPoint to belong to it.
     */
    void AddInside(const CATMathPoint& iPointToAdd);

    /**
     * Replaces <tt>this</tt> CATMathBox by its union with another CATMathBox.
     */
    void AddInside(const CATMathBox& iBoxToAdd);

    /**
     * Modifies <tt>this</tt> CATMathBox by adding a given thickness on each direction.
     *<br>Hence,  the low extremity of the box becomes
     *(<tt>XMin-iThickness, YMin-iThickness, ZMin-iThickness</tt>) and the high
     * extremity becomes
     *(<tt>XMax+iThickness, YMax+iThickness, ZMax+iThickness</tt>).
     *<br>This method does not apply on an empty box, but no error is thrown in this case.
     */
    void Inflate(double iThickness);

    /**
     * Modifies <tt>this</tt> CATMathBox by having it larger at the same place.
     * <br>The CATMathBox increases as follows:
     * Let <tt>f=(iScaleRatio-1)/2 </tt> be the multiplicative ratio on each
     * direction and
     * <tt>dX=XMax-XMin, dY=YMax-YMin, dZ=ZMax-ZMin</tt> be the lengths of the box in
     * each direction.
     * The low extremity of the box becomes
     *(<tt>XMin-dX*f, YMin-dY*f, ZMin-dZ*f</tt>) and the high
     * extremity becomes
     *(<tt>XMax+dX*f, YMax+dY*f, ZMax+dZ*f</tt>). In particular, if
     * the length of the box is null in one direction, it still
     * remains null after a local scale.
     *<br>This method does not apply on an empty box, but no error is thrown in this case.
     */
    void LocalScale(double iScaleRatio);

    //======================================================================
    // COMPUTATION WITH A BOX THAT RETURNS A RESULT
    //======================================================================

    /**
     * Returns <tt>TRUE</tt> if <tt>this</tt> CATMathBox is intersecting an another one.
     * The test takes a given tolerance into account (the result is equivalent
     * to inflating one of the box of iTol and to compute IsIntersecting with
     * no tolerance.
     *<br> Note that if the intersection is a point or a line, the
     * result is true.
     */
    CATBoolean IsIntersecting(const CATMathBox& iBox, double iTol = 0.) const;

    /**
     * Returns <tt>TRUE</tt> if the projection of <tt>this</tt> CATMathBox onto the plane perpendicular to the direction
     * The test takes into account a given tolerance  (the result is equivalent
     * to inflating one of the box of iTol and to compute IsIntersectingAlongDir with
     * no tolerance.
     */
    CATBoolean IsIntersectingAlongDir(CATMathBox& iBox, const CATMathDirection& iDir, double iTol = 0.) const;

    /**
     * Returns <tt>TRUE</tt> if <tt>this</tt> CATMathBox is intersecting the segment [iP1,iP2].
     *<br> Note that if the intersection is a point or a line, the
     * result is true.
     */
    CATBoolean IsIntersecting(const CATMathPoint& iP1, const CATMathPoint& iP2) const;

    /**
     * Returns <tt>TRUE</tt> if <tt>this</tt> CATMathBox is intersecting a CATMathLine.
     *<br> Note that if the intersection is a point or a line, the
     * result is true.
     */
    CATBoolean IsIntersecting(const CATMathLine& iLine) const;

    /**
     * Returns <tt>TRUE</tt> if <tt>this</tt> CATMathBox is intersecting a CATMathPlane.
     *<br> Note that if the intersection is a point or a line, the
     * result is true.
     */
    CATBoolean IsIntersecting(const CATMathPlane& iPlane) const;

    /**
     * Returns <tt>TRUE</tt> if <tt>this</tt> CATMathBox defined at a given tolerance
     * is containing a CATMathPoint.
     *<br>The CATMathBox used is defined by:
     *<tt>[_XMin-iTol, _XMax+iTol] x [_YMin-iTol, _YMax+iTol] x
     * [_ZMin-iTol, _ZMax+iTol] </tt>
     */
    CATBoolean IsContaining(const CATMathPoint& iPoint, double iTol = 0.) const;

    /**
     * Returns <tt>TRUE</tt> if <tt>this</tt> CATMathBox is completely containing an other
     * CATMathBox.
     *<br>Note that the empty CATMathBox is contained by all CATMathBox and does
     * not contain any CATMathBox, even an empty one.
     */
    CATBoolean IsContaining(const CATMathBox& iOtherBox) const;

    /**
     * Returns the geometric volume included in <tt>this</tt> CATMathBox.
     */
    double Volume() const;

    /**
     * Returns the distance between <tt>this</tt> CATMathBox and a CATMathPoint.
     */
    double DistanceTo(const CATMathPoint& iPoint) const;

    /**
     * Returns the square distance between <tt>this</tt> CATMathBox and a CATMathPoint.
     */
    double SquareDistanceTo(const CATMathPoint& iPoint) const;

    /**
     * Returns the square of the maximal distance between <tt>this</tt> CATMathBox and a CATMathPoint.
     * For a point inside the box, the maximal distance is the distance between it and the furthest point of the box from  it.
     */
    double SquareMaxDistanceTo(const CATMathPoint& iPoint) const;
    //======================================================================
    // For Debug
    //======================================================================
    /**
     * @nodoc
     * Returns the minimum square distance between <tt>this</tt> CATMathBox and a CATMathBox.
     * If boxes intersects, returns 0.
     * If one of boxes is empty, returns -1.
     */
    double SquareDistanceTo(const CATMathBox& iBox) const;

    /**
     * @nodoc
     * @deprecated V5R20.
     * Dumps a CATMathBox.
     * <br>This writes the following on the ostream:
     * <dl><dt><tt>Empty CATMathBox </tt> <dd> If the box is empty.
     *     <dt><pre>
     *LowCorner  = ( LowFirstCoord  , LowSecondCoord  , LowThirdCoord )
     *HighCorner = ( HighFirstCoord , HighSecondCoord , HighThirdCoord )</pre>
     *     <dd> If the box is not empty.</dl>
     * @param iStream
     * A pointer to the output. If <tt>0L</tt>, the method dumps
     * on the <tt>cout</tt> output.
     */
    void Dump(ostream* iStream = 0L) const;
    //
    //

    /**
     * @nodoc
     * @deprecated V5R20 DistanceTo
     */
    INLINE double DistanceToPoint(const CATMathPoint& iPoint) const {
        return DistanceTo(iPoint);
    }

    /**
     * @nodoc
     * @deprecated V5R20 SquareDistanceTo
     */
    INLINE double SquareDistanceToPoint(const CATMathPoint& iPoint) const {
        return SquareDistanceTo(iPoint);
    }

    /**
     * @nodoc
     * @deprecated V5R20.
     * <br>Throws an error if the box is empty.
     */
    const CATMathPoint& GetStartPoint() const;

    /**
     * @nodoc
     * @deprecated V5R20.
     * <br>Throws an error if the box is empty.
     */
    const CATMathPoint& GetEndPoint() const;

    /**
     * @nodoc
     * @deprecated V5R20 IsContaining
     */
    int ContainsPoint(const CATMathPoint& iPoint) const;

    /**
     * @nodoc
     * @deprecated V5R20.
     */
    friend ExportedByCATMathematics ostream& operator<<(ostream& s, const CATMathBox& iBox);

    //======================================================================
    // INTERNAL DATAS
    //======================================================================

  private:
    // Extremities
    double _XMin, _YMin, _ZMin, _XMax, _YMax, _ZMax;

    // Flag which is not null if the box is empty
    CATBoolean _Empty;

    // Internal method
    int ComputeZone(const double iX, const double iY, const double iZ) const;
};

//======================================================================
// INLINE IMPLEMENTATIONS
//======================================================================
INLINE void CATMathBox::SetToEmpty() {
    _Empty = 1;
}

INLINE CATBoolean CATMathBox::IsEmpty() const {
    return _Empty;
}

#endif
