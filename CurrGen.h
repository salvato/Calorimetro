//////////////////////////////////////////////////////////////////////
// CurrGen.h: interface for the CCurrGen class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CURRGEN_H__68B43543_B95C_11D8_9B27_00801E0328BA__INCLUDED_)
#define AFX_CURRGEN_H__68B43543_B95C_11D8_9B27_00801E0328BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GpibInstrument.h"

class 
CCurrGen : public CGpibInstrument {

public:
	virtual bool ChangeCurrent(double dCurrent);
	CCurrGen(CWnd* Cal, int Addr);
	virtual ~CCurrGen();
  virtual void  SRQService(long ud, long Ibsta, long Iberr, long Ibcntl, long FAR* RearmMask);

protected:
	virtual bool  myConfigure(CString sConf);
  virtual bool  myInit();
	virtual bool  myDisconnect();
	virtual bool  myConnect();
private:
};

#endif // !defined(AFX_CURRGEN_H__68B43543_B95C_11D8_9B27_00801E0328BA__INCLUDED_)
