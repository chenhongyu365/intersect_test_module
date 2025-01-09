/*******************************************************************/
/*    Copyright (c) 2017-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef CGMPolyImportTriangleContainer_H
#define CGMPolyImportTriangleContainer_H


/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CATCGMReferenceClassImplHolder.h"
#include "CGMCompPoly.h"
#include "CGMMeshGeometry.h"
#include "CGMPolyImportGeometryContainers.h"

namespace CGMPolyImport
{
/**
 * A class storing a collection of triangles all belonging to the same
 * <tt>Mesh</tt> object. This class is designed with "value-class" semantics and
 * is intended to be passed by value.
 */
class ExportedByCGMCompPoly TriangleContainer
{
public:
  /**
   *  A class defining an iterator over triangles inside a
   * <tt>TriangleContainer</tt>.
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
    ~Iterator() {} //= default;

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
     * Check equality to another <tt>Triangle</tt> iterator
     * @param iOther
     *    The input iterator
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
     * Only the past-the-end iterator (queried from TriangleContainer::end() )
     *is not dereferenceable.
     * @return
     *	A <tt>Triangle</tt> object inside a <tt>TriangleContainer</tt>.
     */
    Triangle operator*() const;

    /**
     * Returns a Triangle to which the iterator is pointing.
     * @return
     *	  A <tt>Triangle</tt> object inside a <tt>TriangleContainer</tt>.
     */
    Triangle Get() const;

    /** @nodoc */
    Iterator(CGMPolyImport::GeometryIteratorImpl<Triangle> *impl);

  private:
    CATCGMValueClassImplHolder _implHolder;

    GeometryIteratorImpl<Triangle> const &GetImpl() const;
    GeometryIteratorImpl<Triangle> &GetImpl();
  };

  /**
   * Returns an iterator to the first <tt>Triangle</tt> object in the
   *<tt>TriangleContainer</tt>.
   * @return
   *	The iterator to the first <tt>Triangle</tt> object in the
   *<tt>TriangleContainer</tt>.  Note that this will be an invalid iterator if
   *the <tt>TriangleContainer</tt> is empty.
   **/
  Iterator begin() const;

  /**
   * Returns an iterator past the end of the data in the
   *<tt>TriangleContainer</tt>, which is an invalid iterator.
   * @return
   *	The (invalid) iterator past the end of the data.
   **/
  Iterator end() const;

  /**
   * Adds a <tt>Triangle</tt> into the <tt>TriangleContainer</tt>.
   * @param mesh
   *	The mesh which the triangle belongs to.  If the mesh disagrees with a mesh
   *already captured, an error is thrown.
   * @param t
   *	The triangle to add into the container.
   **/
  void PushBack(Mesh const &mesh, Triangle t);

  /**
   * Returns the number of <tt>Triangle</tt> objects in the
   *<tt>TriangleContainer</tt>.
   * @return
   *	The number of <tt>Triangle</tt> objects in the <tt>TriangleContainer</tt>.
   **/
  int Size() const;

  /**
   * Queries whether or not the <tt>TriangleContainer</tt> is empty.
   * @return
   *	Whether or not the <tt>TriangleContainer</tt> is empty.
   **/
  bool Empty() const;

  /**
   * Returns the unique mesh where all the triangles live.
   * @return
   *	The mesh containing the triangles.  Note that if the container is empty,
   *this method throws.
   **/
  Mesh GetMesh() const;

  /**
   * The default constructor, which constructs an empty
   * <tt>TriangleContainer</tt>.
   */
  TriangleContainer();

  /**
   * The (non-virtual) destructor.
   */
  ~TriangleContainer() {}

  /**
   * The assignment operator.
   */
  TriangleContainer &operator=(TriangleContainer const &other); //= default;

  /**
   * The copy constructor.
   */
  TriangleContainer(TriangleContainer const &other); //= default;

  /** @nodoc */
  TriangleContainer(CGMPolyImport::GeometryContainerImpl<Triangle> *impl);
  /** @nodoc */
  GeometryContainerImpl<Triangle> const &GetImpl() const;
  /** @nodoc */
  GeometryContainerImpl<Triangle> &GetImpl();

private:
  CATCGMReferenceClassImplHolder _implHolder;
  bool _meshLogged;
};
} // namespace CGMPolyImport
#endif
