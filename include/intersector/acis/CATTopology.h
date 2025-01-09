/* -*-c++-*- */
#ifndef CATTopology_H
#define CATTopology_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATGeometry.h"
#include "ListPOfCATCell.h"
#include "ListPOfCATDomain.h"
#include "CATIAV5Level.h"

class CATCell;
class CATBody;
class CATDomain;
class CATCellHashTable;

#include "CATGMModelInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMModelInterfaces IID IID_CATTopology ;
#else
extern "C" const IID IID_CATTopology ;
#endif

/**
 * Base interface of the cell-complexes, including
 * non manifold, non connected complexes, mixing dimensions of topological cells.
 */
class ExportedByCATGMModelInterfaces CATTopology : public CATGeometry
{
  CATDeclareInterface;
  
public:
  
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/**
 * Returns all the CATCells of a prescribed dimension of <tt>this</tt> CATTopology. 
 * 
 * @param ioResult
 * The list of the resulting cells. Each cell only occurs once in the list.
 * @param iDimension
 * The dimension of the cells.
 *<br><b>Legal values</b>:
 *<dl><dt>-1</dt><dd>All the the dimensions.
 * <dt>0</dt><dd>The vertices.
 *<dt>1</dt><dd>The edges.
 * <dt>2</dt><dd>The faces.
 * <dt>3</dt><dd>The volumes.
 *</dl>
 */  
  virtual void GetAllCells( CATLISTP(CATCell)& ioResult, short iDimension=-1 ) = 0;


/**
 * Returns the number of Vertices, Edges, Faces and Volumes of <tt>this</tt> CATTopology. 
 * 
 * @param iopNbVertices, iopNbEdges, iopNbFaces, ioNbVolumes 
 * The pointers to the output numbers.
 */  
  virtual void GetCellNumbers(int* iopNbVertices, int* iopNbEdges, int* iopNbFaces, int* iopNbVolumes) = 0;

  /**
  * Tests whether <tt>this</tt> CATTopology is recursively defined as a boundary of another CATTopology.
  * @param iBody
  * The pointer to the body inside which the search is done.
  * @param iTopologyInside
  * The pointer to the other CATTopology (that must belong to <tt>iBody</tt>).
  * If <tt>NULL</tt> the search is done in the entire body <tt>iBody</tt>.
  * @param iGenerateUpwardLinks
  * Reserved for future use (do not change the default value).
  * @return
  * The result of the test.
  * <br><b>Legal values:</b>:
  * A <tt>TRUE</tt> value is returned if the body owns <tt>this</tt> CATTopology, <tt>FALSE</tt> otherwise.
  */
  virtual CATBoolean IsInside(CATBody      * iBody, 
                              CATTopology  * iTopologyInside      = NULL,
                              CATBoolean     iGenerateUpwardLinks = FALSE ) = 0;

  /**
  * Tests whether <tt>this</tt> CATTopology is touched.
  * <br>  After its creation a CATToplogy is modifiable.
  *   It becomes non-modifiable when a body containing it is frozen.
  *   For smart manipulations of a body, one can first <tt>Touch</tt> some cells of the body, 
  *   then use a <tt>CATSmartBodyDuplicator</tt> in order to duplicate only the touched cells and 
  *   the domains impacted by these modifications.
  *   A non-modifiable touched cell will be duplicated during the smart duplication inside another body
	* where it the copy will be modifiable.
  * @return
  * The result of the test.
  * <br><b>Legal values</b>:
  * <tt>TRUE</tt> if <tt>this</tt> is touched, <tt>FALSE</tt> otherwise.
  */
  virtual CATBoolean IsTouched()    = 0;

	/**
	 * Declares that <tt>this</tt> CATTopology is touched by an operation inside the context of a given body.
	 * <br>The use of a smart duplicator after this method will duplicate the cells that are touched. 
	 * @param iBodyForImpactPropagation
	 * The pointer to the body inside which the propagation of the modifications of <tt>this</tt> has to be
	 * done.
	 * @see CATSmartBodyDuplicator
	 */
  virtual void       Touch(CATBody* iBodyForImpactPropagation) = 0;


  

  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  
  /**
  * @nodoc
  * Returns all the CATCells of a prescribed dimension in the CATTopology. 
  * <br><tt>iDimension = -1</tt> stands for all the cells.
  * Each cell only occurs once in the hashtable. The hash table is allocated
  * by the method. Think to delete it after usage.
  */
  virtual CATCellHashTable * GetAllCells( short iDimension=-1 )=0;

  /**
  * Returns all the CATDomains of prescribed low and high dimensions of <tt>this</tt> CATTopology. 
  * @param iContainedCellsDimension
  * The dimension of the cells contained into the domain.
  * @param iContainingCellDimension
  * The dimension of the unique cell or body containing the domain.
  * <br> Note that <tt>iContainedCellDimension <= iContainingCellDimension</tt>.
  * For a CATDomain contained into a CATBody, this dimension is 3. 
  * @param ioResult
  * The list of the resulting domains. Each domain only occurs once in the list.
  */  
  virtual void GetAllDomains(short iContainedCellsDimension, 
    short iContainingCellDimension,
    CATLISTP(CATDomain)& ioResult) = 0;
  
  /** @nodoc */
  virtual void PropagateQuery(CATICGMUnknown *iFrom, CATCGMQueryManager &iQuery ) = 0;
};


CATDeclareHandler(CATTopology,CATGeometry);

#endif
