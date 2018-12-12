//////////////////////////////////////////////////////////////////////
// LakeShore370.cpp: implementation of the CLakeShore370 class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ni488.h"
#include "resource.h"
#include "Readings.h"
#include "LakeShore370.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLakeShore370::CLakeShore370(CWnd* Cal, int Addr)
  :CTempController(Cal, Addr) {
  inRun	      = false;
	justStarted	= false;
  _ftime(&timebuffer);
  time0 = timebuffer.time + timebuffer.millitm/1000.0;
  pMyValues = NULL; 
}


CLakeShore370::~CLakeShore370() {
  msk=0;
  gpibwrite("*CLS\r\n");
  gpibwrite("*SRE000\r\n");
  gpibwrite("*RST\r\n");
  if(pMyValues != NULL) delete pMyValues;
}


bool
CLakeShore370::StartRun() {
	inRun = true;
	justStarted = true;
	return true;
}


bool
CLakeShore370::StopRun() {
	inRun = false;
	return true;
}


bool
CLakeShore370::myConnect(){
  CWaitCursor WaitCursor;
  myUd = ibdev(0, myGpibAddress, 0, T10s, 1, 0x140A);
  if(myUd < 0) {
    errmsg("Connect(LakeShore370): ibdev() Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }

// Check for the presence of the device on the bus
  short listen;
  ibln(myUd, myGpibAddress, NO_SAD, &listen);
	if(listen == 0) {
    ibonl(myUd, 0);
    char Error[64];
    sprintf(Error, "Connect(LakeShore370): No Listeners at Addr %d", myGpibAddress);
    errmsg(Error, ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
// Set Instrument Parameters to Power-On settings.
	gpibwrite("*RST\r\n");
  if(ThreadIbsta() & ERR) {
    errmsg("Connect(LakeShore370): *RST() Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  Sleep(6000);
// Clear the Interface, Status Byte Register, Standard Event Status Register
// and terminate All pending operations.
	gpibwrite("*CLS\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Connect(LakeShore370): *CLS Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
  }

// Identify The Device
	gpibwrite("*IDN?\r\n");
  if (ThreadIbsta() & ERR) {
	  gpibwrite("*CLS\r\n");
    errmsg("Connect(LakeShore370): *IDN? Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
  }
  strcpy(LastError, "NoError");
	ibrd(myUd, buf, sizeof(buf)-1);
  buf[ThreadIbcnt()] = '\0';
  if(strstr(buf, "LSCI,MODEL370") == NULL) {
    errmsg("Connect(LakeShore370): Different Device at Specified Address\r\n Run Low Level Configuration\r\n", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  if (ThreadIbsta() & ERR) {
    errmsg("Connect(LakeShore370): Error on LakeShore370\r\nSwitch it Off and the On Again", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }

  return true;
}


bool
CLakeShore370::myDisconnect(){
  gpibwrite("*SRE000\r\n");
  if(ThreadIbsta() & ERR) {
    errmsg("Disconnect(LakeShore370): *SRE 0 Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  gpibwrite("*CLS\r\n");
  if(ThreadIbsta() & ERR) {
    errmsg("Disconnect(LakeShore370): *CLS Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  gpibwrite("*RST\r\n");
  if(ThreadIbsta() & ERR) {
    errmsg("Disconnect(LakeShore370): *CLS Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	return true;
}


bool
CLakeShore370::myInit() {
  msk = 0;
  gpibwrite("*SRE 0\r\n");
  if(ThreadIbsta() & ERR) {
    errmsg("Disconnect(LakeShore370): *SRE 0 Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  return true;//myInit()
}


bool
CLakeShore370::myConfigure(CString sConf){
  gpibwrite("*SRE000\r\n");
  gpibwrite("*CLS\r\n");
  msk = 0;
  if(ThreadIbsta() & ERR) {
    errmsg("Disconnect(LakeShore370): *SRE 0 Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }

	gpibwrite(sConf);

  if(ThreadIbsta() & ERR) {
    errmsg("Configure(LakeShore370): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  msk = RQS;
  return true;
}


void
CLakeShore370::SRQService(long ud, long Ibsta, long Iberr, long Ibcntl, 
                    long FAR* RearmMask) {
  _ftime(&timebuffer);
  t = timebuffer.time + timebuffer.millitm/1000.0;
  if(msk == 0) {
    errmsg("SRQService(LakeShore370): Stale Interrupt", Ibsta, Iberr, Ibcntl);
    GpibError(LastError);
    *RearmMask = msk;
    return;
  }
  if(Ibsta & ERR) {
    if(!(Iberr & ESRQ)) {
      errmsg("SRQService(LakeShore370): Ibsta Error", Ibsta, Iberr, Ibcntl);
      GpibError(LastError);
    }
  }
  double x;
  ibrd(ud, buf, sizeof(buf)-1);       
  if (ThreadIbsta() & ERR) {
    errmsg("SRQService(LakeShore370): ibrd() Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
  } else {
    buf[ThreadIbcnt()] = '\0';
    //x= atof(buf);
  	x = Cnv(atof(buf));
    pMyValues->NewValue(x);
    if(inRun && justStarted) {
  		  justStarted = false;
  		  timeStart = t;
    }
  	if (x > 1.0e12) {
  	  x = 1.0e12;
  	}
  	sprintf(cmd, "%g;%g", t-time0, x);
    SendData(cmd);
    if(inRun) {
  	  sprintf(cmd, "%g;%g", t-timeStart, x);
      SendRunData(cmd);
    }
  }
  gpibwrite("RDGR?\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("SRQService(LakeShore370): fetc Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    gpibwrite("RDGR?\r\n");// try once again
  }
  *RearmMask = msk;
  return;
}


bool 
CLakeShore370::ChangeRSetPoint(double R) {
  CString RSetPoint;
  RSetPoint.Format("SETP %g\r\n", R);
  return Configure(RSetPoint);
}


bool
CLakeShore370::ChangeKSetPoint(double K) {
  CString KSetPoint;
  KSetPoint.Format("SETP %g\r\n", K);
  return Configure(KSetPoint);
}


bool
CLakeShore370::ChangeCurrent(int iCurrent) {
  if(iCurrent < 0 || iCurrent > 21)
    return false;
  CString sCurrent;
  sCurrent.Format("RDGRNG 0,1,%d,22,1,0\r\n", iCurrent+1);

  return Configure(sCurrent);
}


bool
CLakeShore370::Heater(int iHeater) {
  if(iHeater < 0 || iHeater > 8)
    return false;
  CString sHeater;
  sHeater.Format("HTRRNG %d\r\n", iHeater);

  return Configure(sHeater);
}


bool
CLakeShore370::GetHeater(int* iHeater) {
  StopReadingR();
	gpibwrite("HTRRNG?\r\n");
  if (ThreadIbsta() & ERR) {
	  gpibwrite("*CLS\r\n");
    errmsg("Connect(LakeShore370): HTRRNG? Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
  }
  strcpy(LastError, "NoError");
	ibrd(myUd, buf, sizeof(buf)-1);
  buf[ThreadIbcnt()] = '\0';
  StartReadingR();
  try {
    *iHeater = atoi(buf);
  } catch(...) {
    return false;
  }
  return true;
}


bool
CLakeShore370::GetPID(double* P_Val, double* I_Val, double* D_Val) {
  StopReadingR();
	gpibwrite("PID?\r\n");
  if (ThreadIbsta() & ERR) {
	  gpibwrite("*CLS\r\n");
    errmsg("Connect(LakeShore370): PID? Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
  }
  strcpy(LastError, "NoError");
	ibrd(myUd, buf, sizeof(buf)-1);
  buf[ThreadIbcnt()] = '\0';
  StartReadingR();
  try {
    *P_Val = atof(strtok(buf, ","));
    *I_Val = atof(strtok(0, ","));
    *D_Val = atof(strtok(0, "\0"));
  } catch(...) {
    return false;
  }
  return true;
}


bool
CLakeShore370::SetPID(double P_Val, double I_Val, double D_Val) {
  if((P_Val < 0.001) || (P_Val > 1000.0))
    return false;
  if((I_Val < 0.0) || (I_Val > 10000.0))
    return false;
  if((D_Val < 0.0) || (D_Val > 2500.0))
    return false;
  CString Command;
  Command.Format("PID %.3f,%5.0f,%4.0f\r\n", P_Val, I_Val, D_Val);
	gpibwrite(Command);
  if (ThreadIbsta() & ERR) {
	  gpibwrite("*CLS\r\n");
    errmsg("(LakeShore370): SetPID Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  return true;
}


bool
CLakeShore370::GetCurrent(int *Current) {
  StopReadingR();
	gpibwrite("RDGRNG? 1\r\n");
  if (ThreadIbsta() & ERR) {
	  gpibwrite("*CLS\r\n");
    errmsg("Connect(LakeShore370): RDGRNG? Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
  }
  strcpy(LastError, "NoError");
	ibrd(myUd, buf, sizeof(buf)-1);
  buf[ThreadIbcnt()] = '\0';
  StartReadingR();
  int dummy;
  try {
    dummy = atoi(strtok(buf, ","));
    *Current = atoi(strtok(0, ",")) - 1;
  } catch(...) {
    return false;
  }
  return true;
}


bool
CLakeShore370::StartReadingR() {
  msk = RQS;
  gpibwrite("*SRE068\r\n");
  _ftime(&timebuffer);
  if(pMyValues == NULL) pMyValues = new CReadings("Ge Data");
  gpibwrite("RDGR?\r\n");
  return true;
}


bool
CLakeShore370::StopReadingR() {
  gpibwrite("*SRE000\r\n");
  gpibwrite("*CLS\r\n");
  msk = 0;
  return true;
}


