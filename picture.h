#if !defined(AFX_PICTURE_H__C8CDAC14_D3F5_11D8_9B27_00801E0328BA__INCLUDED_)
#define AFX_PICTURE_H__C8CDAC14_D3F5_11D8_9B27_00801E0328BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CPicture wrapper class

class CPicture : public COleDispatchDriver
{
public:
	CPicture() {}		// Calls COleDispatchDriver default constructor
	CPicture(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CPicture(const CPicture& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	long GetHandle();
	long GetHPal();
	void SetHPal(long);
	short GetType();
	long GetWidth();
	long GetHeight();

// Operations
public:
	// method 'Render' not emitted because of invalid return type or parameter type
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICTURE_H__C8CDAC14_D3F5_11D8_9B27_00801E0328BA__INCLUDED_)
