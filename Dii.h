////////////////////////////////////////////////////////////////////
//
// Copyright (C) Decision Computer International Co., Ltd
//
//      Dynamic Industrial Interface (DII) V3.0
//
// # Modual Name: Dii.h
//
// # Abstract: Main header file for Dii.dll
//
////////////////////////////////////////////////////////////////////

#define CDEVICELIB_EXPORTS

#ifdef CDEVICELIB_EXPORTS
#define CDEVICELIB_API __declspec(dllexport)
#else
#define CDEVICELIB_API __declspec(dllimport)
#endif

#if !defined(AFX_Dii_H__399A8174_B02D_4493_AFDE_DE52E924A525__INCLUDED_)
#define AFX_Dii_H__399A8174_B02D_4493_AFDE_DE52E924A525__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CDevApp                                                                 //
// See Dii.cpp for the implementation of this class                        //
/////////////////////////////////////////////////////////////////////////////

class CDevApp : public CWinApp
{
public:
	CDevApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDevApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CDevApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
 
/******************************************************************************
******************************************************************************/

// =========================================================================
//                  Device Type Definition
// =========================================================================
// ISA card (not support yet)
#define RD_SMARTLAB_16CHANNEL     0x001
#define RD_SMARTLAB_8CHANNEL      0x002
#define RD_ICC_8RELAY8ISOLATOR    0x003
#define RD_ICC_16RELAY            0x004
#define RD_ICC_16ISOLATOR         0x005
#define RD_ICC_8SSR8LOGIC         0x006
#define RD_TTL                    0x007
#define RD_IBC_32ISOLATOR         0x009
#define RD_ADVANCE_ADDA           0x100
#define RD_SUPER_12BIT_ADDA       0x101
#define RD_12BIT_ADDA             0x102
#define RD_8CHANNEL_DA            0x103
#define RD_SUPER_14BIT_ADDA       0x104

// PCI card
#define RD_PCI_IND_4CHANNEL       0x200
#define RD_PCI_4RELAY4ISOLATOR    0X201
#define RD_PCI_8RELAY8ISOLATOR    0X202
#define RD_PCI_16RELAY16ISOLATOR  0X203
#define RD_PCI_8255               0X204
#define RD_PCI_MULTI_8255         0X205
#define RD_PCI_12BIT_ADDA         0X206
#define RD_PCI_14BIT_ADDA         0x207

// =========================================================================
//               Function Prototype (Function Interface)
// =========================================================================
// -------------------------------------------------------------------------
//					Functions to open and close Devices
// -------------------------------------------------------------------------

extern "C" CDEVICELIB_API HANDLE WINAPI DiiOpenDevice(
						  DWORD,		// device type
						  DWORD,		// index of Device
						  BOOL);		// open exclusively

extern "C" CDEVICELIB_API HANDLE WINAPI DiiOpenNamedDevice(
						  LPTSTR,		// device name
						  BOOL);		// open exclusively

extern "C" CDEVICELIB_API BOOL WINAPI DiiCloseDevice(
						  HANDLE);		// handle of previously opened Device

// -------------------------------------------------------------------------
//				 	Functions to enumerate or browse Devices
// -------------------------------------------------------------------------

extern "C" CDEVICELIB_API BOOL WINAPI DiiSelectDevice(
						  HWND,			 // handle of parent window or NULL
						  LPTSTR,		 // points to the name of the adapter selected
						  DWORD);        // points to the maximum string length of the adapter

extern "C" CDEVICELIB_API BOOL WINAPI DiiGetInstalledDevice (
						  DWORD,		 // device number (different from device index)
						  LPTSTR,		 // points to the name of the adapter selected
						  DWORD);		 // points to the maximum string length of the adapter

// -------------------------------------------------------------------------
//			Functions to retrieve information about an Device
// -------------------------------------------------------------------------

extern "C" CDEVICELIB_API DWORD WINAPI DiiGetNumberOfDigitalChannels (
                          HANDLE);        // a handle of an Device previously opened

extern "C" CDEVICELIB_API BOOL WINAPI DiiGetNumberOfDigitalInOutChannels (
					      HANDLE,	      // a handle of an Device previously opened
			              LPDWORD,	      // a pointer to the number of INPUT channels
			              LPDWORD);	      // a pointer to the number of OUTPUT channels

extern "C" CDEVICELIB_API DWORD WINAPI DiiGetNumberOfAnalogChannels (
			              HANDLE);        // a handle of an Device previously opened

extern "C" CDEVICELIB_API BOOL WINAPI DiiGetNumberOfAnalogInOutChannels (
			              HANDLE,	      // a handle of an Device previously opened
			              LPDWORD,	      // a pointer to the number of INPUT channels
			              LPDWORD);	      // a pointer to the number of OUTPUT channels

extern "C" CDEVICELIB_API DWORD WINAPI DiiGetResolution(
			              HANDLE );       // a handle of an Device previously opened


// -------------------------------------------------------------------------
//			Functions to for digital input/output
// -------------------------------------------------------------------------

extern "C" CDEVICELIB_API BOOL WINAPI DiiSetDigitalBit(
						  HANDLE ,	     // a handle of an Device previously opened
						  DWORD ,		 // the number of the port to write
						  BOOL);		 // the value to write to the channel
						

extern "C" CDEVICELIB_API BOOL WINAPI DiiSetDigitalByte (
						  HANDLE,		 // a handle of an Device previously opened
						  DWORD,		 // the number of the port to write
						  BYTE);		 // the value to write to the channel

	// return value: TRUE if the value was written
	// successfully, FALSE otherwise.
	// see GetLastError error codes for more detailed information
extern "C" CDEVICELIB_API BOOL WINAPI DiiSetDigitalWord (
						  HANDLE,        // a handle of an Device previously opened
						  DWORD,         // the number of the port to write
						  WORD);         // the value to write to the channel

	// return value: TRUE if the value was written
	// successfully, FALSE otherwise.
	// see GetLastError error codes for more detailed information

extern "C" CDEVICELIB_API BOOL WINAPI DiiGetDigitalBit(
						  HANDLE ,	     // a handle of an Device previously opened
						  DWORD ,		 // the number of the port to write
						  LPBOOL);		 // the value to write to the channel
							
	// return value: TRUE if the value was written
	// successfully, FALSE otherwise.
	// see GetLastError error codes for more detailed information


extern "C" CDEVICELIB_API BOOL WINAPI DiiGetDigitalByte (
						  HANDLE,		 // a handle of an Device previously opened
						  DWORD,		 // the number of the port to read
						  LPBYTE);	     // points to the value read from the port

	// return value: TRUE if the value was written
	// successfully, FALSE otherwise.
	// see GetLastError error codes for more detailed information
extern "C" CDEVICELIB_API BOOL WINAPI DiiGetDigitalWord (
						  HANDLE,        // a handle of an Device previously opened
						  DWORD,         // the number of the port to read
						  LPWORD);       // points to the value read from the port


	// return value: TRUE if the value was read
	// successfully, FALSE otherwise.
	// see GetLastError error codes for more detailed information
//
// DiiGetOutputPortByte reads the state of an output port, either
// directly from the card, or from the port cache of the kernel drivers
// (if any)
//

extern "C" CDEVICELIB_API BOOL WINAPI DiiGetOutputPort (
						  HANDLE,		 // a handle of an Device previously opened
						  DWORD,		 // the number of the output port to read
						  LPBYTE);	     // points to the value read from the port


// -------------------------------------------------------------------------
//			Functions to configure digital channels.
// -------------------------------------------------------------------------

// For 8255 Cards, you may also set the chip configuration
// directly using DiiSetChipConfig.

extern "C" CDEVICELIB_API BOOL WINAPI DiiSet8255Config (
						  HANDLE,		 // a handle of an Device previously opened
						  DWORD,		 // the index of the chip to configure
						  BYTE);		 // the new configuration byte for the chip




// -------------------------------------------------------------------------
//          Function to configure analog input / output channels
// -------------------------------------------------------------------------

// These function setup a (programmable) gain for an adapter, either
// for input or output channels.
extern "C" CDEVICELIB_API BOOL WINAPI DiiSetChannelGain (
			              HANDLE,	     // a handle of a device previously opened
			              BOOL,		     // indicates whether an input (TRUE) or output (FALSE) channel is set
			              DWORD,	     // indicates the channel number
			              double);	     // indicates the channel gain to be set

extern "C" CDEVICELIB_API BOOL WINAPI DiiGetChannelGain (
			              HANDLE,	     // a handle of a device previously opened
			              BOOL,		     // indicates, whether an input (TRUE) or output (FALSE) channel is set
			              DWORD,	     // indicates the channel number
			              double*);      // indicates the channel gain to be set

// Sets the uni-polar or bi-polar mode per channel:
extern "C" CDEVICELIB_API BOOL WINAPI DiiSetChannelBipolar (
			              HANDLE,	     // a handle of a device previously opened
			              BOOL,		     // indicates, whether an input (TRUE) or output (FALSE) channel is set
			              DWORD,	     // indicates the channel number
			              BOOL);	     // if TRUE, the channel is set to bipolar, FALSE otherwise

extern "C" CDEVICELIB_API BOOL WINAPI DiiGetChannelBipolar (
			              HANDLE,   	 // a handle of a device previously opened
			              BOOL,		     // indicates, whether an input (TRUE) or output (FALSE) channel is set
			              DWORD,	     // indicates the channel number
			              BOOL*);	     // if TRUE, the channel is set to bipolar, FALSE otherwise

// Set the range that is being captured on the channel. This range
// is user configured and is adjusted to the AD-range the device
// physically supports.
extern "C" CDEVICELIB_API BOOL WINAPI DiiSetChannelRange (
			              HANDLE,		 // a handle of a device previously opened
						  BOOL,			 // indicates, whether an input (TRUE) or output (FALSE) channel is set
						  DWORD,		 // indicates the channel number
						  double,		 // specifies the minimum value for the channel
						  double);		 // specifies the maximum value for the channel

extern "C" CDEVICELIB_API BOOL WINAPI DiiGetChannelRange (
						  HANDLE,		 // a handle of a device previously opened
						  BOOL,			 // indicates, whether an input (TRUE) or output (FALSE) channel is set
						  DWORD,		 // indicates the channel number
						  double *,		 // receives the minimum value for the channel
						  double *);	 // receives the maximum value for the channel

// 
// This function returns the range of AD values that are available
// for this channel. It takes into account the physical limitations
// of the AD device, as well as the currently selected gain for
// the specified channel.
extern "C" CDEVICELIB_API BOOL WINAPI DiiGetDeviceChannelRange (
			              HANDLE,	     // a handle of a device previously opened
			              BOOL,		     // indicates, whether an input (TRUE) or output (FALSE) channel is set
			              DWORD,	     // indicates the channel number
			              double*,	     // receives the minimum value for the channel
			              double*);      // receives the maximum value for the channel

extern "C" CDEVICELIB_API BOOL WINAPI DiiSetADTrigMethod (
						  HANDLE,	     // a handle of a device previously opened								  
						  DWORD);         // indicates the Trig mode



extern "C" CDEVICELIB_API BOOL WINAPI DiiSetADEnableInterrupt (
						  HANDLE,	     // a handle of a device previously opened
						  BOOL);         // indicates the Enable/Disable interrupt
// -------------------------------------------------------------------------
//			       Functions to access timers on cards:
// -------------------------------------------------------------------------

extern "C" CDEVICELIB_API BOOL WINAPI DiiSetTimerConfig (
						  HANDLE,		 // a handle of an Device previously opened
						  DWORD,		 // the index of the timer to configure
						  DWORD);		 // the configuration of the timer

extern "C" CDEVICELIB_API BOOL WINAPI DiiLoadTimer (
						  HANDLE,		 // a handle of an Device previously opened
						  DWORD,		 // the index of the timer to configure
						  DWORD);		 // the value to load into the timer

extern "C" CDEVICELIB_API BOOL WINAPI DiiGetTimer (
						  HANDLE,		 // a handle of an Device previously opened
						  DWORD,		 // the index of the timer to configure
						  LPDWORD);	     // points to a variable receiving the current value of the timer

					

// -------------------------------------------------------------------------
//			Functions for analog input / output
// -------------------------------------------------------------------------

// DiiSetAnalogChannel writes a value to be output on the analog channel.
extern "C" CDEVICELIB_API BOOL WINAPI DiiSetAnalogChannel (
			              HANDLE,	     // a handle of an Device previously opened
			              DWORD,	     // the index of the channel to write to
			              DWORD);   	 // the value to write to the channel
			
// SetRealAnalogChannel set a single AD channel value from the card
extern "C" CDEVICELIB_API BOOL WINAPI DiiSetRealAnalogChannel (
			              HANDLE,	     // a handle of a device previously opened
			              DWORD,	     // indicates the channel number
			              double);	     // the new value of the channel

// DiiReadAnalog reads a value from a specific analog channel
extern "C" CDEVICELIB_API BOOL WINAPI DiiGetAnalogChannel (
			              HANDLE,	     // a handle of an Device previously opened
			              DWORD,	     // the number of the channel to read
			              LPDWORD);	     // points to the value read from the channel

// DiiGetRealAnalogChannel retrieve a single AD channel value from the card
extern "C" CDEVICELIB_API BOOL WINAPI DiiGetRealAnalogChannel (
			              HANDLE,	     // a handle of a device previously opened
			              DWORD,	     // indicates the channel number
			              double *);     // the current value of the channel


						  						

#endif // !defined(AFX_Dii_H__399A8174_B02D_4493_AFDE_DE52E924A525__INCLUDED_)
