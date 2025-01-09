#ifndef CATTopDefine_H
#define CATTopDefine_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

//----------------------------------------------------------------------
// Cell Dimensions
//----------------------------------------------------------------------
/** 
* Defines the dimension of a vertex.
*/
#define CATVertexDimension  0

/** 
* Defines the dimension of an edge.
*/
#define CATEdgeDimension    1

/** 
* Defines the dimension of a face.
*/
#define CATFaceDimension    2

/** 
* Defines the dimension of a volume.
*/
#define CATVolumeDimension  3


/**
 * Defines the relative orientation of an element with regards to another one.
 * @param CATOrientationNegative
 * Their orientation are opposite.
 * @param CATOrientationPositive
 * They have the same orientation.
 * @param CATOrientationUnknown
 * The orientation is not known.
 */
#define CATOrientation      short
/** @nodoc */
#define CATOrientationNegative -1
/** @nodoc */
#define CATOrientationPositive  1
/** @nodoc */
#define CATOrientationUnknown   2

/**
 * Defines the orientation of an element vs another element.
 * @param PositiveSign
 * Positive orientation (of an edge vs another edge)
 * @param NegativeSign
 * Negative/opposite orientation.
 * @param UnknownSign
 * Unknown orientation.
 */
typedef int CATTopSign;
const CATTopSign PositiveSign        =  1;
const CATTopSign NegativeSign        = -1;
const CATTopSign UnknownSign         =  0;
const CATTopSign Forward             =  1;
const CATTopSign Backward            = -1;
const CATTopSign BothDirections      =  2;
const CATTopSign UnknownDirection    =  0;
const CATTopSign PositiveOrientation =  1;
const CATTopSign NegativeOrientation = -1;
const CATTopSign UnknownOrientation  =  0;
const CATTopSign LeftSide            = -1;
const CATTopSign RightSide           =  1;
const CATTopSign UnknownSide         =  0;


/**
 * Defines the side where is the matter when walking along an element in the
 * direction of its default orientation.
 * @param CATSideLeft
 * The matter is on the left.
 * @param CATSideFull
 * The matter is on both sides: the object is immersed inside a cell of higher dimension.
 * (non manifold configuration).
 * @param CATSideRight
 * The matter is on the right.
 * @param CATSideUnknown
 * The matter side is not known.
 */ 
#define CATSide      short
/** @nodoc */
#define CATSideLeft      1
/** @nodoc */
#define CATSideFull      0
/** @nodoc */
#define CATSideRight    -1
/** @nodoc */
#define CATSideUnknown   2


//-------------------------------------------------------------------
// CATLocation : defines whether a domain (loop, shell or other) is
// inner or outer. In some cases, it may also be :
//   - neutral (non-specified, as for the boundaries of a cylinder 
//     with a closed surface) 
//   - full (all cells in this domain are drowned in the domain's cell)
//   - unknown (not initialized)
//
// So far, neutral should not be used. It is not supported.
//-------------------------------------------------------------------
/**
 * Defines the type of boundary defined by a domain.
 * @param CATLocationInner
 * The domain defines an internal boundary (as a hole in a face or a volume).
 * @param CATLocationOuter
 * The domain defines an external boundary.
 * @param CATLocationfull
 * The domain is completely immersed inside a cell: case of non manifold configurations.
 * @param CATLocationIn3DSpace
 * The domain is directly referenced by the body.
 */
#define CATLocation      short
/** @nodoc */
#define CATLocationInner    -1
/** @nodoc */
#define CATLocationNeutral   0 // not supported yet
/** @nodoc */
#define CATLocationOuter     1
/** @nodoc */
#define CATLocationFull      2
/** @nodoc */
#define CATLocationIn3DSpace 3
/** @nodoc */
#define CATLocationIn2DSpace 4
/** @nodoc */
#define CATLocationUnknown   10


#include "CATGeoDef.h"
/**
 * The tangential continuity.
 * @param CATSmooth
 * Tangential continuity.
 * @param CATSharp
 * Tangential discontinuity.
 */
#define CATTopGeoContinuity  CATGeoContinuity
/** @nodoc */
#define CATUnknownContinuity    0

/**
 * The convexity type.
 * @param CATConvex
 * Convex.
 * @param CATConcave
 * Concave.
 * @param CATUnknownConvexity
 * Unknown convexity.
 * param CATRazorBlade
 * The boundary of a skin.
 */
#define CATTopConvexity      CATGeoConvexity
/** @nodoc */
#define CATRazorBlade            2

/**
 * Structure representing the geometric properties of an edge.
 * <br>To test if an edge if flat : 
 *     <pre>  if (Sharpness._GeoContinuity & CATSmooth)</pre> 
 *  To test if an edge if sharp : 
 *<pre>if (!(Sharpness._GeoContinuity & CATSmooth)) ...//          or 
 * if (Sharpness._GeoContinuity == CATSharp) ... </pre>
 */
typedef struct 
{
	/**
	 * Geometric continuity.
	 */
  CATTopGeoContinuity _GeoContinuity;
	/**
	 * Geometric convexity.
	 */
  CATTopConvexity     _Convexity;
} CATTopSharpness;

/**
 * Lying On Diagnostic.
 * @param CatTopNotLyingOn
 * @param CatTopPartiallyLyingOn
 * @param CatTopLyingOn
 */
enum CATTopLyingOnDiagnostic     {CatTopNotLyingOn, CatTopPartiallyLyingOn, CatTopLyingOn };

/**
 * JunctionEdge Flags.
 * @param CatTopJunctionUndefined
 * @param CatTopJunction
 * @param CatTopFunctional
 */
enum CATTopJunctionEdgeStatus	{CatTopJunctionUndefined, CatTopJunction, CatTopFunctional};

//******************************************************************************
//
//   Restricted Area :
//       Valeur de la Vivicite en radian  (0.5 degre)
//       Ne pas trop utiliser en dur, s'il vous plait (LAT), 
//       rien n'est statue sur le sujet. 
//******************************************************************************
 
/** @nodoc */
#define CATTopSharpAngle 0.0087266463



#endif
