/*******************************************************************/
/*    Copyright (c) 2014-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef CATCGMCheckAnomaly_H
#define CATCGMCheckAnomaly_H


/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CATCGMValueClassImplHolder.h"
#include "CATGMModelCmpInterfaces.h"
#include "CATListOfCATCGMCheckAnomalyValueInfo.h"
#include "CATListOfCATICGMObjects.h"
#include "CATListOfCATUnicodeString.h"
#include "CATListOfDouble.h"
#include "CATUnicodeString.h"
#include "CGMMeshGeometry.h"

class CATCGMCheckAnomalyImpl;

/**
 * Class representing an anomaly detected by the <tt>CATICGMCheckBody</tt>
 *operator.
 *
 * <b>Role:</b>This class is designed with "value-class" semantics; it is
 *intended to be owned and passed by value, rather than being allocated on the
 *heap. To minimize memory consumption, use these objects as locally as
 *possible.
 **/
class ExportedByCATGMModelCmpInterfaces CATCGMCheckAnomaly
{
public:
  /**
   * The check anomaly severity enum.
   * @param Warning
   * The anomaly is a warning.
   * @param Error
   * The anomaly is an error.
   */
  enum CATCGMCheckSeverity
  {
    Warning = 1,
    Error = 2
  };

  /**
   * Copy constructor.
   **/
  CATCGMCheckAnomaly(CATCGMCheckAnomaly const &iOther);

  /**
   * Assignment operator.
   **/
  CATCGMCheckAnomaly &operator=(CATCGMCheckAnomaly const &iOther);

  /**
   * Destructor.
   */
  ~CATCGMCheckAnomaly();

  /**
   * @nodoc
   * For internal use only
   */
  bool operator==(CATCGMCheckAnomaly const &iOther) const;

  /**
   * @nodoc
   * For internal use only
   */
  bool operator!=(CATCGMCheckAnomaly const &iOther) const;

  /**
   * Gets the objects generating this anomaly. This function can only retrieve
   * objects if the anomaly involves exact geometry. Calling it on a polyhedral
   * anomaly will return an empty list of <tt>CATICGMObject</tt>s.
   * @param oObjects
   * The list of objects.
   **/
  void GetObjects(CATLISTP(CATICGMObject) & oObjects) const;

  /**
   * Gets the triangle(s) involved in a polyhedral anomaly. Returns the number of
   * triangle(s) associated with the anomaly.
   * @param oTriangle1
   * The handle of the first triangle associated with the anomaly. This will be
   * an invalid handle if the anomaly has no specific triangles (for example,
   * when the anomaly indicates that a mesh is non-orientable).
   * @param oTriangle2
   * The handle of the second triangle associated with the anomaly. This will be
   * an invalid handle if the anomaly has no triangles or only one triangle (for
   * example, when the anomaly indicates that a triangle is degenerate).
   * @return The number of triangles associated with the anomaly. Possible
   * values are zero, one, and two.
   **/
  short GetTriangles(CGMPolyMeshTools::Triangle &oTriangle1,
                     CGMPolyMeshTools::Triangle &oTriangle2) const;

  /**
   * Gets the anomaly label.
   * @param oLabel
   * The label.
   **/
  void GetLabel(CATUnicodeString &oLabel) const;

  /**
   * Gets the severity level of the anomaly (warning or error)
   * @return
   * The severity level of the anomaly
   */
  CATCGMCheckSeverity GetSeverity() const;

  /**
   * Gets the list of value info objects. Each value info object contains a
   *value description and a list of associated values.
   * @param oValueInfos
   * The value info list.
   **/
  void GetValueInfo(CATLISTV(CATCGMCheckAnomalyValueInfo) & oValueInfos) const;

  /**
   * Gets the description of the anomaly.
   * @return
   * A string which contains a short description of the anomaly.
   */
  CATUnicodeString GetDescription() const;

  /**
   * Gets the detailed description of the anomaly.
   * @return
   * A string which contains a detailed description of the anomaly and how it is
   * formed.
   */
  CATUnicodeString GetDetailedDescription() const;

  /* @nodoc
   * For internal use only
   */
  CATCGMCheckAnomaly(CATCGMCheckAnomalyImpl *ipImpl);

  /* @nodoc
   * For internal use only
   */
  unsigned int GetAnomalyCode() const;

  DECLARE_USE_COUNTED_GET_IMPL_METHODS(CATCGMCheckAnomaly);

protected:
  CATCGMValueClassImplHolder _implHolder;
};
#endif
