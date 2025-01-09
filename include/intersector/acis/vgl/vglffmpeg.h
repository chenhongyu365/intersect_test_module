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
/* FFMPEG utility functions header file */

#ifndef VGLFFMPEG_DEF
#define VGLFFMPEG_DEF

#ifdef __cplusplus
extern "C" {
#endif

VKI_EXTERN void
vgl_ffmpegInit(void);
VKI_EXTERN Vint
vgl_ffmpegOpen(vgl_FBuffer* p, Vint codectype, Vint filetype, Vchar filename[]);
VKI_EXTERN void
vgl_ffmpegWrite(vgl_FBuffer* p, Vuchar yuv[]);
VKI_EXTERN void
vgl_ffmpegClose(vgl_FBuffer* p);

#ifdef __cplusplus
}
#endif

#endif /* VGLFFMPEG_DEF */
