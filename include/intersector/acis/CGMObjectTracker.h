/*******************************************************************/
/*    Copyright (c) 2010-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef CGMObjectTracker_H
#define CGMObjectTracker_H


/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CATBody.h"
#include "CATBoolean.h"
#include "CATCGMJournalList.h"
#include "CATListOfCATICGMObjects.h"
#include "CGMComponent.h"
class CGMIObjectTrackerImpl;

/**
 * Class that tracks the relationship between the input and output objects of an
 *operation. <b>Role:</b> The <tt>CGMObjectTracker</tt> provides a mapping from
 *each input cell to its corresponding output cell(s) and vice-versa. The
 *<tt>CGMObjectTracker</tt> tracks <tt>CATICGMObject</tt> objects of type
 *<tt>CATBody</tt>, <tt>CATFace</tt>, <tt>CATEdge</tt>, and <tt>CATVertex</tt>.
 **/
class ExportedByCGMComponent CGMObjectTracker
{
public:
  /**
   * Returns the input objects corresponding to an output object.
   * @param ipOutputObject
   * The output object.
   * @param oInputObjects
   * The input objects corresponding to <tt>iOutputObject</tt>.  Any incoming
   * contents in this list are overwritten.
   */
  void GetInputs(CATICGMObject const *ipOutputObject,
                 CATListPtrCATICGMObject &oInputObjects) const;

  /**
   * Returns the output objects corresponding to an input object.
   * @param ipInputObject
   * The input object.
   * @param oOutputObjects
   * The output objects corresponding to <tt>iInputObject</tt>.  Any incoming
   * contents in this list are overwritten.
   */
  void GetOutputs(CATICGMObject const *ipInputObject,
                  CATListPtrCATICGMObject &oOutputObjects) const;

  /**
   * Returns the operator-specific optional info corresponding to the input and
   * output objects.
   * @param ipInputObject
   * The input object.
   * @param ipOutputObject
   * The output object.
   * @param oInfo
   * The optional info value if available.
   * @return
   * <tt>TRUE</tt>: optional info is available; <tt>FALSE</tt> otherwise.
   */
  CATBoolean GetOptionalInfo(CATICGMObject const *ipInputObject,
                             CATICGMObject const *ipOutputObject,
                             CATLONG32 &oInfo) const;

  /**
   * Returns a list that contains all input objects with non-trivial
   * correspondences.  A trivial correspondence is one in which an input object
   * has itself as its corresponding output object, and has no other input or
   * output correspondences.  This method will include all objects with
   * non-trivial correspondences in the <tt>oInputObjects</tt> list.  In
   * addition, it may also include some objects with trivial correspondences.
   * @param oInputObjects
   * The list containing all input objects with non-trivial correspondences.
   * Any incoming contents in this list are overwritten.
   */
  void GetTrackedInputs(CATListPtrCATICGMObject &oInputObjects) const;

  /**
   * Returns a list that contains all output objects with non-trivial
   * correspondences.  A trivial correspondence is one in which an input object
   * has itself as its corresponding output object, and has no other input or
   * output correspondences.  This method will include all objects with
   * non-trivial correspondences in the <tt>oOutputObjects</tt> list.  In
   * addition it may also include some objects with trivial correspondences.
   * @param oOutputObjects
   * The list containing all output objects with non-trivial correspondences.
   * Any incoming contents in this list are overwritten.
   */
  void GetTrackedOutputs(CATListPtrCATICGMObject &oOutputObjects) const;

  /**
   * Default constructor.
   */
  CGMObjectTracker();

  /**
   * Destructor.
   */
  ~CGMObjectTracker();

  /**
   * Copy constructor.
   * @param iOther
   * The source object tracker.
   */
  CGMObjectTracker(CGMObjectTracker const &iOther);

  /**
   * Assignment operator.
   * @param iOther
   * The source object tracker.
   * @return
   * A reference to the assigned <tt>CGMObjectTracker</tt>.
   */
  CGMObjectTracker &operator=(const CGMObjectTracker &iOther);

  /**
   * @nodoc
   */
  CATBoolean GetJournal(CATBody const *ipJournalBody,
                        CATCGMJournalList &oJournal) const;

  /**
   * @nodoc
   */
  CGMObjectTracker(CGMIObjectTrackerImpl *ipImpl);

private:
  void GetTrackedInputsInternal(CATListPtrCATICGMObject &oInputObjects,
                                CATBoolean iDoContractCheck) const;
  void GetTrackedOutputsInternal(CATListPtrCATICGMObject &oOutputObjects,
                                 CATBoolean iDoContractCheck) const;
  void GetInputsInternal(CATICGMObject const *ipOutputObject,
                         CATListPtrCATICGMObject &oInputObjects,
                         CATBoolean iDoContractCheck) const;
  void GetOutputsInternal(CATICGMObject const *ipInputObject,
                          CATListPtrCATICGMObject &oOutputObjects,
                          CATBoolean iDoContractCheck) const;
  CATBoolean GetOptionalInfoInternal(CATICGMObject const *ipInputObject,
                                     CATICGMObject const *ipOutputObject,
                                     CATLONG32 &oInfo,
                                     CATBoolean iDoContractCheck) const;

  CGMIObjectTrackerImpl *_impl;
};
#endif
