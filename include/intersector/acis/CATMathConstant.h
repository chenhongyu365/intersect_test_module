#ifndef CATMathConstant_H
#define CATMathConstant_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATMathematics.h"

#include "CATBoolean.h"

/**
 * Defines the type "angle".
 */
typedef double CATAngle ;


/**
 * Defines the type "CATMathClassId", to decribe the types of mathematical curves. 
 */
typedef const char * CATMathClassId;
//
// Constant connected to Pi
//
/**
 * Defines <tt>Pi = 3.14159265358979323846 </tt>
 */
extern ExportedByCATMathematics const double CATPI;     

/**
 * Defines <tt>2*Pi = 6.28318530717958647692 </tt>
 */
extern ExportedByCATMathematics const double CAT2PI;    

/**
 * Defines <tt>3*Pi = 9.42477796076937971538 </tt>
 */
extern ExportedByCATMathematics const double CAT3PI;      

/**
 * Defines <tt>Pi/2 = 1.57079632679489661923 </tt>
 */
extern ExportedByCATMathematics const double CATPIBY2;    

/**
 * Defines <tt>3*Pi/2 = 4.71238898038468985769 </tt>
 */
extern ExportedByCATMathematics const double CAT3PIBY2;   

/**
 * Defines <tt>Pi/4 = 0.78539816339744830961 </tt>
 */
extern ExportedByCATMathematics const double CATPIBY4;    

/**
 * Defines <tt>3*Pi/4 = 2.35619449019234492884 </tt>
 */
extern ExportedByCATMathematics const double CAT3PIBY4;  

/**
 * Defines <tt>1/Pi= 0.31830988618379067153 </tt>
 */
extern ExportedByCATMathematics const double CATINVPI;   

/**
 * Defines <tt>1/(2*Pi) =0.15915494309189533577 </tt>
 */
extern ExportedByCATMathematics const double CATINV2PI;  
//
// Square roots
//
/**
 * Defines <tt>sqrt(2) = 1.41421356237309504880 </tt>
 */
extern ExportedByCATMathematics const double CATSQRT2;     

/**
 * Defines <tt>1/sqrt(2) = 0.70710678118654752440 </tt>
 */
extern ExportedByCATMathematics const double CATINVSQRT2; 

/**
 * Defines <tt>sqrt(3) = 1.73205080756887729352 </tt>
 */
extern ExportedByCATMathematics const double CATSQRT3;      

/**
 * Defines <tt>1/sqrt(3) = 0.57735026918962576451 </tt>
 */
extern ExportedByCATMathematics const double CATINVSQRT3;   
//
// Convertors constants from radian to degree and from degree to radian
//
/**
 * Defines the factor <tt>57.295779513082323 </tt> to convert radians into degrees.
 */
extern ExportedByCATMathematics const double CATRadianToDegree; 

/**
 * Defines the factor <tt>0.017453292519943295 </tt> to convert degrees into radians
 */
extern ExportedByCATMathematics const double CATDegreeToRadian; 

#endif
 
