//////////////////////////////////////////////////////////////////////
// GpibInstrument.cpp: implementation of the CGpibInstrument class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "ni488.h"
#include "GpibInstrument.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGpibInstrument::CGpibInstrument(CWnd* Parent, int Addr)
: pParent(Parent), myGpibAddress(Addr) {
  Connected     = false;
  Initialized   = false;
  Configured    = false;
  pGpibNotify   = NULL;
  msk           = 0;
  strcpy(LastError, "NoError");
}


CGpibInstrument::~CGpibInstrument() {
}


bool
CGpibInstrument::Connect() {
  if(Connected)
    return true;
  Connected = myConnect();
  return Connected;
}


bool
CGpibInstrument::Init(CGpibNotify* pNotify) {
  if(pNotify == NULL) {
    Initialized = myInit();
    return Initialized;
  }
  strcpy(LastError, "NoError");
  if(Initialized)
    return true;
  if(!Connected) {
    strcpy(LastError, "Init: Trying to Connect");
    pParent->SendMessage(GPIB_MSG, WPARAM(strlen(LastError)), LPARAM(LastError));
    if(!Connect()) {
      strcpy(LastError, "Init: Fail to Connect");
      pParent->SendMessage(GPIB_MSG, WPARAM(strlen(LastError)), LPARAM(LastError));
      return false;
    }
  }
  pGpibNotify = pNotify;
  VARIANT mask;
  msk = RQS;
  VariantInit(&mask);
  mask.vt = VT_I4;
	mask.lVal = msk;
	if (pGpibNotify->SetupNotify(myUd, mask) & ERR) {
    errmsg("GpibInstrument-Init(): SetupNotify failed!", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    pParent->SendMessage(GPIB_MSG, WPARAM(strlen(LastError)), LPARAM(LastError));
    return false;
  }
	if (ThreadIbsta() & ERR) {
    errmsg("GpibInstrument-Init(): SetupNotify failed!", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
    pParent->SendMessage(GPIB_MSG, WPARAM(strlen(LastError)), LPARAM(LastError));
    return false;
  }
  Initialized = myInit();
  return Initialized;
}


bool
CGpibInstrument::Configure(CString sConf) {
  if(!CouldConfigure()) {
    return false;
  }
  if(!myConfigure(sConf))
    Configured = false;
  else
    Configured = true;
  return Configured;
}


bool
CGpibInstrument::CouldConfigure() {
  return Connected && Initialized;
}


bool
CGpibInstrument::Disconnect() {
  if(!Initialized)
    return true;
 
  myDisconnect();

  if(pGpibNotify != NULL) {
    int msk = 0;
    VARIANT mask;
    strcpy(LastError, "NoError");
    VariantInit(&mask);
    mask.vt = VT_I4;
	  mask.lVal = 0;
	  pGpibNotify->SetupNotify(myUd, mask);
	  if(ThreadIbsta() & ERR)	{
      errmsg("Disconnect(): SetupNotify failed", ThreadIbsta(), ThreadIberr(), ThreadIbcntl());
      pParent->SendMessage(GPIB_MSG, WPARAM(strlen(LastError)), LPARAM(LastError));
      return false;
    }
  }

  ibclr(myUd);
  Sleep(1);
  Initialized = false;
  Connected   = false;
  Configured  = false;
  ibonl(myUd, 0);
  return true;
}


char*
CGpibInstrument::GetError() {
  return LastError;
}


void
CGpibInstrument::errmsg(char *msg, int sta, int err, long cntl) {
	char tempbuf[20];

	sprintf(LastError, "%s", msg);
  strcat(LastError, "\r\nsta = 0x");
	_itoa(sta, tempbuf, 16);
	strcat(LastError, tempbuf);
	strcat(LastError, " <");
  if (sta & ERR )  strcat(LastError, " ERR");
  if (sta & TIMO)  strcat(LastError, " TIMO");
  if (sta & END )  strcat(LastError, " END");
  if (sta & SRQI)  strcat(LastError, " SRQI");
  if (sta & RQS )  strcat(LastError, " RQS");
  if (sta & CMPL)  strcat(LastError, " CMPL");
  if (sta & LOK )  strcat(LastError, " LOK");
  if (sta & REM )  strcat(LastError, " REM");
  if (sta & CIC )  strcat(LastError, " CIC");
  if (sta & ATN )  strcat(LastError, " ATN");
  if (sta & TACS)  strcat(LastError, " TACS");
  if (sta & LACS)  strcat(LastError, " LACS");
  if (sta & DTAS)  strcat(LastError, " DTAS");
  if (sta & DCAS)  strcat(LastError, " DCAS");
 
  sprintf(tempbuf, ">\r\nerr = %d", err);
  strcat(LastError, tempbuf);
  if (err == EDVR) strcat(LastError, " EDVR <DOS Error>");
  if (err == ECIC) strcat(LastError, " ECIC <Not CIC>");
  if (err == ENOL) strcat(LastError, " ENOL <No Listener>");
  if (err == EADR) strcat(LastError, " EADR <Address error>");
  if (err == EARG) strcat(LastError, " EARG <Invalid argument>");
  if (err == ESAC) strcat(LastError, " ESAC <Not Sys Ctrlr>");
  if (err == EABO) strcat(LastError, " EABO <Op. aborted>");
  if (err == ENEB) strcat(LastError, " ENEB <No GPIB board>");
  if (err == EOIP) strcat(LastError, " EOIP <Async I/O in prg>");
  if (err == ECAP) strcat(LastError, " ECAP <No capability>");
  if (err == EFSO) strcat(LastError, " EFSO <File sys. error>");
  if (err == EBUS) strcat(LastError, " EBUS <Command error>");
  if (err == ESTB) strcat(LastError, " ESTB <Status byte lost>");
  if (err == ESRQ) strcat(LastError, " ESRQ <SRQ stuck on>");
  if (err == ETAB) strcat(LastError, " ETAB <Table Overflow>");
 
  sprintf(tempbuf, "\r\ncntl = %lX", cntl);
  strcat(LastError, tempbuf);
}


void 
CGpibInstrument::GpibError(char *message) {
  pParent->SendMessage(GPIB_MSG, WPARAM(strlen(LastError)), LPARAM(message));
}


int
CGpibInstrument::gpibwrite(char *cmd) {
  return int(ibwrt(myUd, cmd, long(strlen(cmd))));
}


int 
CGpibInstrument::gpibwrite(CString sCmd) {
  char* cmd = new char[sCmd.GetLength()+1];
  strcpy(cmd, sCmd);
  int iStat = int(ibwrt(myUd, cmd, long(strlen(cmd))));
  delete[] cmd;
  return iStat;
}


bool
CGpibInstrument::myConfigure(CString sConf) {
  return false;
}


bool
CGpibInstrument::myInit() {
  return false;
}


bool
CGpibInstrument::myDisconnect() {
  return false;
}


bool
CGpibInstrument::myConnect() {
  return false;
}

