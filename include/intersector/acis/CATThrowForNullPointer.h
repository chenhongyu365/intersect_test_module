#ifndef CATThrowForNullPointer_H
#define CATThrowForNullPointer_H
/** @CAA2Required */
// COPYRIGHT DASSAULT SYSTEMES  2001
/**
 *  Purpose : Throw an Error After detection of a NULL pointeur 
 *
 *  Audience : CGM (CATIA Geometric Modeler)   
 *
 *  Abstract : Quality improvement of V5R7+ integrated with mkCheckSource in June 2001.
 *
 *  Usage samples : 
 *
 *            void *pointer = ?;
 *
 *            if ( pointer == NULL ) CATThrowForNullPointer();
 *
 *            if ( pointer == NULL ) CATThrowForNullPointerReturnValue(ReturnValue);
 *
 *  Advice to avoid compilation error on wrong usage : 
 *   
 *    if your method (or function) returns a value, you must use 
 *      CATThrowForNullPointerReturnValue(ReturnValue) with a default value
 *      even if an assert or an exception is thrown inside the Macro 
 *    in other cases (method of function without return value), you must use 
 *       CATThrowForNullPointer()
 */


#include "CATIACGMLevel.h"
#include "CATMathematics.h"
#include "CATCGMBuildDebug.h"

#ifndef NULL
#define NULL    0
#endif

#ifdef CATIACGMV5R22
ExportedByCATMathematics void CATCGMnull();
#endif
ExportedByCATMathematics void CATCGMnull(char *ifile, int iline); 
#define CATCGMThrowForNullPointer(ifile,iline) CATCGMnull(ifile,iline)


#if defined ( CATCGMBuildDebug )
#define CATThrowForNullPointer()                          { CATCGMnull(__FILE__,__LINE__); return; }
#define CATThrowForNullPointerReturnValue( ReturnValue )  { CATCGMnull(__FILE__,__LINE__); return ReturnValue; }
#else
#ifdef CATIACGMV5R22
#define CATThrowForNullPointer()                          { CATCGMnull(); }
#define CATThrowForNullPointerReturnValue( ReturnValue )  { CATCGMnull(); return ReturnValue; }
#else
#define CATThrowForNullPointer()                          { CATCGMnull(NULL,0); return; }
#define CATThrowForNullPointerReturnValue( ReturnValue )  { CATCGMnull(NULL,0); return ReturnValue; }
#endif
#endif


#endif





