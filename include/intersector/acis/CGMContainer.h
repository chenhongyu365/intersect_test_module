/*******************************************************************/
/*    Copyright (c) 2010-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef CGMContainer_H
#define CGMContainer_H


/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CATCGMNewArray.h"
#include "CATCGMScaleCategoryDef.h"
#include "CATCGMVirtual.h"
#include "CATICGMObject.h"
#include "CGMComponent.h"
#include "CGMContainerImplHolder.h"
#include "ListPOfCATBody.h"

class CATGeoFactory;
class LoadCGMContainer;
class CGMContainerImpl;
class CGMPart;
class CATICGMObject;
class SPALengthUnit;

/**
 *  Container class for all <tt>CATICGMObject</tt> objects.
 *
 * <b>Role</b>: The <tt>CGMContainer</tt> represents a space in which modeling
 * operations on <tt>CATICGMObject</tt> objects take place. Its two
 * responsibilities are to provide a <tt>CATGeoFactory</tt> which is used to
 * create new <tt>CATICGMObject</tt> objects and to provide a <tt>CGMPart</tt>
 * which manages a working set of top-level objects within the space. <br> A
 * <tt>CGMContainer</tt> is created from data on disk using
 * <tt>CGMContainerLoad</tt>, or anew using the global function
 * <tt>CreateCGMContainer</tt>.
 *
 * A CGMContainer is always created on the heap, and clients must call the
 * <tt>Release</tt> method at the end of its lifetime.
 */
class ExportedByCGMComponent CGMContainer : public CATCGMVirtual
{
  friend ExportedByCGMComponent CGMContainer *
  CreateCGMContainer(CATCGMScaleCategory iScaleCategory);
  friend ExportedByCGMComponent CGMContainer *
  CGMWrapCATGeoFactory(CATGeoFactory *ipFactory,
                       CATLISTP(CATICGMObject) & iStateObjects);
  friend class CGMPlayBackEntryImpl;
  friend class CGMContainerHolder;
  friend class CGMContainerConstHolder;
  friend class CGMContainerImpl;

public:
  CATCGMNewClassArrayDeclare;

private:
  CGMContainerImplHolder _implHolder;
  CATBoolean _isReleased;
  CATLONG32 _refCountInternal;

  CGMContainer(CGMContainerImplHolder &ipImpl);
  ~CGMContainer();

  /** @nodoc
   * Copy CTOR and operator= not implemented - prevent users from accidentally
   * calling.
   */
  CGMContainer(const CGMContainer &);
  CGMContainer operator=(const CGMContainer &);

  /** @nodoc
   * Internal method
   */
  void NullOutNCGMPointer();
  /** @nodoc
   * Add ref function for use by internal clients.  Must be paired with calls to
   * ReleaseInternal.
   */
  void AddRefInternal();
  /** @nodoc
   * Release function for use by internal clients.  Must be paired with calls to
   * AddRefInternal. Internal reference count must be zero AND Release() must
   * have been called for *this to delete itself when either Release() or
   * ReleaseInternal() is called.
   */
  void ReleaseInternal();
  /** @nodoc
   * Function to handle release of the container depending on reference count by
   * internal clients and whether Release has been called.
   */
  void OnRelease();
  /** @nodoc
   * Helper function used during creation
   */
  static CGMContainer *Create(CGMContainerImplHolder &iImplHolder);

  /** @nodoc
   * Helper function used during creation
   */
  static CGMContainer *Create(CATGeoFactory *&ipFactory,
                              CATBoolean iOwnFactory,
                              CATLISTP(CATICGMObject) & iTopLevelObjects,
                              CATCGMScaleCategory iScaleCategory);

public:
  /**
   * Clients should always call the <tt>Release</tt> method at the end of the
   * CGMContainer's lifetime.
   */
  void Release() const;

  /**
   * Returns a pointer-to-const to the @href <tt>CGMPart</tt> owned by the
   * <tt>CGMContainer</tt>.
   * @return
   * A pointer to the const <tt>CGMPart</tt> owned by <tt>this</tt> container.
   */
  CGMPart const *GetPart() const;

  /**
   * Returns a pointer to the @href <tt>CGMPart</tt> owned by the
   * <tt>CGMContainer</tt>.
   * @return
   * A pointer to the <tt>CGMPart</tt> owned by <tt>this</tt> container.
   */
  CGMPart *GetPart();

  /**
   * @nodoc
   */
  CGMContainerImpl const *GetImpl() const;

  /**
   * @nodoc
   */
  CGMContainerImpl *GetImpl();

  /**
   * Returns a pointer to the implicit @href <tt>CATGeoFactory</tt> interface
   * used to create <tt>CATICGMObject</tt> objects in this
   * <tt>CGMContainer</tt>. This factory will typically have two uses: to be
   * passed into the the create routine for a <tt>CATOperator</tt>, or to
   * provide creation routines for geometric objects, which will usually be used
   * as input to <tt>CATTopOperator</tt> objects.
   * @return
   * A pointer to the implicit <tt>CATGeoFactory</tt> associated with
   * <tt>this</tt> container.
   */
  CATGeoFactory *GetFactory() const;

  /**
   * @deprecated 2016 1.0
   * The ability to change the model units on a container by calling
   * <tt>SetDynamicRange</tt> will be removed in a future release, but this
   * method to retrieve the model units will continue to be available for the
   * foreseeable future for backward compatibility with legacy data.  The
   * supported approach to specifying a different dynamic range for modeling is
   * to use a scale category during creation of the <tt>CGMContainer</tt>. The
   * scale category can be retrieved using the <tt>GetScaleCategory</tt> method.
   * All data using the model units mechanism should be converted to the scale
   * category mechanism, since this <tt>GetModelUnits</tt> method may also be
   * removed in a future release.
   *
   * Returns the modeling unit associated with this <tt>CGMContainer</tt>.
   * <b>Role</b>: This unit is directly related to the range of lengths that can
   * be represented by the modeler.  See the description of the
   * <tt>SetDynamicRange</tt> method for more details. <br><br> Note that the
   * return value is unrelated to display units.
   * @param oUnit
   * The model unit associated with the container.
   */
  void GetModelUnits(SPALengthUnit &oUnit) const;

  /**
   * Returns the scale category associated with this <tt>CGMContainer</tt>.
   * <b>Role</b>: Use this method to retrieve the dynamic range available for
   * modeling with this container.  The scale category can only be set when
   * creating a new container.  Refer to
   * <tt>CreateCGMContainer(CATCGMScaleCategory iScaleCategory)</tt> for
   * details. Currently, only normal scale
   * (<tt>CATCGMScaleCategory::ScaleN</tt>), large scale
   * (<tt>CATCGMScaleCategory::ScaleL</tt>) and small scale
   * (<tt>CATCGMScaleCategory::ScaleS</tt>) are supported.
   * @return
   * The scale category enumeration value.
   */
  CATCGMScaleCategory GetScaleCategory() const;

  /**
   * Returns the model resolution of this container.
   * <b>Role</b>: Use this method to retrieve the lower bound for the dynamic
   * range available for modeling with this container.
   * @return The model resolution value.
   */
  double GetResolution() const;

  /**
   * Indicates whether this <tt>CGMContainer</tt> owns its underlying
   * <tt>CATGeoFactory</tt>. <b>Role</b>: If a <tt>CGMContainer</tt> was created
   * using <tt>CreateCGMContainer</tt>, then it owns the underlying
   * <tt>CATGeoFactory</tt> and takes responsibility for closing that
   * <tt>CATGeoFactory</tt>. If the <tt>CGMContainer</tt> was created using
   * <tt>CGMWrapCATGeoFactory</tt>, then it does not own the underlying factory,
   * and the client code is responsible for closing that <tt>CATGeoFactory</tt>.
   * @return
   * A Boolean flag indicating whether <tt>this</tt> container owns its
   * underlying <tt>CATGeoFactory</tt>.
   */
  CATBoolean OwnsFactory() const;
};

/**
 * Global function for creating an empty <tt>CGMContainer</tt>.
 * Clients must call the <tt>Release</tt> method at the end of its lifetime.
 * <b>Role</b>: By default, the modeler creates a container in normal scale
 * (<tt>CATCGMScaleCategory::ScaleN</tt>) which means that the range of lengths
 * that can be represented by the modeler corresponds to a minimum edge length
 * of 10<sup>-3</sup> (the modeling resolution) and to a maximum model size of
 * 10<sup>6</sup> in all three dimensions.  Most applications interpret this to
 * correspond to a range of 0.001 mm to 1 km.  Use the create function which
 * takes a <tt>CATCGMScaleCategory</tt> enumeration value as input to create a
 * container with a different dynamic range.
 * @return
 * A pointer to an empty container.
 */
ExportedByCGMComponent CGMContainer *CreateCGMContainer();

/**
 * Global function for creating an empty <tt>CGMContainer</tt> with the
 * specified dynamic range. Clients must call the <tt>Release</tt> method at the
 * end of its lifetime. <b>Role</b>: This function allows users to create a
 * container using a dynamic range of their choice.  The currently supported
 * scale categories are: <li> normal scale
 * (<tt>CATCGMScaleCategory::ScaleN</tt>) - dynamic range of 10<sup>-3</sup> to
 * 10<sup>6</sup> <li> large scale (<tt>CATCGMScaleCategory::ScaleL</tt>) -
 * dynamic range of 10<sup>-1</sup> to 10<sup>8</sup> <li> small scale
 * (<tt>CATCGMScaleCategory::ScaleS</tt>) - dynamic range of 10<sup>-5</sup> to
 * 10<sup>4</sup>
 * @return
 * A pointer to an empty container.
 */
ExportedByCGMComponent CGMContainer *
CreateCGMContainer(CATCGMScaleCategory iScaleCategory);

/**
 * Global function for creating a <tt>CGMContainer</tt> that is a wrapper for a
 * <tt>CATGeoFactory</tt> owned by the application. <b>Role</b>: Unlike the
 * <tt>CGMContainer</tt> created by <tt>CreateCGMContainer</tt>, this
 * <tt>CGMContainer</tt> does not control the lifetime of the
 * <tt>CATGeoFactory</tt> that it wraps.  In addition, all objects created by
 * <tt>CGMPart::ModifyUsing</tt> will be implicit, unless an explicit
 * <tt>CATGeoFactory</tt> is passed in. The intent of this function is to allow
 * a customer, for example one who has written CAA-style applications, to
 * temporarily create a <tt>CGMContainer</tt> that wraps their
 * <tt>CATGeoFactory</tt>.  You should take care to only have a single
 * <tt>CGMContainer</tt> wrapping a particular <tt>CATGeoFactory</tt> at any one
 * time.
 * @param ipFactory
 * The <tt>CATGeoFactory</tt> to be wrapped.
 * @param iStateObjects
 * A list of top-level <tt>CATICGMObject</tt> objects which will be inserted
 * into the initial state of the <tt>CGMPart</tt>. These should already exist in
 * ipFactory.
 * @return
 * The <tt>CGMContainer</tt> that wraps <tt>ipFactory</tt>.
 */
ExportedByCGMComponent CGMContainer *
CGMWrapCATGeoFactory(CATGeoFactory *ipFactory,
                     CATLISTP(CATICGMObject) & iStateObjects);

#endif
