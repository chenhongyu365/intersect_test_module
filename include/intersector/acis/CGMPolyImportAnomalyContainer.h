/*******************************************************************/
/*    Copyright (c) 2017-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef CGMPolyImportAnomalyContainer_H
#define CGMPolyImportAnomalyContainer_H


/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CATCGMCheckAnomaly.h"
#include "CATCGMValueClassImplHolder.h"
#include "CGMCompPoly.h"
#include "CGMMeshGeometry.h"
#include "CGMPolyImportContainers.h"

namespace CGMPolyImport
{
class Mesh;

/**
 * A class storing a collection of anomalies.  This container is queryable
 * from <tt>Mesh::Check()</tt>. This class is designed with "value-class" 
 * semantics and is intended to be passed by value.
 */
class ExportedByCGMCompPoly AnomalyContainer
{
  /**
   *  A class defining an iterator over anomalies inside an
   * <tt>AnomalyContainer</tt>.
   */
public:
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
    bool operator==(Iterator const &iOther) const;

    /**
     * Check equality to another <tt>Anomaly</tt> iterator
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
     * Only the past-the-end iterator (queried from AnomalyContainer::end() ) is
     *not dereferenceable.
     * @return
     *	A <tt>Anomaly</tt> object inside a <tt>AnomalyContainer</tt>.
     */
    Anomaly operator*() const;

    /**
     * Returns a Anomaly to which the iterator is pointing.
     * @return
     *    A <tt>Anomaly</tt> object inside a <tt>AnomalyContainer</tt>.
     */
    Anomaly Get() const;

    /** @nodoc */
    Iterator(CGMPolyImport::IteratorImpl<Anomaly> *impl);

  private:
    CATCGMValueClassImplHolder _implHolder;

    IteratorImpl<Anomaly> const &GetImpl() const;
    IteratorImpl<Anomaly> &GetImpl();
  };

  /**
   * Returns an iterator to the first <tt>Anomaly</tt> object in the
   *<tt>AnomalyContainer</tt>.
   * @return
   *	The iterator to the first <tt>Anomaly</tt> object in the
   *<tt>AnomalyContainer</tt>.  Note that this will be an invalid iterator if
   *the <tt>AnomalyContainer</tt> is empty.
   **/
  Iterator begin() const;

  /**
   * Returns an iterator past the end of the data in the
   *<tt>AnomalyContainer</tt>, which is an invalid iterator.
   * @return
   *	The (invalid) iterator past the end of the data.
   **/
  Iterator end() const;

  /**
   * Adds an <tt>Anomaly</tt> object into the <tt>AnomalyContainer</tt>.
   * @param a
   *	The anomaly to add into the container.
   **/
  void PushBack(Anomaly a);

  /**
   * Returns the number of <tt>Anomaly</tt> objects in the
   *<tt>AnomalyContainer</tt>.
   * @return
   *	The number of <tt>Anomaly</tt> objects in the <tt>AnomalyContainer</tt>.
   **/
  int Size() const;

  /**
   * Queries whether or not the <tt>AnomalyContainer</tt> is empty.
   * @return
   *	Whether or not the <tt>AnomalyContainer</tt> is empty.
   **/
  bool Empty() const;

  /**
  * Selects a subset of the anomalies in this container and copies them into a
  * new <tt>AnomalyContainer</tt>.
  * @param iStart
  * Start index. Must satisfy <tt>0 <= iStart <= iEnd</tt>.
  * @param iEnd
  * End index. Must satisfy <tt>iStart <= iEnd <= this->Size()</tt>.
  * @return 
  * An <tt>AnomalyContainer</tt> holding the anomalies indexed from
   * <tt>iStart</tt> up to but not including <tt>iEnd</tt> from this container.
  **/
  AnomalyContainer Slice(int iStart, int iEnd) const;

  /**
   * The default constructor, which constructs an empty
   * <tt>AnomalyContainer</tt>. Deprecated; use the constructor that takes a
   * <tt>Mesh</tt>.
   */
  [[deprecated("This constructor is deprecated. Please use the constructor that takes a Mesh instead.")]]
  AnomalyContainer();

  /**
   * Constructs an empty <tt>AnomalyContainer</tt> associated with the mesh
   * <tt>iMesh</tt>.
   */
  AnomalyContainer(const Mesh &iMesh);

  /**
   * Gets the mesh associated with the anomalies in this container.
   */
  CGMPolyImport::Mesh GetMesh() const;

  /**
   * The (non-virtual) destructor.
   */
  ~AnomalyContainer() {} //= default;

  /**
   * The assignment operator.
   */
  AnomalyContainer &operator=(AnomalyContainer const &other); // = default;

  /**
   * The copy constructor.
   */
  AnomalyContainer(AnomalyContainer const &other); // = default;

  /** @nodoc **/
  class Impl;
  /** @nodoc **/
  AnomalyContainer(CGMPolyImport::AnomalyContainer::Impl *impl);
  /** @nodoc **/
  Impl const &GetImpl() const;
  /** @nodoc **/
  Impl &GetImpl();

private:
  CATCGMValueClassImplHolder _implHolder;
};
} // namespace CGMPolyImport
#endif
