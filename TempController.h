// TempController.h: interface for the CTempController class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEMPCONTROLLER_H__44718E41_C07C_11D8_9B27_00801E0328BA__INCLUDED_)
#define AFX_TEMPCONTROLLER_H__44718E41_C07C_11D8_9B27_00801E0328BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <sys/timeb.h>
#include "Afxtempl.h"
#include "Zone.h"
#include "GpibInstrument.h"

class CReadings;

class 
CTempController : public CGpibInstrument {
public:
	CTempController(CWnd* Cal, int Addr);
	virtual ~CTempController();

  void          SRQService(long, long, long, long, long FAR*);
	virtual bool  myConfigure(CString sConf);
  virtual bool  myInit();
	virtual bool  myDisconnect();
	virtual bool  myConnect();
	virtual bool  StartRun();
	virtual bool  StopRun();

	virtual bool ChangeKSetPoint(double K);
	virtual bool ChangeRSetPoint(double R);
	virtual bool ChangeCurrent(int Current);
	virtual bool GetCurrent(int *Current);
	virtual bool GetHeater(int *Heater);
	virtual bool Heater(int iHeater);
	virtual bool SetPID(double P_Val, double I_Val, double D_Val);
	virtual bool GetPID(double* P_Val, double* I_Val, double* D_Val);
  virtual bool StartReadingR();
  virtual bool StopReadingR();
 	bool ReadChebCoef(CString FileName);

protected:
	double Cnv(double r);
	void SendData(char *message);
	void SendRunData(char *message);
  CReadings*    pMyValues;
	struct _timeb timebuffer;
	double x, t;
	bool 	 justStarted;
	bool   inRun;
	double timeStart;
	double time0;
	double rMin, rMax;
	CArray<CZone, CZone&>  rZone;
};

#endif // !defined(AFX_TEMPCONTROLLER_H__44718E41_C07C_11D8_9B27_00801E0328BA__INCLUDED_)
