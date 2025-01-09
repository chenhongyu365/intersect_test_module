#ifndef CATCGMScaleCategoryDef_H
#define CATCGMScaleCategoryDef_H
// COPYRIGHT DASSAULT SYSTEMES  2006
/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

/**
 * Scale as a discrete value instead of a double.
 * Note that the Extreme Scale capability is not available in V5. It is available in V6 from V6R417.
 * ScaleNaS and ScaleXS are not supported.
 * @param ScaleNotSet
 *   Not defined.
 * @param ScaleNaS     
 *   Nanometric scale,     Scale = 1e-6, ResolutionC0 = 1e-9.
 * @param ScaleXS     
 *   Extra small scale,    Scale = 1e-4, ResolutionC0 = 1e-7.
 * @param ScaleS      
 *   Small scale,          Scale = 1e-2, ResolutionC0 = 1e-5.
 * @param ScaleN      
 *   Normal scale,         Scale = 1e 0, ResolutionC0 = 1e-3.
 * @param ScaleL      
 *   Large scale,          Scale = 1e+2, ResolutionC0 = 1e-1.
 * @param ScaleXL     
 *   Extra large scale,    Scale = 1e+4, ResolutionC0 = 1e+1.
*/
enum CATCGMScaleCategory 
{
  ScaleNotSet = 0,
  ScaleXS     = 1, 
  ScaleS      = 2,
  ScaleN      = 3,
  ScaleL      = 4,
  ScaleXL     = 5,
  ScaleNaS    = 6 
};
//@nodoc
//number of different ScaleCategory discrete values
const int ScaleCategory_MaxNumber=ScaleNaS+1;

//@nodoc
//Represent the range: ratio between model size and scale
enum CATCGMScaleRange 
{
  RangeNotSet   = 0,
  RangeReduced  = 1, //Range = 1.e+5
  RangeExtended = 2  //Range = 1.e+6
};

#endif
