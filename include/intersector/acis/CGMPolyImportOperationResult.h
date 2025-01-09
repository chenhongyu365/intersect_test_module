/*******************************************************************/
/*    Copyright (c) 2017-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef CGMPolyImportOperationResult_H
#define CGMPolyImportOperationResult_H


/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CATCGMValueClassImplHolder.h"
#include "CGMCompPoly.h"
#include "CGMPolyImportContainers.h"
#include "CGMPolyImportMesh.h"

namespace CGMPolyImport
{
/**
 * Class holding the results of an <tt>Operator</tt> that was run through
 * <tt>Part::ModifyUsing</tt>. Note that the meshes contained in an
 * <tt>OperationResult</tt> exist in the <tt>Part</tt> from the time
 * <tt>ModifyUsing</tt> was called.
 *
 * This class is designed with "value-class" semantics and is intended to be
 * passed by value.
 */
class ExportedByCGMCompPoly OperationResult
{
public:
  /**
   *  A class defining an iterator over meshes inside an
   * <tt>OperationResult</tt>.
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
     * Check equality to another <tt>Mesh</tt> iterator
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
     * Only the past-the-end iterator (queried from OperationResult::end() )
     * is not dereferenceable.
     * @return
     *	   A <tt>Mesh</tt> object inside an <tt>OperationResult</tt>.
     */
    Mesh operator*() const;

	/**
	 * Returns a Mesh to which the iterator is pointing.
	 * @return
	 *    A <tt>Mesh</tt> object inside an <tt>OperationResult</tt>.
	 */
	Mesh Get() const;

    /** @nodoc */
    Iterator(CGMPolyImport::IteratorImpl<Mesh> *impl);

  private:
    CATCGMValueClassImplHolder _implHolder;

    IteratorImpl<Mesh> const &GetImpl() const;
    IteratorImpl<Mesh> &GetImpl();
  };

  /**
   * Returns an iterator to the first <tt>Mesh</tt> object in the
   *<tt>OperationResult</tt>.
   * @return
   *	The iterator to the first <tt>Mesh</tt> object in the
   *<tt>OperationResult</tt>.  Note that this will be an invalid iterator if the
   *<tt>OperationResult</tt> is empty.
   **/
  Iterator begin() const;

  /**
   * Returns an iterator past the end of the data in the
   *<tt>OperationResult</tt>, which is an invalid iterator.
   * @return
   *	The (invalid) iterator past the end of the data.
   **/
  Iterator end() const;

  /**
   * Returns the number of <tt>Mesh</tt> objects in the
   *<tt>OperationResult</tt>.
   * @return
   *	The number of <tt>Mesh</tt> objects in the <tt>OperationResult</tt>.
   **/
  int Size() const;

  /**
   * Queries whether or not the <tt>OperationResult</tt> is empty.
   * @return
   *	Whether or not the <tt>OperationResult</tt> is empty.
   **/
  bool Empty() const;

  /**
   * The default constructor, which constructs an empty
   * <tt>OperationResult</tt>.
   */
  OperationResult();

  /**
   * Appends another <tt>OperationResult</tt> to this one
   * @param toAppend
   *	The <tt>OperationResult</tt> to append to the end of this one.
   **/
  void Concatenate(OperationResult toAppend);

  /**
   * The (non-virtual) destructor.
   */
  ~OperationResult() {} //= default;

  /**
   * The assignment operator.
   */
  OperationResult &operator=(OperationResult const &other); // = default;

  /**
   * The copy constructor.
   */
  OperationResult(OperationResult const &other); // = default;

  /** @nodoc */
  OperationResult(CGMPolyImport::ContainerImpl<Mesh> *impl);
  /** @nodoc */
  ContainerImpl<Mesh> const &GetImpl() const;
  /** @nodoc */
  ContainerImpl<Mesh> &GetImpl();

private:
  CATCGMValueClassImplHolder _implHolder;
};
} // namespace CGMPolyImport
#endif
