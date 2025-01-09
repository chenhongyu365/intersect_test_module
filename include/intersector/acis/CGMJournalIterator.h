/*******************************************************************/
/*    Copyright (c) 2011-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef CGMJournalIterator_h
#define CGMJournalIterator_h


/**
 * @CAA2Level L0
 * @CAA2Usage U1
 */

#include "CATBoolean.h"
#include "CATCGMJournalList.h"
#include "CATDataType.h"
#include "CATMathPoint.h"
#include "CGMComponent.h"
class CGMIModificationResultImpl;
class CATBody;


/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

/**
 * Class used to iterate over individual journals obtained from
 *<tt>CGMModificationResult</tt>
 **/
class ExportedByCGMComponent CGMJournalIterator
{
public:
  /**
   * Sets the iterator to the location before the first point.  To get to the
   *first point, call <tt>Reset</tt>, then <tt>GoToNext</tt>.
   **/
  void Reset();

  /**
   * Returns the current <tt>CATCGMJournalList</tt> and corresponding
   *<tt>CATBody</tt>, returns TRUE if succeeded.
   * @return
   * A Boolean indicating success or failure.
   **/
  CATBoolean GetNextJournal(CATCGMJournalList &oJournal,
                            CATBody *&opJournalBody);

  /**
   * @nodoc
   **/
  CGMJournalIterator();

  /**
   * @nodoc
   **/
  CGMJournalIterator(CGMJournalIterator const &iOther);

  /**
   * @nodoc
   **/
  ~CGMJournalIterator();

  /**
   * @nodoc
   **/
  CGMJournalIterator &operator=(CGMJournalIterator const &iOther);

  /**
   * @nodoc. Internal use only.
   **/
  CGMJournalIterator(CGMIModificationResultImpl *iImpl);

private:
  CGMIModificationResultImpl *_impl;
  int _index;
};
#endif
