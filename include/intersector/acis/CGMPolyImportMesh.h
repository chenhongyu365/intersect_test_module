/*******************************************************************/
/*    Copyright (c) 2016-2022 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef CGMPolyImportMesh_H
#define CGMPolyImportMesh_H

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CATCGMReferenceClassImplHolder.h"
#include "CATMathPoint.h"
#include "CGMCompPoly.h"
#include "CGMMeshGeometry.h"
#include "CGMPolyImportAnomalyContainer.h"
#include "CGMPolyImportBarContainer.h"
#include "CGMPolyImportGeometryContainers.h"
#include "CGMPolyImportNodeContainer.h"
#include "CGMPolyImportPart.h"
#include "CGMPolyImportTriangleContainer.h"
#include "CGMTessBodyFaceSerializer.h"
class CATMathBox;

namespace CGMPolyImport
{
class CATListValHoleBoundary;
/**
 * Class used to represent mesh geometry.
 *
 * Use an <tt>Operator</tt> with <tt>Part::ModifyUsing</tt> to make
 * modifications to one or several <tt>Mesh</tt> objects.
 * This class is designed with "value-class" semantics and is intended
 * to be passed by value.
 **/
class ExportedByCGMCompPoly Mesh
{

public:
  /**
   * Gets all the triangles in this <tt>Mesh</tt>.
   * @return
   *   A container storing the triangles in the mesh.
   * @see TriangleContainer
   **/
  TriangleContainer GetAllTriangles() const;

  /**
   * Gets all the nodes in this <tt>Mesh</tt>.
   * @return
   *   A container storing the nodes in the mesh.
   * @see NodeContainer
   **/
  NodeContainer GetAllNodes() const;

  /**
   * Gets the three nodes of a triangle.
   * @param t
   *   The input triangle.
   * @return
   *   The three nodes of an input triangle.
   * @see NodeContainer
   **/
  NodeContainer GetNodes(Triangle t) const;

  /**
   * Gets the two nodes of a bar.
   * @param b
   *   The input bar.
   * @return
   *   The two nodes of an input bar.
   * @see NodeContainer
   **/
  NodeContainer GetNodes(Bar b) const;

  /**
   * Gets the neighbors of a given node.
   * @param n
   *   The input node.
   * @return
   *   The set of nodes connected to the input node by a bar.
   * @see NodeContainer
   **/
  NodeContainer GetNodeNeighbors(Node n) const;

  /**
   * Gets the neighbors of a given Triangle.
   * @param t
   *   The input triangle.
   * @return
   *   The set of triangles connected to the input triangle by a bar.
   * @see TriangleContainer
   **/
  TriangleContainer GetTriangleNeighbors(Triangle t) const;

  /**
   * Gets the physical position of a node.
   * @param n
   *   The input node.
   * @return
   *   The physical position of the node.
   **/
  CATMathPoint GetPosition(Node n) const;

  /**
   * Gets the int label of a node.
   * @param n
   *   The input node.
   * @return
   *   The internal int tag of the node.
   **/
  CATULONG64 GetID(Node n) const;

  /**
   * Gets the int label of a triangle.
   * @param t
   *   The input triangle.
   * @return
   *   The internal int tag of the triangle.
   **/
  CATULONG64 GetID(Triangle t) const;

  /**
   * Returns a serializer for visualization or export.
   * @return
   *   The serialized information which can be used to query raw
   *   rendering arrays.
   **/
  CGMTessBodyFaceSerializer GetSerializer() const;

  /**
   * Tests the mesh for watertightness.
   * @return
   *   A container holding the border bars of the mesh. A border bar is
   *   defined as a bar that touches only one triangle. If the container
   *   is empty, the mesh is watertight.
   **/
  BarContainer IsWatertight() const;

  /**
   * Checks what problems exist on this mesh.
   * @return
   *   A container holding the list of anomalies on the mesh
   **/
  AnomalyContainer Check() const;

  /**
   * Returns the bounding box of this mesh.
   * @return
   *   The bounding box of the mesh.
   **/
  CATMathBox GetBoundingBox() const;

  /**
   * Method for getting all the boundaries of this mesh.
   * This method is convenient to get the boundaries required as inputs when
   * using CGMPolyImport::FillHolesNonPlanar.
   **/
  CATListValHoleBoundary GetBoundaries() const;

  /**
   * Returns the area this mesh.
   * @return
   *   The area of the mesh.
   **/
  double GetArea() const;

  /**
   * Maps input node to index in the serialized array corresponding to this
   * mesh.
   * @return
   *   Serialized index corresponding to the given node.
   **/
  int GetSerializedNodeIndex(Node iNode);

  /**
   * Maps input serialized index to corresponding mesh node.
   * @return
   *   Node corresponding to serialized index.
   **/
  Node GetNode(int iSerializedNodeIndex);

  /**
   * Maps input triangle to index in the serialized array corresponding to this
   * mesh.
   * @return
   *   Serialized index corresponding to the given triangle.
   **/
  int GetSerializedTriangleIndex(Triangle iTriangle);

  /**
   * Maps input serialized index to corresponding mesh triangle.
   * @return
   *   Triangle corresponding to serialized index.
   **/
  Triangle GetTriangle(int iSerializedTriangleIndex);

   /**
   * Gets the tag of the given triangle.
   * @return
   *	Returns a (positive) tag if one has been assigned, and 0 if no tag has
   *    been assigned to the triangle.
   */
  int GetTag(Triangle iTriangle);

  /**
   * Returns <tt>true</tt> if any of the triangles in the mesh have tags
   * assigned to them.
  */
  bool HasTaggedTriangles() const;

  /**
   * The == operator.
   **/
  bool operator==(Mesh const &iOther) const;

  /**
   * The != operator.
   **/
  bool operator!=(Mesh const &iOther) const;

  /**
   * The copy constructor.
   **/
  Mesh(Mesh const &iOther); // = default;

  /**
   * The assignment operator.
   **/
  Mesh &operator=(Mesh const &other); // = default;

  /**
   * The (non-virtual) destructor.
   **/
  ~Mesh() {} // = default;

  /** @nodoc **/
  class Impl;
  /** @nodoc **/
  Mesh(CGMPolyImport::Mesh::Impl *impl);
  /** @nodoc **/
  Impl const &GetImpl() const;
  /** @nodoc **/
  Impl &GetImpl();

private:
  friend class CGMPolyImportPartImpl;

  Mesh();
  // data:
  CATCGMReferenceClassImplHolder _implHolder;
};

} // namespace CGMPolyImport
#endif
