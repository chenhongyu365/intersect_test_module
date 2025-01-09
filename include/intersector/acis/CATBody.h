#ifndef CATBody_H
#define CATBody_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */

#include "CATTopObject.h"
#include "CATDomain.h"
#include "CATCellHashTable.h"

#include "ListPOfCATCell.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATEdge.h"
#include "ListVOfLong.h"
#include "CATMathDef.h"
#include "ListPOfCATConnectedCellsIterator.h"
#include "CATTopData.h"
#include "CATIAV5Level.h"

class CATMathVector;
class CATSurface;

class CATGeoFactory;
class CATCell;
class CATVolume;
class CATFace;
class CATEdge;
class CATVertex;
class CATDomain;
class CATLump;
class CATShell;
class CATWire;
class CATVertexInVolume;
class CATLoop;
class CATVertexInFace;

class CATSmartBodyDuplicator;
class CATICGMSmartBodyDuplicator;
class CATCGMJournalList;

#include "CATGMModelInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMModelInterfaces IID IID_CATBody ;
#else
extern "C" const IID IID_CATBody ;
#endif

/**
 * Interface representing a topological body.
 *<br>
 * A body is a set of cells with the following conditions:
 *<ul><li>If one of the cells belongs to the body, all the bounding cells also
 *        belong to this body.
 *    <li>If two cells of a same body are intersecting together, their
 *        intersection is a set of cells belonging to this body.
 *     <li> Cells can be shared between several bodies.
 *</ul>
 *This interface is dedicated to represent all kind of cell-complexes including
 * non-manifold, non connected complexes, mixing dimensions of topological cells.
 * The boundaries of a body are grouped into
 * domains (CATDomain), connected sets of cells (CATCell) of same
 * dimension. This definition is unique.
 *<ul><li>a vertex can border:
 *         <ul><li>an egde (the vertex is one of the edge extremities)
 *             <li>a face ( the vertex is immersed inside the face:
 * non manifold case -> <tt>CATVertexInFace</tt> domain )
 *             <li>a volume or a body ( the vertex is immersed into the volume:
 * non manifold case -> <tt>CATVertexInVolume</tt> domain) </ul>
 *    <li>an edge may border:
 *         <ul><li>a face ( the edge is one of the face borders
 * -> <tt>CATLoop</tt> domain)
 *             <li>a face ( the edge is immersed inside the face:
 * non manifold case -> <tt>CATLoop</tt> domain)
 *             <li>a volume or a body( the edge is immersed inside the volume:
 * non manifold case -> <tt>CATWire</tt> domain) </ul>
 *    <li>an face may border (-> <tt>CATShell</tt> domain ):
 *         <ul><li>a volume ( the face is one of the volume borders)
 *             <li>a volume ( the face is immersed into the volume:
 * non manifold case) </ul>
 *    <li>a <tt>CATLump</tt> is a domain of dimension 3.
 *</ul>
 * Note that a vertex can not be immersed inside an egde, because it would cut
 * the edge in two pieces. As the same manner, an edge (/face) or a set
 * of edges (/faces) may be immersed inside a face (/volume) only if it does
 * not go right through it.
 * A CATCell is composed of CATDomains of lower dimension.
 * The CATBody interface is the factory of all domains and cells that it owns.
 * A CATBody is created with the
 *  @href CATGeoFactory#CreateBody method and deleted with the @href CATICGMContainer#Remove method.
 */
class ExportedByCATGMModelInterfaces CATBody : public CATTopObject
{
  CATDeclareInterface;

public:
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


  //----------------------------------------------------------------------
  // CATBody As Cell's Factory
  //----------------------------------------------------------------------

/**
 * Creates a topological cell of a given dimension.
 * @param iDimension
 * <dl><dt>0</dt><dd> Creates a CATVertex
 *    <dt>1</dt><dd> Creates a CATEdge
 *    <dt>2</dt><dd> Creates a CATFace
 *    <dt>3</dt><dd> Creates a CATVolume </dl>
 */
  virtual CATCell     * CreateCell( short iDimension )=0;

/**
 * Creates a volume.
 * @return
 * The pointer to the created volume (cell of dimension 3)
 */
  virtual CATVolume   * CreateVolume()=0;

/**
 * Creates a face.
 * @return
 * The pointer to the created face (cell of dimension 2)
 */
  virtual CATFace     * CreateFace()=0;

/**
 * Creates an edge.
 * @return
 * The pointer to the created edge (cell of dimension 1)
 */
  virtual CATEdge     * CreateEdge()=0;

/**
 * Creates a vertex.
 * @return
 * The pointer to the created vertex (cell of dimension 0)
 */
  virtual CATVertex   * CreateVertex()=0;


  //----------------------------------------------------------------------
  // CATBody As Domains's Factory
  //----------------------------------------------------------------------

/**
 * Creates a topological domain.
 *<br>A CATDomain is composed of connected cells
 * of same dimension. It represents a cell boundary.
 * @param iContainedCellsDimension
 * The dimension of the cells contained into the domain to create.
 * @param iContainingCellDimension
 * The dimension of the unique cell containing the domain to create.
 *<br> Note that <tt>iContainedCellDimension <= iContainingCellDimension</tt>.
 * For a CATDomain contained into a CATBody, this dimension is 3.
 * @param iLocation
 * The location of the contained cells relative to the containing cell.
 * <dl><dt><tt>CATLocationInner</tt></dt><dd> For internal boundaries (holes
 * into a faces or cavities into a volumes).
 *     <dt><tt>CATLocationOuter</tt></dt><dd> For external boundaries.
 *     <dt><tt>CATLocationFull</tt></dt><dd> All cells of the domain to
 * create are immersed into the containing cell (non-manifold topology).
 *     <dt><tt>CATLocationIn3DSpace</tt></dt><dd> For creation into a body.
 *</dl>
 */
  virtual CATDomain   * CreateDomain( short iContainedCellsDimension,
    short iContainingCellDimension=3,
    CATLocation iLocation=CATLocationIn3DSpace)=0;

/**
 * Creates a topological domain (called lump) which contained cells are CATVolumes.
 * <br>It corresponds to <tt>iContainedCellsDimension = 3,
 * iContainingCellDimension = 3</tt>.
 * @return
 * The pointer to the created lump.
 */
  virtual CATLump           * CreateLump()=0;

/**
 * Creates a topological domain (called shell) which contained connected cells are CATFaces.
 * <br>It corresponds to <tt>iContainedCellsDimension = 2,
 * iContainingCellDimension = 3</tt>.
 * @param iLocation
 * The location of the contained cells relative to the containing cell.
 * <dl><dt><tt>CATLocationInner</tt></dt><dd> For internal boundaries (
 * cavities into volumes).
 *     <dt><tt>CATLocationOuter</tt></dt><dd> For external boundaries.
 *     <dt><tt>CATLocationFull</tt></dt><dd> All cells of the domain to
 * create are immersed into the containing cell (non-manifold topology).
 *     <dt><tt>CATLocationIn3DSpace</tt></dt><dd> For creation into a body.
 *</dl>
 * @return
 * The pointer to the created shell.
 */
  virtual CATShell          * CreateShell( CATLocation iLocation)=0;

/**
 * Creates a topological domain representing a set of connected edges (called wire) of a
 * body or a volume.
 * <br>It corresponds to <tt>iContainedCellsDimension = 1,
 * iContainingCellDimension = 3</tt>.
 * @return
 * The pointer to the created wire.
 */
  virtual CATWire           * CreateWire()=0;

/**
 * Creates a topological domain representing a vertex immersed inside a volume.
 * <br>It corresponds to <tt>iContainedCellsDimension = 0,
 * iContainingCellDimension = 3</tt>.
 * @return
 * The pointer to the created VertexInVolume domain.
 */
  virtual CATVertexInVolume * CreateVertexInVolume()=0;

/**
 * Creates a topological domain (called loop) representing a set of connected egdes bounding
 * a face .
 * <br>It corresponds to <tt>iContainedCellsDimension = 1,
 * iContainingCellDimension = 2</tt>. The loop may be closed or not.
 * @param iLocation
 * The location of the contained cells relative to the containing cell.
 * <dl><dt><tt>CATLocationInner</tt></dt><dd> For internal boundaries (holes
 * into a faces).
 *     <dt><tt>CATLocationOuter</tt></dt><dd> For external boundaries.
 *     <dt><tt>CATLocationFull</tt></dt><dd> All cells of the domain to
 * create are immersed into the containing cell (non-manifold topology).
 *</dl>
 * @return
 * The pointer to the created loop.
 */
  virtual CATLoop           * CreateLoop( CATLocation iLocation)=0;

/**
 * Creates a topological domain representing a vertex immersed inside a face.
 * <br>It corresponds to <tt>iContainedCellsDimension = 0,
 * iContainingCellDimension = 2</tt>.
 * @return
 * The pointer to the created VertexInFace domain.
 */
  virtual CATVertexInFace   * CreateVertexInFace()=0;


  //----------------------------------------------------------------------
  // CATBody Constuction Management
  //----------------------------------------------------------------------
 /**
 * Adds a CATDomain to <tt>this</tt> CATBody.
 * @param iDomainToAdd
 * The pointer to the domain to add, which location must be set to
 * <tt>CATLocationIn3DSpace</tt>.
 * @param iLocation
 * The location of the domain to bound <tt>this</tt>.
 */
  virtual void AddDomain( CATDomain * iDomainToAdd, CATLocation iLocation=CATLocationIn3DSpace  )=0;


/**
 * @nodoc
 * Creates a smart duplicator.
 *<br>This is used in the context of the "smart mechanism".
 *   When a body is frozen, the cells and domains that it contains cannot be modified anymore.
 * To allow an operator to operate on cells of a frozen body,
 *   the smart duplicator only duplicates the touched cells and
 *   domains. Hence:
 *<ul>
 *    <li> This is used to duplicate or share cells and domains from <tt>iBodyToRecopy</tt> into <tt>this</tt>.
 *    <li> a cell or domain will be duplicated if it is non-modifiable and touched,
 *      otherwise, it will be shared
 *    <li> <tt>iBodyToRecopy</tt> and <tt>this</tt> can be the same body.
 *</ul>
 * @param iBodyToRecopy
 * The frozen body where cells are touched.
 * @param iTopData
 * The object defining the CATSoftwareConfiguration and the CATCGMJournalList.
 * @return
 * The pointer to the created duplicator. After use, you
 * have to <tt>delete</tt> it.
 * @see CATSmartBodyDuplicator
 */
  virtual CATSmartBodyDuplicator*  CreateSmartDuplicator(CATBody* iBodyToRecopy, CATTopData &iTopData)=0;

/**
 * Creates a smart duplicator.
 *<br>This is used in the context of the "smart mechanism".
 *   When a body is frozen, the cells and domains that it contains cannot be modified anymore.
 * To allow an operator to operate on cells of a frozen body,
 *   the smart duplicator only duplicates the touched cells and
 *   domains. Hence:
 *<ul>
 *    <li> This is used to duplicate or share cells and domains from <tt>iBodyToRecopy</tt> into <tt>this</tt>.
 *    <li> a cell or domain will be duplicated if it is non-modifiable and touched,
 *      otherwise, it will be shared
 *    <li> <tt>iBodyToRecopy</tt> and <tt>this</tt> can be the same body.
 *</ul>
 * @param iBodyToRecopy
 * The frozen body where cells are touched.
 * @param iTopData
 * The object defining the CATSoftwareConfiguration and the CATCGMJournalList.
 * @return [out, IUnknown#Release]
 * The pointer to the created duplicator. After use, you
 * have to <tt>Release</tt> it.
 * @see CATICGMSmartBodyDuplicator
 */
  virtual CATICGMSmartBodyDuplicator*  CreateISmartDuplicator(CATBody* iBodyToRecopy, CATTopData &iTopData)=0;

  //----------------------------------------------------------------------
  // CATBody Specialized Analysis Services
  //----------------------------------------------------------------------

  /**
  *  Gets information on the dimensions in <tt>this</tt> body.
  *  @param ioCellsMaxDim
  * The maximum dimension of the cells.
  *  @param ioIsHomogeneous
  * The homogeneity in dimension.
  * <br><b>Legal values</b>:
  * <dl><dt><tt>TRUE</tt></dt><dd>Every domain at the higest level has the same dimension <tt>ioCellsMaxDim</tt>.
  *      <dt><tt>FALSE</tt> <dd>otherwise.</dl>
  *  @param IsLocallyManifold
  * If not <tt>NULL</tt>, it will be filled by :
  *  <dl><dt> <tt>TRUE</tt></dt><dd>if <tt>ioIsHomogeneous</tt> is <tt>TRUE</tt>
  * and the body is locally <tt>ioCellsMaxDim</tt>-Manifold
  *  <dt> <tt>FALSE</tt></dt> <dd>otherwise</dl>
  *  @param oNonManifoldCells
  * The optional pointer to a list containing the cells that lead to a non manifold context.
  */
  virtual void GetCellsHighestDimension(CATLONG32& ioCellsMaxDim,CATBoolean& ioIsHomogeneous,
    CATBoolean* ioIsLocallyManifold = NULL, ListPOfCATCell * oNonManifoldCells = NULL) = 0;

/**
 * Retrieves the number of manifold domains inside a list of cells.
 * @param iCellList
 * The pointer to the list of cells to handle.
 * @param oNbOfCellsByDomain
 * The number of manifold groups.
 */
  virtual CATLISTP(CATCell) GroupCells(const CATLISTP(CATCell) * iCellList,
    CATListOfLong          & ioNbOfCellsByDomain ) = 0;


/**
 * Tests whether <tt>this</tt> CATBody is lying on another one.
 * @param iDomain
 * The body on which <tt>this</tt> may lay.
 * @return
 * The diagnosis of the test.
 */
  virtual CATTopLyingOnDiagnostic IsLyingOn(CATBody* iDomain) = 0;


/**
 * @nodoc
 * @deprecated V5R14 Completed.
 * <br>Use now @href CATICGMObject#Completed with the <tt>TRUE</tt> value.
 * Freezes the contents of <tt>this</tt> body.<br> Further modifications of this
 * body will imply that all modified elements will be copied first,
 * thus keeping the current body state unmodified.
 */
  virtual void Freeze() = 0;



  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


/**
 * @nodoc
 * Returns the implicit factory associated with <tt>this</tt> CATBody.
 */
  virtual CATGeoFactory * GetFactory() = 0;

  /**
   * @nodoc
	 * Clean touched topology inside <tt>this</tt>.
	 * @see CATSmartBodyDuplicator
	 */
  virtual void CleanTouch() = 0;


/**
 * @nodoc
 * Creates a smart duplicator.
 *<br>This is used in the context of the "smart mechanism".
 *   When a body is frozen, the cells and domains that it contains cannot be modified anymore.
 * To allow an operator to operate on cells of a frozen body,
 *   the smart duplicator only duplicates the touched cells and
 *   domains. Hence:
 *<ul>
 *    <li> This is used to duplicate or share cells and domains from <tt>iBodyToRecopy</tt> into <tt>this</tt>.
 *    <li> a cell or domain will be duplicated if it is non-modifiable and touched,
 *      otherwise, it will be shared
 *    <li> <tt>iBodyToRecopy</tt> and <tt>this</tt> can be the same body.
 *</ul>
 * @param iBodyToRecopy
 * The frozen body where cells are touched.
 * @param iReport
 * The pointer to a journal that logs the duplication. If <tt>NULL</tt>, nothing is written.
 * @return
 * The pointer to the created duplicator. After use, you
 * have to <tt>delete</tt> it.
 * @see CATSmartBodyDuplicator
 */
  virtual CATSmartBodyDuplicator*  CreateSmartDuplicator(CATBody* iBodyToRecopy, CATCGMJournalList* iReport=NULL)=0;

/**
 * @nodoc
 * Creates a smart duplicator.
 *<br>This is used in the context of the "smart mechanism".
 *   When a body is frozen, the cells and domains that it contains cannot be modified anymore.
 * To allow an operator to operate on cells of a frozen body,
 *   the smart duplicator only duplicates the touched cells and
 *   domains. Hence:
 *<ul>
 *    <li> This is used to duplicate or share cells and domains from <tt>iBodyToRecopy</tt> into <tt>this</tt>.
 *    <li> a cell or domain will be duplicated if it is non-modifiable and touched,
 *      otherwise, it will be shared
 *    <li> <tt>iBodyToRecopy</tt> and <tt>this</tt> can be the same body.
 *</ul>
 * @param iBodyToRecopy
 * The frozen body where cells are touched.
 * @param iReport
 * The pointer to a journal that logs the duplication. If <tt>NULL</tt>, nothing is written.
 * @return [out, IUnknown#Release]
 * The pointer to the created duplicator. After use, you
 * have to <tt>Release</tt> it.
 * @see CATSmartBodyDuplicator
 */
  virtual CATICGMSmartBodyDuplicator*  CreateISmartDuplicator(CATBody* iBodyToRecopy, CATCGMJournalList* iReport=NULL)=0;

  //-----------------------------------------------------------------------------------
  // Propagation types  describe the way edges or faces are selected by propagation.
  //------------------------------------------------------------------------------------
/** @nodoc */
  enum CATPropagationTypePr3 {CATEdgePropagManual=0, CATEdgePropagAuto=1, CATEdgePropagStopOnCorner=2, CATEdgePropagUnknown=666};
/** @nodoc */
  enum CATReflectPropagationType {CATStandard, CATKeepEdge, CATKeepFace};

/**
 * @nodoc
 *  Tangency Propagation on <tt>this</tt> body
 */
  virtual CATLISTP(CATCell) CATEdgePropagate(CATLISTP(CATCell) * iInitialEdges,
    CATPropagationTypePr3 iPropagationType,
	CATLISTP(CATEdge) * iRollingEdges = NULL) = 0;
 /** @nodoc */
  virtual CATLISTP(CATFace) CATFacePropagate(CATLISTP(CATFace) * iInitialFaces) = 0;


/**
 * @nodoc
 * Groups the list of cells in connex and manifold groups (cells of dimension N connected by
 * cells of dimension N-1).
 * @param iCellList
 * The pointer to the list of cells to handle.
 * @param ioCellsIterator
 * The pointer to the iterator on the manifold groups.
 */
  virtual void GroupCells(const CATLISTP(CATCell) * iCellList,
    CATLISTP(CATConnectedCellsIterator) & ioCellsIterator ) = 0;


/**
 * @nodoc
 * Returns the list of edges bounding at least one face in each specified list of faces
 */
  virtual CATLISTP(CATCell) CommonEdges(const CATLISTP(CATCell) * iFaceList_1,
    const CATLISTP(CATCell) * iFaceList_2,
    CATListOfLong          & oListOrientation,
    CATListOfLong          & oNbOfEdgesByDomain ) = 0;


/**
 * @nodoc
 * Returns the immediate neighbour cells of same dimension of the specified cells' list
 */
  virtual CATLISTP(CATCell) CellNeighbours(const CATLISTP(CATCell) * iCellList,
    const CATListOfLong     * iListOrientation,
    CATListOfLong           & oNbOfCellsByDomain,
    const short iVersionGenericNaming = 0 ) = 0;

/**
 * @nodoc
 * Returns the edges frontier of the specified cells' list.
 */
  virtual CATLISTP(CATCell) SelectEdgesFromFaces(const CATLISTP(CATFace) * iFaceList) = 0;


/**
 * @nodoc
 * Special method for Reflect Line Propagation
 */
  virtual CATLISTP(CATFace) FacePropagateReflectLine(CATReflectPropagationType  Propagation,
    const CATMathVector        &PullingDirection,
    const CATAngle            &Angle,
    const CATLISTP(CATFace)   *iInitialFaces) = 0;

/**
 * @nodoc
 * Checks the intersections between the wires of <tt>this</tt> body.
 * @param iSurface
 * The pointer to the surface on which the wire is laying on (if it is).
 */
  virtual CATBoolean CheckWiresIntersection(CATSurface *iSurface = NULL) = 0;

};


CATDeclareHandler(CATBody,CATTopology);

#endif
