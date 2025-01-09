/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/

#ifndef MMGR_DBG_HXX
#define MMGR_DBG_HXX

#ifdef mac
#include <time.h>
#endif

#include <sys/timeb.h>
#include "base.hxx"
#include "mmgr.hxx"
#include "mutex.hxx"

// struct storing mismatch info
struct mmgr_mismatch_block 
{
	mmgr_mismatch_block* next = NULL;
	const char* alloc_file;
	AcisMemCall alloc_call;
	AcisMemCall dealloc_call;
	size_t alloc_num;
	unsigned int alloc_line;
};

struct mmgr_audit_block {
	
	mmgr_audit_block * next;
	void * alloc_ptr;
	const char * alloc_file;
	size_t alloc_size;
	size_t alloc_num;
	AcisMemType alloc_type;
	AcisMemCall alloc_call;
	unsigned int alloc_line;

#ifdef THREAD_SAFE_ACIS
	int alloc_thread;
	int delete_thread;
#endif
};


// 24 bits (4096 entries) are used to hash the allocated
// pointers when auditleaks in enabled.
LOCAL_CONST int hash_size = 4096;
#define HASH_FUNCTION(p)	(((intptr_t)p & 0x000fff00) >> 8)


struct mmgr_statistics {

	size_t high_bytes;
	size_t high_alloc_call;
	size_t alloc_bytes;
	size_t alloc_calls;
	size_t free_bytes;
	size_t free_calls;
	size_t size_array[257];

	char ** alloc_file_names;
	int alloc_file_count;

	char audit_file[256];

	size_t double_deletes;
	size_t mismatched_callers;
	size_t mismatched_sizes;
	size_t pre_alloc_calls;
	size_t global_new_calls;
	size_t global_delete_calls;
	size_t range_begin, range_end;
	struct timeb start_time;
	mmgr_audit_block * hash_array[hash_size];
	FILE * mmgrfile;

	mutex_resource mmgr_statistics_mutex;

	mmgr_mismatch_block* mismatch_block_start = NULL;
};


DECL_BASE mmgr_statistics * mmgr_debug_stats();
DECL_BASE void mmgr_dump_range( size_t range_begin, size_t range_end );
DECL_BASE void mmgr_dump_info( void* alloc_ptr );

#endif 
// MMGR_DBG_HXX
