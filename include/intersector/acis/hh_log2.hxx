/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/

#include <stdio.h>
#include "dcl_stitch.h"

//---------------------------------------
// Utility functions relating to logfile
//---------------------------------------

// Function for setting the Log File pointer (default value is NULL)
DECL_STITCH int
hh_set_stitch_log_file ( FILE* );

// Function for getting the current value of the Log File pointer
DECL_STITCH FILE*
hh_get_stitch_log_file (void);

// Function for getting the current value of the Log File pointer
DECL_STITCH void
hh_reset_stitch_log_file (void);

//---------------------------------------------------------------------------
