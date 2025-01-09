#ifndef CATICGMUnknown_h
#define CATICGMUnknown_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATBaseUnknown.h"
#include "ExportedByCATGMGeometricInterfaces.h"
#include "CATCGMNewInterface.h"
#include "CATGeometryType.h"

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATICGMUnknown ;
#else
extern "C" const IID IID_CATICGMUnknown ;
#endif

class CATCGMQueryManager;
class CATTolerance;
 
//CAA_Exposed CATIGemContainer
/**
 * Interface representing  the base class of all the objects of the Catia Geometrical Modeler 
 */
class ExportedByCATGMGeometricInterfaces CATICGMUnknown : public CATBaseUnknown
{
  CATDeclareInterface;
  CATNewInterfaceDeclare;
public:

  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    //CAA_Exposed 
/**
  * Tests the type of <tt>this</tt> CATICGMUnknown.
  * @param iTypeReference
  * The geometric type that must be tested
  * @return
  * The result of the test.
  * <br><b>Legal values</b>:
  * <tt>1</tt> if <tt>this</tt> CATICGMUnknown type is <tt>iTypeReference</tt>, <tt>0</tt> otherwise.
  */
  virtual int  IsATypeOf(CATGeometricType iTypeReference)const =0;


  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

 /**
  * @nodoc
  */
  virtual void *IsCGMV5() const = 0;
  

      //CAA_Exposed 
/**
  * Compare the type of <tt>this</tt> CATICGMUnknown with another object.
  * @param iOtherObject
  * Another geometric object whose type is to be compared with.
  * @return
  * The result of the test.
  * <br><b>Legal values</b>:
  * <tt>1</tt> if these two objects have same type, <tt>0</tt> otherwise.
  */
  virtual int  IsSameTypeAs(CATICGMUnknown * iOtherObject) const = 0;

//CAA_Exposed 
/**
  * Returns the CATTolerance Object associated with <tt>this</tt> CATICGMUnknown.
  * <tt>this</tt> CATICGMUnknown must be alive.
  * Note that the Extreme Scale capability is not available in V5. It is available in V6 from V6R417.
  * @return
  *   The constant CATTolerance Object associated with <tt>this</tt> CATICGMUnknown.
  */
  virtual const CATTolerance & GetToleranceObject() const = 0;
};
  
CATDeclareHandler(CATICGMUnknown,CATBaseUnknown);

#endif
