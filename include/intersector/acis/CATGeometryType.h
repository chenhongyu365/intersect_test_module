#ifndef CATGeometryType_H
#define CATGeometryType_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 
/**
 * Geometric object type.
 * @param CATGeometryType
 * The generic type.
 * @param CATCurveType
 * The Curve type.
 * @param CATConicType
 * The Conic type.
 * @param CATCircleType
 * The Circle type.
 * @param CATEllipseType
 * The Ellipse type.
 * @param CATEdgeCurveType
 * The EdgeCurve type.
 * @param CATIntCurveType
 * The IntCurve type.
 * @param CATLineType
 * The line type.
 * @param CATNurbsCurveType
 * The Curve type.
 * @param CATCurveType
 * The Nurbs curve type.
 * @param CATPCurveType
 * The PCurve type.
 * @param CATPCircleType
 * The PCircle type.
 * @param CATPEllipseType
 * The PEllipse type.
 * @param CATPParabolaType
 * The Curve type.
 * @param CATCurveType
 * The PParabola type.
 * @param CATPHyperbolaType
 * The PHyperbola type.
 * @param CATPLineType
 * The Pline type.
 * @param CATPNurbsType
 * The PNurbs type.
 * @param CATIForeignPCurveType
 * The foreign Pcurve type.
 * @param CATPSplineType
 * The PSpline type.
 * @param CATSplineCurveType
 * The Splinecurve type.
 * @param CATIForeignCurveType
 * The foreign curve type.
 * @param CATProcCurveType
 * The ProcCurve type.
 * @param CATPointType
 * The point type.
 * @param CATCartesianPointType
 * The cartesian point type.
 * @param CATMacroPointType
 * The macro point type.
 * @param CATPointOnCurveType
 * The point on curve type.
 * @param CATPointOnSurfaceType
 * The point on surface type.
 * @param CATPointOnEdgeCurveType
 * The point on edge curve type.
 * @param CATSurfaceType
 * The surface type.
 * @param CATElementarySurfaceType
 * The elementary surface type.
 * @param CATCylinderType
 * The cylinder type.
 * @param CATSphereType
 * The sphere type.
 * @param CATTorusType
 * The torus type.
 * @param CATConeType
 * The cone type.
 * @param CATNurbsSurfaceType
 * The Nurbs surface type.
 * @param CATPlaneType
 * The plane type.
 * @param CATRevolutionSurfaceType
 * The revolution surface type.
 * @param CATTabulatedCylinderType
 * The tabulated cylinder type.
 * @param CATOffsetSurfaceType
 * The offset surface type.
 * @param CATIForeignSurfaceType
 * The foreign surface type.
 * @param  CATBodyType 
 * The body type.
 * @param  CATCellType
 * The cell type. 
 * @param  CATEdgeType 
 * The edge type.
 * @param  CATFaceType  
 * The face type.
 * @param  CATVertexType 
 * The vertex type.
 * @param  CATVolumeType 
 * The volume type.
 * @param  CATDomainType  
 * The domain type.
 * @param  CATLoopType   
 * The loop type.
 * @param  CATLumpType   
 * The lump type.
 * @param  CATShellType 
 * The shell type.
 * @param  CATVertexInFaceType 
 * The vertex in face type.
 * @param  CATVertexInVolumeType 
 * The vertex in volume type.
 * @param  CATWireType   
 * The wire type.
 * @param  CATLawType   
 * The law type.
 * @param  CATLinearLawType   
 * The linear law type.
 * @param  CATConstantLawType   
 * The constant law type.
 * @param  CATSplineLawType   
 * The spline law type.
 * @param  CATSubdivisionObjectType
 * The generic subdivision type
 * @param  CATSubdivMeshType
 * The subdivision mesh type
 * @param  CATSubdivMeshBaseType
 * The subdivision MeshBase type
 * @param  CATSubdivMeshCurveType
 * The subdivision mesh Curve type
 * @param  CATSubdivMeshGeoType
 * The geo subdivision mesh type
 * @param  CATCellManifoldType
 * The cell manifold type
 * @param  CATDeclarativeManifoldType
 * The declarative manifold type
* @param  CATDatumManifoldType
 * The datum manifold type
* @param  CATEvaluableManifoldType
 * The evaluable manifold type
* @param  CATSubdivisionManifoldType
 * The subdivision manifold type
* @param  CATPlaneManifoldType
 * The plane manifold type
 * @param  CATCylinderManifoldType
 * The cylinder manifold type
 * @param  CATSphereManifoldType
 * The sphere manifold type
 * @param  CATConeManifoldType
 * The cone manifold type
 * @param  CATTorusManifoldType
 * The torus manifold type
* @param  CATContextualManifoldType
 * The contextual manifold type
* @param  CATBoneFilletType
 * The bone fillet type
* @param  CATJointFilletType
 * The joint fillet type
 */


#define CATGeometricType        unsigned int

#include "CATIACGMLevel.h"
#include "CATIAV5Level.h"


/** @nodoc   ---------- Geometry -------------   */
#define CATGeometryType                     0x00000001

/** @nodoc */
#define CATCloudOfPointsType                0x02000002

/** @nodoc */
#define CATCurveType                        0x03000002

/** @nodoc */
#define CATPointType                        0x04000002

/** @nodoc */
#define CATSurfaceType                      0x06000002

/** @nodoc */
#define CATUserGeometryType                 0x07000002

/** @nodoc */
#define CATTopologyType                     0x08000002	


/** @nodoc   -------------- Curve ----------------   */
/** @nodoc */
#define CATBoundedCurveType                 0x03200003	
/** @nodoc */
#define CATBSplineCurveType                 0x03210004			

/** @nodoc */
#define CATConicType                        0x03300003
/** @nodoc */
#define CATCircleType                       0x03310004	
/** @nodoc */
#define CATEllipseType                      0x03320004	
/** @nodoc */
#define CATHyperbolaType                    0x03330004	
/** @nodoc */
#define CATParabolaType                     0x03340004	

/** @nodoc */
#define CATEdgeCurveType                    0x03400003	
/** @nodoc */
#define CATIntCurveType                     0x03410004	
/** @nodoc */
#define CATMergedCurveType                  0x03420004	
/** @nodoc */
#define CATSimCurveType                     0x03430004	
/** @nodoc */
#define CATContactCurveType                 0x03440004	

/** @nodoc */
#define CATLineType                         0x03500003	
/** @nodoc */
#define CATNurbsCurveType                   0x03600003	

/** @nodoc */
#define CATPCurveType                       0x03700003	
/** @nodoc */
#define CATPCircleType                      0x03710004	
/** @nodoc */
#define CATPCurveEquationType               0x03720004	
/** @nodoc */
#define CATPEllipseType                     0x03730004
/** @nodoc */
#define CATPParabolaType                    0x03780004
/** @nodoc */
#define CATPHyperbolaType	                  0x03790004
/** @nodoc */
#define CATPLineType                        0x03740004	
/** @nodoc */
#define CATPNurbsType  	                    0x03750004	
/** @nodoc */
#define CATIForeignPCurveType               0x03760004
/** @nodoc */
#define CATPSplineType                      0x03770004  
/** @nodoc */
#define CATNonLinearTransfoPCurveType       0x037A0004
/** @nodoc */
#define CATTrimmedPCurveType                0x037B0004

/** @nodoc */
#define CATSplineCurveType                  0x03800003
/** @nodoc */
#define CATIForeignCurveType                0x03900003
/** @nodoc */
#define CATProcCurveType                    0x03A00003
/** @nodoc */
#define CATHelixType                        0x03B00003	
	
/** @nodoc   -------------- Point ----------------   */
/** @nodoc */	
#define CATCartesianPointType               0x04100003
/** @nodoc */
#define CATMacroPointType                   0x04200003	
/** @nodoc */
#define CATPointOnCurveType                 0x04300003	
/** @nodoc */
#define CATPointOnEdgeCurveType             0x04310004	
/** @nodoc */
#define CATPointOnSurfaceType               0x04400003	

/** @nodoc   -------------- Surface ----------------   */
/** @nodoc */
#define CATChamferSurfaceType               0x06010004
/** @nodoc */
#define CATBoundedSurfaceType               0x06020004
/** @nodoc */
#define CATBSplineSurfaceType               0x06021005
/** @nodoc */
#define CATCircularSweepType                0x06030004
/** @nodoc */
#define CATDraftSurfaceType                 0x06040004
/** @nodoc */
#define CATElementarySurfaceType            0x06050004
/** @nodoc */
#define CATCylinderType                     0x06051005
/** @nodoc */
#define CATSphereType                       0x06052005
/** @nodoc */
#define CATConeType                         0x06053005
/** @nodoc */
#define CATTorusType                        0x06054005
/** @nodoc */
#define CATFilletSurfaceType                0x06060004
/** @nodoc */
#define CATNurbsSurfaceType                 0x06070004
/** @nodoc */
#define CATOffsetSurfaceType                0x06080004
/** @nodoc */
#define CATPlaneType                        0x06090004
/** @nodoc */
#define CATRevolutionSurfaceType            0x060A0004
/** @nodoc */
#define CATRuledSurfaceType                 0x060B0004
/** @nodoc */
#define CATSweepSurfaceType                 0x060C0004
/** @nodoc */
#define CATTabulatedCylinderType            0x060D0004
/** @nodoc */
#define CATProcOffsetSurfaceType            0x060E0004
/** @nodoc */
#define CATGenericFilletType                0x060F0004

/** @nodoc */
#define CATGenericRuledSurfaceType          0x06100004
/** @nodoc */
#define CATNonLinearTransfoSurfaceType      0x06110004
/** @nodoc */
#define CATLinearTransfoSurfaceType         0x06120004
/** @nodoc */
#define CATDirectionalSurfaceType           0x06130004
/** @nodoc */
#define CATIForeignSurfaceType              0x06140004
/** @nodoc */
#define CATSweepSegmentSurfaceType          0x06150004
/** @nodoc */
#define CATSpecSurfaceType                  0x06160004
/** @nodoc */
#define CATProcSurfaceType                  0x06170004

/** @nodoc   - Subdivision biparametric surfaces -   */
/** @nodoc */
#define CATSubdivCellSurfaceType            0x06180004
#define CATSubdivGridSurfaceType            0x06190004

	
/** @nodoc   -------------- Topology ------------   */
/** @nodoc */
#define CATTopObjectType                    0x08000003	
/** @nodoc */
#define CATDomainType                       0x08100003	


/** @nodoc */
#define CATBodyType                         0x08000004
/** @nodoc */	
#define CATCellType                         0x08010004	

/** @nodoc */
#define CATVertexType                       0x08010005	
/** @nodoc */
#define CATEdgeType                         0x08011005	
/** @nodoc */
#define CATFaceType                         0x08012005	
/** @nodoc */
#define CATVolumeType                       0x08013005
	
/** @nodoc */
#define CATEdgeDomainType                   0x08110004	
/** @nodoc */
#define CATVertexDomainType                 0x08100004	

/** @nodoc */
#define CATLoopType                         0x08112005	
/** @nodoc */
#define CATWireType                         0x08113005	
/** @nodoc */
#define CATLumpType                         0x08133005	
/** @nodoc */
#define CATShellType                        0x08123005
/** @nodoc */
#define CATVertexInFaceType                 0x08102005
/** @nodoc */	
#define CATVertexInVolumeType               0x08103005	



/** @nodoc   -------------- Cloud ----------------   */
/** @nodoc */
#define CATSetOfPointsType                  0x02100003



/** @nodoc   -------------- Cloud V1 ------------   */
/** @nodoc */
#define CATClayType                         0x0B000002
/** @nodoc */
#define CATCloudType                        0x0B100003
/** @nodoc */
#define CATScanType                         0x0B200003

/** @nodoc   -------------- Tess V1 ------------   */
/** @nodoc */
#define CATTessClayType                     0x0C000002
/** @nodoc */
#define CATTessCloudType                    0x0C100003
/** @nodoc */
#define CATTessScanType                     0x0C200003

/** @nodoc   -------------- Cld ------------   */
/** @nodoc */
#define CATCldGenEntityType                 0x0D000002
/** @nodoc */
#define CATCldBodyType                      0x0D100003
/** @nodoc */
#define CATCldCellType                      0x0D200003
/** @nodoc */
#define CATCldUniCellType                   0x0D210004
/** @nodoc */
#define CATCldCloudType                     0x0D211005
/** @nodoc */
#define CATCldScanType                      0x0D212005
/** @nodoc */
#define CATCldGridType                      0x0D213005
/** @nodoc */
#define CATCldPolygonType                   0x0D214005
/** @nodoc */
#define CATCldVectorsType                   0x0D215005
/** @nodoc */
#define CATCldMultiCellType                 0x0D220004
/** @nodoc */
#define CATCldSetOfScansType                0x0D222005
/** @nodoc */
#define CATCldSetOfGridsType                0x0D223005
/** @nodoc */
#define CATCldScanOnPolygonType             0x0D212106
/** @nodoc */
#define CATCldSubPolygonType                0x0D214106
/** @nodoc */
#define CATCldSetOfPointsType               0x0E000002
/** @nodoc */
#define CATCldSetOfPointsFType              0x0E100003
/** @nodoc */
#define CATCldSetOfPointsDType              0x0E200003
  

/** @nodoc */
#define CATLawType                          0x10000001

/** @nodoc   -------------- Law  ----------------   */
/** @nodoc */	
#define CATCompositeLawType                 0x11000002	
/** @nodoc */
#define CATConstantLawType                  0x12000002	
/** @nodoc */
#define CATLinearLawType                    0x13000002	
/** @nodoc */
#define CATSTypeLawType                     0x14000002
/** @nodoc */
#define CATSplineLawType                    0x15000002


/** @nodoc   -------------- Factory --------------   */
/** @nodoc */
#define CATGeoFactoryType                   0x20000001


/** @nodoc  --------- Subdivision objects --------   */
/** @nodoc */	
#define CATSubdivisionObjectType            0x0F000002


#ifdef  CATIACGMR426CAA 
/** @nodoc */
#define CATSubdivMeshBaseType               0x0F100003   
/** @nodoc */
#define CATSubdivMeshType                   0x0F110004  
/** @nodoc */
#define CATSubdivMeshCurveType              0x0F120004  

#else
#define CATSubdivMeshType                   0x0F100003
#endif
/** @nodoc */	
#define CATSubdivMeshGeoType                0x0F200003


/** @nodoc   --------- Polyhedral Objects  -------- */	

/** @nodoc */
#define CATGeoPolyObjectType                0x09000002

/** @nodoc */
#define CATGeoPolyPointType                 0x09000003
/** @nodoc */
#define CATGeoPolyCurveType                 0x09100003
/** @nodoc */
#define CATGeoPolySurfaceType               0x09200003
/** @nodoc */
#define CATGeoPolyBodyType                  0x09300003

/** @nodoc */
#define CATGeoPolyPointOnCurveType          0x09010004
/** @nodoc */
#define CATGeoPolyPointOnSurfaceType        0x09020004
/** @nodoc */
#define CATGeoPolyCurveOnCurveType          0x09110004
/** @nodoc */
#define CATGeoPolyCurveOnSurfaceType        0x09120004
/** @nodoc */
#define CATGeoPolyCouplingCurveType         0x09130004
/** @nodoc */
#define CATGeoPolyCurveOnPlaneType          0x09140004

/** @nodoc   --------- Implicit Objects  -------- */	

/** @nodoc */
#define CATGeoImplicitObjectType            0x05000002

/** @nodoc */
#define CATGeoImplicitSurfaceType           0x05200003

/** @nodoc   --------------   Live  --------------   */
/** @nodoc */

#define CATDRepGeometryType                 0x01000002

#define CATCellManifoldType                 0x01100003

#ifdef CATIACGMR217CAA

#define CATManifoldType                     0x01600003
#define CATDeclarativeManifoldType          0x01610004
#define CATDatumManifoldType                 0x01611005
#define CATEvaluableManifoldType             0x01612005
#define CATSubdivisionManifoldType            0x01612106
#define CATPlaneManifoldType                  0x01612206
#define CATCylinderManifoldType               0x01612306
#define CATSphereManifoldType                 0x01612406
#define CATConeManifoldType                   0x01612506
#define CATTorusManifoldType                  0x01612606
#define CATContextualManifoldType            0x01613005
#define CATBoneFilletType                     0x01613106
#define CATJointFilletType                    0x01613206
#define CATBoneChamferType                    0x01613306
#define CATDraftManifoldType                  0x01613406
#define CATButtonManifoldType                 0x01613506
#define CATCellManifoldGroupType            0x01620004
#define CATJointChamferType                   0x01613606

#else

#define CATDeclarativeManifoldType          0x01200003
#define CATDatumManifoldType                 0x01210004
#define CATEvaluableManifoldType             0x01220004
#define CATSubdivisionManifoldType            0x01221005
#define CATPlaneManifoldType                  0x01222005
#define CATCylinderManifoldType               0x01223005
#define CATSphereManifoldType                 0x01224005
#define CATConeManifoldType                   0x01225005
#define CATTorusManifoldType                  0x01226005
#define CATContextualManifoldType            0x01230004
#define CATBoneFilletType                     0x01231005
#define CATJointFilletType                    0x01232005
#define CATBoneChamferType                    0x01233005
#define CATDraftManifoldType                  0x01234005
#define CATButtonManifoldType                 0x01235005
#define CATCellManifoldGroupType            0x01500003
#define CATJointChamferType                 0x01236005

#endif

#define CATManifoldGroupType                0x01300003
#define CATContextualManifoldGroupType      0x01310004
#define CATHierarchicalManifoldGroupType    0x01320004

#define CATHGeometryType                    0x01400003
#define CATHEdgeType                        0x01410004
#define CATHVertexType                      0x01420004
#define CATIntersectionHVertexType          0x01421005
#define CATRatioHVertexType                 0x01422005
#define CATDistanceHVertexType              0x01423005


/** @nodoc */
#define CATUnknownGeometryType              0x00000000

/** @nodoc */
/* Please refer to AAD before use */
#define CATGhostGeometryType                0x0A000002

#endif
