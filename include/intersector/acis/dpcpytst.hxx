// $Id: dpcpytst.hxx,v 1.3 2001/04/10 17:47:30 acisdev Exp $
/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef DPCPYTST
#define DPCPYTST

#include "dcl_kern.h"
#include "lists.hxx"
#include "logical.h"

DECL_KERN logical test_deep_copy(ENTITY_LIST const& entity_list, double numerical_tolerance, logical report_all_errors, char* file1, char* file2);

DECL_KERN logical test_sat_file_diff(const char* file1, const char* file2, double tol, logical report_all_errors);

#endif
