/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
//----------------------------------------------------------------------
// purpose---
//    A string class optimized for use as a reference SPAparameter.
//
// usage---
//    The intent is that a top level function allocates one of these
//    on the stack and passes it as a SPAparameter to other functions
//    that want to return string data.  The called functions can simply
//    use operator= to set the return value.  Storage is handled automatically
//    for both large and small strings.
//
//    Param_strings can also be allocated on the stack in many situations
//    where one works with strings of unknown size.  Small strings are
//    handled efficiently in a local buffer.  Larger strings take advantage
//    of automatic storage managment.
//
//----------------------------------------------------------------------
/**
 * @file parm_str.hxx
 * @CAA2Level L1
 * @CAA2Usage U1
 * \addtogroup SCMAPI
 * \Declared at <parm_str.hxx>
 * @{
 */

#ifndef parm_str_hxx
#define parm_str_hxx

#include "scheme.hxx" // for ScmObject // for ScmObject

/*
// tbrv
*/
/**
 * @nodoc
 */
const char* get_Scm_String(ScmObject s );

/**
 * References parameters.
 * <br>
 * <b>Role:</b> This class is a string class that is optimized for use as a
 * reference parameter.
 * <br><br>
 * A top level method allocates a <tt>param_string</tt> on the stack and passes it as a
 * parameter to other functions with which to return string data. The called
 * methods use <tt>operator=</tt> to set the return value. Storage is handled automatically
 * for both large and small string.
 * <br><br>
 * Parameter strings can also be allocated on the stack in many situations where
 * one works with strings of unknown size. Small strings are handled efficiently
 * in a local buffer. Larger strings take advantage of automatic storage management.
 */
class param_string: public ACIS_OBJECT
{
        char  buffer[128];
        char* bufp;
		size_t buffer_size;
		size_t data_size;
		logical null;	// Was set to a null string

        // The copy constructor is private so it is hard to pass these
        // things other than by reference.  Pass by value would be very
        // inefficient and that violates the intent of this class.
/*
// tbrv
*/
/**
 * @nodoc
 */
        param_string( const param_string& );

		// get_Scm_String needs to set the length independent of the
		// null string terminator.  Thus, we make an exception to the normal
		// access restrictions so it can call set( const char* unsigned)
/*
// tbrv
*/
/**
 * @nodoc
 */
		friend
			const char* get_Scm_String(ScmObject s );

/*
// tbrv
*/
/**
 * @nodoc
 */
        void set( const char*, unsigned len); // len is as in strlen.
/*
// tbrv
*/
/**
 * @nodoc
 */
        void set( const char* );

		// Append data
/*
// tbrv
*/
/**
 * @nodoc
 */
		void append( const char*, size_t);

 public:

		// Create a new param_string with a default value of ""
/**
 * C++ allocation constructor requests memory for this object but does not populate it.
 */
        param_string();

		// Create a new param_string from a point to char
/**
 * C++ initialize constructor requests memory for this object and populates it with the data supplied as arguments.
 * <br><br>
 * @param cstr
 * character string.
 */
        param_string( const char* cstr);

		// Destroy a param_string and return any allocated storage
/**
 * C++ destructor, deleting a <tt>param_string</tt>.
 */
        ~param_string();

		// Set the string value from a pointer to char
/**
 * Sets the string value from a pointer to char.
 * <br><br>
 * @param pstr
 * pointer to character string.
 */
        param_string& operator= ( const char* pstr);

		// Set the string value from another param_string
/**
 * Sets the string value from a pointer to <tt>param_string</tt>.
 * <br><br>
 * @param pstr
 * pointer to parameter string.
 */
        param_string& operator= ( const param_string& pstr);

		// Convert a param_string to a pointer to immutable characters.
/**
 * Converts a <tt>param_string</tt> to a pointer to immutable characters.
 */
        operator const char*() const;

		// Compare to strings
/**
 * Determines if two parameter strings are equal.
 * <br><br>
 * @param pstr
 * pointer to parameter string.
 */
		int operator==(const param_string& pstr) const;

		// Get the length of the string
/**
 * Returns the length of the <tt>param_string</tt>.
 */
		size_t length() const { return data_size; }

		// See if the string is empty
/**
 * Returns <tt>FALSE</tt> if the <tt>param_string</tt> is empty - else, it returns <tt>TRUE</tt>.
 */
		int is_empty() const {return data_size == 0;}

		// Get the character at a SPAposition
/**
 * Returns the character at the given position.
 * <br><br>
 * @param pos
 * given position.
 */
		char operator[] (int pos) const;

		// Append data to the string
/**
 * Appends a character string to the <tt>param_string</tt>.
 * <br><br>
 * @param cstr
 * character string.
 */
		param_string& operator+=(char cstr);
/**
 * Appends the characters to which char points to the <tt>param_string</tt>.
 * <br><br>
 * @param pstr
 * pointer to the character string.
 */
		param_string& operator+=(const char* pstr);
/**
 * Appends the characters to which <tt>param_string</tt> points to the <tt>param_string</tt>.
 * <br><br>
 * @param pstr
 * pointer to the parameter string.
 */
		param_string& operator+=(const param_string& pstr);

		// Clear the string (does not free up buffer);
/**
 * Clears the <tt>param_string</tt>, but it does not free up the buffer.
 */
		void clear();
};
/** @} */
#endif
