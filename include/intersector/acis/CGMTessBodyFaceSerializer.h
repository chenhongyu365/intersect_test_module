/*******************************************************************/
/*    Copyright (c) 2015-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef CGMTessBodyFaceSerializer_H
#define CGMTessBodyFaceSerializer_H


/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CATCGMValueClassImplHolder.h"
#include "CATGMModelCmpInterfaces.h"

class CATBody;
class CATEdge;
class CATFace;
class CGMTessellateId;
class CGMTessBodyFaceSerializerImpl;

/**
 * Serializes the body face tessellation data into compact arrays of floats,
 *doubles, and integers. The buffers must be allocated before calls to the
 *serialize methods, and their sizes should be large enough to contain the data.
 *
 * <b>Role:</b>This class is designed with "value-class" semantics; it is
 *intended to be owned and passed by value, rather than being allocated on the
 *heap. To minimize memory consumption, use these objects as locally as
 *possible.
 **/
class ExportedByCATGMModelCmpInterfaces CGMTessBodyFaceSerializer
{
public:
  /**
   * Default constructor.
   **/
  CGMTessBodyFaceSerializer();
  /**
   * Copy constructor.
   **/
  CGMTessBodyFaceSerializer(CGMTessBodyFaceSerializer const &iOther);

  /**
   * Assignment operator.
   **/
  CGMTessBodyFaceSerializer &operator=(CGMTessBodyFaceSerializer const &iOther);

  /**
   * Destructor.
   */
  ~CGMTessBodyFaceSerializer();

  /**
   * Returns the tessellation ID associated to the CATFace.
   * @param oTessId
   *   The output <tt>CGMTessellateId</tt> object.
   */
  void GetTessellateId(CGMTessellateId &oTessId) const;

  /**
   * Returns a pointer to the <tt>CATBody</tt> that is tessellated.
   * @return
   *   The <tt>CATBody</tt> that is tessellated.
   */
  CATBody *GetBody();

  /**
   * Directs this object to serialize the size of each triangular polygon
   * (that is, the number �3� preceding the triangle�s data).  This method must
   * Make sure you call this function (if necessary) before calling
   * GetSizeOfTriangleBuffer and GetTriangles.  This function is included for
   * easy compatibility with Hoops.
   * @param iDoIncludePolygonSize
   * When this flag is set to <tt>TRUE</tt>, the triangles are serialized as
   * follows: <br> <tt>3 t0v0 t0v1 t0v2 3 t1v0 t1v1 t1v2 ... 3 tnv0 tnv1
   * tnv2</tt>. <br> Otherwise, the triangles are serialized as follows: <br>
   * <tt>t0v0 t0v1 t0v2 t1v0 t1v1 t1v2 ... tnv0 tnv1 tnv2</tt>.
   * <br>
   * By default this flag is set to <tt>FALSE</tt>.
   */
  void SerializePolygonSize(CATBoolean iDoIncludePolygonSize);

  /**
   * Returns the number of nodes to be serialized.
   * @return
   *   The number of the triangle nodes (i.e., triangle vertices).
   */
  int GetNbNodes() const;

  /**
   * Returns the number of triangles to be serialized.
   * @return
   *   The number of the triangles.
   */
  int GetNbTriangles() const;

  /**
   * Returns the required size of the buffer for serialization of the node
   * positions.
   * @return
   *   The size of the node positions buffer.
   */
  int GetSizeOfNodePositionBuffer() const;

  /**
   * Returns the required size of the buffer for serialization of the node
   * normals. The method may return 0 if no normal is available.
   * @return
   *   The size of the node normals buffer.
   */
  int GetSizeOfNodeNormalBuffer() const;

  /**
   * Returns the required size of the buffer for serialization of the node UV
   * parameters. The method may return 0 if no parameter is available.
   * @return
   *   The size of the node UV parameters buffer.
   */
  int GetSizeOfNodeParamBuffer() const;

  /**
   * Returns the required size of the buffer for serialization of the triangles.
   * The size of the buffer is equal to 3 times the number of triangles.
   * @return
   *   The size of the triangle indices buffer.
   */
  int GetSizeOfTriangleBuffer() const;

  /**
   * Serializes the node position coordinates into a float buffer.
   * The buffer must be pre-allocated, and its size should be at least
   * GetSizeOfNodePositionBuffer().
   * @param ioNodePositionBuffer
   *    The positions buffer.
   */
  void GetNodePositions(float *ioNodePositionBuffer) const;

  /**
   * Serializes the node normal coordinates into a float buffer.
   * The buffer must be pre-allocated, and its size should be at least
   * GetSizeOfNodeNormalBuffer().
   * @param ioNodeNormalBuffer
   *    The normal vectors buffer.
   */
  void GetNodeNormals(float *ioNodeNormalBuffer) const;

  /**
   * Serializes the node UV parameters into a float buffer.
   * The buffer must be pre-allocated, and its size should be at least
   * GetSizeOfNodeParamBuffer().
   * @param ioNodeParamBuffer
   *    The parameters buffer.
   */
  void GetNodeParamValues(float *ioNodeParamBuffer) const;

  /**
   * Serializes the node position coordinates into a double buffer.
   * The buffer must be pre-allocated, and its size should be at least
   * GetSizeOfNodePositionBuffer().
   * @param ioNodePositionBuffer
   *    The positionss buffer.
   */
  void GetNodePositions(double *ioNodePositionBuffer) const;

  /**
   * Serializes the node normal coordinates into a double buffer.
   * The buffer must be pre-allocated, and its size should be at least
   * GetSizeOfNodeNormalBuffer().
   * @param ioNodeNormalBuffer
   *    The normal vectors buffer.
   */
  void GetNodeNormals(double *ioNodeNormalBuffer) const;

  /**
   * Serializes the node UV parameters into a double buffer.
   * The buffer must be pre-allocated, and its size should be at least
   * GetSizeOfNodeParamBuffer().
   * @param ioNodeParamBuffer
   *    The parameter vectors buffer.
   */
  void GetNodeParamValues(double *ioNodeUVBuffer) const;

  /**
   * Serializes the triangle nodes into an integer buffer.
   * The buffer must be pre-allocated, and its size should be at least
   * GetSizeOfTriangleBuffer().
   * @param ioTriangleNodeIndices
   *    The triangle indices buffer.
   */
  void GetTriangles(int *ioTriangleNodeIndices) const;

  /**
   * For use with GetSurfaceNodeIndices.  Provides the size of the buffer needed
   *to store the node indices on an edge.
   * @param iEdge
   *    The edge to get the points from
   * @return
   *   The size of the indices buffer.
   **/

  int GetSizeOfSurfaceNodeIndexBuffer(CATEdge &iEdge) const;

  /**
   * Serializes the points on iEdge into ioIndexBuffer.
   * @param iEdge
   *    The edge to get the points from
   * @param ioIndexBuffer
   *    The indices buffer.
   **/
  void GetSurfaceNodeIndices(CATEdge &iEdge, int *ioIndexBuffer) const;

  /* @nodoc
   * For internal use only
   */
  CGMTessBodyFaceSerializer(CGMTessBodyFaceSerializerImpl *ipImpl);

/**
*  @nodoc.  Internal use only.
*/
  DECLARE_USE_COUNTED_GET_IMPL_METHODS(CGMTessBodyFaceSerializer);

protected:
  CATCGMValueClassImplHolder _implHolder;
};
#endif
