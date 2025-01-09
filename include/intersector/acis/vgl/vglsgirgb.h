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
#ifndef VGLSGIRGB_DEF
#define VGLSGIRGB_DEF

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int
vgl_SGIRGBFileToMem(FILE*, unsigned int*);
extern int
vgl_SGIRGBMemToFile(FILE*, unsigned int*, int, int, int);
extern int
vgl_SGIRGBSizeOfImage(FILE*, int*, int*, int*);

#ifdef __cplusplus
}
#endif

#endif
