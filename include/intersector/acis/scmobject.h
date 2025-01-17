/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
/* The Scheme object representation, and a few other important
 * data types.
 */
/**
 * @file scmobject.h
 * @CAA2Level L1
 * @CAA2Usage U1
 * \addtogroup SCMAPI
 * \Declared at <scmobject.h>
 * @{
 */
#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include "funcproto.h"
#include "mmgr.hxx"

/**
 * Declaration of Scheme object data type.
 */
typedef struct {
    size_t data;
    int tag;
} ScmObject;

#define FIXBITS         (8 * sizeof(int))
#define SIGNBIT         ((unsigned)1 << (FIXBITS-1))
#define CONSTBIT        1
#define TYPEBITS        (8 * sizeof(int) - 1)
#define MAX_TYPE        ((1 << TYPEBITS) - 1)

#define UFIXNUM_FITS(i) (((i) & SIGNBIT) == 0)
#define FIXNUM_FITS(i)  1

#define TYPE(x)         ((x).tag >> 1)

#define FIXNUM(x)       ((int)(x).data)
#define CHAR(x)         ((char)(x).data)

#define POINTER(x)      ((x).data)
#define SETPOINTER(x,p) ((x).data = (size_t)(p))
#define SET(x,t,p)      ((x).tag = (int)t << 1, (x).data = (size_t)(p))

#define ISCONST(x)      ((x).tag & CONSTBIT)
#define SETCONST(x)     ((x).tag |= CONSTBIT)

#define EQ(x,y)         ((x).data == (y).data && (x).tag == (y).tag)

/* GC related macros:
 */
#define WAS_FORWARDED(obj) (TYPE(*(ScmObject *)POINTER(obj)) == T_Broken_Heart)
#define UPDATE_OBJ(obj)    SETPOINTER(obj, POINTER(*(ScmObject *)POINTER(obj)))

#ifdef GENERATIONAL_GC
/*
// tbrv
*/
/**
 * @nodoc
 */
   typedef int  gcspace_t;            /* type used for space and type arrays */
/*
// tbrv
*/
/**
 * @nodoc
 */
   typedef size_t gcptr_t;     /* type used for pointers */
/*
// tbrv
*/
/**
 * @nodoc
 */
   typedef size_t pageno_t;    /* type used for page numbers */
/*
// tbrv
*/
/**
 * @nodoc
 */
   typedef size_t addrarith_t; /* type used for address arithmetic */
/*
// tbrv
*/
/**
 * @nodoc
 */
   extern gcspace_t *space;

/*
// tbrv
*/
/**
 * @nodoc
 */
 extern gcspace_t current_space;
   C_LINKAGE_BEGIN
/*
// tbrv
*/
/**
 * @nodoc
 */
   extern Visit P_((ScmObject*));       /* required for REVIVE_OBJ below */
   C_LINKAGE_END

#  ifdef ARRAY_BROKEN
   extern pageno_t pagebase;
#  else
#  define pagebase ((pageno_t)0)
#  endif

#  define PAGEBYTES        512
#  define PAGE_TO_OBJ(p)   ((ScmObject *) (((p) + pagebase) * PAGEBYTES))
#  define OBJ_TO_PAGE(p)   ((((gcptr_t)POINTER(p)) / PAGEBYTES) - pagebase)
#  define STABLE(x)        ((~space[(x)]) & 1)
#  define MAKEOBJ(o,t,p)   (SET(o, t, p))
#  define IS_ALIVE(obj)    ((WAS_FORWARDED(obj)) || \
                            (STABLE(OBJ_TO_PAGE(obj))) || \
			    (space[OBJ_TO_PAGE(obj)] == current_space))
#  define REVIVE_OBJ(obj)  Visit (&obj);
#else
#  define IS_ALIVE(obj)    WAS_FORWARDED(obj)
#  define REVIVE_OBJ(obj)
#endif

/* Fixed types.  Cannot use enum, because the set of types is extensible:
 */
#define T_Fixnum          0      /* Must be 0 */
#define T_Bignum          1
#define T_Flonum          2
#define T_Null            3      /* empty list */
#define T_Boolean         4      /* #t (1) and #f (0) */
#define T_Unbound         5      /* only used internally */
#define T_Special         6      /* only used internally */
#define T_Character       7
#define T_Symbol          8
#define T_Pair            9
#define T_Environment    10      /* A pair */
#define T_String         11
#define T_Vector         12
#define T_Primitive      13      /* Primitive procedure */
#define T_Compound       14      /* Compound procedure */
#define T_Control_Point  15
#define T_Promise        16      /* Result of (delay expression) */
#define T_Port           17
#define T_End_Of_File    18
#define T_Autoload       19
#define T_Macro          20
#define T_Broken_Heart   21      /* only used internally */
#ifdef GENERATIONAL_GC
#  define T_Align_8Byte  22      /* only used internally */
#  define T_Freespace    23      /* only used internally */
#endif

#define BIGNUM(x)   ((struct S_Bignum *)POINTER(x))
#define FLONUM(x)   ((struct S_Flonum *)POINTER(x))
#define STRING(x)   ((struct S_String *)POINTER(x))
#define VECTOR(x)   ((struct S_Vector *)POINTER(x))
#define SYMBOL(x)   ((struct S_Symbol *)POINTER(x))
#define PAIR(x)     ((struct S_Pair *)POINTER(x))
#define PRIM(x)     ((struct S_Primitive *)POINTER(x))
#define COMPOUND(x) ((struct S_Compound *)POINTER(x))
#define CONTROL(x)  ((struct S_Control *)POINTER(x))
#define PROMISE(x)  ((struct S_Promise *)POINTER(x))
#define PORT(x)     ((struct S_Port *)POINTER(x))
#define AUTOLOAD(x) ((struct S_Autoload *)POINTER(x))
#define MACRO(x)    ((struct S_Macro *)POINTER(x))

/*
// tbrv
*/
/**
 * @nodoc
 */
typedef unsigned short gran_t;	/* Granularity of bignums */

/*
// tbrv
*/
/**
 * @nodoc
 */
struct S_Bignum {
    ScmObject minusp;
    unsigned size;		/* Number of ushorts allocated */
    unsigned usize;		/* Number of ushorts actually used */
    gran_t data[1];		/* Data, lsw first */
};

/*
// tbrv
*/
/**
 * @nodoc
 */
struct S_Flonum {
    ScmObject tag;               /* Each S_Foo must start with an ScmObject */
    double val;
};

/*
// tbrv
*/
/**
 * @nodoc
 */
struct S_Symbol {
    ScmObject value;
    ScmObject next;
    ScmObject name;               /* A string */
    ScmObject plist;
};

/*
// tbrv
*/
/**
 * @nodoc
 */
struct S_Pair {
    ScmObject car, cdr;
};

/*
// tbrv
*/
/**
 * @nodoc
 */
struct S_String {
    ScmObject tag;
    int size;
    char data[1];
};

/*
// tbrv
*/
/**
 * @nodoc
 */
struct S_Vector {
    ScmObject tag;
    int size;
    ScmObject data[1];
};

/*
// tbrv
*/
/**
 * @nodoc
 */
enum discipline { EVAL, NOEVAL, VARARGS };
/*
// tbrv
*/
/**
 * @nodoc
 */
struct S_Primitive {
    ScmObject tag;
    /**
	 * @nodoc
	 */
    ScmObject (*fun) P_((ELLIPSIS));
    const char *name;
    int minargs;
    int maxargs;    /* Or MANY */
    enum discipline disc;
};
#define MANY    100

/*
// tbrv
*/
/**
 * @nodoc
 */
struct S_Compound {
    ScmObject closure;     /* (lambda (args) form ...) */
    ScmObject env;         /* Procedure's environment */
    int min_args, max_args;
    int numforms;
    ScmObject name;
};

/*
// tbrv
*/
/**
 * @nodoc
 */
typedef struct wind {
    struct wind *next, *prev;
    ScmObject inout;                  /* Pair of thunks */
} WIND;

/*
// tbrv
*/
/**
 * @nodoc
 */
typedef struct funct {
    struct funct *next;
    char *name;
    void (*func) P_((void));
} FUNCT;

/*
// tbrv
*/
/**
 * @nodoc
 */
typedef struct gcnode {
    struct gcnode *next;
    int gclen;
    ScmObject *gcobj;
} GCNODE;

/*
// tbrv
*/
/**
 * @nodoc
 */
typedef struct mem_node {
    struct mem_node *next;
    unsigned len;
    unsigned long refcnt;
} MEM_NODE;

#if defined(vax) || defined(__vax__)
   typedef int jmp_buf[17];
#else
#  include <setjmp.h>
#endif

/*
// tbrv
*/
/**
 * @nodoc
 */
struct S_Control {
    ScmObject env;
    GCNODE *gclist;
    MEM_NODE *memlist;
    ScmObject memsave;             /* string */
    ScmObject gcsave;              /* vector */
    WIND *firstwind, *lastwind;
    int tailcall;
    unsigned delta;
#ifdef GENERATIONAL_GC
    int reloc;
#endif
    jmp_buf j;
    int size;
    unsigned long intrlevel;
    char stack[1];    /* must be word aligned */
};
/*
// tbrv
*/
/**
 * @nodoc
 */

struct S_Promise {
    ScmObject env;
    ScmObject thunk;
    int done;
};

/*
// tbrv
*/
/**
 * @nodoc
 */
struct S_Port {
    ScmObject name;    /* string */
    short flags;
    char unread;
    int ptr;
    FILE *file;
    unsigned lno;
    int (*closefun) P_((FILE*));
};
#define P_OPEN    1 /* flags */
#define P_INPUT   2
#define P_STRING  4
#define P_UNREAD  8
#define P_BIDIR  16
#define P_STDIO  32
#define P_BINARY 64
#define P_ERROR 128 /* This port is being used in error reporting.  Recursion stop. */

#define IS_INPUT(port)   (PORT(port)->flags & (P_INPUT|P_BIDIR))
#define IS_OUTPUT(port) ((PORT(port)->flags & (P_INPUT|P_BIDIR)) != P_INPUT)
/**
 * @nodoc
 */
struct S_Autoload {
    ScmObject files;
    ScmObject env;
};
/**
 * @nodoc
 */
struct S_Macro {
    ScmObject body;
    int min_args, max_args;
    ScmObject name;
};
/**
 * @nodoc
 * "size" is called with one object and returns the size of the object.
 *    If "size" is NOFUNC, then "const_size" is taken instead.
 * "eqv" and "equal" are called with two objects and return 0 or 1.
 *    NOFUNC may be passed instead (then eqv and equal always return #f).
 * "print" is called with an object, a port, a flag indicating whether
 *    the object is to be printed "raw" (a la display), the print-depth,
 *    and the print-length.
 * "visit" is called with a pointer to an object and a function.
 *    For each component of the object, the function must be called with
 *    a pointer to the component.  NOFUNC may be supplied.
 */
typedef struct {
    int haspointer;
    const char *name;
    int (*size) P_((ScmObject));
    int const_size;
    int (*eqv) P_((ScmObject, ScmObject));
    int (*equal) P_((ScmObject, ScmObject));
    int (*print) P_((ScmObject, ScmObject, int, int, int));
    int (*visit) P_((ScmObject*, int (*)(ScmObject*)));
} TYPEDESCR;

#ifdef ELK_USE_PROTOTYPES
#  define NOFUNC 0
#else
#  define NOFUNC ((int (*)())0)
#endif

/*
// tbrv
*/
/**
 * @nodoc
 */
typedef struct sym {
    struct sym *next;
    char *name;
    unsigned long value;
} SYM;

/*
// tbrv
*/
/**
 * @nodoc
 */
typedef struct {
    SYM *first;
    char *strings;
} SYMTAB;

/*
// tbrv
*/
/**
 * @nodoc
 */
typedef struct {
    char *name;
    int type;
} SYMPREFIX;

#define PR_EXTENSION     0   /* Elk extension initializers/finalizers */
#define PR_CONSTRUCTOR   1   /* C++ static constructors/destructors */


/* PFO, GENERIC, and MATCHFUN exist for backwards compatibility
 */
/*
// tbrv
*/
/**
 * @nodoc
 */
typedef ScmObject (*PFO) P_((ScmObject));
/*
// tbrv
*/
/**
 * @nodoc
 */
typedef int (*MATCHFUN) P_((ELLIPSIS));
#define GENERIC char*
/*
// tbrv
*/
/**
 * @nodoc
 */
typedef struct weak_node {
    struct weak_node *next;
    ScmObject obj;
    PFO term;
    GENERIC group;
    char flags;
} WEAK_NODE;

/* flags */
#define WK_LEADER 1

/*
// tbrv
*/
/**
 * @nodoc
 */
typedef struct {
    char *name;
    unsigned long val;
} SYMDESCR;


/* Function that can be registered as a reader by Define_Reader():
 */
/*
// tbrv
*/
/**
 * @nodoc
 */
typedef ScmObject (*READFUN) P_((ScmObject, int, int));
/** @} */
#endif
