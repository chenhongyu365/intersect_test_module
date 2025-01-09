/* $Id: tim.hxx,v 1.16 2002/01/30 17:29:08 skenny Exp $ */
/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/

#ifndef TIMH
#define TIMH

#ifdef D3_TIMES

// THE D-CUBED PERFORMANCE TIMING MECHANISMINTRODUCTThis is available by compiling all the sources with D3_TIMES dYou do NOT need to define D3_STANDALONE, D3_DEBUG or anythinThere is no extra baggage involved in using D3_TIMES, for eyou do not pick up any D3 stream or debug coThe system is based on the internal clock of the computer, so no point trying to analyse things which are typically much lea few clock ticks. So in practice this probably means "hundredths of a seconThe system will record time spent within each instrumented for block of code and output the time when it exits that funcblock of code. It will also maintain a cumulative total acrthe calls to that code which it will output when the image exwhen test harness "time" command is invoked (or the Scheme fd3:time is invoked). When the "time" command is issued, ouonly produced for those functions which have been called silast "time" command, and the cumulative time recorded is alsince the last "time" commaThis system is obviously designed not to impact performance tin its own right, but each timing call does typically involve aof heap allocations. However, so long as only "expensive" functiinstrumented the information it provides should be useful anaccurate.SIMPLE USThe system can be used very simply, just like the old D-Cubedsystem of which it is an extension. When using the macros itnecessary to wrap them in an "#ifdef D3_TIMES". No special acnecessary for recursive functions, they are handled correctFunctions or blocks of code to be timed may be instrumented wTIM_init( "function_name"which causes a timing statement for that single call to beupon exit, and a cumulative total to be maintained which is ouat image exit or invocation of the test harness "time" commthe Scheme function d3:time invokeTIM_init_no_acc( "function_name"a timing statement is outputted when this function or block is exited. No running total is accumulated, howevTIM_init_output( "function_name", 0here NO timing statement is issued when this call is exited, ha cumulative total IS maintained as usual. (Replacing the 0 wis identical to the basic "TIM_initThe only real difference from the old system is that "TIM_ounot necessary, as output happens when the TIM_init goes out ofTIM_out() may be used to cause the output to happen earlytimer will only issue one timing statement, successive cTIM_out() have no effect.RUNTIME CONTROL OF THE TIMING MECHANThe option "d3_times" can be used to control the behaviourmechanism at runtime. If set to 0, the timing mechanism is scompletely. If set to 1, only the summary statistics are through use of the test harness time command, the Scheme fd3:time, or at image exit. If set to 2, the timings foinstrumented call are output as they happThe default setting of the option is 0, unless other D-Cubed are included (D3_DEBUG or D3_STANDALONE) when the default is 2.MAKING TIMERS AVAILABLE TO OTHIf the algorithm you are instrumenting is relatively low levlots of other algorithms use it, it may be helpful to make thepublicly available, so that people can measure how long tspending in *your* algorithm on behalf of *their* algoritexample, you might wish to know how much time SSI is spendingas distinct from how much time you are spending in CSI as during a boolean operatiIn this case you will have to make a "handle" for your tim"handle" - an instance of the TIMER_HANDLE class - is thething that you export to other algorithms by making it avariable. This is perhaps not ideal, but there aren't too maof getting hold of it elsewhere without potentially signperformance overheads - hardly what we want! So you might add file (and here you need the ifdef) something li#ifdef DTIMER_HANDLE my_function_TIMER_#enthen, instead of using the TIM_init macro, use the followiTIM_init_handle( "my_function", &my_function_TIMER_HANDLEand it should all be business as usual. You will need to declaration of your handle into a header file somewhere to others easy access, look at intersct/kernint/timers.hxxexample. For an example of this being done you could intersct/kernint/d3_ssi/ssi_intr.cxx . How someone else woyour timer is covered later.MORE ADVANCED USAGE - EXPLICIT USE OF TIMYou can explicitly make your own timers - instancesTIMING_DATA class - and use them in your code. You will "#ifdef D3_TIMES" such code appropriately. For example, yolike to set a timer running and at various intervals obtelapsed time from it, maybe resetting it occasionally as you TIMING_DATA timer( "func", 0 );	// now it's ...do somtdouble elapsed_time = timer.elapsed_sec// You could call timer.stop() here - it's otimer.start();	// resets the timer ...do some double more_elapsed_time = timer.elapsed_seceNote the initial "0" passed to the timer constructor, which inthat no timing statement is to be output when the "stop()" fis called, or the timer goes out of scoRULE 1: TIMING_DATA objects should have local or function scoBecause a TIMING_DATA object always has local scope, itrecognise recursion. So to do this correctly we have a "handle- the TIMER_HANDLE - which is a global or static variable whung onto the timer itself (this is what TIM_init_no_acc doestatic TIMER_HANDLE TIMING_DATA timer( "func", 1, &ha...now recursion will be recognised correctly.RULE 2: the TIMER_HANDLE object should always have static orscoIf you know that code is non-recursive then there's no provide a "handle", otherwise best policy would probably be alsupply one (as the TIM macros do). If you forget, the conseare not dire - timing statements for recursive calls will beno different from top-level ones, so you won't be able to teapaNote, however, that the examples above making explicit TIMINdo NOT accumulate any times. For that we need to kno"buckets".MORE ADVANCED USAGE - BUCKTo accumulate times from a timer, we have to attach a "buckinstance of the TIMER_BUCKET class) to it, so that the timer its results in. Again, because the TIMING_DATA only ever hascope we actually attach buckets to the timer's handA bucket outputs its accumulated times when it is destroyed. Icircumstances this meaRULE 3: TIMER_BUCKETs should have static or global sco(Actually, if you know what you are doing you may wish to their scope explicity - for example, you might wish to acctimes within one function for calls to another, and always ouaccumulated time when the first function exitThe same bucket can be added to several different timers. Thiyou can, for example, create a "miscellaneous" bucket for fcalls you are not interested in seeing separately. To do thwould create a bucket with, say, global scope (or file scopethe references will be in the same filTIMER_BUCKET misc_bucket( "miscellaneous_functions"and then you could instrument the start of each function wiTIM_init_bucket_output( "func", &misc_bucket, 0This will accumulate all the times in the same bucket, which output when the image quits (or the "time" command used), bissue NO per-call timing statements (that's what the "0" meansthat there's no problem if your functions call one anothbucket will not count any time spent more than once.
EVEN MORE ADVANCED - ADDING EXTRA BUCKIn the most simple circumstance - and this is what TIM_init domake a bucket along with the timer, and hang the bucket on theBelow is more-or-less what the TIM_init macro dostatic TIMER_BUCKET bucket( "bucket" );	// the name the bucketstatic TIMER_HANDLE TIMER_ADD_BUCKET add_bucket( &handle, &bucket );	// hang bucket oTIMING_DATA timer( "func", 1, &ha...now off we go and do somethingBuckets are attached to timers by the TIMER_ADD_BUCKET class. actually creating an object with local scope which performs tThe reason for doing it this way is that the bucket gets unawhen the TIMER_ADD_BUCKET goes out of scoRULE 4: TIMER_ADD_BUCKET should always have local scope. Alshould make it BEFORE you make the TIMING_DATA itself, or the will be incorreMore usefully, here's how we attach an additional bucket to else's timer. Suppose we have either declared, or included a file with this declaratiextern TIMER_HANDLE someone_else_TIMER_HANDthen, within an "#ifdef D3_TIMES" we could wristatic TIMER_BUCKET my_bucket( "my_calls_to_someone_eTIMER_ADD_BUCKET my_add_bucket( &someone_else_TIMER_HANDLE, &my_bu...stuff which calls "someone_else"and we will get, in addition to anything else, a cumulativtime for all the calls to "someone_else" when called from withblock of coAny number of buckets can be attached to pretty much any nutimers. Buckets are sufficiently smart that time will ncounted twice (or more). For example, if you rig up a buaccumulate time spent in CSI and SSI, time spent in CSI on beSSI will not be counted twice. It is only the first timer thatrunning with a particular bucket attached that will be allowedits time in at the eFor an example, look in blend/kernbool/capping/capping.cxx .FINAL WORDS AND CAUTIAs usual there's plenty of rope here to hang yourself. But if intended it seems to work well, and if programmed carefully incode can yield useful statistics for performance analysis executing the progrIf anyone has any requests for fixes, modifications, enhancemenplease submit thDAP 23-Oct-97.

// VPL 18June2001: moved the implementation classes out of D3_TIMES macro definition.

// The basic macros for "simple use". We can add more if the need
// arises.

// Automatically define a timer and bucket to go togther. The timer
// issues timing statements if output is non-zero. The bucket will
// output a cumulative time at image exit, or when
// TIM_output_timer_buckets is invoked (e.g. by the test harness "time"
// command.

#    define TIM_init_output(fn, output)                   \
        LOCAL_VAR TIMER_BUCKET _BUCKET(fn);               \
        LOCAL_VAR TIMER_HANDLE _HANDLE;                   \
        TIMER_ADD_BUCKET _ADD_BUCKET(&_HANDLE, &_BUCKET); \
        TIMING_DATA _DATA(fn, output, &_HANDLE)

// Automatically define a timer and bucket, both of which output in the
// normal manner.

#    define TIM_init(fn) TIM_init_output(fn, 1)

// Automatically define a timer but which does no accumulation.

#    define TIM_init_no_acc(fn)         \
        LOCAL_VAR TIMER_HANDLE _HANDLE; \
        TIMING_DATA _DATA(fn, 1, &_HANDLE)

// Automatically define a bucket and timer to accumulate times for the
// given handle. You would use this if you have defined the handle
// externally so that other algorithms can reference it.

#    define TIM_init_handle_output(fn, handle_ptr, output)  \
        LOCAL_VAR TIMER_BUCKET _BUCKET(fn);                 \
        TIMER_ADD_BUCKET _ADD_BUCKET(handle_ptr, &_BUCKET); \
        TIMING_DATA _DATA(fn, output, handle_ptr)

// Automatically define a timer which uses the given handle which
// outputs in the normal manner.

#    define TIM_init_handle(fn, handle_ptr) TIM_init_handle_output(fn, handle_ptr, 1)

// Automatically define a timer to put its results in this bucket. You
// would use this if you want several different functions all to
// accumulate a combined total. The timer will issue timing statements
// per-call if output is non-zero.

#    define TIM_init_bucket_output(fn, bucket_ptr, output)  \
        LOCAL_VAR TIMER_HANDLE _HANDLE;                     \
        TIMER_ADD_BUCKET _ADD_BUCKET(&_HANDLE, bucket_ptr); \
        TIMING_DATA _DATA(fn, output, &_HANDLE)

// Automatically create a timer to dump its results in the given bucket,
// and *do* produce timing statements for each call.

#    define TIM_init_bucket(fn, ptr) TIM_init_bucket_output(fn, ptr, 1)

#    define TIM_out() \
        { _DATA.stop(); }

#else  // D3_TIMES

#    define TIM_init(fn)

#    define TIM_init_output(fn, output)

#    define TIM_init_no_acc(fn)

#    define TIM_init_handle(fn, handle_ptr)

#    define TIM_init_handle_output(fn, handle_ptr, output)

#    define TIM_init_bucket(fn, bucket_ptr)

#    define TIM_init_bucket_output(fn, bucket_ptr, output)

#    define TIM_out()

#endif  // D3_TIMES

// VPL 18June2001: moved the implementation classes out of D3_TIMES macro definition.

#include <stdlib.h>
#include <string.h>

#include "base.hxx"  // to make sure we have ACIS_OBJECT base class
#include "dcl_kern.h"
#include "debugmsc.hxx"  // for D3 macros
#ifndef _WINDOWS

// STIPORT TAC macintosh doesn't have these headers
#    if !defined(mac) || defined(MacX)
#        include <sys/times.h>
#        include <sys/types.h>
#        ifndef MacX
#            include <malloc.h>
#        endif
#    else
#        include <extras.h>  // for strdup
#    endif

#else
#    include <time.h>
#endif

// Now the implementation of the classes themselves.

// First we need to be able to create arbitrary lists of buckets, as
// pretty much any bucket can be attached to any timer.

class TIMER_BUCKET;

class DECL_KERN TIMER_BUCKET_LIST : public ACIS_OBJECT {
  public:
    TIMER_BUCKET_LIST(TIMER_BUCKET* b, TIMER_BUCKET_LIST* n = NULL): bucket(b), next(n) {}
    TIMER_BUCKET* bucket;
    TIMER_BUCKET_LIST* next;
};

// This class maintains accumulated times for all calls to any timers
// (TIMING_DATAs) to which it has been attached. We also maintain a
// global list of all the existing buckets so that
// TIM_output_timer_buckets() can zip through them all and print the
// statistics.

class DECL_KERN TIMER_BUCKET : public ACIS_OBJECT {
    // The name which will be printed ahead of "accumulated times".

    char* _name;

    // User time and system time accumulate here.

    double _user_time, _sys_time;

    // Number of calls to the timer which have been made. If this is 0
    // we won't bother outputting anything.

    int _ncalls;

    // The number of running timers which want to put their time into
    // this bucket will be kept here. That's because only the first
    // of those timers started will actually be allowed to do so, to
    // stop us counting double (or worse). This gets incremented each
    // time a timer with an interest in this bucket starts, and
    // decremented when it stops.

    int _active;

    // To main the global list. Doubly-linked so that we can easily
    // extract ourselves when we are destroyed.

    TIMER_BUCKET *_prev, *_next;

  public:
    // Constructor, given the name.

    TIMER_BUCKET(char* n);

    ~TIMER_BUCKET();

    // Next in the global list of all existing buckets.

    TIMER_BUCKET* next() const { return _next; }

    char* name() { return _name; }

    // VPL 19June2001: added functions to access user time & system time.
    double user_time() const { return _user_time; }
    double system_time() const { return _sys_time; }

    // Print the accumulated time.

    void output();

    friend class TIMING_DATA;
};

// The "handle" class. Handles are made for TIMING_DATAs, and any
// buckets can then be hung on the handle. The handle also allows
// recursion to be handled correctly as it should not have local scope.

class DECL_KERN TIMER_HANDLE : public ACIS_OBJECT {
    // The depth of any recursive call to a timer.

    int _depth;

    // The list of buckets the timer is interested in.

    TIMER_BUCKET_LIST* _buckets;

  public:
    TIMER_HANDLE(): _depth(0), _buckets(NULL) {}

    ~TIMER_HANDLE() {}

    friend class TIMER_ADD_BUCKET;
    friend class TIMING_DATA;
};

// This is the TIMING_DATA class which represents a "timer". When it is
// constructed it starts running. It may be explicitly stopped, and even
// re-started. When it is stopped it looks for any attached buckets into
// which it will dump its times so as to accumulate running totals.

class DECL_KERN TIMING_DATA : public ACIS_OBJECT {
    // The name to be printed ahead of "timings".

    char* _name;

    // Whether the timer is running.

    int _running;

    // Whether timing statements are to be issued by this timer.

    int _output;

    // The moment at which we started.

#ifndef _WINDOWS
#    if defined(mac) && !defined(MacX)
    unsigned long initial_time;
#    else
    struct tms initial_times;
#    endif
#else
    clock_t initial_time;
#endif

    // The "handle". This is the static or global data structure where
    // buckets actually get attached. Being static/global, it also
    // allows us to handle recursion properly.

    TIMER_HANDLE* _handle;

  public:
    // Constructor, given the name, whether we want this timer to
    // generate per-call timings or not, and an associated handle.

    TIMING_DATA(char* n, int oput = 1, TIMER_HANDLE* h = NULL);

    ~TIMING_DATA();

    char* name() {
        return _name;
    }

    // Change the timer's name. Not usually needed, except for
    // marginally nefarious purposes.

    void set_name(char const* new_name);

    // Re-start the timer. If not running (i.e. already been stopped) we
    // are restarted. If already running the time is re-zeroed, so any
    // time between the original start and re-start is "lost".

    void start();

    // Stop the timer. Also outputs a timing statement if output is
    // requested.

    void stop();

    // Return the number of elapsed seconds since the timer was started.

    double elapsed_seconds();
};

// A class of which we make an instance in order to tell the given timer
// that it should be accumulating its time in the given bucket. We do
// this with a class object (instead of an obvious function call) so as
// to undo the effect automatically when we go out of scope.

class DECL_KERN TIMER_ADD_BUCKET : public ACIS_OBJECT {
    // The timer (referenced via its handle) to which we have added a bucket.

    TIMER_HANDLE* _handle;

  public:
    // Add bucket to timer (actually its handle). A timer can have any
    // number of buckets. Even if you accidentally repeat some it
    // shouldn't matter.
    // VPL 19June2001: added level SPAparameter. this controls whether or not the bucket will be added to timer,
    // based on the current setting of the d3_times option. default value of -1 will always add the timer.

    TIMER_ADD_BUCKET(TIMER_HANDLE* handle, TIMER_BUCKET* bucket, int iLevel = -1);

    // Destructor which automatically unravels what we did.

    ~TIMER_ADD_BUCKET();
};

// Function to output and reset all the timing buckets in existence.
// This is what the test harness "time" command calls, though in
// principle anyone else could too.
// this function is implemented only in the D3_TIMES version.

void DECL_KERN TIM_output_timer_buckets();

// VPL 19June2001: new function for timing data output to file, in customizable format.
// Function to ouput all the timing data from current bucket list. the data will be
// written out into a file (with specified name). the format for the data is also taken as
// argument. this format controls which buckets will be accessed (filter like behaviour).

void DECL_KERN TIM_log_data(const char* filename, const char* format);

#endif
