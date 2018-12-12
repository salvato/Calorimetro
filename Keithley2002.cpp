/////////////////////////////////////////////////////////////////////////////
// Keithley2002.cpp : implementation file
/////////////////////////////////////////////////////////////////////////////

//***********************************************************
// Ricordarsi che il timer del multimetro ha un overflofw
// ogni 99999.999999 secondi e che questo overflow potrebbe
// causare problemi nel caso che il multimetro resti acceso
// per piu' di 24 ore.
//***********************************************************

#include "stdafx.h"

#include "ni488.h"
#include "Readings.h"
#include "Keithley2002.h"


CKeithley2002::CKeithley2002(CWnd* Cal, int Addr)
  :CBolReader(Cal, Addr) {
	inRun	      = false;
	justStarted	= false;
  timeStart   = 0.0;
  pMyValues   = NULL;
}


CKeithley2002::~CKeithley2002(){
  if(pMyValues != NULL) delete pMyValues;
}


bool  
CKeithley2002::ChangeScale(int iScale) {
  CString sConf;

	if(iScale == 1)
		sConf = ":sens:volt:dc:rang 0.2\n";
	else if(iScale == 2)
		sConf = ":sens:volt:dc:rang 2\n";
	else if(iScale == 3)
		sConf = ":sens:volt:dc:rang 20\n";
	else if(iScale == 4)
		sConf = ":sens:volt:dc:rang 200\n";
	else
		sConf = ":sens:volt:dc:rang 1000\n";

  return Configure(sConf);
}


bool
CKeithley2002::ChangeDigits(int iDigits) {
  CString sConf;
	sConf.Format(":sens:volt:dc:dig %d\n", iDigits);
	return Configure(sConf);
}


bool
CKeithley2002::ChangePlc(int iPlc) {
  CString sConf;
	sConf.Format(":sens:volt:dc:nplc %d\n", iPlc);
  return Configure(sConf);
}


bool
CKeithley2002::ChangeAutoZero(int iAutoZero) {
  CString sConf;
	sConf.Format(":syst:azer:stat %d\n", iAutoZero);
  return Configure(sConf);
}


bool
CKeithley2002::myConnect(){
  myUd = ibdev(0, myGpibAddress, 0, T1s, 1, 0);
  if(myUd < 0) {
    errmsg("Connect(Keithley2002): ibdev() Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
// Check for the presence of the device on the bus
  short listen;
  ibln(myUd, myGpibAddress, NO_SAD, &listen);
	if(listen == 0) {
    ibonl(myUd, 0);
    char Error[64];
    sprintf(Error, "Connect(Keithley2002): No Listeners at Addr %d", myGpibAddress);
    errmsg(Error, ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
// Identify The Device
	gpibwrite("*idn?\n");
  if (ThreadIbsta() & ERR) {
	  gpibwrite("*cls\n");
    errmsg("Connect(Keithley2002): *idn? Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
  }
  strcpy(LastError, "NoError");
	ibrd(myUd, buf, sizeof(buf)-1);
  buf[ThreadIbcnt()] = '\0';
  if(strstr(buf, "KEITHLEY INSTRUMENTS INC.,MODEL 2002") == NULL) {
    errmsg("Connect(Keithley2002): Different device at Specified Address\r\n Run Low Level Configuration\r\n", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  if (ThreadIbsta() & ERR) {
    errmsg("Connect(Keithley2002): Error on Keithley2002\r\nSwitch it Off and the On Again", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  // Resets Controls in INIT, ARM:LAY1, ARM:LAY2 and TRIG subsystems
  // and put trigger model in IDLE state.
	gpibwrite("*rst\n");
  if(ThreadIbsta() & ERR) {
    errmsg("Connect(Keithley2002): *rst() Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  //Reset Status subsystem (not affected by *RST)
	gpibwrite("stat:pres;*cls\n");
  if(ThreadIbsta() & ERR) {
    errmsg("Connect(Keithley2002): *cls() Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":syst:pres\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Connect(Keithley2001): *rst Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  pMyValues = new CReadings("Bol Data");
  return true;
}


bool
CKeithley2002::myDisconnect(){
  gpibwrite("*sre 0\n");
  if(ThreadIbsta() & ERR) {
    errmsg("Disconnect(Keithley2002): *sre0 Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  gpibwrite("*cls\n");
  if(ThreadIbsta() & ERR) {
    errmsg("Disconnect(Keithley2002): *cls Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	return true;
}


void
CKeithley2002::SRQService(long ud, long Ibsta, long Iberr, long Ibcntl, 
                    long FAR* RearmMask) {
  if(msk == 0) {
    errmsg("SRQService(Kei2002): Stale Interrupt", Ibsta, Iberr, Ibcntl);
    GpibError(LastError);
    *RearmMask = msk;
    return;
  }
  if(Ibsta & ERR) {
    if(!(Iberr & ESRQ)) {
      errmsg("SRQService(Kei2002): Ibsta Error", Ibsta, Iberr, Ibcntl);
      GpibError(LastError);
    }
  }
  CHAR spb;
	ibrsp(ud, &spb);
  if(ThreadIbsta() & ERR) {
    if(ThreadIberr() & ESTB) {
      GpibError("Kei2002 Data Lost!");
    } else {
      errmsg("SRQService(Kei2002): ibrsp() Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
      GpibError(LastError);
    }
    *RearmMask = msk;
    return;
  }
  strcpy(LastError, "NoError");
	gpibwrite(":data?\n");
  if(ThreadIbsta() & ERR) {
    errmsg("SRQService(Kei2002): ibwrt(:data?) Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    *RearmMask = msk;
    return;
  }
	ibrd(ud, buf, sizeof(buf)-1);
  if(!(ThreadIbsta() & ERR)) {
    buf[ThreadIbcnt()] = '\0';          
  	x = atof(strtok(buf, ","));
    t = atof(strtok(0, "\0"));
    if(inRun && justStarted) {
  	  justStarted = false;
  	  timeStart = t;
  	}
    if(x > 1000.0) {
      x = 1000.0;
  	}
    if(pMyValues != NULL) pMyValues->NewValue(x);
  	sprintf(cmd, "%g;%g", t, x);
    SendData(cmd);
    if(inRun) {
  	  sprintf(cmd, "%g;%g", t-timeStart, x);
      SendRunData(cmd);
     	nData++;
    }
  } else {
    GpibError("Err");
  }
  gpibwrite("*cls\n");
  if(ThreadIbsta() & ERR) {
    errmsg("SRQService(Kei2002): *cls Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
  }
  *RearmMask = msk;
  return;
}


bool
CKeithley2002::StartRun() {
	nData       = 0;
	inRun       = true;
	justStarted = true;
	return true;
}


bool
CKeithley2002::StopRun() {
	inRun = false;
	return true;
}


bool
CKeithley2002::myConfigure(CString sConf){
  msk = 0;
  gpibwrite("*sre 0\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Configure(Kei2002): *sre 1 Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":init:cont 0\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Configure(Keithley2002): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":abor\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Configure(Keithley2002): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }

	gpibwrite(sConf);

  if (ThreadIbsta() & ERR) {
    errmsg("Configure(Keithley2002): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":init:cont 1\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Configure(Keithley2002): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }

  msk = RQS;
	gpibwrite("*sre 1\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Configure(Keithley2002): *sre 1 Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  return true;
}


bool
CKeithley2002::myInit() {
  msk = 0;
  gpibwrite("*sre 0\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2002): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":syst:pres\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2002): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":init:cont 0\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2002): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":abor\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2002): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  gpibwrite(":syst:azer:stat 1\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2002): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":syst:azer:type sync\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2002): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":syst:lsync:stat 1\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2002): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":form:elem read,time\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2002): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":arm:sour imm\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2002): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":arm:lay2:sour imm\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2002): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":trig:sour tim\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2002): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":trig:del 0\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2002): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":trig:tcon:dir sour\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2002): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":trig:tim 0.01\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2002): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":stat:meas:ptr 32\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2002): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":stat:meas:enab 32\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2002): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":volt:dc:nplc 1.00\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2002): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":sens:volt:dc:rang max\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2002): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":sens:volt:dc:dig 7\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2002): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":sens:volt:dc:aver:adv:ntol 1\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2002): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":sens:volt:dc:aver:adv 0\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2002): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":sens:volt:dc:aver 0\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2002): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":sens:func 'volt:dc'\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2002): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":syst:amet norm\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2002): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  gpibwrite(":init:cont 1\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2002): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  gpibwrite("*cls\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2002): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  return true;//myInit()
}


void 
CKeithley2002::SendData(char *message) {
  pParent->SendMessage(BOL_READER_DATA, WPARAM(strlen(message)), LPARAM(message));
}


void 
CKeithley2002::SendRunData(char *message) {
  pParent->SendMessage(BOL_READER_RUN_DATA, WPARAM(strlen(message)), LPARAM(message));
}

