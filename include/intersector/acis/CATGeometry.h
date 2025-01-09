#ifndef CATGeometry_h
#define CATGeometry_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */

#define CATCGMIncludeForCompatibility
#ifdef CATCGMIncludeForCompatibility
#    include "CATBaseUnknown.h"
#    include "CATMathBox.h"
#endif

#include "CATICGMObject.h"

class CATTransfoManager;
class CATMathTransformation;
class CATMathBox;

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATGeometry;
#else
extern "C" const IID IID_CATGeometry;
#endif

class CATMathAdvancedBox;
#include "CATMathAdvancedBoxType.h"

// CAA_Exposed CATIGeometry
/**
 * Interface representing the base class for all geometric
 * objects that can be streamed and moved.
 * <br>The derived objects are created inside a geometric container
 * (<tt>CATGeoFactory</tt>) by using the corresponding <tt>CATGeoFactory::Createxxx</tt>
 * methods . They are removed by the <tt>CATICGMContainer::Remove</tt> method.
 * The factory specifies the model size and the minimum size of a valid object.
 * <ul>
 * <li>A CATGeometry can return a box (called bounding box) that contains it.
 * <li>A CATGeometry can be transformed (in duplicate or replace mode)
 * by the use of a <tt>CATTransfoManager</tt> that takes into account
 * the forward links.
 *</ul>
 * @see CATGeoFactory, CATTransfoManager
 */
class ExportedByCATGMGeometricInterfaces CATGeometry : public CATICGMObject {
    CATDeclareInterface;

  public:
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //
    //            C A A             M E T H O D S
    //
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    /**
     * Returns a CATMathBox that contains <tt>this</tt> CATGeometry, with regards to
     * its current limitations. <br>
     * Note: <br>
     * A bounding box is a portion of the 3D space that fully encompasses the geometry.
     * It is an estimate of the space surrounding the geometry and is not intended to
     * provide an accurate result. The computation is a trade-off between accuracy and
     * performance that sacrifices the former. The bounding box returned by the GetBoundingBox method
     * is based on the current limits. As no operator guarantees the stability of current limits,
     * the returned bounding box may possibly vary. No application should rely on the bounding box
     * returned by this GetBoundingBox method unless it controls completely all the operations onto the manipulated geometry.
     * @param ioBox
     * The containing box.
     */
    virtual void GetBoundingBox(CATMathBox& ioBox) const = 0;

    /**
     * Returns a CATMathBox that contains <tt>this</tt> CATGeometry, with regards to
     * its current limitations. The signature which returns the CATMathBox in output argument
     * should be preferably used. <br>
     * Note: <br>
     * A bounding box is a portion of the 3D space that fully encompasses the geometry.
     * It is an estimate of the space surrounding the geometry and is not intended to
     * provide an accurate result. The computation is a trade-off between accuracy and
     * performance that sacrifices the former. The bounding box returned by the GetBoundingBox method
     * is based on the current limits. As no operator guarantees the stability of current limits,
     * the returned bounding box may possibly vary. No application should rely on the bounding box
     * returned by this GetBoundingBox method unless it controls completely all the operations onto the manipulated geometry.
     * @return
     * The containing box.
     */
    virtual CATMathBox GetBoundingBox() const = 0;

    /**
     * @nodoc
     * @return 0 on success, negative number upon error
     */
    virtual int GetAdvancedBoundingBox(CATMathAdvancedBox& ioBox) const = 0;

    /**
     * @nodoc
     * @return TRUE if given type of advanced bounding box is available
     */
    virtual CATBoolean IsAdvancedBoundingBoxTypeAvailable(CATMathAdvancedBoxType iType) const = 0;

    /**
     * @nodoc
     * Moves <tt>this</tt> within a CATTransfoManager process.<br>Do not direcly use
     * to transform a CATGeometry, especially if this CATGeometry
     * has forward links.
     * Use instead a <tt>CATTransfoManager</tt>:
     * <pre>
     * CATTransfoManager MyManager(MyTransfo,MyGeoFactory,CATTransfoManager::Replace);
     * MyManager.Add(MyGeomObject);
     * MyManager.Run();
     * CATGeometry* TransformedObject=MyManager.ReadImage(MyGeomObject);
     * </pre>
     */
    virtual void Move3D(CATTransfoManager& iTransfo) = 0;

    /**
     * @nodoc
     * Clones and moves <tt>this</tt> within a CATTransfoManager process.<br>Do not direcly use
     * to transform a CATGeometry, especially if this CATGeometry
     * has forward links.
     * Use instead a <tt>CATTransfoManager</tt>:
     * <pre>
     * CATTransfoManager MyManager(MyTransfo,MyGeoFactory,CATTransfoManager::Duplicate);
     * MyManager.Add(MyGeomObject);
     * MyManager.Run();
     * CATGeometry* TransformedObject=MyManager.ReadImage(MyGeomObject);
     * </pre>
     */
    virtual CATGeometry* CloneAndMove3D(CATTransfoManager& iTransfo) = 0;

    /**
     * @nodoc
     * Tests the transformation of <tt>this</tt> CATGeometry.
     * Returns <tt>1</tt> . Returns <tt>0</tt> otherwise.
     * @return
     * The result of the test.
     * <br><b>Legal values</b>:
     * <dl><dt>TRUE</dt><dd>if the transformation of <tt>this</tt> and
     * its forward linked CATGeometry
     * are geometricaly confused with <tt>iTGeometry</tt> and
     * its corresponding forward linked CATGeometry.
     * <dt>FALSE</dt><dd>otherwise
     *</dl>
     */
    virtual CATBoolean IsDeepConfused(CATTransfoManager& iTransfo, const CATGeometry* iTGeometry) const = 0;

    /**
     * @nodoc
     * Use now a CATTransfoManager to transform a CATGeometry.
     */
    virtual void ApplyTransformation(const CATMathTransformation& iTranfoToApply) = 0;
};

CATDeclareHandler(CATGeometry, CATICGMObject);

#endif
