/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifdef MacCarbon
#include <stdio.h>

int stricmp(const char *s1, const char *s2);
int strnicmp(const char *s1, const char *s2, int n);

extern char * mac_fgets( char * string, int maxchar, FILE * file_pointer );

#define isascii(i) (i>=0 && i<128)

#endif