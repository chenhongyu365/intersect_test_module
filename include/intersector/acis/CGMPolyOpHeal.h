/*******************************************************************/
/*    Copyright (c) 2019-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef CGMPolyOpHeal_H2
#define CGMPolyOpHeal_H2

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CGMCompPoly.h"
#include "CGMPolyImportMeshContainer.h"
#include "CGMPolyImportOperator.h"

namespace CGMPolyImport
{
class HealImpl;

/**
 * Enumeration for specifying how CGMPolyImport::Heal deals with sliver volumes.
 * The current modes are eRemoveSliverVolumes (which removes sliver volumes)
 * and eKeepSliverVolumes which does not remove sliver volumes.
 **/
enum SliverVolumeMode
{
  eRemoveSliverVolumes,
  eKeepSliverVolumes
};

/**
 * Enumeration for specifying what CGMPolyImport::Heal does with shells with
 * strict containment. The default behavior is to have one shell per mesh. On
 * request, CGMPolyImport::Heal can combine shells where there is a proper
 * containment into a common mesh.
 **/
enum ShellContainmentMode
{
  eOneShellPerMesh,
  eCombineContainedShells
};

/**
 * Automatically heals the input mesh by performing a sequence of healing
 * operations that separate disconnected components, remove intersections, fix
 * orientation problems, fix non-manifold inputs (bars shared by more than 2
 * triangles), and close the mesh into a solid if desired. The operator assumes
 * a solid result is desired unless you call <tt>SetCloseMesh(false)</tt>. If
 * other healing methods fail to fix the problems in the input mesh, global
 * voxel remeshing will be used unless you call
 * <tt>SetUseVoxelHealAsFallback(false)</tt>.
 *
 * All PolyImport operators require a CGMPolyImport::Part to use. The basic
 * usage to heal a mesh is:
 *
 * CGMPolyImport::OperationResult exampleUsage(CGMPolyImport::Part &ioPart,
 *                                             CGMPolyImport::Mesh iMesh)
 * {
 *   CGMReleasable_uptr<CGMPolyImport::Heal> op =
 *       CGMPolyImport::Heal::Create(iMesh);
 *   return ioPart.ModifyUsing(op.get());
 * }
 *
 * The OperationResult holds the result meshes.
 */
class ExportedByCGMCompPoly Heal : public Operator
{
public:
  /**
   * Creates a <tt>Heal</tt> operator.
   * @param iMesh
   *	The mesh to be operated on.
   * @return
   *	The <tt>Heal</tt> operator.
   */
  static Heal *Create(Mesh const &iMesh);

  /**
   * Determines whether the operator will try to close the mesh to
   * make a solid if the input has holes (true by default)
   * @param doCloseMesh
   *	Flag that determines whether to close the mesh.
   */
  virtual void SetCloseMesh(bool doCloseMesh) = 0;

  /**
   * Determines whether to use voxel healing as a fallback method if
   * other healing methods fail (true by default).
   * @param doVoxelHeal
   *	Flag that determines whether voxel healing is used as a fallback method.
   */
  virtual void SetUseVoxelHealAsFallback(bool doVoxelHeal) = 0;

  /**
   * Determines the level of detail if voxel healing is used (default 8.0)
   * See details in CGMPolyOpRemeshByVoxel.h
   * @param iLod
   *	The level of detail.
   */
  virtual void SetVoxelHealingLevelOfDetail(double iLod) = 0;

  /**
   * To be called after running. If any connected components of the input mesh
   * failed to be healed, this method will return them, otherwise it will be
   * empty
   */
  virtual MeshContainer GetFailedMeshes() const = 0;

  /**
   * To be called after running and calling <tt>GetFailedMeshes</tt>. If any
   * connected components of the input mesh failed to be healed, this method
   * will return the anomalies associated with them. Only call this method with
   * meshes that were returned by <tt>GetFailedMeshes()</tt>, otherwise an empty
   * <tt>AnomalyContainer</tt> will always be returned.
   */
  virtual AnomalyContainer GetFailedMeshAnomalies(Mesh const &mesh) const = 0;

  /**
   * Sets policy for dealing with sliver volumes. When this option
   * is eRemoveSliverVolumes (default behavior) the operator treats the sliver
   * volumes as noise.  When the mode is
   * eKeepSliverVolumes, sliver volumes are kept.
   * @param iMode
   *    An enum to set the thin feature preservation mode. The default
   *    value is <tt>eRemoveSliverVolumes</tt>
   */
  virtual void SetSliverVolumeMode(SliverVolumeMode iMode) = 0;

  /**
   * Sets policy for dealing with containment of shells resulting from healing.
   * The default behavior is to put each shell into its own mesh.  Optionally,
   * the user can select <tt>eCombineContainedShells</tt> in which case,
   * the operator will do a containment analysis between the shells
   * combining shells where there is a strict containment.
   * @param iMode
   *    An enum to set the shell containment mode. The default
   *    value is <tt>eOneShellPerMesh</tt>
   */
  virtual void SetShellContainmentMode(ShellContainmentMode iMode) = 0;

  /**
   * Determines whether to use decimation (false by default).
   * @param iMode
   *    Flag that determines whether decimation is used.
   *    The default value is false.
   * @param iTolerance
   *    Decimation tolerance. The value of <tt>iTolerance</tt> must be positive
   *    otherwise decimation will not be performed.
   */
  virtual void SetDecimation(bool iMode, double iTolerance) = 0;

  /**
   * Determines whether the operation Remove Intersecting Slivers (RIS)
   * will be performed or not (true by default).
   * Setting this option to false can significantly improve performance
   * for meshes with a large number of triangles. However, in some cases, the 
   * RIS step is required to fully heal the mesh.
   * @param iDoRIS
   *	  Flag that determines whether to remove intersecting slivers.
   */
  virtual void SetDoRIS(bool iDoRIS) = 0;

  /**
   * @nodoc
   **/
  virtual HealImpl *GetImpl() = 0;

protected:
  virtual ~Heal() {}
  Heal();

private:
  Heal &operator=(Heal const &iOther);
  Heal(Heal const &iOther);
};
} // namespace CGMPolyImport

#endif
