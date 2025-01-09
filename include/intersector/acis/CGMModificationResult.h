/*******************************************************************/
/*    Copyright (c) 2010-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef CGMModificationResult_H
#define CGMModificationResult_H


/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CATBoolean.h"
#include "CGMChangeData.h"
#include "CGMComponent.h"
#include "CGMJournalIterator.h"
#include "CGMObjectTracker.h"
#include "ListPOfCATBody.h"

class CATBody;
class CATListPtrCATBody;
class CGMIModificationResultImpl;
class CATCGMJournalList;
class CGMMessageList;

/**
 * Class used to represent the result of calling the <tt>ModifyUsing</tt> method
 *of <tt>CGMPart</tt>. <b>Role</b>: This class is one of a set of result classes
 *that are returned by transactions that operate on <tt>CGMPart</tt> objects.
 * These result objects collect information about the transaction that can be
 *queried by the caller. The other responsibility of these result objects is to
 *maintain use counts on the items involved in the queries, so that they will
 * not be deleted as long as the corresponding result object is in scope.
 *
 * If an instance of this class is constructed but never updated through a call
 *to <tt>CGMPart</tt>, then it remains uninitialized, and calls to any of the
 *Get methods will result in an exception.
 *
 * This class is designed with "value-class" semantics; it is intended to be
 *owned and passed by value, rather than being allocated on the heap. To
 *minimize memory consumption, you are advised to use
 *<tt>CGMModificationResult</tt> objects as locally as possible.
 **/
class ExportedByCGMComponent CGMModificationResult
{
public:
  /**
   * Fills a list with the <tt>CATBody</tt> objects created as a result of the
   *operator. <b>Role</b>: If this method is called on an instance that is
   *constructed but never updated through a call to <tt>CGMPart</tt>, then an
   *exception will be thrown.
   * @param oResultBodies
   * The list of result bodies.
   **/
  void GetResultBodies(CATListPtrCATBody &oResultBodies) const;

  /**
   * Helper routine to obtain the resulting <tt>CATBody</tt> of a modification
   * which produces at most one result body. <b>Role</b>: If this method is
   * called on an instance that is constructed but never updated through a call
   * to <tt>CGMPart</tt>, then an exception will be thrown.
   *
   * If the instance is updated and the modification has no result body, then
   * this method will return <tt>NULL</tt>. This method will then throw under
   * the following conditions: <ul> <li> The modification produces multiple
   * result bodies. For example, this object is the result of concatenating
   * multiple <tt>CGMModificationResult</tt> objects. <li> The modification
   * involves multi-result operations. For example, it involves an operator
   * derived from <tt>CATICGMTopMultiResult</tt>, or it involves
   * <tt>CGMPart::Add</tt>. This behavior is designed to help prevent
   * inadvertent misuse that might not be detected in unit testing.
   * </ul>
   * @return
   * A pointer to the resulting body.
   */
  CATBody *GetResultBody() const;

  /**
   * Helper routine to obtain the resulting <tt>CATBody</tt> of a modification
   * which produces at most one result body. <b>Role</b>: If this method is
   * called on an instance that is constructed but never updated through a call
   * to <tt>CGMPart</tt>, then an exception will be thrown.
   *
   * If the instance is updated and the modification has no result body, then
   * this method will return <tt>NULL</tt>. This method will then throw under
   * the following conditions: <ul> <li> The modification produces multiple
   * result bodies. For example, this object is the result of concatenating
   * multiple <tt>CGMModificationResult</tt> objects. <li> The modification
   * involves multi-result operations and <tt>iThrowIfMultiResultOperation</tt>
   * is <tt>TRUE</tt>. For example, it involves an operator derived from
   * <tt>CATICGMTopMultiResult</tt>, or it involves <tt>CGMPart::Add</tt>. You
   * should set <tt>iThrowIfMultiResultOperation</tt> to <tt>FALSE</tt> only if
   * you are certain the modification will never produce more than one result
   * body.
   * </ul>
   * The behavior of this method with <tt>iThrowIfMultiResultOperation</tt> set
   * to <tt>TRUE</tt> is identical to the alternate signature with no arguments.
   * @param iThrowIfMultiResultOperation
   * The Boolean argument used to disable the throw behavior for multi-result
   * operations.
   * @return
   * A pointer to the resulting body.
   */
  CATBody *GetResultBody(CATBoolean iThrowIfMultiResultOperation) const;

  /**
   * Returns a <tt>CGMChangeData</tt> that encapsulates the contents of the
   *<tt>CGMPart</tt> before and after the operator is run. <b>Role</b>: If this
   *method is called on an instance that is constructed but never updated
   *through a call to <tt>CGMPart</tt>, then an exception will be thrown.
   * @return
   * The <tt>CGMChangeData</tt> describing changes to the part made by the
   *operator.
   **/
  CGMChangeData GetChangeData() const;

  /**
   * Returns the object tracker for the operation. An object tracker provides
   *data about which input cells and objects correspond to which output cells
   *and objects. <b>Role</b>: If this method is called on an instance that is
   *constructed but never updated through a call to <tt>CGMPart</tt>, then an
   *exception will be thrown.
   * @return
   * The object tracker describing the correspondence between input and output
   *objects.
   **/
  CGMObjectTracker GetObjectTracker() const;

  /**
   * Helper routine to obtain the <tt>CATCGMJournalList</tt> for operators that
   *result in only one body. <b>Role</b>: If this method is called on an
   *instance that is constructed but never updated through a call to
   *<tt>CGMPart</tt>, then an exception will be thrown. This convenience method
   *should only be used if the user knows the operator only has one result
   *<tt>CATBody</tt>. If the operator has multiple result bodies, this method
   *will throw.
   * @param oJournal
   * The journal.
   **/
  void GetJournal(CATCGMJournalList &oJournal) const;

  /**
   * Returns a <tt>CGMJournalIterator</tt> object for the operation.
   * <b>Role</b>: If this method is called on an instance that is constructed
   *but never updated through a call to <tt>CGMPart</tt>, then an exception will
   *be thrown.
   * @return
   * The journal iterator.
   **/
  CGMJournalIterator GetJournalIterator() const;

  /**
   * Returns messages such as warnings for the operation.
   * <b>Role</b>: If this method is called on an instance that is constructed
   *but never updated through a call to <tt>CGMPart</tt>, then an exception will
   *be thrown.
   * @return
   * A message list object containing all messages created by the operation.
   **/
  CGMMessageList GetMessages() const;

  /**
   * Appends the "iOther" CGMModificationResult to this.
   * <b>Role</b>:
   * For use with compound (i.e., multi-operator)  operations.
   * You may only concatenate consecutive results (<tt>iOther</tt> must have
   *come from the operation immediately after the operation producing this.) If
   *iOther is uninitalized by a call to <tt>CGMPart</tt>, then this operation is
   *a no-op.
   * @param iOther
   * The latest result to concatenate with <tt>this</tt>.
   **/
  void Concatenate(CGMModificationResult const &iOther);

  /**
   * Default constructor.
   **/
  CGMModificationResult();

  /**
   * Copy constructor.
   **/
  CGMModificationResult(CGMModificationResult const &iOther);

  /**
   * Assignment operator.
   **/
  CGMModificationResult &operator=(CGMModificationResult const &iOther);

  /**
   * Destructor.
   */
  ~CGMModificationResult();

  /**
   * Checks if *this is a fully constructed
   * object.
   */
  bool IsValid() const;

private:
  friend class ExportedByCGMComponent CGMModificationResultCreator;
  friend class ExportedByCGMComponent CGMPart;
  friend class ExportedByCGMComponent CGMPartFriend;
  CGMModificationResult(CGMIModificationResultImpl *ipImpl);

  void SetMessages(CGMMessageList const &iMessages);

  CGMIModificationResultImpl *_impl;
};

#endif
