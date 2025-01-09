#ifndef CATICGMObject_h
#define CATICGMObject_h
// COPYRIGHT DASSAULT SYSTEMES  1999
/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATICGMUnknown.h"
#include "CATListOfCATGeometries.h"
#include "CATListOfCATICGMObjects.h"
#include "CATListOfCATString.h"
#include "CATListOfInt.h"
#include "CATMathDef.h"

class CATCloneManager;
class CATGeometry;
class CATGeoFactory;
class CATCGMAttrId;
class CATCGMAttribute;
class CATLISTP(CATCGMAttribute);
class CATTopData;
class CATCGMOperator;

#include "ExportedByCATGMGeometricInterfaces.h"

/** @nodoc */
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATICGMObject ;
#else
extern "C" const IID IID_CATICGMObject ;
#endif
//CAA_Exposed 
/**
 * Defines how to follow the links between the CATICGMObjects.
 * Let us illustrate each item on this example: A CATEdgeCurve is made of 
 * two CATPCurves. Each CATPCurve lay on a CATSurface. A CATPointOnEdgeCurve
 * is defined on the CATEdgeCurve.
 * <pre>
 *    CATPointOnEdgeCurve -> CATEdgeCurve -> CATPCurve1 -> CATSurface1
 *                                        -> CATPCurve2 -> CATSurface2
 * </pre>
 * @param CatCGMDependancies
 * Going forward the first level of links. Applied to the CATEdgeCurve of the 
 * example, it returns CATPCurve1 and CATPCurve2.
 * @param CatCGMAll
 * Going forward and backward one level of links. Applied to the CATEdgeCurve of the
 * example , it returns CATPCurve1, CATPCurve2 and CATPointOnEdgeCurve.
 * @param CatCGMAllDependancies
 * Going forward until the last level. Applied to the CATEdgeCurve of the example, 
 * it returns CATPCurve1, CATPCurve2, CATSurface1, CATSurface2
 */
enum CATCGMLinkType {CatCGMDependancies = +16, CatCGMAll = +17, CatCGMAllDependancies = +18};

//CAA_Exposed 
/**
 * Defines the type of CATGeoFactory.
 * @param CatCGMImplicit
 * Refers to the implicit factory
 * @param CatCGMExplicit
 * Refers to the explicit factory
 */
enum CATCGMMode     {CatCGMImplicit = +7, CatCGMExplicit = +8};


//CAA_Exposed 
/**
 * Defines the kind of links that arrives to an object.
 * @param CatCGMUseCountAllCATICGMObject
 * Refers to all CATICGMObject of the CATGeoFactory.
 * @param CatCGMUseCountExtendedTopology
 * Not Yet Avalaible, Refers to topological links.
 */
enum CATCGMUseCountType { CatCGMUseCountAllCATICGMObject = +11, CatCGMUseCountExtendedTopology = +12};

//CAA_Exposed 
/**
 * Interface representing the base class of all the objects of the 
 * Catia Geometrical Modeler that
 * can be streamed.<br>
 * These objects can be geometrical objects (CATGeometry) and other objects
 * such as a CATLaw.
 * <ul>
 * <li>They are identified by a persistent tag. 
 * <li>They are implicit or explicit.
 * <li>If they are frozen through a smart process, 
 * they cannot be modifiable
 * <li>They can point attributes. Attributes allow an application programmer 
 * to put data on a CATICGMObject.Attributes can
 * be streamed (CATCGMStreamAttribute) or not (CATCGMAttribute). 
 * <li>They can be cloned, (i.e. duplicated with or without the objects that
 * are forward linked) by the use of a <tt>CATCloneManager</tt>.
 * </ul>
 */

class ExportedByCATGMGeometricInterfaces CATICGMObject : public CATICGMUnknown
{
  CATDeclareInterface;
public:


  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


/**
  * Declares that the CATICGMObject construction is achieved. 
  *  <br>This method also runs basic checks.
  *  @param IsNoMoreModifiable     
  *   The status of the CATICGMObject after completion.
  *  <br><b>Legal values</b>: 
  *   <dl><dt><tt>TRUE</tt></dt><dd> To freeze the content of the CATICGMObject. Further modifications of this
  *   object will imply that all modified elements will be copied first,
  *   thus keeping the current object state unmodified.
  *   <dt><tt>FALSE</tt></dt><dd>The CATICGMObject can be later modified.</dl>
  *  @param IdentityBuildOperator    
  *    Internal use, to let at the default value.
  *  @param iData
  *    Internal use, to let at the default value.
  */
  virtual void Completed(CATBoolean          iIsNoMoreModifiable = FALSE,
                         const char          iIdentityBuildOperator[] = "",
                         const CATTopData  * iData = NULL) = 0;
 //CAA_Exposed  
/**
  * Tests whether <tt>this</tt> CATICGMObject is modifiable.
  * @return
  * The result of the test.
  * <br><b>Legal velues</b>:
  * <tt>1</tt> if <tt>this</tt> CATICGMObject is modifiable, <tt>0</tt> otherwise.<br>
  * A CATICGMObject is not modifiable when it depends on another CATICGMObject
  * that has been frozen. This is used in the topology by the smart mechanism.  
  */
  virtual CATBoolean IsModifiable()  = 0;
  
  //----------------------------------------------------------------------
  // General Purpose Analysis : Tag,Factory,Explicit,Links
  //----------------------------------------------------------------------

  //CAA_Exposed 
/**
  * Returns the number of links that arrives to <tt>this</tt> CATICGMObject.
  * @param iUseType
  * The kind of links that are taken into account.
  * @return
  * The number of links that refer to <tt>this</tt>.
  */
  virtual CATULONG32  GetUseCount(CATCGMUseCountType iUseType = CatCGMUseCountAllCATICGMObject) const  = 0;

    //CAA_Exposed 
/**
  * Returns the persistent tag of <tt>this</tt> CATICGMObject. 
  * <br><b>WARNING:</b> The returned tag is not necessarily incremented each time a new
  * object is created. 
  * @return
  * The tag.
  */
  virtual CATULONG32  GetPersistentTag() const  = 0;

  //CAA_Exposed 
  /**
  * Returns a pointer to the CATGeoFactory of <tt>this</tt> CATICGMObject.
  * @param iThrowOnNullFactory
  * Specify if an error must be thrown in case of a NULL return CATGeoFactory pointer.
  * Notice that this configuration remains unsual.
  * @param iMode
  * The mode of the required <tt>CATGeoFactory</tt>.
  * @return
  * The pointer to the CATGeoFactory.
  */
  virtual CATGeoFactory* GetContainer(CATBoolean iThrowOnNullFactory = TRUE, CATCGMMode iMode = CatCGMExplicit) = 0;

//CAA_Exposed 
  /**
  * Modifies the implicit/explicit mode of <tt>this</tt> CATICGMObject.
  * @param iMode
  * The new mode of <tt>this</tt> CATICGMObject.
  */
  virtual void SetMode(CATCGMMode iMode) = 0;

//CAA_Exposed 
  /**
  * Tests whether <tt>this</tt> CATICGMObject is explicit.
  * @return
  * The result of the test.
  * <br><b>Legal values</b>:
  * <tt>1</tt> if <tt>this</tt> CATICGMObject is explicit, <tt>0</tt> otherwise.
  */
  virtual CATLONG32 IsExplicit() const = 0; 

  //----------------------------------------------------------------------
  // Attribute management: new version.
  //----------------------------------------------------------------------
    //CAA_Exposed 
/**
  * Links an attribute to <tt>this</tt> CATIGGMObject.
  * @param iNewAttr
  * A pointer to the attribute to be pointed by <tt>this</tt> CATICGMObject.
  * @return
  * The result of the association
  * <tt>1</tt> if the attribute has been successfully pointed, 
  * <tt>0</tt> otherwise.
  */
  virtual CATLONG32         PutAttribute(CATCGMAttribute * iNewAttr)=0 ;

    //CAA_Exposed 
/** 
  * Returns a pointer to an attribute, pointed by <tt>this</tt> CATICGMObject.
  * @param iAttrId
  * The attribute identifier  (given by the macro <tt>iAttrId=UIDName(MyAttributeClassName)</tt>)
  * @return
  * A pointer to the attribute.
  */
  virtual CATCGMAttribute * GetAttribute(const CATCGMAttrId* iAttrId)=0 ;

    //CAA_Exposed 
  /**
  * Releases an attribute so that 
  * <tt>this</tt> CATICGMObject no longer points to the given attribute. 
  * The attribute is deleted if it is not pointed to by any other object.
  * @param iAttr
  * The pointer to the attribute 
  * @return
  * <tt>1</tt> if the attribute has been successfully released, 
  * <tt>0</tt> otherwise.
  */
  virtual CATLONG32         ReleaseAttribute(CATCGMAttribute * iAttr)=0 ;

    //CAA_Exposed 
  /**
  * Retrieves the attributes, pointed by <tt>this</tt> CATICGMObject.
  * @param oListOfAttr
  * The retrieving list. Notice that all the derived attributes are also retrieved.
  * @param iAttrId
  * The attribute identifier to take into account. If <tt>NULL</tt>, it retrieves all the attributes
  * of <tt>this</tt> CATICGMObject.
  */
  virtual void        GetListAttribute(CATLISTP(CATCGMAttribute) & oListOfAttr, 
    const CATCGMAttrId* iAttrId=NULL)=0;

      //CAA_Exposed 
/**
  * Retrieves the next attribute of <tt>this</tt> CATICGMObject.
  * @param iPrev
  * A pointer to the previous attribute. <tt>iPrevAttr=NULL</tt> for the first attribute.
  * @param ioNextAttr
  * A pointer to the next attribute.
  */
  virtual void        GetNextAttribute(CATCGMAttribute * iPrevAttr,
    CATCGMAttribute *& ioNextAttr)=0;
  

  






  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

 
/**
  * @nodoc
  * Declares that the CATICGMObject construction is achieved, by sending an event. 
  *  <br>This method also runs basic checks.
  *  @param iOperator      
  *   The pointer to the CGM operator that achieves the construction.
  */
  virtual void CompletedFreeze(CATCGMOperator *iOperator) = 0;
  
/**
  * @nodoc
  * Tests whether <tt>this</tt> CATICGMObject has been completed as NoMoreModifiable Object in this session
  */
  virtual CATBoolean HasBeenCompletedAsNoMoreModifiable() const = 0;

/**
  * @nodoc
  * Tests whether <tt>this</tt> CATICGMObject has loaded otherwise created in this Session
  */
  virtual CATBoolean HasBeenLoaded() const = 0;

/**
  * @nodoc
  * Retrieves the CATICGMObjects linked to <tt>this</tt>.
  * @param oLinks
  * The lists of linked CATICGMObjects.
  * @param iLinkType
  * The type of links to follow.
  * @param oSharedStatus
  * <dl><dt>2</dt><dd> If the linked object is the geometric representation
  *  of a spec surface except for an offset surface. Example:
  *<pre>CATFilletSurface->CATCylinder</pre>
  * Applied to a
  * CATFilletSurface (that is a spec surface), the forward linked object
  * is the CATCylinder and the shared status is 2.
  *     <dt>1</dt><dd>Identifies a forward linked object that cannot be
  * shared with two pointing objects. Example: a CATPCurve cannot be shared
  * by two different CATIntCurves, a CATGeometry cannot be shared by two offset
  * surfaces.
  *      <dt>0</dt><dd>otherwise
  *</dl>
  * @param oListString 
  * The name of the type of link with <tt>this</tt> of each CATICGMObjects of 
  * <tt>oLinks</tt>. 
  */
  virtual void GetLinks(CATLISTP(CATICGMObject) &oLinks,
    CATCGMLinkType           iLinkType     = CatCGMDependancies,
    CATRCOLL(int)*           oSharedStatus = NULL,
    CATLISTV(CATString)*     oLinksString  = NULL) = 0;
  
/**
  * @nodoc
  * DEBUG purpose Only : Returns the number of detected anomalies 
  */
  virtual int Check()=0;
 
  
 /**
  * @nodoc
  * Clones <tt>this</tt> within a CATCloneManager process.<br>Do not direcly use
  * to clone a CATICGMObject, especially if this CATICGMObject
  * has forward links. 
  * Use instead a <tt>CATCloneManager</tt>:
  * <pre>
  * CATCloneManager MyManager(MyGeoFactory);
  * MyManager.Add(MyCGMObject);
  * MyManager.Run();
  * CATICGMObject* ClonedObject=MyManager.ReadImage(MyCGMObject);
  * </pre>
  */
  virtual CATICGMObject* Clone(CATCloneManager& iCloneManager) const = 0;
  
 /**
  * @nodoc
  * Use now <tt>CATICGMObject::GetLinks</tt> with <tt>iLinkType=CatCGMAllDependancies</tt>
  */
  virtual void GetAllLinks(CATLISTP(CATGeometry) &oLinks) = 0;

 /**
  * @nodoc
  * Use now <tt>CATICGMObject::SetMode</tt> with <tt>iMode=CatCGMExplicit</tt>
  */
  virtual void SetExplicit() = 0;
  

 /**
  * @nodoc
  * Defines an attribute on a CATIGGMObject (deprecated).
  * <br>Use now the other signature.
  * @param iKey
  * The integer that characterizes the attribute. 
  * Use the <tt>CATGiveUniqueAttributeKey() </tt> global function to initialize
  * <tt>iKey</tt>.
  * @param iBuffer
  * The void pointer to a memory space that contains the data.
  * @param iLength
  * The length of <tt>iBuffer</tt>.
  * @param iControl
  * <tt>1</tt> if the attribute may not be replaced, 
  * <tt>0</tt> otherwise.
  * @return
  * <tt>1</tt> if the attribute has been successfully created or replaced, 
  * <tt>0</tt> otherwise.
  */
  virtual int         PutAttribute(const int iKey, void* iBuffer, const int iLength,  const int iControl) = 0;
  
 /**
  * @nodoc
  * Reads on <tt>this</tt> the attribute of a given key  (deprecated).
  * <br>Use now the other signature.
  * @param iKey
  * The key of the attribute to read.
  * @param oLength
  * The length of the returned buffer.
  * @return
  * The pointer to the buffer containing the CATICGMObject attribute data.
  */
  virtual const void* GetAttribute( const int iKey, int& oLength) = 0;
  
  
 /**
  * @nodoc
  * Deletes on <tt>this</tt> the attribute of a given key  (deprecated).
  * <br>Use now the other signature.
  * @param iKey
  * The key of the attribute to delete. (obsolete)
  */
  virtual int         DeleteAttribute( const int iKey ) = 0;
  
 /**
  * @nodoc
  * Deletes all the attributes on <tt>this</tt>  (deprecated). 
  * <br>Use now the other signature.
  */
  virtual void        DeleteAllAttribute() = 0;
  
 /**
  * @nodoc
  */
  virtual void *GetImplementCGM(CATGeometricType iTypeReference) const = 0;

 /**
  * @nodoc
  */
  virtual int  IsImplementCGMRemoved(const CATGeometricType iTypeReference=CATGeometryType) const = 0;

 /**
  * @nodoc
  */
 virtual ULONG __stdcall CATAddRefFrom(void *iForDebug, CATBoolean iLockEquation = FALSE) = 0;

 /**
  * @nodoc
  */
 virtual ULONG __stdcall CATReleaseFrom(void *iForDebug, CATBoolean iLockEquation = FALSE) = 0;

};

/** @nodoc */ 
CATDeclareHandler(CATICGMObject,CATICGMUnknown);

/** @nodoc */
ExportedByCATGMGeometricInterfaces int CATGiveUniqueAttributeKey();


#endif
