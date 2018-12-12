#ifndef __TEMPCTRL_H       /* prevent multiple includes */
#define __TEMPCTRL_H

#include "TempController.h"

class
CTempCtrl : public CTempController {
public:
	CTempCtrl(CWnd* Cal, int Addr);
	virtual  ~CTempCtrl();

  void         SRQService(long, long, long, long, long FAR*);
	virtual bool ChangeKSetPoint(double K);
	virtual bool ChangeRSetPoint(double R);
	virtual bool ChangeCurrent(int C);
	virtual bool SetPID(double P_Val, double I_Val, double D_Val);
	virtual bool GetPID(double* P_Val, double* I_Val, double* D_Val);

private:
	virtual bool  myConfigure(CString sConf);
  virtual bool  myInit();
	virtual bool  myDisconnect();
	virtual bool  myConnect();

	HANDLE myHandle;
  bool SetTempController();
	bool ProgramDtoA(WORD DtoA);
  int Current;
  double Resistance;
  void ExactMicroDelay(int MicroSeconds);
};
#endif