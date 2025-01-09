/*******************************************************************/
/*    Copyright (c) 2016-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef CGMPolyImportPartIterator_H
#define CGMPolyImportPartIterator_H


/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CATCGMValueClassImplHolder.h"
#include "CATCGMVirtual.h"
#include "CGMCompPoly.h"
#include "CGMPolyImportPart.h"

namespace CGMPolyImport
{
/**
 *  A class defining an iterator over meshes inside a <tt>Part</tt>.
 *
 * Usage:	for( Part::Iterator it = processor.begin(); it != processor.end();
 *++it)
 *			{
 *				Mesh m = *it;
 *				CGMTessBodyFaceSerializer serializer = m.GetSerializer();
 *			}
 *
 * or equivalently,
 *			for(auto const& mesh : processor)
 *			{
 *				auto serializer = mesh.GetSerializer();
 *			}
 *
 * @see Part
 */
class ExportedByCGMCompPoly Part::Iterator
{

public:
  /**
   * The increment operator.
   */
  Iterator &operator++();

  /**
   * To increment the iterator.
   */
  void Increment();

  /**
   * The dereference operator.
   * Only the past-the-end iterator (queried from Part::end() ) is not
   * dereferenceable.
   * @return
   *	A <tt>Mesh</tt> object inside a <tt>Part</tt>.
   */
  Mesh operator*() const;

  /**
   * Returns a mesh to which the iterator is pointing.
   * @return
   *	A <tt>Mesh</tt> object inside a <tt>Part</tt>.
   */
  Mesh Get() const;

  /**
   * The != operator.
   */
  bool operator!=(Iterator const &iOther) const;

  /**
   * The == operator.
   */
  bool operator==(Iterator const &iOther) const;

  /**
   * Check equality to another operator
   * @param iOther
   * The input iterator
   * @return
   * A Boolean value which indicates if <tt>this<tt> iterator and the input
   * iterator are the same.
   */
  bool EqualTo(Iterator const& iOther) const;

  /**
   * The assignment operator.
   */
  Iterator &operator=(Iterator const &iOther); //= default;

  /**
   * The copy constructor.
   */
  Iterator(Iterator const &iOther); //= default;

  /**
   * The (non-virtual) destructor.
   */
  ~Iterator() {}
  class Impl;

private:
  friend class PartImpl;

  CATCGMValueClassImplHolder _implHolder;

  Iterator(Impl const &impl);
  Impl &GetImpl();
  Impl const &GetImpl() const;
};

} // namespace CGMPolyImport
#endif
