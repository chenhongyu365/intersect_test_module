#ifndef CATTopObject_H
#define CATTopObject_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
* @CAA2Level L1
* @CAA2Usage U3
*/ 

#include "CATTopology.h"
#include "CATTopDef.h"
#include "CATGMModelInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMModelInterfaces IID IID_CATTopObject ;
#else
extern "C" const IID IID_CATTopObject ;
#endif

class CATBody;
class CATDomain;
/**
* Base interface representing a <tt>CATBody</tt> or a <tt>CATCell</tt>.
*/

class ExportedByCATGMModelInterfaces CATTopObject : public CATTopology
{
  
  CATDeclareInterface;
  
public :
  
   //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
   //
   //            C A A             M E T H O D S
   //
   //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 
/**
* Returns the number of CATDomains of <tt>this</tt> CATTopObject.
* @return
* The number of domains.
  */
  virtual CATLONG32 GetNbDomains()=0;
  
  /**
  * Returns the <tt>iNum</tt>-th CATDomain of <tt>this</tt> CATTopObject.
  * @param iNum
  * The domain number starting at 1.
  * @param oLocation
  * The pointer to the corresponding CATLocation. If <tt>NULL</tt> in input, this is not output.
  * @return
  * The pointer to the <tt>iNum</tt>-th CATDomain.
  */
  virtual CATDomain* GetDomain(CATLONG32 iNum, CATLocation *oLocation=NULL ) = 0;    
  
  /**
  * Adds a CATDomain to <tt>this</tt> CATTopObject.
  * <br>For bodies, volumes and faces only.
  * @param iDomain
  * The pointer to the domain to add.
  * @param iLocation
  * The location of the domain to bound <tt>this</tt>.
  */
  virtual void AddDomainWithLocation( CATDomain * iDomain, CATLocation iLocation )=0;
  
  /**
  * Removes a CATDomain from <tt>this</tt> CATTopObject. 
  * <br>For bodies, volumes and faces only.
  * @param iDomainToDetach
  * The pointer to the domain to detach from <tt>this</tt>. The domain still remains in the CATGeoFactory,
  * but is not a boundary of <tt>this</tt> anymore in default mode.
  * @param iRemoveFromFactory
  * The action on the detached domain <tt>iDomainToDetach</tt>.
  * Dedicated to the case where no more CATTopObject refers to <tt>iDomainToDetach</tt>.
  * <br><b>Legal values</b>:
  * <dl><dt><tt>FALSE</tt></dt><dd> the <tt>iDomainToDetach</tt> remains in the factory
  *     <dt><tt>TRUE</tt></dt><dd> the <tt>iDomainToDetach</tt> is removed from the factory with RemoveDependancies management</dl>
  */
  virtual void RemoveDomain( CATDomain * iDomainToDetach, CATBoolean iRemoveFromFactory = FALSE )=0;
  
  
  
  /**
  * Test whether <tt>this</tt> CATTopObject can be considered as infinite.
  * @return
  * The infinity status of <tt>this</tt>.
  * <br><b>Legal values</b>:
  * <tt>TRUE</tt>, if <tt>this</tt> contains (or is) an infinite cell or has a bounding box outside ModelSize,
  * <tt>FALSE</tt> if it is finite topology.
  */
  virtual CATBoolean HasInfiniteGeometry() const =0;




  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  /**
  * @nodoc
  * Returns all the CATTopObjects inside <tt>iBody</tt> bounding <tt>this</tt>. 
  * @param iBody
  * The pointer to the body inside which the search is done.
  * @param ioTopObjects
  * The CATTopObjects bounding <tt>this</tt>. 
  * @param ioSides
  * The matter side of the bouding CATTopObject.
  * @param iSizeOutput
  * The <tt>ioTopObjects</tt>, <tt>ioSides</tt>, <tt>ioDomains</tt> and <tt>ioGeometries</tt> are filled according to this maximun number.
  * @param ioDomains
  * The Domains associated to the bounded CATTopObject. 
  * @param ioGeometries
  * The Geometries associated to the boundary. 
  * @return
  * The number of CATTopObjects inside <tt>iBody</tt> bounding <tt>this</tt>.
  */
  virtual int GetBoundedTopObjects(CATBody  * iBody, CATTopObject **ioTopObjects, CATSide *ioSides, const int iSizeOutput,
                                   CATDomain **ioDomains = NULL, CATGeometry **ioGeometries = NULL)= 0;
  

  /**
  * @nodoc
  * Returns all the CATTopObjects boundaries of <tt>this</tt>. 
  * @param ioTopObjects
  * The CATTopObjects boundaries of <tt>this</tt>. 
  * @param ioSides
  * The matter side of the boundaries CATTopObject.
  * @param iSizeOutput
  * The <tt>ioTopObjects</tt>, <tt>ioSides</tt>, <tt>ioDomains</tt> and <tt>ioGeometries</tt> are filled according to this maximun number.
  * @param ioDomains
  * The Domains associated to the boundary CATTopObject. 
  * @param ioGeometries
  * The Geometries associated to the boundary. 
  * @return
  * The number of CATTopObjects which are boundaries of <tt>this</tt>. 
  */
  virtual int GetBoundaryTopObjects(CATTopObject **ioTopObjects, CATSide *ioSides,
    const int iSizeOutput,
    CATDomain **ioDomains = NULL, CATGeometry **ioGeometries = NULL)= 0;
  
   /**
   * @nodoc
   * Check if <tt>this</tt> is a boundary of <tt>iTopObject</tt>. 
   * @param iTopObject
   * The CATTopObjects boundaries of <tt>this</tt>. 
   * @param ioSides
   * The matter side associated.
   * @param iSizeOutput
   * The <tt>ioSides</tt>, <tt>ioDomains</tt> and <tt>ioGeometries</tt> are filled according to this maximun number.
   * @param ioDomains
   * The Domains associated.
   * @param ioGeometries
   * The Geometries associated.
   * @return
   * The number of times <tt>this</tt> is defined as a boundary of <tt>iTopObject</tt>. 
  */
  virtual int IsBoundaryOfTopObject(CATTopObject *iTopObject, CATSide *ioSides,
    const int iSizeOutput,
    CATDomain **ioDomains = NULL, CATGeometry **ioGeometries = NULL)= 0;
  
  

};

CATDeclareHandler(CATTopObject,CATTopology);
 
#endif
 
