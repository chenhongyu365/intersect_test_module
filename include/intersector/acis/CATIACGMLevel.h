/** @CAA2Required */
/*---------------------------------------------------------------------*/
/* DON'T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS  */
/* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPPEAR AT ANY TIME */
/*---------------------------------------------------------------------*/
// COPYRIGHT DASSAULT SYSTEMES 2004
#include "CATIAV5Level.h"

#ifdef CATIAV5R15
  #define CATIACGMV5R15
#endif

#ifdef CATIAV5R16
  #define CATIACGMV5R16
#else
  #ifdef CATIAR201
    #define CATIACGMV5R16
  #endif
#endif

#ifdef CATIAV5R17
  #define CATIACGMV5R17
#else
  #ifdef CATIAR201
    #define CATIACGMV5R17
  #endif
#endif

#ifdef CATIAV5R18
  #define CATIACGMV5R18
#else
  #ifdef CATIAR201
    #define CATIACGMV5R18
  #endif
#endif

#ifdef CATIAV5R19
  #define CATIACGMV5R19
#else
  #ifdef CATIAR204
    #define CATIACGMV5R19
  #endif
#endif

#ifdef CATIAV5R20
  #define CATIACGMV5R20
#else
  #ifdef CATIAR206
    #define CATIACGMV5R20
  #endif
#endif

#ifdef CATIAV5R21
  #define CATIACGMV5R21
#else
  #ifdef CATIAR209
    #define CATIACGMV5R21
  #endif
#endif

#ifdef CATIAV5R22
  #define CATIACGMV5R22
#else
  #ifdef CATIAR212
    #define CATIACGMV5R22
  #endif
#endif

#ifdef CATIAV5R23
  #define CATIACGMV5R23
#else
  #ifdef CATIAR213
    #define CATIACGMV5R23
  #endif
#endif

#ifdef CATIAV5R23
  #define CATIACGMR214CAA
  #define CATIACGMR214Code
#else
  #ifdef CATIAR214
  #define CATIACGMR214CAA
  #define CATIACGMR214Code
  #endif
#endif

#ifdef CATIAV5R24
  #define CATIACGMR215CAA
  #define CATIACGMR215Code
  #define CATIACGMR216CAA
  #define CATIACGMR216Code
#else
  #ifdef CATIAR215
  #define CATIACGMR215CAA
  #define CATIACGMR215Code
  #endif
  
  #ifdef CATIAR216
  #define CATIACGMR216CAA
  #define CATIACGMR216Code
  #endif
#endif

#ifdef CATIAV5R25
  #define CATIACGMR217CAA
  #define CATIACGMR217Code
  #define CATIACGMR417CAA
  #define CATIACGMR417Code
#else
  #ifdef CATIAR417
  #define CATIACGMR217CAA
  #define CATIACGMR217Code
  #define CATIACGMR417CAA
  #define CATIACGMR417Code
  #endif
#endif

#ifdef CATIAV5R26
  #define CATIACGMR418CAA
  #define CATIACGMR418Code
#else
  #ifdef CATIAR418
  #define CATIACGMR418CAA
  #define CATIACGMR418Code
  #endif
#endif
 

#ifdef CATIAV5R27
  #define CATIACGMR419CAA
  #define CATIACGMR419Code
#else
  #ifdef CATIAR419
  #define CATIACGMR419CAA
  #define CATIACGMR419Code
  #endif 
#endif

#ifdef CATIAV5R28
  #define CATIACGMR420CAA
  #define CATIACGMR420Code
#else
  #ifdef CATIAR420
  #define CATIACGMR420CAA
  #define CATIACGMR420Code
  #endif 
#endif

#ifdef CATIAV5R29
  #define CATIACGMR421CAA
  #define CATIACGMR421Code
#else
  #ifdef CATIAR421
  #define CATIACGMR421CAA
  #define CATIACGMR421Code
  #endif
#endif 

#ifdef CATIAV5R30
  #define CATIACGMR422CAA
  #define CATIACGMR422Code
#else
  #ifdef CATIAR422
  #define CATIACGMR422CAA
  #define CATIACGMR422Code
  #endif
#endif

#ifdef CATIAV5R31
  #define CATIACGMR423CAA
  #define CATIACGMR423Code
#else
  #ifdef CATIAR423
  #define CATIACGMR423CAA
  #define CATIACGMR423Code
  #endif
#endif

#ifdef CATIAV5R32
  #define CATIACGMR424CAA
  #define CATIACGMR424Code
#else
  #ifdef CATIAR424
  #define CATIACGMR424CAA
  #define CATIACGMR424Code
  #endif
#endif

#ifdef CATIAV5R33
  #define CATIACGMR425CAA
  #define CATIACGMR425Code
#else
  #ifdef CATIAR425
  #define CATIACGMR425CAA
  #define CATIACGMR425Code
  #endif
#endif

#ifdef CATIAV5R34
  #define CATIACGMR426CAA
  #define CATIACGMR426Code
#else
  #ifdef CATIAR426
  #define CATIACGMR426CAA
  #define CATIACGMR426Code
  #endif
#endif

#ifdef CATIAV5R35
  #define CATIACGMR427CAA
  #define CATIACGMR427Code
#else
  #ifdef CATIAR427
  #define CATIACGMR427CAA
  #define CATIACGMR427Code
  #endif
#endif

