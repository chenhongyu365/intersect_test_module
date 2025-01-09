/*******************************************************************/
/*    Copyright (c) 2017-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef CGMPolyImportBarContainer_H
#define CGMPolyImportBarContainer_H


/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CATCGMValueClassImplHolder.h"
#include "CGMCompPoly.h"
#include "CGMPolyImportGeometryContainers.h"

namespace CGMPolyImport
{

/**
 * A class storing a collection of bars all belonging to the same <tt>Mesh</tt>
 * object. This class is designed with "value-class" semantics and is intended
 * to be passed by value.
 */
class ExportedByCGMCompPoly BarContainer
{
public:
  /**
   *  A class defining an iterator over bars inside a <tt>BarContainer</tt>.
   */
  class ExportedByCGMCompPoly Iterator
  {
  public:
    /**
     * The copy constructor.
     */
    Iterator(Iterator const &other); //= default;

    /**
     * The (non-virtual) destructor.
     */
    ~Iterator() {}

    /**
     * The assignment operator.
     */
    Iterator &operator=(Iterator const &other); //= default;

    /**
     * The != operator.
     */
    bool operator!=(Iterator const &other) const;

    /**
     * The == operator.
     */
    bool operator==(Iterator const &other) const;

    /**
     * Check equality to another <tt>Bar</tt> iterator
     * @param iOther
     *    The input iterator.
     * @return
     *    A Boolean value which indicates if <tt>this<tt> iterator 
     *    and the input iterator are the same.
     */
    bool EqualTo(Iterator const &iOther) const;

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
     * Only the past-the-end iterator (queried from BarContainer::end() ) is not
     *dereferenceable.
     * @return
     *	A <tt>Bar</tt> object inside a <tt>BarContainer</tt>.
     */
    Bar operator*() const;

    /**
     * Returns a Bar to which the iterator is pointing.
     * @return
     *    A <tt>Bar</tt> object inside a <tt>BarContainer</tt>.
     */
    Bar Get() const;

    /** @nodoc */
    Iterator(CGMPolyImport::GeometryIteratorImpl<Bar> *impl);

  private:
    CATCGMValueClassImplHolder _implHolder;

    GeometryIteratorImpl<Bar> const &GetImpl() const;
    GeometryIteratorImpl<Bar> &GetImpl();
  };

  /**
   * Returns an iterator to the first <tt>Bar</tt> object in the
   *<tt>BarContainer</tt>.
   * @return
   *	The iterator to the first <tt>Bar</tt> object in the
   *<tt>BarContainer</tt>.  Note that this will be an invalid iterator if the
   *<tt>BarContainer</tt> is empty.
   **/
  Iterator begin() const;

  /**
   * Returns an iterator past the end of the data in the <tt>BarContainer</tt>,
   *which is an invalid iterator.
   * @return
   *	The (invalid) iterator past the end of the data.
   **/
  Iterator end() const;

  /**
   * Returns the number of <tt>Bar</tt> objects in the <tt>BarContainer</tt>.
   * @return
   *	The number of <tt>Bar</tt> objects in the <tt>BarContainer</tt>.
   **/
  int Size() const;

  /**
   * Queries whether or not the <tt>BarContainer</tt> is empty.
   * @return
   *	Whether or not the <tt>BarContainer</tt> is empty.
   **/
  bool Empty() const;

  /**
   * Returns the unique mesh where all the bars live.
   * @return
   *	The mesh containing the bars.  Note that if the container is empty, this
   *method throws.
   **/
  Mesh GetMesh() const;

  /**
   * The default constructor, which constructs an empty <tt>BarContainer</tt>.
   */
  BarContainer();

  /**
   * The (non-virtual) destructor.
   */
  ~BarContainer() {} //= default;

  /**
   * The copy constructor.
   */
  BarContainer(BarContainer const &other); //= default;

  /**
   * The assignment operator.
   */
  BarContainer &operator=(BarContainer const &other); //= default;

  /** @nodoc */
  BarContainer(CGMPolyImport::GeometryContainerImpl<Bar> *impl);
  /** @nodoc */
  GeometryContainerImpl<Bar> const &GetImpl() const;
  /** @nodoc */
  GeometryContainerImpl<Bar> &GetImpl();

private:
  CATCGMValueClassImplHolder _implHolder;
};
} // namespace CGMPolyImport
#endif
