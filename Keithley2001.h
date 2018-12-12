#ifndef __Keithley2001_H
#define __Keithley2001_H

#include "BolReader.h"

class CNotify;
class CReadings;

class
CKeithley2001: public CBolReader {
public:

	CKeithley2001(CWnd* Cal, int Addr);
	~CKeithley2001();
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

#endif

