#ifndef CATMshBase_H
#define CATMshBase_H
// COPYRIGHT Dassault Systemes 2022
/**
 * @CAA2Level L0
 * @CAA2Usage U1
 */
//===================================================================
//
// CATMshBase.h
// Define the CATMshBase interface
//
//===================================================================
//
// Usage notes:
//   Reference counting
//
//===================================================================

#include "ExportedByCATMshMesherCore.h"
#include "CATSysErrorDef.h"
/**
 * Reference counting
 */
class ExportedByCATMshMesherCore CATMshBase
{

public:

  /**
   * Increments the reference count of the instance.
   */
  void AddRef ();

  /**
   * Decrements the reference count of the instance.  When the counter reaches 0, the instance is deleted.
   */
  void Release ();


protected:

  CATMshBase();
  virtual ~CATMshBase();

private:

  CATMshBase(const CATMshBase& Source);
  CATMshBase& operator=(const CATMshBase& Source);

  unsigned int _Ref;

};


#endif
