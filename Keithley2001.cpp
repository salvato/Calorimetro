/////////////////////////////////////////////////////////////////////////////
// Keithley2001.cpp : implementation file
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
#include "Keithley2001.h"


CKeithley2001::CKeithley2001(CWnd* Cal, int Addr)
  : CBolReader(Cal, Addr) {
	inRun	      = false;
	justStarted	= false;
  timeStart   = 0.0;
  pMyValues   = NULL;
}


CKeithley2001::~CKeithley2001(){
  if(pMyValues != NULL) delete pMyValues;
}


bool  
CKeithley2001::ChangeScale(int iScale) {
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
CKeithley2001::ChangeDigits(int iDigits) {
  CString sConf;
	sConf.Format(":sens:volt:dc:dig %d\n", iDigits);
	return Configure(sConf);
}


bool
CKeithley2001::ChangePlc(int iPlc) {
  CString sConf;
	sConf.Format(":sens:volt:dc:nplc %d\n", iPlc);
  return Configure(sConf);
}


bool
CKeithley2001::ChangeAutoZero(int iAutoZero) {
  CString sConf;
	sConf.Format(":syst:azer:stat %d\n", iAutoZero);
  return Configure(sConf);
}


bool
CKeithley2001::myConnect(){
  myUd = ibdev(0, myGpibAddress, 0, T3s, 1, 0);
  if(myUd < 0) {
    errmsg("Connect(Keithley2001): ibdev() Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
// Check for the presence of the device on the bus
  short listen;
  ibln(myUd, myGpibAddress, NO_SAD, &listen);
	if (listen == 0) {
    ibonl(myUd, 0);
    char Error[64];
    sprintf(Error, "Connect(Keithley2001): No Listeners at Addr %d", myGpibAddress);
    errmsg(Error, ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
// Clear the Input Buffer and Output Queue
// Cancel Deferred Commands and 
// Clear any command that prevents the processing of any other device command.
  ibclr(myUd);
  if (ThreadIbsta() & ERR) {
    errmsg("Connect(Keithley2001): ibclr() Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  Sleep(1);// Necessario! NON TOGLIERE!
	gpibwrite(":syst:pres\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Connect(Keithley2001): *rst Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite("*rst\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Connect(Keithley2001): *rst Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
// Clear Status Register and Error Queue
	gpibwrite("*cls\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Connect(Keithley2001): *cls() Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
// Identify The Device
	gpibwrite("*idn?\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Connect(Keithley2001): *idn? Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  strcpy(LastError, "NoError");
	ibrd(myUd, buf, sizeof(buf)-1);
  buf[ThreadIbcnt()] = '\0';
  if (ThreadIbsta() & ERR) {
    errmsg("Connect(Keithley2001): ibrd() Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
	  return false;
  }
  if(strstr(buf, "KEITHLEY INSTRUMENTS INC.,MODEL 2001") == NULL) return false;
  pMyValues = new CReadings("Bol Data");
  return true;
}


bool
CKeithley2001::myDisconnect(){
  gpibwrite("*sre 0\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Disconnect(Keithley2001): *sre0 Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  gpibwrite("*cls\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Disconnect(Keithley2001): *cls Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	return true;
}


void
CKeithley2001::SRQService(long ud, long Ibsta, long Iberr, long Ibcntl, 
                    long FAR* RearmMask) {
  if(msk == 0) {
    errmsg("SRQService(Keithley2001): Stale Interrupt", Ibsta, Iberr, Ibcntl);
    GpibError(LastError);
    *RearmMask = msk;
    return;
  }
  if(Ibsta & ERR) {
    if(!(Iberr & ESRQ)) {
      errmsg("SRQService(Keithley2001): Ibsta Error", Ibsta, Iberr, Ibcntl);
      GpibError(LastError);
    }
  }
  CHAR spb;
	ibrsp(ud, &spb);
  if (ThreadIbsta() & ERR) {
    if(ThreadIberr() & ESTB) {
      GpibError("Keithley2001 Data Lost!");
    } else {
      errmsg("SRQService(Keithley2001): ibrsp() Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
      GpibError(LastError);
    }
    *RearmMask = msk;
    return;
  }
  strcpy(LastError, "NoError");
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
  gpibwrite("*cls\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("SRQService(Keithley2001): *cls Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
  }
  gpibwrite(":data?\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("SRQService(Keithley2001): data? Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
  }
  *RearmMask = msk;
  return;
}


bool
CKeithley2001::StartRun() {
	nData       = 0;
	inRun       = true;
	justStarted = true;
	return true;
}


bool
CKeithley2001::StopRun() {
	inRun = false;
	return true;
}


bool
CKeithley2001::myConfigure(CString sConf){
  msk = 0;
  ibclr(myUd);
  if (ThreadIbsta() & ERR) {
    errmsg("Configure(Keithley2001): ibclr() Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  Sleep(1);// Necessario! NON TOGLIERE!
	gpibwrite("*sre 0\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Configure(Keithley2001): *sre 1 Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":init:cont 0\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Configure(Keithley2001): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":abor\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Configure(Keithley2001): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }

	gpibwrite(sConf);

  if (ThreadIbsta() & ERR) {
    errmsg("Configure(Keithley2001): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }

  gpibwrite("*opc?\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Configure(Keithley2001): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	ibrd(myUd, buf, sizeof(buf)-1);
  if (ThreadIbsta() & ERR) {
    errmsg("Configure(Keithley2001): ibrd() Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
  }
  buf[ThreadIbcnt()] = '\0';          
  int ival = atoi(buf);
  if(ival != 1) {
    errmsg("Configure(Keithley2001): Instrument Busy", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
  }
	gpibwrite(":init:cont 1\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Configure(Keithley2001): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  msk = RQS;
	gpibwrite("*sre 1\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Configure(Keithley2001): *sre 1 Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite("*cls\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2001): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
 	gpibwrite(":data?\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Configure(Keithley2001): ibwrt(:data?) Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  return true;
}


bool
CKeithley2001::myInit() {
  msk = 0;
  gpibwrite("*sre 0\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2001): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":syst:pres\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2001): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":init:cont 0\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2001): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":abor\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2001): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  gpibwrite(":syst:azer:stat 1\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2001): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":syst:azer:type norm\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2001): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":syst:lsync:stat 1\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2001): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":form:elem read,time\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2001): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":arm:sour imm\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2001): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":arm:lay2:sour imm\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2001): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":trig:sour tim\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2001): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":trig:del 0\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2001): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":trig:tcon:dir sour\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2001): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":trig:tim 0.01\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2001): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":stat:meas:ptr 32\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2001): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":stat:meas:enab 32\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2001): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":volt:dc:nplc 1.00\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2001): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":volt:dc:rang max\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2001): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":volt:dc:dig 7\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2001): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":volt:dc:aver:adv:ntol 1\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2001): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":volt:dc:aver:adv 0\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2001): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":volt:dc:aver 0\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2001): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  gpibwrite("*opc?\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2001): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	ibrd(myUd, buf, sizeof(buf)-1);
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2001): ibrd() Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
  }
  buf[ThreadIbcnt()] = '\0';          
  int ival = atoi(buf);
  if(ival != 1) {
    errmsg("Init(Keithley2001): Instrument Busy", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
  }
  gpibwrite(":init:cont 1\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2001): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite(":func 'volt:dc'\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2001): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
  gpibwrite("*sre 1\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2001): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	gpibwrite("*cls\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2001): Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
 	gpibwrite(":data?\r\n");
  if (ThreadIbsta() & ERR) {
    errmsg("Init(Keithley2001): ibwrt(:data?) Failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    GpibError(LastError);
    return false;
  }
	return true;
}


void 
CKeithley2001::SendData(char *message) {
  pParent->SendMessage(BOL_READER_DATA, WPARAM(strlen(message)), LPARAM(message));
}


void 
CKeithley2001::SendRunData(char *message) {
  pParent->SendMessage(BOL_READER_RUN_DATA, WPARAM(strlen(message)), LPARAM(message));
}


