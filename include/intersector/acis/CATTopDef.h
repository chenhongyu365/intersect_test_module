#ifndef CATTopDef_H
#define CATTopDef_H

/** @CAA2Required */

// COPYRIGHT DASSAULT SYSTEMES  1997
//=============================================================================
//
// CATTopDef : Constants for topology
// 
//=============================================================================

#include "CATTopDefine.h"

//----------------------------------------------------------------------
// Edge Sharpness (Regarding a couple of adjacents faces)
//      NB : CATG0 = CATSharp
//----------------------------------------------------------------------
#define CATG0                   1
#define CATG1                   3
#define CATG2                   7



//------------------------------------------------------------------------------
//  To test if an edge if flat : 
//        if (Sharpness._GeoContinuity & Smooth) 
//  To test if an edge if sharp : 
//        if (!(Sharpness._GeoContinuity & Smooth)) ...
//          or 
//        if (Sharpness._GeoContinuity == Sharp) ...
//------------------------------------------------------------------------------


// Lying On Diagnostic
// enum CATTopLyingOnDiagnostic     {CatTopNotLyingOn, CatTopPartiallyLyingOn, CatTopLyingOn };

// JunctionEdge Flags
// enum CATTopJunctionEdgeStatus	{CatTopJunctionUndefined, CatTopJunction, CatTopFunctional};


// To define common macros
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL 0
#endif

//------------------------------------------------------------------------------
//  Dump 
//------------------------------------------------------------------------------
#include "CATGMModelInterfaces.h"
class CATCGMOutput;
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif
ExportedByCATGMModelInterfaces ostream&      operator<< (ostream& , const CATTopSharpness& );
ExportedByCATGMModelInterfaces CATCGMOutput& operator<< (CATCGMOutput& , const CATTopSharpness& );
ExportedByCATGMModelInterfaces void CATDumpOrientation(CATCGMOutput& , CATOrientation);
ExportedByCATGMModelInterfaces void CATDumpSide(CATCGMOutput& , CATSide);
ExportedByCATGMModelInterfaces void CATDumpLocation(CATCGMOutput& , CATLocation);


//******************************************************************************
//
//   Restricted Area :
//       Valeur de la Vivicite en radian  (0.5 degre)
//       Ne pas trop utiliser en dur, s'il vous plait (LAT), 
//       rien n'est statue sur le sujet. 
//******************************************************************************
//#define CATTopSharpAngle 0.0087266463

// pour faire compiler CATCGMVisuController qui inclut un header inconnu ou 
//  Convex est uen macro qui vaut 2
#ifdef Convex
#undef Convex
#endif

const CATTopGeoContinuity G0                   =  1;
const CATTopGeoContinuity G1                   =  3;
const CATTopGeoContinuity G2                   =  7;
const CATTopGeoContinuity Sharp                =  1; // = G0
//const CATTopGeoContinuity Smooth               =  2;
const CATTopGeoContinuity UnknownGeoContinuity =  0; 

const CATTopConvexity   Convex           =   1;
const CATTopConvexity   Concave          =  -1;
const CATTopConvexity   UnknownConvexity =   0;
const CATTopConvexity   RazorBlade       =   2; // reserve aux bords de skin


#endif
