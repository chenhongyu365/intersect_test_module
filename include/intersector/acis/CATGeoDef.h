#ifndef CATGeoDef_H
#define CATGeoDef_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

/**
 * The tangential continuity.
 * @param CATSmooth
 * Tangential continuity.
 * @param CATSharp
 * Tangential discontinuity.
 */
#define CATGeoContinuity  short
/** @nodoc */
#define CATSharp                1
/** @nodoc */
#define CATSmooth               2



/**
 * The convexity type.
 * @param CATConvex
 * Convex.
 * @param CATConcave
 * Concave
 * @param CATUnknownConvexity
 * Unknown convexity.
 */
#define CATGeoConvexity      short
/** @nodoc */
#define CATConvex                1
/** @nodoc */
#define CATConcave              -1
/** @nodoc */
#define CATUnknownConvexity      0


#endif
