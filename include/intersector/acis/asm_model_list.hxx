/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/

// This class implements a variable-length list for asm_model objects.  The list
// is meant to look and feel much like the ENTITY_LIST class.  But in addition
// to the standard list functionality, this class can also act as a "holding"
// object and/or as a counted list.
//
// When "holding" is turned on, the list "holds" the objects in the sense that
// entries' use counts are adjusted as they are added to and deleted from the
// list.  The use counting mechanism ensures that cleanup operations do not
// destroy the objects being held.
//
// In counted list mode, the entry count keeps track of the number of times an
// entry has been added minus the number of times the same entry has been
// removed.  The entry count must be zero in order for the entry to actually
// be taken off list, i.e. the number of adds must equal the number of deletes.
// When the counted list mode is turned off, the first call to remove an entry
// from the list always causes that entry to be taken off the list immediately.
//
// The asm_model_list class is a wrapper for the asm_model_list_eng class, 
// which implements the core functionality.

#ifndef ASM_MODEL_LIST_HXX
#define ASM_MODEL_LIST_HXX

#include "acis.hxx"
#include "dcl_asm.h"
#include "asm_list_opts.hxx"
#include "spa_null_base.hxx"
/**
* @file asm_model_list.hxx
 * @CAA2Level L1
 * @CAA2Usage U1
 * \addtogroup ACISASSEMBLIES
 *
 * @{
 */

class asm_model;
class asm_model_list_eng;

/**
 * Implements a variable length list of assembly models with set and index behavior and optional holding and counting mechanisms.
 * <br>
 * <b>Role:</b> This class is a list object for <tt>asm_model</tt> objects that is intended to have the look and feel
 * of the ENTITY_LIST class.  But the functionality has been extended to include holding and counting mechanisms.
 * <br><br>
 * If the counting mechanism is turned on, then the list keeps track of the entry count, i.e. the number of times the same entry
 * has been added minus the number of times it has been removed.  The entry is deleted from the list
 * only if the entry count reaches zero.
 * <br>
 * When the holding state of the list is set to <tt>ASM_HOLD</tt>, the list increments the use count of each entry.
 * This ensures that "held" entries are not deleted when the models are cleaned up.  For details on cleaning up models,
 * please refer to the documentation on the <tt>asm_model_mgr</tt> object.
 * <br>
 * The holding and counting mechanisms are specified when the <tt>asm_model_list</tt> object is constructed.
 * Additionally, the holding state can be changed using <tt>asm_model_list::set_hold_state</tt>.
 * <br><br>
 * Models are added to the end of the list using <tt>asm_model_list::add</tt> which ensures that the models are not
 * already in the list (i.e. set behavior).  The <tt>asm_model_list::remove</tt> methods take entries off the list, 
 * but a tombstone remains at the position of the former entries.  The <tt>asm_model_list::add_notify</tt> and 
 * <tt>asm_model_list::remove_notify</tt> methods notify the caller when the list is actually modified.
 * <br>
 * The position of current entries can be determined using <tt>asm_model_list::lookup</tt>, and the entry at a specified position
 * may be accessed using the overloaded <tt>"[ ]"</tt> index operator.  The number of entries in the list is returned by
 * <tt>asm_model_list::count</tt> (includes tombstones) and <tt>asm_model_list::iteration_count</tt> (excludes tombstones).
 * The preferred way of accessing the data items is through <tt>asm_model_list::init</tt> which rewinds the list
 * and <tt>asm_model_list::next</tt> which returns the next undeleted item.  The <tt>asm_model_list::first</tt> method
 * rewinds the list and returns the first non-deleted entry.
 * <br><br>
 * The current implementation uses hashing so that <tt>asm_model_list::lookup</tt> is fast;
 * it is also efficient for very short lists and for repeated lookups of the same assembly model.
 * <br><br>
 * When a group of assembly models must be returned, and the number of arguments is not known in
 * advance, the system returns the arguments as an <tt>asm_model_list</tt>. For instance, when the routine
 * <tt>api_asm_get_models</tt> is used to find every model in the model tree beow the specified assembly, the models found
 * are put into an <tt>asm_model_list</tt> that is returned.
 * <br>
 * <pre>
 * asm_model_list my_models;
 * api_asm_get_models( assembly, my_models );
 * for ( asm_model* model = my_models.first(); model != NULL; model = my_models.next() )
 * {
 * .
 * .
 * .
 *
 * }
 * </pre>
 * <br>
 * <b>Note: </b>The general method for retrieving the number of entries in an <tt>asm_model_list</tt> is iteration_count().
 * This function prevents having the list iterators skip deleted entries. Else some routines encounter arrays
 * with uninitialized entries and unexpected results may occur.
 * <br>
 * If the count method is used to determine the number of entries in an <tt>asm_model_list</tt> (including tombstones),
 * then individual entries can be accessed with the index <tt>operator [ ]</tt>.
 * <br>
 * <b>Note: </b> The index <tt>operator [ ]</tt> does not ignore "removed" entries).
 * <br> <br>
 * Be sure to check the returned pointer
 * for the constant LIST_ENTRY_DELETED (-1), which indicates a tombstone (removed entry) at that index.
 * <br><br>
 * The <tt>asm_model_list</tt> class is a variable length associative array of <tt>asm_model</tt> pointers. When using
 * the subscript operator, a cast is required to change the <tt>asm_model</tt> pointer into the correct type.
 * Many ACIS internal algorithms use <tt>asm_model_list</tt> including the save, and restore algorithms.
 * <tt>asm_model_list</tt> is also useful in <tt>ACIS</tt> components and applications.
 * <br><br>
 * @see asm_model, asm_model_mgr
 */
class DECL_ASM asm_model_list : public ACIS_OBJECT {

	asm_model_list_eng* list_ptr;		// list engine
	asm_model_list_eng* get_list();		// for internal use, instantiates the engine if not already present

	asm_list_options list_opts;

public:

 /**
  * Default constructor, creating an <tt>asm_model_list</tt>.
  * <br><br>
  * <b>Role:</b> By default, the hold state is set to <tt>ASM_NO_HOLD</tt> and the counting mechanism is turned off.
  * <br><br>
  * @see asm_hold_state
  */
	asm_model_list();

 /**
  * C++ constructor, creating an <tt>asm_model_list</tt> with the specified holding behavior.
  * <br><br>
  * <b>Role:</b> By default, the counting mechanism is turned off.
  * <br><br>
  * @param state
  * hold state.
  * <br><br>
  * @see asm_hold_state
  */
	asm_model_list( asm_hold_state state );

 /**
  * C++ constructor, creating an <tt>asm_model_list</tt> with the behavior specified by the <tt>asm_list_options</tt> object.
  * <br><br>
  * @param list_opts
  * pointer to assembly list options.
  * <br><br>
  * @see asm_list_options
  */
	asm_model_list( asm_list_options* list_opts );

 /**
  * C++ destructor, deleting an <tt>asm_model_list</tt>.
  * <br><br>
  * <b>Role:</b> If holding is turned on, the use counts of all entries are decremented.
  */
	~asm_model_list();

 /**
  * C++ constructor, creating an <tt>asm_model_list</tt> from an array with the behavior specified by the <tt>asm_list_options</tt> object. 
  * <br><br>
  * <b>Role:</b> If the check flag is set to <tt>FALSE</tt>, the elements of the array are not checked to ensure that the
  * entries of the list are unique.
  * <br><br>
  * @param count
  * size of array
  * @param model_array
  * array of assembly models
  * @param list_opts
  * pointer to assembly list options.
  * @param check
  * check unique.
  * @see asm_list_options
  */
	asm_model_list( int count, asm_model** model_array, asm_list_options* list_opts = NULL, logical check = TRUE );

 /**
  * C++ copy constructor, which copies the whole list (complete with deleted entries, if any), so that the indices in the copy match those in the original.
  * <br><br>
  * <b>Role:</b> If holding is turned on, the use count of all active entries is incremented.  For counted lists, the entry count
  * for each entry is also copied.
  * <br><br>
  * @param list_copy
  * list to copy.
  */
	asm_model_list( const asm_model_list& list_copy);

 /**
  * <tt>Assignment</tt> operator performs a full copy of the list, complete with tombstones for deleted entries so that the indices are the same.
  * <br><br>
  * <b>Role:</b> If holding is turned on, the use count of all active entries of the original list is decremented and
  * the use count of all entries of the copied list is incremented.  For counted lists, the entry count
  * for each entry is also copied.
  * <br><br>
  * @param asm_model_list
  * asm_model list.
  */
	asm_model_list& operator=( const asm_model_list& asm_model_list);

 /**
  * Sets the hold state of the model list.
  * <br><br>
  * <b>Role:</b> If holding is turned on, the use count of all active entries of the list is incremented.
  * <br><br>
  * @param state
  * hold state.
  * @see asm_hold_state
  */
	void set_hold_state( asm_hold_state state );

 /**
  * Clear all entries from the list and reset indexes and counters for reuse.
  * <br><br>
  * <b>Role:</b> If holding is turned on, the use count of all active entries of the list is decremented before
  * being removed from the list.  The holding and counting behavior of the list remains unchanged.
  * <br><br>
  */
	void clear();

 /**
  * Adds an assembly model to the list and returns its index number.
  * <br><br>
  * <b>Role:</b> If the check flag is set to <tt>FALSE</tt>, then the lookup that assures a unique entry is skipped.
  * If holding is turned on, the model's use count is incremented the first time it is added to the list.
  * If the counting mechanism is turned on, the entry count for the added entry is incremented.
  * <br><br>
  * @param model
  * asm_model to add.
  * @param check
  * check unique.
  */
	int add( asm_model* model, logical check = TRUE );

 /**
  * Adds an assembly model to the list, returns its index number and notifies if the model is new.
  * <br><br>
  * <b>Role:  </b>Same as <tt>asm_model_list::add</tt>, but notifies the caller if the model is added
  * to the list for the first time and returns the entry count for the added entry.
  * <br><br>
  * @param model
  * asm_model to add.
  * @param was_added
  * notify if new on list.
  * @param list_count
  * number of adds minus removes
  */
	int add_notify( asm_model* model, logical& was_added, int& list_count );

 /**
  * Adds the models of an <tt>asm_model_list</tt> to this <tt>asm_model_list</tt>.
  * <br><br>
  * <b>Role:</b>Same as <tt>asm_model_list::add</tt> for all models in the input list.
  * <br><br>
  * @param asm_model_list
  * asm_model list.
  * @param check
  * check unique.
  */
	void add( const asm_model_list& model_list, logical check = TRUE );

 /**
  * Lookup the specified asmsembly model in the list and return its index.
  * <br><br>
  * @param model
  * entry to lookup
  */
	int lookup( const asm_model* model ) const;

 /**
  * Remove the specified entry from the list and return its index.
  * <br><br>
  * <b>Role:</b> If the counting mechanism is turned on and entry count of the specified entry is greater than one, 
  * then that count is decremented and the entry is not actually deleted from the list.  The entry is deleted from the list
  * only when the entry count reaches zero.  When the entry is deleted from the list, a tombstone is left in its place.
  * The count of the list is not reduced, the iteration_count, however, is.  If holding is turned on, the model's use count
  * is decremented when the object is deleted from the list.
  * <br><br>
  * @param model
  * entry to remove
  */
	int remove( const asm_model* model );

 /**
  * Remove the specified entry from the list and return its index.
  * <br><br>
  * <b>Role:</b> Same as <tt>asm_model_list::remove</tt>, but the caller is notified if the entry is actually deleted
  * the list and the entry count of the removed entry is returned.
  * <br><br>
  * @param model
  * entry to remove
  * @param was_removed
  * notify if deleted from list.
  * @param list_count
  * number of adds minus removes
  */
	int remove_notify( const asm_model* model, logical& was_removed, int& list_count );

 /**
  * Removes asm models in the given list from the list; however, it does not free space.
  * <br><br>
  * <b>Role:</b> Same as <tt>asm_model_list::remove</tt> for a list of models.
  * <br><br>
  * @param model_list
  * asm_model list.
  */
	void remove( const asm_model_list& model_list );

 /**
  * Remove the entry at the specified index from the list and return its index.
  * <br><br>
  * <b>Role:</b> Same as <tt>asm_model_list::remove</tt>.
  * <br><br>
  * @param index
  * index of entry to remove.
  */
	int remove( int index );

 /**
  * Returns the number of entries in the list including the deleted ones (tombstones).
  */
	int count() const;

 /**
  * Returns the number of live entries in the list not including deleted entries.
  */
	int iteration_count() const;

 /**
  * Returns the number of times an entry has been added minus the number of times it has been removed.
  * <br><br>
  * <b>Role:</b> This method returns -1 if counting is turned off, the index corresponds to a deleted
  * entry or the index is out of range.
  * <br><br>
  * @param index
  * integer.
  */
	int entry_count( int index );

 /**
  * Returns the number of times an entry has been added minus the number of times it has been removed.
  * <br><br>
  * <b>Role:</b> This method returns -1 if counting is turned off or the list member is not found.
  * <br><br>
  * @param list_member
  * assembly model.
  */
	int entry_count( const asm_model* list_member );

 /**
  * Returns the assembly model at the given index from the list.
  * <br><br>
  * <b>Role:</b> This method returns NULL if the given index is out of range,
  * or the constant LIST_ENTRY_DELETED if the indexed assembly model was removed from the list.
  * <br><br>
  * @param index
  * integer.
  */
	asm_model *operator[]( int index ) const;

 /**
  * Initializes the iterator, which is used by the next method, to the beginning of the list.
  */
	void init() const;

 /**
  * Returns the first undeleted (live) entry and updates the iterator correctly for the next method.
  */
	asm_model *first() const;

 /**
  * Returns the next undeleted (live) entry.
  */
	asm_model *next() const;

 /**
  * Returns the next non-deleted entry after the index given without affecting the member variables used by <tt>init</tt> and <tt>next</tt>.
  * <br><br>
  * <b>Role:</b> This allows clients to create iterators that can be multiply instantiated and which run
  * independently of each other. This is accomplished simply by giving the the user the appropriate
  * variables to save themselves.
  * <br><br>
  * @param index
  * integer.
  */
	asm_model *next_from( int& index );

 /**
  * Reverses the order of the assembly model list.
  * <br><br>
  * <b>Role:</b> If the compress flag is <tt>TRUE</tt>, tombstones associated with deleted models are removed.
  * <br><br>
  * @param compress
  *  remove deleted entries.
  */
	void reverse( logical compress = TRUE );

 /**
  * Gets an array of the assembly models in the list.
  * <br><br>
  * <b>Role:</b> The default returns an array that must be freed by using <tt>ACIS_DELETE [] STD_CAST</tt>
  * <br><br>
  * @param model_array
  * pointer of array to be used if provided.
  * @param array_count
  *  number of models in array.
  * @param tombstones
  *  add tombstones to array.
  */
	asm_model** array( asm_model ** model_array = NULL,
					   int &array_count = SpaAcis::NullObj::get_int(),
					   logical tombstones = FALSE );

 /**
  * Returns the size in bytes of this class.
  * <br><br>
  * <b>Role:</b>  It does not include the size of the individual <tt>asm_models</tt> themselves.
  * <br><br>
  * @param countSelf
  * count self or not.
  */
	int byte_count( logical countSelf = TRUE ) const;

 /**
  * Sorts the list based upon the user-supplied comparison function.
  * <br><br>
  * <b>Role:</b>  Implements the runtime qsort function to sort the list and expects the input compare funcion
  * to have the same behavior as described for qsort. The return value should be less than zero if model1
  * is less than model2, greater than zero if model1 is greater than model2, and zero if they are the same.
  * Tombstones are removed bofore sorting and do not have to be considered by the compare function. 
  * The sorted list is obviously re-indexed, which may occur even when the list does not actually 
  * require sorting changes.
  * <br><br>
  * @param compare_func
  * comparison function
  */
	void sort( int (*compare_func)(const void* model1, const void* model2 ) );
};


 /** @} */
#endif /*ASM_MODEL_LIST_HXX */
