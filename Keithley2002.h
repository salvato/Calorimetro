#ifndef __Keithley2002_H
#define __Keithley2002_H

#include "BolReader.h"

class CReadings;

class
CKeithley2002: public CBolReader {
public:

	CKeithley2002(CWnd* Cal, int Addr);
	~CKeithley2002();
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

