/*******************************************************************/
/*    Copyright (c) 1999-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef API_ACISPOLYHEDRA_DECIMATE_H
#define API_ACISPOLYHEDRA_DECIMATE_H

#include "api.hxx"
#include "dcl_acispolyhedra.h"

class BODY;
class polyhedra_decimate_options_impl;

/**
 * @file api_AcisPolyhedra_Decimate.h
 * \defgroup ACISPOLYDECAPI ACIS Polyhedra Decimation
 * \ingroup ACISPOLYAPI
 * @{
 */

/**
 * Options for the decimation of a polyhedral body.
 * This class contains parameters that govern the behavior of @href api_polyhedra_decimate.
 * <b>Technical Article:</b> <i>[Decimation](http://doc.spatial.com/articles/d/e/c/Decimation.html)</i>
 * <br><br>
 * <br>
 * <b>Role :</b>  <tt>polyhedra_decimate_options</tt> allows customization of behavior for @href api_polyhedra_decimate.
 * The constructor of @href polyhedra_decimate_options initializes all the parameters to their default value.
 * You can use the <tt>set</tt> functions to change any of the parameters and the <tt>get</tt> functions
 * to obtain the current value of the parameter set into a @href polyhedra_decimate_options object. <br>
 * <ul>
 * <li> <b>Freeze Boundary</b><br>
 * Flag that controls whether or not boundary ( Along Edges ) to be decimated or not.
 * <li> <b>Sag Value</b><br>
 * The amount of decimation is controlled by the input sag value, which determines the amount by which the output mesh is allowed to deviate from the input mesh.
 * <br><br>
 * A sample snippet code to illustrate the usage is given below: <br>
 * <pre>
 * double sag = 0.1;
 * polyhedra_decimate_options pdo;
 * pdo.set_sag_value(sag);
 * pdo.set_freeze_boundary(true);
 *
 * check_outcome(api_polyhedra_decimate(poly_body, &pdo));
 *
 * </pre>
 * <br>
 *
 * @see api_polyhedra_decimate
 */
class DECL_SPAACISPOLY polyhedra_decimate_options : public ACIS_OBJECT {
    polyhedra_decimate_options_impl* Impl;

    polyhedra_decimate_options(polyhedra_decimate_options const& input);

    polyhedra_decimate_options& operator=(polyhedra_decimate_options const& input);

  public:
    // ********************************************************************

    // Constructor
    polyhedra_decimate_options();

    // Destructor
    ~polyhedra_decimate_options();

    // ********************************************************************

    /**
     * Disallow triangle edges on the boundary from being decimated. False by default.
     */
    void set_freeze_boundary(bool do_freeze);

    /**
     * Query whether triangle edges on the boundary are frozen during decimation. False by default.
     */
    bool get_freeze_boundary() const;
    // ********************************************************************

    /**
     * The amount of decimation is controlled by the input sag value, which determines
     * the amount by which the output mesh is allowed to deviate from the input mesh.
     * Default sag value is 0.001.
     */
    void set_sag_value(double value);

    /**
     * Query current sag value. Default sag value is 0.001.
     */
    double get_sag_value() const;

    // ********************************************************************
};

/**
 * Decimates the polyhedral geometry of an ACIS body.
 * <b>Technical Article:</b> <i>[Decimation](http://doc.spatial.com/articles/d/e/c/Decimation.html)</i>
 * <br><br>
 * <b>Role: </b> This API reduces the number of triangles ("decimation") in the polyhedral geometry underneath the input ACIS body.
 * <br><br>
 * <b>Errors:</b>
 * <ul>
 * <li><tt>NOT_ACISPOLY_BODY</tt>: Input is not a polyhedral BODY.</li>
 * <li><tt>ACISPOLY_ALGO_FAILED</tt>: ACIS Polyhedra operation failed due to algorithmic issues.</li>
 * <li><tt>ACISPOLY_INTERNAL_ERROR</tt>: Internal Error in ACIS Polyhedra Component.</li>
 * </ul>
 * <br><br>
 * <b>Limitations:</b>
 * <ul>
 * <li>Non-polyhredral ACIS input body is not supported. </li>
 * </ul>
 * <br><br>
 * <b>Journal:</b> Available
 * <br><br>
 * <b>Product(s):</b> 3D ACIS Polyhedral
 * <br><br>
 * @param body
 * ACIS BODY with polyhedra mesh geometry
 * @param decimate_options
 * polyhedra_decimate_options
 * @param ao
 * ACIS options.
 */

outcome DECL_SPAACISPOLY api_polyhedra_decimate(BODY* body, polyhedra_decimate_options* decimate_options = NULL, AcisOptions* ao = NULL);

#endif
