#ifndef CATCGMBuildDebug_H
#define CATCGMBuildDebug_H
// COPYRIGHT DASSAULT SYSTEMES  2001
/** @CAA2Required */

/**
 *  Purpose  : Determine if Debug information can be integrated in the Build Process
 *  Audience : CGM (CATIA Geometric Modeler)   
 *  Abstract : Quality improvement of V5R7+ (default Build is the customer optimized Build) 
 */

#undef  CATCGMBuildDebug
#if defined ( _DEBUG ) && defined ( _CATCGMBuildDebug )
#define CATCGMBuildDebug
#endif

#endif





