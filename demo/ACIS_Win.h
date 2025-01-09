// $Id: blend_smoke_test.hxx,v 1.4 2002/01/28 16:53:03 rocon Exp $
/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/

#pragma once

#include "resource.h"
class ENTITY_LIST;
class AcisOptions;
class outcome;
typedef outcome (*ACIS_fp)(ENTITY_LIST&,AcisOptions*);
