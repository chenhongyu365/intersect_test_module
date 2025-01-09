#ifndef CATCGMCheckAnomalyValueInfo_H
#define CATCGMCheckAnomalyValueInfo_H

// COPYRIGHT DASSAULT SYSTEMES 2015

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CATGMModelInterfaces.h"
#include "CATCGMValueClassImplHolder.h"
#include "CATUnicodeString.h"
#include "CATListOfDouble.h"

class CATCGMCheckAnomalyValueInfoImpl;
class CATLISTV(CATCGMCheckAnomalyValueInfo);

/**
 * Class representing an anomaly value info.
 *
 * <b>Role:</b>This class is designed with "value-class" semantics; it is intended to 
 * be owned and passed by value, rather than being allocated on the heap.
 * To minimize memory consumption, use these objects as locally as possible.  
 **/
class ExportedByCATGMModelInterfaces CATCGMCheckAnomalyValueInfo
{
public:

	/**
	* Copy constructor. 
	**/
	CATCGMCheckAnomalyValueInfo(CATCGMCheckAnomalyValueInfo const& iOther);

	/**
	* Assignment operator.
	**/
	CATCGMCheckAnomalyValueInfo& operator=(CATCGMCheckAnomalyValueInfo const& iOther); 

	/**
	* Destructor.
	*/
	~CATCGMCheckAnomalyValueInfo();

	/**
	* @nodoc
	* For internal use only
	*/
	CATBoolean operator==(CATCGMCheckAnomalyValueInfo const& iOther) const;

	/**
	* @nodoc
	* For internal use only
	*/
	CATBoolean operator!=(CATCGMCheckAnomalyValueInfo const& iOther) const;

	/**
	* Gets the description and values of the anomaly.
	* @param oValueDescription
	* The descriptions.
	* @param oValues
	* The values.
	**/
	void GetInfo(CATUnicodeString& oValueDescription, CATListOfDouble & oValues) const;

	/**
	* Gets the value info list from the sub-catalog.
	* @param oSubValueInfos
	* The list of value info from the sub-catalog.
	**/
	void GetSubValueInfos(CATLISTV(CATCGMCheckAnomalyValueInfo) &oSubValueInfos) const;


	/**
	* @nodoc
	* For internal use only
	*/
	CATCGMCheckAnomalyValueInfo(CATCGMCheckAnomalyValueInfoImpl* ipImpl);

private:
	DECLARE_USE_COUNTED_GET_IMPL_METHODS(CATCGMCheckAnomalyValueInfo);

protected:
	CATCGMValueClassImplHolder _implHolder;
	

};
#endif
