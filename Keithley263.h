//////////////////////////////////////////////////////////////////////
// Keithley263.h: interface for the CKeithley263 class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KEITHLEY263_H__68B43544_B95C_11D8_9B27_00801E0328BA__INCLUDED_)
#define AFX_KEITHLEY263_H__68B43544_B95C_11D8_9B27_00801E0328BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CurrGen.h"

class 
CKeithley263 : public CCurrGen {
public:
	virtual bool ChangeCurrent(double dCurrent);
	CKeithley263(CWnd* Cal, int Addr);
	virtual ~CKeithley263();

private:
	virtual bool  myConfigure(CString sConf);
  virtual bool  myInit();
	virtual bool  myDisconnect();
	virtual bool  myConnect();
  virtual void  SRQService(long ud, long Ibsta, long Iberr, long Ibcntl, long FAR* RearmMask);
};

#endif // !defined(AFX_KEITHLEY263_H__68B43544_B95C_11D8_9B27_00801E0328BA__INCLUDED_)
