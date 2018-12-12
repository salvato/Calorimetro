//////////////////////////////////////////////////////////////////////////////////
// In Configurazione OHM
//////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "ni488.h"
#include "math.h"
#include <fstream>
#include "Readings.h"
#include "HP34401.h"


CHP34401::CHP34401(CWnd* Cal, int Addr)
  :CGeReader(Cal, Addr) {
  inRun	      = false;
	justStarted	= false;
  _ftime(&timebuffer);
  time0 = timebuffer.time + timebuffer.millitm/1000.0;
  pMyValues = NULL;
}


CHP34401::~CHP34401() {
  if(pMyValues != NULL) delete pMyValues;
}


bool
CHP34401::StartRun() {
	inRun = true;
	justStarted = true;
	return true;
}


bool
CHP34401::StopRun() {
	inRun = false;
	return true;
}


bool
CHP34401::myConnect(){
  myUd = ibdev(0, myGpibAddress, 0, T1s, 1, 0);
  if(myUd < 0) {
    errmsg("Connect(HP34401): ibdev() Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
// Check for the presence of the device on the bus
  short listen;
  ibln(myUd, myGpibAddress, NO_SAD, &listen);
	if (listen == 0) {
    ibonl(myUd, 0);
    char Error[64];
    sprintf(Error, "Connect(HP34401): Nolistener at Addr %d", myGpibAddress);
    errmsg(Error, ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
// Clear the Input Buffer and Output Queue
// Cancel Deferred Commands and 
// Clear any command that prevents the processing of any other device command.
  ibclr(myUd);
  if (ThreadIbsta() & ERR) {
    errmsg("Connect(HP34401): ibclr() Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
// Identify The Device
	gpibwrite("*idn?\n");
  if (ThreadIbsta() & ERR) {
	  gpibwrite("*cls\n");
    errmsg("Connect(HP34401): *idn? Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
  }
  strcpy(LastError, "NoError");
	ibrd(myUd, buf, sizeof(buf)-1);
  buf[ThreadIbcnt()] = '\0';
  if(strstr(buf, "HEWLETT-PACKARD,34401A") == NULL) {
    errmsg("Connect(HP34401): Different device at Specified Address\r\n Run Low Level Configuration\r\n", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  if (ThreadIbsta() & ERR) {
    errmsg("Connect(HP34401): Error on Keithley2002\r\nSwitch it Off and the On Again", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite("*rst\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Connect(HP34401): *rst Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite("*cls\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Connect(HP34401): *cls() Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  pMyValues = new CReadings("Ge Data");
  return true;
}


bool
CHP34401::myInit() {
	ibclr(myUd);
  if (ThreadIbsta() & ERR) {
    errmsg("Init(HP34401): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  gpibwrite("conf:fres 1e8, 1e2\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(HP34401): conf:fres 1e8, 1e2 Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  gpibwrite("trig:sour imm\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(HP34401): trig:sour imm Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  gpibwrite("*sre 16\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(HP34401): *sre16 Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  gpibwrite("init\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(HP34401): init Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  gpibwrite("fetc?\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(HP34401): fetc? Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  return true;
}


bool
CHP34401::myConfigure(CString sConf){
  strcpy(LastError, "NoError");
  msk = 0;
  ibclr(myUd);
  if (ThreadIbsta() & ERR) {
    errmsg("Configure(HP34401): ibclr() Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  gpibwrite("*rst\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(HP34401): *rst Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  gpibwrite("*cls\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(HP34401): *cls Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }

	gpibwrite(sConf);
  
  if (ThreadIbsta() & ERR) {
    errmsg("Configure(HP34401): conf:fres Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }

  gpibwrite("*sre 16\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(HP34401): *sre16 Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  gpibwrite("init\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Configure(HP34401): init Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  gpibwrite("fetc?\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Configure(HP34401): init Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  msk = RQS;
  return true;
}


void
CHP34401::SRQService(long ud, long Ibsta, long Iberr, long Ibcntl, long FAR* RearmMask) {
  _ftime(&timebuffer);
  t = timebuffer.time + timebuffer.millitm/1000.0;
  if(msk == 0) {
    errmsg("SRQService(HP34401): Stale Interrupt", Ibsta, Iberr, Ibcntl);
    GpibError(LastError);
    *RearmMask = msk;
    return;
  }
  if(Ibsta & ERR) {
    if(!(Iberr & ESRQ)) {
      errmsg("SRQService(HP34401): Ibsta Error", Ibsta, Iberr, Ibcntl);
      GpibError(LastError);
    }
  }
  CHAR spb;
  ibrsp(ud, &spb);
  if (ThreadIbsta() & ERR) {
    if(ThreadIberr() & ESTB) {
      GpibError("HP34401 Data Lost!");
    } else {
      errmsg("SRQService(HP34401): ibrsp() Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    }
    *RearmMask = msk;
    return;
  }
  strcpy(LastError, "NoError");
  ibrd(ud, buf, sizeof(buf)-1);       
  if (ThreadIbsta() & ERR) {
    errmsg("SRQService(HP34401): ibrd() Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
  } else {
    buf[ThreadIbcnt()] = '\0';          
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
    gpibwrite("init\r\n");
    if (ThreadIbsta() & ERR) {
      errmsg("SRQService(HP34401): init Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
      GpibError(LastError);
      *RearmMask = msk;
      return;
    }
  }
  gpibwrite("fetc?\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("SRQService(HP34401): fetc Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    gpibwrite("fetc?\r\n");// try once again
  }
  *RearmMask = msk;
  return;
}


bool
CHP34401::myDisconnect() {
  gpibwrite(":abor\r\n");
  gpibwrite("*sre 0\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Disconnect(HP34401): *sre0 Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  gpibwrite("*cls\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Disconnect(HP34401): *cls Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  return true;
}


void 
CHP34401::SendData(char *message) {
  pParent->SendMessage(GE_READER_DATA, WPARAM(strlen(message)), LPARAM(message));
}


void 
CHP34401::SendRunData(char *message) {
  pParent->SendMessage(GE_READER_RUN_DATA, WPARAM(strlen(message)), LPARAM(message));
}


bool 
CHP34401::ChangeScale(int iScale) {
  CString sConf;
	if (iScale == 1)
		  sConf = "conf:fres 1e2, 1e-4\r\n";
	else if(iScale == 2)
		sConf = "conf:fres 1e3, 1e-3\r\n";
	else if(iScale == 3)
		sConf = "conf:fres 1e4, 1e-2\r\n";
	else if(iScale == 4)
		sConf = "conf:fres 1e5, 1e-1\r\n";
	else if(iScale == 5)
		sConf = "conf:fres 1e6, 1e0\r\n";
	else if(iScale == 6)
		sConf = "conf:fres 1e7, 1e1\r\n";
	else
		sConf = "conf:fres 1e8, 1e2\r\n";

	return Configure(sConf);
}
