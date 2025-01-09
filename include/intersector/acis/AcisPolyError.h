// Error code definitions for module "spaacispoly/src"

#ifndef SPAACISPOLY_ACISPOLY_ERRMOD_INCLUDED
#define SPAACISPOLY_ACISPOLY_ERRMOD_INCLUDED

#include "errorbase.hxx"
#include "errmsg.hxx"

#include "importexport.h"
#ifdef __SPAAcisPoly
extern EXPORT_SYMBOL message_module spaacispoly_acispoly_errmod;

#else
extern IMPORT_SYMBOL message_module spaacispoly_acispoly_errmod;

#endif
#define ACISPOLY_NOT_SUPPORTED spaacispoly_acispoly_errmod.message_code(0)
#define ACISPOLY_INTERNAL_ERROR spaacispoly_acispoly_errmod.message_code(1)
#define ACISPOLY_MIX_NOT_SUPPORTED spaacispoly_acispoly_errmod.message_code(2)
#define NOT_ACISPOLY_BODY spaacispoly_acispoly_errmod.message_code(3)
#define BAD_ACISPOLY_BODY spaacispoly_acispoly_errmod.message_code(4)
#define ACISPOLY_ALGO_FAILED spaacispoly_acispoly_errmod.message_code(5)
#define ACISPOLY_UNAUTHORIZED spaacispoly_acispoly_errmod.message_code(6)
#define ACISPOLY_OPTION_NOT_SUPPORTED spaacispoly_acispoly_errmod.message_code(7)
#define ACISPOLY_BAD_INPUT spaacispoly_acispoly_errmod.message_code(8)
#define ACISPOLY_POLYBODY_FAILURE spaacispoly_acispoly_errmod.message_code(9)
#define ACISPOLY_POLYMESH_FAILURE spaacispoly_acispoly_errmod.message_code(10)
#define ACISPOLY_BAD_POLYMESH spaacispoly_acispoly_errmod.message_code(11)
#define ACISPOLY_OFFSET_OPENFACE spaacispoly_acispoly_errmod.message_code(12)
#define ACISPOLY_NO_SHALLOW_COPY spaacispoly_acispoly_errmod.message_code(13)
#define ACISPOLY_STD_EXCEPT spaacispoly_acispoly_errmod.message_code(14)
#define ACISPOLY_BOOL_NOT_SUPPORTED spaacispoly_acispoly_errmod.message_code(15)
#define ACISPOLY_NO_BACK_SAVE spaacispoly_acispoly_errmod.message_code(16)
#define ACISPOLY_MWT_SAG_ERR spaacispoly_acispoly_errmod.message_code(17)
#define ACISPOLY_MWT_STEP_ERR spaacispoly_acispoly_errmod.message_code(18)
#define ACISPOLY_MWT_INDEX_ERR spaacispoly_acispoly_errmod.message_code(19)
#define ACISPOLY_INPUT_NOT_SOLID_BODY spaacispoly_acispoly_errmod.message_code(20)
#define ACISPOLY_CANONIC_DETECT_FAILURE spaacispoly_acispoly_errmod.message_code(21)
#define ACISPOLY_OFST_LESS_OFST_DIST spaacispoly_acispoly_errmod.message_code(22)
#define ACISPOLY_OFST_EMPTY_RESULT spaacispoly_acispoly_errmod.message_code(23)
#define ACISPOLY_NO_SINGLE_SIDE_THICKENING spaacispoly_acispoly_errmod.message_code(24) 
#define ACISPOLY_OFST_TESS_LEVEL_CHANGED spaacispoly_acispoly_errmod.message_code(25)


#endif /* SPAACISPOLY_ACISPOLY_ERRMOD_INCLUDED */
