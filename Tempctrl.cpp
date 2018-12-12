#include <stdafx.h>
#include "dii.h"
#include "TempController.h"
#include "TempCtrl.h"

#define nWRITE				2
#define nSTROBE				4
#define MICROAMP1			3
#define MICROAMP10    1
#define MICROAMP100   2
#define MILLIAMP1			0
#define GAIN1			    0
#define GAIN10				4
#define GAIN100				8
#define DVM200				16
#define DVM2000				32
#define DVM20000			0
#define PORT_MODE0    0x80
#define PORT2         1
#define PORT2A		    3				// Used by the Pulser !!
#define PORT2B		    4
#define PORT2C		    5 

CTempCtrl::CTempCtrl(CWnd* Cal, int Addr) 
: CTempController(Cal, Addr) {

  Current    = 0;
  Resistance = 10000.0;
}


CTempCtrl::~CTempCtrl() {
}


void
CTempCtrl::SRQService(long ud, long Ibsta, long Iberr, long Ibcntl, long FAR* RearmMask) {
}


bool
CTempCtrl::myInit() {
	// Temperature Controller
  if(!DiiSet8255Config(myHandle, PORT2, PORT_MODE0))//#2:Mode0,PortA-Out,PortB-Out,PortC-Out
    return false;
  if(!DiiSetDigitalByte(myHandle, PORT2A, 0))	//Unused
    return false;
  if(!DiiSetDigitalByte(myHandle, PORT2C, nWRITE | nSTROBE))
    return false;
  if(!DiiSetDigitalByte(myHandle, PORT2B, MICROAMP1 | GAIN1))
    return false;
  return true;
}


bool
CTempCtrl::myConnect() {
  char szBoardName[201];
 	strcpy(szBoardName, "PCI_82550001");
  // Set Device Handle
  myHandle = DiiOpenNamedDevice(szBoardName, TRUE);
  if(myHandle==INVALID_HANDLE_VALUE) {
    DiiSelectDevice (NULL, szBoardName, sizeof(szBoardName)-1);
    myHandle = DiiOpenNamedDevice(szBoardName, TRUE);
    if(myHandle==INVALID_HANDLE_VALUE) {
      AfxMessageBox("Error PCI 8255 Not Responding");
      PostQuitMessage(-321);
      return false;
    }
  }//verifica se l'accesso alla scheda
  return true;
}


bool
CTempCtrl::myDisconnect() {
  if(!DiiCloseDevice(myHandle))
    return false;
  return true;
}


bool
CTempCtrl::myConfigure(CString sConf) {
  return false;
}



bool 
CTempCtrl::SetPID(double P_Val, double I_Val, double D_Val) {
  return false;
}


bool 
CTempCtrl::GetPID(double* P_Val, double* I_Val, double* D_Val){
  return false;
}


bool
CTempCtrl::ChangeKSetPoint(double K) {
  return false;
}


bool
CTempCtrl::ChangeRSetPoint(double R) {
  Resistance = R;
  return SetTempController();
}


bool
CTempCtrl::ChangeCurrent(int C) {
  Current = C;
  return SetTempController();
}


bool
CTempCtrl::SetTempController() {
  BOOL result = false;
//-->
// Indica le modifiche apportate per l'inserimento del preamplificatore
// X10 con il CAZ Intersil
//
	switch(Current){
		case 1:// 1uA - 199.99K max
//-->			outportb(PORT2B_BUFFER, MICROAMP1 | GAIN10 | DVM200);
			result = DiiSetDigitalByte(myHandle, PORT2B, MICROAMP1 | GAIN1 | DVM200);
			Resistance /= 10.0;
			break;
		case 2:// 10uA - 19999 max
//-->			outportb(PORT2B_BUFFER, MICROAMP10 | GAIN10 | DVM20000);
			result = DiiSetDigitalByte(myHandle, PORT2B, MICROAMP10 | GAIN1 | DVM20000);
			break;
		case 3:// 10uA - 1999.9 max
//-->			outportb(PORT2B_BUFFER, MICROAMP10 | GAIN100 | DVM2000);
			result = DiiSetDigitalByte(myHandle, PORT2B, MICROAMP10 | GAIN10 | DVM2000);
			Resistance *= 10.0;
			break;
		case 4:// 100uA - 1999.9 max
//-->			outportb(PORT2B_BUFFER, MICROAMP100 | GAIN10 | DVM2000);
			result = DiiSetDigitalByte(myHandle, PORT2B, MICROAMP100 | GAIN1 | DVM2000);
			Resistance *= 10.0;
			break;
		case 5:// 100uA - 199.99 max
//-->			outportb(PORT2B_BUFFER, MICROAMP100 | GAIN100 | DVM200);
			result = DiiSetDigitalByte(myHandle, PORT2B, MICROAMP100 | GAIN10 | DVM200);
			Resistance *= 100.0;
			break;
		case 6:// 1mA - 199.99 max
//-->			outportb(PORT2B_BUFFER, MILLIAMP1 | GAIN10 | DVM200);
			result = DiiSetDigitalByte(myHandle, PORT2B, MILLIAMP1 | GAIN1 | DVM200);
			Resistance *= 100.0;
			break;
    default:
      result = false;
	}
  if(!result) return false;
	WORD DtoA = WORD((Resistance * 3.2767) + 0.5);
	return ProgramDtoA(DtoA);
}


bool
CTempCtrl::ProgramDtoA(WORD DtoA){
  int Delay = 40;// Microsecondi
	if ((DtoA & 0x8000) == 0)
		DtoA |= 0x8000;
	else
		DtoA &= 0x7fff;
	WORD Mask = 0x8000;
	if(!DiiSetDigitalByte(myHandle, PORT2C, nSTROBE)) return false;
  ExactMicroDelay(Delay);
	for (int j = 0; j < 16; j++) {
    int iVal = ((DtoA & Mask)== 0) ? 0 : 1;
		if(!DiiSetDigitalByte(myHandle, PORT2C,  iVal | nSTROBE)) return false;
    ExactMicroDelay(Delay);
		if(!DiiSetDigitalByte(myHandle, PORT2C, iVal)) return false;
    ExactMicroDelay(Delay);
		if(!DiiSetDigitalByte(myHandle, PORT2C, iVal | nSTROBE)) return false;
    ExactMicroDelay(Delay);
		Mask >>= 1;
	}
	if(!DiiSetDigitalByte(myHandle, PORT2C, nWRITE | nSTROBE)) return false;
  ExactMicroDelay(Delay);
  return true;
}


void 
CTempCtrl::ExactMicroDelay(int MicroSeconds) {
  LARGE_INTEGER t0, t1;
  LARGE_INTEGER count_freq;
  LARGE_INTEGER ntick;

  QueryPerformanceCounter(&t0);// Retrieves the current value of the high-resolution performance counter
 
  QueryPerformanceFrequency (&count_freq);// Retrieves the frequency of the high-resolution performance counter
  ntick.QuadPart = (count_freq.QuadPart * MicroSeconds) / 1000000;

  QueryPerformanceCounter(&t1);
  while(t1.QuadPart-t0.QuadPart < ntick.QuadPart) {
    QueryPerformanceCounter(&t1);
  }
}
