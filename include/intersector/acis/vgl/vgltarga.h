/*********************************************************************
 *                                                                   *
 *                          DevTools 1.8.0                           *
 *                                                                   *
 *  These coded instructions, statements and computer programs       *
 *  contain unpublished proprietary information of Tech Soft 3D,     *
 *  and are protected by Federal copyright law.  They may not be     *
 *  disclosed to third parties or copied or duplicated in any form,  *
 *  in whole or in part, without the prior written consent of        *
 *  Tech Soft 3D.                                                    *
 *                                                                   *
 *                 Copyright (C) 2023, Tech Soft 3D                  *
 *                                                                   *
 *********************************************************************/
/* local functions header file */
#ifndef VGLTARGA_DEF
#define VGLTARGA_DEF

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int
vgl_targaFileToMem(FILE*, unsigned int*);
extern int
vgl_targaSizeOfImage(FILE*, int*, int*);
extern void
vgl_targaMemToFile(FILE*, unsigned int*, int, int);

#ifdef __cplusplus
}
#endif

#endif
