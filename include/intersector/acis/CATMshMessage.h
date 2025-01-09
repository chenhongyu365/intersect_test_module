#ifndef CATMshMessage_H
#define CATMshMessage_H


//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2022
//=============================================================================
/**
 * @CAA2Level L0
 * @CAA2Usage U1
 */

//=============================================================================
//
// CATMshMessage :
//
// Object use to define and manage message during a meshing component session
//
//=============================================================================

#include "CATMshBase.h"
#include <string>
#include "ExportedByCATMshMesherCore.h"

class CATMshMessage;

#define CATMSH_MESSAGE_SEVERITY_INFO      0
#define CATMSH_MESSAGE_SEVERITY_WARNING   1
#define CATMSH_MESSAGE_SEVERITY_ERROR     2

#define CATMSH_MESSAGE_ORIGIN_NONE        0
#define CATMSH_MESSAGE_ORIGIN_CADSURF     1
#define CATMSH_MESSAGE_ORIGIN_CVM         2

/**
 * Type for a message callback function.
 * This is the type for the function which will be called by a meshing component
 * to send the user a message during a computation.
 * @param msg (in) : the message object
 * @param iUserData (in) : a user pointer.
 * @return
 *   An HRESULT.
 *   <br><b>Legal values</b>:
 *   <dl><dt>S_OK</dt><dd>The Compute is OK.
 *   <dt>E_FAIL</dt><dd>The Compute failed.
 *   </dl>
 */
typedef HRESULT(*CATMshMessageCB)(CATMshMessage *iMsg, void *iUserData);


/**
 * Object describing the structured message sent by a meshing
 * component to the caller.
 * <b>Role</b>: This classe provides all necessary informations about a
 * message.
 */
class ExportedByCATMshMesherCore CATMshMessage : public CATMshBase
{

public:
	
	/**
	* Constructor
	*/
	CATMshMessage();

	/**
	* Destructor
	*/
	virtual ~CATMshMessage();


	/**
	* Get the code of the message.
	* @return
	*   The code of the message.
	*/
  int GetCode() { return _Code; };


	/**
	* Get the integer data attached to the message.
	* @param oData
	*   An array of size oDataCount containing the integer data
	* @return
	*   The number oDataCount of integer data attached to the message.
	*/
	int GetAttachedData(int **oData);


  /**
  * Get the double data attached to the message.
  * @param oData
  *   An array of size oDataCount containing the doule data
  * @return
  *   The number oDataCount of double data attached to the message.
  */
  int GetAttachedData(double **oData);


	/**
	* Get the description of the message.
	* @return
	*   The description of the message, or empty if there is no description.
	*/
  const char* GetDescription();


	/**
	* Get the severity of the message.
	* @return
	*   The severity of the message.
	*/
  int GetSeverity() { return _Severity; };


	/**
	* Get the origin of the message.
	* @return
	*   The origin of the message.
	*/
  int GetOrigin() { return _Origin; };


  /**
  * @nodoc : intern usage only
  */
  HRESULT SetCode(int iNumber);
  HRESULT SetDescription(const char* iDesc);
  HRESULT SetSeverity(int iSeverity);
  HRESULT SetOrigin(int iFrom);
  HRESULT SetAttachedData(int iDataCount, int *iData);
  HRESULT SetAttachedData(int iDataCount, double *iData);

private:

  std::string _Description;

  double * _dData;

  int _iDataCount;
  int * _iData;
  int _dDataCount;
  int _Severity;
  int _Origin;
  int _Code;

};




ExportedByCATMshMesherCore HRESULT MessageCBEmpty(CATMshMessage *iMsg, void *iUserData);
ExportedByCATMshMesherCore HRESULT MessageCBFile(CATMshMessage *iMsg, void *iUserData);



#endif
