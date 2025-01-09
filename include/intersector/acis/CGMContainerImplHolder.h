/*******************************************************************/
/*    Copyright (c) 2010-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef CGMContainerImplHolder_H
#define CGMContainerImplHolder_H


/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CGMComponent.h"

#include "CATCGMReferenceClassImplHolder.h"

class CGMContainerImpl;

/**
 * @nodoc
 * For internal use only.
 */
class ExportedByCGMComponent CGMContainerImplHolder
{
public:
  /**
   * Default constructor.
   */
  CGMContainerImplHolder();

  /**
   * Copy constructor.
   * @param iOther
   * The <tt>CGMContainerImplHolder</tt> to copy.
   */
  CGMContainerImplHolder(CGMContainerImplHolder const &iOther);

  /**
   * Assignment operator.
   * @param iOther
   * The <tt>CGMContainerImplHolder</tt> to assign to <tt>this</tt>.
   * @return
   * A reference to the assigned <tt>CGMContainerImplHolder</tt>.
   */
  CGMContainerImplHolder &operator=(CGMContainerImplHolder const &iOther);

  /**
   * @nodoc
   * internal use only
   */
  CGMContainerImplHolder(CGMContainerImpl *ipImpl);

  /**
   * Destructor
   */
  ~CGMContainerImplHolder();

  CGMContainerImpl const *GetImpl() const;
  CGMContainerImpl *GetImpl();

  CGMContainerImpl const &GetImplRef() const;
  CGMContainerImpl &GetImplRef();

private:
  CATCGMReferenceClassImplHolder _implHolder;
};

#endif
