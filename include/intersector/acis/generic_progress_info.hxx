/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/

#ifndef GENERIC_PROGRESS_INFO_HXX
#define GENERIC_PROGRESS_INFO_HXX

#include "spa_progress_info.hxx"
#include "mutex.hxx"

/**
 * @file generic_progress_info.hxx
 */

/**
* The class <tt>generic_progress_info</tt> provides a basic template for the progress info required
* for user-defined progress bars. A custom progress bar can be created by defining a new progress info
* type derived from this class.
* <br>
* <b>Role:</b> The class <tt>generic_progress_info</tt> provides all the functionality that would be
* needed for creating custom progress bars.
* <br><br>
**/
class DECL_BASE generic_progress_info : public SPA_progress_info
{
	double m_curr_percent;
	double m_increment_val;
	enum { Not_Started, Running, Ended, Interrupted } m_state;

	int m_display_percent, m_last_display_percent;

	const SPA_progress_info_type_id m_type_id;

	mutex_resource m_progress_info_mutex;
	
	void update();

public:
	generic_progress_info(SPA_progress_info_type_id type_id);
	~generic_progress_info();

	/**
	 * Initialize the progress bar.
	 */
	void start();

	/**
	* Set new value of the progress bar. Must be between 0 and 100.
	*/
	void set_percent(double new_percent);

	/**
	 * Increment the progress bar using the default increment.
	 */
	void increment();
	
	/**
	 * Increment the progress bar using the given increment.
	 */
	void increment(double increment_percent);
	
	/**
	 * Mark the end of the progress bar.
	 */
	void end();
	
	/**
	* Query if the progress bar has been interrupted by the user.
	*/
	bool interrupted();

	/**
	* Query if the progress bar has been initialized.
	*/
	bool initialized();

	/**
	 * Set the increment value for a default increment
	 * to the progress bar.
	 */
	void set_increment_val(double val);

	/**
	* Get the current percentage.
	*/
	int percentage() const override;

	/**
	* Get the progress bar type id.
	*/
	SPA_progress_info_type_id get_type() const override;

	/**
	* This implementation is thread safe, therefore this function returns TRUE.
	*/
	logical thread_safe() const override;
};

#endif
