/*******************************************************************/
/*    Copyright (c) 2010-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef CGMChangeData_H
#define CGMChangeData_H


/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CGMComponent.h"
#include "ListPOfCATBody.h"

class CGMIChangeResultImpl;
class CATListPtrCATICGMObject;
/**
 * Summarizes information about any transaction that changes
 *<tt>CATICGMObject</tt> objects in a <tt>CGMPart</tt>. <b>Role</b>:  A
 *<tt>CGMChangeData</tt> object is generated as a result of a modeling
 *operation, a load operation or a change of state. This object is returned by
 *<tt>GetChangeData</tt> method of all <tt>CGMModificationResult</tt>,
 *<tt>CGMContainerLoadResult</tt> and <CGMChangeStateResult</tt> result objects.
 * This class gives access to the <tt>CATICGMObject</tt> objects existing in the
 *part before and after the transaction. To minimize memory consumption you are
 *advised to use <tt>CGMChangeData</tt> objects as locally as possible.
 *
 * Do not release the <tt>CGMContainer</tt> associated with the <tt>CGMPart</tt>
 *while <tt>CGMChangeData</tt> objects are in scope.
 **/
class ExportedByCGMComponent CGMChangeData
{
public:
  /**
   * Returns a list containing all <tt>CATBody</tt> objects
   * which were in the <tt>CGMPart</tt> before the transaction.
   * @param oBeforeBodies
   * The list containing the before bodies.
   * Callers should not depend on the ordering of this list being consistent if
   * the current state of the associated <tt>CGMPart</tt> is modified between
   * calls to this method.
   */
  void GetBeforeBodies(CATListPtrCATBody &oBeforeBodies) const;

  /**
   * Returns a list containing all <tt>CATBody</tt> objects
   * which are in the <tt>CGMPart</tt> after the transaction.
   * @param oAfterBodies
   * The list containing the after bodies.
   * Callers should not depend on the ordering of this list being consistent if
   * the current state of the associated <tt>CGMPart</tt> is modified between
   * calls to this method.
   */
  void GetAfterBodies(CATListPtrCATBody &oAfterBodies) const;

  /**
   * Returns a list containing all <tt>CATICGMObject</tt> objects
   * which were in the <tt>CGMPart</tt> before the transaction.
   * @param oBeforeObjects
   * The list containing the before <tt>CATICGMObject</tt> objects.
   * Callers should not depend on the ordering of this list being consistent if
   * the current state of the associated <tt>CGMPart</tt> is modified between
   * calls to this method.
   */
  void GetBeforeObjects(CATListPtrCATICGMObject &oBeforeObjects) const;

  /**
   * Returns a list containing all <tt>CATICGMObject</tt> objects
   * which are in the <tt>CGMPart</tt> after the transaction.
   * @param oAfterObjects
   * The list containing the after <tt>CATICGMObject</tt> objects.
   * Callers should not depend on the ordering of this list being consistent if
   * the current state of the associated <tt>CGMPart</tt> is modified between
   * calls to this method.
   */
  void GetAfterObjects(CATListPtrCATICGMObject &oAfterObjects) const;

  /**
   * Default Constructor
   **/
  CGMChangeData();

  /**
   * Copy constructor.
   * @param iOther
   * The <tt>CGMChangeData</tt> to copy.
   **/
  CGMChangeData(CGMChangeData const &iOther);

  /**
   * Assignment operator.
   * @param iOneOf
   * The <tt>CGMChangeData</tt> to assign to <tt>this</tt>.
   * @return
   * A reference to the assigned <tt>CGMChangeData</tt>.
   **/
  CGMChangeData &operator=(const CGMChangeData &iOneOf);

  // do not use.  internal use only.
  /**
   * @nodoc
   */
  CGMChangeData(CGMIChangeResultImpl *ipImpl);

  // do not use.  internal use only.
  /**
   * @nodoc
   */
  CGMIChangeResultImpl *GetImpl() const;

  /**
   * Destructor.
   */
  ~CGMChangeData();

private:
  CGMIChangeResultImpl *_impl;
};

#endif
