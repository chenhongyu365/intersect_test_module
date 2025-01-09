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
/* OpenGLDev object */

#ifndef OPENGLDEV_DEF
#define OPENGLDEV_DEF

#ifdef VKI_3DAPI_OPENGL

#ifdef VKI_WIND_X11
#include <X11/Xlib.h>
#ifdef VKI_LIBAPI_GLEW
#define GL_GLEXT_PROTOTYPES
#include "GL/glew.h"
#else
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#endif
#include <GL/glx.h>
#endif

#ifdef VKI_WIND_WIN32
#include <windows.h>
#include <tchar.h>
#ifdef VKI_LIBAPI_GLEW
#include "GL/glew.h"
#endif
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#endif

#ifdef VKI_WIND_MESA
#define GL_GLEXT_PROTOTYPES
#include "GL/gl.h"
#include "GL/osmesa.h"
#endif

#endif

#include "base/basedefs.h"
#include "vgl/vgldefs.h"
#include "vgl/drawfun.h"
#include "vgl/xfm.h"
#include "vgl/xfmstack.h"
#include "vgl/attstack.h"
#include "vgl/bitmap.h"
#include "vgl/rasfont.h"
#include "vgl/texture.h"
#include "vgl/rmode.h"
#include "vgl/pixelmap.h"
#include "vgl/fbuffer.h"

#ifdef VKI_3DAPI_OPENGL
typedef struct {
    GLuint vboid;
    Vint offset;
    Vint size;
    Vint deleted;
    Vint cflag;
    Vint vflag;
    Vint tflag;
    Vint dflag;
    Vint npts;
    Vint vsize;
} vgl_OpenGLDev_VBO;
#endif

#define VBO_BUFNUM 1024

struct vgl_OpenGLDev {
    Vint ierr;
#ifdef VKI_3DAPI_OPENGL
    int isxpix, isypix; /* hardware pixels in x,y */
    float sxcm, sycm;   /* hardware centimeters in x,y */
    int depth;          /* hardware planes in frame buffer */
    int sten_bits;      /* hardware planes in stencil buffer */
    int xorig, yorig;   /* requested position and size */
    int xsize, ysize;
    int ctxflag;                    /* use existing GL context */
    int visflag;                    /* requested size */
    float xlencm, ylencm;           /* device centimeters in x,y */
    float xgupcm, ygupcm;           /* resolution, pixels per centimeter */
    int p1x, p1y, p2x, p2y;         /* device pixel limits in x,y */
    float right, left, bottom, top; /* current projection x,y limits */
    float nearz, farz;              /* current projection z limits */
    int pxmn, pxmx, pymn, pymx;     /* current viewport x,y limits */
    float fzmn, fzmx;               /* current depth range z limits */
    Vfloat projsx, projsy, factsz;
    Vint projtype;
    Vint open;             /* window opened flag */
    Vint connect;          /* window connected flag */
    Vint rendermode;       /* VGL_RENDER or defer to rmode */
    Vint multisampleflag;  /* Multisample visual flag */
    float zpfact, zpbias;  /* current polygon factor and bias */
    int pgrendmode;        /* current polygon rendering mode */
                           /* current graphics modes */
    int idbfl;             /* doublebuffer mode */
    int ifbfl;             /* frontbuffer draw mode */
    int ifrfl;             /* frontbuffer read mode */
    int izbfl;             /* zbuffer mode */
    int truecolor;         /* true color mode */
    int iltfl;             /* lighting mode */
    int ixorm;             /* xor mode */
    int ipdfl;             /* polygon depth mode */
    int ibffl;             /* back face cull mode */
    int ifffl;             /* front face cull mode */
    int ifffpfl;           /* front face flip mode */
    int ipcfl;             /* point cull mode */
    int ilcfl;             /* line cull mode */
    int icpfl;             /* clip mode */
    int ieqfl;             /* event queue mode */
    int ibtfl;             /* blend transparency mode */
    int ilntfl;            /* line transparency mode */
    int itsfl;             /* two side light mode */
    int izwfl;             /* zbuffer write mode */
    int ilbfl;             /* leftbuffer draw mode */
    int irffl;             /* rasfontdraw mode */
    int itafl;             /* textanchor mode */
    int itdfl;             /* textdirection mode */
    int issfl;             /* select stack mode */
    int itpsfl;            /* textpixelsize mode */
    int izbfn;             /* zbuffer function comparison mode */
    int lsfact;            /* line style factor */
    int istfl;             /* stencil buffer mode */
    int ifwfl;             /* color buffer write mode */
    int ispfl;             /* swap mode */
    int palmfl;            /* point array light mode */
    int lalmfl;            /* line array light mode */
    int iupfl;             /* update mode */
    int msaamode;          /* multisample mode */
    int ssaomode;          /* ssao mode */
    int primmode;          /* primitive mode */
                           /* saved graphics modes */
    int inormalize;        /* GL_NORMALIZE */
    int ilighting;         /* GL_LIGHTING */
    int icolor_material;   /* GL_COLOR_MATERIAL */
    int idepth_test;       /* GL_DEPTH_TEST */
    int icull_face;        /* GL_CULL_FACE */
    int ipolystipple;      /* GL_POLYGON_STIPPLE */
    int ilinestipple;      /* GL_LINE_STIPPLE */
    int iscissortest;      /* GL_SCISSOR_TEST */
    int itexture1d;        /* GL_TEXTURE_1D */
    int itexture2d;        /* GL_TEXTURE_2D */
    int iblend;            /* GL_BLEND */
    int ipolydepth;        /* GL_POLYGON_OFFSET_FILL */
    GLfloat offset, units; /* glPolygonOffset */

    /* hardware capabilities */
    int dbufhard;   /* hardware double buffering */
    int zbufhard;   /* hardware z buffering */
    int overplanes; /* hardware number of overlay planes */
    int winsystem;  /* hardware window system */
    int xormhard;   /* hardware XOR operation */
    int plofhard;   /* hardware Polygonoffset operation */
    int sterhard;   /* hardware stereo */

    int polyflag; /* polygon primitive flag */
    int dcflag;   /* dc primitive flag */
    int planflag; /* text plane primitive flag */
    int plantemp;
    float path[3];
    float plane[3];
    float pixelsize;
    int iliton;                 /* lighting model status */
    float znear;                /* Z buffer near value */
    float znears;               /* Z buffer near value for lines */
    float zfar;                 /* Z buffer far value */
    float zfars;                /* Z buffer far value for lines */
    int izfull;                 /* Z buffer status */
    int itrpat;                 /* current pattern index */
    int itrans;                 /* non solid pattern active flag */
    float transp;               /* current transparency */
    int pointsize;              /* current point size */
    int pointstyle;             /* current point style */
    int linestyle;              /* current line style */
    int linewidth;              /* current line width */
    float intensity, shininess; /* current specularity */
    int rasfontind;             /* current raster font index */
    int textureind;             /* current texture index */
    int textureindpos;          /* last positive texture index */
    int bitmapind;              /* current bitmap index */
    GLubyte bmask[128];
    int forecind;      /* Foreground color index */
    float forecrgb[4]; /* Foreground color RGBA */
    int backcind;      /* Background color index */
    float backcrgb[4]; /* Background color RGB */
    float ctm[4][4];   /* current transformation matrix */

    vgl_OpenGLDev* oglshare;
    vgl_DrawFun* drawfun;
    vgl_Attstack* attstack;
    vsy_HashTable* rasfonthash;
    vsy_HashTable* texturehash;
    vgl_RasFont* rasfontcur;
    GLuint fontoffsetcur;
    Vint fonttextureindexcur;
    vsy_HashTable* bitmaphash;
    vgl_Xfmstack* xfmstack;
    vgl_Xfm* xfmtmp;
    vgl_RMode* rmode;
    /* update buffers */
    vgl_Pixelmap* fpixelmap;
    vgl_Pixelmap* zpixelmap;

    vgl_Bitmap* bitmap;
    Vuint pbitmap[3];
    Vuint dbitmap[10][3];

    /* stencil */
    Vuint stenwritemask;
    Vint stenfuncmode;
    Vint stenfuncref;
    Vuint stenfuncmask;
    Vint stenopfail;
    Vint stenopzfail;
    Vint stenopzpass;
    Vint bfsiz;
    Vuchar* bf;
    Vint mpts;
    Vfloat (*xb)[3];
    Vuint* ix;

    Vint parflag; /* parent specified */
    Vint pixflag; /* pixmap specified */
    Vint strflag; /* stereo pixelformat specified */
    Vint scpflag; /* swap copy pixelformat specified */
    Vint defflag; /* default pecified */
    GLuint tex1d; /* 1D texture name */
    GLuint tex2d; /* 2D texture name */
                  /* device specific elements */
#ifdef VKI_WIND_X11
    Display* display; /* test for connection */
    int screen;
    Window parent; /* X window parent */
    Window win;    /* X window */
    Pixmap pix;
    GLXPixmap glxpix; /* glX Pixmap */
    Visual* visual;
    Colormap cmap;
    GLXContext ctx;
#endif
#ifdef VKI_WIND_MESA
    OSMesaContext ctx;
    Vuchar* win;
    Vuchar* mesabuf;
#endif
#ifdef VKI_WIND_WIN32
    WNDCLASS wc;
    HWND parent;
    HWND win;
    HDC hdc;
    HGLRC ctx;
    HPALETTE palette;
    DWORD dwStyle;
    HMENU childid;
    _TCHAR AppName[33];
#endif
    Vint arrayflag;
    Vint pointernum;
    Vfloat* pointern;
    Vint vertexenabled;
    Vint textureenabled;
    Vint colorenabled;
    Vint normalenabled;
    GLint colorarraynum;
    GLenum colorarraytype;
    GLenum normalarraytype;
    GLenum normalarraystride;
    GLint texturearraynum;

    /* buffer data */
    Vint nvbos, *pnvbos;
    vgl_OpenGLDev_VBO *vbo, **pvbo;

    Vint shadermode;
    Vint lightflags[8];
    Vint texflag;
    Vint texenv;

    Vfloat* data;
    Vint ndata;
    Vint maxdata;

    /* floating point factors */
    Vfloat zbufferedgescale;
    Vfloat deformscale;
    Vfloat worldsize;
    Vfloat alphavalue;
    Vfloat colorvalue[3];
    Vfloat ssaodist;

    /* dflag offset for buffer */
    Vchar* dflagoff;
    Vint vsize;

    /* shader data */
    GLuint identvshader;
    GLuint identvoitshader;
    GLuint identfshader;
    GLuint identfoitshader1;
    GLuint identfoitshader2;
    GLuint zedgevshader;
    GLuint zedgefshader;
    GLuint useProg;
    GLuint identprog;
    GLuint identoitprog1;
    GLuint identoitprog2;
    GLuint zedgeprog;
    GLint xrloc;
    GLint yrloc;
    GLint xbloc;
    GLint ybloc;
    GLint wbloc;

    GLint xpixelloc;
    GLint ypixelloc;
    GLint idloc;
    GLint pbitmaploc;
    GLint dbitmaploc;
    GLint itsflloc;
    GLint lightenabledloc;
    GLint spriteloc; /* 1 if gl_PointSize in vertex shader */
    GLint spritesizeloc;
    GLint spritedepthloc;
    GLint spritedepth0loc;
    GLint spritedepth1loc;
    GLint l11loc;
    GLint w1loc;
    GLint l1factorloc;
    GLint worldsizeloc;

    /* oit light for spheres */
    GLint lightambientloc[8];
    GLint lightdiffuseloc[8];
    GLint lightspecularloc[8];
    GLint lightpositionloc[8];

    Vfloat lightambient[8][4];
    Vfloat lightdiffuse[8][4];
    Vfloat lightspecular[8][4];
    Vfloat lightposition[8][4];

    GLint dscaleflagloc;
    GLint scaleloc;
    GLint lightflagsloc;
    GLint clipflagsloc;
    GLint clipplanesloc;
    GLint tex1Dloc;
    GLint tex2Dloc;
    GLint texflagvloc;
    GLint texflagfloc;
    GLint texenvloc;
    GLint depthtex2loc;
    GLint colortex2loc;

    GLint pointstyleloc;
    GLint centerloc;
    GLint dscaleloc;
    GLint nvecflagloc;
    GLint nvecloc;

    GLint linecullflagloc;
    GLint depthpeelloc;
    GLint alphavalueloc;
    GLint colorvalueloc;
    GLint alphaflagloc;
    GLint colorflagloc;
    GLint shininessloc;
    GLint intensityloc;
    GLuint* geom_color;
    GLuint* geom_depth;
    GLuint* geom_fbo;
    GLint depthtexeloc;
    GLint colortexeloc;
    GLint depthtexeMSloc;
    GLint colortexeMSloc;
    GLint depthtexpeelloc;
    GLint colortexpeelloc;
    GLint depthtexpeelMSloc;
    GLint colortexpeelMSloc;
    GLint multisampleflagloc;
    GLint zbufferedgemodeloc;
    GLint edgescaleloc;

    GLint ssaomodeloc;
    GLint ssaonsamploc;
    GLint ssaorsamploc;
    GLint ssaodistloc;
    GLint ssaordistloc;
    GLint ssaofilterradiusloc;
    GLint isxloc;
    GLint isyloc;
    GLint ssaop2loc;
    GLint projtypeloc;
    GLint invmvprojloc;
    GLint pxiloc;
    GLint pyiloc;
    GLint leftloc;
    GLint bottomloc;

    /*
     * linked list oit algorithm
     * 0: atomic counter
     * 1: linked list
     */
    GLuint oitbuffers[3];
    /* the buffer for the head pointers, as an image texture */
    GLuint oitheadPtrTex;

    /* flag that oit mode is enabled */
    Vint oitmode;
    /* the number of entries in the linked list */
    GLuint oitmaxNodes;
    GLint oitmaxNodeloc;
    GLuint oitpass1index;
    GLuint oitpass2index;
    GLint zbuffermodeloc;

    /* maximum average number of layers to blend */
    Vint oitavelayers;

    Vint zbufferedgemode;
    Vint datadeformmode;
    Vint datasizemode;
    Vint alphavaluemode;
    Vint colorvaluemode;
    GLuint usingshader;
    Vint depthpeelmode;
    Vint depthpeellast;
    Vint drawfbo;
    Vint readfbo;
    Vint imagefbo;
    GLuint rendfbo;
    GLint maxtextures;
    Vint* clearflag;
    Vint maxpeel;
    Vint iversion;
    /* dataindex data */
    Vint nprims;                           /* current number of index primitive */
    Vint nrows;                            /* current number of index rows */
                                           /* render buffer_data */
    Vint buffercolorx, buffercolory;       /* Buffer Color size */
    Vint curbuffercolorx, curbuffercolory; /* Buffer Color size */
    Vint savedxsize, savedysize;

    Vint shadersupported;
    Vint multisamplesupported;
    Vint buffersupported;

    Vint hasoit;
    Vint oitmemfail;
    Vint deverror;

    /* dataindex shader data */
    Vint dataindexmaxrows;
    GLint dataindexnrowsloc;
    GLint dataindexnprimsloc;
    GLint dataindexloc;
    GLuint dataindexbuffer;
    GLuint dataindextexture;
    GLuint dataindexouttex[VGL_MAXDATAROWS];
    Vint* irowindex[VGL_MAXDATAROWS];
#ifdef VGL_TIMER
    vsy_Timer* timer;
#endif

#endif
#ifdef __cplusplus
  public:
    VKI_EXTERN
    vgl_OpenGLDev(void);
    VKI_EXTERN void* operator new(size_t);
    VKI_EXTERN ~vgl_OpenGLDev(void);
    VKI_EXTERN void
    operator delete(void*);
    VKI_EXTERN Vint
    Error();
#ifdef VKI_WIND_X11
    VKI_EXTERN void
    BestVisualX(Visual**);
#endif
#ifndef VKI_WIND_X11
    VKI_EXTERN void
    BestVisualX(void**);
#endif
    VKI_EXTERN void PositionWindow(Vint, Vint, Vint, Vint);
    VKI_EXTERN void VisualWindow(Vint);
    VKI_EXTERN void ParentWindow(Vword);
    VKI_EXTERN void
    ConfigureWindow(Vint, Vint*);
    VKI_EXTERN void
    ShareBuffers(vgl_OpenGLDev*);
    VKI_EXTERN void
    OpenWindow(const Vchar*);
    VKI_EXTERN void
    CloseWindow();
    VKI_EXTERN void ConnectWindow(Vword);
    VKI_EXTERN void
    DisconnectWindow();
    VKI_EXTERN void
    SetWindow();
    VKI_EXTERN void
    QueryWindow(Vword*);
    VKI_EXTERN void
    Clear();
    VKI_EXTERN void DrawTexture(Vint);
    VKI_EXTERN void
    Swap();
    VKI_EXTERN void
    Flush();
    VKI_EXTERN void
    Bell();
    VKI_EXTERN void Delay(Vfloat);
    VKI_EXTERN void
    Resize();
    VKI_EXTERN void SetMode(Vint, Vint);
    VKI_EXTERN void
    GetMode(Vint, Vint*);
    VKI_EXTERN void
    GetInteger(Vint, Vint*);
    VKI_EXTERN void
    GetFloat(Vint, Vfloat*);
    VKI_EXTERN void GetString(Vint, Vchar[]);
    VKI_EXTERN void
    FBufferRead(Vint, Vint, Vint, Vint, vgl_FBuffer*);
    VKI_EXTERN void
    FBufferWrite(Vint, Vint, Vint, Vint, vgl_FBuffer*);
    VKI_EXTERN void
    ZBufferRead(Vint, Vint, Vint, Vint, vgl_ZBuffer*);
    VKI_EXTERN void
    ZBufferWrite(Vint, Vint, Vint, Vint, vgl_ZBuffer*);
    VKI_EXTERN void
    PixelmapCreate(vgl_Pixelmap*);
    VKI_EXTERN void
    PixelmapDestroy(vgl_Pixelmap*);
    VKI_EXTERN void
    PixelmapRead(vgl_Pixelmap*);
    VKI_EXTERN void
    PixelmapWrite(vgl_Pixelmap*);
    VKI_EXTERN void
    BitmapDefine(Vint, vgl_Bitmap*);
    VKI_EXTERN void BitmapSelect(Vint);
    VKI_EXTERN void
    TextureDefine(Vint, vgl_Texture*);
    VKI_EXTERN void TextureSelect(Vint);
    VKI_EXTERN void
    RasFontDefine(Vint, vgl_RasFont*);
    VKI_EXTERN void RasFontSelect(Vint);
    VKI_EXTERN void ClipPlane(Vint, Vfloat[4]);
    VKI_EXTERN void SetSwitch(Vint, Vint, Vint);
    VKI_EXTERN void SetFactors(Vint, Vfloat[]);
    VKI_EXTERN void Light(Vint, Vint, Vfloat[3], Vfloat[3]);
    VKI_EXTERN void LightSwitch(Vint, Vint);
    VKI_EXTERN void LightModel(Vint, Vfloat, Vfloat);
    VKI_EXTERN void ProjOrtho(Vfloat, Vfloat, Vfloat, Vfloat, Vfloat, Vfloat);
    VKI_EXTERN void ProjFrustum(Vfloat, Vfloat, Vfloat, Vfloat, Vfloat, Vfloat);
    VKI_EXTERN void
    ProjPush();
    VKI_EXTERN void
    ProjPop();
    VKI_EXTERN void ProjLoad(Vfloat[4][4]);
    VKI_EXTERN void Viewport(Vint, Vint, Vint, Vint);
    VKI_EXTERN void DepthRange(Vfloat, Vfloat);
    VKI_EXTERN void PolygonOffset(Vfloat, Vfloat);
    VKI_EXTERN void PolygonMode(Vint);
    VKI_EXTERN void TextPlane(Vfloat[3], Vfloat[3]);
    VKI_EXTERN void TextPixelSize(Vfloat);
    VKI_EXTERN void
    PollMouse(Vint*, Vint*, Vint*, Vint*, Vint*);
    VKI_EXTERN void WarpMouse(Vint, Vint);
    VKI_EXTERN void SetCursor(Vint);
    VKI_EXTERN void
    PollModifiers(Vint*, Vint*);
    VKI_EXTERN void
    ReadQueue(Vint*, Vint*);
    VKI_EXTERN void
    TestQueue(Vint*);
    VKI_EXTERN void
    ResetQueue();
    VKI_EXTERN void PolyPoint(Vint, Vfloat[][3]);
    VKI_EXTERN void PolyPointColor(Vint, Vfloat[][3], Vfloat[][3]);
    VKI_EXTERN void PolyPointDC(Vint, Vfloat[3], Vint[][3]);
    VKI_EXTERN void PolyLine(Vint, Vint, Vfloat[][3]);
    VKI_EXTERN void PolyLineColor(Vint, Vint, Vfloat[][3], Vfloat[][3]);
    VKI_EXTERN void PolyLineDC(Vint, Vint, Vfloat[3], Vint[][3]);
    VKI_EXTERN void Polygon(Vint, Vint, Vfloat[][3], Vint, Vfloat[]);
    VKI_EXTERN void PolygonColor(Vint, Vint, Vfloat[][3], Vfloat[][3], Vint, Vfloat[]);
    VKI_EXTERN void PolygonDC(Vint, Vint, Vfloat[3], Vint[][3]);
    VKI_EXTERN void PolyPointArray(Vint, Vfloat[][3], Vint, void*, Vint, void*, Vint, Vfloat*, Vint, Vfloat*);
    VKI_EXTERN void PolyLineArray(Vint, Vint, Vfloat[][3], Vint, void*, Vint, void*, Vint, Vfloat*, Vint, Vfloat*);
    VKI_EXTERN void PolygonArray(Vint, Vint, Vfloat[][3], Vint, void*, Vint, void*, Vint, Vfloat*, Vint, Vfloat*);
    VKI_EXTERN void PolyArray(Vint, Vint, Vfloat[][3], Vint, void*, Vint, void*, Vint, Vfloat*, Vint, Vfloat*);
    VKI_EXTERN void PolyBuffer(Vint, Vint, Vint, Vint, Vint, Vint, Vint, Vint);
    VKI_EXTERN void PolyElemArray(Vint, Vint, Vuint[], Vfloat[][3], Vint, void*, Vint, void*, Vint, Vfloat*, Vint, Vfloat*);
    VKI_EXTERN void PolyElemBuffer(Vint, Vint, Vint, Vint, Vint, Vint, Vint, Vint, Vint, Vint);
    VKI_EXTERN void
    XfmPush();
    VKI_EXTERN void
    XfmPop();
    VKI_EXTERN void XfmMult(Vfloat[4][4]);
    VKI_EXTERN void XfmLoad(Vfloat[4][4]);
    VKI_EXTERN void AttPush(Vint);
    VKI_EXTERN void
    AttPop();
    VKI_EXTERN void PointSize(Vint);
    VKI_EXTERN void PointStyle(Vint);
    VKI_EXTERN void LineStyle(Vint);
    VKI_EXTERN void LineWidth(Vint);
    VKI_EXTERN void BackColorIndex(Vint);
    VKI_EXTERN void BackColor(Vfloat[3]);
    VKI_EXTERN void BackTrans(Vfloat);
    VKI_EXTERN void ColorIndex(Vint);
    VKI_EXTERN void Color(Vfloat[3]);
    VKI_EXTERN void Trans(Vfloat);
    VKI_EXTERN void TransIndex(Vint);
    VKI_EXTERN void Clip(Vint, Vint, Vint, Vint);
    VKI_EXTERN void Text(Vfloat[3], Vtchar*);
    VKI_EXTERN void TextDC(Vfloat[3], Vint[3], Vtchar*);
    VKI_EXTERN void Specularity(Vfloat, Vfloat);
    VKI_EXTERN void
    FBufferDataIndex(Vint, vgl_FBuffer*);
    VKI_EXTERN void
    DataIndex(Vint, Vint, Vint*);
    VKI_EXTERN void Data(Vint, Vfloat[]);
    VKI_EXTERN void PolyPointData(Vint, Vfloat[][3], Vint, Vfloat[]);
    VKI_EXTERN void PolyLineData(Vint, Vint, Vfloat[][3], Vint, Vfloat[]);
    VKI_EXTERN void PolygonData(Vint, Vint, Vfloat[][3], Vint, Vfloat*, Vint, Vfloat[]);
    VKI_EXTERN void Render(Vint);
    VKI_EXTERN void SelectRegion(Vint, Vint[]);
    VKI_EXTERN void
    SelectBuffer(Vint, Vint*, Vfloat*, Vfloat*);
    VKI_EXTERN void
    SelectQuery(Vint*);
    VKI_EXTERN void
    ExtentQuery(Vfloat*, Vfloat*, Vfloat*, Vfloat*, Vfloat*, Vfloat*);
    VKI_EXTERN void BufferSize(Vint, Vint);
    VKI_EXTERN void
    InitBuffer(Vint, Vint*);
    VKI_EXTERN void TermBuffer(Vint);
    VKI_EXTERN void CopyBuffer(Vint, Vint, Vfloat[][3], Vint, void*, Vint, void*, Vint, Vfloat*, Vint, Vfloat*, Vint*);
    VKI_EXTERN void
    CopyElemBuffer(Vint, Vint, Vuint*, Vint*);
    VKI_EXTERN void ReadBuffer(Vint, Vint, Vint, Vfloat[][3], Vint, void*, Vint, void*, Vint, Vfloat*, Vint, Vfloat*);
    VKI_EXTERN void
    ReadElemBuffer(Vint, Vint, Vint, Vuint*);
    VKI_EXTERN void PolyPointBuffer(Vint, Vint, Vint, Vint, Vint, Vint, Vint);
    VKI_EXTERN void PolyLineBuffer(Vint, Vint, Vint, Vint, Vint, Vint, Vint, Vint);
    VKI_EXTERN void PolygonBuffer(Vint, Vint, Vint, Vint, Vint, Vint, Vint, Vint);
    VKI_EXTERN void
    DrawFun(vgl_DrawFun*);
#endif
};

#ifdef __cplusplus
extern "C" {
#endif

VKI_EXTERN vgl_OpenGLDev*
vgl_OpenGLDevBegin(void);
VKI_EXTERN void
vgl_OpenGLDev_Construct(vgl_OpenGLDev* p);
VKI_EXTERN void
vgl_OpenGLDevEnd(vgl_OpenGLDev* p);
VKI_EXTERN void
vgl_OpenGLDev_Destruct(vgl_OpenGLDev* p);
VKI_EXTERN Vint
vgl_OpenGLDevError(vgl_OpenGLDev* p);
VKI_EXTERN void
vgl_OpenGLDevTestX(Vint* flag);
VKI_EXTERN void
vgl_OpenGLDevTestMesa(Vint* flag);
#ifdef VKI_WIND_X11
VKI_EXTERN void
vgl_OpenGLDevConnectX(Display* display, int screen);
#endif
#ifndef VKI_WIND_X11
VKI_EXTERN void
vgl_OpenGLDevConnectX(void* display, int screen);
#endif
VKI_EXTERN void
vgl_OpenGLDevTestWIN(Vint* flag);
VKI_EXTERN void
vgl_OpenGLDevConnectWIN(void);
VKI_EXTERN void
vgl_OpenGLDevConnectMesa(void);
VKI_EXTERN void
vgl_OpenGLDevDisconnect(void);
#ifdef VKI_WIND_X11
VKI_EXTERN void
vgl_OpenGLDevBestVisualX(vgl_OpenGLDev* p, Visual** bestvisual);
#endif
#ifndef VKI_WIND_X11
VKI_EXTERN void
vgl_OpenGLDevBestVisualX(vgl_OpenGLDev* p, void** bestvisual);
#endif
VKI_EXTERN void
vgl_OpenGLDevPositionWindow(vgl_OpenGLDev* p, Vint xorig, Vint yorig, Vint xsize, Vint ysize);
VKI_EXTERN void
vgl_OpenGLDevVisualWindow(vgl_OpenGLDev* p, Vint visflag);
VKI_EXTERN void
vgl_OpenGLDevParentWindow(vgl_OpenGLDev* p, Vword parent);
VKI_EXTERN void
vgl_OpenGLDevConfigureWindow(vgl_OpenGLDev* p, Vint oper, Vint* params);
VKI_EXTERN void
vgl_OpenGLDevShareBuffers(vgl_OpenGLDev* p, vgl_OpenGLDev* pshare);
VKI_EXTERN void
vgl_OpenGLDevOpenWindow(vgl_OpenGLDev* p, const Vchar* title);
VKI_EXTERN void
vgl_OpenGLDevCloseWindow(vgl_OpenGLDev* p);
VKI_EXTERN void
vgl_OpenGLDevConnectWindow(vgl_OpenGLDev* p, Vword window);
VKI_EXTERN void
vgl_OpenGLDevDisconnectWindow(vgl_OpenGLDev* p);
VKI_EXTERN void
vgl_OpenGLDevSetWindow(vgl_OpenGLDev* p);
VKI_EXTERN void
vgl_OpenGLDevQueryWindow(vgl_OpenGLDev* p, Vword* window);
VKI_EXTERN void
vgl_OpenGLDevClear(vgl_OpenGLDev* p);
VKI_EXTERN void
vgl_OpenGLDevDrawTexture(vgl_OpenGLDev* p, Vint id);
VKI_EXTERN void
vgl_OpenGLDevSwap(vgl_OpenGLDev* p);
VKI_EXTERN void
vgl_OpenGLDevFlush(vgl_OpenGLDev* p);
VKI_EXTERN void
vgl_OpenGLDevBell(vgl_OpenGLDev* p);
VKI_EXTERN void
vgl_OpenGLDevDelay(vgl_OpenGLDev* p, Vfloat sec);
VKI_EXTERN void
vgl_OpenGLDevResize(vgl_OpenGLDev* p);
VKI_EXTERN void
vgl_OpenGLDevSetMode(vgl_OpenGLDev* p, Vint mode, Vint flag);
VKI_EXTERN void
vgl_OpenGLDevGetMode(vgl_OpenGLDev* p, Vint mode, Vint* flag);
VKI_EXTERN void
vgl_OpenGLDevGetInteger(vgl_OpenGLDev* p, Vint type, Vint* params);
VKI_EXTERN void
vgl_OpenGLDevGetFloat(vgl_OpenGLDev* p, Vint type, Vfloat* params);
VKI_EXTERN void
vgl_OpenGLDevGetString(vgl_OpenGLDev* p, Vint type, Vchar params[]);
VKI_EXTERN void
vgl_OpenGLDevFBufferRead(vgl_OpenGLDev* p, Vint left, Vint right, Vint bottom, Vint top, vgl_FBuffer* fbuffer);
VKI_EXTERN void
vgl_OpenGLDevFBufferWrite(vgl_OpenGLDev* p, Vint left, Vint right, Vint bottom, Vint top, vgl_FBuffer* fbuffer);
VKI_EXTERN void
vgl_OpenGLDevZBufferRead(vgl_OpenGLDev* p, Vint left, Vint right, Vint bottom, Vint top, vgl_ZBuffer* zbuffer);
VKI_EXTERN void
vgl_OpenGLDevZBufferWrite(vgl_OpenGLDev* p, Vint left, Vint right, Vint bottom, Vint top, vgl_ZBuffer* zbuffer);
VKI_EXTERN void
vgl_OpenGLDevPixelmapCreate(vgl_OpenGLDev* p, vgl_Pixelmap* pixelmap);
VKI_EXTERN void
vgl_OpenGLDevPixelmapDestroy(vgl_OpenGLDev* p, vgl_Pixelmap* pixelmap);
VKI_EXTERN void
vgl_OpenGLDevPixelmapRead(vgl_OpenGLDev* p, vgl_Pixelmap* pixelmap);
VKI_EXTERN void
vgl_OpenGLDevPixelmapWrite(vgl_OpenGLDev* p, vgl_Pixelmap* pixelmap);
VKI_EXTERN void
vgl_OpenGLDevBitmapDefine(vgl_OpenGLDev* p, Vint index, vgl_Bitmap* bitmap);
VKI_EXTERN void
vgl_OpenGLDevBitmapSelect(vgl_OpenGLDev* p, Vint index);
VKI_EXTERN void
vgl_OpenGLDevTextureDefine(vgl_OpenGLDev* p, Vint index, vgl_Texture* texture);
VKI_EXTERN void
vgl_OpenGLDevTextureSelect(vgl_OpenGLDev* p, Vint index);
VKI_EXTERN void
vgl_OpenGLDevRasFontDefine(vgl_OpenGLDev* p, Vint index, vgl_RasFont* rasfont);
VKI_EXTERN void
vgl_OpenGLDevRasFontSelect(vgl_OpenGLDev* p, Vint index);
VKI_EXTERN void
vgl_OpenGLDevClipPlane(vgl_OpenGLDev* p, Vint index, Vfloat eqn[4]);
VKI_EXTERN void
vgl_OpenGLDevSetSwitch(vgl_OpenGLDev* p, Vint type, Vint index, Vint flag);
VKI_EXTERN void
vgl_OpenGLDevSetFactors(vgl_OpenGLDev* p, Vint type, Vfloat factors[]);
VKI_EXTERN void
vgl_OpenGLDevLight(vgl_OpenGLDev* p, Vint index, Vint type, Vfloat c[3], Vfloat x[3]);
VKI_EXTERN void
vgl_OpenGLDevLightSwitch(vgl_OpenGLDev* p, Vint index, Vint flag);
VKI_EXTERN void
vgl_OpenGLDevLightModel(vgl_OpenGLDev* p, Vint localviewer, Vfloat koffset, Vfloat krate);
VKI_EXTERN void
vgl_OpenGLDevProjOrtho(vgl_OpenGLDev* p, Vfloat left, Vfloat right, Vfloat bottom, Vfloat top, Vfloat nearz, Vfloat farz);
VKI_EXTERN void
vgl_OpenGLDevProjFrustum(vgl_OpenGLDev* p, Vfloat left, Vfloat right, Vfloat bottom, Vfloat top, Vfloat nearz, Vfloat farz);
VKI_EXTERN void
vgl_OpenGLDevProjPush(vgl_OpenGLDev* p);
VKI_EXTERN void
vgl_OpenGLDevProjPop(vgl_OpenGLDev* p);
VKI_EXTERN void
vgl_OpenGLDevProjLoad(vgl_OpenGLDev* p, Vfloat xfm[4][4]);
VKI_EXTERN void
vgl_OpenGLDevViewport(vgl_OpenGLDev* p, Vint left, Vint right, Vint bottom, Vint top);
VKI_EXTERN void
vgl_OpenGLDevDepthRange(vgl_OpenGLDev* p, Vfloat nearz, Vfloat farz);
VKI_EXTERN void
vgl_OpenGLDevPolygonOffset(vgl_OpenGLDev* p, Vfloat factor, Vfloat bias);
VKI_EXTERN void
vgl_OpenGLDevPolygonMode(vgl_OpenGLDev* p, Vint rend);
VKI_EXTERN void
vgl_OpenGLDevTextPlane(vgl_OpenGLDev* p, Vfloat path[3], Vfloat plane[3]);
VKI_EXTERN void
vgl_OpenGLDevTextPixelSize(vgl_OpenGLDev* p, Vfloat pixelsize);
VKI_EXTERN void
vgl_OpenGLDevPollMouse(vgl_OpenGLDev* p, Vint* px, Vint* py, Vint* but1, Vint* but2, Vint* but3);
VKI_EXTERN void
vgl_OpenGLDevWarpMouse(vgl_OpenGLDev* p, Vint px, Vint py);
VKI_EXTERN void
vgl_OpenGLDevSetCursor(vgl_OpenGLDev* p, Vint type);
VKI_EXTERN void
vgl_OpenGLDevPollModifiers(vgl_OpenGLDev* p, Vint* cntl, Vint* shft);
VKI_EXTERN void
vgl_OpenGLDevReadQueue(vgl_OpenGLDev* p, Vint* dev, Vint* val);
VKI_EXTERN void
vgl_OpenGLDevTestQueue(vgl_OpenGLDev* p, Vint* dev);
VKI_EXTERN void
vgl_OpenGLDevResetQueue(vgl_OpenGLDev* p);
VKI_EXTERN void
vgl_OpenGLDevPolyPoint(vgl_OpenGLDev* p, Vint npts, Vfloat x[][3]);
VKI_EXTERN void
vgl_OpenGLDevPolyPointColor(vgl_OpenGLDev* p, Vint npts, Vfloat x[][3], Vfloat c[][3]);
VKI_EXTERN void
vgl_OpenGLDevPolyPointDC(vgl_OpenGLDev* p, Vint npts, Vfloat x[3], Vint dc[][3]);
VKI_EXTERN void
vgl_OpenGLDevPolyLine(vgl_OpenGLDev* p, Vint type, Vint npts, Vfloat x[][3]);
VKI_EXTERN void
vgl_OpenGLDevPolyLineColor(vgl_OpenGLDev* p, Vint type, Vint npts, Vfloat x[][3], Vfloat c[][3]);
VKI_EXTERN void
vgl_OpenGLDevPolyLineDC(vgl_OpenGLDev* p, Vint type, Vint npts, Vfloat x[3], Vint dc[][3]);
VKI_EXTERN void
vgl_OpenGLDevPolygon(vgl_OpenGLDev* p, Vint type, Vint npts, Vfloat x[][3], Vint vtflag, Vfloat vt[]);
VKI_EXTERN void
vgl_OpenGLDevPolygonColor(vgl_OpenGLDev* p, Vint type, Vint npts, Vfloat x[][3], Vfloat c[][3], Vint vtflag, Vfloat vt[]);
VKI_EXTERN void
vgl_OpenGLDevPolygonDC(vgl_OpenGLDev* p, Vint type, Vint npts, Vfloat x[3], Vint dc[][3]);
VKI_EXTERN void
vgl_OpenGLDevPolyPointArray(vgl_OpenGLDev* p, Vint npts, Vfloat x[][3], Vint cflag, void* c, Vint vflag, void* v, Vint tflag,
                            Vfloat* t, Vint dflag, Vfloat* d);
VKI_EXTERN void
vgl_OpenGLDevPolyLineArray(vgl_OpenGLDev* p, Vint type, Vint npts, Vfloat x[][3], Vint cflag, void* c, Vint vflag, void* v,
                           Vint tflag, Vfloat* t, Vint dflag, Vfloat* d);
VKI_EXTERN void
vgl_OpenGLDevPolygonArray(vgl_OpenGLDev* p, Vint type, Vint npts, Vfloat x[][3], Vint cflag, void* c, Vint vflag, void* v,
                          Vint tflag, Vfloat* t, Vint dflag, Vfloat* d);
VKI_EXTERN void
vgl_OpenGLDevPolyArray(vgl_OpenGLDev* p, Vint type, Vint npts, Vfloat x[][3], Vint cflag, void* c, Vint vflag, void* v,
                       Vint tflag, Vfloat* t, Vint dflag, Vfloat* d);
VKI_EXTERN void
vgl_OpenGLDevPolyBuffer(vgl_OpenGLDev* p, Vint vboid, Vint offset, Vint type, Vint npts, Vint cflag, Vint vflag, Vint tflag,
                        Vint dflag);
VKI_EXTERN void
vgl_OpenGLDevPolyElemArray(vgl_OpenGLDev* p, Vint type, Vint npts, Vuint ix[], Vfloat x[][3], Vint cflag, void* c, Vint vflag,
                           void* v, Vint tflag, Vfloat* t, Vint dflag, Vfloat* d);
VKI_EXTERN void
vgl_OpenGLDevPolyElemBuffer(vgl_OpenGLDev* p, Vint elemvboid, Vint elemoffset, Vint vboid, Vint offset, Vint type, Vint npts,
                            Vint cflag, Vint vflag, Vint tflag, Vint dflag);
VKI_EXTERN void
vgl_OpenGLDevXfmPush(vgl_OpenGLDev* p);
VKI_EXTERN void
vgl_OpenGLDevXfmPop(vgl_OpenGLDev* p);
VKI_EXTERN void
vgl_OpenGLDevXfmMult(vgl_OpenGLDev* p, Vfloat xfm[4][4]);
VKI_EXTERN void
vgl_OpenGLDevXfmLoad(vgl_OpenGLDev* p, Vfloat xfm[4][4]);
VKI_EXTERN void
vgl_OpenGLDevAttPush(vgl_OpenGLDev* p, Vint mask);
VKI_EXTERN void
vgl_OpenGLDevAttPop(vgl_OpenGLDev* p);
VKI_EXTERN void
vgl_OpenGLDevPointSize(vgl_OpenGLDev* p, Vint psize);
VKI_EXTERN void
vgl_OpenGLDevPointStyle(vgl_OpenGLDev* p, Vint pstyle);
VKI_EXTERN void
vgl_OpenGLDevLineStyle(vgl_OpenGLDev* p, Vint lstyle);
VKI_EXTERN void
vgl_OpenGLDevLineWidth(vgl_OpenGLDev* p, Vint lwidth);
VKI_EXTERN void
vgl_OpenGLDevBackColorIndex(vgl_OpenGLDev* p, Vint index);
VKI_EXTERN void
vgl_OpenGLDevBackColor(vgl_OpenGLDev* p, Vfloat c[3]);
VKI_EXTERN void
vgl_OpenGLDevBackTrans(vgl_OpenGLDev* p, Vfloat transp);
VKI_EXTERN void
vgl_OpenGLDevColorIndex(vgl_OpenGLDev* p, Vint index);
VKI_EXTERN void
vgl_OpenGLDevColor(vgl_OpenGLDev* p, Vfloat c[3]);
VKI_EXTERN void
vgl_OpenGLDevTrans(vgl_OpenGLDev* p, Vfloat transp);
VKI_EXTERN void
vgl_OpenGLDevTransIndex(vgl_OpenGLDev* p, Vint index);
VKI_EXTERN void
vgl_OpenGLDevClip(vgl_OpenGLDev* p, Vint left, Vint right, Vint bottom, Vint top);
VKI_EXTERN void
vgl_OpenGLDevText(vgl_OpenGLDev* p, Vfloat x[3], Vtchar* string);
VKI_EXTERN void
vgl_OpenGLDevTextDC(vgl_OpenGLDev* p, Vfloat x[3], Vint dc[3], Vtchar* string);
VKI_EXTERN void
vgl_OpenGLDevSpecularity(vgl_OpenGLDev* p, Vfloat intensity, Vfloat shininess);
VKI_EXTERN void
vgl_OpenGLDevFBufferDataIndex(vgl_OpenGLDev* p, Vint irow, vgl_FBuffer* fbuffer);
VKI_EXTERN void
vgl_OpenGLDevDataIndex(vgl_OpenGLDev* p, Vint nprims, Vint nrws, Vint* index);
VKI_EXTERN void
vgl_OpenGLDevData(vgl_OpenGLDev* p, Vint nrws, Vfloat d[]);
VKI_EXTERN void
vgl_OpenGLDevPolyPointData(vgl_OpenGLDev* p, Vint npts, Vfloat x[][3], Vint nrws, Vfloat d[]);
VKI_EXTERN void
vgl_OpenGLDevPolyLineData(vgl_OpenGLDev* p, Vint type, Vint npts, Vfloat x[][3], Vint nrws, Vfloat d[]);
VKI_EXTERN void
vgl_OpenGLDevPolygonData(vgl_OpenGLDev* p, Vint type, Vint npts, Vfloat x[][3], Vint nrws, Vfloat* d, Vint vtflag, Vfloat vt[]);
VKI_EXTERN void
vgl_OpenGLDevRender(vgl_OpenGLDev* p, Vint type);
VKI_EXTERN void
vgl_OpenGLDevSelectRegion(vgl_OpenGLDev* p, Vint type, Vint params[]);
VKI_EXTERN void
vgl_OpenGLDevSelectBuffer(vgl_OpenGLDev* p, Vint size, Vint* indexlist, Vfloat* mindepth, Vfloat* maxdepth);
VKI_EXTERN void
vgl_OpenGLDevSelectQuery(vgl_OpenGLDev* p, Vint* hits);
VKI_EXTERN void
vgl_OpenGLDevExtentQuery(vgl_OpenGLDev* p, Vfloat* lft, Vfloat* rgt, Vfloat* btm, Vfloat* top, Vfloat* znear, Vfloat* zfar);
VKI_EXTERN void
vgl_OpenGLDevBufferSize(vgl_OpenGLDev* p, Vint xsize, Vint ysize);
VKI_EXTERN void
vgl_OpenGLDevInitBuffer(vgl_OpenGLDev* p, Vint size, Vint* vboid);
VKI_EXTERN void
vgl_OpenGLDevTermBuffer(vgl_OpenGLDev* p, Vint vboid);
VKI_EXTERN void
vgl_OpenGLDevCopyBuffer(vgl_OpenGLDev* p, Vint vboid, Vint npts, Vfloat x[][3], Vint cflag, void* c, Vint vflag, void* v,
                        Vint tflag, Vfloat* t, Vint dflag, Vfloat* d, Vint* offset);
VKI_EXTERN void
vgl_OpenGLDevCopyElemBuffer(vgl_OpenGLDev* p, Vint vboid, Vint npts, Vuint* ix, Vint* offset);
VKI_EXTERN void
vgl_OpenGLDevReadBuffer(vgl_OpenGLDev* p, Vint vboid, Vint offset, Vint npts, Vfloat x[][3], Vint cflag, void* c, Vint vflag,
                        void* v, Vint tflag, Vfloat* t, Vint dflag, Vfloat* d);
VKI_EXTERN void
vgl_OpenGLDevReadElemBuffer(vgl_OpenGLDev* p, Vint vboid, Vint offset, Vint npts, Vuint* ix);
VKI_EXTERN void
vgl_OpenGLDevPolyPointBuffer(vgl_OpenGLDev* p, Vint vboid, Vint offset, Vint npts, Vint cflag, Vint vflag, Vint tflag, Vint dflag);
VKI_EXTERN void
vgl_OpenGLDevPolyLineBuffer(vgl_OpenGLDev* p, Vint vboid, Vint offset, Vint type, Vint npts, Vint cflag, Vint vflag, Vint tflag,
                            Vint dflag);
VKI_EXTERN void
vgl_OpenGLDevPolygonBuffer(vgl_OpenGLDev* p, Vint vboid, Vint offset, Vint type, Vint npts, Vint cflag, Vint vflag, Vint tflag,
                           Vint dflag);
VKI_EXTERN void
vgl_OpenGLDevDrawFun(vgl_OpenGLDev* p, vgl_DrawFun* df);

#ifdef __cplusplus
}
#endif

#endif
