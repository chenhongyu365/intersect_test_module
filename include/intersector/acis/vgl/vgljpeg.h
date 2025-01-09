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
/* vgljpeg header */
#include <stdio.h>

#ifndef VGLJPEG_DEF
#define VGLJPEG_DEF

extern void
vgl_jpegWrite(FILE* fileptr, unsigned int* fbufi, int vd[2], int quality, int grayflag);
extern void
vgl_jpegRead1(FILE* fileptr, void** pcinfo, void** pjerr, int* width, int* height);
extern void
vgl_jpegRead2(FILE* fileptr, unsigned int* fbufi, int vd[2], void* pcinfo, void* pjerr);

#endif
