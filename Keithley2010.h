//////////////////////////////////////////////////////////////////////
// Keithley2010.h: interface for the CKeithley2010 class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KEITHLEY2010_H__F95B0860_BA12_11D8_9B27_00801E0328BA__INCLUDED_)
#define AFX_KEITHLEY2010_H__F95B0860_BA12_11D8_9B27_00801E0328BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BolReader.h"

class 
CKeithley2010 : public CBolReader {
public:
	CKeithley2010(CWnd* Cal, int Addr);
	virtual ~CKeithley2010();
  void          SRQService(long, long, long, long, long FAR*);
	virtual bool  StartRun();
	virtual bool  StopRun();

	virtual bool  ChangeScale(int iScale);
  virtual bool  ChangeDigits(int iDigits);
	virtual bool  ChangePlc(int iPlc);
	virtual bool  ChangeAutoZero(int iAutoZero);

private:
	virtual bool  myConfigure(CString sConf);
  virtual bool  myInit();
	virtual bool  myDisconnect();
	virtual bool  myConnect();
	void SendData(char *message);
	void SendRunData(char *message);
  CReadings*    pMyValues;
	double 		    x, t;
	bool 			    justStarted;
	bool          inRun;
	double		    timeStart;
	long          nData;

};

#endif // !defined(AFX_KEITHLEY2010_H__F95B0860_BA12_11D8_9B27_00801E0328BA__INCLUDED_)
