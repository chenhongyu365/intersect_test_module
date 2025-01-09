/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef API_ACISPOLYHEDRA_INIT_H
#define API_ACISPOLYHEDRA_INIT_H

#include "api.hxx"
#include "dcl_acispolyhedra.h"
#include "CGMPolyImportPart.h"
#include "CGMPolyImportMesh.h"
#include "CGMContainer.h"

/**
 * \defgroup ACISPOLYAPI ACIS Polyhedra
 *
 */
/**
 * @file api_AcisPolyhedra_Init.h
 * \defgroup ACISPOLYINIAPI ACIS Polyhedra Initialization
 * \ingroup ACISPOLYAPI
 * @{
 */

/**
* Initializes the AcisPolyhedra component library.
* <br><br>
* <b>Role:</b> This API initializes the AcisPolyhedra component.
* It must be called before calling any AcisPolyhedra APIs.
* <br><br>
* <b>Effect:</b> System routine
* <br><br>
* <b>Journal:</b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Polyhedral
* <br><br>
*/

DECL_SPAACISPOLY outcome api_initialize_polyhedra();


/**
* Terminates the AcisPolyhedra component library.
* <br><br>
* <b>Role:</b> This API terminates the AcisPolyhedra component and frees its internal data.
* Further calls made to AcisPolyhedra APIs may cause unpredictable consequences.
* <br><br>
* <b>Effect:</b> System Routine
* <br><br>
* <b>Journal:</b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Polyhedral
* <br><br>
*/

DECL_SPAACISPOLY outcome api_terminate_polyhedra();

/**
Gets the default CGMContainer
* <br><br>
* <b>Role:</b> This API gets the default CGMContainer to carry out downstream CGM Poly operations.
* <br><br>
* <b>Effect:</b> System Routine
* <br><br>
* <b>Journal:</b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Polyhedral
* <br><br>
*/
DECL_SPAACISPOLY outcome api_get_default_cgm_container(CGMContainer*& oDefaultCGMContainer);

#endif

