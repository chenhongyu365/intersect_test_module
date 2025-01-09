#ifndef CATIMshCVMCore_h
#define CATIMshCVMCore_h

// COPYRIGHT DASSAULT SYSTEMES 2022
//=============================================================================
/**
 * @CAA2Level L0
 * @CAA2Usage U1
 */

#include "CATIMshMesh.h"
#include "CATIMshMesher.h"
#include "CATSysErrorDef.h"
#include "ExportedByCATMshCVMCore.h"

/**
 * Class holding the CVMVerbose parameter
 */
enum class ExportedByCATMshCVMCore CATMshCVMVerbose {
    Minimal,
    Normal,
    Maximal,
};

/**
 * Class holding the CVMMetric parameter
 */
enum class ExportedByCATMshCVMCore CATMshCVMMetric {
    Isotropic,
    Anisotropic,
};

/**
 * Class holding the CVMMetricPropagation parameter
 */
enum class ExportedByCATMshCVMCore CATMshCVMMetricPropagation {
    InAllDirections,
    InDirection,
    TowardIsotropic,
};

/**
 * Class holding the CVMElementTarget parameter
 */
enum class ExportedByCATMshCVMCore CATMshCVMElementTarget {
    Tetra,
    Hexa,
};

/**
 * Class holding the CVMElementGeneration parameter
 */
enum class ExportedByCATMshCVMCore CATMshCVMElementGeneration {
    Regular,
    Orthogonal,
    Cartesian,
};

/**
 * Class holding the CATMshCVMSurfaceInsertionEffort parameter
 */
enum class ExportedByCATMshCVMCore CATMshCVMSurfaceInsertionEffort {
    Minimal,
    Light,
    Standard,
    Strong,
    Maximal,
};

/**
 * Class holding the CVMComponents parameter
 */
enum class ExportedByCATMshCVMCore CATMshCVMComponents {
    All,
    Outside,
};

/**
 * Class holding the CVMInternalPointsRemovalEffort parameter
 */
enum class ExportedByCATMshCVMCore CATMshCVMInternalPointsRemovalEffort {
    Minimal,
    Light,
    Standard,
    Strong,
    Maximal,
};

/**
 * Class holding the CVMOptimizationLevel parameter
 */
enum class ExportedByCATMshCVMCore CATMshCVMOptimizationLevel {
    Light,
    Standard,
    Strong,
};

/**
 * Class holding the CVMOverConstrainedElement parameter
 */
enum class ExportedByCATMshCVMCore CATMshCVMOverConstrainedElement {
    Edges,
    Tetrahedra,
    Elements,
};

/**
 * Class holding the CVMReproducibility parameter
 */
enum class ExportedByCATMshCVMCore CATMshCVMReproducibility {
    Always,
    NotGuaranteed,
};

/**
 * Class holding the CVMMemoryTradeoff parameter
 */
enum class ExportedByCATMshCVMCore CATMshCVMMemoryTradeoff {
    PerformanceInsteadOfMemory,
    MemoryInsteadOfPerformance,
};

/**
 * Class holding the CVMKernel parameter
 */
enum class ExportedByCATMshCVMCore CATMshCVMKernel {
    KernelI32,
    KernelI64,
    KernelI64MPI,
};

/**
 * Private class holding the CVMCore
 * Should never be used directly
 */
template <CATMshCVMKernel KERNEL>
class ExportedByCATMshCVMCore CATIMshCVMCore : public CATIMshMesher {
public:
    class impl;
    class ExportedByCATMshCVMCore helper;

    explicit CATIMshCVMCore() noexcept;
    virtual ~CATIMshCVMCore();

    CATIMshCVMCore(const CATIMshCVMCore&) = delete;
    CATIMshCVMCore& operator=(CATIMshCVMCore&) = delete;
    CATIMshCVMCore& operator=(CATIMshCVMCore&&) noexcept = default;

    HRESULT Init();
    HRESULT Reset();

    HRESULT SetInterruptCallback(CATMshInterruptCB callback, void* userData);
    HRESULT SetMessageCallback(CATMshMessageCB callback, void* userData);

    void SetMaxNumberOfProcesses(const unsigned int maxNumberOfProcesses);
    void SetNumberOfSubdomains(const unsigned int numberOfSubdomains);
    void SetUnconstrainedDelaunay(const bool unconstrainedDelaunay);
    void SetNonOriginalDomainsToKeep(const bool nonOriginalDomainsToKeep);

    void SetVerbose(const CATMshCVMVerbose verbose);
    void SetMetric(const CATMshCVMMetric metric);
    void SetMetricPropagation(const CATMshCVMMetricPropagation propagation);
    void SetElementTarget(const CATMshCVMElementTarget elementTarget);
    void SetElementGeneration(
        const CATMshCVMElementGeneration elementGeneration);
    void SetReproducibility(const CATMshCVMReproducibility reproducibility);
    void SetMemoryTradeoff(const CATMshCVMMemoryTradeoff memoryTradeoff);
    void SetSurfaceInsertionEffort(
        const CATMshCVMSurfaceInsertionEffort surfaceInsertionEffort);
    void SetComputeComponents(const CATMshCVMComponents components);
    void SetInternalPointsRemovalEffort(
        const CATMshCVMInternalPointsRemovalEffort effort);
    void SetOptimizationLevel(const CATMshCVMOptimizationLevel level);
    void SetOverconstrainedElement(
        const CATMshCVMOverConstrainedElement overConstrainedElement);

    void SetSurfaceFrozen(const bool surfaceFrozen);
    void SetResilientInsertion(const bool resilientInsertion);
    void SetResilientInsertionNewENR(const bool resilientInsertionNewENR);
    void SetNumericalResolution(const double numericalResolution);
    void SetEnforceNumericalResolution(const bool enforceNumericalResolution);
    void SetInternalPoints(const bool internalPoints);

    void SetSurfaceGradation(const double surfaceGradation);
    void SetSurfaceMinEdgeLength(const double surfaceMinEdgeLength);
    void SetSurfaceMaxEdgeLength(const double surfaceMaxEdgeLength);
    void SetSurfaceMinSize(const double surfaceMinSize);
    void SetSurfaceMaxSize(const double surfaceMaxSize);
    void SetChordalError(const double chordalError);
    void SetGeometricApproximationAngle(
        const double geometricApproximationAngle);
    void SetSurfaceRidgeAngle(const double surfaceRidgeAngle);
    void SetSurfaceProximityLayers(const int numberOfLayers);

    void SetVolumeGradation(const double volumeGradation);
    void SetVolumeMinEdgeLength(const double volumeMinEdgeLength);
    void SetVolumeMaxEdgeLength(const double volumeMaxEdgeLength);
    void SetVolumeMinSize(const double volumeMinSize);
    void SetVolumeMaxSize(const double volumeMaxSize);
    void SetVolumeProximityLayers(const double numberOfLayers);

    void SetSmoothWrapSurface(const bool smoothWrapSurface);
    void SetExternalGapSize(const double gapSize);
    void SetInternalGapSize(const double gapSize);
    void SetHoleSize(const double holeSize);
    void SetVoxelSize(const double voxelSize);
    void SetPenetrationDepth(const double penetrationDepth);
    void SetMinimumPenetrationDepth(const double minimumPenetrationDepth);
    void SetAvoidExternalSurfacesEffort(
        const double avoidExternalSurfacesEffort);
    void SetCostFactorForBoundarySurfaceFace(
        const double costFactorForBoundarySurfaceFace);
    void SetAvoidExternalSurfaces(const bool avoidExternalSurfaces);
    void SetEnforceGapFilling(const bool enforceGapFilling);
    void SetWrapOptimizationEffort(const double wrapOptimizationEffort);
    void SetWrapSmoothSurfaceAngle(const double wrapSmoothSurfaceAngle);
    void SetWrapSmoothSurfaceEffort(const double wrapSmoothSurfaceEffort);
    void SetGapHitAngleCos(const double hitAngle);
    void SetLegacySpikes(const double legacySpikes);
    void SetPreserveSurfaceGenus(const double preserveSurfaceGenus);

    void SetIdealizationTolerance(const double idealizationTolerance);
    void SetIdealizationProcessExternalDomain(
        const bool idealizationProcessExternalDomain);
    void SetIdealizationRegularizeInternalSurfaces(
        const bool idealizationRegularizeInternalSurfaces);

    void SetSurfaceOptimizationFlatAngle(const double flatAngle);
    void SetSurfaceOptimizationSliver(const double sliver);
    void SetSurfaceOptimizationDensity(const bool surfaceOptimizationDensity);
    void SetCrossSurfaceVolumeOptimization(
        const bool crossSurfaceVolumeOptimization);

    void SetBoundaryLayerImprinting(const bool boundaryLayerImprinting);

    HRESULT AddTrackerConstraint(CATIMshMesh* mesh,
                                 const CATMshVertexIndex vertexIndex);
    HRESULT AddTrackerConstraint(const CATMshVertexIndex vertexIndex);
    HRESULT AddTrackerConstraint(CATIMshMesh* mesh,
                                 const CATMshElementIndex elementIndex);
    HRESULT AddTrackerConstraint(const CATMshElementIndex elementIndex);

    HRESULT AddFrozenConstraint(CATIMshMesh* mesh,
                                const CATMshVertexIndex vertexIndex);
    HRESULT AddFrozenConstraint(CATIMshMesh* mesh,
                                const CATMshElementIndex elementIndex);

    HRESULT AddBoxConstraint(CATIMshMesh* mesh);
    HRESULT AddBoxConstraint(const CATMshTag tag);

    HRESULT AddExplicitDomainConstraint(CATIMshMesh* mesh,
                                        const bool artificial,
                                        const bool toKeep, const bool toWrap);
    HRESULT AddExplicitDomainConstraint(CATIMshMesh* mesh,
                                        const CATMshDomainIndex domainIndex,
                                        const bool artificial,
                                        const bool toKeep, const bool toWrap);
    HRESULT AddExplicitDomainConstraint(const CATMshTag tag,
                                        CATMshElement::Orientation orientation,
                                        const bool artificial,
                                        const bool toKeep, const bool toWrap);

    HRESULT AddImplicitDomainConstraint(const CATMshTag tag,
                                        CATMshElement::Orientation orientation,
                                        const bool toKeep);

    HRESULT AddExternalWrapConstraint(CATIMshMesh* mesh, const double gap_size);

    HRESULT AddSurfaceGeometricConstraint(
        const CATMshTag tag, const double geometricApproximationAngle,
        const double chordalError, const double minSize, const double maxSize);

    HRESULT AddBoundaryLayerUniformConstraint(
        const CATMshTag tag, const CATMshElement::Orientation orientation,
        const double h, const int n, const bool r);

    HRESULT AddBoundaryLayerArithmeticConstraint(
        const CATMshTag tag, const CATMshElement::Orientation orientation,
        const double h0, const double d, const double b, const int nMin,
        const int nMax, const bool r);

    HRESULT AddBoundaryLayerGeometricConstraint(
        const CATMshTag tag, const CATMshElement::Orientation orientation,
        const double h0, const double p, const double b, const int nMin,
        const int nMax, const bool r);

    HRESULT AddVertexSizeConstraint(const CATMshVertexIndex vertexIndex,
                                    const double sizeIso, const bool relative);
    HRESULT AddVertexSizeConstraint(const CATMshVertexIndex vertexIndex,
                                    const double (&sizeAniso)[6],
                                    const bool relative);
    HRESULT AddVertexSizeConstraint(CATIMshMesh* mesh,
                                    const CATMshVertexIndex vertexIndex,
                                    const double sizeIso, const bool relative);
    HRESULT AddVertexSizeConstraint(CATIMshMesh* mesh,
                                    const CATMshVertexIndex vertexIndex,
                                    const double (&sizeAniso)[6],
                                    const bool relative);

    HRESULT AddPointSizeConstraint(const double (&xyz)[3],
                                   const double sizeIso);
    HRESULT AddPointSizeConstraint(const double (&xyz)[3],
                                   const double (&sizeAniso)[6]);

    HRESULT AddCubeSizeConstraint(
        const double (&xyzV1)[3], const double (&xyzV2)[3],
        const double (&xyzV3)[3], const double (&xyzV4)[3],
        const double (&xyzV5)[3], const double (&xyzV6)[3],
        const double (&xyzV7)[3], const double (&xyzV8)[3], const double size);
    HRESULT AddCubeSizeConstraint(
        const double (&xyzV1)[3], const double (&xyzV2)[3],
        const double (&xyzV3)[3], const double (&xyzV4)[3],
        const double (&xyzV5)[3], const double (&xyzV6)[3],
        const double (&xyzV7)[3], const double (&xyzV8)[3],
        const double (&sizeAniso)[6]);

    HRESULT AddCylinderSizeConstraint(const double (&p1)[3],
                                      const double (&p2)[3],
                                      const double radius, const double size);
    HRESULT AddCylinderSizeConstraint(const double (&p1)[3],
                                      const double (&p2)[3],
                                      const double radius,
                                      const double (&sizeAniso)[6]);

    HRESULT AddSphereSizeConstraint(const double (&center)[3],
                                    const double radius, const double size);
    HRESULT AddSphereSizeConstraint(const double (&center)[3],
                                    const double radius,
                                    const double (&sizeAniso)[6]);

    HRESULT AddShapeSizeConstraint(CATIMshMesh* mesh, const double sizeIso);
    HRESULT AddShapeSizeConstraint(CATIMshMesh* mesh,
                                   const double (&sizeAniso)[6]);

    HRESULT AddVertexMorphingConstraint(CATIMshMesh* mesh,
                                        const CATMshVertexIndex vertexIndex,
                                        const double (&target)[3]);

    CATMshCVMVerbose GetVerbose() const;
    CATMshCVMMetric GetMetric() const;

    CATMshCVMSurfaceInsertionEffort GetSurfaceInsertionEffort() const;

    bool GetSurfaceFrozen() const;
    bool GetResilientInsertion() const;
    double GetNumericalResolution() const;

    double GetChordalError() const;
    double GetGeometricApproximationAngle() const;
    double GetSurfaceGradation() const;
    double GetSurfaceMinEdgeLength() const;
    double GetSurfaceMaxEdgeLength() const;
    double GetSurfaceMinSize() const;
    double GetSurfaceMaxSize() const;

    double GetVolumeMinSize() const;
    double GetVolumeMaxSize() const;
    double GetVolumeGradation() const;

    virtual HRESULT Mesh() = 0;

    virtual CATIMshMesh* GetMesh() = 0;
    virtual CATIMshMesh* GetMesh(CATIMshMesh* mesh);
    virtual CATIMshMesh* GetMesh(CATIMshMesh* mesh, const CATMshTag tag);
    virtual CATIMshMesh* GetMesh(CATIMshMesh* mesh, const CATMshTag tag,
                                 CATMshElement::Orientation orientation);

    void Sleep();

    CATMshVertexIndex Track(CATIMshMesh* mesh,
                            const CATMshVertexIndex vertexIndex);
    CATMshElementIndex Track(CATIMshMesh* mesh,
                             const CATMshElementIndex elementIndex);

    void DebugDisableSurfaceInsertion(const bool disableSurfaceInsertion);
    void DebugDisableIdealization(const bool disableIdealization);
    void DebugDisableSurfaceOptimization(const bool disableSurfaceOptimization);
    void DebugDisableRegular(const bool disableRegular);
    void DebugDisableBoundaryLayers(const bool disableBoundaryLayers);
    void DebugDisableOptimization(const bool disableOptimization);
    void DebugDisableVolume(const bool disableVolume);

    void* GetLegacyMorphingSpecs() const;
    void SetLegacyMorphingSpecs(void* legacyMorphingSpecs);

protected:
    virtual bool IsDebug() const;
    virtual bool IsDebugDeep() const;
    virtual const char* GetDebugPrefix() const;

    void Message(CATMshMessage& message) const;
    void Info(const char* msg) const;
    void Warning(const char* msg) const;
    void Error(const char* msg) const;

    void SetEstimatedBoundingBox(double*);

protected:
    impl* _impl;
    helper* _helper;
};

#endif
