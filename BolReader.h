//////////////////////////////////////////////////////////////////////
// BolReader.h: interface for the CBolReader class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOLREADER_H__68B43540_B95C_11D8_9B27_00801E0328BA__INCLUDED_)
#define AFX_BOLREADER_H__68B43540_B95C_11D8_9B27_00801E0328BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GpibInstrument.h"

class CNotify;
class CReadings;


class 
CBolReader : public CGpibInstrument {
public:
	CBolReader(CWnd* Cal, int Addr);
	virtual ~CBolReader();
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
	void          SendData(char *message);
	void          SendRunData(char *message);
  CReadings*    pMyValues;
	double 		    x, t;
	bool 			    justStarted;
	bool          inRun;
	double		    timeStart;
	long          nData;

};

#endif // !defined(AFX_BOLREADER_H__68B43540_B95C_11D8_9B27_00801E0328BA__INCLUDED_)
