//////////////////////////////////////////////////////////////////////
// Keithley263.cpp: implementation of the CKeithley263 class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ni488.h"
#include "Keithley263.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKeithley263::CKeithley263(CWnd* Cal, int Addr)
  : CCurrGen(Cal, Addr) {
}


CKeithley263::~CKeithley263() {
}


bool
CKeithley263::myConnect() {
  myUd = ibdev(0, myGpibAddress, 0, T3s, 1, 0x180A);
  if(myUd < 0) {
    errmsg("Connect(Current Generator): ibdev() Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
// Check for the presence of the device on the bus
  short listen;
  ibln(myUd, myGpibAddress, NO_SAD, &listen);
	if (listen == 0) {
    ibonl(myUd, 0);
    char Error[64];
    sprintf(Error, "Connect(Current Generator): Nolistener at Addr %d", myGpibAddress);
    errmsg(Error, ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }

  ibclr(myUd);
  if (ThreadIbsta() & ERR) {
    errmsg("Connect(Current Generator): ibclr() Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }

  return true;
}


bool
CKeithley263::myDisconnect(){
  return true;
}


bool
CKeithley263::myInit() {
  return true;
}


bool
CKeithley263::myConfigure(CString sConf) {
	gpibwrite(sConf);
  if (ThreadIbsta() & ERR) {
    errmsg("Configure(Current Generator): ibwrt() Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  msk = RQS;
	return true;
}

void
CKeithley263::SRQService(long ud, long Ibsta, long Iberr, long Ibcntl, long FAR* RearmMask) {
  if(msk == 0) {
    errmsg("SRQService(Current Generator): Stale Interrupt", Ibsta, Iberr, Ibcntl);
    GpibError(LastError);
    *RearmMask = msk;
    return;
  }
  if(Ibsta & ERR) {
    if(!(Iberr & ESRQ)) {
      errmsg("SRQService(Current Generator): Ibsta Error", Ibsta, Iberr, Ibcntl);
      GpibError(LastError);
    *RearmMask = msk;
    return;
    }
  }
  *RearmMask = msk;
  return;
}


bool 
CKeithley263::ChangeCurrent(double NewCurrent) {
//  int iStat = gpibwrite("Y0X");
  CString sConf;
	if (NewCurrent < 2.0E-12)
		sConf = "F1R1Z1X";
	else if(NewCurrent < 20.0E-12)
		sConf = "F1R2Z1X";
	else if(NewCurrent < 200.0E-12)
		sConf = "F1R3Z1X";
	else if(NewCurrent < 2.0E-9)
		sConf = "F1R4Z1X";
	else if(NewCurrent < 20.0E-9)
		sConf = "F1R5Z1X";
	else if(NewCurrent < 200.0E-9)
		sConf = "F1R6Z1X";
	else if(NewCurrent < 2.0E-6)
		sConf = "F1R7Z1X";
	else if(NewCurrent < 20.0E-6)
		sConf = "F1R8Z1X";
	else if(NewCurrent < 200.0E-6)
		sConf = "F1R9Z1X";
	else if(NewCurrent < 2.0E-3)
		sConf = "F1R10Z1X";
	else if(NewCurrent < 20.0E-3)
		sConf = "F1R11Z1X";
	else {
    NewCurrent = 1.0E-12;
		sConf = "F1R1Z1X";
	}
  Configure(sConf);
	sConf.Format("V%gO1X", NewCurrent);
	return Configure(sConf);
}
