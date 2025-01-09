#ifndef CATIMshCVMSpa_h
#define CATIMshCVMSpa_h

#include "CATIMshCVMCore.h"
#include "ExportedByCATMshCVMSpa.h"

/**
 * Class holding a CVM for Spatial version
 * Should be used directly
 *
 * CATMshCVMKernel availables :
 *  - CATMshCVMKernel::KernelI32
 */
template <CATMshCVMKernel KERNEL> class ExportedByCATMshCVMSpa CATIMshCVMSpa : protected CATIMshCVMCore<KERNEL> {
  public:
    class impl;

    using base_type = CATIMshCVMCore<CATMshCVMKernel::KernelI32>;

    explicit CATIMshCVMSpa() noexcept;
    virtual ~CATIMshCVMSpa();
    CATIMshCVMSpa& operator=(CATIMshCVMSpa&&) noexcept = default;

    /**
     * Initializes the mesher after creation
     * The call to this function is MANDATORY
     * @param mesh
     *   The input mesh
     *  @return
     *   a HRESULT
     */
    HRESULT Init(CATIMshMesh* mesh);

    /**
     * Reset the mesher after the meshing step.
     * All the constraints will be discarded.
     * Parameters will remain unchanged.
     * The call to this function is MANDATORY in case
     * of mesh adaptation (several call to the Mesh function).
     * This function can only be called after a first call
     * to the Mesh function.
     *  @return
     *   a HRESULT
     */
    HRESULT Reset();

    /**
     * Can be used to release the mesher
     */
    void Release();

    /*
     * Sets the verbosity of the mesher
     * @param verbose
     *   the verbosity
     */
    void SetVerbose(const CATMshCVMVerbose verbose);

    /*
     * Sets the maximum number of threads to be used
     * @param maxNumberOfThreads
     *   the maximum number of threads
     */
    void SetMaxNumberOfThreads(const int maxNumberOfThreads);

    /*
     * Sets the level of reproducibility to be guaranteed
     * @param reproducibility
     *   the level of reproducibility
     */
    void SetReproducibility(const CATMshCVMReproducibility reproducibility);

    /*
     * Sets the type of metric
     * @param metric
     *   the type of metric
     */
    void SetMetric(const CATMshCVMMetric metric);

    /*
     * Sets the type of metric propagation
     * @param propagation
     *   the type of metric propagation
     */
    void SetMetricPropagation(const CATMshCVMMetricPropagation propagation);

    /*
     * Sets the type of element to target
     * @param elementTarget
     *   the type of element to target
     */
    void SetElementTarget(const CATMshCVMElementTarget elementTarget);

    /*
     * Sets the method of generation of elements
     * @param elementGeneration
     *   the method of generation of elements
     */
    void SetElementGeneration(const CATMshCVMElementGeneration elementGeneration);

    /*
     * Sets the components to compute
     * @param components
     *   the components
     */
    void SetComputeComponents(const CATMshCVMComponents components);

    /*
     * Sets the level of effort to use to remove internal points
     * @param effort
     *   the effort
     */
    void SetInternalPointsRemovalEffort(const CATMshCVMInternalPointsRemovalEffort effort);

    /*
     * Sets the level of optimization needed
     * @param level
     *   the level
     */
    void SetOptimizationLevel(const CATMshCVMOptimizationLevel level);

    /*
     * Sets the type of overconstrained elements
     * @param overConstrainedElement
     *   the type of overconstrained elements
     */
    void SetOverconstrainedElement(const CATMshCVMOverConstrainedElement overConstrainedElement);

    /*
     * Sets whether the surface can be modified or not
     * @param surfaceFrozen
     *   are surface changes allowed or not
     */
    void SetSurfaceFrozen(const bool surfaceFrozen);

    /*
     * Sets whether internal points can be inserted or not
     * @param internalPoints
     *   are internal points needed or not
     */
    void SetInternalPoints(const bool internalPoints);

    /*
     * Sets the ridge angle
     * @param boundaryLayerRidgeAngle
     *   the ridge angle
     */
    void SetSurfaceRidgeAngle(const double surfaceRidgeAngle);

    /*
     * Sets the gradation to use in the volume
     * @param volumeGradation
     *   the gradation in the volume
     */
    void SetVolumeGradation(const double volumeGradation);

    /*
     * Sets the minimum edge length in the volume
     * @param volumeMinEdgeLength
     *   the minimum edge length in the volume
     */
    void SetVolumeMinEdgeLength(const double volumeMinEdgeLength);

    /*
     * Sets the maximum edge length in the volume
     * @param volumeMaxEdgeLength
     *   the maximum edge length in the volume
     */
    void SetVolumeMaxEdgeLength(const double volumeMaxEdgeLength);

    /*
     * Sets the minimum size in the volume
     * @param volumeMinSize
     *   the minimum size in the volume
     */
    void SetVolumeMinSize(const double volumeMinSize);

    /*
     * Sets the maximum size in the volume
     * @param volumeMaxSize
     *   the maximum size in the volume
     */
    void SetVolumeMaxSize(const double volumeMaxSize);

    /*
     * Sets the desired number of layers in the volume
     * @param numberOfLayers
     *   the number of layers in the volume
     */
    void SetVolumeProximityLayers(const int numberOfLayers);

    /*
     * Sets whether to imprint boundary layers or not
     * @param boundaryLayerImprinting
     *   is imprinting needed in boundary layers
     */
    void SetBoundaryLayerImprinting(const bool boundaryLayerImprinting);

    /*
     * Add a uniform boundary layer constraint on a tag
     * @param tag
     *   the tag
     * @param h0
     *   the height of the first layer
     * @param n
     *   the number of boundary layers
     * @param r
     *   is the size relative to the surface or not
     * @return
     *   a HRESULT
     */
    HRESULT AddBoundaryLayerUniformConstraint(const CATMshTag tag, const double h0, const int n, const bool r);

    /*
     * Add a uniform boundary layer constraint on an oriented tag
     * @param tag
     *   the tag
     * @param orientation
     *   the orientation
     * @param h0
     *   the height of the first layer
     * @param n
     *   the number of boundary layers
     * @param r
     *   is the size relative to the surface or not
     * @return
     *   a HRESULT
     */
    HRESULT AddBoundaryLayerUniformConstraint(const CATMshTag tag, const CATMshElement::Orientation orientation, const double h0, const int n, const bool r);

    /*
     * Add an arithmetic boundary layer constraint on a tag
     * @param tag
     *   the tag
     * @param h0
     *   the height of the first layer
     * @param d
     *   the distance between two consecutive layers
     * @param b
     *   the blending
     * @param nMin
     *   the minimum number of boundary layers
     * @param nMax
     *   the maximum number of boundary layers
     * @param r
     *   is the size relative to the surface or not
     * @return
     *   a HRESULT
     */
    HRESULT AddBoundaryLayerArithmeticConstraint(const CATMshTag tag, const double h0, const double d, const double b, const int nMin, const int nMax, const bool r);

    /*
     * Add an arithmetic boundary layer constraint on an oriented tag
     * @param tag
     *   the tag
     * @param orientation
     *   the orientation
     * @param h0
     *   the height of the first layer
     * @param d
     *   the distance between two consecutive layers
     * @param b
     *   the blending
     * @param nMin
     *   the minimum number of boundary layers
     * @param nMax
     *   the maximum number of boundary layers
     * @param r
     *   is the size relative to the surface or not
     * @return
     *   a HRESULT
     */
    HRESULT AddBoundaryLayerArithmeticConstraint(const CATMshTag tag, const CATMshElement::Orientation orientation, const double h0, const double d, const double b, const int nMin, const int nMax, const bool r);

    /*
     * Add a geometric boundary layer constraint on a tag
     * @param tag
     *   the tag
     * @param h0
     *   the height of the first layer
     * @param p
     *   the progression between two consecutive layers
     * @param b
     *   the blending
     * @param nMin
     *   the minimum number of boundary layers
     * @param nMax
     *   the maximum number of boundary layers
     * @param r
     *   is the size relative to the surface or not
     * @return
     *   a HRESULT
     */
    HRESULT AddBoundaryLayerGeometricConstraint(const CATMshTag tag, const double h0, const double p, const double b, const int nMin, const int nMax, const bool r);

    /*
     * Add a geometric boundary layer constraint on an oriented tag
     * @param tag
     *   the tag
     * @param orientation
     *   the orientation
     * @param h0
     *   the height of the first layer
     * @param p
     *   the progression between two consecutive layers
     * @param b
     *   the blending
     * @param nMin
     *   the minimum number of boundary layers
     * @param nMax
     *   the maximum number of boundary layers
     * @param r
     *   is the size relative to the surface or not
     * @return
     *   a HRESULT
     */
    HRESULT AddBoundaryLayerGeometricConstraint(const CATMshTag tag, const CATMshElement::Orientation orientation, const double h0, const double p, const double b, const int nMin, const int nMax, const bool r);

    /*
     * Add an isotropic constraint at a given vertex index
     * @param vertexIndex
     *   the vertex index
     * @param sizeIso
     *   the isotropic size to be set
     * @return
     *   a HRESULT
     */
    HRESULT AddVertexSizeConstraint(const CATMshVertexIndex vertexIndex, const double sizeIso);

    /*
     * Add a relative isotropic constraint at a given vertex index
     * For now, this function can only be called in an adaptative
     * workflow after the Mesh function
     * @param vertexIndex
     *   the vertex index
     * @param sizeIso
     *   the isotropic size to be set
     * @param relative
     *   is the size relative or not
     * @return
     *   a HRESULT
     */
    HRESULT AddVertexSizeConstraint(const CATMshVertexIndex vertexIndex, const double sizeIso, const bool relative);

    /*
     * Add an anisotropic constraint at a given vertex index
     * For now, only the last size will be taken into account
     * @param vertexIndex
     *   the vertex index
     * @param sizeAniso
     *   the anisotropic size to be set
     * @return
     *   a HRESULT
     */
    HRESULT AddVertexSizeConstraint(const CATMshVertexIndex vertexIndex, const double (&sizeAniso)[6]);

    /*
     * Add an anisotropic constraint at a given vertex index
     * For now, only the last size will be taken into account
     * For now, this function can only be called in an adaptative
     * workflow after the Mesh function
     * @param vertexIndex
     *   the vertex index
     * @param sizeAniso
     *   the anisotropic size to be set
     * @param relative
     *   is the size relative or not
     * @return
     *   a HRESULT
     */
    HRESULT AddVertexSizeConstraint(const CATMshVertexIndex vertexIndex, const double (&sizeAniso)[6], const bool relative);

    /*
     * Add a sphere size constraint
     * For now, this constraint can not be mixed with VertexSizeConstraint
     * @param center
     *   the center of the sphere
     * @param radius
     *   the radius of the sphere
     * @param size
     *   the size to be set inside the sphere
     * @return
     *   a HRESULT
     */
    HRESULT AddSphereSizeConstraint(const double (&center)[3], const double radius, const double size);

    /*
     * Add a sphere size constraint
     * For now, this constraint can not be mixed with VertexSizeConstraint
     * @param center
     *   the center of the sphere
     * @param radius
     *   the radius of the sphere
     * @param sizeAniso
     *   the anisotropic sizeAniso to be set inside the sphere
     * @return
     *   a HRESULT
     */
    HRESULT AddSphereSizeConstraint(const double (&center)[3], const double radius, const double (&sizeAniso)[6]);

    /*
     * Add a cylinder size constraint
     * For now, this constraint can not be mixed with VertexSizeConstraint
     * @param p1
     *   the top center point of the cylinder
     * @param p2
     *   the bottom center point of the cylinder
     * @param radius
     *   the radius of the cylinder
     * @param size
     *   the size to be set inside the cylinder
     * @return
     *   a HRESULT
     */
    HRESULT AddCylinderSizeConstraint(const double (&p1)[3], const double (&p2)[3], const double radius, const double size);

    /*
     * Add a cylinder size constraint
     * For now, this constraint can not be mixed with VertexSizeConstraint
     * @param p1
     *   the top center point of the cylinder
     * @param p2
     *   the bottom center point of the cylinder
     * @param radius
     *   the radius of the cylinder
     * @param sizeAniso
     *   the anisotropic sizeAniso to be set inside the cylinder
     * @return
     *   a HRESULT
     */
    HRESULT AddCylinderSizeConstraint(const double (&p1)[3], const double (&p2)[3], const double radius, const double (&sizeAniso)[6]);

    /*
     * Add a cube size constraint
     * For now, this constraint can not be mixed with VertexSizeConstraint
     * @param xyzVi
     *   coordinates of the ith vertex of the cube
     * @param size
     *   the size to be set inside the cube
     * @return
     *   a HRESULT
     */
    HRESULT AddCubeSizeConstraint(const double (&xyzV1)[3], const double (&xyzV2)[3], const double (&xyzV3)[3], const double (&xyzV4)[3], const double (&xyzV5)[3], const double (&xyzV6)[3], const double (&xyzV7)[3], const double (&xyzV8)[3],
                                  const double size);

    /*
     * Add a cube size constraint
     * For now, this constraint can not be mixed with VertexSizeConstraint
     * @param xyzVi
     *   coordinates of the ith vertex of the cube
     * @param sizeAniso
     *   the anisotropic sizeAniso to be set inside the cube
     * @return
     *   a HRESULT
     */
    HRESULT AddCubeSizeConstraint(const double (&xyzV1)[3], const double (&xyzV2)[3], const double (&xyzV3)[3], const double (&xyzV4)[3], const double (&xyzV5)[3], const double (&xyzV6)[3], const double (&xyzV7)[3], const double (&xyzV8)[3],
                                  const double (&sizeAniso)[6]);

    /*
     * Add a frozen constraint at a given vertex index
     * @param vertexIndex
     *   the vertex index
     * @return
     *   a HRESULT
     */
    HRESULT AddFrozenConstraint(const CATMshVertexIndex vertexIndex);

    /*
     * Add a frozen constraint at a given element index
     * @param elementIndex
     *   the element index
     * @return
     *   a HRESULT
     */
    HRESULT AddFrozenConstraint(const CATMshElementIndex elementIndex);

    /*
     * Add a tracker constraint at a given vertex index
     * @param vertexIndex
     *   the vertex index to be tracked
     * @return
     *   a HRESULT
     */
    HRESULT AddTrackerConstraint(const CATMshVertexIndex vertexIndex);

    /*
     * Add a tracker constraint at a given element index
     * @param elementIndex
     *   the element index in the input mesh to be tracked
     * @return
     *   a HRESULT
     */
    HRESULT AddTrackerConstraint(const CATMshElementIndex elementIndex);

    /**
     * Generate a mesh
     *  @return
     *   a HRESULT
     */
    virtual HRESULT Mesh() override;

    /**
     * Get the generated mesh
     * @return
     *   the mesh
     */
    virtual CATIMshMesh* GetMesh() override;

    /*
     * Sets the mesher in sleep position.
     * Can be used between adaptation iteration to reduce memory footprint.
     */
    void Sleep();

    /*
     * Track a vertex index
     * Can be used to get the associativity between input and output vertices.
     * @param mesh
     *  the input mesh
     * @param index
     *  the index of a vertex
     * @return
     *  the corresponding vertex index in ouput mesh
     */
    CATMshVertexIndex Track(CATIMshMesh* mesh, CATMshVertexIndex index);

    /**
     * Unlock the product with a licence key
     * @return
     *   a HRESULT
     */
    HRESULT UnlockProduct(const char* key);

  public:
    /* Internal - Not documented */
    HRESULT AddTrackerConstraint(CATIMshMesh* mesh, const CATMshVertexIndex vertexIndex);
    HRESULT AddTrackerConstraint(CATIMshMesh* mesh, const CATMshElementIndex elementIndex);

  public:
    /*
     * DEPREACTED FEATURES
     */
    void SetRemoveInternalPoints(const bool removeInternalPoints);
    void SetRegularInsertion(const bool regularInsertion);
    void SetBoundaryLayerInsertion(const bool boundaryLayerInsertion);
    void SetCartesianCoreInsertion(const bool cartesianCoreInsertion);
    void SetCartesianCoreSize(const double cartesianCoreSize);
    void SetComplexConformityEnforcement(const bool complexConformityEnforcement);
    void SetSplitOverConstrained(const bool splitOverConstrained);
    void SetOptimization(const bool optimization);
    void SetAdaptation(const bool adaptation);
    void SetBoundaryLayerRidgeAngle(const double boundaryLayerRidgeAngle);
    HRESULT SetInterruptCallback(CATMshInterruptCB callback, void* userData);
    HRESULT SetMessageCallback(CATMshMessageCB callback, void* userData);
    HRESULT AddBoundaryLayerUniformConstraint(CATIMshMesh* mesh, const double h0, const int n, const bool r);
    HRESULT AddBoundaryLayerArithmeticConstraint(CATIMshMesh* mesh, const double h0, const double d, const double b, const int nMin, const int nMax, const bool r);
    HRESULT AddBoundaryLayerGeometricConstraint(CATIMshMesh* mesh, const double h0, const double p, const double b, const int nMin, const int nMax, const bool r);
    HRESULT UpdateMesh();
    base_type* GetCVMCore();

  private:
    impl* _impl;
};

#endif
