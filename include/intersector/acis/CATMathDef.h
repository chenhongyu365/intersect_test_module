#ifndef CATMathDef_H
#define CATMathDef_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#if(defined(_MSC_VER) && (_MSC_VER >= 1900))
#    include <cmath>
#else
#    include <math.h>
#endif
#include "CATDataType.h"
#include "CATMathConstant.h"

/**
 * Type to define a length.
 */
typedef double CATLength;
/**
 * Type to define a positive length.
 */
typedef double CATPositiveLength;

/**
 * Type to define the available evaluators of a mathematical function.
 * @param OptionEval
 * The function evaluation.
 * @param OptionEvalFirstDeriv
 * The evaluation of the first derivative.
 * @param OptionEvalSecondDeriv
 * The evaluation of the second derivative.
 * @param OptionEvalThirdDeriv
 * The evaluation of the third derivative.
 */
typedef CATLONG32 CATMathOption;
/** @nodoc */
#define OptionEval 1
/** @nodoc */
#define OptionEvalFirstDeriv 2
/** @nodoc */
#define OptionEvalSecondDeriv 4
/** @nodoc */
#define OptionEvalThirdDeriv 8
/** @nodoc */
#define OptionEvalInterval 16
/** @nodoc */
#define OptionEvalFirstDerivInterval 32
/** @nodoc */
#define OptionEvalSecondDerivInterval 64
/** @nodoc */
#define OptionEvalThirdDerivInterval 128

/** @nodoc */
typedef const char* CATMathAttrId;

#endif
