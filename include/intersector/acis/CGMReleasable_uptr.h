/*******************************************************************/
/*    Copyright (c) 2016-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef CGMReleasable_uptr_h
#define CGMReleasable_uptr_h


/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include <memory>
#include <stdexcept>

/** @nodoc */
template <typename T> struct __releaser__CGM
{
  void operator()(T *t)
  {
    if (t)
      t->Release();
  }
};

/**
 * This class implements a unique pointer that calls the Release() method on the
 * pointer when it is time to release the memory. This class may be used to
 * implement RAII type techniques with the CGM Component API. Note that no CGM
 * classes use the smart pointers in their interface.  This code is intended
 * only as a convenience for customer code.
 *
 * Please note: we strongly recommend that you release each operator
 * as soon as you are done using it.  Operators may attach attributes to bodies
 * which are removed when they are released.  Having multiple operators active
 * at the same time can corrupt the model producing bugs which are difficult to reproduce.
 * For this reason you should either
 * (1) write short functions which only use on operator call each (in which case
 * the operators will be automatically cleaned up when you leave the scope) or
 * (2) use the CGMReleasable_uptr::reset method to destroy each operator when you
 * are done using it.
 */
template <typename CGMClassType>
class CGMReleasable_uptr
  : public std::unique_ptr<CGMClassType, __releaser__CGM<CGMClassType>>
{
public:
  /* Constructor for an empty unique pointer */
  CGMReleasable_uptr()
    : std::unique_ptr<CGMClassType, __releaser__CGM<CGMClassType>>()
  {
  }

  /* Constructor to manage a CGM object that is deleted by calling the Release
   * method */
  CGMReleasable_uptr(CGMClassType *pOp)
    : std::unique_ptr<CGMClassType, __releaser__CGM<CGMClassType>>(pOp)
  {
  }

  /* @nodoc */
  CGMReleasable_uptr(CGMReleasable_uptr &&movedFrom)
  {
    this->reset(movedFrom.release());
  }
};

/**
 * Template function to check for null and throw if it is.
 */
template <typename smartPtrType>
void throwIfPointerIsNull(smartPtrType const &ptr)
{
  if (ptr.get() == NULL)
  {
    throw std::logic_error("The unique pointer is empty.");
  }
}

/**
* Wrap releasable object in a CGMReleasable_uptr.  This method
* assumes that the pointer is something owned by the caller;
* when the return value is destructed it will release the input argument.
**/

template<typename T> CGMReleasable_uptr<T> CGMWrapReleasable(T* t) {
  return CGMReleasable_uptr<T>(t);
}


#endif
