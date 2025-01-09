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
#ifndef VGLGIF_DEF
#define VGLGIF_DEF

#include <stdio.h>
#include "vgl/vgldefs.h"

#define GIFWRITER_INTERLACE  1
#define GIFWRITER_DELAYTIME  2
#define GIFWRITER_LOOPS      3
#define GIFWRITER_COMPRESS   4
#define GIFWRITER_COLORMAP   5
#define GIFWRITER_COLORMATCH 6

#ifdef __cplusplus
extern "C" {
#endif

VKI_EXTERN vgl_GIFWriter*
vgl_GIFWriterBegin(void);
VKI_EXTERN void
vgl_GIFWriterEnd(vgl_GIFWriter* gifwriter);
VKI_EXTERN void
vgl_GIFWriterSetParami(vgl_GIFWriter* gifwriter, Vint type, Vint iparam);
VKI_EXTERN void
vgl_GIFWriterInitFile(vgl_GIFWriter* gifwriter, unsigned int* buffer, int xsize, int ysize, int bwflag, FILE* fp);
VKI_EXTERN void
vgl_GIFWriterAddImage(vgl_GIFWriter* gifwriter, unsigned int* buffer, int xsize, int ysize, FILE* fp);
VKI_EXTERN void
vgl_GIFWriterAppendImage(vgl_GIFWriter* gifwriter, unsigned int* buffer, int xsize, int ysize, FILE* fp);

#ifdef __cplusplus
}
#endif

#endif
