/*******************************************************************/
/*    Copyright (c) 2016-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef CGMPolyImportPart_H
#define CGMPolyImportPart_H

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CATCGMReferenceClassImplHolder.h"
#include "CGMCompPoly.h"
#include "stddef.h"

class CGMPart;
class CGMModificationResult;
class CATTolerance;
class CATSoftwareConfiguration;

namespace CGMPolyImport
{
class Operator;
class OperationResult;
class StateId;
class Mesh;
class MeshBuffer;
class PartImpl;
class StateIdImpl;
class TriangleTagMap;

/**
 * Class used for cleaning up polygonal mesh data before it can be used for
 * modeling operations within the <tt>CGMPart</tt>. <b>Role</b>: As of CGM
 * Release 2018 1.0, a <tt>CATBody</tt> can contain polyhedral geometry.
 *
 * The specification of a <tt>CATBody</tt> requires that it never has any
 * geometric anomalies; for imported mesh data there is no guarantee that the
 * data forms a valid polyhedral <tt>CATBody</tt>. This class acts as a
 * quarantine for mesh data that is not ready to be used as a <tt>CATBody</tt>.
 * The methods <tt>CreateAllBodies</tt> and <tt>CreateBody</tt> are used to
 * create a <tt>CATBody</tt>(s) out of the data inside the
 * <tt>CGMPolyImport::Part</tt> and add these bodies to the <tt>CGMPart</tt>.
 *
 * Remaining anomalies on a particular mesh can be checked using the
 * <tt>Check</tt> method. Several operators are provided for healing meshes with
 * anomalies.
 * @see CGMPolyImport::Operator
 *
 * This class is designed with "value-class" semantics and is intended to be
 * passed by value.
 */
class ExportedByCGMCompPoly Part
{
public:
  class Iterator;

  /**
   * Returns an iterator to the first mesh in the <tt>Part</tt>.
   * @return
   *	The iterator to the first mesh in the <tt>Part</tt>.  Note that this will
   *be an invalid iterator if the <tt>Part</tt> is empty.
   **/
  Iterator begin() const;

  /**
   * Returns an iterator past the end of the data in the <tt>Part</tt>, which is
   *an invalid iterator.
   * @return
   *	The (invalid) iterator past the end of the data.
   **/
  Iterator end() const;

  /**
   * Returns whether or not the <tt>Part</tt> is empty.
   * @return
   *	Whether or not the <tt>Part</tt> is empty.
   **/
  bool Empty() const;

  /**
   * Returns the number of <tt>Mesh</tt> objects currently in the <tt>Part</tt>.
   * @return
   *	The number of <tt>Mesh</tt> objects currently in the <tt>Part</tt>.
   **/
  int Size() const;

  /**
   * Creates a <tt>CATBody</tt> for each mesh inside the <tt>Part</tt>.
   * If a mesh doesn't form a valid <tt>CATBody</tt>, it throws with a helpful
   *error message. If the construction is successful, the <tt>Part</tt> empties
   *its contents, invalidating any <tt>Part::Iterator</tt> in scope.
   * @param ioPart
   *	The <tt>CGMPart</tt> to add the resulting bodies to.
   * @param oFaceToInputTag
   *    (Optional) Pointer to a <tt>CGMPolyImport::TriangleTagMap</tt>.
   *    This will be populated so that it maps faces of each newly created
   *    <tt>CATBody</tt> to the tag of the corresponding triangles in the
   *    input mesh.
   * @return
   *	A <tt>CGMModificationResult</tt> describing the transaction.
   **/
  CGMModificationResult
  CreateAllBodies(CGMPart &ioPart, TriangleTagMap *oFaceToInputTag = nullptr);

  /**
   * Creates a <tt>CATBody</tt> from a <tt>Mesh</tt> if possible and adds it to
   *the <tt>CGMPart</tt>.
   * @param ioPart
   *	The <tt>CGMPart</tt> to add the resulting body to.
   * @param iMesh
   *	The mesh to convert to a <tt>CATBody</tt>.
   * @param oFaceToInputTag
   *    (Optional) Pointer to a <tt>CGMPolyImport::TriangleTagMap</tt>.
   *    This will be populated so that it maps faces of the newly created
   *    <tt>CATBody</tt> to the tag of the corresponding triangles in the
   *    input mesh.
   * @return
   *	A <tt>CGMModificationResult</tt> describing the transaction.
   **/
  CGMModificationResult
  CreateBody(CGMPart &ioPart,
             Mesh const &iMesh,
             TriangleTagMap *oFaceToInputTag = nullptr) const;

  /**
   * Removes <tt>Mesh</tt> from the <tt>Part</tt>.
   * Invalidates any <tt>Part::Iterator</tt> upon successful removal.
   * @param iMesh
   *	<tt>Mesh</tt> to remove.
   **/
  void Remove(Mesh &iMesh);

  /**
   * Runs a modification operation.
   * Operations that are not one-to-one, such as Separate and Stitch, invalidate
   *any Iterator in scope.
   * @param ipOperator
   *	The operator to run.  The Operator should already know about its input(s)
   *when being passed to <tt>ModifyUsing</tt>.
   **/
  OperationResult ModifyUsing(Operator const *ipOperator);

  /**
   * Saves the current state.
   * @return
   *	The <tt>StateId</tt> capturing the current list of meshes.
   **/
  StateId NoteState() const;

  /**
   * Returns to a recorded state.
   * @param iToState
   *	The state (list of meshes) to return to.
   **/
  void ChangeState(StateId const &iToState);

  /**
   * The (non-virtual) destructor.
   **/
  ~Part();

  /**
   * The copy constructor.  This only creates a reference to <tt>iOther</tt>.
   */
  Part(Part const &iOther); //= default;

  /**
   * The assignment operator.  This only creates a reference to <tt>iOther</tt>.
   */
  Part &operator=(Part const &iOther); //= default;

  /**
   * Adds a buffered mesh and takes ownership of the data inside iMeshBuffer.
   * @param iMeshBuffer
   *	The mesh to add into the <tt>Part</tt>.
   */
  OperationResult AddMesh(MeshBuffer &iMeshBuffer);

  /**
   * Constructor.
   */
  Part(CGMPart &iPart);

  /**
   * The default constructor.
   * Using this constructor will create a <tt>CGMPolyImport::Part</tt> that uses
   * the default scale. Use the other constructor or the function
   * <tt>CGMPolyImport::Part::SetCGMPart</tt> to change the scale.
   */
  Part();

  /**
   * Change the <tt>CGMPart</tt> that this <tt>CGMPolyImport::Part</tt> is
   * associated with.
   */
  void SetCGMPart(CGMPart &iPart);

  /**
   * Returns the <tt>CGMPart</tt> that this CGMPolyImport::Part is associated
   * with.
   */
  CGMPart *GetCGMPart() const;

  /**
   * Get the modeler tolerance object. Note that this is determined by the
   * <tt>CGMPart</tt>.
   */
  const CATTolerance &GetToleranceObject() const;

  /**
   * @brief Controls whether the methods CGMPolyImport::Part::CreateBody
   * and CGMPolyImport::Part::CreateAllBodies may subdivide bars in the
   * meshes to create more faces.  This alters the input geometry,
   * but may improve performance due to better spatial partitioning
   * in internal algorithms.  Subdivisions will only occur if
   * the input mesh has a bounding box > 1% of the allowed model size.
   * By default, subdivision is authorized.
   *
   * @param doAuthorize
   */
  void AuthorizeMeshSubdivisionInBodyCreation(bool doAuthorize);

  /**
   * @brief Returns a bool indicating whether mesh subdivisions
   * are allowed when creating polyhedral CATBody objects.
   * See the docs for AuthorizeMeshSubdivisionInBodyCreation
   * for details about what the flag does.
   **/
  bool IsMeshSubdivisionInBodyCreationAuthorized() const;
  /**
   * Get the software configuration from the <tt>CGMPart</tt>.
   */
  CATSoftwareConfiguration *GetSoftwareConfiguration() const;

  /** @nodoc */
  DECLARE_USE_COUNTED_GET_IMPL_METHODS(Part);

  /**
   * Set the number of threads to use in supported importer operations.
   * Note: static setting on the part.
   * @param numberOfThreads
   *	Number of threads to use.
   */
  static void SetNumberOfThreads(int numberOfThreads);

  /**
   * Get the number of threads used in supported importer operations.
   * @return
   *	Number of threads to use.
   */
  static int GetNumberOfThreads();

  friend class PartImpl;

private:
  Part(PartImpl *impl);

  // Data
  CATCGMReferenceClassImplHolder _implHolder;

  // Helpers
  PartImpl const &Impl() const;
  PartImpl &ImplNonConst();
  size_t GetUniqueID() const;
};
} // namespace CGMPolyImport
// header included as a convenience for clients
#include "CGMPolyImportOperationResult.h"
#include "CGMPolyImportPartIterator.h"
#endif
