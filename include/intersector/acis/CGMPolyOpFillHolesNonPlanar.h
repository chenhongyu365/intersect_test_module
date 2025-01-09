/*******************************************************************/
/*    Copyright (c) 2016-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef CGMPolyOpFillHolesNonPlanar_H
#define CGMPolyOpFillHolesNonPlanar_H

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 **/

#include "CATCGMReferenceClassImplHolder.h"
#include "CATListOfInt.h"
#include "CATListOfShort.h"
#include "CGMCompPoly.h"
#include "CGMPolyImportHoleBoundary.h"
#include "CGMPolyImportOperator.h"

namespace CGMPolyImport {

    /**
     * This operator has two functionalities, [Func1] and [Func2]: <br>
     *
     *  [Func1] Fill planar and non-planar arbitrarily shaped holes, each one
     *          of them defined by ONE OPEN BOUNDARY (or closed loop).
     *          The operator tries to find an optimal 3D triangulation for each
     *          closed 3D polyline defining the boundary of a hole.
     *          The operator provides the option to:
     *             (i) Fill all holes at once (when the input is a surface
     *                 polyhedral mesh); and
     *             (ii) Fill one hole at a time (by providing the boundary of
     *                  the hole to be filled as input). <br>
     *
     *  [Func2] Fill a hole defined by a PAIR OF OPEN BOUNDARIES, i.e. two
     *          different closed 3D polylines, that can come from different
     *          meshes and must be provided as inputs.
     *          The operator tries to find an optimal 3D triangulation for the
     *          surface that connects the two closed polylines. <br>
     *
     * Optionally, the operator can also refine and smooth the 3D triangulations
     * created by [Func1] or [Func2]. Thus the hole filling process consists
     * of three completely independent stages: (1) Hole Triangulation; (2) Mesh
     * Refinement; and (3) Mesh Smoothing. The first stage is intrinsic to the
     * operator and is always carried out, while the other two are optional and
     * must be explicitly enabled by the user to be performed. <br>
     *
     * An extended explanation of each stage is provided below: <br>
     *
     *  (1) HOLE TRIANGULATION: <br>
     *      In the case of functionality [Func1], this operation creates a patch
     *      mesh or triangulated surface for each one of the holes existing in
     *      the original input mesh. <br>
     *      In the case of functionality [Func2], this operation creates a patch
     *      mesh or triangulated surface that connects the pair of input open
     *      boundaries. <br>
     *      The algorithm guarantees an optimal mesh in the sense that a given
     *      cost function is minimized (see method <tt>SetTriangulationCost</tt>
     *      to choose the objective function to be optimized). <br>
     *      <b>Note:</b> This operation does not guarantee intersection-free
     *               triangulations. Self-intersections can be fixed a posteriori
     *               by applying the <tt>Heal</tt> operator. <br><br>
     *
     *  (2) MESH REFINEMENT (OPTIONAL): This operation refines each individual
     *      patch mesh to obtain a Delaunay triangulation. <br>
     *      The mesh surrounding each hole is used to locally estimate length scales
     *      in order to produce refined patches with a mesh density or resolution
     *      similar to that of the neighboring triangles. This stage is convenient
     *      to improve the quality of the initial patch meshes. <br>
     *      <b>Note 1:</b> The user must explicitly activate this stage by
     *                 specifying the type of refinement criterion to be followed
     *                 to achieve a Delaunay triangulation (see further discussion
     *                 in method <tt>SetDoRefinement</tt>). <br>
     *      <b>Note 2:</b> This operation is only applied to the patch meshes
     *                 created by the Hole Triangulation stage. It means that
     *                 the refinement operation will never modify the input mesh,
     *                 regardless of whether or not it has holes. <br><br>
     *
     *  (3) MESH SMOOTHING (OPTIONAL): This operation makes more visually
     *      appealing each patch mesh. In practice, the smoothing is achieved
     *      by minimizing a fairness functional. The nature of this type of
     *      smoothing is global in the sense that the goal is not to preserve
     *      specific features of a mesh but to enhance the overall smoothness
     *      of the triangulated surface. <br>
     *      <b>Note 1:</b> This operation must be explicitly set by the user
     *                 in order to be activated (see method <tt>SetDoSmoothing</tt>
     *                 for a further discussion). <br>
     *      <b>Note 2:</b> This operation is only applied to the patch meshes
     *                 created by the Hole Triangulation stage and refined by the
     *                 Mesh Refinement stage. It means that the smoothing
     *                 operation will never modify the input mesh, whether it has
     *                 holes or not, and will not modify a patch mesh that has
     *                 not been refined. <br><br>
     *
     * <b>Differences with <tt>FillHoles</tt> operator:</b> <br>
     *    (a) <tt>FillHolesNonPlanar</tt> is able to fill holes with arbitrary
     *        shapes while <tt>FillHoles</tt> only works for planar holes
     *        or holes projectable onto planes (i.e. intersection-free planar
     *        projections). Notice that here each hole is defined by only one
     *        closed 3D polyline (one open boundary). <br>
     *    (b) <tt>FillHolesNonPlanar</tt> is able to fill a hole defined by two
     *        closed 3D polylines (two open boundaries) while <tt>FillHoles</tt>
     *        does not provide such a functionality. <br>
     *    (c) <tt>FillHolesNonPlanar</tt> allows the patch meshes spanning holes
     *        to be refined and smoothed, which is useful to make the final mesh
     *        more visually appealing. <br>
     *    (d) <tt>FillHolesNonPlanar</tt> is computationally more expensive both
     *        in space and time because triangulations have to be determined in
     *        the 3D space rather than on a flat surface. <br><br>
     *
     * @see Operator <br>
     **/
    class ExportedByCGMCompPoly FillHolesNonPlanar : public Operator {
      public:
        /**
         * Creates a <tt>FillHolesNonPlanar</tt> operator to perform
         * functionality [Func1], i.e., to fill multiple arbitrary planar
         * and non-planar holes in an input surface polyhedral mesh. <br>
         *
         * @param iMesh <br>
         *	The mesh to be operated on. <br>
         * @return <br>
         *	The <tt>FillHolesNonPlanar</tt> operator. <br>
         **/
        static FillHolesNonPlanar* Create(Mesh const& iMesh);

        /**
         * Creates a <tt>FillHolesNonPlanar</tt> operator to perform
         * functionality [Func1] for the case in which the boundary
         * of a planar or non-planar hole is provided. <br>
         *
         * @param iBoundary <br>
         *	Boundary defining the hole. <br>
         * @return <br>
         *	The <tt>FillHolesNonPlanar</tt> operator. <br>
         **/
        static FillHolesNonPlanar* Create(HoleBoundary const& iBoundary);

        /**
         * Creates a <tt>FillHolesNonPlanar</tt> operator to perform
         * functionality [Func2], i.e., to fill a hole defined by a pair of
         * open boundaries (two closed 3D polylines) provided as inputs. <br>
         *
         * @param iBoundary1 <br>
         *  The first boundary defining the hole. <br>
         * @param iBoundary2 <br>
         *	The second boundary defining the hole. <br>
         * @param iConnectionPoints1 <br>
         *   List containing point indices from iBoundary1 to be connected to
         *   corresponding point indices in iConnectionPoints2. <br>
         * @param iConnectionPoints2 <br>
         *   List containing point indices from iBoundary2 to be connected to
         *   corresponding point indices in iConnectionPoints1. <br>
         * @param iConnectionIsStrong <br>
         *   List containing information about the kind of connection. A "weak"
         *   connection is indicated with 0 while any other number (preferably 1)
         *   can be used to indicate that the connection is "strong". <br>
         * @return <br>
         *	The <tt>FillHolesNonPlanar</tt> operator. <br>
         *
         *    <b>Note 1:</b> Boundaries iBoundary1 and iBoundary2 can belong to
         *               different meshes. <br>
         *    <b>Note 2:</b> A connection can be thought of as a bridge between the
         *               boundaries iBoundary1 and iBoundary2, and is defined by the
         *               indices of two points, one belonging to each boundary. The
         *               point indices for each boundary have to be respectively
         *               indicated through iConnectionPoints1 and iConnectionPoints2.
         *               The numbering of indices starts in 0. <br>
         *    <b>Note 3:</b> A connection creates a physical edge between the two
         *               boundaries. This edge can be of kind "strong" or "weak".
         *               Strong means that the edge has to be kept when filling the
         *               hole (a sharp edge, for instance), while weak means that it
         *               can be smoothed out. The default is to set all the edges as
         *               "weak" if the list iConnectionIsStrong is empty. <br>
         *    <b>Note 4:</b> Lists iConnectionPoints1 and iConnectionPoints2 must
         *               always have the same length. If non-empty, list
         *               iConnectionIsStrong must also have the same length as
         *               the lists of connection points. <br>
         *    <b>Note 5:</b> If no connections are specified, the operator will make
         *               an attempt to construct at least two connections. <br>
         *
         *    <b>Example on how to construct the lists of connections. </b> <br>
         *       Given the lists: <br>
         *       iConnectionPoints1 = {8, 15}, <br>
         *       iConnectionPoints2 = {4, 8}, and <br>
         *       iConnectionIsStrong = {1, 0}, <br>
         *    the operator will interpret them as the representation of two
         *    connections.
         *    The first connection will create an edge of kind "strong" between
         *    points 8 and 4 of iBoundary1 and iBoundary2, respectively.
         *    The second connection will create a "weak" edge between the
         *    points 15 and 8 belonging to boundaries 1 and 2, respectively. <br>
         **/
        static FillHolesNonPlanar* Create(HoleBoundary const& iBoundary1, HoleBoundary const& iBoundary2, CATListOfInt const& iConnectionPoints1, CATListOfInt const& iConnectionPoints2, CATListOfShort const& iConnectionIsStrong);

        /**
         * Cost function involved in the Hole Triangulation stage. <br>
         * There are two types: <br>
         *   - Area: The total surface area of the hole is minimized. <br>
         *   - AngleArea: The cost function is defined by a pair (Angle, Area).
         *                A greedy algorithm finds the minimum area triangulation
         *                among those that minimize the maximum (worst)
         *                dihedral angle. <br>
         **/
        enum TriangulationCost { Area = 0, AngleArea = 1 };

        /**
         * Set the cost function involved in the computation of the optimal
         * triangulation that extends across each hole. <br>
         * The triangulation spanning each hole is optimal with respect to the
         * specified objective function and does not depend on the triangulation
         * computed for any other hole. <br>
         * The input mesh is not modified during the process. <br>
         *
         * @param iCost specifies the type of cost function: <br>
         *   - Area. <br>
         *   - AngleArea (DEFAULT). <br>
         *
         * <b>Note:</b> Hole Triangulation operation is always performed.
         *          Default cost function is applied when the user does not
         *          specified a preference. <br>
         **/
        virtual void SetTriangulationCost(TriangulationCost iCost) = 0;

        /**
         * Refinement used in the Mesh Refinement stage. <br>
         * There are three options: <br>
         *   - NoRefinement: Refinement of patch meshes is not performed. <br>
         *   - MaxCircumradiusRefinement: Delaunay triangulation follows a maximum
         *        circumradius splitting criterion. It means that a triangle is
         *        split/refined if its circumradius is larger than a value locally
         *        estimated for each patch mesh. This type of refinement produces
         *        unstructured uniform meshes. <br>
         *   - MinAngleRefinement: Delaunay triangulation follows a minimum angle
         *        splitting criterion. It implies that a triangle is refined only
         *        when any of its interior angles is less than 30 degrees and its
         *        circumradius is larger than a value locally estimated for each
         *        patch mesh. Coarse unstructured meshes having larger triangles
         *        in the interior and smaller closest to the boundary are
         *        generated by this type of refinement. <br>
         **/
        enum RefinementType { NoRefinement = 1, MaxCircumradiusRefinement = 2, MinAngleRefinement = 3 };

        /**
         * Set parameters to perform a Delaunay refinement of each patch mesh. <br>
         * Refined patch meshes are unstructured and the input mesh is not modified
         * during the process. <br>
         *
         * @param iType is the type of refinement: <br>
         *   - NoRefinement (DEFAULT). <br>
         *   - MaxCircumradiusRefinement. <br>
         *   - MinAngleRefinement. <br>
         *
         * <b>Note 1:</b> Refinement is not performed by default and must be
         *            explicitly enabled by the user. <br>
         * <b>Note 2:</b> MinAngle criterion produces unstructured meshes much more
         *            coarse than MaxCircumradius criterion. <br>
         * <b>Note 3:</b> Distortions or irregularities generated during refinement
         *            can be easily removed by applying smoothing operation. <br>
         **/
        virtual void SetDoRefinement(RefinementType iType) = 0;

        /**
         * Discrete operator used in the Mesh Smoothing stage. <br>
         * There are two types: <br>
         *   - Laplacian: Most convenient and robust from a computational
         *                point of view. <br>
         *   - Bilaplacian: Computationally more expensive but produces more
         *                  aesthetic meshes because takes into account surface
         *                  curvature effects. <br>
         **/
        enum SmoothingType { Laplacian = 1, Bilaplacian = 2 };

        /**
         * Weight required to construct the discrete operator used in the Mesh
         * Smoothing stage. <br>
         * There are two types: <br>
         *   - Uniform: More robust because weights depend only on the topology
         *              of the mesh. <br>
         *   - ScaleDependent: Less robust but includes length-scale dependences
         *                     through the coordinates of the vertices. <br>
         **/
        enum SmoothingWeight { Uniform = 1, ScaleDependent = 2 };

        /**
         * Set parameters to smooth or make more visually appealing the patch
         * meshes. <br>
         * Each patch mesh is smoothed separately and independently, but the same
         * set of parameters is used to compute each optimal smoothing. The input
         * mesh is not modified during the process. <br>
         * The parameters to be specified are: (1) type of discrete operator,
         * and (2) type of weight used to evaluate the discrete operator. <br>
         *
         * @param iType is the type of discrete operator: <br>
         *   - Laplacian. <br>
         *   - Bilaplacian. <br>
         *
         * @param iWeight is the type of weight used to construct the discrete
         *        operator: <br>
         *   - Uniform. <br>
         *   - ScaleDependent. <br>
         *
         * <b>Note 1:</b> The user must explicitly set the types of discrete
         *            operator and weights in order to enable the smoothing. <br>
         * <b>Note 2:</b> The combination Bilaplacian-ScaleDependent is recommended
         *            to produce the most aesthetic smoothing while Laplacian-Uniform
         *            is the most convenient choice if robustness and computational
         *            performance are the priorities. The other two alternatives
         *            are a kind of trade-off between robustness-performance and
         *            aesthetics. <br>
         **/
        virtual void SetDoSmoothing(SmoothingType iType, SmoothingWeight iWeight) = 0;

      protected:
        virtual ~FillHolesNonPlanar() {}
        FillHolesNonPlanar();

      private:
        FillHolesNonPlanar& operator=(FillHolesNonPlanar const& iOther);
        FillHolesNonPlanar(FillHolesNonPlanar const& iOther);
    };
}  // namespace CGMPolyImport
#endif
