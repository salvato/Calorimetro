//////////////////////////////////////////////////////////////////////
// LakeShore370.h: interface for the CLakeShore370 class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LAKESHORE370_H__2BB119A0_BFA7_11D8_9B27_00801E0328BA__INCLUDED_)
#define AFX_LAKESHORE370_H__2BB119A0_BFA7_11D8_9B27_00801E0328BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TempController.h"

class
CLakeShore370 
: public CTempController {
public:
	bool GetCurrent(int *Current);
	bool SetPID(double P_Val, double I_Val, double D_Val);
	bool GetPID(double* P_Val, double* I_Val, double* D_Val);
	bool Heater(int iHeater);
	bool GetHeater(int* iHeater);
	virtual bool ChangeCurrent(int C);
	CLakeShore370(CWnd* Cal, int Addr);
	virtual ~CLakeShore370();

  void          SRQService(long ud, long Ibsta, long Iberr, long Ibcntl, long FAR* RearmMask);
	virtual bool  myConfigure(CString sConf);
  virtual bool  myInit();
	virtual bool  myDisconnect();
	virtual bool  myConnect();

	virtual bool ChangeKSetPoint(double K);
	virtual bool ChangeRSetPoint(double R);
  virtual bool StartReadingR();
  virtual bool StopReadingR();
	virtual bool StartRun();
	virtual bool StopRun();

};

#endif // !defined(AFX_LAKESHORE370_H__2BB119A0_BFA7_11D8_9B27_00801E0328BA__INCLUDED_)
