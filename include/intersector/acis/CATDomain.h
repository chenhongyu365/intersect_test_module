#ifndef CATDomain_H
#define CATDomain_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */

#include "CATGMModelInterfaces.h"
#include "CATTopology.h"
//#include "CATTopDef.h"
#include "CATCellHashTable.h"
#include "CATTopDefine.h"
class CATMathBox;
class CATCell;
class CATBody;

//-----------------------------------------------------------------------------
#include "CATGMModelInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMModelInterfaces IID IID_CATDomain;
#else
extern "C" const IID IID_CATDomain;
#endif

/**
 * Interface representing a topological domain.
 * <br>A
 * domain (CATDomain) is a connected set of cells (CATCell) of same
 * dimension. Hence, a domain defines a boundary of a cell:
 *<ul><li>a vertex can border:
 *         <ul><li>an egde (the vertex is one of the edge extremities)
 *             <li>a face ( the vertex is immersed into the face:
 * non manifold case -> <tt>CATVertexInFace</tt> domain )
 *             <li>a volume or a body ( the vertex is immersed into the volume:
 * non manifold case -> <tt>CATVertexInVolume</tt> domain) </ul>
 *    <li>an edge can border:
 *         <ul><li>a face ( the edge is one of the face borders
 * -> <tt>CATLoop</tt> domain)
 *             <li>a face ( the edge is immersed into the face:
 * non manifold case -> <tt>CATLoop</tt> domain)
 *             <li>a volume or a body( the edge is immersed into the volume:
 * non manifold case -> <tt>CATWire</tt> domain) </ul>
 *    <li>an face can border (-> <tt>CATShell</tt> domain ):
 *         <ul><li>a volume ( the face is one of the volume borders)
 *             <li>a volume ( the face is immersed into the volume:
 * non manifold case) </ul>
 *    <li>a <tt>CATLump</tt> is a domain of dimension 3.
 *</ul>
 * Note that a vertex can not be immersed into an egde, because it would cut
 * the edge in two pieces. As the same manner, an edge (/face) or a set
 * of edges (/faces) may be immersed into a face (/volume) only if it does
 * not go right through it.<br>
 * A CATDomain is contained into an unique CATCell of higher dimension and is
 * located with regards to this cell in the following manner:
 * <dl><dt><tt>CATLocationInner</tt></dt><dd> For internal boundaries (holes
 * into a faces or cavities into a volumes).
 *     <dt><tt>CATLocationOuter</tt></dt><dd> For external boundaries.
 *     <dt><tt>CATLocationFull</tt></dt><dd> All cells of the domain to
 * create are immersed into the containing cell (non-manifold topology).
 *     <dt><tt>CATLocationIn3DSpace</tt></dt><dd> For creation into a body.</dl>
 * <br>A CATDomain is created with the @href CATBody#CreateDomain method and
 * deleted with the @href CATICGMContainer#Remove method.
 */
class ExportedByCATGMModelInterfaces CATDomain : public CATTopology {
    CATDeclareInterface;

  public:
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //
    //            C A A             M E T H O D S
    //
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    /**
     * Returns the dimension of the CATCells contained into <tt>this</tt> CATDomain.
     * @return
     * The dimension.
     */
    virtual short GetLowDimension() = 0;

    /**
     * Returns the dimension of the unique CATCell containing <tt>this</tt> CATDomain.
     * @return
     * The dimension. If the domain is directly referred by a CATBody, it returns 3.
     */
    virtual short GetHighDimension() = 0;

    /**
     * Returns the location of <tt>this</tt> CATDomain.
     * @param iBodyOrCell
     * The pointer to the Body or Cell, <tt>this</tt> CATDomain belongs to.
     * @return
     * The location.
     * <br><b>Legal values</b>:
     * <dl><dt><tt>CATLocationInner</tt></dt><dd> For internal boundaries (holes
     * into a faces or cavities into a volumes).
     *     <dt><tt>CATLocationOuter</tt></dt><dd> For external boundaries.
     *     <dt><tt>CATLocationFull</tt></dt><dd> All cells of the domain to
     * create are immersed into the containing cell (non-manifold topology).
     *     <dt><tt>CATLocationIn3DSpace</tt></dt><dd> For creation into a body.
     *</dl>
     */
    virtual CATLocation GetLocation(CATTopology* iBodyOrCell = NULL) = 0;

    /**
     * Sets the default location of <tt>this</tt> CATDomain.
     * @param iLocation
     * The location.
     * <br><b>Legal values</b>:
     * <dl><dt><tt>CATLocationInner</tt></dt><dd> For internal boundaries (holes
     * into a faces or cavities into a volumes).
     *     <dt><tt>CATLocationOuter</tt></dt><dd> For external boundaries.
     *     <dt><tt>CATLocationFull</tt></dt><dd> All cells of the domain to
     * create are immersed into the containing cell (non-manifold topology).
     *     <dt><tt>CATLocationIn3DSpace</tt></dt><dd> For creation into a body.
     *</dl>
     */
    virtual void SetLocation(CATLocation iLocation) = 0;

    /**
     * Returns the unique CATCell that owns <tt>this</tt> CATDomain in the context of a CATBody.
     * @param iInBody
     * The pointer to the body in which the bounded cells are searched. Recall
     * that a same CATCell can be used by several bodies.
     * @return
     * The pointer to the found CATCell.
     */
    virtual CATCell* GetOwningCell(CATBody* iInBody) const = 0;

    /**
     * Adds a CATCell into <tt>this</tt> CATDomain.
     * @param iCellToAdd
     * The pointer to the cell to add.
     * @param iOrientation
     * The cell orientation, with regards to the domain orientation.
     */
    virtual void AddCell(CATCell* iCellToAdd, CATOrientation iOrientation = CATOrientationPositive) = 0;

    /**
     * Removes a CATCell from <tt>this</tt> CATDomain.
     * @param iCellToDetach
     * The pointer to the cell to detach from <tt>this</tt>domain.
     * However, the cell still remains in the CATGeoFactory in default mode.
     * @param iRemoveFromFactory
     * The action on the detached cell <tt>iDomainToDetach</tt>.
     * Dedicated to the case where no more CATDomain refers to <tt>iCellToDetach</tt>.
     * <br><b>Legal values</b>:
     * <dl><dt><tt>FALSE</tt></dt><dd> the <tt>iCellToDetach</tt> remains in the factory
     *     <dt><tt>TRUE</tt></dt><dd> the <tt>iCellToDetach</tt> is removed from the factory with RemoveDependancies management</dl>
     */
    virtual void RemoveCell(CATCell* iCellToDetach, CATBoolean iRemoveFromFactory = FALSE) = 0;

    /**
     * Returns the number of CATCells used by <tt>this</tt> CATDomain.
     * @return
     * The number of used cells. If one cell is
     * used more than once within the domain, it is counted twice. The scan is
     * not recursive.
     */
    virtual CATLONG32 GetNbCellUses() = 0;

    /**
     * Returns the given CATCell of <tt>this</tt> CATDomain.
     *<br>The scan is not recursive.
     * @param iNumCell
     * The cell rank (starting at 1).
     * @param ioOrientation
     * A pointer to the cell orientation. If <tt>NULL</tt>,
     * this argument is not filled out.
     * @return
     * The pointer to the corresponding cell.
     */
    virtual CATCell* GetCell(CATLONG32 iNumCell, CATOrientation* oOrientation = NULL) = 0;

    /**
     * Returns the rank (starting at 1) of the CATCell in <tt>this</tt> CATomain. .
     * @param iCell
     * The pointer to cell.
     * @param ioOrientation
     * A pointer to the cell orientation. If <tt>NULL</tt>,
     * this argument is not filled out.
     * @return
     * The result of the search.
     * <br><b>Legal values</b>: 1 if found, 0 if not found.
     */
    virtual CATLONG32 GetCellRank(CATCell* iCell, CATOrientation* ioOrientation = NULL) = 0;

    /**
     * Tests whether a CATCell belongs to <tt>this</tt> CATDomain.
     * @param iCellToTest
     * The pointer to the cell to test.
     * @param ioSide
     * The pointer to the matter side at the boundary.
     * If <tt>NULL</tt>, this argument is not filled out.
     * @return
     * How many times <tt>iCell</tt> bounds <tt>this</tt>.
     */
    virtual int Owns(CATCell* iCellToTest, CATSide* ioSide = NULL) = 0;

    /**
     * Tests whether <tt>this</tt> CATDomain is lying on another one.
     * @param iDomain
     * The pointer to the other domain.
     * @return
     * The result of the test.
     */
    virtual CATTopLyingOnDiagnostic IsLyingOn(CATDomain* iDomain) = 0;

    /**
     * Reverses the order or the orientation in <tt>this</tt> domain where the cells are defined.
     *<table>
     *      <tr><td>Wire, Loop : </td> <td>the edge order is reversed</td></tr>
     *      <tr><td>Shell      : </td> <td>the face orientations in the shell are reversed</td></tr>
     *      <tr><td>otherwise : </td> <td> nothing happens</td></tr></table>
     * <br> To define a valid loop, the edges must be set counter-
     * clockwise for an outer loop and clockwise for an inner loop.
     */
    virtual void Invert() = 0;
};

CATDeclareHandler(CATDomain, CATTopology);

#endif  // CATDomain_H
