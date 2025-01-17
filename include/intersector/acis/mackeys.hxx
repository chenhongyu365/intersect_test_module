/* $Id: mackeys.hxx,v 1.4 2000/12/26 19:05:42 products Exp $ */
/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/

#ifdef mac

#pragma once


/*  Character Codes  */

	/*  Navigation Keys  */

#define		char_LeftArrow		0x1C
#define		char_RightArrow		0x1D
#define		char_UpArrow		0x1E
#define		char_DownArrow		0x1F

#define		char_Home			0x01
#define		char_End			0x04
#define		char_PageUp			0x0B
#define		char_PageDown		0x0C

	/*  Deletion Keys  */

#define		char_Backspace		0x08
#define		char_FwdDelete		0x7F	/* Only nonprinting above $20 */
#define		char_Clear			0x1B	/* Same as Escape */
#define		vkey_Clear			0x00004700

	/*  Action Keys  */

#define		char_Enter			0x03
#define		char_Tab			0x09
#define		char_Return			0x0D
#define		char_Escape			0x1B	/* Same as Clear */
#define		vkey_Escape			0x00003500

	/*  Special Keys  */

#define		char_Help			0x05
#define		char_Function		0x10	/* All function keys F1 to F15 */
#define		vkey_F1				0x7A	/* Undo */
#define		vkey_F2				0x78	/* Cut */
#define		vkey_F3				0x63	/* Copy */
#define		vkey_F4				0x76	/* Paste */
#define		vkey_F5				0x60
#define		vkey_F6				0x61
#define		vkey_F7				0x62
#define		vkey_F8				0x64
#define		vkey_F9				0x65
#define		vkey_F10			0x6D
#define		vkey_F11			0x67
#define		vkey_F12			0x6F
#define		vkey_F13			0x69	/* Print Screen */
#define		vkey_F14			0x6B	/* Scroll Lock */
#define		vkey_F15			0x71	/* Pause */

	/*  Special Characters  */

#define		char_Propeller		0x11	/* Symbol for Command key */
#define		char_Lozenge		0x12
#define		char_Radical		0x13
#define		char_AppleLogo		0x14

#define		char_FirstPrinting	0x20	/* Nonprinting if less than */
#define		char_Period			0x2E	/* For detecting Command-Period */

#endif
