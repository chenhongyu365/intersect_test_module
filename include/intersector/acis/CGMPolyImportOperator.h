/*******************************************************************/
/*    Copyright (c) 2016-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef CGMPolyImportPartOperator_H
#define CGMPolyImportPartOperator_H


/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CATCGMVirtual.h"
#include "CGMCompPoly.h"
#include "CGMPolyImportPart.h"

namespace CGMPolyImport
{
/**
 *  Base class for all modification operations used within the <tt>Part</tt>.
 *
 * <b>Role</b>: Each <tt>Operator</tt> is always created on the heap using
 * <tt>DerivedClass::Create(...)</tt>, and clients must call the
 * <tt>Release</tt> method at the end of its lifetime. Unlike other operations
 * in CGM, there is no way to run an <tt>Operator</tt> without a <tt>Part</tt>.
 * After creating an <tt>Operator</tt> and adjusting its settings,
 * clients pass it into the method <tt>Part::ModifyUsing(Operator const*
 * op)</tt>.
 *
 * @see Part
 */
class ExportedByCGMCompPoly Operator
{
public:
  /**
   * Clients should always call the <tt>Release</tt> method at the end of the
   * Operator's lifetime.
   */
  virtual void Release() = 0;

  /** @nodoc */
  class Wrapper;

protected:
  Operator();
  virtual ~Operator();

  friend class OperatorFriend;
  virtual Wrapper *GetWrapper() const = 0;

private:
  Operator(Operator const &iOther);
  Operator &operator=(Operator const &iOther);
};

} // namespace CGMPolyImport

#endif
